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
#അന്തര്ഭാവ "SDL_internal.h"

#എങ്കിൽ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#അന്തര്ഭാവ "SDL_windowsvideo.h"

#അന്തര്ഭാവ "../../events/SDL_keyboard_c.h"
#അന്തര്ഭാവ "../../events/scancodes_windows.h"

#അന്തര്ഭാവ <imm.h>
#അന്തര്ഭാവ <oleauto.h>

#ifndef SDL_DISABLE_WINDOWS_IME
#എങ്കിൽ 0
#define SDL_DebugIMELog SDL_Log
#അല്ലെങ്കിൽ
#define SDL_DebugIMELog(...)
#endif
സ്ഥിതം bool IME_Init(SDL_VideoData *videodata, SDL_Window *window);
സ്ഥിതം ശൂന്യം IME_Enable(SDL_VideoData *videodata, HWND hwnd);
സ്ഥിതം ശൂന്യം IME_Disable(SDL_VideoData *videodata, HWND hwnd);
സ്ഥിതം ശൂന്യം IME_Set_Text_നിവേശം_Area(SDL_VideoData *videodata, HWND hwnd, സ്ഥിരം SDL_Rect *rect, പൂർണ്ണസംഖ്യ cursor);
സ്ഥിതം ശൂന്യം IME_ClearComposition(SDL_VideoData *videodata);
സ്ഥിതം ശൂന്യം IME_GetCandidateList(SDL_VideoData *videodata, HWND hwnd);
സ്ഥിതം ശൂന്യം IME_Quit(SDL_VideoData *videodata);
#അല്ലെങ്കിൽ
സ്ഥിതം ശൂന്യം IME_Set_Text_നിവേശം_Area(SDL_VideoData *videodata, HWND hwnd, സ്ഥിരം SDL_Rect *rect, പൂർണ്ണസംഖ്യ cursor);
#endif // !SDL_DISABLE_WINDOWS_IME

#ifndef MAPVK_VK_TO_VSC
#define MAPVK_VK_TO_VSC 0
#endif
#ifndef MAPVK_VSC_TO_VK
#define MAPVK_VSC_TO_VK 1
#endif

/* Building keymaps is expensive, so keep a reasonably-sized LRU cache to
 * enable fast switching between commonly used ones.
 */
സ്ഥിതം ഘടന WIN_KeymapCache
{
    HKL keyboard_layout;
    SDL_Keymap *keymap;
} keymap_cache[4];

സ്ഥിതം പൂർണ്ണസംഖ്യ keymap_cache_size;

സ്ഥിതം SDL_Keymap *WIN_GetCachedKeymap(HKL layout)
{
    SDL_Keymap *keymap = ശൂന്യ;
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < keymap_cache_size; ++i) {
        എങ്കിൽ (keymap_cache[i].keyboard_layout == layout) {
            keymap = keymap_cache[i].keymap;

            // Move the map to the front of the list.
            എങ്കിൽ (i) {
                SDL_memmove(keymap_cache + 1, keymap_cache, വലുപ്പം(ഘടന WIN_KeymapCache) * i);
                keymap_cache[0].keyboard_layout = layout;
                keymap_cache[0].keymap = keymap;
            }
            നിർത്തുക;
        }
    }
    തിരികെ keymap;
}

സ്ഥിതം ശൂന്യം WIN_CacheKeymap(HKL layout, SDL_Keymap *keymap)
{
    // If the cache is full, evict the last keymap.
    എങ്കിൽ (keymap_cache_size == SDL_arraysize(keymap_cache)) {
        SDL_DestroyKeymap(keymap_cache[--keymap_cache_size].keymap);
    }

    // Move all elements down by one.
    എങ്കിൽ (keymap_cache_size) {
        SDL_memmove(keymap_cache + 1, keymap_cache, വലുപ്പം(ഘടന WIN_KeymapCache) * keymap_cache_size);
    }

    keymap_cache[0].keyboard_layout = layout;
    keymap_cache[0].keymap = keymap;
    ++keymap_cache_size;
}

സ്ഥിതം SDL_Keymap *WIN_BuildKeymap(ശൂന്യം)
{
    SDL_Scancode scancode;
    BYTE keyboardState[256] = { 0 };
    WCHAR buffer[16];
    സ്ഥിരം SDL_Keymod mods[] = {
        SDL_KMOD_NONE,
        SDL_KMOD_SHIFT,
        SDL_KMOD_CAPS,
        (SDL_KMOD_SHIFT | SDL_KMOD_CAPS),
        SDL_KMOD_MODE,
        (SDL_KMOD_MODE | SDL_KMOD_SHIFT),
        (SDL_KMOD_MODE | SDL_KMOD_CAPS),
        (SDL_KMOD_MODE | SDL_KMOD_SHIFT | SDL_KMOD_CAPS)
    };

    WIN_Reset_Dead_താക്കോലുകൾ();

    SDL_Keymap *keymap = SDL_CreateKeymap(false);
    എങ്കിൽ (!keymap) {
        തിരികെ ശൂന്യ;
    }

    വേണ്ടി (പൂർണ്ണസംഖ്യ m = 0; m < SDL_arraysize(mods); ++m) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < SDL_arraysize(windows_scancode_table); i++) {
            പൂർണ്ണസംഖ്യ vk, sc, result;
            Uint32 *ch = 0;

            // Make sure this scancode is a valid character scancode
            scancode = windows_scancode_table[i];
            എങ്കിൽ (scancode == SDL_SCANCODE_UNKNOWN ||
                scancode == SDL_SCANCODE_DELETE ||
                (SDL_GetKeymapKeycode(ശൂന്യ, scancode, SDL_KMOD_NONE) & SDLK_SCANCODE_MASK)) {

                // The Colemak mapping swaps Backspace and CapsLock
                എങ്കിൽ (mods[m] == SDL_KMOD_NONE &&
                    (scancode == SDL_SCANCODE_CAPSLOCK ||
                     scancode == SDL_SCANCODE_BACKSPACE)) {
                    vk = LOBYTE(Map_Virtual_താക്കോൽ(i, MAPVK_VSC_TO_VK));
                    എങ്കിൽ (vk == VK_CAPITAL) {
                        SDL_SetKeymapEntry(keymap, scancode, mods[m], SDLK_CAPSLOCK);
                    } അല്ലെങ്കിൽ എങ്കിൽ (vk == VK_BACK) {
                        SDL_SetKeymapEntry(keymap, scancode, mods[m], SDLK_BACKSPACE);
                    }
                }
                തുടരുക;
            }

            // Unpack the single byte index to make the scan code.
            sc = MAKEWORD(i & 0x7f, (i & 0x80) ? 0xe0 : 0x00);
            vk = LOBYTE(Map_Virtual_താക്കോൽ(sc, MAPVK_VSC_TO_VK));
            എങ്കിൽ (!vk) {
                തുടരുക;
            }

            // Update the keyboard state for the modifiers
            keyboardState[VK_SHIFT] = (mods[m] & SDL_KMOD_SHIFT) ? 0x80 : 0x00;
            keyboardState[VK_CAPITAL] = (mods[m] & SDL_KMOD_CAPS) ? 0x01 : 0x00;
            keyboardState[VK_CONTROL] = (mods[m] & SDL_KMOD_MODE) ? 0x80 : 0x00;
            keyboardState[VK_MENU] = (mods[m] & SDL_KMOD_MODE) ? 0x80 : 0x00;

            result = ToUnicode(vk, sc, keyboardState, buffer, 16, 0);
            buffer[SDL_abs(result)] = 0;

            // Convert UTF-16 to UTF-32 code points
            ch = (Uint32 *)SDL_iconv_string("UTF-32LE", "UTF-16LE", (സ്ഥിരം അക്ഷരം *)buffer, (SDL_abs(result) + 1) * വലുപ്പം(WCHAR));
            എങ്കിൽ (ch) {
                /* Windows keyboard layouts can emit several UTF-32 code points on a single key press.
                 * Use <U+FFFD REPLACEMENT CHARACTER> since we cannot fit into single SDL_Keycode value in SDL keymap.
                 * See https://kbdlayout.info/features/ligatures for a list of such keys. */
                SDL_SetKeymapEntry(keymap, scancode, mods[m], ch[1] == 0 ? ch[0] : 0xfffd);
                SDL_free(ch);
            } അല്ലെങ്കിൽ {
                // The default keymap doesn't have any SDL_KMOD_MODE entries, so we don't need to override them
                എങ്കിൽ (!(mods[m] & SDL_KMOD_MODE)) {
                    SDL_SetKeymapEntry(keymap, scancode, mods[m], SDLK_UNKNOWN);
                }
            }

            എങ്കിൽ (result < 0) {
                WIN_Reset_Dead_താക്കോലുകൾ();
            }
        }
    }

    തിരികെ keymap;
}

