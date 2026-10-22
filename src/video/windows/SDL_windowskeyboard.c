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

#অন্তর্ভাব "../../events/SDL_keyboard_c.h"
#অন্তর্ভাব "../../events/scancodes_windows.h"

#অন্তর্ভাব <imm.h>
#অন্তর্ভাব <oleauto.h>

#ifndef SDL_DISABLE_WINDOWS_IME
#যদি 0
#define SDL_DebugIMELog SDL_Log
#অন্যথা
#define SDL_DebugIMELog(...)
#endif
স্থির bool IME_Init(SDL_VideoData *videodata, SDL_Window *window);
স্থির শূন্য IME_Enable(SDL_VideoData *videodata, HWND hwnd);
স্থির শূন্য IME_Disable(SDL_VideoData *videodata, HWND hwnd);
স্থির শূন্য IME_Set_Text_প্রবেশ_Area(SDL_VideoData *videodata, HWND hwnd, ধ্রুব SDL_Rect *rect, পূর্ণাঙ্ক cursor);
স্থির শূন্য IME_ClearComposition(SDL_VideoData *videodata);
স্থির শূন্য IME_GetCandidateList(SDL_VideoData *videodata, HWND hwnd);
স্থির শূন্য IME_Quit(SDL_VideoData *videodata);
#অন্যথা
স্থির শূন্য IME_Set_Text_প্রবেশ_Area(SDL_VideoData *videodata, HWND hwnd, ধ্রুব SDL_Rect *rect, পূর্ণাঙ্ক cursor);
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
স্থির সংরচনা WIN_KeymapCache
{
    HKL keyboard_layout;
    SDL_Keymap *keymap;
} keymap_cache[4];

স্থির পূর্ণাঙ্ক keymap_cache_size;

স্থির SDL_Keymap *WIN_GetCachedKeymap(HKL layout)
{
    SDL_Keymap *keymap = রিক্ত;
    প্রতি (পূর্ণাঙ্ক i = 0; i < keymap_cache_size; ++i) {
        যদি (keymap_cache[i].keyboard_layout == layout) {
            keymap = keymap_cache[i].keymap;

            // Move the map to the front of the list.
            যদি (i) {
                SDL_memmove(keymap_cache + 1, keymap_cache, পরিমাণ(সংরচনা WIN_KeymapCache) * i);
                keymap_cache[0].keyboard_layout = layout;
                keymap_cache[0].keymap = keymap;
            }
            ভঙ্গ;
        }
    }
    প্রত্যাগম keymap;
}

স্থির শূন্য WIN_CacheKeymap(HKL layout, SDL_Keymap *keymap)
{
    // If the cache is full, evict the last keymap.
    যদি (keymap_cache_size == SDL_arraysize(keymap_cache)) {
        SDL_DestroyKeymap(keymap_cache[--keymap_cache_size].keymap);
    }

    // Move all elements down by one.
    যদি (keymap_cache_size) {
        SDL_memmove(keymap_cache + 1, keymap_cache, পরিমাণ(সংরচনা WIN_KeymapCache) * keymap_cache_size);
    }

    keymap_cache[0].keyboard_layout = layout;
    keymap_cache[0].keymap = keymap;
    ++keymap_cache_size;
}

স্থির SDL_Keymap *WIN_BuildKeymap(শূন্য)
{
    SDL_Scancode scancode;
    BYTE keyboardState[256] = { 0 };
    WCHAR buffer[16];
    ধ্রুব SDL_Keymod mods[] = {
        SDL_KMOD_NONE,
        SDL_KMOD_SHIFT,
        SDL_KMOD_CAPS,
        (SDL_KMOD_SHIFT | SDL_KMOD_CAPS),
        SDL_KMOD_MODE,
        (SDL_KMOD_MODE | SDL_KMOD_SHIFT),
        (SDL_KMOD_MODE | SDL_KMOD_CAPS),
        (SDL_KMOD_MODE | SDL_KMOD_SHIFT | SDL_KMOD_CAPS)
    };

    WIN_Reset_Dead_চাবিগুলি();

    SDL_Keymap *keymap = SDL_CreateKeymap(false);
    যদি (!keymap) {
        প্রত্যাগম রিক্ত;
    }

    প্রতি (পূর্ণাঙ্ক m = 0; m < SDL_arraysize(mods); ++m) {
        প্রতি (পূর্ণাঙ্ক i = 0; i < SDL_arraysize(windows_scancode_table); i++) {
            পূর্ণাঙ্ক vk, sc, result;
            Uint32 *ch = 0;

            // Make sure this scancode is a valid character scancode
            scancode = windows_scancode_table[i];
            যদি (scancode == SDL_SCANCODE_UNKNOWN ||
                scancode == SDL_SCANCODE_DELETE ||
                (SDL_GetKeymapKeycode(রিক্ত, scancode, SDL_KMOD_NONE) & SDLK_SCANCODE_MASK)) {

                // The Colemak mapping swaps Backspace and CapsLock
                যদি (mods[m] == SDL_KMOD_NONE &&
                    (scancode == SDL_SCANCODE_CAPSLOCK ||
                     scancode == SDL_SCANCODE_BACKSPACE)) {
                    vk = LOBYTE(Map_Virtual_চাবি(i, MAPVK_VSC_TO_VK));
                    যদি (vk == VK_CAPITAL) {
                        SDL_SetKeymapEntry(keymap, scancode, mods[m], SDLK_CAPSLOCK);
                    } অন্যথা যদি (vk == VK_BACK) {
                        SDL_SetKeymapEntry(keymap, scancode, mods[m], SDLK_BACKSPACE);
                    }
                }
                অনুবর্ত;
            }

            // Unpack the single byte index to make the scan code.
            sc = MAKEWORD(i & 0x7f, (i & 0x80) ? 0xe0 : 0x00);
            vk = LOBYTE(Map_Virtual_চাবি(sc, MAPVK_VSC_TO_VK));
            যদি (!vk) {
                অনুবর্ত;
            }

            // Update the keyboard state for the modifiers
            keyboardState[VK_SHIFT] = (mods[m] & SDL_KMOD_SHIFT) ? 0x80 : 0x00;
            keyboardState[VK_CAPITAL] = (mods[m] & SDL_KMOD_CAPS) ? 0x01 : 0x00;
            keyboardState[VK_CONTROL] = (mods[m] & SDL_KMOD_MODE) ? 0x80 : 0x00;
            keyboardState[VK_MENU] = (mods[m] & SDL_KMOD_MODE) ? 0x80 : 0x00;

            result = ToUnicode(vk, sc, keyboardState, buffer, 16, 0);
            buffer[SDL_abs(result)] = 0;

            // Convert UTF-16 to UTF-32 code points
            ch = (Uint32 *)SDL_iconv_string("UTF-32LE", "UTF-16LE", (ধ্রুব বর্ণ *)buffer, (SDL_abs(result) + 1) * পরিমাণ(WCHAR));
            যদি (ch) {
                /* Windows keyboard layouts can emit several UTF-32 code points on a single key press.
                 * Use <U+FFFD REPLACEMENT CHARACTER> since we cannot fit into single SDL_Keycode value in SDL keymap.
                 * See https://kbdlayout.info/features/ligatures for a list of such keys. */
                SDL_SetKeymapEntry(keymap, scancode, mods[m], ch[1] == 0 ? ch[0] : 0xfffd);
                SDL_free(ch);
            } অন্যথা {
                // The default keymap doesn't have any SDL_KMOD_MODE entries, so we don't need to override them
                যদি (!(mods[m] & SDL_KMOD_MODE)) {
                    SDL_SetKeymapEntry(keymap, scancode, mods[m], SDLK_UNKNOWN);
                }
            }

            যদি (result < 0) {
                WIN_Reset_Dead_চাবিগুলি();
            }
        }
    }

    প্রত্যাগম keymap;
}

