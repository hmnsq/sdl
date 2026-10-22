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
#ضمن "SDL_windowswindow.h"
#ضمن "../SDL_clipboard_c.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../../events/SDL_clipboardevents_c.h"

#تعریف_کړه BFT_BITMAP 0x4d42 // 'BM'

// Assume we can directly read and write BMP fields without byte swapping
SDL_COMPILE_وخت_ASSERT(verify_byte_ترتیب, SDL_BYTEORDER == SDL_LIL_ENDIAN);

ساكن UINT GetClipboardFormatPNG(فراغ)
{
    ساكن UINT format;

    إذا (!format) {
        format = ثبتوونکی_Clipboard_Format(متن_2("PNG"));
    }
    أرجع format;
}

ساكن BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    ثابت صحيح MAX_ATTEMPTS = 3;
    صحيح attempt;
    HWND hwnd = عدم;

    إذا (_this->windows) {
        hwnd = _this->windows->دننی->hwnd;
    }
    لكل (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        إذا (OpenClipboard(hwnd)) {
            أرجع TRUE;
        }
        SDL_Delay(10);
    }
    أرجع FALSE;
}

ساكن فراغ WIN_CloseClipboard(فراغ)
{
    CloseClipboard();
}

ساكن HANDLE WIN_ConvertBMPtoDIB(ثابت فراغ *bmp, size_t bmp_اندازه, UINT *format)
{
    HANDLE hMem = عدم;

    إذا (bmp && bmp_اندازه > حجم(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + حجم(BITMAPFILEHEADER));
        size_t bih_اندازه = pbih->bi_اندازه + pbih->bi_Clr_کارول_شوی * حجم(RGBQUAD);
        size_t pixels_اندازه = pbih->bi_اندازه_Image;

        إذا (pbih->bi_اندازه >= حجم(BITMAPV5_سرلیک)) {
            *format = CF_DIBV5;
        } وإلا {
            *format = CF_DIB;
        }

        إذا (pbfh->bf_Off_بټونه >= (حجم(BITMAPFILEHEADER) + bih_اندازه) &&
            (pbfh->bf_Off_بټونه + pixels_اندازه) <= bmp_اندازه) {
            ثابت Uint8 *pixels = (ثابت Uint8 *)bmp + pbfh->bf_Off_بټونه;
            size_t dib_اندازه = bih_اندازه + pixels_اندازه;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_اندازه);
            إذا (hMem) {
                LPVOID dst = Global_قلف(hMem);
                إذا (dst) {
                    SDL_memcpy(dst, pbih, bih_اندازه);
                    SDL_memcpy((Uint8 *)dst + bih_اندازه, pixels, pixels_اندازه);
                    GlobalUnlock(hMem);
                } وإلا {
                    WIN_سېټ_Error("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = عدم;
                }
            } وإلا {
                SDL_بهر_د_حافظه();
            }
        } وإلا {
            SDL_سېټ_Error("Invalid BMP data");
        }
    } وإلا {
        SDL_سېټ_Error("Invalid BMP data");
    }
    أرجع hMem;
}

