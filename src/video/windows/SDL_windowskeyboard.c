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
স্থির bool IME_Init(SDL_Video_তথ্য *videodata, SDL_Window *window);
স্থির শূন্য IME_Enable(SDL_Video_তথ্য *videodata, HWND hwnd);
স্থির শূন্য IME_Disable(SDL_Video_তথ্য *videodata, HWND hwnd);
স্থির শূন্য IME_Set_Text_প্রবেশ_Area(SDL_Video_তথ্য *videodata, HWND hwnd, ধ্রুবক SDL_Rect *rect, পূর্ণসংখ্যা cursor);
স্থির শূন্য IME_ClearComposition(SDL_Video_তথ্য *videodata);
স্থির শূন্য IME_GetCandidateList(SDL_Video_তথ্য *videodata, HWND hwnd);
স্থির শূন্য IME_Quit(SDL_Video_তথ্য *videodata);
#অন্যথা
স্থির শূন্য IME_Set_Text_প্রবেশ_Area(SDL_Video_তথ্য *videodata, HWND hwnd, ধ্রুবক SDL_Rect *rect, পূর্ণসংখ্যা cursor);
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
স্থির কাঠামো WIN_KeymapCache
{
    HKL keyboard_layout;
    SDL_Keymap *keymap;
} keymap_cache[4];

স্থির পূর্ণসংখ্যা keymap_cache_আকার;

স্থির SDL_Keymap *WIN_GetCachedKeymap(HKL layout)
{
    SDL_Keymap *keymap = ফাঁকা;
    জন্য (পূর্ণসংখ্যা i = 0; i < keymap_cache_আকার; ++i) {
        যদি (keymap_cache[i].keyboard_layout == layout) {
            keymap = keymap_cache[i].keymap;

            // Move the map to the front of the list.
            যদি (i) {
                SDL_memmove(keymap_cache + 1, keymap_cache, আকার(কাঠামো WIN_KeymapCache) * i);
                keymap_cache[0].keyboard_layout = layout;
                keymap_cache[0].keymap = keymap;
            }
            বিরতি;
        }
    }
    ফেরত keymap;
}

স্থির শূন্য WIN_CacheKeymap(HKL layout, SDL_Keymap *keymap)
{
    // If the cache is full, evict the last keymap.
    যদি (keymap_cache_আকার == SDL_arraysize(keymap_cache)) {
        SDL_DestroyKeymap(keymap_cache[--keymap_cache_আকার].keymap);
    }

    // Move all elements down by one.
    যদি (keymap_cache_আকার) {
        SDL_memmove(keymap_cache + 1, keymap_cache, আকার(কাঠামো WIN_KeymapCache) * keymap_cache_আকার);
    }

    keymap_cache[0].keyboard_layout = layout;
    keymap_cache[0].keymap = keymap;
    ++keymap_cache_আকার;
}

স্থির SDL_Keymap *WIN_BuildKeymap(শূন্য)
{
    SDL_Scancode scancode;
    BYTE keyboardState[256] = { 0 };
    WCHAR বাফার_2[16];
    ধ্রুবক SDL_Keymod mods[] = {
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
        ফেরত ফাঁকা;
    }

    জন্য (পূর্ণসংখ্যা m = 0; m < SDL_arraysize(mods); ++m) {
        জন্য (পূর্ণসংখ্যা i = 0; i < SDL_arraysize(windows_scancode_table); i++) {
            পূর্ণসংখ্যা vk, sc, ফলাফল;
            Uint32 *ch = 0;

            // Make sure this scancode is a valid character scancode
            scancode = windows_scancode_table[i];
            যদি (scancode == SDL_SCANCODE_UNKNOWN ||
                scancode == SDL_SCANCODE_DELETE ||
                (SDL_GetKeymapKeycode(ফাঁকা, scancode, SDL_KMOD_NONE) & SDLK_SCANCODE_MASK)) {

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
                চালু;
            }

            // Unpack the single byte index to make the scan code.
            sc = MAKEWORD(i & 0x7f, (i & 0x80) ? 0xe0 : 0x00);
            vk = LOBYTE(Map_Virtual_চাবি(sc, MAPVK_VSC_TO_VK));
            যদি (!vk) {
                চালু;
            }

            // Update the keyboard state for the modifiers
            keyboardState[VK_SHIFT] = (mods[m] & SDL_KMOD_SHIFT) ? 0x80 : 0x00;
            keyboardState[VK_CAPITAL] = (mods[m] & SDL_KMOD_CAPS) ? 0x01 : 0x00;
            keyboardState[VK_CONTROL] = (mods[m] & SDL_KMOD_MODE) ? 0x80 : 0x00;
            keyboardState[VK_MENU] = (mods[m] & SDL_KMOD_MODE) ? 0x80 : 0x00;

            ফলাফল = ToUnicode(vk, sc, keyboardState, বাফার_2, 16, 0);
            বাফার_2[SDL_abs(ফলাফল)] = 0;

            // Convert UTF-16 to UTF-32 code points
            ch = (Uint32 *)SDL_iconv_string("UTF-32LE", "UTF-16LE", (ধ্রুবক অক্ষর *)বাফার_2, (SDL_abs(ফলাফল) + 1) * আকার(WCHAR));
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

            যদি (ফলাফল < 0) {
                WIN_Reset_Dead_চাবিগুলি();
            }
        }
    }

    ফেরত keymap;
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
    SDL_Video_তথ্য *তথ্য = _this->internal;

    তথ্য->ime_candlistindexbase = 1;
    তথ্য->ime_composition_দৈর্ঘ্য = 32 * আকার(WCHAR);
    তথ্য->ime_composition = (WCHAR *)SDL_calloc(তথ্য->ime_composition_দৈর্ঘ্য, আকার(WCHAR));
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
    SDL_Video_তথ্য *তথ্য = _this->internal;

    IME_Quit(তথ্য);

    যদি (তথ্য->ime_composition) {
        SDL_free(তথ্য->ime_composition);
        তথ্য->ime_composition = ফাঁকা;
    }
#endif // !SDL_DISABLE_WINDOWS_IME

    জন্য (পূর্ণসংখ্যা i = 0; i < keymap_cache_আকার; ++i) {
        SDL_DestroyKeymap(keymap_cache[i].keymap);
    }
    SDL_zeroa(keymap_cache);
    keymap_cache_আকার = 0;
}