ശൂന്യം WIN_UpdateKeymap(bool send_event)
{
    HKL layout = GetKeyboardLayout(0);
    SDL_Keymap *keymap = WIN_GetCachedKeymap(layout);
    എങ്കിൽ (!keymap) {
        keymap = WIN_BuildKeymap();
        എങ്കിൽ (keymap) {
            WIN_CacheKeymap(layout, keymap);
        }
    }

    SDL_SetKeymap(keymap, send_event);
}

// Alphabetic scancodes for PC keyboards
ശൂന്യം WIN_InitKeyboard(SDL_VideoDevice *_this)
{
#ifndef SDL_DISABLE_WINDOWS_IME
    SDL_VideoData *data = _this->internal;

    data->ime_candlistindexbase = 1;
    data->ime_composition_length = 32 * വലുപ്പം(WCHAR);
    data->ime_composition = (WCHAR *)SDL_calloc(data->ime_composition_length, വലുപ്പം(WCHAR));
#endif // !SDL_DISABLE_WINDOWS_IME

    // Build and bind the current keymap.
    WIN_UpdateKeymap(false);

    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");
    SDL_SetScancodeName(SDL_SCANCODE_LGUI, "Left Windows");
    SDL_SetScancodeName(SDL_SCANCODE_RGUI, "Right Windows");

    // Are system caps/num/scroll lock active? Set our state to match.
    SDL_ToggleModState(SDL_KMOD_CAPS, (Get_താക്കോൽ_State(VK_CAPITAL) & 0x0001) ? true : false);
    SDL_ToggleModState(SDL_KMOD_അക്കം, (Get_താക്കോൽ_State(VK_NUMLOCK) & 0x0001) ? true : false);
    SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_താക്കോൽ_State(VK_SCROLL) & 0x0001) ? true : false);
}

ശൂന്യം WIN_QuitKeyboard(SDL_VideoDevice *_this)
{
#ifndef SDL_DISABLE_WINDOWS_IME
    SDL_VideoData *data = _this->internal;

    IME_Quit(data);

    എങ്കിൽ (data->ime_composition) {
        SDL_free(data->ime_composition);
        data->ime_composition = ശൂന്യ;
    }
#endif // !SDL_DISABLE_WINDOWS_IME

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < keymap_cache_size; ++i) {
        SDL_DestroyKeymap(keymap_cache[i].keymap);
    }
    SDL_zeroa(keymap_cache);
    keymap_cache_size = 0;
}

ശൂന്യം WIN_Reset_Dead_താക്കോലുകൾ(ശൂന്യം)
{
    /*
    if a deadkey has been typed, but not the next character (which the deadkey might modify),
    this tries to undo the effect pressing the deadkey.
    see: http://archives.miloush.net/michkap/archive/2006/09/10/748775.html
    */
    BYTE keyboardState[256];
    WCHAR buffer[16];
    പൂർണ്ണസംഖ്യ vk, sc, result, i;

    എങ്കിൽ (!GetKeyboardState(keyboardState)) {
        തിരികെ;
    }

    vk = VK_SPACE;
    sc = Map_Virtual_താക്കോൽ(vk, MAPVK_VK_TO_VSC);
    എങ്കിൽ (sc == 0) {
        // the keyboard doesn't have this key
        തിരികെ;
    }

    വേണ്ടി (i = 0; i < 5; i++) {
        result = ToUnicode(vk, sc, keyboardState, buffer, 16, 0);
        എങ്കിൽ (result > 0) {
            // success
            തിരികെ;
        }
    }
}

bool WIN_Start_Text_നിവേശം(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    WIN_Reset_Dead_താക്കോലുകൾ();

#ifndef SDL_DISABLE_WINDOWS_IME
    HWND hwnd = window->internal->hwnd;
    SDL_VideoData *videodata = _this->internal;
    IME_Init(videodata, window);
    IME_Enable(videodata, hwnd);

    WIN_Update_Text_നിവേശം_Area(_this, window);
#endif // !SDL_DISABLE_WINDOWS_IME

    തിരികെ true;
}

bool WIN_Stop_Text_നിവേശം(SDL_VideoDevice *_this, SDL_Window *window)
{
    WIN_Reset_Dead_താക്കോലുകൾ();

#ifndef SDL_DISABLE_WINDOWS_IME
    HWND hwnd = window->internal->hwnd;
    SDL_VideoData *videodata = _this->internal;
    IME_Init(videodata, window);
    IME_Disable(videodata, hwnd);
#endif // !SDL_DISABLE_WINDOWS_IME

    തിരികെ true;
}

bool WIN_Update_Text_നിവേശം_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_WindowData *data = window->internal;

    IME_Set_Text_നിവേശം_Area(videodata, data->hwnd, &window->text_നിവേശം_rect, window->text_നിവേശം_cursor);
    തിരികെ true;
}

bool WIN_ClearComposition(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifndef SDL_DISABLE_WINDOWS_IME
    SDL_VideoData *videodata = _this->internal;

    IME_ClearComposition(videodata);
#endif
    തിരികെ true;
}

