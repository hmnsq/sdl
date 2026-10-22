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
#ضمن "SDL_internal.h"

#إذا defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ضمن "SDL_windowsvideo.h"

#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/scancodes_windows.h"

#ضمن <imm.h>
#ضمن <oleauto.h>

#جے_بنا_تعریف SDL_DISABLE_WINDOWS_IME
#إذا 0
#تعریف_کرو SDL_DebugIMELog SDL_Log
#وإلا
#تعریف_کرو SDL_DebugIMELog(...)
#جے_انت
ساكن bool IME_Init(SDL_Video_انکڑے *videodata, SDL_کھڑکی *کھڑکی);
ساكن فراغ IME_Enable(SDL_Video_انکڑے *videodata, HWND hwnd);
ساكن فراغ IME_Disable(SDL_Video_انکڑے *videodata, HWND hwnd);
ساكن فراغ IME_سیٹ_متن_داخلہ_Area(SDL_Video_انکڑے *videodata, HWND hwnd, ثابت SDL_Rect *rect, صحيح cursor);
ساكن فراغ IME_ClearComposition(SDL_Video_انکڑے *videodata);
ساكن فراغ IME_GetCandidateList(SDL_Video_انکڑے *videodata, HWND hwnd);
ساكن فراغ IME_Quit(SDL_Video_انکڑے *videodata);
#وإلا
ساكن فراغ IME_سیٹ_متن_داخلہ_Area(SDL_Video_انکڑے *videodata, HWND hwnd, ثابت SDL_Rect *rect, صحيح cursor);
#جے_انت // !SDL_DISABLE_WINDOWS_IME

#جے_بنا_تعریف MAPVK_VK_منزل_VSC
#تعریف_کرو MAPVK_VK_منزل_VSC 0
#جے_انت
#جے_بنا_تعریف MAPVK_VSC_منزل_VK
#تعریف_کرو MAPVK_VSC_منزل_VK 1
#جے_انت

/* Building keymaps is expensive, so keep a reasonably-sized LRU cache to
 * enable fast switching between commonly used ones.
 */
ساكن بنية WIN_KeymapCache
{
    HKL keyboard_layout;
    SDL_Keymap *keymap;
} keymap_cache[4];

ساكن صحيح keymap_cache_ناپ;

ساكن SDL_Keymap *WIN_GetCachedKeymap(HKL layout)
{
    SDL_Keymap *keymap = عدم;
    لكل (صحيح i = 0; i < keymap_cache_ناپ; ++i) {
        إذا (keymap_cache[i].keyboard_layout == layout) {
            keymap = keymap_cache[i].keymap;

            // Move the map to the front of the list.
            إذا (i) {
                SDL_memmove(keymap_cache + 1, keymap_cache, حجم(بنية WIN_KeymapCache) * i);
                keymap_cache[0].keyboard_layout = layout;
                keymap_cache[0].keymap = keymap;
            }
            اكسر;
        }
    }
    أرجع keymap;
}

ساكن فراغ WIN_CacheKeymap(HKL layout, SDL_Keymap *keymap)
{
    // If the cache is full, evict the last keymap.
    إذا (keymap_cache_ناپ == SDL_arraysize(keymap_cache)) {
        SDL_DestroyKeymap(keymap_cache[--keymap_cache_ناپ].keymap);
    }

    // Move all elements down by one.
    إذا (keymap_cache_ناپ) {
        SDL_memmove(keymap_cache + 1, keymap_cache, حجم(بنية WIN_KeymapCache) * keymap_cache_ناپ);
    }

    keymap_cache[0].keyboard_layout = layout;
    keymap_cache[0].keymap = keymap;
    ++keymap_cache_ناپ;
}

ساكن SDL_Keymap *WIN_BuildKeymap(فراغ)
{
    SDL_Scancode scancode;
    BYTE keyboardState[256] = { 0 };
    WCHAR بفر_2[16];
    ثابت SDL_Keymod mods[] = {
        SDL_KMOD_NONE,
        SDL_KMOD_کھسکاؤ,
        SDL_KMOD_CAPS,
        (SDL_KMOD_کھسکاؤ | SDL_KMOD_CAPS),
        SDL_KMOD_منوال,
        (SDL_KMOD_منوال | SDL_KMOD_کھسکاؤ),
        (SDL_KMOD_منوال | SDL_KMOD_CAPS),
        (SDL_KMOD_منوال | SDL_KMOD_کھسکاؤ | SDL_KMOD_CAPS)
    };

    WIN_Reset_Dead_کلیدیں();

    SDL_Keymap *keymap = SDL_CreateKeymap(false);
    إذا (!keymap) {
        أرجع عدم;
    }

    لكل (صحيح m = 0; m < SDL_arraysize(mods); ++m) {
        لكل (صحيح i = 0; i < SDL_arraysize(windows_scancode_جدول); i++) {
            صحيح vk, sc, نتیجہ;
            Uint32 *ch = 0;

            // Make sure this scancode is a valid character scancode
            scancode = windows_scancode_جدول[i];
            إذا (scancode == SDL_SCANCODE_UNKNOWN ||
                scancode == SDL_SCANCODE_DELETE ||
                (SDL_GetKeymapKeycode(عدم, scancode, SDL_KMOD_NONE) & SDLK_SCANCODE_نقاب)) {

                // The Colemak mapping swaps Backspace and CapsLock
                إذا (mods[m] == SDL_KMOD_NONE &&
                    (scancode == SDL_SCANCODE_CAPSLOCK ||
                     scancode == SDL_SCANCODE_BACKSPACE)) {
                    vk = LOBYTE(Map_Virtual_کلید(i, MAPVK_VSC_منزل_VK));
                    إذا (vk == VK_CAPITAL) {
                        SDL_سیٹ_Keymap_اندراج(keymap, scancode, mods[m], SDLK_CAPSLOCK);
                    } وإلا إذا (vk == VK_پٹھ) {
                        SDL_سیٹ_Keymap_اندراج(keymap, scancode, mods[m], SDLK_BACKSPACE);
                    }
                }
                استمر;
            }

            // Unpack the single byte index to make the scan code.
            sc = MAKEWORD(i & 0x7f, (i & 0x80) ? 0xe0 : 0x00);
            vk = LOBYTE(Map_Virtual_کلید(sc, MAPVK_VSC_منزل_VK));
            إذا (!vk) {
                استمر;
            }

            // Update the keyboard state for the modifiers
            keyboardState[VK_کھسکاؤ] = (mods[m] & SDL_KMOD_کھسکاؤ) ? 0x80 : 0x00;
            keyboardState[VK_CAPITAL] = (mods[m] & SDL_KMOD_CAPS) ? 0x01 : 0x00;
            keyboardState[VK_CONTROL] = (mods[m] & SDL_KMOD_منوال) ? 0x80 : 0x00;
            keyboardState[VK_MENU] = (mods[m] & SDL_KMOD_منوال) ? 0x80 : 0x00;

            نتیجہ = منزل_Unicode(vk, sc, keyboardState, بفر_2, 16, 0);
            بفر_2[SDL_abs(نتیجہ)] = 0;

            // Convert UTF-16 to UTF-32 code points
            ch = (Uint32 *)SDL_iconv_string("UTF-32LE", "UTF-16LE", (ثابت حرف *)بفر_2, (SDL_abs(نتیجہ) + 1) * حجم(WCHAR));
            إذا (ch) {
                /* Windows keyboard layouts can emit several UTF-32 code points on a single key press.
                 * Use <U+FFFD REPLACEMENT CHARACTER> since we cannot fit into single SDL_Keycode value in SDL keymap.
                 * See https://kbdlayout.info/features/ligatures for a list of such keys. */
                SDL_سیٹ_Keymap_اندراج(keymap, scancode, mods[m], ch[1] == 0 ? ch[0] : 0xfffd);
                SDL_free(ch);
            } وإلا {
                // The default keymap doesn't have any SDL_KMOD_MODE entries, so we don't need to override them
                إذا (!(mods[m] & SDL_KMOD_منوال)) {
                    SDL_سیٹ_Keymap_اندراج(keymap, scancode, mods[m], SDLK_UNKNOWN);
                }
            }

            إذا (نتیجہ < 0) {
                WIN_Reset_Dead_کلیدیں();
            }
        }
    }

    أرجع keymap;
}

