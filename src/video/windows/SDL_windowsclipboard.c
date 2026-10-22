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
#അന്തര്ഭാവ "SDL_internal.h"

#എങ്കിൽ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#അന്തര്ഭാവ "SDL_windowsvideo.h"
#അന്തര്ഭാവ "SDL_windowswindow.h"
#അന്തര്ഭാവ "../SDL_clipboard_c.h"
#അന്തര്ഭാവ "../../events/SDL_events_c.h"
#അന്തര്ഭാവ "../../events/SDL_clipboardevents_c.h"

#define BFT_BITMAP 0x4d42 // 'BM'

// Assume we can directly read and write BMP fields without byte swapping
SDL_COMPILE_TIME_ASSERT(verify_byte_order, SDL_BYTEORDER == SDL_LIL_ENDIAN);

സ്ഥിതം UINT GetClipboardFormatPNG(ശൂന്യം)
{
    സ്ഥിതം UINT format;

    എങ്കിൽ (!format) {
        format = RegisterClipboardFormat(TEXT("PNG"));
    }
    തിരികെ format;
}

സ്ഥിതം BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    സ്ഥിരം പൂർണ്ണസംഖ്യ MAX_ATTEMPTS = 3;
    പൂർണ്ണസംഖ്യ attempt;
    HWND hwnd = ശൂന്യ;

    എങ്കിൽ (_this->windows) {
        hwnd = _this->windows->internal->hwnd;
    }
    വേണ്ടി (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        എങ്കിൽ (OpenClipboard(hwnd)) {
            തിരികെ TRUE;
        }
        SDL_Delay(10);
    }
    തിരികെ FALSE;
}

സ്ഥിതം ശൂന്യം WIN_CloseClipboard(ശൂന്യം)
{
    CloseClipboard();
}

സ്ഥിതം HANDLE WIN_ConvertBMPtoDIB(സ്ഥിരം ശൂന്യം *bmp, size_t bmp_size, UINT *format)
{
    HANDLE hMem = ശൂന്യ;

    എങ്കിൽ (bmp && bmp_size > വലുപ്പം(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + വലുപ്പം(BITMAPFILEHEADER));
        size_t bih_size = pbih->biSize + pbih->biClrUsed * വലുപ്പം(RGBQUAD);
        size_t pixels_size = pbih->biSizeImage;

        എങ്കിൽ (pbih->biSize >= വലുപ്പം(BITMAPV5HEADER)) {
            *format = CF_DIBV5;
        } അല്ലെങ്കിൽ {
            *format = CF_DIB;
        }

        എങ്കിൽ (pbfh->bfOffBits >= (വലുപ്പം(BITMAPFILEHEADER) + bih_size) &&
            (pbfh->bfOffBits + pixels_size) <= bmp_size) {
            സ്ഥിരം Uint8 *pixels = (സ്ഥിരം Uint8 *)bmp + pbfh->bfOffBits;
            size_t dib_size = bih_size + pixels_size;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_size);
            എങ്കിൽ (hMem) {
                LPVOID dst = GlobalLock(hMem);
                എങ്കിൽ (dst) {
                    SDL_memcpy(dst, pbih, bih_size);
                    SDL_memcpy((Uint8 *)dst + bih_size, pixels, pixels_size);
                    GlobalUnlock(hMem);
                } അല്ലെങ്കിൽ {
                    WIN_SetError("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = ശൂന്യ;
                }
            } അല്ലെങ്കിൽ {
                SDL_OutOfMemory();
            }
        } അല്ലെങ്കിൽ {
            SDL_SetError("Invalid BMP data");
        }
    } അല്ലെങ്കിൽ {
        SDL_SetError("Invalid BMP data");
    }
    തിരികെ hMem;
}

