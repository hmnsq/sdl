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
#شامل "SDL_internal.h"

#اگر defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#شامل "SDL_windowsvideo.h"
#شامل "../../events/SDL_displayevents_c.h"
#شامل "../SDL_pixels_c.h"

#ifdef HAVE_DXGI1_6_H
#define COBJMACROS
#شامل <dxgi1_6.h>
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

ایستا تهی WIN_UpdateDisplayMode(SDL_VideoDevice *_this, LPCWSTR deviceName, DWORD index, SDL_DisplayMode *mode)
{
    SDL_DisplayModeData *data = (SDL_DisplayModeData *)mode->internal;
    HDC hdc;

    data->DeviceMode.dmFields = (DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS);

    // NOLINTNEXTLINE(bugprone-assignment-in-if-condition): No simple way to extract the assignment
    اگر (index == ENUM_CURRENT_SETTINGS && (hdc = CreateDCW(deviceName, پوچ, پوچ, پوچ)) != پوچ) {
        نویسه bmi_data[اندازه(BITMAPINFOHEADER) + 256 * اندازه(RGBQUAD)];
        LPBITMAPINFO bmi;
        HBITMAP hbm;

        SDL_zeroa(bmi_data);
        bmi = (LPBITMAPINFO)bmi_data;
        bmi->bmiHeader.biSize = اندازه(BITMAPINFOHEADER);

        hbm = CreateCompatibleBitmap(hdc, 1, 1);
        GetDIBits(hdc, hbm, 0, 1, پوچ, bmi, DIB_RGB_COLORS);
        GetDIBits(hdc, hbm, 0, 1, پوچ, bmi, DIB_RGB_COLORS);
        DeleteObject(hbm);
        DeleteDC(hdc);
        اگر (bmi->bmiHeader.biCompression == BI_BITFIELDS) {
            انتخاب (*(Uint32 *)bmi->bmiColors) {
            حالت 0x00FF0000:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                بشکن;
            حالت 0x000000FF:
                mode->format = SDL_PIXELFORMAT_XBGR8888;
                بشکن;
            حالت 0xF800:
                mode->format = SDL_PIXELFORMAT_RGB565;
                بشکن;
            حالت 0x7C00:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                بشکن;
            }
        } وگرنه اگر (bmi->bmiHeader.biCompression == BI_RGB) {
            اگر (bmi->bmiHeader.bi_Bit_شمار == 24) {
                mode->format = SDL_PIXELFORMAT_RGB24;
            } وگرنه اگر (bmi->bmiHeader.bi_Bit_شمار == 8) {
                mode->format = SDL_PIXELFORMAT_INDEX8;
            } وگرنه اگر (bmi->bmiHeader.bi_Bit_شمار == 4) {
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
            }
        }
    } وگرنه اگر (mode->format == SDL_PIXELFORMAT_UNKNOWN) {
        // FIXME: Can we tell what this will be?
        اگر ((data->DeviceMode.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL) {
            انتخاب (data->DeviceMode.dmBitsPerPel) {
            حالت 32:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                بشکن;
            حالت 24:
                mode->format = SDL_PIXELFORMAT_RGB24;
                بشکن;
            حالت 16:
                mode->format = SDL_PIXELFORMAT_RGB565;
                بشکن;
            حالت 15:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                بشکن;
            حالت 8:
                mode->format = SDL_PIXELFORMAT_INDEX8;
                بشکن;
            حالت 4:
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
                بشکن;
            }
        }
    }
}

ایستا تهی *WIN_GetDXGIOutput(SDL_VideoDevice *_this, ثابت WCHAR *DeviceName)
{
    تهی *result = پوچ;

#ifdef HAVE_DXGI_H
    ثابت SDL_VideoData *videodata = (ثابت SDL_VideoData *)_this->internal;
    صحیح nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    اگر (!videodata->pDXGIFactory) {
        بازگشت پوچ;
    }

    nAdapter = 0;
    وقتی (!result && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        وقتی (!result && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            اگر (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                اگر (SDL_wcscmp(outputDesc.DeviceName, DeviceName) == 0) {
                    result = pDXGIOutput;
                }
            }
            اگر (pDXGIOutput != result) {
                IDXGIOutput_Release(pDXGIOutput);
            }
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }
#endif
    بازگشت result;
}

ایستا تهی WIN_ReleaseDXGIOutput(تهی *dxgi_output)
{
#ifdef HAVE_DXGI_H
    IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;

    اگر (pDXGIOutput) {
        IDXGIOutput_Release(pDXGIOutput);
    }
#endif
}

ایستا SDL_DisplayOrientation WIN_GetNaturalOrientation(DEVMODEW *mode)
{
    صحیح width = mode->dmPelsWidth;
    صحیح height = mode->dmPelsHeight;

    // Use unrotated width/height to guess orientation
    اگر (mode->dmDisplayOrientation == DMDO_90 || mode->dmDisplayOrientation == DMDO_270) {
        صحیح temp = width;
        width = height;
        height = temp;
    }

    اگر (width >= height) {
        بازگشت SDL_ORIENTATION_LANDSCAPE;
    } وگرنه {
        بازگشت SDL_ORIENTATION_PORTRAIT;
    }
}

ایستا SDL_DisplayOrientation WIN_GetDisplayOrientation(DEVMODEW *mode)
{
    اگر (WIN_GetNaturalOrientation(mode) == SDL_ORIENTATION_LANDSCAPE) {
        انتخاب (mode->dmDisplayOrientation) {
        حالت DMDO_DEFAULT:
            بازگشت SDL_ORIENTATION_LANDSCAPE;
        حالت DMDO_90:
            بازگشت SDL_ORIENTATION_PORTRAIT;
        حالت DMDO_180:
            بازگشت SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        حالت DMDO_270:
            بازگشت SDL_ORIENTATION_PORTRAIT_FLIPPED;
        پیشفرض:
            بازگشت SDL_ORIENTATION_UNKNOWN;
        }
    } وگرنه {
        انتخاب (mode->dmDisplayOrientation) {
        حالت DMDO_DEFAULT:
            بازگشت SDL_ORIENTATION_PORTRAIT;
        حالت DMDO_90:
            بازگشت SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        حالت DMDO_180:
            بازگشت SDL_ORIENTATION_PORTRAIT_FLIPPED;
        حالت DMDO_270:
            بازگشت SDL_ORIENTATION_LANDSCAPE;
        پیشفرض:
            بازگشت SDL_ORIENTATION_UNKNOWN;
        }
    }
}

ایستا تهی WIN_GetRefreshRate(تهی *dxgi_output, DEVMODEW *mode, صحیح *numerator, صحیح *denominator)
{
    // We're not currently using DXGI to query display modes, so fake NTSC timings
    انتخاب (mode->dmDisplayFrequency) {
    حالت 119:
    حالت 59:
    حالت 29:
        *numerator = (mode->dmDisplayFrequency + 1) * 1000;
        *denominator = 1001;
        بشکن;
    پیشفرض:
        *numerator = mode->dmDisplayFrequency;
        *denominator = 1;
        بشکن;
    }

#ifdef HAVE_DXGI_H
    اگر (dxgi_output) {
        IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;
        DXGI_MODE_DESC modeToMatch;
        DXGI_MODE_DESC closestMatch;

        SDL_zero(modeToMatch);
        modeToMatch.Width = mode->dmPelsWidth;
        modeToMatch.Height = mode->dmPelsHeight;
        modeToMatch.RefreshRate.Numerator = *numerator;
        modeToMatch.RefreshRate.Denominator = *denominator;
        modeToMatch.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        اگر (SUCCEEDED(IDXGIOutput_FindClosestMatchingMode(pDXGIOutput, &modeToMatch, &closestMatch, پوچ))) {
            *numerator = closestMatch.RefreshRate.Numerator;
            *denominator = closestMatch.RefreshRate.Denominator;
        }
    }
#endif // HAVE_DXGI_H
}

ایستا اعشاری WIN_GetContentScale(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    صحیح dpi = 0;

    ثابت SDL_VideoData *videodata = (ثابت SDL_VideoData *)_this->internal;
    اگر (videodata->GetDpiForMonitor) {
        UINT hdpi_uint, vdpi_uint;
        اگر (videodata->GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
            dpi = (صحیح)hdpi_uint;
        }
    }
    اگر (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(پوچ);
        اگر (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(پوچ, hdc);
        }
    }
    اگر (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    بازگشت dpi / (اعشاری)USER_DEFAULT_SCREEN_DPI;
}

ایستا bool WIN_GetDisplayMode(SDL_VideoDevice *_this, تهی *dxgi_output, HMONITOR hMonitor, LPCWSTR deviceName, DWORD index, SDL_DisplayMode *mode, SDL_DisplayOrientation *natural_orientation, SDL_DisplayOrientation *current_orientation)
{
    SDL_DisplayModeData *data;
    DEVMODEW devmode;

    devmode.dmSize = اندازه(devmode);
    devmode.dmDriverExtra = 0;
    اگر (!EnumDisplaySettingsW(deviceName, index, &devmode)) {
        بازگشت false;
    }

    data = (SDL_DisplayModeData *)SDL_malloc(اندازه(*data));
    اگر (!data) {
        بازگشت false;
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

    اگر (natural_orientation) {
        *natural_orientation = WIN_GetNaturalOrientation(&devmode);
    }
    اگر (current_orientation) {
        *current_orientation = WIN_GetDisplayOrientation(&devmode);
    }

    بازگشت true;
}

ایستا نویسه *WIN_GetDisplayNameVista(SDL_VideoData *videodata, ثابت WCHAR *deviceName)
{
    DISPLAYCONFIG_PATH_INFO *paths = پوچ;
    DISPLAYCONFIG_MODE_INFO *modes = پوچ;
    نویسه *result = پوچ;
    UINT32 path_شمار_2 = 0;
    UINT32 mode_شمار_2 = 0;
    UINT32 i;
    LONG rc;

    اگر (!videodata->GetDisplayConfigBufferSizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        بازگشت پوچ;
    }

    انجامبده {
        rc = videodata->GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &path_شمار_2, &mode_شمار_2);
        اگر (rc != ERROR_SUCCESS) {
            برو WIN_GetDisplayNameVista_failed;
        }

        SDL_free(paths);
        SDL_free(modes);

        paths = (DISPLAYCONFIG_PATH_INFO *)SDL_malloc(اندازه(DISPLAYCONFIG_PATH_INFO) * path_شمار_2);
        modes = (DISPLAYCONFIG_MODE_INFO *)SDL_malloc(اندازه(DISPLAYCONFIG_MODE_INFO) * mode_شمار_2);
        اگر ((!paths) || (!modes)) {
            برو WIN_GetDisplayNameVista_failed;
        }

        rc = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &path_شمار_2, paths, &mode_شمار_2, modes, 0);
    } وقتی (rc == ERROR_INSUFFICIENT_BUFFER);

    اگر (rc == ERROR_SUCCESS) {
        برای (i = 0; i < path_شمار_2; i++) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME sourceName;
            DISPLAYCONFIG_TARGET_DEVICE_NAME targetName;

            SDL_zero(sourceName);
            sourceName.header.adapterId = paths[i].targetInfo.adapterId;
            sourceName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            sourceName.header.size = اندازه(sourceName);
            sourceName.header.id = paths[i].sourceInfo.id;
            rc = videodata->DisplayConfigGetDeviceInfo(&sourceName.header);
            اگر (rc != ERROR_SUCCESS) {
                بشکن;
            } وگرنه اگر (SDL_wcscmp(deviceName, sourceName.viewGdiDeviceName) != 0) {
                ادامه;
            }

            SDL_zero(targetName);
            targetName.header.adapterId = paths[i].targetInfo.adapterId;
            targetName.header.id = paths[i].targetInfo.id;
            targetName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
            targetName.header.size = اندازه(targetName);
            rc = videodata->DisplayConfigGetDeviceInfo(&targetName.header);
            اگر (rc == ERROR_SUCCESS) {
                result = WIN_StringToUTF8W(targetName.monitorFriendlyDeviceName);
                /* if we got an empty string, treat it as failure so we'll fallback
                   to getting the generic name. */
                اگر (result && (*result == '\0')) {
                    SDL_free(result);
                    result = پوچ;
                }
            }
            بشکن;
        }
    }

    SDL_free(paths);
    SDL_free(modes);
    بازگشت result;

WIN_GetDisplayNameVista_failed:
    SDL_free(result);
    SDL_free(paths);
    SDL_free(modes);
    بازگشت پوچ;
}

#ifdef HAVE_DXGI1_6_H
ایستا bool WIN_GetMonitorDESC1(HMONITOR hMonitor, DXGI_OUTPUT_DESC1 *desc)
{
    تعریفنوع HRESULT (WINAPI *pfnCreateDXGIFactory1)(REFIID riid, تهی **ppFactory);
    pfnCreateDXGIFactory1 pCreateDXGIFactory1 = پوچ;
    SDL_SharedObject *hDXGIMod = پوچ;
    bool found = false;

    hDXGIMod = SDL_LoadObject("dxgi.dll");
    اگر (hDXGIMod) {
        pCreateDXGIFactory1 = (pfnCreateDXGIFactory1)SDL_LoadFunction(hDXGIMod, "CreateDXGIFactory1");
    }
    اگر (pCreateDXGIFactory1) {
        ایستا ثابت GUID SDL_IID_IDXGIFactory1 = { 0x770aae78, 0xf26f, 0x4dba, { 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 } };
        ایستا ثابت GUID SDL_IID_IDXGIOutput6 = { 0x068346e8, 0xaaec, 0x4b84, { 0xad, 0xd7, 0x13, 0x7f, 0x51, 0x3f, 0x77, 0xa1 } };
        IDXGIFactory1 *dxgiFactory;

        اگر (SUCCEEDED(pCreateDXGIFactory1(&SDL_IID_IDXGIFactory1, (تهی **)&dxgiFactory))) {
            IDXGIAdapter1 *dxgiAdapter;
            UINT adapter = 0;
            وقتی (!found && SUCCEEDED(IDXGIFactory1_EnumAdapters1(dxgiFactory, adapter, &dxgiAdapter))) {
                IDXGIOutput *dxgiOutput;
                UINT output = 0;
                وقتی (!found && SUCCEEDED(IDXGIAdapter1_EnumOutputs(dxgiAdapter, output, &dxgiOutput))) {
                    IDXGIOutput6 *dxgiOutput6;
                    اگر (SUCCEEDED(IDXGIOutput_QueryInterface(dxgiOutput, &SDL_IID_IDXGIOutput6, (تهی **)&dxgiOutput6))) {
                        اگر (SUCCEEDED(IDXGIOutput6_GetDesc1(dxgiOutput6, desc))) {
                            اگر (desc->Monitor == hMonitor) {
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
    اگر (hDXGIMod) {
        SDL_UnloadObject(hDXGIMod);
    }
    بازگشت found;
}

ایستا bool WIN_GetMonitorPathInfo(SDL_VideoData *videodata, HMONITOR hMonitor, DISPLAYCONFIG_PATH_INFO *path_info)
{
    LONG result;
    MONITORINFOEXW view_info;
    UINT32 i;
    UINT32 رقم_path_array_elements = 0;
    UINT32 رقم_mode_info_array_elements = 0;
    DISPLAYCONFIG_PATH_INFO *path_infos = پوچ, *new_path_infos;
    DISPLAYCONFIG_MODE_INFO *mode_infos = پوچ, *new_mode_infos;
    bool found = false;

    اگر (!videodata->GetDisplayConfigBufferSizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        بازگشت false;
    }

    SDL_zero(view_info);
    view_info.cbSize = اندازه(view_info);
    اگر (!GetMonitorInfoW(hMonitor, (MONITORINFO *)&view_info)) {
        برو done;
    }

    انجامبده {
        اگر (videodata->GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &رقم_path_array_elements, &رقم_mode_info_array_elements) != ERROR_SUCCESS) {
            SDL_free(path_infos);
            SDL_free(mode_infos);
            بازگشت false;
        }

        new_path_infos = (DISPLAYCONFIG_PATH_INFO *)SDL_realloc(path_infos, رقم_path_array_elements * اندازه(*path_infos));
        اگر (!new_path_infos) {
            برو done;
        }
        path_infos = new_path_infos;

        new_mode_infos = (DISPLAYCONFIG_MODE_INFO *)SDL_realloc(mode_infos, رقم_mode_info_array_elements * اندازه(*mode_infos));
        اگر (!new_mode_infos) {
            برو done;
        }
        mode_infos = new_mode_infos;

        result = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &رقم_path_array_elements, path_infos, &رقم_mode_info_array_elements, mode_infos, پوچ);

    } وقتی (result == ERROR_INSUFFICIENT_BUFFER);

    اگر (result == ERROR_SUCCESS) {
        برای (i = 0; i < رقم_path_array_elements; ++i) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME device_name;

            SDL_zero(device_name);
            device_name.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            device_name.header.size = اندازه(device_name);
            device_name.header.adapterId = path_infos[i].sourceInfo.adapterId;
            device_name.header.id = path_infos[i].sourceInfo.id;
            اگر (videodata->DisplayConfigGetDeviceInfo(&device_name.header) == ERROR_SUCCESS) {
                اگر (SDL_wcscmp(view_info.szDevice, device_name.viewGdiDeviceName) == 0) {
                    SDL_copyp(path_info, &path_infos[i]);
                    found = true;
                    بشکن;
                }
            }
        }
    }

done:
    SDL_free(path_infos);
    SDL_free(mode_infos);

    بازگشت found;
}

ایستا اعشاری WIN_GetSDRWhitePoint(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    DISPLAYCONFIG_PATH_INFO path_info;
    SDL_VideoData *videodata = _this->internal;
    اعشاری SDR_white_level = 1.0f;

    اگر (WIN_GetMonitorPathInfo(videodata, hMonitor, &path_info)) {
        /* workarounds for https://github.com/libsdl-org/SDL/issues/11193 */
        ساختار SDL_DISPLAYCONFIG_SDR_WHITE_LEVEL {
          DISPLAYCONFIG_DEVICE_INFO_HEADER header;
          ULONG SDRWhiteLevel;
        } white_level;
        #define DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL 11

        SDL_zero(white_level);
        white_level.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
        white_level.header.size = اندازه(white_level);
        white_level.header.adapterId = path_info.targetInfo.adapterId;
        white_level.header.id = path_info.targetInfo.id;
        // WIN_GetMonitorPathInfo() succeeded: DisplayConfigGetDeviceInfo is not NULL
        اگر (videodata->DisplayConfigGetDeviceInfo(&white_level.header) == ERROR_SUCCESS &&
            white_level.SDRWhiteLevel > 0) {
            SDR_white_level = (white_level.SDRWhiteLevel / 1000.0f);
        }
    }
    بازگشت SDR_white_level;
}

ایستا تهی WIN_GetHDRProperties(SDL_VideoDevice *_this, HMONITOR hMonitor, SDL_HDROutputProperties *HDR)
{
    DXGI_OUTPUT_DESC1 desc;

    SDL_zerop(HDR);

    اگر (WIN_GetMonitorDESC1(hMonitor, &desc)) {
        اگر (desc.ColorSpace == DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020) {
            HDR->SDR_white_level = WIN_GetSDRWhitePoint(_this, hMonitor);
            HDR->HDR_headroom = (desc.MaxLuminance / SCRGB_NITS) / HDR->SDR_white_level;
        }
    }
}
#endif // HAVE_DXGI1_6_H

ایستا تهی WIN_AddDisplay(SDL_VideoDevice *_this, HMONITOR hMonitor, ثابت MONITORINFOEXW *info, صحیح *display_index)
{
    صحیح i, index = *display_index;
    SDL_VideoDisplay display;
    SDL_DisplayData *displaydata;
    تهی *dxgi_output = پوچ;
    SDL_DisplayMode mode;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    اعشاری content_scale = WIN_GetContentScale(_this, hMonitor);

#ifdef DEBUG_MODES
    SDL_Log("Display: %s", WIN_StringToUTF8W(info->szDevice));
#endif

    dxgi_output = WIN_GetDXGIOutput(_this, info->szDevice);
    bool found = WIN_GetDisplayMode(_this, dxgi_output, hMonitor, info->szDevice, ENUM_CURRENT_SETTINGS, &mode, &natural_orientation, &current_orientation);
    WIN_ReleaseDXGIOutput(dxgi_output);
    اگر (!found) {
        بازگشت;
    }

    // Prevent adding duplicate displays. Do this after we know the display is
    // ready to be added to allow any displays that we can't fully query to be
    // removed
    برای (i = 0; i < _this->رقم_displays; ++i) {
        SDL_DisplayData *internal = _this->displays[i]->internal;
        اگر (SDL_wcscmp(internal->DeviceName, info->szDevice) == 0) {
            bool moved = (index != i);
            bool changed_bounds = false;

            اگر (internal->state != DisplayRemoved) {
                // We've already enumerated this display, don't move it
                برو cleanup;
            }

            اگر (index >= _this->رقم_displays) {
                // This should never happen due to the check above, but just in case...
                برو cleanup;
            }

            اگر (moved) {
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

            اگر (!_this->setting_display_mode) {
                SDL_VideoDisplay *existing_display = _this->displays[i];
                SDL_Rect bounds;

                SDL_ResetFullscreenDisplayModes(existing_display);
                SDL_SetDesktopDisplayMode(existing_display, &mode);
                // The mode is owned by the video subsystem
                mode.internal = پوچ;
                اگر (WIN_GetDisplayBounds(_this, existing_display, &bounds) &&
                    SDL_memcmp(&internal->bounds, &bounds, اندازه(bounds)) != 0) {
                    changed_bounds = true;
                    SDL_copyp(&internal->bounds, &bounds);
                }
                اگر (moved || changed_bounds) {
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
            برو done;
        }
    }

    displaydata = (SDL_DisplayData *)SDL_calloc(1, اندازه(*displaydata));
    اگر (!displaydata) {
        برو cleanup;
    }
    SDL_memcpy(displaydata->DeviceName, info->szDevice, اندازه(displaydata->DeviceName));
    displaydata->MonitorHandle = hMonitor;
    displaydata->state = DisplayAdded;

    SDL_zero(display);
    display.name = WIN_GetDisplayNameVista(_this->internal, info->szDevice);
    اگر (!display.name) {
        DISPLAY_DEVICEW device;
        SDL_zero(device);
        device.cb = اندازه(device);
        اگر (EnumDisplayDevicesW(info->szDevice, 0, &device, 0)) {
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
    اگر (displayID) {
        // The mode is owned by the video subsystem
        mode.internal = پوچ;

        SDL_PropertiesID props = SDL_GetDisplayProperties(displayID);
        SDL_SetPointerProperty(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_POINTER, hMonitor);
    } وگرنه {
        SDL_free(displaydata);
    }
    SDL_free(display.name);

done:
    *display_index += 1;

cleanup:
    SDL_free(mode.internal);
}

تعریفنوع ساختار _WIN_AddDisplaysData
{
    SDL_VideoDevice *video_device;
    صحیح display_index;
    bool want_primary;
} WIN_AddDisplaysData;

ایستا BOOL CALLBACK WIN_AddDisplaysCallback(HMONITOR hMonitor,
                                             HDC hdcMonitor,
                                             LPRECT lprcMonitor,
                                             LPARAM dwData)
{
    WIN_AddDisplaysData *data = (WIN_AddDisplaysData *)dwData;
    MONITORINFOEXW info;

    SDL_zero(info);
    info.cbSize = اندازه(info);

    اگر (GetMonitorInfoW(hMonitor, (LPMONITORINFO)&info) != 0) {
        ثابت bool is_primary = ((info.dwFlags & MONITORINFOF_PRIMARY) == MONITORINFOF_PRIMARY);

        اگر (is_primary == data->want_primary) {
            WIN_AddDisplay(data->video_device, hMonitor, &info, &data->display_index);
        }
    }

    // continue enumeration
    بازگشت TRUE;
}

ایستا تهی WIN_AddDisplays(SDL_VideoDevice *_this)
{
    WIN_AddDisplaysData callback_data;
    callback_data.video_device = _this;
    callback_data.display_index = 0;

    callback_data.want_primary = true;
    EnumDisplayMonitors(پوچ, پوچ, WIN_AddDisplaysCallback, (LPARAM)&callback_data);

    callback_data.want_primary = false;
    EnumDisplayMonitors(پوچ, پوچ, WIN_AddDisplaysCallback, (LPARAM)&callback_data);
}

bool WIN_InitModes(SDL_VideoDevice *_this)
{
    WIN_AddDisplays(_this);

    اگر (_this->رقم_displays == 0) {
        بازگشت SDL_SetError("No displays available");
    }
    بازگشت true;
}

bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ثابت SDL_DisplayData *data = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cbSize = اندازه(MONITORINFO);
    rc = GetMonitorInfo(data->MonitorHandle, &minfo);

    اگر (!rc) {
        بازگشت SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcMonitor.چپ;
    rect->y = minfo.rcMonitor.بالاترین;
    rect->w = minfo.rcMonitor.راست - minfo.rcMonitor.چپ;
    rect->h = minfo.rcMonitor.bottom - minfo.rcMonitor.بالاترین;

    بازگشت true;
}

bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ثابت SDL_DisplayData *data = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cbSize = اندازه(MONITORINFO);
    rc = GetMonitorInfo(data->MonitorHandle, &minfo);

    اگر (!rc) {
        بازگشت SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcWork.چپ;
    rect->y = minfo.rcWork.بالاترین;
    rect->w = minfo.rcWork.راست - minfo.rcWork.چپ;
    rect->h = minfo.rcWork.bottom - minfo.rcWork.بالاترین;

    بازگشت true;
}

bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_DisplayData *data = display->internal;
    تهی *dxgi_output;
    DWORD i;
    SDL_DisplayMode mode;

    dxgi_output = WIN_GetDXGIOutput(_this, data->DeviceName);

    // Make sure we add the current mode to the list in case it's a custom mode that doesn't enumerate
    برای (i = ENUM_CURRENT_SETTINGS; ; ++i) {
        اگر (!WIN_GetDisplayMode(_this, dxgi_output, data->MonitorHandle, data->DeviceName, i, &mode, پوچ, پوچ)) {
            بشکن;
        }
        اگر (SDL_ISPIXELFORMAT_INDEXED(mode.format)) {
            // We don't support palettized modes now
            SDL_free(mode.internal);
            ادامه;
        }
        اگر (mode.format != SDL_PIXELFORMAT_UNKNOWN) {
            اگر (!SDL_AddFullscreenDisplayMode(display, &mode)) {
                SDL_free(mode.internal);
            }
        } وگرنه {
            SDL_free(mode.internal);
        }
    }

    WIN_ReleaseDXGIOutput(dxgi_output);

    بازگشت true;
}

#ifdef DEBUG_MODES
ایستا تهی WIN_LogMonitor(SDL_VideoDevice *_this, HMONITOR mon)
{
    ثابت SDL_VideoData *vid_data = (ثابت SDL_VideoData *)_this->internal;
    MONITORINFOEX minfo;
    UINT xdpi = 0, ydpi = 0;
    نویسه *name_utf8;

    اگر (vid_data->GetDpiForMonitor) {
        vid_data->GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &xdpi, &ydpi);
    }

    SDL_zero(minfo);
    minfo.cbSize = اندازه(minfo);
    GetMonitorInfo(mon, (LPMONITORINFO)&minfo);

    name_utf8 = WIN_StringToUTF8(minfo.szDevice);

    SDL_Log("WIN_LogMonitor: monitor \"%s\": dpi: %d windows screen coordinates: %d, %d, %dx%d",
            name_utf8,
            xdpi,
            minfo.rcMonitor.چپ,
            minfo.rcMonitor.بالاترین,
            minfo.rcMonitor.راست - minfo.rcMonitor.چپ,
            minfo.rcMonitor.bottom - minfo.rcMonitor.بالاترین);

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
    اگر (mode->internal == display->desktop_mode.internal) {
#ifdef DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: resetting to original resolution");
#endif
        status = ChangeDisplaySettingsExW(displaydata->DeviceName, پوچ, پوچ, CDS_FULLSCREEN, پوچ);
    } وگرنه {
#ifdef DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: changing to %dx%d pixels", data->DeviceMode.dmPelsWidth, data->DeviceMode.dmPelsHeight);
#endif
        status = ChangeDisplaySettingsExW(displaydata->DeviceName, &data->DeviceMode, پوچ, CDS_FULLSCREEN, پوچ);
    }
    اگر (status != DISP_CHANGE_SUCCESSFUL) {
        ثابت نویسه *reason = "Unknown reason";
        انتخاب (status) {
        حالت DISP_CHANGE_BADFLAGS:
            reason = "DISP_CHANGE_BADFLAGS";
            بشکن;
        حالت DISP_CHANGE_BADMODE:
            reason = "DISP_CHANGE_BADMODE";
            بشکن;
        حالت DISP_CHANGE_BADPARAM:
            reason = "DISP_CHANGE_BADPARAM";
            بشکن;
        حالت DISP_CHANGE_FAILED:
            reason = "DISP_CHANGE_FAILED";
            بشکن;
        }
        بازگشت SDL_SetError("ChangeDisplaySettingsEx() failed: %s", reason);
    }

#ifdef DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state after mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#endif

    EnumDisplaySettingsW(displaydata->DeviceName, ENUM_CURRENT_SETTINGS, &data->DeviceMode);
    WIN_UpdateDisplayMode(_this, displaydata->DeviceName, ENUM_CURRENT_SETTINGS, mode);
    بازگشت true;
}

تهی WIN_RefreshDisplays(SDL_VideoDevice *_this)
{
    صحیح i;

    // Mark all displays as potentially invalid to detect
    // entries that have actually been removed
    برای (i = 0; i < _this->رقم_displays; ++i) {
        SDL_DisplayData *internal = _this->displays[i]->internal;
        internal->state = DisplayRemoved;
    }

    // Enumerate displays to add any new ones and mark still
    // connected entries as valid
    WIN_AddDisplays(_this);

    // Delete any entries still marked as invalid, iterate
    // in reverse as each delete takes effect immediately
    برای (i = _this->رقم_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DisplayData *internal = display->internal;
        اگر (internal->state == DisplayRemoved) {
            SDL_DelVideoDisplay(display->id, true);
        }
    }

    // Send events for any newly added displays
    برای (i = 0; i < _this->رقم_displays; ++i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DisplayData *internal = display->internal;
        اگر (internal->state == DisplayAdded) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
        }
    }
}

تهی WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this)
{
    // This almost never happens, so just go ahead and send update events for all displays
    برای (صحیح i = 0; i < _this->رقم_displays; ++i) {
        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_CHANGED, 0, 0);
    }
}

تهی WIN_QuitModes(SDL_VideoDevice *_this)
{
    // All fullscreen windows should have restored modes by now
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
