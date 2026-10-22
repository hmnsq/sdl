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
#समावेश "SDL_internal.h"

#अगर defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#समावेश "SDL_windowsvideo.h"
#समावेश "../../events/SDL_displayevents_c.h"
#समावेश "../SDL_pixels_c.h"

#अगर_घोषित HAVE_DXGI1_6_H
#घोषणा COBJMACROS
#समावेश <dxgi1_6.h>
#पूर्ण_अगर

// Windows CE compatibility
#अगर_अघोषित CDS_FULLSCREEN
#घोषणा CDS_FULLSCREEN 0
#पूर्ण_अगर
#अगर_अघोषित USER_DEFAULT_SCREEN_DPI
#घोषणा USER_DEFAULT_SCREEN_DPI 96
#पूर्ण_अगर

// #define DEBUG_MODES
// #define HIGHDPI_DEBUG_VERBOSE

अटल व्योम WIN_UpdateDisplayMode(SDL_VideoDevice *_this, LPCWSTR deviceName, DWORD सूचकांक, SDL_DisplayMode *mode)
{
    SDL_Display_Mode_तथ्य *तथ्य = (SDL_Display_Mode_तथ्य *)mode->internal;
    HDC hdc;

    तथ्य->DeviceMode.dmFields = (DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS);

    // NOLINTNEXTLINE(bugprone-assignment-in-if-condition): No simple way to extract the assignment
    अगर (सूचकांक == ENUM_CURRENT_SETTINGS && (hdc = CreateDCW(deviceName, शून्य, शून्य, शून्य)) != शून्य) {
        अक्षर bmi_तथ्य[माप(BITMAPINFOHEADER) + 256 * माप(RGBQUAD)];
        LPBITMAPINFO bmi;
        HBITMAP hbm;

        SDL_zeroa(bmi_तथ्य);
        bmi = (LPBITMAPINFO)bmi_तथ्य;
        bmi->bmiHeader.bi_आकार = माप(BITMAPINFOHEADER);

        hbm = CreateCompatibleBitmap(hdc, 1, 1);
        GetDIBits(hdc, hbm, 0, 1, शून्य, bmi, DIB_RGB_COLORS);
        GetDIBits(hdc, hbm, 0, 1, शून्य, bmi, DIB_RGB_COLORS);
        DeleteObject(hbm);
        DeleteDC(hdc);
        अगर (bmi->bmiHeader.biCompression == BI_BITFIELDS) {
            चयन (*(Uint32 *)bmi->bmiColors) {
            हाल 0x00FF0000:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                अवरोध;
            हाल 0x000000FF:
                mode->format = SDL_PIXELFORMAT_XBGR8888;
                अवरोध;
            हाल 0xF800:
                mode->format = SDL_PIXELFORMAT_RGB565;
                अवरोध;
            हाल 0x7C00:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                अवरोध;
            }
        } अन्यथा अगर (bmi->bmiHeader.biCompression == BI_RGB) {
            अगर (bmi->bmiHeader.bi_Bit_गिनती == 24) {
                mode->format = SDL_PIXELFORMAT_RGB24;
            } अन्यथा अगर (bmi->bmiHeader.bi_Bit_गिनती == 8) {
                mode->format = SDL_PIXELFORMAT_INDEX8;
            } अन्यथा अगर (bmi->bmiHeader.bi_Bit_गिनती == 4) {
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
            }
        }
    } अन्यथा अगर (mode->format == SDL_PIXELFORMAT_UNKNOWN) {
        // FIXME: Can we tell what this will be?
        अगर ((तथ्य->DeviceMode.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL) {
            चयन (तथ्य->DeviceMode.dmBitsPerPel) {
            हाल 32:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                अवरोध;
            हाल 24:
                mode->format = SDL_PIXELFORMAT_RGB24;
                अवरोध;
            हाल 16:
                mode->format = SDL_PIXELFORMAT_RGB565;
                अवरोध;
            हाल 15:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                अवरोध;
            हाल 8:
                mode->format = SDL_PIXELFORMAT_INDEX8;
                अवरोध;
            हाल 4:
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
                अवरोध;
            }
        }
    }
}

अटल व्योम *WIN_GetDXGIOutput(SDL_VideoDevice *_this, स्थिर WCHAR *DeviceName)
{
    व्योम *परिणाम = शून्य;

#अगर_घोषित HAVE_DXGI_H
    स्थिर SDL_Video_तथ्य *videodata = (स्थिर SDL_Video_तथ्य *)_this->internal;
    पूर्णांक nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    अगर (!videodata->pDXGIFactory) {
        वापस शून्य;
    }

    nAdapter = 0;
    जबतक (!परिणाम && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        जबतक (!परिणाम && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            अगर (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                अगर (SDL_wcscmp(outputDesc.DeviceName, DeviceName) == 0) {
                    परिणाम = pDXGIOutput;
                }
            }
            अगर (pDXGIOutput != परिणाम) {
                IDXGIOutput_Release(pDXGIOutput);
            }
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }
#पूर्ण_अगर
    वापस परिणाम;
}

अटल व्योम WIN_ReleaseDXGIOutput(व्योम *dxgi_output)
{
#अगर_घोषित HAVE_DXGI_H
    IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;

    अगर (pDXGIOutput) {
        IDXGIOutput_Release(pDXGIOutput);
    }
#पूर्ण_अगर
}

अटल SDL_DisplayOrientation WIN_GetNaturalOrientation(DEVMODEW *mode)
{
    पूर्णांक width = mode->dmPelsWidth;
    पूर्णांक height = mode->dmPelsHeight;

    // Use unrotated width/height to guess orientation
    अगर (mode->dmDisplayOrientation == DMDO_90 || mode->dmDisplayOrientation == DMDO_270) {
        पूर्णांक अस्थायी = width;
        width = height;
        height = अस्थायी;
    }

    अगर (width >= height) {
        वापस SDL_ORIENTATION_LANDSCAPE;
    } अन्यथा {
        वापस SDL_ORIENTATION_PORTRAIT;
    }
}

अटल SDL_DisplayOrientation WIN_GetDisplayOrientation(DEVMODEW *mode)
{
    अगर (WIN_GetNaturalOrientation(mode) == SDL_ORIENTATION_LANDSCAPE) {
        चयन (mode->dmDisplayOrientation) {
        हाल DMDO_DEFAULT:
            वापस SDL_ORIENTATION_LANDSCAPE;
        हाल DMDO_90:
            वापस SDL_ORIENTATION_PORTRAIT;
        हाल DMDO_180:
            वापस SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        हाल DMDO_270:
            वापस SDL_ORIENTATION_PORTRAIT_FLIPPED;
        शेष:
            वापस SDL_ORIENTATION_UNKNOWN;
        }
    } अन्यथा {
        चयन (mode->dmDisplayOrientation) {
        हाल DMDO_DEFAULT:
            वापस SDL_ORIENTATION_PORTRAIT;
        हाल DMDO_90:
            वापस SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        हाल DMDO_180:
            वापस SDL_ORIENTATION_PORTRAIT_FLIPPED;
        हाल DMDO_270:
            वापस SDL_ORIENTATION_LANDSCAPE;
        शेष:
            वापस SDL_ORIENTATION_UNKNOWN;
        }
    }
}

अटल व्योम WIN_GetRefreshRate(व्योम *dxgi_output, DEVMODEW *mode, पूर्णांक *numerator, पूर्णांक *denominator)
{
    // We're not currently using DXGI to query display modes, so fake NTSC timings
    चयन (mode->dmDisplayFrequency) {
    हाल 119:
    हाल 59:
    हाल 29:
        *numerator = (mode->dmDisplayFrequency + 1) * 1000;
        *denominator = 1001;
        अवरोध;
    शेष:
        *numerator = mode->dmDisplayFrequency;
        *denominator = 1;
        अवरोध;
    }

#अगर_घोषित HAVE_DXGI_H
    अगर (dxgi_output) {
        IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;
        DXGI_MODE_DESC modeToMatch;
        DXGI_MODE_DESC closestMatch;

        SDL_zero(modeToMatch);
        modeToMatch.Width = mode->dmPelsWidth;
        modeToMatch.Height = mode->dmPelsHeight;
        modeToMatch.RefreshRate.Numerator = *numerator;
        modeToMatch.RefreshRate.Denominator = *denominator;
        modeToMatch.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        अगर (SUCCEEDED(IDXGIOutput_FindClosestMatchingMode(pDXGIOutput, &modeToMatch, &closestMatch, शून्य))) {
            *numerator = closestMatch.RefreshRate.Numerator;
            *denominator = closestMatch.RefreshRate.Denominator;
        }
    }
#पूर्ण_अगर // HAVE_DXGI_H
}

अटल भग्न WIN_GetContentScale(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    पूर्णांक dpi = 0;

    स्थिर SDL_Video_तथ्य *videodata = (स्थिर SDL_Video_तथ्य *)_this->internal;
    अगर (videodata->GetDpiForMonitor) {
        UINT hdpi_uint, vdpi_uint;
        अगर (videodata->GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
            dpi = (पूर्णांक)hdpi_uint;
        }
    }
    अगर (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(शून्य);
        अगर (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(शून्य, hdc);
        }
    }
    अगर (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    वापस dpi / (भग्न)USER_DEFAULT_SCREEN_DPI;
}

अटल bool WIN_GetDisplayMode(SDL_VideoDevice *_this, व्योम *dxgi_output, HMONITOR hMonitor, LPCWSTR deviceName, DWORD सूचकांक, SDL_DisplayMode *mode, SDL_DisplayOrientation *natural_orientation, SDL_DisplayOrientation *current_orientation)
{
    SDL_Display_Mode_तथ्य *तथ्य;
    DEVMODEW devmode;

    devmode.dm_आकार = माप(devmode);
    devmode.dmDriverExtra = 0;
    अगर (!EnumDisplaySettingsW(deviceName, सूचकांक, &devmode)) {
        वापस false;
    }

    तथ्य = (SDL_Display_Mode_तथ्य *)SDL_malloc(माप(*तथ्य));
    अगर (!तथ्य) {
        वापस false;
    }

    SDL_zerop(mode);
    mode->internal = तथ्य;
    तथ्य->DeviceMode = devmode;

    mode->format = SDL_PIXELFORMAT_UNKNOWN;
    mode->w = तथ्य->DeviceMode.dmPelsWidth;
    mode->h = तथ्य->DeviceMode.dmPelsHeight;
    WIN_GetRefreshRate(dxgi_output, &तथ्य->DeviceMode, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);

    // Fill in the mode information
    WIN_UpdateDisplayMode(_this, deviceName, सूचकांक, mode);

    अगर (natural_orientation) {
        *natural_orientation = WIN_GetNaturalOrientation(&devmode);
    }
    अगर (current_orientation) {
        *current_orientation = WIN_GetDisplayOrientation(&devmode);
    }

    वापस true;
}

अटल अक्षर *WIN_GetDisplayNameVista(SDL_Video_तथ्य *videodata, स्थिर WCHAR *deviceName)
{
    DISPLAYCONFIG_PATH_INFO *paths = शून्य;
    DISPLAYCONFIG_MODE_INFO *modes = शून्य;
    अक्षर *परिणाम = शून्य;
    UINT32 path_गिनती_2 = 0;
    UINT32 mode_गिनती_2 = 0;
    UINT32 i;
    LONG rc;

    अगर (!videodata->Get_Display_Config_बफर_Sizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        वापस शून्य;
    }

    करो {
        rc = videodata->Get_Display_Config_बफर_Sizes(QDC_ONLY_ACTIVE_PATHS, &path_गिनती_2, &mode_गिनती_2);
        अगर (rc != ERROR_SUCCESS) {
            जाओ WIN_GetDisplayNameVista_failed;
        }

        SDL_free(paths);
        SDL_free(modes);

        paths = (DISPLAYCONFIG_PATH_INFO *)SDL_malloc(माप(DISPLAYCONFIG_PATH_INFO) * path_गिनती_2);
        modes = (DISPLAYCONFIG_MODE_INFO *)SDL_malloc(माप(DISPLAYCONFIG_MODE_INFO) * mode_गिनती_2);
        अगर ((!paths) || (!modes)) {
            जाओ WIN_GetDisplayNameVista_failed;
        }

        rc = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &path_गिनती_2, paths, &mode_गिनती_2, modes, 0);
    } जबतक (rc == ERROR_INSUFFICIENT_बफर);

    अगर (rc == ERROR_SUCCESS) {
        क्रम (i = 0; i < path_गिनती_2; i++) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME sourceName;
            DISPLAYCONFIG_TARGET_DEVICE_NAME targetName;

            SDL_zero(sourceName);
            sourceName.header.adapterId = paths[i].targetInfo.adapterId;
            sourceName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            sourceName.header.आकार = माप(sourceName);
            sourceName.header.id = paths[i].sourceInfo.id;
            rc = videodata->DisplayConfigGetDeviceInfo(&sourceName.header);
            अगर (rc != ERROR_SUCCESS) {
                अवरोध;
            } अन्यथा अगर (SDL_wcscmp(deviceName, sourceName.viewGdiDeviceName) != 0) {
                जारी;
            }

            SDL_zero(targetName);
            targetName.header.adapterId = paths[i].targetInfo.adapterId;
            targetName.header.id = paths[i].targetInfo.id;
            targetName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
            targetName.header.आकार = माप(targetName);
            rc = videodata->DisplayConfigGetDeviceInfo(&targetName.header);
            अगर (rc == ERROR_SUCCESS) {
                परिणाम = WIN_StringToUTF8W(targetName.monitorFriendlyDeviceName);
                /* if we got an empty string, treat it as failure so we'll fallback
                   to getting the generic name. */
                अगर (परिणाम && (*परिणाम == '\0')) {
                    SDL_free(परिणाम);
                    परिणाम = शून्य;
                }
            }
            अवरोध;
        }
    }

    SDL_free(paths);
    SDL_free(modes);
    वापस परिणाम;

WIN_GetDisplayNameVista_failed:
    SDL_free(परिणाम);
    SDL_free(paths);
    SDL_free(modes);
    वापस शून्य;
}

#अगर_घोषित HAVE_DXGI1_6_H
अटल bool WIN_GetMonitorDESC1(HMONITOR hMonitor, DXGI_OUTPUT_DESC1 *desc)
{
    प्रकार HRESULT (WINAPI *pfnCreateDXGIFactory1)(REFIID riid, व्योम **ppFactory);
    pfnCreateDXGIFactory1 pCreateDXGIFactory1 = शून्य;
    SDL_SharedObject *hDXGIMod = शून्य;
    bool found = false;

    hDXGIMod = SDL_LoadObject("dxgi.dll");
    अगर (hDXGIMod) {
        pCreateDXGIFactory1 = (pfnCreateDXGIFactory1)SDL_LoadFunction(hDXGIMod, "CreateDXGIFactory1");
    }
    अगर (pCreateDXGIFactory1) {
        अटल स्थिर GUID SDL_IID_IDXGIFactory1 = { 0x770aae78, 0xf26f, 0x4dba, { 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 } };
        अटल स्थिर GUID SDL_IID_IDXGIOutput6 = { 0x068346e8, 0xaaec, 0x4b84, { 0xad, 0xd7, 0x13, 0x7f, 0x51, 0x3f, 0x77, 0xa1 } };
        IDXGIFactory1 *dxgiFactory;

        अगर (SUCCEEDED(pCreateDXGIFactory1(&SDL_IID_IDXGIFactory1, (व्योम **)&dxgiFactory))) {
            IDXGIAdapter1 *dxgiAdapter;
            UINT adapter = 0;
            जबतक (!found && SUCCEEDED(IDXGIFactory1_EnumAdapters1(dxgiFactory, adapter, &dxgiAdapter))) {
                IDXGIOutput *dxgiOutput;
                UINT output = 0;
                जबतक (!found && SUCCEEDED(IDXGIAdapter1_EnumOutputs(dxgiAdapter, output, &dxgiOutput))) {
                    IDXGIOutput6 *dxgiOutput6;
                    अगर (SUCCEEDED(IDXGIOutput_QueryInterface(dxgiOutput, &SDL_IID_IDXGIOutput6, (व्योम **)&dxgiOutput6))) {
                        अगर (SUCCEEDED(IDXGIOutput6_GetDesc1(dxgiOutput6, desc))) {
                            अगर (desc->Monitor == hMonitor) {
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
    अगर (hDXGIMod) {
        SDL_UnloadObject(hDXGIMod);
    }
    वापस found;
}

अटल bool WIN_GetMonitorPathInfo(SDL_Video_तथ्य *videodata, HMONITOR hMonitor, DISPLAYCONFIG_PATH_INFO *path_info)
{
    LONG परिणाम;
    MONITORINFOEXW view_info;
    UINT32 i;
    UINT32 अंक_path_array_elements = 0;
    UINT32 अंक_mode_info_array_elements = 0;
    DISPLAYCONFIG_PATH_INFO *path_infos = शून्य, *new_path_infos;
    DISPLAYCONFIG_MODE_INFO *mode_infos = शून्य, *new_mode_infos;
    bool found = false;

    अगर (!videodata->Get_Display_Config_बफर_Sizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        वापस false;
    }

    SDL_zero(view_info);
    view_info.cb_आकार = माप(view_info);
    अगर (!GetMonitorInfoW(hMonitor, (MONITORINFO *)&view_info)) {
        जाओ done;
    }

    करो {
        अगर (videodata->Get_Display_Config_बफर_Sizes(QDC_ONLY_ACTIVE_PATHS, &अंक_path_array_elements, &अंक_mode_info_array_elements) != ERROR_SUCCESS) {
            SDL_free(path_infos);
            SDL_free(mode_infos);
            वापस false;
        }

        new_path_infos = (DISPLAYCONFIG_PATH_INFO *)SDL_realloc(path_infos, अंक_path_array_elements * माप(*path_infos));
        अगर (!new_path_infos) {
            जाओ done;
        }
        path_infos = new_path_infos;

        new_mode_infos = (DISPLAYCONFIG_MODE_INFO *)SDL_realloc(mode_infos, अंक_mode_info_array_elements * माप(*mode_infos));
        अगर (!new_mode_infos) {
            जाओ done;
        }
        mode_infos = new_mode_infos;

        परिणाम = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &अंक_path_array_elements, path_infos, &अंक_mode_info_array_elements, mode_infos, शून्य);

    } जबतक (परिणाम == ERROR_INSUFFICIENT_बफर);

    अगर (परिणाम == ERROR_SUCCESS) {
        क्रम (i = 0; i < अंक_path_array_elements; ++i) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME device_name;

            SDL_zero(device_name);
            device_name.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            device_name.header.आकार = माप(device_name);
            device_name.header.adapterId = path_infos[i].sourceInfo.adapterId;
            device_name.header.id = path_infos[i].sourceInfo.id;
            अगर (videodata->DisplayConfigGetDeviceInfo(&device_name.header) == ERROR_SUCCESS) {
                अगर (SDL_wcscmp(view_info.szDevice, device_name.viewGdiDeviceName) == 0) {
                    SDL_copyp(path_info, &path_infos[i]);
                    found = true;
                    अवरोध;
                }
            }
        }
    }

done:
    SDL_free(path_infos);
    SDL_free(mode_infos);

    वापस found;
}

अटल भग्न WIN_GetSDRWhitePoint(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    DISPLAYCONFIG_PATH_INFO path_info;
    SDL_Video_तथ्य *videodata = _this->internal;
    भग्न SDR_white_level = 1.0f;

    अगर (WIN_GetMonitorPathInfo(videodata, hMonitor, &path_info)) {
        /* workarounds for https://github.com/libsdl-org/SDL/issues/11193 */
        काष्ठा SDL_DISPLAYCONFIG_SDR_WHITE_LEVEL {
          DISPLAYCONFIG_DEVICE_INFO_HEADER header;
          ULONG SDRWhiteLevel;
        } white_level;
        #घोषणा DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL 11

        SDL_zero(white_level);
        white_level.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
        white_level.header.आकार = माप(white_level);
        white_level.header.adapterId = path_info.targetInfo.adapterId;
        white_level.header.id = path_info.targetInfo.id;
        // WIN_GetMonitorPathInfo() succeeded: DisplayConfigGetDeviceInfo is not NULL
        अगर (videodata->DisplayConfigGetDeviceInfo(&white_level.header) == ERROR_SUCCESS &&
            white_level.SDRWhiteLevel > 0) {
            SDR_white_level = (white_level.SDRWhiteLevel / 1000.0f);
        }
    }
    वापस SDR_white_level;
}

अटल व्योम WIN_GetHDRProperties(SDL_VideoDevice *_this, HMONITOR hMonitor, SDL_HDROutputProperties *HDR)
{
    DXGI_OUTPUT_DESC1 desc;

    SDL_zerop(HDR);

    अगर (WIN_GetMonitorDESC1(hMonitor, &desc)) {
        अगर (desc.ColorSpace == DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020) {
            HDR->SDR_white_level = WIN_GetSDRWhitePoint(_this, hMonitor);
            HDR->HDR_headroom = (desc.MaxLuminance / SCRGB_NITS) / HDR->SDR_white_level;
        }
    }
}
#पूर्ण_अगर // HAVE_DXGI1_6_H

अटल व्योम WIN_AddDisplay(SDL_VideoDevice *_this, HMONITOR hMonitor, स्थिर MONITORINFOEXW *info, पूर्णांक *display_सूचकांक)
{
    पूर्णांक i, सूचकांक = *display_सूचकांक;
    SDL_VideoDisplay display;
    SDL_Display_तथ्य *displaydata;
    व्योम *dxgi_output = शून्य;
    SDL_DisplayMode mode;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    भग्न content_scale = WIN_GetContentScale(_this, hMonitor);

#अगर_घोषित DEBUG_MODES
    SDL_Log("Display: %s", WIN_StringToUTF8W(info->szDevice));
#पूर्ण_अगर

    dxgi_output = WIN_GetDXGIOutput(_this, info->szDevice);
    bool found = WIN_GetDisplayMode(_this, dxgi_output, hMonitor, info->szDevice, ENUM_CURRENT_SETTINGS, &mode, &natural_orientation, &current_orientation);
    WIN_ReleaseDXGIOutput(dxgi_output);
    अगर (!found) {
        वापस;
    }

    // Prevent adding duplicate displays. Do this after we know the display is
    // ready to be added to allow any displays that we can't fully query to be
    // removed
    क्रम (i = 0; i < _this->अंक_displays; ++i) {
        SDL_Display_तथ्य *internal = _this->displays[i]->internal;
        अगर (SDL_wcscmp(internal->DeviceName, info->szDevice) == 0) {
            bool moved = (सूचकांक != i);
            bool changed_bounds = false;

            अगर (internal->state != DisplayRemoved) {
                // We've already enumerated this display, don't move it
                जाओ cleanup;
            }

            अगर (सूचकांक >= _this->अंक_displays) {
                // This should never happen due to the check above, but just in case...
                जाओ cleanup;
            }

            अगर (moved) {
                SDL_VideoDisplay *tmp;

                tmp = _this->displays[सूचकांक];
                _this->displays[सूचकांक] = _this->displays[i];
                _this->displays[i] = tmp;
                i = सूचकांक;
            }

            internal->MonitorHandle = hMonitor;
            internal->state = DisplayUnchanged;

            SDL_PropertiesID props = SDL_GetDisplayProperties(_this->displays[i]->id);
            SDL_SetPointerProperty(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_POINTER, hMonitor);

            अगर (!_this->setting_display_mode) {
                SDL_VideoDisplay *existing_display = _this->displays[i];
                SDL_Rect bounds;

                SDL_ResetFullscreenDisplayModes(existing_display);
                SDL_SetDesktopDisplayMode(existing_display, &mode);
                // The mode is owned by the video subsystem
                mode.internal = शून्य;
                अगर (WIN_GetDisplayBounds(_this, existing_display, &bounds) &&
                    SDL_memcmp(&internal->bounds, &bounds, माप(bounds)) != 0) {
                    changed_bounds = true;
                    SDL_copyp(&internal->bounds, &bounds);
                }
                अगर (moved || changed_bounds) {
                    SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_MOVED, 0, 0);
                }
                SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_ORIENTATION, current_orientation, 0);
                SDL_SetDisplayContentScale(existing_display, content_scale);
#अगर_घोषित HAVE_DXGI1_6_H
                SDL_HDROutputProperties HDR;
                WIN_GetHDRProperties(_this, hMonitor, &HDR);
                SDL_SetDisplayHDRProperties(existing_display, &HDR);
#पूर्ण_अगर
            }
            जाओ done;
        }
    }

    displaydata = (SDL_Display_तथ्य *)SDL_calloc(1, माप(*displaydata));
    अगर (!displaydata) {
        जाओ cleanup;
    }
    SDL_memcpy(displaydata->DeviceName, info->szDevice, माप(displaydata->DeviceName));
    displaydata->MonitorHandle = hMonitor;
    displaydata->state = DisplayAdded;

    SDL_zero(display);
    display.name = WIN_GetDisplayNameVista(_this->internal, info->szDevice);
    अगर (!display.name) {
        DISPLAY_DEVICEW device;
        SDL_zero(device);
        device.cb = माप(device);
        अगर (EnumDisplayDevicesW(info->szDevice, 0, &device, 0)) {
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
#अगर_घोषित HAVE_DXGI1_6_H
    WIN_GetHDRProperties(_this, hMonitor, &display.HDR);
#पूर्ण_अगर
    SDL_DisplayID displayID = SDL_AddVideoDisplay(&display, false);
    अगर (displayID) {
        // The mode is owned by the video subsystem
        mode.internal = शून्य;

        SDL_PropertiesID props = SDL_GetDisplayProperties(displayID);
        SDL_SetPointerProperty(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_POINTER, hMonitor);
    } अन्यथा {
        SDL_free(displaydata);
    }
    SDL_free(display.name);

done:
    *display_सूचकांक += 1;

cleanup:
    SDL_free(mode.internal);
}

प्रकार काष्ठा WIN_Add_Displays_तथ्य
{
    SDL_VideoDevice *video_device;
    पूर्णांक display_सूचकांक;
    bool want_primary;
} WIN_Add_Displays_तथ्य_2;

अटल BOOL CALLBACK WIN_AddDisplaysCallback(HMONITOR hMonitor,
                                             HDC hdcMonitor,
                                             LPRECT lprcMonitor,
                                             LPARAM dw_तथ्य)
{
    WIN_Add_Displays_तथ्य_2 *तथ्य = (WIN_Add_Displays_तथ्य_2 *)dw_तथ्य;
    MONITORINFOEXW info;

    SDL_zero(info);
    info.cb_आकार = माप(info);

    अगर (GetMonitorInfoW(hMonitor, (LPMONITORINFO)&info) != 0) {
        स्थिर bool is_primary = ((info.dwFlags & MONITORINFOF_PRIMARY) == MONITORINFOF_PRIMARY);

        अगर (is_primary == तथ्य->want_primary) {
            WIN_AddDisplay(तथ्य->video_device, hMonitor, &info, &तथ्य->display_सूचकांक);
        }
    }

    // continue enumeration
    वापस TRUE;
}

अटल व्योम WIN_AddDisplays(SDL_VideoDevice *_this)
{
    WIN_Add_Displays_तथ्य_2 callback_तथ्य;
    callback_तथ्य.video_device = _this;
    callback_तथ्य.display_सूचकांक = 0;

    callback_तथ्य.want_primary = true;
    EnumDisplayMonitors(शून्य, शून्य, WIN_AddDisplaysCallback, (LPARAM)&callback_तथ्य);

    callback_तथ्य.want_primary = false;
    EnumDisplayMonitors(शून्य, शून्य, WIN_AddDisplaysCallback, (LPARAM)&callback_तथ्य);
}

bool WIN_InitModes(SDL_VideoDevice *_this)
{
    WIN_AddDisplays(_this);

    अगर (_this->अंक_displays == 0) {
        वापस SDL_SetError("No displays available");
    }
    वापस true;
}

bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    स्थिर SDL_Display_तथ्य *तथ्य = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cb_आकार = माप(MONITORINFO);
    rc = GetMonitorInfo(तथ्य->MonitorHandle, &minfo);

    अगर (!rc) {
        वापस SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcMonitor.बायाँ;
    rect->y = minfo.rcMonitor.शीर्ष;
    rect->w = minfo.rcMonitor.दायाँ - minfo.rcMonitor.बायाँ;
    rect->h = minfo.rcMonitor.bottom - minfo.rcMonitor.शीर्ष;

    वापस true;
}

bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    स्थिर SDL_Display_तथ्य *तथ्य = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cb_आकार = माप(MONITORINFO);
    rc = GetMonitorInfo(तथ्य->MonitorHandle, &minfo);

    अगर (!rc) {
        वापस SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcWork.बायाँ;
    rect->y = minfo.rcWork.शीर्ष;
    rect->w = minfo.rcWork.दायाँ - minfo.rcWork.बायाँ;
    rect->h = minfo.rcWork.bottom - minfo.rcWork.शीर्ष;

    वापस true;
}

bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_तथ्य *तथ्य = display->internal;
    व्योम *dxgi_output;
    DWORD i;
    SDL_DisplayMode mode;

    dxgi_output = WIN_GetDXGIOutput(_this, तथ्य->DeviceName);

    // Make sure we add the current mode to the list in case it's a custom mode that doesn't enumerate
    क्रम (i = ENUM_CURRENT_SETTINGS; ; ++i) {
        अगर (!WIN_GetDisplayMode(_this, dxgi_output, तथ्य->MonitorHandle, तथ्य->DeviceName, i, &mode, शून्य, शून्य)) {
            अवरोध;
        }
        अगर (SDL_ISPIXELFORMAT_INDEXED(mode.format)) {
            // We don't support palettized modes now
            SDL_free(mode.internal);
            जारी;
        }
        अगर (mode.format != SDL_PIXELFORMAT_UNKNOWN) {
            अगर (!SDL_AddFullscreenDisplayMode(display, &mode)) {
                SDL_free(mode.internal);
            }
        } अन्यथा {
            SDL_free(mode.internal);
        }
    }

    WIN_ReleaseDXGIOutput(dxgi_output);

    वापस true;
}

#अगर_घोषित DEBUG_MODES
अटल व्योम WIN_LogMonitor(SDL_VideoDevice *_this, HMONITOR mon)
{
    स्थिर SDL_Video_तथ्य *vid_तथ्य = (स्थिर SDL_Video_तथ्य *)_this->internal;
    MONITORINFOEX minfo;
    UINT xdpi = 0, ydpi = 0;
    अक्षर *name_utf8;

    अगर (vid_तथ्य->GetDpiForMonitor) {
        vid_तथ्य->GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &xdpi, &ydpi);
    }

    SDL_zero(minfo);
    minfo.cb_आकार = माप(minfo);
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
#पूर्ण_अगर

bool WIN_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    SDL_Display_तथ्य *displaydata = display->internal;
    SDL_Display_Mode_तथ्य *तथ्य = (SDL_Display_Mode_तथ्य *)mode->internal;
    LONG status;

#अगर_घोषित DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state before mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#पूर्ण_अगर

    /* High-DPI notes:

       - ChangeDisplaySettingsEx always takes pixels.
       - e.g. if the display is set to 2880x1800 with 200% scaling in Display Settings
         - calling ChangeDisplaySettingsEx with a dmPelsWidth/Height other than 2880x1800 will
           change the monitor DPI to 96. (100% scaling)
         - calling ChangeDisplaySettingsEx with a dmPelsWidth/Height of 2880x1800 (or a NULL DEVMODE*) will
           reset the monitor DPI to 192. (200% scaling)

       NOTE: these are temporary changes in DPI, not modifications to the Control Panel setting. */
    अगर (mode->internal == display->desktop_mode.internal) {
#अगर_घोषित DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: resetting to original resolution");
#पूर्ण_अगर
        status = ChangeDisplaySettingsExW(displaydata->DeviceName, शून्य, शून्य, CDS_FULLSCREEN, शून्य);
    } अन्यथा {
#अगर_घोषित DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: changing to %dx%d pixels", तथ्य->DeviceMode.dmPelsWidth, तथ्य->DeviceMode.dmPelsHeight);
#पूर्ण_अगर
        status = ChangeDisplaySettingsExW(displaydata->DeviceName, &तथ्य->DeviceMode, शून्य, CDS_FULLSCREEN, शून्य);
    }
    अगर (status != DISP_CHANGE_SUCCESSFUL) {
        स्थिर अक्षर *reason = "Unknown reason";
        चयन (status) {
        हाल DISP_CHANGE_BADFLAGS:
            reason = "DISP_CHANGE_BADFLAGS";
            अवरोध;
        हाल DISP_CHANGE_BADMODE:
            reason = "DISP_CHANGE_BADMODE";
            अवरोध;
        हाल DISP_CHANGE_BADPARAM:
            reason = "DISP_CHANGE_BADPARAM";
            अवरोध;
        हाल DISP_CHANGE_FAILED:
            reason = "DISP_CHANGE_FAILED";
            अवरोध;
        }
        वापस SDL_SetError("ChangeDisplaySettingsEx() failed: %s", reason);
    }

#अगर_घोषित DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state after mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#पूर्ण_अगर

    EnumDisplaySettingsW(displaydata->DeviceName, ENUM_CURRENT_SETTINGS, &तथ्य->DeviceMode);
    WIN_UpdateDisplayMode(_this, displaydata->DeviceName, ENUM_CURRENT_SETTINGS, mode);
    वापस true;
}

व्योम WIN_RefreshDisplays(SDL_VideoDevice *_this)
{
    पूर्णांक i;

    // Mark all displays as potentially invalid to detect
    // entries that have actually been removed
    क्रम (i = 0; i < _this->अंक_displays; ++i) {
        SDL_Display_तथ्य *internal = _this->displays[i]->internal;
        internal->state = DisplayRemoved;
    }

    // Enumerate displays to add any new ones and mark still
    // connected entries as valid
    WIN_AddDisplays(_this);

    // Delete any entries still marked as invalid, iterate
    // in reverse as each delete takes effect immediately
    क्रम (i = _this->अंक_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_Display_तथ्य *internal = display->internal;
        अगर (internal->state == DisplayRemoved) {
            SDL_DelVideoDisplay(display->id, true);
        }
    }

    // Send events for any newly added displays
    क्रम (i = 0; i < _this->अंक_displays; ++i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_Display_तथ्य *internal = display->internal;
        अगर (internal->state == DisplayAdded) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
        }
    }
}

व्योम WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this)
{
    // This almost never happens, so just go ahead and send update events for all displays
    क्रम (पूर्णांक i = 0; i < _this->अंक_displays; ++i) {
        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_CHANGED, 0, 0);
    }
}

व्योम WIN_QuitModes(SDL_VideoDevice *_this)
{
    // All fullscreen windows should have restored modes by now
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WINDOWS