സ്ഥിതം ശൂന്യം *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *size)
{
    ശൂന്യം *bmp = ശൂന്യ;
    size_t mem_size = GlobalSize(hMem);

    എങ്കിൽ (mem_size > വലുപ്പം(BITMAPINFOHEADER)) {
        LPVOID dib = GlobalLock(hMem);
        എങ്കിൽ (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_table_size;
            തിരഞ്ഞെടുപ്പ് (pbih->biCompression) {
            അവസ്ഥ BI_RGB:
                എങ്കിൽ (pbih->bi_Bit_എണ്ണം <= 8) {
                    color_table_size = വലുപ്പം(RGBQUAD) * (pbih->biClrUsed == 0 ? 1 << pbih->bi_Bit_എണ്ണം : pbih->biClrUsed);
                } അല്ലെങ്കിൽ {
                    color_table_size = 0;
                }
                നിർത്തുക;
            അവസ്ഥ BI_BITFIELDS:
                color_table_size = 3 * വലുപ്പം(DWORD);
                നിർത്തുക;
            അവസ്ഥ 6 /* BI_ALPHABITFIELDS */:
                // https://learn.microsoft.com/en-us/previous-versions/windows/embedded/aa452885(v=msdn.10)
                color_table_size = 4 * വലുപ്പം(DWORD);
                നിർത്തുക;
            സ്ഥിരസ്ഥിതി: // FOURCC
                color_table_size = വലുപ്പം(RGBQUAD) * pbih->biClrUsed;
            }

            size_t bih_size = pbih->biSize + color_table_size;
            size_t dib_size = bih_size + pbih->biSizeImage;
            എങ്കിൽ (dib_size <= mem_size) {
                size_t bmp_size = വലുപ്പം(BITMAPFILEHEADER) + mem_size;
                bmp = SDL_malloc(bmp_size);
                എങ്കിൽ (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bfSize = (DWORD)bmp_size;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bfOffBits = (DWORD)(വലുപ്പം(BITMAPFILEHEADER) + pbih->biSize + color_table_size);
                    SDL_memcpy((Uint8 *)bmp + വലുപ്പം(BITMAPFILEHEADER), dib, mem_size);
                    *size = bmp_size;
                }
            } അല്ലെങ്കിൽ {
                SDL_SetError("Invalid BMP data");
            }
            GlobalUnlock(hMem);
        } അല്ലെങ്കിൽ {
            WIN_SetError("GlobalLock()");
        }
    } അല്ലെങ്കിൽ {
        SDL_SetError("Invalid BMP data");
    }
    തിരികെ bmp;
}

സ്ഥിതം bool WIN_SetClipboardImage(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *mime_type)
{
    UINT format = 0;
    HANDLE hMem = ശൂന്യ;
    size_t clipboard_data_size;
    സ്ഥിരം ശൂന്യം *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    എങ്കിൽ (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_data, clipboard_data_size, &format);
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_data_size);
        എങ്കിൽ (hMem) {
            LPVOID dst = GlobalLock(hMem);
            എങ്കിൽ (dst) {
                SDL_memcpy(dst, clipboard_data, clipboard_data_size);
                GlobalUnlock(hMem);
            } അല്ലെങ്കിൽ {
                result = WIN_SetError("GlobalLock()");
                GlobalFree(hMem);
                hMem = ശൂന്യ;
            }
        } അല്ലെങ്കിൽ {
            result = SDL_OutOfMemory();
        }
    } അല്ലെങ്കിൽ {
        result = SDL_SetError("Unknown image format");
    }
    എങ്കിൽ (hMem) {
        // Save the image to the clipboard
        എങ്കിൽ (!SetClipboardData(format, hMem)) {
            result = WIN_SetError("Couldn't set clipboard data");
        }
    } അല്ലെങ്കിൽ {
        // WIN_ConvertBMPtoDIB() set the error
        result = false;
    }
    തിരികെ result;
}

