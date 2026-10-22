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
#شامل "SDL_windowswindow.h"
#شامل "../SDL_clipboard_c.h"
#شامل "../../events/SDL_events_c.h"
#شامل "../../events/SDL_clipboardevents_c.h"

#تعریف_کرو BFT_BITMAP 0x4d42 // 'BM'

// Assume we can directly read and write BMP fields without byte swapping
SDL_COMPILE_وقت_ASSERT(verify_byte_ترتیب, SDL_BYTEORDER == SDL_LIL_ENDIAN);

ساکن UINT GetClipboardFormatPNG(خالی)
{
    ساکن UINT format;

    اگر (!format) {
        format = رجسٹر_Clipboard_Format(متن_2("PNG"));
    }
    واپس format;
}

ساکن BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    ثابت صحیح MAX_ATTEMPTS = 3;
    صحیح attempt;
    HWND hwnd = تہی;

    اگر (_this->windows) {
        hwnd = _this->windows->اندرونی_2->hwnd;
    }
    برائے (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        اگر (OpenClipboard(hwnd)) {
            واپس TRUE;
        }
        SDL_Delay(10);
    }
    واپس FALSE;
}

ساکن خالی WIN_CloseClipboard(خالی)
{
    CloseClipboard();
}

ساکن HANDLE WIN_ConvertBMPtoDIB(ثابت خالی *bmp, size_t bmp_سائز, UINT *format)
{
    HANDLE hMem = تہی;

    اگر (bmp && bmp_سائز > حجم(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + حجم(BITMAPFILEHEADER));
        size_t bih_سائز = pbih->bi_سائز + pbih->bi_Clr_مستعمل * حجم(RGBQUAD);
        size_t pixels_سائز = pbih->bi_سائز_Image;

        اگر (pbih->bi_سائز >= حجم(BITMAPV5_سرخی)) {
            *format = CF_DIBV5;
        } ورنہ {
            *format = CF_DIB;
        }

        اگر (pbfh->bf_Off_بٹ >= (حجم(BITMAPFILEHEADER) + bih_سائز) &&
            (pbfh->bf_Off_بٹ + pixels_سائز) <= bmp_سائز) {
            ثابت Uint8 *pixels = (ثابت Uint8 *)bmp + pbfh->bf_Off_بٹ;
            size_t dib_سائز = bih_سائز + pixels_سائز;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_سائز);
            اگر (hMem) {
                LPVOID dst = Global_تالا(hMem);
                اگر (dst) {
                    SDL_memcpy(dst, pbih, bih_سائز);
                    SDL_memcpy((Uint8 *)dst + bih_سائز, pixels, pixels_سائز);
                    GlobalUnlock(hMem);
                } ورنہ {
                    WIN_سیٹ_Error("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = تہی;
                }
            } ورنہ {
                SDL_برآمد_کا_حافظہ();
            }
        } ورنہ {
            SDL_سیٹ_Error("Invalid BMP data");
        }
    } ورنہ {
        SDL_سیٹ_Error("Invalid BMP data");
    }
    واپس hMem;
}

ساکن خالی *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *سائز)
{
    خالی *bmp = تہی;
    size_t mem_سائز = Global_سائز(hMem);

    اگر (mem_سائز > حجم(BITMAPINFOHEADER)) {
        LPVOID dib = Global_تالا(hMem);
        اگر (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_جدول_سائز;
            انتخاب (pbih->biCompression) {
            حالت BI_RGB:
                اگر (pbih->bi_ثنائی_ہندسہ_گنتی <= 8) {
                    color_جدول_سائز = حجم(RGBQUAD) * (pbih->bi_Clr_مستعمل == 0 ? 1 << pbih->bi_ثنائی_ہندسہ_گنتی : pbih->bi_Clr_مستعمل);
                } ورنہ {
                    color_جدول_سائز = 0;
                }
                توڑو;
            حالت BI_BITFIELDS:
                color_جدول_سائز = 3 * حجم(DWORD);
                توڑو;
            حالت 6 /* BI_ALPHABITFIELDS */:
                // https://learn.microsoft.com/en-us/previous-versions/windows/embedded/aa452885(v=msdn.10)
                color_جدول_سائز = 4 * حجم(DWORD);
                توڑو;
            طےشدہ: // FOURCC
                color_جدول_سائز = حجم(RGBQUAD) * pbih->bi_Clr_مستعمل;
            }

            size_t bih_سائز = pbih->bi_سائز + color_جدول_سائز;
            size_t dib_سائز = bih_سائز + pbih->bi_سائز_Image;
            اگر (dib_سائز <= mem_سائز) {
                size_t bmp_سائز = حجم(BITMAPFILEHEADER) + mem_سائز;
                bmp = SDL_malloc(bmp_سائز);
                اگر (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bf_سائز = (DWORD)bmp_سائز;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bf_Off_بٹ = (DWORD)(حجم(BITMAPFILEHEADER) + pbih->bi_سائز + color_جدول_سائز);
                    SDL_memcpy((Uint8 *)bmp + حجم(BITMAPFILEHEADER), dib, mem_سائز);
                    *سائز = bmp_سائز;
                }
            } ورنہ {
                SDL_سیٹ_Error("Invalid BMP data");
            }
            GlobalUnlock(hMem);
        } ورنہ {
            WIN_سیٹ_Error("GlobalLock()");
        }
    } ورنہ {
        SDL_سیٹ_Error("Invalid BMP data");
    }
    واپس bmp;
}