فراغ WIN_UpdateKeymap(bool send_event)
{
    HKL layout = GetKeyboardLayout(0);
    SDL_Keymap *keymap = WIN_GetCachedKeymap(layout);
    إذا (!keymap) {
        keymap = WIN_BuildKeymap();
        إذا (keymap) {
            WIN_CacheKeymap(layout, keymap);
        }
    }

    SDL_سیٹ_Keymap(keymap, send_event);
}

// Alphabetic scancodes for PC keyboards
فراغ WIN_InitKeyboard(SDL_VideoDevice *_this)
{
#جے_بنا_تعریف SDL_DISABLE_WINDOWS_IME
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;

    انکڑے->ime_candlistindexbase = 1;
    انکڑے->ime_composition_لمائی = 32 * حجم(WCHAR);
    انکڑے->ime_composition = (WCHAR *)SDL_calloc(انکڑے->ime_composition_لمائی, حجم(WCHAR));
#جے_انت // !SDL_DISABLE_WINDOWS_IME

    // Build and bind the current keymap.
    WIN_UpdateKeymap(false);

    SDL_سیٹ_Scancode_Name(SDL_SCANCODE_APPLICATION, "Menu");
    SDL_سیٹ_Scancode_Name(SDL_SCANCODE_LGUI, "Left Windows");
    SDL_سیٹ_Scancode_Name(SDL_SCANCODE_RGUI, "Right Windows");

    // Are system caps/num/scroll lock active? Set our state to match.
    SDL_ToggleModState(SDL_KMOD_CAPS, (Get_کلید_State(VK_CAPITAL) & 0x0001) ? true : false);
    SDL_ToggleModState(SDL_KMOD_عدد, (Get_کلید_State(VK_NUMLOCK) & 0x0001) ? true : false);
    SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_کلید_State(VK_SCROLL) & 0x0001) ? true : false);
}

فراغ WIN_QuitKeyboard(SDL_VideoDevice *_this)
{
#جے_بنا_تعریف SDL_DISABLE_WINDOWS_IME
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;

    IME_Quit(انکڑے);

    إذا (انکڑے->ime_composition) {
        SDL_free(انکڑے->ime_composition);
        انکڑے->ime_composition = عدم;
    }
#جے_انت // !SDL_DISABLE_WINDOWS_IME

    لكل (صحيح i = 0; i < keymap_cache_ناپ; ++i) {
        SDL_DestroyKeymap(keymap_cache[i].keymap);
    }
    SDL_zeroa(keymap_cache);
    keymap_cache_ناپ = 0;
}

فراغ WIN_Reset_Dead_کلیدیں(فراغ)
{
    /*
    if a deadkey has been typed, but not the next character (which the deadkey might modify),
    this tries to undo the effect pressing the deadkey.
    see: http://archives.miloush.net/michkap/archive/2006/09/10/748775.html
    */
    BYTE keyboardState[256];
    WCHAR بفر_2[16];
    صحيح vk, sc, نتیجہ, i;

    إذا (!GetKeyboardState(keyboardState)) {
        أرجع;
    }

    vk = VK_SPACE;
    sc = Map_Virtual_کلید(vk, MAPVK_VK_منزل_VSC);
    إذا (sc == 0) {
        // the keyboard doesn't have this key
        أرجع;
    }

    لكل (i = 0; i < 5; i++) {
        نتیجہ = منزل_Unicode(vk, sc, keyboardState, بفر_2, 16, 0);
        إذا (نتیجہ > 0) {
            // success
            أرجع;
        }
    }
}

bool WIN_شروع_متن_داخلہ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props)
{
    WIN_Reset_Dead_کلیدیں();

#جے_بنا_تعریف SDL_DISABLE_WINDOWS_IME
    HWND hwnd = کھڑکی->اندرونی->hwnd;
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    IME_Init(videodata, کھڑکی);
    IME_Enable(videodata, hwnd);

    WIN_Update_متن_داخلہ_Area(_this, کھڑکی);
#جے_انت // !SDL_DISABLE_WINDOWS_IME

    أرجع true;
}

bool WIN_Stop_متن_داخلہ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    WIN_Reset_Dead_کلیدیں();

#جے_بنا_تعریف SDL_DISABLE_WINDOWS_IME
    HWND hwnd = کھڑکی->اندرونی->hwnd;
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    IME_Init(videodata, کھڑکی);
    IME_Disable(videodata, hwnd);
#جے_انت // !SDL_DISABLE_WINDOWS_IME

    أرجع true;
}

bool WIN_Update_متن_داخلہ_Area(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;

    IME_سیٹ_متن_داخلہ_Area(videodata, انکڑے->hwnd, &کھڑکی->متن_داخلہ_rect, کھڑکی->متن_داخلہ_cursor);
    أرجع true;
}

