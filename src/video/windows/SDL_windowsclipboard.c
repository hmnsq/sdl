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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowswindow.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_clipboard_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_clipboardevents_c.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BFT_BITMAP 0x4d42 // 'BM'

// Assume we can directly read and write BMP fields without byte swapping
SDL_COMPILE_ਸਮਾਂ_ASSERT(verify_byte_ਕ੍ਰਮ, SDL_BYTEORDER == SDL_LIL_ENDIAN);

ਸਥਿਰ UINT GetClipboardFormatPNG(ਖਾਲੀ)
{
    ਸਥਿਰ UINT format;

    ਜੇ (!format) {
        format = ਰਜਿਸਟਰ_Clipboard_Format(ਪਾਠ_2("PNG"));
    }
    ਵਾਪਸ format;
}

ਸਥਿਰ BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    ਅਚਲ ਪੂਰਨ MAX_ATTEMPTS = 3;
    ਪੂਰਨ attempt;
    HWND hwnd = ਨਿਰਾ;

    ਜੇ (_this->windows) {
        hwnd = _this->windows->ਅੰਦਰੂਨੀ->hwnd;
    }
    ਲਈ (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        ਜੇ (OpenClipboard(hwnd)) {
            ਵਾਪਸ TRUE;
        }
        SDL_Delay(10);
    }
    ਵਾਪਸ FALSE;
}

ਸਥਿਰ ਖਾਲੀ WIN_CloseClipboard(ਖਾਲੀ)
{
    CloseClipboard();
}

ਸਥਿਰ HANDLE WIN_ConvertBMPtoDIB(ਅਚਲ ਖਾਲੀ *bmp, size_t bmp_ਮਾਪ, UINT *format)
{
    HANDLE hMem = ਨਿਰਾ;

    ਜੇ (bmp && bmp_ਮਾਪ > ਆਕਾਰ(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + ਆਕਾਰ(BITMAPFILEHEADER));
        size_t bih_ਮਾਪ = pbih->bi_ਮਾਪ + pbih->bi_Clr_ਵਰਤਿਆ * ਆਕਾਰ(RGBQUAD);
        size_t pixels_ਮਾਪ = pbih->bi_ਮਾਪ_Image;

        ਜੇ (pbih->bi_ਮਾਪ >= ਆਕਾਰ(BITMAPV5_ਸਿਰਲੇਖ)) {
            *format = CF_DIBV5;
        } ਨਹੀਂਤਾਂ {
            *format = CF_DIB;
        }

        ਜੇ (pbfh->bf_Off_ਬਿੱਟ >= (ਆਕਾਰ(BITMAPFILEHEADER) + bih_ਮਾਪ) &&
            (pbfh->bf_Off_ਬਿੱਟ + pixels_ਮਾਪ) <= bmp_ਮਾਪ) {
            ਅਚਲ Uint8 *pixels = (ਅਚਲ Uint8 *)bmp + pbfh->bf_Off_ਬਿੱਟ;
            size_t dib_ਮਾਪ = bih_ਮਾਪ + pixels_ਮਾਪ;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_ਮਾਪ);
            ਜੇ (hMem) {
                LPVOID dst = Global_ਤਾਲਾ(hMem);
                ਜੇ (dst) {
                    SDL_memcpy(dst, pbih, bih_ਮਾਪ);
                    SDL_memcpy((Uint8 *)dst + bih_ਮਾਪ, pixels, pixels_ਮਾਪ);
                    GlobalUnlock(hMem);
                } ਨਹੀਂਤਾਂ {
                    WIN_ਸੈੱਟ_Error("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = ਨਿਰਾ;
                }
            } ਨਹੀਂਤਾਂ {
                SDL_ਬਾਹਰਲਾ_ਦਾ_ਸਮ੍ਰਿਤੀ();
            }
        } ਨਹੀਂਤਾਂ {
            SDL_ਸੈੱਟ_Error("Invalid BMP data");
        }
    } ਨਹੀਂਤਾਂ {
        SDL_ਸੈੱਟ_Error("Invalid BMP data");
    }
    ਵਾਪਸ hMem;
}