ساكن فراغ *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *اندازه)
{
    فراغ *bmp = عدم;
    size_t mem_اندازه = Global_اندازه(hMem);

    إذا (mem_اندازه > حجم(BITMAPINFOHEADER)) {
        LPVOID dib = Global_قلف(hMem);
        إذا (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_جدول_اندازه;
            بدل (pbih->biCompression) {
            حالة BI_RGB:
                إذا (pbih->bi_بټ_شمېر <= 8) {
                    color_جدول_اندازه = حجم(RGBQUAD) * (pbih->bi_Clr_کارول_شوی == 0 ? 1 << pbih->bi_بټ_شمېر : pbih->bi_Clr_کارول_شوی);
                } وإلا {
                    color_جدول_اندازه = 0;
                }
                اكسر;
            حالة BI_BITFIELDS:
                color_جدول_اندازه = 3 * حجم(DWORD);
                اكسر;
            حالة 6 /* BI_ALPHABITFIELDS */:
                // https://learn.microsoft.com/en-us/previous-versions/windows/embedded/aa452885(v=msdn.10)
                color_جدول_اندازه = 4 * حجم(DWORD);
                اكسر;
            افتراضي: // FOURCC
                color_جدول_اندازه = حجم(RGBQUAD) * pbih->bi_Clr_کارول_شوی;
            }

            size_t bih_اندازه = pbih->bi_اندازه + color_جدول_اندازه;
            size_t dib_اندازه = bih_اندازه + pbih->bi_اندازه_Image;
            إذا (dib_اندازه <= mem_اندازه) {
                size_t bmp_اندازه = حجم(BITMAPFILEHEADER) + mem_اندازه;
                bmp = SDL_malloc(bmp_اندازه);
                إذا (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bf_اندازه = (DWORD)bmp_اندازه;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bf_Off_بټونه = (DWORD)(حجم(BITMAPFILEHEADER) + pbih->bi_اندازه + color_جدول_اندازه);
                    SDL_memcpy((Uint8 *)bmp + حجم(BITMAPFILEHEADER), dib, mem_اندازه);
                    *اندازه = bmp_اندازه;
                }
            } وإلا {
                SDL_سېټ_Error("Invalid BMP data");
            }
            GlobalUnlock(hMem);
        } وإلا {
            WIN_سېټ_Error("GlobalLock()");
        }
    } وإلا {
        SDL_سېټ_Error("Invalid BMP data");
    }
    أرجع bmp;
}

ساكن bool WIN_سېټ_Clipboard_Image(SDL_VideoDevice *_this, ثابت حرف *mime_type)
{
    UINT format = 0;
    HANDLE hMem = عدم;
    size_t clipboard_معلومات_اندازه;
    ثابت فراغ *clipboard_معلومات;
    bool پایله = true;

    clipboard_معلومات = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_معلومات_اندازه);
    إذا (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_معلومات, clipboard_معلومات_اندازه, &format);
    } وإلا إذا (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_معلومات_اندازه);
        إذا (hMem) {
            LPVOID dst = Global_قلف(hMem);
            إذا (dst) {
                SDL_memcpy(dst, clipboard_معلومات, clipboard_معلومات_اندازه);
                GlobalUnlock(hMem);
            } وإلا {
                پایله = WIN_سېټ_Error("GlobalLock()");
                GlobalFree(hMem);
                hMem = عدم;
            }
        } وإلا {
            پایله = SDL_بهر_د_حافظه();
        }
    } وإلا {
        پایله = SDL_سېټ_Error("Unknown image format");
    }
    إذا (hMem) {
        // Save the image to the clipboard
        إذا (!سېټ_Clipboard_معلومات(format, hMem)) {
            پایله = WIN_سېټ_Error("Couldn't set clipboard data");
        }
    } وإلا {
        // WIN_ConvertBMPtoDIB() set the error
        پایله = false;
    }
    أرجع پایله;
}

