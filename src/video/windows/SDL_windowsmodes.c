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
#അന്തര്ഭാവ "SDL_internal.h"

#എങ്കിൽ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#അന്തര്ഭാവ "SDL_windowsvideo.h"
#അന്തര്ഭാവ "../../events/SDL_displayevents_c.h"
#അന്തര്ഭാവ "../SDL_pixels_c.h"

#ifdef HAVE_DXGI1_6_H
#define COBJMACROS
#അന്തര്ഭാവ <dxgi1_6.h>
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

സ്ഥിതം ശൂന്യം WIN_UpdateDisplayMode(SDL_VideoDevice *_this, LPCWSTR deviceName, DWORD index, SDL_DisplayMode *mode)
{
    SDL_DisplayModeData *data = (SDL_DisplayModeData *)mode->internal;
    HDC hdc;

    data->DeviceMode.dmFields = (DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS);

    // NOLINTNEXTLINE(bugprone-assignment-in-if-condition): No simple way to extract the assignment
    എങ്കിൽ (index == ENUM_CURRENT_SETTINGS && (hdc = CreateDCW(deviceName, ശൂന്യ, ശൂന്യ, ശൂന്യ)) != ശൂന്യ) {
        അക്ഷരം bmi_data[വലുപ്പം(BITMAPINFOHEADER) + 256 * വലുപ്പം(RGBQUAD)];
        LPBITMAPINFO bmi;
        HBITMAP hbm;

        SDL_zeroa(bmi_data);
        bmi = (LPBITMAPINFO)bmi_data;
        bmi->bmiHeader.biSize = വലുപ്പം(BITMAPINFOHEADER);

        hbm = CreateCompatibleBitmap(hdc, 1, 1);
        GetDIBits(hdc, hbm, 0, 1, ശൂന്യ, bmi, DIB_RGB_COLORS);
        GetDIBits(hdc, hbm, 0, 1, ശൂന്യ, bmi, DIB_RGB_COLORS);
        DeleteObject(hbm);
        DeleteDC(hdc);
        എങ്കിൽ (bmi->bmiHeader.biCompression == BI_BITFIELDS) {
            തിരഞ്ഞെടുപ്പ് (*(Uint32 *)bmi->bmiColors) {
            അവസ്ഥ 0x00FF0000:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                നിർത്തുക;
            അവസ്ഥ 0x000000FF:
                mode->format = SDL_PIXELFORMAT_XBGR8888;
                നിർത്തുക;
            അവസ്ഥ 0xF800:
                mode->format = SDL_PIXELFORMAT_RGB565;
                നിർത്തുക;
            അവസ്ഥ 0x7C00:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                നിർത്തുക;
            }
        } അല്ലെങ്കിൽ എങ്കിൽ (bmi->bmiHeader.biCompression == BI_RGB) {
            എങ്കിൽ (bmi->bmiHeader.bi_Bit_എണ്ണം == 24) {
                mode->format = SDL_PIXELFORMAT_RGB24;
            } അല്ലെങ്കിൽ എങ്കിൽ (bmi->bmiHeader.bi_Bit_എണ്ണം == 8) {
                mode->format = SDL_PIXELFORMAT_INDEX8;
            } അല്ലെങ്കിൽ എങ്കിൽ (bmi->bmiHeader.bi_Bit_എണ്ണം == 4) {
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
            }
        }
    } അല്ലെങ്കിൽ എങ്കിൽ (mode->format == SDL_PIXELFORMAT_UNKNOWN) {
        // FIXME: Can we tell what this will be?
        എങ്കിൽ ((data->DeviceMode.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL) {
            തിരഞ്ഞെടുപ്പ് (data->DeviceMode.dmBitsPerPel) {
            അവസ്ഥ 32:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                നിർത്തുക;
            അവസ്ഥ 24:
                mode->format = SDL_PIXELFORMAT_RGB24;
                നിർത്തുക;
            അവസ്ഥ 16:
                mode->format = SDL_PIXELFORMAT_RGB565;
                നിർത്തുക;
            അവസ്ഥ 15:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                നിർത്തുക;
            അവസ്ഥ 8:
                mode->format = SDL_PIXELFORMAT_INDEX8;
                നിർത്തുക;
            അവസ്ഥ 4:
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
                നിർത്തുക;
            }
        }
    }
}

സ്ഥിതം ശൂന്യം *WIN_GetDXGIOutput(SDL_VideoDevice *_this, സ്ഥിരം WCHAR *DeviceName)
{
    ശൂന്യം *result = ശൂന്യ;

#ifdef HAVE_DXGI_H
    സ്ഥിരം SDL_VideoData *videodata = (സ്ഥിരം SDL_VideoData *)_this->internal;
    പൂർണ്ണസംഖ്യ nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    എങ്കിൽ (!videodata->pDXGIFactory) {
        തിരികെ ശൂന്യ;
    }

    nAdapter = 0;
    ആകുമ്പോൾ (!result && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        ആകുമ്പോൾ (!result && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            എങ്കിൽ (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                എങ്കിൽ (SDL_wcscmp(outputDesc.DeviceName, DeviceName) == 0) {
                    result = pDXGIOutput;
                }
            }
            എങ്കിൽ (pDXGIOutput != result) {
                IDXGIOutput_Release(pDXGIOutput);
            }
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }
#endif
    തിരികെ result;
}

സ്ഥിതം ശൂന്യം WIN_ReleaseDXGIOutput(ശൂന്യം *dxgi_output)
{
#ifdef HAVE_DXGI_H
    IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;

    എങ്കിൽ (pDXGIOutput) {
        IDXGIOutput_Release(pDXGIOutput);
    }
#endif
}

സ്ഥിതം SDL_DisplayOrientation WIN_GetNaturalOrientation(DEVMODEW *mode)
{
    പൂർണ്ണസംഖ്യ width = mode->dmPelsWidth;
    പൂർണ്ണസംഖ്യ height = mode->dmPelsHeight;

    // Use unrotated width/height to guess orientation
    എങ്കിൽ (mode->dmDisplayOrientation == DMDO_90 || mode->dmDisplayOrientation == DMDO_270) {
        പൂർണ്ണസംഖ്യ temp = width;
        width = height;
        height = temp;
    }

    എങ്കിൽ (width >= height) {
        തിരികെ SDL_ORIENTATION_LANDSCAPE;
    } അല്ലെങ്കിൽ {
        തിരികെ SDL_ORIENTATION_PORTRAIT;
    }
}

സ്ഥിതം SDL_DisplayOrientation WIN_GetDisplayOrientation(DEVMODEW *mode)
{
    എങ്കിൽ (WIN_GetNaturalOrientation(mode) == SDL_ORIENTATION_LANDSCAPE) {
        തിരഞ്ഞെടുപ്പ് (mode->dmDisplayOrientation) {
        അവസ്ഥ DMDO_DEFAULT:
            തിരികെ SDL_ORIENTATION_LANDSCAPE;
        അവസ്ഥ DMDO_90:
            തിരികെ SDL_ORIENTATION_PORTRAIT;
        അവസ്ഥ DMDO_180:
            തിരികെ SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        അവസ്ഥ DMDO_270:
            തിരികെ SDL_ORIENTATION_PORTRAIT_FLIPPED;
        സ്ഥിരസ്ഥിതി:
            തിരികെ SDL_ORIENTATION_UNKNOWN;
        }
    } അല്ലെങ്കിൽ {
        തിരഞ്ഞെടുപ്പ് (mode->dmDisplayOrientation) {
        അവസ്ഥ DMDO_DEFAULT:
            തിരികെ SDL_ORIENTATION_PORTRAIT;
        അവസ്ഥ DMDO_90:
            തിരികെ SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        അവസ്ഥ DMDO_180:
            തിരികെ SDL_ORIENTATION_PORTRAIT_FLIPPED;
        അവസ്ഥ DMDO_270:
            തിരികെ SDL_ORIENTATION_LANDSCAPE;
        സ്ഥിരസ്ഥിതി:
            തിരികെ SDL_ORIENTATION_UNKNOWN;
        }
    }
}

സ്ഥിതം ശൂന്യം WIN_GetRefreshRate(ശൂന്യം *dxgi_output, DEVMODEW *mode, പൂർണ്ണസംഖ്യ *numerator, പൂർണ്ണസംഖ്യ *denominator)
{
    // We're not currently using DXGI to query display modes, so fake NTSC timings
    തിരഞ്ഞെടുപ്പ് (mode->dmDisplayFrequency) {
    അവസ്ഥ 119:
    അവസ്ഥ 59:
    അവസ്ഥ 29:
        *numerator = (mode->dmDisplayFrequency + 1) * 1000;
        *denominator = 1001;
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        *numerator = mode->dmDisplayFrequency;
        *denominator = 1;
        നിർത്തുക;
    }

#ifdef HAVE_DXGI_H
    എങ്കിൽ (dxgi_output) {
        IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;
        DXGI_MODE_DESC modeToMatch;
        DXGI_MODE_DESC closestMatch;

        SDL_zero(modeToMatch);
        modeToMatch.Width = mode->dmPelsWidth;
        modeToMatch.Height = mode->dmPelsHeight;
        modeToMatch.RefreshRate.Numerator = *numerator;
        modeToMatch.RefreshRate.Denominator = *denominator;
        modeToMatch.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        എങ്കിൽ (SUCCEEDED(IDXGIOutput_FindClosestMatchingMode(pDXGIOutput, &modeToMatch, &closestMatch, ശൂന്യ))) {
            *numerator = closestMatch.RefreshRate.Numerator;
            *denominator = closestMatch.RefreshRate.Denominator;
        }
    }
#endif // HAVE_DXGI_H
}

സ്ഥിതം ദശാംശം WIN_GetContentScale(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    പൂർണ്ണസംഖ്യ dpi = 0;

    സ്ഥിരം SDL_VideoData *videodata = (സ്ഥിരം SDL_VideoData *)_this->internal;
    എങ്കിൽ (videodata->GetDpiForMonitor) {
        UINT hdpi_uint, vdpi_uint;
        എങ്കിൽ (videodata->GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
            dpi = (പൂർണ്ണസംഖ്യ)hdpi_uint;
        }
    }
    എങ്കിൽ (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(ശൂന്യ);
        എങ്കിൽ (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(ശൂന്യ, hdc);
        }
    }
    എങ്കിൽ (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    തിരികെ dpi / (ദശാംശം)USER_DEFAULT_SCREEN_DPI;
}

സ്ഥിതം bool WIN_GetDisplayMode(SDL_VideoDevice *_this, ശൂന്യം *dxgi_output, HMONITOR hMonitor, LPCWSTR deviceName, DWORD index, SDL_DisplayMode *mode, SDL_DisplayOrientation *natural_orientation, SDL_DisplayOrientation *current_orientation)
{
    SDL_DisplayModeData *data;
    DEVMODEW devmode;

    devmode.dmSize = വലുപ്പം(devmode);
    devmode.dmDriverExtra = 0;
    എങ്കിൽ (!EnumDisplaySettingsW(deviceName, index, &devmode)) {
        തിരികെ false;
    }

    data = (SDL_DisplayModeData *)SDL_malloc(വലുപ്പം(*data));
    എങ്കിൽ (!data) {
        തിരികെ false;
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

    എങ്കിൽ (natural_orientation) {
        *natural_orientation = WIN_GetNaturalOrientation(&devmode);
    }
    എങ്കിൽ (current_orientation) {
        *current_orientation = WIN_GetDisplayOrientation(&devmode);
    }

    തിരികെ true;
}

സ്ഥിതം അക്ഷരം *WIN_GetDisplayNameVista(SDL_VideoData *videodata, സ്ഥിരം WCHAR *deviceName)
{
    DISPLAYCONFIG_PATH_INFO *paths = ശൂന്യ;
    DISPLAYCONFIG_MODE_INFO *modes = ശൂന്യ;
    അക്ഷരം *result = ശൂന്യ;
    UINT32 path_എണ്ണം_2 = 0;
    UINT32 mode_എണ്ണം_2 = 0;
    UINT32 i;
    LONG rc;

    എങ്കിൽ (!videodata->GetDisplayConfigBufferSizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        തിരികെ ശൂന്യ;
    }

    ചെയ്യുക {
        rc = videodata->GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &path_എണ്ണം_2, &mode_എണ്ണം_2);
        എങ്കിൽ (rc != ERROR_SUCCESS) {
            പോകുക WIN_GetDisplayNameVista_failed;
        }

        SDL_free(paths);
        SDL_free(modes);

        paths = (DISPLAYCONFIG_PATH_INFO *)SDL_malloc(വലുപ്പം(DISPLAYCONFIG_PATH_INFO) * path_എണ്ണം_2);
        modes = (DISPLAYCONFIG_MODE_INFO *)SDL_malloc(വലുപ്പം(DISPLAYCONFIG_MODE_INFO) * mode_എണ്ണം_2);
        എങ്കിൽ ((!paths) || (!modes)) {
            പോകുക WIN_GetDisplayNameVista_failed;
        }

        rc = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &path_എണ്ണം_2, paths, &mode_എണ്ണം_2, modes, 0);
    } ആകുമ്പോൾ (rc == ERROR_INSUFFICIENT_BUFFER);

    എങ്കിൽ (rc == ERROR_SUCCESS) {
        വേണ്ടി (i = 0; i < path_എണ്ണം_2; i++) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME sourceName;
            DISPLAYCONFIG_TARGET_DEVICE_NAME targetName;

            SDL_zero(sourceName);
            sourceName.header.adapterId = paths[i].targetInfo.adapterId;
            sourceName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            sourceName.header.size = വലുപ്പം(sourceName);
            sourceName.header.id = paths[i].sourceInfo.id;
            rc = videodata->DisplayConfigGetDeviceInfo(&sourceName.header);
            എങ്കിൽ (rc != ERROR_SUCCESS) {
                നിർത്തുക;
            } അല്ലെങ്കിൽ എങ്കിൽ (SDL_wcscmp(deviceName, sourceName.viewGdiDeviceName) != 0) {
                തുടരുക;
            }

            SDL_zero(targetName);
            targetName.header.adapterId = paths[i].targetInfo.adapterId;
            targetName.header.id = paths[i].targetInfo.id;
            targetName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
            targetName.header.size = വലുപ്പം(targetName);
            rc = videodata->DisplayConfigGetDeviceInfo(&targetName.header);
            എങ്കിൽ (rc == ERROR_SUCCESS) {
                result = WIN_StringToUTF8W(targetName.monitorFriendlyDeviceName);
                /* if we got an empty string, treat it as failure so we'll fallback
                   to getting the generic name. */
                എങ്കിൽ (result && (*result == '\0')) {
                    SDL_free(result);
                    result = ശൂന്യ;
                }
            }
            നിർത്തുക;
        }
    }

    SDL_free(paths);
    SDL_free(modes);
    തിരികെ result;

WIN_GetDisplayNameVista_failed:
    SDL_free(result);
    SDL_free(paths);
    SDL_free(modes);
    തിരികെ ശൂന്യ;
}

#ifdef HAVE_DXGI1_6_H
സ്ഥിതം bool WIN_GetMonitorDESC1(HMONITOR hMonitor, DXGI_OUTPUT_DESC1 *desc)
{
    തരനിർവചനം HRESULT (WINAPI *pfnCreateDXGIFactory1)(REFIID riid, ശൂന്യം **ppFactory);
    pfnCreateDXGIFactory1 pCreateDXGIFactory1 = ശൂന്യ;
    SDL_SharedObject *hDXGIMod = ശൂന്യ;
    bool found = false;

    hDXGIMod = SDL_LoadObject("dxgi.dll");
    എങ്കിൽ (hDXGIMod) {
        pCreateDXGIFactory1 = (pfnCreateDXGIFactory1)SDL_LoadFunction(hDXGIMod, "CreateDXGIFactory1");
    }
    എങ്കിൽ (pCreateDXGIFactory1) {
        സ്ഥിതം സ്ഥിരം GUID SDL_IID_IDXGIFactory1 = { 0x770aae78, 0xf26f, 0x4dba, { 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 } };
        സ്ഥിതം സ്ഥിരം GUID SDL_IID_IDXGIOutput6 = { 0x068346e8, 0xaaec, 0x4b84, { 0xad, 0xd7, 0x13, 0x7f, 0x51, 0x3f, 0x77, 0xa1 } };
        IDXGIFactory1 *dxgiFactory;

        എങ്കിൽ (SUCCEEDED(pCreateDXGIFactory1(&SDL_IID_IDXGIFactory1, (ശൂന്യം **)&dxgiFactory))) {
            IDXGIAdapter1 *dxgiAdapter;
            UINT adapter = 0;
            ആകുമ്പോൾ (!found && SUCCEEDED(IDXGIFactory1_EnumAdapters1(dxgiFactory, adapter, &dxgiAdapter))) {
                IDXGIOutput *dxgiOutput;
                UINT output = 0;
                ആകുമ്പോൾ (!found && SUCCEEDED(IDXGIAdapter1_EnumOutputs(dxgiAdapter, output, &dxgiOutput))) {
                    IDXGIOutput6 *dxgiOutput6;
                    എങ്കിൽ (SUCCEEDED(IDXGIOutput_QueryInterface(dxgiOutput, &SDL_IID_IDXGIOutput6, (ശൂന്യം **)&dxgiOutput6))) {
                        എങ്കിൽ (SUCCEEDED(IDXGIOutput6_GetDesc1(dxgiOutput6, desc))) {
                            എങ്കിൽ (desc->Monitor == hMonitor) {
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
    എങ്കിൽ (hDXGIMod) {
        SDL_UnloadObject(hDXGIMod);
    }
    തിരികെ found;
}

സ്ഥിതം bool WIN_GetMonitorPathInfo(SDL_VideoData *videodata, HMONITOR hMonitor, DISPLAYCONFIG_PATH_INFO *path_info)
{
    LONG result;
    MONITORINFOEXW view_info;
    UINT32 i;
    UINT32 അക്കം_path_array_elements = 0;
    UINT32 അക്കം_mode_info_array_elements = 0;
    DISPLAYCONFIG_PATH_INFO *path_infos = ശൂന്യ, *new_path_infos;
    DISPLAYCONFIG_MODE_INFO *mode_infos = ശൂന്യ, *new_mode_infos;
    bool found = false;

    എങ്കിൽ (!videodata->GetDisplayConfigBufferSizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        തിരികെ false;
    }

    SDL_zero(view_info);
    view_info.cbSize = വലുപ്പം(view_info);
    എങ്കിൽ (!GetMonitorInfoW(hMonitor, (MONITORINFO *)&view_info)) {
        പോകുക done;
    }

    ചെയ്യുക {
        എങ്കിൽ (videodata->GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &അക്കം_path_array_elements, &അക്കം_mode_info_array_elements) != ERROR_SUCCESS) {
            SDL_free(path_infos);
            SDL_free(mode_infos);
            തിരികെ false;
        }

        new_path_infos = (DISPLAYCONFIG_PATH_INFO *)SDL_realloc(path_infos, അക്കം_path_array_elements * വലുപ്പം(*path_infos));
        എങ്കിൽ (!new_path_infos) {
            പോകുക done;
        }
        path_infos = new_path_infos;

        new_mode_infos = (DISPLAYCONFIG_MODE_INFO *)SDL_realloc(mode_infos, അക്കം_mode_info_array_elements * വലുപ്പം(*mode_infos));
        എങ്കിൽ (!new_mode_infos) {
            പോകുക done;
        }
        mode_infos = new_mode_infos;

        result = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &അക്കം_path_array_elements, path_infos, &അക്കം_mode_info_array_elements, mode_infos, ശൂന്യ);

    } ആകുമ്പോൾ (result == ERROR_INSUFFICIENT_BUFFER);

    എങ്കിൽ (result == ERROR_SUCCESS) {
        വേണ്ടി (i = 0; i < അക്കം_path_array_elements; ++i) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME device_name;

            SDL_zero(device_name);
            device_name.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            device_name.header.size = വലുപ്പം(device_name);
            device_name.header.adapterId = path_infos[i].sourceInfo.adapterId;
            device_name.header.id = path_infos[i].sourceInfo.id;
            എങ്കിൽ (videodata->DisplayConfigGetDeviceInfo(&device_name.header) == ERROR_SUCCESS) {
                എങ്കിൽ (SDL_wcscmp(view_info.szDevice, device_name.viewGdiDeviceName) == 0) {
                    SDL_copyp(path_info, &path_infos[i]);
                    found = true;
                    നിർത്തുക;
                }
            }
        }
    }

done:
    SDL_free(path_infos);
    SDL_free(mode_infos);

    തിരികെ found;
}

സ്ഥിതം ദശാംശം WIN_GetSDRWhitePoint(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    DISPLAYCONFIG_PATH_INFO path_info;
    SDL_VideoData *videodata = _this->internal;
    ദശാംശം SDR_white_level = 1.0f;

    എങ്കിൽ (WIN_GetMonitorPathInfo(videodata, hMonitor, &path_info)) {
        /* workarounds for https://github.com/libsdl-org/SDL/issues/11193 */
        ഘടന SDL_DISPLAYCONFIG_SDR_WHITE_LEVEL {
          DISPLAYCONFIG_DEVICE_INFO_HEADER header;
          ULONG SDRWhiteLevel;
        } white_level;
        #define DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL 11

        SDL_zero(white_level);
        white_level.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
        white_level.header.size = വലുപ്പം(white_level);
        white_level.header.adapterId = path_info.targetInfo.adapterId;
        white_level.header.id = path_info.targetInfo.id;
        // WIN_GetMonitorPathInfo() succeeded: DisplayConfigGetDeviceInfo is not NULL
        എങ്കിൽ (videodata->DisplayConfigGetDeviceInfo(&white_level.header) == ERROR_SUCCESS &&
            white_level.SDRWhiteLevel > 0) {
            SDR_white_level = (white_level.SDRWhiteLevel / 1000.0f);
        }
    }
    തിരികെ SDR_white_level;
}

സ്ഥിതം ശൂന്യം WIN_GetHDRProperties(SDL_VideoDevice *_this, HMONITOR hMonitor, SDL_HDROutputProperties *HDR)
{
    DXGI_OUTPUT_DESC1 desc;

    SDL_zerop(HDR);

    എങ്കിൽ (WIN_GetMonitorDESC1(hMonitor, &desc)) {
        എങ്കിൽ (desc.ColorSpace == DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020) {
            HDR->SDR_white_level = WIN_GetSDRWhitePoint(_this, hMonitor);
            HDR->HDR_headroom = (desc.MaxLuminance / SCRGB_NITS) / HDR->SDR_white_level;
        }
    }
}
#endif // HAVE_DXGI1_6_H

സ്ഥിതം ശൂന്യം WIN_AddDisplay(SDL_VideoDevice *_this, HMONITOR hMonitor, സ്ഥിരം MONITORINFOEXW *info, പൂർണ്ണസംഖ്യ *display_index)
{
    പൂർണ്ണസംഖ്യ i, index = *display_index;
    SDL_VideoDisplay display;
    SDL_DisplayData *displaydata;
    ശൂന്യം *dxgi_output = ശൂന്യ;
    SDL_DisplayMode mode;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    ദശാംശം content_scale = WIN_GetContentScale(_this, hMonitor);

#ifdef DEBUG_MODES
    SDL_Log("Display: %s", WIN_StringToUTF8W(info->szDevice));
#endif

    dxgi_output = WIN_GetDXGIOutput(_this, info->szDevice);
    bool found = WIN_GetDisplayMode(_this, dxgi_output, hMonitor, info->szDevice, ENUM_CURRENT_SETTINGS, &mode, &natural_orientation, &current_orientation);
    WIN_ReleaseDXGIOutput(dxgi_output);
    എങ്കിൽ (!found) {
        തിരികെ;
    }

    // Prevent adding duplicate displays. Do this after we know the display is
    // ready to be added to allow any displays that we can't fully query to be
    // removed
    വേണ്ടി (i = 0; i < _this->അക്കം_displays; ++i) {
        SDL_DisplayData *internal = _this->displays[i]->internal;
        എങ്കിൽ (SDL_wcscmp(internal->DeviceName, info->szDevice) == 0) {
            bool moved = (index != i);
            bool changed_bounds = false;

            എങ്കിൽ (internal->state != DisplayRemoved) {
                // We've already enumerated this display, don't move it
                പോകുക cleanup;
            }

            എങ്കിൽ (index >= _this->അക്കം_displays) {
                // This should never happen due to the check above, but just in case...
                പോകുക cleanup;
            }

            എങ്കിൽ (moved) {
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

            എങ്കിൽ (!_this->setting_display_mode) {
                SDL_VideoDisplay *existing_display = _this->displays[i];
                SDL_Rect bounds;

                SDL_ResetFullscreenDisplayModes(existing_display);
                SDL_SetDesktopDisplayMode(existing_display, &mode);
                // The mode is owned by the video subsystem
                mode.internal = ശൂന്യ;
                എങ്കിൽ (WIN_GetDisplayBounds(_this, existing_display, &bounds) &&
                    SDL_memcmp(&internal->bounds, &bounds, വലുപ്പം(bounds)) != 0) {
                    changed_bounds = true;
                    SDL_copyp(&internal->bounds, &bounds);
                }
                എങ്കിൽ (moved || changed_bounds) {
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
            പോകുക done;
        }
    }

    displaydata = (SDL_DisplayData *)SDL_calloc(1, വലുപ്പം(*displaydata));
    എങ്കിൽ (!displaydata) {
        പോകുക cleanup;
    }
    SDL_memcpy(displaydata->DeviceName, info->szDevice, വലുപ്പം(displaydata->DeviceName));
    displaydata->MonitorHandle = hMonitor;
    displaydata->state = DisplayAdded;

    SDL_zero(display);
    display.name = WIN_GetDisplayNameVista(_this->internal, info->szDevice);
    എങ്കിൽ (!display.name) {
        DISPLAY_DEVICEW device;
        SDL_zero(device);
        device.cb = വലുപ്പം(device);
        എങ്കിൽ (EnumDisplayDevicesW(info->szDevice, 0, &device, 0)) {
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
    എങ്കിൽ (displayID) {
        // The mode is owned by the video subsystem
        mode.internal = ശൂന്യ;

        SDL_PropertiesID props = SDL_GetDisplayProperties(displayID);
        SDL_SetPointerProperty(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_POINTER, hMonitor);
    } അല്ലെങ്കിൽ {
        SDL_free(displaydata);
    }
    SDL_free(display.name);

done:
    *display_index += 1;

cleanup:
    SDL_free(mode.internal);
}

തരനിർവചനം ഘടന _WIN_AddDisplaysData
{
    SDL_VideoDevice *video_device;
    പൂർണ്ണസംഖ്യ display_index;
    bool want_primary;
} WIN_AddDisplaysData;

സ്ഥിതം BOOL CALLBACK WIN_AddDisplaysCallback(HMONITOR hMonitor,
                                             HDC hdcMonitor,
                                             LPRECT lprcMonitor,
                                             LPARAM dwData)
{
    WIN_AddDisplaysData *data = (WIN_AddDisplaysData *)dwData;
    MONITORINFOEXW info;

    SDL_zero(info);
    info.cbSize = വലുപ്പം(info);

    എങ്കിൽ (GetMonitorInfoW(hMonitor, (LPMONITORINFO)&info) != 0) {
        സ്ഥിരം bool is_primary = ((info.dwFlags & MONITORINFOF_PRIMARY) == MONITORINFOF_PRIMARY);

        എങ്കിൽ (is_primary == data->want_primary) {
            WIN_AddDisplay(data->video_device, hMonitor, &info, &data->display_index);
        }
    }

    // continue enumeration
    തിരികെ TRUE;
}

സ്ഥിതം ശൂന്യം WIN_AddDisplays(SDL_VideoDevice *_this)
{
    WIN_AddDisplaysData callback_data;
    callback_data.video_device = _this;
    callback_data.display_index = 0;

    callback_data.want_primary = true;
    EnumDisplayMonitors(ശൂന്യ, ശൂന്യ, WIN_AddDisplaysCallback, (LPARAM)&callback_data);

    callback_data.want_primary = false;
    EnumDisplayMonitors(ശൂന്യ, ശൂന്യ, WIN_AddDisplaysCallback, (LPARAM)&callback_data);
}

bool WIN_InitModes(SDL_VideoDevice *_this)
{
    WIN_AddDisplays(_this);

    എങ്കിൽ (_this->അക്കം_displays == 0) {
        തിരികെ SDL_SetError("No displays available");
    }
    തിരികെ true;
}

bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    സ്ഥിരം SDL_DisplayData *data = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cbSize = വലുപ്പം(MONITORINFO);
    rc = GetMonitorInfo(data->MonitorHandle, &minfo);

    എങ്കിൽ (!rc) {
        തിരികെ SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcMonitor.ഇടത്;
    rect->y = minfo.rcMonitor.മുകൾ;
    rect->w = minfo.rcMonitor.വലത് - minfo.rcMonitor.ഇടത്;
    rect->h = minfo.rcMonitor.bottom - minfo.rcMonitor.മുകൾ;

    തിരികെ true;
}

bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    സ്ഥിരം SDL_DisplayData *data = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cbSize = വലുപ്പം(MONITORINFO);
    rc = GetMonitorInfo(data->MonitorHandle, &minfo);

    എങ്കിൽ (!rc) {
        തിരികെ SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcWork.ഇടത്;
    rect->y = minfo.rcWork.മുകൾ;
    rect->w = minfo.rcWork.വലത് - minfo.rcWork.ഇടത്;
    rect->h = minfo.rcWork.bottom - minfo.rcWork.മുകൾ;

    തിരികെ true;
}

bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_DisplayData *data = display->internal;
    ശൂന്യം *dxgi_output;
    DWORD i;
    SDL_DisplayMode mode;

    dxgi_output = WIN_GetDXGIOutput(_this, data->DeviceName);

    // Make sure we add the current mode to the list in case it's a custom mode that doesn't enumerate
    വേണ്ടി (i = ENUM_CURRENT_SETTINGS; ; ++i) {
        എങ്കിൽ (!WIN_GetDisplayMode(_this, dxgi_output, data->MonitorHandle, data->DeviceName, i, &mode, ശൂന്യ, ശൂന്യ)) {
            നിർത്തുക;
        }
        എങ്കിൽ (SDL_ISPIXELFORMAT_INDEXED(mode.format)) {
            // We don't support palettized modes now
            SDL_free(mode.internal);
            തുടരുക;
        }
        എങ്കിൽ (mode.format != SDL_PIXELFORMAT_UNKNOWN) {
            എങ്കിൽ (!SDL_AddFullscreenDisplayMode(display, &mode)) {
                SDL_free(mode.internal);
            }
        } അല്ലെങ്കിൽ {
            SDL_free(mode.internal);
        }
    }

    WIN_ReleaseDXGIOutput(dxgi_output);

    തിരികെ true;
}

#ifdef DEBUG_MODES
സ്ഥിതം ശൂന്യം WIN_LogMonitor(SDL_VideoDevice *_this, HMONITOR mon)
{
    സ്ഥിരം SDL_VideoData *vid_data = (സ്ഥിരം SDL_VideoData *)_this->internal;
    MONITORINFOEX minfo;
    UINT xdpi = 0, ydpi = 0;
    അക്ഷരം *name_utf8;

    എങ്കിൽ (vid_data->GetDpiForMonitor) {
        vid_data->GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &xdpi, &ydpi);
    }

    SDL_zero(minfo);
    minfo.cbSize = വലുപ്പം(minfo);
    GetMonitorInfo(mon, (LPMONITORINFO)&minfo);

    name_utf8 = WIN_StringToUTF8(minfo.szDevice);

    SDL_Log("WIN_LogMonitor: monitor \"%s\": dpi: %d windows screen coordinates: %d, %d, %dx%d",
            name_utf8,
            xdpi,
            minfo.rcMonitor.ഇടത്,
            minfo.rcMonitor.മുകൾ,
            minfo.rcMonitor.വലത് - minfo.rcMonitor.ഇടത്,
            minfo.rcMonitor.bottom - minfo.rcMonitor.മുകൾ);

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
    എങ്കിൽ (mode->internal == display->desktop_mode.internal) {
#ifdef DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: resetting to original resolution");
#endif
        status = ChangeDisplaySettingsExW(displaydata->DeviceName, ശൂന്യ, ശൂന്യ, CDS_FULLSCREEN, ശൂന്യ);
    } അല്ലെങ്കിൽ {
#ifdef DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: changing to %dx%d pixels", data->DeviceMode.dmPelsWidth, data->DeviceMode.dmPelsHeight);
#endif
        status = ChangeDisplaySettingsExW(displaydata->DeviceName, &data->DeviceMode, ശൂന്യ, CDS_FULLSCREEN, ശൂന്യ);
    }
    എങ്കിൽ (status != DISP_CHANGE_SUCCESSFUL) {
        സ്ഥിരം അക്ഷരം *reason = "Unknown reason";
        തിരഞ്ഞെടുപ്പ് (status) {
        അവസ്ഥ DISP_CHANGE_BADFLAGS:
            reason = "DISP_CHANGE_BADFLAGS";
            നിർത്തുക;
        അവസ്ഥ DISP_CHANGE_BADMODE:
            reason = "DISP_CHANGE_BADMODE";
            നിർത്തുക;
        അവസ്ഥ DISP_CHANGE_BADPARAM:
            reason = "DISP_CHANGE_BADPARAM";
            നിർത്തുക;
        അവസ്ഥ DISP_CHANGE_FAILED:
            reason = "DISP_CHANGE_FAILED";
            നിർത്തുക;
        }
        തിരികെ SDL_SetError("ChangeDisplaySettingsEx() failed: %s", reason);
    }

#ifdef DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state after mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#endif

    EnumDisplaySettingsW(displaydata->DeviceName, ENUM_CURRENT_SETTINGS, &data->DeviceMode);
    WIN_UpdateDisplayMode(_this, displaydata->DeviceName, ENUM_CURRENT_SETTINGS, mode);
    തിരികെ true;
}

ശൂന്യം WIN_RefreshDisplays(SDL_VideoDevice *_this)
{
    പൂർണ്ണസംഖ്യ i;

    // Mark all displays as potentially invalid to detect
    // entries that have actually been removed
    വേണ്ടി (i = 0; i < _this->അക്കം_displays; ++i) {
        SDL_DisplayData *internal = _this->displays[i]->internal;
        internal->state = DisplayRemoved;
    }

    // Enumerate displays to add any new ones and mark still
    // connected entries as valid
    WIN_AddDisplays(_this);

    // Delete any entries still marked as invalid, iterate
    // in reverse as each delete takes effect immediately
    വേണ്ടി (i = _this->അക്കം_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DisplayData *internal = display->internal;
        എങ്കിൽ (internal->state == DisplayRemoved) {
            SDL_DelVideoDisplay(display->id, true);
        }
    }

    // Send events for any newly added displays
    വേണ്ടി (i = 0; i < _this->അക്കം_displays; ++i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DisplayData *internal = display->internal;
        എങ്കിൽ (internal->state == DisplayAdded) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
        }
    }
}

ശൂന്യം WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this)
{
    // This almost never happens, so just go ahead and send update events for all displays
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < _this->അക്കം_displays; ++i) {
        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_CHANGED, 0, 0);
    }
}

ശൂന്യം WIN_QuitModes(SDL_VideoDevice *_this)
{
    // All fullscreen windows should have restored modes by now
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
