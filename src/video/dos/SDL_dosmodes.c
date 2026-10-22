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

#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_DOSVESA

// SDL internals
#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "SDL_dosframebuffer_c.h"

// DOS declarations
#अन्तर्भाव "SDL_dosmodes.h"
#अन्तर्भाव "SDL_dosvideo.h"
#अन्तर्भाव <sys/movedata.h> // for dosmemput (banked framebuffer access)

// Some VESA usage information:
//   https://delorie.com/djgpp/doc/ug/graphics/vesa.html.en
//   https://delorie.com/djgpp/doc/ug/graphics/vbe20.html
//   https://wiki.osdev.org/User:Omarrx024/VESA_Tutorial
//   https://wiki.osdev.org/VESA_Video_Modes
//   https://www.phatcode.net/res/221/files/vbe20.pdf

// VBE mode attribute bits (ModeAttributes field)
#परिभाषय VBE_MODEATTR_SUPPORTED 0x01 // bit 0: mode supported in hardware
#परिभाषय VBE_MODEATTR_COLOR     0x08 // bit 3: color mode (vs. monochrome)
#परिभाषय VBE_MODEATTR_GRAPHICS  0x10 // bit 4: graphics mode (vs. text)
#परिभाषय VBE_MODEATTR_LFB       0x80 // bit 7: linear framebuffer available

// Minimum required mode attributes for usable graphics modes
#परिभाषय VBE_MODEATTR_REQUIRED (VBE_MODEATTR_SUPPORTED | VBE_MODEATTR_COLOR | VBE_MODEATTR_GRAPHICS)

// VBE memory model types (MemoryModel field)
#परिभाषय VBE_MEMMODEL_PACKED_PIXEL 4 // packed pixel (includes 8-bit indexed)
#परिभाषय VBE_MEMMODEL_प्रत्यक्षम्_COLOR 6 // direct color (RGB with masks)

// VBE set-mode flag
#परिभाषय VBE_SETMODE_LFB 0x4000 // request linear framebuffer when setting mode

// VBE mode list sentinel
#परिभाषय VBE_MODELIST_अन्तः 0xFFFF

// VGA mode 13h (320x200x256) is universally supported, but most VESA
// BIOSes do not include it in their VESA mode list. This sentinel
// value is used to identify the legacy fallback.
#परिभाषय VGA_बहुलकम्_13_H_SENTINEL 0xFFEE
#परिभाषय VGA_बहुलकम्_13_H_SEGMENT  0xA000

#निर्देशः pack(प्रक्षिप, 1)
// this is the struct from the hardware; we save only a few parts from this, later, in SDL_VESAInfo.
प्रकारनिर्देश संरचना SDL_VESAHardwareInfo
{
    Uint8 VESASignature[4];
    Uint16 VESAVersion;
    Uint32 OEMStringPtr; // segment:offset
    Uint8 Capabilities[4];
    Uint32 Video_बहुलकम्_Ptr; // segment:offset
    Uint16 योग_स्मृतिः;
    Uint16 OEMSoftwareRev;
    Uint32 OEMVendorNamePtr;  // segment:offset
    Uint32 OEMProductNamePtr; // segment:offset
    Uint32 OEMProductRevPtr;  // segment:offset
    Uint8 Reserved[222];
    Uint8 Oem_दत्त[256];
} SDL_VESAHardwareInfo;

