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

#如果 defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

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
    如果 (index == ENUM_CURRENT_SETTINGS && (hdc = CreateDCW(deviceName, NULL, NULL, NULL)) != NULL) {
        char bmi_data[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)];
        LPBITMAPINFO bmi;
        HBITMAP hbm;

        SDL_zeroa(bmi_data);
        bmi = (LPBITMAPINFO)bmi_data;
        bmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

        hbm = CreateCompatibleBitmap(hdc, 1, 1);
        GetDIBits(hdc, hbm, 0, 1, NULL, bmi, DIB_RGB_COLORS);
        GetDIBits(hdc, hbm, 0, 1, NULL, bmi, DIB_RGB_COLORS);
        DeleteObject(hbm);
        DeleteDC(hdc);
        如果 (bmi->bmiHeader.biCompression == BI_BITFIELDS) {
            switch (*(Uint32 *)bmi->bmiColors) {
            case 0x00FF0000:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                break;
            case 0x000000FF:
                mode->format = SDL_PIXELFORMAT_XBGR8888;
                break;
            case 0xF800:
                mode->format = SDL_PIXELFORMAT_RGB565;
                break;
            case 0x7C00:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                break;
            }
        } 否则 如果 (bmi->bmiHeader.biCompression == BI_RGB) {
            如果 (bmi->bmiHeader.biBitCount == 24) {
                mode->format = SDL_PIXELFORMAT_RGB24;
            } 否则 如果 (bmi->bmiHeader.biBitCount == 8) {
                mode->format = SDL_PIXELFORMAT_INDEX8;
            } 否则 如果 (bmi->bmiHeader.biBitCount == 4) {
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
            }
        }
    } 否则 如果 (mode->format == SDL_PIXELFORMAT_UNKNOWN) {
        // FIXME: Can we tell what this will be?
        如果 ((data->DeviceMode.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL) {
            switch (data->DeviceMode.dmBitsPerPel) {
            case 32:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                break;
            case 24:
                mode->format = SDL_PIXELFORMAT_RGB24;
                break;
            case 16:
                mode->format = SDL_PIXELFORMAT_RGB565;
                break;
            case 15:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                break;
            case 8:
                mode->format = SDL_PIXELFORMAT_INDEX8;
                break;
            case 4:
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
                break;
            }
        }
    }
}

