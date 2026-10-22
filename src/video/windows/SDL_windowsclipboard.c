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
#అన్తర్భావ "SDL_windowswindow.h"
#అన్తర్భావ "../SDL_clipboard_c.h"
#అన్తర్భావ "../../events/SDL_events_c.h"
#అన్తర్భావ "../../events/SDL_clipboardevents_c.h"

#నిర్వచించు BFT_BITMAP 0x4d42 // 'BM'

// Assume we can directly read and write BMP fields without byte swapping
SDL_COMPILE_సమయం_ASSERT(verify_byte_క్రమం, SDL_BYTEORDER == SDL_LIL_ENDIAN);

స్థిర UINT GetClipboardFormatPNG(శూన్య)
{
    స్థిర UINT format;

    ఒకవేళ (!format) {
        format = రిజిస్టరు_Clipboard_Format(పాఠ్యం_2("PNG"));
    }
    తిరిగి format;
}

స్థిర BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    స్థిరరాశి పూర్ణాంకం MAX_ATTEMPTS = 3;
    పూర్ణాంకం attempt;
    HWND hwnd = ఖాళీ;

    ఒకవేళ (_this->windows) {
        hwnd = _this->windows->అంతర్గత->hwnd;
    }
    కొరకు (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        ఒకవేళ (OpenClipboard(hwnd)) {
            తిరిగి TRUE;
        }
        SDL_Delay(10);
    }
    తిరిగి FALSE;
}

స్థిర శూన్య WIN_CloseClipboard(శూన్య)
{
    CloseClipboard();
}

స్థిర HANDLE WIN_ConvertBMPtoDIB(స్థిరరాశి శూన్య *bmp, size_t bmp_కొలత, UINT *format)
{
    HANDLE hMem = ఖాళీ;

    ఒకవేళ (bmp && bmp_కొలత > పరిమాణం(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + పరిమాణం(BITMAPFILEHEADER));
        size_t bih_కొలత = pbih->bi_కొలత + pbih->bi_Clr_వాడిన * పరిమాణం(RGBQUAD);
        size_t pixels_కొలత = pbih->bi_కొలత_Image;

        ఒకవేళ (pbih->bi_కొలత >= పరిమాణం(BITMAPV5_శీర్షిక)) {
            *format = CF_DIBV5;
        } లేకపోతే {
            *format = CF_DIB;
        }

        ఒకవేళ (pbfh->bf_Off_బిట్లు >= (పరిమాణం(BITMAPFILEHEADER) + bih_కొలత) &&
            (pbfh->bf_Off_బిట్లు + pixels_కొలత) <= bmp_కొలత) {
            స్థిరరాశి Uint8 *pixels = (స్థిరరాశి Uint8 *)bmp + pbfh->bf_Off_బిట్లు;
            size_t dib_కొలత = bih_కొలత + pixels_కొలత;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_కొలత);
            ఒకవేళ (hMem) {
                LPVOID dst = Global_తాళం(hMem);
                ఒకవేళ (dst) {
                    SDL_memcpy(dst, pbih, bih_కొలత);
                    SDL_memcpy((Uint8 *)dst + bih_కొలత, pixels, pixels_కొలత);
                    GlobalUnlock(hMem);
                } లేకపోతే {
                    WIN_సమితి_Error("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = ఖాళీ;
                }
            } లేకపోతే {
                SDL_బహిర్గతం_యొక్క_జ్ఞాపకం();
            }
        } లేకపోతే {
            SDL_సమితి_Error("Invalid BMP data");
        }
    } లేకపోతే {
        SDL_సమితి_Error("Invalid BMP data");
    }
    తిరిగి hMem;
}