ساكن bool WIN_سېټ_Clipboard_متن(SDL_VideoDevice *_this, ثابت حرف *mime_type)
{
    HANDLE hMem;
    size_t clipboard_معلومات_اندازه;
    ثابت فراغ *clipboard_معلومات;
    bool پایله = true;

    clipboard_معلومات = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_معلومات_اندازه);
    إذا (clipboard_معلومات && clipboard_معلومات_اندازه > 0) {
        اندازه_T i, اندازه;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (ثابت حرف *)clipboard_معلومات, clipboard_معلومات_اندازه);
        إذا (!tstr) {
            أرجع SDL_سېټ_Error("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        لكل (اندازه = 0, i = 0; tstr[i]; ++i, ++اندازه) {
            إذا (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++اندازه;
            }
        }
        اندازه = (اندازه + 1) * حجم(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, اندازه);
        إذا (hMem) {
            LPWSTR dst = (LPWSTR)Global_قلف(hMem);
            إذا (dst) {
                // Copy the text over, adding carriage returns as necessary
                لكل (i = 0; tstr[i]; ++i) {
                    إذا (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            إذا (!سېټ_Clipboard_معلومات(CF_UNICODETEXT, hMem)) {
                پایله = WIN_سېټ_Error("Couldn't set clipboard data");
            }
        } وإلا {
            پایله = SDL_بهر_د_حافظه();
        }
        SDL_free(tstr);
    }
    أرجع پایله;
}

bool WIN_سېټ_Clipboard_معلومات(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->دننی;
    size_t i;
    bool پایله = true;

    /* I investigated delayed clipboard rendering, and at least with text and image
     * formats you have to use an output window, not SDL_HelperWindow, and the system
     * requests them being rendered immediately, so there isn't any benefit.
     */

    إذا (WIN_OpenClipboard(_this)) {
        تشه_Clipboard();

        // Set the clipboard text
        لكل (i = 0; i < _this->عدد_clipboard_mime_types; ++i) {
            ثابت حرف *mime_type = _this->clipboard_mime_types[i];

            إذا (SDL_Is_متن_Mime_Type(mime_type)) {
                إذا (!WIN_سېټ_Clipboard_متن(_this, mime_type)) {
                    پایله = false;
                }
                // Only set the first clipboard text
                اكسر;
            }
        }

        // Set the clipboard image
        لكل (i = 0; i < _this->عدد_clipboard_mime_types; ++i) {
            ثابت حرف *mime_type = _this->clipboard_mime_types[i];

            إذا (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                إذا (!WIN_سېټ_Clipboard_Image(_this, mime_type)) {
                    پایله = false;
                }
                اكسر;
            }
        }

        معلومات->clipboard_شمېر = Get_Clipboard_Sequence_شمېره();
        WIN_CloseClipboard();
    } وإلا {
        پایله = WIN_سېټ_Error("Couldn't open clipboard");
    }
    أرجع پایله;
}

فراغ *WIN_Get_Clipboard_معلومات(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *اندازه)
{
    فراغ *معلومات = عدم;

    إذا (SDL_Is_متن_Mime_Type(mime_type)) {
        حرف *متن = عدم;

        إذا (Is_Clipboard_Format_شته(CF_UNICODETEXT)) {
            إذا (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = Get_Clipboard_معلومات(CF_UNICODETEXT);
                إذا (hMem) {
                    str = (LPTSTR)Global_قلف(hMem);
                    إذا (str) {
                        متن = WIN_String_منزل_UTF8_W(str);
                        GlobalUnlock(hMem);
                    } وإلا {
                        WIN_سېټ_Error("Couldn't lock clipboard data");
                    }
                } وإلا {
                    WIN_سېټ_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } وإلا إذا (Is_Clipboard_Format_شته(CF_متن)) {
            إذا (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = Get_Clipboard_معلومات(CF_متن);
                إذا (hMem) {
                    str = (LPCSTR)Global_قلف(hMem);
                    إذا (str) {
                        متن = SDL_strdup(str);
                        GlobalUnlock(hMem);
                    } وإلا {
                        WIN_سېټ_Error("Couldn't lock clipboard data");
                    }
                } وإلا {
                    WIN_سېټ_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }
        إذا (!متن) {
            متن = SDL_strdup("");
        }
        معلومات = متن;
        *اندازه = SDL_strlen(متن);

    } وإلا إذا (SDL_strcmp(mime_type, "image/bmp") == 0) {
        إذا (Is_Clipboard_Format_شته(CF_DIBV5)) {
            إذا (WIN_OpenClipboard(_this)) {
                HANDLE hMem = Get_Clipboard_معلومات(CF_DIBV5);
                إذا (hMem) {
                    معلومات = WIN_ConvertDIBtoBMP(hMem, اندازه);
                } وإلا {
                    WIN_سېټ_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } وإلا إذا (Is_Clipboard_Format_شته(CF_DIB)) {
            إذا (WIN_OpenClipboard(_this)) {
                HANDLE hMem = Get_Clipboard_معلومات(CF_DIB);
                إذا (hMem) {
                    معلومات = WIN_ConvertDIBtoBMP(hMem, اندازه);
                } وإلا {
                    WIN_سېټ_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } وإلا إذا (SDL_strcmp(mime_type, "image/png") == 0) {
        إذا (Is_Clipboard_Format_شته(GetClipboardFormatPNG())) {
            إذا (WIN_OpenClipboard(_this)) {
                HANDLE hMem = Get_Clipboard_معلومات(GetClipboardFormatPNG());
                إذا (hMem) {
                    size_t mem_اندازه = Global_اندازه(hMem);
                    فراغ *mem = Global_قلف(hMem);
                    إذا (mem) {
                        معلومات = SDL_malloc(mem_اندازه);
                        إذا (معلومات) {
                            SDL_memcpy(معلومات, mem, mem_اندازه);
                            *اندازه = mem_اندازه;
                        }
                        GlobalUnlock(hMem);
                    } وإلا {
                        WIN_سېټ_Error("Couldn't lock clipboard data");
                    }
                } وإلا {
                    WIN_سېټ_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } وإلا {
        معلومات = SDL_Get_دننی_Clipboard_معلومات(_this, mime_type, اندازه);
    }
    أرجع معلومات;
}

bool WIN_Has_Clipboard_معلومات(SDL_VideoDevice *_this, ثابت حرف *mime_type)
{
    إذا (SDL_Is_متن_Mime_Type(mime_type)) {
        إذا (Is_Clipboard_Format_شته(CF_UNICODETEXT) || Is_Clipboard_Format_شته(CF_متن)) {
            أرجع true;
        }
    } وإلا إذا (SDL_strcmp(mime_type, "image/bmp") == 0) {
        إذا (Is_Clipboard_Format_شته(CF_DIBV5) || Is_Clipboard_Format_شته(CF_DIB)) {
            أرجع true;
        }
    } وإلا إذا (SDL_strcmp(mime_type, "image/png") == 0) {
        إذا (Is_Clipboard_Format_شته(GetClipboardFormatPNG())) {
            أرجع true;
        }
    }
    أرجع SDL_Has_دننی_Clipboard_معلومات(_this, mime_type);
}

ساكن صحيح GetClipboardFormatMimeType(UINT format, حرف *name)
{
    ثابت حرف *mime_type = عدم;

    بدل (format) {
    حالة CF_متن:
        mime_type = "text/plain";
        اكسر;
    حالة CF_UNICODETEXT:
        mime_type = "text/plain;charset=utf-8";
        اكسر;
    حالة CF_DIB:
    حالة CF_DIBV5:
        mime_type = "image/bmp";
        اكسر;
    افتراضي:
        إذا (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        اكسر;
    }
    إذا (mime_type) {
        size_t len = SDL_strlen(mime_type) + 1;
        إذا (name) {
            SDL_memcpy(name, mime_type, len);
        }
        أرجع (صحيح)len;
    }
    أرجع 0;
}

ساكن حرف **GetMimeTypes(صحيح *pnformats)
{
    حرف **new_mime_types = عدم;

    *pnformats = 0;

    إذا (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        صحيح nformats = 0;
        UINT format = 0;
        صحيح formatsSz = 0;
        bool have_image_bmp = false;
        لكل ( ; ; ) {
            format = EnumClipboardFormats(format);
            إذا (!format) {
                اكسر;
            }

#که_تعریف_شوی DEBUG_CLIPBOARD
            حرف name[128] = { 0 };
            GetClipboardFormatNameA(format, name, حجم(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#د_که_پای

            إذا (format == CF_DIB || format == CF_DIBV5) {
                إذا (have_image_bmp) {
                    // We have already registered this format
                    استمر;
                }
                have_image_bmp = true;
            }

            صحيح len = GetClipboardFormatMimeType(format, عدم);
            إذا (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_Allocate_Temporary_حافظه((nformats + 1) * حجم(حرف *) + formatsSz);
        إذا (new_mime_types) {
            format = 0;
            حرف *strPtr = (حرف *)(new_mime_types + nformats + 1);
            صحيح i = 0;
            لكل ( ; ; ) {
                format = EnumClipboardFormats(format);
                إذا (!format) {
                    اكسر;
                }

                إذا (format == CF_DIB || format == CF_DIBV5) {
                    إذا (have_image_bmp) {
                        // We have already registered this format
                        استمر;
                    }
                    have_image_bmp = true;
                }

                صحيح len = GetClipboardFormatMimeType(format, strPtr);
                إذا (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = عدم;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    أرجع new_mime_types;
}

فراغ WIN_CheckClipboardUpdate(بنية SDL_Video_معلومات *معلومات)
{
    DWORD شمېر = Get_Clipboard_Sequence_شمېره();
    إذا (شمېر != معلومات->clipboard_شمېر) {
        إذا (شمېر) {
            صحيح nformats = 0;
            حرف **new_mime_types = GetMimeTypes(&nformats);
            إذا (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        معلومات->clipboard_شمېر = شمېر;
    }
}

#د_که_پای // SDL_VIDEO_DRIVER_WINDOWS
