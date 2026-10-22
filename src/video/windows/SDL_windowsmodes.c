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

#यदि_परिभाषितम् HAVE_DXGI1_6_H
#परिभाषय COBJMACROS
#अन्तर्भाव <dxgi1_6.h>
#यदि_अन्तः

// Windows CE compatibility
#यदि_अपरिभाषितम् CDS_FULLSCREEN
#परिभाषय CDS_FULLSCREEN 0
#यदि_अन्तः
#यदि_अपरिभाषितम् USER_DEFAULT_SCREEN_DPI
#परिभाषय USER_DEFAULT_SCREEN_DPI 96
#यदि_अन्तः

// #define DEBUG_MODES
// #define HIGHDPI_DEBUG_VERBOSE

स्थिर शून्य WIN_Update_Display_बहुलकम्(SDL_VideoDevice *_this, LPCWSTR deviceName, DWORD सूचकांक, SDL_Display_बहुलकम् *बहुलकम्)
{
    SDL_Display_बहुलकम्_दत्त *दत्त = (SDL_Display_बहुलकम्_दत्त *)बहुलकम्->आन्तरिकम्;
    HDC hdc;

    दत्त->Device_बहुलकम्.dmFields = (DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS);

    // NOLINTNEXTLINE(bugprone-assignment-in-if-condition): No simple way to extract the assignment
    यदि (सूचकांक == ENUM_CURRENT_SETTINGS && (hdc = CreateDCW(deviceName, रिक्त, रिक्त, रिक्त)) != रिक्त) {
        वर्ण bmi_दत्त[परिमाण(BITMAPINFOHEADER) + 256 * परिमाण(RGBQUAD)];
        LPBITMAPINFO bmi;
        HBITMAP hbm;

        SDL_zeroa(bmi_दत्त);
        bmi = (LPBITMAPINFO)bmi_दत्त;
        bmi->bmi_शीर्षकम्.bi_आकार = परिमाण(BITMAPINFOHEADER);

        hbm = CreateCompatibleBitmap(hdc, 1, 1);
        GetDIBits(hdc, hbm, 0, 1, रिक्त, bmi, DIB_RGB_COLORS);
        GetDIBits(hdc, hbm, 0, 1, रिक्त, bmi, DIB_RGB_COLORS);
        DeleteObject(hbm);
        DeleteDC(hdc);
        यदि (bmi->bmi_शीर्षकम्.biCompression == BI_BITFIELDS) {
            विकल्प (*(Uint32 *)bmi->bmiColors) {
            पक्ष 0x00FF0000:
                बहुलकम्->format = SDL_PIXELFORMAT_XRGB8888;
                भङ्ग;
            पक्ष 0x000000FF:
                बहुलकम्->format = SDL_PIXELFORMAT_XBGR8888;
                भङ्ग;
            पक्ष 0xF800:
                बहुलकम्->format = SDL_PIXELFORMAT_RGB565;
                भङ्ग;
            पक्ष 0x7C00:
                बहुलकम्->format = SDL_PIXELFORMAT_XRGB1555;
                भङ्ग;
            }
        } अन्यथा यदि (bmi->bmi_शीर्षकम्.biCompression == BI_RGB) {
            यदि (bmi->bmi_शीर्षकम्.bi_Bit_गणनम् == 24) {
                बहुलकम्->format = SDL_PIXELFORMAT_RGB24;
            } अन्यथा यदि (bmi->bmi_शीर्षकम्.bi_Bit_गणनम् == 8) {
                बहुलकम्->format = SDL_PIXELFORMAT_INDEX8;
            } अन्यथा यदि (bmi->bmi_शीर्षकम्.bi_Bit_गणनम् == 4) {
                बहुलकम्->format = SDL_PIXELFORMAT_INDEX4LSB;
            }
        }
    } अन्यथा यदि (बहुलकम्->format == SDL_PIXELFORMAT_UNKNOWN) {
        // FIXME: Can we tell what this will be?
        यदि ((दत्त->Device_बहुलकम्.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL) {
            विकल्प (दत्त->Device_बहुलकम्.dm_द्वयङ्काः_प्रत्येकम्_Pel) {
            पक्ष 32:
                बहुलकम्->format = SDL_PIXELFORMAT_XRGB8888;
                भङ्ग;
            पक्ष 24:
                बहुलकम्->format = SDL_PIXELFORMAT_RGB24;
                भङ्ग;
            पक्ष 16:
                बहुलकम्->format = SDL_PIXELFORMAT_RGB565;
                भङ्ग;
            पक्ष 15:
                बहुलकम्->format = SDL_PIXELFORMAT_XRGB1555;
                भङ्ग;
            पक्ष 8:
                बहुलकम्->format = SDL_PIXELFORMAT_INDEX8;
                भङ्ग;
            पक्ष 4:
                बहुलकम्->format = SDL_PIXELFORMAT_INDEX4LSB;
                भङ्ग;
            }
        }
    }
}

स्थिर शून्य *WIN_GetDXGIOutput(SDL_VideoDevice *_this, ध्रुव WCHAR *DeviceName)
{
    शून्य *परिणाम = रिक्त;

#यदि_परिभाषितम् HAVE_DXGI_H
    ध्रुव SDL_Video_दत्त *videodata = (ध्रुव SDL_Video_दत्त *)_this->आन्तरिकम्;
    पूर्णाङ्क nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    यदि (!videodata->pDXGIFactory) {
        प्रत्यागम रिक्त;
    }

    nAdapter = 0;
    यावत् (!परिणाम && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        यावत् (!परिणाम && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            यदि (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                यदि (SDL_wcscmp(outputDesc.DeviceName, DeviceName) == 0) {
                    परिणाम = pDXGIOutput;
                }
            }
            यदि (pDXGIOutput != परिणाम) {
                IDXGIOutput_Release(pDXGIOutput);
            }
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }
#यदि_अन्तः
    प्रत्यागम परिणाम;
}

स्थिर शून्य WIN_ReleaseDXGIOutput(शून्य *dxgi_output)
{
#यदि_परिभाषितम् HAVE_DXGI_H
    IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;

    यदि (pDXGIOutput) {
        IDXGIOutput_Release(pDXGIOutput);
    }
#यदि_अन्तः
}

स्थिर SDL_DisplayOrientation WIN_GetNaturalOrientation(DEVMODEW *बहुलकम्)
{
    पूर्णाङ्क विस्तारः = बहुलकम्->dm_Pels_विस्तारः;
    पूर्णाङ्क height = बहुलकम्->dmPelsHeight;

    // Use unrotated width/height to guess orientation
    यदि (बहुलकम्->dmDisplayOrientation == DMDO_90 || बहुलकम्->dmDisplayOrientation == DMDO_270) {
        पूर्णाङ्क अस्थायी = विस्तारः;
        विस्तारः = height;
        height = अस्थायी;
    }

    यदि (विस्तारः >= height) {
        प्रत्यागम SDL_ORIENTATION_LANDSCAPE;
    } अन्यथा {
        प्रत्यागम SDL_ORIENTATION_PORTRAIT;
    }
}

स्थिर SDL_DisplayOrientation WIN_GetDisplayOrientation(DEVMODEW *बहुलकम्)
{
    यदि (WIN_GetNaturalOrientation(बहुलकम्) == SDL_ORIENTATION_LANDSCAPE) {
        विकल्प (बहुलकम्->dmDisplayOrientation) {
        पक्ष DMDO_DEFAULT:
            प्रत्यागम SDL_ORIENTATION_LANDSCAPE;
        पक्ष DMDO_90:
            प्रत्यागम SDL_ORIENTATION_PORTRAIT;
        पक्ष DMDO_180:
            प्रत्यागम SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        पक्ष DMDO_270:
            प्रत्यागम SDL_ORIENTATION_PORTRAIT_FLIPPED;
        स्वभाव:
            प्रत्यागम SDL_ORIENTATION_UNKNOWN;
        }
    } अन्यथा {
        विकल्प (बहुलकम्->dmDisplayOrientation) {
        पक्ष DMDO_DEFAULT:
            प्रत्यागम SDL_ORIENTATION_PORTRAIT;
        पक्ष DMDO_90:
            प्रत्यागम SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        पक्ष DMDO_180:
            प्रत्यागम SDL_ORIENTATION_PORTRAIT_FLIPPED;
        पक्ष DMDO_270:
            प्रत्यागम SDL_ORIENTATION_LANDSCAPE;
        स्वभाव:
            प्रत्यागम SDL_ORIENTATION_UNKNOWN;
        }
    }
}

स्थिर शून्य WIN_Get_Refresh_दरः(शून्य *dxgi_output, DEVMODEW *बहुलकम्, पूर्णाङ्क *numerator, पूर्णाङ्क *denominator)
{
    // We're not currently using DXGI to query display modes, so fake NTSC timings
    विकल्प (बहुलकम्->dmDisplayFrequency) {
    पक्ष 119:
    पक्ष 59:
    पक्ष 29:
        *numerator = (बहुलकम्->dmDisplayFrequency + 1) * 1000;
        *denominator = 1001;
        भङ्ग;
    स्वभाव:
        *numerator = बहुलकम्->dmDisplayFrequency;
        *denominator = 1;
        भङ्ग;
    }

#यदि_परिभाषितम् HAVE_DXGI_H
    यदि (dxgi_output) {
        IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;
        DXGI_बहुलकम्_DESC बहुलकम्_गन्तव्यम्_मेलनम्;
        DXGI_बहुलकम्_DESC closest_मेलनम्;

        SDL_zero(बहुलकम्_गन्तव्यम्_मेलनम्);
        बहुलकम्_गन्तव्यम्_मेलनम्.विस्तारः_2 = बहुलकम्->dm_Pels_विस्तारः;
        बहुलकम्_गन्तव्यम्_मेलनम्.Height = बहुलकम्->dmPelsHeight;
        बहुलकम्_गन्तव्यम्_मेलनम्.Refresh_दरः.Numerator = *numerator;
        बहुलकम्_गन्तव्यम्_मेलनम्.Refresh_दरः.Denominator = *denominator;
        बहुलकम्_गन्तव्यम्_मेलनम्.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        यदि (SUCCEEDED(IDXGIOutput_Find_Closest_Matching_बहुलकम्(pDXGIOutput, &बहुलकम्_गन्तव्यम्_मेलनम्, &closest_मेलनम्, रिक्त))) {
            *numerator = closest_मेलनम्.Refresh_दरः.Numerator;
            *denominator = closest_मेलनम्.Refresh_दरः.Denominator;
        }
    }
#यदि_अन्तः // HAVE_DXGI_H
}

स्थिर भिन्न WIN_GetContentScale(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    पूर्णाङ्क dpi = 0;

    ध्रुव SDL_Video_दत्त *videodata = (ध्रुव SDL_Video_दत्त *)_this->आन्तरिकम्;
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
    प्रत्यागम dpi / (भिन्न)USER_DEFAULT_SCREEN_DPI;
}

स्थिर bool WIN_Get_Display_बहुलकम्(SDL_VideoDevice *_this, शून्य *dxgi_output, HMONITOR hMonitor, LPCWSTR deviceName, DWORD सूचकांक, SDL_Display_बहुलकम् *बहुलकम्, SDL_DisplayOrientation *natural_orientation, SDL_DisplayOrientation *current_orientation)
{
    SDL_Display_बहुलकम्_दत्त *दत्त;
    DEVMODEW devmode;

    devmode.dm_आकार = परिमाण(devmode);
    devmode.dmDriverExtra = 0;
    यदि (!EnumDisplaySettingsW(deviceName, सूचकांक, &devmode)) {
        प्रत्यागम false;
    }

    दत्त = (SDL_Display_बहुलकम्_दत्त *)SDL_malloc(परिमाण(*दत्त));
    यदि (!दत्त) {
        प्रत्यागम false;
    }

    SDL_zerop(बहुलकम्);
    बहुलकम्->आन्तरिकम् = दत्त;
    दत्त->Device_बहुलकम् = devmode;

    बहुलकम्->format = SDL_PIXELFORMAT_UNKNOWN;
    बहुलकम्->w = दत्त->Device_बहुलकम्.dm_Pels_विस्तारः;
    बहुलकम्->h = दत्त->Device_बहुलकम्.dmPelsHeight;
    WIN_Get_Refresh_दरः(dxgi_output, &दत्त->Device_बहुलकम्, &बहुलकम्->refresh_दरः_numerator, &बहुलकम्->refresh_दरः_denominator);

    // Fill in the mode information
    WIN_Update_Display_बहुलकम्(_this, deviceName, सूचकांक, बहुलकम्);

    यदि (natural_orientation) {
        *natural_orientation = WIN_GetNaturalOrientation(&devmode);
    }
    यदि (current_orientation) {
        *current_orientation = WIN_GetDisplayOrientation(&devmode);
    }

    प्रत्यागम true;
}

स्थिर वर्ण *WIN_GetDisplayNameVista(SDL_Video_दत्त *videodata, ध्रुव WCHAR *deviceName)
{
    DISPLAYCONFIG_मार्गः_INFO *paths = रिक्त;
    DISPLAYCONFIG_बहुलकम्_INFO *modes = रिक्त;
    वर्ण *परिणाम = रिक्त;
    UINT32 मार्गः_गणनम्_2 = 0;
    UINT32 बहुलकम्_गणनम्_2 = 0;
    UINT32 i;
    LONG rc;

    यदि (!videodata->Get_Display_Config_बफर_Sizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        प्रत्यागम रिक्त;
    }

    कुरु {
        rc = videodata->Get_Display_Config_बफर_Sizes(QDC_ONLY_सक्रिय_PATHS, &मार्गः_गणनम्_2, &बहुलकम्_गणनम्_2);
        यदि (rc != ERROR_SUCCESS) {
            गच्छ WIN_GetDisplayNameVista_failed;
        }

        SDL_free(paths);
        SDL_free(modes);

        paths = (DISPLAYCONFIG_मार्गः_INFO *)SDL_malloc(परिमाण(DISPLAYCONFIG_मार्गः_INFO) * मार्गः_गणनम्_2);
        modes = (DISPLAYCONFIG_बहुलकम्_INFO *)SDL_malloc(परिमाण(DISPLAYCONFIG_बहुलकम्_INFO) * बहुलकम्_गणनम्_2);
        यदि ((!paths) || (!modes)) {
            गच्छ WIN_GetDisplayNameVista_failed;
        }

        rc = videodata->QueryDisplayConfig(QDC_ONLY_सक्रिय_PATHS, &मार्गः_गणनम्_2, paths, &बहुलकम्_गणनम्_2, modes, 0);
    } यावत् (rc == ERROR_INSUFFICIENT_बफर);

    यदि (rc == ERROR_SUCCESS) {
        प्रति (i = 0; i < मार्गः_गणनम्_2; i++) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME sourceName;
            DISPLAYCONFIG_TARGET_DEVICE_NAME targetName;

            SDL_zero(sourceName);
            sourceName.शीर्षकम्.adapterId = paths[i].targetInfo.adapterId;
            sourceName.शीर्षकम्.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            sourceName.शीर्षकम्.आकार = परिमाण(sourceName);
            sourceName.शीर्षकम्.id = paths[i].sourceInfo.id;
            rc = videodata->DisplayConfigGetDeviceInfo(&sourceName.शीर्षकम्);
            यदि (rc != ERROR_SUCCESS) {
                भङ्ग;
            } अन्यथा यदि (SDL_wcscmp(deviceName, sourceName.viewGdiDeviceName) != 0) {
                अनुवर्त;
            }

            SDL_zero(targetName);
            targetName.शीर्षकम्.adapterId = paths[i].targetInfo.adapterId;
            targetName.शीर्षकम्.id = paths[i].targetInfo.id;
            targetName.शीर्षकम्.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
            targetName.शीर्षकम्.आकार = परिमाण(targetName);
            rc = videodata->DisplayConfigGetDeviceInfo(&targetName.शीर्षकम्);
            यदि (rc == ERROR_SUCCESS) {
                परिणाम = WIN_String_गन्तव्यम्_UTF8_W(targetName.monitorFriendlyDeviceName);
                /* if we got an empty string, treat it as failure so we'll fallback
                   to getting the generic name. */
                यदि (परिणाम && (*परिणाम == '\0')) {
                    SDL_free(परिणाम);
                    परिणाम = रिक्त;
                }
            }
            भङ्ग;
        }
    }

    SDL_free(paths);
    SDL_free(modes);
    प्रत्यागम परिणाम;

WIN_GetDisplayNameVista_failed:
    SDL_free(परिणाम);
    SDL_free(paths);
    SDL_free(modes);
    प्रत्यागम रिक्त;
}

#यदि_परिभाषितम् HAVE_DXGI1_6_H
स्थिर bool WIN_GetMonitorDESC1(HMONITOR hMonitor, DXGI_OUTPUT_DESC1 *desc)
{
    प्रकारनिर्देश HRESULT (WINAPI *pfnCreateDXGIFactory1)(REFIID riid, शून्य **ppFactory);
    pfnCreateDXGIFactory1 pCreateDXGIFactory1 = रिक्त;
    SDL_SharedObject *hDXGIMod = रिक्त;
    bool प्राप्तम् = false;

    hDXGIMod = SDL_आरोपय_Object("dxgi.dll");
    यदि (hDXGIMod) {
        pCreateDXGIFactory1 = (pfnCreateDXGIFactory1)SDL_आरोपय_Function(hDXGIMod, "CreateDXGIFactory1");
    }
    यदि (pCreateDXGIFactory1) {
        स्थिर ध्रुव GUID SDL_IID_IDXGIFactory1 = { 0x770aae78, 0xf26f, 0x4dba, { 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 } };
        स्थिर ध्रुव GUID SDL_IID_IDXGIOutput6 = { 0x068346e8, 0xaaec, 0x4b84, { 0xad, 0xd7, 0x13, 0x7f, 0x51, 0x3f, 0x77, 0xa1 } };
        IDXGIFactory1 *dxgiFactory;

        यदि (SUCCEEDED(pCreateDXGIFactory1(&SDL_IID_IDXGIFactory1, (शून्य **)&dxgiFactory))) {
            IDXGIAdapter1 *dxgiAdapter;
            UINT adapter = 0;
            यावत् (!प्राप्तम् && SUCCEEDED(IDXGIFactory1_EnumAdapters1(dxgiFactory, adapter, &dxgiAdapter))) {
                IDXGIOutput *dxgiOutput;
                UINT output = 0;
                यावत् (!प्राप्तम् && SUCCEEDED(IDXGIAdapter1_EnumOutputs(dxgiAdapter, output, &dxgiOutput))) {
                    IDXGIOutput6 *dxgiOutput6;
                    यदि (SUCCEEDED(IDXGIOutput_QueryInterface(dxgiOutput, &SDL_IID_IDXGIOutput6, (शून्य **)&dxgiOutput6))) {
                        यदि (SUCCEEDED(IDXGIOutput6_GetDesc1(dxgiOutput6, desc))) {
                            यदि (desc->Monitor == hMonitor) {
                                प्राप्तम् = true;
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
    प्रत्यागम प्राप्तम्;
}

स्थिर bool WIN_Get_Monitor_मार्गः_Info(SDL_Video_दत्त *videodata, HMONITOR hMonitor, DISPLAYCONFIG_मार्गः_INFO *मार्गः_info)
{
    LONG परिणाम;
    MONITORINFOEXW view_info;
    UINT32 i;
    UINT32 अङ्कः_मार्गः_array_elements = 0;
    UINT32 अङ्कः_बहुलकम्_info_array_elements = 0;
    DISPLAYCONFIG_मार्गः_INFO *मार्गः_infos = रिक्त, *new_मार्गः_infos;
    DISPLAYCONFIG_बहुलकम्_INFO *बहुलकम्_infos = रिक्त, *new_बहुलकम्_infos;
    bool प्राप्तम् = false;

    यदि (!videodata->Get_Display_Config_बफर_Sizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        प्रत्यागम false;
    }

    SDL_zero(view_info);
    view_info.cb_आकार = परिमाण(view_info);
    यदि (!GetMonitorInfoW(hMonitor, (MONITORINFO *)&view_info)) {
        गच्छ समाप्तम्;
    }

    कुरु {
        यदि (videodata->Get_Display_Config_बफर_Sizes(QDC_ONLY_सक्रिय_PATHS, &अङ्कः_मार्गः_array_elements, &अङ्कः_बहुलकम्_info_array_elements) != ERROR_SUCCESS) {
            SDL_free(मार्गः_infos);
            SDL_free(बहुलकम्_infos);
            प्रत्यागम false;
        }

        new_मार्गः_infos = (DISPLAYCONFIG_मार्गः_INFO *)SDL_realloc(मार्गः_infos, अङ्कः_मार्गः_array_elements * परिमाण(*मार्गः_infos));
        यदि (!new_मार्गः_infos) {
            गच्छ समाप्तम्;
        }
        मार्गः_infos = new_मार्गः_infos;

        new_बहुलकम्_infos = (DISPLAYCONFIG_बहुलकम्_INFO *)SDL_realloc(बहुलकम्_infos, अङ्कः_बहुलकम्_info_array_elements * परिमाण(*बहुलकम्_infos));
        यदि (!new_बहुलकम्_infos) {
            गच्छ समाप्तम्;
        }
        बहुलकम्_infos = new_बहुलकम्_infos;

        परिणाम = videodata->QueryDisplayConfig(QDC_ONLY_सक्रिय_PATHS, &अङ्कः_मार्गः_array_elements, मार्गः_infos, &अङ्कः_बहुलकम्_info_array_elements, बहुलकम्_infos, रिक्त);

    } यावत् (परिणाम == ERROR_INSUFFICIENT_बफर);

    यदि (परिणाम == ERROR_SUCCESS) {
        प्रति (i = 0; i < अङ्कः_मार्गः_array_elements; ++i) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME device_name;

            SDL_zero(device_name);
            device_name.शीर्षकम्.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            device_name.शीर्षकम्.आकार = परिमाण(device_name);
            device_name.शीर्षकम्.adapterId = मार्गः_infos[i].sourceInfo.adapterId;
            device_name.शीर्षकम्.id = मार्गः_infos[i].sourceInfo.id;
            यदि (videodata->DisplayConfigGetDeviceInfo(&device_name.शीर्षकम्) == ERROR_SUCCESS) {
                यदि (SDL_wcscmp(view_info.szDevice, device_name.viewGdiDeviceName) == 0) {
                    SDL_copyp(मार्गः_info, &मार्गः_infos[i]);
                    प्राप्तम् = true;
                    भङ्ग;
                }
            }
        }
    }

समाप्तम्:
    SDL_free(मार्गः_infos);
    SDL_free(बहुलकम्_infos);

    प्रत्यागम प्राप्तम्;
}

स्थिर भिन्न WIN_GetSDRWhitePoint(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    DISPLAYCONFIG_मार्गः_INFO मार्गः_info;
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    भिन्न SDR_white_level = 1.0f;

    यदि (WIN_Get_Monitor_मार्गः_Info(videodata, hMonitor, &मार्गः_info)) {
        /* workarounds for https://github.com/libsdl-org/SDL/issues/11193 */
        संरचना SDL_DISPLAYCONFIG_SDR_WHITE_LEVEL {
          DISPLAYCONFIG_DEVICE_INFO_शीर्षकम् शीर्षकम्;
          ULONG SDRWhiteLevel;
        } white_level;
        #परिभाषय DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL 11

        SDL_zero(white_level);
        white_level.शीर्षकम्.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
        white_level.शीर्षकम्.आकार = परिमाण(white_level);
        white_level.शीर्षकम्.adapterId = मार्गः_info.targetInfo.adapterId;
        white_level.शीर्षकम्.id = मार्गः_info.targetInfo.id;
        // WIN_GetMonitorPathInfo() succeeded: DisplayConfigGetDeviceInfo is not NULL
        यदि (videodata->DisplayConfigGetDeviceInfo(&white_level.शीर्षकम्) == ERROR_SUCCESS &&
            white_level.SDRWhiteLevel > 0) {
            SDR_white_level = (white_level.SDRWhiteLevel / 1000.0f);
        }
    }
    प्रत्यागम SDR_white_level;
}

स्थिर शून्य WIN_GetHDRProperties(SDL_VideoDevice *_this, HMONITOR hMonitor, SDL_HDROutputProperties *HDR)
{
    DXGI_OUTPUT_DESC1 desc;

    SDL_zerop(HDR);

    यदि (WIN_GetMonitorDESC1(hMonitor, &desc)) {
        यदि (desc.ColorSpace == DXGI_COLOR_SPACE_RGB_पूर्णम्_G2084_NONE_P2020) {
            HDR->SDR_white_level = WIN_GetSDRWhitePoint(_this, hMonitor);
            HDR->HDR_headroom = (desc.MaxLuminance / SCRGB_NITS) / HDR->SDR_white_level;
        }
    }
}
#यदि_अन्तः // HAVE_DXGI1_6_H

स्थिर शून्य WIN_सङ्कलय_Display(SDL_VideoDevice *_this, HMONITOR hMonitor, ध्रुव MONITORINFOEXW *info, पूर्णाङ्क *display_सूचकांक)
{
    पूर्णाङ्क i, सूचकांक = *display_सूचकांक;
    SDL_VideoDisplay display;
    SDL_Display_दत्त *displaydata;
    शून्य *dxgi_output = रिक्त;
    SDL_Display_बहुलकम् बहुलकम्;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    भिन्न content_scale = WIN_GetContentScale(_this, hMonitor);

#यदि_परिभाषितम् DEBUG_MODES
    SDL_Log("Display: %s", WIN_String_गन्तव्यम्_UTF8_W(info->szDevice));
#यदि_अन्तः

    dxgi_output = WIN_GetDXGIOutput(_this, info->szDevice);
    bool प्राप्तम् = WIN_Get_Display_बहुलकम्(_this, dxgi_output, hMonitor, info->szDevice, ENUM_CURRENT_SETTINGS, &बहुलकम्, &natural_orientation, &current_orientation);
    WIN_ReleaseDXGIOutput(dxgi_output);
    यदि (!प्राप्तम्) {
        प्रत्यागम;
    }

    // Prevent adding duplicate displays. Do this after we know the display is
    // ready to be added to allow any displays that we can't fully query to be
    // removed
    प्रति (i = 0; i < _this->अङ्कः_displays; ++i) {
        SDL_Display_दत्त *आन्तरिकम् = _this->displays[i]->आन्तरिकम्;
        यदि (SDL_wcscmp(आन्तरिकम्->DeviceName, info->szDevice) == 0) {
            bool moved = (सूचकांक != i);
            bool परिवर्तितम्_bounds = false;

            यदि (आन्तरिकम्->state != DisplayRemoved) {
                // We've already enumerated this display, don't move it
                गच्छ cleanup;
            }

            यदि (सूचकांक >= _this->अङ्कः_displays) {
                // This should never happen due to the check above, but just in case...
                गच्छ cleanup;
            }

            यदि (moved) {
                SDL_VideoDisplay *tmp;

                tmp = _this->displays[सूचकांक];
                _this->displays[सूचकांक] = _this->displays[i];
                _this->displays[i] = tmp;
                i = सूचकांक;
            }

            आन्तरिकम्->MonitorHandle = hMonitor;
            आन्तरिकम्->state = DisplayUnchanged;

            SDL_PropertiesID props = SDL_GetDisplayProperties(_this->displays[i]->id);
            SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_POINTER, hMonitor);

            यदि (!_this->setting_display_बहुलकम्) {
                SDL_VideoDisplay *existing_display = _this->displays[i];
                SDL_Rect bounds;

                SDL_ResetFullscreenDisplayModes(existing_display);
                SDL_समुच्चयः_Desktop_Display_बहुलकम्(existing_display, &बहुलकम्);
                // The mode is owned by the video subsystem
                बहुलकम्.आन्तरिकम् = रिक्त;
                यदि (WIN_GetDisplayBounds(_this, existing_display, &bounds) &&
                    SDL_memcmp(&आन्तरिकम्->bounds, &bounds, परिमाण(bounds)) != 0) {
                    परिवर्तितम्_bounds = true;
                    SDL_copyp(&आन्तरिकम्->bounds, &bounds);
                }
                यदि (moved || परिवर्तितम्_bounds) {
                    SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_MOVED, 0, 0);
                }
                SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_ORIENTATION, current_orientation, 0);
                SDL_समुच्चयः_Display_Content_Scale(existing_display, content_scale);
#यदि_परिभाषितम् HAVE_DXGI1_6_H
                SDL_HDROutputProperties HDR;
                WIN_GetHDRProperties(_this, hMonitor, &HDR);
                SDL_समुच्चयः_Display_HDRProperties(existing_display, &HDR);
#यदि_अन्तः
            }
            गच्छ समाप्तम्;
        }
    }

    displaydata = (SDL_Display_दत्त *)SDL_calloc(1, परिमाण(*displaydata));
    यदि (!displaydata) {
        गच्छ cleanup;
    }
    SDL_memcpy(displaydata->DeviceName, info->szDevice, परिमाण(displaydata->DeviceName));
    displaydata->MonitorHandle = hMonitor;
    displaydata->state = DisplayAdded;

    SDL_zero(display);
    display.name = WIN_GetDisplayNameVista(_this->आन्तरिकम्, info->szDevice);
    यदि (!display.name) {
        DISPLAY_DEVICEW device;
        SDL_zero(device);
        device.cb = परिमाण(device);
        यदि (EnumDisplayDevicesW(info->szDevice, 0, &device, 0)) {
            display.name = WIN_String_गन्तव्यम्_UTF8_W(device.DeviceString);
        }
    }

    display.desktop_बहुलकम् = बहुलकम्;
    display.natural_orientation = natural_orientation;
    display.current_orientation = current_orientation;
    display.content_scale = content_scale;
    display.device = _this;
    display.आन्तरिकम् = displaydata;
    WIN_GetDisplayBounds(_this, &display, &displaydata->bounds);
#यदि_परिभाषितम् HAVE_DXGI1_6_H
    WIN_GetHDRProperties(_this, hMonitor, &display.HDR);
#यदि_अन्तः
    SDL_DisplayID displayID = SDL_सङ्कलय_Video_Display(&display, false);
    यदि (displayID) {
        // The mode is owned by the video subsystem
        बहुलकम्.आन्तरिकम् = रिक्त;

        SDL_PropertiesID props = SDL_GetDisplayProperties(displayID);
        SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_POINTER, hMonitor);
    } अन्यथा {
        SDL_free(displaydata);
    }
    SDL_free(display.name);

समाप्तम्:
    *display_सूचकांक += 1;

cleanup:
    SDL_free(बहुलकम्.आन्तरिकम्);
}

प्रकारनिर्देश संरचना WIN_सङ्कलय_Displays_दत्त
{
    SDL_VideoDevice *video_device;
    पूर्णाङ्क display_सूचकांक;
    bool want_primary;
} WIN_सङ्कलय_Displays_दत्त_2;

स्थिर BOOL CALLBACK WIN_सङ्कलय_Displays_Callback(HMONITOR hMonitor,
                                             HDC hdcMonitor,
                                             LPRECT lprcMonitor,
                                             LPARAM dw_दत्त)
{
    WIN_सङ्कलय_Displays_दत्त_2 *दत्त = (WIN_सङ्कलय_Displays_दत्त_2 *)dw_दत्त;
    MONITORINFOEXW info;

    SDL_zero(info);
    info.cb_आकार = परिमाण(info);

    यदि (GetMonitorInfoW(hMonitor, (LPMONITORINFO)&info) != 0) {
        ध्रुव bool is_primary = ((info.dwFlags & MONITORINFOF_PRIMARY) == MONITORINFOF_PRIMARY);

        यदि (is_primary == दत्त->want_primary) {
            WIN_सङ्कलय_Display(दत्त->video_device, hMonitor, &info, &दत्त->display_सूचकांक);
        }
    }

    // continue enumeration
    प्रत्यागम TRUE;
}

स्थिर शून्य WIN_सङ्कलय_Displays(SDL_VideoDevice *_this)
{
    WIN_सङ्कलय_Displays_दत्त_2 callback_दत्त;
    callback_दत्त.video_device = _this;
    callback_दत्त.display_सूचकांक = 0;

    callback_दत्त.want_primary = true;
    EnumDisplayMonitors(रिक्त, रिक्त, WIN_सङ्कलय_Displays_Callback, (LPARAM)&callback_दत्त);

    callback_दत्त.want_primary = false;
    EnumDisplayMonitors(रिक्त, रिक्त, WIN_सङ्कलय_Displays_Callback, (LPARAM)&callback_दत्त);
}

bool WIN_InitModes(SDL_VideoDevice *_this)
{
    WIN_सङ्कलय_Displays(_this);

    यदि (_this->अङ्कः_displays == 0) {
        प्रत्यागम SDL_समुच्चयः_Error("No displays available");
    }
    प्रत्यागम true;
}

bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ध्रुव SDL_Display_दत्त *दत्त = display->आन्तरिकम्;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cb_आकार = परिमाण(MONITORINFO);
    rc = GetMonitorInfo(दत्त->MonitorHandle, &minfo);

    यदि (!rc) {
        प्रत्यागम SDL_समुच्चयः_Error("Couldn't find monitor data");
    }

    rect->x = minfo.rcMonitor.वामः;
    rect->y = minfo.rcMonitor.शिखरम्;
    rect->w = minfo.rcMonitor.दक्षिणः - minfo.rcMonitor.वामः;
    rect->h = minfo.rcMonitor.bottom - minfo.rcMonitor.शिखरम्;

    प्रत्यागम true;
}

bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ध्रुव SDL_Display_दत्त *दत्त = display->आन्तरिकम्;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cb_आकार = परिमाण(MONITORINFO);
    rc = GetMonitorInfo(दत्त->MonitorHandle, &minfo);

    यदि (!rc) {
        प्रत्यागम SDL_समुच्चयः_Error("Couldn't find monitor data");
    }

    rect->x = minfo.rcWork.वामः;
    rect->y = minfo.rcWork.शिखरम्;
    rect->w = minfo.rcWork.दक्षिणः - minfo.rcWork.वामः;
    rect->h = minfo.rcWork.bottom - minfo.rcWork.शिखरम्;

    प्रत्यागम true;
}

bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_दत्त *दत्त = display->आन्तरिकम्;
    शून्य *dxgi_output;
    DWORD i;
    SDL_Display_बहुलकम् बहुलकम्;

    dxgi_output = WIN_GetDXGIOutput(_this, दत्त->DeviceName);

    // Make sure we add the current mode to the list in case it's a custom mode that doesn't enumerate
    प्रति (i = ENUM_CURRENT_SETTINGS; ; ++i) {
        यदि (!WIN_Get_Display_बहुलकम्(_this, dxgi_output, दत्त->MonitorHandle, दत्त->DeviceName, i, &बहुलकम्, रिक्त, रिक्त)) {
            भङ्ग;
        }
        यदि (SDL_ISPIXELFORMAT_अनुक्रमितम्(बहुलकम्.format)) {
            // We don't support palettized modes now
            SDL_free(बहुलकम्.आन्तरिकम्);
            अनुवर्त;
        }
        यदि (बहुलकम्.format != SDL_PIXELFORMAT_UNKNOWN) {
            यदि (!SDL_सङ्कलय_Fullscreen_Display_बहुलकम्(display, &बहुलकम्)) {
                SDL_free(बहुलकम्.आन्तरिकम्);
            }
        } अन्यथा {
            SDL_free(बहुलकम्.आन्तरिकम्);
        }
    }

    WIN_ReleaseDXGIOutput(dxgi_output);

    प्रत्यागम true;
}

