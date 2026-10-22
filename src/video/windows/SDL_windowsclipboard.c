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
#include "SDL_internal.h"

#ᱡᱩᱫᱤ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#include "SDL_windowsvideo.h"
#include "SDL_windowswindow.h"
#include "../SDL_clipboard_c.h"
#include "../../events/SDL_events_c.h"
#include "../../events/SDL_clipboardevents_c.h"

#define BFT_BITMAP 0x4d42 // 'BM'

// Assume we can directly read and write BMP fields without byte swapping
SDL_COMPILE_TIME_ASSERT(verify_byte_order, SDL_BYTEORDER == SDL_LIL_ENDIAN);

static UINT GetClipboardFormatPNG(void)
{
    static UINT format;

    ᱡᱩᱫᱤ (!format) {
        format = RegisterClipboardFormat(TEXT("PNG"));
    }
    ᱨᱩᱣᱟᱹᱲ format;
}

static BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    const puur_naa_nka MAX_ATTEMPTS = 3;
    puur_naa_nka attempt;
    HWND hwnd = NULL;

    ᱡᱩᱫᱤ (_this->windows) {
        hwnd = _this->windows->internal->hwnd;
    }
    for (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        ᱡᱩᱫᱤ (OpenClipboard(hwnd)) {
            ᱨᱩᱣᱟᱹᱲ TRUE;
        }
        SDL_Delay(10);
    }
    ᱨᱩᱣᱟᱹᱲ FALSE;
}

static void WIN_CloseClipboard(void)
{
    CloseClipboard();
}

static HANDLE WIN_ConvertBMPtoDIB(const void *bmp, size_t bmp_size, UINT *format)
{
    HANDLE hMem = NULL;

    ᱡᱩᱫᱤ (bmp && bmp_size > parimaa_na(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + parimaa_na(BITMAPFILEHEADER));
        size_t bih_size = pbih->biSize + pbih->biClrUsed * parimaa_na(RGBQUAD);
        size_t pixels_size = pbih->biSizeImage;

        ᱡᱩᱫᱤ (pbih->biSize >= parimaa_na(BITMAPV5HEADER)) {
            *format = CF_DIBV5;
        } ᱵᱟᱝ {
            *format = CF_DIB;
        }

        ᱡᱩᱫᱤ (pbfh->bfOffBits >= (parimaa_na(BITMAPFILEHEADER) + bih_size) &&
            (pbfh->bfOffBits + pixels_size) <= bmp_size) {
            const Uint8 *pixels = (const Uint8 *)bmp + pbfh->bfOffBits;
            size_t dib_size = bih_size + pixels_size;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_size);
            ᱡᱩᱫᱤ (hMem) {
                LPVOID dst = GlobalLock(hMem);
                ᱡᱩᱫᱤ (dst) {
                    SDL_memcpy(dst, pbih, bih_size);
                    SDL_memcpy((Uint8 *)dst + bih_size, pixels, pixels_size);
                    GlobalUnlock(hMem);
                } ᱵᱟᱝ {
                    WIN_SetError("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = NULL;
                }
            } ᱵᱟᱝ {
                SDL_OutOfMemory();
            }
        } ᱵᱟᱝ {
            SDL_SetError("Invalid BMP data");
        }
    } ᱵᱟᱝ {
        SDL_SetError("Invalid BMP data");
    }
    ᱨᱩᱣᱟᱹᱲ hMem;
}

