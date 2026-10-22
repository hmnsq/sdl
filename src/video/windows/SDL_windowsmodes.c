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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ଯଦି defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ଅନ୍ତର୍ଭାଵ "SDL_windowsvideo.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_displayevents_c.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_pixels_c.h"

#ifdef HAVE_DXGI1_6_H
#define COBJMACROS
#ଅନ୍ତର୍ଭାଵ <dxgi1_6.h>
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

ସ୍ଥିର ଶୂନ୍ୟ WIN_UpdateDisplayMode(SDL_VideoDevice *_this, LPCWSTR deviceName, DWORD index, SDL_DisplayMode *mode)
{
    SDL_DisplayModeData *data = (SDL_DisplayModeData *)mode->internal;
    HDC hdc;

    data->DeviceMode.dmFields = (DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS);

    // NOLINTNEXTLINE(bugprone-assignment-in-if-condition): No simple way to extract the assignment
    ଯଦି (index == ENUM_CURRENT_SETTINGS && (hdc = CreateDCW(deviceName, ଖାଲି, ଖାଲି, ଖାଲି)) != ଖାଲି) {
        ଅକ୍ଷର bmi_data[ଆକାର(BITMAPINFOHEADER) + 256 * ଆକାର(RGBQUAD)];
        LPBITMAPINFO bmi;
        HBITMAP hbm;

        SDL_zeroa(bmi_data);
        bmi = (LPBITMAPINFO)bmi_data;
        bmi->bmiHeader.biSize = ଆକାର(BITMAPINFOHEADER);

        hbm = CreateCompatibleBitmap(hdc, 1, 1);
        GetDIBits(hdc, hbm, 0, 1, ଖାଲି, bmi, DIB_RGB_COLORS);
        GetDIBits(hdc, hbm, 0, 1, ଖାଲି, bmi, DIB_RGB_COLORS);
        DeleteObject(hbm);
        DeleteDC(hdc);
        ଯଦି (bmi->bmiHeader.biCompression == BI_BITFIELDS) {
            ବାଛ (*(Uint32 *)bmi->bmiColors) {
            ସ୍ଥିତି 0x00FF0000:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                ଭାଙ୍ଗ;
            ସ୍ଥିତି 0x000000FF:
                mode->format = SDL_PIXELFORMAT_XBGR8888;
                ଭାଙ୍ଗ;
            ସ୍ଥିତି 0xF800:
                mode->format = SDL_PIXELFORMAT_RGB565;
                ଭାଙ୍ଗ;
            ସ୍ଥିତି 0x7C00:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                ଭାଙ୍ଗ;
            }
        } ଅନ୍ୟଥା ଯଦି (bmi->bmiHeader.biCompression == BI_RGB) {
            ଯଦି (bmi->bmiHeader.bi_Bit_ଗଣନା == 24) {
                mode->format = SDL_PIXELFORMAT_RGB24;
            } ଅନ୍ୟଥା ଯଦି (bmi->bmiHeader.bi_Bit_ଗଣନା == 8) {
                mode->format = SDL_PIXELFORMAT_INDEX8;
            } ଅନ୍ୟଥା ଯଦି (bmi->bmiHeader.bi_Bit_ଗଣନା == 4) {
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
            }
        }
    } ଅନ୍ୟଥା ଯଦି (mode->format == SDL_PIXELFORMAT_UNKNOWN) {
        // FIXME: Can we tell what this will be?
        ଯଦି ((data->DeviceMode.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL) {
            ବାଛ (data->DeviceMode.dmBitsPerPel) {
            ସ୍ଥିତି 32:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                ଭାଙ୍ଗ;
            ସ୍ଥିତି 24:
                mode->format = SDL_PIXELFORMAT_RGB24;
                ଭାଙ୍ଗ;
            ସ୍ଥିତି 16:
                mode->format = SDL_PIXELFORMAT_RGB565;
                ଭାଙ୍ଗ;
            ସ୍ଥିତି 15:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                ଭାଙ୍ଗ;
            ସ୍ଥିତି 8:
                mode->format = SDL_PIXELFORMAT_INDEX8;
                ଭାଙ୍ଗ;
            ସ୍ଥିତି 4:
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
                ଭାଙ୍ଗ;
            }
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ *WIN_GetDXGIOutput(SDL_VideoDevice *_this, ଅଚଳ WCHAR *DeviceName)
{
    ଶୂନ୍ୟ *result = ଖାଲି;

#ifdef HAVE_DXGI_H
    ଅଚଳ SDL_VideoData *videodata = (ଅଚଳ SDL_VideoData *)_this->internal;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    ଯଦି (!videodata->pDXGIFactory) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    nAdapter = 0;
    ଯେତେବେଳେ (!result && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        ଯେତେବେଳେ (!result && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            ଯଦି (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                ଯଦି (SDL_wcscmp(outputDesc.DeviceName, DeviceName) == 0) {
                    result = pDXGIOutput;
                }
            }
            ଯଦି (pDXGIOutput != result) {
                IDXGIOutput_Release(pDXGIOutput);
            }
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }
#endif
    ଫେରନ୍ତୁ result;
}

ସ୍ଥିର ଶୂନ୍ୟ WIN_ReleaseDXGIOutput(ଶୂନ୍ୟ *dxgi_output)
{
#ifdef HAVE_DXGI_H
    IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;

    ଯଦି (pDXGIOutput) {
        IDXGIOutput_Release(pDXGIOutput);
    }
#endif
}

ସ୍ଥିର SDL_DisplayOrientation WIN_GetNaturalOrientation(DEVMODEW *mode)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width = mode->dmPelsWidth;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା height = mode->dmPelsHeight;

    // Use unrotated width/height to guess orientation
    ଯଦି (mode->dmDisplayOrientation == DMDO_90 || mode->dmDisplayOrientation == DMDO_270) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା temp = width;
        width = height;
        height = temp;
    }

    ଯଦି (width >= height) {
        ଫେରନ୍ତୁ SDL_ORIENTATION_LANDSCAPE;
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ SDL_ORIENTATION_PORTRAIT;
    }
}

ସ୍ଥିର SDL_DisplayOrientation WIN_GetDisplayOrientation(DEVMODEW *mode)
{
    ଯଦି (WIN_GetNaturalOrientation(mode) == SDL_ORIENTATION_LANDSCAPE) {
        ବାଛ (mode->dmDisplayOrientation) {
        ସ୍ଥିତି DMDO_DEFAULT:
            ଫେରନ୍ତୁ SDL_ORIENTATION_LANDSCAPE;
        ସ୍ଥିତି DMDO_90:
            ଫେରନ୍ତୁ SDL_ORIENTATION_PORTRAIT;
        ସ୍ଥିତି DMDO_180:
            ଫେରନ୍ତୁ SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        ସ୍ଥିତି DMDO_270:
            ଫେରନ୍ତୁ SDL_ORIENTATION_PORTRAIT_FLIPPED;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଫେରନ୍ତୁ SDL_ORIENTATION_UNKNOWN;
        }
    } ଅନ୍ୟଥା {
        ବାଛ (mode->dmDisplayOrientation) {
        ସ୍ଥିତି DMDO_DEFAULT:
            ଫେରନ୍ତୁ SDL_ORIENTATION_PORTRAIT;
        ସ୍ଥିତି DMDO_90:
            ଫେରନ୍ତୁ SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        ସ୍ଥିତି DMDO_180:
            ଫେରନ୍ତୁ SDL_ORIENTATION_PORTRAIT_FLIPPED;
        ସ୍ଥିତି DMDO_270:
            ଫେରନ୍ତୁ SDL_ORIENTATION_LANDSCAPE;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଫେରନ୍ତୁ SDL_ORIENTATION_UNKNOWN;
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ WIN_GetRefreshRate(ଶୂନ୍ୟ *dxgi_output, DEVMODEW *mode, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *numerator, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *denominator)
{
    // We're not currently using DXGI to query display modes, so fake NTSC timings
    ବାଛ (mode->dmDisplayFrequency) {
    ସ୍ଥିତି 119:
    ସ୍ଥିତି 59:
    ସ୍ଥିତି 29:
        *numerator = (mode->dmDisplayFrequency + 1) * 1000;
        *denominator = 1001;
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        *numerator = mode->dmDisplayFrequency;
        *denominator = 1;
        ଭାଙ୍ଗ;
    }

#ifdef HAVE_DXGI_H
    ଯଦି (dxgi_output) {
        IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;
        DXGI_MODE_DESC modeToMatch;
        DXGI_MODE_DESC closestMatch;

        SDL_zero(modeToMatch);
        modeToMatch.Width = mode->dmPelsWidth;
        modeToMatch.Height = mode->dmPelsHeight;
        modeToMatch.RefreshRate.Numerator = *numerator;
        modeToMatch.RefreshRate.Denominator = *denominator;
        modeToMatch.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        ଯଦି (SUCCEEDED(IDXGIOutput_FindClosestMatchingMode(pDXGIOutput, &modeToMatch, &closestMatch, ଖାଲି))) {
            *numerator = closestMatch.RefreshRate.Numerator;
            *denominator = closestMatch.RefreshRate.Denominator;
        }
    }
#endif // HAVE_DXGI_H
}

ସ୍ଥିର ଦଶମିକ WIN_GetContentScale(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dpi = 0;

    ଅଚଳ SDL_VideoData *videodata = (ଅଚଳ SDL_VideoData *)_this->internal;
    ଯଦି (videodata->GetDpiForMonitor) {
        UINT hdpi_uint, vdpi_uint;
        ଯଦି (videodata->GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
            dpi = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)hdpi_uint;
        }
    }
    ଯଦି (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(ଖାଲି);
        ଯଦି (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(ଖାଲି, hdc);
        }
    }
    ଯଦି (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    ଫେରନ୍ତୁ dpi / (ଦଶମିକ)USER_DEFAULT_SCREEN_DPI;
}

ସ୍ଥିର bool WIN_GetDisplayMode(SDL_VideoDevice *_this, ଶୂନ୍ୟ *dxgi_output, HMONITOR hMonitor, LPCWSTR deviceName, DWORD index, SDL_DisplayMode *mode, SDL_DisplayOrientation *natural_orientation, SDL_DisplayOrientation *current_orientation)
{
    SDL_DisplayModeData *data;
    DEVMODEW devmode;

    devmode.dmSize = ଆକାର(devmode);
    devmode.dmDriverExtra = 0;
    ଯଦି (!EnumDisplaySettingsW(deviceName, index, &devmode)) {
        ଫେରନ୍ତୁ false;
    }

    data = (SDL_DisplayModeData *)SDL_malloc(ଆକାର(*data));
    ଯଦି (!data) {
        ଫେରନ୍ତୁ false;
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

    ଯଦି (natural_orientation) {
        *natural_orientation = WIN_GetNaturalOrientation(&devmode);
    }
    ଯଦି (current_orientation) {
        *current_orientation = WIN_GetDisplayOrientation(&devmode);
    }

    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର ଅକ୍ଷର *WIN_GetDisplayNameVista(SDL_VideoData *videodata, ଅଚଳ WCHAR *deviceName)
{
    DISPLAYCONFIG_PATH_INFO *paths = ଖାଲି;
    DISPLAYCONFIG_MODE_INFO *modes = ଖାଲି;
    ଅକ୍ଷର *result = ଖାଲି;
    UINT32 path_ଗଣନା_2 = 0;
    UINT32 mode_ଗଣନା_2 = 0;
    UINT32 i;
    LONG rc;

    ଯଦି (!videodata->GetDisplayConfigBufferSizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    କର {
        rc = videodata->GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &path_ଗଣନା_2, &mode_ଗଣନା_2);
        ଯଦି (rc != ERROR_SUCCESS) {
            ଯାଅ WIN_GetDisplayNameVista_failed;
        }

        SDL_free(paths);
        SDL_free(modes);

        paths = (DISPLAYCONFIG_PATH_INFO *)SDL_malloc(ଆକାର(DISPLAYCONFIG_PATH_INFO) * path_ଗଣନା_2);
        modes = (DISPLAYCONFIG_MODE_INFO *)SDL_malloc(ଆକାର(DISPLAYCONFIG_MODE_INFO) * mode_ଗଣନା_2);
        ଯଦି ((!paths) || (!modes)) {
            ଯାଅ WIN_GetDisplayNameVista_failed;
        }

        rc = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &path_ଗଣନା_2, paths, &mode_ଗଣନା_2, modes, 0);
    } ଯେତେବେଳେ (rc == ERROR_INSUFFICIENT_BUFFER);

    ଯଦି (rc == ERROR_SUCCESS) {
        ପାଇଁ (i = 0; i < path_ଗଣନା_2; i++) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME sourceName;
            DISPLAYCONFIG_TARGET_DEVICE_NAME targetName;

            SDL_zero(sourceName);
            sourceName.header.adapterId = paths[i].targetInfo.adapterId;
            sourceName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            sourceName.header.size = ଆକାର(sourceName);
            sourceName.header.id = paths[i].sourceInfo.id;
            rc = videodata->DisplayConfigGetDeviceInfo(&sourceName.header);
            ଯଦି (rc != ERROR_SUCCESS) {
                ଭାଙ୍ଗ;
            } ଅନ୍ୟଥା ଯଦି (SDL_wcscmp(deviceName, sourceName.viewGdiDeviceName) != 0) {
                ଜାରି;
            }

            SDL_zero(targetName);
            targetName.header.adapterId = paths[i].targetInfo.adapterId;
            targetName.header.id = paths[i].targetInfo.id;
            targetName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
            targetName.header.size = ଆକାର(targetName);
            rc = videodata->DisplayConfigGetDeviceInfo(&targetName.header);
            ଯଦି (rc == ERROR_SUCCESS) {
                result = WIN_StringToUTF8W(targetName.monitorFriendlyDeviceName);
                /* if we got an empty string, treat it as failure so we'll fallback
                   to getting the generic name. */
                ଯଦି (result && (*result == '\0')) {
                    SDL_free(result);
                    result = ଖାଲି;
                }
            }
            ଭାଙ୍ଗ;
        }
    }

    SDL_free(paths);
    SDL_free(modes);
    ଫେରନ୍ତୁ result;

WIN_GetDisplayNameVista_failed:
    SDL_free(result);
    SDL_free(paths);
    SDL_free(modes);
    ଫେରନ୍ତୁ ଖାଲି;
}

#ifdef HAVE_DXGI1_6_H
ସ୍ଥିର bool WIN_GetMonitorDESC1(HMONITOR hMonitor, DXGI_OUTPUT_DESC1 *desc)
{
    ପ୍ରକାରବ୍ୟାଖ୍ୟା HRESULT (WINAPI *pfnCreateDXGIFactory1)(REFIID riid, ଶୂନ୍ୟ **ppFactory);
    pfnCreateDXGIFactory1 pCreateDXGIFactory1 = ଖାଲି;
    SDL_SharedObject *hDXGIMod = ଖାଲି;
    bool found = false;

    hDXGIMod = SDL_LoadObject("dxgi.dll");
    ଯଦି (hDXGIMod) {
        pCreateDXGIFactory1 = (pfnCreateDXGIFactory1)SDL_LoadFunction(hDXGIMod, "CreateDXGIFactory1");
    }
    ଯଦି (pCreateDXGIFactory1) {
        ସ୍ଥିର ଅଚଳ GUID SDL_IID_IDXGIFactory1 = { 0x770aae78, 0xf26f, 0x4dba, { 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 } };
        ସ୍ଥିର ଅଚଳ GUID SDL_IID_IDXGIOutput6 = { 0x068346e8, 0xaaec, 0x4b84, { 0xad, 0xd7, 0x13, 0x7f, 0x51, 0x3f, 0x77, 0xa1 } };
        IDXGIFactory1 *dxgiFactory;

        ଯଦି (SUCCEEDED(pCreateDXGIFactory1(&SDL_IID_IDXGIFactory1, (ଶୂନ୍ୟ **)&dxgiFactory))) {
            IDXGIAdapter1 *dxgiAdapter;
            UINT adapter = 0;
            ଯେତେବେଳେ (!found && SUCCEEDED(IDXGIFactory1_EnumAdapters1(dxgiFactory, adapter, &dxgiAdapter))) {
                IDXGIOutput *dxgiOutput;
                UINT output = 0;
                ଯେତେବେଳେ (!found && SUCCEEDED(IDXGIAdapter1_EnumOutputs(dxgiAdapter, output, &dxgiOutput))) {
                    IDXGIOutput6 *dxgiOutput6;
                    ଯଦି (SUCCEEDED(IDXGIOutput_QueryInterface(dxgiOutput, &SDL_IID_IDXGIOutput6, (ଶୂନ୍ୟ **)&dxgiOutput6))) {
                        ଯଦି (SUCCEEDED(IDXGIOutput6_GetDesc1(dxgiOutput6, desc))) {
                            ଯଦି (desc->Monitor == hMonitor) {
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
    ଯଦି (hDXGIMod) {
        SDL_UnloadObject(hDXGIMod);
    }
    ଫେରନ୍ତୁ found;
}

ସ୍ଥିର bool WIN_GetMonitorPathInfo(SDL_VideoData *videodata, HMONITOR hMonitor, DISPLAYCONFIG_PATH_INFO *path_info)
{
    LONG result;
    MONITORINFOEXW view_info;
    UINT32 i;
    UINT32 ଅଙ୍କ_path_array_elements = 0;
    UINT32 ଅଙ୍କ_mode_info_array_elements = 0;
    DISPLAYCONFIG_PATH_INFO *path_infos = ଖାଲି, *new_path_infos;
    DISPLAYCONFIG_MODE_INFO *mode_infos = ଖାଲି, *new_mode_infos;
    bool found = false;

    ଯଦି (!videodata->GetDisplayConfigBufferSizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        ଫେରନ୍ତୁ false;
    }

    SDL_zero(view_info);
    view_info.cbSize = ଆକାର(view_info);
    ଯଦି (!GetMonitorInfoW(hMonitor, (MONITORINFO *)&view_info)) {
        ଯାଅ done;
    }

    କର {
        ଯଦି (videodata->GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &ଅଙ୍କ_path_array_elements, &ଅଙ୍କ_mode_info_array_elements) != ERROR_SUCCESS) {
            SDL_free(path_infos);
            SDL_free(mode_infos);
            ଫେରନ୍ତୁ false;
        }

        new_path_infos = (DISPLAYCONFIG_PATH_INFO *)SDL_realloc(path_infos, ଅଙ୍କ_path_array_elements * ଆକାର(*path_infos));
        ଯଦି (!new_path_infos) {
            ଯାଅ done;
        }
        path_infos = new_path_infos;

        new_mode_infos = (DISPLAYCONFIG_MODE_INFO *)SDL_realloc(mode_infos, ଅଙ୍କ_mode_info_array_elements * ଆକାର(*mode_infos));
        ଯଦି (!new_mode_infos) {
            ଯାଅ done;
        }
        mode_infos = new_mode_infos;

        result = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &ଅଙ୍କ_path_array_elements, path_infos, &ଅଙ୍କ_mode_info_array_elements, mode_infos, ଖାଲି);

    } ଯେତେବେଳେ (result == ERROR_INSUFFICIENT_BUFFER);

    ଯଦି (result == ERROR_SUCCESS) {
        ପାଇଁ (i = 0; i < ଅଙ୍କ_path_array_elements; ++i) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME device_name;

            SDL_zero(device_name);
            device_name.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            device_name.header.size = ଆକାର(device_name);
            device_name.header.adapterId = path_infos[i].sourceInfo.adapterId;
            device_name.header.id = path_infos[i].sourceInfo.id;
            ଯଦି (videodata->DisplayConfigGetDeviceInfo(&device_name.header) == ERROR_SUCCESS) {
                ଯଦି (SDL_wcscmp(view_info.szDevice, device_name.viewGdiDeviceName) == 0) {
                    SDL_copyp(path_info, &path_infos[i]);
                    found = true;
                    ଭାଙ୍ଗ;
                }
            }
        }
    }

done:
    SDL_free(path_infos);
    SDL_free(mode_infos);

    ଫେରନ୍ତୁ found;
}

ସ୍ଥିର ଦଶମିକ WIN_GetSDRWhitePoint(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    DISPLAYCONFIG_PATH_INFO path_info;
    SDL_VideoData *videodata = _this->internal;
    ଦଶମିକ SDR_white_level = 1.0f;

    ଯଦି (WIN_GetMonitorPathInfo(videodata, hMonitor, &path_info)) {
        /* workarounds for https://github.com/libsdl-org/SDL/issues/11193 */
        ସଂରଚନା SDL_DISPLAYCONFIG_SDR_WHITE_LEVEL {
          DISPLAYCONFIG_DEVICE_INFO_HEADER header;
          ULONG SDRWhiteLevel;
        } white_level;
        #define DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL 11

        SDL_zero(white_level);
        white_level.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
        white_level.header.size = ଆକାର(white_level);
        white_level.header.adapterId = path_info.targetInfo.adapterId;
        white_level.header.id = path_info.targetInfo.id;
        // WIN_GetMonitorPathInfo() succeeded: DisplayConfigGetDeviceInfo is not NULL
        ଯଦି (videodata->DisplayConfigGetDeviceInfo(&white_level.header) == ERROR_SUCCESS &&
            white_level.SDRWhiteLevel > 0) {
            SDR_white_level = (white_level.SDRWhiteLevel / 1000.0f);
        }
    }
    ଫେରନ୍ତୁ SDR_white_level;
}

ସ୍ଥିର ଶୂନ୍ୟ WIN_GetHDRProperties(SDL_VideoDevice *_this, HMONITOR hMonitor, SDL_HDROutputProperties *HDR)
{
    DXGI_OUTPUT_DESC1 desc;

    SDL_zerop(HDR);

    ଯଦି (WIN_GetMonitorDESC1(hMonitor, &desc)) {
        ଯଦି (desc.ColorSpace == DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020) {
            HDR->SDR_white_level = WIN_GetSDRWhitePoint(_this, hMonitor);
            HDR->HDR_headroom = (desc.MaxLuminance / SCRGB_NITS) / HDR->SDR_white_level;
        }
    }
}
#endif // HAVE_DXGI1_6_H

ସ୍ଥିର ଶୂନ୍ୟ WIN_AddDisplay(SDL_VideoDevice *_this, HMONITOR hMonitor, ଅଚଳ MONITORINFOEXW *info, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *display_index)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, index = *display_index;
    SDL_VideoDisplay display;
    SDL_DisplayData *displaydata;
    ଶୂନ୍ୟ *dxgi_output = ଖାଲି;
    SDL_DisplayMode mode;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    ଦଶମିକ content_scale = WIN_GetContentScale(_this, hMonitor);

#ifdef DEBUG_MODES
    SDL_Log("Display: %s", WIN_StringToUTF8W(info->szDevice));
#endif

    dxgi_output = WIN_GetDXGIOutput(_this, info->szDevice);
    bool found = WIN_GetDisplayMode(_this, dxgi_output, hMonitor, info->szDevice, ENUM_CURRENT_SETTINGS, &mode, &natural_orientation, &current_orientation);
    WIN_ReleaseDXGIOutput(dxgi_output);
    ଯଦି (!found) {
        ଫେରନ୍ତୁ;
    }

    // Prevent adding duplicate displays. Do this after we know the display is
    // ready to be added to allow any displays that we can't fully query to be
    // removed
    ପାଇଁ (i = 0; i < _this->ଅଙ୍କ_displays; ++i) {
        SDL_DisplayData *internal = _this->displays[i]->internal;
        ଯଦି (SDL_wcscmp(internal->DeviceName, info->szDevice) == 0) {
            bool moved = (index != i);
            bool changed_bounds = false;

            ଯଦି (internal->state != DisplayRemoved) {
                // We've already enumerated this display, don't move it
                ଯାଅ cleanup;
            }

            ଯଦି (index >= _this->ଅଙ୍କ_displays) {
                // This should never happen due to the check above, but just in case...
                ଯାଅ cleanup;
            }

            ଯଦି (moved) {
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

            ଯଦି (!_this->setting_display_mode) {
                SDL_VideoDisplay *existing_display = _this->displays[i];
                SDL_Rect bounds;

                SDL_ResetFullscreenDisplayModes(existing_display);
                SDL_SetDesktopDisplayMode(existing_display, &mode);
                // The mode is owned by the video subsystem
                mode.internal = ଖାଲି;
                ଯଦି (WIN_GetDisplayBounds(_this, existing_display, &bounds) &&
                    SDL_memcmp(&internal->bounds, &bounds, ଆକାର(bounds)) != 0) {
                    changed_bounds = true;
                    SDL_copyp(&internal->bounds, &bounds);
                }
                ଯଦି (moved || changed_bounds) {
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
            ଯାଅ done;
        }
    }

    displaydata = (SDL_DisplayData *)SDL_calloc(1, ଆକାର(*displaydata));
    ଯଦି (!displaydata) {
        ଯାଅ cleanup;
    }
    SDL_memcpy(displaydata->DeviceName, info->szDevice, ଆକାର(displaydata->DeviceName));
    displaydata->MonitorHandle = hMonitor;
    displaydata->state = DisplayAdded;

    SDL_zero(display);
    display.name = WIN_GetDisplayNameVista(_this->internal, info->szDevice);
    ଯଦି (!display.name) {
        DISPLAY_DEVICEW device;
        SDL_zero(device);
        device.cb = ଆକାର(device);
        ଯଦି (EnumDisplayDevicesW(info->szDevice, 0, &device, 0)) {
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
    ଯଦି (displayID) {
        // The mode is owned by the video subsystem
        mode.internal = ଖାଲି;

        SDL_PropertiesID props = SDL_GetDisplayProperties(displayID);
        SDL_SetPointerProperty(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_POINTER, hMonitor);
    } ଅନ୍ୟଥା {
        SDL_free(displaydata);
    }
    SDL_free(display.name);

done:
    *display_index += 1;

cleanup:
    SDL_free(mode.internal);
}

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା _WIN_AddDisplaysData
{
    SDL_VideoDevice *video_device;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା display_index;
    bool want_primary;
} WIN_AddDisplaysData;

ସ୍ଥିର BOOL CALLBACK WIN_AddDisplaysCallback(HMONITOR hMonitor,
                                             HDC hdcMonitor,
                                             LPRECT lprcMonitor,
                                             LPARAM dwData)
{
    WIN_AddDisplaysData *data = (WIN_AddDisplaysData *)dwData;
    MONITORINFOEXW info;

    SDL_zero(info);
    info.cbSize = ଆକାର(info);

    ଯଦି (GetMonitorInfoW(hMonitor, (LPMONITORINFO)&info) != 0) {
        ଅଚଳ bool is_primary = ((info.dwFlags & MONITORINFOF_PRIMARY) == MONITORINFOF_PRIMARY);

        ଯଦି (is_primary == data->want_primary) {
            WIN_AddDisplay(data->video_device, hMonitor, &info, &data->display_index);
        }
    }

    // continue enumeration
    ଫେରନ୍ତୁ TRUE;
}

ସ୍ଥିର ଶୂନ୍ୟ WIN_AddDisplays(SDL_VideoDevice *_this)
{
    WIN_AddDisplaysData callback_data;
    callback_data.video_device = _this;
    callback_data.display_index = 0;

    callback_data.want_primary = true;
    EnumDisplayMonitors(ଖାଲି, ଖାଲି, WIN_AddDisplaysCallback, (LPARAM)&callback_data);

    callback_data.want_primary = false;
    EnumDisplayMonitors(ଖାଲି, ଖାଲି, WIN_AddDisplaysCallback, (LPARAM)&callback_data);
}

bool WIN_InitModes(SDL_VideoDevice *_this)
{
    WIN_AddDisplays(_this);

    ଯଦି (_this->ଅଙ୍କ_displays == 0) {
        ଫେରନ୍ତୁ SDL_SetError("No displays available");
    }
    ଫେରନ୍ତୁ true;
}

bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ଅଚଳ SDL_DisplayData *data = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cbSize = ଆକାର(MONITORINFO);
    rc = GetMonitorInfo(data->MonitorHandle, &minfo);

    ଯଦି (!rc) {
        ଫେରନ୍ତୁ SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcMonitor.ବାମ;
    rect->y = minfo.rcMonitor.ଶୀର୍ଷ;
    rect->w = minfo.rcMonitor.ଡାହାଣ - minfo.rcMonitor.ବାମ;
    rect->h = minfo.rcMonitor.bottom - minfo.rcMonitor.ଶୀର୍ଷ;

    ଫେରନ୍ତୁ true;
}

bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ଅଚଳ SDL_DisplayData *data = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cbSize = ଆକାର(MONITORINFO);
    rc = GetMonitorInfo(data->MonitorHandle, &minfo);

    ଯଦି (!rc) {
        ଫେରନ୍ତୁ SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcWork.ବାମ;
    rect->y = minfo.rcWork.ଶୀର୍ଷ;
    rect->w = minfo.rcWork.ଡାହାଣ - minfo.rcWork.ବାମ;
    rect->h = minfo.rcWork.bottom - minfo.rcWork.ଶୀର୍ଷ;

    ଫେରନ୍ତୁ true;
}

bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_DisplayData *data = display->internal;
    ଶୂନ୍ୟ *dxgi_output;
    DWORD i;
    SDL_DisplayMode mode;

    dxgi_output = WIN_GetDXGIOutput(_this, data->DeviceName);

    // Make sure we add the current mode to the list in case it's a custom mode that doesn't enumerate
    ପାଇଁ (i = ENUM_CURRENT_SETTINGS; ; ++i) {
        ଯଦି (!WIN_GetDisplayMode(_this, dxgi_output, data->MonitorHandle, data->DeviceName, i, &mode, ଖାଲି, ଖାଲି)) {
            ଭାଙ୍ଗ;
        }
        ଯଦି (SDL_ISPIXELFORMAT_INDEXED(mode.format)) {
            // We don't support palettized modes now
            SDL_free(mode.internal);
            ଜାରି;
        }
        ଯଦି (mode.format != SDL_PIXELFORMAT_UNKNOWN) {
            ଯଦି (!SDL_AddFullscreenDisplayMode(display, &mode)) {
                SDL_free(mode.internal);
            }
        } ଅନ୍ୟଥା {
            SDL_free(mode.internal);
        }
    }

    WIN_ReleaseDXGIOutput(dxgi_output);

    ଫେରନ୍ତୁ true;
}

#ifdef DEBUG_MODES
ସ୍ଥିର ଶୂନ୍ୟ WIN_LogMonitor(SDL_VideoDevice *_this, HMONITOR mon)
{
    ଅଚଳ SDL_VideoData *vid_data = (ଅଚଳ SDL_VideoData *)_this->internal;
    MONITORINFOEX minfo;
    UINT xdpi = 0, ydpi = 0;
    ଅକ୍ଷର *name_utf8;

    ଯଦି (vid_data->GetDpiForMonitor) {
        vid_data->GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &xdpi, &ydpi);
    }

    SDL_zero(minfo);
    minfo.cbSize = ଆକାର(minfo);
    GetMonitorInfo(mon, (LPMONITORINFO)&minfo);

    name_utf8 = WIN_StringToUTF8(minfo.szDevice);

    SDL_Log("WIN_LogMonitor: monitor \"%s\": dpi: %d windows screen coordinates: %d, %d, %dx%d",
            name_utf8,
            xdpi,
            minfo.rcMonitor.ବାମ,
            minfo.rcMonitor.ଶୀର୍ଷ,
            minfo.rcMonitor.ଡାହାଣ - minfo.rcMonitor.ବାମ,
            minfo.rcMonitor.bottom - minfo.rcMonitor.ଶୀର୍ଷ);

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
    ଯଦି (mode->internal == display->desktop_mode.internal) {
#ifdef DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: resetting to original resolution");
#endif
        status = ChangeDisplaySettingsExW(displaydata->DeviceName, ଖାଲି, ଖାଲି, CDS_FULLSCREEN, ଖାଲି);
    } ଅନ୍ୟଥା {
#ifdef DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: changing to %dx%d pixels", data->DeviceMode.dmPelsWidth, data->DeviceMode.dmPelsHeight);
#endif
        status = ChangeDisplaySettingsExW(displaydata->DeviceName, &data->DeviceMode, ଖାଲି, CDS_FULLSCREEN, ଖାଲି);
    }
    ଯଦି (status != DISP_CHANGE_SUCCESSFUL) {
        ଅଚଳ ଅକ୍ଷର *reason = "Unknown reason";
        ବାଛ (status) {
        ସ୍ଥିତି DISP_CHANGE_BADFLAGS:
            reason = "DISP_CHANGE_BADFLAGS";
            ଭାଙ୍ଗ;
        ସ୍ଥିତି DISP_CHANGE_BADMODE:
            reason = "DISP_CHANGE_BADMODE";
            ଭାଙ୍ଗ;
        ସ୍ଥିତି DISP_CHANGE_BADPARAM:
            reason = "DISP_CHANGE_BADPARAM";
            ଭାଙ୍ଗ;
        ସ୍ଥିତି DISP_CHANGE_FAILED:
            reason = "DISP_CHANGE_FAILED";
            ଭାଙ୍ଗ;
        }
        ଫେରନ୍ତୁ SDL_SetError("ChangeDisplaySettingsEx() failed: %s", reason);
    }

#ifdef DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state after mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#endif

    EnumDisplaySettingsW(displaydata->DeviceName, ENUM_CURRENT_SETTINGS, &data->DeviceMode);
    WIN_UpdateDisplayMode(_this, displaydata->DeviceName, ENUM_CURRENT_SETTINGS, mode);
    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ WIN_RefreshDisplays(SDL_VideoDevice *_this)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    // Mark all displays as potentially invalid to detect
    // entries that have actually been removed
    ପାଇଁ (i = 0; i < _this->ଅଙ୍କ_displays; ++i) {
        SDL_DisplayData *internal = _this->displays[i]->internal;
        internal->state = DisplayRemoved;
    }

    // Enumerate displays to add any new ones and mark still
    // connected entries as valid
    WIN_AddDisplays(_this);

    // Delete any entries still marked as invalid, iterate
    // in reverse as each delete takes effect immediately
    ପାଇଁ (i = _this->ଅଙ୍କ_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DisplayData *internal = display->internal;
        ଯଦି (internal->state == DisplayRemoved) {
            SDL_DelVideoDisplay(display->id, true);
        }
    }

    // Send events for any newly added displays
    ପାଇଁ (i = 0; i < _this->ଅଙ୍କ_displays; ++i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DisplayData *internal = display->internal;
        ଯଦି (internal->state == DisplayAdded) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
        }
    }
}

ଶୂନ୍ୟ WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this)
{
    // This almost never happens, so just go ahead and send update events for all displays
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < _this->ଅଙ୍କ_displays; ++i) {
        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_CHANGED, 0, 0);
    }
}

ଶୂନ୍ୟ WIN_QuitModes(SDL_VideoDevice *_this)
{
    // All fullscreen windows should have restored modes by now
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
