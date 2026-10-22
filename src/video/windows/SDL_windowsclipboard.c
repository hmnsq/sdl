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

#如果 defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

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

    如果 (!format) {
        format = RegisterClipboardFormat(TEXT("PNG"));
    }
    返回 format;
}

static BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    const 整数 MAX_ATTEMPTS = 3;
    整数 attempt;
    HWND hwnd = NULL;

    如果 (_this->windows) {
        hwnd = _this->windows->internal->hwnd;
    }
    为 (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        如果 (OpenClipboard(hwnd)) {
            返回 TRUE;
        }
        SDL_Delay(10);
    }
    返回 FALSE;
}

static void WIN_CloseClipboard(void)
{
    CloseClipboard();
}

static HANDLE WIN_ConvertBMPtoDIB(const void *bmp, size_t bmp_size, UINT *format)
{
    HANDLE hMem = NULL;

    如果 (bmp && bmp_size > sizeof(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + sizeof(BITMAPFILEHEADER));
        size_t bih_size = pbih->biSize + pbih->biClrUsed * sizeof(RGBQUAD);
        size_t pixels_size = pbih->biSizeImage;

        如果 (pbih->biSize >= sizeof(BITMAPV5HEADER)) {
            *format = CF_DIBV5;
        } 否则 {
            *format = CF_DIB;
        }

        如果 (pbfh->bfOffBits >= (sizeof(BITMAPFILEHEADER) + bih_size) &&
            (pbfh->bfOffBits + pixels_size) <= bmp_size) {
            const Uint8 *pixels = (const Uint8 *)bmp + pbfh->bfOffBits;
            size_t dib_size = bih_size + pixels_size;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_size);
            如果 (hMem) {
                LPVOID dst = GlobalLock(hMem);
                如果 (dst) {
                    SDL_memcpy(dst, pbih, bih_size);
                    SDL_memcpy((Uint8 *)dst + bih_size, pixels, pixels_size);
                    GlobalUnlock(hMem);
                } 否则 {
                    WIN_SetError("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = NULL;
                }
            } 否则 {
                SDL_OutOfMemory();
            }
        } 否则 {
            SDL_SetError("Invalid BMP data");
        }
    } 否则 {
        SDL_SetError("Invalid BMP data");
    }
    返回 hMem;
}

static void *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *size)
{
    void *bmp = NULL;
    size_t mem_size = GlobalSize(hMem);

    如果 (mem_size > sizeof(BITMAPINFOHEADER)) {
        LPVOID dib = GlobalLock(hMem);
        如果 (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_table_size;
            switch (pbih->biCompression) {
            case BI_RGB:
                如果 (pbih->biBitCount <= 8) {
                    color_table_size = sizeof(RGBQUAD) * (pbih->biClrUsed == 0 ? 1 << pbih->biBitCount : pbih->biClrUsed);
                } 否则 {
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
            如果 (dib_size <= mem_size) {
                size_t bmp_size = sizeof(BITMAPFILEHEADER) + mem_size;
                bmp = SDL_malloc(bmp_size);
                如果 (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bfSize = (DWORD)bmp_size;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bfOffBits = (DWORD)(sizeof(BITMAPFILEHEADER) + pbih->biSize + color_table_size);
                    SDL_memcpy((Uint8 *)bmp + sizeof(BITMAPFILEHEADER), dib, mem_size);
                    *size = bmp_size;
                }
            } 否则 {
                SDL_SetError("Invalid BMP data");
            }
            GlobalUnlock(hMem);
        } 否则 {
            WIN_SetError("GlobalLock()");
        }
    } 否则 {
        SDL_SetError("Invalid BMP data");
    }
    返回 bmp;
}

static bool WIN_SetClipboardImage(SDL_VideoDevice *_this, const char *mime_type)
{
    UINT format = 0;
    HANDLE hMem = NULL;
    size_t clipboard_data_size;
    const void *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    如果 (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_data, clipboard_data_size, &format);
    } 否则 如果 (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_data_size);
        如果 (hMem) {
            LPVOID dst = GlobalLock(hMem);
            如果 (dst) {
                SDL_memcpy(dst, clipboard_data, clipboard_data_size);
                GlobalUnlock(hMem);
            } 否则 {
                result = WIN_SetError("GlobalLock()");
                GlobalFree(hMem);
                hMem = NULL;
            }
        } 否则 {
            result = SDL_OutOfMemory();
        }
    } 否则 {
        result = SDL_SetError("Unknown image format");
    }
    如果 (hMem) {
        // Save the image to the clipboard
        如果 (!SetClipboardData(format, hMem)) {
            result = WIN_SetError("Couldn't set clipboard data");
        }
    } 否则 {
        // WIN_ConvertBMPtoDIB() set the error
        result = false;
    }
    返回 result;
}