bool WIN_ClearComposition(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#جے_بنا_تعریف SDL_DISABLE_WINDOWS_IME
    SDL_Video_انکڑے *videodata = _this->اندرونی;

    IME_ClearComposition(videodata);
#جے_انت
    أرجع true;
}

#جے_تعریف_شدہ SDL_DISABLE_WINDOWS_IME

bool WIN_HandleIMEMessage(HWND hwnd, UINT پیغام, WPARAM wParam, LPARAM *lParam, SDL_Video_انکڑے *videodata)
{
    أرجع false;
}

فراغ WIN_UpdateIMECandidates(SDL_VideoDevice *_this)
{
    أرجع;
}

#وإلا

#تعریف_کرو LANG_CHT MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_TRADITIONAL)
#تعریف_کرو LANG_CHS MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED)

#تعریف_کرو MAKEIMEVERSION(major, minor) ((DWORD)(((BYTE)(major) << 24) | ((BYTE)(minor) << 16)))
#تعریف_کرو IMEID_VER(id)                ((id)&0xffff0000)
#تعریف_کرو IMEID_LANG(id)               ((id)&0x0000ffff)

#تعریف_کرو CHT_HKL_DAYI          ((HKL)(UINT_PTR)0xE0060404)
#تعریف_کرو CHT_HKL_NEW_PHONETIC  ((HKL)(UINT_PTR)0xE0080404)
#تعریف_کرو CHT_HKL_NEW_CHANG_JIE ((HKL)(UINT_PTR)0xE0090404)
#تعریف_کرو CHT_HKL_NEW_تیز     ((HKL)(UINT_PTR)0xE00A0404)
#تعریف_کرو CHT_HKL_HK_CANTONESE  ((HKL)(UINT_PTR)0xE00B0404)
#تعریف_کرو CHT_IMEFILENAME1      "TINTLGNT.IME"
#تعریف_کرو CHT_IMEFILENAME2      "CINTLGNT.IME"
#تعریف_کرو CHT_IMEFILENAME3      "MSTCIPHA.IME"
#تعریف_کرو IMEID_CHT_VER42       (LANG_CHT | MAKEIMEVERSION(4, 2))
#تعریف_کرو IMEID_CHT_VER43       (LANG_CHT | MAKEIMEVERSION(4, 3))
#تعریف_کرو IMEID_CHT_VER44       (LANG_CHT | MAKEIMEVERSION(4, 4))
#تعریف_کرو IMEID_CHT_VER50       (LANG_CHT | MAKEIMEVERSION(5, 0))
#تعریف_کرو IMEID_CHT_VER51       (LANG_CHT | MAKEIMEVERSION(5, 1))
#تعریف_کرو IMEID_CHT_VER52       (LANG_CHT | MAKEIMEVERSION(5, 2))
#تعریف_کرو IMEID_CHT_VER60       (LANG_CHT | MAKEIMEVERSION(6, 0))
#تعریف_کرو IMEID_CHT_VER_VISTA   (LANG_CHT | MAKEIMEVERSION(7, 0))

#تعریف_کرو CHS_HKL          ((HKL)(UINT_PTR)0xE00E0804)
#تعریف_کرو CHS_IMEFILENAME1 "PINTLGNT.IME"
#تعریف_کرو CHS_IMEFILENAME2 "MSSCIPYA.IME"
#تعریف_کرو IMEID_CHS_VER41  (LANG_CHS | MAKEIMEVERSION(4, 1))
#تعریف_کرو IMEID_CHS_VER42  (LANG_CHS | MAKEIMEVERSION(4, 2))
#تعریف_کرو IMEID_CHS_VER53  (LANG_CHS | MAKEIMEVERSION(5, 3))

#تعریف_کرو LANG()         LOWORD((videodata->ime_hkl))
#تعریف_کرو PRIMLANG()     ((لفظ)PRIMARYLANGID(LANG()))
#تعریف_کرو SUBLANG()      SUBLANGID(LANG())

ساكن فراغ IME_Update_داخلہ_Locale(SDL_Video_انکڑے *videodata);
ساكن فراغ IME_سیٹ_کھڑکی(SDL_Video_انکڑے *videodata, SDL_کھڑکی *کھڑکی);
ساكن فراغ IME_تیاری_API(SDL_Video_انکڑے *videodata);
ساكن DWORD IME_GetId(SDL_Video_انکڑے *videodata, UINT u_اشاریہ);
ساكن فراغ IME_SendEditingEvent(SDL_Video_انکڑے *videodata);
ساكن فراغ IME_SendClearComposition(SDL_Video_انکڑے *videodata);

ساكن bool IME_Init(SDL_Video_انکڑے *videodata, SDL_کھڑکی *کھڑکی)
{
    HWND hwnd = کھڑکی->اندرونی->hwnd;

    إذا (videodata->ime_initialized) {
        أرجع true;
    }

    ثابت حرف *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);
    إذا (hint && SDL_strstr(hint, "composition")) {
        videodata->ime_اندرونی_composition = true;
    }
    إذا (hint && SDL_strstr(hint, "candidates")) {
        videodata->ime_اندرونی_candidates = true;
    }

    videodata->ime_hwnd_main = hwnd;
    videodata->ime_initialized = true;
    videodata->ime_himm32 = SDL_لدو_Object("imm32.dll");
    إذا (!videodata->ime_himm32) {
        videodata->ime_دستیاب = false;
        SDL_ClearError();
        أرجع true;
    }
    /* *INDENT-OFF* */ // clang-format off
    videodata->Imm_جندرا_IMC = (LPINPUTCONTEXT2 (WINAPI *)(HIMC))SDL_لدو_Function(videodata->ime_himm32, "ImmLockIMC");
    videodata->ImmUnlockIMC = (BOOL (WINAPI *)(HIMC))SDL_لدو_Function(videodata->ime_himm32, "ImmUnlockIMC");
    videodata->Imm_جندرا_IMCC = (LPVOID (WINAPI *)(HIMCC))SDL_لدو_Function(videodata->ime_himm32, "ImmLockIMCC");
    videodata->ImmUnlockIMCC = (BOOL (WINAPI *)(HIMCC))SDL_لدو_Function(videodata->ime_himm32, "ImmUnlockIMCC");
    /* *INDENT-ON* */ // clang-format on

    IME_سیٹ_کھڑکی(videodata, کھڑکی);
    videodata->ime_himc = ImmGetContext(hwnd);
    ImmReleaseContext(hwnd, videodata->ime_himc);
    إذا (!videodata->ime_himc) {
        videodata->ime_دستیاب = false;
        IME_Disable(videodata, hwnd);
        أرجع true;
    }
    videodata->ime_دستیاب = true;
    IME_Update_داخلہ_Locale(videodata);
    IME_تیاری_API(videodata);
    IME_Update_داخلہ_Locale(videodata);
    IME_Disable(videodata, hwnd);
    أرجع true;
}