ساکن bool WIN_سیٹ_Clipboard_Image(SDL_VideoDevice *_this, ثابت حرف *mime_type)
{
    UINT format = 0;
    HANDLE hMem = تہی;
    size_t clipboard_ڈیٹا_سائز;
    ثابت خالی *clipboard_ڈیٹا;
    bool نتیجہ = true;

    clipboard_ڈیٹا = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_ڈیٹا_سائز);
    اگر (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_ڈیٹا, clipboard_ڈیٹا_سائز, &format);
    } ورنہ اگر (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_ڈیٹا_سائز);
        اگر (hMem) {
            LPVOID dst = Global_تالا(hMem);
            اگر (dst) {
                SDL_memcpy(dst, clipboard_ڈیٹا, clipboard_ڈیٹا_سائز);
                GlobalUnlock(hMem);
            } ورنہ {
                نتیجہ = WIN_سیٹ_Error("GlobalLock()");
                GlobalFree(hMem);
                hMem = تہی;
            }
        } ورنہ {
            نتیجہ = SDL_برآمد_کا_حافظہ();
        }
    } ورنہ {
        نتیجہ = SDL_سیٹ_Error("Unknown image format");
    }
    اگر (hMem) {
        // Save the image to the clipboard
        اگر (!سیٹ_Clipboard_ڈیٹا(format, hMem)) {
            نتیجہ = WIN_سیٹ_Error("Couldn't set clipboard data");
        }
    } ورنہ {
        // WIN_ConvertBMPtoDIB() set the error
        نتیجہ = false;
    }
    واپس نتیجہ;
}

