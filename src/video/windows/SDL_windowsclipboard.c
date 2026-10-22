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

#nếu defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

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

    nếu (!format) {
        format = RegisterClipboardFormat(TEXT("PNG"));
    }
    trả_về format;
}

static BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    const số_nguyên MAX_ATTEMPTS = 3;
    số_nguyên attempt;
    HWND hwnd = NULL;

    nếu (_this->windows) {
        hwnd = _this->windows->internal->hwnd;
    }
    cho (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        nếu (OpenClipboard(hwnd)) {
            trả_về TRUE;
        }
        SDL_Delay(10);
    }
    trả_về FALSE;
}

static void WIN_CloseClipboard(void)
{
    CloseClipboard();
}

static HANDLE WIN_ConvertBMPtoDIB(const void *bmp, size_t bmp_size, UINT *format)
{
    HANDLE hMem = NULL;

    nếu (bmp && bmp_size > sizeof(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + sizeof(BITMAPFILEHEADER));
        size_t bih_size = pbih->biSize + pbih->biClrUsed * sizeof(RGBQUAD);
        size_t pixels_size = pbih->biSizeImage;

        nếu (pbih->biSize >= sizeof(BITMAPV5HEADER)) {
            *format = CF_DIBV5;
        } không_thì {
            *format = CF_DIB;
        }

        nếu (pbfh->bfOffBits >= (sizeof(BITMAPFILEHEADER) + bih_size) &&
            (pbfh->bfOffBits + pixels_size) <= bmp_size) {
            const Uint8 *pixels = (const Uint8 *)bmp + pbfh->bfOffBits;
            size_t dib_size = bih_size + pixels_size;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_size);
            nếu (hMem) {
                LPVOID dst = GlobalLock(hMem);
                nếu (dst) {
                    SDL_memcpy(dst, pbih, bih_size);
                    SDL_memcpy((Uint8 *)dst + bih_size, pixels, pixels_size);
                    GlobalUnlock(hMem);
                } không_thì {
                    WIN_SetError("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = NULL;
                }
            } không_thì {
                SDL_OutOfMemory();
            }
        } không_thì {
            SDL_SetError("Invalid BMP data");
        }
    } không_thì {
        SDL_SetError("Invalid BMP data");
    }
    trả_về hMem;
}

static void *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *size)
{
    void *bmp = NULL;
    size_t mem_size = GlobalSize(hMem);

    nếu (mem_size > sizeof(BITMAPINFOHEADER)) {
        LPVOID dib = GlobalLock(hMem);
        nếu (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_table_size;
            switch (pbih->biCompression) {
            case BI_RGB:
                nếu (pbih->biBitCount <= 8) {
                    color_table_size = sizeof(RGBQUAD) * (pbih->biClrUsed == 0 ? 1 << pbih->biBitCount : pbih->biClrUsed);
                } không_thì {
                    color_table_size = 0;
                }
                break;
            case BI_BITFIELDS:
                color_table_size = 3 * sizeof(DWORD);
                break;
            case 6 /* BI_ALPHABITFIELDS */:
                // https://learn.microsoft.com/en-us/previous-versions/windows/embedded/aa452885(v=msdn.10)
                color_table_size = 4 * sizeof(DWORD);
                break;
            default: // FOURCC
                color_table_size = sizeof(RGBQUAD) * pbih->biClrUsed;
            }

            size_t bih_size = pbih->biSize + color_table_size;
            size_t dib_size = bih_size + pbih->biSizeImage;
            nếu (dib_size <= mem_size) {
                size_t bmp_size = sizeof(BITMAPFILEHEADER) + mem_size;
                bmp = SDL_malloc(bmp_size);
                nếu (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bfSize = (DWORD)bmp_size;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bfOffBits = (DWORD)(sizeof(BITMAPFILEHEADER) + pbih->biSize + color_table_size);
                    SDL_memcpy((Uint8 *)bmp + sizeof(BITMAPFILEHEADER), dib, mem_size);
                    *size = bmp_size;
                }
            } không_thì {
                SDL_SetError("Invalid BMP data");
            }
            GlobalUnlock(hMem);
        } không_thì {
            WIN_SetError("GlobalLock()");
        }
    } không_thì {
        SDL_SetError("Invalid BMP data");
    }
    trả_về bmp;
}

