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

#ಯದಿ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ಅನ್ತರ್ಭಾವ "SDL_windowsvideo.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_displayevents_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_pixels_c.h"

#ifdef HAVE_DXGI1_6_H
#define COBJMACROS
#ಅನ್ತರ್ಭಾವ <dxgi1_6.h>
#endif

// Windows CE compatibility
#ifndef CDS_FULLSCREEN
#define CDS_FULLSCREEN 0
#endif
#ifndef USER_DEFAULT_SCREEN_DPI
#define USER_DEFAULT_SCREEN_DPI 96
#endif

// #define DEBUG_MODES
// #define HIGHDPI_DEBUG_VERBOSE

ಸ್ಥಿರ ಶೂನ್ಯ WIN_UpdateDisplayMode(SDL_VideoDevice *_this, LPCWSTR deviceName, DWORD index, SDL_DisplayMode *mode)
{
    SDL_DisplayModeData *data = (SDL_DisplayModeData *)mode->internal;
    HDC hdc;

    data->DeviceMode.dmFields = (DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS);

    // NOLINTNEXTLINE(bugprone-assignment-in-if-condition): No simple way to extract the assignment
    ಯದಿ (index == ENUM_CURRENT_SETTINGS && (hdc = CreateDCW(deviceName, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ)) != ರಿಕ್ತ) {
        ವರ್ಣ bmi_data[ಪರಿಮಾಣ(BITMAPINFOHEADER) + 256 * ಪರಿಮಾಣ(RGBQUAD)];
        LPBITMAPINFO bmi;
        HBITMAP hbm;

        SDL_zeroa(bmi_data);
        bmi = (LPBITMAPINFO)bmi_data;
        bmi->bmiHeader.biSize = ಪರಿಮಾಣ(BITMAPINFOHEADER);

        hbm = CreateCompatibleBitmap(hdc, 1, 1);
        GetDIBits(hdc, hbm, 0, 1, ರಿಕ್ತ, bmi, DIB_RGB_COLORS);
        GetDIBits(hdc, hbm, 0, 1, ರಿಕ್ತ, bmi, DIB_RGB_COLORS);
        DeleteObject(hbm);
        DeleteDC(hdc);
        ಯದಿ (bmi->bmiHeader.biCompression == BI_BITFIELDS) {
            ವಿಕಲ್ಪ (*(Uint32 *)bmi->bmiColors) {
            ಪಕ್ಷ 0x00FF0000:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                ಭಙ್ಗ;
            ಪಕ್ಷ 0x000000FF:
                mode->format = SDL_PIXELFORMAT_XBGR8888;
                ಭಙ್ಗ;
            ಪಕ್ಷ 0xF800:
                mode->format = SDL_PIXELFORMAT_RGB565;
                ಭಙ್ಗ;
            ಪಕ್ಷ 0x7C00:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                ಭಙ್ಗ;
            }
        } ಅನ್ಯಥಾ ಯದಿ (bmi->bmiHeader.biCompression == BI_RGB) {
            ಯದಿ (bmi->bmiHeader.bi_Bit_ಎಣಿಕೆ == 24) {
                mode->format = SDL_PIXELFORMAT_RGB24;
            } ಅನ್ಯಥಾ ಯದಿ (bmi->bmiHeader.bi_Bit_ಎಣಿಕೆ == 8) {
                mode->format = SDL_PIXELFORMAT_INDEX8;
            } ಅನ್ಯಥಾ ಯದಿ (bmi->bmiHeader.bi_Bit_ಎಣಿಕೆ == 4) {
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
            }
        }
    } ಅನ್ಯಥಾ ಯದಿ (mode->format == SDL_PIXELFORMAT_UNKNOWN) {
        // FIXME: Can we tell what this will be?
        ಯದಿ ((data->DeviceMode.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL) {
            ವಿಕಲ್ಪ (data->DeviceMode.dmBitsPerPel) {
            ಪಕ್ಷ 32:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                ಭಙ್ಗ;
            ಪಕ್ಷ 24:
                mode->format = SDL_PIXELFORMAT_RGB24;
                ಭಙ್ಗ;
            ಪಕ್ಷ 16:
                mode->format = SDL_PIXELFORMAT_RGB565;
                ಭಙ್ಗ;
            ಪಕ್ಷ 15:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                ಭಙ್ಗ;
            ಪಕ್ಷ 8:
                mode->format = SDL_PIXELFORMAT_INDEX8;
                ಭಙ್ಗ;
            ಪಕ್ಷ 4:
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
                ಭಙ್ಗ;
            }
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ *WIN_GetDXGIOutput(SDL_VideoDevice *_this, ಧ್ರುವ WCHAR *DeviceName)
{
    ಶೂನ್ಯ *result = ರಿಕ್ತ;

#ifdef HAVE_DXGI_H
    ಧ್ರುವ SDL_VideoData *videodata = (ಧ್ರುವ SDL_VideoData *)_this->internal;
    ಪೂರ್ಣಾಙ್ಕ nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    ಯದಿ (!videodata->pDXGIFactory) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    nAdapter = 0;
    ಯಾವತ್ (!result && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        ಯಾವತ್ (!result && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            ಯದಿ (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                ಯದಿ (SDL_wcscmp(outputDesc.DeviceName, DeviceName) == 0) {
                    result = pDXGIOutput;
                }
            }
            ಯದಿ (pDXGIOutput != result) {
                IDXGIOutput_Release(pDXGIOutput);
            }
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }
#endif
    ಪ್ರತ್ಯಾಗಮ result;
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_ReleaseDXGIOutput(ಶೂನ್ಯ *dxgi_output)
{
#ifdef HAVE_DXGI_H
    IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;

    ಯದಿ (pDXGIOutput) {
        IDXGIOutput_Release(pDXGIOutput);
    }
#endif
}

ಸ್ಥಿರ SDL_DisplayOrientation WIN_GetNaturalOrientation(DEVMODEW *mode)
{
    ಪೂರ್ಣಾಙ್ಕ width = mode->dmPelsWidth;
    ಪೂರ್ಣಾಙ್ಕ height = mode->dmPelsHeight;

    // Use unrotated width/height to guess orientation
    ಯದಿ (mode->dmDisplayOrientation == DMDO_90 || mode->dmDisplayOrientation == DMDO_270) {
        ಪೂರ್ಣಾಙ್ಕ temp = width;
        width = height;
        height = temp;
    }

    ಯದಿ (width >= height) {
        ಪ್ರತ್ಯಾಗಮ SDL_ORIENTATION_LANDSCAPE;
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ SDL_ORIENTATION_PORTRAIT;
    }
}

ಸ್ಥಿರ SDL_DisplayOrientation WIN_GetDisplayOrientation(DEVMODEW *mode)
{
    ಯದಿ (WIN_GetNaturalOrientation(mode) == SDL_ORIENTATION_LANDSCAPE) {
        ವಿಕಲ್ಪ (mode->dmDisplayOrientation) {
        ಪಕ್ಷ DMDO_DEFAULT:
            ಪ್ರತ್ಯಾಗಮ SDL_ORIENTATION_LANDSCAPE;
        ಪಕ್ಷ DMDO_90:
            ಪ್ರತ್ಯಾಗಮ SDL_ORIENTATION_PORTRAIT;
        ಪಕ್ಷ DMDO_180:
            ಪ್ರತ್ಯಾಗಮ SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        ಪಕ್ಷ DMDO_270:
            ಪ್ರತ್ಯಾಗಮ SDL_ORIENTATION_PORTRAIT_FLIPPED;
        ಸ್ವಭಾವ:
            ಪ್ರತ್ಯಾಗಮ SDL_ORIENTATION_UNKNOWN;
        }
    } ಅನ್ಯಥಾ {
        ವಿಕಲ್ಪ (mode->dmDisplayOrientation) {
        ಪಕ್ಷ DMDO_DEFAULT:
            ಪ್ರತ್ಯಾಗಮ SDL_ORIENTATION_PORTRAIT;
        ಪಕ್ಷ DMDO_90:
            ಪ್ರತ್ಯಾಗಮ SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        ಪಕ್ಷ DMDO_180:
            ಪ್ರತ್ಯಾಗಮ SDL_ORIENTATION_PORTRAIT_FLIPPED;
        ಪಕ್ಷ DMDO_270:
            ಪ್ರತ್ಯಾಗಮ SDL_ORIENTATION_LANDSCAPE;
        ಸ್ವಭಾವ:
            ಪ್ರತ್ಯಾಗಮ SDL_ORIENTATION_UNKNOWN;
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_GetRefreshRate(ಶೂನ್ಯ *dxgi_output, DEVMODEW *mode, ಪೂರ್ಣಾಙ್ಕ *numerator, ಪೂರ್ಣಾಙ್ಕ *denominator)
{
    // We're not currently using DXGI to query display modes, so fake NTSC timings
    ವಿಕಲ್ಪ (mode->dmDisplayFrequency) {
    ಪಕ್ಷ 119:
    ಪಕ್ಷ 59:
    ಪಕ್ಷ 29:
        *numerator = (mode->dmDisplayFrequency + 1) * 1000;
        *denominator = 1001;
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        *numerator = mode->dmDisplayFrequency;
        *denominator = 1;
        ಭಙ್ಗ;
    }

#ifdef HAVE_DXGI_H
    ಯದಿ (dxgi_output) {
        IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;
        DXGI_MODE_DESC modeToMatch;
        DXGI_MODE_DESC closestMatch;

        SDL_zero(modeToMatch);
        modeToMatch.Width = mode->dmPelsWidth;
        modeToMatch.Height = mode->dmPelsHeight;
        modeToMatch.RefreshRate.Numerator = *numerator;
        modeToMatch.RefreshRate.Denominator = *denominator;
        modeToMatch.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        ಯದಿ (SUCCEEDED(IDXGIOutput_FindClosestMatchingMode(pDXGIOutput, &modeToMatch, &closestMatch, ರಿಕ್ತ))) {
            *numerator = closestMatch.RefreshRate.Numerator;
            *denominator = closestMatch.RefreshRate.Denominator;
        }
    }
#endif // HAVE_DXGI_H
}

ಸ್ಥಿರ ಭಿನ್ನ WIN_GetContentScale(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    ಪೂರ್ಣಾಙ್ಕ dpi = 0;

    ಧ್ರುವ SDL_VideoData *videodata = (ಧ್ರುವ SDL_VideoData *)_this->internal;
    ಯದಿ (videodata->GetDpiForMonitor) {
        UINT hdpi_uint, vdpi_uint;
        ಯದಿ (videodata->GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
            dpi = (ಪೂರ್ಣಾಙ್ಕ)hdpi_uint;
        }
    }
    ಯದಿ (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(ರಿಕ್ತ);
        ಯದಿ (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(ರಿಕ್ತ, hdc);
        }
    }
    ಯದಿ (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    ಪ್ರತ್ಯಾಗಮ dpi / (ಭಿನ್ನ)USER_DEFAULT_SCREEN_DPI;
}

ಸ್ಥಿರ bool WIN_GetDisplayMode(SDL_VideoDevice *_this, ಶೂನ್ಯ *dxgi_output, HMONITOR hMonitor, LPCWSTR deviceName, DWORD index, SDL_DisplayMode *mode, SDL_DisplayOrientation *natural_orientation, SDL_DisplayOrientation *current_orientation)
{
    SDL_DisplayModeData *data;
    DEVMODEW devmode;

    devmode.dmSize = ಪರಿಮಾಣ(devmode);
    devmode.dmDriverExtra = 0;
    ಯದಿ (!EnumDisplaySettingsW(deviceName, index, &devmode)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    data = (SDL_DisplayModeData *)SDL_malloc(ಪರಿಮಾಣ(*data));
    ಯದಿ (!data) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    SDL_zerop(mode);
    mode->internal = data;
    data->DeviceMode = devmode;

    mode->format = SDL_PIXELFORMAT_UNKNOWN;
    mode->w = data->DeviceMode.dmPelsWidth;
    mode->h = data->DeviceMode.dmPelsHeight;
    WIN_GetRefreshRate(dxgi_output, &data->DeviceMode, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);

    // Fill in the mode information
    WIN_UpdateDisplayMode(_this, deviceName, index, mode);

    ಯದಿ (natural_orientation) {
        *natural_orientation = WIN_GetNaturalOrientation(&devmode);
    }
    ಯದಿ (current_orientation) {
        *current_orientation = WIN_GetDisplayOrientation(&devmode);
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ ವರ್ಣ *WIN_GetDisplayNameVista(SDL_VideoData *videodata, ಧ್ರುವ WCHAR *deviceName)
{
    DISPLAYCONFIG_PATH_INFO *paths = ರಿಕ್ತ;
    DISPLAYCONFIG_MODE_INFO *modes = ರಿಕ್ತ;
    ವರ್ಣ *result = ರಿಕ್ತ;
    UINT32 path_ಎಣಿಕೆ_2 = 0;
    UINT32 mode_ಎಣಿಕೆ_2 = 0;
    UINT32 i;
    LONG rc;

    ಯದಿ (!videodata->GetDisplayConfigBufferSizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಕುರು {
        rc = videodata->GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &path_ಎಣಿಕೆ_2, &mode_ಎಣಿಕೆ_2);
        ಯದಿ (rc != ERROR_SUCCESS) {
            ಗಚ್ಛ WIN_GetDisplayNameVista_failed;
        }

        SDL_free(paths);
        SDL_free(modes);

        paths = (DISPLAYCONFIG_PATH_INFO *)SDL_malloc(ಪರಿಮಾಣ(DISPLAYCONFIG_PATH_INFO) * path_ಎಣಿಕೆ_2);
        modes = (DISPLAYCONFIG_MODE_INFO *)SDL_malloc(ಪರಿಮಾಣ(DISPLAYCONFIG_MODE_INFO) * mode_ಎಣಿಕೆ_2);
        ಯದಿ ((!paths) || (!modes)) {
            ಗಚ್ಛ WIN_GetDisplayNameVista_failed;
        }

        rc = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &path_ಎಣಿಕೆ_2, paths, &mode_ಎಣಿಕೆ_2, modes, 0);
    } ಯಾವತ್ (rc == ERROR_INSUFFICIENT_BUFFER);

    ಯದಿ (rc == ERROR_SUCCESS) {
        ಪ್ರತಿ (i = 0; i < path_ಎಣಿಕೆ_2; i++) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME sourceName;
            DISPLAYCONFIG_TARGET_DEVICE_NAME targetName;

            SDL_zero(sourceName);
            sourceName.header.adapterId = paths[i].targetInfo.adapterId;
            sourceName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            sourceName.header.size = ಪರಿಮಾಣ(sourceName);
            sourceName.header.id = paths[i].sourceInfo.id;
            rc = videodata->DisplayConfigGetDeviceInfo(&sourceName.header);
            ಯದಿ (rc != ERROR_SUCCESS) {
                ಭಙ್ಗ;
            } ಅನ್ಯಥಾ ಯದಿ (SDL_wcscmp(deviceName, sourceName.viewGdiDeviceName) != 0) {
                ಅನುವರ್ತ;
            }

            SDL_zero(targetName);
            targetName.header.adapterId = paths[i].targetInfo.adapterId;
            targetName.header.id = paths[i].targetInfo.id;
            targetName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
            targetName.header.size = ಪರಿಮಾಣ(targetName);
            rc = videodata->DisplayConfigGetDeviceInfo(&targetName.header);
            ಯದಿ (rc == ERROR_SUCCESS) {
                result = WIN_StringToUTF8W(targetName.monitorFriendlyDeviceName);
                /* if we got an empty string, treat it as failure so we'll fallback
                   to getting the generic name. */
                ಯದಿ (result && (*result == '\0')) {
                    SDL_free(result);
                    result = ರಿಕ್ತ;
                }
            }
            ಭಙ್ಗ;
        }
    }

    SDL_free(paths);
    SDL_free(modes);
    ಪ್ರತ್ಯಾಗಮ result;

WIN_GetDisplayNameVista_failed:
    SDL_free(result);
    SDL_free(paths);
    SDL_free(modes);
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

#ifdef HAVE_DXGI1_6_H
ಸ್ಥಿರ bool WIN_GetMonitorDESC1(HMONITOR hMonitor, DXGI_OUTPUT_DESC1 *desc)
{
    ಪ್ರಕಾರನಿರ್ದೇಶ HRESULT (WINAPI *pfnCreateDXGIFactory1)(REFIID riid, ಶೂನ್ಯ **ppFactory);
    pfnCreateDXGIFactory1 pCreateDXGIFactory1 = ರಿಕ್ತ;
    SDL_SharedObject *hDXGIMod = ರಿಕ್ತ;
    bool found = false;

    hDXGIMod = SDL_LoadObject("dxgi.dll");
    ಯದಿ (hDXGIMod) {
        pCreateDXGIFactory1 = (pfnCreateDXGIFactory1)SDL_LoadFunction(hDXGIMod, "CreateDXGIFactory1");
    }
    ಯದಿ (pCreateDXGIFactory1) {
        ಸ್ಥಿರ ಧ್ರುವ GUID SDL_IID_IDXGIFactory1 = { 0x770aae78, 0xf26f, 0x4dba, { 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 } };
        ಸ್ಥಿರ ಧ್ರುವ GUID SDL_IID_IDXGIOutput6 = { 0x068346e8, 0xaaec, 0x4b84, { 0xad, 0xd7, 0x13, 0x7f, 0x51, 0x3f, 0x77, 0xa1 } };
        IDXGIFactory1 *dxgiFactory;

        ಯದಿ (SUCCEEDED(pCreateDXGIFactory1(&SDL_IID_IDXGIFactory1, (ಶೂನ್ಯ **)&dxgiFactory))) {
            IDXGIAdapter1 *dxgiAdapter;
            UINT adapter = 0;
            ಯಾವತ್ (!found && SUCCEEDED(IDXGIFactory1_EnumAdapters1(dxgiFactory, adapter, &dxgiAdapter))) {
                IDXGIOutput *dxgiOutput;
                UINT output = 0;
                ಯಾವತ್ (!found && SUCCEEDED(IDXGIAdapter1_EnumOutputs(dxgiAdapter, output, &dxgiOutput))) {
                    IDXGIOutput6 *dxgiOutput6;
                    ಯದಿ (SUCCEEDED(IDXGIOutput_QueryInterface(dxgiOutput, &SDL_IID_IDXGIOutput6, (ಶೂನ್ಯ **)&dxgiOutput6))) {
                        ಯದಿ (SUCCEEDED(IDXGIOutput6_GetDesc1(dxgiOutput6, desc))) {
                            ಯದಿ (desc->Monitor == hMonitor) {
                                found = true;
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
    ಯದಿ (hDXGIMod) {
        SDL_UnloadObject(hDXGIMod);
    }
    ಪ್ರತ್ಯಾಗಮ found;
}

ಸ್ಥಿರ bool WIN_GetMonitorPathInfo(SDL_VideoData *videodata, HMONITOR hMonitor, DISPLAYCONFIG_PATH_INFO *path_info)
{
    LONG result;
    MONITORINFOEXW view_info;
    UINT32 i;
    UINT32 ಅಂಕೆ_path_array_elements = 0;
    UINT32 ಅಂಕೆ_mode_info_array_elements = 0;
    DISPLAYCONFIG_PATH_INFO *path_infos = ರಿಕ್ತ, *new_path_infos;
    DISPLAYCONFIG_MODE_INFO *mode_infos = ರಿಕ್ತ, *new_mode_infos;
    bool found = false;

    ಯದಿ (!videodata->GetDisplayConfigBufferSizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    SDL_zero(view_info);
    view_info.cbSize = ಪರಿಮಾಣ(view_info);
    ಯದಿ (!GetMonitorInfoW(hMonitor, (MONITORINFO *)&view_info)) {
        ಗಚ್ಛ done;
    }

    ಕುರು {
        ಯದಿ (videodata->GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &ಅಂಕೆ_path_array_elements, &ಅಂಕೆ_mode_info_array_elements) != ERROR_SUCCESS) {
            SDL_free(path_infos);
            SDL_free(mode_infos);
            ಪ್ರತ್ಯಾಗಮ false;
        }

        new_path_infos = (DISPLAYCONFIG_PATH_INFO *)SDL_realloc(path_infos, ಅಂಕೆ_path_array_elements * ಪರಿಮಾಣ(*path_infos));
        ಯದಿ (!new_path_infos) {
            ಗಚ್ಛ done;
        }
        path_infos = new_path_infos;

        new_mode_infos = (DISPLAYCONFIG_MODE_INFO *)SDL_realloc(mode_infos, ಅಂಕೆ_mode_info_array_elements * ಪರಿಮಾಣ(*mode_infos));
        ಯದಿ (!new_mode_infos) {
            ಗಚ್ಛ done;
        }
        mode_infos = new_mode_infos;

        result = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &ಅಂಕೆ_path_array_elements, path_infos, &ಅಂಕೆ_mode_info_array_elements, mode_infos, ರಿಕ್ತ);

    } ಯಾವತ್ (result == ERROR_INSUFFICIENT_BUFFER);

    ಯದಿ (result == ERROR_SUCCESS) {
        ಪ್ರತಿ (i = 0; i < ಅಂಕೆ_path_array_elements; ++i) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME device_name;

            SDL_zero(device_name);
            device_name.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            device_name.header.size = ಪರಿಮಾಣ(device_name);
            device_name.header.adapterId = path_infos[i].sourceInfo.adapterId;
            device_name.header.id = path_infos[i].sourceInfo.id;
            ಯದಿ (videodata->DisplayConfigGetDeviceInfo(&device_name.header) == ERROR_SUCCESS) {
                ಯದಿ (SDL_wcscmp(view_info.szDevice, device_name.viewGdiDeviceName) == 0) {
                    SDL_copyp(path_info, &path_infos[i]);
                    found = true;
                    ಭಙ್ಗ;
                }
            }
        }
    }

done:
    SDL_free(path_infos);
    SDL_free(mode_infos);

    ಪ್ರತ್ಯಾಗಮ found;
}

ಸ್ಥಿರ ಭಿನ್ನ WIN_GetSDRWhitePoint(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    DISPLAYCONFIG_PATH_INFO path_info;
    SDL_VideoData *videodata = _this->internal;
    ಭಿನ್ನ SDR_white_level = 1.0f;

    ಯದಿ (WIN_GetMonitorPathInfo(videodata, hMonitor, &path_info)) {
        /* workarounds for https://github.com/libsdl-org/SDL/issues/11193 */
        ಸಂರಚನಾ SDL_DISPLAYCONFIG_SDR_WHITE_LEVEL {
          DISPLAYCONFIG_DEVICE_INFO_HEADER header;
          ULONG SDRWhiteLevel;
        } white_level;
        #define DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL 11

        SDL_zero(white_level);
        white_level.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
        white_level.header.size = ಪರಿಮಾಣ(white_level);
        white_level.header.adapterId = path_info.targetInfo.adapterId;
        white_level.header.id = path_info.targetInfo.id;
        // WIN_GetMonitorPathInfo() succeeded: DisplayConfigGetDeviceInfo is not NULL
        ಯದಿ (videodata->DisplayConfigGetDeviceInfo(&white_level.header) == ERROR_SUCCESS &&
            white_level.SDRWhiteLevel > 0) {
            SDR_white_level = (white_level.SDRWhiteLevel / 1000.0f);
        }
    }
    ಪ್ರತ್ಯಾಗಮ SDR_white_level;
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_GetHDRProperties(SDL_VideoDevice *_this, HMONITOR hMonitor, SDL_HDROutputProperties *HDR)
{
    DXGI_OUTPUT_DESC1 desc;

    SDL_zerop(HDR);

    ಯದಿ (WIN_GetMonitorDESC1(hMonitor, &desc)) {
        ಯದಿ (desc.ColorSpace == DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020) {
            HDR->SDR_white_level = WIN_GetSDRWhitePoint(_this, hMonitor);
            HDR->HDR_headroom = (desc.MaxLuminance / SCRGB_NITS) / HDR->SDR_white_level;
        }
    }
}
#endif // HAVE_DXGI1_6_H

ಸ್ಥಿರ ಶೂನ್ಯ WIN_AddDisplay(SDL_VideoDevice *_this, HMONITOR hMonitor, ಧ್ರುವ MONITORINFOEXW *info, ಪೂರ್ಣಾಙ್ಕ *display_index)
{
    ಪೂರ್ಣಾಙ್ಕ i, index = *display_index;
    SDL_VideoDisplay display;
    SDL_DisplayData *displaydata;
    ಶೂನ್ಯ *dxgi_output = ರಿಕ್ತ;
    SDL_DisplayMode mode;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    ಭಿನ್ನ content_scale = WIN_GetContentScale(_this, hMonitor);

#ifdef DEBUG_MODES
    SDL_Log("Display: %s", WIN_StringToUTF8W(info->szDevice));
#endif

    dxgi_output = WIN_GetDXGIOutput(_this, info->szDevice);
    bool found = WIN_GetDisplayMode(_this, dxgi_output, hMonitor, info->szDevice, ENUM_CURRENT_SETTINGS, &mode, &natural_orientation, &current_orientation);
    WIN_ReleaseDXGIOutput(dxgi_output);
    ಯದಿ (!found) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    // Prevent adding duplicate displays. Do this after we know the display is
    // ready to be added to allow any displays that we can't fully query to be
    // removed
    ಪ್ರತಿ (i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
        SDL_DisplayData *internal = _this->displays[i]->internal;
        ಯದಿ (SDL_wcscmp(internal->DeviceName, info->szDevice) == 0) {
            bool moved = (index != i);
            bool changed_bounds = false;

            ಯದಿ (internal->state != DisplayRemoved) {
                // We've already enumerated this display, don't move it
                ಗಚ್ಛ cleanup;
            }

            ಯದಿ (index >= _this->ಅಂಕೆ_displays) {
                // This should never happen due to the check above, but just in case...
                ಗಚ್ಛ cleanup;
            }

            ಯದಿ (moved) {
                SDL_VideoDisplay *tmp;

                tmp = _this->displays[index];
                _this->displays[index] = _this->displays[i];
                _this->displays[i] = tmp;
                i = index;
            }

            internal->MonitorHandle = hMonitor;
            internal->state = DisplayUnchanged;

            SDL_PropertiesID props = SDL_GetDisplayProperties(_this->displays[i]->id);
            SDL_SetPointerProperty(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_POINTER, hMonitor);

            ಯದಿ (!_this->setting_display_mode) {
                SDL_VideoDisplay *existing_display = _this->displays[i];
                SDL_Rect bounds;

                SDL_ResetFullscreenDisplayModes(existing_display);
                SDL_SetDesktopDisplayMode(existing_display, &mode);
                // The mode is owned by the video subsystem
                mode.internal = ರಿಕ್ತ;
                ಯದಿ (WIN_GetDisplayBounds(_this, existing_display, &bounds) &&
                    SDL_memcmp(&internal->bounds, &bounds, ಪರಿಮಾಣ(bounds)) != 0) {
                    changed_bounds = true;
                    SDL_copyp(&internal->bounds, &bounds);
                }
                ಯದಿ (moved || changed_bounds) {
                    SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_MOVED, 0, 0);
                }
                SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_ORIENTATION, current_orientation, 0);
                SDL_SetDisplayContentScale(existing_display, content_scale);
#ifdef HAVE_DXGI1_6_H
                SDL_HDROutputProperties HDR;
                WIN_GetHDRProperties(_this, hMonitor, &HDR);
                SDL_SetDisplayHDRProperties(existing_display, &HDR);
#endif
            }
            ಗಚ್ಛ done;
        }
    }

    displaydata = (SDL_DisplayData *)SDL_calloc(1, ಪರಿಮಾಣ(*displaydata));
    ಯದಿ (!displaydata) {
        ಗಚ್ಛ cleanup;
    }
    SDL_memcpy(displaydata->DeviceName, info->szDevice, ಪರಿಮಾಣ(displaydata->DeviceName));
    displaydata->MonitorHandle = hMonitor;
    displaydata->state = DisplayAdded;

    SDL_zero(display);
    display.name = WIN_GetDisplayNameVista(_this->internal, info->szDevice);
    ಯದಿ (!display.name) {
        DISPLAY_DEVICEW device;
        SDL_zero(device);
        device.cb = ಪರಿಮಾಣ(device);
        ಯದಿ (EnumDisplayDevicesW(info->szDevice, 0, &device, 0)) {
            display.name = WIN_StringToUTF8W(device.DeviceString);
        }
    }

    display.desktop_mode = mode;
    display.natural_orientation = natural_orientation;
    display.current_orientation = current_orientation;
    display.content_scale = content_scale;
    display.device = _this;
    display.internal = displaydata;
    WIN_GetDisplayBounds(_this, &display, &displaydata->bounds);
#ifdef HAVE_DXGI1_6_H
    WIN_GetHDRProperties(_this, hMonitor, &display.HDR);
#endif
    SDL_DisplayID displayID = SDL_AddVideoDisplay(&display, false);
    ಯದಿ (displayID) {
        // The mode is owned by the video subsystem
        mode.internal = ರಿಕ್ತ;

        SDL_PropertiesID props = SDL_GetDisplayProperties(displayID);
        SDL_SetPointerProperty(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_POINTER, hMonitor);
    } ಅನ್ಯಥಾ {
        SDL_free(displaydata);
    }
    SDL_free(display.name);

done:
    *display_index += 1;

cleanup:
    SDL_free(mode.internal);
}

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ _WIN_AddDisplaysData
{
    SDL_VideoDevice *video_device;
    ಪೂರ್ಣಾಙ್ಕ display_index;
    bool want_primary;
} WIN_AddDisplaysData;

ಸ್ಥಿರ BOOL CALLBACK WIN_AddDisplaysCallback(HMONITOR hMonitor,
                                             HDC hdcMonitor,
                                             LPRECT lprcMonitor,
                                             LPARAM dwData)
{
    WIN_AddDisplaysData *data = (WIN_AddDisplaysData *)dwData;
    MONITORINFOEXW info;

    SDL_zero(info);
    info.cbSize = ಪರಿಮಾಣ(info);

    ಯದಿ (GetMonitorInfoW(hMonitor, (LPMONITORINFO)&info) != 0) {
        ಧ್ರುವ bool is_primary = ((info.dwFlags & MONITORINFOF_PRIMARY) == MONITORINFOF_PRIMARY);

        ಯದಿ (is_primary == data->want_primary) {
            WIN_AddDisplay(data->video_device, hMonitor, &info, &data->display_index);
        }
    }

    // continue enumeration
    ಪ್ರತ್ಯಾಗಮ TRUE;
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_AddDisplays(SDL_VideoDevice *_this)
{
    WIN_AddDisplaysData callback_data;
    callback_data.video_device = _this;
    callback_data.display_index = 0;

    callback_data.want_primary = true;
    EnumDisplayMonitors(ರಿಕ್ತ, ರಿಕ್ತ, WIN_AddDisplaysCallback, (LPARAM)&callback_data);

    callback_data.want_primary = false;
    EnumDisplayMonitors(ರಿಕ್ತ, ರಿಕ್ತ, WIN_AddDisplaysCallback, (LPARAM)&callback_data);
}

bool WIN_InitModes(SDL_VideoDevice *_this)
{
    WIN_AddDisplays(_this);

    ಯದಿ (_this->ಅಂಕೆ_displays == 0) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("No displays available");
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ಧ್ರುವ SDL_DisplayData *data = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cbSize = ಪರಿಮಾಣ(MONITORINFO);
    rc = GetMonitorInfo(data->MonitorHandle, &minfo);

    ಯದಿ (!rc) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcMonitor.ಎಡ;
    rect->y = minfo.rcMonitor.ತುದಿ;
    rect->w = minfo.rcMonitor.ಬಲ - minfo.rcMonitor.ಎಡ;
    rect->h = minfo.rcMonitor.bottom - minfo.rcMonitor.ತುದಿ;

    ಪ್ರತ್ಯಾಗಮ true;
}

bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ಧ್ರುವ SDL_DisplayData *data = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cbSize = ಪರಿಮಾಣ(MONITORINFO);
    rc = GetMonitorInfo(data->MonitorHandle, &minfo);

    ಯದಿ (!rc) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcWork.ಎಡ;
    rect->y = minfo.rcWork.ತುದಿ;
    rect->w = minfo.rcWork.ಬಲ - minfo.rcWork.ಎಡ;
    rect->h = minfo.rcWork.bottom - minfo.rcWork.ತುದಿ;

    ಪ್ರತ್ಯಾಗಮ true;
}

bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_DisplayData *data = display->internal;
    ಶೂನ್ಯ *dxgi_output;
    DWORD i;
    SDL_DisplayMode mode;

    dxgi_output = WIN_GetDXGIOutput(_this, data->DeviceName);

    // Make sure we add the current mode to the list in case it's a custom mode that doesn't enumerate
    ಪ್ರತಿ (i = ENUM_CURRENT_SETTINGS; ; ++i) {
        ಯದಿ (!WIN_GetDisplayMode(_this, dxgi_output, data->MonitorHandle, data->DeviceName, i, &mode, ರಿಕ್ತ, ರಿಕ್ತ)) {
            ಭಙ್ಗ;
        }
        ಯದಿ (SDL_ISPIXELFORMAT_INDEXED(mode.format)) {
            // We don't support palettized modes now
            SDL_free(mode.internal);
            ಅನುವರ್ತ;
        }
        ಯದಿ (mode.format != SDL_PIXELFORMAT_UNKNOWN) {
            ಯದಿ (!SDL_AddFullscreenDisplayMode(display, &mode)) {
                SDL_free(mode.internal);
            }
        } ಅನ್ಯಥಾ {
            SDL_free(mode.internal);
        }
    }

    WIN_ReleaseDXGIOutput(dxgi_output);

    ಪ್ರತ್ಯಾಗಮ true;
}

#ifdef DEBUG_MODES
ಸ್ಥಿರ ಶೂನ್ಯ WIN_LogMonitor(SDL_VideoDevice *_this, HMONITOR mon)
{
    ಧ್ರುವ SDL_VideoData *vid_data = (ಧ್ರುವ SDL_VideoData *)_this->internal;
    MONITORINFOEX minfo;
    UINT xdpi = 0, ydpi = 0;
    ವರ್ಣ *name_utf8;

    ಯದಿ (vid_data->GetDpiForMonitor) {
        vid_data->GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &xdpi, &ydpi);
    }

    SDL_zero(minfo);
    minfo.cbSize = ಪರಿಮಾಣ(minfo);
    GetMonitorInfo(mon, (LPMONITORINFO)&minfo);

    name_utf8 = WIN_StringToUTF8(minfo.szDevice);

    SDL_Log("WIN_LogMonitor: monitor \"%s\": dpi: %d windows screen coordinates: %d, %d, %dx%d",
            name_utf8,
            xdpi,
            minfo.rcMonitor.ಎಡ,
            minfo.rcMonitor.ತುದಿ,
            minfo.rcMonitor.ಬಲ - minfo.rcMonitor.ಎಡ,
            minfo.rcMonitor.bottom - minfo.rcMonitor.ತುದಿ);

    SDL_free(name_utf8);
}
#endif

bool WIN_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    SDL_DisplayData *displaydata = display->internal;
    SDL_DisplayModeData *data = (SDL_DisplayModeData *)mode->internal;
    LONG status;

#ifdef DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state before mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#endif

    /* High-DPI notes:

       - ChangeDisplaySettingsEx always takes pixels.
       - e.g. if the display is set to 2880x1800 with 200% scaling in Display Settings
         - calling ChangeDisplaySettingsEx with a dmPelsWidth/Height other than 2880x1800 will
           change the monitor DPI to 96. (100% scaling)
         - calling ChangeDisplaySettingsEx with a dmPelsWidth/Height of 2880x1800 (or a NULL DEVMODE*) will
           reset the monitor DPI to 192. (200% scaling)

       NOTE: these are temporary changes in DPI, not modifications to the Control Panel setting. */
    ಯದಿ (mode->internal == display->desktop_mode.internal) {
#ifdef DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: resetting to original resolution");
#endif
        status = ChangeDisplaySettingsExW(displaydata->DeviceName, ರಿಕ್ತ, ರಿಕ್ತ, CDS_FULLSCREEN, ರಿಕ್ತ);
    } ಅನ್ಯಥಾ {
#ifdef DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: changing to %dx%d pixels", data->DeviceMode.dmPelsWidth, data->DeviceMode.dmPelsHeight);
#endif
        status = ChangeDisplaySettingsExW(displaydata->DeviceName, &data->DeviceMode, ರಿಕ್ತ, CDS_FULLSCREEN, ರಿಕ್ತ);
    }
    ಯದಿ (status != DISP_CHANGE_SUCCESSFUL) {
        ಧ್ರುವ ವರ್ಣ *reason = "Unknown reason";
        ವಿಕಲ್ಪ (status) {
        ಪಕ್ಷ DISP_CHANGE_BADFLAGS:
            reason = "DISP_CHANGE_BADFLAGS";
            ಭಙ್ಗ;
        ಪಕ್ಷ DISP_CHANGE_BADMODE:
            reason = "DISP_CHANGE_BADMODE";
            ಭಙ್ಗ;
        ಪಕ್ಷ DISP_CHANGE_BADPARAM:
            reason = "DISP_CHANGE_BADPARAM";
            ಭಙ್ಗ;
        ಪಕ್ಷ DISP_CHANGE_FAILED:
            reason = "DISP_CHANGE_FAILED";
            ಭಙ್ಗ;
        }
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("ChangeDisplaySettingsEx() failed: %s", reason);
    }

#ifdef DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state after mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#endif

    EnumDisplaySettingsW(displaydata->DeviceName, ENUM_CURRENT_SETTINGS, &data->DeviceMode);
    WIN_UpdateDisplayMode(_this, displaydata->DeviceName, ENUM_CURRENT_SETTINGS, mode);
    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ WIN_RefreshDisplays(SDL_VideoDevice *_this)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    // Mark all displays as potentially invalid to detect
    // entries that have actually been removed
    ಪ್ರತಿ (i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
        SDL_DisplayData *internal = _this->displays[i]->internal;
        internal->state = DisplayRemoved;
    }

    // Enumerate displays to add any new ones and mark still
    // connected entries as valid
    WIN_AddDisplays(_this);

    // Delete any entries still marked as invalid, iterate
    // in reverse as each delete takes effect immediately
    ಪ್ರತಿ (i = _this->ಅಂಕೆ_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DisplayData *internal = display->internal;
        ಯದಿ (internal->state == DisplayRemoved) {
            SDL_DelVideoDisplay(display->id, true);
        }
    }

    // Send events for any newly added displays
    ಪ್ರತಿ (i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DisplayData *internal = display->internal;
        ಯದಿ (internal->state == DisplayAdded) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
        }
    }
}

ಶೂನ್ಯ WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this)
{
    // This almost never happens, so just go ahead and send update events for all displays
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_CHANGED, 0, 0);
    }
}

ಶೂನ್ಯ WIN_QuitModes(SDL_VideoDevice *_this)
{
    // All fullscreen windows should have restored modes by now
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