സ്ഥിതം bool WIN_SetClipboardText(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *mime_type)
{
    HANDLE hMem;
    size_t clipboard_data_size;
    സ്ഥിരം ശൂന്യം *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    എങ്കിൽ (clipboard_data && clipboard_data_size > 0) {
        SIZE_T i, size;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (സ്ഥിരം അക്ഷരം *)clipboard_data, clipboard_data_size);
        എങ്കിൽ (!tstr) {
            തിരികെ SDL_SetError("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        വേണ്ടി (size = 0, i = 0; tstr[i]; ++i, ++size) {
            എങ്കിൽ (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++size;
            }
        }
        size = (size + 1) * വലുപ്പം(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, size);
        എങ്കിൽ (hMem) {
            LPWSTR dst = (LPWSTR)GlobalLock(hMem);
            എങ്കിൽ (dst) {
                // Copy the text over, adding carriage returns as necessary
                വേണ്ടി (i = 0; tstr[i]; ++i) {
                    എങ്കിൽ (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            എങ്കിൽ (!SetClipboardData(CF_UNICODETEXT, hMem)) {
                result = WIN_SetError("Couldn't set clipboard data");
            }
        } അല്ലെങ്കിൽ {
            result = SDL_OutOfMemory();
        }
        SDL_free(tstr);
    }
    തിരികെ result;
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

    എങ്കിൽ (WIN_OpenClipboard(_this)) {
        EmptyClipboard();

        // Set the clipboard text
        വേണ്ടി (i = 0; i < _this->അക്കം_clipboard_mime_types; ++i) {
            സ്ഥിരം അക്ഷരം *mime_type = _this->clipboard_mime_types[i];

            എങ്കിൽ (SDL_IsTextMimeType(mime_type)) {
                എങ്കിൽ (!WIN_SetClipboardText(_this, mime_type)) {
                    result = false;
                }
                // Only set the first clipboard text
                നിർത്തുക;
            }
        }

        // Set the clipboard image
        വേണ്ടി (i = 0; i < _this->അക്കം_clipboard_mime_types; ++i) {
            സ്ഥിരം അക്ഷരം *mime_type = _this->clipboard_mime_types[i];

            എങ്കിൽ (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                എങ്കിൽ (!WIN_SetClipboardImage(_this, mime_type)) {
                    result = false;
                }
                നിർത്തുക;
            }
        }

        data->clipboard_എണ്ണം = Get_Clipboard_Sequence_സംഖ്യ();
        WIN_CloseClipboard();
    } അല്ലെങ്കിൽ {
        result = WIN_SetError("Couldn't open clipboard");
    }
    തിരികെ result;
}

ശൂന്യം *WIN_GetClipboardData(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *mime_type, size_t *size)
{
    ശൂന്യം *data = ശൂന്യ;

    എങ്കിൽ (SDL_IsTextMimeType(mime_type)) {
        അക്ഷരം *text = ശൂന്യ;

        എങ്കിൽ (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
            എങ്കിൽ (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = GetClipboardData(CF_UNICODETEXT);
                എങ്കിൽ (hMem) {
                    str = (LPTSTR)GlobalLock(hMem);
                    എങ്കിൽ (str) {
                        text = WIN_StringToUTF8W(str);
                        GlobalUnlock(hMem);
                    } അല്ലെങ്കിൽ {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } അല്ലെങ്കിൽ {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } അല്ലെങ്കിൽ എങ്കിൽ (IsClipboardFormatAvailable(CF_TEXT)) {
            എങ്കിൽ (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = GetClipboardData(CF_TEXT);
                എങ്കിൽ (hMem) {
                    str = (LPCSTR)GlobalLock(hMem);
                    എങ്കിൽ (str) {
                        text = SDL_strdup(str);
                        GlobalUnlock(hMem);
                    } അല്ലെങ്കിൽ {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } അല്ലെങ്കിൽ {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }
        എങ്കിൽ (!text) {
            text = SDL_strdup("");
        }
        data = text;
        *size = SDL_strlen(text);

    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_strcmp(mime_type, "image/bmp") == 0) {
        എങ്കിൽ (IsClipboardFormatAvailable(CF_DIBV5)) {
            എങ്കിൽ (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIBV5);
                എങ്കിൽ (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } അല്ലെങ്കിൽ {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } അല്ലെങ്കിൽ എങ്കിൽ (IsClipboardFormatAvailable(CF_DIB)) {
            എങ്കിൽ (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIB);
                എങ്കിൽ (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } അല്ലെങ്കിൽ {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_strcmp(mime_type, "image/png") == 0) {
        എങ്കിൽ (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            എങ്കിൽ (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(GetClipboardFormatPNG());
                എങ്കിൽ (hMem) {
                    size_t mem_size = GlobalSize(hMem);
                    ശൂന്യം *mem = GlobalLock(hMem);
                    എങ്കിൽ (mem) {
                        data = SDL_malloc(mem_size);
                        എങ്കിൽ (data) {
                            SDL_memcpy(data, mem, mem_size);
                            *size = mem_size;
                        }
                        GlobalUnlock(hMem);
                    } അല്ലെങ്കിൽ {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } അല്ലെങ്കിൽ {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } അല്ലെങ്കിൽ {
        data = SDL_GetInternalClipboardData(_this, mime_type, size);
    }
    തിരികെ data;
}

bool WIN_HasClipboardData(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *mime_type)
{
    എങ്കിൽ (SDL_IsTextMimeType(mime_type)) {
        എങ്കിൽ (IsClipboardFormatAvailable(CF_UNICODETEXT) || IsClipboardFormatAvailable(CF_TEXT)) {
            തിരികെ true;
        }
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_strcmp(mime_type, "image/bmp") == 0) {
        എങ്കിൽ (IsClipboardFormatAvailable(CF_DIBV5) || IsClipboardFormatAvailable(CF_DIB)) {
            തിരികെ true;
        }
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_strcmp(mime_type, "image/png") == 0) {
        എങ്കിൽ (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            തിരികെ true;
        }
    }
    തിരികെ SDL_HasInternalClipboardData(_this, mime_type);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ GetClipboardFormatMimeType(UINT format, അക്ഷരം *name)
{
    സ്ഥിരം അക്ഷരം *mime_type = ശൂന്യ;

    തിരഞ്ഞെടുപ്പ് (format) {
    അവസ്ഥ CF_TEXT:
        mime_type = "text/plain";
        നിർത്തുക;
    അവസ്ഥ CF_UNICODETEXT:
        mime_type = "text/plain;charset=utf-8";
        നിർത്തുക;
    അവസ്ഥ CF_DIB:
    അവസ്ഥ CF_DIBV5:
        mime_type = "image/bmp";
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        എങ്കിൽ (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        നിർത്തുക;
    }
    എങ്കിൽ (mime_type) {
        size_t len = SDL_strlen(mime_type) + 1;
        എങ്കിൽ (name) {
            SDL_memcpy(name, mime_type, len);
        }
        തിരികെ (പൂർണ്ണസംഖ്യ)len;
    }
    തിരികെ 0;
}

സ്ഥിതം അക്ഷരം **GetMimeTypes(പൂർണ്ണസംഖ്യ *pnformats)
{
    അക്ഷരം **new_mime_types = ശൂന്യ;

    *pnformats = 0;

    എങ്കിൽ (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        പൂർണ്ണസംഖ്യ nformats = 0;
        UINT format = 0;
        പൂർണ്ണസംഖ്യ formatsSz = 0;
        bool have_image_bmp = false;
        വേണ്ടി ( ; ; ) {
            format = EnumClipboardFormats(format);
            എങ്കിൽ (!format) {
                നിർത്തുക;
            }

#ifdef DEBUG_CLIPBOARD
            അക്ഷരം name[128] = { 0 };
            GetClipboardFormatNameA(format, name, വലുപ്പം(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#endif

            എങ്കിൽ (format == CF_DIB || format == CF_DIBV5) {
                എങ്കിൽ (have_image_bmp) {
                    // We have already registered this format
                    തുടരുക;
                }
                have_image_bmp = true;
            }

            പൂർണ്ണസംഖ്യ len = GetClipboardFormatMimeType(format, ശൂന്യ);
            എങ്കിൽ (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_AllocateTemporaryMemory((nformats + 1) * വലുപ്പം(അക്ഷരം *) + formatsSz);
        എങ്കിൽ (new_mime_types) {
            format = 0;
            അക്ഷരം *strPtr = (അക്ഷരം *)(new_mime_types + nformats + 1);
            പൂർണ്ണസംഖ്യ i = 0;
            വേണ്ടി ( ; ; ) {
                format = EnumClipboardFormats(format);
                എങ്കിൽ (!format) {
                    നിർത്തുക;
                }

                എങ്കിൽ (format == CF_DIB || format == CF_DIBV5) {
                    എങ്കിൽ (have_image_bmp) {
                        // We have already registered this format
                        തുടരുക;
                    }
                    have_image_bmp = true;
                }

                പൂർണ്ണസംഖ്യ len = GetClipboardFormatMimeType(format, strPtr);
                എങ്കിൽ (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = ശൂന്യ;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    തിരികെ new_mime_types;
}

ശൂന്യം WIN_CheckClipboardUpdate(ഘടന SDL_VideoData *data)
{
    DWORD എണ്ണം = Get_Clipboard_Sequence_സംഖ്യ();
    എങ്കിൽ (എണ്ണം != data->clipboard_എണ്ണം) {
        എങ്കിൽ (എണ്ണം) {
            പൂർണ്ണസംഖ്യ nformats = 0;
            അക്ഷരം **new_mime_types = GetMimeTypes(&nformats);
            എങ്കിൽ (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        data->clipboard_എണ്ണം = എണ്ണം;
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
