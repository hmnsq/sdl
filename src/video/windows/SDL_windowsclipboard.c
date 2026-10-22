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

#जर defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

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

    जर (!format) {
        format = RegisterClipboardFormat(TEXT("PNG"));
    }
    परत format;
}

स्थिर BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    स्थिरांक पूर्णांक MAX_ATTEMPTS = 3;
    पूर्णांक attempt;
    HWND hwnd = रिक्त;

    जर (_this->windows) {
        hwnd = _this->windows->internal->hwnd;
    }
    साठी (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        जर (OpenClipboard(hwnd)) {
            परत TRUE;
        }
        SDL_Delay(10);
    }
    परत FALSE;
}

स्थिर शून्य WIN_CloseClipboard(शून्य)
{
    CloseClipboard();
}

स्थिर HANDLE WIN_ConvertBMPtoDIB(स्थिरांक शून्य *bmp, माप_प्रकार bmp_size, UINT *format)
{
    HANDLE hMem = रिक्त;

    जर (bmp && bmp_size > आकार(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + आकार(BITMAPFILEHEADER));
        माप_प्रकार bih_size = pbih->biSize + pbih->biClrUsed * आकार(RGBQUAD);
        माप_प्रकार pixels_size = pbih->biSizeImage;

        जर (pbih->biSize >= आकार(BITMAPV5HEADER)) {
            *format = CF_DIBV5;
        } अन्यथा {
            *format = CF_DIB;
        }

        जर (pbfh->bfOffBits >= (आकार(BITMAPFILEHEADER) + bih_size) &&
            (pbfh->bfOffBits + pixels_size) <= bmp_size) {
            स्थिरांक Uint8 *pixels = (स्थिरांक Uint8 *)bmp + pbfh->bfOffBits;
            माप_प्रकार dib_size = bih_size + pixels_size;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_size);
            जर (hMem) {
                LPVOID dst = GlobalLock(hMem);
                जर (dst) {
                    SDL_memcpy(dst, pbih, bih_size);
                    SDL_memcpy((Uint8 *)dst + bih_size, pixels, pixels_size);
                    GlobalUnlock(hMem);
                } अन्यथा {
                    WIN_SetError("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = रिक्त;
                }
            } अन्यथा {
                SDL_OutOfMemory();
            }
        } अन्यथा {
            SDL_SetError("Invalid BMP data");
        }
    } अन्यथा {
        SDL_SetError("Invalid BMP data");
    }
    परत hMem;
}

स्थिर शून्य *WIN_ConvertDIBtoBMP(HANDLE hMem, माप_प्रकार *size)
{
    शून्य *bmp = रिक्त;
    माप_प्रकार mem_size = GlobalSize(hMem);

    जर (mem_size > आकार(BITMAPINFOHEADER)) {
        LPVOID dib = GlobalLock(hMem);
        जर (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            माप_प्रकार color_table_size;
            निवड (pbih->biCompression) {
            स्थिती BI_RGB:
                जर (pbih->bi_Bit_मोजणी <= 8) {
                    color_table_size = आकार(RGBQUAD) * (pbih->biClrUsed == 0 ? 1 << pbih->bi_Bit_मोजणी : pbih->biClrUsed);
                } अन्यथा {
                    color_table_size = 0;
                }
                थांबा;
            स्थिती BI_BITFIELDS:
                color_table_size = 3 * आकार(DWORD);
                थांबा;
            स्थिती 6 /* BI_ALPHABITFIELDS */:
                // https://learn.microsoft.com/en-us/previous-versions/windows/embedded/aa452885(v=msdn.10)
                color_table_size = 4 * आकार(DWORD);
                थांबा;
            पूर्वनिर्धारित: // FOURCC
                color_table_size = आकार(RGBQUAD) * pbih->biClrUsed;
            }

            माप_प्रकार bih_size = pbih->biSize + color_table_size;
            माप_प्रकार dib_size = bih_size + pbih->biSizeImage;
            जर (dib_size <= mem_size) {
                माप_प्रकार bmp_size = आकार(BITMAPFILEHEADER) + mem_size;
                bmp = SDL_malloc(bmp_size);
                जर (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bfSize = (DWORD)bmp_size;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bfOffBits = (DWORD)(आकार(BITMAPFILEHEADER) + pbih->biSize + color_table_size);
                    SDL_memcpy((Uint8 *)bmp + आकार(BITMAPFILEHEADER), dib, mem_size);
                    *size = bmp_size;
                }
            } अन्यथा {
                SDL_SetError("Invalid BMP data");
            }
            GlobalUnlock(hMem);
        } अन्यथा {
            WIN_SetError("GlobalLock()");
        }
    } अन्यथा {
        SDL_SetError("Invalid BMP data");
    }
    परत bmp;
}

