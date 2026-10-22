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
#அந்தர்பாவ "SDL_internal.h"

#எனில் defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#அந்தர்பாவ "SDL_windowsvideo.h"
#அந்தர்பாவ "../../events/SDL_displayevents_c.h"
#அந்தர்பாவ "../SDL_pixels_c.h"

#ifdef HAVE_DXGI1_6_H
#define COBJMACROS
#அந்தர்பாவ <dxgi1_6.h>
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

நிலையான வெறுமை WIN_UpdateDisplayMode(SDL_VideoDevice *_this, LPCWSTR deviceName, DWORD index, SDL_DisplayMode *mode)
{
    SDL_DisplayModeData *data = (SDL_DisplayModeData *)mode->internal;
    HDC hdc;

    data->DeviceMode.dmFields = (DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS);

    // NOLINTNEXTLINE(bugprone-assignment-in-if-condition): No simple way to extract the assignment
    எனில் (index == ENUM_CURRENT_SETTINGS && (hdc = CreateDCW(deviceName, வெற்று, வெற்று, வெற்று)) != வெற்று) {
        எழுத்து bmi_data[அளவு(BITMAPINFOHEADER) + 256 * அளவு(RGBQUAD)];
        LPBITMAPINFO bmi;
        HBITMAP hbm;

        SDL_zeroa(bmi_data);
        bmi = (LPBITMAPINFO)bmi_data;
        bmi->bmiHeader.biSize = அளவு(BITMAPINFOHEADER);

        hbm = CreateCompatibleBitmap(hdc, 1, 1);
        GetDIBits(hdc, hbm, 0, 1, வெற்று, bmi, DIB_RGB_COLORS);
        GetDIBits(hdc, hbm, 0, 1, வெற்று, bmi, DIB_RGB_COLORS);
        DeleteObject(hbm);
        DeleteDC(hdc);
        எனில் (bmi->bmiHeader.biCompression == BI_BITFIELDS) {
            தேர்வு (*(Uint32 *)bmi->bmiColors) {
            நிலை 0x00FF0000:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                நிறுத்து;
            நிலை 0x000000FF:
                mode->format = SDL_PIXELFORMAT_XBGR8888;
                நிறுத்து;
            நிலை 0xF800:
                mode->format = SDL_PIXELFORMAT_RGB565;
                நிறுத்து;
            நிலை 0x7C00:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                நிறுத்து;
            }
        } இல்லையெனில் எனில் (bmi->bmiHeader.biCompression == BI_RGB) {
            எனில் (bmi->bmiHeader.bi_Bit_மொத்தம் == 24) {
                mode->format = SDL_PIXELFORMAT_RGB24;
            } இல்லையெனில் எனில் (bmi->bmiHeader.bi_Bit_மொத்தம் == 8) {
                mode->format = SDL_PIXELFORMAT_INDEX8;
            } இல்லையெனில் எனில் (bmi->bmiHeader.bi_Bit_மொத்தம் == 4) {
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
            }
        }
    } இல்லையெனில் எனில் (mode->format == SDL_PIXELFORMAT_UNKNOWN) {
        // FIXME: Can we tell what this will be?
        எனில் ((data->DeviceMode.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL) {
            தேர்வு (data->DeviceMode.dmBitsPerPel) {
            நிலை 32:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                நிறுத்து;
            நிலை 24:
                mode->format = SDL_PIXELFORMAT_RGB24;
                நிறுத்து;
            நிலை 16:
                mode->format = SDL_PIXELFORMAT_RGB565;
                நிறுத்து;
            நிலை 15:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                நிறுத்து;
            நிலை 8:
                mode->format = SDL_PIXELFORMAT_INDEX8;
                நிறுத்து;
            நிலை 4:
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
                நிறுத்து;
            }
        }
    }
}

நிலையான வெறுமை *WIN_GetDXGIOutput(SDL_VideoDevice *_this, மாறிலி WCHAR *DeviceName)
{
    வெறுமை *result = வெற்று;

#ifdef HAVE_DXGI_H
    மாறிலி SDL_VideoData *videodata = (மாறிலி SDL_VideoData *)_this->internal;
    முழு nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    எனில் (!videodata->pDXGIFactory) {
        திரும்பு வெற்று;
    }

    nAdapter = 0;
    போது (!result && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        போது (!result && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            எனில் (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                எனில் (SDL_wcscmp(outputDesc.DeviceName, DeviceName) == 0) {
                    result = pDXGIOutput;
                }
            }
            எனில் (pDXGIOutput != result) {
                IDXGIOutput_Release(pDXGIOutput);
            }
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }
#endif
    திரும்பு result;
}

நிலையான வெறுமை WIN_ReleaseDXGIOutput(வெறுமை *dxgi_output)
{
#ifdef HAVE_DXGI_H
    IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;

    எனில் (pDXGIOutput) {
        IDXGIOutput_Release(pDXGIOutput);
    }
#endif
}

நிலையான SDL_DisplayOrientation WIN_GetNaturalOrientation(DEVMODEW *mode)
{
    முழு width = mode->dmPelsWidth;
    முழு height = mode->dmPelsHeight;

    // Use unrotated width/height to guess orientation
    எனில் (mode->dmDisplayOrientation == DMDO_90 || mode->dmDisplayOrientation == DMDO_270) {
        முழு temp = width;
        width = height;
        height = temp;
    }

    எனில் (width >= height) {
        திரும்பு SDL_ORIENTATION_LANDSCAPE;
    } இல்லையெனில் {
        திரும்பு SDL_ORIENTATION_PORTRAIT;
    }
}

நிலையான SDL_DisplayOrientation WIN_GetDisplayOrientation(DEVMODEW *mode)
{
    எனில் (WIN_GetNaturalOrientation(mode) == SDL_ORIENTATION_LANDSCAPE) {
        தேர்வு (mode->dmDisplayOrientation) {
        நிலை DMDO_DEFAULT:
            திரும்பு SDL_ORIENTATION_LANDSCAPE;
        நிலை DMDO_90:
            திரும்பு SDL_ORIENTATION_PORTRAIT;
        நிலை DMDO_180:
            திரும்பு SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        நிலை DMDO_270:
            திரும்பு SDL_ORIENTATION_PORTRAIT_FLIPPED;
        இயல்பு:
            திரும்பு SDL_ORIENTATION_UNKNOWN;
        }
    } இல்லையெனில் {
        தேர்வு (mode->dmDisplayOrientation) {
        நிலை DMDO_DEFAULT:
            திரும்பு SDL_ORIENTATION_PORTRAIT;
        நிலை DMDO_90:
            திரும்பு SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        நிலை DMDO_180:
            திரும்பு SDL_ORIENTATION_PORTRAIT_FLIPPED;
        நிலை DMDO_270:
            திரும்பு SDL_ORIENTATION_LANDSCAPE;
        இயல்பு:
            திரும்பு SDL_ORIENTATION_UNKNOWN;
        }
    }
}

நிலையான வெறுமை WIN_GetRefreshRate(வெறுமை *dxgi_output, DEVMODEW *mode, முழு *numerator, முழு *denominator)
{
    // We're not currently using DXGI to query display modes, so fake NTSC timings
    தேர்வு (mode->dmDisplayFrequency) {
    நிலை 119:
    நிலை 59:
    நிலை 29:
        *numerator = (mode->dmDisplayFrequency + 1) * 1000;
        *denominator = 1001;
        நிறுத்து;
    இயல்பு:
        *numerator = mode->dmDisplayFrequency;
        *denominator = 1;
        நிறுத்து;
    }

#ifdef HAVE_DXGI_H
    எனில் (dxgi_output) {
        IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;
        DXGI_MODE_DESC modeToMatch;
        DXGI_MODE_DESC closestMatch;

        SDL_zero(modeToMatch);
        modeToMatch.Width = mode->dmPelsWidth;
        modeToMatch.Height = mode->dmPelsHeight;
        modeToMatch.RefreshRate.Numerator = *numerator;
        modeToMatch.RefreshRate.Denominator = *denominator;
        modeToMatch.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        எனில் (SUCCEEDED(IDXGIOutput_FindClosestMatchingMode(pDXGIOutput, &modeToMatch, &closestMatch, வெற்று))) {
            *numerator = closestMatch.RefreshRate.Numerator;
            *denominator = closestMatch.RefreshRate.Denominator;
        }
    }
#endif // HAVE_DXGI_H
}

நிலையான தசம WIN_GetContentScale(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    முழு dpi = 0;

    மாறிலி SDL_VideoData *videodata = (மாறிலி SDL_VideoData *)_this->internal;
    எனில் (videodata->GetDpiForMonitor) {
        UINT hdpi_uint, vdpi_uint;
        எனில் (videodata->GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
            dpi = (முழு)hdpi_uint;
        }
    }
    எனில் (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(வெற்று);
        எனில் (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(வெற்று, hdc);
        }
    }
    எனில் (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    திரும்பு dpi / (தசம)USER_DEFAULT_SCREEN_DPI;
}

நிலையான bool WIN_GetDisplayMode(SDL_VideoDevice *_this, வெறுமை *dxgi_output, HMONITOR hMonitor, LPCWSTR deviceName, DWORD index, SDL_DisplayMode *mode, SDL_DisplayOrientation *natural_orientation, SDL_DisplayOrientation *current_orientation)
{
    SDL_DisplayModeData *data;
    DEVMODEW devmode;

    devmode.dmSize = அளவு(devmode);
    devmode.dmDriverExtra = 0;
    எனில் (!EnumDisplaySettingsW(deviceName, index, &devmode)) {
        திரும்பு false;
    }

    data = (SDL_DisplayModeData *)SDL_malloc(அளவு(*data));
    எனில் (!data) {
        திரும்பு false;
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

    எனில் (natural_orientation) {
        *natural_orientation = WIN_GetNaturalOrientation(&devmode);
    }
    எனில் (current_orientation) {
        *current_orientation = WIN_GetDisplayOrientation(&devmode);
    }

    திரும்பு true;
}

நிலையான எழுத்து *WIN_GetDisplayNameVista(SDL_VideoData *videodata, மாறிலி WCHAR *deviceName)
{
    DISPLAYCONFIG_PATH_INFO *paths = வெற்று;
    DISPLAYCONFIG_MODE_INFO *modes = வெற்று;
    எழுத்து *result = வெற்று;
    UINT32 path_மொத்தம்_2 = 0;
    UINT32 mode_மொத்தம்_2 = 0;
    UINT32 i;
    LONG rc;

    எனில் (!videodata->GetDisplayConfigBufferSizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        திரும்பு வெற்று;
    }

    செய் {
        rc = videodata->GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &path_மொத்தம்_2, &mode_மொத்தம்_2);
        எனில் (rc != ERROR_SUCCESS) {
            செல் WIN_GetDisplayNameVista_failed;
        }

        SDL_free(paths);
        SDL_free(modes);

        paths = (DISPLAYCONFIG_PATH_INFO *)SDL_malloc(அளவு(DISPLAYCONFIG_PATH_INFO) * path_மொத்தம்_2);
        modes = (DISPLAYCONFIG_MODE_INFO *)SDL_malloc(அளவு(DISPLAYCONFIG_MODE_INFO) * mode_மொத்தம்_2);
        எனில் ((!paths) || (!modes)) {
            செல் WIN_GetDisplayNameVista_failed;
        }

        rc = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &path_மொத்தம்_2, paths, &mode_மொத்தம்_2, modes, 0);
    } போது (rc == ERROR_INSUFFICIENT_BUFFER);

    எனில் (rc == ERROR_SUCCESS) {
        க்கு (i = 0; i < path_மொத்தம்_2; i++) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME sourceName;
            DISPLAYCONFIG_TARGET_DEVICE_NAME targetName;

            SDL_zero(sourceName);
            sourceName.header.adapterId = paths[i].targetInfo.adapterId;
            sourceName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            sourceName.header.size = அளவு(sourceName);
            sourceName.header.id = paths[i].sourceInfo.id;
            rc = videodata->DisplayConfigGetDeviceInfo(&sourceName.header);
            எனில் (rc != ERROR_SUCCESS) {
                நிறுத்து;
            } இல்லையெனில் எனில் (SDL_wcscmp(deviceName, sourceName.viewGdiDeviceName) != 0) {
                தொடர்;
            }

            SDL_zero(targetName);
            targetName.header.adapterId = paths[i].targetInfo.adapterId;
            targetName.header.id = paths[i].targetInfo.id;
            targetName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
            targetName.header.size = அளவு(targetName);
            rc = videodata->DisplayConfigGetDeviceInfo(&targetName.header);
            எனில் (rc == ERROR_SUCCESS) {
                result = WIN_StringToUTF8W(targetName.monitorFriendlyDeviceName);
                /* if we got an empty string, treat it as failure so we'll fallback
                   to getting the generic name. */
                எனில் (result && (*result == '\0')) {
                    SDL_free(result);
                    result = வெற்று;
                }
            }
            நிறுத்து;
        }
    }

    SDL_free(paths);
    SDL_free(modes);
    திரும்பு result;

WIN_GetDisplayNameVista_failed:
    SDL_free(result);
    SDL_free(paths);
    SDL_free(modes);
    திரும்பு வெற்று;
}

#ifdef HAVE_DXGI1_6_H
நிலையான bool WIN_GetMonitorDESC1(HMONITOR hMonitor, DXGI_OUTPUT_DESC1 *desc)
{
    வகைவரை HRESULT (WINAPI *pfnCreateDXGIFactory1)(REFIID riid, வெறுமை **ppFactory);
    pfnCreateDXGIFactory1 pCreateDXGIFactory1 = வெற்று;
    SDL_SharedObject *hDXGIMod = வெற்று;
    bool found = false;

    hDXGIMod = SDL_LoadObject("dxgi.dll");
    எனில் (hDXGIMod) {
        pCreateDXGIFactory1 = (pfnCreateDXGIFactory1)SDL_LoadFunction(hDXGIMod, "CreateDXGIFactory1");
    }
    எனில் (pCreateDXGIFactory1) {
        நிலையான மாறிலி GUID SDL_IID_IDXGIFactory1 = { 0x770aae78, 0xf26f, 0x4dba, { 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 } };
        நிலையான மாறிலி GUID SDL_IID_IDXGIOutput6 = { 0x068346e8, 0xaaec, 0x4b84, { 0xad, 0xd7, 0x13, 0x7f, 0x51, 0x3f, 0x77, 0xa1 } };
        IDXGIFactory1 *dxgiFactory;

        எனில் (SUCCEEDED(pCreateDXGIFactory1(&SDL_IID_IDXGIFactory1, (வெறுமை **)&dxgiFactory))) {
            IDXGIAdapter1 *dxgiAdapter;
            UINT adapter = 0;
            போது (!found && SUCCEEDED(IDXGIFactory1_EnumAdapters1(dxgiFactory, adapter, &dxgiAdapter))) {
                IDXGIOutput *dxgiOutput;
                UINT output = 0;
                போது (!found && SUCCEEDED(IDXGIAdapter1_EnumOutputs(dxgiAdapter, output, &dxgiOutput))) {
                    IDXGIOutput6 *dxgiOutput6;
                    எனில் (SUCCEEDED(IDXGIOutput_QueryInterface(dxgiOutput, &SDL_IID_IDXGIOutput6, (வெறுமை **)&dxgiOutput6))) {
                        எனில் (SUCCEEDED(IDXGIOutput6_GetDesc1(dxgiOutput6, desc))) {
                            எனில் (desc->Monitor == hMonitor) {
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
    எனில் (hDXGIMod) {
        SDL_UnloadObject(hDXGIMod);
    }
    திரும்பு found;
}

நிலையான bool WIN_GetMonitorPathInfo(SDL_VideoData *videodata, HMONITOR hMonitor, DISPLAYCONFIG_PATH_INFO *path_info)
{
    LONG result;
    MONITORINFOEXW view_info;
    UINT32 i;
    UINT32 இலக்கம்_path_array_elements = 0;
    UINT32 இலக்கம்_mode_info_array_elements = 0;
    DISPLAYCONFIG_PATH_INFO *path_infos = வெற்று, *new_path_infos;
    DISPLAYCONFIG_MODE_INFO *mode_infos = வெற்று, *new_mode_infos;
    bool found = false;

    எனில் (!videodata->GetDisplayConfigBufferSizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        திரும்பு false;
    }

    SDL_zero(view_info);
    view_info.cbSize = அளவு(view_info);
    எனில் (!GetMonitorInfoW(hMonitor, (MONITORINFO *)&view_info)) {
        செல் done;
    }

    செய் {
        எனில் (videodata->GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &இலக்கம்_path_array_elements, &இலக்கம்_mode_info_array_elements) != ERROR_SUCCESS) {
            SDL_free(path_infos);
            SDL_free(mode_infos);
            திரும்பு false;
        }

        new_path_infos = (DISPLAYCONFIG_PATH_INFO *)SDL_realloc(path_infos, இலக்கம்_path_array_elements * அளவு(*path_infos));
        எனில் (!new_path_infos) {
            செல் done;
        }
        path_infos = new_path_infos;

        new_mode_infos = (DISPLAYCONFIG_MODE_INFO *)SDL_realloc(mode_infos, இலக்கம்_mode_info_array_elements * அளவு(*mode_infos));
        எனில் (!new_mode_infos) {
            செல் done;
        }
        mode_infos = new_mode_infos;

        result = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &இலக்கம்_path_array_elements, path_infos, &இலக்கம்_mode_info_array_elements, mode_infos, வெற்று);

    } போது (result == ERROR_INSUFFICIENT_BUFFER);

    எனில் (result == ERROR_SUCCESS) {
        க்கு (i = 0; i < இலக்கம்_path_array_elements; ++i) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME device_name;

            SDL_zero(device_name);
            device_name.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            device_name.header.size = அளவு(device_name);
            device_name.header.adapterId = path_infos[i].sourceInfo.adapterId;
            device_name.header.id = path_infos[i].sourceInfo.id;
            எனில் (videodata->DisplayConfigGetDeviceInfo(&device_name.header) == ERROR_SUCCESS) {
                எனில் (SDL_wcscmp(view_info.szDevice, device_name.viewGdiDeviceName) == 0) {
                    SDL_copyp(path_info, &path_infos[i]);
                    found = true;
                    நிறுத்து;
                }
            }
        }
    }

done:
    SDL_free(path_infos);
    SDL_free(mode_infos);

    திரும்பு found;
}

நிலையான தசம WIN_GetSDRWhitePoint(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    DISPLAYCONFIG_PATH_INFO path_info;
    SDL_VideoData *videodata = _this->internal;
    தசம SDR_white_level = 1.0f;

    எனில் (WIN_GetMonitorPathInfo(videodata, hMonitor, &path_info)) {
        /* workarounds for https://github.com/libsdl-org/SDL/issues/11193 */
        கட்டமைப்பு SDL_DISPLAYCONFIG_SDR_WHITE_LEVEL {
          DISPLAYCONFIG_DEVICE_INFO_HEADER header;
          ULONG SDRWhiteLevel;
        } white_level;
        #define DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL 11

        SDL_zero(white_level);
        white_level.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
        white_level.header.size = அளவு(white_level);
        white_level.header.adapterId = path_info.targetInfo.adapterId;
        white_level.header.id = path_info.targetInfo.id;
        // WIN_GetMonitorPathInfo() succeeded: DisplayConfigGetDeviceInfo is not NULL
        எனில் (videodata->DisplayConfigGetDeviceInfo(&white_level.header) == ERROR_SUCCESS &&
            white_level.SDRWhiteLevel > 0) {
            SDR_white_level = (white_level.SDRWhiteLevel / 1000.0f);
        }
    }
    திரும்பு SDR_white_level;
}

நிலையான வெறுமை WIN_GetHDRProperties(SDL_VideoDevice *_this, HMONITOR hMonitor, SDL_HDROutputProperties *HDR)
{
    DXGI_OUTPUT_DESC1 desc;

    SDL_zerop(HDR);

    எனில் (WIN_GetMonitorDESC1(hMonitor, &desc)) {
        எனில் (desc.ColorSpace == DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020) {
            HDR->SDR_white_level = WIN_GetSDRWhitePoint(_this, hMonitor);
            HDR->HDR_headroom = (desc.MaxLuminance / SCRGB_NITS) / HDR->SDR_white_level;
        }
    }
}
#endif // HAVE_DXGI1_6_H

நிலையான வெறுமை WIN_AddDisplay(SDL_VideoDevice *_this, HMONITOR hMonitor, மாறிலி MONITORINFOEXW *info, முழு *display_index)
{
    முழு i, index = *display_index;
    SDL_VideoDisplay display;
    SDL_DisplayData *displaydata;
    வெறுமை *dxgi_output = வெற்று;
    SDL_DisplayMode mode;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    தசம content_scale = WIN_GetContentScale(_this, hMonitor);

#ifdef DEBUG_MODES
    SDL_Log("Display: %s", WIN_StringToUTF8W(info->szDevice));
#endif

    dxgi_output = WIN_GetDXGIOutput(_this, info->szDevice);
    bool found = WIN_GetDisplayMode(_this, dxgi_output, hMonitor, info->szDevice, ENUM_CURRENT_SETTINGS, &mode, &natural_orientation, &current_orientation);
    WIN_ReleaseDXGIOutput(dxgi_output);
    எனில் (!found) {
        திரும்பு;
    }

    // Prevent adding duplicate displays. Do this after we know the display is
    // ready to be added to allow any displays that we can't fully query to be
    // removed
    க்கு (i = 0; i < _this->இலக்கம்_displays; ++i) {
        SDL_DisplayData *internal = _this->displays[i]->internal;
        எனில் (SDL_wcscmp(internal->DeviceName, info->szDevice) == 0) {
            bool moved = (index != i);
            bool changed_bounds = false;

            எனில் (internal->state != DisplayRemoved) {
                // We've already enumerated this display, don't move it
                செல் cleanup;
            }

            எனில் (index >= _this->இலக்கம்_displays) {
                // This should never happen due to the check above, but just in case...
                செல் cleanup;
            }

            எனில் (moved) {
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

            எனில் (!_this->setting_display_mode) {
                SDL_VideoDisplay *existing_display = _this->displays[i];
                SDL_Rect bounds;

                SDL_ResetFullscreenDisplayModes(existing_display);
                SDL_SetDesktopDisplayMode(existing_display, &mode);
                // The mode is owned by the video subsystem
                mode.internal = வெற்று;
                எனில் (WIN_GetDisplayBounds(_this, existing_display, &bounds) &&
                    SDL_memcmp(&internal->bounds, &bounds, அளவு(bounds)) != 0) {
                    changed_bounds = true;
                    SDL_copyp(&internal->bounds, &bounds);
                }
                எனில் (moved || changed_bounds) {
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
            செல் done;
        }
    }

    displaydata = (SDL_DisplayData *)SDL_calloc(1, அளவு(*displaydata));
    எனில் (!displaydata) {
        செல் cleanup;
    }
    SDL_memcpy(displaydata->DeviceName, info->szDevice, அளவு(displaydata->DeviceName));
    displaydata->MonitorHandle = hMonitor;
    displaydata->state = DisplayAdded;

    SDL_zero(display);
    display.name = WIN_GetDisplayNameVista(_this->internal, info->szDevice);
    எனில் (!display.name) {
        DISPLAY_DEVICEW device;
        SDL_zero(device);
        device.cb = அளவு(device);
        எனில் (EnumDisplayDevicesW(info->szDevice, 0, &device, 0)) {
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
    எனில் (displayID) {
        // The mode is owned by the video subsystem
        mode.internal = வெற்று;

        SDL_PropertiesID props = SDL_GetDisplayProperties(displayID);
        SDL_SetPointerProperty(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_POINTER, hMonitor);
    } இல்லையெனில் {
        SDL_free(displaydata);
    }
    SDL_free(display.name);

done:
    *display_index += 1;

cleanup:
    SDL_free(mode.internal);
}

வகைவரை கட்டமைப்பு _WIN_AddDisplaysData
{
    SDL_VideoDevice *video_device;
    முழு display_index;
    bool want_primary;
} WIN_AddDisplaysData;

நிலையான BOOL CALLBACK WIN_AddDisplaysCallback(HMONITOR hMonitor,
                                             HDC hdcMonitor,
                                             LPRECT lprcMonitor,
                                             LPARAM dwData)
{
    WIN_AddDisplaysData *data = (WIN_AddDisplaysData *)dwData;
    MONITORINFOEXW info;

    SDL_zero(info);
    info.cbSize = அளவு(info);

    எனில் (GetMonitorInfoW(hMonitor, (LPMONITORINFO)&info) != 0) {
        மாறிலி bool is_primary = ((info.dwFlags & MONITORINFOF_PRIMARY) == MONITORINFOF_PRIMARY);

        எனில் (is_primary == data->want_primary) {
            WIN_AddDisplay(data->video_device, hMonitor, &info, &data->display_index);
        }
    }

    // continue enumeration
    திரும்பு TRUE;
}

நிலையான வெறுமை WIN_AddDisplays(SDL_VideoDevice *_this)
{
    WIN_AddDisplaysData callback_data;
    callback_data.video_device = _this;
    callback_data.display_index = 0;

    callback_data.want_primary = true;
    EnumDisplayMonitors(வெற்று, வெற்று, WIN_AddDisplaysCallback, (LPARAM)&callback_data);

    callback_data.want_primary = false;
    EnumDisplayMonitors(வெற்று, வெற்று, WIN_AddDisplaysCallback, (LPARAM)&callback_data);
}

bool WIN_InitModes(SDL_VideoDevice *_this)
{
    WIN_AddDisplays(_this);

    எனில் (_this->இலக்கம்_displays == 0) {
        திரும்பு SDL_SetError("No displays available");
    }
    திரும்பு true;
}

bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    மாறிலி SDL_DisplayData *data = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cbSize = அளவு(MONITORINFO);
    rc = GetMonitorInfo(data->MonitorHandle, &minfo);

    எனில் (!rc) {
        திரும்பு SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcMonitor.இடது;
    rect->y = minfo.rcMonitor.உச்சி;
    rect->w = minfo.rcMonitor.வலது - minfo.rcMonitor.இடது;
    rect->h = minfo.rcMonitor.bottom - minfo.rcMonitor.உச்சி;

    திரும்பு true;
}

bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    மாறிலி SDL_DisplayData *data = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cbSize = அளவு(MONITORINFO);
    rc = GetMonitorInfo(data->MonitorHandle, &minfo);

    எனில் (!rc) {
        திரும்பு SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcWork.இடது;
    rect->y = minfo.rcWork.உச்சி;
    rect->w = minfo.rcWork.வலது - minfo.rcWork.இடது;
    rect->h = minfo.rcWork.bottom - minfo.rcWork.உச்சி;

    திரும்பு true;
}

bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_DisplayData *data = display->internal;
    வெறுமை *dxgi_output;
    DWORD i;
    SDL_DisplayMode mode;

    dxgi_output = WIN_GetDXGIOutput(_this, data->DeviceName);

    // Make sure we add the current mode to the list in case it's a custom mode that doesn't enumerate
    க்கு (i = ENUM_CURRENT_SETTINGS; ; ++i) {
        எனில் (!WIN_GetDisplayMode(_this, dxgi_output, data->MonitorHandle, data->DeviceName, i, &mode, வெற்று, வெற்று)) {
            நிறுத்து;
        }
        எனில் (SDL_ISPIXELFORMAT_INDEXED(mode.format)) {
            // We don't support palettized modes now
            SDL_free(mode.internal);
            தொடர்;
        }
        எனில் (mode.format != SDL_PIXELFORMAT_UNKNOWN) {
            எனில் (!SDL_AddFullscreenDisplayMode(display, &mode)) {
                SDL_free(mode.internal);
            }
        } இல்லையெனில் {
            SDL_free(mode.internal);
        }
    }

    WIN_ReleaseDXGIOutput(dxgi_output);

    திரும்பு true;
}

#ifdef DEBUG_MODES
நிலையான வெறுமை WIN_LogMonitor(SDL_VideoDevice *_this, HMONITOR mon)
{
    மாறிலி SDL_VideoData *vid_data = (மாறிலி SDL_VideoData *)_this->internal;
    MONITORINFOEX minfo;
    UINT xdpi = 0, ydpi = 0;
    எழுத்து *name_utf8;

    எனில் (vid_data->GetDpiForMonitor) {
        vid_data->GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &xdpi, &ydpi);
    }

    SDL_zero(minfo);
    minfo.cbSize = அளவு(minfo);
    GetMonitorInfo(mon, (LPMONITORINFO)&minfo);

    name_utf8 = WIN_StringToUTF8(minfo.szDevice);

    SDL_Log("WIN_LogMonitor: monitor \"%s\": dpi: %d windows screen coordinates: %d, %d, %dx%d",
            name_utf8,
            xdpi,
            minfo.rcMonitor.இடது,
            minfo.rcMonitor.உச்சி,
            minfo.rcMonitor.வலது - minfo.rcMonitor.இடது,
            minfo.rcMonitor.bottom - minfo.rcMonitor.உச்சி);

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
    எனில் (mode->internal == display->desktop_mode.internal) {
#ifdef DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: resetting to original resolution");
#endif
        status = ChangeDisplaySettingsExW(displaydata->DeviceName, வெற்று, வெற்று, CDS_FULLSCREEN, வெற்று);
    } இல்லையெனில் {
#ifdef DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: changing to %dx%d pixels", data->DeviceMode.dmPelsWidth, data->DeviceMode.dmPelsHeight);
#endif
        status = ChangeDisplaySettingsExW(displaydata->DeviceName, &data->DeviceMode, வெற்று, CDS_FULLSCREEN, வெற்று);
    }
    எனில் (status != DISP_CHANGE_SUCCESSFUL) {
        மாறிலி எழுத்து *reason = "Unknown reason";
        தேர்வு (status) {
        நிலை DISP_CHANGE_BADFLAGS:
            reason = "DISP_CHANGE_BADFLAGS";
            நிறுத்து;
        நிலை DISP_CHANGE_BADMODE:
            reason = "DISP_CHANGE_BADMODE";
            நிறுத்து;
        நிலை DISP_CHANGE_BADPARAM:
            reason = "DISP_CHANGE_BADPARAM";
            நிறுத்து;
        நிலை DISP_CHANGE_FAILED:
            reason = "DISP_CHANGE_FAILED";
            நிறுத்து;
        }
        திரும்பு SDL_SetError("ChangeDisplaySettingsEx() failed: %s", reason);
    }

#ifdef DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state after mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#endif

    EnumDisplaySettingsW(displaydata->DeviceName, ENUM_CURRENT_SETTINGS, &data->DeviceMode);
    WIN_UpdateDisplayMode(_this, displaydata->DeviceName, ENUM_CURRENT_SETTINGS, mode);
    திரும்பு true;
}

வெறுமை WIN_RefreshDisplays(SDL_VideoDevice *_this)
{
    முழு i;

    // Mark all displays as potentially invalid to detect
    // entries that have actually been removed
    க்கு (i = 0; i < _this->இலக்கம்_displays; ++i) {
        SDL_DisplayData *internal = _this->displays[i]->internal;
        internal->state = DisplayRemoved;
    }

    // Enumerate displays to add any new ones and mark still
    // connected entries as valid
    WIN_AddDisplays(_this);

    // Delete any entries still marked as invalid, iterate
    // in reverse as each delete takes effect immediately
    க்கு (i = _this->இலக்கம்_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DisplayData *internal = display->internal;
        எனில் (internal->state == DisplayRemoved) {
            SDL_DelVideoDisplay(display->id, true);
        }
    }

    // Send events for any newly added displays
    க்கு (i = 0; i < _this->இலக்கம்_displays; ++i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DisplayData *internal = display->internal;
        எனில் (internal->state == DisplayAdded) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
        }
    }
}

வெறுமை WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this)
{
    // This almost never happens, so just go ahead and send update events for all displays
    க்கு (முழு i = 0; i < _this->இலக்கம்_displays; ++i) {
        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_CHANGED, 0, 0);
    }
}

வெறுமை WIN_QuitModes(SDL_VideoDevice *_this)
{
    // All fullscreen windows should have restored modes by now
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
