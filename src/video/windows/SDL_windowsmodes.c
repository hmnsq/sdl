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

#اگر_تعریف_شدہ HAVE_DXGI1_6_H
#تعریف_کرو COBJMACROS
#شامل <dxgi1_6.h>
#اگر_ختم

// Windows CE compatibility
#اگر_غیر_تعریف_شدہ CDS_FULLSCREEN
#تعریف_کرو CDS_FULLSCREEN 0
#اگر_ختم
#اگر_غیر_تعریف_شدہ USER_DEFAULT_SCREEN_DPI
#تعریف_کرو USER_DEFAULT_SCREEN_DPI 96
#اگر_ختم

// #define DEBUG_MODES
// #define HIGHDPI_DEBUG_VERBOSE

ساکن خالی WIN_Update_Display_منوال(SDL_VideoDevice *_this, LPCWSTR deviceName, DWORD اشاریہ, SDL_Display_منوال *منوال)
{
    SDL_Display_منوال_ڈیٹا *ڈیٹا = (SDL_Display_منوال_ڈیٹا *)منوال->اندرونی_2;
    HDC hdc;

    ڈیٹا->Device_منوال.dmFields = (DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS);

    // NOLINTNEXTLINE(bugprone-assignment-in-if-condition): No simple way to extract the assignment
    اگر (اشاریہ == ENUM_CURRENT_SETTINGS && (hdc = CreateDCW(deviceName, تہی, تہی, تہی)) != تہی) {
        حرف bmi_ڈیٹا[حجم(BITMAPINFOHEADER) + 256 * حجم(RGBQUAD)];
        LPBITMAPINFO bmi;
        HBITMAP hbm;

        SDL_zeroa(bmi_ڈیٹا);
        bmi = (LPBITMAPINFO)bmi_ڈیٹا;
        bmi->bmi_سرخی.bi_سائز = حجم(BITMAPINFOHEADER);

        hbm = CreateCompatibleBitmap(hdc, 1, 1);
        GetDIBits(hdc, hbm, 0, 1, تہی, bmi, DIB_RGB_COLORS);
        GetDIBits(hdc, hbm, 0, 1, تہی, bmi, DIB_RGB_COLORS);
        DeleteObject(hbm);
        DeleteDC(hdc);
        اگر (bmi->bmi_سرخی.biCompression == BI_BITFIELDS) {
            انتخاب (*(Uint32 *)bmi->bmiColors) {
            حالت 0x00FF0000:
                منوال->format = SDL_PIXELFORMAT_XRGB8888;
                توڑو;
            حالت 0x000000FF:
                منوال->format = SDL_PIXELFORMAT_XBGR8888;
                توڑو;
            حالت 0xF800:
                منوال->format = SDL_PIXELFORMAT_RGB565;
                توڑو;
            حالت 0x7C00:
                منوال->format = SDL_PIXELFORMAT_XRGB1555;
                توڑو;
            }
        } ورنہ اگر (bmi->bmi_سرخی.biCompression == BI_RGB) {
            اگر (bmi->bmi_سرخی.bi_ثنائی_ہندسہ_گنتی == 24) {
                منوال->format = SDL_PIXELFORMAT_RGB24;
            } ورنہ اگر (bmi->bmi_سرخی.bi_ثنائی_ہندسہ_گنتی == 8) {
                منوال->format = SDL_PIXELFORMAT_INDEX8;
            } ورنہ اگر (bmi->bmi_سرخی.bi_ثنائی_ہندسہ_گنتی == 4) {
                منوال->format = SDL_PIXELFORMAT_INDEX4LSB;
            }
        }
    } ورنہ اگر (منوال->format == SDL_PIXELFORMAT_UNKNOWN) {
        // FIXME: Can we tell what this will be?
        اگر ((ڈیٹا->Device_منوال.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL) {
            انتخاب (ڈیٹا->Device_منوال.dm_بٹ_فی_Pel) {
            حالت 32:
                منوال->format = SDL_PIXELFORMAT_XRGB8888;
                توڑو;
            حالت 24:
                منوال->format = SDL_PIXELFORMAT_RGB24;
                توڑو;
            حالت 16:
                منوال->format = SDL_PIXELFORMAT_RGB565;
                توڑو;
            حالت 15:
                منوال->format = SDL_PIXELFORMAT_XRGB1555;
                توڑو;
            حالت 8:
                منوال->format = SDL_PIXELFORMAT_INDEX8;
                توڑو;
            حالت 4:
                منوال->format = SDL_PIXELFORMAT_INDEX4LSB;
                توڑو;
            }
        }
    }
}

ساکن خالی *WIN_GetDXGIOutput(SDL_VideoDevice *_this, ثابت WCHAR *DeviceName)
{
    خالی *نتیجہ = تہی;

#اگر_تعریف_شدہ HAVE_DXGI_H
    ثابت SDL_Video_ڈیٹا *videodata = (ثابت SDL_Video_ڈیٹا *)_this->اندرونی_2;
    صحیح nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    اگر (!videodata->pDXGIFactory) {
        واپس تہی;
    }

    nAdapter = 0;
    جب (!نتیجہ && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        جب (!نتیجہ && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            اگر (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                اگر (SDL_wcscmp(outputDesc.DeviceName, DeviceName) == 0) {
                    نتیجہ = pDXGIOutput;
                }
            }
            اگر (pDXGIOutput != نتیجہ) {
                IDXGIOutput_Release(pDXGIOutput);
            }
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }
#اگر_ختم
    واپس نتیجہ;
}

ساکن خالی WIN_ReleaseDXGIOutput(خالی *dxgi_output)
{
#اگر_تعریف_شدہ HAVE_DXGI_H
    IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;

    اگر (pDXGIOutput) {
        IDXGIOutput_Release(pDXGIOutput);
    }
#اگر_ختم
}

ساکن SDL_DisplayOrientation WIN_GetNaturalOrientation(DEVMODEW *منوال)
{
    صحیح چوڑائی = منوال->dm_Pels_چوڑائی;
    صحیح اونچائی = منوال->dm_Pels_اونچائی;

    // Use unrotated width/height to guess orientation
    اگر (منوال->dmDisplayOrientation == DMDO_90 || منوال->dmDisplayOrientation == DMDO_270) {
        صحیح عارضی = چوڑائی;
        چوڑائی = اونچائی;
        اونچائی = عارضی;
    }

    اگر (چوڑائی >= اونچائی) {
        واپس SDL_ORIENTATION_LANDSCAPE;
    } ورنہ {
        واپس SDL_ORIENTATION_PORTRAIT;
    }
}

ساکن SDL_DisplayOrientation WIN_GetDisplayOrientation(DEVMODEW *منوال)
{
    اگر (WIN_GetNaturalOrientation(منوال) == SDL_ORIENTATION_LANDSCAPE) {
        انتخاب (منوال->dmDisplayOrientation) {
        حالت DMDO_DEFAULT:
            واپس SDL_ORIENTATION_LANDSCAPE;
        حالت DMDO_90:
            واپس SDL_ORIENTATION_PORTRAIT;
        حالت DMDO_180:
            واپس SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        حالت DMDO_270:
            واپس SDL_ORIENTATION_PORTRAIT_FLIPPED;
        طےشدہ:
            واپس SDL_ORIENTATION_UNKNOWN;
        }
    } ورنہ {
        انتخاب (منوال->dmDisplayOrientation) {
        حالت DMDO_DEFAULT:
            واپس SDL_ORIENTATION_PORTRAIT;
        حالت DMDO_90:
            واپس SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        حالت DMDO_180:
            واپس SDL_ORIENTATION_PORTRAIT_FLIPPED;
        حالت DMDO_270:
            واپس SDL_ORIENTATION_LANDSCAPE;
        طےشدہ:
            واپس SDL_ORIENTATION_UNKNOWN;
        }
    }
}

ساکن خالی WIN_Get_Refresh_شرح(خالی *dxgi_output, DEVMODEW *منوال, صحیح *numerator, صحیح *denominator)
{
    // We're not currently using DXGI to query display modes, so fake NTSC timings
    انتخاب (منوال->dmDisplayFrequency) {
    حالت 119:
    حالت 59:
    حالت 29:
        *numerator = (منوال->dmDisplayFrequency + 1) * 1000;
        *denominator = 1001;
        توڑو;
    طےشدہ:
        *numerator = منوال->dmDisplayFrequency;
        *denominator = 1;
        توڑو;
    }

#اگر_تعریف_شدہ HAVE_DXGI_H
    اگر (dxgi_output) {
        IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;
        DXGI_منوال_DESC منوال_مقصد_مطابقت;
        DXGI_منوال_DESC closest_مطابقت;

        SDL_zero(منوال_مقصد_مطابقت);
        منوال_مقصد_مطابقت.چوڑائی_2 = منوال->dm_Pels_چوڑائی;
        منوال_مقصد_مطابقت.اونچائی_2 = منوال->dm_Pels_اونچائی;
        منوال_مقصد_مطابقت.Refresh_شرح.Numerator = *numerator;
        منوال_مقصد_مطابقت.Refresh_شرح.Denominator = *denominator;
        منوال_مقصد_مطابقت.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        اگر (SUCCEEDED(IDXGIOutput_ڈھونڈو_Closest_Matching_منوال(pDXGIOutput, &منوال_مقصد_مطابقت, &closest_مطابقت, تہی))) {
            *numerator = closest_مطابقت.Refresh_شرح.Numerator;
            *denominator = closest_مطابقت.Refresh_شرح.Denominator;
        }
    }
#اگر_ختم // HAVE_DXGI_H
}

ساکن اعشاری WIN_GetContentScale(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    صحیح dpi = 0;

    ثابت SDL_Video_ڈیٹا *videodata = (ثابت SDL_Video_ڈیٹا *)_this->اندرونی_2;
    اگر (videodata->GetDpiForMonitor) {
        UINT hdpi_uint, vdpi_uint;
        اگر (videodata->GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
            dpi = (صحیح)hdpi_uint;
        }
    }
    اگر (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(تہی);
        اگر (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(تہی, hdc);
        }
    }
    اگر (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    واپس dpi / (اعشاری)USER_DEFAULT_SCREEN_DPI;
}

ساکن bool WIN_Get_Display_منوال(SDL_VideoDevice *_this, خالی *dxgi_output, HMONITOR hMonitor, LPCWSTR deviceName, DWORD اشاریہ, SDL_Display_منوال *منوال, SDL_DisplayOrientation *natural_orientation, SDL_DisplayOrientation *current_orientation)
{
    SDL_Display_منوال_ڈیٹا *ڈیٹا;
    DEVMODEW devmode;

    devmode.dm_سائز = حجم(devmode);
    devmode.dmDriverExtra = 0;
    اگر (!EnumDisplaySettingsW(deviceName, اشاریہ, &devmode)) {
        واپس false;
    }

    ڈیٹا = (SDL_Display_منوال_ڈیٹا *)SDL_malloc(حجم(*ڈیٹا));
    اگر (!ڈیٹا) {
        واپس false;
    }

    SDL_zerop(منوال);
    منوال->اندرونی_2 = ڈیٹا;
    ڈیٹا->Device_منوال = devmode;

    منوال->format = SDL_PIXELFORMAT_UNKNOWN;
    منوال->w = ڈیٹا->Device_منوال.dm_Pels_چوڑائی;
    منوال->h = ڈیٹا->Device_منوال.dm_Pels_اونچائی;
    WIN_Get_Refresh_شرح(dxgi_output, &ڈیٹا->Device_منوال, &منوال->refresh_شرح_numerator, &منوال->refresh_شرح_denominator);

    // Fill in the mode information
    WIN_Update_Display_منوال(_this, deviceName, اشاریہ, منوال);

    اگر (natural_orientation) {
        *natural_orientation = WIN_GetNaturalOrientation(&devmode);
    }
    اگر (current_orientation) {
        *current_orientation = WIN_GetDisplayOrientation(&devmode);
    }

    واپس true;
}

ساکن حرف *WIN_GetDisplayNameVista(SDL_Video_ڈیٹا *videodata, ثابت WCHAR *deviceName)
{
    DISPLAYCONFIG_راستہ_INFO *paths = تہی;
    DISPLAYCONFIG_منوال_INFO *modes = تہی;
    حرف *نتیجہ = تہی;
    UINT32 راستہ_گنتی_2 = 0;
    UINT32 منوال_گنتی_2 = 0;
    UINT32 i;
    LONG rc;

    اگر (!videodata->Get_Display_Config_بفر_Sizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        واپس تہی;
    }

    کرو {
        rc = videodata->Get_Display_Config_بفر_Sizes(QDC_ONLY_فعال_PATHS, &راستہ_گنتی_2, &منوال_گنتی_2);
        اگر (rc != ERROR_SUCCESS) {
            جاؤ WIN_GetDisplayNameVista_failed;
        }

        SDL_free(paths);
        SDL_free(modes);

        paths = (DISPLAYCONFIG_راستہ_INFO *)SDL_malloc(حجم(DISPLAYCONFIG_راستہ_INFO) * راستہ_گنتی_2);
        modes = (DISPLAYCONFIG_منوال_INFO *)SDL_malloc(حجم(DISPLAYCONFIG_منوال_INFO) * منوال_گنتی_2);
        اگر ((!paths) || (!modes)) {
            جاؤ WIN_GetDisplayNameVista_failed;
        }

        rc = videodata->QueryDisplayConfig(QDC_ONLY_فعال_PATHS, &راستہ_گنتی_2, paths, &منوال_گنتی_2, modes, 0);
    } جب (rc == ERROR_INSUFFICIENT_بفر);

    اگر (rc == ERROR_SUCCESS) {
        برائے (i = 0; i < راستہ_گنتی_2; i++) {
            DISPLAYCONFIG_ماخذ_DEVICE_NAME ماخذ_Name;
            DISPLAYCONFIG_ہدف_DEVICE_NAME ہدف_Name;

            SDL_zero(ماخذ_Name);
            ماخذ_Name.سرخی.adapterId = paths[i].ہدف_Info.adapterId;
            ماخذ_Name.سرخی.type = DISPLAYCONFIG_DEVICE_INFO_GET_ماخذ_NAME;
            ماخذ_Name.سرخی.سائز = حجم(ماخذ_Name);
            ماخذ_Name.سرخی.id = paths[i].ماخذ_Info.id;
            rc = videodata->DisplayConfigGetDeviceInfo(&ماخذ_Name.سرخی);
            اگر (rc != ERROR_SUCCESS) {
                توڑو;
            } ورنہ اگر (SDL_wcscmp(deviceName, ماخذ_Name.viewGdiDeviceName) != 0) {
                جاری;
            }

            SDL_zero(ہدف_Name);
            ہدف_Name.سرخی.adapterId = paths[i].ہدف_Info.adapterId;
            ہدف_Name.سرخی.id = paths[i].ہدف_Info.id;
            ہدف_Name.سرخی.type = DISPLAYCONFIG_DEVICE_INFO_GET_ہدف_NAME;
            ہدف_Name.سرخی.سائز = حجم(ہدف_Name);
            rc = videodata->DisplayConfigGetDeviceInfo(&ہدف_Name.سرخی);
            اگر (rc == ERROR_SUCCESS) {
                نتیجہ = WIN_String_مقصد_UTF8_W(ہدف_Name.monitorFriendlyDeviceName);
                /* if we got an empty string, treat it as failure so we'll fallback
                   to getting the generic name. */
                اگر (نتیجہ && (*نتیجہ == '\0')) {
                    SDL_free(نتیجہ);
                    نتیجہ = تہی;
                }
            }
            توڑو;
        }
    }

    SDL_free(paths);
    SDL_free(modes);
    واپس نتیجہ;

WIN_GetDisplayNameVista_failed:
    SDL_free(نتیجہ);
    SDL_free(paths);
    SDL_free(modes);
    واپس تہی;
}

#اگر_تعریف_شدہ HAVE_DXGI1_6_H
ساکن bool WIN_GetMonitorDESC1(HMONITOR hMonitor, DXGI_OUTPUT_DESC1 *desc)
{
    قسمتعریف HRESULT (WINAPI *pfnCreateDXGIFactory1)(REFIID riid, خالی **ppFactory);
    pfnCreateDXGIFactory1 pCreateDXGIFactory1 = تہی;
    SDL_SharedObject *hDXGIMod = تہی;
    bool ملا = false;

    hDXGIMod = SDL_بھرو_Object("dxgi.dll");
    اگر (hDXGIMod) {
        pCreateDXGIFactory1 = (pfnCreateDXGIFactory1)SDL_بھرو_Function(hDXGIMod, "CreateDXGIFactory1");
    }
    اگر (pCreateDXGIFactory1) {
        ساکن ثابت GUID SDL_IID_IDXGIFactory1 = { 0x770aae78, 0xf26f, 0x4dba, { 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 } };
        ساکن ثابت GUID SDL_IID_IDXGIOutput6 = { 0x068346e8, 0xaaec, 0x4b84, { 0xad, 0xd7, 0x13, 0x7f, 0x51, 0x3f, 0x77, 0xa1 } };
        IDXGIFactory1 *dxgiFactory;

        اگر (SUCCEEDED(pCreateDXGIFactory1(&SDL_IID_IDXGIFactory1, (خالی **)&dxgiFactory))) {
            IDXGIAdapter1 *dxgiAdapter;
            UINT adapter = 0;
            جب (!ملا && SUCCEEDED(IDXGIFactory1_EnumAdapters1(dxgiFactory, adapter, &dxgiAdapter))) {
                IDXGIOutput *dxgiOutput;
                UINT output = 0;
                جب (!ملا && SUCCEEDED(IDXGIAdapter1_EnumOutputs(dxgiAdapter, output, &dxgiOutput))) {
                    IDXGIOutput6 *dxgiOutput6;
                    اگر (SUCCEEDED(IDXGIOutput_QueryInterface(dxgiOutput, &SDL_IID_IDXGIOutput6, (خالی **)&dxgiOutput6))) {
                        اگر (SUCCEEDED(IDXGIOutput6_GetDesc1(dxgiOutput6, desc))) {
                            اگر (desc->Monitor == hMonitor) {
                                ملا = true;
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
    واپس ملا;
}

ساکن bool WIN_Get_Monitor_راستہ_Info(SDL_Video_ڈیٹا *videodata, HMONITOR hMonitor, DISPLAYCONFIG_راستہ_INFO *راستہ_info)
{
    LONG نتیجہ;
    MONITORINFOEXW view_info;
    UINT32 i;
    UINT32 عدد_راستہ_array_elements = 0;
    UINT32 عدد_منوال_info_array_elements = 0;
    DISPLAYCONFIG_راستہ_INFO *راستہ_infos = تہی, *new_راستہ_infos;
    DISPLAYCONFIG_منوال_INFO *منوال_infos = تہی, *new_منوال_infos;
    bool ملا = false;

    اگر (!videodata->Get_Display_Config_بفر_Sizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        واپس false;
    }

    SDL_zero(view_info);
    view_info.cb_سائز = حجم(view_info);
    اگر (!GetMonitorInfoW(hMonitor, (MONITORINFO *)&view_info)) {
        جاؤ مکمل;
    }

    کرو {
        اگر (videodata->Get_Display_Config_بفر_Sizes(QDC_ONLY_فعال_PATHS, &عدد_راستہ_array_elements, &عدد_منوال_info_array_elements) != ERROR_SUCCESS) {
            SDL_free(راستہ_infos);
            SDL_free(منوال_infos);
            واپس false;
        }

        new_راستہ_infos = (DISPLAYCONFIG_راستہ_INFO *)SDL_realloc(راستہ_infos, عدد_راستہ_array_elements * حجم(*راستہ_infos));
        اگر (!new_راستہ_infos) {
            جاؤ مکمل;
        }
        راستہ_infos = new_راستہ_infos;

        new_منوال_infos = (DISPLAYCONFIG_منوال_INFO *)SDL_realloc(منوال_infos, عدد_منوال_info_array_elements * حجم(*منوال_infos));
        اگر (!new_منوال_infos) {
            جاؤ مکمل;
        }
        منوال_infos = new_منوال_infos;

        نتیجہ = videodata->QueryDisplayConfig(QDC_ONLY_فعال_PATHS, &عدد_راستہ_array_elements, راستہ_infos, &عدد_منوال_info_array_elements, منوال_infos, تہی);

    } جب (نتیجہ == ERROR_INSUFFICIENT_بفر);

    اگر (نتیجہ == ERROR_SUCCESS) {
        برائے (i = 0; i < عدد_راستہ_array_elements; ++i) {
            DISPLAYCONFIG_ماخذ_DEVICE_NAME device_name;

            SDL_zero(device_name);
            device_name.سرخی.type = DISPLAYCONFIG_DEVICE_INFO_GET_ماخذ_NAME;
            device_name.سرخی.سائز = حجم(device_name);
            device_name.سرخی.adapterId = راستہ_infos[i].ماخذ_Info.adapterId;
            device_name.سرخی.id = راستہ_infos[i].ماخذ_Info.id;
            اگر (videodata->DisplayConfigGetDeviceInfo(&device_name.سرخی) == ERROR_SUCCESS) {
                اگر (SDL_wcscmp(view_info.szDevice, device_name.viewGdiDeviceName) == 0) {
                    SDL_copyp(راستہ_info, &راستہ_infos[i]);
                    ملا = true;
                    توڑو;
                }
            }
        }
    }

مکمل:
    SDL_free(راستہ_infos);
    SDL_free(منوال_infos);

    واپس ملا;
}

ساکن اعشاری WIN_Get_SDRWhite_نقطہ(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    DISPLAYCONFIG_راستہ_INFO راستہ_info;
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    اعشاری SDR_white_level = 1.0f;

    اگر (WIN_Get_Monitor_راستہ_Info(videodata, hMonitor, &راستہ_info)) {
        /* workarounds for https://github.com/libsdl-org/SDL/issues/11193 */
        ساخت SDL_DISPLAYCONFIG_SDR_WHITE_LEVEL {
          DISPLAYCONFIG_DEVICE_INFO_سرخی سرخی;
          ULONG SDRWhiteLevel;
        } white_level;
        #تعریف_کرو DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL 11

        SDL_zero(white_level);
        white_level.سرخی.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
        white_level.سرخی.سائز = حجم(white_level);
        white_level.سرخی.adapterId = راستہ_info.ہدف_Info.adapterId;
        white_level.سرخی.id = راستہ_info.ہدف_Info.id;
        // WIN_GetMonitorPathInfo() succeeded: DisplayConfigGetDeviceInfo is not NULL
        اگر (videodata->DisplayConfigGetDeviceInfo(&white_level.سرخی) == ERROR_SUCCESS &&
            white_level.SDRWhiteLevel > 0) {
            SDR_white_level = (white_level.SDRWhiteLevel / 1000.0f);
        }
    }
    واپس SDR_white_level;
}

ساکن خالی WIN_GetHDRProperties(SDL_VideoDevice *_this, HMONITOR hMonitor, SDL_HDROutputProperties *HDR)
{
    DXGI_OUTPUT_DESC1 desc;

    SDL_zerop(HDR);

    اگر (WIN_GetMonitorDESC1(hMonitor, &desc)) {
        اگر (desc.ColorSpace == DXGI_COLOR_SPACE_RGB_بھرا_G2084_NONE_P2020) {
            HDR->SDR_white_level = WIN_Get_SDRWhite_نقطہ(_this, hMonitor);
            HDR->HDR_headroom = (desc.MaxLuminance / SCRGB_NITS) / HDR->SDR_white_level;
        }
    }
}
#اگر_ختم // HAVE_DXGI1_6_H

ساکن خالی WIN_جوڑو_Display(SDL_VideoDevice *_this, HMONITOR hMonitor, ثابت MONITORINFOEXW *info, صحیح *display_اشاریہ)
{
    صحیح i, اشاریہ = *display_اشاریہ;
    SDL_VideoDisplay display;
    SDL_Display_ڈیٹا *displaydata;
    خالی *dxgi_output = تہی;
    SDL_Display_منوال منوال;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    اعشاری content_scale = WIN_GetContentScale(_this, hMonitor);

#اگر_تعریف_شدہ DEBUG_MODES
    SDL_Log("Display: %s", WIN_String_مقصد_UTF8_W(info->szDevice));
#اگر_ختم

    dxgi_output = WIN_GetDXGIOutput(_this, info->szDevice);
    bool ملا = WIN_Get_Display_منوال(_this, dxgi_output, hMonitor, info->szDevice, ENUM_CURRENT_SETTINGS, &منوال, &natural_orientation, &current_orientation);
    WIN_ReleaseDXGIOutput(dxgi_output);
    اگر (!ملا) {
        واپس;
    }

    // Prevent adding duplicate displays. Do this after we know the display is
    // ready to be added to allow any displays that we can't fully query to be
    // removed
    برائے (i = 0; i < _this->عدد_displays; ++i) {
        SDL_Display_ڈیٹا *اندرونی_2 = _this->displays[i]->اندرونی_2;
        اگر (SDL_wcscmp(اندرونی_2->DeviceName, info->szDevice) == 0) {
            bool moved = (اشاریہ != i);
            bool بدلا_bounds = false;

            اگر (اندرونی_2->state != DisplayRemoved) {
                // We've already enumerated this display, don't move it
                جاؤ cleanup;
            }

            اگر (اشاریہ >= _this->عدد_displays) {
                // This should never happen due to the check above, but just in case...
                جاؤ cleanup;
            }

            اگر (moved) {
                SDL_VideoDisplay *tmp;

                tmp = _this->displays[اشاریہ];
                _this->displays[اشاریہ] = _this->displays[i];
                _this->displays[i] = tmp;
                i = اشاریہ;
            }

            اندرونی_2->MonitorHandle = hMonitor;
            اندرونی_2->state = DisplayUnchanged;

            SDL_PropertiesID props = SDL_GetDisplayProperties(_this->displays[i]->id);
            SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_اشارہ_گر, hMonitor);

            اگر (!_this->setting_display_منوال) {
                SDL_VideoDisplay *existing_display = _this->displays[i];
                SDL_Rect bounds;

                SDL_ResetFullscreenDisplayModes(existing_display);
                SDL_سیٹ_Desktop_Display_منوال(existing_display, &منوال);
                // The mode is owned by the video subsystem
                منوال.اندرونی_2 = تہی;
                اگر (WIN_GetDisplayBounds(_this, existing_display, &bounds) &&
                    SDL_memcmp(&اندرونی_2->bounds, &bounds, حجم(bounds)) != 0) {
                    بدلا_bounds = true;
                    SDL_copyp(&اندرونی_2->bounds, &bounds);
                }
                اگر (moved || بدلا_bounds) {
                    SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_MOVED, 0, 0);
                }
                SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_ORIENTATION, current_orientation, 0);
                SDL_سیٹ_Display_Content_Scale(existing_display, content_scale);
#اگر_تعریف_شدہ HAVE_DXGI1_6_H
                SDL_HDROutputProperties HDR;
                WIN_GetHDRProperties(_this, hMonitor, &HDR);
                SDL_سیٹ_Display_HDRProperties(existing_display, &HDR);
#اگر_ختم
            }
            جاؤ مکمل;
        }
    }

    displaydata = (SDL_Display_ڈیٹا *)SDL_calloc(1, حجم(*displaydata));
    اگر (!displaydata) {
        جاؤ cleanup;
    }
    SDL_memcpy(displaydata->DeviceName, info->szDevice, حجم(displaydata->DeviceName));
    displaydata->MonitorHandle = hMonitor;
    displaydata->state = DisplayAdded;

    SDL_zero(display);
    display.name = WIN_GetDisplayNameVista(_this->اندرونی_2, info->szDevice);
    اگر (!display.name) {
        DISPLAY_DEVICEW device;
        SDL_zero(device);
        device.cb = حجم(device);
        اگر (EnumDisplayDevicesW(info->szDevice, 0, &device, 0)) {
            display.name = WIN_String_مقصد_UTF8_W(device.DeviceString);
        }
    }

    display.desktop_منوال = منوال;
    display.natural_orientation = natural_orientation;
    display.current_orientation = current_orientation;
    display.content_scale = content_scale;
    display.device = _this;
    display.اندرونی_2 = displaydata;
    WIN_GetDisplayBounds(_this, &display, &displaydata->bounds);
#اگر_تعریف_شدہ HAVE_DXGI1_6_H
    WIN_GetHDRProperties(_this, hMonitor, &display.HDR);
#اگر_ختم
    SDL_DisplayID displayID = SDL_جوڑو_Video_Display(&display, false);
    اگر (displayID) {
        // The mode is owned by the video subsystem
        منوال.اندرونی_2 = تہی;

        SDL_PropertiesID props = SDL_GetDisplayProperties(displayID);
        SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_اشارہ_گر, hMonitor);
    } ورنہ {
        SDL_free(displaydata);
    }
    SDL_free(display.name);

مکمل:
    *display_اشاریہ += 1;

cleanup:
    SDL_free(منوال.اندرونی_2);
}

قسمتعریف ساخت WIN_جوڑو_Displays_ڈیٹا
{
    SDL_VideoDevice *video_device;
    صحیح display_اشاریہ;
    bool want_primary;
} WIN_جوڑو_Displays_ڈیٹا_2;

ساکن BOOL CALLBACK WIN_جوڑو_Displays_Callback(HMONITOR hMonitor,
                                             HDC hdcMonitor,
                                             LPRECT lprcMonitor,
                                             LPARAM dw_ڈیٹا)
{
    WIN_جوڑو_Displays_ڈیٹا_2 *ڈیٹا = (WIN_جوڑو_Displays_ڈیٹا_2 *)dw_ڈیٹا;
    MONITORINFOEXW info;

    SDL_zero(info);
    info.cb_سائز = حجم(info);

    اگر (GetMonitorInfoW(hMonitor, (LPMONITORINFO)&info) != 0) {
        ثابت bool is_primary = ((info.dwFlags & MONITORINFOF_PRIMARY) == MONITORINFOF_PRIMARY);

        اگر (is_primary == ڈیٹا->want_primary) {
            WIN_جوڑو_Display(ڈیٹا->video_device, hMonitor, &info, &ڈیٹا->display_اشاریہ);
        }
    }

    // continue enumeration
    واپس TRUE;
}

ساکن خالی WIN_جوڑو_Displays(SDL_VideoDevice *_this)
{
    WIN_جوڑو_Displays_ڈیٹا_2 callback_ڈیٹا;
    callback_ڈیٹا.video_device = _this;
    callback_ڈیٹا.display_اشاریہ = 0;

    callback_ڈیٹا.want_primary = true;
    EnumDisplayMonitors(تہی, تہی, WIN_جوڑو_Displays_Callback, (LPARAM)&callback_ڈیٹا);

    callback_ڈیٹا.want_primary = false;
    EnumDisplayMonitors(تہی, تہی, WIN_جوڑو_Displays_Callback, (LPARAM)&callback_ڈیٹا);
}

bool WIN_InitModes(SDL_VideoDevice *_this)
{
    WIN_جوڑو_Displays(_this);

    اگر (_this->عدد_displays == 0) {
        واپس SDL_سیٹ_Error("No displays available");
    }
    واپس true;
}

bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ثابت SDL_Display_ڈیٹا *ڈیٹا = display->اندرونی_2;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cb_سائز = حجم(MONITORINFO);
    rc = GetMonitorInfo(ڈیٹا->MonitorHandle, &minfo);

    اگر (!rc) {
        واپس SDL_سیٹ_Error("Couldn't find monitor data");
    }

    rect->x = minfo.rcMonitor.بایاں;
    rect->y = minfo.rcMonitor.چوٹی;
    rect->w = minfo.rcMonitor.دایاں - minfo.rcMonitor.بایاں;
    rect->h = minfo.rcMonitor.bottom - minfo.rcMonitor.چوٹی;

    واپس true;
}

bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ثابت SDL_Display_ڈیٹا *ڈیٹا = display->اندرونی_2;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cb_سائز = حجم(MONITORINFO);
    rc = GetMonitorInfo(ڈیٹا->MonitorHandle, &minfo);

    اگر (!rc) {
        واپس SDL_سیٹ_Error("Couldn't find monitor data");
    }

    rect->x = minfo.rcWork.بایاں;
    rect->y = minfo.rcWork.چوٹی;
    rect->w = minfo.rcWork.دایاں - minfo.rcWork.بایاں;
    rect->h = minfo.rcWork.bottom - minfo.rcWork.چوٹی;

    واپس true;
}

bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_ڈیٹا *ڈیٹا = display->اندرونی_2;
    خالی *dxgi_output;
    DWORD i;
    SDL_Display_منوال منوال;

    dxgi_output = WIN_GetDXGIOutput(_this, ڈیٹا->DeviceName);

    // Make sure we add the current mode to the list in case it's a custom mode that doesn't enumerate
    برائے (i = ENUM_CURRENT_SETTINGS; ; ++i) {
        اگر (!WIN_Get_Display_منوال(_this, dxgi_output, ڈیٹا->MonitorHandle, ڈیٹا->DeviceName, i, &منوال, تہی, تہی)) {
            توڑو;
        }
        اگر (SDL_ISPIXELFORMAT_اشاریہ_دار(منوال.format)) {
            // We don't support palettized modes now
            SDL_free(منوال.اندرونی_2);
            جاری;
        }
        اگر (منوال.format != SDL_PIXELFORMAT_UNKNOWN) {
            اگر (!SDL_جوڑو_Fullscreen_Display_منوال(display, &منوال)) {
                SDL_free(منوال.اندرونی_2);
            }
        } ورنہ {
            SDL_free(منوال.اندرونی_2);
        }
    }

    WIN_ReleaseDXGIOutput(dxgi_output);

    واپس true;
}

#اگر_تعریف_شدہ DEBUG_MODES
ساکن خالی WIN_LogMonitor(SDL_VideoDevice *_this, HMONITOR mon)
{
    ثابت SDL_Video_ڈیٹا *vid_ڈیٹا = (ثابت SDL_Video_ڈیٹا *)_this->اندرونی_2;
    MONITORINFOEX minfo;
    UINT xdpi = 0, ydpi = 0;
    حرف *name_utf8;

    اگر (vid_ڈیٹا->GetDpiForMonitor) {
        vid_ڈیٹا->GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &xdpi, &ydpi);
    }

    SDL_zero(minfo);
    minfo.cb_سائز = حجم(minfo);
    GetMonitorInfo(mon, (LPMONITORINFO)&minfo);

    name_utf8 = WIN_String_مقصد_UTF8(minfo.szDevice);

    SDL_Log("WIN_LogMonitor: monitor \"%s\": dpi: %d windows screen coordinates: %d, %d, %dx%d",
            name_utf8,
            xdpi,
            minfo.rcMonitor.بایاں,
            minfo.rcMonitor.چوٹی,
            minfo.rcMonitor.دایاں - minfo.rcMonitor.بایاں,
            minfo.rcMonitor.bottom - minfo.rcMonitor.چوٹی);

    SDL_free(name_utf8);
}
#اگر_ختم

bool WIN_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال)
{
    SDL_Display_ڈیٹا *displaydata = display->اندرونی_2;
    SDL_Display_منوال_ڈیٹا *ڈیٹا = (SDL_Display_منوال_ڈیٹا *)منوال->اندرونی_2;
    LONG حالت_2;

#اگر_تعریف_شدہ DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state before mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#اگر_ختم

    /* High-DPI notes:

       - ChangeDisplaySettingsEx always takes pixels.
       - e.g. if the display is set to 2880x1800 with 200% scaling in Display Settings
         - calling ChangeDisplaySettingsEx with a dmPelsWidth/Height other than 2880x1800 will
           change the monitor DPI to 96. (100% scaling)
         - calling ChangeDisplaySettingsEx with a dmPelsWidth/Height of 2880x1800 (or a NULL DEVMODE*) will
           reset the monitor DPI to 192. (200% scaling)

       NOTE: these are temporary changes in DPI, not modifications to the Control Panel setting. */
    اگر (منوال->اندرونی_2 == display->desktop_منوال.اندرونی_2) {
#اگر_تعریف_شدہ DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: resetting to original resolution");
#اگر_ختم
        حالت_2 = ChangeDisplaySettingsExW(displaydata->DeviceName, تہی, تہی, CDS_FULLSCREEN, تہی);
    } ورنہ {
#اگر_تعریف_شدہ DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: changing to %dx%d pixels", ڈیٹا->Device_منوال.dm_Pels_چوڑائی, ڈیٹا->Device_منوال.dm_Pels_اونچائی);
#اگر_ختم
        حالت_2 = ChangeDisplaySettingsExW(displaydata->DeviceName, &ڈیٹا->Device_منوال, تہی, CDS_FULLSCREEN, تہی);
    }
    اگر (حالت_2 != DISP_CHANGE_SUCCESSFUL) {
        ثابت حرف *reason = "Unknown reason";
        انتخاب (حالت_2) {
        حالت DISP_CHANGE_BADFLAGS:
            reason = "DISP_CHANGE_BADFLAGS";
            توڑو;
        حالت DISP_CHANGE_BADMODE:
            reason = "DISP_CHANGE_BADMODE";
            توڑو;
        حالت DISP_CHANGE_BADPARAM:
            reason = "DISP_CHANGE_BADPARAM";
            توڑو;
        حالت DISP_CHANGE_FAILED:
            reason = "DISP_CHANGE_FAILED";
            توڑو;
        }
        واپس SDL_سیٹ_Error("ChangeDisplaySettingsEx() failed: %s", reason);
    }

#اگر_تعریف_شدہ DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state after mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#اگر_ختم

    EnumDisplaySettingsW(displaydata->DeviceName, ENUM_CURRENT_SETTINGS, &ڈیٹا->Device_منوال);
    WIN_Update_Display_منوال(_this, displaydata->DeviceName, ENUM_CURRENT_SETTINGS, منوال);
    واپس true;
}

خالی WIN_RefreshDisplays(SDL_VideoDevice *_this)
{
    صحیح i;

    // Mark all displays as potentially invalid to detect
    // entries that have actually been removed
    برائے (i = 0; i < _this->عدد_displays; ++i) {
        SDL_Display_ڈیٹا *اندرونی_2 = _this->displays[i]->اندرونی_2;
        اندرونی_2->state = DisplayRemoved;
    }

    // Enumerate displays to add any new ones and mark still
    // connected entries as valid
    WIN_جوڑو_Displays(_this);

    // Delete any entries still marked as invalid, iterate
    // in reverse as each delete takes effect immediately
    برائے (i = _this->عدد_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_Display_ڈیٹا *اندرونی_2 = display->اندرونی_2;
        اگر (اندرونی_2->state == DisplayRemoved) {
            SDL_DelVideoDisplay(display->id, true);
        }
    }

    // Send events for any newly added displays
    برائے (i = 0; i < _this->عدد_displays; ++i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_Display_ڈیٹا *اندرونی_2 = display->اندرونی_2;
        اگر (اندرونی_2->state == DisplayAdded) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
        }
    }
}

خالی WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this)
{
    // This almost never happens, so just go ahead and send update events for all displays
    برائے (صحیح i = 0; i < _this->عدد_displays; ++i) {
        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_بدلا, 0, 0);
    }
}

خالی WIN_QuitModes(SDL_VideoDevice *_this)
{
    // All fullscreen windows should have restored modes by now
}

#اگر_ختم // SDL_VIDEO_DRIVER_WINDOWS
