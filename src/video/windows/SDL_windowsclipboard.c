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
#अन्तर्भाव "SDL_internal.h"

#जइ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#अन्तर्भाव "SDL_windowsvideo.h"
#अन्तर्भाव "SDL_windowswindow.h"
#अन्तर्भाव "../SDL_clipboard_c.h"
#अन्तर्भाव "../../events/SDL_events_c.h"
#अन्तर्भाव "../../events/SDL_clipboardevents_c.h"

#define BFT_BITMAP 0x4d42 // 'BM'

// Assume we can directly read and write BMP fields without byte swapping
SDL_COMPILE_TIME_ASSERT(verify_byte_order, SDL_BYTEORDER == SDL_LIL_ENDIAN);

स्थिर UINT GetClipboardFormatPNG(शून्य)
{
    स्थिर UINT format;

    जइ (!format) {
        format = RegisterClipboardFormat(TEXT("PNG"));
    }
    प्रत्यागम format;
}

स्थिर BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    ध्रुव पूर्णाङ्क MAX_ATTEMPTS = 3;
    पूर्णाङ्क attempt;
    HWND hwnd = रिक्त;

    जइ (_this->windows) {
        hwnd = _this->windows->internal->hwnd;
    }
    प्रति (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        जइ (OpenClipboard(hwnd)) {
            प्रत्यागम TRUE;
        }
        SDL_Delay(10);
    }
    प्रत्यागम FALSE;
}

स्थिर शून्य WIN_CloseClipboard(शून्य)
{
    CloseClipboard();
}

स्थिर HANDLE WIN_ConvertBMPtoDIB(ध्रुव शून्य *bmp, size_t bmp_size, UINT *format)
{
    HANDLE hMem = रिक्त;

    जइ (bmp && bmp_size > परिमाण(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + परिमाण(BITMAPFILEHEADER));
        size_t bih_size = pbih->biSize + pbih->biClrUsed * परिमाण(RGBQUAD);
        size_t pixels_size = pbih->biSizeImage;

        जइ (pbih->biSize >= परिमाण(BITMAPV5HEADER)) {
            *format = CF_DIBV5;
        } अण्णहा {
            *format = CF_DIB;
        }

        जइ (pbfh->bfOffBits >= (परिमाण(BITMAPFILEHEADER) + bih_size) &&
            (pbfh->bfOffBits + pixels_size) <= bmp_size) {
            ध्रुव Uint8 *pixels = (ध्रुव Uint8 *)bmp + pbfh->bfOffBits;
            size_t dib_size = bih_size + pixels_size;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_size);
            जइ (hMem) {
                LPVOID dst = GlobalLock(hMem);
                जइ (dst) {
                    SDL_memcpy(dst, pbih, bih_size);
                    SDL_memcpy((Uint8 *)dst + bih_size, pixels, pixels_size);
                    GlobalUnlock(hMem);
                } अण्णहा {
                    WIN_SetError("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = रिक्त;
                }
            } अण्णहा {
                SDL_OutOfMemory();
            }
        } अण्णहा {
            SDL_SetError("Invalid BMP data");
        }
    } अण्णहा {
        SDL_SetError("Invalid BMP data");
    }
    प्रत्यागम hMem;
}

स्थिर शून्य *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *size)
{
    शून्य *bmp = रिक्त;
    size_t mem_size = GlobalSize(hMem);

    जइ (mem_size > परिमाण(BITMAPINFOHEADER)) {
        LPVOID dib = GlobalLock(hMem);
        जइ (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_table_size;
            विकल्प (pbih->biCompression) {
            पक्ष BI_RGB:
                जइ (pbih->bi_Bit_गणनम् <= 8) {
                    color_table_size = परिमाण(RGBQUAD) * (pbih->biClrUsed == 0 ? 1 << pbih->bi_Bit_गणनम् : pbih->biClrUsed);
                } अण्णहा {
                    color_table_size = 0;
                }
                भङ्ग;
            पक्ष BI_BITFIELDS:
                color_table_size = 3 * परिमाण(DWORD);
                भङ्ग;
            पक्ष 6 /* BI_ALPHABITFIELDS */:
                // https://learn.microsoft.com/en-us/previous-versions/windows/embedded/aa452885(v=msdn.10)
                color_table_size = 4 * परिमाण(DWORD);
                भङ्ग;
            स्वभाव: // FOURCC
                color_table_size = परिमाण(RGBQUAD) * pbih->biClrUsed;
            }

            size_t bih_size = pbih->biSize + color_table_size;
            size_t dib_size = bih_size + pbih->biSizeImage;
            जइ (dib_size <= mem_size) {
                size_t bmp_size = परिमाण(BITMAPFILEHEADER) + mem_size;
                bmp = SDL_malloc(bmp_size);
                जइ (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bfSize = (DWORD)bmp_size;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bfOffBits = (DWORD)(परिमाण(BITMAPFILEHEADER) + pbih->biSize + color_table_size);
                    SDL_memcpy((Uint8 *)bmp + परिमाण(BITMAPFILEHEADER), dib, mem_size);
                    *size = bmp_size;
                }
            } अण्णहा {
                SDL_SetError("Invalid BMP data");
            }
            GlobalUnlock(hMem);
        } अण्णहा {
            WIN_SetError("GlobalLock()");
        }
    } अण्णहा {
        SDL_SetError("Invalid BMP data");
    }
    प्रत्यागम bmp;
}

