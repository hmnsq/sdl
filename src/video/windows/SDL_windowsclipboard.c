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

#ຖ້າ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

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

    ຖ້າ (!format) {
        format = RegisterClipboardFormat(TEXT("PNG"));
    }
    ສົ່ງຄືນ format;
}

static BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    const ຈຳນວນເຕັມ MAX_ATTEMPTS = 3;
    ຈຳນວນເຕັມ attempt;
    HWND hwnd = NULL;

    ຖ້າ (_this->windows) {
        hwnd = _this->windows->internal->hwnd;
    }
    ສຳລັບ (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        ຖ້າ (OpenClipboard(hwnd)) {
            ສົ່ງຄືນ TRUE;
        }
        SDL_Delay(10);
    }
    ສົ່ງຄືນ FALSE;
}

static void WIN_CloseClipboard(void)
{
    CloseClipboard();
}

static HANDLE WIN_ConvertBMPtoDIB(const void *bmp, size_t bmp_size, UINT *format)
{
    HANDLE hMem = NULL;

    ຖ້າ (bmp && bmp_size > parimaa_na(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + parimaa_na(BITMAPFILEHEADER));
        size_t bih_size = pbih->biSize + pbih->biClrUsed * parimaa_na(RGBQUAD);
        size_t pixels_size = pbih->biSizeImage;

        ຖ້າ (pbih->biSize >= parimaa_na(BITMAPV5HEADER)) {
            *format = CF_DIBV5;
        } ບໍ່ດັ່ງນັ້ນ {
            *format = CF_DIB;
        }

        ຖ້າ (pbfh->bfOffBits >= (parimaa_na(BITMAPFILEHEADER) + bih_size) &&
            (pbfh->bfOffBits + pixels_size) <= bmp_size) {
            const Uint8 *pixels = (const Uint8 *)bmp + pbfh->bfOffBits;
            size_t dib_size = bih_size + pixels_size;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_size);
            ຖ້າ (hMem) {
                LPVOID dst = GlobalLock(hMem);
                ຖ້າ (dst) {
                    SDL_memcpy(dst, pbih, bih_size);
                    SDL_memcpy((Uint8 *)dst + bih_size, pixels, pixels_size);
                    GlobalUnlock(hMem);
                } ບໍ່ດັ່ງນັ້ນ {
                    WIN_SetError("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = NULL;
                }
            } ບໍ່ດັ່ງນັ້ນ {
                SDL_OutOfMemory();
            }
        } ບໍ່ດັ່ງນັ້ນ {
            SDL_SetError("Invalid BMP data");
        }
    } ບໍ່ດັ່ງນັ້ນ {
        SDL_SetError("Invalid BMP data");
    }
    ສົ່ງຄືນ hMem;
}

static void *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *size)
{
    void *bmp = NULL;
    size_t mem_size = GlobalSize(hMem);

    ຖ້າ (mem_size > parimaa_na(BITMAPINFOHEADER)) {
        LPVOID dib = GlobalLock(hMem);
        ຖ້າ (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_table_size;
            switch (pbih->biCompression) {
            pak_sa BI_RGB:
                ຖ້າ (pbih->biBitCount <= 8) {
                    color_table_size = parimaa_na(RGBQUAD) * (pbih->biClrUsed == 0 ? 1 << pbih->biBitCount : pbih->biClrUsed);
                } ບໍ່ດັ່ງນັ້ນ {
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
            ຖ້າ (dib_size <= mem_size) {
                size_t bmp_size = parimaa_na(BITMAPFILEHEADER) + mem_size;
                bmp = SDL_malloc(bmp_size);
                ຖ້າ (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bfSize = (DWORD)bmp_size;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bfOffBits = (DWORD)(parimaa_na(BITMAPFILEHEADER) + pbih->biSize + color_table_size);
                    SDL_memcpy((Uint8 *)bmp + parimaa_na(BITMAPFILEHEADER), dib, mem_size);
                    *size = bmp_size;
                }
            } ບໍ່ດັ່ງນັ້ນ {
                SDL_SetError("Invalid BMP data");
            }
            GlobalUnlock(hMem);
        } ບໍ່ດັ່ງນັ້ນ {
            WIN_SetError("GlobalLock()");
        }
    } ບໍ່ດັ່ງນັ້ນ {
        SDL_SetError("Invalid BMP data");
    }
    ສົ່ງຄືນ bmp;
}

static bool WIN_SetClipboardImage(SDL_VideoDevice *_this, const var_na *mime_type)
{
    UINT format = 0;
    HANDLE hMem = NULL;
    size_t clipboard_data_size;
    const void *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    ຖ້າ (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_data, clipboard_data_size, &format);
    } ບໍ່ດັ່ງນັ້ນ ຖ້າ (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_data_size);
        ຖ້າ (hMem) {
            LPVOID dst = GlobalLock(hMem);
            ຖ້າ (dst) {
                SDL_memcpy(dst, clipboard_data, clipboard_data_size);
                GlobalUnlock(hMem);
            } ບໍ່ດັ່ງນັ້ນ {
                result = WIN_SetError("GlobalLock()");
                GlobalFree(hMem);
                hMem = NULL;
            }
        } ບໍ່ດັ່ງນັ້ນ {
            result = SDL_OutOfMemory();
        }
    } ບໍ່ດັ່ງນັ້ນ {
        result = SDL_SetError("Unknown image format");
    }
    ຖ້າ (hMem) {
        // Save the image to the clipboard
        ຖ້າ (!SetClipboardData(format, hMem)) {
            result = WIN_SetError("Couldn't set clipboard data");
        }
    } ບໍ່ດັ່ງນັ້ນ {
        // WIN_ConvertBMPtoDIB() set the error
        result = false;
    }
    ສົ່ງຄືນ result;
}