स्थिर bool WIN_SetClipboardImage(SDL_VideoDevice *_this, स्थिरांक अक्षर *mime_type)
{
    UINT format = 0;
    HANDLE hMem = रिक्त;
    माप_प्रकार clipboard_data_size;
    स्थिरांक शून्य *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    जर (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_data, clipboard_data_size, &format);
    } अन्यथा जर (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_data_size);
        जर (hMem) {
            LPVOID dst = GlobalLock(hMem);
            जर (dst) {
                SDL_memcpy(dst, clipboard_data, clipboard_data_size);
                GlobalUnlock(hMem);
            } अन्यथा {
                result = WIN_SetError("GlobalLock()");
                GlobalFree(hMem);
                hMem = रिक्त;
            }
        } अन्यथा {
            result = SDL_OutOfMemory();
        }
    } अन्यथा {
        result = SDL_SetError("Unknown image format");
    }
    जर (hMem) {
        // Save the image to the clipboard
        जर (!SetClipboardData(format, hMem)) {
            result = WIN_SetError("Couldn't set clipboard data");
        }
    } अन्यथा {
        // WIN_ConvertBMPtoDIB() set the error
        result = false;
    }
    परत result;
}

स्थिर bool WIN_SetClipboardText(SDL_VideoDevice *_this, स्थिरांक अक्षर *mime_type)
{
    HANDLE hMem;
    माप_प्रकार clipboard_data_size;
    स्थिरांक शून्य *clipboard_data;
    bool result = true;

    clipboard_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_data_size);
    जर (clipboard_data && clipboard_data_size > 0) {
        SIZE_T i, size;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (स्थिरांक अक्षर *)clipboard_data, clipboard_data_size);
        जर (!tstr) {
            परत SDL_SetError("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        साठी (size = 0, i = 0; tstr[i]; ++i, ++size) {
            जर (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++size;
            }
        }
        size = (size + 1) * आकार(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, size);
        जर (hMem) {
            LPWSTR dst = (LPWSTR)GlobalLock(hMem);
            जर (dst) {
                // Copy the text over, adding carriage returns as necessary
                साठी (i = 0; tstr[i]; ++i) {
                    जर (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            जर (!SetClipboardData(CF_UNICODETEXT, hMem)) {
                result = WIN_SetError("Couldn't set clipboard data");
            }
        } अन्यथा {
            result = SDL_OutOfMemory();
        }
        SDL_free(tstr);
    }
    परत result;
}

bool WIN_SetClipboardData(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    माप_प्रकार i;
    bool result = true;

    /* I investigated delayed clipboard rendering, and at least with text and image
     * formats you have to use an output window, not SDL_HelperWindow, and the system
     * requests them being rendered immediately, so there isn't any benefit.
     */

    जर (WIN_OpenClipboard(_this)) {
        EmptyClipboard();

        // Set the clipboard text
        साठी (i = 0; i < _this->अंक_clipboard_mime_types; ++i) {
            स्थिरांक अक्षर *mime_type = _this->clipboard_mime_types[i];

            जर (SDL_IsTextMimeType(mime_type)) {
                जर (!WIN_SetClipboardText(_this, mime_type)) {
                    result = false;
                }
                // Only set the first clipboard text
                थांबा;
            }
        }

        // Set the clipboard image
        साठी (i = 0; i < _this->अंक_clipboard_mime_types; ++i) {
            स्थिरांक अक्षर *mime_type = _this->clipboard_mime_types[i];

            जर (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                जर (!WIN_SetClipboardImage(_this, mime_type)) {
                    result = false;
                }
                थांबा;
            }
        }

        data->clipboard_मोजणी = Get_Clipboard_Sequence_संख्या();
        WIN_CloseClipboard();
    } अन्यथा {
        result = WIN_SetError("Couldn't open clipboard");
    }
    परत result;
}

शून्य *WIN_GetClipboardData(SDL_VideoDevice *_this, स्थिरांक अक्षर *mime_type, माप_प्रकार *size)
{
    शून्य *data = रिक्त;

    जर (SDL_IsTextMimeType(mime_type)) {
        अक्षर *text = रिक्त;

        जर (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
            जर (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = GetClipboardData(CF_UNICODETEXT);
                जर (hMem) {
                    str = (LPTSTR)GlobalLock(hMem);
                    जर (str) {
                        text = WIN_StringToUTF8W(str);
                        GlobalUnlock(hMem);
                    } अन्यथा {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } अन्यथा {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } अन्यथा जर (IsClipboardFormatAvailable(CF_TEXT)) {
            जर (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = GetClipboardData(CF_TEXT);
                जर (hMem) {
                    str = (LPCSTR)GlobalLock(hMem);
                    जर (str) {
                        text = SDL_strdup(str);
                        GlobalUnlock(hMem);
                    } अन्यथा {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } अन्यथा {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }
        जर (!text) {
            text = SDL_strdup("");
        }
        data = text;
        *size = SDL_strlen(text);

    } अन्यथा जर (SDL_strcmp(mime_type, "image/bmp") == 0) {
        जर (IsClipboardFormatAvailable(CF_DIBV5)) {
            जर (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIBV5);
                जर (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } अन्यथा {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } अन्यथा जर (IsClipboardFormatAvailable(CF_DIB)) {
            जर (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(CF_DIB);
                जर (hMem) {
                    data = WIN_ConvertDIBtoBMP(hMem, size);
                } अन्यथा {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } अन्यथा जर (SDL_strcmp(mime_type, "image/png") == 0) {
        जर (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            जर (WIN_OpenClipboard(_this)) {
                HANDLE hMem = GetClipboardData(GetClipboardFormatPNG());
                जर (hMem) {
                    माप_प्रकार mem_size = GlobalSize(hMem);
                    शून्य *mem = GlobalLock(hMem);
                    जर (mem) {
                        data = SDL_malloc(mem_size);
                        जर (data) {
                            SDL_memcpy(data, mem, mem_size);
                            *size = mem_size;
                        }
                        GlobalUnlock(hMem);
                    } अन्यथा {
                        WIN_SetError("Couldn't lock clipboard data");
                    }
                } अन्यथा {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } अन्यथा {
        data = SDL_GetInternalClipboardData(_this, mime_type, size);
    }
    परत data;
}

bool WIN_HasClipboardData(SDL_VideoDevice *_this, स्थिरांक अक्षर *mime_type)
{
    जर (SDL_IsTextMimeType(mime_type)) {
        जर (IsClipboardFormatAvailable(CF_UNICODETEXT) || IsClipboardFormatAvailable(CF_TEXT)) {
            परत true;
        }
    } अन्यथा जर (SDL_strcmp(mime_type, "image/bmp") == 0) {
        जर (IsClipboardFormatAvailable(CF_DIBV5) || IsClipboardFormatAvailable(CF_DIB)) {
            परत true;
        }
    } अन्यथा जर (SDL_strcmp(mime_type, "image/png") == 0) {
        जर (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            परत true;
        }
    }
    परत SDL_HasInternalClipboardData(_this, mime_type);
}

स्थिर पूर्णांक GetClipboardFormatMimeType(UINT format, अक्षर *name)
{
    स्थिरांक अक्षर *mime_type = रिक्त;

    निवड (format) {
    स्थिती CF_TEXT:
        mime_type = "text/plain";
        थांबा;
    स्थिती CF_UNICODETEXT:
        mime_type = "text/plain;charset=utf-8";
        थांबा;
    स्थिती CF_DIB:
    स्थिती CF_DIBV5:
        mime_type = "image/bmp";
        थांबा;
    पूर्वनिर्धारित:
        जर (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        थांबा;
    }
    जर (mime_type) {
        माप_प्रकार len = SDL_strlen(mime_type) + 1;
        जर (name) {
            SDL_memcpy(name, mime_type, len);
        }
        परत (पूर्णांक)len;
    }
    परत 0;
}

स्थिर अक्षर **GetMimeTypes(पूर्णांक *pnformats)
{
    अक्षर **new_mime_types = रिक्त;

    *pnformats = 0;

    जर (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        पूर्णांक nformats = 0;
        UINT format = 0;
        पूर्णांक formatsSz = 0;
        bool have_image_bmp = false;
        साठी ( ; ; ) {
            format = EnumClipboardFormats(format);
            जर (!format) {
                थांबा;
            }

#ifdef DEBUG_CLIPBOARD
            अक्षर name[128] = { 0 };
            GetClipboardFormatNameA(format, name, आकार(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#endif

            जर (format == CF_DIB || format == CF_DIBV5) {
                जर (have_image_bmp) {
                    // We have already registered this format
                    सुरूठेवा;
                }
                have_image_bmp = true;
            }

            पूर्णांक len = GetClipboardFormatMimeType(format, रिक्त);
            जर (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_AllocateTemporaryMemory((nformats + 1) * आकार(अक्षर *) + formatsSz);
        जर (new_mime_types) {
            format = 0;
            अक्षर *strPtr = (अक्षर *)(new_mime_types + nformats + 1);
            पूर्णांक i = 0;
            साठी ( ; ; ) {
                format = EnumClipboardFormats(format);
                जर (!format) {
                    थांबा;
                }

                जर (format == CF_DIB || format == CF_DIBV5) {
                    जर (have_image_bmp) {
                        // We have already registered this format
                        सुरूठेवा;
                    }
                    have_image_bmp = true;
                }

                पूर्णांक len = GetClipboardFormatMimeType(format, strPtr);
                जर (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = रिक्त;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    परत new_mime_types;
}

शून्य WIN_CheckClipboardUpdate(संरचना SDL_VideoData *data)
{
    DWORD मोजणी = Get_Clipboard_Sequence_संख्या();
    जर (मोजणी != data->clipboard_मोजणी) {
        जर (मोजणी) {
            पूर्णांक nformats = 0;
            अक्षर **new_mime_types = GetMimeTypes(&nformats);
            जर (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        data->clipboard_मोजणी = मोजणी;
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