प्रकारनिर्देश संरचना SDL_VESAModeHardwareInfo
{
    Uint16 बहुलकम्_गुणाः;
    Uint8 WinAAttributes;
    Uint8 WinBAttributes;
    Uint16 WinGranularity;
    Uint16 Win_आकार;
    Uint16 WinASegment;
    Uint16 WinBSegment;
    Uint32 WinFuncPtr;
    Uint16 अष्टकानि_प्रत्येकम्_अवलोकनम्_पङ्क्तिः;
    Uint16 XResolution;
    Uint16 YResolution;
    Uint8 XChar_आकार;
    Uint8 YChar_आकार;
    Uint8 सङ्ख्या_सम्बन्धि_Planes;
    Uint8 द्वयङ्काः_प्रत्येकम्_Pixel;
    Uint8 सङ्ख्या_सम्बन्धि_Banks;
    Uint8 स्मृतिः_Model;
    Uint8 Bank_आकार;
    Uint8 सङ्ख्या_सम्बन्धि_Image_पृष्ठानि;
    Uint8 Reserved_page;
    Uint8 Red_आवरणम्_आकार;
    Uint8 Red_आवरणम्_Pos;
    Uint8 Green_आवरणम्_आकार;
    Uint8 Green_आवरणम्_Pos;
    Uint8 Blue_आवरणम्_आकार;
    Uint8 Blue_आवरणम्_Pos;
    Uint8 Reserved_आवरणम्_आकार;
    Uint8 Reserved_आवरणम्_Pos;
    Uint8 प्रत्यक्षम्_Color_बहुलकम्_Info;
    Uint32 Phys_आधारः_Ptr;
    Uint32 Off_Screen_Mem_विस्थापनम्;
    Uint16 Off_Screen_Mem_आकार;
    Uint8 Reserved[206];
} SDL_VESAModeHardwareInfo;
#निर्देशः pack(निष्कासय)

प्रकारनिर्देश संरचना SDL_VESAInfo
{
    Uint16 संस्करणम्;              // 0x200 == 2.0, etc.
    Uint32 योग_स्मृतिः_2;         // in bytes (SDL_VESAHardwareInfo::TotalMemory does it in 64k pages).
    Uint32 video_addr_segoffset; // real mode segment:offset (only valid while VBE info block is allocated!)
    Uint16 *बहुलकम्_list;           // copied out of conventional memory before freeing
    पूर्णाङ्क अङ्कः_modes;
    Uint16 oem_software_revision;
    वर्ण *oem_string;
    वर्ण *oem_vendor;
    वर्ण *oem_गुणनफलम्;
    वर्ण *oem_revision;
} SDL_VESAInfo;

स्थिर SDL_VESAInfo *vesa_info = रिक्त;

शून्य DOSVESA_FreeVESAInfo(शून्य)
{
    यदि (vesa_info) {
        SDL_free(vesa_info->बहुलकम्_list);
        SDL_free(vesa_info->oem_string);
        SDL_free(vesa_info->oem_vendor);
        SDL_free(vesa_info->oem_गुणनफलम्);
        SDL_free(vesa_info->oem_revision);
        SDL_free(vesa_info);
        vesa_info = रिक्त;
    }
}

स्थिर ध्रुव SDL_VESAInfo *GetVESAInfo(शून्य)
{
    यदि (vesa_info) {
        प्रत्यागम vesa_info;
    }

    _go32_dpmi_seginfo hwinfo_seginfo;
    SDL_VESAHardwareInfo *hwinfo = (SDL_VESAHardwareInfo *)DOS_Allocate_Conventional_स्मृतिः(परिमाण(*hwinfo), &hwinfo_seginfo);
    यदि (!hwinfo) {
        प्रत्यागम रिक्त;
    }

    SDL_zerop(hwinfo);
    SDL_memcpy(hwinfo->VESASignature, "VBE2", 4);

    __dpmi_regs regs;
    regs.x.ax = 0x4F00;
    regs.x.es = DOS_रैखिकम्_गन्तव्यम्_Physical(hwinfo) / 16;
    regs.x.di = DOS_रैखिकम्_गन्तव्यम्_Physical(hwinfo) & 0xF;
    __dpmi_int(0x10, &regs);

    // al is 0x4F if VESA is supported, ah is 0x00 if this specific call succeeded.
    // If the interrupt call didn't replace VESASignature with "VESA" then something went wrong, too.
    यदि ((regs.x.ax != 0x004F) || (SDL_memcmp(hwinfo->VESASignature, "VESA", 4) != 0)) {
        SDL_समुच्चयः_Error("VESA video not supported on this system");
    } अन्यथा {
        vesa_info = (SDL_VESAInfo *)SDL_calloc(1, परिमाण(*vesa_info));
        यदि (vesa_info) {
            vesa_info->संस्करणम् = hwinfo->VESAVersion;
            vesa_info->योग_स्मृतिः_2 = ((Uint32)hwinfo->योग_स्मृतिः) * (64 * 1024); // TotalMemory is 64k chunks, convert to bytes.
            vesa_info->video_addr_segoffset = hwinfo->Video_बहुलकम्_Ptr;
            vesa_info->oem_software_revision = hwinfo->OEMSoftwareRev;
            // these strings are often empty (or maybe NULL), but it's fine. We don't _actually_ need them.
            vesa_info->oem_string = DOS_GetFarPtrCString(hwinfo->OEMStringPtr);
            vesa_info->oem_vendor = DOS_GetFarPtrCString(hwinfo->OEMVendorNamePtr);
            vesa_info->oem_गुणनफलम् = DOS_GetFarPtrCString(hwinfo->OEMProductNamePtr);
            vesa_info->oem_revision = DOS_GetFarPtrCString(hwinfo->OEMProductRevPtr);

            // Copy the mode list out of conventional memory BEFORE freeing
            // the VBE info block. Some VESA BIOSes store the mode list
            // inside the 512-byte info block itself. If we free the block
            // first, the mode list pointer becomes dangling and we read
            // garbage, silently losing modes.
            {
                Uint32 segoffset = vesa_info->video_addr_segoffset;
                पूर्णाङ्क गणनम् = 0;
                यावत् (DOS_PeekUint16(segoffset + गणनम् * परिमाण(Uint16)) != VBE_MODELIST_अन्तः) {
                    गणनम्++;
                    यदि (गणनम् > 64)
                        भङ्ग; // sanity limit
                }
                vesa_info->अङ्कः_modes = गणनम्;
                vesa_info->बहुलकम्_list = (Uint16 *)SDL_malloc(गणनम् * परिमाण(Uint16));
                यदि (vesa_info->बहुलकम्_list) {
                    प्रति (पूर्णाङ्क i = 0; i < गणनम्; i++) {
                        vesa_info->बहुलकम्_list[i] = DOS_PeekUint16(segoffset + i * परिमाण(Uint16));
                    }
                } अन्यथा {
                    vesa_info->अङ्कः_modes = 0;
                }
            }
        }
    }

    DOS_Free_Conventional_स्मृतिः(&hwinfo_seginfo);

    प्रत्यागम vesa_info;
}