#यदि_परिभाषितम् DEBUG_MODES
स्थिर शून्य WIN_LogMonitor(SDL_VideoDevice *_this, HMONITOR mon)
{
    ध्रुव SDL_Video_दत्त *vid_दत्त = (ध्रुव SDL_Video_दत्त *)_this->आन्तरिकम्;
    MONITORINFOEX minfo;
    UINT xdpi = 0, ydpi = 0;
    वर्ण *name_utf8;

    यदि (vid_दत्त->GetDpiForMonitor) {
        vid_दत्त->GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &xdpi, &ydpi);
    }

    SDL_zero(minfo);
    minfo.cb_आकार = परिमाण(minfo);
    GetMonitorInfo(mon, (LPMONITORINFO)&minfo);

    name_utf8 = WIN_String_गन्तव्यम्_UTF8(minfo.szDevice);

    SDL_Log("WIN_LogMonitor: monitor \"%s\": dpi: %d windows screen coordinates: %d, %d, %dx%d",
            name_utf8,
            xdpi,
            minfo.rcMonitor.वामः,
            minfo.rcMonitor.शिखरम्,
            minfo.rcMonitor.दक्षिणः - minfo.rcMonitor.वामः,
            minfo.rcMonitor.bottom - minfo.rcMonitor.शिखरम्);

    SDL_free(name_utf8);
}
#यदि_अन्तः

