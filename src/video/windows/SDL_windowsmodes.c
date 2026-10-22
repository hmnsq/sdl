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
#অন্তর্ভাব "SDL_internal.h"

#যদি defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#অন্তর্ভাব "SDL_windowsvideo.h"
#অন্তর্ভাব "../../events/SDL_displayevents_c.h"
#অন্তর্ভাব "../SDL_pixels_c.h"

#ifdef HAVE_DXGI1_6_H
#define COBJMACROS
#অন্তর্ভাব <dxgi1_6.h>
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

স্থির শূন্য WIN_UpdateDisplayMode(SDL_VideoDevice *_this, LPCWSTR deviceName, DWORD সূচক, SDL_DisplayMode *mode)
{
    SDL_Display_Mode_তথ্য *তথ্য = (SDL_Display_Mode_তথ্য *)mode->internal;
    HDC hdc;

    তথ্য->DeviceMode.dmFields = (DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS);

    // NOLINTNEXTLINE(bugprone-assignment-in-if-condition): No simple way to extract the assignment
    যদি (সূচক == ENUM_CURRENT_SETTINGS && (hdc = CreateDCW(deviceName, ফাঁকা, ফাঁকা, ফাঁকা)) != ফাঁকা) {
        অক্ষর bmi_তথ্য[আকার(BITMAPINFOHEADER) + 256 * আকার(RGBQUAD)];
        LPBITMAPINFO bmi;
        HBITMAP hbm;

        SDL_zeroa(bmi_তথ্য);
        bmi = (LPBITMAPINFO)bmi_তথ্য;
        bmi->bmiHeader.bi_আকার = আকার(BITMAPINFOHEADER);

        hbm = CreateCompatibleBitmap(hdc, 1, 1);
        GetDIBits(hdc, hbm, 0, 1, ফাঁকা, bmi, DIB_RGB_COLORS);
        GetDIBits(hdc, hbm, 0, 1, ফাঁকা, bmi, DIB_RGB_COLORS);
        DeleteObject(hbm);
        DeleteDC(hdc);
        যদি (bmi->bmiHeader.biCompression == BI_BITFIELDS) {
            নির্বাচন (*(Uint32 *)bmi->bmiColors) {
            ক্ষেত্র 0x00FF0000:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                বিরতি;
            ক্ষেত্র 0x000000FF:
                mode->format = SDL_PIXELFORMAT_XBGR8888;
                বিরতি;
            ক্ষেত্র 0xF800:
                mode->format = SDL_PIXELFORMAT_RGB565;
                বিরতি;
            ক্ষেত্র 0x7C00:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                বিরতি;
            }
        } অন্যথা যদি (bmi->bmiHeader.biCompression == BI_RGB) {
            যদি (bmi->bmiHeader.bi_Bit_গুনতি == 24) {
                mode->format = SDL_PIXELFORMAT_RGB24;
            } অন্যথা যদি (bmi->bmiHeader.bi_Bit_গুনতি == 8) {
                mode->format = SDL_PIXELFORMAT_INDEX8;
            } অন্যথা যদি (bmi->bmiHeader.bi_Bit_গুনতি == 4) {
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
            }
        }
    } অন্যথা যদি (mode->format == SDL_PIXELFORMAT_UNKNOWN) {
        // FIXME: Can we tell what this will be?
        যদি ((তথ্য->DeviceMode.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL) {
            নির্বাচন (তথ্য->DeviceMode.dmBitsPerPel) {
            ক্ষেত্র 32:
                mode->format = SDL_PIXELFORMAT_XRGB8888;
                বিরতি;
            ক্ষেত্র 24:
                mode->format = SDL_PIXELFORMAT_RGB24;
                বিরতি;
            ক্ষেত্র 16:
                mode->format = SDL_PIXELFORMAT_RGB565;
                বিরতি;
            ক্ষেত্র 15:
                mode->format = SDL_PIXELFORMAT_XRGB1555;
                বিরতি;
            ক্ষেত্র 8:
                mode->format = SDL_PIXELFORMAT_INDEX8;
                বিরতি;
            ক্ষেত্র 4:
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
                বিরতি;
            }
        }
    }
}

স্থির শূন্য *WIN_GetDXGIOutput(SDL_VideoDevice *_this, ধ্রুবক WCHAR *DeviceName)
{
    শূন্য *ফলাফল = ফাঁকা;

#ifdef HAVE_DXGI_H
    ধ্রুবক SDL_Video_তথ্য *videodata = (ধ্রুবক SDL_Video_তথ্য *)_this->internal;
    পূর্ণসংখ্যা nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    যদি (!videodata->pDXGIFactory) {
        ফেরত ফাঁকা;
    }

    nAdapter = 0;
    যখন (!ফলাফল && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        যখন (!ফলাফল && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            যদি (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                যদি (SDL_wcscmp(outputDesc.DeviceName, DeviceName) == 0) {
                    ফলাফল = pDXGIOutput;
                }
            }
            যদি (pDXGIOutput != ফলাফল) {
                IDXGIOutput_Release(pDXGIOutput);
            }
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }
#endif
    ফেরত ফলাফল;
}

স্থির শূন্য WIN_ReleaseDXGIOutput(শূন্য *dxgi_output)
{
#ifdef HAVE_DXGI_H
    IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;

    যদি (pDXGIOutput) {
        IDXGIOutput_Release(pDXGIOutput);
    }
#endif
}

স্থির SDL_DisplayOrientation WIN_GetNaturalOrientation(DEVMODEW *mode)
{
    পূর্ণসংখ্যা width = mode->dmPelsWidth;
    পূর্ণসংখ্যা height = mode->dmPelsHeight;

    // Use unrotated width/height to guess orientation
    যদি (mode->dmDisplayOrientation == DMDO_90 || mode->dmDisplayOrientation == DMDO_270) {
        পূর্ণসংখ্যা অস্থায়ী = width;
        width = height;
        height = অস্থায়ী;
    }

    যদি (width >= height) {
        ফেরত SDL_ORIENTATION_LANDSCAPE;
    } অন্যথা {
        ফেরত SDL_ORIENTATION_PORTRAIT;
    }
}

স্থির SDL_DisplayOrientation WIN_GetDisplayOrientation(DEVMODEW *mode)
{
    যদি (WIN_GetNaturalOrientation(mode) == SDL_ORIENTATION_LANDSCAPE) {
        নির্বাচন (mode->dmDisplayOrientation) {
        ক্ষেত্র DMDO_DEFAULT:
            ফেরত SDL_ORIENTATION_LANDSCAPE;
        ক্ষেত্র DMDO_90:
            ফেরত SDL_ORIENTATION_PORTRAIT;
        ক্ষেত্র DMDO_180:
            ফেরত SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        ক্ষেত্র DMDO_270:
            ফেরত SDL_ORIENTATION_PORTRAIT_FLIPPED;
        পূর্বনির্ধারিত:
            ফেরত SDL_ORIENTATION_UNKNOWN;
        }
    } অন্যথা {
        নির্বাচন (mode->dmDisplayOrientation) {
        ক্ষেত্র DMDO_DEFAULT:
            ফেরত SDL_ORIENTATION_PORTRAIT;
        ক্ষেত্র DMDO_90:
            ফেরত SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        ক্ষেত্র DMDO_180:
            ফেরত SDL_ORIENTATION_PORTRAIT_FLIPPED;
        ক্ষেত্র DMDO_270:
            ফেরত SDL_ORIENTATION_LANDSCAPE;
        পূর্বনির্ধারিত:
            ফেরত SDL_ORIENTATION_UNKNOWN;
        }
    }
}

স্থির শূন্য WIN_GetRefreshRate(শূন্য *dxgi_output, DEVMODEW *mode, পূর্ণসংখ্যা *numerator, পূর্ণসংখ্যা *denominator)
{
    // We're not currently using DXGI to query display modes, so fake NTSC timings
    নির্বাচন (mode->dmDisplayFrequency) {
    ক্ষেত্র 119:
    ক্ষেত্র 59:
    ক্ষেত্র 29:
        *numerator = (mode->dmDisplayFrequency + 1) * 1000;
        *denominator = 1001;
        বিরতি;
    পূর্বনির্ধারিত:
        *numerator = mode->dmDisplayFrequency;
        *denominator = 1;
        বিরতি;
    }

#ifdef HAVE_DXGI_H
    যদি (dxgi_output) {
        IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;
        DXGI_MODE_DESC modeToMatch;
        DXGI_MODE_DESC closestMatch;

        SDL_zero(modeToMatch);
        modeToMatch.Width = mode->dmPelsWidth;
        modeToMatch.Height = mode->dmPelsHeight;
        modeToMatch.RefreshRate.Numerator = *numerator;
        modeToMatch.RefreshRate.Denominator = *denominator;
        modeToMatch.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        যদি (SUCCEEDED(IDXGIOutput_FindClosestMatchingMode(pDXGIOutput, &modeToMatch, &closestMatch, ফাঁকা))) {
            *numerator = closestMatch.RefreshRate.Numerator;
            *denominator = closestMatch.RefreshRate.Denominator;
        }
    }
#endif // HAVE_DXGI_H
}

স্থির দশমিক WIN_GetContentScale(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    পূর্ণসংখ্যা dpi = 0;

    ধ্রুবক SDL_Video_তথ্য *videodata = (ধ্রুবক SDL_Video_তথ্য *)_this->internal;
    যদি (videodata->GetDpiForMonitor) {
        UINT hdpi_uint, vdpi_uint;
        যদি (videodata->GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
            dpi = (পূর্ণসংখ্যা)hdpi_uint;
        }
    }
    যদি (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(ফাঁকা);
        যদি (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(ফাঁকা, hdc);
        }
    }
    যদি (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    ফেরত dpi / (দশমিক)USER_DEFAULT_SCREEN_DPI;
}

স্থির bool WIN_GetDisplayMode(SDL_VideoDevice *_this, শূন্য *dxgi_output, HMONITOR hMonitor, LPCWSTR deviceName, DWORD সূচক, SDL_DisplayMode *mode, SDL_DisplayOrientation *natural_orientation, SDL_DisplayOrientation *current_orientation)
{
    SDL_Display_Mode_তথ্য *তথ্য;
    DEVMODEW devmode;

    devmode.dm_আকার = আকার(devmode);
    devmode.dmDriverExtra = 0;
    যদি (!EnumDisplaySettingsW(deviceName, সূচক, &devmode)) {
        ফেরত false;
    }

    তথ্য = (SDL_Display_Mode_তথ্য *)SDL_malloc(আকার(*তথ্য));
    যদি (!তথ্য) {
        ফেরত false;
    }

    SDL_zerop(mode);
    mode->internal = তথ্য;
    তথ্য->DeviceMode = devmode;

    mode->format = SDL_PIXELFORMAT_UNKNOWN;
    mode->w = তথ্য->DeviceMode.dmPelsWidth;
    mode->h = তথ্য->DeviceMode.dmPelsHeight;
    WIN_GetRefreshRate(dxgi_output, &তথ্য->DeviceMode, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);

    // Fill in the mode information
    WIN_UpdateDisplayMode(_this, deviceName, সূচক, mode);

    যদি (natural_orientation) {
        *natural_orientation = WIN_GetNaturalOrientation(&devmode);
    }
    যদি (current_orientation) {
        *current_orientation = WIN_GetDisplayOrientation(&devmode);
    }

    ফেরত true;
}

স্থির অক্ষর *WIN_GetDisplayNameVista(SDL_Video_তথ্য *videodata, ধ্রুবক WCHAR *deviceName)
{
    DISPLAYCONFIG_PATH_INFO *paths = ফাঁকা;
    DISPLAYCONFIG_MODE_INFO *modes = ফাঁকা;
    অক্ষর *ফলাফল = ফাঁকা;
    UINT32 path_গুনতি_2 = 0;
    UINT32 mode_গুনতি_2 = 0;
    UINT32 i;
    LONG rc;

    যদি (!videodata->Get_Display_Config_বাফার_Sizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        ফেরত ফাঁকা;
    }

    করো {
        rc = videodata->Get_Display_Config_বাফার_Sizes(QDC_ONLY_ACTIVE_PATHS, &path_গুনতি_2, &mode_গুনতি_2);
        যদি (rc != ERROR_SUCCESS) {
            যাও WIN_GetDisplayNameVista_failed;
        }

        SDL_free(paths);
        SDL_free(modes);

        paths = (DISPLAYCONFIG_PATH_INFO *)SDL_malloc(আকার(DISPLAYCONFIG_PATH_INFO) * path_গুনতি_2);
        modes = (DISPLAYCONFIG_MODE_INFO *)SDL_malloc(আকার(DISPLAYCONFIG_MODE_INFO) * mode_গুনতি_2);
        যদি ((!paths) || (!modes)) {
            যাও WIN_GetDisplayNameVista_failed;
        }

        rc = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &path_গুনতি_2, paths, &mode_গুনতি_2, modes, 0);
    } যখন (rc == ERROR_INSUFFICIENT_বাফার);

    যদি (rc == ERROR_SUCCESS) {
        জন্য (i = 0; i < path_গুনতি_2; i++) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME sourceName;
            DISPLAYCONFIG_TARGET_DEVICE_NAME targetName;

            SDL_zero(sourceName);
            sourceName.header.adapterId = paths[i].targetInfo.adapterId;
            sourceName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            sourceName.header.আকার_2 = আকার(sourceName);
            sourceName.header.id = paths[i].sourceInfo.id;
            rc = videodata->DisplayConfigGetDeviceInfo(&sourceName.header);
            যদি (rc != ERROR_SUCCESS) {
                বিরতি;
            } অন্যথা যদি (SDL_wcscmp(deviceName, sourceName.viewGdiDeviceName) != 0) {
                চালু;
            }

            SDL_zero(targetName);
            targetName.header.adapterId = paths[i].targetInfo.adapterId;
            targetName.header.id = paths[i].targetInfo.id;
            targetName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
            targetName.header.আকার_2 = আকার(targetName);
            rc = videodata->DisplayConfigGetDeviceInfo(&targetName.header);
            যদি (rc == ERROR_SUCCESS) {
                ফলাফল = WIN_StringToUTF8W(targetName.monitorFriendlyDeviceName);
                /* if we got an empty string, treat it as failure so we'll fallback
                   to getting the generic name. */
                যদি (ফলাফল && (*ফলাফল == '\0')) {
                    SDL_free(ফলাফল);
                    ফলাফল = ফাঁকা;
                }
            }
            বিরতি;
        }
    }

    SDL_free(paths);
    SDL_free(modes);
    ফেরত ফলাফল;

WIN_GetDisplayNameVista_failed:
    SDL_free(ফলাফল);
    SDL_free(paths);
    SDL_free(modes);
    ফেরত ফাঁকা;
}

#ifdef HAVE_DXGI1_6_H
স্থির bool WIN_GetMonitorDESC1(HMONITOR hMonitor, DXGI_OUTPUT_DESC1 *desc)
{
    প্রকারলেখ HRESULT (WINAPI *pfnCreateDXGIFactory1)(REFIID riid, শূন্য **ppFactory);
    pfnCreateDXGIFactory1 pCreateDXGIFactory1 = ফাঁকা;
    SDL_SharedObject *hDXGIMod = ফাঁকা;
    bool found = false;

    hDXGIMod = SDL_LoadObject("dxgi.dll");
    যদি (hDXGIMod) {
        pCreateDXGIFactory1 = (pfnCreateDXGIFactory1)SDL_LoadFunction(hDXGIMod, "CreateDXGIFactory1");
    }
    যদি (pCreateDXGIFactory1) {
        স্থির ধ্রুবক GUID SDL_IID_IDXGIFactory1 = { 0x770aae78, 0xf26f, 0x4dba, { 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 } };
        স্থির ধ্রুবক GUID SDL_IID_IDXGIOutput6 = { 0x068346e8, 0xaaec, 0x4b84, { 0xad, 0xd7, 0x13, 0x7f, 0x51, 0x3f, 0x77, 0xa1 } };
        IDXGIFactory1 *dxgiFactory;

        যদি (SUCCEEDED(pCreateDXGIFactory1(&SDL_IID_IDXGIFactory1, (শূন্য **)&dxgiFactory))) {
            IDXGIAdapter1 *dxgiAdapter;
            UINT adapter = 0;
            যখন (!found && SUCCEEDED(IDXGIFactory1_EnumAdapters1(dxgiFactory, adapter, &dxgiAdapter))) {
                IDXGIOutput *dxgiOutput;
                UINT output = 0;
                যখন (!found && SUCCEEDED(IDXGIAdapter1_EnumOutputs(dxgiAdapter, output, &dxgiOutput))) {
                    IDXGIOutput6 *dxgiOutput6;
                    যদি (SUCCEEDED(IDXGIOutput_QueryInterface(dxgiOutput, &SDL_IID_IDXGIOutput6, (শূন্য **)&dxgiOutput6))) {
                        যদি (SUCCEEDED(IDXGIOutput6_GetDesc1(dxgiOutput6, desc))) {
                            যদি (desc->Monitor == hMonitor) {
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
    যদি (hDXGIMod) {
        SDL_UnloadObject(hDXGIMod);
    }
    ফেরত found;
}

স্থির bool WIN_GetMonitorPathInfo(SDL_Video_তথ্য *videodata, HMONITOR hMonitor, DISPLAYCONFIG_PATH_INFO *path_info)
{
    LONG ফলাফল;
    MONITORINFOEXW view_info;
    UINT32 i;
    UINT32 অঙ্ক_path_array_elements = 0;
    UINT32 অঙ্ক_mode_info_array_elements = 0;
    DISPLAYCONFIG_PATH_INFO *path_infos = ফাঁকা, *new_path_infos;
    DISPLAYCONFIG_MODE_INFO *mode_infos = ফাঁকা, *new_mode_infos;
    bool found = false;

    যদি (!videodata->Get_Display_Config_বাফার_Sizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        ফেরত false;
    }

    SDL_zero(view_info);
    view_info.cb_আকার = আকার(view_info);
    যদি (!GetMonitorInfoW(hMonitor, (MONITORINFO *)&view_info)) {
        যাও done;
    }

    করো {
        যদি (videodata->Get_Display_Config_বাফার_Sizes(QDC_ONLY_ACTIVE_PATHS, &অঙ্ক_path_array_elements, &অঙ্ক_mode_info_array_elements) != ERROR_SUCCESS) {
            SDL_free(path_infos);
            SDL_free(mode_infos);
            ফেরত false;
        }

        new_path_infos = (DISPLAYCONFIG_PATH_INFO *)SDL_realloc(path_infos, অঙ্ক_path_array_elements * আকার(*path_infos));
        যদি (!new_path_infos) {
            যাও done;
        }
        path_infos = new_path_infos;

        new_mode_infos = (DISPLAYCONFIG_MODE_INFO *)SDL_realloc(mode_infos, অঙ্ক_mode_info_array_elements * আকার(*mode_infos));
        যদি (!new_mode_infos) {
            যাও done;
        }
        mode_infos = new_mode_infos;

        ফলাফল = videodata->QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &অঙ্ক_path_array_elements, path_infos, &অঙ্ক_mode_info_array_elements, mode_infos, ফাঁকা);

    } যখন (ফলাফল == ERROR_INSUFFICIENT_বাফার);

    যদি (ফলাফল == ERROR_SUCCESS) {
        জন্য (i = 0; i < অঙ্ক_path_array_elements; ++i) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME device_name;

            SDL_zero(device_name);
            device_name.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            device_name.header.আকার_2 = আকার(device_name);
            device_name.header.adapterId = path_infos[i].sourceInfo.adapterId;
            device_name.header.id = path_infos[i].sourceInfo.id;
            যদি (videodata->DisplayConfigGetDeviceInfo(&device_name.header) == ERROR_SUCCESS) {
                যদি (SDL_wcscmp(view_info.szDevice, device_name.viewGdiDeviceName) == 0) {
                    SDL_copyp(path_info, &path_infos[i]);
                    found = true;
                    বিরতি;
                }
            }
        }
    }

done:
    SDL_free(path_infos);
    SDL_free(mode_infos);

    ফেরত found;
}

স্থির দশমিক WIN_GetSDRWhitePoint(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    DISPLAYCONFIG_PATH_INFO path_info;
    SDL_Video_তথ্য *videodata = _this->internal;
    দশমিক SDR_white_level = 1.0f;

    যদি (WIN_GetMonitorPathInfo(videodata, hMonitor, &path_info)) {
        /* workarounds for https://github.com/libsdl-org/SDL/issues/11193 */
        কাঠামো SDL_DISPLAYCONFIG_SDR_WHITE_LEVEL {
          DISPLAYCONFIG_DEVICE_INFO_HEADER header;
          ULONG SDRWhiteLevel;
        } white_level;
        #define DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL 11

        SDL_zero(white_level);
        white_level.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
        white_level.header.আকার_2 = আকার(white_level);
        white_level.header.adapterId = path_info.targetInfo.adapterId;
        white_level.header.id = path_info.targetInfo.id;
        // WIN_GetMonitorPathInfo() succeeded: DisplayConfigGetDeviceInfo is not NULL
        যদি (videodata->DisplayConfigGetDeviceInfo(&white_level.header) == ERROR_SUCCESS &&
            white_level.SDRWhiteLevel > 0) {
            SDR_white_level = (white_level.SDRWhiteLevel / 1000.0f);
        }
    }
    ফেরত SDR_white_level;
}

স্থির শূন্য WIN_GetHDRProperties(SDL_VideoDevice *_this, HMONITOR hMonitor, SDL_HDROutputProperties *HDR)
{
    DXGI_OUTPUT_DESC1 desc;

    SDL_zerop(HDR);

    যদি (WIN_GetMonitorDESC1(hMonitor, &desc)) {
        যদি (desc.ColorSpace == DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020) {
            HDR->SDR_white_level = WIN_GetSDRWhitePoint(_this, hMonitor);
            HDR->HDR_headroom = (desc.MaxLuminance / SCRGB_NITS) / HDR->SDR_white_level;
        }
    }
}
#endif // HAVE_DXGI1_6_H

স্থির শূন্য WIN_AddDisplay(SDL_VideoDevice *_this, HMONITOR hMonitor, ধ্রুবক MONITORINFOEXW *info, পূর্ণসংখ্যা *display_সূচক)
{
    পূর্ণসংখ্যা i, সূচক = *display_সূচক;
    SDL_VideoDisplay display;
    SDL_Display_তথ্য *displaydata;
    শূন্য *dxgi_output = ফাঁকা;
    SDL_DisplayMode mode;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    দশমিক content_scale = WIN_GetContentScale(_this, hMonitor);

#ifdef DEBUG_MODES
    SDL_Log("Display: %s", WIN_StringToUTF8W(info->szDevice));
#endif

    dxgi_output = WIN_GetDXGIOutput(_this, info->szDevice);
    bool found = WIN_GetDisplayMode(_this, dxgi_output, hMonitor, info->szDevice, ENUM_CURRENT_SETTINGS, &mode, &natural_orientation, &current_orientation);
    WIN_ReleaseDXGIOutput(dxgi_output);
    যদি (!found) {
        ফেরত;
    }

    // Prevent adding duplicate displays. Do this after we know the display is
    // ready to be added to allow any displays that we can't fully query to be
    // removed
    জন্য (i = 0; i < _this->অঙ্ক_displays; ++i) {
        SDL_Display_তথ্য *internal = _this->displays[i]->internal;
        যদি (SDL_wcscmp(internal->DeviceName, info->szDevice) == 0) {
            bool moved = (সূচক != i);
            bool changed_bounds = false;

            যদি (internal->state != DisplayRemoved) {
                // We've already enumerated this display, don't move it
                যাও cleanup;
            }

            যদি (সূচক >= _this->অঙ্ক_displays) {
                // This should never happen due to the check above, but just in case...
                যাও cleanup;
            }

            যদি (moved) {
                SDL_VideoDisplay *tmp;

                tmp = _this->displays[সূচক];
                _this->displays[সূচক] = _this->displays[i];
                _this->displays[i] = tmp;
                i = সূচক;
            }

            internal->MonitorHandle = hMonitor;
            internal->state = DisplayUnchanged;

            SDL_PropertiesID props = SDL_GetDisplayProperties(_this->displays[i]->id);
            SDL_SetPointerProperty(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_POINTER, hMonitor);

            যদি (!_this->setting_display_mode) {
                SDL_VideoDisplay *existing_display = _this->displays[i];
                SDL_Rect bounds;

                SDL_ResetFullscreenDisplayModes(existing_display);
                SDL_SetDesktopDisplayMode(existing_display, &mode);
                // The mode is owned by the video subsystem
                mode.internal = ফাঁকা;
                যদি (WIN_GetDisplayBounds(_this, existing_display, &bounds) &&
                    SDL_memcmp(&internal->bounds, &bounds, আকার(bounds)) != 0) {
                    changed_bounds = true;
                    SDL_copyp(&internal->bounds, &bounds);
                }
                যদি (moved || changed_bounds) {
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
            যাও done;
        }
    }

    displaydata = (SDL_Display_তথ্য *)SDL_calloc(1, আকার(*displaydata));
    যদি (!displaydata) {
        যাও cleanup;
    }
    SDL_memcpy(displaydata->DeviceName, info->szDevice, আকার(displaydata->DeviceName));
    displaydata->MonitorHandle = hMonitor;
    displaydata->state = DisplayAdded;

    SDL_zero(display);
    display.name = WIN_GetDisplayNameVista(_this->internal, info->szDevice);
    যদি (!display.name) {
        DISPLAY_DEVICEW device;
        SDL_zero(device);
        device.cb = আকার(device);
        যদি (EnumDisplayDevicesW(info->szDevice, 0, &device, 0)) {
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
    যদি (displayID) {
        // The mode is owned by the video subsystem
        mode.internal = ফাঁকা;

        SDL_PropertiesID props = SDL_GetDisplayProperties(displayID);
        SDL_SetPointerProperty(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_POINTER, hMonitor);
    } অন্যথা {
        SDL_free(displaydata);
    }
    SDL_free(display.name);

done:
    *display_সূচক += 1;

cleanup:
    SDL_free(mode.internal);
}

প্রকারলেখ কাঠামো WIN_Add_Displays_তথ্য
{
    SDL_VideoDevice *video_device;
    পূর্ণসংখ্যা display_সূচক;
    bool want_primary;
} WIN_Add_Displays_তথ্য_2;

স্থির BOOL CALLBACK WIN_AddDisplaysCallback(HMONITOR hMonitor,
                                             HDC hdcMonitor,
                                             LPRECT lprcMonitor,
                                             LPARAM dw_তথ্য)
{
    WIN_Add_Displays_তথ্য_2 *তথ্য = (WIN_Add_Displays_তথ্য_2 *)dw_তথ্য;
    MONITORINFOEXW info;

    SDL_zero(info);
    info.cb_আকার = আকার(info);

    যদি (GetMonitorInfoW(hMonitor, (LPMONITORINFO)&info) != 0) {
        ধ্রুবক bool is_primary = ((info.dwFlags & MONITORINFOF_PRIMARY) == MONITORINFOF_PRIMARY);

        যদি (is_primary == তথ্য->want_primary) {
            WIN_AddDisplay(তথ্য->video_device, hMonitor, &info, &তথ্য->display_সূচক);
        }
    }

    // continue enumeration
    ফেরত TRUE;
}

স্থির শূন্য WIN_AddDisplays(SDL_VideoDevice *_this)
{
    WIN_Add_Displays_তথ্য_2 callback_তথ্য;
    callback_তথ্য.video_device = _this;
    callback_তথ্য.display_সূচক = 0;

    callback_তথ্য.want_primary = true;
    EnumDisplayMonitors(ফাঁকা, ফাঁকা, WIN_AddDisplaysCallback, (LPARAM)&callback_তথ্য);

    callback_তথ্য.want_primary = false;
    EnumDisplayMonitors(ফাঁকা, ফাঁকা, WIN_AddDisplaysCallback, (LPARAM)&callback_তথ্য);
}

bool WIN_InitModes(SDL_VideoDevice *_this)
{
    WIN_AddDisplays(_this);

    যদি (_this->অঙ্ক_displays == 0) {
        ফেরত SDL_SetError("No displays available");
    }
    ফেরত true;
}

bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ধ্রুবক SDL_Display_তথ্য *তথ্য = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cb_আকার = আকার(MONITORINFO);
    rc = GetMonitorInfo(তথ্য->MonitorHandle, &minfo);

    যদি (!rc) {
        ফেরত SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcMonitor.বাম;
    rect->y = minfo.rcMonitor.শীর্ষ;
    rect->w = minfo.rcMonitor.ডান - minfo.rcMonitor.বাম;
    rect->h = minfo.rcMonitor.bottom - minfo.rcMonitor.শীর্ষ;

    ফেরত true;
}

bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ধ্রুবক SDL_Display_তথ্য *তথ্য = display->internal;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cb_আকার = আকার(MONITORINFO);
    rc = GetMonitorInfo(তথ্য->MonitorHandle, &minfo);

    যদি (!rc) {
        ফেরত SDL_SetError("Couldn't find monitor data");
    }

    rect->x = minfo.rcWork.বাম;
    rect->y = minfo.rcWork.শীর্ষ;
    rect->w = minfo.rcWork.ডান - minfo.rcWork.বাম;
    rect->h = minfo.rcWork.bottom - minfo.rcWork.শীর্ষ;

    ফেরত true;
}

bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_তথ্য *তথ্য = display->internal;
    শূন্য *dxgi_output;
    DWORD i;
    SDL_DisplayMode mode;

    dxgi_output = WIN_GetDXGIOutput(_this, তথ্য->DeviceName);

    // Make sure we add the current mode to the list in case it's a custom mode that doesn't enumerate
    জন্য (i = ENUM_CURRENT_SETTINGS; ; ++i) {
        যদি (!WIN_GetDisplayMode(_this, dxgi_output, তথ্য->MonitorHandle, তথ্য->DeviceName, i, &mode, ফাঁকা, ফাঁকা)) {
            বিরতি;
        }
        যদি (SDL_ISPIXELFORMAT_INDEXED(mode.format)) {
            // We don't support palettized modes now
            SDL_free(mode.internal);
            চালু;
        }
        যদি (mode.format != SDL_PIXELFORMAT_UNKNOWN) {
            যদি (!SDL_AddFullscreenDisplayMode(display, &mode)) {
                SDL_free(mode.internal);
            }
        } অন্যথা {
            SDL_free(mode.internal);
        }
    }

    WIN_ReleaseDXGIOutput(dxgi_output);

    ফেরত true;
}

#ifdef DEBUG_MODES
স্থির শূন্য WIN_LogMonitor(SDL_VideoDevice *_this, HMONITOR mon)
{
    ধ্রুবক SDL_Video_তথ্য *vid_তথ্য = (ধ্রুবক SDL_Video_তথ্য *)_this->internal;
    MONITORINFOEX minfo;
    UINT xdpi = 0, ydpi = 0;
    অক্ষর *name_utf8;

    যদি (vid_তথ্য->GetDpiForMonitor) {
        vid_তথ্য->GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &xdpi, &ydpi);
    }

    SDL_zero(minfo);
    minfo.cb_আকার = আকার(minfo);
    GetMonitorInfo(mon, (LPMONITORINFO)&minfo);

    name_utf8 = WIN_StringToUTF8(minfo.szDevice);

    SDL_Log("WIN_LogMonitor: monitor \"%s\": dpi: %d windows screen coordinates: %d, %d, %dx%d",
            name_utf8,
            xdpi,
            minfo.rcMonitor.বাম,
            minfo.rcMonitor.শীর্ষ,
            minfo.rcMonitor.ডান - minfo.rcMonitor.বাম,
            minfo.rcMonitor.bottom - minfo.rcMonitor.শীর্ষ);

    SDL_free(name_utf8);
}
#endif

bool WIN_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    SDL_Display_তথ্য *displaydata = display->internal;
    SDL_Display_Mode_তথ্য *তথ্য = (SDL_Display_Mode_তথ্য *)mode->internal;
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
    যদি (mode->internal == display->desktop_mode.internal) {
#ifdef DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: resetting to original resolution");
#endif
        status = ChangeDisplaySettingsExW(displaydata->DeviceName, ফাঁকা, ফাঁকা, CDS_FULLSCREEN, ফাঁকা);
    } অন্যথা {
#ifdef DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: changing to %dx%d pixels", তথ্য->DeviceMode.dmPelsWidth, তথ্য->DeviceMode.dmPelsHeight);
#endif
        status = ChangeDisplaySettingsExW(displaydata->DeviceName, &তথ্য->DeviceMode, ফাঁকা, CDS_FULLSCREEN, ফাঁকা);
    }
    যদি (status != DISP_CHANGE_SUCCESSFUL) {
        ধ্রুবক অক্ষর *reason = "Unknown reason";
        নির্বাচন (status) {
        ক্ষেত্র DISP_CHANGE_BADFLAGS:
            reason = "DISP_CHANGE_BADFLAGS";
            বিরতি;
        ক্ষেত্র DISP_CHANGE_BADMODE:
            reason = "DISP_CHANGE_BADMODE";
            বিরতি;
        ক্ষেত্র DISP_CHANGE_BADPARAM:
            reason = "DISP_CHANGE_BADPARAM";
            বিরতি;
        ক্ষেত্র DISP_CHANGE_FAILED:
            reason = "DISP_CHANGE_FAILED";
            বিরতি;
        }
        ফেরত SDL_SetError("ChangeDisplaySettingsEx() failed: %s", reason);
    }

#ifdef DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state after mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#endif

    EnumDisplaySettingsW(displaydata->DeviceName, ENUM_CURRENT_SETTINGS, &তথ্য->DeviceMode);
    WIN_UpdateDisplayMode(_this, displaydata->DeviceName, ENUM_CURRENT_SETTINGS, mode);
    ফেরত true;
}

শূন্য WIN_RefreshDisplays(SDL_VideoDevice *_this)
{
    পূর্ণসংখ্যা i;

    // Mark all displays as potentially invalid to detect
    // entries that have actually been removed
    জন্য (i = 0; i < _this->অঙ্ক_displays; ++i) {
        SDL_Display_তথ্য *internal = _this->displays[i]->internal;
        internal->state = DisplayRemoved;
    }

    // Enumerate displays to add any new ones and mark still
    // connected entries as valid
    WIN_AddDisplays(_this);

    // Delete any entries still marked as invalid, iterate
    // in reverse as each delete takes effect immediately
    জন্য (i = _this->অঙ্ক_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_Display_তথ্য *internal = display->internal;
        যদি (internal->state == DisplayRemoved) {
            SDL_DelVideoDisplay(display->id, true);
        }
    }

    // Send events for any newly added displays
    জন্য (i = 0; i < _this->অঙ্ক_displays; ++i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_Display_তথ্য *internal = display->internal;
        যদি (internal->state == DisplayAdded) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
        }
    }
}

শূন্য WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this)
{
    // This almost never happens, so just go ahead and send update events for all displays
    জন্য (পূর্ণসংখ্যা i = 0; i < _this->অঙ্ক_displays; ++i) {
        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_CHANGED, 0, 0);
    }
}

শূন্য WIN_QuitModes(SDL_VideoDevice *_this)
{
    // All fullscreen windows should have restored modes by now
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
