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

#اگر_تعریف_شده HAVE_DXGI1_6_H
#تعریف_کن COBJMACROS
#ضمن <dxgi1_6.h>
#پایان_اگر

// Windows CE compatibility
#اگر_تعریف_نشده CDS_FULLSCREEN
#تعریف_کن CDS_FULLSCREEN 0
#پایان_اگر
#اگر_تعریف_نشده USER_DEFAULT_SCREEN_DPI
#تعریف_کن USER_DEFAULT_SCREEN_DPI 96
#پایان_اگر

// #define DEBUG_MODES
// #define HIGHDPI_DEBUG_VERBOSE

ساكن فراغ WIN_Update_Display_نما(SDL_VideoDevice *_this, LPCWSTR deviceName, DWORD شاخص, SDL_Display_نما *نما)
{
    SDL_Display_نما_داده *داده = (SDL_Display_نما_داده *)نما->داخلی;
    HDC hdc;

    داده->Device_نما.dmFields = (DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS);

    // NOLINTNEXTLINE(bugprone-assignment-in-if-condition): No simple way to extract the assignment
    إذا (شاخص == ENUM_CURRENT_SETTINGS && (hdc = CreateDCW(deviceName, عدم, عدم, عدم)) != عدم) {
        حرف bmi_داده[حجم(BITMAPINFOHEADER) + 256 * حجم(RGBQUAD)];
        LPBITMAPINFO bmi;
        HBITMAP hbm;

        SDL_zeroa(bmi_داده);
        bmi = (LPBITMAPINFO)bmi_داده;
        bmi->bmi_سرآیند.bi_اندازه = حجم(BITMAPINFOHEADER);

        hbm = CreateCompatibleBitmap(hdc, 1, 1);
        GetDIBits(hdc, hbm, 0, 1, عدم, bmi, DIB_RGB_COLORS);
        GetDIBits(hdc, hbm, 0, 1, عدم, bmi, DIB_RGB_COLORS);
        DeleteObject(hbm);
        DeleteDC(hdc);
        إذا (bmi->bmi_سرآیند.biCompression == BI_BITFIELDS) {
            بدل (*(Uint32 *)bmi->bmiColors) {
            حالة 0x00FF0000:
                نما->format = SDL_PIXELFORMAT_XRGB8888;
                اكسر;
            حالة 0x000000FF:
                نما->format = SDL_PIXELFORMAT_XBGR8888;
                اكسر;
            حالة 0xF800:
                نما->format = SDL_PIXELFORMAT_RGB565;
                اكسر;
            حالة 0x7C00:
                نما->format = SDL_PIXELFORMAT_XRGB1555;
                اكسر;
            }
        } وإلا إذا (bmi->bmi_سرآیند.biCompression == BI_RGB) {
            إذا (bmi->bmi_سرآیند.bi_بیت_شمار == 24) {
                نما->format = SDL_PIXELFORMAT_RGB24;
            } وإلا إذا (bmi->bmi_سرآیند.bi_بیت_شمار == 8) {
                نما->format = SDL_PIXELFORMAT_INDEX8;
            } وإلا إذا (bmi->bmi_سرآیند.bi_بیت_شمار == 4) {
                نما->format = SDL_PIXELFORMAT_INDEX4LSB;
            }
        }
    } وإلا إذا (نما->format == SDL_PIXELFORMAT_UNKNOWN) {
        // FIXME: Can we tell what this will be?
        إذا ((داده->Device_نما.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL) {
            بدل (داده->Device_نما.dm_بیتها_در_هر_Pel) {
            حالة 32:
                نما->format = SDL_PIXELFORMAT_XRGB8888;
                اكسر;
            حالة 24:
                نما->format = SDL_PIXELFORMAT_RGB24;
                اكسر;
            حالة 16:
                نما->format = SDL_PIXELFORMAT_RGB565;
                اكسر;
            حالة 15:
                نما->format = SDL_PIXELFORMAT_XRGB1555;
                اكسر;
            حالة 8:
                نما->format = SDL_PIXELFORMAT_INDEX8;
                اكسر;
            حالة 4:
                نما->format = SDL_PIXELFORMAT_INDEX4LSB;
                اكسر;
            }
        }
    }
}

ساكن فراغ *WIN_GetDXGIOutput(SDL_VideoDevice *_this, ثابت WCHAR *DeviceName)
{
    فراغ *نتیجه = عدم;

#اگر_تعریف_شده HAVE_DXGI_H
    ثابت SDL_Video_داده *videodata = (ثابت SDL_Video_داده *)_this->داخلی;
    صحيح nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    إذا (!videodata->pDXGIFactory) {
        أرجع عدم;
    }

    nAdapter = 0;
    طالما (!نتیجه && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        طالما (!نتیجه && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            إذا (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                إذا (SDL_wcscmp(outputDesc.DeviceName, DeviceName) == 0) {
                    نتیجه = pDXGIOutput;
                }
            }
            إذا (pDXGIOutput != نتیجه) {
                IDXGIOutput_Release(pDXGIOutput);
            }
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }
#پایان_اگر
    أرجع نتیجه;
}

ساكن فراغ WIN_ReleaseDXGIOutput(فراغ *dxgi_output)
{
#اگر_تعریف_شده HAVE_DXGI_H
    IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;

    إذا (pDXGIOutput) {
        IDXGIOutput_Release(pDXGIOutput);
    }
#پایان_اگر
}

ساكن SDL_DisplayOrientation WIN_GetNaturalOrientation(DEVMODEW *نما)
{
    صحيح عرض = نما->dm_Pels_عرض;
    صحيح ارتفاع = نما->dm_Pels_ارتفاع;

    // Use unrotated width/height to guess orientation
    إذا (نما->dmDisplayOrientation == DMDO_90 || نما->dmDisplayOrientation == DMDO_270) {
        صحيح موقت = عرض;
        عرض = ارتفاع;
        ارتفاع = موقت;
    }

    إذا (عرض >= ارتفاع) {
        أرجع SDL_ORIENTATION_LANDSCAPE;
    } وإلا {
        أرجع SDL_ORIENTATION_PORTRAIT;
    }
}

ساكن SDL_DisplayOrientation WIN_GetDisplayOrientation(DEVMODEW *نما)
{
    إذا (WIN_GetNaturalOrientation(نما) == SDL_ORIENTATION_LANDSCAPE) {
        بدل (نما->dmDisplayOrientation) {
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
        بدل (نما->dmDisplayOrientation) {
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

ساكن فراغ WIN_Get_Refresh_نرخ(فراغ *dxgi_output, DEVMODEW *نما, صحيح *numerator, صحيح *denominator)
{
    // We're not currently using DXGI to query display modes, so fake NTSC timings
    بدل (نما->dmDisplayFrequency) {
    حالة 119:
    حالة 59:
    حالة 29:
        *numerator = (نما->dmDisplayFrequency + 1) * 1000;
        *denominator = 1001;
        اكسر;
    افتراضي:
        *numerator = نما->dmDisplayFrequency;
        *denominator = 1;
        اكسر;
    }

#اگر_تعریف_شده HAVE_DXGI_H
    إذا (dxgi_output) {
        IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;
        DXGI_نما_DESC نما_مقصد_تطابق;
        DXGI_نما_DESC closest_تطابق;

        SDL_zero(نما_مقصد_تطابق);
        نما_مقصد_تطابق.عرض_2 = نما->dm_Pels_عرض;
        نما_مقصد_تطابق.ارتفاع_2 = نما->dm_Pels_ارتفاع;
        نما_مقصد_تطابق.Refresh_نرخ.Numerator = *numerator;
        نما_مقصد_تطابق.Refresh_نرخ.Denominator = *denominator;
        نما_مقصد_تطابق.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        إذا (SUCCEEDED(IDXGIOutput_پیدا_کن_Closest_Matching_نما(pDXGIOutput, &نما_مقصد_تطابق, &closest_تطابق, عدم))) {
            *numerator = closest_تطابق.Refresh_نرخ.Numerator;
            *denominator = closest_تطابق.Refresh_نرخ.Denominator;
        }
    }
#پایان_اگر // HAVE_DXGI_H
}

ساكن عائم WIN_GetContentScale(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    صحيح dpi = 0;

    ثابت SDL_Video_داده *videodata = (ثابت SDL_Video_داده *)_this->داخلی;
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

ساكن bool WIN_Get_Display_نما(SDL_VideoDevice *_this, فراغ *dxgi_output, HMONITOR hMonitor, LPCWSTR deviceName, DWORD شاخص, SDL_Display_نما *نما, SDL_DisplayOrientation *natural_orientation, SDL_DisplayOrientation *current_orientation)
{
    SDL_Display_نما_داده *داده;
    DEVMODEW devmode;

    devmode.dm_اندازه = حجم(devmode);
    devmode.dmDriverExtra = 0;
    إذا (!EnumDisplaySettingsW(deviceName, شاخص, &devmode)) {
        أرجع false;
    }

    داده = (SDL_Display_نما_داده *)SDL_malloc(حجم(*داده));
    إذا (!داده) {
        أرجع false;
    }

    SDL_zerop(نما);
    نما->داخلی = داده;
    داده->Device_نما = devmode;

    نما->format = SDL_PIXELFORMAT_UNKNOWN;
    نما->w = داده->Device_نما.dm_Pels_عرض;
    نما->h = داده->Device_نما.dm_Pels_ارتفاع;
    WIN_Get_Refresh_نرخ(dxgi_output, &داده->Device_نما, &نما->refresh_نرخ_numerator, &نما->refresh_نرخ_denominator);

    // Fill in the mode information
    WIN_Update_Display_نما(_this, deviceName, شاخص, نما);

    إذا (natural_orientation) {
        *natural_orientation = WIN_GetNaturalOrientation(&devmode);
    }
    إذا (current_orientation) {
        *current_orientation = WIN_GetDisplayOrientation(&devmode);
    }

    أرجع true;
}

ساكن حرف *WIN_GetDisplayNameVista(SDL_Video_داده *videodata, ثابت WCHAR *deviceName)
{
    DISPLAYCONFIG_مسیر_INFO *paths = عدم;
    DISPLAYCONFIG_نما_INFO *modes = عدم;
    حرف *نتیجه = عدم;
    UINT32 مسیر_شمار_2 = 0;
    UINT32 نما_شمار_2 = 0;
    UINT32 i;
    LONG rc;

    إذا (!videodata->Get_Display_Config_میانگیر_Sizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        أرجع عدم;
    }

    افعل {
        rc = videodata->Get_Display_Config_میانگیر_Sizes(QDC_ONLY_فعال_PATHS, &مسیر_شمار_2, &نما_شمار_2);
        إذا (rc != ERROR_SUCCESS) {
            اذهب WIN_GetDisplayNameVista_failed;
        }

        SDL_free(paths);
        SDL_free(modes);

        paths = (DISPLAYCONFIG_مسیر_INFO *)SDL_malloc(حجم(DISPLAYCONFIG_مسیر_INFO) * مسیر_شمار_2);
        modes = (DISPLAYCONFIG_نما_INFO *)SDL_malloc(حجم(DISPLAYCONFIG_نما_INFO) * نما_شمار_2);
        إذا ((!paths) || (!modes)) {
            اذهب WIN_GetDisplayNameVista_failed;
        }

        rc = videodata->QueryDisplayConfig(QDC_ONLY_فعال_PATHS, &مسیر_شمار_2, paths, &نما_شمار_2, modes, 0);
    } طالما (rc == ERROR_INSUFFICIENT_میانگیر);

    إذا (rc == ERROR_SUCCESS) {
        لكل (i = 0; i < مسیر_شمار_2; i++) {
            DISPLAYCONFIG_منبع_DEVICE_NAME منبع_Name;
            DISPLAYCONFIG_هدف_DEVICE_NAME هدف_Name;

            SDL_zero(منبع_Name);
            منبع_Name.سرآیند.adapterId = paths[i].هدف_Info.adapterId;
            منبع_Name.سرآیند.type = DISPLAYCONFIG_DEVICE_INFO_GET_منبع_NAME;
            منبع_Name.سرآیند.اندازه = حجم(منبع_Name);
            منبع_Name.سرآیند.id = paths[i].منبع_Info.id;
            rc = videodata->DisplayConfigGetDeviceInfo(&منبع_Name.سرآیند);
            إذا (rc != ERROR_SUCCESS) {
                اكسر;
            } وإلا إذا (SDL_wcscmp(deviceName, منبع_Name.viewGdiDeviceName) != 0) {
                استمر;
            }

            SDL_zero(هدف_Name);
            هدف_Name.سرآیند.adapterId = paths[i].هدف_Info.adapterId;
            هدف_Name.سرآیند.id = paths[i].هدف_Info.id;
            هدف_Name.سرآیند.type = DISPLAYCONFIG_DEVICE_INFO_GET_هدف_NAME;
            هدف_Name.سرآیند.اندازه = حجم(هدف_Name);
            rc = videodata->DisplayConfigGetDeviceInfo(&هدف_Name.سرآیند);
            إذا (rc == ERROR_SUCCESS) {
                نتیجه = WIN_String_مقصد_UTF8_W(هدف_Name.monitorFriendlyDeviceName);
                /* if we got an empty string, treat it as failure so we'll fallback
                   to getting the generic name. */
                إذا (نتیجه && (*نتیجه == '\0')) {
                    SDL_free(نتیجه);
                    نتیجه = عدم;
                }
            }
            اكسر;
        }
    }

    SDL_free(paths);
    SDL_free(modes);
    أرجع نتیجه;

WIN_GetDisplayNameVista_failed:
    SDL_free(نتیجه);
    SDL_free(paths);
    SDL_free(modes);
    أرجع عدم;
}

#اگر_تعریف_شده HAVE_DXGI1_6_H
ساكن bool WIN_GetMonitorDESC1(HMONITOR hMonitor, DXGI_OUTPUT_DESC1 *desc)
{
    تعريفنوع HRESULT (WINAPI *pfnCreateDXGIFactory1)(REFIID riid, فراغ **ppFactory);
    pfnCreateDXGIFactory1 pCreateDXGIFactory1 = عدم;
    SDL_SharedObject *hDXGIMod = عدم;
    bool یافت = false;

    hDXGIMod = SDL_بارگیری_Object("dxgi.dll");
    إذا (hDXGIMod) {
        pCreateDXGIFactory1 = (pfnCreateDXGIFactory1)SDL_بارگیری_Function(hDXGIMod, "CreateDXGIFactory1");
    }
    إذا (pCreateDXGIFactory1) {
        ساكن ثابت GUID SDL_IID_IDXGIFactory1 = { 0x770aae78, 0xf26f, 0x4dba, { 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 } };
        ساكن ثابت GUID SDL_IID_IDXGIOutput6 = { 0x068346e8, 0xaaec, 0x4b84, { 0xad, 0xd7, 0x13, 0x7f, 0x51, 0x3f, 0x77, 0xa1 } };
        IDXGIFactory1 *dxgiFactory;

        إذا (SUCCEEDED(pCreateDXGIFactory1(&SDL_IID_IDXGIFactory1, (فراغ **)&dxgiFactory))) {
            IDXGIAdapter1 *dxgiAdapter;
            UINT adapter = 0;
            طالما (!یافت && SUCCEEDED(IDXGIFactory1_EnumAdapters1(dxgiFactory, adapter, &dxgiAdapter))) {
                IDXGIOutput *dxgiOutput;
                UINT output = 0;
                طالما (!یافت && SUCCEEDED(IDXGIAdapter1_EnumOutputs(dxgiAdapter, output, &dxgiOutput))) {
                    IDXGIOutput6 *dxgiOutput6;
                    إذا (SUCCEEDED(IDXGIOutput_QueryInterface(dxgiOutput, &SDL_IID_IDXGIOutput6, (فراغ **)&dxgiOutput6))) {
                        إذا (SUCCEEDED(IDXGIOutput6_GetDesc1(dxgiOutput6, desc))) {
                            إذا (desc->Monitor == hMonitor) {
                                یافت = true;
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
    أرجع یافت;
}

ساكن bool WIN_Get_Monitor_مسیر_Info(SDL_Video_داده *videodata, HMONITOR hMonitor, DISPLAYCONFIG_مسیر_INFO *مسیر_info)
{
    LONG نتیجه;
    MONITORINFOEXW view_info;
    UINT32 i;
    UINT32 رقم_مسیر_array_elements = 0;
    UINT32 رقم_نما_info_array_elements = 0;
    DISPLAYCONFIG_مسیر_INFO *مسیر_infos = عدم, *new_مسیر_infos;
    DISPLAYCONFIG_نما_INFO *نما_infos = عدم, *new_نما_infos;
    bool یافت = false;

    إذا (!videodata->Get_Display_Config_میانگیر_Sizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        أرجع false;
    }

    SDL_zero(view_info);
    view_info.cb_اندازه = حجم(view_info);
    إذا (!GetMonitorInfoW(hMonitor, (MONITORINFO *)&view_info)) {
        اذهب انجامشده;
    }

    افعل {
        إذا (videodata->Get_Display_Config_میانگیر_Sizes(QDC_ONLY_فعال_PATHS, &رقم_مسیر_array_elements, &رقم_نما_info_array_elements) != ERROR_SUCCESS) {
            SDL_free(مسیر_infos);
            SDL_free(نما_infos);
            أرجع false;
        }

        new_مسیر_infos = (DISPLAYCONFIG_مسیر_INFO *)SDL_realloc(مسیر_infos, رقم_مسیر_array_elements * حجم(*مسیر_infos));
        إذا (!new_مسیر_infos) {
            اذهب انجامشده;
        }
        مسیر_infos = new_مسیر_infos;

        new_نما_infos = (DISPLAYCONFIG_نما_INFO *)SDL_realloc(نما_infos, رقم_نما_info_array_elements * حجم(*نما_infos));
        إذا (!new_نما_infos) {
            اذهب انجامشده;
        }
        نما_infos = new_نما_infos;

        نتیجه = videodata->QueryDisplayConfig(QDC_ONLY_فعال_PATHS, &رقم_مسیر_array_elements, مسیر_infos, &رقم_نما_info_array_elements, نما_infos, عدم);

    } طالما (نتیجه == ERROR_INSUFFICIENT_میانگیر);

    إذا (نتیجه == ERROR_SUCCESS) {
        لكل (i = 0; i < رقم_مسیر_array_elements; ++i) {
            DISPLAYCONFIG_منبع_DEVICE_NAME device_name;

            SDL_zero(device_name);
            device_name.سرآیند.type = DISPLAYCONFIG_DEVICE_INFO_GET_منبع_NAME;
            device_name.سرآیند.اندازه = حجم(device_name);
            device_name.سرآیند.adapterId = مسیر_infos[i].منبع_Info.adapterId;
            device_name.سرآیند.id = مسیر_infos[i].منبع_Info.id;
            إذا (videodata->DisplayConfigGetDeviceInfo(&device_name.سرآیند) == ERROR_SUCCESS) {
                إذا (SDL_wcscmp(view_info.szDevice, device_name.viewGdiDeviceName) == 0) {
                    SDL_copyp(مسیر_info, &مسیر_infos[i]);
                    یافت = true;
                    اكسر;
                }
            }
        }
    }

انجامشده:
    SDL_free(مسیر_infos);
    SDL_free(نما_infos);

    أرجع یافت;
}

ساكن عائم WIN_Get_SDRWhite_نقطه(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    DISPLAYCONFIG_مسیر_INFO مسیر_info;
    SDL_Video_داده *videodata = _this->داخلی;
    عائم SDR_white_level = 1.0f;

    إذا (WIN_Get_Monitor_مسیر_Info(videodata, hMonitor, &مسیر_info)) {
        /* workarounds for https://github.com/libsdl-org/SDL/issues/11193 */
        بنية SDL_DISPLAYCONFIG_SDR_WHITE_LEVEL {
          DISPLAYCONFIG_DEVICE_INFO_سرآیند سرآیند;
          ULONG SDRWhiteLevel;
        } white_level;
        #تعریف_کن DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL 11

        SDL_zero(white_level);
        white_level.سرآیند.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
        white_level.سرآیند.اندازه = حجم(white_level);
        white_level.سرآیند.adapterId = مسیر_info.هدف_Info.adapterId;
        white_level.سرآیند.id = مسیر_info.هدف_Info.id;
        // WIN_GetMonitorPathInfo() succeeded: DisplayConfigGetDeviceInfo is not NULL
        إذا (videodata->DisplayConfigGetDeviceInfo(&white_level.سرآیند) == ERROR_SUCCESS &&
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
        إذا (desc.ColorSpace == DXGI_COLOR_SPACE_RGB_پر_G2084_NONE_P2020) {
            HDR->SDR_white_level = WIN_Get_SDRWhite_نقطه(_this, hMonitor);
            HDR->HDR_headroom = (desc.MaxLuminance / SCRGB_NITS) / HDR->SDR_white_level;
        }
    }
}
#پایان_اگر // HAVE_DXGI1_6_H

ساكن فراغ WIN_جمع_کن_Display(SDL_VideoDevice *_this, HMONITOR hMonitor, ثابت MONITORINFOEXW *info, صحيح *display_شاخص)
{
    صحيح i, شاخص = *display_شاخص;
    SDL_VideoDisplay display;
    SDL_Display_داده *displaydata;
    فراغ *dxgi_output = عدم;
    SDL_Display_نما نما;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    عائم content_scale = WIN_GetContentScale(_this, hMonitor);

#اگر_تعریف_شده DEBUG_MODES
    SDL_Log("Display: %s", WIN_String_مقصد_UTF8_W(info->szDevice));
#پایان_اگر

    dxgi_output = WIN_GetDXGIOutput(_this, info->szDevice);
    bool یافت = WIN_Get_Display_نما(_this, dxgi_output, hMonitor, info->szDevice, ENUM_CURRENT_SETTINGS, &نما, &natural_orientation, &current_orientation);
    WIN_ReleaseDXGIOutput(dxgi_output);
    إذا (!یافت) {
        أرجع;
    }

    // Prevent adding duplicate displays. Do this after we know the display is
    // ready to be added to allow any displays that we can't fully query to be
    // removed
    لكل (i = 0; i < _this->رقم_displays; ++i) {
        SDL_Display_داده *داخلی = _this->displays[i]->داخلی;
        إذا (SDL_wcscmp(داخلی->DeviceName, info->szDevice) == 0) {
            bool moved = (شاخص != i);
            bool تغییریافته_bounds = false;

            إذا (داخلی->state != DisplayRemoved) {
                // We've already enumerated this display, don't move it
                اذهب cleanup;
            }

            إذا (شاخص >= _this->رقم_displays) {
                // This should never happen due to the check above, but just in case...
                اذهب cleanup;
            }

            إذا (moved) {
                SDL_VideoDisplay *tmp;

                tmp = _this->displays[شاخص];
                _this->displays[شاخص] = _this->displays[i];
                _this->displays[i] = tmp;
                i = شاخص;
            }

            داخلی->MonitorHandle = hMonitor;
            داخلی->state = DisplayUnchanged;

            SDL_PropertiesID props = SDL_GetDisplayProperties(_this->displays[i]->id);
            SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_اشاره_گر, hMonitor);

            إذا (!_this->setting_display_نما) {
                SDL_VideoDisplay *existing_display = _this->displays[i];
                SDL_Rect bounds;

                SDL_ResetFullscreenDisplayModes(existing_display);
                SDL_مجموعه_Desktop_Display_نما(existing_display, &نما);
                // The mode is owned by the video subsystem
                نما.داخلی = عدم;
                إذا (WIN_GetDisplayBounds(_this, existing_display, &bounds) &&
                    SDL_memcmp(&داخلی->bounds, &bounds, حجم(bounds)) != 0) {
                    تغییریافته_bounds = true;
                    SDL_copyp(&داخلی->bounds, &bounds);
                }
                إذا (moved || تغییریافته_bounds) {
                    SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_MOVED, 0, 0);
                }
                SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_ORIENTATION, current_orientation, 0);
                SDL_مجموعه_Display_Content_Scale(existing_display, content_scale);
#اگر_تعریف_شده HAVE_DXGI1_6_H
                SDL_HDROutputProperties HDR;
                WIN_GetHDRProperties(_this, hMonitor, &HDR);
                SDL_مجموعه_Display_HDRProperties(existing_display, &HDR);
#پایان_اگر
            }
            اذهب انجامشده;
        }
    }

    displaydata = (SDL_Display_داده *)SDL_calloc(1, حجم(*displaydata));
    إذا (!displaydata) {
        اذهب cleanup;
    }
    SDL_memcpy(displaydata->DeviceName, info->szDevice, حجم(displaydata->DeviceName));
    displaydata->MonitorHandle = hMonitor;
    displaydata->state = DisplayAdded;

    SDL_zero(display);
    display.name = WIN_GetDisplayNameVista(_this->داخلی, info->szDevice);
    إذا (!display.name) {
        DISPLAY_DEVICEW device;
        SDL_zero(device);
        device.cb = حجم(device);
        إذا (EnumDisplayDevicesW(info->szDevice, 0, &device, 0)) {
            display.name = WIN_String_مقصد_UTF8_W(device.DeviceString);
        }
    }

    display.desktop_نما = نما;
    display.natural_orientation = natural_orientation;
    display.current_orientation = current_orientation;
    display.content_scale = content_scale;
    display.device = _this;
    display.داخلی = displaydata;
    WIN_GetDisplayBounds(_this, &display, &displaydata->bounds);
#اگر_تعریف_شده HAVE_DXGI1_6_H
    WIN_GetHDRProperties(_this, hMonitor, &display.HDR);
#پایان_اگر
    SDL_DisplayID displayID = SDL_جمع_کن_Video_Display(&display, false);
    إذا (displayID) {
        // The mode is owned by the video subsystem
        نما.داخلی = عدم;

        SDL_PropertiesID props = SDL_GetDisplayProperties(displayID);
        SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_اشاره_گر, hMonitor);
    } وإلا {
        SDL_free(displaydata);
    }
    SDL_free(display.name);

انجامشده:
    *display_شاخص += 1;

cleanup:
    SDL_free(نما.داخلی);
}

تعريفنوع بنية WIN_جمع_کن_Displays_داده
{
    SDL_VideoDevice *video_device;
    صحيح display_شاخص;
    bool want_primary;
} WIN_جمع_کن_Displays_داده_2;

ساكن BOOL CALLBACK WIN_جمع_کن_Displays_Callback(HMONITOR hMonitor,
                                             HDC hdcMonitor,
                                             LPRECT lprcMonitor,
                                             LPARAM dw_داده)
{
    WIN_جمع_کن_Displays_داده_2 *داده = (WIN_جمع_کن_Displays_داده_2 *)dw_داده;
    MONITORINFOEXW info;

    SDL_zero(info);
    info.cb_اندازه = حجم(info);

    إذا (GetMonitorInfoW(hMonitor, (LPMONITORINFO)&info) != 0) {
        ثابت bool is_primary = ((info.dwFlags & MONITORINFOF_PRIMARY) == MONITORINFOF_PRIMARY);

        إذا (is_primary == داده->want_primary) {
            WIN_جمع_کن_Display(داده->video_device, hMonitor, &info, &داده->display_شاخص);
        }
    }

    // continue enumeration
    أرجع TRUE;
}

ساكن فراغ WIN_جمع_کن_Displays(SDL_VideoDevice *_this)
{
    WIN_جمع_کن_Displays_داده_2 callback_داده;
    callback_داده.video_device = _this;
    callback_داده.display_شاخص = 0;

    callback_داده.want_primary = true;
    EnumDisplayMonitors(عدم, عدم, WIN_جمع_کن_Displays_Callback, (LPARAM)&callback_داده);

    callback_داده.want_primary = false;
    EnumDisplayMonitors(عدم, عدم, WIN_جمع_کن_Displays_Callback, (LPARAM)&callback_داده);
}

bool WIN_InitModes(SDL_VideoDevice *_this)
{
    WIN_جمع_کن_Displays(_this);

    إذا (_this->رقم_displays == 0) {
        أرجع SDL_مجموعه_Error("No displays available");
    }
    أرجع true;
}

bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ثابت SDL_Display_داده *داده = display->داخلی;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cb_اندازه = حجم(MONITORINFO);
    rc = GetMonitorInfo(داده->MonitorHandle, &minfo);

    إذا (!rc) {
        أرجع SDL_مجموعه_Error("Couldn't find monitor data");
    }

    rect->x = minfo.rcMonitor.چپ;
    rect->y = minfo.rcMonitor.بالاترین;
    rect->w = minfo.rcMonitor.راست - minfo.rcMonitor.چپ;
    rect->h = minfo.rcMonitor.bottom - minfo.rcMonitor.بالاترین;

    أرجع true;
}

bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ثابت SDL_Display_داده *داده = display->داخلی;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cb_اندازه = حجم(MONITORINFO);
    rc = GetMonitorInfo(داده->MonitorHandle, &minfo);

    إذا (!rc) {
        أرجع SDL_مجموعه_Error("Couldn't find monitor data");
    }

    rect->x = minfo.rcWork.چپ;
    rect->y = minfo.rcWork.بالاترین;
    rect->w = minfo.rcWork.راست - minfo.rcWork.چپ;
    rect->h = minfo.rcWork.bottom - minfo.rcWork.بالاترین;

    أرجع true;
}

bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_داده *داده = display->داخلی;
    فراغ *dxgi_output;
    DWORD i;
    SDL_Display_نما نما;

    dxgi_output = WIN_GetDXGIOutput(_this, داده->DeviceName);

    // Make sure we add the current mode to the list in case it's a custom mode that doesn't enumerate
    لكل (i = ENUM_CURRENT_SETTINGS; ; ++i) {
        إذا (!WIN_Get_Display_نما(_this, dxgi_output, داده->MonitorHandle, داده->DeviceName, i, &نما, عدم, عدم)) {
            اكسر;
        }
        إذا (SDL_ISPIXELFORMAT_نمایهای(نما.format)) {
            // We don't support palettized modes now
            SDL_free(نما.داخلی);
            استمر;
        }
        إذا (نما.format != SDL_PIXELFORMAT_UNKNOWN) {
            إذا (!SDL_جمع_کن_Fullscreen_Display_نما(display, &نما)) {
                SDL_free(نما.داخلی);
            }
        } وإلا {
            SDL_free(نما.داخلی);
        }
    }

    WIN_ReleaseDXGIOutput(dxgi_output);

    أرجع true;
}

#اگر_تعریف_شده DEBUG_MODES
ساكن فراغ WIN_LogMonitor(SDL_VideoDevice *_this, HMONITOR mon)
{
    ثابت SDL_Video_داده *vid_داده = (ثابت SDL_Video_داده *)_this->داخلی;
    MONITORINFOEX minfo;
    UINT xdpi = 0, ydpi = 0;
    حرف *name_utf8;

    إذا (vid_داده->GetDpiForMonitor) {
        vid_داده->GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &xdpi, &ydpi);
    }

    SDL_zero(minfo);
    minfo.cb_اندازه = حجم(minfo);
    GetMonitorInfo(mon, (LPMONITORINFO)&minfo);

    name_utf8 = WIN_String_مقصد_UTF8(minfo.szDevice);

    SDL_Log("WIN_LogMonitor: monitor \"%s\": dpi: %d windows screen coordinates: %d, %d, %dx%d",
            name_utf8,
            xdpi,
            minfo.rcMonitor.چپ,
            minfo.rcMonitor.بالاترین,
            minfo.rcMonitor.راست - minfo.rcMonitor.چپ,
            minfo.rcMonitor.bottom - minfo.rcMonitor.بالاترین);

    SDL_free(name_utf8);
}
#پایان_اگر

bool WIN_مجموعه_Display_نما(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_نما *نما)
{
    SDL_Display_داده *displaydata = display->داخلی;
    SDL_Display_نما_داده *داده = (SDL_Display_نما_داده *)نما->داخلی;
    LONG وضعیت;

#اگر_تعریف_شده DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state before mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#پایان_اگر

    /* High-DPI notes:

       - ChangeDisplaySettingsEx always takes pixels.
       - e.g. if the display is set to 2880x1800 with 200% scaling in Display Settings
         - calling ChangeDisplaySettingsEx with a dmPelsWidth/Height other than 2880x1800 will
           change the monitor DPI to 96. (100% scaling)
         - calling ChangeDisplaySettingsEx with a dmPelsWidth/Height of 2880x1800 (or a NULL DEVMODE*) will
           reset the monitor DPI to 192. (200% scaling)

       NOTE: these are temporary changes in DPI, not modifications to the Control Panel setting. */
    إذا (نما->داخلی == display->desktop_نما.داخلی) {
#اگر_تعریف_شده DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: resetting to original resolution");
#پایان_اگر
        وضعیت = ChangeDisplaySettingsExW(displaydata->DeviceName, عدم, عدم, CDS_FULLSCREEN, عدم);
    } وإلا {
#اگر_تعریف_شده DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: changing to %dx%d pixels", داده->Device_نما.dm_Pels_عرض, داده->Device_نما.dm_Pels_ارتفاع);
#پایان_اگر
        وضعیت = ChangeDisplaySettingsExW(displaydata->DeviceName, &داده->Device_نما, عدم, CDS_FULLSCREEN, عدم);
    }
    إذا (وضعیت != DISP_CHANGE_SUCCESSFUL) {
        ثابت حرف *reason = "Unknown reason";
        بدل (وضعیت) {
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
        أرجع SDL_مجموعه_Error("ChangeDisplaySettingsEx() failed: %s", reason);
    }

#اگر_تعریف_شده DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state after mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#پایان_اگر

    EnumDisplaySettingsW(displaydata->DeviceName, ENUM_CURRENT_SETTINGS, &داده->Device_نما);
    WIN_Update_Display_نما(_this, displaydata->DeviceName, ENUM_CURRENT_SETTINGS, نما);
    أرجع true;
}

فراغ WIN_RefreshDisplays(SDL_VideoDevice *_this)
{
    صحيح i;

    // Mark all displays as potentially invalid to detect
    // entries that have actually been removed
    لكل (i = 0; i < _this->رقم_displays; ++i) {
        SDL_Display_داده *داخلی = _this->displays[i]->داخلی;
        داخلی->state = DisplayRemoved;
    }

    // Enumerate displays to add any new ones and mark still
    // connected entries as valid
    WIN_جمع_کن_Displays(_this);

    // Delete any entries still marked as invalid, iterate
    // in reverse as each delete takes effect immediately
    لكل (i = _this->رقم_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_Display_داده *داخلی = display->داخلی;
        إذا (داخلی->state == DisplayRemoved) {
            SDL_DelVideoDisplay(display->id, true);
        }
    }

    // Send events for any newly added displays
    لكل (i = 0; i < _this->رقم_displays; ++i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_Display_داده *داخلی = display->داخلی;
        إذا (داخلی->state == DisplayAdded) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
        }
    }
}

فراغ WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this)
{
    // This almost never happens, so just go ahead and send update events for all displays
    لكل (صحيح i = 0; i < _this->رقم_displays; ++i) {
        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_تغییریافته, 0, 0);
    }
}

فراغ WIN_QuitModes(SDL_VideoDevice *_this)
{
    // All fullscreen windows should have restored modes by now
}

#پایان_اگر // SDL_VIDEO_DRIVER_WINDOWS