শূন্য WIN_UpdateKeymap(bool send_event)
{
    HKL layout = GetKeyboardLayout(0);
    SDL_Keymap *keymap = WIN_GetCachedKeymap(layout);
    যদি (!keymap) {
        keymap = WIN_BuildKeymap();
        যদি (keymap) {
            WIN_CacheKeymap(layout, keymap);
        }
    }

    SDL_SetKeymap(keymap, send_event);
}

// Alphabetic scancodes for PC keyboards
শূন্য WIN_InitKeyboard(SDL_VideoDevice *_this)
{
#ifndef SDL_DISABLE_WINDOWS_IME
    SDL_VideoData *data = _this->internal;

    data->ime_candlistindexbase = 1;
    data->ime_composition_length = 32 * পরিমাণ(WCHAR);
    data->ime_composition = (WCHAR *)SDL_calloc(data->ime_composition_length, পরিমাণ(WCHAR));
#endif // !SDL_DISABLE_WINDOWS_IME

    // Build and bind the current keymap.
    WIN_UpdateKeymap(false);

    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");
    SDL_SetScancodeName(SDL_SCANCODE_LGUI, "Left Windows");
    SDL_SetScancodeName(SDL_SCANCODE_RGUI, "Right Windows");

    // Are system caps/num/scroll lock active? Set our state to match.
    SDL_ToggleModState(SDL_KMOD_CAPS, (Get_চাবি_State(VK_CAPITAL) & 0x0001) ? true : false);
    SDL_ToggleModState(SDL_KMOD_অঙ্ক, (Get_চাবি_State(VK_NUMLOCK) & 0x0001) ? true : false);
    SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_চাবি_State(VK_SCROLL) & 0x0001) ? true : false);
}

শূন্য WIN_QuitKeyboard(SDL_VideoDevice *_this)
{
#ifndef SDL_DISABLE_WINDOWS_IME
    SDL_VideoData *data = _this->internal;

    IME_Quit(data);

    যদি (data->ime_composition) {
        SDL_free(data->ime_composition);
        data->ime_composition = রিক্ত;
    }
#endif // !SDL_DISABLE_WINDOWS_IME

    প্রতি (পূর্ণাঙ্ক i = 0; i < keymap_cache_size; ++i) {
        SDL_DestroyKeymap(keymap_cache[i].keymap);
    }
    SDL_zeroa(keymap_cache);
    keymap_cache_size = 0;
}

শূন্য WIN_Reset_Dead_চাবিগুলি(শূন্য)
{
    /*
    if a deadkey has been typed, but not the next character (which the deadkey might modify),
    this tries to undo the effect pressing the deadkey.
    see: http://archives.miloush.net/michkap/archive/2006/09/10/748775.html
    */
    BYTE keyboardState[256];
    WCHAR buffer[16];
    পূর্ণাঙ্ক vk, sc, result, i;

    যদি (!GetKeyboardState(keyboardState)) {
        প্রত্যাগম;
    }

    vk = VK_SPACE;
    sc = Map_Virtual_চাবি(vk, MAPVK_VK_TO_VSC);
    যদি (sc == 0) {
        // the keyboard doesn't have this key
        প্রত্যাগম;
    }

    প্রতি (i = 0; i < 5; i++) {
        result = ToUnicode(vk, sc, keyboardState, buffer, 16, 0);
        যদি (result > 0) {
            // success
            প্রত্যাগম;
        }
    }
}

bool WIN_Start_Text_প্রবেশ(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    WIN_Reset_Dead_চাবিগুলি();

#ifndef SDL_DISABLE_WINDOWS_IME
    HWND hwnd = window->internal->hwnd;
    SDL_VideoData *videodata = _this->internal;
    IME_Init(videodata, window);
    IME_Enable(videodata, hwnd);

    WIN_Update_Text_প্রবেশ_Area(_this, window);
#endif // !SDL_DISABLE_WINDOWS_IME

    প্রত্যাগম true;
}

