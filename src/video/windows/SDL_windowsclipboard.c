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
#অন্তর্ভাব "SDL_internal.h"

#যদি defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#অন্তর্ভাব "SDL_windowsvideo.h"
#অন্তর্ভাব "SDL_windowswindow.h"
#অন্তর্ভাব "../SDL_clipboard_c.h"
#অন্তর্ভাব "../../events/SDL_events_c.h"
#অন্তর্ভাব "../../events/SDL_clipboardevents_c.h"

#define BFT_BITMAP 0x4d42 // 'BM'

// Assume we can directly read and write BMP fields without byte swapping
SDL_COMPILE_TIME_ASSERT(verify_byte_order, SDL_BYTEORDER == SDL_LIL_ENDIAN);

স্থির UINT GetClipboardFormatPNG(শূন্য)
{
    স্থির UINT format;

    যদি (!format) {
        format = RegisterClipboardFormat(TEXT("PNG"));
    }
    প্রত্যাগম format;
}

স্থির BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    ধ্রুব পূর্ণাঙ্ক MAX_ATTEMPTS = 3;
    পূর্ণাঙ্ক attempt;
    HWND hwnd = রিক্ত;

    যদি (_this->windows) {
        hwnd = _this->windows->internal->hwnd;
    }
    প্রতি (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        যদি (OpenClipboard(hwnd)) {
            প্রত্যাগম TRUE;
        }
        SDL_Delay(10);
    }
    প্রত্যাগম FALSE;
}

স্থির শূন্য WIN_CloseClipboard(শূন্য)
{
    CloseClipboard();
}

স্থির HANDLE WIN_ConvertBMPtoDIB(ধ্রুব শূন্য *bmp, size_t bmp_size, UINT *format)
{
    HANDLE hMem = রিক্ত;

    যদি (bmp && bmp_size > পরিমাণ(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + পরিমাণ(BITMAPFILEHEADER));
        size_t bih_size = pbih->biSize + pbih->biClrUsed * পরিমাণ(RGBQUAD);
        size_t pixels_size = pbih->biSizeImage;

        যদি (pbih->biSize >= পরিমাণ(BITMAPV5HEADER)) {
            *format = CF_DIBV5;
        } অন্যথা {
            *format = CF_DIB;
        }

        যদি (pbfh->bfOffBits >= (পরিমাণ(BITMAPFILEHEADER) + bih_size) &&
            (pbfh->bfOffBits + pixels_size) <= bmp_size) {
            ধ্রুব Uint8 *pixels = (ধ্রুব Uint8 *)bmp + pbfh->bfOffBits;
            size_t dib_size = bih_size + pixels_size;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_size);
            যদি (hMem) {
                LPVOID dst = GlobalLock(hMem);
                যদি (dst) {
                    SDL_memcpy(dst, pbih, bih_size);
                    SDL_memcpy((Uint8 *)dst + bih_size, pixels, pixels_size);
                    GlobalUnlock(hMem);
                } অন্যথা {
                    WIN_SetError("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = রিক্ত;
                }
            } অন্যথা {
                SDL_OutOfMemory();
            }
        } অন্যথা {
            SDL_SetError("Invalid BMP data");
        }
    } অন্যথা {
        SDL_SetError("Invalid BMP data");
    }
    প্রত্যাগম hMem;
}

