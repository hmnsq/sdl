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
#અન્તર્ભાવ "SDL_internal.h"

#જો defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#અન્તર્ભાવ "SDL_windowsvideo.h"
#અન્તર્ભાવ "../../events/SDL_displayevents_c.h"
#અન્તર્ભાવ "../SDL_pixels_c.h"

#ifdef HAVE_DXGI1_6_H
#define COBJMACROS
#અન્તર્ભાવ <dxgi1_6.h>
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

સ્થિર શૂન્ય WIN_UpdateDisplayMode(SDL_VideoDevice *_this, LPCWSTR deviceName, DWORD index, SDL_DisplayMode *mode)
{
    SDL_DisplayModeData *data = (SDL_DisplayModeData *)mode->internal;
    HDC hdc;

    data->DeviceMode.dmFields = (DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS);

    // NOLINTNEXTLINE(bugprone-assignment-in-if-condition): No simple way to extract the assignment
    જો (index == ENUM_CURRENT_SETTINGS && (hdc = CreateDCW(deviceName, ખાલી, ખાલી, ખાલી)) != ખાલી) {
        અક્ષર bmi_data[કદ(BITMAPINFOHEADER) + 256 * કદ(RGBQUAD)];
        LPBITMAPINFO bmi;
        HBITMAP hbm;

        SDL_zeroa(bmi_data);
        bmi = (LPBITMAPINFO)bmi_data;
        bmi->bmiHeader.biSize = કદ(BITMAPINFOHEADER);

        hbm = CreateCompatibleBitmap(hdc, 1, 1);
        GetDIBits(hdc, hbm, 0, 1, ખાલી, bmi, DIB_RGB_COLORS);
        GetDIBits(hdc, hbm, 0, 1, ખાલી, bmi, DIB_RGB_COLORS);
        DeleteObject(hbm);
        DeleteDC(hdc);
        જો (bmi->bmiHeader.biCompression == BI_BITFIELDS) {
            પસંદગી (*(Uint32 *)bmi->bmiColors) {
            સ્થિતિ 0x00FF0000:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                તોડો;
            સ્થિતિ 0x000000FF:
                mode->format = SDL_PIXELFORMAT_XBGR8888;
                તોડો;
            સ્થિતિ 0xF800:
                mode->format = SDL_PIXELFORMAT_RGB565;
                તોડો;
            સ્થિતિ 0x7C00:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                તોડો;
            }
        } નહીંતર જો (bmi->bmiHeader.biCompression == BI_RGB) {
            જો (bmi->bmiHeader.bi_Bit_ગણતરી == 24) {
                mode->format = SDL_PIXELFORMAT_RGB24;
            } નહીંતર જો (bmi->bmiHeader.bi_Bit_ગણતરી == 8) {
                mode->format = SDL_PIXELFORMAT_INDEX8;
            } નહીંતર જો (bmi->bmiHeader.bi_Bit_ગણતરી == 4) {
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
            }
        }
    } નહીંતર જો (mode->format == SDL_PIXELFORMAT_UNKNOWN) {
        // FIXME: Can we tell what this will be?
        જો ((data->DeviceMode.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL) {
            પસંદગી (data->DeviceMode.dmBitsPerPel) {
            સ્થિતિ 32:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                તોડો;
            સ્થિતિ 24:
                mode->format = SDL_PIXELFORMAT_RGB24;
                તોડો;
            સ્થિતિ 16:
                mode->format = SDL_PIXELFORMAT_RGB565;
                તોડો;
            સ્થિતિ 15:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                તોડો;
            સ્થિતિ 8:
                mode->format = SDL_PIXELFORMAT_INDEX8;
                તોડો;
            સ્થિતિ 4:
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
                તોડો;
            }
        }
    }
}

સ્થિર શૂન્ય *WIN_GetDXGIOutput(SDL_VideoDevice *_this, અચલ WCHAR *DeviceName)
{
    શૂન્ય *result = ખાલી;

#ifdef HAVE_DXGI_H
    અચલ SDL_VideoData *videodata = (અચલ SDL_VideoData *)_this->internal;
    પૂર્ણાંક nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    જો (!videodata->pDXGIFactory) {
        પાછા ખાલી;
    }

    nAdapter = 0;
    જ્યારે (!result && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        જ્યારે (!result && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            જો (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                જો (SDL_wcscmp(outputDesc.DeviceName, DeviceName) == 0) {
                    result = pDXGIOutput;
                }
            }
            જો (pDXGIOutput != result) {
                IDXGIOutput_Release(pDXGIOutput);
            }
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }
#endif
    પાછા result;
}

સ્થિર શૂન્ય WIN_ReleaseDXGIOutput(શૂન્ય *dxgi_output)
{
#ifdef HAVE_DXGI_H
    IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;

    જો (pDXGIOutput) {
        IDXGIOutput_Release(pDXGIOutput);
    }
#endif
}

સ્થિર SDL_DisplayOrientation WIN_GetNaturalOrientation(DEVMODEW *mode)
{
    પૂર્ણાંક width = mode->dmPelsWidth;
    પૂર્ણાંક height = mode->dmPelsHeight;

    // Use unrotated width/height to guess orientation
    જો (mode->dmDisplayOrientation == DMDO_90 || mode->dmDisplayOrientation == DMDO_270) {
        પૂર્ણાંક temp = width;
        width = height;
        height = temp;
    }

    જો (width >= height) {
        પાછા SDL_ORIENTATION_LANDSCAPE;
    } નહીંતર {
        પાછા SDL_ORIENTATION_PORTRAIT;
    }
}

સ્થિર SDL_DisplayOrientation WIN_GetDisplayOrientation(DEVMODEW *mode)
{
    જો (WIN_GetNaturalOrientation(mode) == SDL_ORIENTATION_LANDSCAPE) {
        પસંદગી (mode->dmDisplayOrientation) {
        સ્થિતિ DMDO_DEFAULT:
            પાછા SDL_ORIENTATION_LANDSCAPE;
        સ્થિતિ DMDO_90:
            પાછા SDL_ORIENTATION_PORTRAIT;
        સ્થિતિ DMDO_180:
            પાછા SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        સ્થિતિ DMDO_270:
            પાછા SDL_ORIENTATION_PORTRAIT_FLIPPED;
        મૂળભૂત:
            પાછા SDL_ORIENTATION_UNKNOWN;
        }
    } નહીંતર {
        પસંદગી (mode->dmDisplayOrientation) {
        સ્થિતિ DMDO_DEFAULT:
            પાછા SDL_ORIENTATION_PORTRAIT;
        સ્થિતિ DMDO_90:
            પાછા SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        સ્થિતિ DMDO_180:
            પાછા SDL_ORIENTATION_PORTRAIT_FLIPPED;
        સ્થિતિ DMDO_270:
            પાછા SDL_ORIENTATION_LANDSCAPE;
        મૂળભૂત:
            પાછા SDL_ORIENTATION_UNKNOWN;
        }
    }
}

સ્થિર શૂન્ય WIN_GetRefreshRate(શૂન્ય *dxgi_output, DEVMODEW *mode, પૂર્ણાંક *numerator, પૂર્ણાંક *denominator)
{
    // We're not currently using DXGI to query display modes, so fake NTSC timings
    પસંદગી (mode->dmDisplayFrequency) {
    સ્થિતિ 119:
    સ્થિતિ 59:
    સ્થિતિ 29:
        *numerator = (mode->dmDisplayFrequency + 1) * 1000;
        *denominator = 1001;
        તોડો;
    મૂળભૂત:
        *numerator = mode->dmDisplayFrequency;
        *denominator = 1;
        તોડો;
    }

#ifdef HAVE_DXGI_H
    જો (dxgi_output) {
        IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;
        DXGI_MODE_DESC modeToMatch;
        DXGI_MODE_DESC closestMatch;

        SDL_zero(modeToMatch);
        modeToMatch.Width = mode->dmPelsWidth;
        modeToMatch.Height = mode->dmPelsHeight;
        modeToMatch.RefreshRate.Numerator = *numerator;
        modeToMatch.RefreshRate.Denominator = *denominator;
        modeToMatch.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        જો (SUCCEEDED(IDXGIOutput_FindClosestMatchingMode(pDXGIOutput, &modeToMatch, &closestMatch, ખાલી))) {
            *numerator = closestMatch.RefreshRate.Numerator;
            *denominator = closestMatch.RefreshRate.Denominator;
        }
    }
#endif // HAVE_DXGI_H
}

સ્થિર દશાંશ WIN_GetContentScale(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    પૂર્ણાંક dpi = 0;

    અચલ SDL_VideoData *videodata = (અચલ SDL_VideoData *)_this->internal;
    જો (videodata->GetDpiForMonitor) {
        UINT hdpi_uint, vdpi_uint;
        જો (videodata->GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
            dpi = (પૂર્ણાંક)hdpi_uint;
        }
    }
    જો (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(ખાલી);
        જો (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(ખાલી, hdc);
        }
    }
    જો (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    પાછા dpi / (દશાંશ)USER_DEFAULT_SCREEN_DPI;
}

સ્થિર bool WIN_GetDisplayMode(SDL_VideoDevice *_this, શૂન્ય *dxgi_output, HMONITOR hMonitor, LPCWSTR deviceName, DWORD index, SDL_DisplayMode *mode, SDL_DisplayOrientation *natural_orientation, SDL_DisplayOrientation *current_orientation)
{
    SDL_DisplayModeData *data;
    DEVMODEW devmode;

    devmode.dmSize = કદ(devmode);
    devmode.dmDriverExtra = 0;
    જો (!EnumDisplaySettingsW(deviceName, index, &devmode)) {
        પાછા false;
    }

    data = (SDL_DisplayModeData *)SDL_malloc(કદ(*data));
    જો (!data) {
        પાછા false;
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

    જો (natural_orientation) {
        *natural_orientation = WIN_GetNaturalOrientation(&devmode);
    }
    જો (current_orientation) {
        *current_orientation = WIN_GetDisplayOrientation(&devmode);
    }

    પાછા true;
}

સ્થિર અક્ષર *WIN_GetDisplayNameVista(SDL_VideoData *videodata, અચલ WCHAR *deviceName)
{
    DISPLAYCONFIG_PATH_INFO *paths = ખાલી;
    DISPLAYCONFIG_MODE_INFO *modes = ખાલી;
    અક્ષર *result = ખાલી;
    UINT32 path_ગણતરી_2 = 0;
    UINT32 mode_ગણતરી_2 = 0;
    UINT32 i;
    LONG rc;

    જો (!videodata->GetDisplayConfigBufferSizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        પાછા ખાલી;
    }

    કરો {
        rc = videodata->GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &path_ગણતરી_2, &mode_ગણતરી_2);
        જો (rc != ERROR_SUCCESS) {
            જાઓ WIN_GetDisplayNameVista_failed;
        }

        SDL_free(paths);
        SDL_free(modes);

        paths = (DISPLAYCONFIG_PATH_INFO *)SDL_malloc(કદ(DISPLAYCONFIG_PATH_INFO) * path_ગણતરી_2);
        modes = (DISPLAYCONFIG_MODE_INFO *)SDL_malloc(કદ(DISPLAYCONFIG_MODE_INFO) * mode_ગણતરી_2);
        જો ((!paths) || (!modes)) {
            જાઓ WIN_GetDisplayNameVista_failed;
        }

        rc = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &path_ગણતરી_2, paths, &mode_ગણતરી_2, modes, 0);
    } જ્યારે (rc == ERROR_INSUFFICIENT_BUFFER);

    જો (rc == ERROR_SUCCESS) {
        માટે (i = 0; i < path_ગણતરી_2; i++) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME sourceName;
            DISPLAYCONFIG_TARGET_DEVICE_NAME targetName;

            SDL_zero(sourceName);
            sourceName.header.adapterId = paths[i].targetInfo.adapterId;
            sourceName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            sourceName.header.size = કદ(sourceName);
            sourceName.header.id = paths[i].sourceInfo.id;
            rc = videodata->DisplayConfigGetDeviceInfo(&sourceName.header);
            જો (rc != ERROR_SUCCESS) {
                તોડો;
            } નહીંતર જો (SDL_wcscmp(deviceName, sourceName.viewGdiDeviceName) != 0) {
                ચાલુ;
            }

            SDL_zero(targetName);
            targetName.header.adapterId = paths[i].targetInfo.adapterId;
            targetName.header.id = paths[i].targetInfo.id;
            targetName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
            targetName.header.size = કદ(targetName);
            rc = videodata->DisplayConfigGetDeviceInfo(&targetName.header);
            જો (rc == ERROR_SUCCESS) {
                result = WIN_StringToUTF8W(targetName.monitorFriendlyDeviceName);
                /* if we got an empty string, treat it as failure so we'll fallback
                   to getting the generic name. */
                જો (result && (*result == '\0')) {
                    SDL_free(result);
                    result = ખાલી;
                }
            }
            તોડો;
        }
    }

    SDL_free(paths);
    SDL_free(modes);
    પાછા result;

WIN_GetDisplayNameVista_failed:
    SDL_free(result);
    SDL_free(paths);
    SDL_free(modes);
    પાછા ખાલી;
}

#ifdef HAVE_DXGI1_6_H
સ્થિર bool WIN_GetMonitorDESC1(HMONITOR hMonitor, DXGI_OUTPUT_DESC1 *desc)
{
    પ્રકારવ્યાખ્યા HRESULT (WINAPI *pfnCreateDXGIFactory1)(REFIID riid, શૂન્ય **ppFactory);
    pfnCreateDXGIFactory1 pCreateDXGIFactory1 = ખાલી;
    SDL_SharedObject *hDXGIMod = ખાલી;
    bool found = false;

    hDXGIMod = SDL_LoadObject("dxgi.dll");
    જો (hDXGIMod) {
        pCreateDXGIFactory1 = (pfnCreateDXGIFactory1)SDL_LoadFunction(hDXGIMod, "CreateDXGIFactory1");
    }
    જો (pCreateDXGIFactory1) {
        સ્થિર અચલ GUID SDL_IID_IDXGIFactory1 = { 0x770aae78, 0xf26f, 0x4dba, { 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 } };
        સ્થિર અચલ GUID SDL_IID_IDXGIOutput6 = { 0x068346e8, 0xaaec, 0x4b84, { 0xad, 0xd7, 0x13, 0x7f, 0x51, 0x3f, 0x77, 0xa1 } };
        IDXGIFactory1 *dxgiFactory;

        જો (SUCCEEDED(pCreateDXGIFactory1(&SDL_IID_IDXGIFactory1, (શૂન્ય **)&dxgiFactory))) {
            IDXGIAdapter1 *dxgiAdapter;
            UINT adapter = 0;
            જ્યારે (!found && SUCCEEDED(IDXGIFactory1_EnumAdapters1(dxgiFactory, adapter, &dxgiAdapter))) {
                IDXGIOutput *dxgiOutput;
                UINT output = 0;
                જ્યારે (!found && SUCCEEDED(IDXGIAdapter1_EnumOutputs(dxgiAdapter, output, &dxgiOutput))) {
                    IDXGIOutput6 *dxgiOutput6;
                    જો (SUCCEEDED(IDXGIOutput_QueryInterface(dxgiOutput, &SDL_IID_IDXGIOutput6, (શૂન્ય **)&dxgiOutput6))) {
                        જો (SUCCEEDED(IDXGIOutput6_GetDesc1(dxgiOutput6, desc))) {
                            જો (desc->Monitor == hMonitor) {
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
    જો (hDXGIMod) {
        SDL_UnloadObject(hDXGIMod);
    }
    પાછા found;
}

સ્થિર bool WIN_GetMonitorPathInfo(SDL_VideoData *videodata, HMONITOR hMonitor, DISPLAYCONFIG_PATH_INFO *path_info)
{
    LONG result;
    MONITORINFOEXW view_info;
    UINT32 i;
    UINT32 અંક_path_array_elements = 0;
    UINT32 અંક_mode_info_array_elements = 0;
    DISPLAYCONFIG_PATH_INFO *path_infos = ખાલી, *new_path_infos;
    DISPLAYCONFIG_MODE_INFO *mode_infos = ખાલી, *new_mode_infos;
    bool found = false;

    જો (!videodata->GetDisplayConfigBufferSizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        પાછા false;
    }

    SDL_zero(view_info);
    view_info.cbSize = કદ(view_info);
    જો (!GetMonitorInfoW(hMonitor, (MONITORINFO *)&view_info)) {
        જાઓ done;
    }

    કરો {
        જો (videodata->GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &અંક_path_array_elements, &અંક_mode_info_array_elements) != ERROR_SUCCESS) {
            SDL_free(path_infos);
            SDL_free(mode_infos);
            પાછા false;
        }

        new_path_infos = (DISPLAYCONFIG_PATH_INFO *)SDL_realloc(path_infos, અંક_path_array_elements * કદ(*path_infos));
        જો (!new_path_infos) {
            જાઓ done;
        }
        path_infos = new_path_infos;

        new_mode_infos = (DISPLAYCONFIG_MODE_INFO *)SDL_realloc(mode_infos, અંક_mode_info_array_elements * કદ(*mode_infos));
        જો (!new_mode_infos) {
            જાઓ done;
        }
        mode_infos = new_mode_infos;

        result = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &અંક_path_array_elements, path_infos, &અંક_mode_info_array_elements, mode_infos, ખાલી);

    } જ્યારે (result == ERROR_INSUFFICIENT_BUFFER);

    જો (result == ERROR_SUCCESS) {
        માટે (i = 0; i < અંક_path_array_elements; ++i) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME device_name;

            SDL_zero(device_name);
            device_name.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            device_name.header.size = કદ(device_name);
            device_name.header.adapterId = path_infos[i].sourceInfo.adapterId;
            device_name.header.id = path_infos[i].sourceInfo.id;
            જો (videodata->DisplayConfigGetDeviceInfo(&device_name.header) == ERROR_SUCCESS) {
                જો (SDL_wcscmp(view_info.szDevice, device_name.viewGdiDeviceName) == 0) {
                    SDL_copyp(path_info, &path_infos[i]);
                    found = true;
                    તોડો;
                }
            }
        }
    }

done:
    SDL_free(path_infos);
    SDL_free(mode_infos);

    પાછા found;
}

સ્થિર દશાંશ WIN_GetSDRWhitePoint(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    DISPLAYCONFIG_PATH_INFO path_info;
    SDL_VideoData *videodata = _this->internal;
    દશાંશ SDR_white_level = 1.0f;

    જો (WIN_GetMonitorPathInfo(videodata, hMonitor, &path_info)) {
        /* workarounds for https://github.com/libsdl-org/SDL/issues/11193 */
        સંરચના SDL_DISPLAYCONFIG_SDR_WHITE_LEVEL {
          DISPLAYCONFIG_DEVICE_INFO_HEADER header;
          ULONG SDRWhiteLevel;
        } white_level;
        #define DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL 11

        SDL_zero(white_level);
        white_level.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
        white_level.header.size = કદ(white_level);
        white_level.header.adapterId = path_info.targetInfo.adapterId;
        white_level.header.id = path_info.targetInfo.id;
        // WIN_GetMonitorPathInfo() succeeded: DisplayConfigGetDeviceInfo is not NULL
        જો (videodata->DisplayConfigGetDeviceInfo(&white_level.header) == ERROR_SUCCESS &&
            white_level.SDRWhiteLevel > 0) {
            SDR_white_level = (white_level.SDRWhiteLevel / 1000.0f);
        }
    }
    પાછા SDR_white_level;
}

સ્થિર શૂન્ય WIN_GetHDRProperties(SDL_VideoDevice *_this, HMONITOR hMonitor, SDL_HDROutputProperties *HDR)
{
    DXGI_OUTPUT_DESC1 desc;

    SDL_zerop(HDR);

    જો (WIN_GetMonitorDESC1(hMonitor, &desc)) {
        જો (desc.ColorSpace == DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020) {
            HDR->SDR_white_level = WIN_GetSDRWhitePoint(_this, hMonitor);
            HDR->HDR_headroom = (desc.MaxLuminance / SCRGB_NITS) / HDR->SDR_white_level;
        }
    }
}
#endif // HAVE_DXGI1_6_H

સ્થિર શૂન્ય WIN_AddDisplay(SDL_VideoDevice *_this, HMONITOR hMonitor, અચલ MONITORINFOEXW *info, પૂર્ણાંક *display_index)
{
    પૂર્ણાંક i, index = *display_index;
    SDL_VideoDisplay display;
    SDL_DisplayData *displaydata;
    શૂન્ય *dxgi_output = ખાલી;
    SDL_DisplayMode mode;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    દશાંશ content_scale = WIN_GetContentScale(_this, hMonitor);

#ifdef DEBUG_MODES
    SDL_Log("Display: %s", WIN_StringToUTF8W(info->szDevice));
#endif

    dxgi_output = WIN_GetDXGIOutput(_this, info->szDevice);
    bool found = WIN_GetDisplayMode(_this, dxgi_output, hMonitor, info->szDevice, ENUM_CURRENT_SETTINGS, &mode, &natural_orientation, &current_orientation);
    WIN_ReleaseDXGIOutput(dxgi_output);
    જો (!found) {
        પાછા;
    }

    // Prevent adding duplicate displays. Do this after we know the display is
    // ready to be added to allow any displays that we can't fully query to be
    // removed
    માટે (i = 0; i < _this->અંક_displays; ++i) {
        SDL_DisplayData *internal = _this->displays[i]->internal;
        જો (SDL_wcscmp(internal->DeviceName, info->szDevice) == 0) {
            bool moved = (index != i);
            bool changed_bounds = false;

            જો (internal->state != DisplayRemoved) {
                // We've already enumerated this display, don't move it
                જાઓ cleanup;
            }

            જો (index >= _this->અંક_displays) {
                // This should never happen due to the check above, but just in case...
                જાઓ cleanup;
            }

            જો (moved) {
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

            જો (!_this->setting_display_mode) {
                SDL_VideoDisplay *existing_display = _this->displays[i];
                SDL_Rect bounds;

                SDL_ResetFullscreenDisplayModes(existing_display);
                SDL_SetDesktopDisplayMode(existing_display, &mode);
                // The mode is owned by the video subsystem
                mode.internal = ખાલી;
                જો (WIN_GetDisplayBounds(_this, existing_display, &bounds) &&
                    SDL_memcmp(&internal->bounds, &bounds, કદ(bounds)) != 0) {
                    changed_bounds = true;
                    SDL_copyp(&internal->bounds, &bounds);
                }
                જો (moved || changed_bounds) {
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
            જાઓ done;
        }
    }

    displaydata = (SDL_DisplayData *)SDL_calloc(1, કદ(*displaydata));
    જો (!displaydata) {
        જાઓ cleanup;
    }
    SDL_memcpy(displaydata->DeviceName, info->szDevice, કદ(displaydata->DeviceName));
    displaydata->MonitorHandle = hMonitor;
    displaydata->state = DisplayAdded;

    SDL_zero(display);
    display.name = WIN_GetDisplayNameVista(_this->internal, info->szDevice);
    જો (!display.name) {
        DISPLAY_DEVICEW device;
        SDL_zero(device);
        device.cb = કદ(device);
        જો (EnumDisplayDevicesW(info->szDevice, 0, &device, 0)) {
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
    જો (displayID) {
        // The mode is owned by the video subsystem
        mode.internal = ખાલી;

        SDL_PropertiesID props = SDL_GetDisplayProperties(displayID);
        SDL_SetPointerProperty(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_POINTER, hMonitor);
    } નહીંતર {
        SDL_free(displaydata);
    }
    SDL_free(display.name);

done:
    *display_index += 1;

cleanup:
    SDL_free(mode.internal);
}

પ્રકારવ્યાખ્યા સંરચના _WIN_AddDisplaysData
{
    SDL_VideoDevice *video_device;
    પૂર્ણાંક display_index;
    bool want_primary;
} WIN_AddDisplaysData;

સ્થિર BOOL CALLBACK WIN_AddDisplaysCallback(HMONITOR hMonitor,
                                             HDC hdcMonitor,
                                             LPRECT lprcMonitor,
                                             LPARAM dwData)
{
    WIN_AddDisplaysData *data = (WIN_AddDisplaysData *)dwData;
    MONITORINFOEXW info;

    SDL_zero(info);
    info.cbSize = કદ(info);

    જો (GetMonitorInfoW(hMonitor, (LPMONITORINFO)&info) != 0) {
        અચલ bool is_primary = ((info.dwFlags & MONITORINFOF_PRIMARY) == MONITORINFOF_PRIMARY);

        જો (is_primary == data->want_primary) {
            WIN_AddDisplay(data->video_device, hMonitor, &info, &data->display_index);
        }
    }

    // continue enumeration
    પાછા TRUE;
}

સ્થિર શૂન્ય WIN_AddDisplays(SDL_VideoDevice *_this)
{
    WIN_AddDisplaysData callback_data;
    callback_data.video_device = _this;
    callback_data.display_index = 0;

    callback_data.want_primary = true;
    EnumDisplayMonitors(ખાલી, ખાલી, WIN_AddDisplaysCallback, (LPARAM)&callback_data);

    callback_data.want_primary = false;
    EnumDisplayMonitors(ખાલી, ખાલી, WIN_AddDisplaysCallback, (LPARAM)&callback_data);
}

bool WIN_InitModes(SDL_VideoDevice *_this)
{
    WIN_AddDisplays(_this);

    જો (_this->અંક_displays == 0) {
        પાછા SDL_SetError("No displays available");
    }
    પાછા true;
}

bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    અચલ SDL_DisplayData *data = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cbSize = કદ(MONITORINFO);
    rc = GetMonitorInfo(data->MonitorHandle, &minfo);

    જો (!rc) {
        પાછા SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcMonitor.ડાબું;
    rect->y = minfo.rcMonitor.ટોચ;
    rect->w = minfo.rcMonitor.જમણું - minfo.rcMonitor.ડાબું;
    rect->h = minfo.rcMonitor.bottom - minfo.rcMonitor.ટોચ;

    પાછા true;
}

bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    અચલ SDL_DisplayData *data = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cbSize = કદ(MONITORINFO);
    rc = GetMonitorInfo(data->MonitorHandle, &minfo);

    જો (!rc) {
        પાછા SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcWork.ડાબું;
    rect->y = minfo.rcWork.ટોચ;
    rect->w = minfo.rcWork.જમણું - minfo.rcWork.ડાબું;
    rect->h = minfo.rcWork.bottom - minfo.rcWork.ટોચ;

    પાછા true;
}

bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_DisplayData *data = display->internal;
    શૂન્ય *dxgi_output;
    DWORD i;
    SDL_DisplayMode mode;

    dxgi_output = WIN_GetDXGIOutput(_this, data->DeviceName);

    // Make sure we add the current mode to the list in case it's a custom mode that doesn't enumerate
    માટે (i = ENUM_CURRENT_SETTINGS; ; ++i) {
        જો (!WIN_GetDisplayMode(_this, dxgi_output, data->MonitorHandle, data->DeviceName, i, &mode, ખાલી, ખાલી)) {
            તોડો;
        }
        જો (SDL_ISPIXELFORMAT_INDEXED(mode.format)) {
            // We don't support palettized modes now
            SDL_free(mode.internal);
            ચાલુ;
        }
        જો (mode.format != SDL_PIXELFORMAT_UNKNOWN) {
            જો (!SDL_AddFullscreenDisplayMode(display, &mode)) {
                SDL_free(mode.internal);
            }
        } નહીંતર {
            SDL_free(mode.internal);
        }
    }

    WIN_ReleaseDXGIOutput(dxgi_output);

    પાછા true;
}

#ifdef DEBUG_MODES
સ્થિર શૂન્ય WIN_LogMonitor(SDL_VideoDevice *_this, HMONITOR mon)
{
    અચલ SDL_VideoData *vid_data = (અચલ SDL_VideoData *)_this->internal;
    MONITORINFOEX minfo;
    UINT xdpi = 0, ydpi = 0;
    અક્ષર *name_utf8;

    જો (vid_data->GetDpiForMonitor) {
        vid_data->GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &xdpi, &ydpi);
    }

    SDL_zero(minfo);
    minfo.cbSize = કદ(minfo);
    GetMonitorInfo(mon, (LPMONITORINFO)&minfo);

    name_utf8 = WIN_StringToUTF8(minfo.szDevice);

    SDL_Log("WIN_LogMonitor: monitor \"%s\": dpi: %d windows screen coordinates: %d, %d, %dx%d",
            name_utf8,
            xdpi,
            minfo.rcMonitor.ડાબું,
            minfo.rcMonitor.ટોચ,
            minfo.rcMonitor.જમણું - minfo.rcMonitor.ડાબું,
            minfo.rcMonitor.bottom - minfo.rcMonitor.ટોચ);

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
    જો (mode->internal == display->desktop_mode.internal) {
#ifdef DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: resetting to original resolution");
#endif
        status = ChangeDisplaySettingsExW(displaydata->DeviceName, ખાલી, ખાલી, CDS_FULLSCREEN, ખાલી);
    } નહીંતર {
#ifdef DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: changing to %dx%d pixels", data->DeviceMode.dmPelsWidth, data->DeviceMode.dmPelsHeight);
#endif
        status = ChangeDisplaySettingsExW(displaydata->DeviceName, &data->DeviceMode, ખાલી, CDS_FULLSCREEN, ખાલી);
    }
    જો (status != DISP_CHANGE_SUCCESSFUL) {
        અચલ અક્ષર *reason = "Unknown reason";
        પસંદગી (status) {
        સ્થિતિ DISP_CHANGE_BADFLAGS:
            reason = "DISP_CHANGE_BADFLAGS";
            તોડો;
        સ્થિતિ DISP_CHANGE_BADMODE:
            reason = "DISP_CHANGE_BADMODE";
            તોડો;
        સ્થિતિ DISP_CHANGE_BADPARAM:
            reason = "DISP_CHANGE_BADPARAM";
            તોડો;
        સ્થિતિ DISP_CHANGE_FAILED:
            reason = "DISP_CHANGE_FAILED";
            તોડો;
        }
        પાછા SDL_SetError("ChangeDisplaySettingsEx() failed: %s", reason);
    }

#ifdef DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state after mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#endif

    EnumDisplaySettingsW(displaydata->DeviceName, ENUM_CURRENT_SETTINGS, &data->DeviceMode);
    WIN_UpdateDisplayMode(_this, displaydata->DeviceName, ENUM_CURRENT_SETTINGS, mode);
    પાછા true;
}

શૂન્ય WIN_RefreshDisplays(SDL_VideoDevice *_this)
{
    પૂર્ણાંક i;

    // Mark all displays as potentially invalid to detect
    // entries that have actually been removed
    માટે (i = 0; i < _this->અંક_displays; ++i) {
        SDL_DisplayData *internal = _this->displays[i]->internal;
        internal->state = DisplayRemoved;
    }

    // Enumerate displays to add any new ones and mark still
    // connected entries as valid
    WIN_AddDisplays(_this);

    // Delete any entries still marked as invalid, iterate
    // in reverse as each delete takes effect immediately
    માટે (i = _this->અંક_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DisplayData *internal = display->internal;
        જો (internal->state == DisplayRemoved) {
            SDL_DelVideoDisplay(display->id, true);
        }
    }

    // Send events for any newly added displays
    માટે (i = 0; i < _this->અંક_displays; ++i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DisplayData *internal = display->internal;
        જો (internal->state == DisplayAdded) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
        }
    }
}

શૂન્ય WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this)
{
    // This almost never happens, so just go ahead and send update events for all displays
    માટે (પૂર્ણાંક i = 0; i < _this->અંક_displays; ++i) {
        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_CHANGED, 0, 0);
    }
}

શૂન્ય WIN_QuitModes(SDL_VideoDevice *_this)
{
    // All fullscreen windows should have restored modes by now
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
