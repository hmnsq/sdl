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
#અન્તર્ભાવ "SDL_internal.h"

#જો defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#અન્તર્ભાવ "SDL_windowsvideo.h"
#અન્તર્ભાવ "SDL_windowswindow.h"
#અન્તર્ભાવ "../SDL_clipboard_c.h"
#અન્તર્ભાવ "../../events/SDL_events_c.h"
#અન્તર્ભાવ "../../events/SDL_clipboardevents_c.h"

#define BFT_BITMAP 0x4d42 // 'BM'

// Assume we can directly read and write BMP fields without byte swapping
SDL_COMPILE_TIME_ASSERT(verify_byte_order, SDL_BYTEORDER == SDL_LIL_ENDIAN);

સ્થિર UINT GetClipboardFormatPNG(શૂન્ય)
{
    સ્થિર UINT format;

    જો (!format) {
        format = RegisterClipboardFormat(TEXT("PNG"));
    }
    પાછા format;
}

સ્થિર BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    અચલ પૂર્ણાંક MAX_ATTEMPTS = 3;
    પૂર્ણાંક attempt;
    HWND hwnd = ખાલી;

    જો (_this->windows) {
        hwnd = _this->windows->internal->hwnd;
    }
    માટે (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        જો (OpenClipboard(hwnd)) {
            પાછા TRUE;
        }
        SDL_Delay(10);
    }
    પાછા FALSE;
}

સ્થિર શૂન્ય WIN_CloseClipboard(શૂન્ય)
{
    CloseClipboard();
}

સ્થિર HANDLE WIN_ConvertBMPtoDIB(અચલ શૂન્ય *bmp, size_t bmp_size, UINT *format)
{
    HANDLE hMem = ખાલી;

    જો (bmp && bmp_size > કદ(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + કદ(BITMAPFILEHEADER));
        size_t bih_size = pbih->biSize + pbih->biClrUsed * કદ(RGBQUAD);
        size_t pixels_size = pbih->biSizeImage;

        જો (pbih->biSize >= કદ(BITMAPV5HEADER)) {
            *format = CF_DIBV5;
        } નહીંતર {
            *format = CF_DIB;
        }

        જો (pbfh->bfOffBits >= (કદ(BITMAPFILEHEADER) + bih_size) &&
            (pbfh->bfOffBits + pixels_size) <= bmp_size) {
            અચલ Uint8 *pixels = (અચલ Uint8 *)bmp + pbfh->bfOffBits;
            size_t dib_size = bih_size + pixels_size;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_size);
            જો (hMem) {
                LPVOID dst = GlobalLock(hMem);
                જો (dst) {
                    SDL_memcpy(dst, pbih, bih_size);
                    SDL_memcpy((Uint8 *)dst + bih_size, pixels, pixels_size);
                    GlobalUnlock(hMem);
                } નહીંતર {
                    WIN_SetError("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = ખાલી;
                }
            } નહીંતર {
                SDL_OutOfMemory();
            }
        } નહીંતર {
            SDL_SetError("Invalid BMP data");
        }
    } નહીંતર {
        SDL_SetError("Invalid BMP data");
    }
    પાછા hMem;
}

સ્થિર શૂન્ય *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *size)
{
    શૂન્ય *bmp = ખાલી;
    size_t mem_size = GlobalSize(hMem);

    જો (mem_size > કદ(BITMAPINFOHEADER)) {
        LPVOID dib = GlobalLock(hMem);
        જો (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_table_size;
            પસંદગી (pbih->biCompression) {
            સ્થિતિ BI_RGB:
                જો (pbih->bi_Bit_ગણતરી <= 8) {
                    color_table_size = કદ(RGBQUAD) * (pbih->biClrUsed == 0 ? 1 << pbih->bi_Bit_ગણતરી : pbih->biClrUsed);
                } નહીંતર {
                    color_table_size = 0;
                }
                તોડો;
            સ્થિતિ BI_BITFIELDS:
                color_table_size = 3 * કદ(DWORD);
                તોડો;
            સ્થિતિ 6 /* BI_ALPHABITFIELDS */:
                // https://learn.microsoft.com/en-us/previous-versions/windows/embedded/aa452885(v=msdn.10)
                color_table_size = 4 * કદ(DWORD);
                તોડો;
            મૂળભૂત: // FOURCC
                color_table_size = કદ(RGBQUAD) * pbih->biClrUsed;
            }

            size_t bih_size = pbih->biSize + color_table_size;
            size_t dib_size = bih_size + pbih->biSizeImage;
            જો (dib_size <= mem_size) {
                size_t bmp_size = કદ(BITMAPFILEHEADER) + mem_size;
                bmp = SDL_malloc(bmp_size);
                જો (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bfSize = (DWORD)bmp_size;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bfOffBits = (DWORD)(કદ(BITMAPFILEHEADER) + pbih->biSize + color_table_size);
                    SDL_memcpy((Uint8 *)bmp + કદ(BITMAPFILEHEADER), dib, mem_size);
                    *size = bmp_size;
                }
            } નહીંતર {
                SDL_SetError("Invalid BMP data");
            }
            GlobalUnlock(hMem);
        } નહીંતર {
            WIN_SetError("GlobalLock()");
        }
    } નહીંતર {
        SDL_SetError("Invalid BMP data");
    }
    પાછા bmp;
}