স্থির শূন্য *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *size)
{
    শূন্য *bmp = রিক্ত;
    size_t mem_size = GlobalSize(hMem);

    যদি (mem_size > পরিমাণ(BITMAPINFOHEADER)) {
        LPVOID dib = GlobalLock(hMem);
        যদি (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_table_size;
            বিকল্প (pbih->biCompression) {
            পক্ষ BI_RGB:
                যদি (pbih->bi_Bit_গুনতি <= 8) {
                    color_table_size = পরিমাণ(RGBQUAD) * (pbih->biClrUsed == 0 ? 1 << pbih->bi_Bit_গুনতি : pbih->biClrUsed);
                } অন্যথা {
                    color_table_size = 0;
                }
                ভঙ্গ;
            পক্ষ BI_BITFIELDS:
                color_table_size = 3 * পরিমাণ(DWORD);
                ভঙ্গ;
            পক্ষ 6 /* BI_ALPHABITFIELDS */:
                // https://learn.microsoft.com/en-us/previous-versions/windows/embedded/aa452885(v=msdn.10)
                color_table_size = 4 * পরিমাণ(DWORD);
                ভঙ্গ;
            স্বভাব: // FOURCC
                color_table_size = পরিমাণ(RGBQUAD) * pbih->biClrUsed;
            }

            size_t bih_size = pbih->biSize + color_table_size;
            size_t dib_size = bih_size + pbih->biSizeImage;
            যদি (dib_size <= mem_size) {
                size_t bmp_size = পরিমাণ(BITMAPFILEHEADER) + mem_size;
                bmp = SDL_malloc(bmp_size);
                যদি (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bfSize = (DWORD)bmp_size;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bfOffBits = (DWORD)(পরিমাণ(BITMAPFILEHEADER) + pbih->biSize + color_table_size);
                    SDL_memcpy((Uint8 *)bmp + পরিমাণ(BITMAPFILEHEADER), dib, mem_size);
                    *size = bmp_size;
                }
            } অন্যথা {
                SDL_SetError("Invalid BMP data");
            }
            GlobalUnlock(hMem);
        } অন্যথা {
            WIN_SetError("GlobalLock()");
        }
    } অন্যথা {
        SDL_SetError("Invalid BMP data");
    }
    প্রত্যাগম bmp;
}

স্থির bool WIN_SetClipboardImage(SDL_VideoDevice *_this, ধ্রুব বর্ণ *mime_type)
{
    UINT format = 0;
    HANDLE hMem = রিক্ত;
    size_t clipboard_data_size;
    ধ্রুব শূন্য *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    যদি (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_data, clipboard_data_size, &format);
    } অন্যথা যদি (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_data_size);
        যদি (hMem) {
            LPVOID dst = GlobalLock(hMem);
            যদি (dst) {
                SDL_memcpy(dst, clipboard_data, clipboard_data_size);
                GlobalUnlock(hMem);
            } অন্যথা {
                result = WIN_SetError("GlobalLock()");
                GlobalFree(hMem);
                hMem = রিক্ত;
            }
        } অন্যথা {
            result = SDL_OutOfMemory();
        }
    } অন্যথা {
        result = SDL_SetError("Unknown image format");
    }
    যদি (hMem) {
        // Save the image to the clipboard
        যদি (!SetClipboardData(format, hMem)) {
            result = WIN_SetError("Couldn't set clipboard data");
        }
    } অন্যথা {
        // WIN_ConvertBMPtoDIB() set the error
        result = false;
    }
    প্রত্যাগম result;
}

