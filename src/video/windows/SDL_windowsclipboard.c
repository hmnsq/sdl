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

#ถ้า defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

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

    ถ้า (!format) {
        format = RegisterClipboardFormat(TEXT("PNG"));
    }
    คืน format;
}

static BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    const จำนวนเต็ม MAX_ATTEMPTS = 3;
    จำนวนเต็ม attempt;
    HWND hwnd = NULL;

    ถ้า (_this->windows) {
        hwnd = _this->windows->internal->hwnd;
    }
    สำหรับ (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        ถ้า (OpenClipboard(hwnd)) {
            คืน TRUE;
        }
        SDL_Delay(10);
    }
    คืน FALSE;
}

static void WIN_CloseClipboard(void)
{
    CloseClipboard();
}

static HANDLE WIN_ConvertBMPtoDIB(const void *bmp, size_t bmp_size, UINT *format)
{
    HANDLE hMem = NULL;

    ถ้า (bmp && bmp_size > parimaa_na(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + parimaa_na(BITMAPFILEHEADER));
        size_t bih_size = pbih->biSize + pbih->biClrUsed * parimaa_na(RGBQUAD);
        size_t pixels_size = pbih->biSizeImage;

        ถ้า (pbih->biSize >= parimaa_na(BITMAPV5HEADER)) {
            *format = CF_DIBV5;
        } มิฉะนั้น {
            *format = CF_DIB;
        }

        ถ้า (pbfh->bfOffBits >= (parimaa_na(BITMAPFILEHEADER) + bih_size) &&
            (pbfh->bfOffBits + pixels_size) <= bmp_size) {
            const Uint8 *pixels = (const Uint8 *)bmp + pbfh->bfOffBits;
            size_t dib_size = bih_size + pixels_size;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_size);
            ถ้า (hMem) {
                LPVOID dst = GlobalLock(hMem);
                ถ้า (dst) {
                    SDL_memcpy(dst, pbih, bih_size);
                    SDL_memcpy((Uint8 *)dst + bih_size, pixels, pixels_size);
                    GlobalUnlock(hMem);
                } มิฉะนั้น {
                    WIN_SetError("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = NULL;
                }
            } มิฉะนั้น {
                SDL_OutOfMemory();
            }
        } มิฉะนั้น {
            SDL_SetError("Invalid BMP data");
        }
    } มิฉะนั้น {
        SDL_SetError("Invalid BMP data");
    }
    คืน hMem;
}

static void *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *size)
{
    void *bmp = NULL;
    size_t mem_size = GlobalSize(hMem);

    ถ้า (mem_size > parimaa_na(BITMAPINFOHEADER)) {
        LPVOID dib = GlobalLock(hMem);
        ถ้า (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_table_size;
            switch (pbih->biCompression) {
            pak_sa BI_RGB:
                ถ้า (pbih->biBitCount <= 8) {
                    color_table_size = parimaa_na(RGBQUAD) * (pbih->biClrUsed == 0 ? 1 << pbih->biBitCount : pbih->biClrUsed);
                } มิฉะนั้น {
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
            ถ้า (dib_size <= mem_size) {
                size_t bmp_size = parimaa_na(BITMAPFILEHEADER) + mem_size;
                bmp = SDL_malloc(bmp_size);
                ถ้า (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bfSize = (DWORD)bmp_size;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bfOffBits = (DWORD)(parimaa_na(BITMAPFILEHEADER) + pbih->biSize + color_table_size);
                    SDL_memcpy((Uint8 *)bmp + parimaa_na(BITMAPFILEHEADER), dib, mem_size);
                    *size = bmp_size;
                }
            } มิฉะนั้น {
                SDL_SetError("Invalid BMP data");
            }
            GlobalUnlock(hMem);
        } มิฉะนั้น {
            WIN_SetError("GlobalLock()");
        }
    } มิฉะนั้น {
        SDL_SetError("Invalid BMP data");
    }
    คืน bmp;
}

static bool WIN_SetClipboardImage(SDL_VideoDevice *_this, const var_na *mime_type)
{
    UINT format = 0;
    HANDLE hMem = NULL;
    size_t clipboard_data_size;
    const void *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    ถ้า (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_data, clipboard_data_size, &format);
    } มิฉะนั้น ถ้า (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_data_size);
        ถ้า (hMem) {
            LPVOID dst = GlobalLock(hMem);
            ถ้า (dst) {
                SDL_memcpy(dst, clipboard_data, clipboard_data_size);
                GlobalUnlock(hMem);
            } มิฉะนั้น {
                result = WIN_SetError("GlobalLock()");
                GlobalFree(hMem);
                hMem = NULL;
            }
        } มิฉะนั้น {
            result = SDL_OutOfMemory();
        }
    } มิฉะนั้น {
        result = SDL_SetError("Unknown image format");
    }
    ถ้า (hMem) {
        // Save the image to the clipboard
        ถ้า (!SetClipboardData(format, hMem)) {
            result = WIN_SetError("Couldn't set clipboard data");
        }
    } มิฉะนั้น {
        // WIN_ConvertBMPtoDIB() set the error
        result = false;
    }
    คืน result;
}

