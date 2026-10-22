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

#만약 defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

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

    만약 (!format) {
        format = RegisterClipboardFormat(TEXT("PNG"));
    }
    반환 format;
}

static BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    const 정수 MAX_ATTEMPTS = 3;
    정수 attempt;
    HWND hwnd = NULL;

    만약 (_this->windows) {
        hwnd = _this->windows->internal->hwnd;
    }
    위해 (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        만약 (OpenClipboard(hwnd)) {
            반환 TRUE;
        }
        SDL_Delay(10);
    }
    반환 FALSE;
}

static void WIN_CloseClipboard(void)
{
    CloseClipboard();
}

static HANDLE WIN_ConvertBMPtoDIB(const void *bmp, size_t bmp_size, UINT *format)
{
    HANDLE hMem = NULL;

    만약 (bmp && bmp_size > sizeof(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + sizeof(BITMAPFILEHEADER));
        size_t bih_size = pbih->biSize + pbih->biClrUsed * sizeof(RGBQUAD);
        size_t pixels_size = pbih->biSizeImage;

        만약 (pbih->biSize >= sizeof(BITMAPV5HEADER)) {
            *format = CF_DIBV5;
        } 아니면 {
            *format = CF_DIB;
        }

        만약 (pbfh->bfOffBits >= (sizeof(BITMAPFILEHEADER) + bih_size) &&
            (pbfh->bfOffBits + pixels_size) <= bmp_size) {
            const Uint8 *pixels = (const Uint8 *)bmp + pbfh->bfOffBits;
            size_t dib_size = bih_size + pixels_size;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_size);
            만약 (hMem) {
                LPVOID dst = GlobalLock(hMem);
                만약 (dst) {
                    SDL_memcpy(dst, pbih, bih_size);
                    SDL_memcpy((Uint8 *)dst + bih_size, pixels, pixels_size);
                    GlobalUnlock(hMem);
                } 아니면 {
                    WIN_SetError("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = NULL;
                }
            } 아니면 {
                SDL_OutOfMemory();
            }
        } 아니면 {
            SDL_SetError("Invalid BMP data");
        }
    } 아니면 {
        SDL_SetError("Invalid BMP data");
    }
    반환 hMem;
}

static void *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *size)
{
    void *bmp = NULL;
    size_t mem_size = GlobalSize(hMem);

    만약 (mem_size > sizeof(BITMAPINFOHEADER)) {
        LPVOID dib = GlobalLock(hMem);
        만약 (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_table_size;
            switch (pbih->biCompression) {
            case BI_RGB:
                만약 (pbih->biBitCount <= 8) {
                    color_table_size = sizeof(RGBQUAD) * (pbih->biClrUsed == 0 ? 1 << pbih->biBitCount : pbih->biClrUsed);
                } 아니면 {
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
            만약 (dib_size <= mem_size) {
                size_t bmp_size = sizeof(BITMAPFILEHEADER) + mem_size;
                bmp = SDL_malloc(bmp_size);
                만약 (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bfSize = (DWORD)bmp_size;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bfOffBits = (DWORD)(sizeof(BITMAPFILEHEADER) + pbih->biSize + color_table_size);
                    SDL_memcpy((Uint8 *)bmp + sizeof(BITMAPFILEHEADER), dib, mem_size);
                    *size = bmp_size;
                }
            } 아니면 {
                SDL_SetError("Invalid BMP data");
            }
            GlobalUnlock(hMem);
        } 아니면 {
            WIN_SetError("GlobalLock()");
        }
    } 아니면 {
        SDL_SetError("Invalid BMP data");
    }
    반환 bmp;
}

static bool WIN_SetClipboardImage(SDL_VideoDevice *_this, const char *mime_type)
{
    UINT format = 0;
    HANDLE hMem = NULL;
    size_t clipboard_data_size;
    const void *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    만약 (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_data, clipboard_data_size, &format);
    } 아니면 만약 (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_data_size);
        만약 (hMem) {
            LPVOID dst = GlobalLock(hMem);
            만약 (dst) {
                SDL_memcpy(dst, clipboard_data, clipboard_data_size);
                GlobalUnlock(hMem);
            } 아니면 {
                result = WIN_SetError("GlobalLock()");
                GlobalFree(hMem);
                hMem = NULL;
            }
        } 아니면 {
            result = SDL_OutOfMemory();
        }
    } 아니면 {
        result = SDL_SetError("Unknown image format");
    }
    만약 (hMem) {
        // Save the image to the clipboard
        만약 (!SetClipboardData(format, hMem)) {
            result = WIN_SetError("Couldn't set clipboard data");
        }
    } 아니면 {
        // WIN_ConvertBMPtoDIB() set the error
        result = false;
    }
    반환 result;
}

