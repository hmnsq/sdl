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
    ফেরত format;
}

স্থির BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    ধ্রুবক পূর্ণসংখ্যা MAX_ATTEMPTS = 3;
    পূর্ণসংখ্যা attempt;
    HWND hwnd = ফাঁকা;

    যদি (_this->windows) {
        hwnd = _this->windows->internal->hwnd;
    }
    জন্য (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        যদি (OpenClipboard(hwnd)) {
            ফেরত TRUE;
        }
        SDL_Delay(10);
    }
    ফেরত FALSE;
}

স্থির শূন্য WIN_CloseClipboard(শূন্য)
{
    CloseClipboard();
}

স্থির HANDLE WIN_ConvertBMPtoDIB(ধ্রুবক শূন্য *bmp, size_t bmp_আকার, UINT *format)
{
    HANDLE hMem = ফাঁকা;

    যদি (bmp && bmp_আকার > আকার(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + আকার(BITMAPFILEHEADER));
        size_t bih_আকার = pbih->bi_আকার + pbih->biClrUsed * আকার(RGBQUAD);
        size_t pixels_আকার = pbih->bi_আকার_Image;

        যদি (pbih->bi_আকার >= আকার(BITMAPV5HEADER)) {
            *format = CF_DIBV5;
        } অন্যথা {
            *format = CF_DIB;
        }

        যদি (pbfh->bfOffBits >= (আকার(BITMAPFILEHEADER) + bih_আকার) &&
            (pbfh->bfOffBits + pixels_আকার) <= bmp_আকার) {
            ধ্রুবক Uint8 *pixels = (ধ্রুবক Uint8 *)bmp + pbfh->bfOffBits;
            size_t dib_আকার = bih_আকার + pixels_আকার;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_আকার);
            যদি (hMem) {
                LPVOID dst = GlobalLock(hMem);
                যদি (dst) {
                    SDL_memcpy(dst, pbih, bih_আকার);
                    SDL_memcpy((Uint8 *)dst + bih_আকার, pixels, pixels_আকার);
                    GlobalUnlock(hMem);
                } অন্যথা {
                    WIN_SetError("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = ফাঁকা;
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
    ফেরত hMem;
}

স্থির শূন্য *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *আকার_2)
{
    শূন্য *bmp = ফাঁকা;
    size_t mem_আকার = Global_আকার(hMem);

    যদি (mem_আকার > আকার(BITMAPINFOHEADER)) {
        LPVOID dib = GlobalLock(hMem);
        যদি (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_table_আকার;
            নির্বাচন (pbih->biCompression) {
            ক্ষেত্র BI_RGB:
                যদি (pbih->bi_Bit_গুনতি <= 8) {
                    color_table_আকার = আকার(RGBQUAD) * (pbih->biClrUsed == 0 ? 1 << pbih->bi_Bit_গুনতি : pbih->biClrUsed);
                } অন্যথা {
                    color_table_আকার = 0;
                }
                বিরতি;
            ক্ষেত্র BI_BITFIELDS:
                color_table_আকার = 3 * আকার(DWORD);
                বিরতি;
            ক্ষেত্র 6 /* BI_ALPHABITFIELDS */:
                // https://learn.microsoft.com/en-us/previous-versions/windows/embedded/aa452885(v=msdn.10)
                color_table_আকার = 4 * আকার(DWORD);
                বিরতি;
            পূর্বনির্ধারিত: // FOURCC
                color_table_আকার = আকার(RGBQUAD) * pbih->biClrUsed;
            }

            size_t bih_আকার = pbih->bi_আকার + color_table_আকার;
            size_t dib_আকার = bih_আকার + pbih->bi_আকার_Image;
            যদি (dib_আকার <= mem_আকার) {
                size_t bmp_আকার = আকার(BITMAPFILEHEADER) + mem_আকার;
                bmp = SDL_malloc(bmp_আকার);
                যদি (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bf_আকার = (DWORD)bmp_আকার;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bfOffBits = (DWORD)(আকার(BITMAPFILEHEADER) + pbih->bi_আকার + color_table_আকার);
                    SDL_memcpy((Uint8 *)bmp + আকার(BITMAPFILEHEADER), dib, mem_আকার);
                    *আকার_2 = bmp_আকার;
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
    ফেরত bmp;
}

স্থির bool WIN_SetClipboardImage(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *mime_type)
{
    UINT format = 0;
    HANDLE hMem = ফাঁকা;
    size_t clipboard_তথ্য_আকার;
    ধ্রুবক শূন্য *clipboard_তথ্য;
    bool ফলাফল = true;

    clipboard_তথ্য = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_তথ্য_আকার);
    যদি (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_তথ্য, clipboard_তথ্য_আকার, &format);
    } অন্যথা যদি (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_তথ্য_আকার);
        যদি (hMem) {
            LPVOID dst = GlobalLock(hMem);
            যদি (dst) {
                SDL_memcpy(dst, clipboard_তথ্য, clipboard_তথ্য_আকার);
                GlobalUnlock(hMem);
            } অন্যথা {
                ফলাফল = WIN_SetError("GlobalLock()");
                GlobalFree(hMem);
                hMem = ফাঁকা;
            }
        } অন্যথা {
            ফলাফল = SDL_OutOfMemory();
        }
    } অন্যথা {
        ফলাফল = SDL_SetError("Unknown image format");
    }
    যদি (hMem) {
        // Save the image to the clipboard
        যদি (!Set_Clipboard_তথ্য(format, hMem)) {
            ফলাফল = WIN_SetError("Couldn't set clipboard data");
        }
    } অন্যথা {
        // WIN_ConvertBMPtoDIB() set the error
        ফলাফল = false;
    }
    ফেরত ফলাফল;
}

স্থির bool WIN_SetClipboardText(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *mime_type)
{
    HANDLE hMem;
    size_t clipboard_তথ্য_আকার;
    ধ্রুবক শূন্য *clipboard_তথ্য;
    bool ফলাফল = true;

    clipboard_তথ্য = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_তথ্য_আকার);
    যদি (clipboard_তথ্য && clipboard_তথ্য_আকার > 0) {
        আকার_T i, আকার_2;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (ধ্রুবক অক্ষর *)clipboard_তথ্য, clipboard_তথ্য_আকার);
        যদি (!tstr) {
            ফেরত SDL_SetError("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        জন্য (আকার_2 = 0, i = 0; tstr[i]; ++i, ++আকার_2) {
            যদি (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++আকার_2;
            }
        }
        আকার_2 = (আকার_2 + 1) * আকার(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, আকার_2);
        যদি (hMem) {
            LPWSTR dst = (LPWSTR)GlobalLock(hMem);
            যদি (dst) {
                // Copy the text over, adding carriage returns as necessary
                জন্য (i = 0; tstr[i]; ++i) {
                    যদি (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            যদি (!Set_Clipboard_তথ্য(CF_UNICODETEXT, hMem)) {
                ফলাফল = WIN_SetError("Couldn't set clipboard data");
            }
        } অন্যথা {
            ফলাফল = SDL_OutOfMemory();
        }
        SDL_free(tstr);
    }
    ফেরত ফলাফল;
}

bool WIN_Set_Clipboard_তথ্য(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;
    size_t i;
    bool ফলাফল = true;

    /* I investigated delayed clipboard rendering, and at least with text and image
     * formats you have to use an output window, not SDL_HelperWindow, and the system
     * requests them being rendered immediately, so there isn't any benefit.
     */

    যদি (WIN_OpenClipboard(_this)) {
        EmptyClipboard();

        // Set the clipboard text
        জন্য (i = 0; i < _this->অঙ্ক_clipboard_mime_types; ++i) {
            ধ্রুবক অক্ষর *mime_type = _this->clipboard_mime_types[i];

            যদি (SDL_IsTextMimeType(mime_type)) {
                যদি (!WIN_SetClipboardText(_this, mime_type)) {
                    ফলাফল = false;
                }
                // Only set the first clipboard text
                বিরতি;
            }
        }

        // Set the clipboard image
        জন্য (i = 0; i < _this->অঙ্ক_clipboard_mime_types; ++i) {
            ধ্রুবক অক্ষর *mime_type = _this->clipboard_mime_types[i];

            যদি (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                যদি (!WIN_SetClipboardImage(_this, mime_type)) {
                    ফলাফল = false;
                }
                বিরতি;
            }
        }

        তথ্য->clipboard_গুনতি = Get_Clipboard_Sequence_সংখ্যা();
        WIN_CloseClipboard();
    } অন্যথা {
        ফলাফল = WIN_SetError("Couldn't open clipboard");
    }
    ফেরত ফলাফল;
}

শূন্য *WIN_Get_Clipboard_তথ্য(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *mime_type, size_t *আকার_2)
{
    শূন্য *তথ্য = ফাঁকা;

    যদি (SDL_IsTextMimeType(mime_type)) {
        অক্ষর *text = ফাঁকা;

        যদি (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
            যদি (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = Get_Clipboard_তথ্য(CF_UNICODETEXT);
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

                hMem = Get_Clipboard_তথ্য(CF_TEXT);
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
        তথ্য = text;
        *আকার_2 = SDL_strlen(text);

    } অন্যথা যদি (SDL_strcmp(mime_type, "image/bmp") == 0) {
        যদি (IsClipboardFormatAvailable(CF_DIBV5)) {
            যদি (WIN_OpenClipboard(_this)) {
                HANDLE hMem = Get_Clipboard_তথ্য(CF_DIBV5);
                যদি (hMem) {
                    তথ্য = WIN_ConvertDIBtoBMP(hMem, আকার_2);
                } অন্যথা {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } অন্যথা যদি (IsClipboardFormatAvailable(CF_DIB)) {
            যদি (WIN_OpenClipboard(_this)) {
                HANDLE hMem = Get_Clipboard_তথ্য(CF_DIB);
                যদি (hMem) {
                    তথ্য = WIN_ConvertDIBtoBMP(hMem, আকার_2);
                } অন্যথা {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } অন্যথা যদি (SDL_strcmp(mime_type, "image/png") == 0) {
        যদি (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            যদি (WIN_OpenClipboard(_this)) {
                HANDLE hMem = Get_Clipboard_তথ্য(GetClipboardFormatPNG());
                যদি (hMem) {
                    size_t mem_আকার = Global_আকার(hMem);
                    শূন্য *mem = GlobalLock(hMem);
                    যদি (mem) {
                        তথ্য = SDL_malloc(mem_আকার);
                        যদি (তথ্য) {
                            SDL_memcpy(তথ্য, mem, mem_আকার);
                            *আকার_2 = mem_আকার;
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
        তথ্য = SDL_Get_Internal_Clipboard_তথ্য(_this, mime_type, আকার_2);
    }
    ফেরত তথ্য;
}

bool WIN_Has_Clipboard_তথ্য(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *mime_type)
{
    যদি (SDL_IsTextMimeType(mime_type)) {
        যদি (IsClipboardFormatAvailable(CF_UNICODETEXT) || IsClipboardFormatAvailable(CF_TEXT)) {
            ফেরত true;
        }
    } অন্যথা যদি (SDL_strcmp(mime_type, "image/bmp") == 0) {
        যদি (IsClipboardFormatAvailable(CF_DIBV5) || IsClipboardFormatAvailable(CF_DIB)) {
            ফেরত true;
        }
    } অন্যথা যদি (SDL_strcmp(mime_type, "image/png") == 0) {
        যদি (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            ফেরত true;
        }
    }
    ফেরত SDL_Has_Internal_Clipboard_তথ্য(_this, mime_type);
}

স্থির পূর্ণসংখ্যা GetClipboardFormatMimeType(UINT format, অক্ষর *name)
{
    ধ্রুবক অক্ষর *mime_type = ফাঁকা;

    নির্বাচন (format) {
    ক্ষেত্র CF_TEXT:
        mime_type = "text/plain";
        বিরতি;
    ক্ষেত্র CF_UNICODETEXT:
        mime_type = "text/plain;charset=utf-8";
        বিরতি;
    ক্ষেত্র CF_DIB:
    ক্ষেত্র CF_DIBV5:
        mime_type = "image/bmp";
        বিরতি;
    পূর্বনির্ধারিত:
        যদি (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        বিরতি;
    }
    যদি (mime_type) {
        size_t len = SDL_strlen(mime_type) + 1;
        যদি (name) {
            SDL_memcpy(name, mime_type, len);
        }
        ফেরত (পূর্ণসংখ্যা)len;
    }
    ফেরত 0;
}

স্থির অক্ষর **GetMimeTypes(পূর্ণসংখ্যা *pnformats)
{
    অক্ষর **new_mime_types = ফাঁকা;

    *pnformats = 0;

    যদি (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        পূর্ণসংখ্যা nformats = 0;
        UINT format = 0;
        পূর্ণসংখ্যা formatsSz = 0;
        bool have_image_bmp = false;
        জন্য ( ; ; ) {
            format = EnumClipboardFormats(format);
            যদি (!format) {
                বিরতি;
            }

#ifdef DEBUG_CLIPBOARD
            অক্ষর name[128] = { 0 };
            GetClipboardFormatNameA(format, name, আকার(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#endif

            যদি (format == CF_DIB || format == CF_DIBV5) {
                যদি (have_image_bmp) {
                    // We have already registered this format
                    চালু;
                }
                have_image_bmp = true;
            }

            পূর্ণসংখ্যা len = GetClipboardFormatMimeType(format, ফাঁকা);
            যদি (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_AllocateTemporaryMemory((nformats + 1) * আকার(অক্ষর *) + formatsSz);
        যদি (new_mime_types) {
            format = 0;
            অক্ষর *strPtr = (অক্ষর *)(new_mime_types + nformats + 1);
            পূর্ণসংখ্যা i = 0;
            জন্য ( ; ; ) {
                format = EnumClipboardFormats(format);
                যদি (!format) {
                    বিরতি;
                }

                যদি (format == CF_DIB || format == CF_DIBV5) {
                    যদি (have_image_bmp) {
                        // We have already registered this format
                        চালু;
                    }
                    have_image_bmp = true;
                }

                পূর্ণসংখ্যা len = GetClipboardFormatMimeType(format, strPtr);
                যদি (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = ফাঁকা;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    ফেরত new_mime_types;
}

শূন্য WIN_CheckClipboardUpdate(কাঠামো SDL_Video_তথ্য *তথ্য)
{
    DWORD গুনতি = Get_Clipboard_Sequence_সংখ্যা();
    যদি (গুনতি != তথ্য->clipboard_গুনতি) {
        যদি (গুনতি) {
            পূর্ণসংখ্যা nformats = 0;
            অক্ষর **new_mime_types = GetMimeTypes(&nformats);
            যদি (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        তথ্য->clipboard_গুনতি = গুনতি;
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