#ifdef SDL_DISABLE_WINDOWS_IME

bool WIN_HandleIMEMessage(HWND hwnd, UINT സന്ദേശം, WPARAM wParam, LPARAM *lParam, SDL_VideoData *videodata)
{
    തിരികെ false;
}

ശൂന്യം WIN_UpdateIMECandidates(SDL_VideoDevice *_this)
{
    തിരികെ;
}

#അല്ലെങ്കിൽ

#define LANG_CHT MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_TRADITIONAL)
#define LANG_CHS MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED)

#define MAKEIMEVERSION(major, minor) ((DWORD)(((BYTE)(major) << 24) | ((BYTE)(minor) << 16)))
#define IMEID_VER(id)                ((id)&0xffff0000)
#define IMEID_LANG(id)               ((id)&0x0000ffff)

#define CHT_HKL_DAYI          ((HKL)(UINT_PTR)0xE0060404)
#define CHT_HKL_NEW_PHONETIC  ((HKL)(UINT_PTR)0xE0080404)
#define CHT_HKL_NEW_CHANG_JIE ((HKL)(UINT_PTR)0xE0090404)
#define CHT_HKL_NEW_QUICK     ((HKL)(UINT_PTR)0xE00A0404)
#define CHT_HKL_HK_CANTONESE  ((HKL)(UINT_PTR)0xE00B0404)
#define CHT_IMEFILENAME1      "TINTLGNT.IME"
#define CHT_IMEFILENAME2      "CINTLGNT.IME"
#define CHT_IMEFILENAME3      "MSTCIPHA.IME"
#define IMEID_CHT_VER42       (LANG_CHT | MAKEIMEVERSION(4, 2))
#define IMEID_CHT_VER43       (LANG_CHT | MAKEIMEVERSION(4, 3))
#define IMEID_CHT_VER44       (LANG_CHT | MAKEIMEVERSION(4, 4))
#define IMEID_CHT_VER50       (LANG_CHT | MAKEIMEVERSION(5, 0))
#define IMEID_CHT_VER51       (LANG_CHT | MAKEIMEVERSION(5, 1))
#define IMEID_CHT_VER52       (LANG_CHT | MAKEIMEVERSION(5, 2))
#define IMEID_CHT_VER60       (LANG_CHT | MAKEIMEVERSION(6, 0))
#define IMEID_CHT_VER_VISTA   (LANG_CHT | MAKEIMEVERSION(7, 0))

#define CHS_HKL          ((HKL)(UINT_PTR)0xE00E0804)
#define CHS_IMEFILENAME1 "PINTLGNT.IME"
#define CHS_IMEFILENAME2 "MSSCIPYA.IME"
#define IMEID_CHS_VER41  (LANG_CHS | MAKEIMEVERSION(4, 1))
#define IMEID_CHS_VER42  (LANG_CHS | MAKEIMEVERSION(4, 2))
#define IMEID_CHS_VER53  (LANG_CHS | MAKEIMEVERSION(5, 3))

#define LANG()         LOWORD((videodata->ime_hkl))
#define PRIMLANG()     ((WORD)PRIMARYLANGID(LANG()))
#define SUBLANG()      SUBLANGID(LANG())

സ്ഥിതം ശൂന്യം IME_Update_നിവേശം_Locale(SDL_VideoData *videodata);
സ്ഥിതം ശൂന്യം IME_SetWindow(SDL_VideoData *videodata, SDL_Window *window);
സ്ഥിതം ശൂന്യം IME_SetupAPI(SDL_VideoData *videodata);
സ്ഥിതം DWORD IME_GetId(SDL_VideoData *videodata, UINT uIndex);
സ്ഥിതം ശൂന്യം IME_SendEditingEvent(SDL_VideoData *videodata);
സ്ഥിതം ശൂന്യം IME_SendClearComposition(SDL_VideoData *videodata);

സ്ഥിതം bool IME_Init(SDL_VideoData *videodata, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;

    എങ്കിൽ (videodata->ime_initialized) {
        തിരികെ true;
    }

    സ്ഥിരം അക്ഷരം *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);
    എങ്കിൽ (hint && SDL_strstr(hint, "composition")) {
        videodata->ime_internal_composition = true;
    }
    എങ്കിൽ (hint && SDL_strstr(hint, "candidates")) {
        videodata->ime_internal_candidates = true;
    }

    videodata->ime_hwnd_main = hwnd;
    videodata->ime_initialized = true;
    videodata->ime_himm32 = SDL_LoadObject("imm32.dll");
    എങ്കിൽ (!videodata->ime_himm32) {
        videodata->ime_available = false;
        SDL_ClearError();
        തിരികെ true;
    }
    /* *INDENT-OFF* */ // clang-format off
    videodata->ImmLockIMC = (LPINPUTCONTEXT2 (WINAPI *)(HIMC))SDL_LoadFunction(videodata->ime_himm32, "ImmLockIMC");
    videodata->ImmUnlockIMC = (BOOL (WINAPI *)(HIMC))SDL_LoadFunction(videodata->ime_himm32, "ImmUnlockIMC");
    videodata->ImmLockIMCC = (LPVOID (WINAPI *)(HIMCC))SDL_LoadFunction(videodata->ime_himm32, "ImmLockIMCC");
    videodata->ImmUnlockIMCC = (BOOL (WINAPI *)(HIMCC))SDL_LoadFunction(videodata->ime_himm32, "ImmUnlockIMCC");
    /* *INDENT-ON* */ // clang-format on

    IME_SetWindow(videodata, window);
    videodata->ime_himc = ImmGetContext(hwnd);
    ImmReleaseContext(hwnd, videodata->ime_himc);
    എങ്കിൽ (!videodata->ime_himc) {
        videodata->ime_available = false;
        IME_Disable(videodata, hwnd);
        തിരികെ true;
    }
    videodata->ime_available = true;
    IME_Update_നിവേശം_Locale(videodata);
    IME_SetupAPI(videodata);
    IME_Update_നിവേശം_Locale(videodata);
    IME_Disable(videodata, hwnd);
    തിരികെ true;
}

സ്ഥിതം ശൂന്യം IME_Enable(SDL_VideoData *videodata, HWND hwnd)
{
    എങ്കിൽ (!videodata->ime_initialized || !videodata->ime_hwnd_current) {
        തിരികെ;
    }

    എങ്കിൽ (!videodata->ime_available) {
        IME_Disable(videodata, hwnd);
        തിരികെ;
    }
    എങ്കിൽ (videodata->ime_hwnd_current == videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_current, videodata->ime_himc);
    }

    videodata->ime_enabled = true;
    IME_Update_നിവേശം_Locale(videodata);
}

സ്ഥിതം ശൂന്യം IME_Disable(SDL_VideoData *videodata, HWND hwnd)
{
    എങ്കിൽ (!videodata->ime_initialized || !videodata->ime_hwnd_current) {
        തിരികെ;
    }

    IME_ClearComposition(videodata);
    എങ്കിൽ (videodata->ime_hwnd_current == videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_current, (HIMC)0);
    }

    videodata->ime_enabled = false;
}

