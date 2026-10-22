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
#అన్తర్భావ "SDL_internal.h"

#ఒకవేళ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#అన్తర్భావ "SDL_windowsvideo.h"
#అన్తర్భావ "../../events/SDL_displayevents_c.h"
#అన్తర్భావ "../SDL_pixels_c.h"

#నిర్వచితమైతే HAVE_DXGI1_6_H
#నిర్వచించు COBJMACROS
#అన్తర్భావ <dxgi1_6.h>
#అయితే_ముగింపు

// Windows CE compatibility
#నిర్వచితం_కాకపోతే CDS_FULLSCREEN
#నిర్వచించు CDS_FULLSCREEN 0
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే USER_DEFAULT_SCREEN_DPI
#నిర్వచించు USER_DEFAULT_SCREEN_DPI 96
#అయితే_ముగింపు

// #define DEBUG_MODES
// #define HIGHDPI_DEBUG_VERBOSE

స్థిర శూన్య WIN_Update_Display_బహుళకం(SDL_VideoDevice *_this, LPCWSTR deviceName, DWORD సూచీ, SDL_Display_బహుళకం *బహుళకం)
{
    SDL_Display_బహుళకం_దత్తాంశం *దత్తాంశం = (SDL_Display_బహుళకం_దత్తాంశం *)బహుళకం->అంతర్గత;
    HDC hdc;

    దత్తాంశం->Device_బహుళకం.dmFields = (DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS);

    // NOLINTNEXTLINE(bugprone-assignment-in-if-condition): No simple way to extract the assignment
    ఒకవేళ (సూచీ == ENUM_CURRENT_SETTINGS && (hdc = CreateDCW(deviceName, ఖాళీ, ఖాళీ, ఖాళీ)) != ఖాళీ) {
        అక్షరం bmi_దత్తాంశం[పరిమాణం(BITMAPINFOHEADER) + 256 * పరిమాణం(RGBQUAD)];
        LPBITMAPINFO bmi;
        HBITMAP hbm;

        SDL_zeroa(bmi_దత్తాంశం);
        bmi = (LPBITMAPINFO)bmi_దత్తాంశం;
        bmi->bmi_శీర్షిక.bi_కొలత = పరిమాణం(BITMAPINFOHEADER);

        hbm = CreateCompatibleBitmap(hdc, 1, 1);
        GetDIBits(hdc, hbm, 0, 1, ఖాళీ, bmi, DIB_RGB_COLORS);
        GetDIBits(hdc, hbm, 0, 1, ఖాళీ, bmi, DIB_RGB_COLORS);
        DeleteObject(hbm);
        DeleteDC(hdc);
        ఒకవేళ (bmi->bmi_శీర్షిక.biCompression == BI_BITFIELDS) {
            ఎంపిక (*(Uint32 *)bmi->bmiColors) {
            స్థితి 0x00FF0000:
                బహుళకం->format = SDL_PIXELFORMAT_XRGB8888;
                ఆపు;
            స్థితి 0x000000FF:
                బహుళకం->format = SDL_PIXELFORMAT_XBGR8888;
                ఆపు;
            స్థితి 0xF800:
                బహుళకం->format = SDL_PIXELFORMAT_RGB565;
                ఆపు;
            స్థితి 0x7C00:
                బహుళకం->format = SDL_PIXELFORMAT_XRGB1555;
                ఆపు;
            }
        } లేకపోతే ఒకవేళ (bmi->bmi_శీర్షిక.biCompression == BI_RGB) {
            ఒకవేళ (bmi->bmi_శీర్షిక.bi_బిట్టు_లెక్క == 24) {
                బహుళకం->format = SDL_PIXELFORMAT_RGB24;
            } లేకపోతే ఒకవేళ (bmi->bmi_శీర్షిక.bi_బిట్టు_లెక్క == 8) {
                బహుళకం->format = SDL_PIXELFORMAT_INDEX8;
            } లేకపోతే ఒకవేళ (bmi->bmi_శీర్షిక.bi_బిట్టు_లెక్క == 4) {
                బహుళకం->format = SDL_PIXELFORMAT_INDEX4LSB;
            }
        }
    } లేకపోతే ఒకవేళ (బహుళకం->format == SDL_PIXELFORMAT_UNKNOWN) {
        // FIXME: Can we tell what this will be?
        ఒకవేళ ((దత్తాంశం->Device_బహుళకం.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL) {
            ఎంపిక (దత్తాంశం->Device_బహుళకం.dm_బిట్లు_చొప్పున_Pel) {
            స్థితి 32:
                బహుళకం->format = SDL_PIXELFORMAT_XRGB8888;
                ఆపు;
            స్థితి 24:
                బహుళకం->format = SDL_PIXELFORMAT_RGB24;
                ఆపు;
            స్థితి 16:
                బహుళకం->format = SDL_PIXELFORMAT_RGB565;
                ఆపు;
            స్థితి 15:
                బహుళకం->format = SDL_PIXELFORMAT_XRGB1555;
                ఆపు;
            స్థితి 8:
                బహుళకం->format = SDL_PIXELFORMAT_INDEX8;
                ఆపు;
            స్థితి 4:
                బహుళకం->format = SDL_PIXELFORMAT_INDEX4LSB;
                ఆపు;
            }
        }
    }
}

స్థిర శూన్య *WIN_GetDXGIOutput(SDL_VideoDevice *_this, స్థిరరాశి WCHAR *DeviceName)
{
    శూన్య *ఫలితం = ఖాళీ;

#నిర్వచితమైతే HAVE_DXGI_H
    స్థిరరాశి SDL_Video_దత్తాంశం *videodata = (స్థిరరాశి SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    పూర్ణాంకం nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    ఒకవేళ (!videodata->pDXGIFactory) {
        తిరిగి ఖాళీ;
    }

    nAdapter = 0;
    అయితే (!ఫలితం && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        అయితే (!ఫలితం && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            ఒకవేళ (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                ఒకవేళ (SDL_wcscmp(outputDesc.DeviceName, DeviceName) == 0) {
                    ఫలితం = pDXGIOutput;
                }
            }
            ఒకవేళ (pDXGIOutput != ఫలితం) {
                IDXGIOutput_Release(pDXGIOutput);
            }
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }
#అయితే_ముగింపు
    తిరిగి ఫలితం;
}

స్థిర శూన్య WIN_ReleaseDXGIOutput(శూన్య *dxgi_output)
{
#నిర్వచితమైతే HAVE_DXGI_H
    IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;

    ఒకవేళ (pDXGIOutput) {
        IDXGIOutput_Release(pDXGIOutput);
    }
#అయితే_ముగింపు
}

స్థిర SDL_DisplayOrientation WIN_GetNaturalOrientation(DEVMODEW *బహుళకం)
{
    పూర్ణాంకం వెడల్పు = బహుళకం->dm_Pels_వెడల్పు;
    పూర్ణాంకం ఎత్తు = బహుళకం->dm_Pels_ఎత్తు;

    // Use unrotated width/height to guess orientation
    ఒకవేళ (బహుళకం->dmDisplayOrientation == DMDO_90 || బహుళకం->dmDisplayOrientation == DMDO_270) {
        పూర్ణాంకం తాత్కాలిక = వెడల్పు;
        వెడల్పు = ఎత్తు;
        ఎత్తు = తాత్కాలిక;
    }

    ఒకవేళ (వెడల్పు >= ఎత్తు) {
        తిరిగి SDL_ORIENTATION_LANDSCAPE;
    } లేకపోతే {
        తిరిగి SDL_ORIENTATION_PORTRAIT;
    }
}

స్థిర SDL_DisplayOrientation WIN_GetDisplayOrientation(DEVMODEW *బహుళకం)
{
    ఒకవేళ (WIN_GetNaturalOrientation(బహుళకం) == SDL_ORIENTATION_LANDSCAPE) {
        ఎంపిక (బహుళకం->dmDisplayOrientation) {
        స్థితి DMDO_DEFAULT:
            తిరిగి SDL_ORIENTATION_LANDSCAPE;
        స్థితి DMDO_90:
            తిరిగి SDL_ORIENTATION_PORTRAIT;
        స్థితి DMDO_180:
            తిరిగి SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        స్థితి DMDO_270:
            తిరిగి SDL_ORIENTATION_PORTRAIT_FLIPPED;
        అప్రమేయ:
            తిరిగి SDL_ORIENTATION_UNKNOWN;
        }
    } లేకపోతే {
        ఎంపిక (బహుళకం->dmDisplayOrientation) {
        స్థితి DMDO_DEFAULT:
            తిరిగి SDL_ORIENTATION_PORTRAIT;
        స్థితి DMDO_90:
            తిరిగి SDL_ORIENTATION_LANDSCAPE_FLIPPED;
        స్థితి DMDO_180:
            తిరిగి SDL_ORIENTATION_PORTRAIT_FLIPPED;
        స్థితి DMDO_270:
            తిరిగి SDL_ORIENTATION_LANDSCAPE;
        అప్రమేయ:
            తిరిగి SDL_ORIENTATION_UNKNOWN;
        }
    }
}

స్థిర శూన్య WIN_Get_Refresh_రేటు(శూన్య *dxgi_output, DEVMODEW *బహుళకం, పూర్ణాంకం *numerator, పూర్ణాంకం *denominator)
{
    // We're not currently using DXGI to query display modes, so fake NTSC timings
    ఎంపిక (బహుళకం->dmDisplayFrequency) {
    స్థితి 119:
    స్థితి 59:
    స్థితి 29:
        *numerator = (బహుళకం->dmDisplayFrequency + 1) * 1000;
        *denominator = 1001;
        ఆపు;
    అప్రమేయ:
        *numerator = బహుళకం->dmDisplayFrequency;
        *denominator = 1;
        ఆపు;
    }

#నిర్వచితమైతే HAVE_DXGI_H
    ఒకవేళ (dxgi_output) {
        IDXGIOutput *pDXGIOutput = (IDXGIOutput *)dxgi_output;
        DXGI_బహుళకం_DESC బహుళకం_గమ్యం_సరిపోలిక;
        DXGI_బహుళకం_DESC closest_సరిపోలిక;

        SDL_zero(బహుళకం_గమ్యం_సరిపోలిక);
        బహుళకం_గమ్యం_సరిపోలిక.వెడల్పు_2 = బహుళకం->dm_Pels_వెడల్పు;
        బహుళకం_గమ్యం_సరిపోలిక.ఎత్తు_2 = బహుళకం->dm_Pels_ఎత్తు;
        బహుళకం_గమ్యం_సరిపోలిక.Refresh_రేటు.Numerator = *numerator;
        బహుళకం_గమ్యం_సరిపోలిక.Refresh_రేటు.Denominator = *denominator;
        బహుళకం_గమ్యం_సరిపోలిక.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        ఒకవేళ (SUCCEEDED(IDXGIOutput_కనుగొను_Closest_Matching_బహుళకం(pDXGIOutput, &బహుళకం_గమ్యం_సరిపోలిక, &closest_సరిపోలిక, ఖాళీ))) {
            *numerator = closest_సరిపోలిక.Refresh_రేటు.Numerator;
            *denominator = closest_సరిపోలిక.Refresh_రేటు.Denominator;
        }
    }
#అయితే_ముగింపు // HAVE_DXGI_H
}

స్థిర దశాంశం WIN_GetContentScale(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    పూర్ణాంకం dpi = 0;

    స్థిరరాశి SDL_Video_దత్తాంశం *videodata = (స్థిరరాశి SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    ఒకవేళ (videodata->GetDpiForMonitor) {
        UINT hdpi_uint, vdpi_uint;
        ఒకవేళ (videodata->GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
            dpi = (పూర్ణాంకం)hdpi_uint;
        }
    }
    ఒకవేళ (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(ఖాళీ);
        ఒకవేళ (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(ఖాళీ, hdc);
        }
    }
    ఒకవేళ (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    తిరిగి dpi / (దశాంశం)USER_DEFAULT_SCREEN_DPI;
}

స్థిర bool WIN_Get_Display_బహుళకం(SDL_VideoDevice *_this, శూన్య *dxgi_output, HMONITOR hMonitor, LPCWSTR deviceName, DWORD సూచీ, SDL_Display_బహుళకం *బహుళకం, SDL_DisplayOrientation *natural_orientation, SDL_DisplayOrientation *current_orientation)
{
    SDL_Display_బహుళకం_దత్తాంశం *దత్తాంశం;
    DEVMODEW devmode;

    devmode.dm_కొలత = పరిమాణం(devmode);
    devmode.dmDriverExtra = 0;
    ఒకవేళ (!EnumDisplaySettingsW(deviceName, సూచీ, &devmode)) {
        తిరిగి false;
    }

    దత్తాంశం = (SDL_Display_బహుళకం_దత్తాంశం *)SDL_malloc(పరిమాణం(*దత్తాంశం));
    ఒకవేళ (!దత్తాంశం) {
        తిరిగి false;
    }

    SDL_zerop(బహుళకం);
    బహుళకం->అంతర్గత = దత్తాంశం;
    దత్తాంశం->Device_బహుళకం = devmode;

    బహుళకం->format = SDL_PIXELFORMAT_UNKNOWN;
    బహుళకం->w = దత్తాంశం->Device_బహుళకం.dm_Pels_వెడల్పు;
    బహుళకం->h = దత్తాంశం->Device_బహుళకం.dm_Pels_ఎత్తు;
    WIN_Get_Refresh_రేటు(dxgi_output, &దత్తాంశం->Device_బహుళకం, &బహుళకం->refresh_రేటు_numerator, &బహుళకం->refresh_రేటు_denominator);

    // Fill in the mode information
    WIN_Update_Display_బహుళకం(_this, deviceName, సూచీ, బహుళకం);

    ఒకవేళ (natural_orientation) {
        *natural_orientation = WIN_GetNaturalOrientation(&devmode);
    }
    ఒకవేళ (current_orientation) {
        *current_orientation = WIN_GetDisplayOrientation(&devmode);
    }

    తిరిగి true;
}

స్థిర అక్షరం *WIN_GetDisplayNameVista(SDL_Video_దత్తాంశం *videodata, స్థిరరాశి WCHAR *deviceName)
{
    DISPLAYCONFIG_మార్గం_INFO *paths = ఖాళీ;
    DISPLAYCONFIG_బహుళకం_INFO *modes = ఖాళీ;
    అక్షరం *ఫలితం = ఖాళీ;
    UINT32 మార్గం_లెక్క_2 = 0;
    UINT32 బహుళకం_లెక్క_2 = 0;
    UINT32 i;
    LONG rc;

    ఒకవేళ (!videodata->Get_Display_Config_బఫరు_Sizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        తిరిగి ఖాళీ;
    }

    చేయి {
        rc = videodata->Get_Display_Config_బఫరు_Sizes(QDC_ONLY_చురుకైన_PATHS, &మార్గం_లెక్క_2, &బహుళకం_లెక్క_2);
        ఒకవేళ (rc != ERROR_SUCCESS) {
            వెళ్ళు WIN_GetDisplayNameVista_failed;
        }

        SDL_free(paths);
        SDL_free(modes);

        paths = (DISPLAYCONFIG_మార్గం_INFO *)SDL_malloc(పరిమాణం(DISPLAYCONFIG_మార్గం_INFO) * మార్గం_లెక్క_2);
        modes = (DISPLAYCONFIG_బహుళకం_INFO *)SDL_malloc(పరిమాణం(DISPLAYCONFIG_బహుళకం_INFO) * బహుళకం_లెక్క_2);
        ఒకవేళ ((!paths) || (!modes)) {
            వెళ్ళు WIN_GetDisplayNameVista_failed;
        }

        rc = videodata->QueryDisplayConfig(QDC_ONLY_చురుకైన_PATHS, &మార్గం_లెక్క_2, paths, &బహుళకం_లెక్క_2, modes, 0);
    } అయితే (rc == ERROR_INSUFFICIENT_బఫరు);

    ఒకవేళ (rc == ERROR_SUCCESS) {
        కొరకు (i = 0; i < మార్గం_లెక్క_2; i++) {
            DISPLAYCONFIG_ఆధారం_DEVICE_NAME ఆధారం_Name;
            DISPLAYCONFIG_లక్ష్యం_DEVICE_NAME లక్ష్యం_Name;

            SDL_zero(ఆధారం_Name);
            ఆధారం_Name.శీర్షిక.adapterId = paths[i].లక్ష్యం_Info.adapterId;
            ఆధారం_Name.శీర్షిక.type = DISPLAYCONFIG_DEVICE_INFO_GET_ఆధారం_NAME;
            ఆధారం_Name.శీర్షిక.కొలత = పరిమాణం(ఆధారం_Name);
            ఆధారం_Name.శీర్షిక.id = paths[i].ఆధారం_Info.id;
            rc = videodata->DisplayConfigGetDeviceInfo(&ఆధారం_Name.శీర్షిక);
            ఒకవేళ (rc != ERROR_SUCCESS) {
                ఆపు;
            } లేకపోతే ఒకవేళ (SDL_wcscmp(deviceName, ఆధారం_Name.viewGdiDeviceName) != 0) {
                కొనసాగు;
            }

            SDL_zero(లక్ష్యం_Name);
            లక్ష్యం_Name.శీర్షిక.adapterId = paths[i].లక్ష్యం_Info.adapterId;
            లక్ష్యం_Name.శీర్షిక.id = paths[i].లక్ష్యం_Info.id;
            లక్ష్యం_Name.శీర్షిక.type = DISPLAYCONFIG_DEVICE_INFO_GET_లక్ష్యం_NAME;
            లక్ష్యం_Name.శీర్షిక.కొలత = పరిమాణం(లక్ష్యం_Name);
            rc = videodata->DisplayConfigGetDeviceInfo(&లక్ష్యం_Name.శీర్షిక);
            ఒకవేళ (rc == ERROR_SUCCESS) {
                ఫలితం = WIN_String_గమ్యం_UTF8_W(లక్ష్యం_Name.monitorFriendlyDeviceName);
                /* if we got an empty string, treat it as failure so we'll fallback
                   to getting the generic name. */
                ఒకవేళ (ఫలితం && (*ఫలితం == '\0')) {
                    SDL_free(ఫలితం);
                    ఫలితం = ఖాళీ;
                }
            }
            ఆపు;
        }
    }

    SDL_free(paths);
    SDL_free(modes);
    తిరిగి ఫలితం;

WIN_GetDisplayNameVista_failed:
    SDL_free(ఫలితం);
    SDL_free(paths);
    SDL_free(modes);
    తిరిగి ఖాళీ;
}

#నిర్వచితమైతే HAVE_DXGI1_6_H
స్థిర bool WIN_GetMonitorDESC1(HMONITOR hMonitor, DXGI_OUTPUT_DESC1 *desc)
{
    రకనిర్వచనం HRESULT (WINAPI *pfnCreateDXGIFactory1)(REFIID riid, శూన్య **ppFactory);
    pfnCreateDXGIFactory1 pCreateDXGIFactory1 = ఖాళీ;
    SDL_SharedObject *hDXGIMod = ఖాళీ;
    bool దొరికింది = false;

    hDXGIMod = SDL_ఎక్కించు_Object("dxgi.dll");
    ఒకవేళ (hDXGIMod) {
        pCreateDXGIFactory1 = (pfnCreateDXGIFactory1)SDL_ఎక్కించు_Function(hDXGIMod, "CreateDXGIFactory1");
    }
    ఒకవేళ (pCreateDXGIFactory1) {
        స్థిర స్థిరరాశి GUID SDL_IID_IDXGIFactory1 = { 0x770aae78, 0xf26f, 0x4dba, { 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 } };
        స్థిర స్థిరరాశి GUID SDL_IID_IDXGIOutput6 = { 0x068346e8, 0xaaec, 0x4b84, { 0xad, 0xd7, 0x13, 0x7f, 0x51, 0x3f, 0x77, 0xa1 } };
        IDXGIFactory1 *dxgiFactory;

        ఒకవేళ (SUCCEEDED(pCreateDXGIFactory1(&SDL_IID_IDXGIFactory1, (శూన్య **)&dxgiFactory))) {
            IDXGIAdapter1 *dxgiAdapter;
            UINT adapter = 0;
            అయితే (!దొరికింది && SUCCEEDED(IDXGIFactory1_EnumAdapters1(dxgiFactory, adapter, &dxgiAdapter))) {
                IDXGIOutput *dxgiOutput;
                UINT output = 0;
                అయితే (!దొరికింది && SUCCEEDED(IDXGIAdapter1_EnumOutputs(dxgiAdapter, output, &dxgiOutput))) {
                    IDXGIOutput6 *dxgiOutput6;
                    ఒకవేళ (SUCCEEDED(IDXGIOutput_QueryInterface(dxgiOutput, &SDL_IID_IDXGIOutput6, (శూన్య **)&dxgiOutput6))) {
                        ఒకవేళ (SUCCEEDED(IDXGIOutput6_GetDesc1(dxgiOutput6, desc))) {
                            ఒకవేళ (desc->Monitor == hMonitor) {
                                దొరికింది = true;
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
    ఒకవేళ (hDXGIMod) {
        SDL_UnloadObject(hDXGIMod);
    }
    తిరిగి దొరికింది;
}

స్థిర bool WIN_Get_Monitor_మార్గం_Info(SDL_Video_దత్తాంశం *videodata, HMONITOR hMonitor, DISPLAYCONFIG_మార్గం_INFO *మార్గం_info)
{
    LONG ఫలితం;
    MONITORINFOEXW view_info;
    UINT32 i;
    UINT32 అంకె_మార్గం_array_elements = 0;
    UINT32 అంకె_బహుళకం_info_array_elements = 0;
    DISPLAYCONFIG_మార్గం_INFO *మార్గం_infos = ఖాళీ, *new_మార్గం_infos;
    DISPLAYCONFIG_బహుళకం_INFO *బహుళకం_infos = ఖాళీ, *new_బహుళకం_infos;
    bool దొరికింది = false;

    ఒకవేళ (!videodata->Get_Display_Config_బఫరు_Sizes || !videodata->QueryDisplayConfig || !videodata->DisplayConfigGetDeviceInfo) {
        తిరిగి false;
    }

    SDL_zero(view_info);
    view_info.cb_కొలత = పరిమాణం(view_info);
    ఒకవేళ (!GetMonitorInfoW(hMonitor, (MONITORINFO *)&view_info)) {
        వెళ్ళు పూర్తి;
    }

    చేయి {
        ఒకవేళ (videodata->Get_Display_Config_బఫరు_Sizes(QDC_ONLY_చురుకైన_PATHS, &అంకె_మార్గం_array_elements, &అంకె_బహుళకం_info_array_elements) != ERROR_SUCCESS) {
            SDL_free(మార్గం_infos);
            SDL_free(బహుళకం_infos);
            తిరిగి false;
        }

        new_మార్గం_infos = (DISPLAYCONFIG_మార్గం_INFO *)SDL_realloc(మార్గం_infos, అంకె_మార్గం_array_elements * పరిమాణం(*మార్గం_infos));
        ఒకవేళ (!new_మార్గం_infos) {
            వెళ్ళు పూర్తి;
        }
        మార్గం_infos = new_మార్గం_infos;

        new_బహుళకం_infos = (DISPLAYCONFIG_బహుళకం_INFO *)SDL_realloc(బహుళకం_infos, అంకె_బహుళకం_info_array_elements * పరిమాణం(*బహుళకం_infos));
        ఒకవేళ (!new_బహుళకం_infos) {
            వెళ్ళు పూర్తి;
        }
        బహుళకం_infos = new_బహుళకం_infos;

        ఫలితం = videodata->QueryDisplayConfig(QDC_ONLY_చురుకైన_PATHS, &అంకె_మార్గం_array_elements, మార్గం_infos, &అంకె_బహుళకం_info_array_elements, బహుళకం_infos, ఖాళీ);

    } అయితే (ఫలితం == ERROR_INSUFFICIENT_బఫరు);

    ఒకవేళ (ఫలితం == ERROR_SUCCESS) {
        కొరకు (i = 0; i < అంకె_మార్గం_array_elements; ++i) {
            DISPLAYCONFIG_ఆధారం_DEVICE_NAME device_name;

            SDL_zero(device_name);
            device_name.శీర్షిక.type = DISPLAYCONFIG_DEVICE_INFO_GET_ఆధారం_NAME;
            device_name.శీర్షిక.కొలత = పరిమాణం(device_name);
            device_name.శీర్షిక.adapterId = మార్గం_infos[i].ఆధారం_Info.adapterId;
            device_name.శీర్షిక.id = మార్గం_infos[i].ఆధారం_Info.id;
            ఒకవేళ (videodata->DisplayConfigGetDeviceInfo(&device_name.శీర్షిక) == ERROR_SUCCESS) {
                ఒకవేళ (SDL_wcscmp(view_info.szDevice, device_name.viewGdiDeviceName) == 0) {
                    SDL_copyp(మార్గం_info, &మార్గం_infos[i]);
                    దొరికింది = true;
                    ఆపు;
                }
            }
        }
    }

పూర్తి:
    SDL_free(మార్గం_infos);
    SDL_free(బహుళకం_infos);

    తిరిగి దొరికింది;
}

స్థిర దశాంశం WIN_Get_SDRWhite_బిందువు(SDL_VideoDevice *_this, HMONITOR hMonitor)
{
    DISPLAYCONFIG_మార్గం_INFO మార్గం_info;
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    దశాంశం SDR_white_level = 1.0f;

    ఒకవేళ (WIN_Get_Monitor_మార్గం_Info(videodata, hMonitor, &మార్గం_info)) {
        /* workarounds for https://github.com/libsdl-org/SDL/issues/11193 */
        నిర్మాణం SDL_DISPLAYCONFIG_SDR_WHITE_LEVEL {
          DISPLAYCONFIG_DEVICE_INFO_శీర్షిక శీర్షిక;
          ULONG SDRWhiteLevel;
        } white_level;
        #నిర్వచించు DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL 11

        SDL_zero(white_level);
        white_level.శీర్షిక.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
        white_level.శీర్షిక.కొలత = పరిమాణం(white_level);
        white_level.శీర్షిక.adapterId = మార్గం_info.లక్ష్యం_Info.adapterId;
        white_level.శీర్షిక.id = మార్గం_info.లక్ష్యం_Info.id;
        // WIN_GetMonitorPathInfo() succeeded: DisplayConfigGetDeviceInfo is not NULL
        ఒకవేళ (videodata->DisplayConfigGetDeviceInfo(&white_level.శీర్షిక) == ERROR_SUCCESS &&
            white_level.SDRWhiteLevel > 0) {
            SDR_white_level = (white_level.SDRWhiteLevel / 1000.0f);
        }
    }
    తిరిగి SDR_white_level;
}

స్థిర శూన్య WIN_GetHDRProperties(SDL_VideoDevice *_this, HMONITOR hMonitor, SDL_HDROutputProperties *HDR)
{
    DXGI_OUTPUT_DESC1 desc;

    SDL_zerop(HDR);

    ఒకవేళ (WIN_GetMonitorDESC1(hMonitor, &desc)) {
        ఒకవేళ (desc.ColorSpace == DXGI_COLOR_SPACE_RGB_నిండిన_G2084_NONE_P2020) {
            HDR->SDR_white_level = WIN_Get_SDRWhite_బిందువు(_this, hMonitor);
            HDR->HDR_headroom = (desc.MaxLuminance / SCRGB_NITS) / HDR->SDR_white_level;
        }
    }
}
#అయితే_ముగింపు // HAVE_DXGI1_6_H

స్థిర శూన్య WIN_కూడు_Display(SDL_VideoDevice *_this, HMONITOR hMonitor, స్థిరరాశి MONITORINFOEXW *info, పూర్ణాంకం *display_సూచీ)
{
    పూర్ణాంకం i, సూచీ = *display_సూచీ;
    SDL_VideoDisplay display;
    SDL_Display_దత్తాంశం *displaydata;
    శూన్య *dxgi_output = ఖాళీ;
    SDL_Display_బహుళకం బహుళకం;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    దశాంశం content_scale = WIN_GetContentScale(_this, hMonitor);

#నిర్వచితమైతే DEBUG_MODES
    SDL_Log("Display: %s", WIN_String_గమ్యం_UTF8_W(info->szDevice));
#అయితే_ముగింపు

    dxgi_output = WIN_GetDXGIOutput(_this, info->szDevice);
    bool దొరికింది = WIN_Get_Display_బహుళకం(_this, dxgi_output, hMonitor, info->szDevice, ENUM_CURRENT_SETTINGS, &బహుళకం, &natural_orientation, &current_orientation);
    WIN_ReleaseDXGIOutput(dxgi_output);
    ఒకవేళ (!దొరికింది) {
        తిరిగి;
    }

    // Prevent adding duplicate displays. Do this after we know the display is
    // ready to be added to allow any displays that we can't fully query to be
    // removed
    కొరకు (i = 0; i < _this->అంకె_displays; ++i) {
        SDL_Display_దత్తాంశం *అంతర్గత = _this->displays[i]->అంతర్గత;
        ఒకవేళ (SDL_wcscmp(అంతర్గత->DeviceName, info->szDevice) == 0) {
            bool moved = (సూచీ != i);
            bool మారింది_bounds = false;

            ఒకవేళ (అంతర్గత->state != DisplayRemoved) {
                // We've already enumerated this display, don't move it
                వెళ్ళు cleanup;
            }

            ఒకవేళ (సూచీ >= _this->అంకె_displays) {
                // This should never happen due to the check above, but just in case...
                వెళ్ళు cleanup;
            }

            ఒకవేళ (moved) {
                SDL_VideoDisplay *tmp;

                tmp = _this->displays[సూచీ];
                _this->displays[సూచీ] = _this->displays[i];
                _this->displays[i] = tmp;
                i = సూచీ;
            }

            అంతర్గత->MonitorHandle = hMonitor;
            అంతర్గత->state = DisplayUnchanged;

            SDL_PropertiesID props = SDL_GetDisplayProperties(_this->displays[i]->id);
            SDL_సమితి_సూచిక_Property(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_సూచిక, hMonitor);

            ఒకవేళ (!_this->setting_display_బహుళకం) {
                SDL_VideoDisplay *existing_display = _this->displays[i];
                SDL_Rect bounds;

                SDL_ResetFullscreenDisplayModes(existing_display);
                SDL_సమితి_Desktop_Display_బహుళకం(existing_display, &బహుళకం);
                // The mode is owned by the video subsystem
                బహుళకం.అంతర్గత = ఖాళీ;
                ఒకవేళ (WIN_GetDisplayBounds(_this, existing_display, &bounds) &&
                    SDL_memcmp(&అంతర్గత->bounds, &bounds, పరిమాణం(bounds)) != 0) {
                    మారింది_bounds = true;
                    SDL_copyp(&అంతర్గత->bounds, &bounds);
                }
                ఒకవేళ (moved || మారింది_bounds) {
                    SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_MOVED, 0, 0);
                }
                SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_ORIENTATION, current_orientation, 0);
                SDL_సమితి_Display_Content_Scale(existing_display, content_scale);
#నిర్వచితమైతే HAVE_DXGI1_6_H
                SDL_HDROutputProperties HDR;
                WIN_GetHDRProperties(_this, hMonitor, &HDR);
                SDL_సమితి_Display_HDRProperties(existing_display, &HDR);
#అయితే_ముగింపు
            }
            వెళ్ళు పూర్తి;
        }
    }

    displaydata = (SDL_Display_దత్తాంశం *)SDL_calloc(1, పరిమాణం(*displaydata));
    ఒకవేళ (!displaydata) {
        వెళ్ళు cleanup;
    }
    SDL_memcpy(displaydata->DeviceName, info->szDevice, పరిమాణం(displaydata->DeviceName));
    displaydata->MonitorHandle = hMonitor;
    displaydata->state = DisplayAdded;

    SDL_zero(display);
    display.name = WIN_GetDisplayNameVista(_this->అంతర్గత, info->szDevice);
    ఒకవేళ (!display.name) {
        DISPLAY_DEVICEW device;
        SDL_zero(device);
        device.cb = పరిమాణం(device);
        ఒకవేళ (EnumDisplayDevicesW(info->szDevice, 0, &device, 0)) {
            display.name = WIN_String_గమ్యం_UTF8_W(device.DeviceString);
        }
    }

    display.desktop_బహుళకం = బహుళకం;
    display.natural_orientation = natural_orientation;
    display.current_orientation = current_orientation;
    display.content_scale = content_scale;
    display.device = _this;
    display.అంతర్గత = displaydata;
    WIN_GetDisplayBounds(_this, &display, &displaydata->bounds);
#నిర్వచితమైతే HAVE_DXGI1_6_H
    WIN_GetHDRProperties(_this, hMonitor, &display.HDR);
#అయితే_ముగింపు
    SDL_DisplayID displayID = SDL_కూడు_Video_Display(&display, false);
    ఒకవేళ (displayID) {
        // The mode is owned by the video subsystem
        బహుళకం.అంతర్గత = ఖాళీ;

        SDL_PropertiesID props = SDL_GetDisplayProperties(displayID);
        SDL_సమితి_సూచిక_Property(props, SDL_PROP_DISPLAY_WINDOWS_HMONITOR_సూచిక, hMonitor);
    } లేకపోతే {
        SDL_free(displaydata);
    }
    SDL_free(display.name);

పూర్తి:
    *display_సూచీ += 1;

cleanup:
    SDL_free(బహుళకం.అంతర్గత);
}

రకనిర్వచనం నిర్మాణం WIN_కూడు_Displays_దత్తాంశం
{
    SDL_VideoDevice *video_device;
    పూర్ణాంకం display_సూచీ;
    bool want_primary;
} WIN_కూడు_Displays_దత్తాంశం_2;

స్థిర BOOL CALLBACK WIN_కూడు_Displays_Callback(HMONITOR hMonitor,
                                             HDC hdcMonitor,
                                             LPRECT lprcMonitor,
                                             LPARAM dw_దత్తాంశం)
{
    WIN_కూడు_Displays_దత్తాంశం_2 *దత్తాంశం = (WIN_కూడు_Displays_దత్తాంశం_2 *)dw_దత్తాంశం;
    MONITORINFOEXW info;

    SDL_zero(info);
    info.cb_కొలత = పరిమాణం(info);

    ఒకవేళ (GetMonitorInfoW(hMonitor, (LPMONITORINFO)&info) != 0) {
        స్థిరరాశి bool is_primary = ((info.dwFlags & MONITORINFOF_PRIMARY) == MONITORINFOF_PRIMARY);

        ఒకవేళ (is_primary == దత్తాంశం->want_primary) {
            WIN_కూడు_Display(దత్తాంశం->video_device, hMonitor, &info, &దత్తాంశం->display_సూచీ);
        }
    }

    // continue enumeration
    తిరిగి TRUE;
}

స్థిర శూన్య WIN_కూడు_Displays(SDL_VideoDevice *_this)
{
    WIN_కూడు_Displays_దత్తాంశం_2 callback_దత్తాంశం;
    callback_దత్తాంశం.video_device = _this;
    callback_దత్తాంశం.display_సూచీ = 0;

    callback_దత్తాంశం.want_primary = true;
    EnumDisplayMonitors(ఖాళీ, ఖాళీ, WIN_కూడు_Displays_Callback, (LPARAM)&callback_దత్తాంశం);

    callback_దత్తాంశం.want_primary = false;
    EnumDisplayMonitors(ఖాళీ, ఖాళీ, WIN_కూడు_Displays_Callback, (LPARAM)&callback_దత్తాంశం);
}

bool WIN_InitModes(SDL_VideoDevice *_this)
{
    WIN_కూడు_Displays(_this);

    ఒకవేళ (_this->అంకె_displays == 0) {
        తిరిగి SDL_సమితి_Error("No displays available");
    }
    తిరిగి true;
}

bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    స్థిరరాశి SDL_Display_దత్తాంశం *దత్తాంశం = display->అంతర్గత;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cb_కొలత = పరిమాణం(MONITORINFO);
    rc = GetMonitorInfo(దత్తాంశం->MonitorHandle, &minfo);

    ఒకవేళ (!rc) {
        తిరిగి SDL_సమితి_Error("Couldn't find monitor data");
    }

    rect->x = minfo.rcMonitor.ఎడమ;
    rect->y = minfo.rcMonitor.శిఖరం;
    rect->w = minfo.rcMonitor.కుడి - minfo.rcMonitor.ఎడమ;
    rect->h = minfo.rcMonitor.bottom - minfo.rcMonitor.శిఖరం;

    తిరిగి true;
}

bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    స్థిరరాశి SDL_Display_దత్తాంశం *దత్తాంశం = display->అంతర్గత;
    MONITORINFO minfo;
    BOOL rc;

    SDL_zero(minfo);
    minfo.cb_కొలత = పరిమాణం(MONITORINFO);
    rc = GetMonitorInfo(దత్తాంశం->MonitorHandle, &minfo);

    ఒకవేళ (!rc) {
        తిరిగి SDL_సమితి_Error("Couldn't find monitor data");
    }

    rect->x = minfo.rcWork.ఎడమ;
    rect->y = minfo.rcWork.శిఖరం;
    rect->w = minfo.rcWork.కుడి - minfo.rcWork.ఎడమ;
    rect->h = minfo.rcWork.bottom - minfo.rcWork.శిఖరం;

    తిరిగి true;
}

bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_దత్తాంశం *దత్తాంశం = display->అంతర్గత;
    శూన్య *dxgi_output;
    DWORD i;
    SDL_Display_బహుళకం బహుళకం;

    dxgi_output = WIN_GetDXGIOutput(_this, దత్తాంశం->DeviceName);

    // Make sure we add the current mode to the list in case it's a custom mode that doesn't enumerate
    కొరకు (i = ENUM_CURRENT_SETTINGS; ; ++i) {
        ఒకవేళ (!WIN_Get_Display_బహుళకం(_this, dxgi_output, దత్తాంశం->MonitorHandle, దత్తాంశం->DeviceName, i, &బహుళకం, ఖాళీ, ఖాళీ)) {
            ఆపు;
        }
        ఒకవేళ (SDL_ISPIXELFORMAT_సూచీకృత(బహుళకం.format)) {
            // We don't support palettized modes now
            SDL_free(బహుళకం.అంతర్గత);
            కొనసాగు;
        }
        ఒకవేళ (బహుళకం.format != SDL_PIXELFORMAT_UNKNOWN) {
            ఒకవేళ (!SDL_కూడు_Fullscreen_Display_బహుళకం(display, &బహుళకం)) {
                SDL_free(బహుళకం.అంతర్గత);
            }
        } లేకపోతే {
            SDL_free(బహుళకం.అంతర్గత);
        }
    }

    WIN_ReleaseDXGIOutput(dxgi_output);

    తిరిగి true;
}

#నిర్వచితమైతే DEBUG_MODES
స్థిర శూన్య WIN_LogMonitor(SDL_VideoDevice *_this, HMONITOR mon)
{
    స్థిరరాశి SDL_Video_దత్తాంశం *vid_దత్తాంశం = (స్థిరరాశి SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    MONITORINFOEX minfo;
    UINT xdpi = 0, ydpi = 0;
    అక్షరం *name_utf8;

    ఒకవేళ (vid_దత్తాంశం->GetDpiForMonitor) {
        vid_దత్తాంశం->GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &xdpi, &ydpi);
    }

    SDL_zero(minfo);
    minfo.cb_కొలత = పరిమాణం(minfo);
    GetMonitorInfo(mon, (LPMONITORINFO)&minfo);

    name_utf8 = WIN_String_గమ్యం_UTF8(minfo.szDevice);

    SDL_Log("WIN_LogMonitor: monitor \"%s\": dpi: %d windows screen coordinates: %d, %d, %dx%d",
            name_utf8,
            xdpi,
            minfo.rcMonitor.ఎడమ,
            minfo.rcMonitor.శిఖరం,
            minfo.rcMonitor.కుడి - minfo.rcMonitor.ఎడమ,
            minfo.rcMonitor.bottom - minfo.rcMonitor.శిఖరం);

    SDL_free(name_utf8);
}
#అయితే_ముగింపు

bool WIN_సమితి_Display_బహుళకం(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం)
{
    SDL_Display_దత్తాంశం *displaydata = display->అంతర్గత;
    SDL_Display_బహుళకం_దత్తాంశం *దత్తాంశం = (SDL_Display_బహుళకం_దత్తాంశం *)బహుళకం->అంతర్గత;
    LONG స్థితి_2;

#నిర్వచితమైతే DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state before mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#అయితే_ముగింపు

    /* High-DPI notes:

       - ChangeDisplaySettingsEx always takes pixels.
       - e.g. if the display is set to 2880x1800 with 200% scaling in Display Settings
         - calling ChangeDisplaySettingsEx with a dmPelsWidth/Height other than 2880x1800 will
           change the monitor DPI to 96. (100% scaling)
         - calling ChangeDisplaySettingsEx with a dmPelsWidth/Height of 2880x1800 (or a NULL DEVMODE*) will
           reset the monitor DPI to 192. (200% scaling)

       NOTE: these are temporary changes in DPI, not modifications to the Control Panel setting. */
    ఒకవేళ (బహుళకం->అంతర్గత == display->desktop_బహుళకం.అంతర్గత) {
#నిర్వచితమైతే DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: resetting to original resolution");
#అయితే_ముగింపు
        స్థితి_2 = ChangeDisplaySettingsExW(displaydata->DeviceName, ఖాళీ, ఖాళీ, CDS_FULLSCREEN, ఖాళీ);
    } లేకపోతే {
#నిర్వచితమైతే DEBUG_MODES
        SDL_Log("WIN_SetDisplayMode: changing to %dx%d pixels", దత్తాంశం->Device_బహుళకం.dm_Pels_వెడల్పు, దత్తాంశం->Device_బహుళకం.dm_Pels_ఎత్తు);
#అయితే_ముగింపు
        స్థితి_2 = ChangeDisplaySettingsExW(displaydata->DeviceName, &దత్తాంశం->Device_బహుళకం, ఖాళీ, CDS_FULLSCREEN, ఖాళీ);
    }
    ఒకవేళ (స్థితి_2 != DISP_CHANGE_SUCCESSFUL) {
        స్థిరరాశి అక్షరం *reason = "Unknown reason";
        ఎంపిక (స్థితి_2) {
        స్థితి DISP_CHANGE_BADFLAGS:
            reason = "DISP_CHANGE_BADFLAGS";
            ఆపు;
        స్థితి DISP_CHANGE_BADMODE:
            reason = "DISP_CHANGE_BADMODE";
            ఆపు;
        స్థితి DISP_CHANGE_BADPARAM:
            reason = "DISP_CHANGE_BADPARAM";
            ఆపు;
        స్థితి DISP_CHANGE_FAILED:
            reason = "DISP_CHANGE_FAILED";
            ఆపు;
        }
        తిరిగి SDL_సమితి_Error("ChangeDisplaySettingsEx() failed: %s", reason);
    }

#నిర్వచితమైతే DEBUG_MODES
    SDL_Log("WIN_SetDisplayMode: monitor state after mode change:");
    WIN_LogMonitor(_this, displaydata->MonitorHandle);
#అయితే_ముగింపు

    EnumDisplaySettingsW(displaydata->DeviceName, ENUM_CURRENT_SETTINGS, &దత్తాంశం->Device_బహుళకం);
    WIN_Update_Display_బహుళకం(_this, displaydata->DeviceName, ENUM_CURRENT_SETTINGS, బహుళకం);
    తిరిగి true;
}

శూన్య WIN_RefreshDisplays(SDL_VideoDevice *_this)
{
    పూర్ణాంకం i;

    // Mark all displays as potentially invalid to detect
    // entries that have actually been removed
    కొరకు (i = 0; i < _this->అంకె_displays; ++i) {
        SDL_Display_దత్తాంశం *అంతర్గత = _this->displays[i]->అంతర్గత;
        అంతర్గత->state = DisplayRemoved;
    }

    // Enumerate displays to add any new ones and mark still
    // connected entries as valid
    WIN_కూడు_Displays(_this);

    // Delete any entries still marked as invalid, iterate
    // in reverse as each delete takes effect immediately
    కొరకు (i = _this->అంకె_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_Display_దత్తాంశం *అంతర్గత = display->అంతర్గత;
        ఒకవేళ (అంతర్గత->state == DisplayRemoved) {
            SDL_DelVideoDisplay(display->id, true);
        }
    }

    // Send events for any newly added displays
    కొరకు (i = 0; i < _this->అంకె_displays; ++i) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_Display_దత్తాంశం *అంతర్గత = display->అంతర్గత;
        ఒకవేళ (అంతర్గత->state == DisplayAdded) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
        }
    }
}

శూన్య WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this)
{
    // This almost never happens, so just go ahead and send update events for all displays
    కొరకు (పూర్ణాంకం i = 0; i < _this->అంకె_displays; ++i) {
        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_మారింది, 0, 0);
    }
}

శూన్య WIN_QuitModes(SDL_VideoDevice *_this)
{
    // All fullscreen windows should have restored modes by now
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WINDOWS