// Check for VGA using BIOS function GET DISPLAY COMBINATION CODE.
// Call INT 0x10 with AX=0x1A00; function is supported if AL=0x1A.
// Returns true for VGA-compatible hardware. 
स्थिर bool DetectVGA(शून्य)
{
    __dpmi_regs regs = {};
    regs.x.ax = 0x1A00;
    __dpmi_int(0x10, &regs);
    प्रत्यागम ((regs.x.ax & 0x00FF) == 0x001A);
}

bool DOSVESA_SupportsVESA(शून्य)
{
    // We need at least VGA hardware (for mode 13h). EGA and CGA cards
    // do not support 256 colors or programmable palettes.
    यदि (!DetectVGA()) {
        प्रत्यागम SDL_समुच्चयः_Error("No VGA card detected");
    }

    // Cache VESA info if available (NULL mean we only have VGA).
    (शून्य)GetVESAInfo();

    प्रत्यागम true;
}

ध्रुव वर्ण *DOSVESA_GetGPUName(शून्य)
{
    ध्रुव SDL_VESAInfo *vinfo = GetVESAInfo();
    यदि (!vinfo) {
        प्रत्यागम "VGA";
    }

    यदि (vinfo->oem_गुणनफलम् && *vinfo->oem_गुणनफलम्) {
        प्रत्यागम vinfo->oem_गुणनफलम्;
    }
    यदि (vinfo->oem_vendor && *vinfo->oem_vendor) {
        प्रत्यागम vinfo->oem_vendor;
    }
    यदि (vinfo->oem_string && *vinfo->oem_string) {
        प्रत्यागम vinfo->oem_string;
    }

    प्रत्यागम "VESA";
}

Uint32 DOSVESA_Get_VESATotal_स्मृतिः(शून्य)
{
    ध्रुव SDL_VESAInfo *info = GetVESAInfo();
    प्रत्यागम info ? info->योग_स्मृतिः_2 : 0;
}