ساکن bool WIN_سیٹ_Clipboard_متن(SDL_VideoDevice *_this, ثابت حرف *mime_type)
{
    HANDLE hMem;
    size_t clipboard_ڈیٹا_سائز;
    ثابت خالی *clipboard_ڈیٹا;
    bool نتیجہ = true;

    clipboard_ڈیٹا = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_ڈیٹا_سائز);
    اگر (clipboard_ڈیٹا && clipboard_ڈیٹا_سائز > 0) {
        سائز_T i, سائز;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (ثابت حرف *)clipboard_ڈیٹا, clipboard_ڈیٹا_سائز);
        اگر (!tstr) {
            واپس SDL_سیٹ_Error("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        برائے (سائز = 0, i = 0; tstr[i]; ++i, ++سائز) {
            اگر (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++سائز;
            }
        }
        سائز = (سائز + 1) * حجم(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, سائز);
        اگر (hMem) {
            LPWSTR dst = (LPWSTR)Global_تالا(hMem);
            اگر (dst) {
                // Copy the text over, adding carriage returns as necessary
                برائے (i = 0; tstr[i]; ++i) {
                    اگر (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            اگر (!سیٹ_Clipboard_ڈیٹا(CF_UNICODETEXT, hMem)) {
                نتیجہ = WIN_سیٹ_Error("Couldn't set clipboard data");
            }
        } ورنہ {
            نتیجہ = SDL_برآمد_کا_حافظہ();
        }
        SDL_free(tstr);
    }
    واپس نتیجہ;
}

bool WIN_سیٹ_Clipboard_ڈیٹا(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    size_t i;
    bool نتیجہ = true;

    /* I investigated delayed clipboard rendering, and at least with text and image
     * formats you have to use an output window, not SDL_HelperWindow, and the system
     * requests them being rendered immediately, so there isn't any benefit.
     */

    اگر (WIN_OpenClipboard(_this)) {
        خالی_خانے_Clipboard();

        // Set the clipboard text
        برائے (i = 0; i < _this->عدد_clipboard_mime_types; ++i) {
            ثابت حرف *mime_type = _this->clipboard_mime_types[i];

            اگر (SDL_Is_متن_Mime_Type(mime_type)) {
                اگر (!WIN_سیٹ_Clipboard_متن(_this, mime_type)) {
                    نتیجہ = false;
                }
                // Only set the first clipboard text
                توڑو;
            }
        }

        // Set the clipboard image
        برائے (i = 0; i < _this->عدد_clipboard_mime_types; ++i) {
            ثابت حرف *mime_type = _this->clipboard_mime_types[i];

            اگر (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                اگر (!WIN_سیٹ_Clipboard_Image(_this, mime_type)) {
                    نتیجہ = false;
                }
                توڑو;
            }
        }

        ڈیٹا->clipboard_گنتی = Get_Clipboard_Sequence_نمبر();
        WIN_CloseClipboard();
    } ورنہ {
        نتیجہ = WIN_سیٹ_Error("Couldn't open clipboard");
    }
    واپس نتیجہ;
}

خالی *WIN_Get_Clipboard_ڈیٹا(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *سائز)
{
    خالی *ڈیٹا = تہی;

    اگر (SDL_Is_متن_Mime_Type(mime_type)) {
        حرف *متن = تہی;

        اگر (Is_Clipboard_Format_دستیاب(CF_UNICODETEXT)) {
            اگر (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = Get_Clipboard_ڈیٹا(CF_UNICODETEXT);
                اگر (hMem) {
                    str = (LPTSTR)Global_تالا(hMem);
                    اگر (str) {
                        متن = WIN_String_مقصد_UTF8_W(str);
                        GlobalUnlock(hMem);
                    } ورنہ {
                        WIN_سیٹ_Error("Couldn't lock clipboard data");
                    }
                } ورنہ {
                    WIN_سیٹ_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } ورنہ اگر (Is_Clipboard_Format_دستیاب(CF_متن)) {
            اگر (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = Get_Clipboard_ڈیٹا(CF_متن);
                اگر (hMem) {
                    str = (LPCSTR)Global_تالا(hMem);
                    اگر (str) {
                        متن = SDL_strdup(str);
                        GlobalUnlock(hMem);
                    } ورنہ {
                        WIN_سیٹ_Error("Couldn't lock clipboard data");
                    }
                } ورنہ {
                    WIN_سیٹ_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }
        اگر (!متن) {
            متن = SDL_strdup("");
        }
        ڈیٹا = متن;
        *سائز = SDL_strlen(متن);

    } ورنہ اگر (SDL_strcmp(mime_type, "image/bmp") == 0) {
        اگر (Is_Clipboard_Format_دستیاب(CF_DIBV5)) {
            اگر (WIN_OpenClipboard(_this)) {
                HANDLE hMem = Get_Clipboard_ڈیٹا(CF_DIBV5);
                اگر (hMem) {
                    ڈیٹا = WIN_ConvertDIBtoBMP(hMem, سائز);
                } ورنہ {
                    WIN_سیٹ_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } ورنہ اگر (Is_Clipboard_Format_دستیاب(CF_DIB)) {
            اگر (WIN_OpenClipboard(_this)) {
                HANDLE hMem = Get_Clipboard_ڈیٹا(CF_DIB);
                اگر (hMem) {
                    ڈیٹا = WIN_ConvertDIBtoBMP(hMem, سائز);
                } ورنہ {
                    WIN_سیٹ_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } ورنہ اگر (SDL_strcmp(mime_type, "image/png") == 0) {
        اگر (Is_Clipboard_Format_دستیاب(GetClipboardFormatPNG())) {
            اگر (WIN_OpenClipboard(_this)) {
                HANDLE hMem = Get_Clipboard_ڈیٹا(GetClipboardFormatPNG());
                اگر (hMem) {
                    size_t mem_سائز = Global_سائز(hMem);
                    خالی *mem = Global_تالا(hMem);
                    اگر (mem) {
                        ڈیٹا = SDL_malloc(mem_سائز);
                        اگر (ڈیٹا) {
                            SDL_memcpy(ڈیٹا, mem, mem_سائز);
                            *سائز = mem_سائز;
                        }
                        GlobalUnlock(hMem);
                    } ورنہ {
                        WIN_سیٹ_Error("Couldn't lock clipboard data");
                    }
                } ورنہ {
                    WIN_سیٹ_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } ورنہ {
        ڈیٹا = SDL_Get_اندرونی_Clipboard_ڈیٹا(_this, mime_type, سائز);
    }
    واپس ڈیٹا;
}

bool WIN_Has_Clipboard_ڈیٹا(SDL_VideoDevice *_this, ثابت حرف *mime_type)
{
    اگر (SDL_Is_متن_Mime_Type(mime_type)) {
        اگر (Is_Clipboard_Format_دستیاب(CF_UNICODETEXT) || Is_Clipboard_Format_دستیاب(CF_متن)) {
            واپس true;
        }
    } ورنہ اگر (SDL_strcmp(mime_type, "image/bmp") == 0) {
        اگر (Is_Clipboard_Format_دستیاب(CF_DIBV5) || Is_Clipboard_Format_دستیاب(CF_DIB)) {
            واپس true;
        }
    } ورنہ اگر (SDL_strcmp(mime_type, "image/png") == 0) {
        اگر (Is_Clipboard_Format_دستیاب(GetClipboardFormatPNG())) {
            واپس true;
        }
    }
    واپس SDL_Has_اندرونی_Clipboard_ڈیٹا(_this, mime_type);
}

ساکن صحیح GetClipboardFormatMimeType(UINT format, حرف *name)
{
    ثابت حرف *mime_type = تہی;

    انتخاب (format) {
    حالت CF_متن:
        mime_type = "text/plain";
        توڑو;
    حالت CF_UNICODETEXT:
        mime_type = "text/plain;charset=utf-8";
        توڑو;
    حالت CF_DIB:
    حالت CF_DIBV5:
        mime_type = "image/bmp";
        توڑو;
    طےشدہ:
        اگر (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        توڑو;
    }
    اگر (mime_type) {
        size_t len = SDL_strlen(mime_type) + 1;
        اگر (name) {
            SDL_memcpy(name, mime_type, len);
        }
        واپس (صحیح)len;
    }
    واپس 0;
}

ساکن حرف **GetMimeTypes(صحیح *pnformats)
{
    حرف **new_mime_types = تہی;

    *pnformats = 0;

    اگر (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        صحیح nformats = 0;
        UINT format = 0;
        صحیح formatsSz = 0;
        bool have_image_bmp = false;
        برائے ( ; ; ) {
            format = EnumClipboardFormats(format);
            اگر (!format) {
                توڑو;
            }

#اگر_تعریف_شدہ DEBUG_CLIPBOARD
            حرف name[128] = { 0 };
            GetClipboardFormatNameA(format, name, حجم(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#اگر_ختم

            اگر (format == CF_DIB || format == CF_DIBV5) {
                اگر (have_image_bmp) {
                    // We have already registered this format
                    جاری;
                }
                have_image_bmp = true;
            }

            صحیح len = GetClipboardFormatMimeType(format, تہی);
            اگر (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_Allocate_Temporary_حافظہ((nformats + 1) * حجم(حرف *) + formatsSz);
        اگر (new_mime_types) {
            format = 0;
            حرف *strPtr = (حرف *)(new_mime_types + nformats + 1);
            صحیح i = 0;
            برائے ( ; ; ) {
                format = EnumClipboardFormats(format);
                اگر (!format) {
                    توڑو;
                }

                اگر (format == CF_DIB || format == CF_DIBV5) {
                    اگر (have_image_bmp) {
                        // We have already registered this format
                        جاری;
                    }
                    have_image_bmp = true;
                }

                صحیح len = GetClipboardFormatMimeType(format, strPtr);
                اگر (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = تہی;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    واپس new_mime_types;
}

خالی WIN_CheckClipboardUpdate(ساخت SDL_Video_ڈیٹا *ڈیٹا)
{
    DWORD گنتی = Get_Clipboard_Sequence_نمبر();
    اگر (گنتی != ڈیٹا->clipboard_گنتی) {
        اگر (گنتی) {
            صحیح nformats = 0;
            حرف **new_mime_types = GetMimeTypes(&nformats);
            اگر (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        ڈیٹا->clipboard_گنتی = گنتی;
    }
}

#اگر_ختم // SDL_VIDEO_DRIVER_WINDOWS