static bool WIN_SetClipboardText(SDL_VideoDevice *_this, const char *mime_type)
{
    HANDLE hMem;
    size_t clipboard_data_size;
    const void *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    만약 (clipboard_data && clipboard_data_size > 0) {
        SIZE_T i, size;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (const char *)clipboard_data, clipboard_data_size);
        만약 (!tstr) {
            반환 SDL_SetError("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        위해 (size = 0, i = 0; tstr[i]; ++i, ++size) {
            만약 (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++size;
            }
        }
        size = (size + 1) * sizeof(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, size);
        만약 (hMem) {
            LPWSTR dst = (LPWSTR)GlobalLock(hMem);
            만약 (dst) {
                // Copy the text over, adding carriage returns as necessary
                위해 (i = 0; tstr[i]; ++i) {
                    만약 (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            만약 (!SetClipboardData(CF_UNICODETEXT, hMem)) {
                result = WIN_SetError("Couldn't set clipboard data");
            }
        } 아니면 {
            result = SDL_OutOfMemory();
        }
        SDL_free(tstr);
    }
    반환 result;
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

    만약 (WIN_OpenClipboard(_this)) {
        EmptyClipboard();

        // Set the clipboard text
        위해 (i = 0; i < _this->num_clipboard_mime_types; ++i) {
            const char *mime_type = _this->clipboard_mime_types[i];

            만약 (SDL_IsTextMimeType(mime_type)) {
                만약 (!WIN_SetClipboardText(_this, mime_type)) {
                    result = false;
                }
                // Only set the first clipboard text
                break;
            }
        }

        // Set the clipboard image
        위해 (i = 0; i < _this->num_clipboard_mime_types; ++i) {
            const char *mime_type = _this->clipboard_mime_types[i];

            만약 (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                만약 (!WIN_SetClipboardImage(_this, mime_type)) {
                    result = false;
                }
                break;
            }
        }

        data->clipboard_count = GetClipboardSequenceNumber();
        WIN_CloseClipboard();
    } 아니면 {
        result = WIN_SetError("Couldn't open clipboard");
    }
    반환 result;
}

void *WIN_GetClipboardData(SDL_VideoDevice *_this, const char *mime_type, size_t *size)
{
    void *data = NULL;

    만약 (SDL_IsTextMimeType(mime_type)) {
        char *text = NULL;

        만약 (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
            만약 (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = GetClipboardData(CF_UNICODETEXT);
                만약 (hMem) {
                    str = (LPTSTR)GlobalLock(hMem);
                    만약 (str) {
                        text = WIN_StringToUTF8W(str);
                        GlobalUnlock(hMem);
                    } 아니면 {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } 아니면 {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } 아니면 만약 (IsClipboardFormatAvailable(CF_TEXT)) {
            만약 (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = GetClipboardData(CF_TEXT);
                만약 (hMem) {
                    str = (LPCSTR)GlobalLock(hMem);
                    만약 (str) {
                        text = SDL_strdup(str);
                        GlobalUnlock(hMem);
                    } 아니면 {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } 아니면 {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }
        만약 (!text) {
            text = SDL_strdup("");
        }
        data = text;
        *size = SDL_strlen(text);

    } 아니면 만약 (SDL_strcmp(mime_type, "image/bmp") == 0) {
        만약 (IsClipboardFormatAvailable(CF_DIBV5)) {
            만약 (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIBV5);
                만약 (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } 아니면 {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } 아니면 만약 (IsClipboardFormatAvailable(CF_DIB)) {
            만약 (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIB);
                만약 (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } 아니면 {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } 아니면 만약 (SDL_strcmp(mime_type, "image/png") == 0) {
        만약 (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            만약 (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(GetClipboardFormatPNG());
                만약 (hMem) {
                    size_t mem_size = GlobalSize(hMem);
                    void *mem = GlobalLock(hMem);
                    만약 (mem) {
                        data = SDL_malloc(mem_size);
                        만약 (data) {
                            SDL_memcpy(data, mem, mem_size);
                            *size = mem_size;
                        }
                        GlobalUnlock(hMem);
                    } 아니면 {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } 아니면 {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } 아니면 {
        data = SDL_GetInternalClipboardData(_this, mime_type, size);
    }
    반환 data;
}

bool WIN_HasClipboardData(SDL_VideoDevice *_this, const char *mime_type)
{
    만약 (SDL_IsTextMimeType(mime_type)) {
        만약 (IsClipboardFormatAvailable(CF_UNICODETEXT) || IsClipboardFormatAvailable(CF_TEXT)) {
            반환 true;
        }
    } 아니면 만약 (SDL_strcmp(mime_type, "image/bmp") == 0) {
        만약 (IsClipboardFormatAvailable(CF_DIBV5) || IsClipboardFormatAvailable(CF_DIB)) {
            반환 true;
        }
    } 아니면 만약 (SDL_strcmp(mime_type, "image/png") == 0) {
        만약 (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            반환 true;
        }
    }
    반환 SDL_HasInternalClipboardData(_this, mime_type);
}

static 정수 GetClipboardFormatMimeType(UINT format, char *name)
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
        만약 (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        break;
    }
    만약 (mime_type) {
        size_t len = SDL_strlen(mime_type) + 1;
        만약 (name) {
            SDL_memcpy(name, mime_type, len);
        }
        반환 (정수)len;
    }
    반환 0;
}

static char **GetMimeTypes(정수 *pnformats)
{
    char **new_mime_types = NULL;

    *pnformats = 0;

    만약 (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        정수 nformats = 0;
        UINT format = 0;
        정수 formatsSz = 0;
        bool have_image_bmp = false;
        위해 ( ; ; ) {
            format = EnumClipboardFormats(format);
            만약 (!format) {
                break;
            }

#ifdef DEBUG_CLIPBOARD
            char name[128] = { 0 };
            GetClipboardFormatNameA(format, name, sizeof(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#endif

            만약 (format == CF_DIB || format == CF_DIBV5) {
                만약 (have_image_bmp) {
                    // We have already registered this format
                    continue;
                }
                have_image_bmp = true;
            }

            정수 len = GetClipboardFormatMimeType(format, NULL);
            만약 (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_AllocateTemporaryMemory((nformats + 1) * sizeof(char *) + formatsSz);
        만약 (new_mime_types) {
            format = 0;
            char *strPtr = (char *)(new_mime_types + nformats + 1);
            정수 i = 0;
            위해 ( ; ; ) {
                format = EnumClipboardFormats(format);
                만약 (!format) {
                    break;
                }

                만약 (format == CF_DIB || format == CF_DIBV5) {
                    만약 (have_image_bmp) {
                        // We have already registered this format
                        continue;
                    }
                    have_image_bmp = true;
                }

                정수 len = GetClipboardFormatMimeType(format, strPtr);
                만약 (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = NULL;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    반환 new_mime_types;
}

void WIN_CheckClipboardUpdate(struct SDL_VideoData *data)
{
    DWORD count = GetClipboardSequenceNumber();
    만약 (count != data->clipboard_count) {
        만약 (count) {
            정수 nformats = 0;
            char **new_mime_types = GetMimeTypes(&nformats);
            만약 (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        data->clipboard_count = count;
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
