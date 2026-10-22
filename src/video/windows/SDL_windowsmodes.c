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

#جے_تعریف_شدہ HAVE_DXGI1_6_H
#تعریف_کرو COBJMACROS
#ضمن <dxgi1_6.h>
#جے_انت

// Windows CE compatibility
#جے_بنا_تعریف CDS_FULLSCREEN
#تعریف_کرو CDS_FULLSCREEN 0
#جے_انت
#جے_بنا_تعریف USER_DEFAULT_SCREEN_DPI
#تعریف_کرو USER_DEFAULT_SCREEN_DPI 96
#جے_انت

// #define DEBUG_MODES
// #define HIGHDPI_DEBUG_VERBOSE

ساكن فراغ WIN_Update_Display_منوال(SDL_VideoDevice *_this, LPCWSTR deviceName, DWORD اشاریہ, SDL_Display_منوال *منوال)
{
    SDL_Display_منوال_انکڑے *انکڑے = (SDL_Display_منوال_انکڑے *)منوال->اندرونی;
    HDC hdc;

    انکڑے->Device_منوال.dmFields = (DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS);

    // NOLINTNEXTLINE(bugprone-assignment-in-if-condition): No simple way to extract the assignment
    إذا (اشاریہ == ENUM_CURRENT_SETTINGS && (hdc = CreateDCW(deviceName, عدم, عدم, عدم)) != عدم) {
        حرف bmi_انکڑے[حجم(BITMAPINFOHEADER) + 256 * حجم(RGBQUAD)];
        LPBITMAPINFO bmi;
        HBITMAP hbm;

        SDL_zeroa(bmi_انکڑے);
        bmi = (LPBITMAPINFO)bmi_انکڑے;
        bmi->bmi_سرخی.bi_ناپ = حجم(BITMAPINFOHEADER);

        hbm = CreateCompatibleBitmap(hdc, 1, 1);
        GetDIBits(hdc, hbm, 0, 1, عدم, bmi, DIB_RGB_COLORS);
        GetDIBits(hdc, hbm, 0, 1, عدم, bmi, DIB_RGB_COLORS);
        DeleteObject(hbm);
        DeleteDC(hdc);
        إذا (bmi->bmi_سرخی.biCompression == BI_BITFIELDS) {
            بدل (*(Uint32 *)bmi->bmiColors) {
            حالة 0x00FF0000:
                منوال->format = SDL_PIXELFORMAT_XRGB8888;
                اكسر;
            حالة 0x000000FF:
                منوال->format = SDL_PIXELFORMAT_XBGR8888;
                اكسر;
            حالة 0xF800:
                منوال->format = SDL_PIXELFORMAT_RGB565;
                اكسر;
            حالة 0x7C00:
                منوال->format = SDL_PIXELFORMAT_XRGB1555;
                اكسر;
            }
        } وإلا إذا (bmi->bmi_سرخی.biCompression == BI_RGB) {
            إذا (bmi->bmi_سرخی.bi_ثنائی_ہندسہ_گنتی == 24) {
                منوال->format = SDL_PIXELFORMAT_RGB24;
            } وإلا إذا (bmi->bmi_سرخی.bi_ثنائی_ہندسہ_گنتی == 8) {
                منوال->format = SDL_PIXELFORMAT_INDEX8;
            } وإلا إذا (bmi->bmi_سرخی.bi_ثنائی_ہندسہ_گنتی == 4) {
                منوال->format = SDL_PIXELFORMAT_INDEX4LSB;
            }
        }
    } وإلا إذا (منوال->format == SDL_PIXELFORMAT_UNKNOWN) {
        // FIXME: Can we tell what this will be?
        إذا ((انکڑے->Device_منوال.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL) {
            بدل (انکڑے->Device_منوال.dm_بٹ_فی_Pel) {
            حالة 32:
                منوال->format = SDL_PIXELFORMAT_XRGB8888;
                اكسر;
            حالة 24:
                منوال->format = SDL_PIXELFORMAT_RGB24;
                اكسر;
            حالة 16:
                منوال->format = SDL_PIXELFORMAT_RGB565;
                اكسر;
            حالة 15:
                منوال->format = SDL_PIXELFORMAT_XRGB1555;
                اكسر;
            حالة 8:
                منوال->format = SDL_PIXELFORMAT_INDEX8;
                اكسر;
            حالة 4:
                منوال->format = SDL_PIXELFORMAT_INDEX4LSB;
                اكسر;
            }
        }
    }
}

ساكن فراغ *WIN_GetDXGIOutput(SDL_VideoDevice *_this, ثابت WCHAR *DeviceName)
{
    فراغ *نتیجہ = عدم;

#جے_تعریف_شدہ HAVE_DXGI_H
    ثابت SDL_Video_انکڑے *videodata = (ثابت SDL_Video_انکڑے *)_this->اندرونی;
    صحيح nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    إذا (!videodata->pDXGIFactory) {
        أرجع عدم;
    }

    nAdapter = 0;
    طالما (!نتیجہ && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        طالما (!نتیجہ && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            إذا (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                إذا (SDL_wcscmp(outputDesc.DeviceName, DeviceName) == 0) {
                    نتیجہ = pDXGIOutput;
                }
            }
            إذا (pDXGIOutput != نتیجہ) {
                IDXGIOutput_Release(pDXGIOutput);
            }
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }
#جے_انت
    أرجع نتیجہ;
}

ساكن فراغ WIN_ReleaseDXGIOutput(فراغ *dxgi_output)
{
#جے_تعریف_شدہ HAVE_DXGI_H
    IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;

    إذا (pDXGIOutput) {
        IDXGIOutput_Release(pDXGIOutput);
    }
#جے_انت
}

ساكن SDL_DisplayOrientation WIN_GetNaturalOrientation(DEVMODEW *منوال)
{
    صحيح چوڑائی = منوال->dm_Pels_چوڑائی;
    صحيح اچائی = منوال->dm_Pels_اچائی;

    // Use unrotated width/height to guess orientation
    إذا (منوال->dmDisplayOrientation == DMDO_90 || منوال->dmDisplayOrientation == DMDO_270) {
        صحيح عارضی = چوڑائی;
        چوڑائی = اچائی;
        اچائی = عارضی;
    }

    إذا (چوڑائی >= اچائی) {
        أرجع SDL_ORIENTATION_LANDSCAPE;
    } وإلا {
        أرجع SDL_ORIENTATION_PORTRAIT;
    }
}

ساكن SDL_DisplayOrientation WIN_GetDisplayOrientation(DEVMODEW *منوال)
{
    إذا (WIN_GetNaturalOrientation(منوال) == SDL_ORIENTATION_LANDSCAPE) {
        بدل (منوال->dmDisplayOrientation) {
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
        بدل (منوال->dmDisplayOrientation) {
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

ساكن فراغ WIN_Get_Refresh_شرح(فراغ *dxgi_output, DEVMODEW *منوال, صحيح *numerator, صحيح *denominator)
{
    // We're not currently using DXGI to query display modes, so fake NTSC timings
    بدل (منوال->dmDisplayFrequency) {
    حالة 119:
    حالة 59:
    حالة 29:
        *numerator = (منوال->dmDisplayFrequency + 1) * 1000;
        *denominator = 1001;
        اكسر;
    افتراضي:
        *numerator = منوال->dmDisplayFrequency;
        *denominator = 1;
        اكسر;
    }

#جے_تعریف_شدہ HAVE_DXGI_H
    إذا (dxgi_output) {
        IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;
        DXGI_منوال_DESC منوال_منزل_میل;
        DXGI_منوال_DESC closest_میل;

        SDL_zero(منوال_منزل_میل);
        منوال_منزل_میل.چوڑائی_2 = منوال->dm_Pels_چوڑائی;
        منوال_منزل_میل.اچائی_2 = منوال->dm_Pels_اچائی;
        منوال_منزل_میل.Refresh_شرح.Numerator = *numerator;
        منوال_منزل_میل.Refresh_شرح.Denominator = *denominator;
        منوال_منزل_میل.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        إذا (SUCCEEDED(IDXGIOutput_لبھو_Closest_Matching_منوال(pDXGIOutput, &منوال_منزل_میل, &closest_میل, عدم))) {
            *numerator = closest_میل.Refresh_شرح.Numerator;
            *denominator = closest_میل.Refresh_شرح.Denominator;
        }
    }
#جے_انت // HAVE_DXGI_H
}

ساكن عائم WIN_GetContentScale(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    صحيح dpi = 0;

    ثابت SDL_Video_انکڑے *videodata = (ثابت SDL_Video_انکڑے *)_this->اندرونی;
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

ساكن bool WIN_Get_Display_منوال(SDL_VideoDevice *_this, فراغ *dxgi_output, HMONITOR hMonitor, LPCWSTR deviceName, DWORD اشاریہ, SDL_Display_منوال *منوال, SDL_DisplayOrientation *natural_orientation, SDL_DisplayOrientation *current_orientation)
{
    SDL_Display_منوال_انکڑے *انکڑے;
    DEVMODEW devmode;

    devmode.dm_ناپ = حجم(devmode);
    devmode.dmDriverExtra = 0;
    إذا (!EnumDisplaySettingsW(deviceName, اشاریہ, &devmode)) {
        أرجع false;
    }

    انکڑے = (SDL_Display_منوال_انکڑے *)SDL_malloc(حجم(*انکڑے));
    إذا (!انکڑے) {
        أرجع false;
    }

    SDL_zerop(منوال);
    منوال->اندرونی = انکڑے;
    انکڑے->Device_منوال = devmode;

    منوال->format = SDL_PIXELFORMAT_UNKNOWN;
    منوال->w = انکڑے->Device_منوال.dm_Pels_چوڑائی;
    منوال->h = انکڑے->Device_منوال.dm_Pels_اچائی;
    WIN_Get_Refresh_شرح(dxgi_output, &انکڑے->Device_منوال, &منوال->refresh_شرح_numerator, &منوال->refresh_شرح_denominator);

    // Fill in the mode information
    WIN_Update_Display_منوال(_this, deviceName, اشاریہ, منوال);

    إذا (natural_orientation) {
        *natural_orientation = WIN_GetNaturalOrientation(&devmode);
    }
    إذا (current_orientation) {
        *current_orientation = WIN_GetDisplayOrientation(&devmode);
    }

    أرجع true;
}

ساكن حرف *WIN_GetDisplayNameVista(SDL_Video_انکڑے *videodata, ثابت WCHAR *deviceName)
{
    DISPLAYCONFIG_رستہ_INFO *paths = عدم;
    DISPLAYCONFIG_منوال_INFO *modes = عدم;
    حرف *نتیجہ = عدم;
    UINT32 رستہ_گنتی_2 = 0;
    UINT32 منوال_گنتی_2 = 0;
    UINT32 i;
    LONG rc;

    إذا (!videodata->Get_Display_Config_بفر_Sizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        أرجع عدم;
    }

    افعل {
        rc = videodata->Get_Display_Config_بفر_Sizes(QDC_ONLY_سرگرم_PATHS, &رستہ_گنتی_2, &منوال_گنتی_2);
        إذا (rc != ERROR_SUCCESS) {
            اذهب WIN_GetDisplayNameVista_failed;
        }

        SDL_free(paths);
        SDL_free(modes);

        paths = (DISPLAYCONFIG_رستہ_INFO *)SDL_malloc(حجم(DISPLAYCONFIG_رستہ_INFO) * رستہ_گنتی_2);
        modes = (DISPLAYCONFIG_منوال_INFO *)SDL_malloc(حجم(DISPLAYCONFIG_منوال_INFO) * منوال_گنتی_2);
        إذا ((!paths) || (!modes)) {
            اذهب WIN_GetDisplayNameVista_failed;
        }

        rc = videodata->QueryDisplayConfig(QDC_ONLY_سرگرم_PATHS, &رستہ_گنتی_2, paths, &منوال_گنتی_2, modes, 0);
    } طالما (rc == ERROR_INSUFFICIENT_بفر);

    إذا (rc == ERROR_SUCCESS) {
        لكل (i = 0; i < رستہ_گنتی_2; i++) {
            DISPLAYCONFIG_سروت_DEVICE_NAME سروت_Name;
            DISPLAYCONFIG_نشانہ_DEVICE_NAME نشانہ_Name;

            SDL_zero(سروت_Name);
            سروت_Name.سرخی.adapterId = paths[i].نشانہ_Info.adapterId;
            سروت_Name.سرخی.type = DISPLAYCONFIG_DEVICE_INFO_GET_سروت_NAME;
            سروت_Name.سرخی.ناپ = حجم(سروت_Name);
            سروت_Name.سرخی.id = paths[i].سروت_Info.id;
            rc = videodata->DisplayConfigGetDeviceInfo(&سروت_Name.سرخی);
            إذا (rc != ERROR_SUCCESS) {
                اكسر;
            } وإلا إذا (SDL_wcscmp(deviceName, سروت_Name.viewGdiDeviceName) != 0) {
                استمر;
            }

            SDL_zero(نشانہ_Name);
            نشانہ_Name.سرخی.adapterId = paths[i].نشانہ_Info.adapterId;
            نشانہ_Name.سرخی.id = paths[i].نشانہ_Info.id;
            نشانہ_Name.سرخی.type = DISPLAYCONFIG_DEVICE_INFO_GET_نشانہ_NAME;
            نشانہ_Name.سرخی.ناپ = حجم(نشانہ_Name);
            rc = videodata->DisplayConfigGetDeviceInfo(&نشانہ_Name.سرخی);
            إذا (rc == ERROR_SUCCESS) {
                نتیجہ = WIN_String_منزل_UTF8_W(نشانہ_Name.monitorFriendlyDeviceName);
                /* if we got an empty string, treat it as failure so we'll fallback
                   to getting the generic name. */
                إذا (نتیجہ && (*نتیجہ == '\0')) {
                    SDL_free(نتیجہ);
                    نتیجہ = عدم;
                }
            }
            اكسر;
        }
    }

    SDL_free(paths);
    SDL_free(modes);
    أرجع نتیجہ;

WIN_GetDisplayNameVista_failed:
    SDL_free(نتیجہ);
    SDL_free(paths);
    SDL_free(modes);
    أرجع عدم;
}

#جے_تعریف_شدہ HAVE_DXGI1_6_H
ساكن bool WIN_GetMonitorDESC1(HMONITOR hMonitor, DXGI_OUTPUT_DESC1 *desc)
{
    تعريفنوع HRESULT (WINAPI *pfnCreateDXGIFactory1)(REFIID riid, فراغ **ppFactory);
    pfnCreateDXGIFactory1 pCreateDXGIFactory1 = عدم;
    SDL_SharedObject *hDXGIMod = عدم;
    bool لبھیا = false;

    hDXGIMod = SDL_لدو_Object("dxgi.dll");
    إذا (hDXGIMod) {
        pCreateDXGIFactory1 = (pfnCreateDXGIFactory1)SDL_لدو_Function(hDXGIMod, "CreateDXGIFactory1");
    }
    إذا (pCreateDXGIFactory1) {
        ساكن ثابت GUID SDL_IID_IDXGIFactory1 = { 0x770aae78, 0xf26f, 0x4dba, { 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 } };
        ساكن ثابت GUID SDL_IID_IDXGIOutput6 = { 0x068346e8, 0xaaec, 0x4b84, { 0xad, 0xd7, 0x13, 0x7f, 0x51, 0x3f, 0x77, 0xa1 } };
        IDXGIFactory1 *dxgiFactory;

        إذا (SUCCEEDED(pCreateDXGIFactory1(&SDL_IID_IDXGIFactory1, (فراغ **)&dxgiFactory))) {
            IDXGIAdapter1 *dxgiAdapter;
            UINT adapter = 0;
            طالما (!لبھیا && SUCCEEDED(IDXGIFactory1_EnumAdapters1(dxgiFactory, adapter, &dxgiAdapter))) {
                IDXGIOutput *dxgiOutput;
                UINT output = 0;
                طالما (!لبھیا && SUCCEEDED(IDXGIAdapter1_EnumOutputs(dxgiAdapter, output, &dxgiOutput))) {
                    IDXGIOutput6 *dxgiOutput6;
                    إذا (SUCCEEDED(IDXGIOutput_QueryInterface(dxgiOutput, &SDL_IID_IDXGIOutput6, (فراغ **)&dxgiOutput6))) {
                        إذا (SUCCEEDED(IDXGIOutput6_GetDesc1(dxgiOutput6, desc))) {
                            إذا (desc->Monitor == hMonitor) {
                                لبھیا = true;
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
    أرجع لبھیا;
}

ساكن bool WIN_Get_Monitor_رستہ_Info(SDL_Video_انکڑے *videodata, HMONITOR hMonitor, DISPLAYCONFIG_رستہ_INFO *رستہ_info)
{
    LONG نتیجہ;
    MONITORINFOEXW view_info;
    UINT32 i;
    UINT32 عدد_رستہ_array_elements = 0;
    UINT32 عدد_منوال_info_array_elements = 0;
    DISPLAYCONFIG_رستہ_INFO *رستہ_infos = عدم, *new_رستہ_infos;
    DISPLAYCONFIG_منوال_INFO *منوال_infos = عدم, *new_منوال_infos;
    bool لبھیا = false;

    إذا (!videodata->Get_Display_Config_بفر_Sizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        أرجع false;
    }

    SDL_zero(view_info);
    view_info.cb_ناپ = حجم(view_info);
    إذا (!GetMonitorInfoW(hMonitor, (MONITORINFO *)&view_info)) {
        اذهب پورا;
    }

    افعل {
        إذا (videodata->Get_Display_Config_بفر_Sizes(QDC_ONLY_سرگرم_PATHS, &عدد_رستہ_array_elements, &عدد_منوال_info_array_elements) != ERROR_SUCCESS) {
            SDL_free(رستہ_infos);
            SDL_free(منوال_infos);
            أرجع false;
        }

        new_رستہ_infos = (DISPLAYCONFIG_رستہ_INFO *)SDL_realloc(رستہ_infos, عدد_رستہ_array_elements * حجم(*رستہ_infos));
        إذا (!new_رستہ_infos) {
            اذهب پورا;
        }
        رستہ_infos = new_رستہ_infos;

        new_منوال_infos = (DISPLAYCONFIG_منوال_INFO *)SDL_realloc(منوال_infos, عدد_منوال_info_array_elements * حجم(*منوال_infos));
        إذا (!new_منوال_infos) {
            اذهب پورا;
        }
        منوال_infos = new_منوال_infos;

        نتیجہ = videodata->QueryDisplayConfig(QDC_ONLY_سرگرم_PATHS, &عدد_رستہ_array_elements, رستہ_infos, &عدد_منوال_info_array_elements, منوال_infos, عدم);

    } طالما (نتیجہ == ERROR_INSUFFICIENT_بفر);

    إذا (نتیجہ == ERROR_SUCCESS) {
        لكل (i = 0; i < عدد_رستہ_array_elements; ++i) {
            DISPLAYCONFIG_سروت_DEVICE_NAME device_name;

            SDL_zero(device_name);
            device_name.سرخی.type = DISPLAYCONFIG_DEVICE_INFO_GET_سروت_NAME;
            device_name.سرخی.ناپ = حجم(device_name);
            device_name.سرخی.adapterId = رستہ_infos[i].سروت_Info.adapterId;
            device_name.سرخی.id = رستہ_infos[i].سروت_Info.id;
            إذا (videodata->DisplayConfigGetDeviceInfo(&device_name.سرخی) == ERROR_SUCCESS) {
                إذا (SDL_wcscmp(view_info.szDevice, device_name.viewGdiDeviceName) == 0) {
                    SDL_copyp(رستہ_info, &رستہ_infos[i]);
                    لبھیا = true;
                    اكسر;
                }
            }
        }
    }

پورا:
    SDL_free(رستہ_infos);
    SDL_free(منوال_infos);

    أرجع لبھیا;
}

ساكن عائم WIN_Get_SDRWhite_نقطہ(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    DISPLAYCONFIG_رستہ_INFO رستہ_info;
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    عائم SDR_white_level = 1.0f;

    إذا (WIN_Get_Monitor_رستہ_Info(videodata, hMonitor, &رستہ_info)) {
        /* workarounds for https://github.com/libsdl-org/SDL/issues/11193 */
        بنية SDL_DISPLAYCONFIG_SDR_WHITE_LEVEL {
          DISPLAYCONFIG_DEVICE_INFO_سرخی سرخی;
          ULONG SDRWhiteLevel;
        } white_level;
        #تعریف_کرو DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL 11

        SDL_zero(white_level);
        white_level.سرخی.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
        white_level.سرخی.ناپ = حجم(white_level);
        white_level.سرخی.adapterId = رستہ_info.نشانہ_Info.adapterId;
        white_level.سرخی.id = رستہ_info.نشانہ_Info.id;
        // WIN_GetMonitorPathInfo() succeeded: DisplayConfigGetDeviceInfo is not NULL
        إذا (videodata->DisplayConfigGetDeviceInfo(&white_level.سرخی) == ERROR_SUCCESS &&
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
        إذا (desc.ColorSpace == DXGI_COLOR_SPACE_RGB_بھریا_G2084_NONE_P2020) {
            HDR->SDR_white_level = WIN_Get_SDRWhite_نقطہ(_this, hMonitor);
            HDR->HDR_headroom = (desc.MaxLuminance / SCRGB_NITS) / HDR->SDR_white_level;
        }
    }
}
#جے_انت // HAVE_DXGI1_6_H

ساكن فراغ WIN_جوڑو_Display(SDL_VideoDevice *_this, HMONITOR hMonitor, ثابت MONITORINFOEXW *info, صحيح *display_اشاریہ)
{
    صحيح i, اشاریہ = *display_اشاریہ;
    SDL_VideoDisplay display;
    SDL_Display_انکڑے *displaydata;
    فراغ *dxgi_output = عدم;
    SDL_Display_منوال منوال;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    عائم content_scale = WIN_GetContentScale(_this, hMonitor);

#جے_تعریف_شدہ DEBUG_MODES
    SDL_Log("Display: %s", WIN_String_منزل_UTF8_W(info->szDevice));
#جے_انت

    dxgi_output = WIN_GetDXGIOutput(_this, info->szDevice);
    bool لبھیا = WIN_Get_Display_منوال(_this, dxgi_output, hMonitor, info->szDevice, ENUM_CURRENT_SETTINGS, &منوال, &natural_orientation, &current_orientation);
    WIN_ReleaseDXGIOutput(dxgi_output);
    إذا (!لبھیا) {
        أرجع;
    }

    // Prevent adding duplicate displays. Do this after we know the display is
    // ready to be added to allow any displays that we can't fully query to be
    // removed
    لكل (i = 0; i < _this->عدد_displays; ++i) {
        SDL_Display_انکڑے *اندرونی = _this->displays[i]->اندرونی;
        إذا (SDL_wcscmp(اندرونی->DeviceName, info->szDevice) == 0) {
            bool moved = (اشاریہ != i);
            bool بدلیا_bounds = false;

            إذا (اندرونی->state != DisplayRemoved) {
                // We've already enumerated this display, don't move it
                اذهب cleanup;
            }

            إذا (اشاریہ >= _this->عدد_displays) {
                // This should never happen due to the check above, but just in case...
                اذهب cleanup;
            }

            إذا (moved) {
                SDL_VideoDisplay *tmp;

                tmp = _this->displays[اشاریہ];
                _this->displays[اشاریہ] = _this->displays[i];
                _this->displays[i] = tmp;
                i = اشاریہ;
            }

            اندرونی->MonitorHandle = hMonitor;
            اندرونی->state = DisplayUnchanged;

            SDL_PropertiesID props = SDL_GetDisplayProperties(_this->displays[i]->id);
            SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_اشارہ_گر, hMonitor);

            إذا (!_this->setting_display_منوال) {
                SDL_VideoDisplay *existing_display = _this->displays[i];
                SDL_Rect bounds;

                SDL_ResetFullscreenDisplayModes(existing_display);
                SDL_سیٹ_Desktop_Display_منوال(existing_display, &منوال);
                // The mode is owned by the video subsystem
                منوال.اندرونی = عدم;
                إذا (WIN_GetDisplayBounds(_this, existing_display, &bounds) &&
                    SDL_memcmp(&اندرونی->bounds, &bounds, حجم(bounds)) != 0) {
                    بدلیا_bounds = true;
                    SDL_copyp(&اندرونی->bounds, &bounds);
                }
                إذا (moved || بدلیا_bounds) {
                    SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_MOVED, 0, 0);
                }
                SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_ORIENTATION, current_orientation, 0);
                SDL_سیٹ_Display_Content_Scale(existing_display, content_scale);
#جے_تعریف_شدہ HAVE_DXGI1_6_H
                SDL_HDROutputProperties HDR;
                WIN_GetHDRProperties(_this, hMonitor, &HDR);
                SDL_سیٹ_Display_HDRProperties(existing_display, &HDR);
#جے_انت
            }
            اذهب پورا;
        }
    }

    displaydata = (SDL_Display_انکڑے *)SDL_calloc(1, حجم(*displaydata));
    إذا (!displaydata) {
        اذهب cleanup;
    }
    SDL_memcpy(displaydata->DeviceName, info->szDevice, حجم(displaydata->DeviceName));
    displaydata->MonitorHandle = hMonitor;
    displaydata->state = DisplayAdded;

    SDL_zero(display);
    display.name = WIN_GetDisplayNameVista(_this->اندرونی, info->szDevice);
    إذا (!display.name) {
        DISPLAY_DEVICEW device;
        SDL_zero(device);
        device.cb = حجم(device);
        إذا (EnumDisplayDevicesW(info->szDevice, 0, &device, 0)) {
            display.name = WIN_String_منزل_UTF8_W(device.DeviceString);
        }
    }

    display.desktop_منوال = منوال;
    display.natural_orientation = natural_orientation;
    display.current_orientation = current_orientation;
    display.content_scale = content_scale;
    display.device = _this;
    display.اندرونی = displaydata;
    WIN_GetDisplayBounds(_this, &display, &displaydata->bounds);
#جے_تعریف_شدہ HAVE_DXGI1_6_H
    WIN_GetHDRProperties(_this, hMonitor, &display.HDR);
#جے_انت
    SDL_DisplayID displayID = SDL_جوڑو_Video_Display(&display, false);
    إذا (displayID) {
        // The mode is owned by the video subsystem
        منوال.اندرونی = عدم;

        SDL_PropertiesID props = SDL_GetDisplayProperties(displayID);
        SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_اشارہ_گر, hMonitor);
    } وإلا {
        SDL_free(displaydata);
    }
    SDL_free(display.name);

پورا:
    *display_اشاریہ += 1;

cleanup:
    SDL_free(منوال.اندرونی);
}

تعريفنوع بنية WIN_جوڑو_Displays_انکڑے
{
    SDL_VideoDevice *video_device;
    صحيح display_اشاریہ;
    bool want_primary;
} WIN_جوڑو_Displays_انکڑے_2;

ساكن BOOL CALLBACK WIN_جوڑو_Displays_Callback(HMONITOR hMonitor,
                                             HDC hdcMonitor,
                                             LPRECT lprcMonitor,
                                             LPARAM dw_انکڑے)
{
    WIN_جوڑو_Displays_انکڑے_2 *انکڑے = (WIN_جوڑو_Displays_انکڑے_2 *)dw_انکڑے;
    MONITORINFOEXW info;

    SDL_zero(info);
    info.cb_ناپ = حجم(info);

    إذا (GetMonitorInfoW(hMonitor, (LPMONITORINFO)&info) != 0) {
        ثابت bool is_primary = ((info.dwFlags & MONITORINFOF_PRIMARY) == MONITORINFOF_PRIMARY);

        إذا (is_primary == انکڑے->want_primary) {
            WIN_جوڑو_Display(انکڑے->video_device, hMonitor, &info, &انکڑے->display_اشاریہ);
        }
    }

    // continue enumeration
    أرجع TRUE;
}

ساكن فراغ WIN_جوڑو_Displays(SDL_VideoDevice *_this)
{
    WIN_جوڑو_Displays_انکڑے_2 callback_انکڑے;
    callback_انکڑے.video_device = _this;
    callback_انکڑے.display_اشاریہ = 0;

    callback_انکڑے.want_primary = true;
    EnumDisplayMonitors(عدم, عدم, WIN_جوڑو_Displays_Callback, (LPARAM)&callback_انکڑے);

    callback_انکڑے.want_primary = false;
    EnumDisplayMonitors(عدم, عدم, WIN_جوڑو_Displays_Callback, (LPARAM)&callback_انکڑے);
}

bool WIN_InitModes(SDL_VideoDevice *_this)
{
    WIN_جوڑو_Displays(_this);

    إذا (_this->عدد_displays == 0) {
        أرجع SDL_سیٹ_Error("No displays available");
    }
    أرجع true;
}

bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ثابت SDL_Display_انکڑے *انکڑے = display->اندرونی;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cb_ناپ = حجم(MONITORINFO);
    rc = GetMonitorInfo(انکڑے->MonitorHandle, &minfo);

    إذا (!rc) {
        أرجع SDL_سیٹ_Error("Couldn't find monitor data");
    }

    rect->x = minfo.rcMonitor.بایاں;
    rect->y = minfo.rcMonitor.چوٹی;
    rect->w = minfo.rcMonitor.دایاں - minfo.rcMonitor.بایاں;
    rect->h = minfo.rcMonitor.bottom - minfo.rcMonitor.چوٹی;

    أرجع true;
}

bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ثابت SDL_Display_انکڑے *انکڑے = display->اندرونی;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cb_ناپ = حجم(MONITORINFO);
    rc = GetMonitorInfo(انکڑے->MonitorHandle, &minfo);

    إذا (!rc) {
        أرجع SDL_سیٹ_Error("Couldn't find monitor data");
    }

    rect->x = minfo.rcWork.بایاں;
    rect->y = minfo.rcWork.چوٹی;
    rect->w = minfo.rcWork.دایاں - minfo.rcWork.بایاں;
    rect->h = minfo.rcWork.bottom - minfo.rcWork.چوٹی;

    أرجع true;
}

bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_انکڑے *انکڑے = display->اندرونی;
    فراغ *dxgi_output;
    DWORD i;
    SDL_Display_منوال منوال;

    dxgi_output = WIN_GetDXGIOutput(_this, انکڑے->DeviceName);

    // Make sure we add the current mode to the list in case it's a custom mode that doesn't enumerate
    لكل (i = ENUM_CURRENT_SETTINGS; ; ++i) {
        إذا (!WIN_Get_Display_منوال(_this, dxgi_output, انکڑے->MonitorHandle, انکڑے->DeviceName, i, &منوال, عدم, عدم)) {
            اكسر;
        }
        إذا (SDL_ISPIXELFORMAT_اشاریہ_دار(منوال.format)) {
            // We don't support palettized modes now
            SDL_free(منوال.اندرونی);
            استمر;
        }
        إذا (منوال.format != SDL_PIXELFORMAT_UNKNOWN) {
            إذا (!SDL_جوڑو_Fullscreen_Display_منوال(display, &منوال)) {
                SDL_free(منوال.اندرونی);
            }
        } وإلا {
            SDL_free(منوال.اندرونی);
        }
    }

    WIN_ReleaseDXGIOutput(dxgi_output);

    أرجع true;
}

#جے_تعریف_شدہ DEBUG_MODES
ساكن فراغ WIN_LogMonitor(SDL_VideoDevice *_this, HMONITOR mon)
{
    ثابت SDL_Video_انکڑے *vid_انکڑے = (ثابت SDL_Video_انکڑے *)_this->اندرونی;
    MONITORINFOEX minfo;
    UINT xdpi = 0, ydpi = 0;
    حرف *name_utf8;

    إذا (vid_انکڑے->GetDpiForMonitor) {
        vid_انکڑے->GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &xdpi, &ydpi);
    }

    SDL_zero(minfo);
    minfo.cb_ناپ = حجم(minfo);
    GetMonitorInfo(mon, (LPMONITORINFO)&minfo);

    name_utf8 = WIN_String_منزل_UTF8(minfo.szDevice);

    SDL_Log("WIN_LogMonitor: monitor \"%s\": dpi: %d windows screen coordinates: %d, %d, %dx%d",
            name_utf8,
            xdpi,
            minfo.rcMonitor.بایاں,
            minfo.rcMonitor.چوٹی,
            minfo.rcMonitor.دایاں - minfo.rcMonitor.بایاں,
            minfo.rcMonitor.bottom - minfo.rcMonitor.چوٹی);

    SDL_free(name_utf8);
}
#جے_انت

bool WIN_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال)
{
    SDL_Display_انکڑے *displaydata = display->اندرونی;
    SDL_Display_منوال_انکڑے *انکڑے = (SDL_Display_منوال_انکڑے *)منوال->اندرونی;
    LONG حالت;

#جے_تعریف_شدہ DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state before mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#جے_انت

    /* High-DPI notes:

       - ChangeDisplaySettingsEx always takes pixels.
       - e.g. if the display is set to 2880x1800 with 200% scaling in Display Settings
         - calling ChangeDisplaySettingsEx with a dmPelsWidth/Height other than 2880x1800 will
           change the monitor DPI to 96. (100% scaling)
         - calling ChangeDisplaySettingsEx with a dmPelsWidth/Height of 2880x1800 (or a NULL DEVMODE*) will
           reset the monitor DPI to 192. (200% scaling)

       NOTE: these are temporary changes in DPI, not modifications to the Control Panel setting. */
    إذا (منوال->اندرونی == display->desktop_منوال.اندرونی) {
#جے_تعریف_شدہ DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: resetting to original resolution");
#جے_انت
        حالت = ChangeDisplaySettingsExW(displaydata->DeviceName, عدم, عدم, CDS_FULLSCREEN, عدم);
    } وإلا {
#جے_تعریف_شدہ DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: changing to %dx%d pixels", انکڑے->Device_منوال.dm_Pels_چوڑائی, انکڑے->Device_منوال.dm_Pels_اچائی);
#جے_انت
        حالت = ChangeDisplaySettingsExW(displaydata->DeviceName, &انکڑے->Device_منوال, عدم, CDS_FULLSCREEN, عدم);
    }
    إذا (حالت != DISP_CHANGE_SUCCESSFUL) {
        ثابت حرف *reason = "Unknown reason";
        بدل (حالت) {
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
        أرجع SDL_سیٹ_Error("ChangeDisplaySettingsEx() failed: %s", reason);
    }

#جے_تعریف_شدہ DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state after mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#جے_انت

    EnumDisplaySettingsW(displaydata->DeviceName, ENUM_CURRENT_SETTINGS, &انکڑے->Device_منوال);
    WIN_Update_Display_منوال(_this, displaydata->DeviceName, ENUM_CURRENT_SETTINGS, منوال);
    أرجع true;
}

فراغ WIN_RefreshDisplays(SDL_VideoDevice *_this)
{
    صحيح i;

    // Mark all displays as potentially invalid to detect
    // entries that have actually been removed
    لكل (i = 0; i < _this->عدد_displays; ++i) {
        SDL_Display_انکڑے *اندرونی = _this->displays[i]->اندرونی;
        اندرونی->state = DisplayRemoved;
    }

    // Enumerate displays to add any new ones and mark still
    // connected entries as valid
    WIN_جوڑو_Displays(_this);

    // Delete any entries still marked as invalid, iterate
    // in reverse as each delete takes effect immediately
    لكل (i = _this->عدد_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_Display_انکڑے *اندرونی = display->اندرونی;
        إذا (اندرونی->state == DisplayRemoved) {
            SDL_DelVideoDisplay(display->id, true);
        }
    }

    // Send events for any newly added displays
    لكل (i = 0; i < _this->عدد_displays; ++i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_Display_انکڑے *اندرونی = display->اندرونی;
        إذا (اندرونی->state == DisplayAdded) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
        }
    }
}

فراغ WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this)
{
    // This almost never happens, so just go ahead and send update events for all displays
    لكل (صحيح i = 0; i < _this->عدد_displays; ++i) {
        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_بدلیا, 0, 0);
    }
}

فراغ WIN_QuitModes(SDL_VideoDevice *_this)
{
    // All fullscreen windows should have restored modes by now
}

#جے_انت // SDL_VIDEO_DRIVER_WINDOWS