bool WIN_Stop_Text_প্রবেশ(SDL_VideoDevice *_this, SDL_Window *window)
{
    WIN_Reset_Dead_চাবিগুলি();

#ifndef SDL_DISABLE_WINDOWS_IME
    HWND hwnd = window->internal->hwnd;
    SDL_VideoData *videodata = _this->internal;
    IME_Init(videodata, window);
    IME_Disable(videodata, hwnd);
#endif // !SDL_DISABLE_WINDOWS_IME

    প্রত্যাগম true;
}

bool WIN_Update_Text_প্রবেশ_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_WindowData *data = window->internal;

    IME_Set_Text_প্রবেশ_Area(videodata, data->hwnd, &window->text_প্রবেশ_rect, window->text_প্রবেশ_cursor);
    প্রত্যাগম true;
}

bool WIN_ClearComposition(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifndef SDL_DISABLE_WINDOWS_IME
    SDL_VideoData *videodata = _this->internal;

    IME_ClearComposition(videodata);
#endif
    প্রত্যাগম true;
}

#ifdef SDL_DISABLE_WINDOWS_IME

bool WIN_HandleIMEMessage(HWND hwnd, UINT বার্তা, WPARAM wParam, LPARAM *lParam, SDL_VideoData *videodata)
{
    প্রত্যাগম false;
}

শূন্য WIN_UpdateIMECandidates(SDL_VideoDevice *_this)
{
    প্রত্যাগম;
}

#অন্যথা

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

স্থির শূন্য IME_Update_প্রবেশ_Locale(SDL_VideoData *videodata);
স্থির শূন্য IME_SetWindow(SDL_VideoData *videodata, SDL_Window *window);
স্থির শূন্য IME_SetupAPI(SDL_VideoData *videodata);
স্থির DWORD IME_GetId(SDL_VideoData *videodata, UINT uIndex);
স্থির শূন্য IME_SendEditingEvent(SDL_VideoData *videodata);
স্থির শূন্য IME_SendClearComposition(SDL_VideoData *videodata);

স্থির bool IME_Init(SDL_VideoData *videodata, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;

    যদি (videodata->ime_initialized) {
        প্রত্যাগম true;
    }

    ধ্রুব বর্ণ *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);
    যদি (hint && SDL_strstr(hint, "composition")) {
        videodata->ime_internal_composition = true;
    }
    যদি (hint && SDL_strstr(hint, "candidates")) {
        videodata->ime_internal_candidates = true;
    }

    videodata->ime_hwnd_main = hwnd;
    videodata->ime_initialized = true;
    videodata->ime_himm32 = SDL_LoadObject("imm32.dll");
    যদি (!videodata->ime_himm32) {
        videodata->ime_available = false;
        SDL_ClearError();
        প্রত্যাগম true;
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
    যদি (!videodata->ime_himc) {
        videodata->ime_available = false;
        IME_Disable(videodata, hwnd);
        প্রত্যাগম true;
    }
    videodata->ime_available = true;
    IME_Update_প্রবেশ_Locale(videodata);
    IME_SetupAPI(videodata);
    IME_Update_প্রবেশ_Locale(videodata);
    IME_Disable(videodata, hwnd);
    প্রত্যাগম true;
}

স্থির শূন্য IME_Enable(SDL_VideoData *videodata, HWND hwnd)
{
    যদি (!videodata->ime_initialized || !videodata->ime_hwnd_current) {
        প্রত্যাগম;
    }

    যদি (!videodata->ime_available) {
        IME_Disable(videodata, hwnd);
        প্রত্যাগম;
    }
    যদি (videodata->ime_hwnd_current == videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_current, videodata->ime_himc);
    }

    videodata->ime_enabled = true;
    IME_Update_প্রবেশ_Locale(videodata);
}

স্থির শূন্য IME_Disable(SDL_VideoData *videodata, HWND hwnd)
{
    যদি (!videodata->ime_initialized || !videodata->ime_hwnd_current) {
        প্রত্যাগম;
    }

    IME_ClearComposition(videodata);
    যদি (videodata->ime_hwnd_current == videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_current, (HIMC)0);
    }

    videodata->ime_enabled = false;
}

স্থির শূন্য IME_Quit(SDL_VideoData *videodata)
{
    যদি (!videodata->ime_initialized) {
        প্রত্যাগম;
    }

    যদি (videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_main, videodata->ime_himc);
    }

    videodata->ime_hwnd_main = 0;
    videodata->ime_himc = 0;
    যদি (videodata->ime_himm32) {
        SDL_UnloadObject(videodata->ime_himm32);
        videodata->ime_himm32 = 0;
    }
    প্রতি (পূর্ণাঙ্ক i = 0; i < videodata->ime_candcount; ++i) {
        SDL_free(videodata->ime_candidates[i]);
        videodata->ime_candidates[i] = রিক্ত;
    }
    videodata->ime_initialized = false;
}