സ്ഥിതം ശൂന്യം IME_Quit(SDL_VideoData *videodata)
{
    എങ്കിൽ (!videodata->ime_initialized) {
        തിരികെ;
    }

    എങ്കിൽ (videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_main, videodata->ime_himc);
    }

    videodata->ime_hwnd_main = 0;
    videodata->ime_himc = 0;
    എങ്കിൽ (videodata->ime_himm32) {
        SDL_UnloadObject(videodata->ime_himm32);
        videodata->ime_himm32 = 0;
    }
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < videodata->ime_candcount; ++i) {
        SDL_free(videodata->ime_candidates[i]);
        videodata->ime_candidates[i] = ശൂന്യ;
    }
    videodata->ime_initialized = false;
}

സ്ഥിതം ശൂന്യം IME_GetReadingString(SDL_VideoData *videodata, HWND hwnd)
{
    DWORD id = 0;
    HIMC himc = 0;
    WCHAR buffer[16];
    WCHAR *s = buffer;
    DWORD len = 0;
    INT err = 0;
    BOOL vertical = FALSE;
    UINT maxuilen = 0;

    videodata->ime_readingstring[0] = 0;

    id = IME_GetId(videodata, 0);
    എങ്കിൽ (!id) {
        തിരികെ;
    }

    himc = ImmGetContext(hwnd);
    എങ്കിൽ (!himc) {
        തിരികെ;
    }

    എങ്കിൽ (videodata->GetReadingString) {
        len = videodata->GetReadingString(himc, 0, 0, &err, &vertical, &maxuilen);
        എങ്കിൽ (len) {
            എങ്കിൽ (len > SDL_arraysize(buffer)) {
                len = SDL_arraysize(buffer);
            }

            len = videodata->GetReadingString(himc, len, s, &err, &vertical, &maxuilen);
        }
        SDL_wcslcpy(videodata->ime_readingstring, s, len);
    } അല്ലെങ്കിൽ {
        LPINPUTCONTEXT2 lpimc = videodata->ImmLockIMC(himc);
        LPBYTE p = 0;
        s = 0;
        തിരഞ്ഞെടുപ്പ് (id) {
        അവസ്ഥ IMEID_CHT_VER42:
        അവസ്ഥ IMEID_CHT_VER43:
        അവസ്ഥ IMEID_CHT_VER44:
            p = *(LPBYTE *)((LPBYTE)videodata->ImmLockIMCC(lpimc->hPrivate) + 24);
            എങ്കിൽ (!p) {
                നിർത്തുക;
            }

            len = *(DWORD *)(p + 7 * 4 + 32 * 4);
            s = (WCHAR *)(p + 56);
            നിർത്തുക;
        അവസ്ഥ IMEID_CHT_VER51:
        അവസ്ഥ IMEID_CHT_VER52:
        അവസ്ഥ IMEID_CHS_VER53:
            p = *(LPBYTE *)((LPBYTE)videodata->ImmLockIMCC(lpimc->hPrivate) + 4);
            എങ്കിൽ (!p) {
                നിർത്തുക;
            }

            p = *(LPBYTE *)(p + 1 * 4 + 5 * 4);
            എങ്കിൽ (!p) {
                നിർത്തുക;
            }

            len = *(DWORD *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4 + 16 * 2);
            s = (WCHAR *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4);
            നിർത്തുക;
        അവസ്ഥ IMEID_CHS_VER41:
        {
            പൂർണ്ണസംഖ്യ offset = (IME_GetId(videodata, 1) >= 0x00000002) ? 8 : 7;
            p = *(LPBYTE *)((LPBYTE)videodata->ImmLockIMCC(lpimc->hPrivate) + offset * 4);
            എങ്കിൽ (!p) {
                നിർത്തുക;
            }

            len = *(DWORD *)(p + 7 * 4 + 16 * 2 * 4);
            s = (WCHAR *)(p + 6 * 4 + 16 * 2 * 1);
        } നിർത്തുക;
        അവസ്ഥ IMEID_CHS_VER42:
            p = *(LPBYTE *)((LPBYTE)videodata->ImmLockIMCC(lpimc->hPrivate) + 1 * 4 + 1 * 4 + 6 * 4);
            എങ്കിൽ (!p) {
                നിർത്തുക;
            }

            len = *(DWORD *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4 + 16 * 2);
            s = (WCHAR *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4);
            നിർത്തുക;
        }
        എങ്കിൽ (s) {
            size_t size = SDL_min((size_t)(len + 1), SDL_arraysize(videodata->ime_readingstring));
            SDL_wcslcpy(videodata->ime_readingstring, s, size);
        }

        videodata->ImmUnlockIMCC(lpimc->hPrivate);
        videodata->ImmUnlockIMC(himc);
    }
    ImmReleaseContext(hwnd, himc);
    IME_SendEditingEvent(videodata);
}

സ്ഥിതം ശൂന്യം IME_നിവേശം_Lang_Changed(SDL_VideoData *videodata)
{
    UINT lang = PRIMLANG();
    IME_Update_നിവേശം_Locale(videodata);

    IME_SetupAPI(videodata);
    എങ്കിൽ (lang != PRIMLANG()) {
        IME_ClearComposition(videodata);
    }
}

