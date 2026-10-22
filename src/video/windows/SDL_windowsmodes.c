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

#जर defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

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
    जर (index == ENUM_CURRENT_SETTINGS && (hdc = CreateDCW(deviceName, रिक्त, रिक्त, रिक्त)) != रिक्त) {
        अक्षर bmi_data[आकार(BITMAPINFOHEADER) + 256 * आकार(RGBQUAD)];
        LPBITMAPINFO bmi;
        HBITMAP hbm;

        SDL_zeroa(bmi_data);
        bmi = (LPBITMAPINFO)bmi_data;
        bmi->bmiHeader.biSize = आकार(BITMAPINFOHEADER);

        hbm = CreateCompatibleBitmap(hdc, 1, 1);
        GetDIBits(hdc, hbm, 0, 1, रिक्त, bmi, DIB_RGB_COLORS);
        GetDIBits(hdc, hbm, 0, 1, रिक्त, bmi, DIB_RGB_COLORS);
        DeleteObject(hbm);
        DeleteDC(hdc);
        जर (bmi->bmiHeader.biCompression == BI_BITFIELDS) {
            निवड (*(Uint32 *)bmi->bmiColors) {
            स्थिती 0x00FF0000:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                थांबा;
            स्थिती 0x000000FF:
                mode->format = SDL_PIXELFORMAT_XBGR8888;
                थांबा;
            स्थिती 0xF800:
                mode->format = SDL_PIXELFORMAT_RGB565;
                थांबा;
            स्थिती 0x7C00:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                थांबा;
            }
        } अन्यथा जर (bmi->bmiHeader.biCompression == BI_RGB) {
            जर (bmi->bmiHeader.bi_Bit_मोजणी == 24) {
                mode->format = SDL_PIXELFORMAT_RGB24;
            } अन्यथा जर (bmi->bmiHeader.bi_Bit_मोजणी == 8) {
                mode->format = SDL_PIXELFORMAT_INDEX8;
            } अन्यथा जर (bmi->bmiHeader.bi_Bit_मोजणी == 4) {
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
            }
        }
    } अन्यथा जर (mode->format == SDL_PIXELFORMAT_UNKNOWN) {
        // FIXME: Can we tell what this will be?
        जर ((data->DeviceMode.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL) {
            निवड (data->DeviceMode.dmBitsPerPel) {
            स्थिती 32:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                थांबा;
            स्थिती 24:
                mode->format = SDL_PIXELFORMAT_RGB24;
                थांबा;
            स्थिती 16:
                mode->format = SDL_PIXELFORMAT_RGB565;
                थांबा;
            स्थिती 15:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                थांबा;
            स्थिती 8:
                mode->format = SDL_PIXELFORMAT_INDEX8;
                थांबा;
            स्थिती 4:
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
                थांबा;
            }
        }
    }
}

