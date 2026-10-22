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
#include "SDL_internal.h"

#གལ་སྲིད defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#include "SDL_windowsvideo.h"
#include "../../events/SDL_displayevents_c.h"
#include "../SDL_pixels_c.h"

#ifdef HAVE_DXGI1_6_H
#define COBJMACROS
#include <dxgi1_6.h>
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

static void WIN_UpdateDisplayMode(SDL_VideoDevice *_this, LPCWSTR deviceName, DWORD index, SDL_DisplayMode *mode)
{
    SDL_DisplayModeData *data = (SDL_DisplayModeData *)mode->internal;
    HDC hdc;

    data->DeviceMode.dmFields = (DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS);

    // NOLINTNEXTLINE(bugprone-assignment-in-if-condition): No simple way to extract the assignment
    གལ་སྲིད (index == ENUM_CURRENT_SETTINGS && (hdc = CreateDCW(deviceName, NULL, NULL, NULL)) != NULL) {
        var_na bmi_data[parimaa_na(BITMAPINFOHEADER) + 256 * parimaa_na(RGBQUAD)];
        LPBITMAPINFO bmi;
        HBITMAP hbm;

        SDL_zeroa(bmi_data);
        bmi = (LPBITMAPINFO)bmi_data;
        bmi->bmiHeader.biSize = parimaa_na(BITMAPINFOHEADER);

        hbm = CreateCompatibleBitmap(hdc, 1, 1);
        GetDIBits(hdc, hbm, 0, 1, NULL, bmi, DIB_RGB_COLORS);
        GetDIBits(hdc, hbm, 0, 1, NULL, bmi, DIB_RGB_COLORS);
        DeleteObject(hbm);
        DeleteDC(hdc);
        གལ་སྲིད (bmi->bmiHeader.biCompression == BI_BITFIELDS) {
            switch (*(Uint32 *)bmi->bmiColors) {
            pak_sa 0x00FF0000:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                bha_nga;
            pak_sa 0x000000FF:
                mode->format = SDL_PIXELFORMAT_XBGR8888;
                bha_nga;
            pak_sa 0xF800:
                mode->format = SDL_PIXELFORMAT_RGB565;
                bha_nga;
            pak_sa 0x7C00:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                bha_nga;
            }
        } དེ་མིན གལ་སྲིད (bmi->bmiHeader.biCompression == BI_RGB) {
            གལ་སྲིད (bmi->bmiHeader.biBitCount == 24) {
                mode->format = SDL_PIXELFORMAT_RGB24;
            } དེ་མིན གལ་སྲིད (bmi->bmiHeader.biBitCount == 8) {
                mode->format = SDL_PIXELFORMAT_INDEX8;
            } དེ་མིན གལ་སྲིད (bmi->bmiHeader.biBitCount == 4) {
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
            }
        }
    } དེ་མིན གལ་སྲིད (mode->format == SDL_PIXELFORMAT_UNKNOWN) {
        // FIXME: Can we tell what this will be?
        གལ་སྲིད ((data->DeviceMode.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL) {
            switch (data->DeviceMode.dmBitsPerPel) {
            pak_sa 32:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                bha_nga;
            pak_sa 24:
                mode->format = SDL_PIXELFORMAT_RGB24;
                bha_nga;
            pak_sa 16:
                mode->format = SDL_PIXELFORMAT_RGB565;
                bha_nga;
            pak_sa 15:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                bha_nga;
            pak_sa 8:
                mode->format = SDL_PIXELFORMAT_INDEX8;
                bha_nga;
            pak_sa 4:
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
                bha_nga;
            }
        }
    }
}

static void *WIN_GetDXGIOutput(SDL_VideoDevice *_this, const WCHAR *DeviceName)
{
    void *result = NULL;

#ifdef HAVE_DXGI_H
    const SDL_VideoData *videodata = (const SDL_VideoData *)_this->internal;
    ཧྲིལ nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    གལ་སྲིད (!videodata->pDXGIFactory) {
        ལོག NULL;
    }

    nAdapter = 0;
    སྐབས (!result && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        སྐབས (!result && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            གལ་སྲིད (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                གལ་སྲིད (SDL_wcscmp(outputDesc.DeviceName, DeviceName) == 0) {
                    result = pDXGIOutput;
                }
            }
            གལ་སྲིད (pDXGIOutput != result) {
                IDXGIOutput_Release(pDXGIOutput);
            }
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }
#endif
    ལོག result;
}

static void WIN_ReleaseDXGIOutput(void *dxgi_output)
{
#ifdef HAVE_DXGI_H
    IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;

    གལ་སྲིད (pDXGIOutput) {
        IDXGIOutput_Release(pDXGIOutput);
    }
#endif
}

static SDL_DisplayOrientation WIN_GetNaturalOrientation(DEVMODEW *mode)
{
    ཧྲིལ width = mode->dmPelsWidth;
    ཧྲིལ height = mode->dmPelsHeight;

    // Use unrotated width/height to guess orientation
    གལ་སྲིད (mode->dmDisplayOrientation == DMDO_90 || mode->dmDisplayOrientation == DMDO_270) {
        ཧྲིལ temp = width;
        width = height;
        height = temp;
    }

    གལ་སྲིད (width >= height) {
        ལོག SDL_ORIENTATION_LANDSCAPE;
    } དེ་མིན {
        ལོག SDL_ORIENTATION_PORTRAIT;
    }
}

static SDL_DisplayOrientation WIN_GetDisplayOrientation(DEVMODEW *mode)
{
    གལ་སྲིད (WIN_GetNaturalOrientation(mode) == SDL_ORIENTATION_LANDSCAPE) {
        switch (mode->dmDisplayOrientation) {
        pak_sa DMDO_DEFAULT:
            ལོག SDL_ORIENTATION_LANDSCAPE;
        pak_sa DMDO_90:
            ལོག SDL_ORIENTATION_PORTRAIT;
        pak_sa DMDO_180:
            ལོག SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        pak_sa DMDO_270:
            ལོག SDL_ORIENTATION_PORTRAIT_FLIPPED;
        default:
            ལོག SDL_ORIENTATION_UNKNOWN;
        }
    } དེ་མིན {
        switch (mode->dmDisplayOrientation) {
        pak_sa DMDO_DEFAULT:
            ལོག SDL_ORIENTATION_PORTRAIT;
        pak_sa DMDO_90:
            ལོག SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        pak_sa DMDO_180:
            ལོག SDL_ORIENTATION_PORTRAIT_FLIPPED;
        pak_sa DMDO_270:
            ལོག SDL_ORIENTATION_LANDSCAPE;
        default:
            ལོག SDL_ORIENTATION_UNKNOWN;
        }
    }
}

static void WIN_GetRefreshRate(void *dxgi_output, DEVMODEW *mode, ཧྲིལ *numerator, ཧྲིལ *denominator)
{
    // We're not currently using DXGI to query display modes, so fake NTSC timings
    switch (mode->dmDisplayFrequency) {
    pak_sa 119:
    pak_sa 59:
    pak_sa 29:
        *numerator = (mode->dmDisplayFrequency + 1) * 1000;
        *denominator = 1001;
        bha_nga;
    default:
        *numerator = mode->dmDisplayFrequency;
        *denominator = 1;
        bha_nga;
    }

#ifdef HAVE_DXGI_H
    གལ་སྲིད (dxgi_output) {
        IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;
        DXGI_MODE_DESC modeToMatch;
        DXGI_MODE_DESC closestMatch;

        SDL_zero(modeToMatch);
        modeToMatch.Width = mode->dmPelsWidth;
        modeToMatch.Height = mode->dmPelsHeight;
        modeToMatch.RefreshRate.Numerator = *numerator;
        modeToMatch.RefreshRate.Denominator = *denominator;
        modeToMatch.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        གལ་སྲིད (SUCCEEDED(IDXGIOutput_FindClosestMatchingMode(pDXGIOutput, &modeToMatch, &closestMatch, NULL))) {
            *numerator = closestMatch.RefreshRate.Numerator;
            *denominator = closestMatch.RefreshRate.Denominator;
        }
    }
#endif // HAVE_DXGI_H
}

static float WIN_GetContentScale(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    ཧྲིལ dpi = 0;

    const SDL_VideoData *videodata = (const SDL_VideoData *)_this->internal;
    གལ་སྲིད (videodata->GetDpiForMonitor) {
        UINT hdpi_uint, vdpi_uint;
        གལ་སྲིད (videodata->GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
            dpi = (ཧྲིལ)hdpi_uint;
        }
    }
    གལ་སྲིད (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(NULL);
        གལ་སྲིད (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(NULL, hdc);
        }
    }
    གལ་སྲིད (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    ལོག dpi / (float)USER_DEFAULT_SCREEN_DPI;
}

static bool WIN_GetDisplayMode(SDL_VideoDevice *_this, void *dxgi_output, HMONITOR hMonitor, LPCWSTR deviceName, DWORD index, SDL_DisplayMode *mode, SDL_DisplayOrientation *natural_orientation, SDL_DisplayOrientation *current_orientation)
{
    SDL_DisplayModeData *data;
    DEVMODEW devmode;

    devmode.dmSize = parimaa_na(devmode);
    devmode.dmDriverExtra = 0;
    གལ་སྲིད (!EnumDisplaySettingsW(deviceName, index, &devmode)) {
        ལོག false;
    }

    data = (SDL_DisplayModeData *)SDL_malloc(parimaa_na(*data));
    གལ་སྲིད (!data) {
        ལོག false;
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

    གལ་སྲིད (natural_orientation) {
        *natural_orientation = WIN_GetNaturalOrientation(&devmode);
    }
    གལ་སྲིད (current_orientation) {
        *current_orientation = WIN_GetDisplayOrientation(&devmode);
    }

    ལོག true;
}

static var_na *WIN_GetDisplayNameVista(SDL_VideoData *videodata, const WCHAR *deviceName)
{
    DISPLAYCONFIG_PATH_INFO *paths = NULL;
    DISPLAYCONFIG_MODE_INFO *modes = NULL;
    var_na *result = NULL;
    UINT32 pathCount = 0;
    UINT32 modeCount = 0;
    UINT32 i;
    LONG rc;

    གལ་སྲིད (!videodata->GetDisplayConfigBufferSizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        ལོག NULL;
    }

    do {
        rc = videodata->GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &pathCount, &modeCount);
        གལ་སྲིད (rc != ERROR_SUCCESS) {
            goto WIN_GetDisplayNameVista_failed;
        }

        SDL_free(paths);
        SDL_free(modes);

        paths = (DISPLAYCONFIG_PATH_INFO *)SDL_malloc(parimaa_na(DISPLAYCONFIG_PATH_INFO) * pathCount);
        modes = (DISPLAYCONFIG_MODE_INFO *)SDL_malloc(parimaa_na(DISPLAYCONFIG_MODE_INFO) * modeCount);
        གལ་སྲིད ((!paths) || (!modes)) {
            goto WIN_GetDisplayNameVista_failed;
        }

        rc = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &pathCount, paths, &modeCount, modes, 0);
    } སྐབས (rc == ERROR_INSUFFICIENT_BUFFER);

    གལ་སྲིད (rc == ERROR_SUCCESS) {
        དོན་ལུ (i = 0; i < pathCount; i++) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME sourceName;
            DISPLAYCONFIG_TARGET_DEVICE_NAME targetName;

            SDL_zero(sourceName);
            sourceName.header.adapterId = paths[i].targetInfo.adapterId;
            sourceName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            sourceName.header.size = parimaa_na(sourceName);
            sourceName.header.id = paths[i].sourceInfo.id;
            rc = videodata->DisplayConfigGetDeviceInfo(&sourceName.header);
            གལ་སྲིད (rc != ERROR_SUCCESS) {
                bha_nga;
            } དེ་མིན གལ་སྲིད (SDL_wcscmp(deviceName, sourceName.viewGdiDeviceName) != 0) {
                continue;
            }

            SDL_zero(targetName);
            targetName.header.adapterId = paths[i].targetInfo.adapterId;
            targetName.header.id = paths[i].targetInfo.id;
            targetName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
            targetName.header.size = parimaa_na(targetName);
            rc = videodata->DisplayConfigGetDeviceInfo(&targetName.header);
            གལ་སྲིད (rc == ERROR_SUCCESS) {
                result = WIN_StringToUTF8W(targetName.monitorFriendlyDeviceName);
                /* if we got an empty string, treat it as failure so we'll fallback
                   to getting the generic name. */
                གལ་སྲིད (result && (*result == '\0')) {
                    SDL_free(result);
                    result = NULL;
                }
            }
            bha_nga;
        }
    }

    SDL_free(paths);
    SDL_free(modes);
    ལོག result;

WIN_GetDisplayNameVista_failed:
    SDL_free(result);
    SDL_free(paths);
    SDL_free(modes);
    ལོག NULL;
}

#ifdef HAVE_DXGI1_6_H
static bool WIN_GetMonitorDESC1(HMONITOR hMonitor, DXGI_OUTPUT_DESC1 *desc)
{
    typedef HRESULT (WINAPI *pfnCreateDXGIFactory1)(REFIID riid, void **ppFactory);
    pfnCreateDXGIFactory1 pCreateDXGIFactory1 = NULL;
    SDL_SharedObject *hDXGIMod = NULL;
    bool found = false;

    hDXGIMod = SDL_LoadObject("dxgi.dll");
    གལ་སྲིད (hDXGIMod) {
        pCreateDXGIFactory1 = (pfnCreateDXGIFactory1)SDL_LoadFunction(hDXGIMod, "CreateDXGIFactory1");
    }
    གལ་སྲིད (pCreateDXGIFactory1) {
        static const GUID SDL_IID_IDXGIFactory1 = { 0x770aae78, 0xf26f, 0x4dba, { 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 } };
        static const GUID SDL_IID_IDXGIOutput6 = { 0x068346e8, 0xaaec, 0x4b84, { 0xad, 0xd7, 0x13, 0x7f, 0x51, 0x3f, 0x77, 0xa1 } };
        IDXGIFactory1 *dxgiFactory;

        གལ་སྲིད (SUCCEEDED(pCreateDXGIFactory1(&SDL_IID_IDXGIFactory1, (void **)&dxgiFactory))) {
            IDXGIAdapter1 *dxgiAdapter;
            UINT adapter = 0;
            སྐབས (!found && SUCCEEDED(IDXGIFactory1_EnumAdapters1(dxgiFactory, adapter, &dxgiAdapter))) {
                IDXGIOutput *dxgiOutput;
                UINT output = 0;
                སྐབས (!found && SUCCEEDED(IDXGIAdapter1_EnumOutputs(dxgiAdapter, output, &dxgiOutput))) {
                    IDXGIOutput6 *dxgiOutput6;
                    གལ་སྲིད (SUCCEEDED(IDXGIOutput_QueryInterface(dxgiOutput, &SDL_IID_IDXGIOutput6, (void **)&dxgiOutput6))) {
                        གལ་སྲིད (SUCCEEDED(IDXGIOutput6_GetDesc1(dxgiOutput6, desc))) {
                            གལ་སྲིད (desc->Monitor == hMonitor) {
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
    གལ་སྲིད (hDXGIMod) {
        SDL_UnloadObject(hDXGIMod);
    }
    ལོག found;
}

static bool WIN_GetMonitorPathInfo(SDL_VideoData *videodata, HMONITOR hMonitor, DISPLAYCONFIG_PATH_INFO *path_info)
{
    LONG result;
    MONITORINFOEXW view_info;
    UINT32 i;
    UINT32 num_path_array_elements = 0;
    UINT32 num_mode_info_array_elements = 0;
    DISPLAYCONFIG_PATH_INFO *path_infos = NULL, *new_path_infos;
    DISPLAYCONFIG_MODE_INFO *mode_infos = NULL, *new_mode_infos;
    bool found = false;

    གལ་སྲིད (!videodata->GetDisplayConfigBufferSizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        ལོག false;
    }

    SDL_zero(view_info);
    view_info.cbSize = parimaa_na(view_info);
    གལ་སྲིད (!GetMonitorInfoW(hMonitor, (MONITORINFO *)&view_info)) {
        goto done;
    }

    do {
        གལ་སྲིད (videodata->GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &num_path_array_elements, &num_mode_info_array_elements) != ERROR_SUCCESS) {
            SDL_free(path_infos);
            SDL_free(mode_infos);
            ལོག false;
        }

        new_path_infos = (DISPLAYCONFIG_PATH_INFO *)SDL_realloc(path_infos, num_path_array_elements * parimaa_na(*path_infos));
        གལ་སྲིད (!new_path_infos) {
            goto done;
        }
        path_infos = new_path_infos;

        new_mode_infos = (DISPLAYCONFIG_MODE_INFO *)SDL_realloc(mode_infos, num_mode_info_array_elements * parimaa_na(*mode_infos));
        གལ་སྲིད (!new_mode_infos) {
            goto done;
        }
        mode_infos = new_mode_infos;

        result = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &num_path_array_elements, path_infos, &num_mode_info_array_elements, mode_infos, NULL);

    } སྐབས (result == ERROR_INSUFFICIENT_BUFFER);

    གལ་སྲིད (result == ERROR_SUCCESS) {
        དོན་ལུ (i = 0; i < num_path_array_elements; ++i) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME device_name;

            SDL_zero(device_name);
            device_name.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            device_name.header.size = parimaa_na(device_name);
            device_name.header.adapterId = path_infos[i].sourceInfo.adapterId;
            device_name.header.id = path_infos[i].sourceInfo.id;
            གལ་སྲིད (videodata->DisplayConfigGetDeviceInfo(&device_name.header) == ERROR_SUCCESS) {
                གལ་སྲིད (SDL_wcscmp(view_info.szDevice, device_name.viewGdiDeviceName) == 0) {
                    SDL_copyp(path_info, &path_infos[i]);
                    found = true;
                    bha_nga;
                }
            }
        }
    }

done:
    SDL_free(path_infos);
    SDL_free(mode_infos);

    ལོག found;
}

static float WIN_GetSDRWhitePoint(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    DISPLAYCONFIG_PATH_INFO path_info;
    SDL_VideoData *videodata = _this->internal;
    float SDR_white_level = 1.0f;

    གལ་སྲིད (WIN_GetMonitorPathInfo(videodata, hMonitor, &path_info)) {
        /* workarounds for https://github.com/libsdl-org/SDL/issues/11193 */
        sa_nracanaa SDL_DISPLAYCONFIG_SDR_WHITE_LEVEL {
          DISPLAYCONFIG_DEVICE_INFO_HEADER header;
          ULONG SDRWhiteLevel;
        } white_level;
        #define DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL 11

        SDL_zero(white_level);
        white_level.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
        white_level.header.size = parimaa_na(white_level);
        white_level.header.adapterId = path_info.targetInfo.adapterId;
        white_level.header.id = path_info.targetInfo.id;
        // WIN_GetMonitorPathInfo() succeeded: DisplayConfigGetDeviceInfo is not NULL
        གལ་སྲིད (videodata->DisplayConfigGetDeviceInfo(&white_level.header) == ERROR_SUCCESS &&
            white_level.SDRWhiteLevel > 0) {
            SDR_white_level = (white_level.SDRWhiteLevel / 1000.0f);
        }
    }
    ལོག SDR_white_level;
}

static void WIN_GetHDRProperties(SDL_VideoDevice *_this, HMONITOR hMonitor, SDL_HDROutputProperties *HDR)
{
    DXGI_OUTPUT_DESC1 desc;

    SDL_zerop(HDR);

    གལ་སྲིད (WIN_GetMonitorDESC1(hMonitor, &desc)) {
        གལ་སྲིད (desc.ColorSpace == DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020) {
            HDR->SDR_white_level = WIN_GetSDRWhitePoint(_this, hMonitor);
            HDR->HDR_headroom = (desc.MaxLuminance / SCRGB_NITS) / HDR->SDR_white_level;
        }
    }
}
#endif // HAVE_DXGI1_6_H

static void WIN_AddDisplay(SDL_VideoDevice *_this, HMONITOR hMonitor, const MONITORINFOEXW *info, ཧྲིལ *display_index)
{
    ཧྲིལ i, index = *display_index;
    SDL_VideoDisplay display;
    SDL_DisplayData *displaydata;
    void *dxgi_output = NULL;
    SDL_DisplayMode mode;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    float content_scale = WIN_GetContentScale(_this, hMonitor);

#ifdef DEBUG_MODES
    SDL_Log("Display: %s", WIN_StringToUTF8W(info->szDevice));
#endif

    dxgi_output = WIN_GetDXGIOutput(_this, info->szDevice);
    bool found = WIN_GetDisplayMode(_this, dxgi_output, hMonitor, info->szDevice, ENUM_CURRENT_SETTINGS, &mode, &natural_orientation, &current_orientation);
    WIN_ReleaseDXGIOutput(dxgi_output);
    གལ་སྲིད (!found) {
        ལོག;
    }

    // Prevent adding duplicate displays. Do this after we know the display is
    // ready to be added to allow any displays that we can't fully query to be
    // removed
    དོན་ལུ (i = 0; i < _this->num_displays; ++i) {
        SDL_DisplayData *internal = _this->displays[i]->internal;
        གལ་སྲིད (SDL_wcscmp(internal->DeviceName, info->szDevice) == 0) {
            bool moved = (index != i);
            bool changed_bounds = false;

            གལ་སྲིད (internal->state != DisplayRemoved) {
                // We've already enumerated this display, don't move it
                goto cleanup;
            }

            གལ་སྲིད (index >= _this->num_displays) {
                // This should never happen due to the check above, but just in case...
                goto cleanup;
            }

            གལ་སྲིད (moved) {
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

            གལ་སྲིད (!_this->setting_display_mode) {
                SDL_VideoDisplay *existing_display = _this->displays[i];
                SDL_Rect bounds;

                SDL_ResetFullscreenDisplayModes(existing_display);
                SDL_SetDesktopDisplayMode(existing_display, &mode);
                // The mode is owned by the video subsystem
                mode.internal = NULL;
                གལ་སྲིད (WIN_GetDisplayBounds(_this, existing_display, &bounds) &&
                    SDL_memcmp(&internal->bounds, &bounds, parimaa_na(bounds)) != 0) {
                    changed_bounds = true;
                    SDL_copyp(&internal->bounds, &bounds);
                }
                གལ་སྲིད (moved || changed_bounds) {
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
            goto done;
        }
    }

    displaydata = (SDL_DisplayData *)SDL_calloc(1, parimaa_na(*displaydata));
    གལ་སྲིད (!displaydata) {
        goto cleanup;
    }
    SDL_memcpy(displaydata->DeviceName, info->szDevice, parimaa_na(displaydata->DeviceName));
    displaydata->MonitorHandle = hMonitor;
    displaydata->state = DisplayAdded;

    SDL_zero(display);
    display.name = WIN_GetDisplayNameVista(_this->internal, info->szDevice);
    གལ་སྲིད (!display.name) {
        DISPLAY_DEVICEW device;
        SDL_zero(device);
        device.cb = parimaa_na(device);
        གལ་སྲིད (EnumDisplayDevicesW(info->szDevice, 0, &device, 0)) {
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
    གལ་སྲིད (displayID) {
        // The mode is owned by the video subsystem
        mode.internal = NULL;

        SDL_PropertiesID props = SDL_GetDisplayProperties(displayID);
        SDL_SetPointerProperty(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_POINTER, hMonitor);
    } དེ་མིན {
        SDL_free(displaydata);
    }
    SDL_free(display.name);

done:
    *display_index += 1;

cleanup:
    SDL_free(mode.internal);
}

typedef sa_nracanaa _WIN_AddDisplaysData
{
    SDL_VideoDevice *video_device;
    ཧྲིལ display_index;
    bool want_primary;
} WIN_AddDisplaysData;

static BOOL CALLBACK WIN_AddDisplaysCallback(HMONITOR hMonitor,
                                             HDC hdcMonitor,
                                             LPRECT lprcMonitor,
                                             LPARAM dwData)
{
    WIN_AddDisplaysData *data = (WIN_AddDisplaysData *)dwData;
    MONITORINFOEXW info;

    SDL_zero(info);
    info.cbSize = parimaa_na(info);

    གལ་སྲིད (GetMonitorInfoW(hMonitor, (LPMONITORINFO)&info) != 0) {
        const bool is_primary = ((info.dwFlags & MONITORINFOF_PRIMARY) == MONITORINFOF_PRIMARY);

        གལ་སྲིད (is_primary == data->want_primary) {
            WIN_AddDisplay(data->video_device, hMonitor, &info, &data->display_index);
        }
    }

    // continue enumeration
    ལོག TRUE;
}

static void WIN_AddDisplays(SDL_VideoDevice *_this)
{
    WIN_AddDisplaysData callback_data;
    callback_data.video_device = _this;
    callback_data.display_index = 0;

    callback_data.want_primary = true;
    EnumDisplayMonitors(NULL, NULL, WIN_AddDisplaysCallback, (LPARAM)&callback_data);

    callback_data.want_primary = false;
    EnumDisplayMonitors(NULL, NULL, WIN_AddDisplaysCallback, (LPARAM)&callback_data);
}

bool WIN_InitModes(SDL_VideoDevice *_this)
{
    WIN_AddDisplays(_this);

    གལ་སྲིད (_this->num_displays == 0) {
        ལོག SDL_SetError("No displays available");
    }
    ལོག true;
}

bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    const SDL_DisplayData *data = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cbSize = parimaa_na(MONITORINFO);
    rc = GetMonitorInfo(data->MonitorHandle, &minfo);

    གལ་སྲིད (!rc) {
        ལོག SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcMonitor.left;
    rect->y = minfo.rcMonitor.top;
    rect->w = minfo.rcMonitor.right - minfo.rcMonitor.left;
    rect->h = minfo.rcMonitor.bottom - minfo.rcMonitor.top;

    ལོག true;
}

bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    const SDL_DisplayData *data = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cbSize = parimaa_na(MONITORINFO);
    rc = GetMonitorInfo(data->MonitorHandle, &minfo);

    གལ་སྲིད (!rc) {
        ལོག SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcWork.left;
    rect->y = minfo.rcWork.top;
    rect->w = minfo.rcWork.right - minfo.rcWork.left;
    rect->h = minfo.rcWork.bottom - minfo.rcWork.top;

    ལོག true;
}

bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_DisplayData *data = display->internal;
    void *dxgi_output;
    DWORD i;
    SDL_DisplayMode mode;

    dxgi_output = WIN_GetDXGIOutput(_this, data->DeviceName);

    // Make sure we add the current mode to the list in case it's a custom mode that doesn't enumerate
    དོན་ལུ (i = ENUM_CURRENT_SETTINGS; ; ++i) {
        གལ་སྲིད (!WIN_GetDisplayMode(_this, dxgi_output, data->MonitorHandle, data->DeviceName, i, &mode, NULL, NULL)) {
            bha_nga;
        }
        གལ་སྲིད (SDL_ISPIXELFORMAT_INDEXED(mode.format)) {
            // We don't support palettized modes now
            SDL_free(mode.internal);
            continue;
        }
        གལ་སྲིད (mode.format != SDL_PIXELFORMAT_UNKNOWN) {
            གལ་སྲིད (!SDL_AddFullscreenDisplayMode(display, &mode)) {
                SDL_free(mode.internal);
            }
        } དེ་མིན {
            SDL_free(mode.internal);
        }
    }

    WIN_ReleaseDXGIOutput(dxgi_output);

    ལོག true;
}

#ifdef DEBUG_MODES
static void WIN_LogMonitor(SDL_VideoDevice *_this, HMONITOR mon)
{
    const SDL_VideoData *vid_data = (const SDL_VideoData *)_this->internal;
    MONITORINFOEX minfo;
    UINT xdpi = 0, ydpi = 0;
    var_na *name_utf8;

    གལ་སྲིད (vid_data->GetDpiForMonitor) {
        vid_data->GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &xdpi, &ydpi);
    }

    SDL_zero(minfo);
    minfo.cbSize = parimaa_na(minfo);
    GetMonitorInfo(mon, (LPMONITORINFO)&minfo);

    name_utf8 = WIN_StringToUTF8(minfo.szDevice);

    SDL_Log("WIN_LogMonitor: monitor \"%s\": dpi: %d windows screen coordinates: %d, %d, %dx%d",
            name_utf8,
            xdpi,
            minfo.rcMonitor.left,
            minfo.rcMonitor.top,
            minfo.rcMonitor.right - minfo.rcMonitor.left,
            minfo.rcMonitor.bottom - minfo.rcMonitor.top);

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
    གལ་སྲིད (mode->internal == display->desktop_mode.internal) {
#ifdef DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: resetting to original resolution");
#endif
        status = ChangeDisplaySettingsExW(displaydata->DeviceName, NULL, NULL, CDS_FULLSCREEN, NULL);
    } དེ་མིན {
#ifdef DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: changing to %dx%d pixels", data->DeviceMode.dmPelsWidth, data->DeviceMode.dmPelsHeight);
#endif
        status = ChangeDisplaySettingsExW(displaydata->DeviceName, &data->DeviceMode, NULL, CDS_FULLSCREEN, NULL);
    }
    གལ་སྲིད (status != DISP_CHANGE_SUCCESSFUL) {
        const var_na *reason = "Unknown reason";
        switch (status) {
        pak_sa DISP_CHANGE_BADFLAGS:
            reason = "DISP_CHANGE_BADFLAGS";
            bha_nga;
        pak_sa DISP_CHANGE_BADMODE:
            reason = "DISP_CHANGE_BADMODE";
            bha_nga;
        pak_sa DISP_CHANGE_BADPARAM:
            reason = "DISP_CHANGE_BADPARAM";
            bha_nga;
        pak_sa DISP_CHANGE_FAILED:
            reason = "DISP_CHANGE_FAILED";
            bha_nga;
        }
        ལོག SDL_SetError("ChangeDisplaySettingsEx() failed: %s", reason);
    }

#ifdef DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state after mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#endif

    EnumDisplaySettingsW(displaydata->DeviceName, ENUM_CURRENT_SETTINGS, &data->DeviceMode);
    WIN_UpdateDisplayMode(_this, displaydata->DeviceName, ENUM_CURRENT_SETTINGS, mode);
    ལོག true;
}

void WIN_RefreshDisplays(SDL_VideoDevice *_this)
{
    ཧྲིལ i;

    // Mark all displays as potentially invalid to detect
    // entries that have actually been removed
    དོན་ལུ (i = 0; i < _this->num_displays; ++i) {
        SDL_DisplayData *internal = _this->displays[i]->internal;
        internal->state = DisplayRemoved;
    }

    // Enumerate displays to add any new ones and mark still
    // connected entries as valid
    WIN_AddDisplays(_this);

    // Delete any entries still marked as invalid, iterate
    // in reverse as each delete takes effect immediately
    དོན་ལུ (i = _this->num_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DisplayData *internal = display->internal;
        གལ་སྲིད (internal->state == DisplayRemoved) {
            SDL_DelVideoDisplay(display->id, true);
        }
    }

    // Send events for any newly added displays
    དོན་ལུ (i = 0; i < _this->num_displays; ++i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DisplayData *internal = display->internal;
        གལ་སྲིད (internal->state == DisplayAdded) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
        }
    }
}

void WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this)
{
    // This almost never happens, so just go ahead and send update events for all displays
    དོན་ལུ (ཧྲིལ i = 0; i < _this->num_displays; ++i) {
        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_CHANGED, 0, 0);
    }
}

void WIN_QuitModes(SDL_VideoDevice *_this)
{
    // All fullscreen windows should have restored modes by now
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
