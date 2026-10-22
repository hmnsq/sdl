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
#அந்தர்பாவ "SDL_internal.h"

#எனில் defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#அந்தர்பாவ "SDL_windowsvideo.h"
#அந்தர்பாவ "SDL_windowswindow.h"
#அந்தர்பாவ "../SDL_clipboard_c.h"
#அந்தர்பாவ "../../events/SDL_events_c.h"
#அந்தர்பாவ "../../events/SDL_clipboardevents_c.h"

#define BFT_BITMAP 0x4d42 // 'BM'

// Assume we can directly read and write BMP fields without byte swapping
SDL_COMPILE_TIME_ASSERT(verify_byte_order, SDL_BYTEORDER == SDL_LIL_ENDIAN);

நிலையான UINT GetClipboardFormatPNG(வெறுமை)
{
    நிலையான UINT format;

    எனில் (!format) {
        format = RegisterClipboardFormat(TEXT("PNG"));
    }
    திரும்பு format;
}

நிலையான BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    மாறிலி முழு MAX_ATTEMPTS = 3;
    முழு attempt;
    HWND hwnd = வெற்று;

    எனில் (_this->windows) {
        hwnd = _this->windows->internal->hwnd;
    }
    க்கு (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        எனில் (OpenClipboard(hwnd)) {
            திரும்பு TRUE;
        }
        SDL_Delay(10);
    }
    திரும்பு FALSE;
}

நிலையான வெறுமை WIN_CloseClipboard(வெறுமை)
{
    CloseClipboard();
}

நிலையான HANDLE WIN_ConvertBMPtoDIB(மாறிலி வெறுமை *bmp, size_t bmp_size, UINT *format)
{
    HANDLE hMem = வெற்று;

    எனில் (bmp && bmp_size > அளவு(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + அளவு(BITMAPFILEHEADER));
        size_t bih_size = pbih->biSize + pbih->biClrUsed * அளவு(RGBQUAD);
        size_t pixels_size = pbih->biSizeImage;

        எனில் (pbih->biSize >= அளவு(BITMAPV5HEADER)) {
            *format = CF_DIBV5;
        } இல்லையெனில் {
            *format = CF_DIB;
        }

        எனில் (pbfh->bfOffBits >= (அளவு(BITMAPFILEHEADER) + bih_size) &&
            (pbfh->bfOffBits + pixels_size) <= bmp_size) {
            மாறிலி Uint8 *pixels = (மாறிலி Uint8 *)bmp + pbfh->bfOffBits;
            size_t dib_size = bih_size + pixels_size;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_size);
            எனில் (hMem) {
                LPVOID dst = GlobalLock(hMem);
                எனில் (dst) {
                    SDL_memcpy(dst, pbih, bih_size);
                    SDL_memcpy((Uint8 *)dst + bih_size, pixels, pixels_size);
                    GlobalUnlock(hMem);
                } இல்லையெனில் {
                    WIN_SetError("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = வெற்று;
                }
            } இல்லையெனில் {
                SDL_OutOfMemory();
            }
        } இல்லையெனில் {
            SDL_SetError("Invalid BMP data");
        }
    } இல்லையெனில் {
        SDL_SetError("Invalid BMP data");
    }
    திரும்பு hMem;
}