শূন্য WIN_Reset_Dead_চাবিগুলি(শূন্য)
{
    /*
    if a deadkey has been typed, but not the next character (which the deadkey might modify),
    this tries to undo the effect pressing the deadkey.
    see: http://archives.miloush.net/michkap/archive/2006/09/10/748775.html
    */
    BYTE keyboardState[256];
    WCHAR বাফার_2[16];
    পূর্ণসংখ্যা vk, sc, ফলাফল, i;

    যদি (!GetKeyboardState(keyboardState)) {
        ফেরত;
    }

    vk = VK_SPACE;
    sc = Map_Virtual_চাবি(vk, MAPVK_VK_TO_VSC);
    যদি (sc == 0) {
        // the keyboard doesn't have this key
        ফেরত;
    }

    জন্য (i = 0; i < 5; i++) {
        ফলাফল = ToUnicode(vk, sc, keyboardState, বাফার_2, 16, 0);
        যদি (ফলাফল > 0) {
            // success
            ফেরত;
        }
    }
}

bool WIN_Start_Text_প্রবেশ(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    WIN_Reset_Dead_চাবিগুলি();

#ifndef SDL_DISABLE_WINDOWS_IME
    HWND hwnd = window->internal->hwnd;
    SDL_Video_তথ্য *videodata = _this->internal;
    IME_Init(videodata, window);
    IME_Enable(videodata, hwnd);

    WIN_Update_Text_প্রবেশ_Area(_this, window);
#endif // !SDL_DISABLE_WINDOWS_IME

    ফেরত true;
}

bool WIN_Stop_Text_প্রবেশ(SDL_VideoDevice *_this, SDL_Window *window)
{
    WIN_Reset_Dead_চাবিগুলি();

#ifndef SDL_DISABLE_WINDOWS_IME
    HWND hwnd = window->internal->hwnd;
    SDL_Video_তথ্য *videodata = _this->internal;
    IME_Init(videodata, window);
    IME_Disable(videodata, hwnd);
#endif // !SDL_DISABLE_WINDOWS_IME

    ফেরত true;
}

bool WIN_Update_Text_প্রবেশ_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_তথ্য *videodata = _this->internal;
    SDL_Window_তথ্য *তথ্য = window->internal;

    IME_Set_Text_প্রবেশ_Area(videodata, তথ্য->hwnd, &window->text_প্রবেশ_rect, window->text_প্রবেশ_cursor);
    ফেরত true;
}

bool WIN_ClearComposition(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifndef SDL_DISABLE_WINDOWS_IME
    SDL_Video_তথ্য *videodata = _this->internal;

    IME_ClearComposition(videodata);
#endif
    ফেরত true;
}

#ifdef SDL_DISABLE_WINDOWS_IME

bool WIN_HandleIMEMessage(HWND hwnd, UINT বার্তা, WPARAM wParam, LPARAM *lParam, SDL_Video_তথ্য *videodata)
{
    ফেরত false;
}

শূন্য WIN_UpdateIMECandidates(SDL_VideoDevice *_this)
{
    ফেরত;
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

স্থির শূন্য IME_Update_প্রবেশ_Locale(SDL_Video_তথ্য *videodata);
স্থির শূন্য IME_SetWindow(SDL_Video_তথ্য *videodata, SDL_Window *window);
স্থির শূন্য IME_SetupAPI(SDL_Video_তথ্য *videodata);
স্থির DWORD IME_GetId(SDL_Video_তথ্য *videodata, UINT u_সূচক);
স্থির শূন্য IME_SendEditingEvent(SDL_Video_তথ্য *videodata);
স্থির শূন্য IME_SendClearComposition(SDL_Video_তথ্য *videodata);

স্থির bool IME_Init(SDL_Video_তথ্য *videodata, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;

    যদি (videodata->ime_initialized) {
        ফেরত true;
    }

    ধ্রুবক অক্ষর *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);
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
        ফেরত true;
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
        ফেরত true;
    }
    videodata->ime_available = true;
    IME_Update_প্রবেশ_Locale(videodata);
    IME_SetupAPI(videodata);
    IME_Update_প্রবেশ_Locale(videodata);
    IME_Disable(videodata, hwnd);
    ফেরত true;
}