static bool WIN_SetClipboardText(SDL_VideoDevice *_this, const char *mime_type)
{
    HANDLE hMem;
    size_t clipboard_data_size;
    const void *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    如果 (clipboard_data && clipboard_data_size > 0) {
        SIZE_T i, size;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (const char *)clipboard_data, clipboard_data_size);
        如果 (!tstr) {
            返回 SDL_SetError("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        为 (size = 0, i = 0; tstr[i]; ++i, ++size) {
            如果 (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++size;
            }
        }
        size = (size + 1) * sizeof(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, size);
        如果 (hMem) {
            LPWSTR dst = (LPWSTR)GlobalLock(hMem);
            如果 (dst) {
                // Copy the text over, adding carriage returns as necessary
                为 (i = 0; tstr[i]; ++i) {
                    如果 (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            如果 (!SetClipboardData(CF_UNICODETEXT, hMem)) {
                result = WIN_SetError("Couldn't set clipboard data");
            }
        } 否则 {
            result = SDL_OutOfMemory();
        }
        SDL_free(tstr);
    }
    返回 result;
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

    如果 (WIN_OpenClipboard(_this)) {
        EmptyClipboard();

        // Set the clipboard text
        为 (i = 0; i < _this->num_clipboard_mime_types; ++i) {
            const char *mime_type = _this->clipboard_mime_types[i];

            如果 (SDL_IsTextMimeType(mime_type)) {
                如果 (!WIN_SetClipboardText(_this, mime_type)) {
                    result = false;
                }
                // Only set the first clipboard text
                break;
            }
        }

        // Set the clipboard image
        为 (i = 0; i < _this->num_clipboard_mime_types; ++i) {
            const char *mime_type = _this->clipboard_mime_types[i];

            如果 (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                如果 (!WIN_SetClipboardImage(_this, mime_type)) {
                    result = false;
                }
                break;
            }
        }

        data->clipboard_count = GetClipboardSequenceNumber();
        WIN_CloseClipboard();
    } 否则 {
        result = WIN_SetError("Couldn't open clipboard");
    }
    返回 result;
}

void *WIN_GetClipboardData(SDL_VideoDevice *_this, const char *mime_type, size_t *size)
{
    void *data = NULL;

    如果 (SDL_IsTextMimeType(mime_type)) {
        char *text = NULL;

        如果 (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
            如果 (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = GetClipboardData(CF_UNICODETEXT);
                如果 (hMem) {
                    str = (LPTSTR)GlobalLock(hMem);
                    如果 (str) {
                        text = WIN_StringToUTF8W(str);
                        GlobalUnlock(hMem);
                    } 否则 {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } 否则 {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } 否则 如果 (IsClipboardFormatAvailable(CF_TEXT)) {
            如果 (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = GetClipboardData(CF_TEXT);
                如果 (hMem) {
                    str = (LPCSTR)GlobalLock(hMem);
                    如果 (str) {
                        text = SDL_strdup(str);
                        GlobalUnlock(hMem);
                    } 否则 {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } 否则 {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }
        如果 (!text) {
            text = SDL_strdup("");
        }
        data = text;
        *size = SDL_strlen(text);

    } 否则 如果 (SDL_strcmp(mime_type, "image/bmp") == 0) {
        如果 (IsClipboardFormatAvailable(CF_DIBV5)) {
            如果 (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIBV5);
                如果 (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } 否则 {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } 否则 如果 (IsClipboardFormatAvailable(CF_DIB)) {
            如果 (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIB);
                如果 (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } 否则 {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } 否则 如果 (SDL_strcmp(mime_type, "image/png") == 0) {
        如果 (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            如果 (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(GetClipboardFormatPNG());
                如果 (hMem) {
                    size_t mem_size = GlobalSize(hMem);
                    void *mem = GlobalLock(hMem);
                    如果 (mem) {
                        data = SDL_malloc(mem_size);
                        如果 (data) {
                            SDL_memcpy(data, mem, mem_size);
                            *size = mem_size;
                        }
                        GlobalUnlock(hMem);
                    } 否则 {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } 否则 {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } 否则 {
        data = SDL_GetInternalClipboardData(_this, mime_type, size);
    }
    返回 data;
}

bool WIN_HasClipboardData(SDL_VideoDevice *_this, const char *mime_type)
{
    如果 (SDL_IsTextMimeType(mime_type)) {
        如果 (IsClipboardFormatAvailable(CF_UNICODETEXT) || IsClipboardFormatAvailable(CF_TEXT)) {
            返回 true;
        }
    } 否则 如果 (SDL_strcmp(mime_type, "image/bmp") == 0) {
        如果 (IsClipboardFormatAvailable(CF_DIBV5) || IsClipboardFormatAvailable(CF_DIB)) {
            返回 true;
        }
    } 否则 如果 (SDL_strcmp(mime_type, "image/png") == 0) {
        如果 (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            返回 true;
        }
    }
    返回 SDL_HasInternalClipboardData(_this, mime_type);
}

static 整数 GetClipboardFormatMimeType(UINT format, char *name)
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
        如果 (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        break;
    }
    如果 (mime_type) {
        size_t len = SDL_strlen(mime_type) + 1;
        如果 (name) {
            SDL_memcpy(name, mime_type, len);
        }
        返回 (整数)len;
    }
    返回 0;
}

static char **GetMimeTypes(整数 *pnformats)
{
    char **new_mime_types = NULL;

    *pnformats = 0;

    如果 (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        整数 nformats = 0;
        UINT format = 0;
        整数 formatsSz = 0;
        bool have_image_bmp = false;
        为 ( ; ; ) {
            format = EnumClipboardFormats(format);
            如果 (!format) {
                break;
            }

#ifdef DEBUG_CLIPBOARD
            char name[128] = { 0 };
            GetClipboardFormatNameA(format, name, sizeof(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#endif

            如果 (format == CF_DIB || format == CF_DIBV5) {
                如果 (have_image_bmp) {
                    // We have already registered this format
                    continue;
                }
                have_image_bmp = true;
            }

            整数 len = GetClipboardFormatMimeType(format, NULL);
            如果 (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_AllocateTemporaryMemory((nformats + 1) * sizeof(char *) + formatsSz);
        如果 (new_mime_types) {
            format = 0;
            char *strPtr = (char *)(new_mime_types + nformats + 1);
            整数 i = 0;
            为 ( ; ; ) {
                format = EnumClipboardFormats(format);
                如果 (!format) {
                    break;
                }

                如果 (format == CF_DIB || format == CF_DIBV5) {
                    如果 (have_image_bmp) {
                        // We have already registered this format
                        continue;
                    }
                    have_image_bmp = true;
                }

                整数 len = GetClipboardFormatMimeType(format, strPtr);
                如果 (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = NULL;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    返回 new_mime_types;
}

void WIN_CheckClipboardUpdate(struct SDL_VideoData *data)
{
    DWORD count = GetClipboardSequenceNumber();
    如果 (count != data->clipboard_count) {
        如果 (count) {
            整数 nformats = 0;
            char **new_mime_types = GetMimeTypes(&nformats);
            如果 (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        data->clipboard_count = count;
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