स्थिर bool GetVESAModeInfo(Uint16 बहुलकम्_id, SDL_Display_बहुलकम्_दत्त *info)
{
    _go32_dpmi_seginfo hwinfo_seginfo;
    SDL_VESAModeHardwareInfo *hwinfo = (SDL_VESAModeHardwareInfo *)DOS_Allocate_Conventional_स्मृतिः(परिमाण(*hwinfo), &hwinfo_seginfo);
    यदि (!hwinfo) {
        प्रत्यागम false;
    }

    SDL_zerop(hwinfo);

    __dpmi_regs regs;
    regs.x.ax = 0x4F01;
    regs.x.es = DOS_रैखिकम्_गन्तव्यम्_Physical(hwinfo) / 16;
    regs.x.di = DOS_रैखिकम्_गन्तव्यम्_Physical(hwinfo) & 0xF;
    regs.x.cx = बहुलकम्_id;
    __dpmi_int(0x10, &regs);

    ध्रुव bool retval = (regs.x.ax == 0x004F);
    यदि (retval) {
        SDL_zerop(info);
        info->बहुलकम्_id = बहुलकम्_id;
        info->गुणाः = hwinfo->बहुलकम्_गुणाः;
        info->pitch = hwinfo->अष्टकानि_प्रत्येकम्_अवलोकनम्_पङ्क्तिः;
        info->w = hwinfo->XResolution;
        info->h = hwinfo->YResolution;
        info->अङ्कः_planes = hwinfo->सङ्ख्या_सम्बन्धि_Planes;
        info->bpp = hwinfo->द्वयङ्काः_प्रत्येकम्_Pixel;
        info->स्मृतिः_model = hwinfo->स्मृतिः_Model;
        info->अङ्कः_image_पृष्ठानि = hwinfo->सङ्ख्या_सम्बन्धि_Image_पृष्ठानि;
        info->red_आवरणम्_आकार = hwinfo->Red_आवरणम्_आकार;
        info->red_आवरणम्_pos = hwinfo->Red_आवरणम्_Pos;
        info->green_आवरणम्_आकार = hwinfo->Green_आवरणम्_आकार;
        info->green_आवरणम्_pos = hwinfo->Green_आवरणम्_Pos;
        info->blue_आवरणम्_आकार = hwinfo->Blue_आवरणम्_आकार;
        info->blue_आवरणम्_pos = hwinfo->Blue_आवरणम्_Pos;
        info->physical_आधारः_addr = hwinfo->Phys_आधारः_Ptr;

        // VBE 1.2 banked framebuffer fields
        info->has_lfb = (hwinfo->बहुलकम्_गुणाः & VBE_MODEATTR_LFB) != 0;
        info->win_granularity = hwinfo->WinGranularity;
        info->win_आकार = hwinfo->Win_आकार;
        info->win_a_segment = hwinfo->WinASegment;
        info->win_func_ptr = hwinfo->WinFuncPtr;
        info->win_a_गुणाः = hwinfo->WinAAttributes;
    }

    DOS_Free_Conventional_स्मृतिः(&hwinfo_seginfo);

    प्रत्यागम retval;
}