സ്ഥിതം DWORD IME_GetId(SDL_VideoData *videodata, UINT uIndex)
{
    സ്ഥിതം HKL hklprev = 0;
    സ്ഥിതം DWORD dwRet[2] = { 0 };
    DWORD dwVerSize = 0;
    LPVOID lpVerBuffer = 0;
    LPVOID lpVerData = 0;
    UINT cbVerData = 0;
    അക്ഷരം szTemp[256];
    HKL hkl = 0;
    DWORD dwLang = 0;
    SDL_assert(uIndex < SDL_arraysize(dwRet));

    hkl = videodata->ime_hkl;
    എങ്കിൽ (hklprev == hkl) {
        തിരികെ dwRet[uIndex];
    }
    hklprev = hkl;

    SDL_assert(uIndex == 0);
    dwLang = ((DWORD_PTR)hkl & 0xffff);
    // FIXME: What does this do?
    എങ്കിൽ (videodata->ime_internal_candidates && dwLang == LANG_CHT) {
        dwRet[0] = IMEID_CHT_VER_VISTA;
        dwRet[1] = 0;
        തിരികെ dwRet[0];
    }
    എങ്കിൽ (hkl != CHT_HKL_NEW_PHONETIC && hkl != CHT_HKL_NEW_CHANG_JIE && hkl != CHT_HKL_NEW_QUICK && hkl != CHT_HKL_HK_CANTONESE && hkl != CHS_HKL) {
        dwRet[0] = dwRet[1] = 0;
        തിരികെ dwRet[0];
    }
    എങ്കിൽ (!ImmGetIMEFileNameA(hkl, szTemp, വലുപ്പം(szTemp) - 1)) {
        dwRet[0] = dwRet[1] = 0;
        തിരികെ dwRet[0];
    }
    എങ്കിൽ (!videodata->GetReadingString) {
#define LCID_INVARIANT MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT)
        എങ്കിൽ (CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, szTemp, -1, CHT_IMEFILENAME1, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, szTemp, -1, CHT_IMEFILENAME2, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, szTemp, -1, CHT_IMEFILENAME3, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, szTemp, -1, CHS_IMEFILENAME1, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, szTemp, -1, CHS_IMEFILENAME2, -1) != 2) {
            dwRet[0] = dwRet[1] = 0;
            തിരികെ dwRet[0];
        }
#undef LCID_INVARIANT
        dwVerSize = GetFileVersionInfoSizeA(szTemp, ശൂന്യ);
        എങ്കിൽ (dwVerSize) {
            lpVerBuffer = SDL_malloc(dwVerSize);
            എങ്കിൽ (lpVerBuffer) {
                എങ്കിൽ (GetFileVersionInfoA(szTemp, 0, dwVerSize, lpVerBuffer)) {
                    എങ്കിൽ (Ver_Query_മൂല്യം_A(lpVerBuffer, "\\", &lpVerData, &cbVerData)) {
#define pVerFixedInfo ((VS_FIXEDFILEINFO FAR *)lpVerData)
                        DWORD dwVer = pVerFixedInfo->dwFileVersionMS;
                        dwVer = (dwVer & 0x00ff0000) << 8 | (dwVer & 0x000000ff) << 16;
                        എങ്കിൽ ((videodata->GetReadingString) ||
                            ((dwLang == LANG_CHT) && (dwVer == MAKEIMEVERSION(4, 2) ||
                                                      dwVer == MAKEIMEVERSION(4, 3) ||
                                                      dwVer == MAKEIMEVERSION(4, 4) ||
                                                      dwVer == MAKEIMEVERSION(5, 0) ||
                                                      dwVer == MAKEIMEVERSION(5, 1) ||
                                                      dwVer == MAKEIMEVERSION(5, 2) ||
                                                      dwVer == MAKEIMEVERSION(6, 0))) ||
                            ((dwLang == LANG_CHS) && (dwVer == MAKEIMEVERSION(4, 1) ||
                                                      dwVer == MAKEIMEVERSION(4, 2) ||
                                                      dwVer == MAKEIMEVERSION(5, 3)))) {
                            dwRet[0] = dwVer | dwLang;
                            dwRet[1] = pVerFixedInfo->dwFileVersionLS;
                            SDL_free(lpVerBuffer);
                            തിരികെ dwRet[0];
                        }
#undef pVerFixedInfo
                    }
                }
            }
            SDL_free(lpVerBuffer);
        }
    }
    dwRet[0] = dwRet[1] = 0;
    തിരികെ dwRet[0];
}

സ്ഥിതം ശൂന്യം IME_SetupAPI(SDL_VideoData *videodata)
{
    അക്ഷരം ime_file[MAX_PATH + 1];
    SDL_SharedObject *hime = 0;
    HKL hkl = 0;
    videodata->GetReadingString = ശൂന്യ;
    videodata->ShowReadingWindow = ശൂന്യ;

    hkl = videodata->ime_hkl;
    എങ്കിൽ (!ImmGetIMEFileNameA(hkl, ime_file, വലുപ്പം(ime_file) - 1)) {
        തിരികെ;
    }

    hime = SDL_LoadObject(ime_file);
    എങ്കിൽ (!hime) {
        തിരികെ;
    }

    /* *INDENT-OFF* */ // clang-format off
    videodata->GetReadingString = (UINT (WINAPI *)(HIMC, UINT, LPWSTR, PINT, BOOL*, PUINT))
        SDL_LoadFunction(hime, "GetReadingString");
    videodata->ShowReadingWindow = (BOOL (WINAPI *)(HIMC, BOOL))
        SDL_LoadFunction(hime, "ShowReadingWindow");
    /* *INDENT-ON* */ // clang-format on

    എങ്കിൽ (videodata->ShowReadingWindow) {
        HIMC himc = ImmGetContext(videodata->ime_hwnd_current);
        എങ്കിൽ (himc) {
            videodata->ShowReadingWindow(himc, FALSE);
            ImmReleaseContext(videodata->ime_hwnd_current, himc);
        }
    }
}

സ്ഥിതം ശൂന്യം IME_SetWindow(SDL_VideoData *videodata, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;

    എങ്കിൽ (hwnd != videodata->ime_hwnd_current) {
        videodata->ime_hwnd_current = hwnd;
        SDL_zero(videodata->ime_composition_area);
        SDL_zero(videodata->ime_candidate_area);
    }

    IME_Set_Text_നിവേശം_Area(videodata, hwnd, &window->text_നിവേശം_rect, window->text_നിവേശം_cursor);
}

#endif

സ്ഥിതം ശൂന്യം IME_Set_Text_നിവേശം_Area(SDL_VideoData *videodata, HWND hwnd, സ്ഥിരം SDL_Rect *rect, പൂർണ്ണസംഖ്യ cursor)
{
    HIMC himc;

    himc = ImmGetContext(hwnd);
    എങ്കിൽ (himc) {
        COMPOSITIONFORM cof;
        CANDIDATEFORM caf;
        പൂർണ്ണസംഖ്യ font_height = rect->h;

        LOGFONTW font;
        എങ്കിൽ (ImmGetCompositionFontW(himc, &font)) {
            font_height = font.lfHeight;
        }

        SDL_zero(cof);
        cof.dwStyle = CFS_RECT;
        cof.ptCurrentPos.x = rect->x + cursor;
        cof.ptCurrentPos.y = rect->y + (rect->h - font_height) / 2;
        cof.rcArea.ഇടത് = rect->x;
        cof.rcArea.വലത് = (LONG)rect->x + rect->w;
        cof.rcArea.മുകൾ = rect->y;
        cof.rcArea.bottom = (LONG)rect->y + rect->h;
        എങ്കിൽ (SDL_memcmp(&cof, &videodata->ime_composition_area, വലുപ്പം(cof)) != 0) {
            SDL_copyp(&videodata->ime_composition_area, &cof);
            ImmSetCompositionWindow(himc, &cof);
        }

        SDL_zero(caf);
        caf.dwIndex = 0;
        caf.dwStyle = CFS_EXCLUDE;
        caf.ptCurrentPos.x = rect->x + cursor;
        caf.ptCurrentPos.y = rect->y;
        caf.rcArea.ഇടത് = rect->x;
        caf.rcArea.വലത് = (LONG)rect->x + rect->w;
        caf.rcArea.മുകൾ = rect->y;
        caf.rcArea.bottom = (LONG)rect->y + rect->h;
        എങ്കിൽ (SDL_memcmp(&caf, &videodata->ime_candidate_area, വലുപ്പം(caf)) != 0) {
            SDL_copyp(&videodata->ime_candidate_area, &caf);
            ImmSetCandidateWindow(himc, &caf);
        }

        ImmReleaseContext(hwnd, himc);
    }
}