स्थिर शून्य *WIN_GetDXGIOutput(SDL_VideoDevice *_this, स्थिरांक WCHAR *DeviceName)
{
    शून्य *result = रिक्त;

#ifdef HAVE_DXGI_H
    स्थिरांक SDL_VideoData *videodata = (स्थिरांक SDL_VideoData *)_this->internal;
    पूर्णांक nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    जर (!videodata->pDXGIFactory) {
        परत रिक्त;
    }

    nAdapter = 0;
    पर्यंत (!result && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        पर्यंत (!result && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            जर (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                जर (SDL_wcscmp(outputDesc.DeviceName, DeviceName) == 0) {
                    result = pDXGIOutput;
                }
            }
            जर (pDXGIOutput != result) {
                IDXGIOutput_Release(pDXGIOutput);
            }
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }
#endif
    परत result;
}

स्थिर शून्य WIN_ReleaseDXGIOutput(शून्य *dxgi_output)
{
#ifdef HAVE_DXGI_H
    IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;

    जर (pDXGIOutput) {
        IDXGIOutput_Release(pDXGIOutput);
    }
#endif
}

स्थिर SDL_DisplayOrientation WIN_GetNaturalOrientation(DEVMODEW *mode)
{
    पूर्णांक width = mode->dmPelsWidth;
    पूर्णांक height = mode->dmPelsHeight;

    // Use unrotated width/height to guess orientation
    जर (mode->dmDisplayOrientation == DMDO_90 || mode->dmDisplayOrientation == DMDO_270) {
        पूर्णांक temp = width;
        width = height;
        height = temp;
    }

    जर (width >= height) {
        परत SDL_ORIENTATION_LANDSCAPE;
    } अन्यथा {
        परत SDL_ORIENTATION_PORTRAIT;
    }
}

स्थिर SDL_DisplayOrientation WIN_GetDisplayOrientation(DEVMODEW *mode)
{
    जर (WIN_GetNaturalOrientation(mode) == SDL_ORIENTATION_LANDSCAPE) {
        निवड (mode->dmDisplayOrientation) {
        स्थिती DMDO_DEFAULT:
            परत SDL_ORIENTATION_LANDSCAPE;
        स्थिती DMDO_90:
            परत SDL_ORIENTATION_PORTRAIT;
        स्थिती DMDO_180:
            परत SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        स्थिती DMDO_270:
            परत SDL_ORIENTATION_PORTRAIT_FLIPPED;
        पूर्वनिर्धारित:
            परत SDL_ORIENTATION_UNKNOWN;
        }
    } अन्यथा {
        निवड (mode->dmDisplayOrientation) {
        स्थिती DMDO_DEFAULT:
            परत SDL_ORIENTATION_PORTRAIT;
        स्थिती DMDO_90:
            परत SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        स्थिती DMDO_180:
            परत SDL_ORIENTATION_PORTRAIT_FLIPPED;
        स्थिती DMDO_270:
            परत SDL_ORIENTATION_LANDSCAPE;
        पूर्वनिर्धारित:
            परत SDL_ORIENTATION_UNKNOWN;
        }
    }
}

स्थिर शून्य WIN_GetRefreshRate(शून्य *dxgi_output, DEVMODEW *mode, पूर्णांक *numerator, पूर्णांक *denominator)
{
    // We're not currently using DXGI to query display modes, so fake NTSC timings
    निवड (mode->dmDisplayFrequency) {
    स्थिती 119:
    स्थिती 59:
    स्थिती 29:
        *numerator = (mode->dmDisplayFrequency + 1) * 1000;
        *denominator = 1001;
        थांबा;
    पूर्वनिर्धारित:
        *numerator = mode->dmDisplayFrequency;
        *denominator = 1;
        थांबा;
    }

#ifdef HAVE_DXGI_H
    जर (dxgi_output) {
        IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;
        DXGI_MODE_DESC modeToMatch;
        DXGI_MODE_DESC closestMatch;

        SDL_zero(modeToMatch);
        modeToMatch.Width = mode->dmPelsWidth;
        modeToMatch.Height = mode->dmPelsHeight;
        modeToMatch.RefreshRate.Numerator = *numerator;
        modeToMatch.RefreshRate.Denominator = *denominator;
        modeToMatch.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        जर (SUCCEEDED(IDXGIOutput_FindClosestMatchingMode(pDXGIOutput, &modeToMatch, &closestMatch, रिक्त))) {
            *numerator = closestMatch.RefreshRate.Numerator;
            *denominator = closestMatch.RefreshRate.Denominator;
        }
    }
#endif // HAVE_DXGI_H
}

स्थिर दशांश WIN_GetContentScale(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    पूर्णांक dpi = 0;

    स्थिरांक SDL_VideoData *videodata = (स्थिरांक SDL_VideoData *)_this->internal;
    जर (videodata->GetDpiForMonitor) {
        UINT hdpi_uint, vdpi_uint;
        जर (videodata->GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
            dpi = (पूर्णांक)hdpi_uint;
        }
    }
    जर (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(रिक्त);
        जर (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(रिक्त, hdc);
        }
    }
    जर (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    परत dpi / (दशांश)USER_DEFAULT_SCREEN_DPI;
}

स्थिर bool WIN_GetDisplayMode(SDL_VideoDevice *_this, शून्य *dxgi_output, HMONITOR hMonitor, LPCWSTR deviceName, DWORD index, SDL_DisplayMode *mode, SDL_DisplayOrientation *natural_orientation, SDL_DisplayOrientation *current_orientation)
{
    SDL_DisplayModeData *data;
    DEVMODEW devmode;

    devmode.dmSize = आकार(devmode);
    devmode.dmDriverExtra = 0;
    जर (!EnumDisplaySettingsW(deviceName, index, &devmode)) {
        परत false;
    }

    data = (SDL_DisplayModeData *)SDL_malloc(आकार(*data));
    जर (!data) {
        परत false;
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

    जर (natural_orientation) {
        *natural_orientation = WIN_GetNaturalOrientation(&devmode);
    }
    जर (current_orientation) {
        *current_orientation = WIN_GetDisplayOrientation(&devmode);
    }

    परत true;
}

स्थिर अक्षर *WIN_GetDisplayNameVista(SDL_VideoData *videodata, स्थिरांक WCHAR *deviceName)
{
    DISPLAYCONFIG_PATH_INFO *paths = रिक्त;
    DISPLAYCONFIG_MODE_INFO *modes = रिक्त;
    अक्षर *result = रिक्त;
    UINT32 path_मोजणी_2 = 0;
    UINT32 mode_मोजणी_2 = 0;
    UINT32 i;
    LONG rc;

    जर (!videodata->GetDisplayConfigBufferSizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        परत रिक्त;
    }

    करा {
        rc = videodata->GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &path_मोजणी_2, &mode_मोजणी_2);
        जर (rc != ERROR_SUCCESS) {
            जा WIN_GetDisplayNameVista_failed;
        }

        SDL_free(paths);
        SDL_free(modes);

        paths = (DISPLAYCONFIG_PATH_INFO *)SDL_malloc(आकार(DISPLAYCONFIG_PATH_INFO) * path_मोजणी_2);
        modes = (DISPLAYCONFIG_MODE_INFO *)SDL_malloc(आकार(DISPLAYCONFIG_MODE_INFO) * mode_मोजणी_2);
        जर ((!paths) || (!modes)) {
            जा WIN_GetDisplayNameVista_failed;
        }

        rc = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &path_मोजणी_2, paths, &mode_मोजणी_2, modes, 0);
    } पर्यंत (rc == ERROR_INSUFFICIENT_BUFFER);

    जर (rc == ERROR_SUCCESS) {
        साठी (i = 0; i < path_मोजणी_2; i++) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME sourceName;
            DISPLAYCONFIG_TARGET_DEVICE_NAME targetName;

            SDL_zero(sourceName);
            sourceName.header.adapterId = paths[i].targetInfo.adapterId;
            sourceName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            sourceName.header.size = आकार(sourceName);
            sourceName.header.id = paths[i].sourceInfo.id;
            rc = videodata->DisplayConfigGetDeviceInfo(&sourceName.header);
            जर (rc != ERROR_SUCCESS) {
                थांबा;
            } अन्यथा जर (SDL_wcscmp(deviceName, sourceName.viewGdiDeviceName) != 0) {
                सुरूठेवा;
            }

            SDL_zero(targetName);
            targetName.header.adapterId = paths[i].targetInfo.adapterId;
            targetName.header.id = paths[i].targetInfo.id;
            targetName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
            targetName.header.size = आकार(targetName);
            rc = videodata->DisplayConfigGetDeviceInfo(&targetName.header);
            जर (rc == ERROR_SUCCESS) {
                result = WIN_StringToUTF8W(targetName.monitorFriendlyDeviceName);
                /* if we got an empty string, treat it as failure so we'll fallback
                   to getting the generic name. */
                जर (result && (*result == '\0')) {
                    SDL_free(result);
                    result = रिक्त;
                }
            }
            थांबा;
        }
    }

    SDL_free(paths);
    SDL_free(modes);
    परत result;

WIN_GetDisplayNameVista_failed:
    SDL_free(result);
    SDL_free(paths);
    SDL_free(modes);
    परत रिक्त;
}

