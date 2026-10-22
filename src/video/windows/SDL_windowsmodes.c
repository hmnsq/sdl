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

#که_تعریف_شوی HAVE_DXGI1_6_H
#تعریف_کړه COBJMACROS
#ضمن <dxgi1_6.h>
#د_که_پای

// Windows CE compatibility
#که_نه_تعریف_شوی CDS_FULLSCREEN
#تعریف_کړه CDS_FULLSCREEN 0
#د_که_پای
#که_نه_تعریف_شوی USER_DEFAULT_SCREEN_DPI
#تعریف_کړه USER_DEFAULT_SCREEN_DPI 96
#د_که_پای

// #define DEBUG_MODES
// #define HIGHDPI_DEBUG_VERBOSE

ساكن فراغ WIN_Update_Display_ډېرپېښ(SDL_VideoDevice *_this, LPCWSTR deviceName, DWORD شاخص, SDL_Display_ډېرپېښ *ډېرپېښ)
{
    SDL_Display_ډېرپېښ_معلومات *معلومات = (SDL_Display_ډېرپېښ_معلومات *)ډېرپېښ->دننی;
    HDC hdc;

    معلومات->Device_ډېرپېښ.dmFields = (DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS);

    // NOLINTNEXTLINE(bugprone-assignment-in-if-condition): No simple way to extract the assignment
    إذا (شاخص == ENUM_CURRENT_SETTINGS && (hdc = CreateDCW(deviceName, عدم, عدم, عدم)) != عدم) {
        حرف bmi_معلومات[حجم(BITMAPINFOHEADER) + 256 * حجم(RGBQUAD)];
        LPBITMAPINFO bmi;
        HBITMAP hbm;

        SDL_zeroa(bmi_معلومات);
        bmi = (LPBITMAPINFO)bmi_معلومات;
        bmi->bmi_سرلیک.bi_اندازه = حجم(BITMAPINFOHEADER);

        hbm = CreateCompatibleBitmap(hdc, 1, 1);
        GetDIBits(hdc, hbm, 0, 1, عدم, bmi, DIB_RGB_COLORS);
        GetDIBits(hdc, hbm, 0, 1, عدم, bmi, DIB_RGB_COLORS);
        DeleteObject(hbm);
        DeleteDC(hdc);
        إذا (bmi->bmi_سرلیک.biCompression == BI_BITFIELDS) {
            بدل (*(Uint32 *)bmi->bmiColors) {
            حالة 0x00FF0000:
                ډېرپېښ->format = SDL_PIXELFORMAT_XRGB8888;
                اكسر;
            حالة 0x000000FF:
                ډېرپېښ->format = SDL_PIXELFORMAT_XBGR8888;
                اكسر;
            حالة 0xF800:
                ډېرپېښ->format = SDL_PIXELFORMAT_RGB565;
                اكسر;
            حالة 0x7C00:
                ډېرپېښ->format = SDL_PIXELFORMAT_XRGB1555;
                اكسر;
            }
        } وإلا إذا (bmi->bmi_سرلیک.biCompression == BI_RGB) {
            إذا (bmi->bmi_سرلیک.bi_بټ_شمېر == 24) {
                ډېرپېښ->format = SDL_PIXELFORMAT_RGB24;
            } وإلا إذا (bmi->bmi_سرلیک.bi_بټ_شمېر == 8) {
                ډېرپېښ->format = SDL_PIXELFORMAT_INDEX8;
            } وإلا إذا (bmi->bmi_سرلیک.bi_بټ_شمېر == 4) {
                ډېرپېښ->format = SDL_PIXELFORMAT_INDEX4LSB;
            }
        }
    } وإلا إذا (ډېرپېښ->format == SDL_PIXELFORMAT_UNKNOWN) {
        // FIXME: Can we tell what this will be?
        إذا ((معلومات->Device_ډېرپېښ.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL) {
            بدل (معلومات->Device_ډېرپېښ.dm_بټونه_فی_Pel) {
            حالة 32:
                ډېرپېښ->format = SDL_PIXELFORMAT_XRGB8888;
                اكسر;
            حالة 24:
                ډېرپېښ->format = SDL_PIXELFORMAT_RGB24;
                اكسر;
            حالة 16:
                ډېرپېښ->format = SDL_PIXELFORMAT_RGB565;
                اكسر;
            حالة 15:
                ډېرپېښ->format = SDL_PIXELFORMAT_XRGB1555;
                اكسر;
            حالة 8:
                ډېرپېښ->format = SDL_PIXELFORMAT_INDEX8;
                اكسر;
            حالة 4:
                ډېرپېښ->format = SDL_PIXELFORMAT_INDEX4LSB;
                اكسر;
            }
        }
    }
}

ساكن فراغ *WIN_GetDXGIOutput(SDL_VideoDevice *_this, ثابت WCHAR *DeviceName)
{
    فراغ *پایله = عدم;

#که_تعریف_شوی HAVE_DXGI_H
    ثابت SDL_Video_معلومات *videodata = (ثابت SDL_Video_معلومات *)_this->دننی;
    صحيح nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    إذا (!videodata->pDXGIFactory) {
        أرجع عدم;
    }

    nAdapter = 0;
    طالما (!پایله && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        طالما (!پایله && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            إذا (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                إذا (SDL_wcscmp(outputDesc.DeviceName, DeviceName) == 0) {
                    پایله = pDXGIOutput;
                }
            }
            إذا (pDXGIOutput != پایله) {
                IDXGIOutput_Release(pDXGIOutput);
            }
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }
#د_که_پای
    أرجع پایله;
}

ساكن فراغ WIN_ReleaseDXGIOutput(فراغ *dxgi_output)
{
#که_تعریف_شوی HAVE_DXGI_H
    IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;

    إذا (pDXGIOutput) {
        IDXGIOutput_Release(pDXGIOutput);
    }
#د_که_پای
}

ساكن SDL_DisplayOrientation WIN_GetNaturalOrientation(DEVMODEW *ډېرپېښ)
{
    صحيح پلنوالی = ډېرپېښ->dm_Pels_پلنوالی;
    صحيح لوړوالی = ډېرپېښ->dm_Pels_لوړوالی;

    // Use unrotated width/height to guess orientation
    إذا (ډېرپېښ->dmDisplayOrientation == DMDO_90 || ډېرپېښ->dmDisplayOrientation == DMDO_270) {
        صحيح لنډمهاله = پلنوالی;
        پلنوالی = لوړوالی;
        لوړوالی = لنډمهاله;
    }

    إذا (پلنوالی >= لوړوالی) {
        أرجع SDL_ORIENTATION_LANDSCAPE;
    } وإلا {
        أرجع SDL_ORIENTATION_PORTRAIT;
    }
}

ساكن SDL_DisplayOrientation WIN_GetDisplayOrientation(DEVMODEW *ډېرپېښ)
{
    إذا (WIN_GetNaturalOrientation(ډېرپېښ) == SDL_ORIENTATION_LANDSCAPE) {
        بدل (ډېرپېښ->dmDisplayOrientation) {
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
        بدل (ډېرپېښ->dmDisplayOrientation) {
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

ساكن فراغ WIN_Get_Refresh_شرح(فراغ *dxgi_output, DEVMODEW *ډېرپېښ, صحيح *numerator, صحيح *denominator)
{
    // We're not currently using DXGI to query display modes, so fake NTSC timings
    بدل (ډېرپېښ->dmDisplayFrequency) {
    حالة 119:
    حالة 59:
    حالة 29:
        *numerator = (ډېرپېښ->dmDisplayFrequency + 1) * 1000;
        *denominator = 1001;
        اكسر;
    افتراضي:
        *numerator = ډېرپېښ->dmDisplayFrequency;
        *denominator = 1;
        اكسر;
    }

#که_تعریف_شوی HAVE_DXGI_H
    إذا (dxgi_output) {
        IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;
        DXGI_ډېرپېښ_DESC ډېرپېښ_منزل_سمون;
        DXGI_ډېرپېښ_DESC closest_سمون;

        SDL_zero(ډېرپېښ_منزل_سمون);
        ډېرپېښ_منزل_سمون.پلنوالی_2 = ډېرپېښ->dm_Pels_پلنوالی;
        ډېرپېښ_منزل_سمون.لوړوالی_2 = ډېرپېښ->dm_Pels_لوړوالی;
        ډېرپېښ_منزل_سمون.Refresh_شرح.Numerator = *numerator;
        ډېرپېښ_منزل_سمون.Refresh_شرح.Denominator = *denominator;
        ډېرپېښ_منزل_سمون.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        إذا (SUCCEEDED(IDXGIOutput_پیدا_کړه_Closest_Matching_ډېرپېښ(pDXGIOutput, &ډېرپېښ_منزل_سمون, &closest_سمون, عدم))) {
            *numerator = closest_سمون.Refresh_شرح.Numerator;
            *denominator = closest_سمون.Refresh_شرح.Denominator;
        }
    }
#د_که_پای // HAVE_DXGI_H
}

ساكن عائم WIN_GetContentScale(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    صحيح dpi = 0;

    ثابت SDL_Video_معلومات *videodata = (ثابت SDL_Video_معلومات *)_this->دننی;
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

ساكن bool WIN_Get_Display_ډېرپېښ(SDL_VideoDevice *_this, فراغ *dxgi_output, HMONITOR hMonitor, LPCWSTR deviceName, DWORD شاخص, SDL_Display_ډېرپېښ *ډېرپېښ, SDL_DisplayOrientation *natural_orientation, SDL_DisplayOrientation *current_orientation)
{
    SDL_Display_ډېرپېښ_معلومات *معلومات;
    DEVMODEW devmode;

    devmode.dm_اندازه = حجم(devmode);
    devmode.dmDriverExtra = 0;
    إذا (!EnumDisplaySettingsW(deviceName, شاخص, &devmode)) {
        أرجع false;
    }

    معلومات = (SDL_Display_ډېرپېښ_معلومات *)SDL_malloc(حجم(*معلومات));
    إذا (!معلومات) {
        أرجع false;
    }

    SDL_zerop(ډېرپېښ);
    ډېرپېښ->دننی = معلومات;
    معلومات->Device_ډېرپېښ = devmode;

    ډېرپېښ->format = SDL_PIXELFORMAT_UNKNOWN;
    ډېرپېښ->w = معلومات->Device_ډېرپېښ.dm_Pels_پلنوالی;
    ډېرپېښ->h = معلومات->Device_ډېرپېښ.dm_Pels_لوړوالی;
    WIN_Get_Refresh_شرح(dxgi_output, &معلومات->Device_ډېرپېښ, &ډېرپېښ->refresh_شرح_numerator, &ډېرپېښ->refresh_شرح_denominator);

    // Fill in the mode information
    WIN_Update_Display_ډېرپېښ(_this, deviceName, شاخص, ډېرپېښ);

    إذا (natural_orientation) {
        *natural_orientation = WIN_GetNaturalOrientation(&devmode);
    }
    إذا (current_orientation) {
        *current_orientation = WIN_GetDisplayOrientation(&devmode);
    }

    أرجع true;
}

ساكن حرف *WIN_GetDisplayNameVista(SDL_Video_معلومات *videodata, ثابت WCHAR *deviceName)
{
    DISPLAYCONFIG_لار_INFO *paths = عدم;
    DISPLAYCONFIG_ډېرپېښ_INFO *modes = عدم;
    حرف *پایله = عدم;
    UINT32 لار_شمېر_2 = 0;
    UINT32 ډېرپېښ_شمېر_2 = 0;
    UINT32 i;
    LONG rc;

    إذا (!videodata->Get_Display_Config_بفر_Sizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        أرجع عدم;
    }

    افعل {
        rc = videodata->Get_Display_Config_بفر_Sizes(QDC_ONLY_فعال_PATHS, &لار_شمېر_2, &ډېرپېښ_شمېر_2);
        إذا (rc != ERROR_SUCCESS) {
            اذهب WIN_GetDisplayNameVista_failed;
        }

        SDL_free(paths);
        SDL_free(modes);

        paths = (DISPLAYCONFIG_لار_INFO *)SDL_malloc(حجم(DISPLAYCONFIG_لار_INFO) * لار_شمېر_2);
        modes = (DISPLAYCONFIG_ډېرپېښ_INFO *)SDL_malloc(حجم(DISPLAYCONFIG_ډېرپېښ_INFO) * ډېرپېښ_شمېر_2);
        إذا ((!paths) || (!modes)) {
            اذهب WIN_GetDisplayNameVista_failed;
        }

        rc = videodata->QueryDisplayConfig(QDC_ONLY_فعال_PATHS, &لار_شمېر_2, paths, &ډېرپېښ_شمېر_2, modes, 0);
    } طالما (rc == ERROR_INSUFFICIENT_بفر);

    إذا (rc == ERROR_SUCCESS) {
        لكل (i = 0; i < لار_شمېر_2; i++) {
            DISPLAYCONFIG_سرچینه_DEVICE_NAME سرچینه_Name;
            DISPLAYCONFIG_موخه_DEVICE_NAME موخه_Name;

            SDL_zero(سرچینه_Name);
            سرچینه_Name.سرلیک.adapterId = paths[i].موخه_Info.adapterId;
            سرچینه_Name.سرلیک.type = DISPLAYCONFIG_DEVICE_INFO_GET_سرچینه_NAME;
            سرچینه_Name.سرلیک.اندازه = حجم(سرچینه_Name);
            سرچینه_Name.سرلیک.id = paths[i].سرچینه_Info.id;
            rc = videodata->DisplayConfigGetDeviceInfo(&سرچینه_Name.سرلیک);
            إذا (rc != ERROR_SUCCESS) {
                اكسر;
            } وإلا إذا (SDL_wcscmp(deviceName, سرچینه_Name.viewGdiDeviceName) != 0) {
                استمر;
            }

            SDL_zero(موخه_Name);
            موخه_Name.سرلیک.adapterId = paths[i].موخه_Info.adapterId;
            موخه_Name.سرلیک.id = paths[i].موخه_Info.id;
            موخه_Name.سرلیک.type = DISPLAYCONFIG_DEVICE_INFO_GET_موخه_NAME;
            موخه_Name.سرلیک.اندازه = حجم(موخه_Name);
            rc = videodata->DisplayConfigGetDeviceInfo(&موخه_Name.سرلیک);
            إذا (rc == ERROR_SUCCESS) {
                پایله = WIN_String_منزل_UTF8_W(موخه_Name.monitorFriendlyDeviceName);
                /* if we got an empty string, treat it as failure so we'll fallback
                   to getting the generic name. */
                إذا (پایله && (*پایله == '\0')) {
                    SDL_free(پایله);
                    پایله = عدم;
                }
            }
            اكسر;
        }
    }

    SDL_free(paths);
    SDL_free(modes);
    أرجع پایله;

WIN_GetDisplayNameVista_failed:
    SDL_free(پایله);
    SDL_free(paths);
    SDL_free(modes);
    أرجع عدم;
}

#که_تعریف_شوی HAVE_DXGI1_6_H
ساكن bool WIN_GetMonitorDESC1(HMONITOR hMonitor, DXGI_OUTPUT_DESC1 *desc)
{
    تعريفنوع HRESULT (WINAPI *pfnCreateDXGIFactory1)(REFIID riid, فراغ **ppFactory);
    pfnCreateDXGIFactory1 pCreateDXGIFactory1 = عدم;
    SDL_SharedObject *hDXGIMod = عدم;
    bool وموندل = false;

    hDXGIMod = SDL_بارول_Object("dxgi.dll");
    إذا (hDXGIMod) {
        pCreateDXGIFactory1 = (pfnCreateDXGIFactory1)SDL_بارول_Function(hDXGIMod, "CreateDXGIFactory1");
    }
    إذا (pCreateDXGIFactory1) {
        ساكن ثابت GUID SDL_IID_IDXGIFactory1 = { 0x770aae78, 0xf26f, 0x4dba, { 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 } };
        ساكن ثابت GUID SDL_IID_IDXGIOutput6 = { 0x068346e8, 0xaaec, 0x4b84, { 0xad, 0xd7, 0x13, 0x7f, 0x51, 0x3f, 0x77, 0xa1 } };
        IDXGIFactory1 *dxgiFactory;

        إذا (SUCCEEDED(pCreateDXGIFactory1(&SDL_IID_IDXGIFactory1, (فراغ **)&dxgiFactory))) {
            IDXGIAdapter1 *dxgiAdapter;
            UINT adapter = 0;
            طالما (!وموندل && SUCCEEDED(IDXGIFactory1_EnumAdapters1(dxgiFactory, adapter, &dxgiAdapter))) {
                IDXGIOutput *dxgiOutput;
                UINT output = 0;
                طالما (!وموندل && SUCCEEDED(IDXGIAdapter1_EnumOutputs(dxgiAdapter, output, &dxgiOutput))) {
                    IDXGIOutput6 *dxgiOutput6;
                    إذا (SUCCEEDED(IDXGIOutput_QueryInterface(dxgiOutput, &SDL_IID_IDXGIOutput6, (فراغ **)&dxgiOutput6))) {
                        إذا (SUCCEEDED(IDXGIOutput6_GetDesc1(dxgiOutput6, desc))) {
                            إذا (desc->Monitor == hMonitor) {
                                وموندل = true;
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
    أرجع وموندل;
}

ساكن bool WIN_Get_Monitor_لار_Info(SDL_Video_معلومات *videodata, HMONITOR hMonitor, DISPLAYCONFIG_لار_INFO *لار_info)
{
    LONG پایله;
    MONITORINFOEXW view_info;
    UINT32 i;
    UINT32 عدد_لار_array_elements = 0;
    UINT32 عدد_ډېرپېښ_info_array_elements = 0;
    DISPLAYCONFIG_لار_INFO *لار_infos = عدم, *new_لار_infos;
    DISPLAYCONFIG_ډېرپېښ_INFO *ډېرپېښ_infos = عدم, *new_ډېرپېښ_infos;
    bool وموندل = false;

    إذا (!videodata->Get_Display_Config_بفر_Sizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        أرجع false;
    }

    SDL_zero(view_info);
    view_info.cb_اندازه = حجم(view_info);
    إذا (!GetMonitorInfoW(hMonitor, (MONITORINFO *)&view_info)) {
        اذهب بشپړ;
    }

    افعل {
        إذا (videodata->Get_Display_Config_بفر_Sizes(QDC_ONLY_فعال_PATHS, &عدد_لار_array_elements, &عدد_ډېرپېښ_info_array_elements) != ERROR_SUCCESS) {
            SDL_free(لار_infos);
            SDL_free(ډېرپېښ_infos);
            أرجع false;
        }

        new_لار_infos = (DISPLAYCONFIG_لار_INFO *)SDL_realloc(لار_infos, عدد_لار_array_elements * حجم(*لار_infos));
        إذا (!new_لار_infos) {
            اذهب بشپړ;
        }
        لار_infos = new_لار_infos;

        new_ډېرپېښ_infos = (DISPLAYCONFIG_ډېرپېښ_INFO *)SDL_realloc(ډېرپېښ_infos, عدد_ډېرپېښ_info_array_elements * حجم(*ډېرپېښ_infos));
        إذا (!new_ډېرپېښ_infos) {
            اذهب بشپړ;
        }
        ډېرپېښ_infos = new_ډېرپېښ_infos;

        پایله = videodata->QueryDisplayConfig(QDC_ONLY_فعال_PATHS, &عدد_لار_array_elements, لار_infos, &عدد_ډېرپېښ_info_array_elements, ډېرپېښ_infos, عدم);

    } طالما (پایله == ERROR_INSUFFICIENT_بفر);

    إذا (پایله == ERROR_SUCCESS) {
        لكل (i = 0; i < عدد_لار_array_elements; ++i) {
            DISPLAYCONFIG_سرچینه_DEVICE_NAME device_name;

            SDL_zero(device_name);
            device_name.سرلیک.type = DISPLAYCONFIG_DEVICE_INFO_GET_سرچینه_NAME;
            device_name.سرلیک.اندازه = حجم(device_name);
            device_name.سرلیک.adapterId = لار_infos[i].سرچینه_Info.adapterId;
            device_name.سرلیک.id = لار_infos[i].سرچینه_Info.id;
            إذا (videodata->DisplayConfigGetDeviceInfo(&device_name.سرلیک) == ERROR_SUCCESS) {
                إذا (SDL_wcscmp(view_info.szDevice, device_name.viewGdiDeviceName) == 0) {
                    SDL_copyp(لار_info, &لار_infos[i]);
                    وموندل = true;
                    اكسر;
                }
            }
        }
    }

بشپړ:
    SDL_free(لار_infos);
    SDL_free(ډېرپېښ_infos);

    أرجع وموندل;
}

ساكن عائم WIN_Get_SDRWhite_ټکی(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    DISPLAYCONFIG_لار_INFO لار_info;
    SDL_Video_معلومات *videodata = _this->دننی;
    عائم SDR_white_level = 1.0f;

    إذا (WIN_Get_Monitor_لار_Info(videodata, hMonitor, &لار_info)) {
        /* workarounds for https://github.com/libsdl-org/SDL/issues/11193 */
        بنية SDL_DISPLAYCONFIG_SDR_WHITE_LEVEL {
          DISPLAYCONFIG_DEVICE_INFO_سرلیک سرلیک;
          ULONG SDRWhiteLevel;
        } white_level;
        #تعریف_کړه DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL 11

        SDL_zero(white_level);
        white_level.سرلیک.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
        white_level.سرلیک.اندازه = حجم(white_level);
        white_level.سرلیک.adapterId = لار_info.موخه_Info.adapterId;
        white_level.سرلیک.id = لار_info.موخه_Info.id;
        // WIN_GetMonitorPathInfo() succeeded: DisplayConfigGetDeviceInfo is not NULL
        إذا (videodata->DisplayConfigGetDeviceInfo(&white_level.سرلیک) == ERROR_SUCCESS &&
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
        إذا (desc.ColorSpace == DXGI_COLOR_SPACE_RGB_ډک_G2084_NONE_P2020) {
            HDR->SDR_white_level = WIN_Get_SDRWhite_ټکی(_this, hMonitor);
            HDR->HDR_headroom = (desc.MaxLuminance / SCRGB_NITS) / HDR->SDR_white_level;
        }
    }
}
#د_که_پای // HAVE_DXGI1_6_H

ساكن فراغ WIN_جمع_کړه_Display(SDL_VideoDevice *_this, HMONITOR hMonitor, ثابت MONITORINFOEXW *info, صحيح *display_شاخص)
{
    صحيح i, شاخص = *display_شاخص;
    SDL_VideoDisplay display;
    SDL_Display_معلومات *displaydata;
    فراغ *dxgi_output = عدم;
    SDL_Display_ډېرپېښ ډېرپېښ;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    عائم content_scale = WIN_GetContentScale(_this, hMonitor);

#که_تعریف_شوی DEBUG_MODES
    SDL_Log("Display: %s", WIN_String_منزل_UTF8_W(info->szDevice));
#د_که_پای

    dxgi_output = WIN_GetDXGIOutput(_this, info->szDevice);
    bool وموندل = WIN_Get_Display_ډېرپېښ(_this, dxgi_output, hMonitor, info->szDevice, ENUM_CURRENT_SETTINGS, &ډېرپېښ, &natural_orientation, &current_orientation);
    WIN_ReleaseDXGIOutput(dxgi_output);
    إذا (!وموندل) {
        أرجع;
    }

    // Prevent adding duplicate displays. Do this after we know the display is
    // ready to be added to allow any displays that we can't fully query to be
    // removed
    لكل (i = 0; i < _this->عدد_displays; ++i) {
        SDL_Display_معلومات *دننی = _this->displays[i]->دننی;
        إذا (SDL_wcscmp(دننی->DeviceName, info->szDevice) == 0) {
            bool moved = (شاخص != i);
            bool بدل_شوی_bounds = false;

            إذا (دننی->state != DisplayRemoved) {
                // We've already enumerated this display, don't move it
                اذهب cleanup;
            }

            إذا (شاخص >= _this->عدد_displays) {
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

            دننی->MonitorHandle = hMonitor;
            دننی->state = DisplayUnchanged;

            SDL_PropertiesID props = SDL_GetDisplayProperties(_this->displays[i]->id);
            SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_اشاره_ګر, hMonitor);

            إذا (!_this->setting_display_ډېرپېښ) {
                SDL_VideoDisplay *existing_display = _this->displays[i];
                SDL_Rect bounds;

                SDL_ResetFullscreenDisplayModes(existing_display);
                SDL_سېټ_Desktop_Display_ډېرپېښ(existing_display, &ډېرپېښ);
                // The mode is owned by the video subsystem
                ډېرپېښ.دننی = عدم;
                إذا (WIN_GetDisplayBounds(_this, existing_display, &bounds) &&
                    SDL_memcmp(&دننی->bounds, &bounds, حجم(bounds)) != 0) {
                    بدل_شوی_bounds = true;
                    SDL_copyp(&دننی->bounds, &bounds);
                }
                إذا (moved || بدل_شوی_bounds) {
                    SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_MOVED, 0, 0);
                }
                SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_ORIENTATION, current_orientation, 0);
                SDL_سېټ_Display_Content_Scale(existing_display, content_scale);
#که_تعریف_شوی HAVE_DXGI1_6_H
                SDL_HDROutputProperties HDR;
                WIN_GetHDRProperties(_this, hMonitor, &HDR);
                SDL_سېټ_Display_HDRProperties(existing_display, &HDR);
#د_که_پای
            }
            اذهب بشپړ;
        }
    }

    displaydata = (SDL_Display_معلومات *)SDL_calloc(1, حجم(*displaydata));
    إذا (!displaydata) {
        اذهب cleanup;
    }
    SDL_memcpy(displaydata->DeviceName, info->szDevice, حجم(displaydata->DeviceName));
    displaydata->MonitorHandle = hMonitor;
    displaydata->state = DisplayAdded;

    SDL_zero(display);
    display.name = WIN_GetDisplayNameVista(_this->دننی, info->szDevice);
    إذا (!display.name) {
        DISPLAY_DEVICEW device;
        SDL_zero(device);
        device.cb = حجم(device);
        إذا (EnumDisplayDevicesW(info->szDevice, 0, &device, 0)) {
            display.name = WIN_String_منزل_UTF8_W(device.DeviceString);
        }
    }

    display.desktop_ډېرپېښ = ډېرپېښ;
    display.natural_orientation = natural_orientation;
    display.current_orientation = current_orientation;
    display.content_scale = content_scale;
    display.device = _this;
    display.دننی = displaydata;
    WIN_GetDisplayBounds(_this, &display, &displaydata->bounds);
#که_تعریف_شوی HAVE_DXGI1_6_H
    WIN_GetHDRProperties(_this, hMonitor, &display.HDR);
#د_که_پای
    SDL_DisplayID displayID = SDL_جمع_کړه_Video_Display(&display, false);
    إذا (displayID) {
        // The mode is owned by the video subsystem
        ډېرپېښ.دننی = عدم;

        SDL_PropertiesID props = SDL_GetDisplayProperties(displayID);
        SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_اشاره_ګر, hMonitor);
    } وإلا {
        SDL_free(displaydata);
    }
    SDL_free(display.name);

بشپړ:
    *display_شاخص += 1;

cleanup:
    SDL_free(ډېرپېښ.دننی);
}

تعريفنوع بنية WIN_جمع_کړه_Displays_معلومات
{
    SDL_VideoDevice *video_device;
    صحيح display_شاخص;
    bool want_primary;
} WIN_جمع_کړه_Displays_معلومات_2;

ساكن BOOL CALLBACK WIN_جمع_کړه_Displays_Callback(HMONITOR hMonitor,
                                             HDC hdcMonitor,
                                             LPRECT lprcMonitor,
                                             LPARAM dw_معلومات)
{
    WIN_جمع_کړه_Displays_معلومات_2 *معلومات = (WIN_جمع_کړه_Displays_معلومات_2 *)dw_معلومات;
    MONITORINFOEXW info;

    SDL_zero(info);
    info.cb_اندازه = حجم(info);

    إذا (GetMonitorInfoW(hMonitor, (LPMONITORINFO)&info) != 0) {
        ثابت bool is_primary = ((info.dwFlags & MONITORINFOF_PRIMARY) == MONITORINFOF_PRIMARY);

        إذا (is_primary == معلومات->want_primary) {
            WIN_جمع_کړه_Display(معلومات->video_device, hMonitor, &info, &معلومات->display_شاخص);
        }
    }

    // continue enumeration
    أرجع TRUE;
}

ساكن فراغ WIN_جمع_کړه_Displays(SDL_VideoDevice *_this)
{
    WIN_جمع_کړه_Displays_معلومات_2 callback_معلومات;
    callback_معلومات.video_device = _this;
    callback_معلومات.display_شاخص = 0;

    callback_معلومات.want_primary = true;
    EnumDisplayMonitors(عدم, عدم, WIN_جمع_کړه_Displays_Callback, (LPARAM)&callback_معلومات);

    callback_معلومات.want_primary = false;
    EnumDisplayMonitors(عدم, عدم, WIN_جمع_کړه_Displays_Callback, (LPARAM)&callback_معلومات);
}

bool WIN_InitModes(SDL_VideoDevice *_this)
{
    WIN_جمع_کړه_Displays(_this);

    إذا (_this->عدد_displays == 0) {
        أرجع SDL_سېټ_Error("No displays available");
    }
    أرجع true;
}

bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ثابت SDL_Display_معلومات *معلومات = display->دننی;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cb_اندازه = حجم(MONITORINFO);
    rc = GetMonitorInfo(معلومات->MonitorHandle, &minfo);

    إذا (!rc) {
        أرجع SDL_سېټ_Error("Couldn't find monitor data");
    }

    rect->x = minfo.rcMonitor.کیڼ;
    rect->y = minfo.rcMonitor.سر;
    rect->w = minfo.rcMonitor.ښی - minfo.rcMonitor.کیڼ;
    rect->h = minfo.rcMonitor.bottom - minfo.rcMonitor.سر;

    أرجع true;
}

bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ثابت SDL_Display_معلومات *معلومات = display->دننی;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cb_اندازه = حجم(MONITORINFO);
    rc = GetMonitorInfo(معلومات->MonitorHandle, &minfo);

    إذا (!rc) {
        أرجع SDL_سېټ_Error("Couldn't find monitor data");
    }

    rect->x = minfo.rcWork.کیڼ;
    rect->y = minfo.rcWork.سر;
    rect->w = minfo.rcWork.ښی - minfo.rcWork.کیڼ;
    rect->h = minfo.rcWork.bottom - minfo.rcWork.سر;

    أرجع true;
}

bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_معلومات *معلومات = display->دننی;
    فراغ *dxgi_output;
    DWORD i;
    SDL_Display_ډېرپېښ ډېرپېښ;

    dxgi_output = WIN_GetDXGIOutput(_this, معلومات->DeviceName);

    // Make sure we add the current mode to the list in case it's a custom mode that doesn't enumerate
    لكل (i = ENUM_CURRENT_SETTINGS; ; ++i) {
        إذا (!WIN_Get_Display_ډېرپېښ(_this, dxgi_output, معلومات->MonitorHandle, معلومات->DeviceName, i, &ډېرپېښ, عدم, عدم)) {
            اكسر;
        }
        إذا (SDL_ISPIXELFORMAT_شاخصي(ډېرپېښ.format)) {
            // We don't support palettized modes now
            SDL_free(ډېرپېښ.دننی);
            استمر;
        }
        إذا (ډېرپېښ.format != SDL_PIXELFORMAT_UNKNOWN) {
            إذا (!SDL_جمع_کړه_Fullscreen_Display_ډېرپېښ(display, &ډېرپېښ)) {
                SDL_free(ډېرپېښ.دننی);
            }
        } وإلا {
            SDL_free(ډېرپېښ.دننی);
        }
    }

    WIN_ReleaseDXGIOutput(dxgi_output);

    أرجع true;
}

#که_تعریف_شوی DEBUG_MODES
ساكن فراغ WIN_LogMonitor(SDL_VideoDevice *_this, HMONITOR mon)
{
    ثابت SDL_Video_معلومات *vid_معلومات = (ثابت SDL_Video_معلومات *)_this->دننی;
    MONITORINFOEX minfo;
    UINT xdpi = 0, ydpi = 0;
    حرف *name_utf8;

    إذا (vid_معلومات->GetDpiForMonitor) {
        vid_معلومات->GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &xdpi, &ydpi);
    }

    SDL_zero(minfo);
    minfo.cb_اندازه = حجم(minfo);
    GetMonitorInfo(mon, (LPMONITORINFO)&minfo);

    name_utf8 = WIN_String_منزل_UTF8(minfo.szDevice);

    SDL_Log("WIN_LogMonitor: monitor \"%s\": dpi: %d windows screen coordinates: %d, %d, %dx%d",
            name_utf8,
            xdpi,
            minfo.rcMonitor.کیڼ,
            minfo.rcMonitor.سر,
            minfo.rcMonitor.ښی - minfo.rcMonitor.کیڼ,
            minfo.rcMonitor.bottom - minfo.rcMonitor.سر);

    SDL_free(name_utf8);
}
#د_که_پای

bool WIN_سېټ_Display_ډېرپېښ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ډېرپېښ *ډېرپېښ)
{
    SDL_Display_معلومات *displaydata = display->دننی;
    SDL_Display_ډېرپېښ_معلومات *معلومات = (SDL_Display_ډېرپېښ_معلومات *)ډېرپېښ->دننی;
    LONG حالت;

#که_تعریف_شوی DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state before mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#د_که_پای

    /* High-DPI notes:

       - ChangeDisplaySettingsEx always takes pixels.
       - e.g. if the display is set to 2880x1800 with 200% scaling in Display Settings
         - calling ChangeDisplaySettingsEx with a dmPelsWidth/Height other than 2880x1800 will
           change the monitor DPI to 96. (100% scaling)
         - calling ChangeDisplaySettingsEx with a dmPelsWidth/Height of 2880x1800 (or a NULL DEVMODE*) will
           reset the monitor DPI to 192. (200% scaling)

       NOTE: these are temporary changes in DPI, not modifications to the Control Panel setting. */
    إذا (ډېرپېښ->دننی == display->desktop_ډېرپېښ.دننی) {
#که_تعریف_شوی DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: resetting to original resolution");
#د_که_پای
        حالت = ChangeDisplaySettingsExW(displaydata->DeviceName, عدم, عدم, CDS_FULLSCREEN, عدم);
    } وإلا {
#که_تعریف_شوی DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: changing to %dx%d pixels", معلومات->Device_ډېرپېښ.dm_Pels_پلنوالی, معلومات->Device_ډېرپېښ.dm_Pels_لوړوالی);
#د_که_پای
        حالت = ChangeDisplaySettingsExW(displaydata->DeviceName, &معلومات->Device_ډېرپېښ, عدم, CDS_FULLSCREEN, عدم);
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
        أرجع SDL_سېټ_Error("ChangeDisplaySettingsEx() failed: %s", reason);
    }

#که_تعریف_شوی DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state after mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#د_که_پای

    EnumDisplaySettingsW(displaydata->DeviceName, ENUM_CURRENT_SETTINGS, &معلومات->Device_ډېرپېښ);
    WIN_Update_Display_ډېرپېښ(_this, displaydata->DeviceName, ENUM_CURRENT_SETTINGS, ډېرپېښ);
    أرجع true;
}

فراغ WIN_RefreshDisplays(SDL_VideoDevice *_this)
{
    صحيح i;

    // Mark all displays as potentially invalid to detect
    // entries that have actually been removed
    لكل (i = 0; i < _this->عدد_displays; ++i) {
        SDL_Display_معلومات *دننی = _this->displays[i]->دننی;
        دننی->state = DisplayRemoved;
    }

    // Enumerate displays to add any new ones and mark still
    // connected entries as valid
    WIN_جمع_کړه_Displays(_this);

    // Delete any entries still marked as invalid, iterate
    // in reverse as each delete takes effect immediately
    لكل (i = _this->عدد_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_Display_معلومات *دننی = display->دننی;
        إذا (دننی->state == DisplayRemoved) {
            SDL_DelVideoDisplay(display->id, true);
        }
    }

    // Send events for any newly added displays
    لكل (i = 0; i < _this->عدد_displays; ++i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_Display_معلومات *دننی = display->دننی;
        إذا (دننی->state == DisplayAdded) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
        }
    }
}

فراغ WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this)
{
    // This almost never happens, so just go ahead and send update events for all displays
    لكل (صحيح i = 0; i < _this->عدد_displays; ++i) {
        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_بدل_شوی, 0, 0);
    }
}

فراغ WIN_QuitModes(SDL_VideoDevice *_this)
{
    // All fullscreen windows should have restored modes by now
}

#د_که_پای // SDL_VIDEO_DRIVER_WINDOWS