#ifndef SDL_DISABLE_WINDOWS_IME

സ്ഥിതം ശൂന്യം IME_Update_നിവേശം_Locale(SDL_VideoData *videodata)
{
    HKL hklnext = GetKeyboardLayout(0);

    എങ്കിൽ (hklnext == videodata->ime_hkl) {
        തിരികെ;
    }

    videodata->ime_hkl = hklnext;
    videodata->ime_horizontal_candidates = (PRIMLANG() == LANG_KOREAN || LANG() == LANG_CHS);
    videodata->ime_candlistindexbase = (videodata->ime_hkl == CHT_HKL_DAYI) ? 0 : 1;
}

സ്ഥിതം ശൂന്യം IME_ClearComposition(SDL_VideoData *videodata)
{
    HIMC himc = 0;
    എങ്കിൽ (!videodata->ime_initialized) {
        തിരികെ;
    }

    himc = ImmGetContext(videodata->ime_hwnd_current);
    എങ്കിൽ (!himc) {
        തിരികെ;
    }

    ImmNotifyIME(himc, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
    ImmSetCompositionString(himc, SCS_SETSTR, TEXT(""), വലുപ്പം(TCHAR), TEXT(""), വലുപ്പം(TCHAR));

    ImmNotifyIME(himc, NI_CLOSECANDIDATE, 0, 0);
    ImmReleaseContext(videodata->ime_hwnd_current, himc);
    IME_SendClearComposition(videodata);
}

സ്ഥിതം ശൂന്യം IME_GetCompositionString(SDL_VideoData *videodata, HIMC himc, LPARAM *lParam, DWORD string)
{
    LONG length;
    DWORD dwLang = ((DWORD_PTR)videodata->ime_hkl & 0xffff);

    എങ്കിൽ (*lParam & GCS_CURSORPOS) {
        videodata->ime_cursor = LOWORD(ImmGetCompositionStringW(himc, GCS_CURSORPOS, 0, 0));
    }
    videodata->ime_selected_start = 0;
    videodata->ime_selected_length = 0;
    SDL_DebugIMELog("Cursor = %d", videodata->ime_cursor);

    length = ImmGetCompositionStringW(himc, string, ശൂന്യ, 0);
    എങ്കിൽ (length > 0 && videodata->ime_composition_length < length) {
        SDL_free(videodata->ime_composition);

        videodata->ime_composition = (WCHAR *)SDL_malloc(length + വലുപ്പം(WCHAR));
        videodata->ime_composition_length = length;
    }

    length = ImmGetCompositionStringW(himc, string, videodata->ime_composition, videodata->ime_composition_length);
    എങ്കിൽ (length < 0) {
        length = 0;
    }
    length /= വലുപ്പം(WCHAR);

    എങ്കിൽ (!(*lParam & GCS_CURSORPOS)) {
        // If the IME doesn't support GCS_CURSORPOS, default the cursor to the end of the composition.
        videodata->ime_cursor = length;
    }

    എങ്കിൽ ((dwLang == LANG_CHT || dwLang == LANG_CHS) &&
        videodata->ime_cursor > 0 &&
        videodata->ime_cursor < (പൂർണ്ണസംഖ്യ)(videodata->ime_composition_length / വലുപ്പം(WCHAR)) &&
        (videodata->ime_composition[0] == 0x3000 || videodata->ime_composition[0] == 0x0020)) {
        // Traditional Chinese IMEs add a placeholder U+3000
        // Simplified Chinese IMEs seem to add a placeholder U+0020 sometimes
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = videodata->ime_cursor + 1; i < length; ++i) {
            videodata->ime_composition[i - 1] = videodata->ime_composition[i];
        }
        --length;
    }

    videodata->ime_composition[length] = 0;

    length = ImmGetCompositionStringW(himc, GCS_COMPATTR, ശൂന്യ, 0);
    എങ്കിൽ (length > 0) {
        Uint8 *attributes = (Uint8 *)SDL_malloc(length);
        എങ്കിൽ (attributes) {
            പൂർണ്ണസംഖ്യ start = 0;
            പൂർണ്ണസംഖ്യ end = 0;

            length = ImmGetCompositionString(himc, GCS_COMPATTR, attributes, length);
            എങ്കിൽ (length < 0) {
                length = 0;
            }

            വേണ്ടി (LONG i = 0; i < length; ++i) {
                SDL_DebugIMELog("attrib[%d] = %d", i, attributes[i]);
            }

            വേണ്ടി (start = 0; start < length; ++start) {
                എങ്കിൽ (attributes[start] == ATTR_TARGET_CONVERTED || attributes[start] == ATTR_TARGET_NOTCONVERTED) {
                    നിർത്തുക;
                }
            }

            വേണ്ടി (end = start; end < length; ++end) {
                എങ്കിൽ (attributes[end] != ATTR_TARGET_CONVERTED && attributes[end] != ATTR_TARGET_NOTCONVERTED) {
                    നിർത്തുക;
                }
            }

            എങ്കിൽ (end > start) {
                videodata->ime_selected_start = start;
                videodata->ime_selected_length = end - start;
            }

            SDL_free(attributes);
        }
    }
}

സ്ഥിതം ശൂന്യം IME_Send_നിവേശം_Event(SDL_VideoData *videodata)
{
    അക്ഷരം *s = 0;
    s = WIN_StringToUTF8W(videodata->ime_composition);
    SDL_SendKeyboardText(s);
    SDL_free(s);

    videodata->ime_composition[0] = 0;
    videodata->ime_readingstring[0] = 0;
    videodata->ime_cursor = 0;
}

സ്ഥിതം ശൂന്യം IME_SendEditingEvent(SDL_VideoData *videodata)
{
    അക്ഷരം *s = ശൂന്യ;
    WCHAR *buffer = ശൂന്യ;
    size_t size = videodata->ime_composition_length;
    എങ്കിൽ (videodata->ime_readingstring[0]) {
        size_t len = SDL_min(SDL_wcslen(videodata->ime_composition), (size_t)videodata->ime_cursor);

        size += വലുപ്പം(videodata->ime_readingstring);
        buffer = (WCHAR *)SDL_malloc(size + വലുപ്പം(WCHAR));
        എങ്കിൽ (!buffer) {
            തിരികെ;
        }
        buffer[0] = 0;

        SDL_wcslcpy(buffer, videodata->ime_composition, len + 1);
        SDL_wcslcat(buffer, videodata->ime_readingstring, size);
        SDL_wcslcat(buffer, &videodata->ime_composition[len], size);
    } അല്ലെങ്കിൽ {
        buffer = (WCHAR *)SDL_malloc(size + വലുപ്പം(WCHAR));
        എങ്കിൽ (!buffer) {
            തിരികെ;
        }
        buffer[0] = 0;
        SDL_wcslcpy(buffer, videodata->ime_composition, size);
    }

    s = WIN_StringToUTF8W(buffer);
    എങ്കിൽ (s) {
        എങ്കിൽ (videodata->ime_readingstring[0]) {
            SDL_SendEditingText(s, videodata->ime_cursor, (പൂർണ്ണസംഖ്യ)SDL_wcslen(videodata->ime_readingstring));
        } അല്ലെങ്കിൽ എങ്കിൽ (videodata->ime_cursor == videodata->ime_selected_start) {
            SDL_SendEditingText(s, videodata->ime_selected_start, videodata->ime_selected_length);
        } അല്ലെങ്കിൽ {
            SDL_SendEditingText(s, videodata->ime_cursor, 0);
        }
        എങ്കിൽ (*s) {
            videodata->ime_needs_clear_composition = true;
        }
        SDL_free(s);
    }
    SDL_free(buffer);
}

