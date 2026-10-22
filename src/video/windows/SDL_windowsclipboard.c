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
#समावेश "SDL_internal.h"

#अगर defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#समावेश "SDL_windowsvideo.h"
#समावेश "SDL_windowswindow.h"
#समावेश "../SDL_clipboard_c.h"
#समावेश "../../events/SDL_events_c.h"
#समावेश "../../events/SDL_clipboardevents_c.h"

#घोषणा BFT_BITMAP 0x4d42 // 'BM'

// Assume we can directly read and write BMP fields without byte swapping
SDL_COMPILE_TIME_ASSERT(verify_byte_order, SDL_BYTEORDER == SDL_LIL_ENDIAN);

अटल UINT GetClipboardFormatPNG(व्योम)
{
    अटल UINT format;

    अगर (!format) {
        format = RegisterClipboardFormat(TEXT("PNG"));
    }
    वापस format;
}

अटल BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    स्थिर पूर्णांक MAX_ATTEMPTS = 3;
    पूर्णांक attempt;
    HWND hwnd = शून्य;

    अगर (_this->windows) {
        hwnd = _this->windows->internal->hwnd;
    }
    क्रम (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        अगर (OpenClipboard(hwnd)) {
            वापस TRUE;
        }
        SDL_Delay(10);
    }
    वापस FALSE;
}

अटल व्योम WIN_CloseClipboard(व्योम)
{
    CloseClipboard();
}

