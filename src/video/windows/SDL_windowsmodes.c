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

#جيڪڏهن_وصف_ٿيل HAVE_DXGI1_6_H
#وصف_ڪريو COBJMACROS
#ضمن <dxgi1_6.h>
#جيڪڏهن_پورو

// Windows CE compatibility
#جيڪڏهن_وصف_نه_ٿيل CDS_FULLSCREEN
#وصف_ڪريو CDS_FULLSCREEN 0
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل USER_DEFAULT_SCREEN_DPI
#وصف_ڪريو USER_DEFAULT_SCREEN_DPI 96
#جيڪڏهن_پورو

// #define DEBUG_MODES
// #define HIGHDPI_DEBUG_VERBOSE

ساكن فراغ WIN_Update_Display_گهڻائي(SDL_VideoDevice *_this, LPCWSTR deviceName, DWORD اشاريو, SDL_Display_گهڻائي *گهڻائي)
{
    SDL_Display_گهڻائي_معلومات *معلومات = (SDL_Display_گهڻائي_معلومات *)گهڻائي->اندروني;
    HDC hdc;

    معلومات->Device_گهڻائي.dmFields = (DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS);

    // NOLINTNEXTLINE(bugprone-assignment-in-if-condition): No simple way to extract the assignment
    إذا (اشاريو == ENUM_CURRENT_SETTINGS && (hdc = CreateDCW(deviceName, عدم, عدم, عدم)) != عدم) {
        حرف bmi_معلومات[حجم(BITMAPINFOHEADER) + 256 * حجم(RGBQUAD)];
        LPBITMAPINFO bmi;
        HBITMAP hbm;

        SDL_zeroa(bmi_معلومات);
        bmi = (LPBITMAPINFO)bmi_معلومات;
        bmi->bmi_سرو.bi_سائيز = حجم(BITMAPINFOHEADER);

        hbm = CreateCompatibleBitmap(hdc, 1, 1);
        GetDIBits(hdc, hbm, 0, 1, عدم, bmi, DIB_RGB_COLORS);
        GetDIBits(hdc, hbm, 0, 1, عدم, bmi, DIB_RGB_COLORS);
        DeleteObject(hbm);
        DeleteDC(hdc);
        إذا (bmi->bmi_سرو.biCompression == BI_BITFIELDS) {
            بدل (*(Uint32 *)bmi->bmiColors) {
            حالة 0x00FF0000:
                گهڻائي->format = SDL_PIXELFORMAT_XRGB8888;
                اكسر;
            حالة 0x000000FF:
                گهڻائي->format = SDL_PIXELFORMAT_XBGR8888;
                اكسر;
            حالة 0xF800:
                گهڻائي->format = SDL_PIXELFORMAT_RGB565;
                اكسر;
            حالة 0x7C00:
                گهڻائي->format = SDL_PIXELFORMAT_XRGB1555;
                اكسر;
            }
        } وإلا إذا (bmi->bmi_سرو.biCompression == BI_RGB) {
            إذا (bmi->bmi_سرو.bi_ٻٽو_انگ_ڳڻپ == 24) {
                گهڻائي->format = SDL_PIXELFORMAT_RGB24;
            } وإلا إذا (bmi->bmi_سرو.bi_ٻٽو_انگ_ڳڻپ == 8) {
                گهڻائي->format = SDL_PIXELFORMAT_INDEX8;
            } وإلا إذا (bmi->bmi_سرو.bi_ٻٽو_انگ_ڳڻپ == 4) {
                گهڻائي->format = SDL_PIXELFORMAT_INDEX4LSB;
            }
        }
    } وإلا إذا (گهڻائي->format == SDL_PIXELFORMAT_UNKNOWN) {
        // FIXME: Can we tell what this will be?
        إذا ((معلومات->Device_گهڻائي.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL) {
            بدل (معلومات->Device_گهڻائي.dm_بٽ_في_Pel) {
            حالة 32:
                گهڻائي->format = SDL_PIXELFORMAT_XRGB8888;
                اكسر;
            حالة 24:
                گهڻائي->format = SDL_PIXELFORMAT_RGB24;
                اكسر;
            حالة 16:
                گهڻائي->format = SDL_PIXELFORMAT_RGB565;
                اكسر;
            حالة 15:
                گهڻائي->format = SDL_PIXELFORMAT_XRGB1555;
                اكسر;
            حالة 8:
                گهڻائي->format = SDL_PIXELFORMAT_INDEX8;
                اكسر;
            حالة 4:
                گهڻائي->format = SDL_PIXELFORMAT_INDEX4LSB;
                اكسر;
            }
        }
    }
}

ساكن فراغ *WIN_GetDXGIOutput(SDL_VideoDevice *_this, ثابت WCHAR *DeviceName)
{
    فراغ *نتيجو = عدم;

#جيڪڏهن_وصف_ٿيل HAVE_DXGI_H
    ثابت SDL_Video_معلومات *videodata = (ثابت SDL_Video_معلومات *)_this->اندروني;
    صحيح nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    إذا (!videodata->pDXGIFactory) {
        أرجع عدم;
    }

    nAdapter = 0;
    طالما (!نتيجو && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        طالما (!نتيجو && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            إذا (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                إذا (SDL_wcscmp(outputDesc.DeviceName, DeviceName) == 0) {
                    نتيجو = pDXGIOutput;
                }
            }
            إذا (pDXGIOutput != نتيجو) {
                IDXGIOutput_Release(pDXGIOutput);
            }
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }
#جيڪڏهن_پورو
    أرجع نتيجو;
}

ساكن فراغ WIN_ReleaseDXGIOutput(فراغ *dxgi_output)
{
#جيڪڏهن_وصف_ٿيل HAVE_DXGI_H
    IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;

    إذا (pDXGIOutput) {
        IDXGIOutput_Release(pDXGIOutput);
    }
#جيڪڏهن_پورو
}

ساكن SDL_DisplayOrientation WIN_GetNaturalOrientation(DEVMODEW *گهڻائي)
{
    صحيح ويڪر = گهڻائي->dm_Pels_ويڪر;
    صحيح اوچائي = گهڻائي->dm_Pels_اوچائي;

    // Use unrotated width/height to guess orientation
    إذا (گهڻائي->dmDisplayOrientation == DMDO_90 || گهڻائي->dmDisplayOrientation == DMDO_270) {
        صحيح عارضي = ويڪر;
        ويڪر = اوچائي;
        اوچائي = عارضي;
    }

    إذا (ويڪر >= اوچائي) {
        أرجع SDL_ORIENTATION_LANDSCAPE;
    } وإلا {
        أرجع SDL_ORIENTATION_PORTRAIT;
    }
}

ساكن SDL_DisplayOrientation WIN_GetDisplayOrientation(DEVMODEW *گهڻائي)
{
    إذا (WIN_GetNaturalOrientation(گهڻائي) == SDL_ORIENTATION_LANDSCAPE) {
        بدل (گهڻائي->dmDisplayOrientation) {
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
        بدل (گهڻائي->dmDisplayOrientation) {
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

ساكن فراغ WIN_Get_Refresh_شرح(فراغ *dxgi_output, DEVMODEW *گهڻائي, صحيح *numerator, صحيح *denominator)
{
    // We're not currently using DXGI to query display modes, so fake NTSC timings
    بدل (گهڻائي->dmDisplayFrequency) {
    حالة 119:
    حالة 59:
    حالة 29:
        *numerator = (گهڻائي->dmDisplayFrequency + 1) * 1000;
        *denominator = 1001;
        اكسر;
    افتراضي:
        *numerator = گهڻائي->dmDisplayFrequency;
        *denominator = 1;
        اكسر;
    }

#جيڪڏهن_وصف_ٿيل HAVE_DXGI_H
    إذا (dxgi_output) {
        IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;
        DXGI_گهڻائي_DESC گهڻائي_منزل_ميلاپ;
        DXGI_گهڻائي_DESC closest_ميلاپ;

        SDL_zero(گهڻائي_منزل_ميلاپ);
        گهڻائي_منزل_ميلاپ.ويڪر_2 = گهڻائي->dm_Pels_ويڪر;
        گهڻائي_منزل_ميلاپ.اوچائي_2 = گهڻائي->dm_Pels_اوچائي;
        گهڻائي_منزل_ميلاپ.Refresh_شرح.Numerator = *numerator;
        گهڻائي_منزل_ميلاپ.Refresh_شرح.Denominator = *denominator;
        گهڻائي_منزل_ميلاپ.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        إذا (SUCCEEDED(IDXGIOutput_ڳوليو_Closest_Matching_گهڻائي(pDXGIOutput, &گهڻائي_منزل_ميلاپ, &closest_ميلاپ, عدم))) {
            *numerator = closest_ميلاپ.Refresh_شرح.Numerator;
            *denominator = closest_ميلاپ.Refresh_شرح.Denominator;
        }
    }
#جيڪڏهن_پورو // HAVE_DXGI_H
}

ساكن عائم WIN_GetContentScale(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    صحيح dpi = 0;

    ثابت SDL_Video_معلومات *videodata = (ثابت SDL_Video_معلومات *)_this->اندروني;
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

ساكن bool WIN_Get_Display_گهڻائي(SDL_VideoDevice *_this, فراغ *dxgi_output, HMONITOR hMonitor, LPCWSTR deviceName, DWORD اشاريو, SDL_Display_گهڻائي *گهڻائي, SDL_DisplayOrientation *natural_orientation, SDL_DisplayOrientation *current_orientation)
{
    SDL_Display_گهڻائي_معلومات *معلومات;
    DEVMODEW devmode;

    devmode.dm_سائيز = حجم(devmode);
    devmode.dmDriverExtra = 0;
    إذا (!EnumDisplaySettingsW(deviceName, اشاريو, &devmode)) {
        أرجع false;
    }

    معلومات = (SDL_Display_گهڻائي_معلومات *)SDL_malloc(حجم(*معلومات));
    إذا (!معلومات) {
        أرجع false;
    }

    SDL_zerop(گهڻائي);
    گهڻائي->اندروني = معلومات;
    معلومات->Device_گهڻائي = devmode;

    گهڻائي->format = SDL_PIXELFORMAT_UNKNOWN;
    گهڻائي->w = معلومات->Device_گهڻائي.dm_Pels_ويڪر;
    گهڻائي->h = معلومات->Device_گهڻائي.dm_Pels_اوچائي;
    WIN_Get_Refresh_شرح(dxgi_output, &معلومات->Device_گهڻائي, &گهڻائي->refresh_شرح_numerator, &گهڻائي->refresh_شرح_denominator);

    // Fill in the mode information
    WIN_Update_Display_گهڻائي(_this, deviceName, اشاريو, گهڻائي);

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
    DISPLAYCONFIG_رستو_INFO *paths = عدم;
    DISPLAYCONFIG_گهڻائي_INFO *modes = عدم;
    حرف *نتيجو = عدم;
    UINT32 رستو_ڳڻپ_2 = 0;
    UINT32 گهڻائي_ڳڻپ_2 = 0;
    UINT32 i;
    LONG rc;

    إذا (!videodata->Get_Display_Config_بفر_Sizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        أرجع عدم;
    }

    افعل {
        rc = videodata->Get_Display_Config_بفر_Sizes(QDC_ONLY_سرگرم_PATHS, &رستو_ڳڻپ_2, &گهڻائي_ڳڻپ_2);
        إذا (rc != ERROR_SUCCESS) {
            اذهب WIN_GetDisplayNameVista_failed;
        }

        SDL_free(paths);
        SDL_free(modes);

        paths = (DISPLAYCONFIG_رستو_INFO *)SDL_malloc(حجم(DISPLAYCONFIG_رستو_INFO) * رستو_ڳڻپ_2);
        modes = (DISPLAYCONFIG_گهڻائي_INFO *)SDL_malloc(حجم(DISPLAYCONFIG_گهڻائي_INFO) * گهڻائي_ڳڻپ_2);
        إذا ((!paths) || (!modes)) {
            اذهب WIN_GetDisplayNameVista_failed;
        }

        rc = videodata->QueryDisplayConfig(QDC_ONLY_سرگرم_PATHS, &رستو_ڳڻپ_2, paths, &گهڻائي_ڳڻپ_2, modes, 0);
    } طالما (rc == ERROR_INSUFFICIENT_بفر);

    إذا (rc == ERROR_SUCCESS) {
        لكل (i = 0; i < رستو_ڳڻپ_2; i++) {
            DISPLAYCONFIG_ذريعو_DEVICE_NAME ذريعو_Name;
            DISPLAYCONFIG_هدف_DEVICE_NAME هدف_Name;

            SDL_zero(ذريعو_Name);
            ذريعو_Name.سرو.adapterId = paths[i].هدف_Info.adapterId;
            ذريعو_Name.سرو.type = DISPLAYCONFIG_DEVICE_INFO_GET_ذريعو_NAME;
            ذريعو_Name.سرو.سائيز = حجم(ذريعو_Name);
            ذريعو_Name.سرو.id = paths[i].ذريعو_Info.id;
            rc = videodata->DisplayConfigGetDeviceInfo(&ذريعو_Name.سرو);
            إذا (rc != ERROR_SUCCESS) {
                اكسر;
            } وإلا إذا (SDL_wcscmp(deviceName, ذريعو_Name.viewGdiDeviceName) != 0) {
                استمر;
            }

            SDL_zero(هدف_Name);
            هدف_Name.سرو.adapterId = paths[i].هدف_Info.adapterId;
            هدف_Name.سرو.id = paths[i].هدف_Info.id;
            هدف_Name.سرو.type = DISPLAYCONFIG_DEVICE_INFO_GET_هدف_NAME;
            هدف_Name.سرو.سائيز = حجم(هدف_Name);
            rc = videodata->DisplayConfigGetDeviceInfo(&هدف_Name.سرو);
            إذا (rc == ERROR_SUCCESS) {
                نتيجو = WIN_String_منزل_UTF8_W(هدف_Name.monitorFriendlyDeviceName);
                /* if we got an empty string, treat it as failure so we'll fallback
                   to getting the generic name. */
                إذا (نتيجو && (*نتيجو == '\0')) {
                    SDL_free(نتيجو);
                    نتيجو = عدم;
                }
            }
            اكسر;
        }
    }

    SDL_free(paths);
    SDL_free(modes);
    أرجع نتيجو;

WIN_GetDisplayNameVista_failed:
    SDL_free(نتيجو);
    SDL_free(paths);
    SDL_free(modes);
    أرجع عدم;
}

#جيڪڏهن_وصف_ٿيل HAVE_DXGI1_6_H
ساكن bool WIN_GetMonitorDESC1(HMONITOR hMonitor, DXGI_OUTPUT_DESC1 *desc)
{
    تعريفنوع HRESULT (WINAPI *pfnCreateDXGIFactory1)(REFIID riid, فراغ **ppFactory);
    pfnCreateDXGIFactory1 pCreateDXGIFactory1 = عدم;
    SDL_SharedObject *hDXGIMod = عدم;
    bool مليو = false;

    hDXGIMod = SDL_ڀريو_Object("dxgi.dll");
    إذا (hDXGIMod) {
        pCreateDXGIFactory1 = (pfnCreateDXGIFactory1)SDL_ڀريو_Function(hDXGIMod, "CreateDXGIFactory1");
    }
    إذا (pCreateDXGIFactory1) {
        ساكن ثابت GUID SDL_IID_IDXGIFactory1 = { 0x770aae78, 0xf26f, 0x4dba, { 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 } };
        ساكن ثابت GUID SDL_IID_IDXGIOutput6 = { 0x068346e8, 0xaaec, 0x4b84, { 0xad, 0xd7, 0x13, 0x7f, 0x51, 0x3f, 0x77, 0xa1 } };
        IDXGIFactory1 *dxgiFactory;

        إذا (SUCCEEDED(pCreateDXGIFactory1(&SDL_IID_IDXGIFactory1, (فراغ **)&dxgiFactory))) {
            IDXGIAdapter1 *dxgiAdapter;
            UINT adapter = 0;
            طالما (!مليو && SUCCEEDED(IDXGIFactory1_EnumAdapters1(dxgiFactory, adapter, &dxgiAdapter))) {
                IDXGIOutput *dxgiOutput;
                UINT output = 0;
                طالما (!مليو && SUCCEEDED(IDXGIAdapter1_EnumOutputs(dxgiAdapter, output, &dxgiOutput))) {
                    IDXGIOutput6 *dxgiOutput6;
                    إذا (SUCCEEDED(IDXGIOutput_QueryInterface(dxgiOutput, &SDL_IID_IDXGIOutput6, (فراغ **)&dxgiOutput6))) {
                        إذا (SUCCEEDED(IDXGIOutput6_GetDesc1(dxgiOutput6, desc))) {
                            إذا (desc->Monitor == hMonitor) {
                                مليو = true;
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
    أرجع مليو;
}

ساكن bool WIN_Get_Monitor_رستو_Info(SDL_Video_معلومات *videodata, HMONITOR hMonitor, DISPLAYCONFIG_رستو_INFO *رستو_info)
{
    LONG نتيجو;
    MONITORINFOEXW view_info;
    UINT32 i;
    UINT32 انگ_رستو_array_elements = 0;
    UINT32 انگ_گهڻائي_info_array_elements = 0;
    DISPLAYCONFIG_رستو_INFO *رستو_infos = عدم, *new_رستو_infos;
    DISPLAYCONFIG_گهڻائي_INFO *گهڻائي_infos = عدم, *new_گهڻائي_infos;
    bool مليو = false;

    إذا (!videodata->Get_Display_Config_بفر_Sizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        أرجع false;
    }

    SDL_zero(view_info);
    view_info.cb_سائيز = حجم(view_info);
    إذا (!GetMonitorInfoW(hMonitor, (MONITORINFO *)&view_info)) {
        اذهب پورو;
    }

    افعل {
        إذا (videodata->Get_Display_Config_بفر_Sizes(QDC_ONLY_سرگرم_PATHS, &انگ_رستو_array_elements, &انگ_گهڻائي_info_array_elements) != ERROR_SUCCESS) {
            SDL_free(رستو_infos);
            SDL_free(گهڻائي_infos);
            أرجع false;
        }

        new_رستو_infos = (DISPLAYCONFIG_رستو_INFO *)SDL_realloc(رستو_infos, انگ_رستو_array_elements * حجم(*رستو_infos));
        إذا (!new_رستو_infos) {
            اذهب پورو;
        }
        رستو_infos = new_رستو_infos;

        new_گهڻائي_infos = (DISPLAYCONFIG_گهڻائي_INFO *)SDL_realloc(گهڻائي_infos, انگ_گهڻائي_info_array_elements * حجم(*گهڻائي_infos));
        إذا (!new_گهڻائي_infos) {
            اذهب پورو;
        }
        گهڻائي_infos = new_گهڻائي_infos;

        نتيجو = videodata->QueryDisplayConfig(QDC_ONLY_سرگرم_PATHS, &انگ_رستو_array_elements, رستو_infos, &انگ_گهڻائي_info_array_elements, گهڻائي_infos, عدم);

    } طالما (نتيجو == ERROR_INSUFFICIENT_بفر);

    إذا (نتيجو == ERROR_SUCCESS) {
        لكل (i = 0; i < انگ_رستو_array_elements; ++i) {
            DISPLAYCONFIG_ذريعو_DEVICE_NAME device_name;

            SDL_zero(device_name);
            device_name.سرو.type = DISPLAYCONFIG_DEVICE_INFO_GET_ذريعو_NAME;
            device_name.سرو.سائيز = حجم(device_name);
            device_name.سرو.adapterId = رستو_infos[i].ذريعو_Info.adapterId;
            device_name.سرو.id = رستو_infos[i].ذريعو_Info.id;
            إذا (videodata->DisplayConfigGetDeviceInfo(&device_name.سرو) == ERROR_SUCCESS) {
                إذا (SDL_wcscmp(view_info.szDevice, device_name.viewGdiDeviceName) == 0) {
                    SDL_copyp(رستو_info, &رستو_infos[i]);
                    مليو = true;
                    اكسر;
                }
            }
        }
    }

پورو:
    SDL_free(رستو_infos);
    SDL_free(گهڻائي_infos);

    أرجع مليو;
}

ساكن عائم WIN_Get_SDRWhite_نقطو(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    DISPLAYCONFIG_رستو_INFO رستو_info;
    SDL_Video_معلومات *videodata = _this->اندروني;
    عائم SDR_white_level = 1.0f;

    إذا (WIN_Get_Monitor_رستو_Info(videodata, hMonitor, &رستو_info)) {
        /* workarounds for https://github.com/libsdl-org/SDL/issues/11193 */
        بنية SDL_DISPLAYCONFIG_SDR_WHITE_LEVEL {
          DISPLAYCONFIG_DEVICE_INFO_سرو سرو;
          ULONG SDRWhiteLevel;
        } white_level;
        #وصف_ڪريو DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL 11

        SDL_zero(white_level);
        white_level.سرو.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
        white_level.سرو.سائيز = حجم(white_level);
        white_level.سرو.adapterId = رستو_info.هدف_Info.adapterId;
        white_level.سرو.id = رستو_info.هدف_Info.id;
        // WIN_GetMonitorPathInfo() succeeded: DisplayConfigGetDeviceInfo is not NULL
        إذا (videodata->DisplayConfigGetDeviceInfo(&white_level.سرو) == ERROR_SUCCESS &&
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
        إذا (desc.ColorSpace == DXGI_COLOR_SPACE_RGB_ڀريل_G2084_NONE_P2020) {
            HDR->SDR_white_level = WIN_Get_SDRWhite_نقطو(_this, hMonitor);
            HDR->HDR_headroom = (desc.MaxLuminance / SCRGB_NITS) / HDR->SDR_white_level;
        }
    }
}
#جيڪڏهن_پورو // HAVE_DXGI1_6_H

ساكن فراغ WIN_جوڙيو_Display(SDL_VideoDevice *_this, HMONITOR hMonitor, ثابت MONITORINFOEXW *info, صحيح *display_اشاريو)
{
    صحيح i, اشاريو = *display_اشاريو;
    SDL_VideoDisplay display;
    SDL_Display_معلومات *displaydata;
    فراغ *dxgi_output = عدم;
    SDL_Display_گهڻائي گهڻائي;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    عائم content_scale = WIN_GetContentScale(_this, hMonitor);

#جيڪڏهن_وصف_ٿيل DEBUG_MODES
    SDL_Log("Display: %s", WIN_String_منزل_UTF8_W(info->szDevice));
#جيڪڏهن_پورو

    dxgi_output = WIN_GetDXGIOutput(_this, info->szDevice);
    bool مليو = WIN_Get_Display_گهڻائي(_this, dxgi_output, hMonitor, info->szDevice, ENUM_CURRENT_SETTINGS, &گهڻائي, &natural_orientation, &current_orientation);
    WIN_ReleaseDXGIOutput(dxgi_output);
    إذا (!مليو) {
        أرجع;
    }

    // Prevent adding duplicate displays. Do this after we know the display is
    // ready to be added to allow any displays that we can't fully query to be
    // removed
    لكل (i = 0; i < _this->انگ_displays; ++i) {
        SDL_Display_معلومات *اندروني = _this->displays[i]->اندروني;
        إذا (SDL_wcscmp(اندروني->DeviceName, info->szDevice) == 0) {
            bool moved = (اشاريو != i);
            bool بدليو_bounds = false;

            إذا (اندروني->state != DisplayRemoved) {
                // We've already enumerated this display, don't move it
                اذهب cleanup;
            }

            إذا (اشاريو >= _this->انگ_displays) {
                // This should never happen due to the check above, but just in case...
                اذهب cleanup;
            }

            إذا (moved) {
                SDL_VideoDisplay *tmp;

                tmp = _this->displays[اشاريو];
                _this->displays[اشاريو] = _this->displays[i];
                _this->displays[i] = tmp;
                i = اشاريو;
            }

            اندروني->MonitorHandle = hMonitor;
            اندروني->state = DisplayUnchanged;

            SDL_PropertiesID props = SDL_GetDisplayProperties(_this->displays[i]->id);
            SDL_سيٽ_اشارو_Property(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_اشارو, hMonitor);

            إذا (!_this->setting_display_گهڻائي) {
                SDL_VideoDisplay *existing_display = _this->displays[i];
                SDL_Rect bounds;

                SDL_ResetFullscreenDisplayModes(existing_display);
                SDL_سيٽ_Desktop_Display_گهڻائي(existing_display, &گهڻائي);
                // The mode is owned by the video subsystem
                گهڻائي.اندروني = عدم;
                إذا (WIN_GetDisplayBounds(_this, existing_display, &bounds) &&
                    SDL_memcmp(&اندروني->bounds, &bounds, حجم(bounds)) != 0) {
                    بدليو_bounds = true;
                    SDL_copyp(&اندروني->bounds, &bounds);
                }
                إذا (moved || بدليو_bounds) {
                    SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_MOVED, 0, 0);
                }
                SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_ORIENTATION, current_orientation, 0);
                SDL_سيٽ_Display_Content_Scale(existing_display, content_scale);
#جيڪڏهن_وصف_ٿيل HAVE_DXGI1_6_H
                SDL_HDROutputProperties HDR;
                WIN_GetHDRProperties(_this, hMonitor, &HDR);
                SDL_سيٽ_Display_HDRProperties(existing_display, &HDR);
#جيڪڏهن_پورو
            }
            اذهب پورو;
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
    display.name = WIN_GetDisplayNameVista(_this->اندروني, info->szDevice);
    إذا (!display.name) {
        DISPLAY_DEVICEW device;
        SDL_zero(device);
        device.cb = حجم(device);
        إذا (EnumDisplayDevicesW(info->szDevice, 0, &device, 0)) {
            display.name = WIN_String_منزل_UTF8_W(device.DeviceString);
        }
    }

    display.desktop_گهڻائي = گهڻائي;
    display.natural_orientation = natural_orientation;
    display.current_orientation = current_orientation;
    display.content_scale = content_scale;
    display.device = _this;
    display.اندروني = displaydata;
    WIN_GetDisplayBounds(_this, &display, &displaydata->bounds);
#جيڪڏهن_وصف_ٿيل HAVE_DXGI1_6_H
    WIN_GetHDRProperties(_this, hMonitor, &display.HDR);
#جيڪڏهن_پورو
    SDL_DisplayID displayID = SDL_جوڙيو_Video_Display(&display, false);
    إذا (displayID) {
        // The mode is owned by the video subsystem
        گهڻائي.اندروني = عدم;

        SDL_PropertiesID props = SDL_GetDisplayProperties(displayID);
        SDL_سيٽ_اشارو_Property(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_اشارو, hMonitor);
    } وإلا {
        SDL_free(displaydata);
    }
    SDL_free(display.name);

پورو:
    *display_اشاريو += 1;

cleanup:
    SDL_free(گهڻائي.اندروني);
}

تعريفنوع بنية WIN_جوڙيو_Displays_معلومات
{
    SDL_VideoDevice *video_device;
    صحيح display_اشاريو;
    bool want_primary;
} WIN_جوڙيو_Displays_معلومات_2;

ساكن BOOL CALLBACK WIN_جوڙيو_Displays_Callback(HMONITOR hMonitor,
                                             HDC hdcMonitor,
                                             LPRECT lprcMonitor,
                                             LPARAM dw_معلومات)
{
    WIN_جوڙيو_Displays_معلومات_2 *معلومات = (WIN_جوڙيو_Displays_معلومات_2 *)dw_معلومات;
    MONITORINFOEXW info;

    SDL_zero(info);
    info.cb_سائيز = حجم(info);

    إذا (GetMonitorInfoW(hMonitor, (LPMONITORINFO)&info) != 0) {
        ثابت bool is_primary = ((info.dwFlags & MONITORINFOF_PRIMARY) == MONITORINFOF_PRIMARY);

        إذا (is_primary == معلومات->want_primary) {
            WIN_جوڙيو_Display(معلومات->video_device, hMonitor, &info, &معلومات->display_اشاريو);
        }
    }

    // continue enumeration
    أرجع TRUE;
}

ساكن فراغ WIN_جوڙيو_Displays(SDL_VideoDevice *_this)
{
    WIN_جوڙيو_Displays_معلومات_2 callback_معلومات;
    callback_معلومات.video_device = _this;
    callback_معلومات.display_اشاريو = 0;

    callback_معلومات.want_primary = true;
    EnumDisplayMonitors(عدم, عدم, WIN_جوڙيو_Displays_Callback, (LPARAM)&callback_معلومات);

    callback_معلومات.want_primary = false;
    EnumDisplayMonitors(عدم, عدم, WIN_جوڙيو_Displays_Callback, (LPARAM)&callback_معلومات);
}

bool WIN_InitModes(SDL_VideoDevice *_this)
{
    WIN_جوڙيو_Displays(_this);

    إذا (_this->انگ_displays == 0) {
        أرجع SDL_سيٽ_Error("No displays available");
    }
    أرجع true;
}

bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ثابت SDL_Display_معلومات *معلومات = display->اندروني;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cb_سائيز = حجم(MONITORINFO);
    rc = GetMonitorInfo(معلومات->MonitorHandle, &minfo);

    إذا (!rc) {
        أرجع SDL_سيٽ_Error("Couldn't find monitor data");
    }

    rect->x = minfo.rcMonitor.کاٻو;
    rect->y = minfo.rcMonitor.چوٽي;
    rect->w = minfo.rcMonitor.ساڄو - minfo.rcMonitor.کاٻو;
    rect->h = minfo.rcMonitor.bottom - minfo.rcMonitor.چوٽي;

    أرجع true;
}

bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ثابت SDL_Display_معلومات *معلومات = display->اندروني;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cb_سائيز = حجم(MONITORINFO);
    rc = GetMonitorInfo(معلومات->MonitorHandle, &minfo);

    إذا (!rc) {
        أرجع SDL_سيٽ_Error("Couldn't find monitor data");
    }

    rect->x = minfo.rcWork.کاٻو;
    rect->y = minfo.rcWork.چوٽي;
    rect->w = minfo.rcWork.ساڄو - minfo.rcWork.کاٻو;
    rect->h = minfo.rcWork.bottom - minfo.rcWork.چوٽي;

    أرجع true;
}

bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_معلومات *معلومات = display->اندروني;
    فراغ *dxgi_output;
    DWORD i;
    SDL_Display_گهڻائي گهڻائي;

    dxgi_output = WIN_GetDXGIOutput(_this, معلومات->DeviceName);

    // Make sure we add the current mode to the list in case it's a custom mode that doesn't enumerate
    لكل (i = ENUM_CURRENT_SETTINGS; ; ++i) {
        إذا (!WIN_Get_Display_گهڻائي(_this, dxgi_output, معلومات->MonitorHandle, معلومات->DeviceName, i, &گهڻائي, عدم, عدم)) {
            اكسر;
        }
        إذا (SDL_ISPIXELFORMAT_اشاريي_وارو(گهڻائي.format)) {
            // We don't support palettized modes now
            SDL_free(گهڻائي.اندروني);
            استمر;
        }
        إذا (گهڻائي.format != SDL_PIXELFORMAT_UNKNOWN) {
            إذا (!SDL_جوڙيو_Fullscreen_Display_گهڻائي(display, &گهڻائي)) {
                SDL_free(گهڻائي.اندروني);
            }
        } وإلا {
            SDL_free(گهڻائي.اندروني);
        }
    }

    WIN_ReleaseDXGIOutput(dxgi_output);

    أرجع true;
}

#جيڪڏهن_وصف_ٿيل DEBUG_MODES
ساكن فراغ WIN_LogMonitor(SDL_VideoDevice *_this, HMONITOR mon)
{
    ثابت SDL_Video_معلومات *vid_معلومات = (ثابت SDL_Video_معلومات *)_this->اندروني;
    MONITORINFOEX minfo;
    UINT xdpi = 0, ydpi = 0;
    حرف *name_utf8;

    إذا (vid_معلومات->GetDpiForMonitor) {
        vid_معلومات->GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &xdpi, &ydpi);
    }

    SDL_zero(minfo);
    minfo.cb_سائيز = حجم(minfo);
    GetMonitorInfo(mon, (LPMONITORINFO)&minfo);

    name_utf8 = WIN_String_منزل_UTF8(minfo.szDevice);

    SDL_Log("WIN_LogMonitor: monitor \"%s\": dpi: %d windows screen coordinates: %d, %d, %dx%d",
            name_utf8,
            xdpi,
            minfo.rcMonitor.کاٻو,
            minfo.rcMonitor.چوٽي,
            minfo.rcMonitor.ساڄو - minfo.rcMonitor.کاٻو,
            minfo.rcMonitor.bottom - minfo.rcMonitor.چوٽي);

    SDL_free(name_utf8);
}
#جيڪڏهن_پورو

bool WIN_سيٽ_Display_گهڻائي(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_گهڻائي *گهڻائي)
{
    SDL_Display_معلومات *displaydata = display->اندروني;
    SDL_Display_گهڻائي_معلومات *معلومات = (SDL_Display_گهڻائي_معلومات *)گهڻائي->اندروني;
    LONG حالت;

#جيڪڏهن_وصف_ٿيل DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state before mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#جيڪڏهن_پورو

    /* High-DPI notes:

       - ChangeDisplaySettingsEx always takes pixels.
       - e.g. if the display is set to 2880x1800 with 200% scaling in Display Settings
         - calling ChangeDisplaySettingsEx with a dmPelsWidth/Height other than 2880x1800 will
           change the monitor DPI to 96. (100% scaling)
         - calling ChangeDisplaySettingsEx with a dmPelsWidth/Height of 2880x1800 (or a NULL DEVMODE*) will
           reset the monitor DPI to 192. (200% scaling)

       NOTE: these are temporary changes in DPI, not modifications to the Control Panel setting. */
    إذا (گهڻائي->اندروني == display->desktop_گهڻائي.اندروني) {
#جيڪڏهن_وصف_ٿيل DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: resetting to original resolution");
#جيڪڏهن_پورو
        حالت = ChangeDisplaySettingsExW(displaydata->DeviceName, عدم, عدم, CDS_FULLSCREEN, عدم);
    } وإلا {
#جيڪڏهن_وصف_ٿيل DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: changing to %dx%d pixels", معلومات->Device_گهڻائي.dm_Pels_ويڪر, معلومات->Device_گهڻائي.dm_Pels_اوچائي);
#جيڪڏهن_پورو
        حالت = ChangeDisplaySettingsExW(displaydata->DeviceName, &معلومات->Device_گهڻائي, عدم, CDS_FULLSCREEN, عدم);
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
        أرجع SDL_سيٽ_Error("ChangeDisplaySettingsEx() failed: %s", reason);
    }

#جيڪڏهن_وصف_ٿيل DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state after mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#جيڪڏهن_پورو

    EnumDisplaySettingsW(displaydata->DeviceName, ENUM_CURRENT_SETTINGS, &معلومات->Device_گهڻائي);
    WIN_Update_Display_گهڻائي(_this, displaydata->DeviceName, ENUM_CURRENT_SETTINGS, گهڻائي);
    أرجع true;
}

فراغ WIN_RefreshDisplays(SDL_VideoDevice *_this)
{
    صحيح i;

    // Mark all displays as potentially invalid to detect
    // entries that have actually been removed
    لكل (i = 0; i < _this->انگ_displays; ++i) {
        SDL_Display_معلومات *اندروني = _this->displays[i]->اندروني;
        اندروني->state = DisplayRemoved;
    }

    // Enumerate displays to add any new ones and mark still
    // connected entries as valid
    WIN_جوڙيو_Displays(_this);

    // Delete any entries still marked as invalid, iterate
    // in reverse as each delete takes effect immediately
    لكل (i = _this->انگ_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_Display_معلومات *اندروني = display->اندروني;
        إذا (اندروني->state == DisplayRemoved) {
            SDL_DelVideoDisplay(display->id, true);
        }
    }

    // Send events for any newly added displays
    لكل (i = 0; i < _this->انگ_displays; ++i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_Display_معلومات *اندروني = display->اندروني;
        إذا (اندروني->state == DisplayAdded) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
        }
    }
}

فراغ WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this)
{
    // This almost never happens, so just go ahead and send update events for all displays
    لكل (صحيح i = 0; i < _this->انگ_displays; ++i) {
        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_بدليو, 0, 0);
    }
}

فراغ WIN_QuitModes(SDL_VideoDevice *_this)
{
    // All fullscreen windows should have restored modes by now
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_WINDOWS