ساكن فراغ IME_Enable(SDL_Video_انکڑے *videodata, HWND hwnd)
{
    إذا (!videodata->ime_initialized || !videodata->ime_hwnd_current) {
        أرجع;
    }

    إذا (!videodata->ime_دستیاب) {
        IME_Disable(videodata, hwnd);
        أرجع;
    }
    إذا (videodata->ime_hwnd_current == videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_current, videodata->ime_himc);
    }

    videodata->ime_enabled = true;
    IME_Update_داخلہ_Locale(videodata);
}

ساكن فراغ IME_Disable(SDL_Video_انکڑے *videodata, HWND hwnd)
{
    إذا (!videodata->ime_initialized || !videodata->ime_hwnd_current) {
        أرجع;
    }

    IME_ClearComposition(videodata);
    إذا (videodata->ime_hwnd_current == videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_current, (HIMC)0);
    }

    videodata->ime_enabled = false;
}

ساكن فراغ IME_Quit(SDL_Video_انکڑے *videodata)
{
    إذا (!videodata->ime_initialized) {
        أرجع;
    }

    إذا (videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_main, videodata->ime_himc);
    }

    videodata->ime_hwnd_main = 0;
    videodata->ime_himc = 0;
    إذا (videodata->ime_himm32) {
        SDL_UnloadObject(videodata->ime_himm32);
        videodata->ime_himm32 = 0;
    }
    لكل (صحيح i = 0; i < videodata->ime_candcount; ++i) {
        SDL_free(videodata->ime_candidates[i]);
        videodata->ime_candidates[i] = عدم;
    }
    videodata->ime_initialized = false;
}

ساكن فراغ IME_GetReadingString(SDL_Video_انکڑے *videodata, HWND hwnd)
{
    DWORD id = 0;
    HIMC himc = 0;
    WCHAR بفر_2[16];
    WCHAR *s = بفر_2;
    DWORD len = 0;
    INT err = 0;
    BOOL vertical = FALSE;
    UINT maxuilen = 0;

    videodata->ime_readingstring[0] = 0;

    id = IME_GetId(videodata, 0);
    إذا (!id) {
        أرجع;
    }

    himc = ImmGetContext(hwnd);
    إذا (!himc) {
        أرجع;
    }

    إذا (videodata->GetReadingString) {
        len = videodata->GetReadingString(himc, 0, 0, &err, &vertical, &maxuilen);
        إذا (len) {
            إذا (len > SDL_arraysize(بفر_2)) {
                len = SDL_arraysize(بفر_2);
            }

            len = videodata->GetReadingString(himc, len, s, &err, &vertical, &maxuilen);
        }
        SDL_wcslcpy(videodata->ime_readingstring, s, len);
    } وإلا {
        LPINPUTCONTEXT2 lpimc = videodata->Imm_جندرا_IMC(himc);
        LPBYTE p = 0;
        s = 0;
        بدل (id) {
        حالة IMEID_CHT_VER42:
        حالة IMEID_CHT_VER43:
        حالة IMEID_CHT_VER44:
            p = *(LPBYTE *)((LPBYTE)videodata->Imm_جندرا_IMCC(lpimc->h_نجی) + 24);
            إذا (!p) {
                اكسر;
            }

            len = *(DWORD *)(p + 7 * 4 + 32 * 4);
            s = (WCHAR *)(p + 56);
            اكسر;
        حالة IMEID_CHT_VER51:
        حالة IMEID_CHT_VER52:
        حالة IMEID_CHS_VER53:
            p = *(LPBYTE *)((LPBYTE)videodata->Imm_جندرا_IMCC(lpimc->h_نجی) + 4);
            إذا (!p) {
                اكسر;
            }

            p = *(LPBYTE *)(p + 1 * 4 + 5 * 4);
            إذا (!p) {
                اكسر;
            }

            len = *(DWORD *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4 + 16 * 2);
            s = (WCHAR *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4);
            اكسر;
        حالة IMEID_CHS_VER41:
        {
            صحيح وتھ_2 = (IME_GetId(videodata, 1) >= 0x00000002) ? 8 : 7;
            p = *(LPBYTE *)((LPBYTE)videodata->Imm_جندرا_IMCC(lpimc->h_نجی) + وتھ_2 * 4);
            إذا (!p) {
                اكسر;
            }

            len = *(DWORD *)(p + 7 * 4 + 16 * 2 * 4);
            s = (WCHAR *)(p + 6 * 4 + 16 * 2 * 1);
        } اكسر;
        حالة IMEID_CHS_VER42:
            p = *(LPBYTE *)((LPBYTE)videodata->Imm_جندرا_IMCC(lpimc->h_نجی) + 1 * 4 + 1 * 4 + 6 * 4);
            إذا (!p) {
                اكسر;
            }

            len = *(DWORD *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4 + 16 * 2);
            s = (WCHAR *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4);
            اكسر;
        }
        إذا (s) {
            size_t ناپ = SDL_min((size_t)(len + 1), SDL_arraysize(videodata->ime_readingstring));
            SDL_wcslcpy(videodata->ime_readingstring, s, ناپ);
        }

        videodata->ImmUnlockIMCC(lpimc->h_نجی);
        videodata->ImmUnlockIMC(himc);
    }
    ImmReleaseContext(hwnd, himc);
    IME_SendEditingEvent(videodata);
}

ساكن فراغ IME_داخلہ_Lang_بدلیا(SDL_Video_انکڑے *videodata)
{
    UINT lang = PRIMLANG();
    IME_Update_داخلہ_Locale(videodata);

    IME_تیاری_API(videodata);
    إذا (lang != PRIMLANG()) {
        IME_ClearComposition(videodata);
    }
}