স্থির শূন্য IME_GetReadingString(SDL_VideoData *videodata, HWND hwnd)
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
    যদি (!id) {
        প্রত্যাগম;
    }

    himc = ImmGetContext(hwnd);
    যদি (!himc) {
        প্রত্যাগম;
    }

    যদি (videodata->GetReadingString) {
        len = videodata->GetReadingString(himc, 0, 0, &err, &vertical, &maxuilen);
        যদি (len) {
            যদি (len > SDL_arraysize(buffer)) {
                len = SDL_arraysize(buffer);
            }

            len = videodata->GetReadingString(himc, len, s, &err, &vertical, &maxuilen);
        }
        SDL_wcslcpy(videodata->ime_readingstring, s, len);
    } অন্যথা {
        LPINPUTCONTEXT2 lpimc = videodata->ImmLockIMC(himc);
        LPBYTE p = 0;
        s = 0;
        বিকল্প (id) {
        পক্ষ IMEID_CHT_VER42:
        পক্ষ IMEID_CHT_VER43:
        পক্ষ IMEID_CHT_VER44:
            p = *(LPBYTE *)((LPBYTE)videodata->ImmLockIMCC(lpimc->hPrivate) + 24);
            যদি (!p) {
                ভঙ্গ;
            }

            len = *(DWORD *)(p + 7 * 4 + 32 * 4);
            s = (WCHAR *)(p + 56);
            ভঙ্গ;
        পক্ষ IMEID_CHT_VER51:
        পক্ষ IMEID_CHT_VER52:
        পক্ষ IMEID_CHS_VER53:
            p = *(LPBYTE *)((LPBYTE)videodata->ImmLockIMCC(lpimc->hPrivate) + 4);
            যদি (!p) {
                ভঙ্গ;
            }

            p = *(LPBYTE *)(p + 1 * 4 + 5 * 4);
            যদি (!p) {
                ভঙ্গ;
            }

            len = *(DWORD *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4 + 16 * 2);
            s = (WCHAR *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4);
            ভঙ্গ;
        পক্ষ IMEID_CHS_VER41:
        {
            পূর্ণাঙ্ক offset = (IME_GetId(videodata, 1) >= 0x00000002) ? 8 : 7;
            p = *(LPBYTE *)((LPBYTE)videodata->ImmLockIMCC(lpimc->hPrivate) + offset * 4);
            যদি (!p) {
                ভঙ্গ;
            }

            len = *(DWORD *)(p + 7 * 4 + 16 * 2 * 4);
            s = (WCHAR *)(p + 6 * 4 + 16 * 2 * 1);
        } ভঙ্গ;
        পক্ষ IMEID_CHS_VER42:
            p = *(LPBYTE *)((LPBYTE)videodata->ImmLockIMCC(lpimc->hPrivate) + 1 * 4 + 1 * 4 + 6 * 4);
            যদি (!p) {
                ভঙ্গ;
            }

            len = *(DWORD *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4 + 16 * 2);
            s = (WCHAR *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4);
            ভঙ্গ;
        }
        যদি (s) {
            size_t size = SDL_min((size_t)(len + 1), SDL_arraysize(videodata->ime_readingstring));
            SDL_wcslcpy(videodata->ime_readingstring, s, size);
        }

        videodata->ImmUnlockIMCC(lpimc->hPrivate);
        videodata->ImmUnlockIMC(himc);
    }
    ImmReleaseContext(hwnd, himc);
    IME_SendEditingEvent(videodata);
}

স্থির শূন্য IME_প্রবেশ_Lang_Changed(SDL_VideoData *videodata)
{
    UINT lang = PRIMLANG();
    IME_Update_প্রবেশ_Locale(videodata);

    IME_SetupAPI(videodata);
    যদি (lang != PRIMLANG()) {
        IME_ClearComposition(videodata);
    }
}

স্থির DWORD IME_GetId(SDL_VideoData *videodata, UINT uIndex)
{
    স্থির HKL hklprev = 0;
    স্থির DWORD dwRet[2] = { 0 };
    DWORD dwVerSize = 0;
    LPVOID lpVerBuffer = 0;
    LPVOID lpVerData = 0;
    UINT cbVerData = 0;
    বর্ণ szTemp[256];
    HKL hkl = 0;
    DWORD dwLang = 0;
    SDL_assert(uIndex < SDL_arraysize(dwRet));

    hkl = videodata->ime_hkl;
    যদি (hklprev == hkl) {
        প্রত্যাগম dwRet[uIndex];
    }
    hklprev = hkl;

    SDL_assert(uIndex == 0);
    dwLang = ((DWORD_PTR)hkl & 0xffff);
    // FIXME: What does this do?
    যদি (videodata->ime_internal_candidates && dwLang == LANG_CHT) {
        dwRet[0] = IMEID_CHT_VER_VISTA;
        dwRet[1] = 0;
        প্রত্যাগম dwRet[0];
    }
    যদি (hkl != CHT_HKL_NEW_PHONETIC && hkl != CHT_HKL_NEW_CHANG_JIE && hkl != CHT_HKL_NEW_QUICK && hkl != CHT_HKL_HK_CANTONESE && hkl != CHS_HKL) {
        dwRet[0] = dwRet[1] = 0;
        প্রত্যাগম dwRet[0];
    }
    যদি (!ImmGetIMEFileNameA(hkl, szTemp, পরিমাণ(szTemp) - 1)) {
        dwRet[0] = dwRet[1] = 0;
        প্রত্যাগম dwRet[0];
    }
    যদি (!videodata->GetReadingString) {
#define LCID_INVARIANT MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT)
        যদি (CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, szTemp, -1, CHT_IMEFILENAME1, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, szTemp, -1, CHT_IMEFILENAME2, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, szTemp, -1, CHT_IMEFILENAME3, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, szTemp, -1, CHS_IMEFILENAME1, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, szTemp, -1, CHS_IMEFILENAME2, -1) != 2) {
            dwRet[0] = dwRet[1] = 0;
            প্রত্যাগম dwRet[0];
        }
#undef LCID_INVARIANT
        dwVerSize = GetFileVersionInfoSizeA(szTemp, রিক্ত);
        যদি (dwVerSize) {
            lpVerBuffer = SDL_malloc(dwVerSize);
            যদি (lpVerBuffer) {
                যদি (GetFileVersionInfoA(szTemp, 0, dwVerSize, lpVerBuffer)) {
                    যদি (Ver_Query_মান_A(lpVerBuffer, "\\", &lpVerData, &cbVerData)) {
#define pVerFixedInfo ((VS_FIXEDFILEINFO FAR *)lpVerData)
                        DWORD dwVer = pVerFixedInfo->dwFileVersionMS;
                        dwVer = (dwVer & 0x00ff0000) << 8 | (dwVer & 0x000000ff) << 16;
                        যদি ((videodata->GetReadingString) ||
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
                            প্রত্যাগম dwRet[0];
                        }
#undef pVerFixedInfo
                    }
                }
            }
            SDL_free(lpVerBuffer);
        }
    }
    dwRet[0] = dwRet[1] = 0;
    প্রত্যাগম dwRet[0];
}

