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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಆದರೆ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ಅನ್ತರ್ಭಾವ "SDL_windowsvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowswindow.h"
#ಅನ್ತರ್ಭಾವ "../SDL_clipboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_clipboardevents_c.h"

#ವ್ಯಾಖ್ಯಾನಿಸು BFT_BITMAP 0x4d42 // 'BM'

// Assume we can directly read and write BMP fields without byte swapping
SDL_COMPILE_ಸಮಯ_ASSERT(verify_byte_ಕ್ರಮ, SDL_BYTEORDER == SDL_LIL_ENDIAN);

ಸ್ಥಿರ UINT GetClipboardFormatPNG(ಶೂನ್ಯ)
{
    ಸ್ಥಿರ UINT format;

    ಆದರೆ (!format) {
        format = ರಿಜಿಸ್ಟರ್_Clipboard_Format(ಪಠ್ಯ_2("PNG"));
    }
    ಹಿಂತಿರುಗಿ format;
}

ಸ್ಥಿರ BOOL WIN_OpenClipboard(SDL_VideoDevice *_this)
{
    // Retry to open the clipboard in case another application has it open
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ MAX_ATTEMPTS = 3;
    ಪೂರ್ಣಾಂಕ attempt;
    HWND hwnd = ಖಾಲಿ;

    ಆದರೆ (_this->windows) {
        hwnd = _this->windows->ಆಂತರಿಕ->hwnd;
    }
    ಗಾಗಿ (attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        ಆದರೆ (OpenClipboard(hwnd)) {
            ಹಿಂತಿರುಗಿ TRUE;
        }
        SDL_Delay(10);
    }
    ಹಿಂತಿರುಗಿ FALSE;
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_CloseClipboard(ಶೂನ್ಯ)
{
    CloseClipboard();
}

ಸ್ಥಿರ HANDLE WIN_ConvertBMPtoDIB(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *bmp, size_t bmp_ಗಾತ್ರ, UINT *format)
{
    HANDLE hMem = ಖಾಲಿ;

    ಆದರೆ (bmp && bmp_ಗಾತ್ರ > ಗಾತ್ರ(BITMAPFILEHEADER) && ((BITMAPFILEHEADER *)bmp)->bfType == BFT_BITMAP) {
        BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
        BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)((Uint8 *)bmp + ಗಾತ್ರ(BITMAPFILEHEADER));
        size_t bih_ಗಾತ್ರ = pbih->bi_ಗಾತ್ರ + pbih->bi_Clr_ಬಳಸಿದ * ಗಾತ್ರ(RGBQUAD);
        size_t pixels_ಗಾತ್ರ = pbih->bi_ಗಾತ್ರ_Image;

        ಆದರೆ (pbih->bi_ಗಾತ್ರ >= ಗಾತ್ರ(BITMAPV5_ಶೀರ್ಷಿಕೆ)) {
            *format = CF_DIBV5;
        } ಇಲ್ಲದಿದ್ದರೆ {
            *format = CF_DIB;
        }

        ಆದರೆ (pbfh->bf_Off_ಬಿಟ್ಟುಗಳು >= (ಗಾತ್ರ(BITMAPFILEHEADER) + bih_ಗಾತ್ರ) &&
            (pbfh->bf_Off_ಬಿಟ್ಟುಗಳು + pixels_ಗಾತ್ರ) <= bmp_ಗಾತ್ರ) {
            ಸ್ಥಿರಾಂಕ Uint8 *pixels = (ಸ್ಥಿರಾಂಕ Uint8 *)bmp + pbfh->bf_Off_ಬಿಟ್ಟುಗಳು;
            size_t dib_ಗಾತ್ರ = bih_ಗಾತ್ರ + pixels_ಗಾತ್ರ;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dib_ಗಾತ್ರ);
            ಆದರೆ (hMem) {
                LPVOID dst = Global_ಬೀಗ(hMem);
                ಆದರೆ (dst) {
                    SDL_memcpy(dst, pbih, bih_ಗಾತ್ರ);
                    SDL_memcpy((Uint8 *)dst + bih_ಗಾತ್ರ, pixels, pixels_ಗಾತ್ರ);
                    GlobalUnlock(hMem);
                } ಇಲ್ಲದಿದ್ದರೆ {
                    WIN_ಗಣ_Error("GlobalLock()");
                    GlobalFree(hMem);
                    hMem = ಖಾಲಿ;
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                SDL_ಹೊರಹೋಗು_ದ_ಸ್ಮರಣೆ();
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_ಗಣ_Error("Invalid BMP data");
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_ಗಣ_Error("Invalid BMP data");
    }
    ಹಿಂತಿರುಗಿ hMem;
}

ಸ್ಥಿರ ಶೂನ್ಯ *WIN_ConvertDIBtoBMP(HANDLE hMem, size_t *ಗಾತ್ರ_2)
{
    ಶೂನ್ಯ *bmp = ಖಾಲಿ;
    size_t mem_ಗಾತ್ರ = Global_ಗಾತ್ರ(hMem);

    ಆದರೆ (mem_ಗಾತ್ರ > ಗಾತ್ರ(BITMAPINFOHEADER)) {
        LPVOID dib = Global_ಬೀಗ(hMem);
        ಆದರೆ (dib) {
            BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)dib;

            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#color-tables
            size_t color_ಕೋಷ್ಟಕ_ಗಾತ್ರ;
            ಆಯ್ಕೆ (pbih->biCompression) {
            ಸ್ಥಿತಿ BI_RGB:
                ಆದರೆ (pbih->bi_ಬಿಟ್_ಎಣಿಕೆ <= 8) {
                    color_ಕೋಷ್ಟಕ_ಗಾತ್ರ = ಗಾತ್ರ(RGBQUAD) * (pbih->bi_Clr_ಬಳಸಿದ == 0 ? 1 << pbih->bi_ಬಿಟ್_ಎಣಿಕೆ : pbih->bi_Clr_ಬಳಸಿದ);
                } ಇಲ್ಲದಿದ್ದರೆ {
                    color_ಕೋಷ್ಟಕ_ಗಾತ್ರ = 0;
                }
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ BI_BITFIELDS:
                color_ಕೋಷ್ಟಕ_ಗಾತ್ರ = 3 * ಗಾತ್ರ(DWORD);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ 6 /* BI_ALPHABITFIELDS */:
                // https://learn.microsoft.com/en-us/previous-versions/windows/embedded/aa452885(v=msdn.10)
                color_ಕೋಷ್ಟಕ_ಗಾತ್ರ = 4 * ಗಾತ್ರ(DWORD);
                ನಿಲ್ಲಿಸು;
            ಪೂರ್ವನಿಯೋಜಿತ: // FOURCC
                color_ಕೋಷ್ಟಕ_ಗಾತ್ರ = ಗಾತ್ರ(RGBQUAD) * pbih->bi_Clr_ಬಳಸಿದ;
            }

            size_t bih_ಗಾತ್ರ = pbih->bi_ಗಾತ್ರ + color_ಕೋಷ್ಟಕ_ಗಾತ್ರ;
            size_t dib_ಗಾತ್ರ = bih_ಗಾತ್ರ + pbih->bi_ಗಾತ್ರ_Image;
            ಆದರೆ (dib_ಗಾತ್ರ <= mem_ಗಾತ್ರ) {
                size_t bmp_ಗಾತ್ರ = ಗಾತ್ರ(BITMAPFILEHEADER) + mem_ಗಾತ್ರ;
                bmp = SDL_malloc(bmp_ಗಾತ್ರ);
                ಆದರೆ (bmp) {
                    BITMAPFILEHEADER *pbfh = (BITMAPFILEHEADER *)bmp;
                    pbfh->bfType = BFT_BITMAP;
                    pbfh->bf_ಗಾತ್ರ = (DWORD)bmp_ಗಾತ್ರ;
                    pbfh->bfReserved1 = 0;
                    pbfh->bfReserved2 = 0;
                    pbfh->bf_Off_ಬಿಟ್ಟುಗಳು = (DWORD)(ಗಾತ್ರ(BITMAPFILEHEADER) + pbih->bi_ಗಾತ್ರ + color_ಕೋಷ್ಟಕ_ಗಾತ್ರ);
                    SDL_memcpy((Uint8 *)bmp + ಗಾತ್ರ(BITMAPFILEHEADER), dib, mem_ಗಾತ್ರ);
                    *ಗಾತ್ರ_2 = bmp_ಗಾತ್ರ;
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                SDL_ಗಣ_Error("Invalid BMP data");
            }
            GlobalUnlock(hMem);
        } ಇಲ್ಲದಿದ್ದರೆ {
            WIN_ಗಣ_Error("GlobalLock()");
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_ಗಣ_Error("Invalid BMP data");
    }
    ಹಿಂತಿರುಗಿ bmp;
}

ಸ್ಥಿರ bool WIN_ಗಣ_Clipboard_Image(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type)
{
    UINT format = 0;
    HANDLE hMem = ಖಾಲಿ;
    size_t clipboard_ದತ್ತಾಂಶ_ಗಾತ್ರ;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *clipboard_ದತ್ತಾಂಶ;
    bool ಫಲಿತಾಂಶ = true;

    clipboard_ದತ್ತಾಂಶ = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_ದತ್ತಾಂಶ_ಗಾತ್ರ);
    ಆದರೆ (SDL_strcmp(mime_type, "image/bmp") == 0) {
        hMem = WIN_ConvertBMPtoDIB(clipboard_ದತ್ತಾಂಶ, clipboard_ದತ್ತಾಂಶ_ಗಾತ್ರ, &format);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(mime_type, "image/png") == 0) {
        format = GetClipboardFormatPNG();
        hMem = GlobalAlloc(GMEM_MOVEABLE, clipboard_ದತ್ತಾಂಶ_ಗಾತ್ರ);
        ಆದರೆ (hMem) {
            LPVOID dst = Global_ಬೀಗ(hMem);
            ಆದರೆ (dst) {
                SDL_memcpy(dst, clipboard_ದತ್ತಾಂಶ, clipboard_ದತ್ತಾಂಶ_ಗಾತ್ರ);
                GlobalUnlock(hMem);
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಫಲಿತಾಂಶ = WIN_ಗಣ_Error("GlobalLock()");
                GlobalFree(hMem);
                hMem = ಖಾಲಿ;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಫಲಿತಾಂಶ = SDL_ಹೊರಹೋಗು_ದ_ಸ್ಮರಣೆ();
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("Unknown image format");
    }
    ಆದರೆ (hMem) {
        // Save the image to the clipboard
        ಆದರೆ (!ಗಣ_Clipboard_ದತ್ತಾಂಶ(format, hMem)) {
            ಫಲಿತಾಂಶ = WIN_ಗಣ_Error("Couldn't set clipboard data");
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        // WIN_ConvertBMPtoDIB() set the error
        ಫಲಿತಾಂಶ = false;
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ಸ್ಥಿರ bool WIN_ಗಣ_Clipboard_ಪಠ್ಯ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type)
{
    HANDLE hMem;
    size_t clipboard_ದತ್ತಾಂಶ_ಗಾತ್ರ;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *clipboard_ದತ್ತಾಂಶ;
    bool ಫಲಿತಾಂಶ = true;

    clipboard_ದತ್ತಾಂಶ = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &clipboard_ದತ್ತಾಂಶ_ಗಾತ್ರ);
    ಆದರೆ (clipboard_ದತ್ತಾಂಶ && clipboard_ದತ್ತಾಂಶ_ಗಾತ್ರ > 0) {
        ಗಾತ್ರ_T i, ಗಾತ್ರ_2;
        LPWSTR tstr = (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)clipboard_ದತ್ತಾಂಶ, clipboard_ದತ್ತಾಂಶ_ಗಾತ್ರ);
        ಆದರೆ (!tstr) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Couldn't convert text from UTF-8");
        }

        // Find out the size of the data
        ಗಾಗಿ (ಗಾತ್ರ_2 = 0, i = 0; tstr[i]; ++i, ++ಗಾತ್ರ_2) {
            ಆದರೆ (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                // We're going to insert a carriage return
                ++ಗಾತ್ರ_2;
            }
        }
        ಗಾತ್ರ_2 = (ಗಾತ್ರ_2 + 1) * ಗಾತ್ರ(*tstr);

        // Save the data to the clipboard
        hMem = GlobalAlloc(GMEM_MOVEABLE, ಗಾತ್ರ_2);
        ಆದರೆ (hMem) {
            LPWSTR dst = (LPWSTR)Global_ಬೀಗ(hMem);
            ಆದರೆ (dst) {
                // Copy the text over, adding carriage returns as necessary
                ಗಾಗಿ (i = 0; tstr[i]; ++i) {
                    ಆದರೆ (tstr[i] == '\n' && (i == 0 || tstr[i - 1] != '\r')) {
                        *dst++ = '\r';
                    }
                    *dst++ = tstr[i];
                }
                *dst = 0;
                GlobalUnlock(hMem);
            }

            ಆದರೆ (!ಗಣ_Clipboard_ದತ್ತಾಂಶ(CF_UNICODETEXT, hMem)) {
                ಫಲಿತಾಂಶ = WIN_ಗಣ_Error("Couldn't set clipboard data");
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಫಲಿತಾಂಶ = SDL_ಹೊರಹೋಗು_ದ_ಸ್ಮರಣೆ();
        }
        SDL_free(tstr);
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

bool WIN_ಗಣ_Clipboard_ದತ್ತಾಂಶ(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    size_t i;
    bool ಫಲಿತಾಂಶ = true;

    /* I investigated delayed clipboard rendering, and at least with text and image
     * formats you have to use an output window, not SDL_HelperWindow, and the system
     * requests them being rendered immediately, so there isn't any benefit.
     */

    ಆದರೆ (WIN_OpenClipboard(_this)) {
        ಖಾಲಿಗಳು_Clipboard();

        // Set the clipboard text
        ಗಾಗಿ (i = 0; i < _this->ಅಂಕೆ_clipboard_mime_types; ++i) {
            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type = _this->clipboard_mime_types[i];

            ಆದರೆ (SDL_Is_ಪಠ್ಯ_Mime_Type(mime_type)) {
                ಆದರೆ (!WIN_ಗಣ_Clipboard_ಪಠ್ಯ(_this, mime_type)) {
                    ಫಲಿತಾಂಶ = false;
                }
                // Only set the first clipboard text
                ನಿಲ್ಲಿಸು;
            }
        }

        // Set the clipboard image
        ಗಾಗಿ (i = 0; i < _this->ಅಂಕೆ_clipboard_mime_types; ++i) {
            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type = _this->clipboard_mime_types[i];

            ಆದರೆ (SDL_strcmp(mime_type, "image/bmp") == 0 ||
                SDL_strcmp(mime_type, "image/png") == 0) {
                ಆದರೆ (!WIN_ಗಣ_Clipboard_Image(_this, mime_type)) {
                    ಫಲಿತಾಂಶ = false;
                }
                ನಿಲ್ಲಿಸು;
            }
        }

        ದತ್ತಾಂಶ->clipboard_ಎಣಿಕೆ = Get_Clipboard_Sequence_ಸಂಖ್ಯೆ();
        WIN_CloseClipboard();
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಫಲಿತಾಂಶ = WIN_ಗಣ_Error("Couldn't open clipboard");
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ಶೂನ್ಯ *WIN_Get_Clipboard_ದತ್ತಾಂಶ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, size_t *ಗಾತ್ರ_2)
{
    ಶೂನ್ಯ *ದತ್ತಾಂಶ = ಖಾಲಿ;

    ಆದರೆ (SDL_Is_ಪಠ್ಯ_Mime_Type(mime_type)) {
        ಅಕ್ಷರ *ಪಠ್ಯ = ಖಾಲಿ;

        ಆದರೆ (Is_Clipboard_Format_ಲಭ್ಯ(CF_UNICODETEXT)) {
            ಆದರೆ (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPTSTR str;

                hMem = Get_Clipboard_ದತ್ತಾಂಶ(CF_UNICODETEXT);
                ಆದರೆ (hMem) {
                    str = (LPTSTR)Global_ಬೀಗ(hMem);
                    ಆದರೆ (str) {
                        ಪಠ್ಯ = WIN_String_ಗಮ್ಯ_UTF8_W(str);
                        GlobalUnlock(hMem);
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        WIN_ಗಣ_Error("Couldn't lock clipboard data");
                    }
                } ಇಲ್ಲದಿದ್ದರೆ {
                    WIN_ಗಣ_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (Is_Clipboard_Format_ಲಭ್ಯ(CF_ಪಠ್ಯ)) {
            ಆದರೆ (WIN_OpenClipboard(_this)) {
                HANDLE hMem;
                LPCSTR str;

                hMem = Get_Clipboard_ದತ್ತಾಂಶ(CF_ಪಠ್ಯ);
                ಆದರೆ (hMem) {
                    str = (LPCSTR)Global_ಬೀಗ(hMem);
                    ಆದರೆ (str) {
                        ಪಠ್ಯ = SDL_strdup(str);
                        GlobalUnlock(hMem);
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        WIN_ಗಣ_Error("Couldn't lock clipboard data");
                    }
                } ಇಲ್ಲದಿದ್ದರೆ {
                    WIN_ಗಣ_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }
        ಆದರೆ (!ಪಠ್ಯ) {
            ಪಠ್ಯ = SDL_strdup("");
        }
        ದತ್ತಾಂಶ = ಪಠ್ಯ;
        *ಗಾತ್ರ_2 = SDL_strlen(ಪಠ್ಯ);

    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(mime_type, "image/bmp") == 0) {
        ಆದರೆ (Is_Clipboard_Format_ಲಭ್ಯ(CF_DIBV5)) {
            ಆದರೆ (WIN_OpenClipboard(_this)) {
                HANDLE hMem = Get_Clipboard_ದತ್ತಾಂಶ(CF_DIBV5);
                ಆದರೆ (hMem) {
                    ದತ್ತಾಂಶ = WIN_ConvertDIBtoBMP(hMem, ಗಾತ್ರ_2);
                } ಇಲ್ಲದಿದ್ದರೆ {
                    WIN_ಗಣ_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (Is_Clipboard_Format_ಲಭ್ಯ(CF_DIB)) {
            ಆದರೆ (WIN_OpenClipboard(_this)) {
                HANDLE hMem = Get_Clipboard_ದತ್ತಾಂಶ(CF_DIB);
                ಆದರೆ (hMem) {
                    ದತ್ತಾಂಶ = WIN_ConvertDIBtoBMP(hMem, ಗಾತ್ರ_2);
                } ಇಲ್ಲದಿದ್ದರೆ {
                    WIN_ಗಣ_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(mime_type, "image/png") == 0) {
        ಆದರೆ (Is_Clipboard_Format_ಲಭ್ಯ(GetClipboardFormatPNG())) {
            ಆದರೆ (WIN_OpenClipboard(_this)) {
                HANDLE hMem = Get_Clipboard_ದತ್ತಾಂಶ(GetClipboardFormatPNG());
                ಆದರೆ (hMem) {
                    size_t mem_ಗಾತ್ರ = Global_ಗಾತ್ರ(hMem);
                    ಶೂನ್ಯ *mem = Global_ಬೀಗ(hMem);
                    ಆದರೆ (mem) {
                        ದತ್ತಾಂಶ = SDL_malloc(mem_ಗಾತ್ರ);
                        ಆದರೆ (ದತ್ತಾಂಶ) {
                            SDL_memcpy(ದತ್ತಾಂಶ, mem, mem_ಗಾತ್ರ);
                            *ಗಾತ್ರ_2 = mem_ಗಾತ್ರ;
                        }
                        GlobalUnlock(hMem);
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        WIN_ಗಣ_Error("Couldn't lock clipboard data");
                    }
                } ಇಲ್ಲದಿದ್ದರೆ {
                    WIN_ಗಣ_Error("Couldn't get clipboard data");
                }
                WIN_CloseClipboard();
            }
        }

    } ಇಲ್ಲದಿದ್ದರೆ {
        ದತ್ತಾಂಶ = SDL_Get_ಆಂತರಿಕ_Clipboard_ದತ್ತಾಂಶ(_this, mime_type, ಗಾತ್ರ_2);
    }
    ಹಿಂತಿರುಗಿ ದತ್ತಾಂಶ;
}

bool WIN_Has_Clipboard_ದತ್ತಾಂಶ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type)
{
    ಆದರೆ (SDL_Is_ಪಠ್ಯ_Mime_Type(mime_type)) {
        ಆದರೆ (Is_Clipboard_Format_ಲಭ್ಯ(CF_UNICODETEXT) || Is_Clipboard_Format_ಲಭ್ಯ(CF_ಪಠ್ಯ)) {
            ಹಿಂತಿರುಗಿ true;
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(mime_type, "image/bmp") == 0) {
        ಆದರೆ (Is_Clipboard_Format_ಲಭ್ಯ(CF_DIBV5) || Is_Clipboard_Format_ಲಭ್ಯ(CF_DIB)) {
            ಹಿಂತಿರುಗಿ true;
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(mime_type, "image/png") == 0) {
        ಆದರೆ (Is_Clipboard_Format_ಲಭ್ಯ(GetClipboardFormatPNG())) {
            ಹಿಂತಿರುಗಿ true;
        }
    }
    ಹಿಂತಿರುಗಿ SDL_Has_ಆಂತರಿಕ_Clipboard_ದತ್ತಾಂಶ(_this, mime_type);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ GetClipboardFormatMimeType(UINT format, ಅಕ್ಷರ *name)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type = ಖಾಲಿ;

    ಆಯ್ಕೆ (format) {
    ಸ್ಥಿತಿ CF_ಪಠ್ಯ:
        mime_type = "text/plain";
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ CF_UNICODETEXT:
        mime_type = "text/plain;charset=utf-8";
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ CF_DIB:
    ಸ್ಥಿತಿ CF_DIBV5:
        mime_type = "image/bmp";
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಆದರೆ (format == GetClipboardFormatPNG()) {
            mime_type = "image/png";
        }
        ನಿಲ್ಲಿಸು;
    }
    ಆದರೆ (mime_type) {
        size_t len = SDL_strlen(mime_type) + 1;
        ಆದರೆ (name) {
            SDL_memcpy(name, mime_type, len);
        }
        ಹಿಂತಿರುಗಿ (ಪೂರ್ಣಾಂಕ)len;
    }
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಅಕ್ಷರ **GetMimeTypes(ಪೂರ್ಣಾಂಕ *pnformats)
{
    ಅಕ್ಷರ **new_mime_types = ಖಾಲಿ;

    *pnformats = 0;

    ಆದರೆ (WIN_OpenClipboard(SDL_GetVideoDevice())) {
        ಪೂರ್ಣಾಂಕ nformats = 0;
        UINT format = 0;
        ಪೂರ್ಣಾಂಕ formatsSz = 0;
        bool have_image_bmp = false;
        ಗಾಗಿ ( ; ; ) {
            format = EnumClipboardFormats(format);
            ಆದರೆ (!format) {
                ನಿಲ್ಲಿಸು;
            }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_CLIPBOARD
            ಅಕ್ಷರ name[128] = { 0 };
            GetClipboardFormatNameA(format, name, ಗಾತ್ರ(name));
            SDL_Log("Clipboard format: %d (0x%x), '%s'", format, format, name);
#ಆದರೆ_ಅಂತ್ಯ

            ಆದರೆ (format == CF_DIB || format == CF_DIBV5) {
                ಆದರೆ (have_image_bmp) {
                    // We have already registered this format
                    ಮುಂದುವರಿ;
                }
                have_image_bmp = true;
            }

            ಪೂರ್ಣಾಂಕ len = GetClipboardFormatMimeType(format, ಖಾಲಿ);
            ಆದರೆ (len > 0) {
                ++nformats;
                formatsSz += len;
            }
        }

        have_image_bmp = false;
        new_mime_types = SDL_Allocate_Temporary_ಸ್ಮರಣೆ((nformats + 1) * ಗಾತ್ರ(ಅಕ್ಷರ *) + formatsSz);
        ಆದರೆ (new_mime_types) {
            format = 0;
            ಅಕ್ಷರ *strPtr = (ಅಕ್ಷರ *)(new_mime_types + nformats + 1);
            ಪೂರ್ಣಾಂಕ i = 0;
            ಗಾಗಿ ( ; ; ) {
                format = EnumClipboardFormats(format);
                ಆದರೆ (!format) {
                    ನಿಲ್ಲಿಸು;
                }

                ಆದರೆ (format == CF_DIB || format == CF_DIBV5) {
                    ಆದರೆ (have_image_bmp) {
                        // We have already registered this format
                        ಮುಂದುವರಿ;
                    }
                    have_image_bmp = true;
                }

                ಪೂರ್ಣಾಂಕ len = GetClipboardFormatMimeType(format, strPtr);
                ಆದರೆ (len > 0) {
                    new_mime_types[i++] = strPtr;
                    strPtr += len;
                }
            }

            new_mime_types[nformats] = ಖಾಲಿ;
            *pnformats = nformats;
        }
        WIN_CloseClipboard();
    }
    ಹಿಂತಿರುಗಿ new_mime_types;
}

ಶೂನ್ಯ WIN_CheckClipboardUpdate(ರಚನೆ SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
    DWORD ಎಣಿಕೆ_2 = Get_Clipboard_Sequence_ಸಂಖ್ಯೆ();
    ಆದರೆ (ಎಣಿಕೆ_2 != ದತ್ತಾಂಶ->clipboard_ಎಣಿಕೆ) {
        ಆದರೆ (ಎಣಿಕೆ_2) {
            ಪೂರ್ಣಾಂಕ nformats = 0;
            ಅಕ್ಷರ **new_mime_types = GetMimeTypes(&nformats);
            ಆದರೆ (new_mime_types) {
                SDL_SendClipboardUpdate(false, new_mime_types, nformats);
            }
        }
        ದತ್ತಾಂಶ->clipboard_ಎಣಿಕೆ = ಎಣಿಕೆ_2;
    }
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WINDOWS