স্থির শূন্য IME_Enable(SDL_Video_তথ্য *videodata, HWND hwnd)
{
    যদি (!videodata->ime_initialized || !videodata->ime_hwnd_current) {
        ফেরত;
    }

    যদি (!videodata->ime_available) {
        IME_Disable(videodata, hwnd);
        ফেরত;
    }
    যদি (videodata->ime_hwnd_current == videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_current, videodata->ime_himc);
    }

    videodata->ime_enabled = true;
    IME_Update_প্রবেশ_Locale(videodata);
}

স্থির শূন্য IME_Disable(SDL_Video_তথ্য *videodata, HWND hwnd)
{
    যদি (!videodata->ime_initialized || !videodata->ime_hwnd_current) {
        ফেরত;
    }

    IME_ClearComposition(videodata);
    যদি (videodata->ime_hwnd_current == videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_current, (HIMC)0);
    }

    videodata->ime_enabled = false;
}

স্থির শূন্য IME_Quit(SDL_Video_তথ্য *videodata)
{
    যদি (!videodata->ime_initialized) {
        ফেরত;
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
    জন্য (পূর্ণসংখ্যা i = 0; i < videodata->ime_candcount; ++i) {
        SDL_free(videodata->ime_candidates[i]);
        videodata->ime_candidates[i] = ফাঁকা;
    }
    videodata->ime_initialized = false;
}

স্থির শূন্য IME_GetReadingString(SDL_Video_তথ্য *videodata, HWND hwnd)
{
    DWORD id = 0;
    HIMC himc = 0;
    WCHAR বাফার_2[16];
    WCHAR *s = বাফার_2;
    DWORD len = 0;
    INT err = 0;
    BOOL vertical = FALSE;
    UINT maxuilen = 0;

    videodata->ime_readingstring[0] = 0;

    id = IME_GetId(videodata, 0);
    যদি (!id) {
        ফেরত;
    }

    himc = ImmGetContext(hwnd);
    যদি (!himc) {
        ফেরত;
    }

    যদি (videodata->GetReadingString) {
        len = videodata->GetReadingString(himc, 0, 0, &err, &vertical, &maxuilen);
        যদি (len) {
            যদি (len > SDL_arraysize(বাফার_2)) {
                len = SDL_arraysize(বাফার_2);
            }

            len = videodata->GetReadingString(himc, len, s, &err, &vertical, &maxuilen);
        }
        SDL_wcslcpy(videodata->ime_readingstring, s, len);
    } অন্যথা {
        LPINPUTCONTEXT2 lpimc = videodata->ImmLockIMC(himc);
        LPBYTE p = 0;
        s = 0;
        নির্বাচন (id) {
        ক্ষেত্র IMEID_CHT_VER42:
        ক্ষেত্র IMEID_CHT_VER43:
        ক্ষেত্র IMEID_CHT_VER44:
            p = *(LPBYTE *)((LPBYTE)videodata->ImmLockIMCC(lpimc->hPrivate) + 24);
            যদি (!p) {
                বিরতি;
            }

            len = *(DWORD *)(p + 7 * 4 + 32 * 4);
            s = (WCHAR *)(p + 56);
            বিরতি;
        ক্ষেত্র IMEID_CHT_VER51:
        ক্ষেত্র IMEID_CHT_VER52:
        ক্ষেত্র IMEID_CHS_VER53:
            p = *(LPBYTE *)((LPBYTE)videodata->ImmLockIMCC(lpimc->hPrivate) + 4);
            যদি (!p) {
                বিরতি;
            }

            p = *(LPBYTE *)(p + 1 * 4 + 5 * 4);
            যদি (!p) {
                বিরতি;
            }

            len = *(DWORD *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4 + 16 * 2);
            s = (WCHAR *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4);
            বিরতি;
        ক্ষেত্র IMEID_CHS_VER41:
        {
            পূর্ণসংখ্যা offset = (IME_GetId(videodata, 1) >= 0x00000002) ? 8 : 7;
            p = *(LPBYTE *)((LPBYTE)videodata->ImmLockIMCC(lpimc->hPrivate) + offset * 4);
            যদি (!p) {
                বিরতি;
            }

            len = *(DWORD *)(p + 7 * 4 + 16 * 2 * 4);
            s = (WCHAR *)(p + 6 * 4 + 16 * 2 * 1);
        } বিরতি;
        ক্ষেত্র IMEID_CHS_VER42:
            p = *(LPBYTE *)((LPBYTE)videodata->ImmLockIMCC(lpimc->hPrivate) + 1 * 4 + 1 * 4 + 6 * 4);
            যদি (!p) {
                বিরতি;
            }

            len = *(DWORD *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4 + 16 * 2);
            s = (WCHAR *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4);
            বিরতি;
        }
        যদি (s) {
            size_t আকার_2 = SDL_min((size_t)(len + 1), SDL_arraysize(videodata->ime_readingstring));
            SDL_wcslcpy(videodata->ime_readingstring, s, আকার_2);
        }

        videodata->ImmUnlockIMCC(lpimc->hPrivate);
        videodata->ImmUnlockIMC(himc);
    }
    ImmReleaseContext(hwnd, himc);
    IME_SendEditingEvent(videodata);
}

স্থির শূন্য IME_প্রবেশ_Lang_Changed(SDL_Video_তথ্য *videodata)
{
    UINT lang = PRIMLANG();
    IME_Update_প্রবেশ_Locale(videodata);

    IME_SetupAPI(videodata);
    যদি (lang != PRIMLANG()) {
        IME_ClearComposition(videodata);
    }
}

স্থির DWORD IME_GetId(SDL_Video_তথ্য *videodata, UINT u_সূচক)
{
    স্থির HKL hklprev = 0;
    স্থির DWORD dwRet[2] = { 0 };
    DWORD dw_Ver_আকার = 0;
    LPVOID lp_Ver_বাফার = 0;
    LPVOID lp_Ver_তথ্য = 0;
    UINT cb_Ver_তথ্য = 0;
    অক্ষর sz_অস্থায়ী[256];
    HKL hkl = 0;
    DWORD dwLang = 0;
    SDL_assert(u_সূচক < SDL_arraysize(dwRet));

    hkl = videodata->ime_hkl;
    যদি (hklprev == hkl) {
        ফেরত dwRet[u_সূচক];
    }
    hklprev = hkl;

    SDL_assert(u_সূচক == 0);
    dwLang = ((DWORD_PTR)hkl & 0xffff);
    // FIXME: What does this do?
    যদি (videodata->ime_internal_candidates && dwLang == LANG_CHT) {
        dwRet[0] = IMEID_CHT_VER_VISTA;
        dwRet[1] = 0;
        ফেরত dwRet[0];
    }
    যদি (hkl != CHT_HKL_NEW_PHONETIC && hkl != CHT_HKL_NEW_CHANG_JIE && hkl != CHT_HKL_NEW_QUICK && hkl != CHT_HKL_HK_CANTONESE && hkl != CHS_HKL) {
        dwRet[0] = dwRet[1] = 0;
        ফেরত dwRet[0];
    }
    যদি (!ImmGetIMEFileNameA(hkl, sz_অস্থায়ী, আকার(sz_অস্থায়ী) - 1)) {
        dwRet[0] = dwRet[1] = 0;
        ফেরত dwRet[0];
    }
    যদি (!videodata->GetReadingString) {
#define LCID_INVARIANT MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT)
        যদি (CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_অস্থায়ী, -1, CHT_IMEFILENAME1, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_অস্থায়ী, -1, CHT_IMEFILENAME2, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_অস্থায়ী, -1, CHT_IMEFILENAME3, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_অস্থায়ী, -1, CHS_IMEFILENAME1, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_অস্থায়ী, -1, CHS_IMEFILENAME2, -1) != 2) {
            dwRet[0] = dwRet[1] = 0;
            ফেরত dwRet[0];
        }
#undef LCID_INVARIANT
        dw_Ver_আকার = Get_File_Version_Info_আকার_A(sz_অস্থায়ী, ফাঁকা);
        যদি (dw_Ver_আকার) {
            lp_Ver_বাফার = SDL_malloc(dw_Ver_আকার);
            যদি (lp_Ver_বাফার) {
                যদি (GetFileVersionInfoA(sz_অস্থায়ী, 0, dw_Ver_আকার, lp_Ver_বাফার)) {
                    যদি (Ver_Query_মান_A(lp_Ver_বাফার, "\\", &lp_Ver_তথ্য, &cb_Ver_তথ্য)) {
#define pVerFixedInfo ((VS_FIXEDFILEINFO FAR *)lp_Ver_তথ্য)
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
                            SDL_free(lp_Ver_বাফার);
                            ফেরত dwRet[0];
                        }
#undef pVerFixedInfo
                    }
                }
            }
            SDL_free(lp_Ver_বাফার);
        }
    }
    dwRet[0] = dwRet[1] = 0;
    ফেরত dwRet[0];
}