સ્થિર bool WIN_SetClipboardImage(SDL_VideoDevice *_this, અચલ અક્ષર *mime_type)
{
    UINT format = 0;
    HANDLE hMem = ખાલી;
    size_t clipboard_data_size;
    અચલ શૂન્ય *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    જો (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_data, clipboard_data_size, &format);
    } નહીંતર જો (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_data_size);
        જો (hMem) {
            LPVOID dst = GlobalLock(hMem);
            જો (dst) {
                SDL_memcpy(dst, clipboard_data, clipboard_data_size);
                GlobalUnlock(hMem);
            } નહીંતર {
                result = WIN_SetError("GlobalLock()");
                GlobalFree(hMem);
                hMem = ખાલી;
            }
        } નહીંતર {
            result = SDL_OutOfMemory();
        }
    } નહીંતર {
        result = SDL_SetError("Unknown image format");
    }
    જો (hMem) {
        // Save the image to the clipboard
        જો (!SetClipboardData(format, hMem)) {
            result = WIN_SetError("Couldn't set clipboard data");
        }
    } નહીંતર {
        // WIN_ConvertBMPtoDIB() set the error
        result = false;
    }
    પાછા result;
}

સ્થિર bool WIN_SetClipboardText(SDL_VideoDevice *_this, અચલ અક્ષર *mime_type)
{
    HANDLE hMem;
    size_t clipboard_data_size;
    અચલ શૂન્ય *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    જો (clipboard_data && clipboard_data_size > 0) {
        SIZE_T i, size;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (અચલ અક્ષર *)clipboard_data, clipboard_data_size);
        જો (!tstr) {
            પાછા SDL_SetError("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        માટે (size = 0, i = 0; tstr[i]; ++i, ++size) {
            જો (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++size;
            }
        }
        size = (size + 1) * કદ(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, size);
        જો (hMem) {
            LPWSTR dst = (LPWSTR)GlobalLock(hMem);
            જો (dst) {
                // Copy the text over, adding carriage returns as necessary
                માટે (i = 0; tstr[i]; ++i) {
                    જો (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            જો (!SetClipboardData(CF_UNICODETEXT, hMem)) {
                result = WIN_SetError("Couldn't set clipboard data");
            }
        } નહીંતર {
            result = SDL_OutOfMemory();
        }
        SDL_free(tstr);
    }
    પાછા result;
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

    જો (WIN_OpenClipboard(_this)) {
        EmptyClipboard();

        // Set the clipboard text
        માટે (i = 0; i < _this->અંક_clipboard_mime_types; ++i) {
            અચલ અક્ષર *mime_type = _this->clipboard_mime_types[i];

            જો (SDL_IsTextMimeType(mime_type)) {
                જો (!WIN_SetClipboardText(_this, mime_type)) {
                    result = false;
                }
                // Only set the first clipboard text
                તોડો;
            }
        }

        // Set the clipboard image
        માટે (i = 0; i < _this->અંક_clipboard_mime_types; ++i) {
            અચલ અક્ષર *mime_type = _this->clipboard_mime_types[i];

            જો (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                જો (!WIN_SetClipboardImage(_this, mime_type)) {
                    result = false;
                }
                તોડો;
            }
        }

        data->clipboard_ગણતરી = Get_Clipboard_Sequence_સંખ્યા();
        WIN_CloseClipboard();
    } નહીંતર {
        result = WIN_SetError("Couldn't open clipboard");
    }
    પાછા result;
}

શૂન્ય *WIN_GetClipboardData(SDL_VideoDevice *_this, અચલ અક્ષર *mime_type, size_t *size)
{
    શૂન્ય *data = ખાલી;

    જો (SDL_IsTextMimeType(mime_type)) {
        અક્ષર *text = ખાલી;

        જો (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
            જો (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = GetClipboardData(CF_UNICODETEXT);
                જો (hMem) {
                    str = (LPTSTR)GlobalLock(hMem);
                    જો (str) {
                        text = WIN_StringToUTF8W(str);
                        GlobalUnlock(hMem);
                    } નહીંતર {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } નહીંતર {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } નહીંતર જો (IsClipboardFormatAvailable(CF_TEXT)) {
            જો (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = GetClipboardData(CF_TEXT);
                જો (hMem) {
                    str = (LPCSTR)GlobalLock(hMem);
                    જો (str) {
                        text = SDL_strdup(str);
                        GlobalUnlock(hMem);
                    } નહીંતર {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } નહીંતર {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }
        જો (!text) {
            text = SDL_strdup("");
        }
        data = text;
        *size = SDL_strlen(text);

    } નહીંતર જો (SDL_strcmp(mime_type, "image/bmp") == 0) {
        જો (IsClipboardFormatAvailable(CF_DIBV5)) {
            જો (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIBV5);
                જો (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } નહીંતર {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } નહીંતર જો (IsClipboardFormatAvailable(CF_DIB)) {
            જો (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIB);
                જો (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } નહીંતર {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } નહીંતર જો (SDL_strcmp(mime_type, "image/png") == 0) {
        જો (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            જો (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(GetClipboardFormatPNG());
                જો (hMem) {
                    size_t mem_size = GlobalSize(hMem);
                    શૂન્ય *mem = GlobalLock(hMem);
                    જો (mem) {
                        data = SDL_malloc(mem_size);
                        જો (data) {
                            SDL_memcpy(data, mem, mem_size);
                            *size = mem_size;
                        }
                        GlobalUnlock(hMem);
                    } નહીંતર {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } નહીંતર {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } નહીંતર {
        data = SDL_GetInternalClipboardData(_this, mime_type, size);
    }
    પાછા data;
}

bool WIN_HasClipboardData(SDL_VideoDevice *_this, અચલ અક્ષર *mime_type)
{
    જો (SDL_IsTextMimeType(mime_type)) {
        જો (IsClipboardFormatAvailable(CF_UNICODETEXT) || IsClipboardFormatAvailable(CF_TEXT)) {
            પાછા true;
        }
    } નહીંતર જો (SDL_strcmp(mime_type, "image/bmp") == 0) {
        જો (IsClipboardFormatAvailable(CF_DIBV5) || IsClipboardFormatAvailable(CF_DIB)) {
            પાછા true;
        }
    } નહીંતર જો (SDL_strcmp(mime_type, "image/png") == 0) {
        જો (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            પાછા true;
        }
    }
    પાછા SDL_HasInternalClipboardData(_this, mime_type);
}

સ્થિર પૂર્ણાંક GetClipboardFormatMimeType(UINT format, અક્ષર *name)
{
    અચલ અક્ષર *mime_type = ખાલી;

    પસંદગી (format) {
    સ્થિતિ CF_TEXT:
        mime_type = "text/plain";
        તોડો;
    સ્થિતિ CF_UNICODETEXT:
        mime_type = "text/plain;charset=utf-8";
        તોડો;
    સ્થિતિ CF_DIB:
    સ્થિતિ CF_DIBV5:
        mime_type = "image/bmp";
        તોડો;
    મૂળભૂત:
        જો (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        તોડો;
    }
    જો (mime_type) {
        size_t len = SDL_strlen(mime_type) + 1;
        જો (name) {
            SDL_memcpy(name, mime_type, len);
        }
        પાછા (પૂર્ણાંક)len;
    }
    પાછા 0;
}

સ્થિર અક્ષર **GetMimeTypes(પૂર્ણાંક *pnformats)
{
    અક્ષર **new_mime_types = ખાલી;

    *pnformats = 0;

    જો (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        પૂર્ણાંક nformats = 0;
        UINT format = 0;
        પૂર્ણાંક formatsSz = 0;
        bool have_image_bmp = false;
        માટે ( ; ; ) {
            format = EnumClipboardFormats(format);
            જો (!format) {
                તોડો;
            }

#ifdef DEBUG_CLIPBOARD
            અક્ષર name[128] = { 0 };
            GetClipboardFormatNameA(format, name, કદ(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#endif

            જો (format == CF_DIB || format == CF_DIBV5) {
                જો (have_image_bmp) {
                    // We have already registered this format
                    ચાલુ;
                }
                have_image_bmp = true;
            }

            પૂર્ણાંક len = GetClipboardFormatMimeType(format, ખાલી);
            જો (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_AllocateTemporaryMemory((nformats + 1) * કદ(અક્ષર *) + formatsSz);
        જો (new_mime_types) {
            format = 0;
            અક્ષર *strPtr = (અક્ષર *)(new_mime_types + nformats + 1);
            પૂર્ણાંક i = 0;
            માટે ( ; ; ) {
                format = EnumClipboardFormats(format);
                જો (!format) {
                    તોડો;
                }

                જો (format == CF_DIB || format == CF_DIBV5) {
                    જો (have_image_bmp) {
                        // We have already registered this format
                        ચાલુ;
                    }
                    have_image_bmp = true;
                }

                પૂર્ણાંક len = GetClipboardFormatMimeType(format, strPtr);
                જો (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = ખાલી;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    પાછા new_mime_types;
}

શૂન્ય WIN_CheckClipboardUpdate(સંરચના SDL_VideoData *data)
{
    DWORD ગણતરી = Get_Clipboard_Sequence_સંખ્યા();
    જો (ગણતરી != data->clipboard_ગણતરી) {
        જો (ગણતરી) {
            પૂર્ણાંક nformats = 0;
            અક્ષર **new_mime_types = GetMimeTypes(&nformats);
            જો (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        data->clipboard_ગણતરી = ગણતરી;
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
