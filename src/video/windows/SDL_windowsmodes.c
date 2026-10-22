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
#अन्तर्भाव "SDL_internal.h"

#यदि defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#अन्तर्भाव "SDL_windowsvideo.h"
#अन्तर्भाव "../../events/SDL_displayevents_c.h"
#अन्तर्भाव "../SDL_pixels_c.h"

#ifdef HAVE_DXGI1_6_H
#define COBJMACROS
#अन्तर्भाव <dxgi1_6.h>
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

स्थिर शून्य WIN_UpdateDisplayMode(SDL_VideoDevice *_this, LPCWSTR deviceName, DWORD index, SDL_DisplayMode *mode)
{
    SDL_DisplayModeData *data = (SDL_DisplayModeData *)mode->internal;
    HDC hdc;

    data->DeviceMode.dmFields = (DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS);

    // NOLINTNEXTLINE(bugprone-assignment-in-if-condition): No simple way to extract the assignment
    यदि (index == ENUM_CURRENT_SETTINGS && (hdc = CreateDCW(deviceName, रिक्त, रिक्त, रिक्त)) != रिक्त) {
        वर्ण bmi_data[परिमाण(BITMAPINFOHEADER) + 256 * परिमाण(RGBQUAD)];
        LPBITMAPINFO bmi;
        HBITMAP hbm;

        SDL_zeroa(bmi_data);
        bmi = (LPBITMAPINFO)bmi_data;
        bmi->bmiHeader.biSize = परिमाण(BITMAPINFOHEADER);

        hbm = CreateCompatibleBitmap(hdc, 1, 1);
        GetDIBits(hdc, hbm, 0, 1, रिक्त, bmi, DIB_RGB_COLORS);
        GetDIBits(hdc, hbm, 0, 1, रिक्त, bmi, DIB_RGB_COLORS);
        DeleteObject(hbm);
        DeleteDC(hdc);
        यदि (bmi->bmiHeader.biCompression == BI_BITFIELDS) {
            विकल्प (*(Uint32 *)bmi->bmiColors) {
            पक्ष 0x00FF0000:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                रोक;
            पक्ष 0x000000FF:
                mode->format = SDL_PIXELFORMAT_XBGR8888;
                रोक;
            पक्ष 0xF800:
                mode->format = SDL_PIXELFORMAT_RGB565;
                रोक;
            पक्ष 0x7C00:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                रोक;
            }
        } अन्यथा यदि (bmi->bmiHeader.biCompression == BI_RGB) {
            यदि (bmi->bmiHeader.bi_Bit_गन्ती == 24) {
                mode->format = SDL_PIXELFORMAT_RGB24;
            } अन्यथा यदि (bmi->bmiHeader.bi_Bit_गन्ती == 8) {
                mode->format = SDL_PIXELFORMAT_INDEX8;
            } अन्यथा यदि (bmi->bmiHeader.bi_Bit_गन्ती == 4) {
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
            }
        }
    } अन्यथा यदि (mode->format == SDL_PIXELFORMAT_UNKNOWN) {
        // FIXME: Can we tell what this will be?
        यदि ((data->DeviceMode.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL) {
            विकल्प (data->DeviceMode.dmBitsPerPel) {
            पक्ष 32:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                रोक;
            पक्ष 24:
                mode->format = SDL_PIXELFORMAT_RGB24;
                रोक;
            पक्ष 16:
                mode->format = SDL_PIXELFORMAT_RGB565;
                रोक;
            पक्ष 15:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                रोक;
            पक्ष 8:
                mode->format = SDL_PIXELFORMAT_INDEX8;
                रोक;
            पक्ष 4:
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
                रोक;
            }
        }
    }
}

स्थिर शून्य *WIN_GetDXGIOutput(SDL_VideoDevice *_this, अचर WCHAR *DeviceName)
{
    शून्य *result = रिक्त;

#ifdef HAVE_DXGI_H
    अचर SDL_VideoData *videodata = (अचर SDL_VideoData *)_this->internal;
    पूर्णाङ्क nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    यदि (!videodata->pDXGIFactory) {
        फर्काऊ रिक्त;
    }

    nAdapter = 0;
    जबसम्म (!result && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        जबसम्म (!result && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            यदि (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                यदि (SDL_wcscmp(outputDesc.DeviceName, DeviceName) == 0) {
                    result = pDXGIOutput;
                }
            }
            यदि (pDXGIOutput != result) {
                IDXGIOutput_Release(pDXGIOutput);
            }
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }
#endif
    फर्काऊ result;
}

स्थिर शून्य WIN_ReleaseDXGIOutput(शून्य *dxgi_output)
{
#ifdef HAVE_DXGI_H
    IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;

    यदि (pDXGIOutput) {
        IDXGIOutput_Release(pDXGIOutput);
    }
#endif
}

स्थिर SDL_DisplayOrientation WIN_GetNaturalOrientation(DEVMODEW *mode)
{
    पूर्णाङ्क width = mode->dmPelsWidth;
    पूर्णाङ्क height = mode->dmPelsHeight;

    // Use unrotated width/height to guess orientation
    यदि (mode->dmDisplayOrientation == DMDO_90 || mode->dmDisplayOrientation == DMDO_270) {
        पूर्णाङ्क temp = width;
        width = height;
        height = temp;
    }

    यदि (width >= height) {
        फर्काऊ SDL_ORIENTATION_LANDSCAPE;
    } अन्यथा {
        फर्काऊ SDL_ORIENTATION_PORTRAIT;
    }
}

स्थिर SDL_DisplayOrientation WIN_GetDisplayOrientation(DEVMODEW *mode)
{
    यदि (WIN_GetNaturalOrientation(mode) == SDL_ORIENTATION_LANDSCAPE) {
        विकल्प (mode->dmDisplayOrientation) {
        पक्ष DMDO_DEFAULT:
            फर्काऊ SDL_ORIENTATION_LANDSCAPE;
        पक्ष DMDO_90:
            फर्काऊ SDL_ORIENTATION_PORTRAIT;
        पक्ष DMDO_180:
            फर्काऊ SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        पक्ष DMDO_270:
            फर्काऊ SDL_ORIENTATION_PORTRAIT_FLIPPED;
        स्वभाव:
            फर्काऊ SDL_ORIENTATION_UNKNOWN;
        }
    } अन्यथा {
        विकल्प (mode->dmDisplayOrientation) {
        पक्ष DMDO_DEFAULT:
            फर्काऊ SDL_ORIENTATION_PORTRAIT;
        पक्ष DMDO_90:
            फर्काऊ SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        पक्ष DMDO_180:
            फर्काऊ SDL_ORIENTATION_PORTRAIT_FLIPPED;
        पक्ष DMDO_270:
            फर्काऊ SDL_ORIENTATION_LANDSCAPE;
        स्वभाव:
            फर्काऊ SDL_ORIENTATION_UNKNOWN;
        }
    }
}

स्थिर शून्य WIN_GetRefreshRate(शून्य *dxgi_output, DEVMODEW *mode, पूर्णाङ्क *numerator, पूर्णाङ्क *denominator)
{
    // We're not currently using DXGI to query display modes, so fake NTSC timings
    विकल्प (mode->dmDisplayFrequency) {
    पक्ष 119:
    पक्ष 59:
    पक्ष 29:
        *numerator = (mode->dmDisplayFrequency + 1) * 1000;
        *denominator = 1001;
        रोक;
    स्वभाव:
        *numerator = mode->dmDisplayFrequency;
        *denominator = 1;
        रोक;
    }

#ifdef HAVE_DXGI_H
    यदि (dxgi_output) {
        IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;
        DXGI_MODE_DESC modeToMatch;
        DXGI_MODE_DESC closestMatch;

        SDL_zero(modeToMatch);
        modeToMatch.Width = mode->dmPelsWidth;
        modeToMatch.Height = mode->dmPelsHeight;
        modeToMatch.RefreshRate.Numerator = *numerator;
        modeToMatch.RefreshRate.Denominator = *denominator;
        modeToMatch.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        यदि (SUCCEEDED(IDXGIOutput_FindClosestMatchingMode(pDXGIOutput, &modeToMatch, &closestMatch, रिक्त))) {
            *numerator = closestMatch.RefreshRate.Numerator;
            *denominator = closestMatch.RefreshRate.Denominator;
        }
    }
#endif // HAVE_DXGI_H
}

स्थिर भिन्न WIN_GetContentScale(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    पूर्णाङ्क dpi = 0;

    अचर SDL_VideoData *videodata = (अचर SDL_VideoData *)_this->internal;
    यदि (videodata->GetDpiForMonitor) {
        UINT hdpi_uint, vdpi_uint;
        यदि (videodata->GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
            dpi = (पूर्णाङ्क)hdpi_uint;
        }
    }
    यदि (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(रिक्त);
        यदि (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(रिक्त, hdc);
        }
    }
    यदि (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    फर्काऊ dpi / (भिन्न)USER_DEFAULT_SCREEN_DPI;
}

स्थिर bool WIN_GetDisplayMode(SDL_VideoDevice *_this, शून्य *dxgi_output, HMONITOR hMonitor, LPCWSTR deviceName, DWORD index, SDL_DisplayMode *mode, SDL_DisplayOrientation *natural_orientation, SDL_DisplayOrientation *current_orientation)
{
    SDL_DisplayModeData *data;
    DEVMODEW devmode;

    devmode.dmSize = परिमाण(devmode);
    devmode.dmDriverExtra = 0;
    यदि (!EnumDisplaySettingsW(deviceName, index, &devmode)) {
        फर्काऊ false;
    }

    data = (SDL_DisplayModeData *)SDL_malloc(परिमाण(*data));
    यदि (!data) {
        फर्काऊ false;
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

    यदि (natural_orientation) {
        *natural_orientation = WIN_GetNaturalOrientation(&devmode);
    }
    यदि (current_orientation) {
        *current_orientation = WIN_GetDisplayOrientation(&devmode);
    }

    फर्काऊ true;
}

स्थिर वर्ण *WIN_GetDisplayNameVista(SDL_VideoData *videodata, अचर WCHAR *deviceName)
{
    DISPLAYCONFIG_PATH_INFO *paths = रिक्त;
    DISPLAYCONFIG_MODE_INFO *modes = रिक्त;
    वर्ण *result = रिक्त;
    UINT32 path_गन्ती_2 = 0;
    UINT32 mode_गन्ती_2 = 0;
    UINT32 i;
    LONG rc;

    यदि (!videodata->GetDisplayConfigBufferSizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        फर्काऊ रिक्त;
    }

    गर {
        rc = videodata->GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &path_गन्ती_2, &mode_गन्ती_2);
        यदि (rc != ERROR_SUCCESS) {
            गच्छ WIN_GetDisplayNameVista_failed;
        }

        SDL_free(paths);
        SDL_free(modes);

        paths = (DISPLAYCONFIG_PATH_INFO *)SDL_malloc(परिमाण(DISPLAYCONFIG_PATH_INFO) * path_गन्ती_2);
        modes = (DISPLAYCONFIG_MODE_INFO *)SDL_malloc(परिमाण(DISPLAYCONFIG_MODE_INFO) * mode_गन्ती_2);
        यदि ((!paths) || (!modes)) {
            गच्छ WIN_GetDisplayNameVista_failed;
        }

        rc = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &path_गन्ती_2, paths, &mode_गन्ती_2, modes, 0);
    } जबसम्म (rc == ERROR_INSUFFICIENT_BUFFER);

    यदि (rc == ERROR_SUCCESS) {
        लागि (i = 0; i < path_गन्ती_2; i++) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME sourceName;
            DISPLAYCONFIG_TARGET_DEVICE_NAME targetName;

            SDL_zero(sourceName);
            sourceName.header.adapterId = paths[i].targetInfo.adapterId;
            sourceName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            sourceName.header.size = परिमाण(sourceName);
            sourceName.header.id = paths[i].sourceInfo.id;
            rc = videodata->DisplayConfigGetDeviceInfo(&sourceName.header);
            यदि (rc != ERROR_SUCCESS) {
                रोक;
            } अन्यथा यदि (SDL_wcscmp(deviceName, sourceName.viewGdiDeviceName) != 0) {
                जारी;
            }

            SDL_zero(targetName);
            targetName.header.adapterId = paths[i].targetInfo.adapterId;
            targetName.header.id = paths[i].targetInfo.id;
            targetName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
            targetName.header.size = परिमाण(targetName);
            rc = videodata->DisplayConfigGetDeviceInfo(&targetName.header);
            यदि (rc == ERROR_SUCCESS) {
                result = WIN_StringToUTF8W(targetName.monitorFriendlyDeviceName);
                /* if we got an empty string, treat it as failure so we'll fallback
                   to getting the generic name. */
                यदि (result && (*result == '\0')) {
                    SDL_free(result);
                    result = रिक्त;
                }
            }
            रोक;
        }
    }

    SDL_free(paths);
    SDL_free(modes);
    फर्काऊ result;

WIN_GetDisplayNameVista_failed:
    SDL_free(result);
    SDL_free(paths);
    SDL_free(modes);
    फर्काऊ रिक्त;
}

#ifdef HAVE_DXGI1_6_H
स्थिर bool WIN_GetMonitorDESC1(HMONITOR hMonitor, DXGI_OUTPUT_DESC1 *desc)
{
    प्रकारनिर्देश HRESULT (WINAPI *pfnCreateDXGIFactory1)(REFIID riid, शून्य **ppFactory);
    pfnCreateDXGIFactory1 pCreateDXGIFactory1 = रिक्त;
    SDL_SharedObject *hDXGIMod = रिक्त;
    bool found = false;

    hDXGIMod = SDL_LoadObject("dxgi.dll");
    यदि (hDXGIMod) {
        pCreateDXGIFactory1 = (pfnCreateDXGIFactory1)SDL_LoadFunction(hDXGIMod, "CreateDXGIFactory1");
    }
    यदि (pCreateDXGIFactory1) {
        स्थिर अचर GUID SDL_IID_IDXGIFactory1 = { 0x770aae78, 0xf26f, 0x4dba, { 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 } };
        स्थिर अचर GUID SDL_IID_IDXGIOutput6 = { 0x068346e8, 0xaaec, 0x4b84, { 0xad, 0xd7, 0x13, 0x7f, 0x51, 0x3f, 0x77, 0xa1 } };
        IDXGIFactory1 *dxgiFactory;

        यदि (SUCCEEDED(pCreateDXGIFactory1(&SDL_IID_IDXGIFactory1, (शून्य **)&dxgiFactory))) {
            IDXGIAdapter1 *dxgiAdapter;
            UINT adapter = 0;
            जबसम्म (!found && SUCCEEDED(IDXGIFactory1_EnumAdapters1(dxgiFactory, adapter, &dxgiAdapter))) {
                IDXGIOutput *dxgiOutput;
                UINT output = 0;
                जबसम्म (!found && SUCCEEDED(IDXGIAdapter1_EnumOutputs(dxgiAdapter, output, &dxgiOutput))) {
                    IDXGIOutput6 *dxgiOutput6;
                    यदि (SUCCEEDED(IDXGIOutput_QueryInterface(dxgiOutput, &SDL_IID_IDXGIOutput6, (शून्य **)&dxgiOutput6))) {
                        यदि (SUCCEEDED(IDXGIOutput6_GetDesc1(dxgiOutput6, desc))) {
                            यदि (desc->Monitor == hMonitor) {
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
    यदि (hDXGIMod) {
        SDL_UnloadObject(hDXGIMod);
    }
    फर्काऊ found;
}

स्थिर bool WIN_GetMonitorPathInfo(SDL_VideoData *videodata, HMONITOR hMonitor, DISPLAYCONFIG_PATH_INFO *path_info)
{
    LONG result;
    MONITORINFOEXW view_info;
    UINT32 i;
    UINT32 अङ्क_path_array_elements = 0;
    UINT32 अङ्क_mode_info_array_elements = 0;
    DISPLAYCONFIG_PATH_INFO *path_infos = रिक्त, *new_path_infos;
    DISPLAYCONFIG_MODE_INFO *mode_infos = रिक्त, *new_mode_infos;
    bool found = false;

    यदि (!videodata->GetDisplayConfigBufferSizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        फर्काऊ false;
    }

    SDL_zero(view_info);
    view_info.cbSize = परिमाण(view_info);
    यदि (!GetMonitorInfoW(hMonitor, (MONITORINFO *)&view_info)) {
        गच्छ done;
    }

    गर {
        यदि (videodata->GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &अङ्क_path_array_elements, &अङ्क_mode_info_array_elements) != ERROR_SUCCESS) {
            SDL_free(path_infos);
            SDL_free(mode_infos);
            फर्काऊ false;
        }

        new_path_infos = (DISPLAYCONFIG_PATH_INFO *)SDL_realloc(path_infos, अङ्क_path_array_elements * परिमाण(*path_infos));
        यदि (!new_path_infos) {
            गच्छ done;
        }
        path_infos = new_path_infos;

        new_mode_infos = (DISPLAYCONFIG_MODE_INFO *)SDL_realloc(mode_infos, अङ्क_mode_info_array_elements * परिमाण(*mode_infos));
        यदि (!new_mode_infos) {
            गच्छ done;
        }
        mode_infos = new_mode_infos;

        result = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &अङ्क_path_array_elements, path_infos, &अङ्क_mode_info_array_elements, mode_infos, रिक्त);

    } जबसम्म (result == ERROR_INSUFFICIENT_BUFFER);

    यदि (result == ERROR_SUCCESS) {
        लागि (i = 0; i < अङ्क_path_array_elements; ++i) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME device_name;

            SDL_zero(device_name);
            device_name.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            device_name.header.size = परिमाण(device_name);
            device_name.header.adapterId = path_infos[i].sourceInfo.adapterId;
            device_name.header.id = path_infos[i].sourceInfo.id;
            यदि (videodata->DisplayConfigGetDeviceInfo(&device_name.header) == ERROR_SUCCESS) {
                यदि (SDL_wcscmp(view_info.szDevice, device_name.viewGdiDeviceName) == 0) {
                    SDL_copyp(path_info, &path_infos[i]);
                    found = true;
                    रोक;
                }
            }
        }
    }

done:
    SDL_free(path_infos);
    SDL_free(mode_infos);

    फर्काऊ found;
}

स्थिर भिन्न WIN_GetSDRWhitePoint(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    DISPLAYCONFIG_PATH_INFO path_info;
    SDL_VideoData *videodata = _this->internal;
    भिन्न SDR_white_level = 1.0f;

    यदि (WIN_GetMonitorPathInfo(videodata, hMonitor, &path_info)) {
        /* workarounds for https://github.com/libsdl-org/SDL/issues/11193 */
        संरचना SDL_DISPLAYCONFIG_SDR_WHITE_LEVEL {
          DISPLAYCONFIG_DEVICE_INFO_HEADER header;
          ULONG SDRWhiteLevel;
        } white_level;
        #define DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL 11

        SDL_zero(white_level);
        white_level.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
        white_level.header.size = परिमाण(white_level);
        white_level.header.adapterId = path_info.targetInfo.adapterId;
        white_level.header.id = path_info.targetInfo.id;
        // WIN_GetMonitorPathInfo() succeeded: DisplayConfigGetDeviceInfo is not NULL
        यदि (videodata->DisplayConfigGetDeviceInfo(&white_level.header) == ERROR_SUCCESS &&
            white_level.SDRWhiteLevel > 0) {
            SDR_white_level = (white_level.SDRWhiteLevel / 1000.0f);
        }
    }
    फर्काऊ SDR_white_level;
}

स्थिर शून्य WIN_GetHDRProperties(SDL_VideoDevice *_this, HMONITOR hMonitor, SDL_HDROutputProperties *HDR)
{
    DXGI_OUTPUT_DESC1 desc;

    SDL_zerop(HDR);

    यदि (WIN_GetMonitorDESC1(hMonitor, &desc)) {
        यदि (desc.ColorSpace == DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020) {
            HDR->SDR_white_level = WIN_GetSDRWhitePoint(_this, hMonitor);
            HDR->HDR_headroom = (desc.MaxLuminance / SCRGB_NITS) / HDR->SDR_white_level;
        }
    }
}
#endif // HAVE_DXGI1_6_H

स्थिर शून्य WIN_AddDisplay(SDL_VideoDevice *_this, HMONITOR hMonitor, अचर MONITORINFOEXW *info, पूर्णाङ्क *display_index)
{
    पूर्णाङ्क i, index = *display_index;
    SDL_VideoDisplay display;
    SDL_DisplayData *displaydata;
    शून्य *dxgi_output = रिक्त;
    SDL_DisplayMode mode;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    भिन्न content_scale = WIN_GetContentScale(_this, hMonitor);

#ifdef DEBUG_MODES
    SDL_Log("Display: %s", WIN_StringToUTF8W(info->szDevice));
#endif

    dxgi_output = WIN_GetDXGIOutput(_this, info->szDevice);
    bool found = WIN_GetDisplayMode(_this, dxgi_output, hMonitor, info->szDevice, ENUM_CURRENT_SETTINGS, &mode, &natural_orientation, &current_orientation);
    WIN_ReleaseDXGIOutput(dxgi_output);
    यदि (!found) {
        फर्काऊ;
    }

    // Prevent adding duplicate displays. Do this after we know the display is
    // ready to be added to allow any displays that we can't fully query to be
    // removed
    लागि (i = 0; i < _this->अङ्क_displays; ++i) {
        SDL_DisplayData *internal = _this->displays[i]->internal;
        यदि (SDL_wcscmp(internal->DeviceName, info->szDevice) == 0) {
            bool moved = (index != i);
            bool changed_bounds = false;

            यदि (internal->state != DisplayRemoved) {
                // We've already enumerated this display, don't move it
                गच्छ cleanup;
            }

            यदि (index >= _this->अङ्क_displays) {
                // This should never happen due to the check above, but just in case...
                गच्छ cleanup;
            }

            यदि (moved) {
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

            यदि (!_this->setting_display_mode) {
                SDL_VideoDisplay *existing_display = _this->displays[i];
                SDL_Rect bounds;

                SDL_ResetFullscreenDisplayModes(existing_display);
                SDL_SetDesktopDisplayMode(existing_display, &mode);
                // The mode is owned by the video subsystem
                mode.internal = रिक्त;
                यदि (WIN_GetDisplayBounds(_this, existing_display, &bounds) &&
                    SDL_memcmp(&internal->bounds, &bounds, परिमाण(bounds)) != 0) {
                    changed_bounds = true;
                    SDL_copyp(&internal->bounds, &bounds);
                }
                यदि (moved || changed_bounds) {
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
            गच्छ done;
        }
    }

    displaydata = (SDL_DisplayData *)SDL_calloc(1, परिमाण(*displaydata));
    यदि (!displaydata) {
        गच्छ cleanup;
    }
    SDL_memcpy(displaydata->DeviceName, info->szDevice, परिमाण(displaydata->DeviceName));
    displaydata->MonitorHandle = hMonitor;
    displaydata->state = DisplayAdded;

    SDL_zero(display);
    display.name = WIN_GetDisplayNameVista(_this->internal, info->szDevice);
    यदि (!display.name) {
        DISPLAY_DEVICEW device;
        SDL_zero(device);
        device.cb = परिमाण(device);
        यदि (EnumDisplayDevicesW(info->szDevice, 0, &device, 0)) {
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
    यदि (displayID) {
        // The mode is owned by the video subsystem
        mode.internal = रिक्त;

        SDL_PropertiesID props = SDL_GetDisplayProperties(displayID);
        SDL_SetPointerProperty(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_POINTER, hMonitor);
    } अन्यथा {
        SDL_free(displaydata);
    }
    SDL_free(display.name);

done:
    *display_index += 1;

cleanup:
    SDL_free(mode.internal);
}

प्रकारनिर्देश संरचना _WIN_AddDisplaysData
{
    SDL_VideoDevice *video_device;
    पूर्णाङ्क display_index;
    bool want_primary;
} WIN_AddDisplaysData;

स्थिर BOOL CALLBACK WIN_AddDisplaysCallback(HMONITOR hMonitor,
                                             HDC hdcMonitor,
                                             LPRECT lprcMonitor,
                                             LPARAM dwData)
{
    WIN_AddDisplaysData *data = (WIN_AddDisplaysData *)dwData;
    MONITORINFOEXW info;

    SDL_zero(info);
    info.cbSize = परिमाण(info);

    यदि (GetMonitorInfoW(hMonitor, (LPMONITORINFO)&info) != 0) {
        अचर bool is_primary = ((info.dwFlags & MONITORINFOF_PRIMARY) == MONITORINFOF_PRIMARY);

        यदि (is_primary == data->want_primary) {
            WIN_AddDisplay(data->video_device, hMonitor, &info, &data->display_index);
        }
    }

    // continue enumeration
    फर्काऊ TRUE;
}

स्थिर शून्य WIN_AddDisplays(SDL_VideoDevice *_this)
{
    WIN_AddDisplaysData callback_data;
    callback_data.video_device = _this;
    callback_data.display_index = 0;

    callback_data.want_primary = true;
    EnumDisplayMonitors(रिक्त, रिक्त, WIN_AddDisplaysCallback, (LPARAM)&callback_data);

    callback_data.want_primary = false;
    EnumDisplayMonitors(रिक्त, रिक्त, WIN_AddDisplaysCallback, (LPARAM)&callback_data);
}

bool WIN_InitModes(SDL_VideoDevice *_this)
{
    WIN_AddDisplays(_this);

    यदि (_this->अङ्क_displays == 0) {
        फर्काऊ SDL_SetError("No displays available");
    }
    फर्काऊ true;
}

bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    अचर SDL_DisplayData *data = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cbSize = परिमाण(MONITORINFO);
    rc = GetMonitorInfo(data->MonitorHandle, &minfo);

    यदि (!rc) {
        फर्काऊ SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcMonitor.बायाँ;
    rect->y = minfo.rcMonitor.शीर्ष;
    rect->w = minfo.rcMonitor.दायाँ - minfo.rcMonitor.बायाँ;
    rect->h = minfo.rcMonitor.bottom - minfo.rcMonitor.शीर्ष;

    फर्काऊ true;
}

bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    अचर SDL_DisplayData *data = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cbSize = परिमाण(MONITORINFO);
    rc = GetMonitorInfo(data->MonitorHandle, &minfo);

    यदि (!rc) {
        फर्काऊ SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcWork.बायाँ;
    rect->y = minfo.rcWork.शीर्ष;
    rect->w = minfo.rcWork.दायाँ - minfo.rcWork.बायाँ;
    rect->h = minfo.rcWork.bottom - minfo.rcWork.शीर्ष;

    फर्काऊ true;
}

bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_DisplayData *data = display->internal;
    शून्य *dxgi_output;
    DWORD i;
    SDL_DisplayMode mode;

    dxgi_output = WIN_GetDXGIOutput(_this, data->DeviceName);

    // Make sure we add the current mode to the list in case it's a custom mode that doesn't enumerate
    लागि (i = ENUM_CURRENT_SETTINGS; ; ++i) {
        यदि (!WIN_GetDisplayMode(_this, dxgi_output, data->MonitorHandle, data->DeviceName, i, &mode, रिक्त, रिक्त)) {
            रोक;
        }
        यदि (SDL_ISPIXELFORMAT_INDEXED(mode.format)) {
            // We don't support palettized modes now
            SDL_free(mode.internal);
            जारी;
        }
        यदि (mode.format != SDL_PIXELFORMAT_UNKNOWN) {
            यदि (!SDL_AddFullscreenDisplayMode(display, &mode)) {
                SDL_free(mode.internal);
            }
        } अन्यथा {
            SDL_free(mode.internal);
        }
    }

    WIN_ReleaseDXGIOutput(dxgi_output);

    फर्काऊ true;
}

#ifdef DEBUG_MODES
स्थिर शून्य WIN_LogMonitor(SDL_VideoDevice *_this, HMONITOR mon)
{
    अचर SDL_VideoData *vid_data = (अचर SDL_VideoData *)_this->internal;
    MONITORINFOEX minfo;
    UINT xdpi = 0, ydpi = 0;
    वर्ण *name_utf8;

    यदि (vid_data->GetDpiForMonitor) {
        vid_data->GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &xdpi, &ydpi);
    }

    SDL_zero(minfo);
    minfo.cbSize = परिमाण(minfo);
    GetMonitorInfo(mon, (LPMONITORINFO)&minfo);

    name_utf8 = WIN_StringToUTF8(minfo.szDevice);

    SDL_Log("WIN_LogMonitor: monitor \"%s\": dpi: %d windows screen coordinates: %d, %d, %dx%d",
            name_utf8,
            xdpi,
            minfo.rcMonitor.बायाँ,
            minfo.rcMonitor.शीर्ष,
            minfo.rcMonitor.दायाँ - minfo.rcMonitor.बायाँ,
            minfo.rcMonitor.bottom - minfo.rcMonitor.शीर्ष);

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
    यदि (mode->internal == display->desktop_mode.internal) {
#ifdef DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: resetting to original resolution");
#endif
        status = ChangeDisplaySettingsExW(displaydata->DeviceName, रिक्त, रिक्त, CDS_FULLSCREEN, रिक्त);
    } अन्यथा {
#ifdef DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: changing to %dx%d pixels", data->DeviceMode.dmPelsWidth, data->DeviceMode.dmPelsHeight);
#endif
        status = ChangeDisplaySettingsExW(displaydata->DeviceName, &data->DeviceMode, रिक्त, CDS_FULLSCREEN, रिक्त);
    }
    यदि (status != DISP_CHANGE_SUCCESSFUL) {
        अचर वर्ण *reason = "Unknown reason";
        विकल्प (status) {
        पक्ष DISP_CHANGE_BADFLAGS:
            reason = "DISP_CHANGE_BADFLAGS";
            रोक;
        पक्ष DISP_CHANGE_BADMODE:
            reason = "DISP_CHANGE_BADMODE";
            रोक;
        पक्ष DISP_CHANGE_BADPARAM:
            reason = "DISP_CHANGE_BADPARAM";
            रोक;
        पक्ष DISP_CHANGE_FAILED:
            reason = "DISP_CHANGE_FAILED";
            रोक;
        }
        फर्काऊ SDL_SetError("ChangeDisplaySettingsEx() failed: %s", reason);
    }

#ifdef DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state after mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#endif

    EnumDisplaySettingsW(displaydata->DeviceName, ENUM_CURRENT_SETTINGS, &data->DeviceMode);
    WIN_UpdateDisplayMode(_this, displaydata->DeviceName, ENUM_CURRENT_SETTINGS, mode);
    फर्काऊ true;
}

शून्य WIN_RefreshDisplays(SDL_VideoDevice *_this)
{
    पूर्णाङ्क i;

    // Mark all displays as potentially invalid to detect
    // entries that have actually been removed
    लागि (i = 0; i < _this->अङ्क_displays; ++i) {
        SDL_DisplayData *internal = _this->displays[i]->internal;
        internal->state = DisplayRemoved;
    }

    // Enumerate displays to add any new ones and mark still
    // connected entries as valid
    WIN_AddDisplays(_this);

    // Delete any entries still marked as invalid, iterate
    // in reverse as each delete takes effect immediately
    लागि (i = _this->अङ्क_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DisplayData *internal = display->internal;
        यदि (internal->state == DisplayRemoved) {
            SDL_DelVideoDisplay(display->id, true);
        }
    }

    // Send events for any newly added displays
    लागि (i = 0; i < _this->अङ्क_displays; ++i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DisplayData *internal = display->internal;
        यदि (internal->state == DisplayAdded) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
        }
    }
}

शून्य WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this)
{
    // This almost never happens, so just go ahead and send update events for all displays
    लागि (पूर्णाङ्क i = 0; i < _this->अङ्क_displays; ++i) {
        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_CHANGED, 0, 0);
    }
}

शून्य WIN_QuitModes(SDL_VideoDevice *_this)
{
    // All fullscreen windows should have restored modes by now
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