স্থির শূন্য IME_SetupAPI(SDL_Video_তথ্য *videodata)
{
    অক্ষর ime_file[MAX_PATH + 1];
    SDL_SharedObject *hime = 0;
    HKL hkl = 0;
    videodata->GetReadingString = ফাঁকা;
    videodata->ShowReadingWindow = ফাঁকা;

    hkl = videodata->ime_hkl;
    যদি (!ImmGetIMEFileNameA(hkl, ime_file, আকার(ime_file) - 1)) {
        ফেরত;
    }

    hime = SDL_LoadObject(ime_file);
    যদি (!hime) {
        ফেরত;
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

স্থির শূন্য IME_SetWindow(SDL_Video_তথ্য *videodata, SDL_Window *window)
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

স্থির শূন্য IME_Set_Text_প্রবেশ_Area(SDL_Video_তথ্য *videodata, HWND hwnd, ধ্রুবক SDL_Rect *rect, পূর্ণসংখ্যা cursor)
{
    HIMC himc;

    himc = ImmGetContext(hwnd);
    যদি (himc) {
        COMPOSITIONFORM cof;
        CANDIDATEFORM caf;
        পূর্ণসংখ্যা font_height = rect->h;

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
        যদি (SDL_memcmp(&cof, &videodata->ime_composition_area, আকার(cof)) != 0) {
            SDL_copyp(&videodata->ime_composition_area, &cof);
            ImmSetCompositionWindow(himc, &cof);
        }

        SDL_zero(caf);
        caf.dw_সূচক = 0;
        caf.dwStyle = CFS_EXCLUDE;
        caf.ptCurrentPos.x = rect->x + cursor;
        caf.ptCurrentPos.y = rect->y;
        caf.rcArea.বাম = rect->x;
        caf.rcArea.ডান = (LONG)rect->x + rect->w;
        caf.rcArea.শীর্ষ = rect->y;
        caf.rcArea.bottom = (LONG)rect->y + rect->h;
        যদি (SDL_memcmp(&caf, &videodata->ime_candidate_area, আকার(caf)) != 0) {
            SDL_copyp(&videodata->ime_candidate_area, &caf);
            ImmSetCandidateWindow(himc, &caf);
        }

        ImmReleaseContext(hwnd, himc);
    }
}

#ifndef SDL_DISABLE_WINDOWS_IME

স্থির শূন্য IME_Update_প্রবেশ_Locale(SDL_Video_তথ্য *videodata)
{
    HKL hklnext = GetKeyboardLayout(0);

    যদি (hklnext == videodata->ime_hkl) {
        ফেরত;
    }

    videodata->ime_hkl = hklnext;
    videodata->ime_horizontal_candidates = (PRIMLANG() == LANG_KOREAN || LANG() == LANG_CHS);
    videodata->ime_candlistindexbase = (videodata->ime_hkl == CHT_HKL_DAYI) ? 0 : 1;
}

স্থির শূন্য IME_ClearComposition(SDL_Video_তথ্য *videodata)
{
    HIMC himc = 0;
    যদি (!videodata->ime_initialized) {
        ফেরত;
    }

    himc = ImmGetContext(videodata->ime_hwnd_current);
    যদি (!himc) {
        ফেরত;
    }

    ImmNotifyIME(himc, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
    ImmSetCompositionString(himc, SCS_SETSTR, TEXT(""), আকার(TCHAR), TEXT(""), আকার(TCHAR));

    ImmNotifyIME(himc, NI_CLOSECANDIDATE, 0, 0);
    ImmReleaseContext(videodata->ime_hwnd_current, himc);
    IME_SendClearComposition(videodata);
}

স্থির শূন্য IME_GetCompositionString(SDL_Video_তথ্য *videodata, HIMC himc, LPARAM *lParam, DWORD string)
{
    LONG দৈর্ঘ্য;
    DWORD dwLang = ((DWORD_PTR)videodata->ime_hkl & 0xffff);

    যদি (*lParam & GCS_CURSORPOS) {
        videodata->ime_cursor = LOWORD(ImmGetCompositionStringW(himc, GCS_CURSORPOS, 0, 0));
    }
    videodata->ime_selected_start = 0;
    videodata->ime_selected_দৈর্ঘ্য = 0;
    SDL_DebugIMELog("Cursor = %d", videodata->ime_cursor);

    দৈর্ঘ্য = ImmGetCompositionStringW(himc, string, ফাঁকা, 0);
    যদি (দৈর্ঘ্য > 0 && videodata->ime_composition_দৈর্ঘ্য < দৈর্ঘ্য) {
        SDL_free(videodata->ime_composition);

        videodata->ime_composition = (WCHAR *)SDL_malloc(দৈর্ঘ্য + আকার(WCHAR));
        videodata->ime_composition_দৈর্ঘ্য = দৈর্ঘ্য;
    }

    দৈর্ঘ্য = ImmGetCompositionStringW(himc, string, videodata->ime_composition, videodata->ime_composition_দৈর্ঘ্য);
    যদি (দৈর্ঘ্য < 0) {
        দৈর্ঘ্য = 0;
    }
    দৈর্ঘ্য /= আকার(WCHAR);

    যদি (!(*lParam & GCS_CURSORPOS)) {
        // If the IME doesn't support GCS_CURSORPOS, default the cursor to the end of the composition.
        videodata->ime_cursor = দৈর্ঘ্য;
    }

    যদি ((dwLang == LANG_CHT || dwLang == LANG_CHS) &&
        videodata->ime_cursor > 0 &&
        videodata->ime_cursor < (পূর্ণসংখ্যা)(videodata->ime_composition_দৈর্ঘ্য / আকার(WCHAR)) &&
        (videodata->ime_composition[0] == 0x3000 || videodata->ime_composition[0] == 0x0020)) {
        // Traditional Chinese IMEs add a placeholder U+3000
        // Simplified Chinese IMEs seem to add a placeholder U+0020 sometimes
        জন্য (পূর্ণসংখ্যা i = videodata->ime_cursor + 1; i < দৈর্ঘ্য; ++i) {
            videodata->ime_composition[i - 1] = videodata->ime_composition[i];
        }
        --দৈর্ঘ্য;
    }

    videodata->ime_composition[দৈর্ঘ্য] = 0;

    দৈর্ঘ্য = ImmGetCompositionStringW(himc, GCS_COMPATTR, ফাঁকা, 0);
    যদি (দৈর্ঘ্য > 0) {
        Uint8 *attributes = (Uint8 *)SDL_malloc(দৈর্ঘ্য);
        যদি (attributes) {
            পূর্ণসংখ্যা start = 0;
            পূর্ণসংখ্যা end = 0;

            দৈর্ঘ্য = ImmGetCompositionString(himc, GCS_COMPATTR, attributes, দৈর্ঘ্য);
            যদি (দৈর্ঘ্য < 0) {
                দৈর্ঘ্য = 0;
            }

            জন্য (LONG i = 0; i < দৈর্ঘ্য; ++i) {
                SDL_DebugIMELog("attrib[%d] = %d", i, attributes[i]);
            }

            জন্য (start = 0; start < দৈর্ঘ্য; ++start) {
                যদি (attributes[start] == ATTR_TARGET_CONVERTED || attributes[start] == ATTR_TARGET_NOTCONVERTED) {
                    বিরতি;
                }
            }

            জন্য (end = start; end < দৈর্ঘ্য; ++end) {
                যদি (attributes[end] != ATTR_TARGET_CONVERTED && attributes[end] != ATTR_TARGET_NOTCONVERTED) {
                    বিরতি;
                }
            }

            যদি (end > start) {
                videodata->ime_selected_start = start;
                videodata->ime_selected_দৈর্ঘ্য = end - start;
            }

            SDL_free(attributes);
        }
    }
}

স্থির শূন্য IME_Send_প্রবেশ_Event(SDL_Video_তথ্য *videodata)
{
    অক্ষর *s = 0;
    s = WIN_StringToUTF8W(videodata->ime_composition);
    SDL_SendKeyboardText(s);
    SDL_free(s);

    videodata->ime_composition[0] = 0;
    videodata->ime_readingstring[0] = 0;
    videodata->ime_cursor = 0;
}

স্থির শূন্য IME_SendEditingEvent(SDL_Video_তথ্য *videodata)
{
    অক্ষর *s = ফাঁকা;
    WCHAR *বাফার_2 = ফাঁকা;
    size_t আকার_2 = videodata->ime_composition_দৈর্ঘ্য;
    যদি (videodata->ime_readingstring[0]) {
        size_t len = SDL_min(SDL_wcslen(videodata->ime_composition), (size_t)videodata->ime_cursor);

        আকার_2 += আকার(videodata->ime_readingstring);
        বাফার_2 = (WCHAR *)SDL_malloc(আকার_2 + আকার(WCHAR));
        যদি (!বাফার_2) {
            ফেরত;
        }
        বাফার_2[0] = 0;

        SDL_wcslcpy(বাফার_2, videodata->ime_composition, len + 1);
        SDL_wcslcat(বাফার_2, videodata->ime_readingstring, আকার_2);
        SDL_wcslcat(বাফার_2, &videodata->ime_composition[len], আকার_2);
    } অন্যথা {
        বাফার_2 = (WCHAR *)SDL_malloc(আকার_2 + আকার(WCHAR));
        যদি (!বাফার_2) {
            ফেরত;
        }
        বাফার_2[0] = 0;
        SDL_wcslcpy(বাফার_2, videodata->ime_composition, আকার_2);
    }

    s = WIN_StringToUTF8W(বাফার_2);
    যদি (s) {
        যদি (videodata->ime_readingstring[0]) {
            SDL_SendEditingText(s, videodata->ime_cursor, (পূর্ণসংখ্যা)SDL_wcslen(videodata->ime_readingstring));
        } অন্যথা যদি (videodata->ime_cursor == videodata->ime_selected_start) {
            SDL_SendEditingText(s, videodata->ime_selected_start, videodata->ime_selected_দৈর্ঘ্য);
        } অন্যথা {
            SDL_SendEditingText(s, videodata->ime_cursor, 0);
        }
        যদি (*s) {
            videodata->ime_needs_clear_composition = true;
        }
        SDL_free(s);
    }
    SDL_free(বাফার_2);
}

স্থির শূন্য IME_SendClearComposition(SDL_Video_তথ্য *videodata)
{
    যদি (videodata->ime_needs_clear_composition) {
        SDL_SendEditingText("", 0, 0);
        videodata->ime_needs_clear_composition = false;
    }
}

স্থির bool IME_OpenCandidateList(SDL_Video_তথ্য *videodata)
{
    videodata->ime_candidates_open = true;
    videodata->ime_candcount = 0;
    ফেরত true;
}

স্থির শূন্য IME_AddCandidate(SDL_Video_তথ্য *videodata, UINT i, LPCWSTR candidate)
{
    যদি (videodata->ime_candidates[i]) {
        SDL_free(videodata->ime_candidates[i]);
        videodata->ime_candidates[i] = ফাঁকা;
    }

    SDL_COMPILE_TIME_ASSERT(IME_CANDIDATE_INDEXING_REQUIRES, MAX_CANDLIST == 10);
    অক্ষর *candidate_utf8 = WIN_StringToUTF8W(candidate);
    SDL_asprintf(&videodata->ime_candidates[i], "%d %s", ((i + videodata->ime_candlistindexbase) % 10), candidate_utf8);
    SDL_free(candidate_utf8);

    videodata->ime_candcount = (i + 1);
}

স্থির শূন্য IME_SendCandidateList(SDL_Video_তথ্য *videodata)
{
    SDL_SendEditingTextCandidates(videodata->ime_candidates, videodata->ime_candcount, videodata->ime_candsel, videodata->ime_horizontal_candidates);
}

স্থির শূন্য IME_CloseCandidateList(SDL_Video_তথ্য *videodata)
{
    videodata->ime_candidates_open = false;

    যদি (videodata->ime_candcount > 0) {
        জন্য (পূর্ণসংখ্যা i = 0; i < videodata->ime_candcount; ++i) {
            SDL_free(videodata->ime_candidates[i]);
            videodata->ime_candidates[i] = ফাঁকা;
        }
        videodata->ime_candcount = 0;

        SDL_SendEditingTextCandidates(ফাঁকা, 0, -1, false);
    }
}

স্থির শূন্য IME_GetCandidateList(SDL_Video_তথ্য *videodata, HWND hwnd)
{
    HIMC himc;
    DWORD আকার_2;
    LPCANDIDATELIST cand_list;
    bool has_candidates = false;

    himc = ImmGetContext(hwnd);
    যদি (himc) {
        আকার_2 = ImmGetCandidateListW(himc, 0, ফাঁকা, 0);
        যদি (আকার_2 != 0) {
            cand_list = (LPCANDIDATELIST)SDL_malloc(আকার_2);
            যদি (cand_list != ফাঁকা) {
                আকার_2 = ImmGetCandidateListW(himc, 0, cand_list, আকার_2);
                যদি (আকার_2 != 0) {
                    যদি (IME_OpenCandidateList(videodata)) {
                        UINT i, j;
                        UINT page_start = 0;
                        UINT page_আকার = 0;

                        videodata->ime_candsel = cand_list->dwSelection;

                        যদি (LANG() == LANG_CHS && IME_GetId(videodata, 0)) {
                            ধ্রুবক UINT maxcandchar = 18;
                            size_t cchars = 0;

                            জন্য (i = 0; i < cand_list->dw_গুনতি; ++i) {
                                size_t len = SDL_wcslen((LPWSTR)((DWORD_PTR)cand_list + cand_list->dwOffset[i])) + 1;
                                যদি (len + cchars > maxcandchar) {
                                    যদি (i > cand_list->dwSelection) {
                                        বিরতি;
                                    }

                                    page_start = i;
                                    cchars = len;
                                } অন্যথা {
                                    cchars += len;
                                }
                            }
                            page_আকার = i - page_start;
                        } অন্যথা {
                            page_আকার = SDL_min(cand_list->dw_Page_আকার == 0 ? MAX_CANDLIST : cand_list->dw_Page_আকার, MAX_CANDLIST);
                            page_start = (cand_list->dwSelection / page_আকার) * page_আকার;
                        }
                        জন্য (i = page_start, j = 0; (DWORD)i < cand_list->dw_গুনতি && j < page_আকার; i++, j++) {
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

bool WIN_HandleIMEMessage(HWND hwnd, UINT বার্তা, WPARAM wParam, LPARAM *lParam, SDL_Video_তথ্য *videodata)
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

        ফেরত false;
    } অন্যথা যদি (বার্তা == WM_IME_STARTCOMPOSITION) {
        SDL_DebugIMELog("WM_IME_STARTCOMPOSITION");
        যদি (videodata->ime_internal_composition) {
            videodata->ime_cursor = 0;
            // Windows may still display a composition dialog even with
            // ISC_SHOWUICOMPOSITIONWINDOW cleared, so trap the message
            // here to prevent that (even when the IME is disabled).
            ফেরত true;
        }
    }

    যদি (!videodata->ime_initialized || !videodata->ime_available || !videodata->ime_enabled) {
        ফেরত false;
    }

    নির্বাচন (বার্তা) {
    ক্ষেত্র WM_KEYDOWN:
        যদি (wParam == VK_PROCESSKEY) {
            SDL_DebugIMELog("WM_KEYDOWN VK_PROCESSKEY");
            trap = true;
        } অন্যথা {
            SDL_DebugIMELog("WM_KEYDOWN normal");
        }
        বিরতি;
    ক্ষেত্র WM_SYSKEYDOWN:
        যদি (wParam == VK_PROCESSKEY) {
            SDL_DebugIMELog("WM_SYSKEYDOWN VK_PROCESSKEY");
            trap = true;
        } অন্যথা {
            SDL_DebugIMELog("WM_SYSKEYDOWN normal");
        }
        বিরতি;
    ক্ষেত্র WM_INPUTLANGCHANGE:
        SDL_DebugIMELog("WM_INPUTLANGCHANGE");
        IME_প্রবেশ_Lang_Changed(videodata);
        বিরতি;
    ক্ষেত্র WM_IME_COMPOSITION:
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
        বিরতি;
    ক্ষেত্র WM_IME_ENDCOMPOSITION:
        SDL_DebugIMELog("WM_IME_ENDCOMPOSITION");
        যদি (videodata->ime_internal_composition) {
            trap = true;
            videodata->ime_composition[0] = 0;
            videodata->ime_readingstring[0] = 0;
            videodata->ime_cursor = 0;
            videodata->ime_selected_start = 0;
            videodata->ime_selected_দৈর্ঘ্য = 0;
            IME_SendClearComposition(videodata);
        }
        বিরতি;
    ক্ষেত্র WM_IME_NOTIFY:
        SDL_DebugIMELog("WM_IME_NOTIFY %x", wParam);
        নির্বাচন (wParam) {
        ক্ষেত্র IMN_SETCOMPOSITIONWINDOW:
            SDL_DebugIMELog("IMN_SETCOMPOSITIONWINDOW");
            বিরতি;
        ক্ষেত্র IMN_SETCOMPOSITIONFONT:
            SDL_DebugIMELog("IMN_SETCOMPOSITIONFONT");
            বিরতি;
        ক্ষেত্র IMN_SETCANDIDATEPOS:
            SDL_DebugIMELog("IMN_SETCANDIDATEPOS");
            বিরতি;
        ক্ষেত্র IMN_SETCONVERSIONMODE:
        ক্ষেত্র IMN_SETOPENSTATUS:
            SDL_DebugIMELog("%s", wParam == IMN_SETCONVERSIONMODE ? "IMN_SETCONVERSIONMODE" : "IMN_SETOPENSTATUS");
            IME_Update_প্রবেশ_Locale(videodata);
            বিরতি;
        ক্ষেত্র IMN_OPENCANDIDATE:
        ক্ষেত্র IMN_CHANGECANDIDATE:
            SDL_DebugIMELog("%s", wParam == IMN_OPENCANDIDATE ? "IMN_OPENCANDIDATE" : "IMN_CHANGECANDIDATE");
            যদি (videodata->ime_internal_candidates) {
                trap = true;
                videodata->ime_update_candidates = true;
            }
            বিরতি;
        ক্ষেত্র IMN_CLOSECANDIDATE:
            SDL_DebugIMELog("IMN_CLOSECANDIDATE");
            যদি (videodata->ime_internal_candidates) {
                trap = true;
                videodata->ime_update_candidates = false;
                IME_CloseCandidateList(videodata);
            }
            বিরতি;
        ক্ষেত্র IMN_PRIVATE:
        {
            DWORD dwId = IME_GetId(videodata, 0);
            SDL_DebugIMELog("IMN_PRIVATE %u", dwId);
            IME_GetReadingString(videodata, hwnd);
            নির্বাচন (dwId) {
            ক্ষেত্র IMEID_CHT_VER42:
            ক্ষেত্র IMEID_CHT_VER43:
            ক্ষেত্র IMEID_CHT_VER44:
            ক্ষেত্র IMEID_CHS_VER41:
            ক্ষেত্র IMEID_CHS_VER42:
                যদি (*lParam == 1 || *lParam == 2) {
                    trap = true;
                }

                বিরতি;
            ক্ষেত্র IMEID_CHT_VER50:
            ক্ষেত্র IMEID_CHT_VER51:
            ক্ষেত্র IMEID_CHT_VER52:
            ক্ষেত্র IMEID_CHT_VER60:
            ক্ষেত্র IMEID_CHS_VER53:
                যদি (*lParam == 16 || *lParam == 17 || *lParam == 26 || *lParam == 27 || *lParam == 28) {
                    trap = true;
                }
                বিরতি;
            }
        } বিরতি;
        পূর্বনির্ধারিত:
            trap = true;
            বিরতি;
        }
        বিরতি;
    }
    ফেরত trap;
}

শূন্য WIN_UpdateIMECandidates(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *videodata = _this->internal;

    যদি (videodata->ime_update_candidates) {
        IME_GetCandidateList(videodata, videodata->ime_hwnd_current);
        videodata->ime_update_candidates = false;
    }
}

#endif // SDL_DISABLE_WINDOWS_IME

#endif // SDL_VIDEO_DRIVER_WINDOWS