static void *WIN_GetDXGIOutput(SDL_VideoDevice *_this, const WCHAR *DeviceName)
{
    void *result = NULL;

#ifdef HAVE_DXGI_H
    const SDL_VideoData *videodata = (const SDL_VideoData *)_this->internal;
    整数 nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    如果 (!videodata->pDXGIFactory) {
        返回 NULL;
    }

    nAdapter = 0;
    当 (!result && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        当 (!result && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            如果 (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                如果 (SDL_wcscmp(outputDesc.DeviceName, DeviceName) == 0) {
                    result = pDXGIOutput;
                }
            }
            如果 (pDXGIOutput != result) {
                IDXGIOutput_Release(pDXGIOutput);
            }
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }
#endif
    返回 result;
}

static void WIN_ReleaseDXGIOutput(void *dxgi_output)
{
#ifdef HAVE_DXGI_H
    IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;

    如果 (pDXGIOutput) {
        IDXGIOutput_Release(pDXGIOutput);
    }
#endif
}

static SDL_DisplayOrientation WIN_GetNaturalOrientation(DEVMODEW *mode)
{
    整数 width = mode->dmPelsWidth;
    整数 height = mode->dmPelsHeight;

    // Use unrotated width/height to guess orientation
    如果 (mode->dmDisplayOrientation == DMDO_90 || mode->dmDisplayOrientation == DMDO_270) {
        整数 temp = width;
        width = height;
        height = temp;
    }

    如果 (width >= height) {
        返回 SDL_ORIENTATION_LANDSCAPE;
    } 否则 {
        返回 SDL_ORIENTATION_PORTRAIT;
    }
}

static SDL_DisplayOrientation WIN_GetDisplayOrientation(DEVMODEW *mode)
{
    如果 (WIN_GetNaturalOrientation(mode) == SDL_ORIENTATION_LANDSCAPE) {
        switch (mode->dmDisplayOrientation) {
        case DMDO_DEFAULT:
            返回 SDL_ORIENTATION_LANDSCAPE;
        case DMDO_90:
            返回 SDL_ORIENTATION_PORTRAIT;
        case DMDO_180:
            返回 SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        case DMDO_270:
            返回 SDL_ORIENTATION_PORTRAIT_FLIPPED;
        default:
            返回 SDL_ORIENTATION_UNKNOWN;
        }
    } 否则 {
        switch (mode->dmDisplayOrientation) {
        case DMDO_DEFAULT:
            返回 SDL_ORIENTATION_PORTRAIT;
        case DMDO_90:
            返回 SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        case DMDO_180:
            返回 SDL_ORIENTATION_PORTRAIT_FLIPPED;
        case DMDO_270:
            返回 SDL_ORIENTATION_LANDSCAPE;
        default:
            返回 SDL_ORIENTATION_UNKNOWN;
        }
    }
}

static void WIN_GetRefreshRate(void *dxgi_output, DEVMODEW *mode, 整数 *numerator, 整数 *denominator)
{
    // We're not currently using DXGI to query display modes, so fake NTSC timings
    switch (mode->dmDisplayFrequency) {
    case 119:
    case 59:
    case 29:
        *numerator = (mode->dmDisplayFrequency + 1) * 1000;
        *denominator = 1001;
        break;
    default:
        *numerator = mode->dmDisplayFrequency;
        *denominator = 1;
        break;
    }

#ifdef HAVE_DXGI_H
    如果 (dxgi_output) {
        IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;
        DXGI_MODE_DESC modeToMatch;
        DXGI_MODE_DESC closestMatch;

        SDL_zero(modeToMatch);
        modeToMatch.Width = mode->dmPelsWidth;
        modeToMatch.Height = mode->dmPelsHeight;
        modeToMatch.RefreshRate.Numerator = *numerator;
        modeToMatch.RefreshRate.Denominator = *denominator;
        modeToMatch.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        如果 (SUCCEEDED(IDXGIOutput_FindClosestMatchingMode(pDXGIOutput, &modeToMatch, &closestMatch, NULL))) {
            *numerator = closestMatch.RefreshRate.Numerator;
            *denominator = closestMatch.RefreshRate.Denominator;
        }
    }
#endif // HAVE_DXGI_H
}

static float WIN_GetContentScale(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    整数 dpi = 0;

    const SDL_VideoData *videodata = (const SDL_VideoData *)_this->internal;
    如果 (videodata->GetDpiForMonitor) {
        UINT hdpi_uint, vdpi_uint;
        如果 (videodata->GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
            dpi = (整数)hdpi_uint;
        }
    }
    如果 (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(NULL);
        如果 (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(NULL, hdc);
        }
    }
    如果 (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    返回 dpi / (float)USER_DEFAULT_SCREEN_DPI;
}

static bool WIN_GetDisplayMode(SDL_VideoDevice *_this, void *dxgi_output, HMONITOR hMonitor, LPCWSTR deviceName, DWORD index, SDL_DisplayMode *mode, SDL_DisplayOrientation *natural_orientation, SDL_DisplayOrientation *current_orientation)
{
    SDL_DisplayModeData *data;
    DEVMODEW devmode;

    devmode.dmSize = sizeof(devmode);
    devmode.dmDriverExtra = 0;
    如果 (!EnumDisplaySettingsW(deviceName, index, &devmode)) {
        返回 false;
    }

    data = (SDL_DisplayModeData *)SDL_malloc(sizeof(*data));
    如果 (!data) {
        返回 false;
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

    如果 (natural_orientation) {
        *natural_orientation = WIN_GetNaturalOrientation(&devmode);
    }
    如果 (current_orientation) {
        *current_orientation = WIN_GetDisplayOrientation(&devmode);
    }

    返回 true;
}

static char *WIN_GetDisplayNameVista(SDL_VideoData *videodata, const WCHAR *deviceName)
{
    DISPLAYCONFIG_PATH_INFO *paths = NULL;
    DISPLAYCONFIG_MODE_INFO *modes = NULL;
    char *result = NULL;
    UINT32 pathCount = 0;
    UINT32 modeCount = 0;
    UINT32 i;
    LONG rc;

    如果 (!videodata->GetDisplayConfigBufferSizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        返回 NULL;
    }

    do {
        rc = videodata->GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &pathCount, &modeCount);
        如果 (rc != ERROR_SUCCESS) {
            goto WIN_GetDisplayNameVista_failed;
        }

        SDL_free(paths);
        SDL_free(modes);

        paths = (DISPLAYCONFIG_PATH_INFO *)SDL_malloc(sizeof(DISPLAYCONFIG_PATH_INFO) * pathCount);
        modes = (DISPLAYCONFIG_MODE_INFO *)SDL_malloc(sizeof(DISPLAYCONFIG_MODE_INFO) * modeCount);
        如果 ((!paths) || (!modes)) {
            goto WIN_GetDisplayNameVista_failed;
        }

        rc = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &pathCount, paths, &modeCount, modes, 0);
    } 当 (rc == ERROR_INSUFFICIENT_BUFFER);

    如果 (rc == ERROR_SUCCESS) {
        为 (i = 0; i < pathCount; i++) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME sourceName;
            DISPLAYCONFIG_TARGET_DEVICE_NAME targetName;

            SDL_zero(sourceName);
            sourceName.header.adapterId = paths[i].targetInfo.adapterId;
            sourceName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            sourceName.header.size = sizeof(sourceName);
            sourceName.header.id = paths[i].sourceInfo.id;
            rc = videodata->DisplayConfigGetDeviceInfo(&sourceName.header);
            如果 (rc != ERROR_SUCCESS) {
                break;
            } 否则 如果 (SDL_wcscmp(deviceName, sourceName.viewGdiDeviceName) != 0) {
                continue;
            }

            SDL_zero(targetName);
            targetName.header.adapterId = paths[i].targetInfo.adapterId;
            targetName.header.id = paths[i].targetInfo.id;
            targetName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
            targetName.header.size = sizeof(targetName);
            rc = videodata->DisplayConfigGetDeviceInfo(&targetName.header);
            如果 (rc == ERROR_SUCCESS) {
                result = WIN_StringToUTF8W(targetName.monitorFriendlyDeviceName);
                /* if we got an empty string, treat it as failure so we'll fallback
                   to getting the generic name. */
                如果 (result && (*result == '\0')) {
                    SDL_free(result);
                    result = NULL;
                }
            }
            break;
        }
    }

    SDL_free(paths);
    SDL_free(modes);
    返回 result;

WIN_GetDisplayNameVista_failed:
    SDL_free(result);
    SDL_free(paths);
    SDL_free(modes);
    返回 NULL;
}