স্থির শূন্য IME_SetupAPI(SDL_VideoData *videodata)
{
    বর্ণ ime_file[MAX_PATH + 1];
    SDL_SharedObject *hime = 0;
    HKL hkl = 0;
    videodata->GetReadingString = রিক্ত;
    videodata->ShowReadingWindow = রিক্ত;

    hkl = videodata->ime_hkl;
    যদি (!ImmGetIMEFileNameA(hkl, ime_file, পরিমাণ(ime_file) - 1)) {
        প্রত্যাগম;
    }

    hime = SDL_LoadObject(ime_file);
    যদি (!hime) {
        প্রত্যাগম;
    }

    /* *INDENT-OFF* */ // clang-format off
    videodata->GetReadingString = (UINT (WINAPI *)(HIMC, UINT, LPWSTR, PINT, BOOL*, PUINT))
        SDL_LoadFunction(hime, "GetReadingString");
    videodata->ShowReadingWindow = (BOOL (WINAPI *)(HIMC, BOOL))
        SDL_LoadFunction(hime, "ShowReadingWindow");
    /* *INDENT-ON* */ // clang-format on

    যদি (videodata->ShowReadingWindow) {
        HIMC himc = ImmGetContext(videodata->ime_hwnd_current);
        যদি (himc) {
            videodata->ShowReadingWindow(himc, FALSE);
            ImmReleaseContext(videodata->ime_hwnd_current, himc);
        }
    }
}

স্থির শূন্য IME_SetWindow(SDL_VideoData *videodata, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;

    যদি (hwnd != videodata->ime_hwnd_current) {
        videodata->ime_hwnd_current = hwnd;
        SDL_zero(videodata->ime_composition_area);
        SDL_zero(videodata->ime_candidate_area);
    }

    IME_Set_Text_প্রবেশ_Area(videodata, hwnd, &window->text_প্রবেশ_rect, window->text_প্রবেশ_cursor);
}

#endif

স্থির শূন্য IME_Set_Text_প্রবেশ_Area(SDL_VideoData *videodata, HWND hwnd, ধ্রুব SDL_Rect *rect, পূর্ণাঙ্ক cursor)
{
    HIMC himc;

    himc = ImmGetContext(hwnd);
    যদি (himc) {
        COMPOSITIONFORM cof;
        CANDIDATEFORM caf;
        পূর্ণাঙ্ক font_height = rect->h;

        LOGFONTW font;
        যদি (ImmGetCompositionFontW(himc, &font)) {
            font_height = font.lfHeight;
        }

        SDL_zero(cof);
        cof.dwStyle = CFS_RECT;
        cof.ptCurrentPos.x = rect->x + cursor;
        cof.ptCurrentPos.y = rect->y + (rect->h - font_height) / 2;
        cof.rcArea.বাম = rect->x;
        cof.rcArea.ডান = (LONG)rect->x + rect->w;
        cof.rcArea.শীর্ষ = rect->y;
        cof.rcArea.bottom = (LONG)rect->y + rect->h;
        যদি (SDL_memcmp(&cof, &videodata->ime_composition_area, পরিমাণ(cof)) != 0) {
            SDL_copyp(&videodata->ime_composition_area, &cof);
            ImmSetCompositionWindow(himc, &cof);
        }

        SDL_zero(caf);
        caf.dwIndex = 0;
        caf.dwStyle = CFS_EXCLUDE;
        caf.ptCurrentPos.x = rect->x + cursor;
        caf.ptCurrentPos.y = rect->y;
        caf.rcArea.বাম = rect->x;
        caf.rcArea.ডান = (LONG)rect->x + rect->w;
        caf.rcArea.শীর্ষ = rect->y;
        caf.rcArea.bottom = (LONG)rect->y + rect->h;
        যদি (SDL_memcmp(&caf, &videodata->ime_candidate_area, পরিমাণ(caf)) != 0) {
            SDL_copyp(&videodata->ime_candidate_area, &caf);
            ImmSetCandidateWindow(himc, &caf);
        }

        ImmReleaseContext(hwnd, himc);
    }
}

#ifndef SDL_DISABLE_WINDOWS_IME

স্থির শূন্য IME_Update_প্রবেশ_Locale(SDL_VideoData *videodata)
{
    HKL hklnext = GetKeyboardLayout(0);

    যদি (hklnext == videodata->ime_hkl) {
        প্রত্যাগম;
    }

    videodata->ime_hkl = hklnext;
    videodata->ime_horizontal_candidates = (PRIMLANG() == LANG_KOREAN || LANG() == LANG_CHS);
    videodata->ime_candlistindexbase = (videodata->ime_hkl == CHT_HKL_DAYI) ? 0 : 1;
}

