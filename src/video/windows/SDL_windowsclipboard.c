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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಯದಿ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ಅನ್ತರ್ಭಾವ "SDL_windowsvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowswindow.h"
#ಅನ್ತರ್ಭಾವ "../SDL_clipboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_clipboardevents_c.h"

#define BFT_BITMAP 0x4d42 // 'BM'

// Assume we can directly read and write BMP fields without byte swapping
SDL_COMPILE_TIME_ASSERT(verify_byte_order, SDL_BYTEORDER == SDL_LIL_ENDIAN);

ಸ್ಥಿರ UINT GetClipboardFormatPNG(ಶೂನ್ಯ)
{
    ಸ್ಥಿರ UINT format;

    ಯದಿ (!format) {
        format = RegisterClipboardFormat(TEXT("PNG"));
    }
    ಪ್ರತ್ಯಾಗಮ format;
}

ಸ್ಥಿರ BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ MAX_ATTEMPTS = 3;
    ಪೂರ್ಣಾಙ್ಕ attempt;
    HWND hwnd = ರಿಕ್ತ;

    ಯದಿ (_this->windows) {
        hwnd = _this->windows->internal->hwnd;
    }
    ಪ್ರತಿ (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        ಯದಿ (OpenClipboard(hwnd)) {
            ಪ್ರತ್ಯಾಗಮ TRUE;
        }
        SDL_Delay(10);
    }
    ಪ್ರತ್ಯಾಗಮ FALSE;
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_CloseClipboard(ಶೂನ್ಯ)
{
    CloseClipboard();
}

ಸ್ಥಿರ HANDLE WIN_ConvertBMPtoDIB(ಧ್ರುವ ಶೂನ್ಯ *bmp, size_t bmp_size, UINT *format)
{
    HANDLE hMem = ರಿಕ್ತ;

    ಯದಿ (bmp && bmp_size > ಪರಿಮಾಣ(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + ಪರಿಮಾಣ(BITMAPFILEHEADER));
        size_t bih_size = pbih->biSize + pbih->biClrUsed * ಪರಿಮಾಣ(RGBQUAD);
        size_t pixels_size = pbih->biSizeImage;

        ಯದಿ (pbih->biSize >= ಪರಿಮಾಣ(BITMAPV5HEADER)) {
            *format = CF_DIBV5;
        } ಅನ್ಯಥಾ {
            *format = CF_DIB;
        }

        ಯದಿ (pbfh->bfOffBits >= (ಪರಿಮಾಣ(BITMAPFILEHEADER) + bih_size) &&
            (pbfh->bfOffBits + pixels_size) <= bmp_size) {
            ಧ್ರುವ Uint8 *pixels = (ಧ್ರುವ Uint8 *)bmp + pbfh->bfOffBits;
            size_t dib_size = bih_size + pixels_size;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_size);
            ಯದಿ (hMem) {
                LPVOID dst = GlobalLock(hMem);
                ಯದಿ (dst) {
                    SDL_memcpy(dst, pbih, bih_size);
                    SDL_memcpy((Uint8 *)dst + bih_size, pixels, pixels_size);
                    GlobalUnlock(hMem);
                } ಅನ್ಯಥಾ {
                    WIN_SetError("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = ರಿಕ್ತ;
                }
            } ಅನ್ಯಥಾ {
                SDL_OutOfMemory();
            }
        } ಅನ್ಯಥಾ {
            SDL_SetError("Invalid BMP data");
        }
    } ಅನ್ಯಥಾ {
        SDL_SetError("Invalid BMP data");
    }
    ಪ್ರತ್ಯಾಗಮ hMem;
}

