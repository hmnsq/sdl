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

#define BFT_BITMAP 0x4d42 // 'BM'

// Assume we can directly read and write BMP fields without byte swapping
SDL_COMPILE_TIME_ASSERT(verify_byte_order, SDL_BYTEORDER == SDL_LIL_ENDIAN);

ایستا UINT GetClipboardFormatPNG(تهی)
{
    ایستا UINT format;

    اگر (!format) {
        format = RegisterClipboardFormat(TEXT("PNG"));
    }
    بازگشت format;
}

ایستا BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    ثابت صحیح MAX_ATTEMPTS = 3;
    صحیح attempt;
    HWND hwnd = پوچ;

    اگر (_this->windows) {
        hwnd = _this->windows->internal->hwnd;
    }
    برای (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        اگر (OpenClipboard(hwnd)) {
            بازگشت TRUE;
        }
        SDL_Delay(10);
    }
    بازگشت FALSE;
}

ایستا تهی WIN_CloseClipboard(تهی)
{
    CloseClipboard();
}

ایستا HANDLE WIN_ConvertBMPtoDIB(ثابت تهی *bmp, size_t bmp_size, UINT *format)
{
    HANDLE hMem = پوچ;

    اگر (bmp && bmp_size > اندازه(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + اندازه(BITMAPFILEHEADER));
        size_t bih_size = pbih->biSize + pbih->biClrUsed * اندازه(RGBQUAD);
        size_t pixels_size = pbih->biSizeImage;

        اگر (pbih->biSize >= اندازه(BITMAPV5HEADER)) {
            *format = CF_DIBV5;
        } وگرنه {
            *format = CF_DIB;
        }

        اگر (pbfh->bfOffBits >= (اندازه(BITMAPFILEHEADER) + bih_size) &&
            (pbfh->bfOffBits + pixels_size) <= bmp_size) {
            ثابت Uint8 *pixels = (ثابت Uint8 *)bmp + pbfh->bfOffBits;
            size_t dib_size = bih_size + pixels_size;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_size);
            اگر (hMem) {
                LPVOID dst = GlobalLock(hMem);
                اگر (dst) {
                    SDL_memcpy(dst, pbih, bih_size);
                    SDL_memcpy((Uint8 *)dst + bih_size, pixels, pixels_size);
                    GlobalUnlock(hMem);
                } وگرنه {
                    WIN_SetError("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = پوچ;
                }
            } وگرنه {
                SDL_OutOfMemory();
            }
        } وگرنه {
            SDL_SetError("Invalid BMP data");
        }
    } وگرنه {
        SDL_SetError("Invalid BMP data");
    }
    بازگشت hMem;
}

ایستا تهی *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *size)
{
    تهی *bmp = پوچ;
    size_t mem_size = GlobalSize(hMem);

    اگر (mem_size > اندازه(BITMAPINFOHEADER)) {
        LPVOID dib = GlobalLock(hMem);
        اگر (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_table_size;
            انتخاب (pbih->biCompression) {
            حالت BI_RGB:
                اگر (pbih->bi_Bit_شمار <= 8) {
                    color_table_size = اندازه(RGBQUAD) * (pbih->biClrUsed == 0 ? 1 << pbih->bi_Bit_شمار : pbih->biClrUsed);
                } وگرنه {
                    color_table_size = 0;
                }
                بشکن;
            حالت BI_BITFIELDS:
                color_table_size = 3 * اندازه(DWORD);
                بشکن;
            حالت 6 /* BI_ALPHABITFIELDS */:
                // https://learn.microsoft.com/en-us/previous-versions/windows/embedded/aa452885(v=msdn.10)
                color_table_size = 4 * اندازه(DWORD);
                بشکن;
            پیشفرض: // FOURCC
                color_table_size = اندازه(RGBQUAD) * pbih->biClrUsed;
            }

            size_t bih_size = pbih->biSize + color_table_size;
            size_t dib_size = bih_size + pbih->biSizeImage;
            اگر (dib_size <= mem_size) {
                size_t bmp_size = اندازه(BITMAPFILEHEADER) + mem_size;
                bmp = SDL_malloc(bmp_size);
                اگر (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bfSize = (DWORD)bmp_size;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bfOffBits = (DWORD)(اندازه(BITMAPFILEHEADER) + pbih->biSize + color_table_size);
                    SDL_memcpy((Uint8 *)bmp + اندازه(BITMAPFILEHEADER), dib, mem_size);
                    *size = bmp_size;
                }
            } وگرنه {
                SDL_SetError("Invalid BMP data");
            }
            GlobalUnlock(hMem);
        } وگرنه {
            WIN_SetError("GlobalLock()");
        }
    } وگرنه {
        SDL_SetError("Invalid BMP data");
    }
    بازگشت bmp;
}

