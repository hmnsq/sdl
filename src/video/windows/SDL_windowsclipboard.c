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

#もし defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

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

    もし (!format) {
        format = RegisterClipboardFormat(TEXT("PNG"));
    }
    戻る format;
}

static BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    const 整数 MAX_ATTEMPTS = 3;
    整数 attempt;
    HWND hwnd = NULL;

    もし (_this->windows) {
        hwnd = _this->windows->internal->hwnd;
    }
    ために (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        もし (OpenClipboard(hwnd)) {
            戻る TRUE;
        }
        SDL_Delay(10);
    }
    戻る FALSE;
}

static void WIN_CloseClipboard(void)
{
    CloseClipboard();
}

static HANDLE WIN_ConvertBMPtoDIB(const void *bmp, size_t bmp_size, UINT *format)
{
    HANDLE hMem = NULL;

    もし (bmp && bmp_size > sizeof(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + sizeof(BITMAPFILEHEADER));
        size_t bih_size = pbih->biSize + pbih->biClrUsed * sizeof(RGBQUAD);
        size_t pixels_size = pbih->biSizeImage;

        もし (pbih->biSize >= sizeof(BITMAPV5HEADER)) {
            *format = CF_DIBV5;
        } 否则 {
            *format = CF_DIB;
        }

        もし (pbfh->bfOffBits >= (sizeof(BITMAPFILEHEADER) + bih_size) &&
            (pbfh->bfOffBits + pixels_size) <= bmp_size) {
            const Uint8 *pixels = (const Uint8 *)bmp + pbfh->bfOffBits;
            size_t dib_size = bih_size + pixels_size;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_size);
            もし (hMem) {
                LPVOID dst = GlobalLock(hMem);
                もし (dst) {
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
    戻る hMem;
}

static void *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *size)
{
    void *bmp = NULL;
    size_t mem_size = GlobalSize(hMem);

    もし (mem_size > sizeof(BITMAPINFOHEADER)) {
        LPVOID dib = GlobalLock(hMem);
        もし (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_table_size;
            switch (pbih->biCompression) {
            case BI_RGB:
                もし (pbih->biBitCount <= 8) {
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
            もし (dib_size <= mem_size) {
                size_t bmp_size = sizeof(BITMAPFILEHEADER) + mem_size;
                bmp = SDL_malloc(bmp_size);
                もし (bmp) {
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
    戻る bmp;
}

static bool WIN_SetClipboardImage(SDL_VideoDevice *_this, const char *mime_type)
{
    UINT format = 0;
    HANDLE hMem = NULL;
    size_t clipboard_data_size;
    const void *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    もし (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_data, clipboard_data_size, &format);
    } 否则 もし (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_data_size);
        もし (hMem) {
            LPVOID dst = GlobalLock(hMem);
            もし (dst) {
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
    もし (hMem) {
        // Save the image to the clipboard
        もし (!SetClipboardData(format, hMem)) {
            result = WIN_SetError("Couldn't set clipboard data");
        }
    } 否则 {
        // WIN_ConvertBMPtoDIB() set the error
        result = false;
    }
    戻る result;
}

static bool WIN_SetClipboardText(SDL_VideoDevice *_this, const char *mime_type)
{
    HANDLE hMem;
    size_t clipboard_data_size;
    const void *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    もし (clipboard_data && clipboard_data_size > 0) {
        SIZE_T i, size;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (const char *)clipboard_data, clipboard_data_size);
        もし (!tstr) {
            戻る SDL_SetError("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        ために (size = 0, i = 0; tstr[i]; ++i, ++size) {
            もし (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++size;
            }
        }
        size = (size + 1) * sizeof(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, size);
        もし (hMem) {
            LPWSTR dst = (LPWSTR)GlobalLock(hMem);
            もし (dst) {
                // Copy the text over, adding carriage returns as necessary
                ために (i = 0; tstr[i]; ++i) {
                    もし (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            もし (!SetClipboardData(CF_UNICODETEXT, hMem)) {
                result = WIN_SetError("Couldn't set clipboard data");
            }
        } 否则 {
            result = SDL_OutOfMemory();
        }
        SDL_free(tstr);
    }
    戻る result;
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

    もし (WIN_OpenClipboard(_this)) {
        EmptyClipboard();

        // Set the clipboard text
        ために (i = 0; i < _this->num_clipboard_mime_types; ++i) {
            const char *mime_type = _this->clipboard_mime_types[i];

            もし (SDL_IsTextMimeType(mime_type)) {
                もし (!WIN_SetClipboardText(_this, mime_type)) {
                    result = false;
                }
                // Only set the first clipboard text
                break;
            }
        }

        // Set the clipboard image
        ために (i = 0; i < _this->num_clipboard_mime_types; ++i) {
            const char *mime_type = _this->clipboard_mime_types[i];

            もし (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                もし (!WIN_SetClipboardImage(_this, mime_type)) {
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
    戻る result;
}

void *WIN_GetClipboardData(SDL_VideoDevice *_this, const char *mime_type, size_t *size)
{
    void *data = NULL;

    もし (SDL_IsTextMimeType(mime_type)) {
        char *text = NULL;

        もし (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
            もし (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = GetClipboardData(CF_UNICODETEXT);
                もし (hMem) {
                    str = (LPTSTR)GlobalLock(hMem);
                    もし (str) {
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
        } 否则 もし (IsClipboardFormatAvailable(CF_TEXT)) {
            もし (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = GetClipboardData(CF_TEXT);
                もし (hMem) {
                    str = (LPCSTR)GlobalLock(hMem);
                    もし (str) {
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
        もし (!text) {
            text = SDL_strdup("");
        }
        data = text;
        *size = SDL_strlen(text);

    } 否则 もし (SDL_strcmp(mime_type, "image/bmp") == 0) {
        もし (IsClipboardFormatAvailable(CF_DIBV5)) {
            もし (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIBV5);
                もし (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } 否则 {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } 否则 もし (IsClipboardFormatAvailable(CF_DIB)) {
            もし (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIB);
                もし (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } 否则 {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } 否则 もし (SDL_strcmp(mime_type, "image/png") == 0) {
        もし (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            もし (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(GetClipboardFormatPNG());
                もし (hMem) {
                    size_t mem_size = GlobalSize(hMem);
                    void *mem = GlobalLock(hMem);
                    もし (mem) {
                        data = SDL_malloc(mem_size);
                        もし (data) {
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
    戻る data;
}

bool WIN_HasClipboardData(SDL_VideoDevice *_this, const char *mime_type)
{
    もし (SDL_IsTextMimeType(mime_type)) {
        もし (IsClipboardFormatAvailable(CF_UNICODETEXT) || IsClipboardFormatAvailable(CF_TEXT)) {
            戻る true;
        }
    } 否则 もし (SDL_strcmp(mime_type, "image/bmp") == 0) {
        もし (IsClipboardFormatAvailable(CF_DIBV5) || IsClipboardFormatAvailable(CF_DIB)) {
            戻る true;
        }
    } 否则 もし (SDL_strcmp(mime_type, "image/png") == 0) {
        もし (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            戻る true;
        }
    }
    戻る SDL_HasInternalClipboardData(_this, mime_type);
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
        もし (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        break;
    }
    もし (mime_type) {
        size_t len = SDL_strlen(mime_type) + 1;
        もし (name) {
            SDL_memcpy(name, mime_type, len);
        }
        戻る (整数)len;
    }
    戻る 0;
}

static char **GetMimeTypes(整数 *pnformats)
{
    char **new_mime_types = NULL;

    *pnformats = 0;

    もし (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        整数 nformats = 0;
        UINT format = 0;
        整数 formatsSz = 0;
        bool have_image_bmp = false;
        ために ( ; ; ) {
            format = EnumClipboardFormats(format);
            もし (!format) {
                break;
            }

#ifdef DEBUG_CLIPBOARD
            char name[128] = { 0 };
            GetClipboardFormatNameA(format, name, sizeof(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#endif

            もし (format == CF_DIB || format == CF_DIBV5) {
                もし (have_image_bmp) {
                    // We have already registered this format
                    continue;
                }
                have_image_bmp = true;
            }

            整数 len = GetClipboardFormatMimeType(format, NULL);
            もし (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_AllocateTemporaryMemory((nformats + 1) * sizeof(char *) + formatsSz);
        もし (new_mime_types) {
            format = 0;
            char *strPtr = (char *)(new_mime_types + nformats + 1);
            整数 i = 0;
            ために ( ; ; ) {
                format = EnumClipboardFormats(format);
                もし (!format) {
                    break;
                }

                もし (format == CF_DIB || format == CF_DIBV5) {
                    もし (have_image_bmp) {
                        // We have already registered this format
                        continue;
                    }
                    have_image_bmp = true;
                }

                整数 len = GetClipboardFormatMimeType(format, strPtr);
                もし (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = NULL;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    戻る new_mime_types;
}

void WIN_CheckClipboardUpdate(struct SDL_VideoData *data)
{
    DWORD count = GetClipboardSequenceNumber();
    もし (count != data->clipboard_count) {
        もし (count) {
            整数 nformats = 0;
            char **new_mime_types = GetMimeTypes(&nformats);
            もし (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        data->clipboard_count = count;
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
