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

#सचे defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

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

    सचे (!format) {
        format = RegisterClipboardFormat(TEXT("PNG"));
    }
    पटिनिवत्त format;
}

स्थिर BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    ध्रुव पूर्णाङ्क MAX_ATTEMPTS = 3;
    पूर्णाङ्क attempt;
    HWND hwnd = रिक्त;

    सचे (_this->windows) {
        hwnd = _this->windows->internal->hwnd;
    }
    अत्थाय (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        सचे (OpenClipboard(hwnd)) {
            पटिनिवत्त TRUE;
        }
        SDL_Delay(10);
    }
    पटिनिवत्त FALSE;
}

स्थिर शून्य WIN_CloseClipboard(शून्य)
{
    CloseClipboard();
}

स्थिर HANDLE WIN_ConvertBMPtoDIB(ध्रुव शून्य *bmp, size_t bmp_size, UINT *format)
{
    HANDLE hMem = रिक्त;

    सचे (bmp && bmp_size > परिमाण(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + परिमाण(BITMAPFILEHEADER));
        size_t bih_size = pbih->biSize + pbih->biClrUsed * परिमाण(RGBQUAD);
        size_t pixels_size = pbih->biSizeImage;

        सचे (pbih->biSize >= परिमाण(BITMAPV5HEADER)) {
            *format = CF_DIBV5;
        } अञ्ञथा {
            *format = CF_DIB;
        }

        सचे (pbfh->bfOffBits >= (परिमाण(BITMAPFILEHEADER) + bih_size) &&
            (pbfh->bfOffBits + pixels_size) <= bmp_size) {
            ध्रुव Uint8 *pixels = (ध्रुव Uint8 *)bmp + pbfh->bfOffBits;
            size_t dib_size = bih_size + pixels_size;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_size);
            सचे (hMem) {
                LPVOID dst = GlobalLock(hMem);
                सचे (dst) {
                    SDL_memcpy(dst, pbih, bih_size);
                    SDL_memcpy((Uint8 *)dst + bih_size, pixels, pixels_size);
                    GlobalUnlock(hMem);
                } अञ्ञथा {
                    WIN_SetError("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = रिक्त;
                }
            } अञ्ञथा {
                SDL_OutOfMemory();
            }
        } अञ्ञथा {
            SDL_SetError("Invalid BMP data");
        }
    } अञ्ञथा {
        SDL_SetError("Invalid BMP data");
    }
    पटिनिवत्त hMem;
}

स्थिर शून्य *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *size)
{
    शून्य *bmp = रिक्त;
    size_t mem_size = GlobalSize(hMem);

    सचे (mem_size > परिमाण(BITMAPINFOHEADER)) {
        LPVOID dib = GlobalLock(hMem);
        सचे (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_table_size;
            विकल्प (pbih->biCompression) {
            पक्ष BI_RGB:
                सचे (pbih->bi_Bit_गणनम् <= 8) {
                    color_table_size = परिमाण(RGBQUAD) * (pbih->biClrUsed == 0 ? 1 << pbih->bi_Bit_गणनम् : pbih->biClrUsed);
                } अञ्ञथा {
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
            सचे (dib_size <= mem_size) {
                size_t bmp_size = परिमाण(BITMAPFILEHEADER) + mem_size;
                bmp = SDL_malloc(bmp_size);
                सचे (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bfSize = (DWORD)bmp_size;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bfOffBits = (DWORD)(परिमाण(BITMAPFILEHEADER) + pbih->biSize + color_table_size);
                    SDL_memcpy((Uint8 *)bmp + परिमाण(BITMAPFILEHEADER), dib, mem_size);
                    *size = bmp_size;
                }
            } अञ्ञथा {
                SDL_SetError("Invalid BMP data");
            }
            GlobalUnlock(hMem);
        } अञ्ञथा {
            WIN_SetError("GlobalLock()");
        }
    } अञ्ञथा {
        SDL_SetError("Invalid BMP data");
    }
    पटिनिवत्त bmp;
}

स्थिर bool WIN_SetClipboardImage(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type)
{
    UINT format = 0;
    HANDLE hMem = रिक्त;
    size_t clipboard_data_size;
    ध्रुव शून्य *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    सचे (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_data, clipboard_data_size, &format);
    } अञ्ञथा सचे (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_data_size);
        सचे (hMem) {
            LPVOID dst = GlobalLock(hMem);
            सचे (dst) {
                SDL_memcpy(dst, clipboard_data, clipboard_data_size);
                GlobalUnlock(hMem);
            } अञ्ञथा {
                result = WIN_SetError("GlobalLock()");
                GlobalFree(hMem);
                hMem = रिक्त;
            }
        } अञ्ञथा {
            result = SDL_OutOfMemory();
        }
    } अञ्ञथा {
        result = SDL_SetError("Unknown image format");
    }
    सचे (hMem) {
        // Save the image to the clipboard
        सचे (!SetClipboardData(format, hMem)) {
            result = WIN_SetError("Couldn't set clipboard data");
        }
    } अञ्ञथा {
        // WIN_ConvertBMPtoDIB() set the error
        result = false;
    }
    पटिनिवत्त result;
}