ایستا bool WIN_SetClipboardImage(SDL_VideoDevice *_this, ثابت نویسه *mime_type)
{
    UINT format = 0;
    HANDLE hMem = پوچ;
    size_t clipboard_data_size;
    ثابت تهی *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    اگر (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_data, clipboard_data_size, &format);
    } وگرنه اگر (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_data_size);
        اگر (hMem) {
            LPVOID dst = GlobalLock(hMem);
            اگر (dst) {
                SDL_memcpy(dst, clipboard_data, clipboard_data_size);
                GlobalUnlock(hMem);
            } وگرنه {
                result = WIN_SetError("GlobalLock()");
                GlobalFree(hMem);
                hMem = پوچ;
            }
        } وگرنه {
            result = SDL_OutOfMemory();
        }
    } وگرنه {
        result = SDL_SetError("Unknown image format");
    }
    اگر (hMem) {
        // Save the image to the clipboard
        اگر (!SetClipboardData(format, hMem)) {
            result = WIN_SetError("Couldn't set clipboard data");
        }
    } وگرنه {
        // WIN_ConvertBMPtoDIB() set the error
        result = false;
    }
    بازگشت result;
}

ایستا bool WIN_SetClipboardText(SDL_VideoDevice *_this, ثابت نویسه *mime_type)
{
    HANDLE hMem;
    size_t clipboard_data_size;
    ثابت تهی *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    اگر (clipboard_data && clipboard_data_size > 0) {
        SIZE_T i, size;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (ثابت نویسه *)clipboard_data, clipboard_data_size);
        اگر (!tstr) {
            بازگشت SDL_SetError("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        برای (size = 0, i = 0; tstr[i]; ++i, ++size) {
            اگر (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++size;
            }
        }
        size = (size + 1) * اندازه(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, size);
        اگر (hMem) {
            LPWSTR dst = (LPWSTR)GlobalLock(hMem);
            اگر (dst) {
                // Copy the text over, adding carriage returns as necessary
                برای (i = 0; tstr[i]; ++i) {
                    اگر (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            اگر (!SetClipboardData(CF_UNICODETEXT, hMem)) {
                result = WIN_SetError("Couldn't set clipboard data");
            }
        } وگرنه {
            result = SDL_OutOfMemory();
        }
        SDL_free(tstr);
    }
    بازگشت result;
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

    اگر (WIN_OpenClipboard(_this)) {
        EmptyClipboard();

        // Set the clipboard text
        برای (i = 0; i < _this->رقم_clipboard_mime_types; ++i) {
            ثابت نویسه *mime_type = _this->clipboard_mime_types[i];

            اگر (SDL_IsTextMimeType(mime_type)) {
                اگر (!WIN_SetClipboardText(_this, mime_type)) {
                    result = false;
                }
                // Only set the first clipboard text
                بشکن;
            }
        }

        // Set the clipboard image
        برای (i = 0; i < _this->رقم_clipboard_mime_types; ++i) {
            ثابت نویسه *mime_type = _this->clipboard_mime_types[i];

            اگر (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                اگر (!WIN_SetClipboardImage(_this, mime_type)) {
                    result = false;
                }
                بشکن;
            }
        }

        data->clipboard_شمار = Get_Clipboard_Sequence_عدد();
        WIN_CloseClipboard();
    } وگرنه {
        result = WIN_SetError("Couldn't open clipboard");
    }
    بازگشت result;
}

تهی *WIN_GetClipboardData(SDL_VideoDevice *_this, ثابت نویسه *mime_type, size_t *size)
{
    تهی *data = پوچ;

    اگر (SDL_IsTextMimeType(mime_type)) {
        نویسه *text = پوچ;

        اگر (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
            اگر (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = GetClipboardData(CF_UNICODETEXT);
                اگر (hMem) {
                    str = (LPTSTR)GlobalLock(hMem);
                    اگر (str) {
                        text = WIN_StringToUTF8W(str);
                        GlobalUnlock(hMem);
                    } وگرنه {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } وگرنه {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } وگرنه اگر (IsClipboardFormatAvailable(CF_TEXT)) {
            اگر (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = GetClipboardData(CF_TEXT);
                اگر (hMem) {
                    str = (LPCSTR)GlobalLock(hMem);
                    اگر (str) {
                        text = SDL_strdup(str);
                        GlobalUnlock(hMem);
                    } وگرنه {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } وگرنه {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }
        اگر (!text) {
            text = SDL_strdup("");
        }
        data = text;
        *size = SDL_strlen(text);

    } وگرنه اگر (SDL_strcmp(mime_type, "image/bmp") == 0) {
        اگر (IsClipboardFormatAvailable(CF_DIBV5)) {
            اگر (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIBV5);
                اگر (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } وگرنه {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } وگرنه اگر (IsClipboardFormatAvailable(CF_DIB)) {
            اگر (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIB);
                اگر (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } وگرنه {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } وگرنه اگر (SDL_strcmp(mime_type, "image/png") == 0) {
        اگر (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            اگر (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(GetClipboardFormatPNG());
                اگر (hMem) {
                    size_t mem_size = GlobalSize(hMem);
                    تهی *mem = GlobalLock(hMem);
                    اگر (mem) {
                        data = SDL_malloc(mem_size);
                        اگر (data) {
                            SDL_memcpy(data, mem, mem_size);
                            *size = mem_size;
                        }
                        GlobalUnlock(hMem);
                    } وگرنه {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } وگرنه {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } وگرنه {
        data = SDL_GetInternalClipboardData(_this, mime_type, size);
    }
    بازگشت data;
}

bool WIN_HasClipboardData(SDL_VideoDevice *_this, ثابت نویسه *mime_type)
{
    اگر (SDL_IsTextMimeType(mime_type)) {
        اگر (IsClipboardFormatAvailable(CF_UNICODETEXT) || IsClipboardFormatAvailable(CF_TEXT)) {
            بازگشت true;
        }
    } وگرنه اگر (SDL_strcmp(mime_type, "image/bmp") == 0) {
        اگر (IsClipboardFormatAvailable(CF_DIBV5) || IsClipboardFormatAvailable(CF_DIB)) {
            بازگشت true;
        }
    } وگرنه اگر (SDL_strcmp(mime_type, "image/png") == 0) {
        اگر (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            بازگشت true;
        }
    }
    بازگشت SDL_HasInternalClipboardData(_this, mime_type);
}

ایستا صحیح GetClipboardFormatMimeType(UINT format, نویسه *name)
{
    ثابت نویسه *mime_type = پوچ;

    انتخاب (format) {
    حالت CF_TEXT:
        mime_type = "text/plain";
        بشکن;
    حالت CF_UNICODETEXT:
        mime_type = "text/plain;charset=utf-8";
        بشکن;
    حالت CF_DIB:
    حالت CF_DIBV5:
        mime_type = "image/bmp";
        بشکن;
    پیشفرض:
        اگر (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        بشکن;
    }
    اگر (mime_type) {
        size_t len = SDL_strlen(mime_type) + 1;
        اگر (name) {
            SDL_memcpy(name, mime_type, len);
        }
        بازگشت (صحیح)len;
    }
    بازگشت 0;
}

ایستا نویسه **GetMimeTypes(صحیح *pnformats)
{
    نویسه **new_mime_types = پوچ;

    *pnformats = 0;

    اگر (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        صحیح nformats = 0;
        UINT format = 0;
        صحیح formatsSz = 0;
        bool have_image_bmp = false;
        برای ( ; ; ) {
            format = EnumClipboardFormats(format);
            اگر (!format) {
                بشکن;
            }

#ifdef DEBUG_CLIPBOARD
            نویسه name[128] = { 0 };
            GetClipboardFormatNameA(format, name, اندازه(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#endif

            اگر (format == CF_DIB || format == CF_DIBV5) {
                اگر (have_image_bmp) {
                    // We have already registered this format
                    ادامه;
                }
                have_image_bmp = true;
            }

            صحیح len = GetClipboardFormatMimeType(format, پوچ);
            اگر (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_AllocateTemporaryMemory((nformats + 1) * اندازه(نویسه *) + formatsSz);
        اگر (new_mime_types) {
            format = 0;
            نویسه *strPtr = (نویسه *)(new_mime_types + nformats + 1);
            صحیح i = 0;
            برای ( ; ; ) {
                format = EnumClipboardFormats(format);
                اگر (!format) {
                    بشکن;
                }

                اگر (format == CF_DIB || format == CF_DIBV5) {
                    اگر (have_image_bmp) {
                        // We have already registered this format
                        ادامه;
                    }
                    have_image_bmp = true;
                }

                صحیح len = GetClipboardFormatMimeType(format, strPtr);
                اگر (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = پوچ;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    بازگشت new_mime_types;
}

تهی WIN_CheckClipboardUpdate(ساختار SDL_VideoData *data)
{
    DWORD شمار = Get_Clipboard_Sequence_عدد();
    اگر (شمار != data->clipboard_شمار) {
        اگر (شمار) {
            صحیح nformats = 0;
            نویسه **new_mime_types = GetMimeTypes(&nformats);
            اگر (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        data->clipboard_شمار = شمار;
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