अटल HANDLE WIN_ConvertBMPtoDIB(स्थिर व्योम *bmp, माप_प्रकार bmp_आकार, UINT *format)
{
    HANDLE hMem = शून्य;

    अगर (bmp && bmp_आकार > माप(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + माप(BITMAPFILEHEADER));
        माप_प्रकार bih_आकार = pbih->bi_आकार + pbih->biClrUsed * माप(RGBQUAD);
        माप_प्रकार pixels_आकार = pbih->bi_आकार_Image;

        अगर (pbih->bi_आकार >= माप(BITMAPV5HEADER)) {
            *format = CF_DIBV5;
        } अन्यथा {
            *format = CF_DIB;
        }

        अगर (pbfh->bfOffBits >= (माप(BITMAPFILEHEADER) + bih_आकार) &&
            (pbfh->bfOffBits + pixels_आकार) <= bmp_आकार) {
            स्थिर Uint8 *pixels = (स्थिर Uint8 *)bmp + pbfh->bfOffBits;
            माप_प्रकार dib_आकार = bih_आकार + pixels_आकार;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_आकार);
            अगर (hMem) {
                LPVOID dst = GlobalLock(hMem);
                अगर (dst) {
                    SDL_memcpy(dst, pbih, bih_आकार);
                    SDL_memcpy((Uint8 *)dst + bih_आकार, pixels, pixels_आकार);
                    GlobalUnlock(hMem);
                } अन्यथा {
                    WIN_SetError("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = शून्य;
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
    वापस hMem;
}

अटल व्योम *WIN_ConvertDIBtoBMP(HANDLE hMem, माप_प्रकार *आकार)
{
    व्योम *bmp = शून्य;
    माप_प्रकार mem_आकार = Global_आकार(hMem);

    अगर (mem_आकार > माप(BITMAPINFOHEADER)) {
        LPVOID dib = GlobalLock(hMem);
        अगर (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            माप_प्रकार color_table_आकार;
            चयन (pbih->biCompression) {
            हाल BI_RGB:
                अगर (pbih->bi_Bit_गिनती <= 8) {
                    color_table_आकार = माप(RGBQUAD) * (pbih->biClrUsed == 0 ? 1 << pbih->bi_Bit_गिनती : pbih->biClrUsed);
                } अन्यथा {
                    color_table_आकार = 0;
                }
                अवरोध;
            हाल BI_BITFIELDS:
                color_table_आकार = 3 * माप(DWORD);
                अवरोध;
            हाल 6 /* BI_ALPHABITFIELDS */:
                // https://learn.microsoft.com/en-us/previous-versions/windows/embedded/aa452885(v=msdn.10)
                color_table_आकार = 4 * माप(DWORD);
                अवरोध;
            शेष: // FOURCC
                color_table_आकार = माप(RGBQUAD) * pbih->biClrUsed;
            }

            माप_प्रकार bih_आकार = pbih->bi_आकार + color_table_आकार;
            माप_प्रकार dib_आकार = bih_आकार + pbih->bi_आकार_Image;
            अगर (dib_आकार <= mem_आकार) {
                माप_प्रकार bmp_आकार = माप(BITMAPFILEHEADER) + mem_आकार;
                bmp = SDL_malloc(bmp_आकार);
                अगर (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bf_आकार = (DWORD)bmp_आकार;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bfOffBits = (DWORD)(माप(BITMAPFILEHEADER) + pbih->bi_आकार + color_table_आकार);
                    SDL_memcpy((Uint8 *)bmp + माप(BITMAPFILEHEADER), dib, mem_आकार);
                    *आकार = bmp_आकार;
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
    वापस bmp;
}

अटल bool WIN_SetClipboardImage(SDL_VideoDevice *_this, स्थिर अक्षर *mime_type)
{
    UINT format = 0;
    HANDLE hMem = शून्य;
    माप_प्रकार clipboard_तथ्य_आकार;
    स्थिर व्योम *clipboard_तथ्य;
    bool परिणाम = true;

    clipboard_तथ्य = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_तथ्य_आकार);
    अगर (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_तथ्य, clipboard_तथ्य_आकार, &format);
    } अन्यथा अगर (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_तथ्य_आकार);
        अगर (hMem) {
            LPVOID dst = GlobalLock(hMem);
            अगर (dst) {
                SDL_memcpy(dst, clipboard_तथ्य, clipboard_तथ्य_आकार);
                GlobalUnlock(hMem);
            } अन्यथा {
                परिणाम = WIN_SetError("GlobalLock()");
                GlobalFree(hMem);
                hMem = शून्य;
            }
        } अन्यथा {
            परिणाम = SDL_OutOfMemory();
        }
    } अन्यथा {
        परिणाम = SDL_SetError("Unknown image format");
    }
    अगर (hMem) {
        // Save the image to the clipboard
        अगर (!Set_Clipboard_तथ्य(format, hMem)) {
            परिणाम = WIN_SetError("Couldn't set clipboard data");
        }
    } अन्यथा {
        // WIN_ConvertBMPtoDIB() set the error
        परिणाम = false;
    }
    वापस परिणाम;
}

अटल bool WIN_SetClipboardText(SDL_VideoDevice *_this, स्थिर अक्षर *mime_type)
{
    HANDLE hMem;
    माप_प्रकार clipboard_तथ्य_आकार;
    स्थिर व्योम *clipboard_तथ्य;
    bool परिणाम = true;

    clipboard_तथ्य = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_तथ्य_आकार);
    अगर (clipboard_तथ्य && clipboard_तथ्य_आकार > 0) {
        आकार_T i, आकार;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (स्थिर अक्षर *)clipboard_तथ्य, clipboard_तथ्य_आकार);
        अगर (!tstr) {
            वापस SDL_SetError("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        क्रम (आकार = 0, i = 0; tstr[i]; ++i, ++आकार) {
            अगर (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++आकार;
            }
        }
        आकार = (आकार + 1) * माप(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, आकार);
        अगर (hMem) {
            LPWSTR dst = (LPWSTR)GlobalLock(hMem);
            अगर (dst) {
                // Copy the text over, adding carriage returns as necessary
                क्रम (i = 0; tstr[i]; ++i) {
                    अगर (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            अगर (!Set_Clipboard_तथ्य(CF_UNICODETEXT, hMem)) {
                परिणाम = WIN_SetError("Couldn't set clipboard data");
            }
        } अन्यथा {
            परिणाम = SDL_OutOfMemory();
        }
        SDL_free(tstr);
    }
    वापस परिणाम;
}

bool WIN_Set_Clipboard_तथ्य(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    माप_प्रकार i;
    bool परिणाम = true;

    /* I investigated delayed clipboard rendering, and at least with text and image
     * formats you have to use an output window, not SDL_HelperWindow, and the system
     * requests them being rendered immediately, so there isn't any benefit.
     */

    अगर (WIN_OpenClipboard(_this)) {
        EmptyClipboard();

        // Set the clipboard text
        क्रम (i = 0; i < _this->अंक_clipboard_mime_types; ++i) {
            स्थिर अक्षर *mime_type = _this->clipboard_mime_types[i];

            अगर (SDL_IsTextMimeType(mime_type)) {
                अगर (!WIN_SetClipboardText(_this, mime_type)) {
                    परिणाम = false;
                }
                // Only set the first clipboard text
                अवरोध;
            }
        }

        // Set the clipboard image
        क्रम (i = 0; i < _this->अंक_clipboard_mime_types; ++i) {
            स्थिर अक्षर *mime_type = _this->clipboard_mime_types[i];

            अगर (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                अगर (!WIN_SetClipboardImage(_this, mime_type)) {
                    परिणाम = false;
                }
                अवरोध;
            }
        }

        तथ्य->clipboard_गिनती = Get_Clipboard_Sequence_संख्या();
        WIN_CloseClipboard();
    } अन्यथा {
        परिणाम = WIN_SetError("Couldn't open clipboard");
    }
    वापस परिणाम;
}

व्योम *WIN_Get_Clipboard_तथ्य(SDL_VideoDevice *_this, स्थिर अक्षर *mime_type, माप_प्रकार *आकार)
{
    व्योम *तथ्य = शून्य;

    अगर (SDL_IsTextMimeType(mime_type)) {
        अक्षर *text = शून्य;

        अगर (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
            अगर (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = Get_Clipboard_तथ्य(CF_UNICODETEXT);
                अगर (hMem) {
                    str = (LPTSTR)GlobalLock(hMem);
                    अगर (str) {
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
        } अन्यथा अगर (IsClipboardFormatAvailable(CF_TEXT)) {
            अगर (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = Get_Clipboard_तथ्य(CF_TEXT);
                अगर (hMem) {
                    str = (LPCSTR)GlobalLock(hMem);
                    अगर (str) {
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
        अगर (!text) {
            text = SDL_strdup("");
        }
        तथ्य = text;
        *आकार = SDL_strlen(text);

    } अन्यथा अगर (SDL_strcmp(mime_type, "image/bmp") == 0) {
        अगर (IsClipboardFormatAvailable(CF_DIBV5)) {
            अगर (WIN_OpenClipboard(_this)) {
                HANDLE hMem = Get_Clipboard_तथ्य(CF_DIBV5);
                अगर (hMem) {
                    तथ्य = WIN_ConvertDIBtoBMP(hMem, आकार);
                } अन्यथा {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } अन्यथा अगर (IsClipboardFormatAvailable(CF_DIB)) {
            अगर (WIN_OpenClipboard(_this)) {
                HANDLE hMem = Get_Clipboard_तथ्य(CF_DIB);
                अगर (hMem) {
                    तथ्य = WIN_ConvertDIBtoBMP(hMem, आकार);
                } अन्यथा {
                    WIN_SetError("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } अन्यथा अगर (SDL_strcmp(mime_type, "image/png") == 0) {
        अगर (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            अगर (WIN_OpenClipboard(_this)) {
                HANDLE hMem = Get_Clipboard_तथ्य(GetClipboardFormatPNG());
                अगर (hMem) {
                    माप_प्रकार mem_आकार = Global_आकार(hMem);
                    व्योम *mem = GlobalLock(hMem);
                    अगर (mem) {
                        तथ्य = SDL_malloc(mem_आकार);
                        अगर (तथ्य) {
                            SDL_memcpy(तथ्य, mem, mem_आकार);
                            *आकार = mem_आकार;
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
        तथ्य = SDL_Get_Internal_Clipboard_तथ्य(_this, mime_type, आकार);
    }
    वापस तथ्य;
}

bool WIN_Has_Clipboard_तथ्य(SDL_VideoDevice *_this, स्थिर अक्षर *mime_type)
{
    अगर (SDL_IsTextMimeType(mime_type)) {
        अगर (IsClipboardFormatAvailable(CF_UNICODETEXT) || IsClipboardFormatAvailable(CF_TEXT)) {
            वापस true;
        }
    } अन्यथा अगर (SDL_strcmp(mime_type, "image/bmp") == 0) {
        अगर (IsClipboardFormatAvailable(CF_DIBV5) || IsClipboardFormatAvailable(CF_DIB)) {
            वापस true;
        }
    } अन्यथा अगर (SDL_strcmp(mime_type, "image/png") == 0) {
        अगर (IsClipboardFormatAvailable(GetClipboardFormatPNG())) {
            वापस true;
        }
    }
    वापस SDL_Has_Internal_Clipboard_तथ्य(_this, mime_type);
}

अटल पूर्णांक GetClipboardFormatMimeType(UINT format, अक्षर *name)
{
    स्थिर अक्षर *mime_type = शून्य;

    चयन (format) {
    हाल CF_TEXT:
        mime_type = "text/plain";
        अवरोध;
    हाल CF_UNICODETEXT:
        mime_type = "text/plain;charset=utf-8";
        अवरोध;
    हाल CF_DIB:
    हाल CF_DIBV5:
        mime_type = "image/bmp";
        अवरोध;
    शेष:
        अगर (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        अवरोध;
    }
    अगर (mime_type) {
        माप_प्रकार len = SDL_strlen(mime_type) + 1;
        अगर (name) {
            SDL_memcpy(name, mime_type, len);
        }
        वापस (पूर्णांक)len;
    }
    वापस 0;
}

अटल अक्षर **GetMimeTypes(पूर्णांक *pnformats)
{
    अक्षर **new_mime_types = शून्य;

    *pnformats = 0;

    अगर (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        पूर्णांक nformats = 0;
        UINT format = 0;
        पूर्णांक formatsSz = 0;
        bool have_image_bmp = false;
        क्रम ( ; ; ) {
            format = EnumClipboardFormats(format);
            अगर (!format) {
                अवरोध;
            }

#अगर_घोषित DEBUG_CLIPBOARD
            अक्षर name[128] = { 0 };
            GetClipboardFormatNameA(format, name, माप(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#पूर्ण_अगर

            अगर (format == CF_DIB || format == CF_DIBV5) {
                अगर (have_image_bmp) {
                    // We have already registered this format
                    जारी;
                }
                have_image_bmp = true;
            }

            पूर्णांक len = GetClipboardFormatMimeType(format, शून्य);
            अगर (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_AllocateTemporaryMemory((nformats + 1) * माप(अक्षर *) + formatsSz);
        अगर (new_mime_types) {
            format = 0;
            अक्षर *strPtr = (अक्षर *)(new_mime_types + nformats + 1);
            पूर्णांक i = 0;
            क्रम ( ; ; ) {
                format = EnumClipboardFormats(format);
                अगर (!format) {
                    अवरोध;
                }

                अगर (format == CF_DIB || format == CF_DIBV5) {
                    अगर (have_image_bmp) {
                        // We have already registered this format
                        जारी;
                    }
                    have_image_bmp = true;
                }

                पूर्णांक len = GetClipboardFormatMimeType(format, strPtr);
                अगर (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = शून्य;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    वापस new_mime_types;
}

व्योम WIN_CheckClipboardUpdate(काष्ठा SDL_Video_तथ्य *तथ्य)
{
    DWORD गिनती = Get_Clipboard_Sequence_संख्या();
    अगर (गिनती != तथ्य->clipboard_गिनती) {
        अगर (गिनती) {
            पूर्णांक nformats = 0;
            अक्षर **new_mime_types = GetMimeTypes(&nformats);
            अगर (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        तथ्य->clipboard_गिनती = गिनती;
    }
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WINDOWS