bool WIN_समुच्चयः_Display_बहुलकम्(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_बहुलकम् *बहुलकम्)
{
    SDL_Display_दत्त *displaydata = display->आन्तरिकम्;
    SDL_Display_बहुलकम्_दत्त *दत्त = (SDL_Display_बहुलकम्_दत्त *)बहुलकम्->आन्तरिकम्;
    LONG स्थितिः;

#यदि_परिभाषितम् DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state before mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#यदि_अन्तः

    /* High-DPI notes:

       - ChangeDisplaySettingsEx always takes pixels.
       - e.g. if the display is set to 2880x1800 with 200% scaling in Display Settings
         - calling ChangeDisplaySettingsEx with a dmPelsWidth/Height other than 2880x1800 will
           change the monitor DPI to 96. (100% scaling)
         - calling ChangeDisplaySettingsEx with a dmPelsWidth/Height of 2880x1800 (or a NULL DEVMODE*) will
           reset the monitor DPI to 192. (200% scaling)

       NOTE: these are temporary changes in DPI, not modifications to the Control Panel setting. */
    यदि (बहुलकम्->आन्तरिकम् == display->desktop_बहुलकम्.आन्तरिकम्) {
#यदि_परिभाषितम् DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: resetting to original resolution");
#यदि_अन्तः
        स्थितिः = ChangeDisplaySettingsExW(displaydata->DeviceName, रिक्त, रिक्त, CDS_FULLSCREEN, रिक्त);
    } अन्यथा {
#यदि_परिभाषितम् DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: changing to %dx%d pixels", दत्त->Device_बहुलकम्.dm_Pels_विस्तारः, दत्त->Device_बहुलकम्.dmPelsHeight);
#यदि_अन्तः
        स्थितिः = ChangeDisplaySettingsExW(displaydata->DeviceName, &दत्त->Device_बहुलकम्, रिक्त, CDS_FULLSCREEN, रिक्त);
    }
    यदि (स्थितिः != DISP_CHANGE_SUCCESSFUL) {
        ध्रुव वर्ण *reason = "Unknown reason";
        विकल्प (स्थितिः) {
        पक्ष DISP_CHANGE_BADFLAGS:
            reason = "DISP_CHANGE_BADFLAGS";
            भङ्ग;
        पक्ष DISP_CHANGE_BADMODE:
            reason = "DISP_CHANGE_BADMODE";
            भङ्ग;
        पक्ष DISP_CHANGE_BADPARAM:
            reason = "DISP_CHANGE_BADPARAM";
            भङ्ग;
        पक्ष DISP_CHANGE_FAILED:
            reason = "DISP_CHANGE_FAILED";
            भङ्ग;
        }
        प्रत्यागम SDL_समुच्चयः_Error("ChangeDisplaySettingsEx() failed: %s", reason);
    }

#यदि_परिभाषितम् DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state after mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#यदि_अन्तः

    EnumDisplaySettingsW(displaydata->DeviceName, ENUM_CURRENT_SETTINGS, &दत्त->Device_बहुलकम्);
    WIN_Update_Display_बहुलकम्(_this, displaydata->DeviceName, ENUM_CURRENT_SETTINGS, बहुलकम्);
    प्रत्यागम true;
}

