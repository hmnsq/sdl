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

#यदि defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#अन्तर्भाव "SDL_windowsvideo.h"
#अन्तर्भाव "SDL_windowswindow.h"
#अन्तर्भाव "../SDL_clipboard_c.h"
#अन्तर्भाव "../../events/SDL_events_c.h"
#अन्तर्भाव "../../events/SDL_clipboardevents_c.h"

#परिभाषय BFT_BITMAP 0x4d42 // 'BM'

// Assume we can directly read and write BMP fields without byte swapping
SDL_COMPILE_TIME_ASSERT(verify_byte_क्रमः, SDL_BYTEORDER == SDL_LIL_ENDIAN);

स्थिर UINT GetClipboardFormatPNG(शून्य)
{
    स्थिर UINT format;

    यदि (!format) {
        format = पञ्जिकाकोशः_Clipboard_Format(TEXT("PNG"));
    }
    प्रत्यागम format;
}

स्थिर BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    ध्रुव पूर्णाङ्क MAX_ATTEMPTS = 3;
    पूर्णाङ्क attempt;
    HWND hwnd = रिक्त;

    यदि (_this->windows) {
        hwnd = _this->windows->आन्तरिकम्->hwnd;
    }
    प्रति (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        यदि (OpenClipboard(hwnd)) {
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

स्थिर HANDLE WIN_ConvertBMPtoDIB(ध्रुव शून्य *bmp, size_t bmp_आकार, UINT *format)
{
    HANDLE hMem = रिक्त;

    यदि (bmp && bmp_आकार > परिमाण(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + परिमाण(BITMAPFILEHEADER));
        size_t bih_आकार = pbih->bi_आकार + pbih->bi_Clr_प्रयुक्तम् * परिमाण(RGBQUAD);
        size_t pixels_आकार = pbih->bi_आकार_Image;

        यदि (pbih->bi_आकार >= परिमाण(BITMAPV5_शीर्षकम्)) {
            *format = CF_DIBV5;
        } अन्यथा {
            *format = CF_DIB;
        }

        यदि (pbfh->bf_Off_द्वयङ्काः >= (परिमाण(BITMAPFILEHEADER) + bih_आकार) &&
            (pbfh->bf_Off_द्वयङ्काः + pixels_आकार) <= bmp_आकार) {
            ध्रुव Uint8 *pixels = (ध्रुव Uint8 *)bmp + pbfh->bf_Off_द्वयङ्काः;
            size_t dib_आकार = bih_आकार + pixels_आकार;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_आकार);
            यदि (hMem) {
                LPVOID dst = Global_तालकम्(hMem);
                यदि (dst) {
                    SDL_memcpy(dst, pbih, bih_आकार);
                    SDL_memcpy((Uint8 *)dst + bih_आकार, pixels, pixels_आकार);
                    GlobalUnlock(hMem);
                } अन्यथा {
                    WIN_समुच्चयः_Error("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = रिक्त;
                }
            } अन्यथा {
                SDL_बहिर्गमनम्_सम्बन्धि_स्मृतिः();
            }
        } अन्यथा {
            SDL_समुच्चयः_Error("Invalid BMP data");
        }
    } अन्यथा {
        SDL_समुच्चयः_Error("Invalid BMP data");
    }
    प्रत्यागम hMem;
}

स्थिर शून्य *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *आकार)
{
    शून्य *bmp = रिक्त;
    size_t mem_आकार = Global_आकार(hMem);

    यदि (mem_आकार > परिमाण(BITMAPINFOHEADER)) {
        LPVOID dib = Global_तालकम्(hMem);
        यदि (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_सारणी_आकार;
            विकल्प (pbih->biCompression) {
            पक्ष BI_RGB:
                यदि (pbih->bi_Bit_गणनम् <= 8) {
                    color_सारणी_आकार = परिमाण(RGBQUAD) * (pbih->bi_Clr_प्रयुक्तम् == 0 ? 1 << pbih->bi_Bit_गणनम् : pbih->bi_Clr_प्रयुक्तम्);
                } अन्यथा {
                    color_सारणी_आकार = 0;
                }
                भङ्ग;
            पक्ष BI_BITFIELDS:
                color_सारणी_आकार = 3 * परिमाण(DWORD);
                भङ्ग;
            पक्ष 6 /* BI_ALPHABITFIELDS */:
                // https://learn.microsoft.com/en-us/previous-versions/windows/embedded/aa452885(v=msdn.10)
                color_सारणी_आकार = 4 * परिमाण(DWORD);
                भङ्ग;
            स्वभाव: // FOURCC
                color_सारणी_आकार = परिमाण(RGBQUAD) * pbih->bi_Clr_प्रयुक्तम्;
            }

            size_t bih_आकार = pbih->bi_आकार + color_सारणी_आकार;
            size_t dib_आकार = bih_आकार + pbih->bi_आकार_Image;
            यदि (dib_आकार <= mem_आकार) {
                size_t bmp_आकार = परिमाण(BITMAPFILEHEADER) + mem_आकार;
                bmp = SDL_malloc(bmp_आकार);
                यदि (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bf_आकार = (DWORD)bmp_आकार;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bf_Off_द्वयङ्काः = (DWORD)(परिमाण(BITMAPFILEHEADER) + pbih->bi_आकार + color_सारणी_आकार);
                    SDL_memcpy((Uint8 *)bmp + परिमाण(BITMAPFILEHEADER), dib, mem_आकार);
                    *आकार = bmp_आकार;
                }
            } अन्यथा {
                SDL_समुच्चयः_Error("Invalid BMP data");
            }
            GlobalUnlock(hMem);
        } अन्यथा {
            WIN_समुच्चयः_Error("GlobalLock()");
        }
    } अन्यथा {
        SDL_समुच्चयः_Error("Invalid BMP data");
    }
    प्रत्यागम bmp;
}

स्थिर bool WIN_समुच्चयः_Clipboard_Image(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type)
{
    UINT format = 0;
    HANDLE hMem = रिक्त;
    size_t clipboard_दत्त_आकार;
    ध्रुव शून्य *clipboard_दत्त;
    bool परिणाम = true;

    clipboard_दत्त = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_दत्त_आकार);
    यदि (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_दत्त, clipboard_दत्त_आकार, &format);
    } अन्यथा यदि (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_दत्त_आकार);
        यदि (hMem) {
            LPVOID dst = Global_तालकम्(hMem);
            यदि (dst) {
                SDL_memcpy(dst, clipboard_दत्त, clipboard_दत्त_आकार);
                GlobalUnlock(hMem);
            } अन्यथा {
                परिणाम = WIN_समुच्चयः_Error("GlobalLock()");
                GlobalFree(hMem);
                hMem = रिक्त;
            }
        } अन्यथा {
            परिणाम = SDL_बहिर्गमनम्_सम्बन्धि_स्मृतिः();
        }
    } अन्यथा {
        परिणाम = SDL_समुच्चयः_Error("Unknown image format");
    }
    यदि (hMem) {
        // Save the image to the clipboard
        यदि (!समुच्चयः_Clipboard_दत्त(format, hMem)) {
            परिणाम = WIN_समुच्चयः_Error("Couldn't set clipboard data");
        }
    } अन्यथा {
        // WIN_ConvertBMPtoDIB() set the error
        परिणाम = false;
    }
    प्रत्यागम परिणाम;
}