ಸ್ಥಿರ ಶೂನ್ಯ *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *size)
{
    ಶೂನ್ಯ *bmp = ರಿಕ್ತ;
    size_t mem_size = GlobalSize(hMem);

    ಯದಿ (mem_size > ಪರಿಮಾಣ(BITMAPINFOHEADER)) {
        LPVOID dib = GlobalLock(hMem);
        ಯದಿ (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_table_size;
            ವಿಕಲ್ಪ (pbih->biCompression) {
            ಪಕ್ಷ BI_RGB:
                ಯದಿ (pbih->bi_Bit_ಎಣಿಕೆ <= 8) {
                    color_table_size = ಪರಿಮಾಣ(RGBQUAD) * (pbih->biClrUsed == 0 ? 1 << pbih->bi_Bit_ಎಣಿಕೆ : pbih->biClrUsed);
                } ಅನ್ಯಥಾ {
                    color_table_size = 0;
                }
                ಭಙ್ಗ;
            ಪಕ್ಷ BI_BITFIELDS:
                color_table_size = 3 * ಪರಿಮಾಣ(DWORD);
                ಭಙ್ಗ;
            ಪಕ್ಷ 6 /* BI_ALPHABITFIELDS */:
                // https://learn.microsoft.com/en-us/previous-versions/windows/embedded/aa452885(v=msdn.10)
                color_table_size = 4 * ಪರಿಮಾಣ(DWORD);
                ಭಙ್ಗ;
            ಸ್ವಭಾವ: // FOURCC
                color_table_size = ಪರಿಮಾಣ(RGBQUAD) * pbih->biClrUsed;
            }

            size_t bih_size = pbih->biSize + color_table_size;
            size_t dib_size = bih_size + pbih->biSizeImage;
            ಯದಿ (dib_size <= mem_size) {
                size_t bmp_size = ಪರಿಮಾಣ(BITMAPFILEHEADER) + mem_size;
                bmp = SDL_malloc(bmp_size);
                ಯದಿ (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bfSize = (DWORD)bmp_size;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bfOffBits = (DWORD)(ಪರಿಮಾಣ(BITMAPFILEHEADER) + pbih->biSize + color_table_size);
                    SDL_memcpy((Uint8 *)bmp + ಪರಿಮಾಣ(BITMAPFILEHEADER), dib, mem_size);
                    *size = bmp_size;
                }
            } ಅನ್ಯಥಾ {
                SDL_SetError("Invalid BMP data");
            }
            GlobalUnlock(hMem);
        } ಅನ್ಯಥಾ {
            WIN_SetError("GlobalLock()");
        }
    } ಅನ್ಯಥಾ {
        SDL_SetError("Invalid BMP data");
    }
    ಪ್ರತ್ಯಾಗಮ bmp;
}

ಸ್ಥಿರ bool WIN_SetClipboardImage(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *mime_type)
{
    UINT format = 0;
    HANDLE hMem = ರಿಕ್ತ;
    size_t clipboard_data_size;
    ಧ್ರುವ ಶೂನ್ಯ *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    ಯದಿ (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_data, clipboard_data_size, &format);
    } ಅನ್ಯಥಾ ಯದಿ (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_data_size);
        ಯದಿ (hMem) {
            LPVOID dst = GlobalLock(hMem);
            ಯದಿ (dst) {
                SDL_memcpy(dst, clipboard_data, clipboard_data_size);
                GlobalUnlock(hMem);
            } ಅನ್ಯಥಾ {
                result = WIN_SetError("GlobalLock()");
                GlobalFree(hMem);
                hMem = ರಿಕ್ತ;
            }
        } ಅನ್ಯಥಾ {
            result = SDL_OutOfMemory();
        }
    } ಅನ್ಯಥಾ {
        result = SDL_SetError("Unknown image format");
    }
    ಯದಿ (hMem) {
        // Save the image to the clipboard
        ಯದಿ (!SetClipboardData(format, hMem)) {
            result = WIN_SetError("Couldn't set clipboard data");
        }
    } ಅನ್ಯಥಾ {
        // WIN_ConvertBMPtoDIB() set the error
        result = false;
    }
    ಪ್ರತ್ಯಾಗಮ result;
}