ساكن DWORD IME_GetId(SDL_Video_انکڑے *videodata, UINT u_اشاریہ)
{
    ساكن HKL hklprev = 0;
    ساكن DWORD dwRet[2] = { 0 };
    DWORD dw_Ver_ناپ = 0;
    LPVOID lp_Ver_بفر = 0;
    LPVOID lp_Ver_انکڑے = 0;
    UINT cb_Ver_انکڑے = 0;
    حرف sz_عارضی[256];
    HKL hkl = 0;
    DWORD dwLang = 0;
    SDL_assert(u_اشاریہ < SDL_arraysize(dwRet));

    hkl = videodata->ime_hkl;
    إذا (hklprev == hkl) {
        أرجع dwRet[u_اشاریہ];
    }
    hklprev = hkl;

    SDL_assert(u_اشاریہ == 0);
    dwLang = ((DWORD_PTR)hkl & 0xffff);
    // FIXME: What does this do?
    إذا (videodata->ime_اندرونی_candidates && dwLang == LANG_CHT) {
        dwRet[0] = IMEID_CHT_VER_VISTA;
        dwRet[1] = 0;
        أرجع dwRet[0];
    }
    إذا (hkl != CHT_HKL_NEW_PHONETIC && hkl != CHT_HKL_NEW_CHANG_JIE && hkl != CHT_HKL_NEW_تیز && hkl != CHT_HKL_HK_CANTONESE && hkl != CHS_HKL) {
        dwRet[0] = dwRet[1] = 0;
        أرجع dwRet[0];
    }
    إذا (!ImmGetIMEFileNameA(hkl, sz_عارضی, حجم(sz_عارضی) - 1)) {
        dwRet[0] = dwRet[1] = 0;
        أرجع dwRet[0];
    }
    إذا (!videodata->GetReadingString) {
#تعریف_کرو LCID_INVARIANT MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), ترتیب_دیو_DEFAULT)
        إذا (CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_عارضی, -1, CHT_IMEFILENAME1, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_عارضی, -1, CHT_IMEFILENAME2, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_عارضی, -1, CHT_IMEFILENAME3, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_عارضی, -1, CHS_IMEFILENAME1, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_عارضی, -1, CHS_IMEFILENAME2, -1) != 2) {
            dwRet[0] = dwRet[1] = 0;
            أرجع dwRet[0];
        }
#تعریف_رد LCID_INVARIANT
        dw_Ver_ناپ = Get_File_نسخہ_Info_ناپ_A(sz_عارضی, عدم);
        إذا (dw_Ver_ناپ) {
            lp_Ver_بفر = SDL_malloc(dw_Ver_ناپ);
            إذا (lp_Ver_بفر) {
                إذا (Get_File_نسخہ_Info_A(sz_عارضی, 0, dw_Ver_ناپ, lp_Ver_بفر)) {
                    إذا (Ver_Query_قدر_A(lp_Ver_بفر, "\\", &lp_Ver_انکڑے, &cb_Ver_انکڑے)) {
#تعریف_کرو pVerFixedInfo ((VS_FIXEDFILEINFO FAR *)lp_Ver_انکڑے)
                        DWORD dwVer = pVerFixedInfo->dw_File_نسخہ_MS;
                        dwVer = (dwVer & 0x00ff0000) << 8 | (dwVer & 0x000000ff) << 16;
                        إذا ((videodata->GetReadingString) ||
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
                            dwRet[1] = pVerFixedInfo->dw_File_نسخہ_LS;
                            SDL_free(lp_Ver_بفر);
                            أرجع dwRet[0];
                        }
#تعریف_رد pVerFixedInfo
                    }
                }
            }
            SDL_free(lp_Ver_بفر);
        }
    }
    dwRet[0] = dwRet[1] = 0;
    أرجع dwRet[0];
}

ساكن فراغ IME_تیاری_API(SDL_Video_انکڑے *videodata)
{
    حرف ime_file[MAX_رستہ + 1];
    SDL_SharedObject *hime = 0;
    HKL hkl = 0;
    videodata->GetReadingString = عدم;
    videodata->Show_Reading_کھڑکی = عدم;

    hkl = videodata->ime_hkl;
    إذا (!ImmGetIMEFileNameA(hkl, ime_file, حجم(ime_file) - 1)) {
        أرجع;
    }

    hime = SDL_لدو_Object(ime_file);
    إذا (!hime) {
        أرجع;
    }

    /* *INDENT-OFF* */ // clang-format off
    videodata->GetReadingString = (UINT (WINAPI *)(HIMC, UINT, LPWSTR, PINT, BOOL*, PUINT))
        SDL_لدو_Function(hime, "GetReadingString");
    videodata->Show_Reading_کھڑکی = (BOOL (WINAPI *)(HIMC, BOOL))
        SDL_لدو_Function(hime, "ShowReadingWindow");
    /* *INDENT-ON* */ // clang-format on

    إذا (videodata->Show_Reading_کھڑکی) {
        HIMC himc = ImmGetContext(videodata->ime_hwnd_current);
        إذا (himc) {
            videodata->Show_Reading_کھڑکی(himc, FALSE);
            ImmReleaseContext(videodata->ime_hwnd_current, himc);
        }
    }
}

ساكن فراغ IME_سیٹ_کھڑکی(SDL_Video_انکڑے *videodata, SDL_کھڑکی *کھڑکی)
{
    HWND hwnd = کھڑکی->اندرونی->hwnd;

    إذا (hwnd != videodata->ime_hwnd_current) {
        videodata->ime_hwnd_current = hwnd;
        SDL_zero(videodata->ime_composition_area);
        SDL_zero(videodata->ime_candidate_area);
    }

    IME_سیٹ_متن_داخلہ_Area(videodata, hwnd, &کھڑکی->متن_داخلہ_rect, کھڑکی->متن_داخلہ_cursor);
}

#جے_انت

ساكن فراغ IME_سیٹ_متن_داخلہ_Area(SDL_Video_انکڑے *videodata, HWND hwnd, ثابت SDL_Rect *rect, صحيح cursor)
{
    HIMC himc;

    himc = ImmGetContext(hwnd);
    إذا (himc) {
        COMPOSITIONFORM cof;
        CANDIDATEFORM caf;
        صحيح font_اچائی = rect->h;

        LOGFONTW font;
        إذا (ImmGetCompositionFontW(himc, &font)) {
            font_اچائی = font.lf_اچائی;
        }

        SDL_zero(cof);
        cof.dwStyle = CFS_RECT;
        cof.ptCurrentPos.x = rect->x + cursor;
        cof.ptCurrentPos.y = rect->y + (rect->h - font_اچائی) / 2;
        cof.rcArea.بایاں = rect->x;
        cof.rcArea.دایاں = (LONG)rect->x + rect->w;
        cof.rcArea.چوٹی = rect->y;
        cof.rcArea.bottom = (LONG)rect->y + rect->h;
        إذا (SDL_memcmp(&cof, &videodata->ime_composition_area, حجم(cof)) != 0) {
            SDL_copyp(&videodata->ime_composition_area, &cof);
            Imm_سیٹ_Composition_کھڑکی(himc, &cof);
        }

        SDL_zero(caf);
        caf.dw_اشاریہ = 0;
        caf.dwStyle = CFS_EXCLUDE;
        caf.ptCurrentPos.x = rect->x + cursor;
        caf.ptCurrentPos.y = rect->y;
        caf.rcArea.بایاں = rect->x;
        caf.rcArea.دایاں = (LONG)rect->x + rect->w;
        caf.rcArea.چوٹی = rect->y;
        caf.rcArea.bottom = (LONG)rect->y + rect->h;
        إذا (SDL_memcmp(&caf, &videodata->ime_candidate_area, حجم(caf)) != 0) {
            SDL_copyp(&videodata->ime_candidate_area, &caf);
            Imm_سیٹ_Candidate_کھڑکی(himc, &caf);
        }

        ImmReleaseContext(hwnd, himc);
    }
}

