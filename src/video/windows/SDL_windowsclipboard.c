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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ଯଦି defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ଅନ୍ତର୍ଭାଵ "SDL_windowsvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_windowswindow.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_clipboard_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_events_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_clipboardevents_c.h"

#define BFT_BITMAP 0x4d42 // 'BM'

// Assume we can directly read and write BMP fields without byte swapping
SDL_COMPILE_TIME_ASSERT(verify_byte_order, SDL_BYTEORDER == SDL_LIL_ENDIAN);

ସ୍ଥିର UINT GetClipboardFormatPNG(ଶୂନ୍ୟ)
{
    ସ୍ଥିର UINT format;

    ଯଦି (!format) {
        format = RegisterClipboardFormat(TEXT("PNG"));
    }
    ଫେରନ୍ତୁ format;
}

ସ୍ଥିର BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା MAX_ATTEMPTS = 3;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା attempt;
    HWND hwnd = ଖାଲି;

    ଯଦି (_this->windows) {
        hwnd = _this->windows->internal->hwnd;
    }
    ପାଇଁ (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        ଯଦି (OpenClipboard(hwnd)) {
            ଫେରନ୍ତୁ TRUE;
        }
        SDL_Delay(10);
    }
    ଫେରନ୍ତୁ FALSE;
}

ସ୍ଥିର ଶୂନ୍ୟ WIN_CloseClipboard(ଶୂନ୍ୟ)
{
    CloseClipboard();
}

ସ୍ଥିର HANDLE WIN_ConvertBMPtoDIB(ଅଚଳ ଶୂନ୍ୟ *bmp, size_t bmp_size, UINT *format)
{
    HANDLE hMem = ଖାଲି;

    ଯଦି (bmp && bmp_size > ଆକାର(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + ଆକାର(BITMAPFILEHEADER));
        size_t bih_size = pbih->biSize + pbih->biClrUsed * ଆକାର(RGBQUAD);
        size_t pixels_size = pbih->biSizeImage;

        ଯଦି (pbih->biSize >= ଆକାର(BITMAPV5HEADER)) {
            *format = CF_DIBV5;
        } ଅନ୍ୟଥା {
            *format = CF_DIB;
        }

        ଯଦି (pbfh->bfOffBits >= (ଆକାର(BITMAPFILEHEADER) + bih_size) &&
            (pbfh->bfOffBits + pixels_size) <= bmp_size) {
            ଅଚଳ Uint8 *pixels = (ଅଚଳ Uint8 *)bmp + pbfh->bfOffBits;
            size_t dib_size = bih_size + pixels_size;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_size);
            ଯଦି (hMem) {
                LPVOID dst = GlobalLock(hMem);
                ଯଦି (dst) {
                    SDL_memcpy(dst, pbih, bih_size);
                    SDL_memcpy((Uint8 *)dst + bih_size, pixels, pixels_size);
                    GlobalUnlock(hMem);
                } ଅନ୍ୟଥା {
                    WIN_SetError("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = ଖାଲି;
                }
            } ଅନ୍ୟଥା {
                SDL_OutOfMemory();
            }
        } ଅନ୍ୟଥା {
            SDL_SetError("Invalid BMP data");
        }
    } ଅନ୍ୟଥା {
        SDL_SetError("Invalid BMP data");
    }
    ଫେରନ୍ତୁ hMem;
}