bool DOSVESA_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display)
{
    ध्रुव SDL_VESAInfo *vinfo = GetVESAInfo();

    // Enumerate VESA modes if we have a VBE 1.2+ BIOS.  Older VBE versions
    // (1.0, 1.1) or no VESA at all just skip this loop and fall through to
    // the VGA mode 13h fallback below.
    पूर्णाङ्क अङ्कः_vesa_modes = (vinfo && vinfo->संस्करणम् >= 0x102) ? vinfo->अङ्कः_modes : 0;

    प्रति (पूर्णाङ्क mi = 0; mi < अङ्कः_vesa_modes; mi++) {
        ध्रुव Uint16 modeid = vinfo->बहुलकम्_list[mi];

        SDL_Display_बहुलकम्_दत्त info;
        यदि (!GetVESAModeInfo(modeid, &info)) {
            अनुवर्त;
        }

        // Skip 320x200x8 from VESA. We always want VGA mode 13h for this
        // resolution (no page flip, no LFB overhead, universal compatibility).
        यदि (info.bpp == 8 && info.w == 320 && info.h == 200) {
            अनुवर्त;
        }

        यदि ((info.गुणाः & VBE_MODEATTR_REQUIRED) != VBE_MODEATTR_REQUIRED) {
            अनुवर्त;
        }

        यदि (!(info.गुणाः & VBE_MODEATTR_LFB) && (info.win_a_गुणाः & VBE_WINATTR_USABLE) != VBE_WINATTR_USABLE) {
            अनुवर्त;
        }

        यदि (info.अङ्कः_planes != 1) {
            अनुवर्त; // skip planar pixel layouts.
        } अन्यथा यदि (info.bpp < 8) {
            अनुवर्त; // skip anything below 8-bit.
        } अन्यथा यदि (!info.w || !info.h) {
            अनुवर्त; // zero-area display mode?!
        } अन्यथा यदि (!info.has_lfb && !info.win_granularity) {
            अनुवर्त; // banked mode with zero granularity would cause division by zero.
        } अन्यथा यदि ((info.स्मृतिः_model != VBE_MEMMODEL_PACKED_PIXEL) && (info.स्मृतिः_model != VBE_MEMMODEL_प्रत्यक्षम्_COLOR)) {
            अनुवर्त; // must be either packed pixel or Direct Color.
            // Note: 8-bit indexed modes are packed pixel.
        }

        SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
        यदि (info.स्मृतिः_model == VBE_MEMMODEL_PACKED_PIXEL) {
            विकल्प (info.bpp) {
            पक्ष 8:
                format = SDL_PIXELFORMAT_INDEX8;
                भङ्ग;
            पक्ष 15:
                format = SDL_PIXELFORMAT_XRGB1555;
                भङ्ग;
            पक्ष 16:
                format = SDL_PIXELFORMAT_RGB565;
                भङ्ग;
            पक्ष 24:
                format = SDL_PIXELFORMAT_RGB24;
                भङ्ग;
            पक्ष 32:
                format = SDL_PIXELFORMAT_XRGB8888;
                भङ्ग;
            स्वभाव:
                भङ्ग;
            }
        } अन्यथा {
            SDL_assert(info.स्मृतिः_model == VBE_MEMMODEL_प्रत्यक्षम्_COLOR);
            ध्रुव Uint32 rmask = ((((Uint32)1) << info.red_आवरणम्_आकार) - 1) << info.red_आवरणम्_pos;
            ध्रुव Uint32 gmask = ((((Uint32)1) << info.green_आवरणम्_आकार) - 1) << info.green_आवरणम्_pos;
            ध्रुव Uint32 bmask = ((((Uint32)1) << info.blue_आवरणम्_आकार) - 1) << info.blue_आवरणम्_pos;
            format = SDL_GetPixelFormatForMasks(info.bpp, rmask, gmask, bmask, 0x00000000);
        }

        यदि (format == SDL_PIXELFORMAT_UNKNOWN) {
            अनुवर्त; // don't know what to do with this one.
        }

        SDL_Display_बहुलकम्_दत्त *आन्तरिकम् = (SDL_Display_बहुलकम्_दत्त *)SDL_malloc(परिमाण(*आन्तरिकम्));
        यदि (!आन्तरिकम्) {
            अनुवर्त; // oof.
        }

        SDL_copyp(आन्तरिकम्, &info);

        SDL_Display_बहुलकम् बहुलकम्;
        SDL_zero(बहुलकम्);
        बहुलकम्.format = format;
        बहुलकम्.w = (पूर्णाङ्क)info.w;
        बहुलकम्.h = (पूर्णाङ्क)info.h;
        बहुलकम्.pixel_density = 1.0f; // no HighDPI scaling here.

        // !!! FIXME: we need to parse EDID data (VESA function 0x4F15, subfunction 0x01) to get refresh rates. Leaving as 0 for now.
        // float refresh_rate;             /**< refresh rate (or 0.0f for unspecified) */
        // int refresh_rate_numerator;     /**< precise refresh rate numerator (or 0 for unspecified) */
        // int refresh_rate_denominator;   /**< precise refresh rate denominator */

        बहुलकम्.आन्तरिकम् = आन्तरिकम्;

        यदि (!SDL_सङ्कलय_Fullscreen_Display_बहुलकम्(sdl_display, &बहुलकम्)) {
            SDL_free(आन्तरिकम्); // oh well, carry on without it.
        }
    }

    // Always add VGA mode 13h for 320x200x8. We skipped any VESA 320x200x8
    // modes above so this is the only entry at that resolution.
    {
        SDL_Display_बहुलकम्_दत्त *आन्तरिकम् = (SDL_Display_बहुलकम्_दत्त *)SDL_malloc(परिमाण(*आन्तरिकम्));
        यदि (आन्तरिकम्) {
            SDL_zerop(आन्तरिकम्);
            आन्तरिकम्->बहुलकम्_id = VGA_बहुलकम्_13_H_SENTINEL;
            आन्तरिकम्->गुणाः = VBE_MODEATTR_REQUIRED;
            आन्तरिकम्->pitch = 320;
            आन्तरिकम्->w = 320;
            आन्तरिकम्->h = 200;
            आन्तरिकम्->अङ्कः_planes = 1;
            आन्तरिकम्->bpp = 8;
            आन्तरिकम्->स्मृतिः_model = VBE_MEMMODEL_PACKED_PIXEL;
            आन्तरिकम्->अङ्कः_image_पृष्ठानि = 0; // no page flipping in mode 13h
            आन्तरिकम्->physical_आधारः_addr = 0;
            आन्तरिकम्->has_lfb = false;
            आन्तरिकम्->win_granularity = 64;
            आन्तरिकम्->win_आकार = 64;
            आन्तरिकम्->win_a_segment = VGA_बहुलकम्_13_H_SEGMENT;
            आन्तरिकम्->win_func_ptr = 0;
            आन्तरिकम्->win_a_गुणाः = VBE_WINATTR_USABLE;

            SDL_Display_बहुलकम् बहुलकम्;
            SDL_zero(बहुलकम्);
            बहुलकम्.format = SDL_PIXELFORMAT_INDEX8;
            बहुलकम्.w = 320;
            बहुलकम्.h = 200;
            बहुलकम्.pixel_density = 1.0f;
            बहुलकम्.आन्तरिकम् = आन्तरिकम्;

            यदि (!SDL_सङ्कलय_Fullscreen_Display_बहुलकम्(sdl_display, &बहुलकम्)) {
                SDL_free(आन्तरिकम्);
            }
        }
    }

    // Sort modes descending: largest to smallest (by width first, then height, then bpp).
    प्रति (पूर्णाङ्क i = 0; i < sdl_display->अङ्कः_fullscreen_modes - 1; i++) {
        प्रति (पूर्णाङ्क j = i + 1; j < sdl_display->अङ्कः_fullscreen_modes; j++) {
            ध्रुव SDL_Display_बहुलकम् *a = &sdl_display->fullscreen_modes[i];
            ध्रुव SDL_Display_बहुलकम् *b = &sdl_display->fullscreen_modes[j];
            bool swap = false;
            यदि (b->w > a->w) {
                swap = true;
            } अन्यथा यदि (b->w == a->w) {
                यदि (b->h > a->h) {
                    swap = true;
                } अन्यथा यदि (b->h == a->h) {
                    यदि (SDL_BITSPERPIXEL(b->format) > SDL_BITSPERPIXEL(a->format)) {
                        swap = true;
                    }
                }
            }
            यदि (swap) {
                SDL_Display_बहुलकम् tmp = sdl_display->fullscreen_modes[i];
                sdl_display->fullscreen_modes[i] = sdl_display->fullscreen_modes[j];
                sdl_display->fullscreen_modes[j] = tmp;
            }
        }
    }

    प्रत्यागम true;
}

