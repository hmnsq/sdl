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

#ಆದರೆ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ಅನ್ತರ್ಭಾವ "SDL_windowsvideo.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_displayevents_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_pixels_c.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_DXGI1_6_H
#ವ್ಯಾಖ್ಯಾನಿಸು COBJMACROS
#ಅನ್ತರ್ಭಾವ <dxgi1_6.h>
#ಆದರೆ_ಅಂತ್ಯ

// Windows CE compatibility
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ CDS_FULLSCREEN
#ವ್ಯಾಖ್ಯಾನಿಸು CDS_FULLSCREEN 0
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ USER_DEFAULT_SCREEN_DPI
#ವ್ಯಾಖ್ಯಾನಿಸು USER_DEFAULT_SCREEN_DPI 96
#ಆದರೆ_ಅಂತ್ಯ

// #define DEBUG_MODES
// #define HIGHDPI_DEBUG_VERBOSE

ಸ್ಥಿರ ಶೂನ್ಯ WIN_Update_Display_ಬಹುಲಕ(SDL_VideoDevice *_this, LPCWSTR deviceName, DWORD ಸೂಚ್ಯಂಕ, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ)
{
    SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = (SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *)ಬಹುಲಕ->ಆಂತರಿಕ;
    HDC hdc;

    ದತ್ತಾಂಶ->Device_ಬಹುಲಕ.dmFields = (DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS);

    // NOLINTNEXTLINE(bugprone-assignment-in-if-condition): No simple way to extract the assignment
    ಆದರೆ (ಸೂಚ್ಯಂಕ == ENUM_CURRENT_SETTINGS && (hdc = CreateDCW(deviceName, ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ)) != ಖಾಲಿ) {
        ಅಕ್ಷರ bmi_ದತ್ತಾಂಶ[ಗಾತ್ರ(BITMAPINFOHEADER) + 256 * ಗಾತ್ರ(RGBQUAD)];
        LPBITMAPINFO bmi;
        HBITMAP hbm;

        SDL_zeroa(bmi_ದತ್ತಾಂಶ);
        bmi = (LPBITMAPINFO)bmi_ದತ್ತಾಂಶ;
        bmi->bmi_ಶೀರ್ಷಿಕೆ.bi_ಗಾತ್ರ = ಗಾತ್ರ(BITMAPINFOHEADER);

        hbm = CreateCompatibleBitmap(hdc, 1, 1);
        GetDIBits(hdc, hbm, 0, 1, ಖಾಲಿ, bmi, DIB_RGB_COLORS);
        GetDIBits(hdc, hbm, 0, 1, ಖಾಲಿ, bmi, DIB_RGB_COLORS);
        DeleteObject(hbm);
        DeleteDC(hdc);
        ಆದರೆ (bmi->bmi_ಶೀರ್ಷಿಕೆ.biCompression == BI_BITFIELDS) {
            ಆಯ್ಕೆ (*(Uint32 *)bmi->bmiColors) {
            ಸ್ಥಿತಿ 0x00FF0000:
                ಬಹುಲಕ->format = SDL_PIXELFORMAT_XRGB8888;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ 0x000000FF:
                ಬಹುಲಕ->format = SDL_PIXELFORMAT_XBGR8888;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ 0xF800:
                ಬಹುಲಕ->format = SDL_PIXELFORMAT_RGB565;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ 0x7C00:
                ಬಹುಲಕ->format = SDL_PIXELFORMAT_XRGB1555;
                ನಿಲ್ಲಿಸು;
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (bmi->bmi_ಶೀರ್ಷಿಕೆ.biCompression == BI_RGB) {
            ಆದರೆ (bmi->bmi_ಶೀರ್ಷಿಕೆ.bi_ಬಿಟ್_ಎಣಿಕೆ == 24) {
                ಬಹುಲಕ->format = SDL_PIXELFORMAT_RGB24;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (bmi->bmi_ಶೀರ್ಷಿಕೆ.bi_ಬಿಟ್_ಎಣಿಕೆ == 8) {
                ಬಹುಲಕ->format = SDL_PIXELFORMAT_INDEX8;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (bmi->bmi_ಶೀರ್ಷಿಕೆ.bi_ಬಿಟ್_ಎಣಿಕೆ == 4) {
                ಬಹುಲಕ->format = SDL_PIXELFORMAT_INDEX4LSB;
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಬಹುಲಕ->format == SDL_PIXELFORMAT_UNKNOWN) {
        // FIXME: Can we tell what this will be?
        ಆದರೆ ((ದತ್ತಾಂಶ->Device_ಬಹುಲಕ.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL) {
            ಆಯ್ಕೆ (ದತ್ತಾಂಶ->Device_ಬಹುಲಕ.dm_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_Pel) {
            ಸ್ಥಿತಿ 32:
                ಬಹುಲಕ->format = SDL_PIXELFORMAT_XRGB8888;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ 24:
                ಬಹುಲಕ->format = SDL_PIXELFORMAT_RGB24;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ 16:
                ಬಹುಲಕ->format = SDL_PIXELFORMAT_RGB565;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ 15:
                ಬಹುಲಕ->format = SDL_PIXELFORMAT_XRGB1555;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ 8:
                ಬಹುಲಕ->format = SDL_PIXELFORMAT_INDEX8;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ 4:
                ಬಹುಲಕ->format = SDL_PIXELFORMAT_INDEX4LSB;
                ನಿಲ್ಲಿಸು;
            }
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ *WIN_GetDXGIOutput(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ WCHAR *DeviceName)
{
    ಶೂನ್ಯ *ಫಲಿತಾಂಶ = ಖಾಲಿ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_DXGI_H
    ಸ್ಥಿರಾಂಕ SDL_Video_ದತ್ತಾಂಶ *videodata = (ಸ್ಥಿರಾಂಕ SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    ಪೂರ್ಣಾಂಕ nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    ಆದರೆ (!videodata->pDXGIFactory) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    nAdapter = 0;
    ಆಗ (!ಫಲಿತಾಂಶ && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        ಆಗ (!ಫಲಿತಾಂಶ && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            ಆದರೆ (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                ಆದರೆ (SDL_wcscmp(outputDesc.DeviceName, DeviceName) == 0) {
                    ಫಲಿತಾಂಶ = pDXGIOutput;
                }
            }
            ಆದರೆ (pDXGIOutput != ಫಲಿತಾಂಶ) {
                IDXGIOutput_Release(pDXGIOutput);
            }
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_ReleaseDXGIOutput(ಶೂನ್ಯ *dxgi_output)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_DXGI_H
    IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;

    ಆದರೆ (pDXGIOutput) {
        IDXGIOutput_Release(pDXGIOutput);
    }
#ಆದರೆ_ಅಂತ್ಯ
}

ಸ್ಥಿರ SDL_DisplayOrientation WIN_GetNaturalOrientation(DEVMODEW *ಬಹುಲಕ)
{
    ಪೂರ್ಣಾಂಕ ಅಗಲ = ಬಹುಲಕ->dm_Pels_ಅಗಲ;
    ಪೂರ್ಣಾಂಕ ಎತ್ತರ = ಬಹುಲಕ->dm_Pels_ಎತ್ತರ;

    // Use unrotated width/height to guess orientation
    ಆದರೆ (ಬಹುಲಕ->dmDisplayOrientation == DMDO_90 || ಬಹುಲಕ->dmDisplayOrientation == DMDO_270) {
        ಪೂರ್ಣಾಂಕ ತಾತ್ಕಾಲಿಕ = ಅಗಲ;
        ಅಗಲ = ಎತ್ತರ;
        ಎತ್ತರ = ತಾತ್ಕಾಲಿಕ;
    }

    ಆದರೆ (ಅಗಲ >= ಎತ್ತರ) {
        ಹಿಂತಿರುಗಿ SDL_ORIENTATION_LANDSCAPE;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_ORIENTATION_PORTRAIT;
    }
}

ಸ್ಥಿರ SDL_DisplayOrientation WIN_GetDisplayOrientation(DEVMODEW *ಬಹುಲಕ)
{
    ಆದರೆ (WIN_GetNaturalOrientation(ಬಹುಲಕ) == SDL_ORIENTATION_LANDSCAPE) {
        ಆಯ್ಕೆ (ಬಹುಲಕ->dmDisplayOrientation) {
        ಸ್ಥಿತಿ DMDO_DEFAULT:
            ಹಿಂತಿರುಗಿ SDL_ORIENTATION_LANDSCAPE;
        ಸ್ಥಿತಿ DMDO_90:
            ಹಿಂತಿರುಗಿ SDL_ORIENTATION_PORTRAIT;
        ಸ್ಥಿತಿ DMDO_180:
            ಹಿಂತಿರುಗಿ SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        ಸ್ಥಿತಿ DMDO_270:
            ಹಿಂತಿರುಗಿ SDL_ORIENTATION_PORTRAIT_FLIPPED;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ಹಿಂತಿರುಗಿ SDL_ORIENTATION_UNKNOWN;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆಯ್ಕೆ (ಬಹುಲಕ->dmDisplayOrientation) {
        ಸ್ಥಿತಿ DMDO_DEFAULT:
            ಹಿಂತಿರುಗಿ SDL_ORIENTATION_PORTRAIT;
        ಸ್ಥಿತಿ DMDO_90:
            ಹಿಂತಿರುಗಿ SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        ಸ್ಥಿತಿ DMDO_180:
            ಹಿಂತಿರುಗಿ SDL_ORIENTATION_PORTRAIT_FLIPPED;
        ಸ್ಥಿತಿ DMDO_270:
            ಹಿಂತಿರುಗಿ SDL_ORIENTATION_LANDSCAPE;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ಹಿಂತಿರುಗಿ SDL_ORIENTATION_UNKNOWN;
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_Get_Refresh_ದರ(ಶೂನ್ಯ *dxgi_output, DEVMODEW *ಬಹುಲಕ, ಪೂರ್ಣಾಂಕ *numerator, ಪೂರ್ಣಾಂಕ *denominator)
{
    // We're not currently using DXGI to query display modes, so fake NTSC timings
    ಆಯ್ಕೆ (ಬಹುಲಕ->dmDisplayFrequency) {
    ಸ್ಥಿತಿ 119:
    ಸ್ಥಿತಿ 59:
    ಸ್ಥಿತಿ 29:
        *numerator = (ಬಹುಲಕ->dmDisplayFrequency + 1) * 1000;
        *denominator = 1001;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        *numerator = ಬಹುಲಕ->dmDisplayFrequency;
        *denominator = 1;
        ನಿಲ್ಲಿಸು;
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_DXGI_H
    ಆದರೆ (dxgi_output) {
        IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;
        DXGI_ಬಹುಲಕ_DESC ಬಹುಲಕ_ಗಮ್ಯ_ಹೊಂದಿಕೆ;
        DXGI_ಬಹುಲಕ_DESC closest_ಹೊಂದಿಕೆ;

        SDL_zero(ಬಹುಲಕ_ಗಮ್ಯ_ಹೊಂದಿಕೆ);
        ಬಹುಲಕ_ಗಮ್ಯ_ಹೊಂದಿಕೆ.ಅಗಲ_2 = ಬಹುಲಕ->dm_Pels_ಅಗಲ;
        ಬಹುಲಕ_ಗಮ್ಯ_ಹೊಂದಿಕೆ.ಎತ್ತರ_2 = ಬಹುಲಕ->dm_Pels_ಎತ್ತರ;
        ಬಹುಲಕ_ಗಮ್ಯ_ಹೊಂದಿಕೆ.Refresh_ದರ.Numerator = *numerator;
        ಬಹುಲಕ_ಗಮ್ಯ_ಹೊಂದಿಕೆ.Refresh_ದರ.Denominator = *denominator;
        ಬಹುಲಕ_ಗಮ್ಯ_ಹೊಂದಿಕೆ.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        ಆದರೆ (SUCCEEDED(IDXGIOutput_ಕಂಡುಹಿಡಿ_Closest_Matching_ಬಹುಲಕ(pDXGIOutput, &ಬಹುಲಕ_ಗಮ್ಯ_ಹೊಂದಿಕೆ, &closest_ಹೊಂದಿಕೆ, ಖಾಲಿ))) {
            *numerator = closest_ಹೊಂದಿಕೆ.Refresh_ದರ.Numerator;
            *denominator = closest_ಹೊಂದಿಕೆ.Refresh_ದರ.Denominator;
        }
    }
#ಆದರೆ_ಅಂತ್ಯ // HAVE_DXGI_H
}

ಸ್ಥಿರ ದಶಮಾಂಶ WIN_GetContentScale(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    ಪೂರ್ಣಾಂಕ dpi = 0;

    ಸ್ಥಿರಾಂಕ SDL_Video_ದತ್ತಾಂಶ *videodata = (ಸ್ಥಿರಾಂಕ SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    ಆದರೆ (videodata->GetDpiForMonitor) {
        UINT hdpi_uint, vdpi_uint;
        ಆದರೆ (videodata->GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
            dpi = (ಪೂರ್ಣಾಂಕ)hdpi_uint;
        }
    }
    ಆದರೆ (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(ಖಾಲಿ);
        ಆದರೆ (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(ಖಾಲಿ, hdc);
        }
    }
    ಆದರೆ (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    ಹಿಂತಿರುಗಿ dpi / (ದಶಮಾಂಶ)USER_DEFAULT_SCREEN_DPI;
}

ಸ್ಥಿರ bool WIN_Get_Display_ಬಹುಲಕ(SDL_VideoDevice *_this, ಶೂನ್ಯ *dxgi_output, HMONITOR hMonitor, LPCWSTR deviceName, DWORD ಸೂಚ್ಯಂಕ, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ, SDL_DisplayOrientation *natural_orientation, SDL_DisplayOrientation *current_orientation)
{
    SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;
    DEVMODEW devmode;

    devmode.dm_ಗಾತ್ರ = ಗಾತ್ರ(devmode);
    devmode.dmDriverExtra = 0;
    ಆದರೆ (!EnumDisplaySettingsW(deviceName, ಸೂಚ್ಯಂಕ, &devmode)) {
        ಹಿಂತಿರುಗಿ false;
    }

    ದತ್ತಾಂಶ = (SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *)SDL_malloc(ಗಾತ್ರ(*ದತ್ತಾಂಶ));
    ಆದರೆ (!ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ false;
    }

    SDL_zerop(ಬಹುಲಕ);
    ಬಹುಲಕ->ಆಂತರಿಕ = ದತ್ತಾಂಶ;
    ದತ್ತಾಂಶ->Device_ಬಹುಲಕ = devmode;

    ಬಹುಲಕ->format = SDL_PIXELFORMAT_UNKNOWN;
    ಬಹುಲಕ->w = ದತ್ತಾಂಶ->Device_ಬಹುಲಕ.dm_Pels_ಅಗಲ;
    ಬಹುಲಕ->h = ದತ್ತಾಂಶ->Device_ಬಹುಲಕ.dm_Pels_ಎತ್ತರ;
    WIN_Get_Refresh_ದರ(dxgi_output, &ದತ್ತಾಂಶ->Device_ಬಹುಲಕ, &ಬಹುಲಕ->refresh_ದರ_numerator, &ಬಹುಲಕ->refresh_ದರ_denominator);

    // Fill in the mode information
    WIN_Update_Display_ಬಹುಲಕ(_this, deviceName, ಸೂಚ್ಯಂಕ, ಬಹುಲಕ);

    ಆದರೆ (natural_orientation) {
        *natural_orientation = WIN_GetNaturalOrientation(&devmode);
    }
    ಆದರೆ (current_orientation) {
        *current_orientation = WIN_GetDisplayOrientation(&devmode);
    }

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಅಕ್ಷರ *WIN_GetDisplayNameVista(SDL_Video_ದತ್ತಾಂಶ *videodata, ಸ್ಥಿರಾಂಕ WCHAR *deviceName)
{
    DISPLAYCONFIG_ಮಾರ್ಗ_INFO *paths = ಖಾಲಿ;
    DISPLAYCONFIG_ಬಹುಲಕ_INFO *modes = ಖಾಲಿ;
    ಅಕ್ಷರ *ಫಲಿತಾಂಶ = ಖಾಲಿ;
    UINT32 ಮಾರ್ಗ_ಎಣಿಕೆ_2 = 0;
    UINT32 ಬಹುಲಕ_ಎಣಿಕೆ_2 = 0;
    UINT32 i;
    LONG rc;

    ಆದರೆ (!videodata->Get_Display_Config_ಬಫರ್_Sizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಮಾಡು {
        rc = videodata->Get_Display_Config_ಬಫರ್_Sizes(QDC_ONLY_ಸಕ್ರಿಯ_PATHS, &ಮಾರ್ಗ_ಎಣಿಕೆ_2, &ಬಹುಲಕ_ಎಣಿಕೆ_2);
        ಆದರೆ (rc != ERROR_SUCCESS) {
            ಹೋಗು WIN_GetDisplayNameVista_failed;
        }

        SDL_free(paths);
        SDL_free(modes);

        paths = (DISPLAYCONFIG_ಮಾರ್ಗ_INFO *)SDL_malloc(ಗಾತ್ರ(DISPLAYCONFIG_ಮಾರ್ಗ_INFO) * ಮಾರ್ಗ_ಎಣಿಕೆ_2);
        modes = (DISPLAYCONFIG_ಬಹುಲಕ_INFO *)SDL_malloc(ಗಾತ್ರ(DISPLAYCONFIG_ಬಹುಲಕ_INFO) * ಬಹುಲಕ_ಎಣಿಕೆ_2);
        ಆದರೆ ((!paths) || (!modes)) {
            ಹೋಗು WIN_GetDisplayNameVista_failed;
        }

        rc = videodata->QueryDisplayConfig(QDC_ONLY_ಸಕ್ರಿಯ_PATHS, &ಮಾರ್ಗ_ಎಣಿಕೆ_2, paths, &ಬಹುಲಕ_ಎಣಿಕೆ_2, modes, 0);
    } ಆಗ (rc == ERROR_INSUFFICIENT_ಬಫರ್);

    ಆದರೆ (rc == ERROR_SUCCESS) {
        ಗಾಗಿ (i = 0; i < ಮಾರ್ಗ_ಎಣಿಕೆ_2; i++) {
            DISPLAYCONFIG_ಮೂಲ_DEVICE_NAME ಮೂಲ_Name;
            DISPLAYCONFIG_ಗುರಿ_DEVICE_NAME ಗುರಿ_Name;

            SDL_zero(ಮೂಲ_Name);
            ಮೂಲ_Name.ಶೀರ್ಷಿಕೆ.adapterId = paths[i].ಗುರಿ_Info.adapterId;
            ಮೂಲ_Name.ಶೀರ್ಷಿಕೆ.type = DISPLAYCONFIG_DEVICE_INFO_GET_ಮೂಲ_NAME;
            ಮೂಲ_Name.ಶೀರ್ಷಿಕೆ.ಗಾತ್ರ_2 = ಗಾತ್ರ(ಮೂಲ_Name);
            ಮೂಲ_Name.ಶೀರ್ಷಿಕೆ.id = paths[i].ಮೂಲ_Info.id;
            rc = videodata->DisplayConfigGetDeviceInfo(&ಮೂಲ_Name.ಶೀರ್ಷಿಕೆ);
            ಆದರೆ (rc != ERROR_SUCCESS) {
                ನಿಲ್ಲಿಸು;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_wcscmp(deviceName, ಮೂಲ_Name.viewGdiDeviceName) != 0) {
                ಮುಂದುವರಿ;
            }

            SDL_zero(ಗುರಿ_Name);
            ಗುರಿ_Name.ಶೀರ್ಷಿಕೆ.adapterId = paths[i].ಗುರಿ_Info.adapterId;
            ಗುರಿ_Name.ಶೀರ್ಷಿಕೆ.id = paths[i].ಗುರಿ_Info.id;
            ಗುರಿ_Name.ಶೀರ್ಷಿಕೆ.type = DISPLAYCONFIG_DEVICE_INFO_GET_ಗುರಿ_NAME;
            ಗುರಿ_Name.ಶೀರ್ಷಿಕೆ.ಗಾತ್ರ_2 = ಗಾತ್ರ(ಗುರಿ_Name);
            rc = videodata->DisplayConfigGetDeviceInfo(&ಗುರಿ_Name.ಶೀರ್ಷಿಕೆ);
            ಆದರೆ (rc == ERROR_SUCCESS) {
                ಫಲಿತಾಂಶ = WIN_String_ಗಮ್ಯ_UTF8_W(ಗುರಿ_Name.monitorFriendlyDeviceName);
                /* if we got an empty string, treat it as failure so we'll fallback
                   to getting the generic name. */
                ಆದರೆ (ಫಲಿತಾಂಶ && (*ಫಲಿತಾಂಶ == '\0')) {
                    SDL_free(ಫಲಿತಾಂಶ);
                    ಫಲಿತಾಂಶ = ಖಾಲಿ;
                }
            }
            ನಿಲ್ಲಿಸು;
        }
    }

    SDL_free(paths);
    SDL_free(modes);
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;

WIN_GetDisplayNameVista_failed:
    SDL_free(ಫಲಿತಾಂಶ);
    SDL_free(paths);
    SDL_free(modes);
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_DXGI1_6_H
ಸ್ಥಿರ bool WIN_GetMonitorDESC1(HMONITOR hMonitor, DXGI_OUTPUT_DESC1 *desc)
{
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ HRESULT (WINAPI *pfnCreateDXGIFactory1)(REFIID riid, ಶೂನ್ಯ **ppFactory);
    pfnCreateDXGIFactory1 pCreateDXGIFactory1 = ಖಾಲಿ;
    SDL_SharedObject *hDXGIMod = ಖಾಲಿ;
    bool ಸಿಕ್ಕಿತು = false;

    hDXGIMod = SDL_ತುಂಬು_Object("dxgi.dll");
    ಆದರೆ (hDXGIMod) {
        pCreateDXGIFactory1 = (pfnCreateDXGIFactory1)SDL_ತುಂಬು_Function(hDXGIMod, "CreateDXGIFactory1");
    }
    ಆದರೆ (pCreateDXGIFactory1) {
        ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ GUID SDL_IID_IDXGIFactory1 = { 0x770aae78, 0xf26f, 0x4dba, { 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 } };
        ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ GUID SDL_IID_IDXGIOutput6 = { 0x068346e8, 0xaaec, 0x4b84, { 0xad, 0xd7, 0x13, 0x7f, 0x51, 0x3f, 0x77, 0xa1 } };
        IDXGIFactory1 *dxgiFactory;

        ಆದರೆ (SUCCEEDED(pCreateDXGIFactory1(&SDL_IID_IDXGIFactory1, (ಶೂನ್ಯ **)&dxgiFactory))) {
            IDXGIAdapter1 *dxgiAdapter;
            UINT adapter = 0;
            ಆಗ (!ಸಿಕ್ಕಿತು && SUCCEEDED(IDXGIFactory1_EnumAdapters1(dxgiFactory, adapter, &dxgiAdapter))) {
                IDXGIOutput *dxgiOutput;
                UINT output = 0;
                ಆಗ (!ಸಿಕ್ಕಿತು && SUCCEEDED(IDXGIAdapter1_EnumOutputs(dxgiAdapter, output, &dxgiOutput))) {
                    IDXGIOutput6 *dxgiOutput6;
                    ಆದರೆ (SUCCEEDED(IDXGIOutput_QueryInterface(dxgiOutput, &SDL_IID_IDXGIOutput6, (ಶೂನ್ಯ **)&dxgiOutput6))) {
                        ಆದರೆ (SUCCEEDED(IDXGIOutput6_GetDesc1(dxgiOutput6, desc))) {
                            ಆದರೆ (desc->Monitor == hMonitor) {
                                ಸಿಕ್ಕಿತು = true;
                            }
                        }
                        IDXGIOutput6_Release(dxgiOutput6);
                    }
                    IDXGIOutput_Release(dxgiOutput);
                    ++output;
                }
                IDXGIAdapter1_Release(dxgiAdapter);
                ++adapter;
            }
            IDXGIFactory2_Release(dxgiFactory);
        }
    }
    ಆದರೆ (hDXGIMod) {
        SDL_UnloadObject(hDXGIMod);
    }
    ಹಿಂತಿರುಗಿ ಸಿಕ್ಕಿತು;
}

ಸ್ಥಿರ bool WIN_Get_Monitor_ಮಾರ್ಗ_Info(SDL_Video_ದತ್ತಾಂಶ *videodata, HMONITOR hMonitor, DISPLAYCONFIG_ಮಾರ್ಗ_INFO *ಮಾರ್ಗ_info)
{
    LONG ಫಲಿತಾಂಶ;
    MONITORINFOEXW view_info;
    UINT32 i;
    UINT32 ಅಂಕೆ_ಮಾರ್ಗ_array_elements = 0;
    UINT32 ಅಂಕೆ_ಬಹುಲಕ_info_array_elements = 0;
    DISPLAYCONFIG_ಮಾರ್ಗ_INFO *ಮಾರ್ಗ_infos = ಖಾಲಿ, *new_ಮಾರ್ಗ_infos;
    DISPLAYCONFIG_ಬಹುಲಕ_INFO *ಬಹುಲಕ_infos = ಖಾಲಿ, *new_ಬಹುಲಕ_infos;
    bool ಸಿಕ್ಕಿತು = false;

    ಆದರೆ (!videodata->Get_Display_Config_ಬಫರ್_Sizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        ಹಿಂತಿರುಗಿ false;
    }

    SDL_zero(view_info);
    view_info.cb_ಗಾತ್ರ = ಗಾತ್ರ(view_info);
    ಆದರೆ (!GetMonitorInfoW(hMonitor, (MONITORINFO *)&view_info)) {
        ಹೋಗು ಮುಗಿದ;
    }

    ಮಾಡು {
        ಆದರೆ (videodata->Get_Display_Config_ಬಫರ್_Sizes(QDC_ONLY_ಸಕ್ರಿಯ_PATHS, &ಅಂಕೆ_ಮಾರ್ಗ_array_elements, &ಅಂಕೆ_ಬಹುಲಕ_info_array_elements) != ERROR_SUCCESS) {
            SDL_free(ಮಾರ್ಗ_infos);
            SDL_free(ಬಹುಲಕ_infos);
            ಹಿಂತಿರುಗಿ false;
        }

        new_ಮಾರ್ಗ_infos = (DISPLAYCONFIG_ಮಾರ್ಗ_INFO *)SDL_realloc(ಮಾರ್ಗ_infos, ಅಂಕೆ_ಮಾರ್ಗ_array_elements * ಗಾತ್ರ(*ಮಾರ್ಗ_infos));
        ಆದರೆ (!new_ಮಾರ್ಗ_infos) {
            ಹೋಗು ಮುಗಿದ;
        }
        ಮಾರ್ಗ_infos = new_ಮಾರ್ಗ_infos;

        new_ಬಹುಲಕ_infos = (DISPLAYCONFIG_ಬಹುಲಕ_INFO *)SDL_realloc(ಬಹುಲಕ_infos, ಅಂಕೆ_ಬಹುಲಕ_info_array_elements * ಗಾತ್ರ(*ಬಹುಲಕ_infos));
        ಆದರೆ (!new_ಬಹುಲಕ_infos) {
            ಹೋಗು ಮುಗಿದ;
        }
        ಬಹುಲಕ_infos = new_ಬಹುಲಕ_infos;

        ಫಲಿತಾಂಶ = videodata->QueryDisplayConfig(QDC_ONLY_ಸಕ್ರಿಯ_PATHS, &ಅಂಕೆ_ಮಾರ್ಗ_array_elements, ಮಾರ್ಗ_infos, &ಅಂಕೆ_ಬಹುಲಕ_info_array_elements, ಬಹುಲಕ_infos, ಖಾಲಿ);

    } ಆಗ (ಫಲಿತಾಂಶ == ERROR_INSUFFICIENT_ಬಫರ್);

    ಆದರೆ (ಫಲಿತಾಂಶ == ERROR_SUCCESS) {
        ಗಾಗಿ (i = 0; i < ಅಂಕೆ_ಮಾರ್ಗ_array_elements; ++i) {
            DISPLAYCONFIG_ಮೂಲ_DEVICE_NAME device_name;

            SDL_zero(device_name);
            device_name.ಶೀರ್ಷಿಕೆ.type = DISPLAYCONFIG_DEVICE_INFO_GET_ಮೂಲ_NAME;
            device_name.ಶೀರ್ಷಿಕೆ.ಗಾತ್ರ_2 = ಗಾತ್ರ(device_name);
            device_name.ಶೀರ್ಷಿಕೆ.adapterId = ಮಾರ್ಗ_infos[i].ಮೂಲ_Info.adapterId;
            device_name.ಶೀರ್ಷಿಕೆ.id = ಮಾರ್ಗ_infos[i].ಮೂಲ_Info.id;
            ಆದರೆ (videodata->DisplayConfigGetDeviceInfo(&device_name.ಶೀರ್ಷಿಕೆ) == ERROR_SUCCESS) {
                ಆದರೆ (SDL_wcscmp(view_info.szDevice, device_name.viewGdiDeviceName) == 0) {
                    SDL_copyp(ಮಾರ್ಗ_info, &ಮಾರ್ಗ_infos[i]);
                    ಸಿಕ್ಕಿತು = true;
                    ನಿಲ್ಲಿಸು;
                }
            }
        }
    }

ಮುಗಿದ:
    SDL_free(ಮಾರ್ಗ_infos);
    SDL_free(ಬಹುಲಕ_infos);

    ಹಿಂತಿರುಗಿ ಸಿಕ್ಕಿತು;
}

ಸ್ಥಿರ ದಶಮಾಂಶ WIN_Get_SDRWhite_ಬಿಂದು(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    DISPLAYCONFIG_ಮಾರ್ಗ_INFO ಮಾರ್ಗ_info;
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    ದಶಮಾಂಶ SDR_white_level = 1.0f;

    ಆದರೆ (WIN_Get_Monitor_ಮಾರ್ಗ_Info(videodata, hMonitor, &ಮಾರ್ಗ_info)) {
        /* workarounds for https://github.com/libsdl-org/SDL/issues/11193 */
        ರಚನೆ SDL_DISPLAYCONFIG_SDR_WHITE_LEVEL {
          DISPLAYCONFIG_DEVICE_INFO_ಶೀರ್ಷಿಕೆ ಶೀರ್ಷಿಕೆ;
          ULONG SDRWhiteLevel;
        } white_level;
        #ವ್ಯಾಖ್ಯಾನಿಸು DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL 11

        SDL_zero(white_level);
        white_level.ಶೀರ್ಷಿಕೆ.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
        white_level.ಶೀರ್ಷಿಕೆ.ಗಾತ್ರ_2 = ಗಾತ್ರ(white_level);
        white_level.ಶೀರ್ಷಿಕೆ.adapterId = ಮಾರ್ಗ_info.ಗುರಿ_Info.adapterId;
        white_level.ಶೀರ್ಷಿಕೆ.id = ಮಾರ್ಗ_info.ಗುರಿ_Info.id;
        // WIN_GetMonitorPathInfo() succeeded: DisplayConfigGetDeviceInfo is not NULL
        ಆದರೆ (videodata->DisplayConfigGetDeviceInfo(&white_level.ಶೀರ್ಷಿಕೆ) == ERROR_SUCCESS &&
            white_level.SDRWhiteLevel > 0) {
            SDR_white_level = (white_level.SDRWhiteLevel / 1000.0f);
        }
    }
    ಹಿಂತಿರುಗಿ SDR_white_level;
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_GetHDRProperties(SDL_VideoDevice *_this, HMONITOR hMonitor, SDL_HDROutputProperties *HDR)
{
    DXGI_OUTPUT_DESC1 desc;

    SDL_zerop(HDR);

    ಆದರೆ (WIN_GetMonitorDESC1(hMonitor, &desc)) {
        ಆದರೆ (desc.ColorSpace == DXGI_COLOR_SPACE_RGB_ತುಂಬಿದ_G2084_NONE_P2020) {
            HDR->SDR_white_level = WIN_Get_SDRWhite_ಬಿಂದು(_this, hMonitor);
            HDR->HDR_headroom = (desc.MaxLuminance / SCRGB_NITS) / HDR->SDR_white_level;
        }
    }
}
#ಆದರೆ_ಅಂತ್ಯ // HAVE_DXGI1_6_H

ಸ್ಥಿರ ಶೂನ್ಯ WIN_ಕೂಡಿಸು_Display(SDL_VideoDevice *_this, HMONITOR hMonitor, ಸ್ಥಿರಾಂಕ MONITORINFOEXW *info, ಪೂರ್ಣಾಂಕ *display_ಸೂಚ್ಯಂಕ)
{
    ಪೂರ್ಣಾಂಕ i, ಸೂಚ್ಯಂಕ = *display_ಸೂಚ್ಯಂಕ;
    SDL_VideoDisplay display;
    SDL_Display_ದತ್ತಾಂಶ *displaydata;
    ಶೂನ್ಯ *dxgi_output = ಖಾಲಿ;
    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    ದಶಮಾಂಶ content_scale = WIN_GetContentScale(_this, hMonitor);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_MODES
    SDL_Log("Display: %s", WIN_String_ಗಮ್ಯ_UTF8_W(info->szDevice));
#ಆದರೆ_ಅಂತ್ಯ

    dxgi_output = WIN_GetDXGIOutput(_this, info->szDevice);
    bool ಸಿಕ್ಕಿತು = WIN_Get_Display_ಬಹುಲಕ(_this, dxgi_output, hMonitor, info->szDevice, ENUM_CURRENT_SETTINGS, &ಬಹುಲಕ, &natural_orientation, &current_orientation);
    WIN_ReleaseDXGIOutput(dxgi_output);
    ಆದರೆ (!ಸಿಕ್ಕಿತು) {
        ಹಿಂತಿರುಗಿ;
    }

    // Prevent adding duplicate displays. Do this after we know the display is
    // ready to be added to allow any displays that we can't fully query to be
    // removed
    ಗಾಗಿ (i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
        SDL_Display_ದತ್ತಾಂಶ *ಆಂತರಿಕ = _this->displays[i]->ಆಂತರಿಕ;
        ಆದರೆ (SDL_wcscmp(ಆಂತರಿಕ->DeviceName, info->szDevice) == 0) {
            bool moved = (ಸೂಚ್ಯಂಕ != i);
            bool ಬದಲಾಯಿತು_bounds = false;

            ಆದರೆ (ಆಂತರಿಕ->state != DisplayRemoved) {
                // We've already enumerated this display, don't move it
                ಹೋಗು cleanup;
            }

            ಆದರೆ (ಸೂಚ್ಯಂಕ >= _this->ಅಂಕೆ_displays) {
                // This should never happen due to the check above, but just in case...
                ಹೋಗು cleanup;
            }

            ಆದರೆ (moved) {
                SDL_VideoDisplay *tmp;

                tmp = _this->displays[ಸೂಚ್ಯಂಕ];
                _this->displays[ಸೂಚ್ಯಂಕ] = _this->displays[i];
                _this->displays[i] = tmp;
                i = ಸೂಚ್ಯಂಕ;
            }

            ಆಂತರಿಕ->MonitorHandle = hMonitor;
            ಆಂತರಿಕ->state = DisplayUnchanged;

            SDL_PropertiesID props = SDL_GetDisplayProperties(_this->displays[i]->id);
            SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_ಸೂಚಕ, hMonitor);

            ಆದರೆ (!_this->setting_display_ಬಹುಲಕ) {
                SDL_VideoDisplay *existing_display = _this->displays[i];
                SDL_Rect bounds;

                SDL_ResetFullscreenDisplayModes(existing_display);
                SDL_ಗಣ_Desktop_Display_ಬಹುಲಕ(existing_display, &ಬಹುಲಕ);
                // The mode is owned by the video subsystem
                ಬಹುಲಕ.ಆಂತರಿಕ = ಖಾಲಿ;
                ಆದರೆ (WIN_GetDisplayBounds(_this, existing_display, &bounds) &&
                    SDL_memcmp(&ಆಂತರಿಕ->bounds, &bounds, ಗಾತ್ರ(bounds)) != 0) {
                    ಬದಲಾಯಿತು_bounds = true;
                    SDL_copyp(&ಆಂತರಿಕ->bounds, &bounds);
                }
                ಆದರೆ (moved || ಬದಲಾಯಿತು_bounds) {
                    SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_MOVED, 0, 0);
                }
                SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_ORIENTATION, current_orientation, 0);
                SDL_ಗಣ_Display_Content_Scale(existing_display, content_scale);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_DXGI1_6_H
                SDL_HDROutputProperties HDR;
                WIN_GetHDRProperties(_this, hMonitor, &HDR);
                SDL_ಗಣ_Display_HDRProperties(existing_display, &HDR);
#ಆದರೆ_ಅಂತ್ಯ
            }
            ಹೋಗು ಮುಗಿದ;
        }
    }

    displaydata = (SDL_Display_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(*displaydata));
    ಆದರೆ (!displaydata) {
        ಹೋಗು cleanup;
    }
    SDL_memcpy(displaydata->DeviceName, info->szDevice, ಗಾತ್ರ(displaydata->DeviceName));
    displaydata->MonitorHandle = hMonitor;
    displaydata->state = DisplayAdded;

    SDL_zero(display);
    display.name = WIN_GetDisplayNameVista(_this->ಆಂತರಿಕ, info->szDevice);
    ಆದರೆ (!display.name) {
        DISPLAY_DEVICEW device;
        SDL_zero(device);
        device.cb = ಗಾತ್ರ(device);
        ಆದರೆ (EnumDisplayDevicesW(info->szDevice, 0, &device, 0)) {
            display.name = WIN_String_ಗಮ್ಯ_UTF8_W(device.DeviceString);
        }
    }

    display.desktop_ಬಹುಲಕ = ಬಹುಲಕ;
    display.natural_orientation = natural_orientation;
    display.current_orientation = current_orientation;
    display.content_scale = content_scale;
    display.device = _this;
    display.ಆಂತರಿಕ = displaydata;
    WIN_GetDisplayBounds(_this, &display, &displaydata->bounds);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_DXGI1_6_H
    WIN_GetHDRProperties(_this, hMonitor, &display.HDR);
#ಆದರೆ_ಅಂತ್ಯ
    SDL_DisplayID displayID = SDL_ಕೂಡಿಸು_Video_Display(&display, false);
    ಆದರೆ (displayID) {
        // The mode is owned by the video subsystem
        ಬಹುಲಕ.ಆಂತರಿಕ = ಖಾಲಿ;

        SDL_PropertiesID props = SDL_GetDisplayProperties(displayID);
        SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_ಸೂಚಕ, hMonitor);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_free(displaydata);
    }
    SDL_free(display.name);

ಮುಗಿದ:
    *display_ಸೂಚ್ಯಂಕ += 1;

cleanup:
    SDL_free(ಬಹುಲಕ.ಆಂತರಿಕ);
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ WIN_ಕೂಡಿಸು_Displays_ದತ್ತಾಂಶ
{
    SDL_VideoDevice *video_device;
    ಪೂರ್ಣಾಂಕ display_ಸೂಚ್ಯಂಕ;
    bool want_primary;
} WIN_ಕೂಡಿಸು_Displays_ದತ್ತಾಂಶ_2;

ಸ್ಥಿರ BOOL CALLBACK WIN_ಕೂಡಿಸು_Displays_Callback(HMONITOR hMonitor,
                                             HDC hdcMonitor,
                                             LPRECT lprcMonitor,
                                             LPARAM dw_ದತ್ತಾಂಶ)
{
    WIN_ಕೂಡಿಸು_Displays_ದತ್ತಾಂಶ_2 *ದತ್ತಾಂಶ = (WIN_ಕೂಡಿಸು_Displays_ದತ್ತಾಂಶ_2 *)dw_ದತ್ತಾಂಶ;
    MONITORINFOEXW info;

    SDL_zero(info);
    info.cb_ಗಾತ್ರ = ಗಾತ್ರ(info);

    ಆದರೆ (GetMonitorInfoW(hMonitor, (LPMONITORINFO)&info) != 0) {
        ಸ್ಥಿರಾಂಕ bool is_primary = ((info.dwFlags & MONITORINFOF_PRIMARY) == MONITORINFOF_PRIMARY);

        ಆದರೆ (is_primary == ದತ್ತಾಂಶ->want_primary) {
            WIN_ಕೂಡಿಸು_Display(ದತ್ತಾಂಶ->video_device, hMonitor, &info, &ದತ್ತಾಂಶ->display_ಸೂಚ್ಯಂಕ);
        }
    }

    // continue enumeration
    ಹಿಂತಿರುಗಿ TRUE;
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_ಕೂಡಿಸು_Displays(SDL_VideoDevice *_this)
{
    WIN_ಕೂಡಿಸು_Displays_ದತ್ತಾಂಶ_2 callback_ದತ್ತಾಂಶ;
    callback_ದತ್ತಾಂಶ.video_device = _this;
    callback_ದತ್ತಾಂಶ.display_ಸೂಚ್ಯಂಕ = 0;

    callback_ದತ್ತಾಂಶ.want_primary = true;
    EnumDisplayMonitors(ಖಾಲಿ, ಖಾಲಿ, WIN_ಕೂಡಿಸು_Displays_Callback, (LPARAM)&callback_ದತ್ತಾಂಶ);

    callback_ದತ್ತಾಂಶ.want_primary = false;
    EnumDisplayMonitors(ಖಾಲಿ, ಖಾಲಿ, WIN_ಕೂಡಿಸು_Displays_Callback, (LPARAM)&callback_ದತ್ತಾಂಶ);
}

bool WIN_InitModes(SDL_VideoDevice *_this)
{
    WIN_ಕೂಡಿಸು_Displays(_this);

    ಆದರೆ (_this->ಅಂಕೆ_displays == 0) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("No displays available");
    }
    ಹಿಂತಿರುಗಿ true;
}

bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ಸ್ಥಿರಾಂಕ SDL_Display_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = display->ಆಂತರಿಕ;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cb_ಗಾತ್ರ = ಗಾತ್ರ(MONITORINFO);
    rc = GetMonitorInfo(ದತ್ತಾಂಶ->MonitorHandle, &minfo);

    ಆದರೆ (!rc) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Couldn't find monitor data");
    }

    rect->x = minfo.rcMonitor.ಎಡ;
    rect->y = minfo.rcMonitor.ತುದಿ;
    rect->w = minfo.rcMonitor.ಬಲ - minfo.rcMonitor.ಎಡ;
    rect->h = minfo.rcMonitor.bottom - minfo.rcMonitor.ತುದಿ;

    ಹಿಂತಿರುಗಿ true;
}

bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ಸ್ಥಿರಾಂಕ SDL_Display_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = display->ಆಂತರಿಕ;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cb_ಗಾತ್ರ = ಗಾತ್ರ(MONITORINFO);
    rc = GetMonitorInfo(ದತ್ತಾಂಶ->MonitorHandle, &minfo);

    ಆದರೆ (!rc) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Couldn't find monitor data");
    }

    rect->x = minfo.rcWork.ಎಡ;
    rect->y = minfo.rcWork.ತುದಿ;
    rect->w = minfo.rcWork.ಬಲ - minfo.rcWork.ಎಡ;
    rect->h = minfo.rcWork.bottom - minfo.rcWork.ತುದಿ;

    ಹಿಂತಿರುಗಿ true;
}

bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = display->ಆಂತರಿಕ;
    ಶೂನ್ಯ *dxgi_output;
    DWORD i;
    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;

    dxgi_output = WIN_GetDXGIOutput(_this, ದತ್ತಾಂಶ->DeviceName);

    // Make sure we add the current mode to the list in case it's a custom mode that doesn't enumerate
    ಗಾಗಿ (i = ENUM_CURRENT_SETTINGS; ; ++i) {
        ಆದರೆ (!WIN_Get_Display_ಬಹುಲಕ(_this, dxgi_output, ದತ್ತಾಂಶ->MonitorHandle, ದತ್ತಾಂಶ->DeviceName, i, &ಬಹುಲಕ, ಖಾಲಿ, ಖಾಲಿ)) {
            ನಿಲ್ಲಿಸು;
        }
        ಆದರೆ (SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(ಬಹುಲಕ.format)) {
            // We don't support palettized modes now
            SDL_free(ಬಹುಲಕ.ಆಂತರಿಕ);
            ಮುಂದುವರಿ;
        }
        ಆದರೆ (ಬಹುಲಕ.format != SDL_PIXELFORMAT_UNKNOWN) {
            ಆದರೆ (!SDL_ಕೂಡಿಸು_Fullscreen_Display_ಬಹುಲಕ(display, &ಬಹುಲಕ)) {
                SDL_free(ಬಹುಲಕ.ಆಂತರಿಕ);
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_free(ಬಹುಲಕ.ಆಂತರಿಕ);
        }
    }

    WIN_ReleaseDXGIOutput(dxgi_output);

    ಹಿಂತಿರುಗಿ true;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_MODES
ಸ್ಥಿರ ಶೂನ್ಯ WIN_LogMonitor(SDL_VideoDevice *_this, HMONITOR mon)
{
    ಸ್ಥಿರಾಂಕ SDL_Video_ದತ್ತಾಂಶ *vid_ದತ್ತಾಂಶ = (ಸ್ಥಿರಾಂಕ SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    MONITORINFOEX minfo;
    UINT xdpi = 0, ydpi = 0;
    ಅಕ್ಷರ *name_utf8;

    ಆದರೆ (vid_ದತ್ತಾಂಶ->GetDpiForMonitor) {
        vid_ದತ್ತಾಂಶ->GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &xdpi, &ydpi);
    }

    SDL_zero(minfo);
    minfo.cb_ಗಾತ್ರ = ಗಾತ್ರ(minfo);
    GetMonitorInfo(mon, (LPMONITORINFO)&minfo);

    name_utf8 = WIN_String_ಗಮ್ಯ_UTF8(minfo.szDevice);

    SDL_Log("WIN_LogMonitor: monitor \"%s\": dpi: %d windows screen coordinates: %d, %d, %dx%d",
            name_utf8,
            xdpi,
            minfo.rcMonitor.ಎಡ,
            minfo.rcMonitor.ತುದಿ,
            minfo.rcMonitor.ಬಲ - minfo.rcMonitor.ಎಡ,
            minfo.rcMonitor.bottom - minfo.rcMonitor.ತುದಿ);

    SDL_free(name_utf8);
}
#ಆದರೆ_ಅಂತ್ಯ

bool WIN_ಗಣ_Display_ಬಹುಲಕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ)
{
    SDL_Display_ದತ್ತಾಂಶ *displaydata = display->ಆಂತರಿಕ;
    SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = (SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *)ಬಹುಲಕ->ಆಂತರಿಕ;
    LONG ಸ್ಥಿತಿ_2;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state before mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#ಆದರೆ_ಅಂತ್ಯ

    /* High-DPI notes:

       - ChangeDisplaySettingsEx always takes pixels.
       - e.g. if the display is set to 2880x1800 with 200% scaling in Display Settings
         - calling ChangeDisplaySettingsEx with a dmPelsWidth/Height other than 2880x1800 will
           change the monitor DPI to 96. (100% scaling)
         - calling ChangeDisplaySettingsEx with a dmPelsWidth/Height of 2880x1800 (or a NULL DEVMODE*) will
           reset the monitor DPI to 192. (200% scaling)

       NOTE: these are temporary changes in DPI, not modifications to the Control Panel setting. */
    ಆದರೆ (ಬಹುಲಕ->ಆಂತರಿಕ == display->desktop_ಬಹುಲಕ.ಆಂತರಿಕ) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: resetting to original resolution");
#ಆದರೆ_ಅಂತ್ಯ
        ಸ್ಥಿತಿ_2 = ChangeDisplaySettingsExW(displaydata->DeviceName, ಖಾಲಿ, ಖಾಲಿ, CDS_FULLSCREEN, ಖಾಲಿ);
    } ಇಲ್ಲದಿದ್ದರೆ {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: changing to %dx%d pixels", ದತ್ತಾಂಶ->Device_ಬಹುಲಕ.dm_Pels_ಅಗಲ, ದತ್ತಾಂಶ->Device_ಬಹುಲಕ.dm_Pels_ಎತ್ತರ);
#ಆದರೆ_ಅಂತ್ಯ
        ಸ್ಥಿತಿ_2 = ChangeDisplaySettingsExW(displaydata->DeviceName, &ದತ್ತಾಂಶ->Device_ಬಹುಲಕ, ಖಾಲಿ, CDS_FULLSCREEN, ಖಾಲಿ);
    }
    ಆದರೆ (ಸ್ಥಿತಿ_2 != DISP_CHANGE_SUCCESSFUL) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *reason = "Unknown reason";
        ಆಯ್ಕೆ (ಸ್ಥಿತಿ_2) {
        ಸ್ಥಿತಿ DISP_CHANGE_BADFLAGS:
            reason = "DISP_CHANGE_BADFLAGS";
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ DISP_CHANGE_BADMODE:
            reason = "DISP_CHANGE_BADMODE";
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ DISP_CHANGE_BADPARAM:
            reason = "DISP_CHANGE_BADPARAM";
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ DISP_CHANGE_FAILED:
            reason = "DISP_CHANGE_FAILED";
            ನಿಲ್ಲಿಸು;
        }
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("ChangeDisplaySettingsEx() failed: %s", reason);
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state after mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#ಆದರೆ_ಅಂತ್ಯ

    EnumDisplaySettingsW(displaydata->DeviceName, ENUM_CURRENT_SETTINGS, &ದತ್ತಾಂಶ->Device_ಬಹುಲಕ);
    WIN_Update_Display_ಬಹುಲಕ(_this, displaydata->DeviceName, ENUM_CURRENT_SETTINGS, ಬಹುಲಕ);
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ WIN_RefreshDisplays(SDL_VideoDevice *_this)
{
    ಪೂರ್ಣಾಂಕ i;

    // Mark all displays as potentially invalid to detect
    // entries that have actually been removed
    ಗಾಗಿ (i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
        SDL_Display_ದತ್ತಾಂಶ *ಆಂತರಿಕ = _this->displays[i]->ಆಂತರಿಕ;
        ಆಂತರಿಕ->state = DisplayRemoved;
    }

    // Enumerate displays to add any new ones and mark still
    // connected entries as valid
    WIN_ಕೂಡಿಸು_Displays(_this);

    // Delete any entries still marked as invalid, iterate
    // in reverse as each delete takes effect immediately
    ಗಾಗಿ (i = _this->ಅಂಕೆ_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_Display_ದತ್ತಾಂಶ *ಆಂತರಿಕ = display->ಆಂತರಿಕ;
        ಆದರೆ (ಆಂತರಿಕ->state == DisplayRemoved) {
            SDL_DelVideoDisplay(display->id, true);
        }
    }

    // Send events for any newly added displays
    ಗಾಗಿ (i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_Display_ದತ್ತಾಂಶ *ಆಂತರಿಕ = display->ಆಂತರಿಕ;
        ಆದರೆ (ಆಂತರಿಕ->state == DisplayAdded) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
        }
    }
}

ಶೂನ್ಯ WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this)
{
    // This almost never happens, so just go ahead and send update events for all displays
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_ಬದಲಾಯಿತು, 0, 0);
    }
}

ಶೂನ್ಯ WIN_QuitModes(SDL_VideoDevice *_this)
{
    // All fullscreen windows should have restored modes by now
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WINDOWS