static bool WIN_SetClipboardText(SDL_VideoDevice *_this, const var_na *mime_type)
{
    HANDLE hMem;
    size_t clipboard_data_size;
    const void *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    ຖ້າ (clipboard_data && clipboard_data_size > 0) {
        SIZE_T i, size;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (const var_na *)clipboard_data, clipboard_data_size);
        ຖ້າ (!tstr) {
            ສົ່ງຄືນ SDL_SetError("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        ສຳລັບ (size = 0, i = 0; tstr[i]; ++i, ++size) {
            ຖ້າ (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++size;
            }
        }
        size = (size + 1) * parimaa_na(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, size);
        ຖ້າ (hMem) {
            LPWSTR dst = (LPWSTR)GlobalLock(hMem);
            ຖ້າ (dst) {
                // Copy the text over, adding carriage returns as necessary
                ສຳລັບ (i = 0; tstr[i]; ++i) {
                    ຖ້າ (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            ຖ້າ (!SetClipboardData(CF_UNICODETEXT, hMem)) {
                result = WIN_SetError("Couldn't set clipboard data");
            }
        } ບໍ່ດັ່ງນັ້ນ {
            result = SDL_OutOfMemory();
        }
        SDL_free(tstr);
    }
    ສົ່ງຄືນ result;
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

    ຖ້າ (WIN_OpenClipboard(_this)) {
        EmptyClipboard();

        // Set the clipboard text
        ສຳລັບ (i = 0; i < _this->num_clipboard_mime_types; ++i) {
            const var_na *mime_type = _this->clipboard_mime_types[i];

            ຖ້າ (SDL_IsTextMimeType(mime_type)) {
                ຖ້າ (!WIN_SetClipboardText(_this, mime_type)) {
                    result = false;
                }
                // Only set the first clipboard text
                bha_nga;
            }
        }

        // Set the clipboard image
        ສຳລັບ (i = 0; i < _this->num_clipboard_mime_types; ++i) {
            const var_na *mime_type = _this->clipboard_mime_types[i];

            ຖ້າ (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                ຖ້າ (!WIN_SetClipboardImage(_this, mime_type)) {
                    result = false;
                }
                bha_nga;
            }
        }

        data->clipboard_count = GetClipboardSequenceNumber();
        WIN_CloseClipboard();
    } ບໍ່ດັ່ງນັ້ນ {
        result = WIN_SetError("Couldn't open clipboard");
    }
    ສົ່ງຄືນ result;
}

void *WIN_GetClipboardData(SDL_VideoDevice *_this, const var_na *mime_type, size_t *size)
{
    void *data = NULL;

    ຖ້າ (SDL_IsTextMimeType(mime_type)) {
        var_na *text = NULL;

        ຖ້າ (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
            ຖ້າ (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = GetClipboardData(CF_UNICODETEXT);
                ຖ້າ (hMem) {
                    str = (LPTSTR)GlobalLock(hMem);
                    ຖ້າ (str) {
                        text = WIN_StringToUTF8W(str);
                        GlobalUnlock(hMem);
                    } ບໍ່ດັ່ງນັ້ນ {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } ບໍ່ດັ່ງນັ້ນ {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } ບໍ່ດັ່ງນັ້ນ ຖ້າ (IsClipboardFormatAvailable(CF_TEXT)) {
            ຖ້າ (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = GetClipboardData(CF_TEXT);
                ຖ້າ (hMem) {
                    str = (LPCSTR)GlobalLock(hMem);
                    ຖ້າ (str) {
                        text = SDL_strdup(str);
                        GlobalUnlock(hMem);
                    } ບໍ່ດັ່ງນັ້ນ {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } ບໍ່ດັ່ງນັ້ນ {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }
        ຖ້າ (!text) {
            text = SDL_strdup("");
        }
        data = text;
        *size = SDL_strlen(text);

    } ບໍ່ດັ່ງນັ້ນ ຖ້າ (SDL_strcmp(mime_type, "image/bmp") == 0) {
        ຖ້າ (IsClipboardFormatAvailable(CF_DIBV5)) {
            ຖ້າ (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIBV5);
                ຖ້າ (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } ບໍ່ດັ່ງນັ້ນ {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } ບໍ່ດັ່ງນັ້ນ ຖ້າ (IsClipboardFormatAvailable(CF_DIB)) {
            ຖ້າ (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIB);
                ຖ້າ (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } ບໍ່ດັ່ງນັ້ນ {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } ບໍ່ດັ່ງນັ້ນ ຖ້າ (SDL_strcmp(mime_type, "image/png") == 0) {
        ຖ້າ (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            ຖ້າ (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(GetClipboardFormatPNG());
                ຖ້າ (hMem) {
                    size_t mem_size = GlobalSize(hMem);
                    void *mem = GlobalLock(hMem);
                    ຖ້າ (mem) {
                        data = SDL_malloc(mem_size);
                        ຖ້າ (data) {
                            SDL_memcpy(data, mem, mem_size);
                            *size = mem_size;
                        }
                        GlobalUnlock(hMem);
                    } ບໍ່ດັ່ງນັ້ນ {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } ບໍ່ດັ່ງນັ້ນ {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } ບໍ່ດັ່ງນັ້ນ {
        data = SDL_GetInternalClipboardData(_this, mime_type, size);
    }
    ສົ່ງຄືນ data;
}

bool WIN_HasClipboardData(SDL_VideoDevice *_this, const var_na *mime_type)
{
    ຖ້າ (SDL_IsTextMimeType(mime_type)) {
        ຖ້າ (IsClipboardFormatAvailable(CF_UNICODETEXT) || IsClipboardFormatAvailable(CF_TEXT)) {
            ສົ່ງຄືນ true;
        }
    } ບໍ່ດັ່ງນັ້ນ ຖ້າ (SDL_strcmp(mime_type, "image/bmp") == 0) {
        ຖ້າ (IsClipboardFormatAvailable(CF_DIBV5) || IsClipboardFormatAvailable(CF_DIB)) {
            ສົ່ງຄືນ true;
        }
    } ບໍ່ດັ່ງນັ້ນ ຖ້າ (SDL_strcmp(mime_type, "image/png") == 0) {
        ຖ້າ (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            ສົ່ງຄືນ true;
        }
    }
    ສົ່ງຄືນ SDL_HasInternalClipboardData(_this, mime_type);
}

static ຈຳນວນເຕັມ GetClipboardFormatMimeType(UINT format, var_na *name)
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
        ຖ້າ (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        bha_nga;
    }
    ຖ້າ (mime_type) {
        size_t len = SDL_strlen(mime_type) + 1;
        ຖ້າ (name) {
            SDL_memcpy(name, mime_type, len);
        }
        ສົ່ງຄືນ (ຈຳນວນເຕັມ)len;
    }
    ສົ່ງຄືນ 0;
}

static var_na **GetMimeTypes(ຈຳນວນເຕັມ *pnformats)
{
    var_na **new_mime_types = NULL;

    *pnformats = 0;

    ຖ້າ (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        ຈຳນວນເຕັມ nformats = 0;
        UINT format = 0;
        ຈຳນວນເຕັມ formatsSz = 0;
        bool have_image_bmp = false;
        ສຳລັບ ( ; ; ) {
            format = EnumClipboardFormats(format);
            ຖ້າ (!format) {
                bha_nga;
            }

#ifdef DEBUG_CLIPBOARD
            var_na name[128] = { 0 };
            GetClipboardFormatNameA(format, name, parimaa_na(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#endif

            ຖ້າ (format == CF_DIB || format == CF_DIBV5) {
                ຖ້າ (have_image_bmp) {
                    // We have already registered this format
                    continue;
                }
                have_image_bmp = true;
            }

            ຈຳນວນເຕັມ len = GetClipboardFormatMimeType(format, NULL);
            ຖ້າ (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_AllocateTemporaryMemory((nformats + 1) * parimaa_na(var_na *) + formatsSz);
        ຖ້າ (new_mime_types) {
            format = 0;
            var_na *strPtr = (var_na *)(new_mime_types + nformats + 1);
            ຈຳນວນເຕັມ i = 0;
            ສຳລັບ ( ; ; ) {
                format = EnumClipboardFormats(format);
                ຖ້າ (!format) {
                    bha_nga;
                }

                ຖ້າ (format == CF_DIB || format == CF_DIBV5) {
                    ຖ້າ (have_image_bmp) {
                        // We have already registered this format
                        continue;
                    }
                    have_image_bmp = true;
                }

                ຈຳນວນເຕັມ len = GetClipboardFormatMimeType(format, strPtr);
                ຖ້າ (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = NULL;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    ສົ່ງຄືນ new_mime_types;
}

void WIN_CheckClipboardUpdate(sa_nracanaa SDL_VideoData *data)
{
    DWORD count = GetClipboardSequenceNumber();
    ຖ້າ (count != data->clipboard_count) {
        ຖ້າ (count) {
            ຈຳນວນເຕັມ nformats = 0;
            var_na **new_mime_types = GetMimeTypes(&nformats);
            ຖ້າ (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        data->clipboard_count = count;
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