ಸ್ಥಿರ bool WIN_SetClipboardText(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *mime_type)
{
    HANDLE hMem;
    size_t clipboard_data_size;
    ಧ್ರುವ ಶೂನ್ಯ *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    ಯದಿ (clipboard_data && clipboard_data_size > 0) {
        SIZE_T i, size;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (ಧ್ರುವ ವರ್ಣ *)clipboard_data, clipboard_data_size);
        ಯದಿ (!tstr) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        ಪ್ರತಿ (size = 0, i = 0; tstr[i]; ++i, ++size) {
            ಯದಿ (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++size;
            }
        }
        size = (size + 1) * ಪರಿಮಾಣ(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, size);
        ಯದಿ (hMem) {
            LPWSTR dst = (LPWSTR)GlobalLock(hMem);
            ಯದಿ (dst) {
                // Copy the text over, adding carriage returns as necessary
                ಪ್ರತಿ (i = 0; tstr[i]; ++i) {
                    ಯದಿ (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            ಯದಿ (!SetClipboardData(CF_UNICODETEXT, hMem)) {
                result = WIN_SetError("Couldn't set clipboard data");
            }
        } ಅನ್ಯಥಾ {
            result = SDL_OutOfMemory();
        }
        SDL_free(tstr);
    }
    ಪ್ರತ್ಯಾಗಮ result;
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

    ಯದಿ (WIN_OpenClipboard(_this)) {
        EmptyClipboard();

        // Set the clipboard text
        ಪ್ರತಿ (i = 0; i < _this->ಅಂಕೆ_clipboard_mime_types; ++i) {
            ಧ್ರುವ ವರ್ಣ *mime_type = _this->clipboard_mime_types[i];

            ಯದಿ (SDL_IsTextMimeType(mime_type)) {
                ಯದಿ (!WIN_SetClipboardText(_this, mime_type)) {
                    result = false;
                }
                // Only set the first clipboard text
                ಭಙ್ಗ;
            }
        }

        // Set the clipboard image
        ಪ್ರತಿ (i = 0; i < _this->ಅಂಕೆ_clipboard_mime_types; ++i) {
            ಧ್ರುವ ವರ್ಣ *mime_type = _this->clipboard_mime_types[i];

            ಯದಿ (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                ಯದಿ (!WIN_SetClipboardImage(_this, mime_type)) {
                    result = false;
                }
                ಭಙ್ಗ;
            }
        }

        data->clipboard_ಎಣಿಕೆ = Get_Clipboard_Sequence_ಸಂಖ್ಯೆ();
        WIN_CloseClipboard();
    } ಅನ್ಯಥಾ {
        result = WIN_SetError("Couldn't open clipboard");
    }
    ಪ್ರತ್ಯಾಗಮ result;
}

ಶೂನ್ಯ *WIN_GetClipboardData(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *mime_type, size_t *size)
{
    ಶೂನ್ಯ *data = ರಿಕ್ತ;

    ಯದಿ (SDL_IsTextMimeType(mime_type)) {
        ವರ್ಣ *text = ರಿಕ್ತ;

        ಯದಿ (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
            ಯದಿ (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = GetClipboardData(CF_UNICODETEXT);
                ಯದಿ (hMem) {
                    str = (LPTSTR)GlobalLock(hMem);
                    ಯದಿ (str) {
                        text = WIN_StringToUTF8W(str);
                        GlobalUnlock(hMem);
                    } ಅನ್ಯಥಾ {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } ಅನ್ಯಥಾ {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } ಅನ್ಯಥಾ ಯದಿ (IsClipboardFormatAvailable(CF_TEXT)) {
            ಯದಿ (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = GetClipboardData(CF_TEXT);
                ಯದಿ (hMem) {
                    str = (LPCSTR)GlobalLock(hMem);
                    ಯದಿ (str) {
                        text = SDL_strdup(str);
                        GlobalUnlock(hMem);
                    } ಅನ್ಯಥಾ {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } ಅನ್ಯಥಾ {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }
        ಯದಿ (!text) {
            text = SDL_strdup("");
        }
        data = text;
        *size = SDL_strlen(text);

    } ಅನ್ಯಥಾ ಯದಿ (SDL_strcmp(mime_type, "image/bmp") == 0) {
        ಯದಿ (IsClipboardFormatAvailable(CF_DIBV5)) {
            ಯದಿ (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIBV5);
                ಯದಿ (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } ಅನ್ಯಥಾ {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } ಅನ್ಯಥಾ ಯದಿ (IsClipboardFormatAvailable(CF_DIB)) {
            ಯದಿ (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIB);
                ಯದಿ (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } ಅನ್ಯಥಾ {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } ಅನ್ಯಥಾ ಯದಿ (SDL_strcmp(mime_type, "image/png") == 0) {
        ಯದಿ (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            ಯದಿ (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(GetClipboardFormatPNG());
                ಯದಿ (hMem) {
                    size_t mem_size = GlobalSize(hMem);
                    ಶೂನ್ಯ *mem = GlobalLock(hMem);
                    ಯದಿ (mem) {
                        data = SDL_malloc(mem_size);
                        ಯದಿ (data) {
                            SDL_memcpy(data, mem, mem_size);
                            *size = mem_size;
                        }
                        GlobalUnlock(hMem);
                    } ಅನ್ಯಥಾ {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } ಅನ್ಯಥಾ {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } ಅನ್ಯಥಾ {
        data = SDL_GetInternalClipboardData(_this, mime_type, size);
    }
    ಪ್ರತ್ಯಾಗಮ data;
}

bool WIN_HasClipboardData(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *mime_type)
{
    ಯದಿ (SDL_IsTextMimeType(mime_type)) {
        ಯದಿ (IsClipboardFormatAvailable(CF_UNICODETEXT) || IsClipboardFormatAvailable(CF_TEXT)) {
            ಪ್ರತ್ಯಾಗಮ true;
        }
    } ಅನ್ಯಥಾ ಯದಿ (SDL_strcmp(mime_type, "image/bmp") == 0) {
        ಯದಿ (IsClipboardFormatAvailable(CF_DIBV5) || IsClipboardFormatAvailable(CF_DIB)) {
            ಪ್ರತ್ಯಾಗಮ true;
        }
    } ಅನ್ಯಥಾ ಯದಿ (SDL_strcmp(mime_type, "image/png") == 0) {
        ಯದಿ (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            ಪ್ರತ್ಯಾಗಮ true;
        }
    }
    ಪ್ರತ್ಯಾಗಮ SDL_HasInternalClipboardData(_this, mime_type);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ GetClipboardFormatMimeType(UINT format, ವರ್ಣ *name)
{
    ಧ್ರುವ ವರ್ಣ *mime_type = ರಿಕ್ತ;

    ವಿಕಲ್ಪ (format) {
    ಪಕ್ಷ CF_TEXT:
        mime_type = "text/plain";
        ಭಙ್ಗ;
    ಪಕ್ಷ CF_UNICODETEXT:
        mime_type = "text/plain;charset=utf-8";
        ಭಙ್ಗ;
    ಪಕ್ಷ CF_DIB:
    ಪಕ್ಷ CF_DIBV5:
        mime_type = "image/bmp";
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        ಯದಿ (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        ಭಙ್ಗ;
    }
    ಯದಿ (mime_type) {
        size_t len = SDL_strlen(mime_type) + 1;
        ಯದಿ (name) {
            SDL_memcpy(name, mime_type, len);
        }
        ಪ್ರತ್ಯಾಗಮ (ಪೂರ್ಣಾಙ್ಕ)len;
    }
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ವರ್ಣ **GetMimeTypes(ಪೂರ್ಣಾಙ್ಕ *pnformats)
{
    ವರ್ಣ **new_mime_types = ರಿಕ್ತ;

    *pnformats = 0;

    ಯದಿ (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        ಪೂರ್ಣಾಙ್ಕ nformats = 0;
        UINT format = 0;
        ಪೂರ್ಣಾಙ್ಕ formatsSz = 0;
        bool have_image_bmp = false;
        ಪ್ರತಿ ( ; ; ) {
            format = EnumClipboardFormats(format);
            ಯದಿ (!format) {
                ಭಙ್ಗ;
            }

#ifdef DEBUG_CLIPBOARD
            ವರ್ಣ name[128] = { 0 };
            GetClipboardFormatNameA(format, name, ಪರಿಮಾಣ(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#endif

            ಯದಿ (format == CF_DIB || format == CF_DIBV5) {
                ಯದಿ (have_image_bmp) {
                    // We have already registered this format
                    ಅನುವರ್ತ;
                }
                have_image_bmp = true;
            }

            ಪೂರ್ಣಾಙ್ಕ len = GetClipboardFormatMimeType(format, ರಿಕ್ತ);
            ಯದಿ (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_AllocateTemporaryMemory((nformats + 1) * ಪರಿಮಾಣ(ವರ್ಣ *) + formatsSz);
        ಯದಿ (new_mime_types) {
            format = 0;
            ವರ್ಣ *strPtr = (ವರ್ಣ *)(new_mime_types + nformats + 1);
            ಪೂರ್ಣಾಙ್ಕ i = 0;
            ಪ್ರತಿ ( ; ; ) {
                format = EnumClipboardFormats(format);
                ಯದಿ (!format) {
                    ಭಙ್ಗ;
                }

                ಯದಿ (format == CF_DIB || format == CF_DIBV5) {
                    ಯದಿ (have_image_bmp) {
                        // We have already registered this format
                        ಅನುವರ್ತ;
                    }
                    have_image_bmp = true;
                }

                ಪೂರ್ಣಾಙ್ಕ len = GetClipboardFormatMimeType(format, strPtr);
                ಯದಿ (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = ರಿಕ್ತ;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    ಪ್ರತ್ಯಾಗಮ new_mime_types;
}

ಶೂನ್ಯ WIN_CheckClipboardUpdate(ಸಂರಚನಾ SDL_VideoData *data)
{
    DWORD ಎಣಿಕೆ = Get_Clipboard_Sequence_ಸಂಖ್ಯೆ();
    ಯದಿ (ಎಣಿಕೆ != data->clipboard_ಎಣಿಕೆ) {
        ಯದಿ (ಎಣಿಕೆ) {
            ಪೂರ್ಣಾಙ್ಕ nformats = 0;
            ವರ್ಣ **new_mime_types = GetMimeTypes(&nformats);
            ಯದಿ (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        data->clipboard_ಎಣಿಕೆ = ಎಣಿಕೆ;
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