#ifdef HAVE_DXGI1_6_H
स्थिर bool WIN_GetMonitorDESC1(HMONITOR hMonitor, DXGI_OUTPUT_DESC1 *desc)
{
    प्रकारव्याख्या HRESULT (WINAPI *pfnCreateDXGIFactory1)(REFIID riid, शून्य **ppFactory);
    pfnCreateDXGIFactory1 pCreateDXGIFactory1 = रिक्त;
    SDL_SharedObject *hDXGIMod = रिक्त;
    bool found = false;

    hDXGIMod = SDL_LoadObject("dxgi.dll");
    जर (hDXGIMod) {
        pCreateDXGIFactory1 = (pfnCreateDXGIFactory1)SDL_LoadFunction(hDXGIMod, "CreateDXGIFactory1");
    }
    जर (pCreateDXGIFactory1) {
        स्थिर स्थिरांक GUID SDL_IID_IDXGIFactory1 = { 0x770aae78, 0xf26f, 0x4dba, { 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 } };
        स्थिर स्थिरांक GUID SDL_IID_IDXGIOutput6 = { 0x068346e8, 0xaaec, 0x4b84, { 0xad, 0xd7, 0x13, 0x7f, 0x51, 0x3f, 0x77, 0xa1 } };
        IDXGIFactory1 *dxgiFactory;

        जर (SUCCEEDED(pCreateDXGIFactory1(&SDL_IID_IDXGIFactory1, (शून्य **)&dxgiFactory))) {
            IDXGIAdapter1 *dxgiAdapter;
            UINT adapter = 0;
            पर्यंत (!found && SUCCEEDED(IDXGIFactory1_EnumAdapters1(dxgiFactory, adapter, &dxgiAdapter))) {
                IDXGIOutput *dxgiOutput;
                UINT output = 0;
                पर्यंत (!found && SUCCEEDED(IDXGIAdapter1_EnumOutputs(dxgiAdapter, output, &dxgiOutput))) {
                    IDXGIOutput6 *dxgiOutput6;
                    जर (SUCCEEDED(IDXGIOutput_QueryInterface(dxgiOutput, &SDL_IID_IDXGIOutput6, (शून्य **)&dxgiOutput6))) {
                        जर (SUCCEEDED(IDXGIOutput6_GetDesc1(dxgiOutput6, desc))) {
                            जर (desc->Monitor == hMonitor) {
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
    जर (hDXGIMod) {
        SDL_UnloadObject(hDXGIMod);
    }
    परत found;
}

स्थिर bool WIN_GetMonitorPathInfo(SDL_VideoData *videodata, HMONITOR hMonitor, DISPLAYCONFIG_PATH_INFO *path_info)
{
    LONG result;
    MONITORINFOEXW view_info;
    UINT32 i;
    UINT32 अंक_path_array_elements = 0;
    UINT32 अंक_mode_info_array_elements = 0;
    DISPLAYCONFIG_PATH_INFO *path_infos = रिक्त, *new_path_infos;
    DISPLAYCONFIG_MODE_INFO *mode_infos = रिक्त, *new_mode_infos;
    bool found = false;

    जर (!videodata->GetDisplayConfigBufferSizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        परत false;
    }

    SDL_zero(view_info);
    view_info.cbSize = आकार(view_info);
    जर (!GetMonitorInfoW(hMonitor, (MONITORINFO *)&view_info)) {
        जा done;
    }

    करा {
        जर (videodata->GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &अंक_path_array_elements, &अंक_mode_info_array_elements) != ERROR_SUCCESS) {
            SDL_free(path_infos);
            SDL_free(mode_infos);
            परत false;
        }

        new_path_infos = (DISPLAYCONFIG_PATH_INFO *)SDL_realloc(path_infos, अंक_path_array_elements * आकार(*path_infos));
        जर (!new_path_infos) {
            जा done;
        }
        path_infos = new_path_infos;

        new_mode_infos = (DISPLAYCONFIG_MODE_INFO *)SDL_realloc(mode_infos, अंक_mode_info_array_elements * आकार(*mode_infos));
        जर (!new_mode_infos) {
            जा done;
        }
        mode_infos = new_mode_infos;

        result = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &अंक_path_array_elements, path_infos, &अंक_mode_info_array_elements, mode_infos, रिक्त);

    } पर्यंत (result == ERROR_INSUFFICIENT_BUFFER);

    जर (result == ERROR_SUCCESS) {
        साठी (i = 0; i < अंक_path_array_elements; ++i) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME device_name;

            SDL_zero(device_name);
            device_name.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            device_name.header.size = आकार(device_name);
            device_name.header.adapterId = path_infos[i].sourceInfo.adapterId;
            device_name.header.id = path_infos[i].sourceInfo.id;
            जर (videodata->DisplayConfigGetDeviceInfo(&device_name.header) == ERROR_SUCCESS) {
                जर (SDL_wcscmp(view_info.szDevice, device_name.viewGdiDeviceName) == 0) {
                    SDL_copyp(path_info, &path_infos[i]);
                    found = true;
                    थांबा;
                }
            }
        }
    }

done:
    SDL_free(path_infos);
    SDL_free(mode_infos);

    परत found;
}

स्थिर दशांश WIN_GetSDRWhitePoint(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    DISPLAYCONFIG_PATH_INFO path_info;
    SDL_VideoData *videodata = _this->internal;
    दशांश SDR_white_level = 1.0f;

    जर (WIN_GetMonitorPathInfo(videodata, hMonitor, &path_info)) {
        /* workarounds for https://github.com/libsdl-org/SDL/issues/11193 */
        संरचना SDL_DISPLAYCONFIG_SDR_WHITE_LEVEL {
          DISPLAYCONFIG_DEVICE_INFO_HEADER header;
          ULONG SDRWhiteLevel;
        } white_level;
        #define DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL 11

        SDL_zero(white_level);
        white_level.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
        white_level.header.size = आकार(white_level);
        white_level.header.adapterId = path_info.targetInfo.adapterId;
        white_level.header.id = path_info.targetInfo.id;
        // WIN_GetMonitorPathInfo() succeeded: DisplayConfigGetDeviceInfo is not NULL
        जर (videodata->DisplayConfigGetDeviceInfo(&white_level.header) == ERROR_SUCCESS &&
            white_level.SDRWhiteLevel > 0) {
            SDR_white_level = (white_level.SDRWhiteLevel / 1000.0f);
        }
    }
    परत SDR_white_level;
}

स्थिर शून्य WIN_GetHDRProperties(SDL_VideoDevice *_this, HMONITOR hMonitor, SDL_HDROutputProperties *HDR)
{
    DXGI_OUTPUT_DESC1 desc;

    SDL_zerop(HDR);

    जर (WIN_GetMonitorDESC1(hMonitor, &desc)) {
        जर (desc.ColorSpace == DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020) {
            HDR->SDR_white_level = WIN_GetSDRWhitePoint(_this, hMonitor);
            HDR->HDR_headroom = (desc.MaxLuminance / SCRGB_NITS) / HDR->SDR_white_level;
        }
    }
}
#endif // HAVE_DXGI1_6_H

स्थिर शून्य WIN_AddDisplay(SDL_VideoDevice *_this, HMONITOR hMonitor, स्थिरांक MONITORINFOEXW *info, पूर्णांक *display_index)
{
    पूर्णांक i, index = *display_index;
    SDL_VideoDisplay display;
    SDL_DisplayData *displaydata;
    शून्य *dxgi_output = रिक्त;
    SDL_DisplayMode mode;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    दशांश content_scale = WIN_GetContentScale(_this, hMonitor);

#ifdef DEBUG_MODES
    SDL_Log("Display: %s", WIN_StringToUTF8W(info->szDevice));
#endif

    dxgi_output = WIN_GetDXGIOutput(_this, info->szDevice);
    bool found = WIN_GetDisplayMode(_this, dxgi_output, hMonitor, info->szDevice, ENUM_CURRENT_SETTINGS, &mode, &natural_orientation, &current_orientation);
    WIN_ReleaseDXGIOutput(dxgi_output);
    जर (!found) {
        परत;
    }

    // Prevent adding duplicate displays. Do this after we know the display is
    // ready to be added to allow any displays that we can't fully query to be
    // removed
    साठी (i = 0; i < _this->अंक_displays; ++i) {
        SDL_DisplayData *internal = _this->displays[i]->internal;
        जर (SDL_wcscmp(internal->DeviceName, info->szDevice) == 0) {
            bool moved = (index != i);
            bool changed_bounds = false;

            जर (internal->state != DisplayRemoved) {
                // We've already enumerated this display, don't move it
                जा cleanup;
            }

            जर (index >= _this->अंक_displays) {
                // This should never happen due to the check above, but just in case...
                जा cleanup;
            }

            जर (moved) {
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

            जर (!_this->setting_display_mode) {
                SDL_VideoDisplay *existing_display = _this->displays[i];
                SDL_Rect bounds;

                SDL_ResetFullscreenDisplayModes(existing_display);
                SDL_SetDesktopDisplayMode(existing_display, &mode);
                // The mode is owned by the video subsystem
                mode.internal = रिक्त;
                जर (WIN_GetDisplayBounds(_this, existing_display, &bounds) &&
                    SDL_memcmp(&internal->bounds, &bounds, आकार(bounds)) != 0) {
                    changed_bounds = true;
                    SDL_copyp(&internal->bounds, &bounds);
                }
                जर (moved || changed_bounds) {
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
            जा done;
        }
    }

    displaydata = (SDL_DisplayData *)SDL_calloc(1, आकार(*displaydata));
    जर (!displaydata) {
        जा cleanup;
    }
    SDL_memcpy(displaydata->DeviceName, info->szDevice, आकार(displaydata->DeviceName));
    displaydata->MonitorHandle = hMonitor;
    displaydata->state = DisplayAdded;

    SDL_zero(display);
    display.name = WIN_GetDisplayNameVista(_this->internal, info->szDevice);
    जर (!display.name) {
        DISPLAY_DEVICEW device;
        SDL_zero(device);
        device.cb = आकार(device);
        जर (EnumDisplayDevicesW(info->szDevice, 0, &device, 0)) {
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
    जर (displayID) {
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

प्रकारव्याख्या संरचना _WIN_AddDisplaysData
{
    SDL_VideoDevice *video_device;
    पूर्णांक display_index;
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
    info.cbSize = आकार(info);

    जर (GetMonitorInfoW(hMonitor, (LPMONITORINFO)&info) != 0) {
        स्थिरांक bool is_primary = ((info.dwFlags & MONITORINFOF_PRIMARY) == MONITORINFOF_PRIMARY);

        जर (is_primary == data->want_primary) {
            WIN_AddDisplay(data->video_device, hMonitor, &info, &data->display_index);
        }
    }

    // continue enumeration
    परत TRUE;
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

    जर (_this->अंक_displays == 0) {
        परत SDL_SetError("No displays available");
    }
    परत true;
}

bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    स्थिरांक SDL_DisplayData *data = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cbSize = आकार(MONITORINFO);
    rc = GetMonitorInfo(data->MonitorHandle, &minfo);

    जर (!rc) {
        परत SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcMonitor.डावा;
    rect->y = minfo.rcMonitor.शीर्ष;
    rect->w = minfo.rcMonitor.उजवा - minfo.rcMonitor.डावा;
    rect->h = minfo.rcMonitor.bottom - minfo.rcMonitor.शीर्ष;

    परत true;
}

bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    स्थिरांक SDL_DisplayData *data = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cbSize = आकार(MONITORINFO);
    rc = GetMonitorInfo(data->MonitorHandle, &minfo);

    जर (!rc) {
        परत SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcWork.डावा;
    rect->y = minfo.rcWork.शीर्ष;
    rect->w = minfo.rcWork.उजवा - minfo.rcWork.डावा;
    rect->h = minfo.rcWork.bottom - minfo.rcWork.शीर्ष;

    परत true;
}

bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_DisplayData *data = display->internal;
    शून्य *dxgi_output;
    DWORD i;
    SDL_DisplayMode mode;

    dxgi_output = WIN_GetDXGIOutput(_this, data->DeviceName);

    // Make sure we add the current mode to the list in case it's a custom mode that doesn't enumerate
    साठी (i = ENUM_CURRENT_SETTINGS; ; ++i) {
        जर (!WIN_GetDisplayMode(_this, dxgi_output, data->MonitorHandle, data->DeviceName, i, &mode, रिक्त, रिक्त)) {
            थांबा;
        }
        जर (SDL_ISPIXELFORMAT_INDEXED(mode.format)) {
            // We don't support palettized modes now
            SDL_free(mode.internal);
            सुरूठेवा;
        }
        जर (mode.format != SDL_PIXELFORMAT_UNKNOWN) {
            जर (!SDL_AddFullscreenDisplayMode(display, &mode)) {
                SDL_free(mode.internal);
            }
        } अन्यथा {
            SDL_free(mode.internal);
        }
    }

    WIN_ReleaseDXGIOutput(dxgi_output);

    परत true;
}

#ifdef DEBUG_MODES
स्थिर शून्य WIN_LogMonitor(SDL_VideoDevice *_this, HMONITOR mon)
{
    स्थिरांक SDL_VideoData *vid_data = (स्थिरांक SDL_VideoData *)_this->internal;
    MONITORINFOEX minfo;
    UINT xdpi = 0, ydpi = 0;
    अक्षर *name_utf8;

    जर (vid_data->GetDpiForMonitor) {
        vid_data->GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &xdpi, &ydpi);
    }

    SDL_zero(minfo);
    minfo.cbSize = आकार(minfo);
    GetMonitorInfo(mon, (LPMONITORINFO)&minfo);

    name_utf8 = WIN_StringToUTF8(minfo.szDevice);

    SDL_Log("WIN_LogMonitor: monitor \"%s\": dpi: %d windows screen coordinates: %d, %d, %dx%d",
            name_utf8,
            xdpi,
            minfo.rcMonitor.डावा,
            minfo.rcMonitor.शीर्ष,
            minfo.rcMonitor.उजवा - minfo.rcMonitor.डावा,
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
    जर (mode->internal == display->desktop_mode.internal) {
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
    जर (status != DISP_CHANGE_SUCCESSFUL) {
        स्थिरांक अक्षर *reason = "Unknown reason";
        निवड (status) {
        स्थिती DISP_CHANGE_BADFLAGS:
            reason = "DISP_CHANGE_BADFLAGS";
            थांबा;
        स्थिती DISP_CHANGE_BADMODE:
            reason = "DISP_CHANGE_BADMODE";
            थांबा;
        स्थिती DISP_CHANGE_BADPARAM:
            reason = "DISP_CHANGE_BADPARAM";
            थांबा;
        स्थिती DISP_CHANGE_FAILED:
            reason = "DISP_CHANGE_FAILED";
            थांबा;
        }
        परत SDL_SetError("ChangeDisplaySettingsEx() failed: %s", reason);
    }

#ifdef DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state after mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#endif

    EnumDisplaySettingsW(displaydata->DeviceName, ENUM_CURRENT_SETTINGS, &data->DeviceMode);
    WIN_UpdateDisplayMode(_this, displaydata->DeviceName, ENUM_CURRENT_SETTINGS, mode);
    परत true;
}

शून्य WIN_RefreshDisplays(SDL_VideoDevice *_this)
{
    पूर्णांक i;

    // Mark all displays as potentially invalid to detect
    // entries that have actually been removed
    साठी (i = 0; i < _this->अंक_displays; ++i) {
        SDL_DisplayData *internal = _this->displays[i]->internal;
        internal->state = DisplayRemoved;
    }

    // Enumerate displays to add any new ones and mark still
    // connected entries as valid
    WIN_AddDisplays(_this);

    // Delete any entries still marked as invalid, iterate
    // in reverse as each delete takes effect immediately
    साठी (i = _this->अंक_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DisplayData *internal = display->internal;
        जर (internal->state == DisplayRemoved) {
            SDL_DelVideoDisplay(display->id, true);
        }
    }

    // Send events for any newly added displays
    साठी (i = 0; i < _this->अंक_displays; ++i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DisplayData *internal = display->internal;
        जर (internal->state == DisplayAdded) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
        }
    }
}

शून्य WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this)
{
    // This almost never happens, so just go ahead and send update events for all displays
    साठी (पूर्णांक i = 0; i < _this->अंक_displays; ++i) {
        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_CHANGED, 0, 0);
    }
}

शून्य WIN_QuitModes(SDL_VideoDevice *_this)
{
    // All fullscreen windows should have restored modes by now
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