நிலையான வெறுமை *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *size)
{
    வெறுமை *bmp = வெற்று;
    size_t mem_size = GlobalSize(hMem);

    எனில் (mem_size > அளவு(BITMAPINFOHEADER)) {
        LPVOID dib = GlobalLock(hMem);
        எனில் (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_table_size;
            தேர்வு (pbih->biCompression) {
            நிலை BI_RGB:
                எனில் (pbih->bi_Bit_மொத்தம் <= 8) {
                    color_table_size = அளவு(RGBQUAD) * (pbih->biClrUsed == 0 ? 1 << pbih->bi_Bit_மொத்தம் : pbih->biClrUsed);
                } இல்லையெனில் {
                    color_table_size = 0;
                }
                நிறுத்து;
            நிலை BI_BITFIELDS:
                color_table_size = 3 * அளவு(DWORD);
                நிறுத்து;
            நிலை 6 /* BI_ALPHABITFIELDS */:
                // https://learn.microsoft.com/en-us/previous-versions/windows/embedded/aa452885(v=msdn.10)
                color_table_size = 4 * அளவு(DWORD);
                நிறுத்து;
            இயல்பு: // FOURCC
                color_table_size = அளவு(RGBQUAD) * pbih->biClrUsed;
            }

            size_t bih_size = pbih->biSize + color_table_size;
            size_t dib_size = bih_size + pbih->biSizeImage;
            எனில் (dib_size <= mem_size) {
                size_t bmp_size = அளவு(BITMAPFILEHEADER) + mem_size;
                bmp = SDL_malloc(bmp_size);
                எனில் (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bfSize = (DWORD)bmp_size;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bfOffBits = (DWORD)(அளவு(BITMAPFILEHEADER) + pbih->biSize + color_table_size);
                    SDL_memcpy((Uint8 *)bmp + அளவு(BITMAPFILEHEADER), dib, mem_size);
                    *size = bmp_size;
                }
            } இல்லையெனில் {
                SDL_SetError("Invalid BMP data");
            }
            GlobalUnlock(hMem);
        } இல்லையெனில் {
            WIN_SetError("GlobalLock()");
        }
    } இல்லையெனில் {
        SDL_SetError("Invalid BMP data");
    }
    திரும்பு bmp;
}

நிலையான bool WIN_SetClipboardImage(SDL_VideoDevice *_this, மாறிலி எழுத்து *mime_type)
{
    UINT format = 0;
    HANDLE hMem = வெற்று;
    size_t clipboard_data_size;
    மாறிலி வெறுமை *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    எனில் (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_data, clipboard_data_size, &format);
    } இல்லையெனில் எனில் (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_data_size);
        எனில் (hMem) {
            LPVOID dst = GlobalLock(hMem);
            எனில் (dst) {
                SDL_memcpy(dst, clipboard_data, clipboard_data_size);
                GlobalUnlock(hMem);
            } இல்லையெனில் {
                result = WIN_SetError("GlobalLock()");
                GlobalFree(hMem);
                hMem = வெற்று;
            }
        } இல்லையெனில் {
            result = SDL_OutOfMemory();
        }
    } இல்லையெனில் {
        result = SDL_SetError("Unknown image format");
    }
    எனில் (hMem) {
        // Save the image to the clipboard
        எனில் (!SetClipboardData(format, hMem)) {
            result = WIN_SetError("Couldn't set clipboard data");
        }
    } இல்லையெனில் {
        // WIN_ConvertBMPtoDIB() set the error
        result = false;
    }
    திரும்பு result;
}