static bool WIN_SetClipboardText(SDL_VideoDevice *_this, const var_na *mime_type)
{
    HANDLE hMem;
    size_t clipboard_data_size;
    const void *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    ถ้า (clipboard_data && clipboard_data_size > 0) {
        SIZE_T i, size;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (const var_na *)clipboard_data, clipboard_data_size);
        ถ้า (!tstr) {
            คืน SDL_SetError("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        สำหรับ (size = 0, i = 0; tstr[i]; ++i, ++size) {
            ถ้า (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++size;
            }
        }
        size = (size + 1) * parimaa_na(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, size);
        ถ้า (hMem) {
            LPWSTR dst = (LPWSTR)GlobalLock(hMem);
            ถ้า (dst) {
                // Copy the text over, adding carriage returns as necessary
                สำหรับ (i = 0; tstr[i]; ++i) {
                    ถ้า (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            ถ้า (!SetClipboardData(CF_UNICODETEXT, hMem)) {
                result = WIN_SetError("Couldn't set clipboard data");
            }
        } มิฉะนั้น {
            result = SDL_OutOfMemory();
        }
        SDL_free(tstr);
    }
    คืน result;
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

    ถ้า (WIN_OpenClipboard(_this)) {
        EmptyClipboard();

        // Set the clipboard text
        สำหรับ (i = 0; i < _this->num_clipboard_mime_types; ++i) {
            const var_na *mime_type = _this->clipboard_mime_types[i];

            ถ้า (SDL_IsTextMimeType(mime_type)) {
                ถ้า (!WIN_SetClipboardText(_this, mime_type)) {
                    result = false;
                }
                // Only set the first clipboard text
                bha_nga;
            }
        }

        // Set the clipboard image
        สำหรับ (i = 0; i < _this->num_clipboard_mime_types; ++i) {
            const var_na *mime_type = _this->clipboard_mime_types[i];

            ถ้า (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                ถ้า (!WIN_SetClipboardImage(_this, mime_type)) {
                    result = false;
                }
                bha_nga;
            }
        }

        data->clipboard_count = GetClipboardSequenceNumber();
        WIN_CloseClipboard();
    } มิฉะนั้น {
        result = WIN_SetError("Couldn't open clipboard");
    }
    คืน result;
}

void *WIN_GetClipboardData(SDL_VideoDevice *_this, const var_na *mime_type, size_t *size)
{
    void *data = NULL;

    ถ้า (SDL_IsTextMimeType(mime_type)) {
        var_na *text = NULL;

        ถ้า (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
            ถ้า (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = GetClipboardData(CF_UNICODETEXT);
                ถ้า (hMem) {
                    str = (LPTSTR)GlobalLock(hMem);
                    ถ้า (str) {
                        text = WIN_StringToUTF8W(str);
                        GlobalUnlock(hMem);
                    } มิฉะนั้น {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } มิฉะนั้น {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } มิฉะนั้น ถ้า (IsClipboardFormatAvailable(CF_TEXT)) {
            ถ้า (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = GetClipboardData(CF_TEXT);
                ถ้า (hMem) {
                    str = (LPCSTR)GlobalLock(hMem);
                    ถ้า (str) {
                        text = SDL_strdup(str);
                        GlobalUnlock(hMem);
                    } มิฉะนั้น {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } มิฉะนั้น {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }
        ถ้า (!text) {
            text = SDL_strdup("");
        }
        data = text;
        *size = SDL_strlen(text);

    } มิฉะนั้น ถ้า (SDL_strcmp(mime_type, "image/bmp") == 0) {
        ถ้า (IsClipboardFormatAvailable(CF_DIBV5)) {
            ถ้า (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIBV5);
                ถ้า (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } มิฉะนั้น {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } มิฉะนั้น ถ้า (IsClipboardFormatAvailable(CF_DIB)) {
            ถ้า (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIB);
                ถ้า (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } มิฉะนั้น {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } มิฉะนั้น ถ้า (SDL_strcmp(mime_type, "image/png") == 0) {
        ถ้า (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            ถ้า (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(GetClipboardFormatPNG());
                ถ้า (hMem) {
                    size_t mem_size = GlobalSize(hMem);
                    void *mem = GlobalLock(hMem);
                    ถ้า (mem) {
                        data = SDL_malloc(mem_size);
                        ถ้า (data) {
                            SDL_memcpy(data, mem, mem_size);
                            *size = mem_size;
                        }
                        GlobalUnlock(hMem);
                    } มิฉะนั้น {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } มิฉะนั้น {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } มิฉะนั้น {
        data = SDL_GetInternalClipboardData(_this, mime_type, size);
    }
    คืน data;
}

bool WIN_HasClipboardData(SDL_VideoDevice *_this, const var_na *mime_type)
{
    ถ้า (SDL_IsTextMimeType(mime_type)) {
        ถ้า (IsClipboardFormatAvailable(CF_UNICODETEXT) || IsClipboardFormatAvailable(CF_TEXT)) {
            คืน true;
        }
    } มิฉะนั้น ถ้า (SDL_strcmp(mime_type, "image/bmp") == 0) {
        ถ้า (IsClipboardFormatAvailable(CF_DIBV5) || IsClipboardFormatAvailable(CF_DIB)) {
            คืน true;
        }
    } มิฉะนั้น ถ้า (SDL_strcmp(mime_type, "image/png") == 0) {
        ถ้า (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            คืน true;
        }
    }
    คืน SDL_HasInternalClipboardData(_this, mime_type);
}

static จำนวนเต็ม GetClipboardFormatMimeType(UINT format, var_na *name)
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
        ถ้า (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        bha_nga;
    }
    ถ้า (mime_type) {
        size_t len = SDL_strlen(mime_type) + 1;
        ถ้า (name) {
            SDL_memcpy(name, mime_type, len);
        }
        คืน (จำนวนเต็ม)len;
    }
    คืน 0;
}

static var_na **GetMimeTypes(จำนวนเต็ม *pnformats)
{
    var_na **new_mime_types = NULL;

    *pnformats = 0;

    ถ้า (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        จำนวนเต็ม nformats = 0;
        UINT format = 0;
        จำนวนเต็ม formatsSz = 0;
        bool have_image_bmp = false;
        สำหรับ ( ; ; ) {
            format = EnumClipboardFormats(format);
            ถ้า (!format) {
                bha_nga;
            }

#ifdef DEBUG_CLIPBOARD
            var_na name[128] = { 0 };
            GetClipboardFormatNameA(format, name, parimaa_na(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#endif

            ถ้า (format == CF_DIB || format == CF_DIBV5) {
                ถ้า (have_image_bmp) {
                    // We have already registered this format
                    continue;
                }
                have_image_bmp = true;
            }

            จำนวนเต็ม len = GetClipboardFormatMimeType(format, NULL);
            ถ้า (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_AllocateTemporaryMemory((nformats + 1) * parimaa_na(var_na *) + formatsSz);
        ถ้า (new_mime_types) {
            format = 0;
            var_na *strPtr = (var_na *)(new_mime_types + nformats + 1);
            จำนวนเต็ม i = 0;
            สำหรับ ( ; ; ) {
                format = EnumClipboardFormats(format);
                ถ้า (!format) {
                    bha_nga;
                }

                ถ้า (format == CF_DIB || format == CF_DIBV5) {
                    ถ้า (have_image_bmp) {
                        // We have already registered this format
                        continue;
                    }
                    have_image_bmp = true;
                }

                จำนวนเต็ม len = GetClipboardFormatMimeType(format, strPtr);
                ถ้า (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = NULL;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    คืน new_mime_types;
}

void WIN_CheckClipboardUpdate(sa_nracanaa SDL_VideoData *data)
{
    DWORD count = GetClipboardSequenceNumber();
    ถ้า (count != data->clipboard_count) {
        ถ้า (count) {
            จำนวนเต็ม nformats = 0;
            var_na **new_mime_types = GetMimeTypes(&nformats);
            ถ้า (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        data->clipboard_count = count;
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
