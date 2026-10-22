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

#если defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

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

    если (!format) {
        format = RegisterClipboardFormat(TEXT("PNG"));
    }
    вернуть format;
}

static BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    const целое MAX_ATTEMPTS = 3;
    целое attempt;
    HWND hwnd = NULL;

    если (_this->windows) {
        hwnd = _this->windows->internal->hwnd;
    }
    для (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        если (OpenClipboard(hwnd)) {
            вернуть TRUE;
        }
        SDL_Delay(10);
    }
    вернуть FALSE;
}

static void WIN_CloseClipboard(void)
{
    CloseClipboard();
}

static HANDLE WIN_ConvertBMPtoDIB(const void *bmp, size_t bmp_size, UINT *format)
{
    HANDLE hMem = NULL;

    если (bmp && bmp_size > sizeof(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + sizeof(BITMAPFILEHEADER));
        size_t bih_size = pbih->biSize + pbih->biClrUsed * sizeof(RGBQUAD);
        size_t pixels_size = pbih->biSizeImage;

        если (pbih->biSize >= sizeof(BITMAPV5HEADER)) {
            *format = CF_DIBV5;
        } иначе {
            *format = CF_DIB;
        }

        если (pbfh->bfOffBits >= (sizeof(BITMAPFILEHEADER) + bih_size) &&
            (pbfh->bfOffBits + pixels_size) <= bmp_size) {
            const Uint8 *pixels = (const Uint8 *)bmp + pbfh->bfOffBits;
            size_t dib_size = bih_size + pixels_size;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_size);
            если (hMem) {
                LPVOID dst = GlobalLock(hMem);
                если (dst) {
                    SDL_memcpy(dst, pbih, bih_size);
                    SDL_memcpy((Uint8 *)dst + bih_size, pixels, pixels_size);
                    GlobalUnlock(hMem);
                } иначе {
                    WIN_SetError("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = NULL;
                }
            } иначе {
                SDL_OutOfMemory();
            }
        } иначе {
            SDL_SetError("Invalid BMP data");
        }
    } иначе {
        SDL_SetError("Invalid BMP data");
    }
    вернуть hMem;
}

static void *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *size)
{
    void *bmp = NULL;
    size_t mem_size = GlobalSize(hMem);

    если (mem_size > sizeof(BITMAPINFOHEADER)) {
        LPVOID dib = GlobalLock(hMem);
        если (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_table_size;
            switch (pbih->biCompression) {
            case BI_RGB:
                если (pbih->biBitCount <= 8) {
                    color_table_size = sizeof(RGBQUAD) * (pbih->biClrUsed == 0 ? 1 << pbih->biBitCount : pbih->biClrUsed);
                } иначе {
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
            если (dib_size <= mem_size) {
                size_t bmp_size = sizeof(BITMAPFILEHEADER) + mem_size;
                bmp = SDL_malloc(bmp_size);
                если (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bfSize = (DWORD)bmp_size;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bfOffBits = (DWORD)(sizeof(BITMAPFILEHEADER) + pbih->biSize + color_table_size);
                    SDL_memcpy((Uint8 *)bmp + sizeof(BITMAPFILEHEADER), dib, mem_size);
                    *size = bmp_size;
                }
            } иначе {
                SDL_SetError("Invalid BMP data");
            }
            GlobalUnlock(hMem);
        } иначе {
            WIN_SetError("GlobalLock()");
        }
    } иначе {
        SDL_SetError("Invalid BMP data");
    }
    вернуть bmp;
}

static bool WIN_SetClipboardImage(SDL_VideoDevice *_this, const char *mime_type)
{
    UINT format = 0;
    HANDLE hMem = NULL;
    size_t clipboard_data_size;
    const void *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    если (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_data, clipboard_data_size, &format);
    } иначе если (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_data_size);
        если (hMem) {
            LPVOID dst = GlobalLock(hMem);
            если (dst) {
                SDL_memcpy(dst, clipboard_data, clipboard_data_size);
                GlobalUnlock(hMem);
            } иначе {
                result = WIN_SetError("GlobalLock()");
                GlobalFree(hMem);
                hMem = NULL;
            }
        } иначе {
            result = SDL_OutOfMemory();
        }
    } иначе {
        result = SDL_SetError("Unknown image format");
    }
    если (hMem) {
        // Save the image to the clipboard
        если (!SetClipboardData(format, hMem)) {
            result = WIN_SetError("Couldn't set clipboard data");
        }
    } иначе {
        // WIN_ConvertBMPtoDIB() set the error
        result = false;
    }
    вернуть result;
}