#جے_بنا_تعریف SDL_DISABLE_WINDOWS_IME

ساكن فراغ IME_Update_داخلہ_Locale(SDL_Video_انکڑے *videodata)
{
    HKL hklnext = GetKeyboardLayout(0);

    إذا (hklnext == videodata->ime_hkl) {
        أرجع;
    }

    videodata->ime_hkl = hklnext;
    videodata->ime_horizontal_candidates = (PRIMLANG() == LANG_KOREAN || LANG() == LANG_CHS);
    videodata->ime_candlistindexbase = (videodata->ime_hkl == CHT_HKL_DAYI) ? 0 : 1;
}

ساكن فراغ IME_ClearComposition(SDL_Video_انکڑے *videodata)
{
    HIMC himc = 0;
    إذا (!videodata->ime_initialized) {
        أرجع;
    }

    himc = ImmGetContext(videodata->ime_hwnd_current);
    إذا (!himc) {
        أرجع;
    }

    ImmNotifyIME(himc, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
    Imm_سیٹ_Composition_String(himc, SCS_SETSTR, متن_2(""), حجم(TCHAR), متن_2(""), حجم(TCHAR));

    ImmNotifyIME(himc, NI_CLOSECANDIDATE, 0, 0);
    ImmReleaseContext(videodata->ime_hwnd_current, himc);
    IME_SendClearComposition(videodata);
}

ساكن فراغ IME_GetCompositionString(SDL_Video_انکڑے *videodata, HIMC himc, LPARAM *lParam, DWORD string)
{
    LONG لمائی;
    DWORD dwLang = ((DWORD_PTR)videodata->ime_hkl & 0xffff);

    إذا (*lParam & GCS_CURSORPOS) {
        videodata->ime_cursor = LOWORD(ImmGetCompositionStringW(himc, GCS_CURSORPOS, 0, 0));
    }
    videodata->ime_selected_شروع = 0;
    videodata->ime_selected_لمائی = 0;
    SDL_DebugIMELog("Cursor = %d", videodata->ime_cursor);

    لمائی = ImmGetCompositionStringW(himc, string, عدم, 0);
    إذا (لمائی > 0 && videodata->ime_composition_لمائی < لمائی) {
        SDL_free(videodata->ime_composition);

        videodata->ime_composition = (WCHAR *)SDL_malloc(لمائی + حجم(WCHAR));
        videodata->ime_composition_لمائی = لمائی;
    }

    لمائی = ImmGetCompositionStringW(himc, string, videodata->ime_composition, videodata->ime_composition_لمائی);
    إذا (لمائی < 0) {
        لمائی = 0;
    }
    لمائی /= حجم(WCHAR);

    إذا (!(*lParam & GCS_CURSORPOS)) {
        // If the IME doesn't support GCS_CURSORPOS, default the cursor to the end of the composition.
        videodata->ime_cursor = لمائی;
    }

    إذا ((dwLang == LANG_CHT || dwLang == LANG_CHS) &&
        videodata->ime_cursor > 0 &&
        videodata->ime_cursor < (صحيح)(videodata->ime_composition_لمائی / حجم(WCHAR)) &&
        (videodata->ime_composition[0] == 0x3000 || videodata->ime_composition[0] == 0x0020)) {
        // Traditional Chinese IMEs add a placeholder U+3000
        // Simplified Chinese IMEs seem to add a placeholder U+0020 sometimes
        لكل (صحيح i = videodata->ime_cursor + 1; i < لمائی; ++i) {
            videodata->ime_composition[i - 1] = videodata->ime_composition[i];
        }
        --لمائی;
    }

    videodata->ime_composition[لمائی] = 0;

    لمائی = ImmGetCompositionStringW(himc, GCS_COMPATTR, عدم, 0);
    إذا (لمائی > 0) {
        Uint8 *گن = (Uint8 *)SDL_malloc(لمائی);
        إذا (گن) {
            صحيح شروع = 0;
            صحيح سرا = 0;

            لمائی = ImmGetCompositionString(himc, GCS_COMPATTR, گن, لمائی);
            إذا (لمائی < 0) {
                لمائی = 0;
            }

            لكل (LONG i = 0; i < لمائی; ++i) {
                SDL_DebugIMELog("attrib[%d] = %d", i, گن[i]);
            }

            لكل (شروع = 0; شروع < لمائی; ++شروع) {
                إذا (گن[شروع] == ATTR_نشانہ_CONVERTED || گن[شروع] == ATTR_نشانہ_NOTCONVERTED) {
                    اكسر;
                }
            }

            لكل (سرا = شروع; سرا < لمائی; ++سرا) {
                إذا (گن[سرا] != ATTR_نشانہ_CONVERTED && گن[سرا] != ATTR_نشانہ_NOTCONVERTED) {
                    اكسر;
                }
            }

            إذا (سرا > شروع) {
                videodata->ime_selected_شروع = شروع;
                videodata->ime_selected_لمائی = سرا - شروع;
            }

            SDL_free(گن);
        }
    }
}

ساكن فراغ IME_Send_داخلہ_Event(SDL_Video_انکڑے *videodata)
{
    حرف *s = 0;
    s = WIN_String_منزل_UTF8_W(videodata->ime_composition);
    SDL_Send_Keyboard_متن(s);
    SDL_free(s);

    videodata->ime_composition[0] = 0;
    videodata->ime_readingstring[0] = 0;
    videodata->ime_cursor = 0;
}

ساكن فراغ IME_SendEditingEvent(SDL_Video_انکڑے *videodata)
{
    حرف *s = عدم;
    WCHAR *بفر_2 = عدم;
    size_t ناپ = videodata->ime_composition_لمائی;
    إذا (videodata->ime_readingstring[0]) {
        size_t len = SDL_min(SDL_wcslen(videodata->ime_composition), (size_t)videodata->ime_cursor);

        ناپ += حجم(videodata->ime_readingstring);
        بفر_2 = (WCHAR *)SDL_malloc(ناپ + حجم(WCHAR));
        إذا (!بفر_2) {
            أرجع;
        }
        بفر_2[0] = 0;

        SDL_wcslcpy(بفر_2, videodata->ime_composition, len + 1);
        SDL_wcslcat(بفر_2, videodata->ime_readingstring, ناپ);
        SDL_wcslcat(بفر_2, &videodata->ime_composition[len], ناپ);
    } وإلا {
        بفر_2 = (WCHAR *)SDL_malloc(ناپ + حجم(WCHAR));
        إذا (!بفر_2) {
            أرجع;
        }
        بفر_2[0] = 0;
        SDL_wcslcpy(بفر_2, videodata->ime_composition, ناپ);
    }

    s = WIN_String_منزل_UTF8_W(بفر_2);
    إذا (s) {
        إذا (videodata->ime_readingstring[0]) {
            SDL_Send_Editing_متن(s, videodata->ime_cursor, (صحيح)SDL_wcslen(videodata->ime_readingstring));
        } وإلا إذا (videodata->ime_cursor == videodata->ime_selected_شروع) {
            SDL_Send_Editing_متن(s, videodata->ime_selected_شروع, videodata->ime_selected_لمائی);
        } وإلا {
            SDL_Send_Editing_متن(s, videodata->ime_cursor, 0);
        }
        إذا (*s) {
            videodata->ime_needs_clear_composition = true;
        }
        SDL_free(s);
    }
    SDL_free(بفر_2);
}

ساكن فراغ IME_SendClearComposition(SDL_Video_انکڑے *videodata)
{
    إذا (videodata->ime_needs_clear_composition) {
        SDL_Send_Editing_متن("", 0, 0);
        videodata->ime_needs_clear_composition = false;
    }
}

ساكن bool IME_OpenCandidateList(SDL_Video_انکڑے *videodata)
{
    videodata->ime_candidates_open = true;
    videodata->ime_candcount = 0;
    أرجع true;
}

ساكن فراغ IME_جوڑو_Candidate(SDL_Video_انکڑے *videodata, UINT i, LPCWSTR candidate)
{
    إذا (videodata->ime_candidates[i]) {
        SDL_free(videodata->ime_candidates[i]);
        videodata->ime_candidates[i] = عدم;
    }

    SDL_COMPILE_ویلا_ASSERT(IME_CANDIDATE_INDEXING_REQUIRES, MAX_CANDLIST == 10);
    حرف *candidate_utf8 = WIN_String_منزل_UTF8_W(candidate);
    SDL_asprintf(&videodata->ime_candidates[i], "%d %s", ((i + videodata->ime_candlistindexbase) % 10), candidate_utf8);
    SDL_free(candidate_utf8);

    videodata->ime_candcount = (i + 1);
}

ساكن فراغ IME_SendCandidateList(SDL_Video_انکڑے *videodata)
{
    SDL_Send_Editing_متن_Candidates(videodata->ime_candidates, videodata->ime_candcount, videodata->ime_candsel, videodata->ime_horizontal_candidates);
}

ساكن فراغ IME_CloseCandidateList(SDL_Video_انکڑے *videodata)
{
    videodata->ime_candidates_open = false;

    إذا (videodata->ime_candcount > 0) {
        لكل (صحيح i = 0; i < videodata->ime_candcount; ++i) {
            SDL_free(videodata->ime_candidates[i]);
            videodata->ime_candidates[i] = عدم;
        }
        videodata->ime_candcount = 0;

        SDL_Send_Editing_متن_Candidates(عدم, 0, -1, false);
    }
}

ساكن فراغ IME_GetCandidateList(SDL_Video_انکڑے *videodata, HWND hwnd)
{
    HIMC himc;
    DWORD ناپ;
    LPCANDIDATELIST cand_list;
    bool has_candidates = false;

    himc = ImmGetContext(hwnd);
    إذا (himc) {
        ناپ = ImmGetCandidateListW(himc, 0, عدم, 0);
        إذا (ناپ != 0) {
            cand_list = (LPCANDIDATELIST)SDL_malloc(ناپ);
            إذا (cand_list != عدم) {
                ناپ = ImmGetCandidateListW(himc, 0, cand_list, ناپ);
                إذا (ناپ != 0) {
                    إذا (IME_OpenCandidateList(videodata)) {
                        UINT i, j;
                        UINT ورقہ_شروع = 0;
                        UINT ورقہ_ناپ = 0;

                        videodata->ime_candsel = cand_list->dwSelection;

                        إذا (LANG() == LANG_CHS && IME_GetId(videodata, 0)) {
                            ثابت UINT maxcandchar = 18;
                            size_t cchars = 0;

                            لكل (i = 0; i < cand_list->dw_گنتی; ++i) {
                                size_t len = SDL_wcslen((LPWSTR)((DWORD_PTR)cand_list + cand_list->dw_وتھ[i])) + 1;
                                إذا (len + cchars > maxcandchar) {
                                    إذا (i > cand_list->dwSelection) {
                                        اكسر;
                                    }

                                    ورقہ_شروع = i;
                                    cchars = len;
                                } وإلا {
                                    cchars += len;
                                }
                            }
                            ورقہ_ناپ = i - ورقہ_شروع;
                        } وإلا {
                            ورقہ_ناپ = SDL_min(cand_list->dw_ورقہ_ناپ == 0 ? MAX_CANDLIST : cand_list->dw_ورقہ_ناپ, MAX_CANDLIST);
                            ورقہ_شروع = (cand_list->dwSelection / ورقہ_ناپ) * ورقہ_ناپ;
                        }
                        لكل (i = ورقہ_شروع, j = 0; (DWORD)i < cand_list->dw_گنتی && j < ورقہ_ناپ; i++, j++) {
                            LPCWSTR candidate = (LPCWSTR)((DWORD_PTR)cand_list + cand_list->dw_وتھ[i]);
                            IME_جوڑو_Candidate(videodata, j, candidate);
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

    إذا (!has_candidates) {
        IME_CloseCandidateList(videodata);
    }
}

bool WIN_HandleIMEMessage(HWND hwnd, UINT پیغام, WPARAM wParam, LPARAM *lParam, SDL_Video_انکڑے *videodata)
{
    bool trap = false;
    HIMC himc = 0;

    إذا (پیغام == WM_IME_SETCONTEXT) {
        SDL_DebugIMELog("WM_IME_SETCONTEXT");

        LPARAM element_نقاب;
        element_نقاب = ISC_SHOWUIALL;
        إذا (videodata->ime_اندرونی_composition) {
            element_نقاب &= ~ISC_SHOWUICOMPOSITIONWINDOW;
        }
        إذا (videodata->ime_اندرونی_candidates) {
            element_نقاب &= ~ISC_SHOWUIALLCANDIDATEWINDOW;
        }
        *lParam &= element_نقاب;

        أرجع false;
    } وإلا إذا (پیغام == WM_IME_STARTCOMPOSITION) {
        SDL_DebugIMELog("WM_IME_STARTCOMPOSITION");
        إذا (videodata->ime_اندرونی_composition) {
            videodata->ime_cursor = 0;
            // Windows may still display a composition dialog even with
            // ISC_SHOWUICOMPOSITIONWINDOW cleared, so trap the message
            // here to prevent that (even when the IME is disabled).
            أرجع true;
        }
    }

    إذا (!videodata->ime_initialized || !videodata->ime_دستیاب || !videodata->ime_enabled) {
        أرجع false;
    }

    بدل (پیغام) {
    حالة WM_KEYDOWN:
        إذا (wParam == VK_PROCESSKEY) {
            SDL_DebugIMELog("WM_KEYDOWN VK_PROCESSKEY");
            trap = true;
        } وإلا {
            SDL_DebugIMELog("WM_KEYDOWN normal");
        }
        اكسر;
    حالة WM_SYSKEYDOWN:
        إذا (wParam == VK_PROCESSKEY) {
            SDL_DebugIMELog("WM_SYSKEYDOWN VK_PROCESSKEY");
            trap = true;
        } وإلا {
            SDL_DebugIMELog("WM_SYSKEYDOWN normal");
        }
        اكسر;
    حالة WM_INPUTLANGCHANGE:
        SDL_DebugIMELog("WM_INPUTLANGCHANGE");
        IME_داخلہ_Lang_بدلیا(videodata);
        اكسر;
    حالة WM_IME_COMPOSITION:
        SDL_DebugIMELog("WM_IME_COMPOSITION %x", lParam);
        إذا (videodata->ime_اندرونی_composition) {
            trap = true;
            himc = ImmGetContext(hwnd);
            إذا (*lParam & GCS_RESULTSTR) {
                SDL_DebugIMELog("GCS_RESULTSTR");
                IME_GetCompositionString(videodata, himc, lParam, GCS_RESULTSTR);
                IME_SendClearComposition(videodata);
                IME_Send_داخلہ_Event(videodata);
            }
            إذا (*lParam & GCS_COMPSTR) {
                SDL_DebugIMELog("GCS_COMPSTR");
                videodata->ime_readingstring[0] = 0;
                IME_GetCompositionString(videodata, himc, lParam, GCS_COMPSTR);
                IME_SendEditingEvent(videodata);
            }
            ImmReleaseContext(hwnd, himc);
        }
        اكسر;
    حالة WM_IME_ENDCOMPOSITION:
        SDL_DebugIMELog("WM_IME_ENDCOMPOSITION");
        إذا (videodata->ime_اندرونی_composition) {
            trap = true;
            videodata->ime_composition[0] = 0;
            videodata->ime_readingstring[0] = 0;
            videodata->ime_cursor = 0;
            videodata->ime_selected_شروع = 0;
            videodata->ime_selected_لمائی = 0;
            IME_SendClearComposition(videodata);
        }
        اكسر;
    حالة WM_IME_NOTIFY:
        SDL_DebugIMELog("WM_IME_NOTIFY %x", wParam);
        بدل (wParam) {
        حالة IMN_SETCOMPOSITIONWINDOW:
            SDL_DebugIMELog("IMN_SETCOMPOSITIONWINDOW");
            اكسر;
        حالة IMN_SETCOMPOSITIONFONT:
            SDL_DebugIMELog("IMN_SETCOMPOSITIONFONT");
            اكسر;
        حالة IMN_SETCANDIDATEPOS:
            SDL_DebugIMELog("IMN_SETCANDIDATEPOS");
            اكسر;
        حالة IMN_SETCONVERSIONMODE:
        حالة IMN_SETOPENSTATUS:
            SDL_DebugIMELog("%s", wParam == IMN_SETCONVERSIONMODE ? "IMN_SETCONVERSIONMODE" : "IMN_SETOPENSTATUS");
            IME_Update_داخلہ_Locale(videodata);
            اكسر;
        حالة IMN_OPENCANDIDATE:
        حالة IMN_CHANGECANDIDATE:
            SDL_DebugIMELog("%s", wParam == IMN_OPENCANDIDATE ? "IMN_OPENCANDIDATE" : "IMN_CHANGECANDIDATE");
            إذا (videodata->ime_اندرونی_candidates) {
                trap = true;
                videodata->ime_update_candidates = true;
            }
            اكسر;
        حالة IMN_CLOSECANDIDATE:
            SDL_DebugIMELog("IMN_CLOSECANDIDATE");
            إذا (videodata->ime_اندرونی_candidates) {
                trap = true;
                videodata->ime_update_candidates = false;
                IME_CloseCandidateList(videodata);
            }
            اكسر;
        حالة IMN_نجی:
        {
            DWORD dwId = IME_GetId(videodata, 0);
            SDL_DebugIMELog("IMN_PRIVATE %u", dwId);
            IME_GetReadingString(videodata, hwnd);
            بدل (dwId) {
            حالة IMEID_CHT_VER42:
            حالة IMEID_CHT_VER43:
            حالة IMEID_CHT_VER44:
            حالة IMEID_CHS_VER41:
            حالة IMEID_CHS_VER42:
                إذا (*lParam == 1 || *lParam == 2) {
                    trap = true;
                }

                اكسر;
            حالة IMEID_CHT_VER50:
            حالة IMEID_CHT_VER51:
            حالة IMEID_CHT_VER52:
            حالة IMEID_CHT_VER60:
            حالة IMEID_CHS_VER53:
                إذا (*lParam == 16 || *lParam == 17 || *lParam == 26 || *lParam == 27 || *lParam == 28) {
                    trap = true;
                }
                اكسر;
            }
        } اكسر;
        افتراضي:
            trap = true;
            اكسر;
        }
        اكسر;
    }
    أرجع trap;
}

فراغ WIN_UpdateIMECandidates(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;

    إذا (videodata->ime_update_candidates) {
        IME_GetCandidateList(videodata, videodata->ime_hwnd_current);
        videodata->ime_update_candidates = false;
    }
}

#جے_انت // SDL_DISABLE_WINDOWS_IME

#جے_انت // SDL_VIDEO_DRIVER_WINDOWS
