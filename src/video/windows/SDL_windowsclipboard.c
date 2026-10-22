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

#define BFT_BITMAP 0x4d42 // 'BM'

// Assume we can directly read and write BMP fields without byte swapping
SDL_COMPILE_TIME_ASSERT(verify_byte_order, SDL_BYTEORDER == SDL_LIL_ENDIAN);

ساكن UINT GetClipboardFormatPNG(فراغ)
{
    ساكن UINT format;

    إذا (!format) {
        format = RegisterClipboardFormat(TEXT("PNG"));
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
        hwnd = _this->windows->internal->hwnd;
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

ساكن HANDLE WIN_ConvertBMPtoDIB(ثابت فراغ *bmp, size_t bmp_size, UINT *format)
{
    HANDLE hMem = عدم;

    إذا (bmp && bmp_size > حجم(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + حجم(BITMAPFILEHEADER));
        size_t bih_size = pbih->biSize + pbih->biClrUsed * حجم(RGBQUAD);
        size_t pixels_size = pbih->biSizeImage;

        إذا (pbih->biSize >= حجم(BITMAPV5HEADER)) {
            *format = CF_DIBV5;
        } وإلا {
            *format = CF_DIB;
        }

        إذا (pbfh->bfOffBits >= (حجم(BITMAPFILEHEADER) + bih_size) &&
            (pbfh->bfOffBits + pixels_size) <= bmp_size) {
            ثابت Uint8 *pixels = (ثابت Uint8 *)bmp + pbfh->bfOffBits;
            size_t dib_size = bih_size + pixels_size;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_size);
            إذا (hMem) {
                LPVOID dst = GlobalLock(hMem);
                إذا (dst) {
                    SDL_memcpy(dst, pbih, bih_size);
                    SDL_memcpy((Uint8 *)dst + bih_size, pixels, pixels_size);
                    GlobalUnlock(hMem);
                } وإلا {
                    WIN_SetError("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = عدم;
                }
            } وإلا {
                SDL_OutOfMemory();
            }
        } وإلا {
            SDL_SetError("Invalid BMP data");
        }
    } وإلا {
        SDL_SetError("Invalid BMP data");
    }
    أرجع hMem;
}

ساكن فراغ *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *size)
{
    فراغ *bmp = عدم;
    size_t mem_size = GlobalSize(hMem);

    إذا (mem_size > حجم(BITMAPINFOHEADER)) {
        LPVOID dib = GlobalLock(hMem);
        إذا (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_table_size;
            بدل (pbih->biCompression) {
            حالة BI_RGB:
                إذا (pbih->bi_Bit_گنتی <= 8) {
                    color_table_size = حجم(RGBQUAD) * (pbih->biClrUsed == 0 ? 1 << pbih->bi_Bit_گنتی : pbih->biClrUsed);
                } وإلا {
                    color_table_size = 0;
                }
                اكسر;
            حالة BI_BITFIELDS:
                color_table_size = 3 * حجم(DWORD);
                اكسر;
            حالة 6 /* BI_ALPHABITFIELDS */:
                // https://learn.microsoft.com/en-us/previous-versions/windows/embedded/aa452885(v=msdn.10)
                color_table_size = 4 * حجم(DWORD);
                اكسر;
            افتراضي: // FOURCC
                color_table_size = حجم(RGBQUAD) * pbih->biClrUsed;
            }

            size_t bih_size = pbih->biSize + color_table_size;
            size_t dib_size = bih_size + pbih->biSizeImage;
            إذا (dib_size <= mem_size) {
                size_t bmp_size = حجم(BITMAPFILEHEADER) + mem_size;
                bmp = SDL_malloc(bmp_size);
                إذا (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bfSize = (DWORD)bmp_size;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bfOffBits = (DWORD)(حجم(BITMAPFILEHEADER) + pbih->biSize + color_table_size);
                    SDL_memcpy((Uint8 *)bmp + حجم(BITMAPFILEHEADER), dib, mem_size);
                    *size = bmp_size;
                }
            } وإلا {
                SDL_SetError("Invalid BMP data");
            }
            GlobalUnlock(hMem);
        } وإلا {
            WIN_SetError("GlobalLock()");
        }
    } وإلا {
        SDL_SetError("Invalid BMP data");
    }
    أرجع bmp;
}

ساكن bool WIN_SetClipboardImage(SDL_VideoDevice *_this, ثابت حرف *mime_type)
{
    UINT format = 0;
    HANDLE hMem = عدم;
    size_t clipboard_data_size;
    ثابت فراغ *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    إذا (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_data, clipboard_data_size, &format);
    } وإلا إذا (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_data_size);
        إذا (hMem) {
            LPVOID dst = GlobalLock(hMem);
            إذا (dst) {
                SDL_memcpy(dst, clipboard_data, clipboard_data_size);
                GlobalUnlock(hMem);
            } وإلا {
                result = WIN_SetError("GlobalLock()");
                GlobalFree(hMem);
                hMem = عدم;
            }
        } وإلا {
            result = SDL_OutOfMemory();
        }
    } وإلا {
        result = SDL_SetError("Unknown image format");
    }
    إذا (hMem) {
        // Save the image to the clipboard
        إذا (!SetClipboardData(format, hMem)) {
            result = WIN_SetError("Couldn't set clipboard data");
        }
    } وإلا {
        // WIN_ConvertBMPtoDIB() set the error
        result = false;
    }
    أرجع result;
}