நிலையான bool WIN_SetClipboardText(SDL_VideoDevice *_this, மாறிலி எழுத்து *mime_type)
{
    HANDLE hMem;
    size_t clipboard_data_size;
    மாறிலி வெறுமை *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    எனில் (clipboard_data && clipboard_data_size > 0) {
        SIZE_T i, size;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (மாறிலி எழுத்து *)clipboard_data, clipboard_data_size);
        எனில் (!tstr) {
            திரும்பு SDL_SetError("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        க்கு (size = 0, i = 0; tstr[i]; ++i, ++size) {
            எனில் (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++size;
            }
        }
        size = (size + 1) * அளவு(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, size);
        எனில் (hMem) {
            LPWSTR dst = (LPWSTR)GlobalLock(hMem);
            எனில் (dst) {
                // Copy the text over, adding carriage returns as necessary
                க்கு (i = 0; tstr[i]; ++i) {
                    எனில் (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            எனில் (!SetClipboardData(CF_UNICODETEXT, hMem)) {
                result = WIN_SetError("Couldn't set clipboard data");
            }
        } இல்லையெனில் {
            result = SDL_OutOfMemory();
        }
        SDL_free(tstr);
    }
    திரும்பு result;
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

    எனில் (WIN_OpenClipboard(_this)) {
        EmptyClipboard();

        // Set the clipboard text
        க்கு (i = 0; i < _this->இலக்கம்_clipboard_mime_types; ++i) {
            மாறிலி எழுத்து *mime_type = _this->clipboard_mime_types[i];

            எனில் (SDL_IsTextMimeType(mime_type)) {
                எனில் (!WIN_SetClipboardText(_this, mime_type)) {
                    result = false;
                }
                // Only set the first clipboard text
                நிறுத்து;
            }
        }

        // Set the clipboard image
        க்கு (i = 0; i < _this->இலக்கம்_clipboard_mime_types; ++i) {
            மாறிலி எழுத்து *mime_type = _this->clipboard_mime_types[i];

            எனில் (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                எனில் (!WIN_SetClipboardImage(_this, mime_type)) {
                    result = false;
                }
                நிறுத்து;
            }
        }

        data->clipboard_மொத்தம் = Get_Clipboard_Sequence_எண்();
        WIN_CloseClipboard();
    } இல்லையெனில் {
        result = WIN_SetError("Couldn't open clipboard");
    }
    திரும்பு result;
}

வெறுமை *WIN_GetClipboardData(SDL_VideoDevice *_this, மாறிலி எழுத்து *mime_type, size_t *size)
{
    வெறுமை *data = வெற்று;

    எனில் (SDL_IsTextMimeType(mime_type)) {
        எழுத்து *text = வெற்று;

        எனில் (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
            எனில் (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = GetClipboardData(CF_UNICODETEXT);
                எனில் (hMem) {
                    str = (LPTSTR)GlobalLock(hMem);
                    எனில் (str) {
                        text = WIN_StringToUTF8W(str);
                        GlobalUnlock(hMem);
                    } இல்லையெனில் {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } இல்லையெனில் {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } இல்லையெனில் எனில் (IsClipboardFormatAvailable(CF_TEXT)) {
            எனில் (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = GetClipboardData(CF_TEXT);
                எனில் (hMem) {
                    str = (LPCSTR)GlobalLock(hMem);
                    எனில் (str) {
                        text = SDL_strdup(str);
                        GlobalUnlock(hMem);
                    } இல்லையெனில் {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } இல்லையெனில் {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }
        எனில் (!text) {
            text = SDL_strdup("");
        }
        data = text;
        *size = SDL_strlen(text);

    } இல்லையெனில் எனில் (SDL_strcmp(mime_type, "image/bmp") == 0) {
        எனில் (IsClipboardFormatAvailable(CF_DIBV5)) {
            எனில் (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIBV5);
                எனில் (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } இல்லையெனில் {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } இல்லையெனில் எனில் (IsClipboardFormatAvailable(CF_DIB)) {
            எனில் (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIB);
                எனில் (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } இல்லையெனில் {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } இல்லையெனில் எனில் (SDL_strcmp(mime_type, "image/png") == 0) {
        எனில் (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            எனில் (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(GetClipboardFormatPNG());
                எனில் (hMem) {
                    size_t mem_size = GlobalSize(hMem);
                    வெறுமை *mem = GlobalLock(hMem);
                    எனில் (mem) {
                        data = SDL_malloc(mem_size);
                        எனில் (data) {
                            SDL_memcpy(data, mem, mem_size);
                            *size = mem_size;
                        }
                        GlobalUnlock(hMem);
                    } இல்லையெனில் {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } இல்லையெனில் {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } இல்லையெனில் {
        data = SDL_GetInternalClipboardData(_this, mime_type, size);
    }
    திரும்பு data;
}

bool WIN_HasClipboardData(SDL_VideoDevice *_this, மாறிலி எழுத்து *mime_type)
{
    எனில் (SDL_IsTextMimeType(mime_type)) {
        எனில் (IsClipboardFormatAvailable(CF_UNICODETEXT) || IsClipboardFormatAvailable(CF_TEXT)) {
            திரும்பு true;
        }
    } இல்லையெனில் எனில் (SDL_strcmp(mime_type, "image/bmp") == 0) {
        எனில் (IsClipboardFormatAvailable(CF_DIBV5) || IsClipboardFormatAvailable(CF_DIB)) {
            திரும்பு true;
        }
    } இல்லையெனில் எனில் (SDL_strcmp(mime_type, "image/png") == 0) {
        எனில் (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            திரும்பு true;
        }
    }
    திரும்பு SDL_HasInternalClipboardData(_this, mime_type);
}

நிலையான முழு GetClipboardFormatMimeType(UINT format, எழுத்து *name)
{
    மாறிலி எழுத்து *mime_type = வெற்று;

    தேர்வு (format) {
    நிலை CF_TEXT:
        mime_type = "text/plain";
        நிறுத்து;
    நிலை CF_UNICODETEXT:
        mime_type = "text/plain;charset=utf-8";
        நிறுத்து;
    நிலை CF_DIB:
    நிலை CF_DIBV5:
        mime_type = "image/bmp";
        நிறுத்து;
    இயல்பு:
        எனில் (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        நிறுத்து;
    }
    எனில் (mime_type) {
        size_t len = SDL_strlen(mime_type) + 1;
        எனில் (name) {
            SDL_memcpy(name, mime_type, len);
        }
        திரும்பு (முழு)len;
    }
    திரும்பு 0;
}

நிலையான எழுத்து **GetMimeTypes(முழு *pnformats)
{
    எழுத்து **new_mime_types = வெற்று;

    *pnformats = 0;

    எனில் (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        முழு nformats = 0;
        UINT format = 0;
        முழு formatsSz = 0;
        bool have_image_bmp = false;
        க்கு ( ; ; ) {
            format = EnumClipboardFormats(format);
            எனில் (!format) {
                நிறுத்து;
            }

#ifdef DEBUG_CLIPBOARD
            எழுத்து name[128] = { 0 };
            GetClipboardFormatNameA(format, name, அளவு(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#endif

            எனில் (format == CF_DIB || format == CF_DIBV5) {
                எனில் (have_image_bmp) {
                    // We have already registered this format
                    தொடர்;
                }
                have_image_bmp = true;
            }

            முழு len = GetClipboardFormatMimeType(format, வெற்று);
            எனில் (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_AllocateTemporaryMemory((nformats + 1) * அளவு(எழுத்து *) + formatsSz);
        எனில் (new_mime_types) {
            format = 0;
            எழுத்து *strPtr = (எழுத்து *)(new_mime_types + nformats + 1);
            முழு i = 0;
            க்கு ( ; ; ) {
                format = EnumClipboardFormats(format);
                எனில் (!format) {
                    நிறுத்து;
                }

                எனில் (format == CF_DIB || format == CF_DIBV5) {
                    எனில் (have_image_bmp) {
                        // We have already registered this format
                        தொடர்;
                    }
                    have_image_bmp = true;
                }

                முழு len = GetClipboardFormatMimeType(format, strPtr);
                எனில் (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = வெற்று;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    திரும்பு new_mime_types;
}

வெறுமை WIN_CheckClipboardUpdate(கட்டமைப்பு SDL_VideoData *data)
{
    DWORD மொத்தம் = Get_Clipboard_Sequence_எண்();
    எனில் (மொத்தம் != data->clipboard_மொத்தம்) {
        எனில் (மொத்தம்) {
            முழு nformats = 0;
            எழுத்து **new_mime_types = GetMimeTypes(&nformats);
            எனில் (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        data->clipboard_மொத்தம் = மொத்தம்;
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