ਸਥਿਰ ਖਾਲੀ *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *ਮਾਪ)
{
    ਖਾਲੀ *bmp = ਨਿਰਾ;
    size_t mem_ਮਾਪ = Global_ਮਾਪ(hMem);

    ਜੇ (mem_ਮਾਪ > ਆਕਾਰ(BITMAPINFOHEADER)) {
        LPVOID dib = Global_ਤਾਲਾ(hMem);
        ਜੇ (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_ਸਾਰਣੀ_ਮਾਪ;
            ਚੋਣ (pbih->biCompression) {
            ਹਾਲਤ BI_RGB:
                ਜੇ (pbih->bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ <= 8) {
                    color_ਸਾਰਣੀ_ਮਾਪ = ਆਕਾਰ(RGBQUAD) * (pbih->bi_Clr_ਵਰਤਿਆ == 0 ? 1 << pbih->bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ : pbih->bi_Clr_ਵਰਤਿਆ);
                } ਨਹੀਂਤਾਂ {
                    color_ਸਾਰਣੀ_ਮਾਪ = 0;
                }
                ਰੋਕੋ;
            ਹਾਲਤ BI_BITFIELDS:
                color_ਸਾਰਣੀ_ਮਾਪ = 3 * ਆਕਾਰ(DWORD);
                ਰੋਕੋ;
            ਹਾਲਤ 6 /* BI_ALPHABITFIELDS */:
                // https://learn.microsoft.com/en-us/previous-versions/windows/embedded/aa452885(v=msdn.10)
                color_ਸਾਰਣੀ_ਮਾਪ = 4 * ਆਕਾਰ(DWORD);
                ਰੋਕੋ;
            ਮੂਲ: // FOURCC
                color_ਸਾਰਣੀ_ਮਾਪ = ਆਕਾਰ(RGBQUAD) * pbih->bi_Clr_ਵਰਤਿਆ;
            }

            size_t bih_ਮਾਪ = pbih->bi_ਮਾਪ + color_ਸਾਰਣੀ_ਮਾਪ;
            size_t dib_ਮਾਪ = bih_ਮਾਪ + pbih->bi_ਮਾਪ_Image;
            ਜੇ (dib_ਮਾਪ <= mem_ਮਾਪ) {
                size_t bmp_ਮਾਪ = ਆਕਾਰ(BITMAPFILEHEADER) + mem_ਮਾਪ;
                bmp = SDL_malloc(bmp_ਮਾਪ);
                ਜੇ (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bf_ਮਾਪ = (DWORD)bmp_ਮਾਪ;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bf_Off_ਬਿੱਟ = (DWORD)(ਆਕਾਰ(BITMAPFILEHEADER) + pbih->bi_ਮਾਪ + color_ਸਾਰਣੀ_ਮਾਪ);
                    SDL_memcpy((Uint8 *)bmp + ਆਕਾਰ(BITMAPFILEHEADER), dib, mem_ਮਾਪ);
                    *ਮਾਪ = bmp_ਮਾਪ;
                }
            } ਨਹੀਂਤਾਂ {
                SDL_ਸੈੱਟ_Error("Invalid BMP data");
            }
            GlobalUnlock(hMem);
        } ਨਹੀਂਤਾਂ {
            WIN_ਸੈੱਟ_Error("GlobalLock()");
        }
    } ਨਹੀਂਤਾਂ {
        SDL_ਸੈੱਟ_Error("Invalid BMP data");
    }
    ਵਾਪਸ bmp;
}