स्थिर bool WIN_समुच्चयः_Clipboard_Text(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type)
{
    HANDLE hMem;
    size_t clipboard_दत्त_आकार;
    ध्रुव शून्य *clipboard_दत्त;
    bool परिणाम = true;

    clipboard_दत्त = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_दत्त_आकार);
    यदि (clipboard_दत्त && clipboard_दत्त_आकार > 0) {
        आकार_T i, आकार;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (ध्रुव वर्ण *)clipboard_दत्त, clipboard_दत्त_आकार);
        यदि (!tstr) {
            प्रत्यागम SDL_समुच्चयः_Error("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        प्रति (आकार = 0, i = 0; tstr[i]; ++i, ++आकार) {
            यदि (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++आकार;
            }
        }
        आकार = (आकार + 1) * परिमाण(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, आकार);
        यदि (hMem) {
            LPWSTR dst = (LPWSTR)Global_तालकम्(hMem);
            यदि (dst) {
                // Copy the text over, adding carriage returns as necessary
                प्रति (i = 0; tstr[i]; ++i) {
                    यदि (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            यदि (!समुच्चयः_Clipboard_दत्त(CF_UNICODETEXT, hMem)) {
                परिणाम = WIN_समुच्चयः_Error("Couldn't set clipboard data");
            }
        } अन्यथा {
            परिणाम = SDL_बहिर्गमनम्_सम्बन्धि_स्मृतिः();
        }
        SDL_free(tstr);
    }
    प्रत्यागम परिणाम;
}

bool WIN_समुच्चयः_Clipboard_दत्त(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    size_t i;
    bool परिणाम = true;

    /* I investigated delayed clipboard rendering, and at least with text and image
     * formats you have to use an output window, not SDL_HelperWindow, and the system
     * requests them being rendered immediately, so there isn't any benefit.
     */

    यदि (WIN_OpenClipboard(_this)) {
        रिक्तानि_Clipboard();

        // Set the clipboard text
        प्रति (i = 0; i < _this->अङ्कः_clipboard_mime_types; ++i) {
            ध्रुव वर्ण *mime_type = _this->clipboard_mime_types[i];

            यदि (SDL_IsTextMimeType(mime_type)) {
                यदि (!WIN_समुच्चयः_Clipboard_Text(_this, mime_type)) {
                    परिणाम = false;
                }
                // Only set the first clipboard text
                भङ्ग;
            }
        }

        // Set the clipboard image
        प्रति (i = 0; i < _this->अङ्कः_clipboard_mime_types; ++i) {
            ध्रुव वर्ण *mime_type = _this->clipboard_mime_types[i];

            यदि (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                यदि (!WIN_समुच्चयः_Clipboard_Image(_this, mime_type)) {
                    परिणाम = false;
                }
                भङ्ग;
            }
        }

        दत्त->clipboard_गणनम् = Get_Clipboard_Sequence_सङ्ख्या();
        WIN_CloseClipboard();
    } अन्यथा {
        परिणाम = WIN_समुच्चयः_Error("Couldn't open clipboard");
    }
    प्रत्यागम परिणाम;
}

शून्य *WIN_Get_Clipboard_दत्त(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type, size_t *आकार)
{
    शून्य *दत्त = रिक्त;

    यदि (SDL_IsTextMimeType(mime_type)) {
        वर्ण *text = रिक्त;

        यदि (Is_Clipboard_Format_उपलब्धम्(CF_UNICODETEXT)) {
            यदि (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = Get_Clipboard_दत्त(CF_UNICODETEXT);
                यदि (hMem) {
                    str = (LPTSTR)Global_तालकम्(hMem);
                    यदि (str) {
                        text = WIN_String_गन्तव्यम्_UTF8_W(str);
                        GlobalUnlock(hMem);
                    } अन्यथा {
                        WIN_समुच्चयः_Error("Couldn't lock clipboard data");
                    }
                } अन्यथा {
                    WIN_समुच्चयः_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } अन्यथा यदि (Is_Clipboard_Format_उपलब्धम्(CF_TEXT)) {
            यदि (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = Get_Clipboard_दत्त(CF_TEXT);
                यदि (hMem) {
                    str = (LPCSTR)Global_तालकम्(hMem);
                    यदि (str) {
                        text = SDL_strdup(str);
                        GlobalUnlock(hMem);
                    } अन्यथा {
                        WIN_समुच्चयः_Error("Couldn't lock clipboard data");
                    }
                } अन्यथा {
                    WIN_समुच्चयः_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }
        यदि (!text) {
            text = SDL_strdup("");
        }
        दत्त = text;
        *आकार = SDL_strlen(text);

    } अन्यथा यदि (SDL_strcmp(mime_type, "image/bmp") == 0) {
        यदि (Is_Clipboard_Format_उपलब्धम्(CF_DIBV5)) {
            यदि (WIN_OpenClipboard(_this)) {
                HANDLE hMem = Get_Clipboard_दत्त(CF_DIBV5);
                यदि (hMem) {
                    दत्त = WIN_ConvertDIBtoBMP(hMem, आकार);
                } अन्यथा {
                    WIN_समुच्चयः_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } अन्यथा यदि (Is_Clipboard_Format_उपलब्धम्(CF_DIB)) {
            यदि (WIN_OpenClipboard(_this)) {
                HANDLE hMem = Get_Clipboard_दत्त(CF_DIB);
                यदि (hMem) {
                    दत्त = WIN_ConvertDIBtoBMP(hMem, आकार);
                } अन्यथा {
                    WIN_समुच्चयः_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } अन्यथा यदि (SDL_strcmp(mime_type, "image/png") == 0) {
        यदि (Is_Clipboard_Format_उपलब्धम्(GetClipboardFormatPNG())) {
            यदि (WIN_OpenClipboard(_this)) {
                HANDLE hMem = Get_Clipboard_दत्त(GetClipboardFormatPNG());
                यदि (hMem) {
                    size_t mem_आकार = Global_आकार(hMem);
                    शून्य *mem = Global_तालकम्(hMem);
                    यदि (mem) {
                        दत्त = SDL_malloc(mem_आकार);
                        यदि (दत्त) {
                            SDL_memcpy(दत्त, mem, mem_आकार);
                            *आकार = mem_आकार;
                        }
                        GlobalUnlock(hMem);
                    } अन्यथा {
                        WIN_समुच्चयः_Error("Couldn't lock clipboard data");
                    }
                } अन्यथा {
                    WIN_समुच्चयः_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } अन्यथा {
        दत्त = SDL_Get_आन्तरिकम्_Clipboard_दत्त(_this, mime_type, आकार);
    }
    प्रत्यागम दत्त;
}

bool WIN_Has_Clipboard_दत्त(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type)
{
    यदि (SDL_IsTextMimeType(mime_type)) {
        यदि (Is_Clipboard_Format_उपलब्धम्(CF_UNICODETEXT) || Is_Clipboard_Format_उपलब्धम्(CF_TEXT)) {
            प्रत्यागम true;
        }
    } अन्यथा यदि (SDL_strcmp(mime_type, "image/bmp") == 0) {
        यदि (Is_Clipboard_Format_उपलब्धम्(CF_DIBV5) || Is_Clipboard_Format_उपलब्धम्(CF_DIB)) {
            प्रत्यागम true;
        }
    } अन्यथा यदि (SDL_strcmp(mime_type, "image/png") == 0) {
        यदि (Is_Clipboard_Format_उपलब्धम्(GetClipboardFormatPNG())) {
            प्रत्यागम true;
        }
    }
    प्रत्यागम SDL_Has_आन्तरिकम्_Clipboard_दत्त(_this, mime_type);
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
        यदि (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        भङ्ग;
    }
    यदि (mime_type) {
        size_t len = SDL_strlen(mime_type) + 1;
        यदि (name) {
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

    यदि (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        पूर्णाङ्क nformats = 0;
        UINT format = 0;
        पूर्णाङ्क formatsSz = 0;
        bool have_image_bmp = false;
        प्रति ( ; ; ) {
            format = EnumClipboardFormats(format);
            यदि (!format) {
                भङ्ग;
            }

#यदि_परिभाषितम् DEBUG_CLIPBOARD
            वर्ण name[128] = { 0 };
            GetClipboardFormatNameA(format, name, परिमाण(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#यदि_अन्तः

            यदि (format == CF_DIB || format == CF_DIBV5) {
                यदि (have_image_bmp) {
                    // We have already registered this format
                    अनुवर्त;
                }
                have_image_bmp = true;
            }

            पूर्णाङ्क len = GetClipboardFormatMimeType(format, रिक्त);
            यदि (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_Allocate_Temporary_स्मृतिः((nformats + 1) * परिमाण(वर्ण *) + formatsSz);
        यदि (new_mime_types) {
            format = 0;
            वर्ण *strPtr = (वर्ण *)(new_mime_types + nformats + 1);
            पूर्णाङ्क i = 0;
            प्रति ( ; ; ) {
                format = EnumClipboardFormats(format);
                यदि (!format) {
                    भङ्ग;
                }

                यदि (format == CF_DIB || format == CF_DIBV5) {
                    यदि (have_image_bmp) {
                        // We have already registered this format
                        अनुवर्त;
                    }
                    have_image_bmp = true;
                }

                पूर्णाङ्क len = GetClipboardFormatMimeType(format, strPtr);
                यदि (len > 0) {
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

शून्य WIN_CheckClipboardUpdate(संरचना SDL_Video_दत्त *दत्त)
{
    DWORD गणनम् = Get_Clipboard_Sequence_सङ्ख्या();
    यदि (गणनम् != दत्त->clipboard_गणनम्) {
        यदि (गणनम्) {
            पूर्णाङ्क nformats = 0;
            वर्ण **new_mime_types = GetMimeTypes(&nformats);
            यदि (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        दत्त->clipboard_गणनम् = गणनम्;
    }
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_WINDOWS