ساكن bool WIN_SetClipboardText(SDL_VideoDevice *_this, ثابت حرف *mime_type)
{
    HANDLE hMem;
    size_t clipboard_data_size;
    ثابت فراغ *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    إذا (clipboard_data && clipboard_data_size > 0) {
        SIZE_T i, size;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (ثابت حرف *)clipboard_data, clipboard_data_size);
        إذا (!tstr) {
            أرجع SDL_SetError("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        لكل (size = 0, i = 0; tstr[i]; ++i, ++size) {
            إذا (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++size;
            }
        }
        size = (size + 1) * حجم(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, size);
        إذا (hMem) {
            LPWSTR dst = (LPWSTR)GlobalLock(hMem);
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

            إذا (!SetClipboardData(CF_UNICODETEXT, hMem)) {
                result = WIN_SetError("Couldn't set clipboard data");
            }
        } وإلا {
            result = SDL_OutOfMemory();
        }
        SDL_free(tstr);
    }
    أرجع result;
}

bool WIN_SetClipboardData(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    size_t i;
    bool result = true;

    /* I investigated delayed clipboard rendering, and at least with text and image
     * formats you have to use an output window, not SDL_HelperWindow, and the system
     * requests them being rendered immediately, so there isn't any benefit.
     */

    إذا (WIN_OpenClipboard(_this)) {
        EmptyClipboard();

        // Set the clipboard text
        لكل (i = 0; i < _this->عدد_clipboard_mime_types; ++i) {
            ثابت حرف *mime_type = _this->clipboard_mime_types[i];

            إذا (SDL_IsTextMimeType(mime_type)) {
                إذا (!WIN_SetClipboardText(_this, mime_type)) {
                    result = false;
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
                إذا (!WIN_SetClipboardImage(_this, mime_type)) {
                    result = false;
                }
                اكسر;
            }
        }

        data->clipboard_گنتی = Get_Clipboard_Sequence_نمبر();
        WIN_CloseClipboard();
    } وإلا {
        result = WIN_SetError("Couldn't open clipboard");
    }
    أرجع result;
}

فراغ *WIN_GetClipboardData(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *size)
{
    فراغ *data = عدم;

    إذا (SDL_IsTextMimeType(mime_type)) {
        حرف *text = عدم;

        إذا (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
            إذا (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = GetClipboardData(CF_UNICODETEXT);
                إذا (hMem) {
                    str = (LPTSTR)GlobalLock(hMem);
                    إذا (str) {
                        text = WIN_StringToUTF8W(str);
                        GlobalUnlock(hMem);
                    } وإلا {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } وإلا {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } وإلا إذا (IsClipboardFormatAvailable(CF_TEXT)) {
            إذا (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = GetClipboardData(CF_TEXT);
                إذا (hMem) {
                    str = (LPCSTR)GlobalLock(hMem);
                    إذا (str) {
                        text = SDL_strdup(str);
                        GlobalUnlock(hMem);
                    } وإلا {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } وإلا {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }
        إذا (!text) {
            text = SDL_strdup("");
        }
        data = text;
        *size = SDL_strlen(text);

    } وإلا إذا (SDL_strcmp(mime_type, "image/bmp") == 0) {
        إذا (IsClipboardFormatAvailable(CF_DIBV5)) {
            إذا (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIBV5);
                إذا (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } وإلا {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } وإلا إذا (IsClipboardFormatAvailable(CF_DIB)) {
            إذا (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIB);
                إذا (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } وإلا {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } وإلا إذا (SDL_strcmp(mime_type, "image/png") == 0) {
        إذا (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            إذا (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(GetClipboardFormatPNG());
                إذا (hMem) {
                    size_t mem_size = GlobalSize(hMem);
                    فراغ *mem = GlobalLock(hMem);
                    إذا (mem) {
                        data = SDL_malloc(mem_size);
                        إذا (data) {
                            SDL_memcpy(data, mem, mem_size);
                            *size = mem_size;
                        }
                        GlobalUnlock(hMem);
                    } وإلا {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } وإلا {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } وإلا {
        data = SDL_GetInternalClipboardData(_this, mime_type, size);
    }
    أرجع data;
}

bool WIN_HasClipboardData(SDL_VideoDevice *_this, ثابت حرف *mime_type)
{
    إذا (SDL_IsTextMimeType(mime_type)) {
        إذا (IsClipboardFormatAvailable(CF_UNICODETEXT) || IsClipboardFormatAvailable(CF_TEXT)) {
            أرجع true;
        }
    } وإلا إذا (SDL_strcmp(mime_type, "image/bmp") == 0) {
        إذا (IsClipboardFormatAvailable(CF_DIBV5) || IsClipboardFormatAvailable(CF_DIB)) {
            أرجع true;
        }
    } وإلا إذا (SDL_strcmp(mime_type, "image/png") == 0) {
        إذا (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            أرجع true;
        }
    }
    أرجع SDL_HasInternalClipboardData(_this, mime_type);
}

ساكن صحيح GetClipboardFormatMimeType(UINT format, حرف *name)
{
    ثابت حرف *mime_type = عدم;

    بدل (format) {
    حالة CF_TEXT:
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

#ifdef DEBUG_CLIPBOARD
            حرف name[128] = { 0 };
            GetClipboardFormatNameA(format, name, حجم(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#endif

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
        new_mime_types = SDL_AllocateTemporaryMemory((nformats + 1) * حجم(حرف *) + formatsSz);
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

فراغ WIN_CheckClipboardUpdate(بنية SDL_VideoData *data)
{
    DWORD گنتی = Get_Clipboard_Sequence_نمبر();
    إذا (گنتی != data->clipboard_گنتی) {
        إذا (گنتی) {
            صحيح nformats = 0;
            حرف **new_mime_types = GetMimeTypes(&nformats);
            إذا (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        data->clipboard_گنتی = گنتی;
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