static bool WIN_SetClipboardText(SDL_VideoDevice *_this, const char *mime_type)
{
    HANDLE hMem;
    size_t clipboard_data_size;
    const void *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    если (clipboard_data && clipboard_data_size > 0) {
        SIZE_T i, size;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (const char *)clipboard_data, clipboard_data_size);
        если (!tstr) {
            вернуть SDL_SetError("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        для (size = 0, i = 0; tstr[i]; ++i, ++size) {
            если (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++size;
            }
        }
        size = (size + 1) * sizeof(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, size);
        если (hMem) {
            LPWSTR dst = (LPWSTR)GlobalLock(hMem);
            если (dst) {
                // Copy the text over, adding carriage returns as necessary
                для (i = 0; tstr[i]; ++i) {
                    если (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            если (!SetClipboardData(CF_UNICODETEXT, hMem)) {
                result = WIN_SetError("Couldn't set clipboard data");
            }
        } иначе {
            result = SDL_OutOfMemory();
        }
        SDL_free(tstr);
    }
    вернуть result;
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

    если (WIN_OpenClipboard(_this)) {
        EmptyClipboard();

        // Set the clipboard text
        для (i = 0; i < _this->num_clipboard_mime_types; ++i) {
            const char *mime_type = _this->clipboard_mime_types[i];

            если (SDL_IsTextMimeType(mime_type)) {
                если (!WIN_SetClipboardText(_this, mime_type)) {
                    result = false;
                }
                // Only set the first clipboard text
                break;
            }
        }

        // Set the clipboard image
        для (i = 0; i < _this->num_clipboard_mime_types; ++i) {
            const char *mime_type = _this->clipboard_mime_types[i];

            если (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                если (!WIN_SetClipboardImage(_this, mime_type)) {
                    result = false;
                }
                break;
            }
        }

        data->clipboard_count = GetClipboardSequenceNumber();
        WIN_CloseClipboard();
    } иначе {
        result = WIN_SetError("Couldn't open clipboard");
    }
    вернуть result;
}

void *WIN_GetClipboardData(SDL_VideoDevice *_this, const char *mime_type, size_t *size)
{
    void *data = NULL;

    если (SDL_IsTextMimeType(mime_type)) {
        char *text = NULL;

        если (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
            если (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = GetClipboardData(CF_UNICODETEXT);
                если (hMem) {
                    str = (LPTSTR)GlobalLock(hMem);
                    если (str) {
                        text = WIN_StringToUTF8W(str);
                        GlobalUnlock(hMem);
                    } иначе {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } иначе {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } иначе если (IsClipboardFormatAvailable(CF_TEXT)) {
            если (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = GetClipboardData(CF_TEXT);
                если (hMem) {
                    str = (LPCSTR)GlobalLock(hMem);
                    если (str) {
                        text = SDL_strdup(str);
                        GlobalUnlock(hMem);
                    } иначе {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } иначе {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }
        если (!text) {
            text = SDL_strdup("");
        }
        data = text;
        *size = SDL_strlen(text);

    } иначе если (SDL_strcmp(mime_type, "image/bmp") == 0) {
        если (IsClipboardFormatAvailable(CF_DIBV5)) {
            если (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIBV5);
                если (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } иначе {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } иначе если (IsClipboardFormatAvailable(CF_DIB)) {
            если (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIB);
                если (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } иначе {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } иначе если (SDL_strcmp(mime_type, "image/png") == 0) {
        если (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            если (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(GetClipboardFormatPNG());
                если (hMem) {
                    size_t mem_size = GlobalSize(hMem);
                    void *mem = GlobalLock(hMem);
                    если (mem) {
                        data = SDL_malloc(mem_size);
                        если (data) {
                            SDL_memcpy(data, mem, mem_size);
                            *size = mem_size;
                        }
                        GlobalUnlock(hMem);
                    } иначе {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } иначе {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } иначе {
        data = SDL_GetInternalClipboardData(_this, mime_type, size);
    }
    вернуть data;
}

bool WIN_HasClipboardData(SDL_VideoDevice *_this, const char *mime_type)
{
    если (SDL_IsTextMimeType(mime_type)) {
        если (IsClipboardFormatAvailable(CF_UNICODETEXT) || IsClipboardFormatAvailable(CF_TEXT)) {
            вернуть true;
        }
    } иначе если (SDL_strcmp(mime_type, "image/bmp") == 0) {
        если (IsClipboardFormatAvailable(CF_DIBV5) || IsClipboardFormatAvailable(CF_DIB)) {
            вернуть true;
        }
    } иначе если (SDL_strcmp(mime_type, "image/png") == 0) {
        если (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            вернуть true;
        }
    }
    вернуть SDL_HasInternalClipboardData(_this, mime_type);
}

static целое GetClipboardFormatMimeType(UINT format, char *name)
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
        если (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        break;
    }
    если (mime_type) {
        size_t len = SDL_strlen(mime_type) + 1;
        если (name) {
            SDL_memcpy(name, mime_type, len);
        }
        вернуть (целое)len;
    }
    вернуть 0;
}

static char **GetMimeTypes(целое *pnformats)
{
    char **new_mime_types = NULL;

    *pnformats = 0;

    если (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        целое nformats = 0;
        UINT format = 0;
        целое formatsSz = 0;
        bool have_image_bmp = false;
        для ( ; ; ) {
            format = EnumClipboardFormats(format);
            если (!format) {
                break;
            }

#ifdef DEBUG_CLIPBOARD
            char name[128] = { 0 };
            GetClipboardFormatNameA(format, name, sizeof(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#endif

            если (format == CF_DIB || format == CF_DIBV5) {
                если (have_image_bmp) {
                    // We have already registered this format
                    continue;
                }
                have_image_bmp = true;
            }

            целое len = GetClipboardFormatMimeType(format, NULL);
            если (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_AllocateTemporaryMemory((nformats + 1) * sizeof(char *) + formatsSz);
        если (new_mime_types) {
            format = 0;
            char *strPtr = (char *)(new_mime_types + nformats + 1);
            целое i = 0;
            для ( ; ; ) {
                format = EnumClipboardFormats(format);
                если (!format) {
                    break;
                }

                если (format == CF_DIB || format == CF_DIBV5) {
                    если (have_image_bmp) {
                        // We have already registered this format
                        continue;
                    }
                    have_image_bmp = true;
                }

                целое len = GetClipboardFormatMimeType(format, strPtr);
                если (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = NULL;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    вернуть new_mime_types;
}

void WIN_CheckClipboardUpdate(struct SDL_VideoData *data)
{
    DWORD count = GetClipboardSequenceNumber();
    если (count != data->clipboard_count) {
        если (count) {
            целое nformats = 0;
            char **new_mime_types = GetMimeTypes(&nformats);
            если (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        data->clipboard_count = count;
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