ସ୍ଥିର ଶୂନ୍ୟ *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *size)
{
    ଶୂନ୍ୟ *bmp = ଖାଲି;
    size_t mem_size = GlobalSize(hMem);

    ଯଦି (mem_size > ଆକାର(BITMAPINFOHEADER)) {
        LPVOID dib = GlobalLock(hMem);
        ଯଦି (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_table_size;
            ବାଛ (pbih->biCompression) {
            ସ୍ଥିତି BI_RGB:
                ଯଦି (pbih->bi_Bit_ଗଣନା <= 8) {
                    color_table_size = ଆକାର(RGBQUAD) * (pbih->biClrUsed == 0 ? 1 << pbih->bi_Bit_ଗଣନା : pbih->biClrUsed);
                } ଅନ୍ୟଥା {
                    color_table_size = 0;
                }
                ଭାଙ୍ଗ;
            ସ୍ଥିତି BI_BITFIELDS:
                color_table_size = 3 * ଆକାର(DWORD);
                ଭାଙ୍ଗ;
            ସ୍ଥିତି 6 /* BI_ALPHABITFIELDS */:
                // https://learn.microsoft.com/en-us/previous-versions/windows/embedded/aa452885(v=msdn.10)
                color_table_size = 4 * ଆକାର(DWORD);
                ଭାଙ୍ଗ;
            ପୂର୍ବନିର୍ଦ୍ଧାରିତ: // FOURCC
                color_table_size = ଆକାର(RGBQUAD) * pbih->biClrUsed;
            }

            size_t bih_size = pbih->biSize + color_table_size;
            size_t dib_size = bih_size + pbih->biSizeImage;
            ଯଦି (dib_size <= mem_size) {
                size_t bmp_size = ଆକାର(BITMAPFILEHEADER) + mem_size;
                bmp = SDL_malloc(bmp_size);
                ଯଦି (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bfSize = (DWORD)bmp_size;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bfOffBits = (DWORD)(ଆକାର(BITMAPFILEHEADER) + pbih->biSize + color_table_size);
                    SDL_memcpy((Uint8 *)bmp + ଆକାର(BITMAPFILEHEADER), dib, mem_size);
                    *size = bmp_size;
                }
            } ଅନ୍ୟଥା {
                SDL_SetError("Invalid BMP data");
            }
            GlobalUnlock(hMem);
        } ଅନ୍ୟଥା {
            WIN_SetError("GlobalLock()");
        }
    } ଅନ୍ୟଥା {
        SDL_SetError("Invalid BMP data");
    }
    ଫେରନ୍ତୁ bmp;
}

ସ୍ଥିର bool WIN_SetClipboardImage(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *mime_type)
{
    UINT format = 0;
    HANDLE hMem = ଖାଲି;
    size_t clipboard_data_size;
    ଅଚଳ ଶୂନ୍ୟ *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    ଯଦି (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_data, clipboard_data_size, &format);
    } ଅନ୍ୟଥା ଯଦି (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_data_size);
        ଯଦି (hMem) {
            LPVOID dst = GlobalLock(hMem);
            ଯଦି (dst) {
                SDL_memcpy(dst, clipboard_data, clipboard_data_size);
                GlobalUnlock(hMem);
            } ଅନ୍ୟଥା {
                result = WIN_SetError("GlobalLock()");
                GlobalFree(hMem);
                hMem = ଖାଲି;
            }
        } ଅନ୍ୟଥା {
            result = SDL_OutOfMemory();
        }
    } ଅନ୍ୟଥା {
        result = SDL_SetError("Unknown image format");
    }
    ଯଦି (hMem) {
        // Save the image to the clipboard
        ଯଦି (!SetClipboardData(format, hMem)) {
            result = WIN_SetError("Couldn't set clipboard data");
        }
    } ଅନ୍ୟଥା {
        // WIN_ConvertBMPtoDIB() set the error
        result = false;
    }
    ଫେରନ୍ତୁ result;
}