bool DOSVESA_समुच्चयः_Display_बहुलकम्(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display, SDL_Display_बहुलकम् *बहुलकम्)
{
    SDL_Video_दत्त *दत्त = device->आन्तरिकम्;
    ध्रुव SDL_Display_बहुलकम्_दत्त *modedata = बहुलकम्->आन्तरिकम्;

    यदि (दत्त->current_बहुलकम्.आन्तरिकम् && (दत्त->current_बहुलकम्.आन्तरिकम्->बहुलकम्_id == modedata->बहुलकम्_id)) {
        प्रत्यागम true;
    }

    DOSVESA_InvalidateCachedFramebuffer();

    यदि (दत्त->mapping.आकार) {
        __dpmi_free_physical_address_mapping(&दत्त->mapping); // dump existing video mapping.
        SDL_zero(दत्त->mapping);
    }

    __dpmi_regs regs;

    यदि (modedata->बहुलकम्_id == VGA_बहुलकम्_13_H_SENTINEL) {
        // Set VGA mode 13h (320x200x256) via legacy BIOS call.
        SDL_zero(regs);
        regs.x.ax = 0x0013;
        __dpmi_int(0x10, &regs);
        // Mode 13h always succeeds on VGA hardware; no status to check.

        दत्त->banked_बहुलकम् = true; // uses A000:0000 segment, no LFB

        SDL_copyp(&दत्त->current_बहुलकम्, बहुलकम्);

        दत्त->page_flip_उपलब्धम् = false;
        दत्त->current_page = 0;
        दत्त->page_विस्थापनम्[0] = 0;
        दत्त->page_विस्थापनम्[1] = 0;

        // Clear the framebuffer
        {
            Uint8 zero_buf[320];
            SDL_zeroa(zero_buf);
            Uint32 vga_आधारः = (Uint32)VGA_बहुलकम्_13_H_SEGMENT << 4;
            प्रति (पूर्णाङ्क row = 0; row < 200; row++) {
                dosmemput(zero_buf, 320, vga_आधारः + row * 320);
            }
        }

        यदि (SDL_GetMouse()->आन्तरिकम् != रिक्त) {
            regs.x.ax = 0x7;
            regs.x.cx = 0;
            regs.x.dx = (Uint16)(बहुलकम्->w - 1);
            __dpmi_int(0x33, &regs);

            regs.x.ax = 0x8;
            regs.x.cx = 0;
            regs.x.dx = (Uint16)(बहुलकम्->h - 1);
            __dpmi_int(0x33, &regs);
        }

        प्रत्यागम true;
    }

    // When the direct-FB hint is active, prefer banked mode. This needs
    // to be set explicitly for some cards (Intel 740).
    ध्रुव bool is_banked_usable = modedata->win_a_segment &&
                                  modedata->win_आकार > 0 &&
                                  (modedata->win_a_गुणाः & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE;
    ध्रुव bool use_lfb = modedata->has_lfb &&
                         (!is_banked_usable || !SDL_GetHintBoolean(SDL_HINT_DOS_ALLOW_प्रत्यक्षम्_FRAMEBUFFER, false));

    regs.x.ax = 0x4F02;
    regs.x.bx = modedata->बहुलकम्_id | (use_lfb ? VBE_SETMODE_LFB : 0);
    __dpmi_int(0x10, &regs);

    यदि (regs.x.ax != 0x004F) {
        प्रत्यागम SDL_समुच्चयः_Error("Failed to set VESA video mode");
    }

    दत्त->banked_बहुलकम् = !use_lfb;

    यदि (use_lfb) {
        दत्त->mapping.स्थानाङ्कः = modedata->physical_आधारः_addr;
        दत्त->mapping.आकार = DOSVESA_Get_VESATotal_स्मृतिः();
        यदि (__dpmi_physical_address_mapping(&दत्त->mapping) != 0) {
            SDL_zero(दत्त->mapping);
            regs.x.ax = 0x03; // try to dump us back into text mode. Not sure if this is a good idea, though.
            __dpmi_int(0x10, &regs);
            SDL_zero(दत्त->current_बहुलकम्);
            प्रत्यागम SDL_समुच्चयः_Error("Failed to map VESA video memory");
        }

        // make sure framebuffer is blanked out.
        SDL_memset(DOS_Physical_गन्तव्यम्_रैखिकम्(दत्त->mapping.स्थानाङ्कः), '\0', (Uint32)modedata->h * (Uint32)modedata->pitch);
    } अन्यथा {
        // Banked mode: no physical address mapping needed.
        // Blank the visible framebuffer through the banked window.
        Uint32 योग_अष्टकानि = (Uint32)modedata->h * (Uint32)modedata->pitch;
        Uint32 win_gran_अष्टकानि = (Uint32)modedata->win_granularity * 1024;
        Uint32 win_आकार_अष्टकानि = (Uint32)modedata->win_आकार * 1024;
        Uint32 win_आधारः = (Uint32)modedata->win_a_segment << 4;
        Uint8 zero_buf[1024];
        SDL_zeroa(zero_buf);

        Uint32 विस्थापनम्_2 = 0;
        पूर्णाङ्क current_bank = -1;
        यावत् (विस्थापनम्_2 < योग_अष्टकानि) {
            पूर्णाङ्क bank = (पूर्णाङ्क)(विस्थापनम्_2 / win_gran_अष्टकानि);
            Uint32 off_अन्तर्_win = विस्थापनम्_2 % win_gran_अष्टकानि;
            Uint32 n = win_आकार_अष्टकानि - off_अन्तर्_win;
            यदि (n > योग_अष्टकानि - विस्थापनम्_2) {
                n = योग_अष्टकानि - विस्थापनम्_2;
            }

            यदि (bank != current_bank) {
                __dpmi_regs bregs;
                SDL_zero(bregs);
                bregs.x.bx = 0; // Window A
                bregs.x.dx = (Uint16)bank;
                यदि (modedata->win_func_ptr) {
                    // Call WinFuncPtr directly — faster than INT 10h.
                    bregs.x.cs = (Uint16)(modedata->win_func_ptr >> 16);
                    bregs.x.ip = (Uint16)(modedata->win_func_ptr & 0xFFFF);
                    __dpmi_simulate_real_mode_procedure_retf(&bregs);
                } अन्यथा {
                    bregs.x.ax = 0x4F05;
                    __dpmi_int(0x10, &bregs);
                }
                current_bank = bank;
            }

            // Zero in 1KB chunks via dosmemput
            Uint32 written = 0;
            यावत् (written < n) {
                Uint32 chunk = n - written;
                यदि (chunk > परिमाण(zero_buf)) {
                    chunk = परिमाण(zero_buf);
                }
                dosmemput(zero_buf, chunk, win_आधारः + off_अन्तर्_win + written);
                written += chunk;
            }
            विस्थापनम्_2 += n;
        }
    }

    SDL_copyp(&दत्त->current_बहुलकम्, बहुलकम्);

    // Set up page-flipping if the mode has at least 1 image page (meaning 2 total)
    // Note: page-flipping is only supported with LFB modes. With banked modes,
    // we would still need to bank-switch through the same 64KB window to write
    // to the back page, so the performance benefit is minimal (just tear-free).
    // For simplicity, disable page-flipping in banked mode for now.
    यदि (!दत्त->banked_बहुलकम् && modedata->अङ्कः_image_पृष्ठानि >= 1) {
        दत्त->page_flip_उपलब्धम् = true;
        दत्त->current_page = 0;
        दत्त->page_विस्थापनम्[0] = 0;
        दत्त->page_विस्थापनम्[1] = (Uint32)modedata->pitch * (Uint32)modedata->h;

        // Check that both pages fit within the mapped region.
        Uint32 page1_अन्तः = दत्त->page_विस्थापनम्[1] + (Uint32)modedata->pitch * (Uint32)modedata->h;
        यदि (page1_अन्तः > दत्त->mapping.आकार) {
            दत्त->page_flip_उपलब्धम् = false;
            दत्त->page_विस्थापनम्[1] = 0;
        } अन्यथा {
            // Also blank the second page
            SDL_memset((Uint8 *)DOS_Physical_गन्तव्यम्_रैखिकम्(दत्त->mapping.स्थानाङ्कः) + दत्त->page_विस्थापनम्[1],
                       '\0', (Uint32)modedata->pitch * (Uint32)modedata->h);

            // Start display at page 0
            regs.x.ax = 0x4F07;
            regs.x.bx = 0x0000; // set display start, wait for retrace
            regs.x.cx = 0;      // first pixel in scan line
            regs.x.dx = 0;      // first scan line
            __dpmi_int(0x10, &regs);
        }
    } अन्यथा {
        दत्त->page_flip_उपलब्धम् = false;
        दत्त->current_page = 0;
        दत्त->page_विस्थापनम्[0] = 0;
        दत्त->page_विस्थापनम्[1] = 0;
    }

    यदि (SDL_GetMouse()->आन्तरिकम् != रिक्त) { // internal != NULL) == int 33h services available.
        regs.x.ax = 0x7;                    // set mouse min/max horizontal position.
        regs.x.cx = 0;
        regs.x.dx = (Uint16)(बहुलकम्->w - 1);
        __dpmi_int(0x33, &regs);

        regs.x.ax = 0x8; // set mouse min/max vertical position.
        regs.x.cx = 0;
        regs.x.dx = (Uint16)(बहुलकम्->h - 1);
        __dpmi_int(0x33, &regs);
    }

    प्रत्यागम true;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_DOSVESA