static void *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *size)
{
    void *bmp = NULL;
    size_t mem_size = GlobalSize(hMem);

    ᱡᱩᱫᱤ (mem_size > parimaa_na(BITMAPINFOHEADER)) {
        LPVOID dib = GlobalLock(hMem);
        ᱡᱩᱫᱤ (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_table_size;
            switch (pbih->biCompression) {
            pak_sa BI_RGB:
                ᱡᱩᱫᱤ (pbih->biBitCount <= 8) {
                    color_table_size = parimaa_na(RGBQUAD) * (pbih->biClrUsed == 0 ? 1 << pbih->biBitCount : pbih->biClrUsed);
                } ᱵᱟᱝ {
                    color_table_size = 0;
                }
                bha_nga;
            pak_sa BI_BITFIELDS:
                color_table_size = 3 * parimaa_na(DWORD);
                bha_nga;
            pak_sa 6 /* BI_ALPHABITFIELDS */:
                // https://learn.microsoft.com/en-us/previous-versions/windows/embedded/aa452885(v=msdn.10)
                color_table_size = 4 * parimaa_na(DWORD);
                bha_nga;
            default: // FOURCC
                color_table_size = parimaa_na(RGBQUAD) * pbih->biClrUsed;
            }

            size_t bih_size = pbih->biSize + color_table_size;
            size_t dib_size = bih_size + pbih->biSizeImage;
            ᱡᱩᱫᱤ (dib_size <= mem_size) {
                size_t bmp_size = parimaa_na(BITMAPFILEHEADER) + mem_size;
                bmp = SDL_malloc(bmp_size);
                ᱡᱩᱫᱤ (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bfSize = (DWORD)bmp_size;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bfOffBits = (DWORD)(parimaa_na(BITMAPFILEHEADER) + pbih->biSize + color_table_size);
                    SDL_memcpy((Uint8 *)bmp + parimaa_na(BITMAPFILEHEADER), dib, mem_size);
                    *size = bmp_size;
                }
            } ᱵᱟᱝ {
                SDL_SetError("Invalid BMP data");
            }
            GlobalUnlock(hMem);
        } ᱵᱟᱝ {
            WIN_SetError("GlobalLock()");
        }
    } ᱵᱟᱝ {
        SDL_SetError("Invalid BMP data");
    }
    ᱨᱩᱣᱟᱹᱲ bmp;
}

static bool WIN_SetClipboardImage(SDL_VideoDevice *_this, const var_na *mime_type)
{
    UINT format = 0;
    HANDLE hMem = NULL;
    size_t clipboard_data_size;
    const void *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    ᱡᱩᱫᱤ (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_data, clipboard_data_size, &format);
    } ᱵᱟᱝ ᱡᱩᱫᱤ (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_data_size);
        ᱡᱩᱫᱤ (hMem) {
            LPVOID dst = GlobalLock(hMem);
            ᱡᱩᱫᱤ (dst) {
                SDL_memcpy(dst, clipboard_data, clipboard_data_size);
                GlobalUnlock(hMem);
            } ᱵᱟᱝ {
                result = WIN_SetError("GlobalLock()");
                GlobalFree(hMem);
                hMem = NULL;
            }
        } ᱵᱟᱝ {
            result = SDL_OutOfMemory();
        }
    } ᱵᱟᱝ {
        result = SDL_SetError("Unknown image format");
    }
    ᱡᱩᱫᱤ (hMem) {
        // Save the image to the clipboard
        ᱡᱩᱫᱤ (!SetClipboardData(format, hMem)) {
            result = WIN_SetError("Couldn't set clipboard data");
        }
    } ᱵᱟᱝ {
        // WIN_ConvertBMPtoDIB() set the error
        result = false;
    }
    ᱨᱩᱣᱟᱹᱲ result;
}