शून्य WIN_RefreshDisplays(SDL_VideoDevice *_this)
{
    पूर्णाङ्क i;

    // Mark all displays as potentially invalid to detect
    // entries that have actually been removed
    प्रति (i = 0; i < _this->अङ्कः_displays; ++i) {
        SDL_Display_दत्त *आन्तरिकम् = _this->displays[i]->आन्तरिकम्;
        आन्तरिकम्->state = DisplayRemoved;
    }

    // Enumerate displays to add any new ones and mark still
    // connected entries as valid
    WIN_सङ्कलय_Displays(_this);

    // Delete any entries still marked as invalid, iterate
    // in reverse as each delete takes effect immediately
    प्रति (i = _this->अङ्कः_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_Display_दत्त *आन्तरिकम् = display->आन्तरिकम्;
        यदि (आन्तरिकम्->state == DisplayRemoved) {
            SDL_DelVideoDisplay(display->id, true);
        }
    }

    // Send events for any newly added displays
    प्रति (i = 0; i < _this->अङ्कः_displays; ++i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_Display_दत्त *आन्तरिकम् = display->आन्तरिकम्;
        यदि (आन्तरिकम्->state == DisplayAdded) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
        }
    }
}

शून्य WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this)
{
    // This almost never happens, so just go ahead and send update events for all displays
    प्रति (पूर्णाङ्क i = 0; i < _this->अङ्कः_displays; ++i) {
        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_परिवर्तितम्, 0, 0);
    }
}

शून्य WIN_QuitModes(SDL_VideoDevice *_this)
{
    // All fullscreen windows should have restored modes by now
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_WINDOWS