സ്ഥിതം ശൂന്യം IME_SendClearComposition(SDL_VideoData *videodata)
{
    എങ്കിൽ (videodata->ime_needs_clear_composition) {
        SDL_SendEditingText("", 0, 0);
        videodata->ime_needs_clear_composition = false;
    }
}

സ്ഥിതം bool IME_OpenCandidateList(SDL_VideoData *videodata)
{
    videodata->ime_candidates_open = true;
    videodata->ime_candcount = 0;
    തിരികെ true;
}

സ്ഥിതം ശൂന്യം IME_AddCandidate(SDL_VideoData *videodata, UINT i, LPCWSTR candidate)
{
    എങ്കിൽ (videodata->ime_candidates[i]) {
        SDL_free(videodata->ime_candidates[i]);
        videodata->ime_candidates[i] = ശൂന്യ;
    }

    SDL_COMPILE_TIME_ASSERT(IME_CANDIDATE_INDEXING_REQUIRES, MAX_CANDLIST == 10);
    അക്ഷരം *candidate_utf8 = WIN_StringToUTF8W(candidate);
    SDL_asprintf(&videodata->ime_candidates[i], "%d %s", ((i + videodata->ime_candlistindexbase) % 10), candidate_utf8);
    SDL_free(candidate_utf8);

    videodata->ime_candcount = (i + 1);
}

സ്ഥിതം ശൂന്യം IME_SendCandidateList(SDL_VideoData *videodata)
{
    SDL_SendEditingTextCandidates(videodata->ime_candidates, videodata->ime_candcount, videodata->ime_candsel, videodata->ime_horizontal_candidates);
}

സ്ഥിതം ശൂന്യം IME_CloseCandidateList(SDL_VideoData *videodata)
{
    videodata->ime_candidates_open = false;

    എങ്കിൽ (videodata->ime_candcount > 0) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < videodata->ime_candcount; ++i) {
            SDL_free(videodata->ime_candidates[i]);
            videodata->ime_candidates[i] = ശൂന്യ;
        }
        videodata->ime_candcount = 0;

        SDL_SendEditingTextCandidates(ശൂന്യ, 0, -1, false);
    }
}

സ്ഥിതം ശൂന്യം IME_GetCandidateList(SDL_VideoData *videodata, HWND hwnd)
{
    HIMC himc;
    DWORD size;
    LPCANDIDATELIST cand_list;
    bool has_candidates = false;

    himc = ImmGetContext(hwnd);
    എങ്കിൽ (himc) {
        size = ImmGetCandidateListW(himc, 0, ശൂന്യ, 0);
        എങ്കിൽ (size != 0) {
            cand_list = (LPCANDIDATELIST)SDL_malloc(size);
            എങ്കിൽ (cand_list != ശൂന്യ) {
                size = ImmGetCandidateListW(himc, 0, cand_list, size);
                എങ്കിൽ (size != 0) {
                    എങ്കിൽ (IME_OpenCandidateList(videodata)) {
                        UINT i, j;
                        UINT page_start = 0;
                        UINT page_size = 0;

                        videodata->ime_candsel = cand_list->dwSelection;

                        എങ്കിൽ (LANG() == LANG_CHS && IME_GetId(videodata, 0)) {
                            സ്ഥിരം UINT maxcandchar = 18;
                            size_t cchars = 0;

                            വേണ്ടി (i = 0; i < cand_list->dw_എണ്ണം; ++i) {
                                size_t len = SDL_wcslen((LPWSTR)((DWORD_PTR)cand_list + cand_list->dwOffset[i])) + 1;
                                എങ്കിൽ (len + cchars > maxcandchar) {
                                    എങ്കിൽ (i > cand_list->dwSelection) {
                                        നിർത്തുക;
                                    }

                                    page_start = i;
                                    cchars = len;
                                } അല്ലെങ്കിൽ {
                                    cchars += len;
                                }
                            }
                            page_size = i - page_start;
                        } അല്ലെങ്കിൽ {
                            page_size = SDL_min(cand_list->dwPageSize == 0 ? MAX_CANDLIST : cand_list->dwPageSize, MAX_CANDLIST);
                            page_start = (cand_list->dwSelection / page_size) * page_size;
                        }
                        വേണ്ടി (i = page_start, j = 0; (DWORD)i < cand_list->dw_എണ്ണം && j < page_size; i++, j++) {
                            LPCWSTR candidate = (LPCWSTR)((DWORD_PTR)cand_list + cand_list->dwOffset[i]);
                            IME_AddCandidate(videodata, j, candidate);
                        }

                        has_candidates = true;
                        IME_SendCandidateList(videodata);
                    }
                }
                SDL_free(cand_list);
            }
        }
        ImmReleaseContext(hwnd, himc);
    }

    എങ്കിൽ (!has_candidates) {
        IME_CloseCandidateList(videodata);
    }
}