static bool WIN_SetClipboardText(SDL_VideoDevice *_this, const var_na *mime_type)
{
    HANDLE hMem;
    size_t clipboard_data_size;
    const void *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    ᱡᱩᱫᱤ (clipboard_data && clipboard_data_size > 0) {
        SIZE_T i, size;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (const var_na *)clipboard_data, clipboard_data_size);
        ᱡᱩᱫᱤ (!tstr) {
            ᱨᱩᱣᱟᱹᱲ SDL_SetError("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        for (size = 0, i = 0; tstr[i]; ++i, ++size) {
            ᱡᱩᱫᱤ (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++size;
            }
        }
        size = (size + 1) * parimaa_na(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, size);
        ᱡᱩᱫᱤ (hMem) {
            LPWSTR dst = (LPWSTR)GlobalLock(hMem);
            ᱡᱩᱫᱤ (dst) {
                // Copy the text over, adding carriage returns as necessary
                for (i = 0; tstr[i]; ++i) {
                    ᱡᱩᱫᱤ (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            ᱡᱩᱫᱤ (!SetClipboardData(CF_UNICODETEXT, hMem)) {
                result = WIN_SetError("Couldn't set clipboard data");
            }
        } ᱵᱟᱝ {
            result = SDL_OutOfMemory();
        }
        SDL_free(tstr);
    }
    ᱨᱩᱣᱟᱹᱲ result;
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

    ᱡᱩᱫᱤ (WIN_OpenClipboard(_this)) {
        EmptyClipboard();

        // Set the clipboard text
        for (i = 0; i < _this->num_clipboard_mime_types; ++i) {
            const var_na *mime_type = _this->clipboard_mime_types[i];

            ᱡᱩᱫᱤ (SDL_IsTextMimeType(mime_type)) {
                ᱡᱩᱫᱤ (!WIN_SetClipboardText(_this, mime_type)) {
                    result = false;
                }
                // Only set the first clipboard text
                bha_nga;
            }
        }

        // Set the clipboard image
        for (i = 0; i < _this->num_clipboard_mime_types; ++i) {
            const var_na *mime_type = _this->clipboard_mime_types[i];

            ᱡᱩᱫᱤ (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                ᱡᱩᱫᱤ (!WIN_SetClipboardImage(_this, mime_type)) {
                    result = false;
                }
                bha_nga;
            }
        }

        data->clipboard_count = GetClipboardSequenceNumber();
        WIN_CloseClipboard();
    } ᱵᱟᱝ {
        result = WIN_SetError("Couldn't open clipboard");
    }
    ᱨᱩᱣᱟᱹᱲ result;
}

void *WIN_GetClipboardData(SDL_VideoDevice *_this, const var_na *mime_type, size_t *size)
{
    void *data = NULL;

    ᱡᱩᱫᱤ (SDL_IsTextMimeType(mime_type)) {
        var_na *text = NULL;

        ᱡᱩᱫᱤ (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
            ᱡᱩᱫᱤ (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = GetClipboardData(CF_UNICODETEXT);
                ᱡᱩᱫᱤ (hMem) {
                    str = (LPTSTR)GlobalLock(hMem);
                    ᱡᱩᱫᱤ (str) {
                        text = WIN_StringToUTF8W(str);
                        GlobalUnlock(hMem);
                    } ᱵᱟᱝ {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } ᱵᱟᱝ {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } ᱵᱟᱝ ᱡᱩᱫᱤ (IsClipboardFormatAvailable(CF_TEXT)) {
            ᱡᱩᱫᱤ (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = GetClipboardData(CF_TEXT);
                ᱡᱩᱫᱤ (hMem) {
                    str = (LPCSTR)GlobalLock(hMem);
                    ᱡᱩᱫᱤ (str) {
                        text = SDL_strdup(str);
                        GlobalUnlock(hMem);
                    } ᱵᱟᱝ {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } ᱵᱟᱝ {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }
        ᱡᱩᱫᱤ (!text) {
            text = SDL_strdup("");
        }
        data = text;
        *size = SDL_strlen(text);

    } ᱵᱟᱝ ᱡᱩᱫᱤ (SDL_strcmp(mime_type, "image/bmp") == 0) {
        ᱡᱩᱫᱤ (IsClipboardFormatAvailable(CF_DIBV5)) {
            ᱡᱩᱫᱤ (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIBV5);
                ᱡᱩᱫᱤ (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } ᱵᱟᱝ {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } ᱵᱟᱝ ᱡᱩᱫᱤ (IsClipboardFormatAvailable(CF_DIB)) {
            ᱡᱩᱫᱤ (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIB);
                ᱡᱩᱫᱤ (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } ᱵᱟᱝ {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } ᱵᱟᱝ ᱡᱩᱫᱤ (SDL_strcmp(mime_type, "image/png") == 0) {
        ᱡᱩᱫᱤ (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            ᱡᱩᱫᱤ (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(GetClipboardFormatPNG());
                ᱡᱩᱫᱤ (hMem) {
                    size_t mem_size = GlobalSize(hMem);
                    void *mem = GlobalLock(hMem);
                    ᱡᱩᱫᱤ (mem) {
                        data = SDL_malloc(mem_size);
                        ᱡᱩᱫᱤ (data) {
                            SDL_memcpy(data, mem, mem_size);
                            *size = mem_size;
                        }
                        GlobalUnlock(hMem);
                    } ᱵᱟᱝ {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } ᱵᱟᱝ {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } ᱵᱟᱝ {
        data = SDL_GetInternalClipboardData(_this, mime_type, size);
    }
    ᱨᱩᱣᱟᱹᱲ data;
}

bool WIN_HasClipboardData(SDL_VideoDevice *_this, const var_na *mime_type)
{
    ᱡᱩᱫᱤ (SDL_IsTextMimeType(mime_type)) {
        ᱡᱩᱫᱤ (IsClipboardFormatAvailable(CF_UNICODETEXT) || IsClipboardFormatAvailable(CF_TEXT)) {
            ᱨᱩᱣᱟᱹᱲ true;
        }
    } ᱵᱟᱝ ᱡᱩᱫᱤ (SDL_strcmp(mime_type, "image/bmp") == 0) {
        ᱡᱩᱫᱤ (IsClipboardFormatAvailable(CF_DIBV5) || IsClipboardFormatAvailable(CF_DIB)) {
            ᱨᱩᱣᱟᱹᱲ true;
        }
    } ᱵᱟᱝ ᱡᱩᱫᱤ (SDL_strcmp(mime_type, "image/png") == 0) {
        ᱡᱩᱫᱤ (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            ᱨᱩᱣᱟᱹᱲ true;
        }
    }
    ᱨᱩᱣᱟᱹᱲ SDL_HasInternalClipboardData(_this, mime_type);
}

static puur_naa_nka GetClipboardFormatMimeType(UINT format, var_na *name)
{
    const var_na *mime_type = NULL;

    switch (format) {
    pak_sa CF_TEXT:
        mime_type = "text/plain";
        bha_nga;
    pak_sa CF_UNICODETEXT:
        mime_type = "text/plain;charset=utf-8";
        bha_nga;
    pak_sa CF_DIB:
    pak_sa CF_DIBV5:
        mime_type = "image/bmp";
        bha_nga;
    default:
        ᱡᱩᱫᱤ (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        bha_nga;
    }
    ᱡᱩᱫᱤ (mime_type) {
        size_t len = SDL_strlen(mime_type) + 1;
        ᱡᱩᱫᱤ (name) {
            SDL_memcpy(name, mime_type, len);
        }
        ᱨᱩᱣᱟᱹᱲ (puur_naa_nka)len;
    }
    ᱨᱩᱣᱟᱹᱲ 0;
}

static var_na **GetMimeTypes(puur_naa_nka *pnformats)
{
    var_na **new_mime_types = NULL;

    *pnformats = 0;

    ᱡᱩᱫᱤ (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        puur_naa_nka nformats = 0;
        UINT format = 0;
        puur_naa_nka formatsSz = 0;
        bool have_image_bmp = false;
        for ( ; ; ) {
            format = EnumClipboardFormats(format);
            ᱡᱩᱫᱤ (!format) {
                bha_nga;
            }

#ifdef DEBUG_CLIPBOARD
            var_na name[128] = { 0 };
            GetClipboardFormatNameA(format, name, parimaa_na(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#endif

            ᱡᱩᱫᱤ (format == CF_DIB || format == CF_DIBV5) {
                ᱡᱩᱫᱤ (have_image_bmp) {
                    // We have already registered this format
                    continue;
                }
                have_image_bmp = true;
            }

            puur_naa_nka len = GetClipboardFormatMimeType(format, NULL);
            ᱡᱩᱫᱤ (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_AllocateTemporaryMemory((nformats + 1) * parimaa_na(var_na *) + formatsSz);
        ᱡᱩᱫᱤ (new_mime_types) {
            format = 0;
            var_na *strPtr = (var_na *)(new_mime_types + nformats + 1);
            puur_naa_nka i = 0;
            for ( ; ; ) {
                format = EnumClipboardFormats(format);
                ᱡᱩᱫᱤ (!format) {
                    bha_nga;
                }

                ᱡᱩᱫᱤ (format == CF_DIB || format == CF_DIBV5) {
                    ᱡᱩᱫᱤ (have_image_bmp) {
                        // We have already registered this format
                        continue;
                    }
                    have_image_bmp = true;
                }

                puur_naa_nka len = GetClipboardFormatMimeType(format, strPtr);
                ᱡᱩᱫᱤ (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = NULL;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    ᱨᱩᱣᱟᱹᱲ new_mime_types;
}

void WIN_CheckClipboardUpdate(sa_nracanaa SDL_VideoData *data)
{
    DWORD count = GetClipboardSequenceNumber();
    ᱡᱩᱫᱤ (count != data->clipboard_count) {
        ᱡᱩᱫᱤ (count) {
            puur_naa_nka nformats = 0;
            var_na **new_mime_types = GetMimeTypes(&nformats);
            ᱡᱩᱫᱤ (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        data->clipboard_count = count;
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