স্থির শূন্য IME_ClearComposition(SDL_VideoData *videodata)
{
    HIMC himc = 0;
    যদি (!videodata->ime_initialized) {
        প্রত্যাগম;
    }

    himc = ImmGetContext(videodata->ime_hwnd_current);
    যদি (!himc) {
        প্রত্যাগম;
    }

    ImmNotifyIME(himc, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
    ImmSetCompositionString(himc, SCS_SETSTR, TEXT(""), পরিমাণ(TCHAR), TEXT(""), পরিমাণ(TCHAR));

    ImmNotifyIME(himc, NI_CLOSECANDIDATE, 0, 0);
    ImmReleaseContext(videodata->ime_hwnd_current, himc);
    IME_SendClearComposition(videodata);
}

স্থির শূন্য IME_GetCompositionString(SDL_VideoData *videodata, HIMC himc, LPARAM *lParam, DWORD string)
{
    LONG length;
    DWORD dwLang = ((DWORD_PTR)videodata->ime_hkl & 0xffff);

    যদি (*lParam & GCS_CURSORPOS) {
        videodata->ime_cursor = LOWORD(ImmGetCompositionStringW(himc, GCS_CURSORPOS, 0, 0));
    }
    videodata->ime_selected_start = 0;
    videodata->ime_selected_length = 0;
    SDL_DebugIMELog("Cursor = %d", videodata->ime_cursor);

    length = ImmGetCompositionStringW(himc, string, রিক্ত, 0);
    যদি (length > 0 && videodata->ime_composition_length < length) {
        SDL_free(videodata->ime_composition);

        videodata->ime_composition = (WCHAR *)SDL_malloc(length + পরিমাণ(WCHAR));
        videodata->ime_composition_length = length;
    }

    length = ImmGetCompositionStringW(himc, string, videodata->ime_composition, videodata->ime_composition_length);
    যদি (length < 0) {
        length = 0;
    }
    length /= পরিমাণ(WCHAR);

    যদি (!(*lParam & GCS_CURSORPOS)) {
        // If the IME doesn't support GCS_CURSORPOS, default the cursor to the end of the composition.
        videodata->ime_cursor = length;
    }

    যদি ((dwLang == LANG_CHT || dwLang == LANG_CHS) &&
        videodata->ime_cursor > 0 &&
        videodata->ime_cursor < (পূর্ণাঙ্ক)(videodata->ime_composition_length / পরিমাণ(WCHAR)) &&
        (videodata->ime_composition[0] == 0x3000 || videodata->ime_composition[0] == 0x0020)) {
        // Traditional Chinese IMEs add a placeholder U+3000
        // Simplified Chinese IMEs seem to add a placeholder U+0020 sometimes
        প্রতি (পূর্ণাঙ্ক i = videodata->ime_cursor + 1; i < length; ++i) {
            videodata->ime_composition[i - 1] = videodata->ime_composition[i];
        }
        --length;
    }

    videodata->ime_composition[length] = 0;

    length = ImmGetCompositionStringW(himc, GCS_COMPATTR, রিক্ত, 0);
    যদি (length > 0) {
        Uint8 *attributes = (Uint8 *)SDL_malloc(length);
        যদি (attributes) {
            পূর্ণাঙ্ক start = 0;
            পূর্ণাঙ্ক end = 0;

            length = ImmGetCompositionString(himc, GCS_COMPATTR, attributes, length);
            যদি (length < 0) {
                length = 0;
            }

            প্রতি (LONG i = 0; i < length; ++i) {
                SDL_DebugIMELog("attrib[%d] = %d", i, attributes[i]);
            }

            প্রতি (start = 0; start < length; ++start) {
                যদি (attributes[start] == ATTR_TARGET_CONVERTED || attributes[start] == ATTR_TARGET_NOTCONVERTED) {
                    ভঙ্গ;
                }
            }

            প্রতি (end = start; end < length; ++end) {
                যদি (attributes[end] != ATTR_TARGET_CONVERTED && attributes[end] != ATTR_TARGET_NOTCONVERTED) {
                    ভঙ্গ;
                }
            }

            যদি (end > start) {
                videodata->ime_selected_start = start;
                videodata->ime_selected_length = end - start;
            }

            SDL_free(attributes);
        }
    }
}

স্থির শূন্য IME_Send_প্রবেশ_Event(SDL_VideoData *videodata)
{
    বর্ণ *s = 0;
    s = WIN_StringToUTF8W(videodata->ime_composition);
    SDL_SendKeyboardText(s);
    SDL_free(s);

    videodata->ime_composition[0] = 0;
    videodata->ime_readingstring[0] = 0;
    videodata->ime_cursor = 0;
}

স্থির শূন্য IME_SendEditingEvent(SDL_VideoData *videodata)
{
    বর্ণ *s = রিক্ত;
    WCHAR *buffer = রিক্ত;
    size_t size = videodata->ime_composition_length;
    যদি (videodata->ime_readingstring[0]) {
        size_t len = SDL_min(SDL_wcslen(videodata->ime_composition), (size_t)videodata->ime_cursor);

        size += পরিমাণ(videodata->ime_readingstring);
        buffer = (WCHAR *)SDL_malloc(size + পরিমাণ(WCHAR));
        যদি (!buffer) {
            প্রত্যাগম;
        }
        buffer[0] = 0;

        SDL_wcslcpy(buffer, videodata->ime_composition, len + 1);
        SDL_wcslcat(buffer, videodata->ime_readingstring, size);
        SDL_wcslcat(buffer, &videodata->ime_composition[len], size);
    } অন্যথা {
        buffer = (WCHAR *)SDL_malloc(size + পরিমাণ(WCHAR));
        যদি (!buffer) {
            প্রত্যাগম;
        }
        buffer[0] = 0;
        SDL_wcslcpy(buffer, videodata->ime_composition, size);
    }

    s = WIN_StringToUTF8W(buffer);
    যদি (s) {
        যদি (videodata->ime_readingstring[0]) {
            SDL_SendEditingText(s, videodata->ime_cursor, (পূর্ণাঙ্ক)SDL_wcslen(videodata->ime_readingstring));
        } অন্যথা যদি (videodata->ime_cursor == videodata->ime_selected_start) {
            SDL_SendEditingText(s, videodata->ime_selected_start, videodata->ime_selected_length);
        } অন্যথা {
            SDL_SendEditingText(s, videodata->ime_cursor, 0);
        }
        যদি (*s) {
            videodata->ime_needs_clear_composition = true;
        }
        SDL_free(s);
    }
    SDL_free(buffer);
}

স্থির শূন্য IME_SendClearComposition(SDL_VideoData *videodata)
{
    যদি (videodata->ime_needs_clear_composition) {
        SDL_SendEditingText("", 0, 0);
        videodata->ime_needs_clear_composition = false;
    }
}

স্থির bool IME_OpenCandidateList(SDL_VideoData *videodata)
{
    videodata->ime_candidates_open = true;
    videodata->ime_candcount = 0;
    প্রত্যাগম true;
}

স্থির শূন্য IME_AddCandidate(SDL_VideoData *videodata, UINT i, LPCWSTR candidate)
{
    যদি (videodata->ime_candidates[i]) {
        SDL_free(videodata->ime_candidates[i]);
        videodata->ime_candidates[i] = রিক্ত;
    }

    SDL_COMPILE_TIME_ASSERT(IME_CANDIDATE_INDEXING_REQUIRES, MAX_CANDLIST == 10);
    বর্ণ *candidate_utf8 = WIN_StringToUTF8W(candidate);
    SDL_asprintf(&videodata->ime_candidates[i], "%d %s", ((i + videodata->ime_candlistindexbase) % 10), candidate_utf8);
    SDL_free(candidate_utf8);

    videodata->ime_candcount = (i + 1);
}

স্থির শূন্য IME_SendCandidateList(SDL_VideoData *videodata)
{
    SDL_SendEditingTextCandidates(videodata->ime_candidates, videodata->ime_candcount, videodata->ime_candsel, videodata->ime_horizontal_candidates);
}

স্থির শূন্য IME_CloseCandidateList(SDL_VideoData *videodata)
{
    videodata->ime_candidates_open = false;

    যদি (videodata->ime_candcount > 0) {
        প্রতি (পূর্ণাঙ্ক i = 0; i < videodata->ime_candcount; ++i) {
            SDL_free(videodata->ime_candidates[i]);
            videodata->ime_candidates[i] = রিক্ত;
        }
        videodata->ime_candcount = 0;

        SDL_SendEditingTextCandidates(রিক্ত, 0, -1, false);
    }
}

স্থির শূন্য IME_GetCandidateList(SDL_VideoData *videodata, HWND hwnd)
{
    HIMC himc;
    DWORD size;
    LPCANDIDATELIST cand_list;
    bool has_candidates = false;

    himc = ImmGetContext(hwnd);
    যদি (himc) {
        size = ImmGetCandidateListW(himc, 0, রিক্ত, 0);
        যদি (size != 0) {
            cand_list = (LPCANDIDATELIST)SDL_malloc(size);
            যদি (cand_list != রিক্ত) {
                size = ImmGetCandidateListW(himc, 0, cand_list, size);
                যদি (size != 0) {
                    যদি (IME_OpenCandidateList(videodata)) {
                        UINT i, j;
                        UINT page_start = 0;
                        UINT page_size = 0;

                        videodata->ime_candsel = cand_list->dwSelection;

                        যদি (LANG() == LANG_CHS && IME_GetId(videodata, 0)) {
                            ধ্রুব UINT maxcandchar = 18;
                            size_t cchars = 0;

                            প্রতি (i = 0; i < cand_list->dw_গুনতি; ++i) {
                                size_t len = SDL_wcslen((LPWSTR)((DWORD_PTR)cand_list + cand_list->dwOffset[i])) + 1;
                                যদি (len + cchars > maxcandchar) {
                                    যদি (i > cand_list->dwSelection) {
                                        ভঙ্গ;
                                    }

                                    page_start = i;
                                    cchars = len;
                                } অন্যথা {
                                    cchars += len;
                                }
                            }
                            page_size = i - page_start;
                        } অন্যথা {
                            page_size = SDL_min(cand_list->dwPageSize == 0 ? MAX_CANDLIST : cand_list->dwPageSize, MAX_CANDLIST);
                            page_start = (cand_list->dwSelection / page_size) * page_size;
                        }
                        প্রতি (i = page_start, j = 0; (DWORD)i < cand_list->dw_গুনতি && j < page_size; i++, j++) {
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

    যদি (!has_candidates) {
        IME_CloseCandidateList(videodata);
    }
}

bool WIN_HandleIMEMessage(HWND hwnd, UINT বার্তা, WPARAM wParam, LPARAM *lParam, SDL_VideoData *videodata)
{
    bool trap = false;
    HIMC himc = 0;

    যদি (বার্তা == WM_IME_SETCONTEXT) {
        SDL_DebugIMELog("WM_IME_SETCONTEXT");

        LPARAM element_mask;
        element_mask = ISC_SHOWUIALL;
        যদি (videodata->ime_internal_composition) {
            element_mask &= ~ISC_SHOWUICOMPOSITIONWINDOW;
        }
        যদি (videodata->ime_internal_candidates) {
            element_mask &= ~ISC_SHOWUIALLCANDIDATEWINDOW;
        }
        *lParam &= element_mask;

        প্রত্যাগম false;
    } অন্যথা যদি (বার্তা == WM_IME_STARTCOMPOSITION) {
        SDL_DebugIMELog("WM_IME_STARTCOMPOSITION");
        যদি (videodata->ime_internal_composition) {
            videodata->ime_cursor = 0;
            // Windows may still display a composition dialog even with
            // ISC_SHOWUICOMPOSITIONWINDOW cleared, so trap the message
            // here to prevent that (even when the IME is disabled).
            প্রত্যাগম true;
        }
    }

    যদি (!videodata->ime_initialized || !videodata->ime_available || !videodata->ime_enabled) {
        প্রত্যাগম false;
    }

    বিকল্প (বার্তা) {
    পক্ষ WM_KEYDOWN:
        যদি (wParam == VK_PROCESSKEY) {
            SDL_DebugIMELog("WM_KEYDOWN VK_PROCESSKEY");
            trap = true;
        } অন্যথা {
            SDL_DebugIMELog("WM_KEYDOWN normal");
        }
        ভঙ্গ;
    পক্ষ WM_SYSKEYDOWN:
        যদি (wParam == VK_PROCESSKEY) {
            SDL_DebugIMELog("WM_SYSKEYDOWN VK_PROCESSKEY");
            trap = true;
        } অন্যথা {
            SDL_DebugIMELog("WM_SYSKEYDOWN normal");
        }
        ভঙ্গ;
    পক্ষ WM_INPUTLANGCHANGE:
        SDL_DebugIMELog("WM_INPUTLANGCHANGE");
        IME_প্রবেশ_Lang_Changed(videodata);
        ভঙ্গ;
    পক্ষ WM_IME_COMPOSITION:
        SDL_DebugIMELog("WM_IME_COMPOSITION %x", lParam);
        যদি (videodata->ime_internal_composition) {
            trap = true;
            himc = ImmGetContext(hwnd);
            যদি (*lParam & GCS_RESULTSTR) {
                SDL_DebugIMELog("GCS_RESULTSTR");
                IME_GetCompositionString(videodata, himc, lParam, GCS_RESULTSTR);
                IME_SendClearComposition(videodata);
                IME_Send_প্রবেশ_Event(videodata);
            }
            যদি (*lParam & GCS_COMPSTR) {
                SDL_DebugIMELog("GCS_COMPSTR");
                videodata->ime_readingstring[0] = 0;
                IME_GetCompositionString(videodata, himc, lParam, GCS_COMPSTR);
                IME_SendEditingEvent(videodata);
            }
            ImmReleaseContext(hwnd, himc);
        }
        ভঙ্গ;
    পক্ষ WM_IME_ENDCOMPOSITION:
        SDL_DebugIMELog("WM_IME_ENDCOMPOSITION");
        যদি (videodata->ime_internal_composition) {
            trap = true;
            videodata->ime_composition[0] = 0;
            videodata->ime_readingstring[0] = 0;
            videodata->ime_cursor = 0;
            videodata->ime_selected_start = 0;
            videodata->ime_selected_length = 0;
            IME_SendClearComposition(videodata);
        }
        ভঙ্গ;
    পক্ষ WM_IME_NOTIFY:
        SDL_DebugIMELog("WM_IME_NOTIFY %x", wParam);
        বিকল্প (wParam) {
        পক্ষ IMN_SETCOMPOSITIONWINDOW:
            SDL_DebugIMELog("IMN_SETCOMPOSITIONWINDOW");
            ভঙ্গ;
        পক্ষ IMN_SETCOMPOSITIONFONT:
            SDL_DebugIMELog("IMN_SETCOMPOSITIONFONT");
            ভঙ্গ;
        পক্ষ IMN_SETCANDIDATEPOS:
            SDL_DebugIMELog("IMN_SETCANDIDATEPOS");
            ভঙ্গ;
        পক্ষ IMN_SETCONVERSIONMODE:
        পক্ষ IMN_SETOPENSTATUS:
            SDL_DebugIMELog("%s", wParam == IMN_SETCONVERSIONMODE ? "IMN_SETCONVERSIONMODE" : "IMN_SETOPENSTATUS");
            IME_Update_প্রবেশ_Locale(videodata);
            ভঙ্গ;
        পক্ষ IMN_OPENCANDIDATE:
        পক্ষ IMN_CHANGECANDIDATE:
            SDL_DebugIMELog("%s", wParam == IMN_OPENCANDIDATE ? "IMN_OPENCANDIDATE" : "IMN_CHANGECANDIDATE");
            যদি (videodata->ime_internal_candidates) {
                trap = true;
                videodata->ime_update_candidates = true;
            }
            ভঙ্গ;
        পক্ষ IMN_CLOSECANDIDATE:
            SDL_DebugIMELog("IMN_CLOSECANDIDATE");
            যদি (videodata->ime_internal_candidates) {
                trap = true;
                videodata->ime_update_candidates = false;
                IME_CloseCandidateList(videodata);
            }
            ভঙ্গ;
        পক্ষ IMN_PRIVATE:
        {
            DWORD dwId = IME_GetId(videodata, 0);
            SDL_DebugIMELog("IMN_PRIVATE %u", dwId);
            IME_GetReadingString(videodata, hwnd);
            বিকল্প (dwId) {
            পক্ষ IMEID_CHT_VER42:
            পক্ষ IMEID_CHT_VER43:
            পক্ষ IMEID_CHT_VER44:
            পক্ষ IMEID_CHS_VER41:
            পক্ষ IMEID_CHS_VER42:
                যদি (*lParam == 1 || *lParam == 2) {
                    trap = true;
                }

                ভঙ্গ;
            পক্ষ IMEID_CHT_VER50:
            পক্ষ IMEID_CHT_VER51:
            পক্ষ IMEID_CHT_VER52:
            পক্ষ IMEID_CHT_VER60:
            পক্ষ IMEID_CHS_VER53:
                যদি (*lParam == 16 || *lParam == 17 || *lParam == 26 || *lParam == 27 || *lParam == 28) {
                    trap = true;
                }
                ভঙ্গ;
            }
        } ভঙ্গ;
        স্বভাব:
            trap = true;
            ভঙ্গ;
        }
        ভঙ্গ;
    }
    প্রত্যাগম trap;
}

শূন্য WIN_UpdateIMECandidates(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;

    যদি (videodata->ime_update_candidates) {
        IME_GetCandidateList(videodata, videodata->ime_hwnd_current);
        videodata->ime_update_candidates = false;
    }
}

#endif // SDL_DISABLE_WINDOWS_IME

#endif // SDL_VIDEO_DRIVER_WINDOWS