স্থির bool WIN_SetClipboardText(SDL_VideoDevice *_this, ধ্রুব বর্ণ *mime_type)
{
    HANDLE hMem;
    size_t clipboard_data_size;
    ধ্রুব শূন্য *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    যদি (clipboard_data && clipboard_data_size > 0) {
        SIZE_T i, size;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (ধ্রুব বর্ণ *)clipboard_data, clipboard_data_size);
        যদি (!tstr) {
            প্রত্যাগম SDL_SetError("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        প্রতি (size = 0, i = 0; tstr[i]; ++i, ++size) {
            যদি (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++size;
            }
        }
        size = (size + 1) * পরিমাণ(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, size);
        যদি (hMem) {
            LPWSTR dst = (LPWSTR)GlobalLock(hMem);
            যদি (dst) {
                // Copy the text over, adding carriage returns as necessary
                প্রতি (i = 0; tstr[i]; ++i) {
                    যদি (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            যদি (!SetClipboardData(CF_UNICODETEXT, hMem)) {
                result = WIN_SetError("Couldn't set clipboard data");
            }
        } অন্যথা {
            result = SDL_OutOfMemory();
        }
        SDL_free(tstr);
    }
    প্রত্যাগম result;
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

    যদি (WIN_OpenClipboard(_this)) {
        EmptyClipboard();

        // Set the clipboard text
        প্রতি (i = 0; i < _this->অঙ্ক_clipboard_mime_types; ++i) {
            ধ্রুব বর্ণ *mime_type = _this->clipboard_mime_types[i];

            যদি (SDL_IsTextMimeType(mime_type)) {
                যদি (!WIN_SetClipboardText(_this, mime_type)) {
                    result = false;
                }
                // Only set the first clipboard text
                ভঙ্গ;
            }
        }

        // Set the clipboard image
        প্রতি (i = 0; i < _this->অঙ্ক_clipboard_mime_types; ++i) {
            ধ্রুব বর্ণ *mime_type = _this->clipboard_mime_types[i];

            যদি (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                যদি (!WIN_SetClipboardImage(_this, mime_type)) {
                    result = false;
                }
                ভঙ্গ;
            }
        }

        data->clipboard_গুনতি = Get_Clipboard_Sequence_সংখ্যা();
        WIN_CloseClipboard();
    } অন্যথা {
        result = WIN_SetError("Couldn't open clipboard");
    }
    প্রত্যাগম result;
}

শূন্য *WIN_GetClipboardData(SDL_VideoDevice *_this, ধ্রুব বর্ণ *mime_type, size_t *size)
{
    শূন্য *data = রিক্ত;

    যদি (SDL_IsTextMimeType(mime_type)) {
        বর্ণ *text = রিক্ত;

        যদি (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
            যদি (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = GetClipboardData(CF_UNICODETEXT);
                যদি (hMem) {
                    str = (LPTSTR)GlobalLock(hMem);
                    যদি (str) {
                        text = WIN_StringToUTF8W(str);
                        GlobalUnlock(hMem);
                    } অন্যথা {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } অন্যথা {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } অন্যথা যদি (IsClipboardFormatAvailable(CF_TEXT)) {
            যদি (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = GetClipboardData(CF_TEXT);
                যদি (hMem) {
                    str = (LPCSTR)GlobalLock(hMem);
                    যদি (str) {
                        text = SDL_strdup(str);
                        GlobalUnlock(hMem);
                    } অন্যথা {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } অন্যথা {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }
        যদি (!text) {
            text = SDL_strdup("");
        }
        data = text;
        *size = SDL_strlen(text);

    } অন্যথা যদি (SDL_strcmp(mime_type, "image/bmp") == 0) {
        যদি (IsClipboardFormatAvailable(CF_DIBV5)) {
            যদি (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIBV5);
                যদি (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } অন্যথা {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } অন্যথা যদি (IsClipboardFormatAvailable(CF_DIB)) {
            যদি (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIB);
                যদি (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } অন্যথা {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } অন্যথা যদি (SDL_strcmp(mime_type, "image/png") == 0) {
        যদি (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            যদি (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(GetClipboardFormatPNG());
                যদি (hMem) {
                    size_t mem_size = GlobalSize(hMem);
                    শূন্য *mem = GlobalLock(hMem);
                    যদি (mem) {
                        data = SDL_malloc(mem_size);
                        যদি (data) {
                            SDL_memcpy(data, mem, mem_size);
                            *size = mem_size;
                        }
                        GlobalUnlock(hMem);
                    } অন্যথা {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } অন্যথা {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } অন্যথা {
        data = SDL_GetInternalClipboardData(_this, mime_type, size);
    }
    প্রত্যাগম data;
}

bool WIN_HasClipboardData(SDL_VideoDevice *_this, ধ্রুব বর্ণ *mime_type)
{
    যদি (SDL_IsTextMimeType(mime_type)) {
        যদি (IsClipboardFormatAvailable(CF_UNICODETEXT) || IsClipboardFormatAvailable(CF_TEXT)) {
            প্রত্যাগম true;
        }
    } অন্যথা যদি (SDL_strcmp(mime_type, "image/bmp") == 0) {
        যদি (IsClipboardFormatAvailable(CF_DIBV5) || IsClipboardFormatAvailable(CF_DIB)) {
            প্রত্যাগম true;
        }
    } অন্যথা যদি (SDL_strcmp(mime_type, "image/png") == 0) {
        যদি (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            প্রত্যাগম true;
        }
    }
    প্রত্যাগম SDL_HasInternalClipboardData(_this, mime_type);
}

স্থির পূর্ণাঙ্ক GetClipboardFormatMimeType(UINT format, বর্ণ *name)
{
    ধ্রুব বর্ণ *mime_type = রিক্ত;

    বিকল্প (format) {
    পক্ষ CF_TEXT:
        mime_type = "text/plain";
        ভঙ্গ;
    পক্ষ CF_UNICODETEXT:
        mime_type = "text/plain;charset=utf-8";
        ভঙ্গ;
    পক্ষ CF_DIB:
    পক্ষ CF_DIBV5:
        mime_type = "image/bmp";
        ভঙ্গ;
    স্বভাব:
        যদি (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        ভঙ্গ;
    }
    যদি (mime_type) {
        size_t len = SDL_strlen(mime_type) + 1;
        যদি (name) {
            SDL_memcpy(name, mime_type, len);
        }
        প্রত্যাগম (পূর্ণাঙ্ক)len;
    }
    প্রত্যাগম 0;
}

স্থির বর্ণ **GetMimeTypes(পূর্ণাঙ্ক *pnformats)
{
    বর্ণ **new_mime_types = রিক্ত;

    *pnformats = 0;

    যদি (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        পূর্ণাঙ্ক nformats = 0;
        UINT format = 0;
        পূর্ণাঙ্ক formatsSz = 0;
        bool have_image_bmp = false;
        প্রতি ( ; ; ) {
            format = EnumClipboardFormats(format);
            যদি (!format) {
                ভঙ্গ;
            }

#ifdef DEBUG_CLIPBOARD
            বর্ণ name[128] = { 0 };
            GetClipboardFormatNameA(format, name, পরিমাণ(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#endif

            যদি (format == CF_DIB || format == CF_DIBV5) {
                যদি (have_image_bmp) {
                    // We have already registered this format
                    অনুবর্ত;
                }
                have_image_bmp = true;
            }

            পূর্ণাঙ্ক len = GetClipboardFormatMimeType(format, রিক্ত);
            যদি (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_AllocateTemporaryMemory((nformats + 1) * পরিমাণ(বর্ণ *) + formatsSz);
        যদি (new_mime_types) {
            format = 0;
            বর্ণ *strPtr = (বর্ণ *)(new_mime_types + nformats + 1);
            পূর্ণাঙ্ক i = 0;
            প্রতি ( ; ; ) {
                format = EnumClipboardFormats(format);
                যদি (!format) {
                    ভঙ্গ;
                }

                যদি (format == CF_DIB || format == CF_DIBV5) {
                    যদি (have_image_bmp) {
                        // We have already registered this format
                        অনুবর্ত;
                    }
                    have_image_bmp = true;
                }

                পূর্ণাঙ্ক len = GetClipboardFormatMimeType(format, strPtr);
                যদি (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = রিক্ত;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    প্রত্যাগম new_mime_types;
}

শূন্য WIN_CheckClipboardUpdate(সংরচনা SDL_VideoData *data)
{
    DWORD গুনতি = Get_Clipboard_Sequence_সংখ্যা();
    যদি (গুনতি != data->clipboard_গুনতি) {
        যদি (গুনতি) {
            পূর্ণাঙ্ক nformats = 0;
            বর্ণ **new_mime_types = GetMimeTypes(&nformats);
            যদি (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        data->clipboard_গুনতি = গুনতি;
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