స్థిర శూన్య *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *కొలత)
{
    శూన్య *bmp = ఖాళీ;
    size_t mem_కొలత = Global_కొలత(hMem);

    ఒకవేళ (mem_కొలత > పరిమాణం(BITMAPINFOHEADER)) {
        LPVOID dib = Global_తాళం(hMem);
        ఒకవేళ (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_పట్టిక_కొలత;
            ఎంపిక (pbih->biCompression) {
            స్థితి BI_RGB:
                ఒకవేళ (pbih->bi_బిట్టు_లెక్క <= 8) {
                    color_పట్టిక_కొలత = పరిమాణం(RGBQUAD) * (pbih->bi_Clr_వాడిన == 0 ? 1 << pbih->bi_బిట్టు_లెక్క : pbih->bi_Clr_వాడిన);
                } లేకపోతే {
                    color_పట్టిక_కొలత = 0;
                }
                ఆపు;
            స్థితి BI_BITFIELDS:
                color_పట్టిక_కొలత = 3 * పరిమాణం(DWORD);
                ఆపు;
            స్థితి 6 /* BI_ALPHABITFIELDS */:
                // https://learn.microsoft.com/en-us/previous-versions/windows/embedded/aa452885(v=msdn.10)
                color_పట్టిక_కొలత = 4 * పరిమాణం(DWORD);
                ఆపు;
            అప్రమేయ: // FOURCC
                color_పట్టిక_కొలత = పరిమాణం(RGBQUAD) * pbih->bi_Clr_వాడిన;
            }

            size_t bih_కొలత = pbih->bi_కొలత + color_పట్టిక_కొలత;
            size_t dib_కొలత = bih_కొలత + pbih->bi_కొలత_Image;
            ఒకవేళ (dib_కొలత <= mem_కొలత) {
                size_t bmp_కొలత = పరిమాణం(BITMAPFILEHEADER) + mem_కొలత;
                bmp = SDL_malloc(bmp_కొలత);
                ఒకవేళ (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bf_కొలత = (DWORD)bmp_కొలత;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bf_Off_బిట్లు = (DWORD)(పరిమాణం(BITMAPFILEHEADER) + pbih->bi_కొలత + color_పట్టిక_కొలత);
                    SDL_memcpy((Uint8 *)bmp + పరిమాణం(BITMAPFILEHEADER), dib, mem_కొలత);
                    *కొలత = bmp_కొలత;
                }
            } లేకపోతే {
                SDL_సమితి_Error("Invalid BMP data");
            }
            GlobalUnlock(hMem);
        } లేకపోతే {
            WIN_సమితి_Error("GlobalLock()");
        }
    } లేకపోతే {
        SDL_సమితి_Error("Invalid BMP data");
    }
    తిరిగి bmp;
}

స్థిర bool WIN_సమితి_Clipboard_Image(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *mime_type)
{
    UINT format = 0;
    HANDLE hMem = ఖాళీ;
    size_t clipboard_దత్తాంశం_కొలత;
    స్థిరరాశి శూన్య *clipboard_దత్తాంశం;
    bool ఫలితం = true;

    clipboard_దత్తాంశం = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_దత్తాంశం_కొలత);
    ఒకవేళ (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_దత్తాంశం, clipboard_దత్తాంశం_కొలత, &format);
    } లేకపోతే ఒకవేళ (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_దత్తాంశం_కొలత);
        ఒకవేళ (hMem) {
            LPVOID dst = Global_తాళం(hMem);
            ఒకవేళ (dst) {
                SDL_memcpy(dst, clipboard_దత్తాంశం, clipboard_దత్తాంశం_కొలత);
                GlobalUnlock(hMem);
            } లేకపోతే {
                ఫలితం = WIN_సమితి_Error("GlobalLock()");
                GlobalFree(hMem);
                hMem = ఖాళీ;
            }
        } లేకపోతే {
            ఫలితం = SDL_బహిర్గతం_యొక్క_జ్ఞాపకం();
        }
    } లేకపోతే {
        ఫలితం = SDL_సమితి_Error("Unknown image format");
    }
    ఒకవేళ (hMem) {
        // Save the image to the clipboard
        ఒకవేళ (!సమితి_Clipboard_దత్తాంశం(format, hMem)) {
            ఫలితం = WIN_సమితి_Error("Couldn't set clipboard data");
        }
    } లేకపోతే {
        // WIN_ConvertBMPtoDIB() set the error
        ఫలితం = false;
    }
    తిరిగి ఫలితం;
}