स्थिर bool WIN_SetClipboardText(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type)
{
    HANDLE hMem;
    size_t clipboard_data_size;
    ध्रुव शून्य *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    सचे (clipboard_data && clipboard_data_size > 0) {
        SIZE_T i, size;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (ध्रुव वर्ण *)clipboard_data, clipboard_data_size);
        सचे (!tstr) {
            पटिनिवत्त SDL_SetError("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        अत्थाय (size = 0, i = 0; tstr[i]; ++i, ++size) {
            सचे (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++size;
            }
        }
        size = (size + 1) * परिमाण(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, size);
        सचे (hMem) {
            LPWSTR dst = (LPWSTR)GlobalLock(hMem);
            सचे (dst) {
                // Copy the text over, adding carriage returns as necessary
                अत्थाय (i = 0; tstr[i]; ++i) {
                    सचे (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            सचे (!SetClipboardData(CF_UNICODETEXT, hMem)) {
                result = WIN_SetError("Couldn't set clipboard data");
            }
        } अञ्ञथा {
            result = SDL_OutOfMemory();
        }
        SDL_free(tstr);
    }
    पटिनिवत्त result;
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

    सचे (WIN_OpenClipboard(_this)) {
        EmptyClipboard();

        // Set the clipboard text
        अत्थाय (i = 0; i < _this->अङ्कः_clipboard_mime_types; ++i) {
            ध्रुव वर्ण *mime_type = _this->clipboard_mime_types[i];

            सचे (SDL_IsTextMimeType(mime_type)) {
                सचे (!WIN_SetClipboardText(_this, mime_type)) {
                    result = false;
                }
                // Only set the first clipboard text
                भङ्ग;
            }
        }

        // Set the clipboard image
        अत्थाय (i = 0; i < _this->अङ्कः_clipboard_mime_types; ++i) {
            ध्रुव वर्ण *mime_type = _this->clipboard_mime_types[i];

            सचे (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                सचे (!WIN_SetClipboardImage(_this, mime_type)) {
                    result = false;
                }
                भङ्ग;
            }
        }

        data->clipboard_गणनम् = Get_Clipboard_Sequence_सङ्ख्या();
        WIN_CloseClipboard();
    } अञ्ञथा {
        result = WIN_SetError("Couldn't open clipboard");
    }
    पटिनिवत्त result;
}

शून्य *WIN_GetClipboardData(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type, size_t *size)
{
    शून्य *data = रिक्त;

    सचे (SDL_IsTextMimeType(mime_type)) {
        वर्ण *text = रिक्त;

        सचे (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
            सचे (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = GetClipboardData(CF_UNICODETEXT);
                सचे (hMem) {
                    str = (LPTSTR)GlobalLock(hMem);
                    सचे (str) {
                        text = WIN_StringToUTF8W(str);
                        GlobalUnlock(hMem);
                    } अञ्ञथा {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } अञ्ञथा {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } अञ्ञथा सचे (IsClipboardFormatAvailable(CF_TEXT)) {
            सचे (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = GetClipboardData(CF_TEXT);
                सचे (hMem) {
                    str = (LPCSTR)GlobalLock(hMem);
                    सचे (str) {
                        text = SDL_strdup(str);
                        GlobalUnlock(hMem);
                    } अञ्ञथा {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } अञ्ञथा {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }
        सचे (!text) {
            text = SDL_strdup("");
        }
        data = text;
        *size = SDL_strlen(text);

    } अञ्ञथा सचे (SDL_strcmp(mime_type, "image/bmp") == 0) {
        सचे (IsClipboardFormatAvailable(CF_DIBV5)) {
            सचे (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIBV5);
                सचे (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } अञ्ञथा {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } अञ्ञथा सचे (IsClipboardFormatAvailable(CF_DIB)) {
            सचे (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIB);
                सचे (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } अञ्ञथा {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } अञ्ञथा सचे (SDL_strcmp(mime_type, "image/png") == 0) {
        सचे (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            सचे (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(GetClipboardFormatPNG());
                सचे (hMem) {
                    size_t mem_size = GlobalSize(hMem);
                    शून्य *mem = GlobalLock(hMem);
                    सचे (mem) {
                        data = SDL_malloc(mem_size);
                        सचे (data) {
                            SDL_memcpy(data, mem, mem_size);
                            *size = mem_size;
                        }
                        GlobalUnlock(hMem);
                    } अञ्ञथा {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } अञ्ञथा {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } अञ्ञथा {
        data = SDL_GetInternalClipboardData(_this, mime_type, size);
    }
    पटिनिवत्त data;
}

bool WIN_HasClipboardData(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type)
{
    सचे (SDL_IsTextMimeType(mime_type)) {
        सचे (IsClipboardFormatAvailable(CF_UNICODETEXT) || IsClipboardFormatAvailable(CF_TEXT)) {
            पटिनिवत्त true;
        }
    } अञ्ञथा सचे (SDL_strcmp(mime_type, "image/bmp") == 0) {
        सचे (IsClipboardFormatAvailable(CF_DIBV5) || IsClipboardFormatAvailable(CF_DIB)) {
            पटिनिवत्त true;
        }
    } अञ्ञथा सचे (SDL_strcmp(mime_type, "image/png") == 0) {
        सचे (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            पटिनिवत्त true;
        }
    }
    पटिनिवत्त SDL_HasInternalClipboardData(_this, mime_type);
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
        सचे (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        भङ्ग;
    }
    सचे (mime_type) {
        size_t len = SDL_strlen(mime_type) + 1;
        सचे (name) {
            SDL_memcpy(name, mime_type, len);
        }
        पटिनिवत्त (पूर्णाङ्क)len;
    }
    पटिनिवत्त 0;
}

स्थिर वर्ण **GetMimeTypes(पूर्णाङ्क *pnformats)
{
    वर्ण **new_mime_types = रिक्त;

    *pnformats = 0;

    सचे (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        पूर्णाङ्क nformats = 0;
        UINT format = 0;
        पूर्णाङ्क formatsSz = 0;
        bool have_image_bmp = false;
        अत्थाय ( ; ; ) {
            format = EnumClipboardFormats(format);
            सचे (!format) {
                भङ्ग;
            }

#ifdef DEBUG_CLIPBOARD
            वर्ण name[128] = { 0 };
            GetClipboardFormatNameA(format, name, परिमाण(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#endif

            सचे (format == CF_DIB || format == CF_DIBV5) {
                सचे (have_image_bmp) {
                    // We have already registered this format
                    अनुवर्त;
                }
                have_image_bmp = true;
            }

            पूर्णाङ्क len = GetClipboardFormatMimeType(format, रिक्त);
            सचे (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_AllocateTemporaryMemory((nformats + 1) * परिमाण(वर्ण *) + formatsSz);
        सचे (new_mime_types) {
            format = 0;
            वर्ण *strPtr = (वर्ण *)(new_mime_types + nformats + 1);
            पूर्णाङ्क i = 0;
            अत्थाय ( ; ; ) {
                format = EnumClipboardFormats(format);
                सचे (!format) {
                    भङ्ग;
                }

                सचे (format == CF_DIB || format == CF_DIBV5) {
                    सचे (have_image_bmp) {
                        // We have already registered this format
                        अनुवर्त;
                    }
                    have_image_bmp = true;
                }

                पूर्णाङ्क len = GetClipboardFormatMimeType(format, strPtr);
                सचे (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = रिक्त;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    पटिनिवत्त new_mime_types;
}

शून्य WIN_CheckClipboardUpdate(संरचना SDL_VideoData *data)
{
    DWORD गणनम् = Get_Clipboard_Sequence_सङ्ख्या();
    सचे (गणनम् != data->clipboard_गणनम्) {
        सचे (गणनम्) {
            पूर्णाङ्क nformats = 0;
            वर्ण **new_mime_types = GetMimeTypes(&nformats);
            सचे (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        data->clipboard_गणनम् = गणनम्;
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