स्थिर bool WIN_SetClipboardImage(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type)
{
    UINT format = 0;
    HANDLE hMem = रिक्त;
    size_t clipboard_data_size;
    ध्रुव शून्य *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    जइ (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_data, clipboard_data_size, &format);
    } अण्णहा जइ (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_data_size);
        जइ (hMem) {
            LPVOID dst = GlobalLock(hMem);
            जइ (dst) {
                SDL_memcpy(dst, clipboard_data, clipboard_data_size);
                GlobalUnlock(hMem);
            } अण्णहा {
                result = WIN_SetError("GlobalLock()");
                GlobalFree(hMem);
                hMem = रिक्त;
            }
        } अण्णहा {
            result = SDL_OutOfMemory();
        }
    } अण्णहा {
        result = SDL_SetError("Unknown image format");
    }
    जइ (hMem) {
        // Save the image to the clipboard
        जइ (!SetClipboardData(format, hMem)) {
            result = WIN_SetError("Couldn't set clipboard data");
        }
    } अण्णहा {
        // WIN_ConvertBMPtoDIB() set the error
        result = false;
    }
    प्रत्यागम result;
}

स्थिर bool WIN_SetClipboardText(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type)
{
    HANDLE hMem;
    size_t clipboard_data_size;
    ध्रुव शून्य *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    जइ (clipboard_data && clipboard_data_size > 0) {
        SIZE_T i, size;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (ध्रुव वर्ण *)clipboard_data, clipboard_data_size);
        जइ (!tstr) {
            प्रत्यागम SDL_SetError("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        प्रति (size = 0, i = 0; tstr[i]; ++i, ++size) {
            जइ (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++size;
            }
        }
        size = (size + 1) * परिमाण(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, size);
        जइ (hMem) {
            LPWSTR dst = (LPWSTR)GlobalLock(hMem);
            जइ (dst) {
                // Copy the text over, adding carriage returns as necessary
                प्रति (i = 0; tstr[i]; ++i) {
                    जइ (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            जइ (!SetClipboardData(CF_UNICODETEXT, hMem)) {
                result = WIN_SetError("Couldn't set clipboard data");
            }
        } अण्णहा {
            result = SDL_OutOfMemory();
        }
        SDL_free(tstr);
    }
    प्रत्यागम result;
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

    जइ (WIN_OpenClipboard(_this)) {
        EmptyClipboard();

        // Set the clipboard text
        प्रति (i = 0; i < _this->अङ्कः_clipboard_mime_types; ++i) {
            ध्रुव वर्ण *mime_type = _this->clipboard_mime_types[i];

            जइ (SDL_IsTextMimeType(mime_type)) {
                जइ (!WIN_SetClipboardText(_this, mime_type)) {
                    result = false;
                }
                // Only set the first clipboard text
                भङ्ग;
            }
        }

        // Set the clipboard image
        प्रति (i = 0; i < _this->अङ्कः_clipboard_mime_types; ++i) {
            ध्रुव वर्ण *mime_type = _this->clipboard_mime_types[i];

            जइ (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                जइ (!WIN_SetClipboardImage(_this, mime_type)) {
                    result = false;
                }
                भङ्ग;
            }
        }

        data->clipboard_गणनम् = Get_Clipboard_Sequence_सङ्ख्या();
        WIN_CloseClipboard();
    } अण्णहा {
        result = WIN_SetError("Couldn't open clipboard");
    }
    प्रत्यागम result;
}

शून्य *WIN_GetClipboardData(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type, size_t *size)
{
    शून्य *data = रिक्त;

    जइ (SDL_IsTextMimeType(mime_type)) {
        वर्ण *text = रिक्त;

        जइ (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
            जइ (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = GetClipboardData(CF_UNICODETEXT);
                जइ (hMem) {
                    str = (LPTSTR)GlobalLock(hMem);
                    जइ (str) {
                        text = WIN_StringToUTF8W(str);
                        GlobalUnlock(hMem);
                    } अण्णहा {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } अण्णहा {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } अण्णहा जइ (IsClipboardFormatAvailable(CF_TEXT)) {
            जइ (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = GetClipboardData(CF_TEXT);
                जइ (hMem) {
                    str = (LPCSTR)GlobalLock(hMem);
                    जइ (str) {
                        text = SDL_strdup(str);
                        GlobalUnlock(hMem);
                    } अण्णहा {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } अण्णहा {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }
        जइ (!text) {
            text = SDL_strdup("");
        }
        data = text;
        *size = SDL_strlen(text);

    } अण्णहा जइ (SDL_strcmp(mime_type, "image/bmp") == 0) {
        जइ (IsClipboardFormatAvailable(CF_DIBV5)) {
            जइ (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIBV5);
                जइ (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } अण्णहा {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } अण्णहा जइ (IsClipboardFormatAvailable(CF_DIB)) {
            जइ (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIB);
                जइ (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } अण्णहा {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } अण्णहा जइ (SDL_strcmp(mime_type, "image/png") == 0) {
        जइ (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            जइ (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(GetClipboardFormatPNG());
                जइ (hMem) {
                    size_t mem_size = GlobalSize(hMem);
                    शून्य *mem = GlobalLock(hMem);
                    जइ (mem) {
                        data = SDL_malloc(mem_size);
                        जइ (data) {
                            SDL_memcpy(data, mem, mem_size);
                            *size = mem_size;
                        }
                        GlobalUnlock(hMem);
                    } अण्णहा {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } अण्णहा {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } अण्णहा {
        data = SDL_GetInternalClipboardData(_this, mime_type, size);
    }
    प्रत्यागम data;
}

bool WIN_HasClipboardData(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type)
{
    जइ (SDL_IsTextMimeType(mime_type)) {
        जइ (IsClipboardFormatAvailable(CF_UNICODETEXT) || IsClipboardFormatAvailable(CF_TEXT)) {
            प्रत्यागम true;
        }
    } अण्णहा जइ (SDL_strcmp(mime_type, "image/bmp") == 0) {
        जइ (IsClipboardFormatAvailable(CF_DIBV5) || IsClipboardFormatAvailable(CF_DIB)) {
            प्रत्यागम true;
        }
    } अण्णहा जइ (SDL_strcmp(mime_type, "image/png") == 0) {
        जइ (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            प्रत्यागम true;
        }
    }
    प्रत्यागम SDL_HasInternalClipboardData(_this, mime_type);
}

स्थिर पूर्णाङ्क GetClipboardFormatMimeType(UINT format, वर्ण *name)
{
    ध्रुव वर्ण *mime_type = रिक्त;

    विकल्प (format) {
    पक्ष CF_TEXT:
        mime_type = "text/plain";
        भङ्ग;
    पक्ष CF_UNICODETEXT:
        mime_type = "text/plain;charset=utf-8";
        भङ्ग;
    पक्ष CF_DIB:
    पक्ष CF_DIBV5:
        mime_type = "image/bmp";
        भङ्ग;
    स्वभाव:
        जइ (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        भङ्ग;
    }
    जइ (mime_type) {
        size_t len = SDL_strlen(mime_type) + 1;
        जइ (name) {
            SDL_memcpy(name, mime_type, len);
        }
        प्रत्यागम (पूर्णाङ्क)len;
    }
    प्रत्यागम 0;
}

स्थिर वर्ण **GetMimeTypes(पूर्णाङ्क *pnformats)
{
    वर्ण **new_mime_types = रिक्त;

    *pnformats = 0;

    जइ (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        पूर्णाङ्क nformats = 0;
        UINT format = 0;
        पूर्णाङ्क formatsSz = 0;
        bool have_image_bmp = false;
        प्रति ( ; ; ) {
            format = EnumClipboardFormats(format);
            जइ (!format) {
                भङ्ग;
            }

#ifdef DEBUG_CLIPBOARD
            वर्ण name[128] = { 0 };
            GetClipboardFormatNameA(format, name, परिमाण(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#endif

            जइ (format == CF_DIB || format == CF_DIBV5) {
                जइ (have_image_bmp) {
                    // We have already registered this format
                    अनुवर्त;
                }
                have_image_bmp = true;
            }

            पूर्णाङ्क len = GetClipboardFormatMimeType(format, रिक्त);
            जइ (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_AllocateTemporaryMemory((nformats + 1) * परिमाण(वर्ण *) + formatsSz);
        जइ (new_mime_types) {
            format = 0;
            वर्ण *strPtr = (वर्ण *)(new_mime_types + nformats + 1);
            पूर्णाङ्क i = 0;
            प्रति ( ; ; ) {
                format = EnumClipboardFormats(format);
                जइ (!format) {
                    भङ्ग;
                }

                जइ (format == CF_DIB || format == CF_DIBV5) {
                    जइ (have_image_bmp) {
                        // We have already registered this format
                        अनुवर्त;
                    }
                    have_image_bmp = true;
                }

                पूर्णाङ्क len = GetClipboardFormatMimeType(format, strPtr);
                जइ (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = रिक्त;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    प्रत्यागम new_mime_types;
}

शून्य WIN_CheckClipboardUpdate(संरचना SDL_VideoData *data)
{
    DWORD गणनम् = Get_Clipboard_Sequence_सङ्ख्या();
    जइ (गणनम् != data->clipboard_गणनम्) {
        जइ (गणनम्) {
            पूर्णाङ्क nformats = 0;
            वर्ण **new_mime_types = GetMimeTypes(&nformats);
            जइ (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        data->clipboard_गणनम् = गणनम्;
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