static bool WIN_SetClipboardImage(SDL_VideoDevice *_this, const char *mime_type)
{
    UINT format = 0;
    HANDLE hMem = NULL;
    size_t clipboard_data_size;
    const void *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    nếu (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_data, clipboard_data_size, &format);
    } không_thì nếu (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_data_size);
        nếu (hMem) {
            LPVOID dst = GlobalLock(hMem);
            nếu (dst) {
                SDL_memcpy(dst, clipboard_data, clipboard_data_size);
                GlobalUnlock(hMem);
            } không_thì {
                result = WIN_SetError("GlobalLock()");
                GlobalFree(hMem);
                hMem = NULL;
            }
        } không_thì {
            result = SDL_OutOfMemory();
        }
    } không_thì {
        result = SDL_SetError("Unknown image format");
    }
    nếu (hMem) {
        // Save the image to the clipboard
        nếu (!SetClipboardData(format, hMem)) {
            result = WIN_SetError("Couldn't set clipboard data");
        }
    } không_thì {
        // WIN_ConvertBMPtoDIB() set the error
        result = false;
    }
    trả_về result;
}

static bool WIN_SetClipboardText(SDL_VideoDevice *_this, const char *mime_type)
{
    HANDLE hMem;
    size_t clipboard_data_size;
    const void *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    nếu (clipboard_data && clipboard_data_size > 0) {
        SIZE_T i, size;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (const char *)clipboard_data, clipboard_data_size);
        nếu (!tstr) {
            trả_về SDL_SetError("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        cho (size = 0, i = 0; tstr[i]; ++i, ++size) {
            nếu (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++size;
            }
        }
        size = (size + 1) * sizeof(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, size);
        nếu (hMem) {
            LPWSTR dst = (LPWSTR)GlobalLock(hMem);
            nếu (dst) {
                // Copy the text over, adding carriage returns as necessary
                cho (i = 0; tstr[i]; ++i) {
                    nếu (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            nếu (!SetClipboardData(CF_UNICODETEXT, hMem)) {
                result = WIN_SetError("Couldn't set clipboard data");
            }
        } không_thì {
            result = SDL_OutOfMemory();
        }
        SDL_free(tstr);
    }
    trả_về result;
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

    nếu (WIN_OpenClipboard(_this)) {
        EmptyClipboard();

        // Set the clipboard text
        cho (i = 0; i < _this->num_clipboard_mime_types; ++i) {
            const char *mime_type = _this->clipboard_mime_types[i];

            nếu (SDL_IsTextMimeType(mime_type)) {
                nếu (!WIN_SetClipboardText(_this, mime_type)) {
                    result = false;
                }
                // Only set the first clipboard text
                break;
            }
        }

        // Set the clipboard image
        cho (i = 0; i < _this->num_clipboard_mime_types; ++i) {
            const char *mime_type = _this->clipboard_mime_types[i];

            nếu (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                nếu (!WIN_SetClipboardImage(_this, mime_type)) {
                    result = false;
                }
                break;
            }
        }

        data->clipboard_count = GetClipboardSequenceNumber();
        WIN_CloseClipboard();
    } không_thì {
        result = WIN_SetError("Couldn't open clipboard");
    }
    trả_về result;
}

void *WIN_GetClipboardData(SDL_VideoDevice *_this, const char *mime_type, size_t *size)
{
    void *data = NULL;

    nếu (SDL_IsTextMimeType(mime_type)) {
        char *text = NULL;

        nếu (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
            nếu (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = GetClipboardData(CF_UNICODETEXT);
                nếu (hMem) {
                    str = (LPTSTR)GlobalLock(hMem);
                    nếu (str) {
                        text = WIN_StringToUTF8W(str);
                        GlobalUnlock(hMem);
                    } không_thì {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } không_thì {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } không_thì nếu (IsClipboardFormatAvailable(CF_TEXT)) {
            nếu (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = GetClipboardData(CF_TEXT);
                nếu (hMem) {
                    str = (LPCSTR)GlobalLock(hMem);
                    nếu (str) {
                        text = SDL_strdup(str);
                        GlobalUnlock(hMem);
                    } không_thì {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } không_thì {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }
        nếu (!text) {
            text = SDL_strdup("");
        }
        data = text;
        *size = SDL_strlen(text);

    } không_thì nếu (SDL_strcmp(mime_type, "image/bmp") == 0) {
        nếu (IsClipboardFormatAvailable(CF_DIBV5)) {
            nếu (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIBV5);
                nếu (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } không_thì {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } không_thì nếu (IsClipboardFormatAvailable(CF_DIB)) {
            nếu (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIB);
                nếu (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } không_thì {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } không_thì nếu (SDL_strcmp(mime_type, "image/png") == 0) {
        nếu (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            nếu (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(GetClipboardFormatPNG());
                nếu (hMem) {
                    size_t mem_size = GlobalSize(hMem);
                    void *mem = GlobalLock(hMem);
                    nếu (mem) {
                        data = SDL_malloc(mem_size);
                        nếu (data) {
                            SDL_memcpy(data, mem, mem_size);
                            *size = mem_size;
                        }
                        GlobalUnlock(hMem);
                    } không_thì {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } không_thì {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } không_thì {
        data = SDL_GetInternalClipboardData(_this, mime_type, size);
    }
    trả_về data;
}

bool WIN_HasClipboardData(SDL_VideoDevice *_this, const char *mime_type)
{
    nếu (SDL_IsTextMimeType(mime_type)) {
        nếu (IsClipboardFormatAvailable(CF_UNICODETEXT) || IsClipboardFormatAvailable(CF_TEXT)) {
            trả_về true;
        }
    } không_thì nếu (SDL_strcmp(mime_type, "image/bmp") == 0) {
        nếu (IsClipboardFormatAvailable(CF_DIBV5) || IsClipboardFormatAvailable(CF_DIB)) {
            trả_về true;
        }
    } không_thì nếu (SDL_strcmp(mime_type, "image/png") == 0) {
        nếu (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            trả_về true;
        }
    }
    trả_về SDL_HasInternalClipboardData(_this, mime_type);
}

static số_nguyên GetClipboardFormatMimeType(UINT format, char *name)
{
    const char *mime_type = NULL;

    switch (format) {
    case CF_TEXT:
        mime_type = "text/plain";
        break;
    case CF_UNICODETEXT:
        mime_type = "text/plain;charset=utf-8";
        break;
    case CF_DIB:
    case CF_DIBV5:
        mime_type = "image/bmp";
        break;
    default:
        nếu (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        break;
    }
    nếu (mime_type) {
        size_t len = SDL_strlen(mime_type) + 1;
        nếu (name) {
            SDL_memcpy(name, mime_type, len);
        }
        trả_về (số_nguyên)len;
    }
    trả_về 0;
}

static char **GetMimeTypes(số_nguyên *pnformats)
{
    char **new_mime_types = NULL;

    *pnformats = 0;

    nếu (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        số_nguyên nformats = 0;
        UINT format = 0;
        số_nguyên formatsSz = 0;
        bool have_image_bmp = false;
        cho ( ; ; ) {
            format = EnumClipboardFormats(format);
            nếu (!format) {
                break;
            }

#ifdef DEBUG_CLIPBOARD
            char name[128] = { 0 };
            GetClipboardFormatNameA(format, name, sizeof(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#endif

            nếu (format == CF_DIB || format == CF_DIBV5) {
                nếu (have_image_bmp) {
                    // We have already registered this format
                    continue;
                }
                have_image_bmp = true;
            }

            số_nguyên len = GetClipboardFormatMimeType(format, NULL);
            nếu (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_AllocateTemporaryMemory((nformats + 1) * sizeof(char *) + formatsSz);
        nếu (new_mime_types) {
            format = 0;
            char *strPtr = (char *)(new_mime_types + nformats + 1);
            số_nguyên i = 0;
            cho ( ; ; ) {
                format = EnumClipboardFormats(format);
                nếu (!format) {
                    break;
                }

                nếu (format == CF_DIB || format == CF_DIBV5) {
                    nếu (have_image_bmp) {
                        // We have already registered this format
                        continue;
                    }
                    have_image_bmp = true;
                }

                số_nguyên len = GetClipboardFormatMimeType(format, strPtr);
                nếu (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = NULL;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    trả_về new_mime_types;
}

void WIN_CheckClipboardUpdate(struct SDL_VideoData *data)
{
    DWORD count = GetClipboardSequenceNumber();
    nếu (count != data->clipboard_count) {
        nếu (count) {
            số_nguyên nformats = 0;
            char **new_mime_types = GetMimeTypes(&nformats);
            nếu (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        data->clipboard_count = count;
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
