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

#ਜੇ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_displayevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_pixels_c.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_DXGI1_6_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ COBJMACROS
#ਅਨ੍ਤਰ੍ਭਾਵ <dxgi1_6.h>
#ਜੇ_ਅੰਤ

// Windows CE compatibility
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ CDS_FULLSCREEN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CDS_FULLSCREEN 0
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ USER_DEFAULT_SCREEN_DPI
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ USER_DEFAULT_SCREEN_DPI 96
#ਜੇ_ਅੰਤ

// #define DEBUG_MODES
// #define HIGHDPI_DEBUG_VERBOSE

ਸਥਿਰ ਖਾਲੀ WIN_Update_Display_ਬਹੁਲਕ(SDL_VideoDevice *_this, LPCWSTR deviceName, DWORD ਸੂਚਕਾਂਕ, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ)
{
    SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *ਅੰਕੜੇ = (SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *)ਬਹੁਲਕ->ਅੰਦਰੂਨੀ;
    HDC hdc;

    ਅੰਕੜੇ->Device_ਬਹੁਲਕ.dmFields = (DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS);

    // NOLINTNEXTLINE(bugprone-assignment-in-if-condition): No simple way to extract the assignment
    ਜੇ (ਸੂਚਕਾਂਕ == ENUM_CURRENT_SETTINGS && (hdc = CreateDCW(deviceName, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ)) != ਨਿਰਾ) {
        ਅੱਖਰ bmi_ਅੰਕੜੇ[ਆਕਾਰ(BITMAPINFOHEADER) + 256 * ਆਕਾਰ(RGBQUAD)];
        LPBITMAPINFO bmi;
        HBITMAP hbm;

        SDL_zeroa(bmi_ਅੰਕੜੇ);
        bmi = (LPBITMAPINFO)bmi_ਅੰਕੜੇ;
        bmi->bmi_ਸਿਰਲੇਖ.bi_ਮਾਪ = ਆਕਾਰ(BITMAPINFOHEADER);

        hbm = CreateCompatibleBitmap(hdc, 1, 1);
        GetDIBits(hdc, hbm, 0, 1, ਨਿਰਾ, bmi, DIB_RGB_COLORS);
        GetDIBits(hdc, hbm, 0, 1, ਨਿਰਾ, bmi, DIB_RGB_COLORS);
        DeleteObject(hbm);
        DeleteDC(hdc);
        ਜੇ (bmi->bmi_ਸਿਰਲੇਖ.biCompression == BI_BITFIELDS) {
            ਚੋਣ (*(Uint32 *)bmi->bmiColors) {
            ਹਾਲਤ 0x00FF0000:
                ਬਹੁਲਕ->format = SDL_PIXELFORMAT_XRGB8888;
                ਰੋਕੋ;
            ਹਾਲਤ 0x000000FF:
                ਬਹੁਲਕ->format = SDL_PIXELFORMAT_XBGR8888;
                ਰੋਕੋ;
            ਹਾਲਤ 0xF800:
                ਬਹੁਲਕ->format = SDL_PIXELFORMAT_RGB565;
                ਰੋਕੋ;
            ਹਾਲਤ 0x7C00:
                ਬਹੁਲਕ->format = SDL_PIXELFORMAT_XRGB1555;
                ਰੋਕੋ;
            }
        } ਨਹੀਂਤਾਂ ਜੇ (bmi->bmi_ਸਿਰਲੇਖ.biCompression == BI_RGB) {
            ਜੇ (bmi->bmi_ਸਿਰਲੇਖ.bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ == 24) {
                ਬਹੁਲਕ->format = SDL_PIXELFORMAT_RGB24;
            } ਨਹੀਂਤਾਂ ਜੇ (bmi->bmi_ਸਿਰਲੇਖ.bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ == 8) {
                ਬਹੁਲਕ->format = SDL_PIXELFORMAT_INDEX8;
            } ਨਹੀਂਤਾਂ ਜੇ (bmi->bmi_ਸਿਰਲੇਖ.bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ == 4) {
                ਬਹੁਲਕ->format = SDL_PIXELFORMAT_INDEX4LSB;
            }
        }
    } ਨਹੀਂਤਾਂ ਜੇ (ਬਹੁਲਕ->format == SDL_PIXELFORMAT_UNKNOWN) {
        // FIXME: Can we tell what this will be?
        ਜੇ ((ਅੰਕੜੇ->Device_ਬਹੁਲਕ.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL) {
            ਚੋਣ (ਅੰਕੜੇ->Device_ਬਹੁਲਕ.dm_ਬਿੱਟ_ਪ੍ਰਤੀ_Pel) {
            ਹਾਲਤ 32:
                ਬਹੁਲਕ->format = SDL_PIXELFORMAT_XRGB8888;
                ਰੋਕੋ;
            ਹਾਲਤ 24:
                ਬਹੁਲਕ->format = SDL_PIXELFORMAT_RGB24;
                ਰੋਕੋ;
            ਹਾਲਤ 16:
                ਬਹੁਲਕ->format = SDL_PIXELFORMAT_RGB565;
                ਰੋਕੋ;
            ਹਾਲਤ 15:
                ਬਹੁਲਕ->format = SDL_PIXELFORMAT_XRGB1555;
                ਰੋਕੋ;
            ਹਾਲਤ 8:
                ਬਹੁਲਕ->format = SDL_PIXELFORMAT_INDEX8;
                ਰੋਕੋ;
            ਹਾਲਤ 4:
                ਬਹੁਲਕ->format = SDL_PIXELFORMAT_INDEX4LSB;
                ਰੋਕੋ;
            }
        }
    }
}

ਸਥਿਰ ਖਾਲੀ *WIN_GetDXGIOutput(SDL_VideoDevice *_this, ਅਚਲ WCHAR *DeviceName)
{
    ਖਾਲੀ *ਨਤੀਜਾ = ਨਿਰਾ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_DXGI_H
    ਅਚਲ SDL_Video_ਅੰਕੜੇ *videodata = (ਅਚਲ SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    ਪੂਰਨ nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    ਜੇ (!videodata->pDXGIFactory) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    nAdapter = 0;
    ਜਦੋਂ (!ਨਤੀਜਾ && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        ਜਦੋਂ (!ਨਤੀਜਾ && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            ਜੇ (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                ਜੇ (SDL_wcscmp(outputDesc.DeviceName, DeviceName) == 0) {
                    ਨਤੀਜਾ = pDXGIOutput;
                }
            }
            ਜੇ (pDXGIOutput != ਨਤੀਜਾ) {
                IDXGIOutput_Release(pDXGIOutput);
            }
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ ਨਤੀਜਾ;
}

ਸਥਿਰ ਖਾਲੀ WIN_ReleaseDXGIOutput(ਖਾਲੀ *dxgi_output)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_DXGI_H
    IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;

    ਜੇ (pDXGIOutput) {
        IDXGIOutput_Release(pDXGIOutput);
    }
#ਜੇ_ਅੰਤ
}

ਸਥਿਰ SDL_DisplayOrientation WIN_GetNaturalOrientation(DEVMODEW *ਬਹੁਲਕ)
{
    ਪੂਰਨ ਚੌੜਾਈ = ਬਹੁਲਕ->dm_Pels_ਚੌੜਾਈ;
    ਪੂਰਨ ਉਚਾਈ = ਬਹੁਲਕ->dm_Pels_ਉਚਾਈ;

    // Use unrotated width/height to guess orientation
    ਜੇ (ਬਹੁਲਕ->dmDisplayOrientation == DMDO_90 || ਬਹੁਲਕ->dmDisplayOrientation == DMDO_270) {
        ਪੂਰਨ ਆਰਜ਼ੀ = ਚੌੜਾਈ;
        ਚੌੜਾਈ = ਉਚਾਈ;
        ਉਚਾਈ = ਆਰਜ਼ੀ;
    }

    ਜੇ (ਚੌੜਾਈ >= ਉਚਾਈ) {
        ਵਾਪਸ SDL_ORIENTATION_LANDSCAPE;
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_ORIENTATION_PORTRAIT;
    }
}

ਸਥਿਰ SDL_DisplayOrientation WIN_GetDisplayOrientation(DEVMODEW *ਬਹੁਲਕ)
{
    ਜੇ (WIN_GetNaturalOrientation(ਬਹੁਲਕ) == SDL_ORIENTATION_LANDSCAPE) {
        ਚੋਣ (ਬਹੁਲਕ->dmDisplayOrientation) {
        ਹਾਲਤ DMDO_DEFAULT:
            ਵਾਪਸ SDL_ORIENTATION_LANDSCAPE;
        ਹਾਲਤ DMDO_90:
            ਵਾਪਸ SDL_ORIENTATION_PORTRAIT;
        ਹਾਲਤ DMDO_180:
            ਵਾਪਸ SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        ਹਾਲਤ DMDO_270:
            ਵਾਪਸ SDL_ORIENTATION_PORTRAIT_FLIPPED;
        ਮੂਲ:
            ਵਾਪਸ SDL_ORIENTATION_UNKNOWN;
        }
    } ਨਹੀਂਤਾਂ {
        ਚੋਣ (ਬਹੁਲਕ->dmDisplayOrientation) {
        ਹਾਲਤ DMDO_DEFAULT:
            ਵਾਪਸ SDL_ORIENTATION_PORTRAIT;
        ਹਾਲਤ DMDO_90:
            ਵਾਪਸ SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        ਹਾਲਤ DMDO_180:
            ਵਾਪਸ SDL_ORIENTATION_PORTRAIT_FLIPPED;
        ਹਾਲਤ DMDO_270:
            ਵਾਪਸ SDL_ORIENTATION_LANDSCAPE;
        ਮੂਲ:
            ਵਾਪਸ SDL_ORIENTATION_UNKNOWN;
        }
    }
}

ਸਥਿਰ ਖਾਲੀ WIN_Get_Refresh_ਦਰ(ਖਾਲੀ *dxgi_output, DEVMODEW *ਬਹੁਲਕ, ਪੂਰਨ *numerator, ਪੂਰਨ *denominator)
{
    // We're not currently using DXGI to query display modes, so fake NTSC timings
    ਚੋਣ (ਬਹੁਲਕ->dmDisplayFrequency) {
    ਹਾਲਤ 119:
    ਹਾਲਤ 59:
    ਹਾਲਤ 29:
        *numerator = (ਬਹੁਲਕ->dmDisplayFrequency + 1) * 1000;
        *denominator = 1001;
        ਰੋਕੋ;
    ਮੂਲ:
        *numerator = ਬਹੁਲਕ->dmDisplayFrequency;
        *denominator = 1;
        ਰੋਕੋ;
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_DXGI_H
    ਜੇ (dxgi_output) {
        IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;
        DXGI_ਬਹੁਲਕ_DESC ਬਹੁਲਕ_ਮੰਜ਼ਿਲ_ਮੇਲ;
        DXGI_ਬਹੁਲਕ_DESC closest_ਮੇਲ;

        SDL_zero(ਬਹੁਲਕ_ਮੰਜ਼ਿਲ_ਮੇਲ);
        ਬਹੁਲਕ_ਮੰਜ਼ਿਲ_ਮੇਲ.ਚੌੜਾਈ_2 = ਬਹੁਲਕ->dm_Pels_ਚੌੜਾਈ;
        ਬਹੁਲਕ_ਮੰਜ਼ਿਲ_ਮੇਲ.ਉਚਾਈ_2 = ਬਹੁਲਕ->dm_Pels_ਉਚਾਈ;
        ਬਹੁਲਕ_ਮੰਜ਼ਿਲ_ਮੇਲ.Refresh_ਦਰ.Numerator = *numerator;
        ਬਹੁਲਕ_ਮੰਜ਼ਿਲ_ਮੇਲ.Refresh_ਦਰ.Denominator = *denominator;
        ਬਹੁਲਕ_ਮੰਜ਼ਿਲ_ਮੇਲ.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        ਜੇ (SUCCEEDED(IDXGIOutput_ਲੱਭੋ_Closest_Matching_ਬਹੁਲਕ(pDXGIOutput, &ਬਹੁਲਕ_ਮੰਜ਼ਿਲ_ਮੇਲ, &closest_ਮੇਲ, ਨਿਰਾ))) {
            *numerator = closest_ਮੇਲ.Refresh_ਦਰ.Numerator;
            *denominator = closest_ਮੇਲ.Refresh_ਦਰ.Denominator;
        }
    }
#ਜੇ_ਅੰਤ // HAVE_DXGI_H
}

ਸਥਿਰ ਦਸ਼ਮਲਵ WIN_GetContentScale(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    ਪੂਰਨ dpi = 0;

    ਅਚਲ SDL_Video_ਅੰਕੜੇ *videodata = (ਅਚਲ SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    ਜੇ (videodata->GetDpiForMonitor) {
        UINT hdpi_uint, vdpi_uint;
        ਜੇ (videodata->GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
            dpi = (ਪੂਰਨ)hdpi_uint;
        }
    }
    ਜੇ (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(ਨਿਰਾ);
        ਜੇ (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(ਨਿਰਾ, hdc);
        }
    }
    ਜੇ (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    ਵਾਪਸ dpi / (ਦਸ਼ਮਲਵ)USER_DEFAULT_SCREEN_DPI;
}

ਸਥਿਰ bool WIN_Get_Display_ਬਹੁਲਕ(SDL_VideoDevice *_this, ਖਾਲੀ *dxgi_output, HMONITOR hMonitor, LPCWSTR deviceName, DWORD ਸੂਚਕਾਂਕ, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ, SDL_DisplayOrientation *natural_orientation, SDL_DisplayOrientation *current_orientation)
{
    SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *ਅੰਕੜੇ;
    DEVMODEW devmode;

    devmode.dm_ਮਾਪ = ਆਕਾਰ(devmode);
    devmode.dmDriverExtra = 0;
    ਜੇ (!EnumDisplaySettingsW(deviceName, ਸੂਚਕਾਂਕ, &devmode)) {
        ਵਾਪਸ false;
    }

    ਅੰਕੜੇ = (SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *)SDL_malloc(ਆਕਾਰ(*ਅੰਕੜੇ));
    ਜੇ (!ਅੰਕੜੇ) {
        ਵਾਪਸ false;
    }

    SDL_zerop(ਬਹੁਲਕ);
    ਬਹੁਲਕ->ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;
    ਅੰਕੜੇ->Device_ਬਹੁਲਕ = devmode;

    ਬਹੁਲਕ->format = SDL_PIXELFORMAT_UNKNOWN;
    ਬਹੁਲਕ->w = ਅੰਕੜੇ->Device_ਬਹੁਲਕ.dm_Pels_ਚੌੜਾਈ;
    ਬਹੁਲਕ->h = ਅੰਕੜੇ->Device_ਬਹੁਲਕ.dm_Pels_ਉਚਾਈ;
    WIN_Get_Refresh_ਦਰ(dxgi_output, &ਅੰਕੜੇ->Device_ਬਹੁਲਕ, &ਬਹੁਲਕ->refresh_ਦਰ_numerator, &ਬਹੁਲਕ->refresh_ਦਰ_denominator);

    // Fill in the mode information
    WIN_Update_Display_ਬਹੁਲਕ(_this, deviceName, ਸੂਚਕਾਂਕ, ਬਹੁਲਕ);

    ਜੇ (natural_orientation) {
        *natural_orientation = WIN_GetNaturalOrientation(&devmode);
    }
    ਜੇ (current_orientation) {
        *current_orientation = WIN_GetDisplayOrientation(&devmode);
    }

    ਵਾਪਸ true;
}

ਸਥਿਰ ਅੱਖਰ *WIN_GetDisplayNameVista(SDL_Video_ਅੰਕੜੇ *videodata, ਅਚਲ WCHAR *deviceName)
{
    DISPLAYCONFIG_ਰਸਤਾ_INFO *paths = ਨਿਰਾ;
    DISPLAYCONFIG_ਬਹੁਲਕ_INFO *modes = ਨਿਰਾ;
    ਅੱਖਰ *ਨਤੀਜਾ = ਨਿਰਾ;
    UINT32 ਰਸਤਾ_ਗਿਣਤੀ_2 = 0;
    UINT32 ਬਹੁਲਕ_ਗਿਣਤੀ_2 = 0;
    UINT32 i;
    LONG rc;

    ਜੇ (!videodata->Get_Display_Config_ਬਫਰ_Sizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਕਰੋ {
        rc = videodata->Get_Display_Config_ਬਫਰ_Sizes(QDC_ONLY_ਸਰਗਰਮ_PATHS, &ਰਸਤਾ_ਗਿਣਤੀ_2, &ਬਹੁਲਕ_ਗਿਣਤੀ_2);
        ਜੇ (rc != ERROR_SUCCESS) {
            ਜਾਓ WIN_GetDisplayNameVista_failed;
        }

        SDL_free(paths);
        SDL_free(modes);

        paths = (DISPLAYCONFIG_ਰਸਤਾ_INFO *)SDL_malloc(ਆਕਾਰ(DISPLAYCONFIG_ਰਸਤਾ_INFO) * ਰਸਤਾ_ਗਿਣਤੀ_2);
        modes = (DISPLAYCONFIG_ਬਹੁਲਕ_INFO *)SDL_malloc(ਆਕਾਰ(DISPLAYCONFIG_ਬਹੁਲਕ_INFO) * ਬਹੁਲਕ_ਗਿਣਤੀ_2);
        ਜੇ ((!paths) || (!modes)) {
            ਜਾਓ WIN_GetDisplayNameVista_failed;
        }

        rc = videodata->QueryDisplayConfig(QDC_ONLY_ਸਰਗਰਮ_PATHS, &ਰਸਤਾ_ਗਿਣਤੀ_2, paths, &ਬਹੁਲਕ_ਗਿਣਤੀ_2, modes, 0);
    } ਜਦੋਂ (rc == ERROR_INSUFFICIENT_ਬਫਰ);

    ਜੇ (rc == ERROR_SUCCESS) {
        ਲਈ (i = 0; i < ਰਸਤਾ_ਗਿਣਤੀ_2; i++) {
            DISPLAYCONFIG_ਸਰੋਤ_DEVICE_NAME ਸਰੋਤ_Name;
            DISPLAYCONFIG_ਨਿਸ਼ਾਨਾ_DEVICE_NAME ਨਿਸ਼ਾਨਾ_Name;

            SDL_zero(ਸਰੋਤ_Name);
            ਸਰੋਤ_Name.ਸਿਰਲੇਖ.adapterId = paths[i].ਨਿਸ਼ਾਨਾ_Info.adapterId;
            ਸਰੋਤ_Name.ਸਿਰਲੇਖ.type = DISPLAYCONFIG_DEVICE_INFO_GET_ਸਰੋਤ_NAME;
            ਸਰੋਤ_Name.ਸਿਰਲੇਖ.ਮਾਪ = ਆਕਾਰ(ਸਰੋਤ_Name);
            ਸਰੋਤ_Name.ਸਿਰਲੇਖ.id = paths[i].ਸਰੋਤ_Info.id;
            rc = videodata->DisplayConfigGetDeviceInfo(&ਸਰੋਤ_Name.ਸਿਰਲੇਖ);
            ਜੇ (rc != ERROR_SUCCESS) {
                ਰੋਕੋ;
            } ਨਹੀਂਤਾਂ ਜੇ (SDL_wcscmp(deviceName, ਸਰੋਤ_Name.viewGdiDeviceName) != 0) {
                ਜਾਰੀ;
            }

            SDL_zero(ਨਿਸ਼ਾਨਾ_Name);
            ਨਿਸ਼ਾਨਾ_Name.ਸਿਰਲੇਖ.adapterId = paths[i].ਨਿਸ਼ਾਨਾ_Info.adapterId;
            ਨਿਸ਼ਾਨਾ_Name.ਸਿਰਲੇਖ.id = paths[i].ਨਿਸ਼ਾਨਾ_Info.id;
            ਨਿਸ਼ਾਨਾ_Name.ਸਿਰਲੇਖ.type = DISPLAYCONFIG_DEVICE_INFO_GET_ਨਿਸ਼ਾਨਾ_NAME;
            ਨਿਸ਼ਾਨਾ_Name.ਸਿਰਲੇਖ.ਮਾਪ = ਆਕਾਰ(ਨਿਸ਼ਾਨਾ_Name);
            rc = videodata->DisplayConfigGetDeviceInfo(&ਨਿਸ਼ਾਨਾ_Name.ਸਿਰਲੇਖ);
            ਜੇ (rc == ERROR_SUCCESS) {
                ਨਤੀਜਾ = WIN_String_ਮੰਜ਼ਿਲ_UTF8_W(ਨਿਸ਼ਾਨਾ_Name.monitorFriendlyDeviceName);
                /* if we got an empty string, treat it as failure so we'll fallback
                   to getting the generic name. */
                ਜੇ (ਨਤੀਜਾ && (*ਨਤੀਜਾ == '\0')) {
                    SDL_free(ਨਤੀਜਾ);
                    ਨਤੀਜਾ = ਨਿਰਾ;
                }
            }
            ਰੋਕੋ;
        }
    }

    SDL_free(paths);
    SDL_free(modes);
    ਵਾਪਸ ਨਤੀਜਾ;

WIN_GetDisplayNameVista_failed:
    SDL_free(ਨਤੀਜਾ);
    SDL_free(paths);
    SDL_free(modes);
    ਵਾਪਸ ਨਿਰਾ;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_DXGI1_6_H
ਸਥਿਰ bool WIN_GetMonitorDESC1(HMONITOR hMonitor, DXGI_OUTPUT_DESC1 *desc)
{
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ HRESULT (WINAPI *pfnCreateDXGIFactory1)(REFIID riid, ਖਾਲੀ **ppFactory);
    pfnCreateDXGIFactory1 pCreateDXGIFactory1 = ਨਿਰਾ;
    SDL_SharedObject *hDXGIMod = ਨਿਰਾ;
    bool ਮਿਲਿਆ = false;

    hDXGIMod = SDL_ਲੱਦੋ_Object("dxgi.dll");
    ਜੇ (hDXGIMod) {
        pCreateDXGIFactory1 = (pfnCreateDXGIFactory1)SDL_ਲੱਦੋ_Function(hDXGIMod, "CreateDXGIFactory1");
    }
    ਜੇ (pCreateDXGIFactory1) {
        ਸਥਿਰ ਅਚਲ GUID SDL_IID_IDXGIFactory1 = { 0x770aae78, 0xf26f, 0x4dba, { 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 } };
        ਸਥਿਰ ਅਚਲ GUID SDL_IID_IDXGIOutput6 = { 0x068346e8, 0xaaec, 0x4b84, { 0xad, 0xd7, 0x13, 0x7f, 0x51, 0x3f, 0x77, 0xa1 } };
        IDXGIFactory1 *dxgiFactory;

        ਜੇ (SUCCEEDED(pCreateDXGIFactory1(&SDL_IID_IDXGIFactory1, (ਖਾਲੀ **)&dxgiFactory))) {
            IDXGIAdapter1 *dxgiAdapter;
            UINT adapter = 0;
            ਜਦੋਂ (!ਮਿਲਿਆ && SUCCEEDED(IDXGIFactory1_EnumAdapters1(dxgiFactory, adapter, &dxgiAdapter))) {
                IDXGIOutput *dxgiOutput;
                UINT output = 0;
                ਜਦੋਂ (!ਮਿਲਿਆ && SUCCEEDED(IDXGIAdapter1_EnumOutputs(dxgiAdapter, output, &dxgiOutput))) {
                    IDXGIOutput6 *dxgiOutput6;
                    ਜੇ (SUCCEEDED(IDXGIOutput_QueryInterface(dxgiOutput, &SDL_IID_IDXGIOutput6, (ਖਾਲੀ **)&dxgiOutput6))) {
                        ਜੇ (SUCCEEDED(IDXGIOutput6_GetDesc1(dxgiOutput6, desc))) {
                            ਜੇ (desc->Monitor == hMonitor) {
                                ਮਿਲਿਆ = true;
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
    ਜੇ (hDXGIMod) {
        SDL_UnloadObject(hDXGIMod);
    }
    ਵਾਪਸ ਮਿਲਿਆ;
}

ਸਥਿਰ bool WIN_Get_Monitor_ਰਸਤਾ_Info(SDL_Video_ਅੰਕੜੇ *videodata, HMONITOR hMonitor, DISPLAYCONFIG_ਰਸਤਾ_INFO *ਰਸਤਾ_info)
{
    LONG ਨਤੀਜਾ;
    MONITORINFOEXW view_info;
    UINT32 i;
    UINT32 ਅੰਕ_ਰਸਤਾ_array_elements = 0;
    UINT32 ਅੰਕ_ਬਹੁਲਕ_info_array_elements = 0;
    DISPLAYCONFIG_ਰਸਤਾ_INFO *ਰਸਤਾ_infos = ਨਿਰਾ, *new_ਰਸਤਾ_infos;
    DISPLAYCONFIG_ਬਹੁਲਕ_INFO *ਬਹੁਲਕ_infos = ਨਿਰਾ, *new_ਬਹੁਲਕ_infos;
    bool ਮਿਲਿਆ = false;

    ਜੇ (!videodata->Get_Display_Config_ਬਫਰ_Sizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        ਵਾਪਸ false;
    }

    SDL_zero(view_info);
    view_info.cb_ਮਾਪ = ਆਕਾਰ(view_info);
    ਜੇ (!GetMonitorInfoW(hMonitor, (MONITORINFO *)&view_info)) {
        ਜਾਓ ਪੂਰਾ;
    }

    ਕਰੋ {
        ਜੇ (videodata->Get_Display_Config_ਬਫਰ_Sizes(QDC_ONLY_ਸਰਗਰਮ_PATHS, &ਅੰਕ_ਰਸਤਾ_array_elements, &ਅੰਕ_ਬਹੁਲਕ_info_array_elements) != ERROR_SUCCESS) {
            SDL_free(ਰਸਤਾ_infos);
            SDL_free(ਬਹੁਲਕ_infos);
            ਵਾਪਸ false;
        }

        new_ਰਸਤਾ_infos = (DISPLAYCONFIG_ਰਸਤਾ_INFO *)SDL_realloc(ਰਸਤਾ_infos, ਅੰਕ_ਰਸਤਾ_array_elements * ਆਕਾਰ(*ਰਸਤਾ_infos));
        ਜੇ (!new_ਰਸਤਾ_infos) {
            ਜਾਓ ਪੂਰਾ;
        }
        ਰਸਤਾ_infos = new_ਰਸਤਾ_infos;

        new_ਬਹੁਲਕ_infos = (DISPLAYCONFIG_ਬਹੁਲਕ_INFO *)SDL_realloc(ਬਹੁਲਕ_infos, ਅੰਕ_ਬਹੁਲਕ_info_array_elements * ਆਕਾਰ(*ਬਹੁਲਕ_infos));
        ਜੇ (!new_ਬਹੁਲਕ_infos) {
            ਜਾਓ ਪੂਰਾ;
        }
        ਬਹੁਲਕ_infos = new_ਬਹੁਲਕ_infos;

        ਨਤੀਜਾ = videodata->QueryDisplayConfig(QDC_ONLY_ਸਰਗਰਮ_PATHS, &ਅੰਕ_ਰਸਤਾ_array_elements, ਰਸਤਾ_infos, &ਅੰਕ_ਬਹੁਲਕ_info_array_elements, ਬਹੁਲਕ_infos, ਨਿਰਾ);

    } ਜਦੋਂ (ਨਤੀਜਾ == ERROR_INSUFFICIENT_ਬਫਰ);

    ਜੇ (ਨਤੀਜਾ == ERROR_SUCCESS) {
        ਲਈ (i = 0; i < ਅੰਕ_ਰਸਤਾ_array_elements; ++i) {
            DISPLAYCONFIG_ਸਰੋਤ_DEVICE_NAME device_name;

            SDL_zero(device_name);
            device_name.ਸਿਰਲੇਖ.type = DISPLAYCONFIG_DEVICE_INFO_GET_ਸਰੋਤ_NAME;
            device_name.ਸਿਰਲੇਖ.ਮਾਪ = ਆਕਾਰ(device_name);
            device_name.ਸਿਰਲੇਖ.adapterId = ਰਸਤਾ_infos[i].ਸਰੋਤ_Info.adapterId;
            device_name.ਸਿਰਲੇਖ.id = ਰਸਤਾ_infos[i].ਸਰੋਤ_Info.id;
            ਜੇ (videodata->DisplayConfigGetDeviceInfo(&device_name.ਸਿਰਲੇਖ) == ERROR_SUCCESS) {
                ਜੇ (SDL_wcscmp(view_info.szDevice, device_name.viewGdiDeviceName) == 0) {
                    SDL_copyp(ਰਸਤਾ_info, &ਰਸਤਾ_infos[i]);
                    ਮਿਲਿਆ = true;
                    ਰੋਕੋ;
                }
            }
        }
    }

ਪੂਰਾ:
    SDL_free(ਰਸਤਾ_infos);
    SDL_free(ਬਹੁਲਕ_infos);

    ਵਾਪਸ ਮਿਲਿਆ;
}

ਸਥਿਰ ਦਸ਼ਮਲਵ WIN_Get_SDRWhite_ਬਿੰਦੂ(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    DISPLAYCONFIG_ਰਸਤਾ_INFO ਰਸਤਾ_info;
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    ਦਸ਼ਮਲਵ SDR_white_level = 1.0f;

    ਜੇ (WIN_Get_Monitor_ਰਸਤਾ_Info(videodata, hMonitor, &ਰਸਤਾ_info)) {
        /* workarounds for https://github.com/libsdl-org/SDL/issues/11193 */
        ਬਣਤਰ SDL_DISPLAYCONFIG_SDR_WHITE_LEVEL {
          DISPLAYCONFIG_DEVICE_INFO_ਸਿਰਲੇਖ ਸਿਰਲੇਖ;
          ULONG SDRWhiteLevel;
        } white_level;
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL 11

        SDL_zero(white_level);
        white_level.ਸਿਰਲੇਖ.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
        white_level.ਸਿਰਲੇਖ.ਮਾਪ = ਆਕਾਰ(white_level);
        white_level.ਸਿਰਲੇਖ.adapterId = ਰਸਤਾ_info.ਨਿਸ਼ਾਨਾ_Info.adapterId;
        white_level.ਸਿਰਲੇਖ.id = ਰਸਤਾ_info.ਨਿਸ਼ਾਨਾ_Info.id;
        // WIN_GetMonitorPathInfo() succeeded: DisplayConfigGetDeviceInfo is not NULL
        ਜੇ (videodata->DisplayConfigGetDeviceInfo(&white_level.ਸਿਰਲੇਖ) == ERROR_SUCCESS &&
            white_level.SDRWhiteLevel > 0) {
            SDR_white_level = (white_level.SDRWhiteLevel / 1000.0f);
        }
    }
    ਵਾਪਸ SDR_white_level;
}

ਸਥਿਰ ਖਾਲੀ WIN_GetHDRProperties(SDL_VideoDevice *_this, HMONITOR hMonitor, SDL_HDROutputProperties *HDR)
{
    DXGI_OUTPUT_DESC1 desc;

    SDL_zerop(HDR);

    ਜੇ (WIN_GetMonitorDESC1(hMonitor, &desc)) {
        ਜੇ (desc.ColorSpace == DXGI_COLOR_SPACE_RGB_ਭਰਿਆ_G2084_NONE_P2020) {
            HDR->SDR_white_level = WIN_Get_SDRWhite_ਬਿੰਦੂ(_this, hMonitor);
            HDR->HDR_headroom = (desc.MaxLuminance / SCRGB_NITS) / HDR->SDR_white_level;
        }
    }
}
#ਜੇ_ਅੰਤ // HAVE_DXGI1_6_H

ਸਥਿਰ ਖਾਲੀ WIN_ਜੋੜੋ_Display(SDL_VideoDevice *_this, HMONITOR hMonitor, ਅਚਲ MONITORINFOEXW *info, ਪੂਰਨ *display_ਸੂਚਕਾਂਕ)
{
    ਪੂਰਨ i, ਸੂਚਕਾਂਕ = *display_ਸੂਚਕਾਂਕ;
    SDL_VideoDisplay display;
    SDL_Display_ਅੰਕੜੇ *displaydata;
    ਖਾਲੀ *dxgi_output = ਨਿਰਾ;
    SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    ਦਸ਼ਮਲਵ content_scale = WIN_GetContentScale(_this, hMonitor);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_MODES
    SDL_Log("Display: %s", WIN_String_ਮੰਜ਼ਿਲ_UTF8_W(info->szDevice));
#ਜੇ_ਅੰਤ

    dxgi_output = WIN_GetDXGIOutput(_this, info->szDevice);
    bool ਮਿਲਿਆ = WIN_Get_Display_ਬਹੁਲਕ(_this, dxgi_output, hMonitor, info->szDevice, ENUM_CURRENT_SETTINGS, &ਬਹੁਲਕ, &natural_orientation, &current_orientation);
    WIN_ReleaseDXGIOutput(dxgi_output);
    ਜੇ (!ਮਿਲਿਆ) {
        ਵਾਪਸ;
    }

    // Prevent adding duplicate displays. Do this after we know the display is
    // ready to be added to allow any displays that we can't fully query to be
    // removed
    ਲਈ (i = 0; i < _this->ਅੰਕ_displays; ++i) {
        SDL_Display_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = _this->displays[i]->ਅੰਦਰੂਨੀ;
        ਜੇ (SDL_wcscmp(ਅੰਦਰੂਨੀ->DeviceName, info->szDevice) == 0) {
            bool moved = (ਸੂਚਕਾਂਕ != i);
            bool ਬਦਲਿਆ_bounds = false;

            ਜੇ (ਅੰਦਰੂਨੀ->state != DisplayRemoved) {
                // We've already enumerated this display, don't move it
                ਜਾਓ cleanup;
            }

            ਜੇ (ਸੂਚਕਾਂਕ >= _this->ਅੰਕ_displays) {
                // This should never happen due to the check above, but just in case...
                ਜਾਓ cleanup;
            }

            ਜੇ (moved) {
                SDL_VideoDisplay *tmp;

                tmp = _this->displays[ਸੂਚਕਾਂਕ];
                _this->displays[ਸੂਚਕਾਂਕ] = _this->displays[i];
                _this->displays[i] = tmp;
                i = ਸੂਚਕਾਂਕ;
            }

            ਅੰਦਰੂਨੀ->MonitorHandle = hMonitor;
            ਅੰਦਰੂਨੀ->state = DisplayUnchanged;

            SDL_PropertiesID props = SDL_GetDisplayProperties(_this->displays[i]->id);
            SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_ਸੂਚਕ, hMonitor);

            ਜੇ (!_this->setting_display_ਬਹੁਲਕ) {
                SDL_VideoDisplay *existing_display = _this->displays[i];
                SDL_Rect bounds;

                SDL_ResetFullscreenDisplayModes(existing_display);
                SDL_ਸੈੱਟ_Desktop_Display_ਬਹੁਲਕ(existing_display, &ਬਹੁਲਕ);
                // The mode is owned by the video subsystem
                ਬਹੁਲਕ.ਅੰਦਰੂਨੀ = ਨਿਰਾ;
                ਜੇ (WIN_GetDisplayBounds(_this, existing_display, &bounds) &&
                    SDL_memcmp(&ਅੰਦਰੂਨੀ->bounds, &bounds, ਆਕਾਰ(bounds)) != 0) {
                    ਬਦਲਿਆ_bounds = true;
                    SDL_copyp(&ਅੰਦਰੂਨੀ->bounds, &bounds);
                }
                ਜੇ (moved || ਬਦਲਿਆ_bounds) {
                    SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_MOVED, 0, 0);
                }
                SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_ORIENTATION, current_orientation, 0);
                SDL_ਸੈੱਟ_Display_Content_Scale(existing_display, content_scale);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_DXGI1_6_H
                SDL_HDROutputProperties HDR;
                WIN_GetHDRProperties(_this, hMonitor, &HDR);
                SDL_ਸੈੱਟ_Display_HDRProperties(existing_display, &HDR);
#ਜੇ_ਅੰਤ
            }
            ਜਾਓ ਪੂਰਾ;
        }
    }

    displaydata = (SDL_Display_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(*displaydata));
    ਜੇ (!displaydata) {
        ਜਾਓ cleanup;
    }
    SDL_memcpy(displaydata->DeviceName, info->szDevice, ਆਕਾਰ(displaydata->DeviceName));
    displaydata->MonitorHandle = hMonitor;
    displaydata->state = DisplayAdded;

    SDL_zero(display);
    display.name = WIN_GetDisplayNameVista(_this->ਅੰਦਰੂਨੀ, info->szDevice);
    ਜੇ (!display.name) {
        DISPLAY_DEVICEW device;
        SDL_zero(device);
        device.cb = ਆਕਾਰ(device);
        ਜੇ (EnumDisplayDevicesW(info->szDevice, 0, &device, 0)) {
            display.name = WIN_String_ਮੰਜ਼ਿਲ_UTF8_W(device.DeviceString);
        }
    }

    display.desktop_ਬਹੁਲਕ = ਬਹੁਲਕ;
    display.natural_orientation = natural_orientation;
    display.current_orientation = current_orientation;
    display.content_scale = content_scale;
    display.device = _this;
    display.ਅੰਦਰੂਨੀ = displaydata;
    WIN_GetDisplayBounds(_this, &display, &displaydata->bounds);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_DXGI1_6_H
    WIN_GetHDRProperties(_this, hMonitor, &display.HDR);
#ਜੇ_ਅੰਤ
    SDL_DisplayID displayID = SDL_ਜੋੜੋ_Video_Display(&display, false);
    ਜੇ (displayID) {
        // The mode is owned by the video subsystem
        ਬਹੁਲਕ.ਅੰਦਰੂਨੀ = ਨਿਰਾ;

        SDL_PropertiesID props = SDL_GetDisplayProperties(displayID);
        SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_ਸੂਚਕ, hMonitor);
    } ਨਹੀਂਤਾਂ {
        SDL_free(displaydata);
    }
    SDL_free(display.name);

ਪੂਰਾ:
    *display_ਸੂਚਕਾਂਕ += 1;

cleanup:
    SDL_free(ਬਹੁਲਕ.ਅੰਦਰੂਨੀ);
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ WIN_ਜੋੜੋ_Displays_ਅੰਕੜੇ
{
    SDL_VideoDevice *video_device;
    ਪੂਰਨ display_ਸੂਚਕਾਂਕ;
    bool want_primary;
} WIN_ਜੋੜੋ_Displays_ਅੰਕੜੇ_2;

ਸਥਿਰ BOOL CALLBACK WIN_ਜੋੜੋ_Displays_Callback(HMONITOR hMonitor,
                                             HDC hdcMonitor,
                                             LPRECT lprcMonitor,
                                             LPARAM dw_ਅੰਕੜੇ)
{
    WIN_ਜੋੜੋ_Displays_ਅੰਕੜੇ_2 *ਅੰਕੜੇ = (WIN_ਜੋੜੋ_Displays_ਅੰਕੜੇ_2 *)dw_ਅੰਕੜੇ;
    MONITORINFOEXW info;

    SDL_zero(info);
    info.cb_ਮਾਪ = ਆਕਾਰ(info);

    ਜੇ (GetMonitorInfoW(hMonitor, (LPMONITORINFO)&info) != 0) {
        ਅਚਲ bool is_primary = ((info.dwFlags & MONITORINFOF_PRIMARY) == MONITORINFOF_PRIMARY);

        ਜੇ (is_primary == ਅੰਕੜੇ->want_primary) {
            WIN_ਜੋੜੋ_Display(ਅੰਕੜੇ->video_device, hMonitor, &info, &ਅੰਕੜੇ->display_ਸੂਚਕਾਂਕ);
        }
    }

    // continue enumeration
    ਵਾਪਸ TRUE;
}

ਸਥਿਰ ਖਾਲੀ WIN_ਜੋੜੋ_Displays(SDL_VideoDevice *_this)
{
    WIN_ਜੋੜੋ_Displays_ਅੰਕੜੇ_2 callback_ਅੰਕੜੇ;
    callback_ਅੰਕੜੇ.video_device = _this;
    callback_ਅੰਕੜੇ.display_ਸੂਚਕਾਂਕ = 0;

    callback_ਅੰਕੜੇ.want_primary = true;
    EnumDisplayMonitors(ਨਿਰਾ, ਨਿਰਾ, WIN_ਜੋੜੋ_Displays_Callback, (LPARAM)&callback_ਅੰਕੜੇ);

    callback_ਅੰਕੜੇ.want_primary = false;
    EnumDisplayMonitors(ਨਿਰਾ, ਨਿਰਾ, WIN_ਜੋੜੋ_Displays_Callback, (LPARAM)&callback_ਅੰਕੜੇ);
}

bool WIN_InitModes(SDL_VideoDevice *_this)
{
    WIN_ਜੋੜੋ_Displays(_this);

    ਜੇ (_this->ਅੰਕ_displays == 0) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("No displays available");
    }
    ਵਾਪਸ true;
}

bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ਅਚਲ SDL_Display_ਅੰਕੜੇ *ਅੰਕੜੇ = display->ਅੰਦਰੂਨੀ;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cb_ਮਾਪ = ਆਕਾਰ(MONITORINFO);
    rc = GetMonitorInfo(ਅੰਕੜੇ->MonitorHandle, &minfo);

    ਜੇ (!rc) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't find monitor data");
    }

    rect->x = minfo.rcMonitor.ਖੱਬਾ;
    rect->y = minfo.rcMonitor.ਸਿਖਰ;
    rect->w = minfo.rcMonitor.ਸੱਜਾ - minfo.rcMonitor.ਖੱਬਾ;
    rect->h = minfo.rcMonitor.bottom - minfo.rcMonitor.ਸਿਖਰ;

    ਵਾਪਸ true;
}

bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ਅਚਲ SDL_Display_ਅੰਕੜੇ *ਅੰਕੜੇ = display->ਅੰਦਰੂਨੀ;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cb_ਮਾਪ = ਆਕਾਰ(MONITORINFO);
    rc = GetMonitorInfo(ਅੰਕੜੇ->MonitorHandle, &minfo);

    ਜੇ (!rc) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't find monitor data");
    }

    rect->x = minfo.rcWork.ਖੱਬਾ;
    rect->y = minfo.rcWork.ਸਿਖਰ;
    rect->w = minfo.rcWork.ਸੱਜਾ - minfo.rcWork.ਖੱਬਾ;
    rect->h = minfo.rcWork.bottom - minfo.rcWork.ਸਿਖਰ;

    ਵਾਪਸ true;
}

bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_ਅੰਕੜੇ *ਅੰਕੜੇ = display->ਅੰਦਰੂਨੀ;
    ਖਾਲੀ *dxgi_output;
    DWORD i;
    SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;

    dxgi_output = WIN_GetDXGIOutput(_this, ਅੰਕੜੇ->DeviceName);

    // Make sure we add the current mode to the list in case it's a custom mode that doesn't enumerate
    ਲਈ (i = ENUM_CURRENT_SETTINGS; ; ++i) {
        ਜੇ (!WIN_Get_Display_ਬਹੁਲਕ(_this, dxgi_output, ਅੰਕੜੇ->MonitorHandle, ਅੰਕੜੇ->DeviceName, i, &ਬਹੁਲਕ, ਨਿਰਾ, ਨਿਰਾ)) {
            ਰੋਕੋ;
        }
        ਜੇ (SDL_ISPIXELFORMAT_ਸੂਚਕਾਂਕਿਤ(ਬਹੁਲਕ.format)) {
            // We don't support palettized modes now
            SDL_free(ਬਹੁਲਕ.ਅੰਦਰੂਨੀ);
            ਜਾਰੀ;
        }
        ਜੇ (ਬਹੁਲਕ.format != SDL_PIXELFORMAT_UNKNOWN) {
            ਜੇ (!SDL_ਜੋੜੋ_Fullscreen_Display_ਬਹੁਲਕ(display, &ਬਹੁਲਕ)) {
                SDL_free(ਬਹੁਲਕ.ਅੰਦਰੂਨੀ);
            }
        } ਨਹੀਂਤਾਂ {
            SDL_free(ਬਹੁਲਕ.ਅੰਦਰੂਨੀ);
        }
    }

    WIN_ReleaseDXGIOutput(dxgi_output);

    ਵਾਪਸ true;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_MODES
ਸਥਿਰ ਖਾਲੀ WIN_LogMonitor(SDL_VideoDevice *_this, HMONITOR mon)
{
    ਅਚਲ SDL_Video_ਅੰਕੜੇ *vid_ਅੰਕੜੇ = (ਅਚਲ SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    MONITORINFOEX minfo;
    UINT xdpi = 0, ydpi = 0;
    ਅੱਖਰ *name_utf8;

    ਜੇ (vid_ਅੰਕੜੇ->GetDpiForMonitor) {
        vid_ਅੰਕੜੇ->GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &xdpi, &ydpi);
    }

    SDL_zero(minfo);
    minfo.cb_ਮਾਪ = ਆਕਾਰ(minfo);
    GetMonitorInfo(mon, (LPMONITORINFO)&minfo);

    name_utf8 = WIN_String_ਮੰਜ਼ਿਲ_UTF8(minfo.szDevice);

    SDL_Log("WIN_LogMonitor: monitor \"%s\": dpi: %d windows screen coordinates: %d, %d, %dx%d",
            name_utf8,
            xdpi,
            minfo.rcMonitor.ਖੱਬਾ,
            minfo.rcMonitor.ਸਿਖਰ,
            minfo.rcMonitor.ਸੱਜਾ - minfo.rcMonitor.ਖੱਬਾ,
            minfo.rcMonitor.bottom - minfo.rcMonitor.ਸਿਖਰ);

    SDL_free(name_utf8);
}
#ਜੇ_ਅੰਤ

bool WIN_ਸੈੱਟ_Display_ਬਹੁਲਕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ)
{
    SDL_Display_ਅੰਕੜੇ *displaydata = display->ਅੰਦਰੂਨੀ;
    SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *ਅੰਕੜੇ = (SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *)ਬਹੁਲਕ->ਅੰਦਰੂਨੀ;
    LONG ਸਥਿਤੀ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state before mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#ਜੇ_ਅੰਤ

    /* High-DPI notes:

       - ChangeDisplaySettingsEx always takes pixels.
       - e.g. if the display is set to 2880x1800 with 200% scaling in Display Settings
         - calling ChangeDisplaySettingsEx with a dmPelsWidth/Height other than 2880x1800 will
           change the monitor DPI to 96. (100% scaling)
         - calling ChangeDisplaySettingsEx with a dmPelsWidth/Height of 2880x1800 (or a NULL DEVMODE*) will
           reset the monitor DPI to 192. (200% scaling)

       NOTE: these are temporary changes in DPI, not modifications to the Control Panel setting. */
    ਜੇ (ਬਹੁਲਕ->ਅੰਦਰੂਨੀ == display->desktop_ਬਹੁਲਕ.ਅੰਦਰੂਨੀ) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: resetting to original resolution");
#ਜੇ_ਅੰਤ
        ਸਥਿਤੀ = ChangeDisplaySettingsExW(displaydata->DeviceName, ਨਿਰਾ, ਨਿਰਾ, CDS_FULLSCREEN, ਨਿਰਾ);
    } ਨਹੀਂਤਾਂ {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: changing to %dx%d pixels", ਅੰਕੜੇ->Device_ਬਹੁਲਕ.dm_Pels_ਚੌੜਾਈ, ਅੰਕੜੇ->Device_ਬਹੁਲਕ.dm_Pels_ਉਚਾਈ);
#ਜੇ_ਅੰਤ
        ਸਥਿਤੀ = ChangeDisplaySettingsExW(displaydata->DeviceName, &ਅੰਕੜੇ->Device_ਬਹੁਲਕ, ਨਿਰਾ, CDS_FULLSCREEN, ਨਿਰਾ);
    }
    ਜੇ (ਸਥਿਤੀ != DISP_CHANGE_SUCCESSFUL) {
        ਅਚਲ ਅੱਖਰ *reason = "Unknown reason";
        ਚੋਣ (ਸਥਿਤੀ) {
        ਹਾਲਤ DISP_CHANGE_BADFLAGS:
            reason = "DISP_CHANGE_BADFLAGS";
            ਰੋਕੋ;
        ਹਾਲਤ DISP_CHANGE_BADMODE:
            reason = "DISP_CHANGE_BADMODE";
            ਰੋਕੋ;
        ਹਾਲਤ DISP_CHANGE_BADPARAM:
            reason = "DISP_CHANGE_BADPARAM";
            ਰੋਕੋ;
        ਹਾਲਤ DISP_CHANGE_FAILED:
            reason = "DISP_CHANGE_FAILED";
            ਰੋਕੋ;
        }
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("ChangeDisplaySettingsEx() failed: %s", reason);
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state after mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#ਜੇ_ਅੰਤ

    EnumDisplaySettingsW(displaydata->DeviceName, ENUM_CURRENT_SETTINGS, &ਅੰਕੜੇ->Device_ਬਹੁਲਕ);
    WIN_Update_Display_ਬਹੁਲਕ(_this, displaydata->DeviceName, ENUM_CURRENT_SETTINGS, ਬਹੁਲਕ);
    ਵਾਪਸ true;
}

ਖਾਲੀ WIN_RefreshDisplays(SDL_VideoDevice *_this)
{
    ਪੂਰਨ i;

    // Mark all displays as potentially invalid to detect
    // entries that have actually been removed
    ਲਈ (i = 0; i < _this->ਅੰਕ_displays; ++i) {
        SDL_Display_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = _this->displays[i]->ਅੰਦਰੂਨੀ;
        ਅੰਦਰੂਨੀ->state = DisplayRemoved;
    }

    // Enumerate displays to add any new ones and mark still
    // connected entries as valid
    WIN_ਜੋੜੋ_Displays(_this);

    // Delete any entries still marked as invalid, iterate
    // in reverse as each delete takes effect immediately
    ਲਈ (i = _this->ਅੰਕ_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_Display_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = display->ਅੰਦਰੂਨੀ;
        ਜੇ (ਅੰਦਰੂਨੀ->state == DisplayRemoved) {
            SDL_DelVideoDisplay(display->id, true);
        }
    }

    // Send events for any newly added displays
    ਲਈ (i = 0; i < _this->ਅੰਕ_displays; ++i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_Display_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = display->ਅੰਦਰੂਨੀ;
        ਜੇ (ਅੰਦਰੂਨੀ->state == DisplayAdded) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
        }
    }
}

ਖਾਲੀ WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this)
{
    // This almost never happens, so just go ahead and send update events for all displays
    ਲਈ (ਪੂਰਨ i = 0; i < _this->ਅੰਕ_displays; ++i) {
        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_ਬਦਲਿਆ, 0, 0);
    }
}

ਖਾਲੀ WIN_QuitModes(SDL_VideoDevice *_this)
{
    // All fullscreen windows should have restored modes by now
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WINDOWS