bool WIN_HandleIMEMessage(HWND hwnd, UINT സന്ദേശം, WPARAM wParam, LPARAM *lParam, SDL_VideoData *videodata)
{
    bool trap = false;
    HIMC himc = 0;

    എങ്കിൽ (സന്ദേശം == WM_IME_SETCONTEXT) {
        SDL_DebugIMELog("WM_IME_SETCONTEXT");

        LPARAM element_mask;
        element_mask = ISC_SHOWUIALL;
        എങ്കിൽ (videodata->ime_internal_composition) {
            element_mask &= ~ISC_SHOWUICOMPOSITIONWINDOW;
        }
        എങ്കിൽ (videodata->ime_internal_candidates) {
            element_mask &= ~ISC_SHOWUIALLCANDIDATEWINDOW;
        }
        *lParam &= element_mask;

        തിരികെ false;
    } അല്ലെങ്കിൽ എങ്കിൽ (സന്ദേശം == WM_IME_STARTCOMPOSITION) {
        SDL_DebugIMELog("WM_IME_STARTCOMPOSITION");
        എങ്കിൽ (videodata->ime_internal_composition) {
            videodata->ime_cursor = 0;
            // Windows may still display a composition dialog even with
            // ISC_SHOWUICOMPOSITIONWINDOW cleared, so trap the message
            // here to prevent that (even when the IME is disabled).
            തിരികെ true;
        }
    }

    എങ്കിൽ (!videodata->ime_initialized || !videodata->ime_available || !videodata->ime_enabled) {
        തിരികെ false;
    }

    തിരഞ്ഞെടുപ്പ് (സന്ദേശം) {
    അവസ്ഥ WM_KEYDOWN:
        എങ്കിൽ (wParam == VK_PROCESSKEY) {
            SDL_DebugIMELog("WM_KEYDOWN VK_PROCESSKEY");
            trap = true;
        } അല്ലെങ്കിൽ {
            SDL_DebugIMELog("WM_KEYDOWN normal");
        }
        നിർത്തുക;
    അവസ്ഥ WM_SYSKEYDOWN:
        എങ്കിൽ (wParam == VK_PROCESSKEY) {
            SDL_DebugIMELog("WM_SYSKEYDOWN VK_PROCESSKEY");
            trap = true;
        } അല്ലെങ്കിൽ {
            SDL_DebugIMELog("WM_SYSKEYDOWN normal");
        }
        നിർത്തുക;
    അവസ്ഥ WM_INPUTLANGCHANGE:
        SDL_DebugIMELog("WM_INPUTLANGCHANGE");
        IME_നിവേശം_Lang_Changed(videodata);
        നിർത്തുക;
    അവസ്ഥ WM_IME_COMPOSITION:
        SDL_DebugIMELog("WM_IME_COMPOSITION %x", lParam);
        എങ്കിൽ (videodata->ime_internal_composition) {
            trap = true;
            himc = ImmGetContext(hwnd);
            എങ്കിൽ (*lParam & GCS_RESULTSTR) {
                SDL_DebugIMELog("GCS_RESULTSTR");
                IME_GetCompositionString(videodata, himc, lParam, GCS_RESULTSTR);
                IME_SendClearComposition(videodata);
                IME_Send_നിവേശം_Event(videodata);
            }
            എങ്കിൽ (*lParam & GCS_COMPSTR) {
                SDL_DebugIMELog("GCS_COMPSTR");
                videodata->ime_readingstring[0] = 0;
                IME_GetCompositionString(videodata, himc, lParam, GCS_COMPSTR);
                IME_SendEditingEvent(videodata);
            }
            ImmReleaseContext(hwnd, himc);
        }
        നിർത്തുക;
    അവസ്ഥ WM_IME_ENDCOMPOSITION:
        SDL_DebugIMELog("WM_IME_ENDCOMPOSITION");
        എങ്കിൽ (videodata->ime_internal_composition) {
            trap = true;
            videodata->ime_composition[0] = 0;
            videodata->ime_readingstring[0] = 0;
            videodata->ime_cursor = 0;
            videodata->ime_selected_start = 0;
            videodata->ime_selected_length = 0;
            IME_SendClearComposition(videodata);
        }
        നിർത്തുക;
    അവസ്ഥ WM_IME_NOTIFY:
        SDL_DebugIMELog("WM_IME_NOTIFY %x", wParam);
        തിരഞ്ഞെടുപ്പ് (wParam) {
        അവസ്ഥ IMN_SETCOMPOSITIONWINDOW:
            SDL_DebugIMELog("IMN_SETCOMPOSITIONWINDOW");
            നിർത്തുക;
        അവസ്ഥ IMN_SETCOMPOSITIONFONT:
            SDL_DebugIMELog("IMN_SETCOMPOSITIONFONT");
            നിർത്തുക;
        അവസ്ഥ IMN_SETCANDIDATEPOS:
            SDL_DebugIMELog("IMN_SETCANDIDATEPOS");
            നിർത്തുക;
        അവസ്ഥ IMN_SETCONVERSIONMODE:
        അവസ്ഥ IMN_SETOPENSTATUS:
            SDL_DebugIMELog("%s", wParam == IMN_SETCONVERSIONMODE ? "IMN_SETCONVERSIONMODE" : "IMN_SETOPENSTATUS");
            IME_Update_നിവേശം_Locale(videodata);
            നിർത്തുക;
        അവസ്ഥ IMN_OPENCANDIDATE:
        അവസ്ഥ IMN_CHANGECANDIDATE:
            SDL_DebugIMELog("%s", wParam == IMN_OPENCANDIDATE ? "IMN_OPENCANDIDATE" : "IMN_CHANGECANDIDATE");
            എങ്കിൽ (videodata->ime_internal_candidates) {
                trap = true;
                videodata->ime_update_candidates = true;
            }
            നിർത്തുക;
        അവസ്ഥ IMN_CLOSECANDIDATE:
            SDL_DebugIMELog("IMN_CLOSECANDIDATE");
            എങ്കിൽ (videodata->ime_internal_candidates) {
                trap = true;
                videodata->ime_update_candidates = false;
                IME_CloseCandidateList(videodata);
            }
            നിർത്തുക;
        അവസ്ഥ IMN_PRIVATE:
        {
            DWORD dwId = IME_GetId(videodata, 0);
            SDL_DebugIMELog("IMN_PRIVATE %u", dwId);
            IME_GetReadingString(videodata, hwnd);
            തിരഞ്ഞെടുപ്പ് (dwId) {
            അവസ്ഥ IMEID_CHT_VER42:
            അവസ്ഥ IMEID_CHT_VER43:
            അവസ്ഥ IMEID_CHT_VER44:
            അവസ്ഥ IMEID_CHS_VER41:
            അവസ്ഥ IMEID_CHS_VER42:
                എങ്കിൽ (*lParam == 1 || *lParam == 2) {
                    trap = true;
                }

                നിർത്തുക;
            അവസ്ഥ IMEID_CHT_VER50:
            അവസ്ഥ IMEID_CHT_VER51:
            അവസ്ഥ IMEID_CHT_VER52:
            അവസ്ഥ IMEID_CHT_VER60:
            അവസ്ഥ IMEID_CHS_VER53:
                എങ്കിൽ (*lParam == 16 || *lParam == 17 || *lParam == 26 || *lParam == 27 || *lParam == 28) {
                    trap = true;
                }
                നിർത്തുക;
            }
        } നിർത്തുക;
        സ്ഥിരസ്ഥിതി:
            trap = true;
            നിർത്തുക;
        }
        നിർത്തുക;
    }
    തിരികെ trap;
}

ശൂന്യം WIN_UpdateIMECandidates(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;

    എങ്കിൽ (videodata->ime_update_candidates) {
        IME_GetCandidateList(videodata, videodata->ime_hwnd_current);
        videodata->ime_update_candidates = false;
    }
}

#endif // SDL_DISABLE_WINDOWS_IME

#endif // SDL_VIDEO_DRIVER_WINDOWS