#ifdef HAVE_DXGI1_6_H
static bool WIN_GetMonitorDESC1(HMONITOR hMonitor, DXGI_OUTPUT_DESC1 *desc)
{
    typedef HRESULT (WINAPI *pfnCreateDXGIFactory1)(REFIID riid, void **ppFactory);
    pfnCreateDXGIFactory1 pCreateDXGIFactory1 = NULL;
    SDL_SharedObject *hDXGIMod = NULL;
    bool found = false;

    hDXGIMod = SDL_LoadObject("dxgi.dll");
    如果 (hDXGIMod) {
        pCreateDXGIFactory1 = (pfnCreateDXGIFactory1)SDL_LoadFunction(hDXGIMod, "CreateDXGIFactory1");
    }
    如果 (pCreateDXGIFactory1) {
        static const GUID SDL_IID_IDXGIFactory1 = { 0x770aae78, 0xf26f, 0x4dba, { 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 } };
        static const GUID SDL_IID_IDXGIOutput6 = { 0x068346e8, 0xaaec, 0x4b84, { 0xad, 0xd7, 0x13, 0x7f, 0x51, 0x3f, 0x77, 0xa1 } };
        IDXGIFactory1 *dxgiFactory;

        如果 (SUCCEEDED(pCreateDXGIFactory1(&SDL_IID_IDXGIFactory1, (void **)&dxgiFactory))) {
            IDXGIAdapter1 *dxgiAdapter;
            UINT adapter = 0;
            当 (!found && SUCCEEDED(IDXGIFactory1_EnumAdapters1(dxgiFactory, adapter, &dxgiAdapter))) {
                IDXGIOutput *dxgiOutput;
                UINT output = 0;
                当 (!found && SUCCEEDED(IDXGIAdapter1_EnumOutputs(dxgiAdapter, output, &dxgiOutput))) {
                    IDXGIOutput6 *dxgiOutput6;
                    如果 (SUCCEEDED(IDXGIOutput_QueryInterface(dxgiOutput, &SDL_IID_IDXGIOutput6, (void **)&dxgiOutput6))) {
                        如果 (SUCCEEDED(IDXGIOutput6_GetDesc1(dxgiOutput6, desc))) {
                            如果 (desc->Monitor == hMonitor) {
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
    如果 (hDXGIMod) {
        SDL_UnloadObject(hDXGIMod);
    }
    返回 found;
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

    如果 (!videodata->GetDisplayConfigBufferSizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        返回 false;
    }

    SDL_zero(view_info);
    view_info.cbSize = sizeof(view_info);
    如果 (!GetMonitorInfoW(hMonitor, (MONITORINFO *)&view_info)) {
        goto done;
    }

    do {
        如果 (videodata->GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &num_path_array_elements, &num_mode_info_array_elements) != ERROR_SUCCESS) {
            SDL_free(path_infos);
            SDL_free(mode_infos);
            返回 false;
        }

        new_path_infos = (DISPLAYCONFIG_PATH_INFO *)SDL_realloc(path_infos, num_path_array_elements * sizeof(*path_infos));
        如果 (!new_path_infos) {
            goto done;
        }
        path_infos = new_path_infos;

        new_mode_infos = (DISPLAYCONFIG_MODE_INFO *)SDL_realloc(mode_infos, num_mode_info_array_elements * sizeof(*mode_infos));
        如果 (!new_mode_infos) {
            goto done;
        }
        mode_infos = new_mode_infos;

        result = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &num_path_array_elements, path_infos, &num_mode_info_array_elements, mode_infos, NULL);

    } 当 (result == ERROR_INSUFFICIENT_BUFFER);

    如果 (result == ERROR_SUCCESS) {
        为 (i = 0; i < num_path_array_elements; ++i) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME device_name;

            SDL_zero(device_name);
            device_name.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            device_name.header.size = sizeof(device_name);
            device_name.header.adapterId = path_infos[i].sourceInfo.adapterId;
            device_name.header.id = path_infos[i].sourceInfo.id;
            如果 (videodata->DisplayConfigGetDeviceInfo(&device_name.header) == ERROR_SUCCESS) {
                如果 (SDL_wcscmp(view_info.szDevice, device_name.viewGdiDeviceName) == 0) {
                    SDL_copyp(path_info, &path_infos[i]);
                    found = true;
                    break;
                }
            }
        }
    }

done:
    SDL_free(path_infos);
    SDL_free(mode_infos);

    返回 found;
}

static float WIN_GetSDRWhitePoint(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    DISPLAYCONFIG_PATH_INFO path_info;
    SDL_VideoData *videodata = _this->internal;
    float SDR_white_level = 1.0f;

    如果 (WIN_GetMonitorPathInfo(videodata, hMonitor, &path_info)) {
        /* workarounds for https://github.com/libsdl-org/SDL/issues/11193 */
        struct SDL_DISPLAYCONFIG_SDR_WHITE_LEVEL {
          DISPLAYCONFIG_DEVICE_INFO_HEADER header;
          ULONG SDRWhiteLevel;
        } white_level;
        #define DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL 11

        SDL_zero(white_level);
        white_level.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
        white_level.header.size = sizeof(white_level);
        white_level.header.adapterId = path_info.targetInfo.adapterId;
        white_level.header.id = path_info.targetInfo.id;
        // WIN_GetMonitorPathInfo() succeeded: DisplayConfigGetDeviceInfo is not NULL
        如果 (videodata->DisplayConfigGetDeviceInfo(&white_level.header) == ERROR_SUCCESS &&
            white_level.SDRWhiteLevel > 0) {
            SDR_white_level = (white_level.SDRWhiteLevel / 1000.0f);
        }
    }
    返回 SDR_white_level;
}

static void WIN_GetHDRProperties(SDL_VideoDevice *_this, HMONITOR hMonitor, SDL_HDROutputProperties *HDR)
{
    DXGI_OUTPUT_DESC1 desc;

    SDL_zerop(HDR);

    如果 (WIN_GetMonitorDESC1(hMonitor, &desc)) {
        如果 (desc.ColorSpace == DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020) {
            HDR->SDR_white_level = WIN_GetSDRWhitePoint(_this, hMonitor);
            HDR->HDR_headroom = (desc.MaxLuminance / SCRGB_NITS) / HDR->SDR_white_level;
        }
    }
}
#endif // HAVE_DXGI1_6_H

static void WIN_AddDisplay(SDL_VideoDevice *_this, HMONITOR hMonitor, const MONITORINFOEXW *info, 整数 *display_index)
{
    整数 i, index = *display_index;
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
    如果 (!found) {
        返回;
    }

    // Prevent adding duplicate displays. Do this after we know the display is
    // ready to be added to allow any displays that we can't fully query to be
    // removed
    为 (i = 0; i < _this->num_displays; ++i) {
        SDL_DisplayData *internal = _this->displays[i]->internal;
        如果 (SDL_wcscmp(internal->DeviceName, info->szDevice) == 0) {
            bool moved = (index != i);
            bool changed_bounds = false;

            如果 (internal->state != DisplayRemoved) {
                // We've already enumerated this display, don't move it
                goto cleanup;
            }

            如果 (index >= _this->num_displays) {
                // This should never happen due to the check above, but just in case...
                goto cleanup;
            }

            如果 (moved) {
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

            如果 (!_this->setting_display_mode) {
                SDL_VideoDisplay *existing_display = _this->displays[i];
                SDL_Rect bounds;

                SDL_ResetFullscreenDisplayModes(existing_display);
                SDL_SetDesktopDisplayMode(existing_display, &mode);
                // The mode is owned by the video subsystem
                mode.internal = NULL;
                如果 (WIN_GetDisplayBounds(_this, existing_display, &bounds) &&
                    SDL_memcmp(&internal->bounds, &bounds, sizeof(bounds)) != 0) {
                    changed_bounds = true;
                    SDL_copyp(&internal->bounds, &bounds);
                }
                如果 (moved || changed_bounds) {
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

    displaydata = (SDL_DisplayData *)SDL_calloc(1, sizeof(*displaydata));
    如果 (!displaydata) {
        goto cleanup;
    }
    SDL_memcpy(displaydata->DeviceName, info->szDevice, sizeof(displaydata->DeviceName));
    displaydata->MonitorHandle = hMonitor;
    displaydata->state = DisplayAdded;

    SDL_zero(display);
    display.name = WIN_GetDisplayNameVista(_this->internal, info->szDevice);
    如果 (!display.name) {
        DISPLAY_DEVICEW device;
        SDL_zero(device);
        device.cb = sizeof(device);
        如果 (EnumDisplayDevicesW(info->szDevice, 0, &device, 0)) {
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
    如果 (displayID) {
        // The mode is owned by the video subsystem
        mode.internal = NULL;

        SDL_PropertiesID props = SDL_GetDisplayProperties(displayID);
        SDL_SetPointerProperty(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_POINTER, hMonitor);
    } 否则 {
        SDL_free(displaydata);
    }
    SDL_free(display.name);

done:
    *display_index += 1;

cleanup:
    SDL_free(mode.internal);
}

typedef struct _WIN_AddDisplaysData
{
    SDL_VideoDevice *video_device;
    整数 display_index;
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
    info.cbSize = sizeof(info);

    如果 (GetMonitorInfoW(hMonitor, (LPMONITORINFO)&info) != 0) {
        const bool is_primary = ((info.dwFlags & MONITORINFOF_PRIMARY) == MONITORINFOF_PRIMARY);

        如果 (is_primary == data->want_primary) {
            WIN_AddDisplay(data->video_device, hMonitor, &info, &data->display_index);
        }
    }

    // continue enumeration
    返回 TRUE;
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

    如果 (_this->num_displays == 0) {
        返回 SDL_SetError("No displays available");
    }
    返回 true;
}

bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    const SDL_DisplayData *data = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cbSize = sizeof(MONITORINFO);
    rc = GetMonitorInfo(data->MonitorHandle, &minfo);

    如果 (!rc) {
        返回 SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcMonitor.left;
    rect->y = minfo.rcMonitor.top;
    rect->w = minfo.rcMonitor.right - minfo.rcMonitor.left;
    rect->h = minfo.rcMonitor.bottom - minfo.rcMonitor.top;

    返回 true;
}

bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    const SDL_DisplayData *data = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cbSize = sizeof(MONITORINFO);
    rc = GetMonitorInfo(data->MonitorHandle, &minfo);

    如果 (!rc) {
        返回 SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcWork.left;
    rect->y = minfo.rcWork.top;
    rect->w = minfo.rcWork.right - minfo.rcWork.left;
    rect->h = minfo.rcWork.bottom - minfo.rcWork.top;

    返回 true;
}

bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_DisplayData *data = display->internal;
    void *dxgi_output;
    DWORD i;
    SDL_DisplayMode mode;

    dxgi_output = WIN_GetDXGIOutput(_this, data->DeviceName);

    // Make sure we add the current mode to the list in case it's a custom mode that doesn't enumerate
    为 (i = ENUM_CURRENT_SETTINGS; ; ++i) {
        如果 (!WIN_GetDisplayMode(_this, dxgi_output, data->MonitorHandle, data->DeviceName, i, &mode, NULL, NULL)) {
            break;
        }
        如果 (SDL_ISPIXELFORMAT_INDEXED(mode.format)) {
            // We don't support palettized modes now
            SDL_free(mode.internal);
            continue;
        }
        如果 (mode.format != SDL_PIXELFORMAT_UNKNOWN) {
            如果 (!SDL_AddFullscreenDisplayMode(display, &mode)) {
                SDL_free(mode.internal);
            }
        } 否则 {
            SDL_free(mode.internal);
        }
    }

    WIN_ReleaseDXGIOutput(dxgi_output);

    返回 true;
}

#ifdef DEBUG_MODES
static void WIN_LogMonitor(SDL_VideoDevice *_this, HMONITOR mon)
{
    const SDL_VideoData *vid_data = (const SDL_VideoData *)_this->internal;
    MONITORINFOEX minfo;
    UINT xdpi = 0, ydpi = 0;
    char *name_utf8;

    如果 (vid_data->GetDpiForMonitor) {
        vid_data->GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &xdpi, &ydpi);
    }

    SDL_zero(minfo);
    minfo.cbSize = sizeof(minfo);
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
    如果 (mode->internal == display->desktop_mode.internal) {
#ifdef DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: resetting to original resolution");
#endif
        status = ChangeDisplaySettingsExW(displaydata->DeviceName, NULL, NULL, CDS_FULLSCREEN, NULL);
    } 否则 {
#ifdef DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: changing to %dx%d pixels", data->DeviceMode.dmPelsWidth, data->DeviceMode.dmPelsHeight);
#endif
        status = ChangeDisplaySettingsExW(displaydata->DeviceName, &data->DeviceMode, NULL, CDS_FULLSCREEN, NULL);
    }
    如果 (status != DISP_CHANGE_SUCCESSFUL) {
        const char *reason = "Unknown reason";
        switch (status) {
        case DISP_CHANGE_BADFLAGS:
            reason = "DISP_CHANGE_BADFLAGS";
            break;
        case DISP_CHANGE_BADMODE:
            reason = "DISP_CHANGE_BADMODE";
            break;
        case DISP_CHANGE_BADPARAM:
            reason = "DISP_CHANGE_BADPARAM";
            break;
        case DISP_CHANGE_FAILED:
            reason = "DISP_CHANGE_FAILED";
            break;
        }
        返回 SDL_SetError("ChangeDisplaySettingsEx() failed: %s", reason);
    }

#ifdef DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state after mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#endif

    EnumDisplaySettingsW(displaydata->DeviceName, ENUM_CURRENT_SETTINGS, &data->DeviceMode);
    WIN_UpdateDisplayMode(_this, displaydata->DeviceName, ENUM_CURRENT_SETTINGS, mode);
    返回 true;
}

void WIN_RefreshDisplays(SDL_VideoDevice *_this)
{
    整数 i;

    // Mark all displays as potentially invalid to detect
    // entries that have actually been removed
    为 (i = 0; i < _this->num_displays; ++i) {
        SDL_DisplayData *internal = _this->displays[i]->internal;
        internal->state = DisplayRemoved;
    }

    // Enumerate displays to add any new ones and mark still
    // connected entries as valid
    WIN_AddDisplays(_this);

    // Delete any entries still marked as invalid, iterate
    // in reverse as each delete takes effect immediately
    为 (i = _this->num_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DisplayData *internal = display->internal;
        如果 (internal->state == DisplayRemoved) {
            SDL_DelVideoDisplay(display->id, true);
        }
    }

    // Send events for any newly added displays
    为 (i = 0; i < _this->num_displays; ++i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DisplayData *internal = display->internal;
        如果 (internal->state == DisplayAdded) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
        }
    }
}

void WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this)
{
    // This almost never happens, so just go ahead and send update events for all displays
    为 (整数 i = 0; i < _this->num_displays; ++i) {
        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_CHANGED, 0, 0);
    }
}

void WIN_QuitModes(SDL_VideoDevice *_this)
{
    // All fullscreen windows should have restored modes by now
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
