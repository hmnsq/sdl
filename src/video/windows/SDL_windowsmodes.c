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
#ضمن "SDL_internal.h"

#إذا defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ضمن "SDL_windowsvideo.h"
#ضمن "../../events/SDL_displayevents_c.h"
#ضمن "../SDL_pixels_c.h"

#ifdef HAVE_DXGI1_6_H
#define COBJMACROS
#ضمن <dxgi1_6.h>
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

ساكن فراغ WIN_UpdateDisplayMode(SDL_VideoDevice *_this, LPCWSTR deviceName, DWORD index, SDL_DisplayMode *mode)
{
    SDL_DisplayModeData *data = (SDL_DisplayModeData *)mode->internal;
    HDC hdc;

    data->DeviceMode.dmFields = (DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS);

    // NOLINTNEXTLINE(bugprone-assignment-in-if-condition): No simple way to extract the assignment
    إذا (index == ENUM_CURRENT_SETTINGS && (hdc = CreateDCW(deviceName, عدم, عدم, عدم)) != عدم) {
        حرف bmi_data[حجم(BITMAPINFOHEADER) + 256 * حجم(RGBQUAD)];
        LPBITMAPINFO bmi;
        HBITMAP hbm;

        SDL_zeroa(bmi_data);
        bmi = (LPBITMAPINFO)bmi_data;
        bmi->bmiHeader.biSize = حجم(BITMAPINFOHEADER);

        hbm = CreateCompatibleBitmap(hdc, 1, 1);
        GetDIBits(hdc, hbm, 0, 1, عدم, bmi, DIB_RGB_COLORS);
        GetDIBits(hdc, hbm, 0, 1, عدم, bmi, DIB_RGB_COLORS);
        DeleteObject(hbm);
        DeleteDC(hdc);
        إذا (bmi->bmiHeader.biCompression == BI_BITFIELDS) {
            بدل (*(Uint32 *)bmi->bmiColors) {
            حالة 0x00FF0000:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                اكسر;
            حالة 0x000000FF:
                mode->format = SDL_PIXELFORMAT_XBGR8888;
                اكسر;
            حالة 0xF800:
                mode->format = SDL_PIXELFORMAT_RGB565;
                اكسر;
            حالة 0x7C00:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                اكسر;
            }
        } وإلا إذا (bmi->bmiHeader.biCompression == BI_RGB) {
            إذا (bmi->bmiHeader.bi_Bit_سانى == 24) {
                mode->format = SDL_PIXELFORMAT_RGB24;
            } وإلا إذا (bmi->bmiHeader.bi_Bit_سانى == 8) {
                mode->format = SDL_PIXELFORMAT_INDEX8;
            } وإلا إذا (bmi->bmiHeader.bi_Bit_سانى == 4) {
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
            }
        }
    } وإلا إذا (mode->format == SDL_PIXELFORMAT_UNKNOWN) {
        // FIXME: Can we tell what this will be?
        إذا ((data->DeviceMode.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL) {
            بدل (data->DeviceMode.dmBitsPerPel) {
            حالة 32:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                اكسر;
            حالة 24:
                mode->format = SDL_PIXELFORMAT_RGB24;
                اكسر;
            حالة 16:
                mode->format = SDL_PIXELFORMAT_RGB565;
                اكسر;
            حالة 15:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                اكسر;
            حالة 8:
                mode->format = SDL_PIXELFORMAT_INDEX8;
                اكسر;
            حالة 4:
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
                اكسر;
            }
        }
    }
}

ساكن فراغ *WIN_GetDXGIOutput(SDL_VideoDevice *_this, ثابت WCHAR *DeviceName)
{
    فراغ *result = عدم;

#ifdef HAVE_DXGI_H
    ثابت SDL_VideoData *videodata = (ثابت SDL_VideoData *)_this->internal;
    صحيح nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    إذا (!videodata->pDXGIFactory) {
        أرجع عدم;
    }

    nAdapter = 0;
    طالما (!result && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        طالما (!result && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            إذا (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                إذا (SDL_wcscmp(outputDesc.DeviceName, DeviceName) == 0) {
                    result = pDXGIOutput;
                }
            }
            إذا (pDXGIOutput != result) {
                IDXGIOutput_Release(pDXGIOutput);
            }
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }
#endif
    أرجع result;
}

ساكن فراغ WIN_ReleaseDXGIOutput(فراغ *dxgi_output)
{
#ifdef HAVE_DXGI_H
    IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;

    إذا (pDXGIOutput) {
        IDXGIOutput_Release(pDXGIOutput);
    }
#endif
}

ساكن SDL_DisplayOrientation WIN_GetNaturalOrientation(DEVMODEW *mode)
{
    صحيح width = mode->dmPelsWidth;
    صحيح height = mode->dmPelsHeight;

    // Use unrotated width/height to guess orientation
    إذا (mode->dmDisplayOrientation == DMDO_90 || mode->dmDisplayOrientation == DMDO_270) {
        صحيح temp = width;
        width = height;
        height = temp;
    }

    إذا (width >= height) {
        أرجع SDL_ORIENTATION_LANDSCAPE;
    } وإلا {
        أرجع SDL_ORIENTATION_PORTRAIT;
    }
}

ساكن SDL_DisplayOrientation WIN_GetDisplayOrientation(DEVMODEW *mode)
{
    إذا (WIN_GetNaturalOrientation(mode) == SDL_ORIENTATION_LANDSCAPE) {
        بدل (mode->dmDisplayOrientation) {
        حالة DMDO_DEFAULT:
            أرجع SDL_ORIENTATION_LANDSCAPE;
        حالة DMDO_90:
            أرجع SDL_ORIENTATION_PORTRAIT;
        حالة DMDO_180:
            أرجع SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        حالة DMDO_270:
            أرجع SDL_ORIENTATION_PORTRAIT_FLIPPED;
        افتراضي:
            أرجع SDL_ORIENTATION_UNKNOWN;
        }
    } وإلا {
        بدل (mode->dmDisplayOrientation) {
        حالة DMDO_DEFAULT:
            أرجع SDL_ORIENTATION_PORTRAIT;
        حالة DMDO_90:
            أرجع SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        حالة DMDO_180:
            أرجع SDL_ORIENTATION_PORTRAIT_FLIPPED;
        حالة DMDO_270:
            أرجع SDL_ORIENTATION_LANDSCAPE;
        افتراضي:
            أرجع SDL_ORIENTATION_UNKNOWN;
        }
    }
}

ساكن فراغ WIN_GetRefreshRate(فراغ *dxgi_output, DEVMODEW *mode, صحيح *numerator, صحيح *denominator)
{
    // We're not currently using DXGI to query display modes, so fake NTSC timings
    بدل (mode->dmDisplayFrequency) {
    حالة 119:
    حالة 59:
    حالة 29:
        *numerator = (mode->dmDisplayFrequency + 1) * 1000;
        *denominator = 1001;
        اكسر;
    افتراضي:
        *numerator = mode->dmDisplayFrequency;
        *denominator = 1;
        اكسر;
    }

#ifdef HAVE_DXGI_H
    إذا (dxgi_output) {
        IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;
        DXGI_MODE_DESC modeToMatch;
        DXGI_MODE_DESC closestMatch;

        SDL_zero(modeToMatch);
        modeToMatch.Width = mode->dmPelsWidth;
        modeToMatch.Height = mode->dmPelsHeight;
        modeToMatch.RefreshRate.Numerator = *numerator;
        modeToMatch.RefreshRate.Denominator = *denominator;
        modeToMatch.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        إذا (SUCCEEDED(IDXGIOutput_FindClosestMatchingMode(pDXGIOutput, &modeToMatch, &closestMatch, عدم))) {
            *numerator = closestMatch.RefreshRate.Numerator;
            *denominator = closestMatch.RefreshRate.Denominator;
        }
    }
#endif // HAVE_DXGI_H
}

ساكن عائم WIN_GetContentScale(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    صحيح dpi = 0;

    ثابت SDL_VideoData *videodata = (ثابت SDL_VideoData *)_this->internal;
    إذا (videodata->GetDpiForMonitor) {
        UINT hdpi_uint, vdpi_uint;
        إذا (videodata->GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
            dpi = (صحيح)hdpi_uint;
        }
    }
    إذا (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(عدم);
        إذا (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(عدم, hdc);
        }
    }
    إذا (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    أرجع dpi / (عائم)USER_DEFAULT_SCREEN_DPI;
}

ساكن bool WIN_GetDisplayMode(SDL_VideoDevice *_this, فراغ *dxgi_output, HMONITOR hMonitor, LPCWSTR deviceName, DWORD index, SDL_DisplayMode *mode, SDL_DisplayOrientation *natural_orientation, SDL_DisplayOrientation *current_orientation)
{
    SDL_DisplayModeData *data;
    DEVMODEW devmode;

    devmode.dmSize = حجم(devmode);
    devmode.dmDriverExtra = 0;
    إذا (!EnumDisplaySettingsW(deviceName, index, &devmode)) {
        أرجع false;
    }

    data = (SDL_DisplayModeData *)SDL_malloc(حجم(*data));
    إذا (!data) {
        أرجع false;
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

    إذا (natural_orientation) {
        *natural_orientation = WIN_GetNaturalOrientation(&devmode);
    }
    إذا (current_orientation) {
        *current_orientation = WIN_GetDisplayOrientation(&devmode);
    }

    أرجع true;
}

ساكن حرف *WIN_GetDisplayNameVista(SDL_VideoData *videodata, ثابت WCHAR *deviceName)
{
    DISPLAYCONFIG_PATH_INFO *paths = عدم;
    DISPLAYCONFIG_MODE_INFO *modes = عدم;
    حرف *result = عدم;
    UINT32 path_سانى_2 = 0;
    UINT32 mode_سانى_2 = 0;
    UINT32 i;
    LONG rc;

    إذا (!videodata->GetDisplayConfigBufferSizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        أرجع عدم;
    }

    افعل {
        rc = videodata->GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &path_سانى_2, &mode_سانى_2);
        إذا (rc != ERROR_SUCCESS) {
            اذهب WIN_GetDisplayNameVista_failed;
        }

        SDL_free(paths);
        SDL_free(modes);

        paths = (DISPLAYCONFIG_PATH_INFO *)SDL_malloc(حجم(DISPLAYCONFIG_PATH_INFO) * path_سانى_2);
        modes = (DISPLAYCONFIG_MODE_INFO *)SDL_malloc(حجم(DISPLAYCONFIG_MODE_INFO) * mode_سانى_2);
        إذا ((!paths) || (!modes)) {
            اذهب WIN_GetDisplayNameVista_failed;
        }

        rc = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &path_سانى_2, paths, &mode_سانى_2, modes, 0);
    } طالما (rc == ERROR_INSUFFICIENT_BUFFER);

    إذا (rc == ERROR_SUCCESS) {
        لكل (i = 0; i < path_سانى_2; i++) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME sourceName;
            DISPLAYCONFIG_TARGET_DEVICE_NAME targetName;

            SDL_zero(sourceName);
            sourceName.header.adapterId = paths[i].targetInfo.adapterId;
            sourceName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            sourceName.header.size = حجم(sourceName);
            sourceName.header.id = paths[i].sourceInfo.id;
            rc = videodata->DisplayConfigGetDeviceInfo(&sourceName.header);
            إذا (rc != ERROR_SUCCESS) {
                اكسر;
            } وإلا إذا (SDL_wcscmp(deviceName, sourceName.viewGdiDeviceName) != 0) {
                استمر;
            }

            SDL_zero(targetName);
            targetName.header.adapterId = paths[i].targetInfo.adapterId;
            targetName.header.id = paths[i].targetInfo.id;
            targetName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
            targetName.header.size = حجم(targetName);
            rc = videodata->DisplayConfigGetDeviceInfo(&targetName.header);
            إذا (rc == ERROR_SUCCESS) {
                result = WIN_StringToUTF8W(targetName.monitorFriendlyDeviceName);
                /* if we got an empty string, treat it as failure so we'll fallback
                   to getting the generic name. */
                إذا (result && (*result == '\0')) {
                    SDL_free(result);
                    result = عدم;
                }
            }
            اكسر;
        }
    }

    SDL_free(paths);
    SDL_free(modes);
    أرجع result;

WIN_GetDisplayNameVista_failed:
    SDL_free(result);
    SDL_free(paths);
    SDL_free(modes);
    أرجع عدم;
}

#ifdef HAVE_DXGI1_6_H
ساكن bool WIN_GetMonitorDESC1(HMONITOR hMonitor, DXGI_OUTPUT_DESC1 *desc)
{
    تعريفنوع HRESULT (WINAPI *pfnCreateDXGIFactory1)(REFIID riid, فراغ **ppFactory);
    pfnCreateDXGIFactory1 pCreateDXGIFactory1 = عدم;
    SDL_SharedObject *hDXGIMod = عدم;
    bool found = false;

    hDXGIMod = SDL_LoadObject("dxgi.dll");
    إذا (hDXGIMod) {
        pCreateDXGIFactory1 = (pfnCreateDXGIFactory1)SDL_LoadFunction(hDXGIMod, "CreateDXGIFactory1");
    }
    إذا (pCreateDXGIFactory1) {
        ساكن ثابت GUID SDL_IID_IDXGIFactory1 = { 0x770aae78, 0xf26f, 0x4dba, { 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 } };
        ساكن ثابت GUID SDL_IID_IDXGIOutput6 = { 0x068346e8, 0xaaec, 0x4b84, { 0xad, 0xd7, 0x13, 0x7f, 0x51, 0x3f, 0x77, 0xa1 } };
        IDXGIFactory1 *dxgiFactory;

        إذا (SUCCEEDED(pCreateDXGIFactory1(&SDL_IID_IDXGIFactory1, (فراغ **)&dxgiFactory))) {
            IDXGIAdapter1 *dxgiAdapter;
            UINT adapter = 0;
            طالما (!found && SUCCEEDED(IDXGIFactory1_EnumAdapters1(dxgiFactory, adapter, &dxgiAdapter))) {
                IDXGIOutput *dxgiOutput;
                UINT output = 0;
                طالما (!found && SUCCEEDED(IDXGIAdapter1_EnumOutputs(dxgiAdapter, output, &dxgiOutput))) {
                    IDXGIOutput6 *dxgiOutput6;
                    إذا (SUCCEEDED(IDXGIOutput_QueryInterface(dxgiOutput, &SDL_IID_IDXGIOutput6, (فراغ **)&dxgiOutput6))) {
                        إذا (SUCCEEDED(IDXGIOutput6_GetDesc1(dxgiOutput6, desc))) {
                            إذا (desc->Monitor == hMonitor) {
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
    إذا (hDXGIMod) {
        SDL_UnloadObject(hDXGIMod);
    }
    أرجع found;
}

ساكن bool WIN_GetMonitorPathInfo(SDL_VideoData *videodata, HMONITOR hMonitor, DISPLAYCONFIG_PATH_INFO *path_info)
{
    LONG result;
    MONITORINFOEXW view_info;
    UINT32 i;
    UINT32 رەقەم_path_array_elements = 0;
    UINT32 رەقەم_mode_info_array_elements = 0;
    DISPLAYCONFIG_PATH_INFO *path_infos = عدم, *new_path_infos;
    DISPLAYCONFIG_MODE_INFO *mode_infos = عدم, *new_mode_infos;
    bool found = false;

    إذا (!videodata->GetDisplayConfigBufferSizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        أرجع false;
    }

    SDL_zero(view_info);
    view_info.cbSize = حجم(view_info);
    إذا (!GetMonitorInfoW(hMonitor, (MONITORINFO *)&view_info)) {
        اذهب done;
    }

    افعل {
        إذا (videodata->GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &رەقەم_path_array_elements, &رەقەم_mode_info_array_elements) != ERROR_SUCCESS) {
            SDL_free(path_infos);
            SDL_free(mode_infos);
            أرجع false;
        }

        new_path_infos = (DISPLAYCONFIG_PATH_INFO *)SDL_realloc(path_infos, رەقەم_path_array_elements * حجم(*path_infos));
        إذا (!new_path_infos) {
            اذهب done;
        }
        path_infos = new_path_infos;

        new_mode_infos = (DISPLAYCONFIG_MODE_INFO *)SDL_realloc(mode_infos, رەقەم_mode_info_array_elements * حجم(*mode_infos));
        إذا (!new_mode_infos) {
            اذهب done;
        }
        mode_infos = new_mode_infos;

        result = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &رەقەم_path_array_elements, path_infos, &رەقەم_mode_info_array_elements, mode_infos, عدم);

    } طالما (result == ERROR_INSUFFICIENT_BUFFER);

    إذا (result == ERROR_SUCCESS) {
        لكل (i = 0; i < رەقەم_path_array_elements; ++i) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME device_name;

            SDL_zero(device_name);
            device_name.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            device_name.header.size = حجم(device_name);
            device_name.header.adapterId = path_infos[i].sourceInfo.adapterId;
            device_name.header.id = path_infos[i].sourceInfo.id;
            إذا (videodata->DisplayConfigGetDeviceInfo(&device_name.header) == ERROR_SUCCESS) {
                إذا (SDL_wcscmp(view_info.szDevice, device_name.viewGdiDeviceName) == 0) {
                    SDL_copyp(path_info, &path_infos[i]);
                    found = true;
                    اكسر;
                }
            }
        }
    }

done:
    SDL_free(path_infos);
    SDL_free(mode_infos);

    أرجع found;
}

ساكن عائم WIN_GetSDRWhitePoint(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    DISPLAYCONFIG_PATH_INFO path_info;
    SDL_VideoData *videodata = _this->internal;
    عائم SDR_white_level = 1.0f;

    إذا (WIN_GetMonitorPathInfo(videodata, hMonitor, &path_info)) {
        /* workarounds for https://github.com/libsdl-org/SDL/issues/11193 */
        بنية SDL_DISPLAYCONFIG_SDR_WHITE_LEVEL {
          DISPLAYCONFIG_DEVICE_INFO_HEADER header;
          ULONG SDRWhiteLevel;
        } white_level;
        #define DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL 11

        SDL_zero(white_level);
        white_level.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
        white_level.header.size = حجم(white_level);
        white_level.header.adapterId = path_info.targetInfo.adapterId;
        white_level.header.id = path_info.targetInfo.id;
        // WIN_GetMonitorPathInfo() succeeded: DisplayConfigGetDeviceInfo is not NULL
        إذا (videodata->DisplayConfigGetDeviceInfo(&white_level.header) == ERROR_SUCCESS &&
            white_level.SDRWhiteLevel > 0) {
            SDR_white_level = (white_level.SDRWhiteLevel / 1000.0f);
        }
    }
    أرجع SDR_white_level;
}

ساكن فراغ WIN_GetHDRProperties(SDL_VideoDevice *_this, HMONITOR hMonitor, SDL_HDROutputProperties *HDR)
{
    DXGI_OUTPUT_DESC1 desc;

    SDL_zerop(HDR);

    إذا (WIN_GetMonitorDESC1(hMonitor, &desc)) {
        إذا (desc.ColorSpace == DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020) {
            HDR->SDR_white_level = WIN_GetSDRWhitePoint(_this, hMonitor);
            HDR->HDR_headroom = (desc.MaxLuminance / SCRGB_NITS) / HDR->SDR_white_level;
        }
    }
}
#endif // HAVE_DXGI1_6_H

ساكن فراغ WIN_AddDisplay(SDL_VideoDevice *_this, HMONITOR hMonitor, ثابت MONITORINFOEXW *info, صحيح *display_index)
{
    صحيح i, index = *display_index;
    SDL_VideoDisplay display;
    SDL_DisplayData *displaydata;
    فراغ *dxgi_output = عدم;
    SDL_DisplayMode mode;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    عائم content_scale = WIN_GetContentScale(_this, hMonitor);

#ifdef DEBUG_MODES
    SDL_Log("Display: %s", WIN_StringToUTF8W(info->szDevice));
#endif

    dxgi_output = WIN_GetDXGIOutput(_this, info->szDevice);
    bool found = WIN_GetDisplayMode(_this, dxgi_output, hMonitor, info->szDevice, ENUM_CURRENT_SETTINGS, &mode, &natural_orientation, &current_orientation);
    WIN_ReleaseDXGIOutput(dxgi_output);
    إذا (!found) {
        أرجع;
    }

    // Prevent adding duplicate displays. Do this after we know the display is
    // ready to be added to allow any displays that we can't fully query to be
    // removed
    لكل (i = 0; i < _this->رەقەم_displays; ++i) {
        SDL_DisplayData *internal = _this->displays[i]->internal;
        إذا (SDL_wcscmp(internal->DeviceName, info->szDevice) == 0) {
            bool moved = (index != i);
            bool changed_bounds = false;

            إذا (internal->state != DisplayRemoved) {
                // We've already enumerated this display, don't move it
                اذهب cleanup;
            }

            إذا (index >= _this->رەقەم_displays) {
                // This should never happen due to the check above, but just in case...
                اذهب cleanup;
            }

            إذا (moved) {
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

            إذا (!_this->setting_display_mode) {
                SDL_VideoDisplay *existing_display = _this->displays[i];
                SDL_Rect bounds;

                SDL_ResetFullscreenDisplayModes(existing_display);
                SDL_SetDesktopDisplayMode(existing_display, &mode);
                // The mode is owned by the video subsystem
                mode.internal = عدم;
                إذا (WIN_GetDisplayBounds(_this, existing_display, &bounds) &&
                    SDL_memcmp(&internal->bounds, &bounds, حجم(bounds)) != 0) {
                    changed_bounds = true;
                    SDL_copyp(&internal->bounds, &bounds);
                }
                إذا (moved || changed_bounds) {
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
            اذهب done;
        }
    }

    displaydata = (SDL_DisplayData *)SDL_calloc(1, حجم(*displaydata));
    إذا (!displaydata) {
        اذهب cleanup;
    }
    SDL_memcpy(displaydata->DeviceName, info->szDevice, حجم(displaydata->DeviceName));
    displaydata->MonitorHandle = hMonitor;
    displaydata->state = DisplayAdded;

    SDL_zero(display);
    display.name = WIN_GetDisplayNameVista(_this->internal, info->szDevice);
    إذا (!display.name) {
        DISPLAY_DEVICEW device;
        SDL_zero(device);
        device.cb = حجم(device);
        إذا (EnumDisplayDevicesW(info->szDevice, 0, &device, 0)) {
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
    إذا (displayID) {
        // The mode is owned by the video subsystem
        mode.internal = عدم;

        SDL_PropertiesID props = SDL_GetDisplayProperties(displayID);
        SDL_SetPointerProperty(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_POINTER, hMonitor);
    } وإلا {
        SDL_free(displaydata);
    }
    SDL_free(display.name);

done:
    *display_index += 1;

cleanup:
    SDL_free(mode.internal);
}

تعريفنوع بنية _WIN_AddDisplaysData
{
    SDL_VideoDevice *video_device;
    صحيح display_index;
    bool want_primary;
} WIN_AddDisplaysData;

ساكن BOOL CALLBACK WIN_AddDisplaysCallback(HMONITOR hMonitor,
                                             HDC hdcMonitor,
                                             LPRECT lprcMonitor,
                                             LPARAM dwData)
{
    WIN_AddDisplaysData *data = (WIN_AddDisplaysData *)dwData;
    MONITORINFOEXW info;

    SDL_zero(info);
    info.cbSize = حجم(info);

    إذا (GetMonitorInfoW(hMonitor, (LPMONITORINFO)&info) != 0) {
        ثابت bool is_primary = ((info.dwFlags & MONITORINFOF_PRIMARY) == MONITORINFOF_PRIMARY);

        إذا (is_primary == data->want_primary) {
            WIN_AddDisplay(data->video_device, hMonitor, &info, &data->display_index);
        }
    }

    // continue enumeration
    أرجع TRUE;
}

ساكن فراغ WIN_AddDisplays(SDL_VideoDevice *_this)
{
    WIN_AddDisplaysData callback_data;
    callback_data.video_device = _this;
    callback_data.display_index = 0;

    callback_data.want_primary = true;
    EnumDisplayMonitors(عدم, عدم, WIN_AddDisplaysCallback, (LPARAM)&callback_data);

    callback_data.want_primary = false;
    EnumDisplayMonitors(عدم, عدم, WIN_AddDisplaysCallback, (LPARAM)&callback_data);
}

bool WIN_InitModes(SDL_VideoDevice *_this)
{
    WIN_AddDisplays(_this);

    إذا (_this->رەقەم_displays == 0) {
        أرجع SDL_SetError("No displays available");
    }
    أرجع true;
}

bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ثابت SDL_DisplayData *data = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cbSize = حجم(MONITORINFO);
    rc = GetMonitorInfo(data->MonitorHandle, &minfo);

    إذا (!rc) {
        أرجع SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcMonitor.سول;
    rect->y = minfo.rcMonitor.چوققا;
    rect->w = minfo.rcMonitor.ئوڭ - minfo.rcMonitor.سول;
    rect->h = minfo.rcMonitor.bottom - minfo.rcMonitor.چوققا;

    أرجع true;
}

bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ثابت SDL_DisplayData *data = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cbSize = حجم(MONITORINFO);
    rc = GetMonitorInfo(data->MonitorHandle, &minfo);

    إذا (!rc) {
        أرجع SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcWork.سول;
    rect->y = minfo.rcWork.چوققا;
    rect->w = minfo.rcWork.ئوڭ - minfo.rcWork.سول;
    rect->h = minfo.rcWork.bottom - minfo.rcWork.چوققا;

    أرجع true;
}

bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_DisplayData *data = display->internal;
    فراغ *dxgi_output;
    DWORD i;
    SDL_DisplayMode mode;

    dxgi_output = WIN_GetDXGIOutput(_this, data->DeviceName);

    // Make sure we add the current mode to the list in case it's a custom mode that doesn't enumerate
    لكل (i = ENUM_CURRENT_SETTINGS; ; ++i) {
        إذا (!WIN_GetDisplayMode(_this, dxgi_output, data->MonitorHandle, data->DeviceName, i, &mode, عدم, عدم)) {
            اكسر;
        }
        إذا (SDL_ISPIXELFORMAT_INDEXED(mode.format)) {
            // We don't support palettized modes now
            SDL_free(mode.internal);
            استمر;
        }
        إذا (mode.format != SDL_PIXELFORMAT_UNKNOWN) {
            إذا (!SDL_AddFullscreenDisplayMode(display, &mode)) {
                SDL_free(mode.internal);
            }
        } وإلا {
            SDL_free(mode.internal);
        }
    }

    WIN_ReleaseDXGIOutput(dxgi_output);

    أرجع true;
}

#ifdef DEBUG_MODES
ساكن فراغ WIN_LogMonitor(SDL_VideoDevice *_this, HMONITOR mon)
{
    ثابت SDL_VideoData *vid_data = (ثابت SDL_VideoData *)_this->internal;
    MONITORINFOEX minfo;
    UINT xdpi = 0, ydpi = 0;
    حرف *name_utf8;

    إذا (vid_data->GetDpiForMonitor) {
        vid_data->GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &xdpi, &ydpi);
    }

    SDL_zero(minfo);
    minfo.cbSize = حجم(minfo);
    GetMonitorInfo(mon, (LPMONITORINFO)&minfo);

    name_utf8 = WIN_StringToUTF8(minfo.szDevice);

    SDL_Log("WIN_LogMonitor: monitor \"%s\": dpi: %d windows screen coordinates: %d, %d, %dx%d",
            name_utf8,
            xdpi,
            minfo.rcMonitor.سول,
            minfo.rcMonitor.چوققا,
            minfo.rcMonitor.ئوڭ - minfo.rcMonitor.سول,
            minfo.rcMonitor.bottom - minfo.rcMonitor.چوققا);

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
    إذا (mode->internal == display->desktop_mode.internal) {
#ifdef DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: resetting to original resolution");
#endif
        status = ChangeDisplaySettingsExW(displaydata->DeviceName, عدم, عدم, CDS_FULLSCREEN, عدم);
    } وإلا {
#ifdef DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: changing to %dx%d pixels", data->DeviceMode.dmPelsWidth, data->DeviceMode.dmPelsHeight);
#endif
        status = ChangeDisplaySettingsExW(displaydata->DeviceName, &data->DeviceMode, عدم, CDS_FULLSCREEN, عدم);
    }
    إذا (status != DISP_CHANGE_SUCCESSFUL) {
        ثابت حرف *reason = "Unknown reason";
        بدل (status) {
        حالة DISP_CHANGE_BADFLAGS:
            reason = "DISP_CHANGE_BADFLAGS";
            اكسر;
        حالة DISP_CHANGE_BADMODE:
            reason = "DISP_CHANGE_BADMODE";
            اكسر;
        حالة DISP_CHANGE_BADPARAM:
            reason = "DISP_CHANGE_BADPARAM";
            اكسر;
        حالة DISP_CHANGE_FAILED:
            reason = "DISP_CHANGE_FAILED";
            اكسر;
        }
        أرجع SDL_SetError("ChangeDisplaySettingsEx() failed: %s", reason);
    }

#ifdef DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state after mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#endif

    EnumDisplaySettingsW(displaydata->DeviceName, ENUM_CURRENT_SETTINGS, &data->DeviceMode);
    WIN_UpdateDisplayMode(_this, displaydata->DeviceName, ENUM_CURRENT_SETTINGS, mode);
    أرجع true;
}

فراغ WIN_RefreshDisplays(SDL_VideoDevice *_this)
{
    صحيح i;

    // Mark all displays as potentially invalid to detect
    // entries that have actually been removed
    لكل (i = 0; i < _this->رەقەم_displays; ++i) {
        SDL_DisplayData *internal = _this->displays[i]->internal;
        internal->state = DisplayRemoved;
    }

    // Enumerate displays to add any new ones and mark still
    // connected entries as valid
    WIN_AddDisplays(_this);

    // Delete any entries still marked as invalid, iterate
    // in reverse as each delete takes effect immediately
    لكل (i = _this->رەقەم_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DisplayData *internal = display->internal;
        إذا (internal->state == DisplayRemoved) {
            SDL_DelVideoDisplay(display->id, true);
        }
    }

    // Send events for any newly added displays
    لكل (i = 0; i < _this->رەقەم_displays; ++i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DisplayData *internal = display->internal;
        إذا (internal->state == DisplayAdded) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
        }
    }
}

فراغ WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this)
{
    // This almost never happens, so just go ahead and send update events for all displays
    لكل (صحيح i = 0; i < _this->رەقەم_displays; ++i) {
        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_CHANGED, 0, 0);
    }
}

فراغ WIN_QuitModes(SDL_VideoDevice *_this)
{
    // All fullscreen windows should have restored modes by now
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