ਸਥਿਰ bool WIN_ਸੈੱਟ_Clipboard_Image(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *mime_type)
{
    UINT format = 0;
    HANDLE hMem = ਨਿਰਾ;
    size_t clipboard_ਅੰਕੜੇ_ਮਾਪ;
    ਅਚਲ ਖਾਲੀ *clipboard_ਅੰਕੜੇ;
    bool ਨਤੀਜਾ = true;

    clipboard_ਅੰਕੜੇ = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_ਅੰਕੜੇ_ਮਾਪ);
    ਜੇ (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_ਅੰਕੜੇ, clipboard_ਅੰਕੜੇ_ਮਾਪ, &format);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_ਅੰਕੜੇ_ਮਾਪ);
        ਜੇ (hMem) {
            LPVOID dst = Global_ਤਾਲਾ(hMem);
            ਜੇ (dst) {
                SDL_memcpy(dst, clipboard_ਅੰਕੜੇ, clipboard_ਅੰਕੜੇ_ਮਾਪ);
                GlobalUnlock(hMem);
            } ਨਹੀਂਤਾਂ {
                ਨਤੀਜਾ = WIN_ਸੈੱਟ_Error("GlobalLock()");
                GlobalFree(hMem);
                hMem = ਨਿਰਾ;
            }
        } ਨਹੀਂਤਾਂ {
            ਨਤੀਜਾ = SDL_ਬਾਹਰਲਾ_ਦਾ_ਸਮ੍ਰਿਤੀ();
        }
    } ਨਹੀਂਤਾਂ {
        ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("Unknown image format");
    }
    ਜੇ (hMem) {
        // Save the image to the clipboard
        ਜੇ (!ਸੈੱਟ_Clipboard_ਅੰਕੜੇ(format, hMem)) {
            ਨਤੀਜਾ = WIN_ਸੈੱਟ_Error("Couldn't set clipboard data");
        }
    } ਨਹੀਂਤਾਂ {
        // WIN_ConvertBMPtoDIB() set the error
        ਨਤੀਜਾ = false;
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

ਸਥਿਰ bool WIN_ਸੈੱਟ_Clipboard_ਪਾਠ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *mime_type)
{
    HANDLE hMem;
    size_t clipboard_ਅੰਕੜੇ_ਮਾਪ;
    ਅਚਲ ਖਾਲੀ *clipboard_ਅੰਕੜੇ;
    bool ਨਤੀਜਾ = true;

    clipboard_ਅੰਕੜੇ = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_ਅੰਕੜੇ_ਮਾਪ);
    ਜੇ (clipboard_ਅੰਕੜੇ && clipboard_ਅੰਕੜੇ_ਮਾਪ > 0) {
        ਮਾਪ_T i, ਮਾਪ;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (ਅਚਲ ਅੱਖਰ *)clipboard_ਅੰਕੜੇ, clipboard_ਅੰਕੜੇ_ਮਾਪ);
        ਜੇ (!tstr) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        ਲਈ (ਮਾਪ = 0, i = 0; tstr[i]; ++i, ++ਮਾਪ) {
            ਜੇ (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++ਮਾਪ;
            }
        }
        ਮਾਪ = (ਮਾਪ + 1) * ਆਕਾਰ(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, ਮਾਪ);
        ਜੇ (hMem) {
            LPWSTR dst = (LPWSTR)Global_ਤਾਲਾ(hMem);
            ਜੇ (dst) {
                // Copy the text over, adding carriage returns as necessary
                ਲਈ (i = 0; tstr[i]; ++i) {
                    ਜੇ (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            ਜੇ (!ਸੈੱਟ_Clipboard_ਅੰਕੜੇ(CF_UNICODETEXT, hMem)) {
                ਨਤੀਜਾ = WIN_ਸੈੱਟ_Error("Couldn't set clipboard data");
            }
        } ਨਹੀਂਤਾਂ {
            ਨਤੀਜਾ = SDL_ਬਾਹਰਲਾ_ਦਾ_ਸਮ੍ਰਿਤੀ();
        }
        SDL_free(tstr);
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

bool WIN_ਸੈੱਟ_Clipboard_ਅੰਕੜੇ(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    size_t i;
    bool ਨਤੀਜਾ = true;

    /* I investigated delayed clipboard rendering, and at least with text and image
     * formats you have to use an output window, not SDL_HelperWindow, and the system
     * requests them being rendered immediately, so there isn't any benefit.
     */

    ਜੇ (WIN_OpenClipboard(_this)) {
        ਖਾਲੀ_ਥਾਵਾਂ_Clipboard();

        // Set the clipboard text
        ਲਈ (i = 0; i < _this->ਅੰਕ_clipboard_mime_types; ++i) {
            ਅਚਲ ਅੱਖਰ *mime_type = _this->clipboard_mime_types[i];

            ਜੇ (SDL_Is_ਪਾਠ_Mime_Type(mime_type)) {
                ਜੇ (!WIN_ਸੈੱਟ_Clipboard_ਪਾਠ(_this, mime_type)) {
                    ਨਤੀਜਾ = false;
                }
                // Only set the first clipboard text
                ਰੋਕੋ;
            }
        }

        // Set the clipboard image
        ਲਈ (i = 0; i < _this->ਅੰਕ_clipboard_mime_types; ++i) {
            ਅਚਲ ਅੱਖਰ *mime_type = _this->clipboard_mime_types[i];

            ਜੇ (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                ਜੇ (!WIN_ਸੈੱਟ_Clipboard_Image(_this, mime_type)) {
                    ਨਤੀਜਾ = false;
                }
                ਰੋਕੋ;
            }
        }

        ਅੰਕੜੇ->clipboard_ਗਿਣਤੀ = Get_Clipboard_Sequence_ਸੰਖਿਆ();
        WIN_CloseClipboard();
    } ਨਹੀਂਤਾਂ {
        ਨਤੀਜਾ = WIN_ਸੈੱਟ_Error("Couldn't open clipboard");
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

ਖਾਲੀ *WIN_Get_Clipboard_ਅੰਕੜੇ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *mime_type, size_t *ਮਾਪ)
{
    ਖਾਲੀ *ਅੰਕੜੇ = ਨਿਰਾ;

    ਜੇ (SDL_Is_ਪਾਠ_Mime_Type(mime_type)) {
        ਅੱਖਰ *ਪਾਠ = ਨਿਰਾ;

        ਜੇ (Is_Clipboard_Format_ਉਪਲਬਧ(CF_UNICODETEXT)) {
            ਜੇ (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = Get_Clipboard_ਅੰਕੜੇ(CF_UNICODETEXT);
                ਜੇ (hMem) {
                    str = (LPTSTR)Global_ਤਾਲਾ(hMem);
                    ਜੇ (str) {
                        ਪਾਠ = WIN_String_ਮੰਜ਼ਿਲ_UTF8_W(str);
                        GlobalUnlock(hMem);
                    } ਨਹੀਂਤਾਂ {
                        WIN_ਸੈੱਟ_Error("Couldn't lock clipboard data");
                    }
                } ਨਹੀਂਤਾਂ {
                    WIN_ਸੈੱਟ_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } ਨਹੀਂਤਾਂ ਜੇ (Is_Clipboard_Format_ਉਪਲਬਧ(CF_ਪਾਠ)) {
            ਜੇ (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = Get_Clipboard_ਅੰਕੜੇ(CF_ਪਾਠ);
                ਜੇ (hMem) {
                    str = (LPCSTR)Global_ਤਾਲਾ(hMem);
                    ਜੇ (str) {
                        ਪਾਠ = SDL_strdup(str);
                        GlobalUnlock(hMem);
                    } ਨਹੀਂਤਾਂ {
                        WIN_ਸੈੱਟ_Error("Couldn't lock clipboard data");
                    }
                } ਨਹੀਂਤਾਂ {
                    WIN_ਸੈੱਟ_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }
        ਜੇ (!ਪਾਠ) {
            ਪਾਠ = SDL_strdup("");
        }
        ਅੰਕੜੇ = ਪਾਠ;
        *ਮਾਪ = SDL_strlen(ਪਾਠ);

    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(mime_type, "image/bmp") == 0) {
        ਜੇ (Is_Clipboard_Format_ਉਪਲਬਧ(CF_DIBV5)) {
            ਜੇ (WIN_OpenClipboard(_this)) {
                HANDLE hMem = Get_Clipboard_ਅੰਕੜੇ(CF_DIBV5);
                ਜੇ (hMem) {
                    ਅੰਕੜੇ = WIN_ConvertDIBtoBMP(hMem, ਮਾਪ);
                } ਨਹੀਂਤਾਂ {
                    WIN_ਸੈੱਟ_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } ਨਹੀਂਤਾਂ ਜੇ (Is_Clipboard_Format_ਉਪਲਬਧ(CF_DIB)) {
            ਜੇ (WIN_OpenClipboard(_this)) {
                HANDLE hMem = Get_Clipboard_ਅੰਕੜੇ(CF_DIB);
                ਜੇ (hMem) {
                    ਅੰਕੜੇ = WIN_ConvertDIBtoBMP(hMem, ਮਾਪ);
                } ਨਹੀਂਤਾਂ {
                    WIN_ਸੈੱਟ_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(mime_type, "image/png") == 0) {
        ਜੇ (Is_Clipboard_Format_ਉਪਲਬਧ(GetClipboardFormatPNG())) {
            ਜੇ (WIN_OpenClipboard(_this)) {
                HANDLE hMem = Get_Clipboard_ਅੰਕੜੇ(GetClipboardFormatPNG());
                ਜੇ (hMem) {
                    size_t mem_ਮਾਪ = Global_ਮਾਪ(hMem);
                    ਖਾਲੀ *mem = Global_ਤਾਲਾ(hMem);
                    ਜੇ (mem) {
                        ਅੰਕੜੇ = SDL_malloc(mem_ਮਾਪ);
                        ਜੇ (ਅੰਕੜੇ) {
                            SDL_memcpy(ਅੰਕੜੇ, mem, mem_ਮਾਪ);
                            *ਮਾਪ = mem_ਮਾਪ;
                        }
                        GlobalUnlock(hMem);
                    } ਨਹੀਂਤਾਂ {
                        WIN_ਸੈੱਟ_Error("Couldn't lock clipboard data");
                    }
                } ਨਹੀਂਤਾਂ {
                    WIN_ਸੈੱਟ_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } ਨਹੀਂਤਾਂ {
        ਅੰਕੜੇ = SDL_Get_ਅੰਦਰੂਨੀ_Clipboard_ਅੰਕੜੇ(_this, mime_type, ਮਾਪ);
    }
    ਵਾਪਸ ਅੰਕੜੇ;
}

bool WIN_Has_Clipboard_ਅੰਕੜੇ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *mime_type)
{
    ਜੇ (SDL_Is_ਪਾਠ_Mime_Type(mime_type)) {
        ਜੇ (Is_Clipboard_Format_ਉਪਲਬਧ(CF_UNICODETEXT) || Is_Clipboard_Format_ਉਪਲਬਧ(CF_ਪਾਠ)) {
            ਵਾਪਸ true;
        }
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(mime_type, "image/bmp") == 0) {
        ਜੇ (Is_Clipboard_Format_ਉਪਲਬਧ(CF_DIBV5) || Is_Clipboard_Format_ਉਪਲਬਧ(CF_DIB)) {
            ਵਾਪਸ true;
        }
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(mime_type, "image/png") == 0) {
        ਜੇ (Is_Clipboard_Format_ਉਪਲਬਧ(GetClipboardFormatPNG())) {
            ਵਾਪਸ true;
        }
    }
    ਵਾਪਸ SDL_Has_ਅੰਦਰੂਨੀ_Clipboard_ਅੰਕੜੇ(_this, mime_type);
}

ਸਥਿਰ ਪੂਰਨ GetClipboardFormatMimeType(UINT format, ਅੱਖਰ *name)
{
    ਅਚਲ ਅੱਖਰ *mime_type = ਨਿਰਾ;

    ਚੋਣ (format) {
    ਹਾਲਤ CF_ਪਾਠ:
        mime_type = "text/plain";
        ਰੋਕੋ;
    ਹਾਲਤ CF_UNICODETEXT:
        mime_type = "text/plain;charset=utf-8";
        ਰੋਕੋ;
    ਹਾਲਤ CF_DIB:
    ਹਾਲਤ CF_DIBV5:
        mime_type = "image/bmp";
        ਰੋਕੋ;
    ਮੂਲ:
        ਜੇ (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        ਰੋਕੋ;
    }
    ਜੇ (mime_type) {
        size_t len = SDL_strlen(mime_type) + 1;
        ਜੇ (name) {
            SDL_memcpy(name, mime_type, len);
        }
        ਵਾਪਸ (ਪੂਰਨ)len;
    }
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਅੱਖਰ **GetMimeTypes(ਪੂਰਨ *pnformats)
{
    ਅੱਖਰ **new_mime_types = ਨਿਰਾ;

    *pnformats = 0;

    ਜੇ (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        ਪੂਰਨ nformats = 0;
        UINT format = 0;
        ਪੂਰਨ formatsSz = 0;
        bool have_image_bmp = false;
        ਲਈ ( ; ; ) {
            format = EnumClipboardFormats(format);
            ਜੇ (!format) {
                ਰੋਕੋ;
            }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_CLIPBOARD
            ਅੱਖਰ name[128] = { 0 };
            GetClipboardFormatNameA(format, name, ਆਕਾਰ(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#ਜੇ_ਅੰਤ

            ਜੇ (format == CF_DIB || format == CF_DIBV5) {
                ਜੇ (have_image_bmp) {
                    // We have already registered this format
                    ਜਾਰੀ;
                }
                have_image_bmp = true;
            }

            ਪੂਰਨ len = GetClipboardFormatMimeType(format, ਨਿਰਾ);
            ਜੇ (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_Allocate_Temporary_ਸਮ੍ਰਿਤੀ((nformats + 1) * ਆਕਾਰ(ਅੱਖਰ *) + formatsSz);
        ਜੇ (new_mime_types) {
            format = 0;
            ਅੱਖਰ *strPtr = (ਅੱਖਰ *)(new_mime_types + nformats + 1);
            ਪੂਰਨ i = 0;
            ਲਈ ( ; ; ) {
                format = EnumClipboardFormats(format);
                ਜੇ (!format) {
                    ਰੋਕੋ;
                }

                ਜੇ (format == CF_DIB || format == CF_DIBV5) {
                    ਜੇ (have_image_bmp) {
                        // We have already registered this format
                        ਜਾਰੀ;
                    }
                    have_image_bmp = true;
                }

                ਪੂਰਨ len = GetClipboardFormatMimeType(format, strPtr);
                ਜੇ (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = ਨਿਰਾ;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    ਵਾਪਸ new_mime_types;
}

ਖਾਲੀ WIN_CheckClipboardUpdate(ਬਣਤਰ SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
    DWORD ਗਿਣਤੀ_2 = Get_Clipboard_Sequence_ਸੰਖਿਆ();
    ਜੇ (ਗਿਣਤੀ_2 != ਅੰਕੜੇ->clipboard_ਗਿਣਤੀ) {
        ਜੇ (ਗਿਣਤੀ_2) {
            ਪੂਰਨ nformats = 0;
            ਅੱਖਰ **new_mime_types = GetMimeTypes(&nformats);
            ਜੇ (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        ਅੰਕੜੇ->clipboard_ਗਿਣਤੀ = ਗਿਣਤੀ_2;
    }
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WINDOWS