స్థిర bool WIN_సమితి_Clipboard_పాఠ్యం(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *mime_type)
{
    HANDLE hMem;
    size_t clipboard_దత్తాంశం_కొలత;
    స్థిరరాశి శూన్య *clipboard_దత్తాంశం;
    bool ఫలితం = true;

    clipboard_దత్తాంశం = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_దత్తాంశం_కొలత);
    ఒకవేళ (clipboard_దత్తాంశం && clipboard_దత్తాంశం_కొలత > 0) {
        కొలత_T i, కొలత;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (స్థిరరాశి అక్షరం *)clipboard_దత్తాంశం, clipboard_దత్తాంశం_కొలత);
        ఒకవేళ (!tstr) {
            తిరిగి SDL_సమితి_Error("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        కొరకు (కొలత = 0, i = 0; tstr[i]; ++i, ++కొలత) {
            ఒకవేళ (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++కొలత;
            }
        }
        కొలత = (కొలత + 1) * పరిమాణం(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, కొలత);
        ఒకవేళ (hMem) {
            LPWSTR dst = (LPWSTR)Global_తాళం(hMem);
            ఒకవేళ (dst) {
                // Copy the text over, adding carriage returns as necessary
                కొరకు (i = 0; tstr[i]; ++i) {
                    ఒకవేళ (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            ఒకవేళ (!సమితి_Clipboard_దత్తాంశం(CF_UNICODETEXT, hMem)) {
                ఫలితం = WIN_సమితి_Error("Couldn't set clipboard data");
            }
        } లేకపోతే {
            ఫలితం = SDL_బహిర్గతం_యొక్క_జ్ఞాపకం();
        }
        SDL_free(tstr);
    }
    తిరిగి ఫలితం;
}

bool WIN_సమితి_Clipboard_దత్తాంశం(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    size_t i;
    bool ఫలితం = true;

    /* I investigated delayed clipboard rendering, and at least with text and image
     * formats you have to use an output window, not SDL_HelperWindow, and the system
     * requests them being rendered immediately, so there isn't any benefit.
     */

    ఒకవేళ (WIN_OpenClipboard(_this)) {
        ఖాళీలు_Clipboard();

        // Set the clipboard text
        కొరకు (i = 0; i < _this->అంకె_clipboard_mime_types; ++i) {
            స్థిరరాశి అక్షరం *mime_type = _this->clipboard_mime_types[i];

            ఒకవేళ (SDL_Is_పాఠ్యం_Mime_Type(mime_type)) {
                ఒకవేళ (!WIN_సమితి_Clipboard_పాఠ్యం(_this, mime_type)) {
                    ఫలితం = false;
                }
                // Only set the first clipboard text
                ఆపు;
            }
        }

        // Set the clipboard image
        కొరకు (i = 0; i < _this->అంకె_clipboard_mime_types; ++i) {
            స్థిరరాశి అక్షరం *mime_type = _this->clipboard_mime_types[i];

            ఒకవేళ (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                ఒకవేళ (!WIN_సమితి_Clipboard_Image(_this, mime_type)) {
                    ఫలితం = false;
                }
                ఆపు;
            }
        }

        దత్తాంశం->clipboard_లెక్క = Get_Clipboard_Sequence_సంఖ్య();
        WIN_CloseClipboard();
    } లేకపోతే {
        ఫలితం = WIN_సమితి_Error("Couldn't open clipboard");
    }
    తిరిగి ఫలితం;
}

శూన్య *WIN_Get_Clipboard_దత్తాంశం(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *mime_type, size_t *కొలత)
{
    శూన్య *దత్తాంశం = ఖాళీ;

    ఒకవేళ (SDL_Is_పాఠ్యం_Mime_Type(mime_type)) {
        అక్షరం *పాఠ్యం = ఖాళీ;

        ఒకవేళ (Is_Clipboard_Format_అందుబాటు(CF_UNICODETEXT)) {
            ఒకవేళ (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = Get_Clipboard_దత్తాంశం(CF_UNICODETEXT);
                ఒకవేళ (hMem) {
                    str = (LPTSTR)Global_తాళం(hMem);
                    ఒకవేళ (str) {
                        పాఠ్యం = WIN_String_గమ్యం_UTF8_W(str);
                        GlobalUnlock(hMem);
                    } లేకపోతే {
                        WIN_సమితి_Error("Couldn't lock clipboard data");
                    }
                } లేకపోతే {
                    WIN_సమితి_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } లేకపోతే ఒకవేళ (Is_Clipboard_Format_అందుబాటు(CF_పాఠ్యం)) {
            ఒకవేళ (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = Get_Clipboard_దత్తాంశం(CF_పాఠ్యం);
                ఒకవేళ (hMem) {
                    str = (LPCSTR)Global_తాళం(hMem);
                    ఒకవేళ (str) {
                        పాఠ్యం = SDL_strdup(str);
                        GlobalUnlock(hMem);
                    } లేకపోతే {
                        WIN_సమితి_Error("Couldn't lock clipboard data");
                    }
                } లేకపోతే {
                    WIN_సమితి_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }
        ఒకవేళ (!పాఠ్యం) {
            పాఠ్యం = SDL_strdup("");
        }
        దత్తాంశం = పాఠ్యం;
        *కొలత = SDL_strlen(పాఠ్యం);

    } లేకపోతే ఒకవేళ (SDL_strcmp(mime_type, "image/bmp") == 0) {
        ఒకవేళ (Is_Clipboard_Format_అందుబాటు(CF_DIBV5)) {
            ఒకవేళ (WIN_OpenClipboard(_this)) {
                HANDLE hMem = Get_Clipboard_దత్తాంశం(CF_DIBV5);
                ఒకవేళ (hMem) {
                    దత్తాంశం = WIN_ConvertDIBtoBMP(hMem, కొలత);
                } లేకపోతే {
                    WIN_సమితి_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } లేకపోతే ఒకవేళ (Is_Clipboard_Format_అందుబాటు(CF_DIB)) {
            ఒకవేళ (WIN_OpenClipboard(_this)) {
                HANDLE hMem = Get_Clipboard_దత్తాంశం(CF_DIB);
                ఒకవేళ (hMem) {
                    దత్తాంశం = WIN_ConvertDIBtoBMP(hMem, కొలత);
                } లేకపోతే {
                    WIN_సమితి_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } లేకపోతే ఒకవేళ (SDL_strcmp(mime_type, "image/png") == 0) {
        ఒకవేళ (Is_Clipboard_Format_అందుబాటు(GetClipboardFormatPNG())) {
            ఒకవేళ (WIN_OpenClipboard(_this)) {
                HANDLE hMem = Get_Clipboard_దత్తాంశం(GetClipboardFormatPNG());
                ఒకవేళ (hMem) {
                    size_t mem_కొలత = Global_కొలత(hMem);
                    శూన్య *mem = Global_తాళం(hMem);
                    ఒకవేళ (mem) {
                        దత్తాంశం = SDL_malloc(mem_కొలత);
                        ఒకవేళ (దత్తాంశం) {
                            SDL_memcpy(దత్తాంశం, mem, mem_కొలత);
                            *కొలత = mem_కొలత;
                        }
                        GlobalUnlock(hMem);
                    } లేకపోతే {
                        WIN_సమితి_Error("Couldn't lock clipboard data");
                    }
                } లేకపోతే {
                    WIN_సమితి_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } లేకపోతే {
        దత్తాంశం = SDL_Get_అంతర్గత_Clipboard_దత్తాంశం(_this, mime_type, కొలత);
    }
    తిరిగి దత్తాంశం;
}

bool WIN_Has_Clipboard_దత్తాంశం(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *mime_type)
{
    ఒకవేళ (SDL_Is_పాఠ్యం_Mime_Type(mime_type)) {
        ఒకవేళ (Is_Clipboard_Format_అందుబాటు(CF_UNICODETEXT) || Is_Clipboard_Format_అందుబాటు(CF_పాఠ్యం)) {
            తిరిగి true;
        }
    } లేకపోతే ఒకవేళ (SDL_strcmp(mime_type, "image/bmp") == 0) {
        ఒకవేళ (Is_Clipboard_Format_అందుబాటు(CF_DIBV5) || Is_Clipboard_Format_అందుబాటు(CF_DIB)) {
            తిరిగి true;
        }
    } లేకపోతే ఒకవేళ (SDL_strcmp(mime_type, "image/png") == 0) {
        ఒకవేళ (Is_Clipboard_Format_అందుబాటు(GetClipboardFormatPNG())) {
            తిరిగి true;
        }
    }
    తిరిగి SDL_Has_అంతర్గత_Clipboard_దత్తాంశం(_this, mime_type);
}

స్థిర పూర్ణాంకం GetClipboardFormatMimeType(UINT format, అక్షరం *name)
{
    స్థిరరాశి అక్షరం *mime_type = ఖాళీ;

    ఎంపిక (format) {
    స్థితి CF_పాఠ్యం:
        mime_type = "text/plain";
        ఆపు;
    స్థితి CF_UNICODETEXT:
        mime_type = "text/plain;charset=utf-8";
        ఆపు;
    స్థితి CF_DIB:
    స్థితి CF_DIBV5:
        mime_type = "image/bmp";
        ఆపు;
    అప్రమేయ:
        ఒకవేళ (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        ఆపు;
    }
    ఒకవేళ (mime_type) {
        size_t len = SDL_strlen(mime_type) + 1;
        ఒకవేళ (name) {
            SDL_memcpy(name, mime_type, len);
        }
        తిరిగి (పూర్ణాంకం)len;
    }
    తిరిగి 0;
}

స్థిర అక్షరం **GetMimeTypes(పూర్ణాంకం *pnformats)
{
    అక్షరం **new_mime_types = ఖాళీ;

    *pnformats = 0;

    ఒకవేళ (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        పూర్ణాంకం nformats = 0;
        UINT format = 0;
        పూర్ణాంకం formatsSz = 0;
        bool have_image_bmp = false;
        కొరకు ( ; ; ) {
            format = EnumClipboardFormats(format);
            ఒకవేళ (!format) {
                ఆపు;
            }

#నిర్వచితమైతే DEBUG_CLIPBOARD
            అక్షరం name[128] = { 0 };
            GetClipboardFormatNameA(format, name, పరిమాణం(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#అయితే_ముగింపు

            ఒకవేళ (format == CF_DIB || format == CF_DIBV5) {
                ఒకవేళ (have_image_bmp) {
                    // We have already registered this format
                    కొనసాగు;
                }
                have_image_bmp = true;
            }

            పూర్ణాంకం len = GetClipboardFormatMimeType(format, ఖాళీ);
            ఒకవేళ (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_Allocate_Temporary_జ్ఞాపకం((nformats + 1) * పరిమాణం(అక్షరం *) + formatsSz);
        ఒకవేళ (new_mime_types) {
            format = 0;
            అక్షరం *strPtr = (అక్షరం *)(new_mime_types + nformats + 1);
            పూర్ణాంకం i = 0;
            కొరకు ( ; ; ) {
                format = EnumClipboardFormats(format);
                ఒకవేళ (!format) {
                    ఆపు;
                }

                ఒకవేళ (format == CF_DIB || format == CF_DIBV5) {
                    ఒకవేళ (have_image_bmp) {
                        // We have already registered this format
                        కొనసాగు;
                    }
                    have_image_bmp = true;
                }

                పూర్ణాంకం len = GetClipboardFormatMimeType(format, strPtr);
                ఒకవేళ (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = ఖాళీ;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    తిరిగి new_mime_types;
}

శూన్య WIN_CheckClipboardUpdate(నిర్మాణం SDL_Video_దత్తాంశం *దత్తాంశం)
{
    DWORD లెక్క = Get_Clipboard_Sequence_సంఖ్య();
    ఒకవేళ (లెక్క != దత్తాంశం->clipboard_లెక్క) {
        ఒకవేళ (లెక్క) {
            పూర్ణాంకం nformats = 0;
            అక్షరం **new_mime_types = GetMimeTypes(&nformats);
            ఒకవేళ (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        దత్తాంశం->clipboard_లెక్క = లెక్క;
    }
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WINDOWS