ସ୍ଥିର bool WIN_SetClipboardText(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *mime_type)
{
    HANDLE hMem;
    size_t clipboard_data_size;
    ଅଚଳ ଶୂନ୍ୟ *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    ଯଦି (clipboard_data && clipboard_data_size > 0) {
        SIZE_T i, size;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (ଅଚଳ ଅକ୍ଷର *)clipboard_data, clipboard_data_size);
        ଯଦି (!tstr) {
            ଫେରନ୍ତୁ SDL_SetError("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        ପାଇଁ (size = 0, i = 0; tstr[i]; ++i, ++size) {
            ଯଦି (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++size;
            }
        }
        size = (size + 1) * ଆକାର(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, size);
        ଯଦି (hMem) {
            LPWSTR dst = (LPWSTR)GlobalLock(hMem);
            ଯଦି (dst) {
                // Copy the text over, adding carriage returns as necessary
                ପାଇଁ (i = 0; tstr[i]; ++i) {
                    ଯଦି (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            ଯଦି (!SetClipboardData(CF_UNICODETEXT, hMem)) {
                result = WIN_SetError("Couldn't set clipboard data");
            }
        } ଅନ୍ୟଥା {
            result = SDL_OutOfMemory();
        }
        SDL_free(tstr);
    }
    ଫେରନ୍ତୁ result;
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

    ଯଦି (WIN_OpenClipboard(_this)) {
        EmptyClipboard();

        // Set the clipboard text
        ପାଇଁ (i = 0; i < _this->ଅଙ୍କ_clipboard_mime_types; ++i) {
            ଅଚଳ ଅକ୍ଷର *mime_type = _this->clipboard_mime_types[i];

            ଯଦି (SDL_IsTextMimeType(mime_type)) {
                ଯଦି (!WIN_SetClipboardText(_this, mime_type)) {
                    result = false;
                }
                // Only set the first clipboard text
                ଭାଙ୍ଗ;
            }
        }

        // Set the clipboard image
        ପାଇଁ (i = 0; i < _this->ଅଙ୍କ_clipboard_mime_types; ++i) {
            ଅଚଳ ଅକ୍ଷର *mime_type = _this->clipboard_mime_types[i];

            ଯଦି (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                ଯଦି (!WIN_SetClipboardImage(_this, mime_type)) {
                    result = false;
                }
                ଭାଙ୍ଗ;
            }
        }

        data->clipboard_ଗଣନା = Get_Clipboard_Sequence_ସଂଖ୍ୟା();
        WIN_CloseClipboard();
    } ଅନ୍ୟଥା {
        result = WIN_SetError("Couldn't open clipboard");
    }
    ଫେରନ୍ତୁ result;
}

ଶୂନ୍ୟ *WIN_GetClipboardData(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *mime_type, size_t *size)
{
    ଶୂନ୍ୟ *data = ଖାଲି;

    ଯଦି (SDL_IsTextMimeType(mime_type)) {
        ଅକ୍ଷର *text = ଖାଲି;

        ଯଦି (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
            ଯଦି (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = GetClipboardData(CF_UNICODETEXT);
                ଯଦି (hMem) {
                    str = (LPTSTR)GlobalLock(hMem);
                    ଯଦି (str) {
                        text = WIN_StringToUTF8W(str);
                        GlobalUnlock(hMem);
                    } ଅନ୍ୟଥା {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } ଅନ୍ୟଥା {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } ଅନ୍ୟଥା ଯଦି (IsClipboardFormatAvailable(CF_TEXT)) {
            ଯଦି (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = GetClipboardData(CF_TEXT);
                ଯଦି (hMem) {
                    str = (LPCSTR)GlobalLock(hMem);
                    ଯଦି (str) {
                        text = SDL_strdup(str);
                        GlobalUnlock(hMem);
                    } ଅନ୍ୟଥା {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } ଅନ୍ୟଥା {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }
        ଯଦି (!text) {
            text = SDL_strdup("");
        }
        data = text;
        *size = SDL_strlen(text);

    } ଅନ୍ୟଥା ଯଦି (SDL_strcmp(mime_type, "image/bmp") == 0) {
        ଯଦି (IsClipboardFormatAvailable(CF_DIBV5)) {
            ଯଦି (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIBV5);
                ଯଦି (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } ଅନ୍ୟଥା {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } ଅନ୍ୟଥା ଯଦି (IsClipboardFormatAvailable(CF_DIB)) {
            ଯଦି (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIB);
                ଯଦି (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } ଅନ୍ୟଥା {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } ଅନ୍ୟଥା ଯଦି (SDL_strcmp(mime_type, "image/png") == 0) {
        ଯଦି (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            ଯଦି (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(GetClipboardFormatPNG());
                ଯଦି (hMem) {
                    size_t mem_size = GlobalSize(hMem);
                    ଶୂନ୍ୟ *mem = GlobalLock(hMem);
                    ଯଦି (mem) {
                        data = SDL_malloc(mem_size);
                        ଯଦି (data) {
                            SDL_memcpy(data, mem, mem_size);
                            *size = mem_size;
                        }
                        GlobalUnlock(hMem);
                    } ଅନ୍ୟଥା {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } ଅନ୍ୟଥା {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } ଅନ୍ୟଥା {
        data = SDL_GetInternalClipboardData(_this, mime_type, size);
    }
    ଫେରନ୍ତୁ data;
}

bool WIN_HasClipboardData(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *mime_type)
{
    ଯଦି (SDL_IsTextMimeType(mime_type)) {
        ଯଦି (IsClipboardFormatAvailable(CF_UNICODETEXT) || IsClipboardFormatAvailable(CF_TEXT)) {
            ଫେରନ୍ତୁ true;
        }
    } ଅନ୍ୟଥା ଯଦି (SDL_strcmp(mime_type, "image/bmp") == 0) {
        ଯଦି (IsClipboardFormatAvailable(CF_DIBV5) || IsClipboardFormatAvailable(CF_DIB)) {
            ଫେରନ୍ତୁ true;
        }
    } ଅନ୍ୟଥା ଯଦି (SDL_strcmp(mime_type, "image/png") == 0) {
        ଯଦି (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            ଫେରନ୍ତୁ true;
        }
    }
    ଫେରନ୍ତୁ SDL_HasInternalClipboardData(_this, mime_type);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା GetClipboardFormatMimeType(UINT format, ଅକ୍ଷର *name)
{
    ଅଚଳ ଅକ୍ଷର *mime_type = ଖାଲି;

    ବାଛ (format) {
    ସ୍ଥିତି CF_TEXT:
        mime_type = "text/plain";
        ଭାଙ୍ଗ;
    ସ୍ଥିତି CF_UNICODETEXT:
        mime_type = "text/plain;charset=utf-8";
        ଭାଙ୍ଗ;
    ସ୍ଥିତି CF_DIB:
    ସ୍ଥିତି CF_DIBV5:
        mime_type = "image/bmp";
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଯଦି (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        ଭାଙ୍ଗ;
    }
    ଯଦି (mime_type) {
        size_t len = SDL_strlen(mime_type) + 1;
        ଯଦି (name) {
            SDL_memcpy(name, mime_type, len);
        }
        ଫେରନ୍ତୁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)len;
    }
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଅକ୍ଷର **GetMimeTypes(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *pnformats)
{
    ଅକ୍ଷର **new_mime_types = ଖାଲି;

    *pnformats = 0;

    ଯଦି (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା nformats = 0;
        UINT format = 0;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା formatsSz = 0;
        bool have_image_bmp = false;
        ପାଇଁ ( ; ; ) {
            format = EnumClipboardFormats(format);
            ଯଦି (!format) {
                ଭାଙ୍ଗ;
            }

#ifdef DEBUG_CLIPBOARD
            ଅକ୍ଷର name[128] = { 0 };
            GetClipboardFormatNameA(format, name, ଆକାର(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#endif

            ଯଦି (format == CF_DIB || format == CF_DIBV5) {
                ଯଦି (have_image_bmp) {
                    // We have already registered this format
                    ଜାରି;
                }
                have_image_bmp = true;
            }

            ପୂର୍ଣ୍ଣସଂଖ୍ୟା len = GetClipboardFormatMimeType(format, ଖାଲି);
            ଯଦି (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_AllocateTemporaryMemory((nformats + 1) * ଆକାର(ଅକ୍ଷର *) + formatsSz);
        ଯଦି (new_mime_types) {
            format = 0;
            ଅକ୍ଷର *strPtr = (ଅକ୍ଷର *)(new_mime_types + nformats + 1);
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0;
            ପାଇଁ ( ; ; ) {
                format = EnumClipboardFormats(format);
                ଯଦି (!format) {
                    ଭାଙ୍ଗ;
                }

                ଯଦି (format == CF_DIB || format == CF_DIBV5) {
                    ଯଦି (have_image_bmp) {
                        // We have already registered this format
                        ଜାରି;
                    }
                    have_image_bmp = true;
                }

                ପୂର୍ଣ୍ଣସଂଖ୍ୟା len = GetClipboardFormatMimeType(format, strPtr);
                ଯଦି (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = ଖାଲି;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    ଫେରନ୍ତୁ new_mime_types;
}

ଶୂନ୍ୟ WIN_CheckClipboardUpdate(ସଂରଚନା SDL_VideoData *data)
{
    DWORD ଗଣନା_2 = Get_Clipboard_Sequence_ସଂଖ୍ୟା();
    ଯଦି (ଗଣନା_2 != data->clipboard_ଗଣନା) {
        ଯଦି (ଗଣନା_2) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା nformats = 0;
            ଅକ୍ଷର **new_mime_types = GetMimeTypes(&nformats);
            ଯଦି (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        data->clipboard_ଗଣନା = ଗଣନା_2;
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
