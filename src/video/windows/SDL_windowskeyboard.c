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
#شامل "SDL_internal.h"

#اگر defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#شامل "SDL_windowsvideo.h"

#شامل "../../events/SDL_keyboard_c.h"
#شامل "../../events/scancodes_windows.h"

#شامل <imm.h>
#شامل <oleauto.h>

#اگر_غیر_تعریف_شدہ SDL_DISABLE_WINDOWS_IME
#اگر 0
#تعریف_کرو SDL_DebugIMELog SDL_Log
#ورنہ
#تعریف_کرو SDL_DebugIMELog(...)
#اگر_ختم
ساکن bool IME_Init(SDL_Video_ڈیٹا *videodata, SDL_کھڑکی *کھڑکی);
ساکن خالی IME_Enable(SDL_Video_ڈیٹا *videodata, HWND hwnd);
ساکن خالی IME_Disable(SDL_Video_ڈیٹا *videodata, HWND hwnd);
ساکن خالی IME_سیٹ_متن_داخلہ_Area(SDL_Video_ڈیٹا *videodata, HWND hwnd, ثابت SDL_Rect *rect, صحیح cursor);
ساکن خالی IME_ClearComposition(SDL_Video_ڈیٹا *videodata);
ساکن خالی IME_GetCandidateList(SDL_Video_ڈیٹا *videodata, HWND hwnd);
ساکن خالی IME_Quit(SDL_Video_ڈیٹا *videodata);
#ورنہ
ساکن خالی IME_سیٹ_متن_داخلہ_Area(SDL_Video_ڈیٹا *videodata, HWND hwnd, ثابت SDL_Rect *rect, صحیح cursor);
#اگر_ختم // !SDL_DISABLE_WINDOWS_IME

#اگر_غیر_تعریف_شدہ MAPVK_VK_مقصد_VSC
#تعریف_کرو MAPVK_VK_مقصد_VSC 0
#اگر_ختم
#اگر_غیر_تعریف_شدہ MAPVK_VSC_مقصد_VK
#تعریف_کرو MAPVK_VSC_مقصد_VK 1
#اگر_ختم

/* Building keymaps is expensive, so keep a reasonably-sized LRU cache to
 * enable fast switching between commonly used ones.
 */
ساکن ساخت WIN_KeymapCache
{
    HKL keyboard_layout;
    SDL_Keymap *keymap;
} keymap_cache[4];

ساکن صحیح keymap_cache_سائز;

ساکن SDL_Keymap *WIN_GetCachedKeymap(HKL layout)
{
    SDL_Keymap *keymap = تہی;
    برائے (صحیح i = 0; i < keymap_cache_سائز; ++i) {
        اگر (keymap_cache[i].keyboard_layout == layout) {
            keymap = keymap_cache[i].keymap;

            // Move the map to the front of the list.
            اگر (i) {
                SDL_memmove(keymap_cache + 1, keymap_cache, حجم(ساخت WIN_KeymapCache) * i);
                keymap_cache[0].keyboard_layout = layout;
                keymap_cache[0].keymap = keymap;
            }
            توڑو;
        }
    }
    واپس keymap;
}

ساکن خالی WIN_CacheKeymap(HKL layout, SDL_Keymap *keymap)
{
    // If the cache is full, evict the last keymap.
    اگر (keymap_cache_سائز == SDL_arraysize(keymap_cache)) {
        SDL_DestroyKeymap(keymap_cache[--keymap_cache_سائز].keymap);
    }

    // Move all elements down by one.
    اگر (keymap_cache_سائز) {
        SDL_memmove(keymap_cache + 1, keymap_cache, حجم(ساخت WIN_KeymapCache) * keymap_cache_سائز);
    }

    keymap_cache[0].keyboard_layout = layout;
    keymap_cache[0].keymap = keymap;
    ++keymap_cache_سائز;
}

ساکن SDL_Keymap *WIN_BuildKeymap(خالی)
{
    SDL_Scancode scancode;
    BYTE keyboardState[256] = { 0 };
    WCHAR بفر_2[16];
    ثابت SDL_Keymod mods[] = {
        SDL_KMOD_NONE,
        SDL_KMOD_سرکاؤ,
        SDL_KMOD_CAPS,
        (SDL_KMOD_سرکاؤ | SDL_KMOD_CAPS),
        SDL_KMOD_منوال,
        (SDL_KMOD_منوال | SDL_KMOD_سرکاؤ),
        (SDL_KMOD_منوال | SDL_KMOD_CAPS),
        (SDL_KMOD_منوال | SDL_KMOD_سرکاؤ | SDL_KMOD_CAPS)
    };

    WIN_Reset_Dead_کلیدیں();

    SDL_Keymap *keymap = SDL_CreateKeymap(false);
    اگر (!keymap) {
        واپس تہی;
    }

    برائے (صحیح m = 0; m < SDL_arraysize(mods); ++m) {
        برائے (صحیح i = 0; i < SDL_arraysize(windows_scancode_جدول); i++) {
            صحیح vk, sc, نتیجہ;
            Uint32 *ch = 0;

            // Make sure this scancode is a valid character scancode
            scancode = windows_scancode_جدول[i];
            اگر (scancode == SDL_SCANCODE_UNKNOWN ||
                scancode == SDL_SCANCODE_DELETE ||
                (SDL_GetKeymapKeycode(تہی, scancode, SDL_KMOD_NONE) & SDLK_SCANCODE_نقاب)) {

                // The Colemak mapping swaps Backspace and CapsLock
                اگر (mods[m] == SDL_KMOD_NONE &&
                    (scancode == SDL_SCANCODE_CAPSLOCK ||
                     scancode == SDL_SCANCODE_BACKSPACE)) {
                    vk = LOBYTE(Map_Virtual_کلید(i, MAPVK_VSC_مقصد_VK));
                    اگر (vk == VK_CAPITAL) {
                        SDL_سیٹ_Keymap_اندراج(keymap, scancode, mods[m], SDLK_CAPSLOCK);
                    } ورنہ اگر (vk == VK_عقب) {
                        SDL_سیٹ_Keymap_اندراج(keymap, scancode, mods[m], SDLK_BACKSPACE);
                    }
                }
                جاری;
            }

            // Unpack the single byte index to make the scan code.
            sc = MAKEWORD(i & 0x7f, (i & 0x80) ? 0xe0 : 0x00);
            vk = LOBYTE(Map_Virtual_کلید(sc, MAPVK_VSC_مقصد_VK));
            اگر (!vk) {
                جاری;
            }

            // Update the keyboard state for the modifiers
            keyboardState[VK_سرکاؤ] = (mods[m] & SDL_KMOD_سرکاؤ) ? 0x80 : 0x00;
            keyboardState[VK_CAPITAL] = (mods[m] & SDL_KMOD_CAPS) ? 0x01 : 0x00;
            keyboardState[VK_CONTROL] = (mods[m] & SDL_KMOD_منوال) ? 0x80 : 0x00;
            keyboardState[VK_MENU] = (mods[m] & SDL_KMOD_منوال) ? 0x80 : 0x00;

            نتیجہ = مقصد_Unicode(vk, sc, keyboardState, بفر_2, 16, 0);
            بفر_2[SDL_abs(نتیجہ)] = 0;

            // Convert UTF-16 to UTF-32 code points
            ch = (Uint32 *)SDL_iconv_string("UTF-32LE", "UTF-16LE", (ثابت حرف *)بفر_2, (SDL_abs(نتیجہ) + 1) * حجم(WCHAR));
            اگر (ch) {
                /* Windows keyboard layouts can emit several UTF-32 code points on a single key press.
                 * Use <U+FFFD REPLACEMENT CHARACTER> since we cannot fit into single SDL_Keycode value in SDL keymap.
                 * See https://kbdlayout.info/features/ligatures for a list of such keys. */
                SDL_سیٹ_Keymap_اندراج(keymap, scancode, mods[m], ch[1] == 0 ? ch[0] : 0xfffd);
                SDL_free(ch);
            } ورنہ {
                // The default keymap doesn't have any SDL_KMOD_MODE entries, so we don't need to override them
                اگر (!(mods[m] & SDL_KMOD_منوال)) {
                    SDL_سیٹ_Keymap_اندراج(keymap, scancode, mods[m], SDLK_UNKNOWN);
                }
            }

            اگر (نتیجہ < 0) {
                WIN_Reset_Dead_کلیدیں();
            }
        }
    }

    واپس keymap;
}

خالی WIN_UpdateKeymap(bool send_event)
{
    HKL layout = GetKeyboardLayout(0);
    SDL_Keymap *keymap = WIN_GetCachedKeymap(layout);
    اگر (!keymap) {
        keymap = WIN_BuildKeymap();
        اگر (keymap) {
            WIN_CacheKeymap(layout, keymap);
        }
    }

    SDL_سیٹ_Keymap(keymap, send_event);
}

// Alphabetic scancodes for PC keyboards
خالی WIN_InitKeyboard(SDL_VideoDevice *_this)
{
#اگر_غیر_تعریف_شدہ SDL_DISABLE_WINDOWS_IME
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    ڈیٹا->ime_candlistindexbase = 1;
    ڈیٹا->ime_composition_لمبائی = 32 * حجم(WCHAR);
    ڈیٹا->ime_composition = (WCHAR *)SDL_calloc(ڈیٹا->ime_composition_لمبائی, حجم(WCHAR));
#اگر_ختم // !SDL_DISABLE_WINDOWS_IME

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

خالی WIN_QuitKeyboard(SDL_VideoDevice *_this)
{
#اگر_غیر_تعریف_شدہ SDL_DISABLE_WINDOWS_IME
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    IME_Quit(ڈیٹا);

    اگر (ڈیٹا->ime_composition) {
        SDL_free(ڈیٹا->ime_composition);
        ڈیٹا->ime_composition = تہی;
    }
#اگر_ختم // !SDL_DISABLE_WINDOWS_IME

    برائے (صحیح i = 0; i < keymap_cache_سائز; ++i) {
        SDL_DestroyKeymap(keymap_cache[i].keymap);
    }
    SDL_zeroa(keymap_cache);
    keymap_cache_سائز = 0;
}

خالی WIN_Reset_Dead_کلیدیں(خالی)
{
    /*
    if a deadkey has been typed, but not the next character (which the deadkey might modify),
    this tries to undo the effect pressing the deadkey.
    see: http://archives.miloush.net/michkap/archive/2006/09/10/748775.html
    */
    BYTE keyboardState[256];
    WCHAR بفر_2[16];
    صحیح vk, sc, نتیجہ, i;

    اگر (!GetKeyboardState(keyboardState)) {
        واپس;
    }

    vk = VK_SPACE;
    sc = Map_Virtual_کلید(vk, MAPVK_VK_مقصد_VSC);
    اگر (sc == 0) {
        // the keyboard doesn't have this key
        واپس;
    }

    برائے (i = 0; i < 5; i++) {
        نتیجہ = مقصد_Unicode(vk, sc, keyboardState, بفر_2, 16, 0);
        اگر (نتیجہ > 0) {
            // success
            واپس;
        }
    }
}

bool WIN_آغاز_متن_داخلہ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props)
{
    WIN_Reset_Dead_کلیدیں();

#اگر_غیر_تعریف_شدہ SDL_DISABLE_WINDOWS_IME
    HWND hwnd = کھڑکی->اندرونی_2->hwnd;
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    IME_Init(videodata, کھڑکی);
    IME_Enable(videodata, hwnd);

    WIN_Update_متن_داخلہ_Area(_this, کھڑکی);
#اگر_ختم // !SDL_DISABLE_WINDOWS_IME

    واپس true;
}

bool WIN_Stop_متن_داخلہ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    WIN_Reset_Dead_کلیدیں();

#اگر_غیر_تعریف_شدہ SDL_DISABLE_WINDOWS_IME
    HWND hwnd = کھڑکی->اندرونی_2->hwnd;
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    IME_Init(videodata, کھڑکی);
    IME_Disable(videodata, hwnd);
#اگر_ختم // !SDL_DISABLE_WINDOWS_IME

    واپس true;
}

bool WIN_Update_متن_داخلہ_Area(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;

    IME_سیٹ_متن_داخلہ_Area(videodata, ڈیٹا->hwnd, &کھڑکی->متن_داخلہ_rect, کھڑکی->متن_داخلہ_cursor);
    واپس true;
}

bool WIN_ClearComposition(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#اگر_غیر_تعریف_شدہ SDL_DISABLE_WINDOWS_IME
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;

    IME_ClearComposition(videodata);
#اگر_ختم
    واپس true;
}

#اگر_تعریف_شدہ SDL_DISABLE_WINDOWS_IME

bool WIN_HandleIMEMessage(HWND hwnd, UINT پیغام_2, WPARAM wParam, LPARAM *lParam, SDL_Video_ڈیٹا *videodata)
{
    واپس false;
}

خالی WIN_UpdateIMECandidates(SDL_VideoDevice *_this)
{
    واپس;
}

#ورنہ

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

ساکن خالی IME_Update_داخلہ_Locale(SDL_Video_ڈیٹا *videodata);
ساکن خالی IME_سیٹ_کھڑکی(SDL_Video_ڈیٹا *videodata, SDL_کھڑکی *کھڑکی);
ساکن خالی IME_تیاری_API(SDL_Video_ڈیٹا *videodata);
ساکن DWORD IME_GetId(SDL_Video_ڈیٹا *videodata, UINT u_اشاریہ);
ساکن خالی IME_SendEditingEvent(SDL_Video_ڈیٹا *videodata);
ساکن خالی IME_SendClearComposition(SDL_Video_ڈیٹا *videodata);

ساکن bool IME_Init(SDL_Video_ڈیٹا *videodata, SDL_کھڑکی *کھڑکی)
{
    HWND hwnd = کھڑکی->اندرونی_2->hwnd;

    اگر (videodata->ime_initialized) {
        واپس true;
    }

    ثابت حرف *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);
    اگر (hint && SDL_strstr(hint, "composition")) {
        videodata->ime_اندرونی_composition = true;
    }
    اگر (hint && SDL_strstr(hint, "candidates")) {
        videodata->ime_اندرونی_candidates = true;
    }

    videodata->ime_hwnd_main = hwnd;
    videodata->ime_initialized = true;
    videodata->ime_himm32 = SDL_بھرو_Object("imm32.dll");
    اگر (!videodata->ime_himm32) {
        videodata->ime_دستیاب = false;
        SDL_ClearError();
        واپس true;
    }
    /* *INDENT-OFF* */ // clang-format off
    videodata->Imm_تالا_IMC = (LPINPUTCONTEXT2 (WINAPI *)(HIMC))SDL_بھرو_Function(videodata->ime_himm32, "ImmLockIMC");
    videodata->ImmUnlockIMC = (BOOL (WINAPI *)(HIMC))SDL_بھرو_Function(videodata->ime_himm32, "ImmUnlockIMC");
    videodata->Imm_تالا_IMCC = (LPVOID (WINAPI *)(HIMCC))SDL_بھرو_Function(videodata->ime_himm32, "ImmLockIMCC");
    videodata->ImmUnlockIMCC = (BOOL (WINAPI *)(HIMCC))SDL_بھرو_Function(videodata->ime_himm32, "ImmUnlockIMCC");
    /* *INDENT-ON* */ // clang-format on

    IME_سیٹ_کھڑکی(videodata, کھڑکی);
    videodata->ime_himc = ImmGetContext(hwnd);
    ImmReleaseContext(hwnd, videodata->ime_himc);
    اگر (!videodata->ime_himc) {
        videodata->ime_دستیاب = false;
        IME_Disable(videodata, hwnd);
        واپس true;
    }
    videodata->ime_دستیاب = true;
    IME_Update_داخلہ_Locale(videodata);
    IME_تیاری_API(videodata);
    IME_Update_داخلہ_Locale(videodata);
    IME_Disable(videodata, hwnd);
    واپس true;
}

ساکن خالی IME_Enable(SDL_Video_ڈیٹا *videodata, HWND hwnd)
{
    اگر (!videodata->ime_initialized || !videodata->ime_hwnd_current) {
        واپس;
    }

    اگر (!videodata->ime_دستیاب) {
        IME_Disable(videodata, hwnd);
        واپس;
    }
    اگر (videodata->ime_hwnd_current == videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_current, videodata->ime_himc);
    }

    videodata->ime_enabled = true;
    IME_Update_داخلہ_Locale(videodata);
}

ساکن خالی IME_Disable(SDL_Video_ڈیٹا *videodata, HWND hwnd)
{
    اگر (!videodata->ime_initialized || !videodata->ime_hwnd_current) {
        واپس;
    }

    IME_ClearComposition(videodata);
    اگر (videodata->ime_hwnd_current == videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_current, (HIMC)0);
    }

    videodata->ime_enabled = false;
}

ساکن خالی IME_Quit(SDL_Video_ڈیٹا *videodata)
{
    اگر (!videodata->ime_initialized) {
        واپس;
    }

    اگر (videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_main, videodata->ime_himc);
    }

    videodata->ime_hwnd_main = 0;
    videodata->ime_himc = 0;
    اگر (videodata->ime_himm32) {
        SDL_UnloadObject(videodata->ime_himm32);
        videodata->ime_himm32 = 0;
    }
    برائے (صحیح i = 0; i < videodata->ime_candcount; ++i) {
        SDL_free(videodata->ime_candidates[i]);
        videodata->ime_candidates[i] = تہی;
    }
    videodata->ime_initialized = false;
}

ساکن خالی IME_GetReadingString(SDL_Video_ڈیٹا *videodata, HWND hwnd)
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
    اگر (!id) {
        واپس;
    }

    himc = ImmGetContext(hwnd);
    اگر (!himc) {
        واپس;
    }

    اگر (videodata->GetReadingString) {
        len = videodata->GetReadingString(himc, 0, 0, &err, &vertical, &maxuilen);
        اگر (len) {
            اگر (len > SDL_arraysize(بفر_2)) {
                len = SDL_arraysize(بفر_2);
            }

            len = videodata->GetReadingString(himc, len, s, &err, &vertical, &maxuilen);
        }
        SDL_wcslcpy(videodata->ime_readingstring, s, len);
    } ورنہ {
        LPINPUTCONTEXT2 lpimc = videodata->Imm_تالا_IMC(himc);
        LPBYTE p = 0;
        s = 0;
        انتخاب (id) {
        حالت IMEID_CHT_VER42:
        حالت IMEID_CHT_VER43:
        حالت IMEID_CHT_VER44:
            p = *(LPBYTE *)((LPBYTE)videodata->Imm_تالا_IMCC(lpimc->h_نجی) + 24);
            اگر (!p) {
                توڑو;
            }

            len = *(DWORD *)(p + 7 * 4 + 32 * 4);
            s = (WCHAR *)(p + 56);
            توڑو;
        حالت IMEID_CHT_VER51:
        حالت IMEID_CHT_VER52:
        حالت IMEID_CHS_VER53:
            p = *(LPBYTE *)((LPBYTE)videodata->Imm_تالا_IMCC(lpimc->h_نجی) + 4);
            اگر (!p) {
                توڑو;
            }

            p = *(LPBYTE *)(p + 1 * 4 + 5 * 4);
            اگر (!p) {
                توڑو;
            }

            len = *(DWORD *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4 + 16 * 2);
            s = (WCHAR *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4);
            توڑو;
        حالت IMEID_CHS_VER41:
        {
            صحیح انحراف_2 = (IME_GetId(videodata, 1) >= 0x00000002) ? 8 : 7;
            p = *(LPBYTE *)((LPBYTE)videodata->Imm_تالا_IMCC(lpimc->h_نجی) + انحراف_2 * 4);
            اگر (!p) {
                توڑو;
            }

            len = *(DWORD *)(p + 7 * 4 + 16 * 2 * 4);
            s = (WCHAR *)(p + 6 * 4 + 16 * 2 * 1);
        } توڑو;
        حالت IMEID_CHS_VER42:
            p = *(LPBYTE *)((LPBYTE)videodata->Imm_تالا_IMCC(lpimc->h_نجی) + 1 * 4 + 1 * 4 + 6 * 4);
            اگر (!p) {
                توڑو;
            }

            len = *(DWORD *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4 + 16 * 2);
            s = (WCHAR *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4);
            توڑو;
        }
        اگر (s) {
            size_t سائز = SDL_min((size_t)(len + 1), SDL_arraysize(videodata->ime_readingstring));
            SDL_wcslcpy(videodata->ime_readingstring, s, سائز);
        }

        videodata->ImmUnlockIMCC(lpimc->h_نجی);
        videodata->ImmUnlockIMC(himc);
    }
    ImmReleaseContext(hwnd, himc);
    IME_SendEditingEvent(videodata);
}

ساکن خالی IME_داخلہ_Lang_بدلا(SDL_Video_ڈیٹا *videodata)
{
    UINT lang = PRIMLANG();
    IME_Update_داخلہ_Locale(videodata);

    IME_تیاری_API(videodata);
    اگر (lang != PRIMLANG()) {
        IME_ClearComposition(videodata);
    }
}

ساکن DWORD IME_GetId(SDL_Video_ڈیٹا *videodata, UINT u_اشاریہ)
{
    ساکن HKL hklprev = 0;
    ساکن DWORD dwRet[2] = { 0 };
    DWORD dw_Ver_سائز = 0;
    LPVOID lp_Ver_بفر = 0;
    LPVOID lp_Ver_ڈیٹا = 0;
    UINT cb_Ver_ڈیٹا = 0;
    حرف sz_عارضی[256];
    HKL hkl = 0;
    DWORD dwLang = 0;
    SDL_assert(u_اشاریہ < SDL_arraysize(dwRet));

    hkl = videodata->ime_hkl;
    اگر (hklprev == hkl) {
        واپس dwRet[u_اشاریہ];
    }
    hklprev = hkl;

    SDL_assert(u_اشاریہ == 0);
    dwLang = ((DWORD_PTR)hkl & 0xffff);
    // FIXME: What does this do?
    اگر (videodata->ime_اندرونی_candidates && dwLang == LANG_CHT) {
        dwRet[0] = IMEID_CHT_VER_VISTA;
        dwRet[1] = 0;
        واپس dwRet[0];
    }
    اگر (hkl != CHT_HKL_NEW_PHONETIC && hkl != CHT_HKL_NEW_CHANG_JIE && hkl != CHT_HKL_NEW_تیز && hkl != CHT_HKL_HK_CANTONESE && hkl != CHS_HKL) {
        dwRet[0] = dwRet[1] = 0;
        واپس dwRet[0];
    }
    اگر (!ImmGetIMEFileNameA(hkl, sz_عارضی, حجم(sz_عارضی) - 1)) {
        dwRet[0] = dwRet[1] = 0;
        واپس dwRet[0];
    }
    اگر (!videodata->GetReadingString) {
#تعریف_کرو LCID_INVARIANT MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), ترتیب_دو_DEFAULT)
        اگر (CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_عارضی, -1, CHT_IMEFILENAME1, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_عارضی, -1, CHT_IMEFILENAME2, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_عارضی, -1, CHT_IMEFILENAME3, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_عارضی, -1, CHS_IMEFILENAME1, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_عارضی, -1, CHS_IMEFILENAME2, -1) != 2) {
            dwRet[0] = dwRet[1] = 0;
            واپس dwRet[0];
        }
#تعریف_منسوخ LCID_INVARIANT
        dw_Ver_سائز = Get_File_نسخہ_Info_سائز_A(sz_عارضی, تہی);
        اگر (dw_Ver_سائز) {
            lp_Ver_بفر = SDL_malloc(dw_Ver_سائز);
            اگر (lp_Ver_بفر) {
                اگر (Get_File_نسخہ_Info_A(sz_عارضی, 0, dw_Ver_سائز, lp_Ver_بفر)) {
                    اگر (Ver_Query_قدر_A(lp_Ver_بفر, "\\", &lp_Ver_ڈیٹا, &cb_Ver_ڈیٹا)) {
#تعریف_کرو pVerFixedInfo ((VS_FIXEDFILEINFO FAR *)lp_Ver_ڈیٹا)
                        DWORD dwVer = pVerFixedInfo->dw_File_نسخہ_MS;
                        dwVer = (dwVer & 0x00ff0000) << 8 | (dwVer & 0x000000ff) << 16;
                        اگر ((videodata->GetReadingString) ||
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
                            واپس dwRet[0];
                        }
#تعریف_منسوخ pVerFixedInfo
                    }
                }
            }
            SDL_free(lp_Ver_بفر);
        }
    }
    dwRet[0] = dwRet[1] = 0;
    واپس dwRet[0];
}

ساکن خالی IME_تیاری_API(SDL_Video_ڈیٹا *videodata)
{
    حرف ime_file[MAX_راستہ + 1];
    SDL_SharedObject *hime = 0;
    HKL hkl = 0;
    videodata->GetReadingString = تہی;
    videodata->Show_Reading_کھڑکی = تہی;

    hkl = videodata->ime_hkl;
    اگر (!ImmGetIMEFileNameA(hkl, ime_file, حجم(ime_file) - 1)) {
        واپس;
    }

    hime = SDL_بھرو_Object(ime_file);
    اگر (!hime) {
        واپس;
    }

    /* *INDENT-OFF* */ // clang-format off
    videodata->GetReadingString = (UINT (WINAPI *)(HIMC, UINT, LPWSTR, PINT, BOOL*, PUINT))
        SDL_بھرو_Function(hime, "GetReadingString");
    videodata->Show_Reading_کھڑکی = (BOOL (WINAPI *)(HIMC, BOOL))
        SDL_بھرو_Function(hime, "ShowReadingWindow");
    /* *INDENT-ON* */ // clang-format on

    اگر (videodata->Show_Reading_کھڑکی) {
        HIMC himc = ImmGetContext(videodata->ime_hwnd_current);
        اگر (himc) {
            videodata->Show_Reading_کھڑکی(himc, FALSE);
            ImmReleaseContext(videodata->ime_hwnd_current, himc);
        }
    }
}

ساکن خالی IME_سیٹ_کھڑکی(SDL_Video_ڈیٹا *videodata, SDL_کھڑکی *کھڑکی)
{
    HWND hwnd = کھڑکی->اندرونی_2->hwnd;

    اگر (hwnd != videodata->ime_hwnd_current) {
        videodata->ime_hwnd_current = hwnd;
        SDL_zero(videodata->ime_composition_area);
        SDL_zero(videodata->ime_candidate_area);
    }

    IME_سیٹ_متن_داخلہ_Area(videodata, hwnd, &کھڑکی->متن_داخلہ_rect, کھڑکی->متن_داخلہ_cursor);
}

#اگر_ختم

ساکن خالی IME_سیٹ_متن_داخلہ_Area(SDL_Video_ڈیٹا *videodata, HWND hwnd, ثابت SDL_Rect *rect, صحیح cursor)
{
    HIMC himc;

    himc = ImmGetContext(hwnd);
    اگر (himc) {
        COMPOSITIONFORM cof;
        CANDIDATEFORM caf;
        صحیح font_اونچائی = rect->h;

        LOGFONTW font;
        اگر (ImmGetCompositionFontW(himc, &font)) {
            font_اونچائی = font.lf_اونچائی;
        }

        SDL_zero(cof);
        cof.dwStyle = CFS_RECT;
        cof.ptCurrentPos.x = rect->x + cursor;
        cof.ptCurrentPos.y = rect->y + (rect->h - font_اونچائی) / 2;
        cof.rcArea.بایاں = rect->x;
        cof.rcArea.دایاں = (LONG)rect->x + rect->w;
        cof.rcArea.چوٹی = rect->y;
        cof.rcArea.bottom = (LONG)rect->y + rect->h;
        اگر (SDL_memcmp(&cof, &videodata->ime_composition_area, حجم(cof)) != 0) {
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
        اگر (SDL_memcmp(&caf, &videodata->ime_candidate_area, حجم(caf)) != 0) {
            SDL_copyp(&videodata->ime_candidate_area, &caf);
            Imm_سیٹ_Candidate_کھڑکی(himc, &caf);
        }

        ImmReleaseContext(hwnd, himc);
    }
}

#اگر_غیر_تعریف_شدہ SDL_DISABLE_WINDOWS_IME

ساکن خالی IME_Update_داخلہ_Locale(SDL_Video_ڈیٹا *videodata)
{
    HKL hklnext = GetKeyboardLayout(0);

    اگر (hklnext == videodata->ime_hkl) {
        واپس;
    }

    videodata->ime_hkl = hklnext;
    videodata->ime_horizontal_candidates = (PRIMLANG() == LANG_KOREAN || LANG() == LANG_CHS);
    videodata->ime_candlistindexbase = (videodata->ime_hkl == CHT_HKL_DAYI) ? 0 : 1;
}

ساکن خالی IME_ClearComposition(SDL_Video_ڈیٹا *videodata)
{
    HIMC himc = 0;
    اگر (!videodata->ime_initialized) {
        واپس;
    }

    himc = ImmGetContext(videodata->ime_hwnd_current);
    اگر (!himc) {
        واپس;
    }

    ImmNotifyIME(himc, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
    Imm_سیٹ_Composition_String(himc, SCS_SETSTR, متن_2(""), حجم(TCHAR), متن_2(""), حجم(TCHAR));

    ImmNotifyIME(himc, NI_CLOSECANDIDATE, 0, 0);
    ImmReleaseContext(videodata->ime_hwnd_current, himc);
    IME_SendClearComposition(videodata);
}

ساکن خالی IME_GetCompositionString(SDL_Video_ڈیٹا *videodata, HIMC himc, LPARAM *lParam, DWORD string)
{
    LONG لمبائی;
    DWORD dwLang = ((DWORD_PTR)videodata->ime_hkl & 0xffff);

    اگر (*lParam & GCS_CURSORPOS) {
        videodata->ime_cursor = LOWORD(ImmGetCompositionStringW(himc, GCS_CURSORPOS, 0, 0));
    }
    videodata->ime_selected_آغاز = 0;
    videodata->ime_selected_لمبائی = 0;
    SDL_DebugIMELog("Cursor = %d", videodata->ime_cursor);

    لمبائی = ImmGetCompositionStringW(himc, string, تہی, 0);
    اگر (لمبائی > 0 && videodata->ime_composition_لمبائی < لمبائی) {
        SDL_free(videodata->ime_composition);

        videodata->ime_composition = (WCHAR *)SDL_malloc(لمبائی + حجم(WCHAR));
        videodata->ime_composition_لمبائی = لمبائی;
    }

    لمبائی = ImmGetCompositionStringW(himc, string, videodata->ime_composition, videodata->ime_composition_لمبائی);
    اگر (لمبائی < 0) {
        لمبائی = 0;
    }
    لمبائی /= حجم(WCHAR);

    اگر (!(*lParam & GCS_CURSORPOS)) {
        // If the IME doesn't support GCS_CURSORPOS, default the cursor to the end of the composition.
        videodata->ime_cursor = لمبائی;
    }

    اگر ((dwLang == LANG_CHT || dwLang == LANG_CHS) &&
        videodata->ime_cursor > 0 &&
        videodata->ime_cursor < (صحیح)(videodata->ime_composition_لمبائی / حجم(WCHAR)) &&
        (videodata->ime_composition[0] == 0x3000 || videodata->ime_composition[0] == 0x0020)) {
        // Traditional Chinese IMEs add a placeholder U+3000
        // Simplified Chinese IMEs seem to add a placeholder U+0020 sometimes
        برائے (صحیح i = videodata->ime_cursor + 1; i < لمبائی; ++i) {
            videodata->ime_composition[i - 1] = videodata->ime_composition[i];
        }
        --لمبائی;
    }

    videodata->ime_composition[لمبائی] = 0;

    لمبائی = ImmGetCompositionStringW(himc, GCS_COMPATTR, تہی, 0);
    اگر (لمبائی > 0) {
        Uint8 *اوصاف = (Uint8 *)SDL_malloc(لمبائی);
        اگر (اوصاف) {
            صحیح آغاز = 0;
            صحیح انتہا = 0;

            لمبائی = ImmGetCompositionString(himc, GCS_COMPATTR, اوصاف, لمبائی);
            اگر (لمبائی < 0) {
                لمبائی = 0;
            }

            برائے (LONG i = 0; i < لمبائی; ++i) {
                SDL_DebugIMELog("attrib[%d] = %d", i, اوصاف[i]);
            }

            برائے (آغاز = 0; آغاز < لمبائی; ++آغاز) {
                اگر (اوصاف[آغاز] == ATTR_ہدف_CONVERTED || اوصاف[آغاز] == ATTR_ہدف_NOTCONVERTED) {
                    توڑو;
                }
            }

            برائے (انتہا = آغاز; انتہا < لمبائی; ++انتہا) {
                اگر (اوصاف[انتہا] != ATTR_ہدف_CONVERTED && اوصاف[انتہا] != ATTR_ہدف_NOTCONVERTED) {
                    توڑو;
                }
            }

            اگر (انتہا > آغاز) {
                videodata->ime_selected_آغاز = آغاز;
                videodata->ime_selected_لمبائی = انتہا - آغاز;
            }

            SDL_free(اوصاف);
        }
    }
}

ساکن خالی IME_Send_داخلہ_Event(SDL_Video_ڈیٹا *videodata)
{
    حرف *s = 0;
    s = WIN_String_مقصد_UTF8_W(videodata->ime_composition);
    SDL_Send_Keyboard_متن(s);
    SDL_free(s);

    videodata->ime_composition[0] = 0;
    videodata->ime_readingstring[0] = 0;
    videodata->ime_cursor = 0;
}

ساکن خالی IME_SendEditingEvent(SDL_Video_ڈیٹا *videodata)
{
    حرف *s = تہی;
    WCHAR *بفر_2 = تہی;
    size_t سائز = videodata->ime_composition_لمبائی;
    اگر (videodata->ime_readingstring[0]) {
        size_t len = SDL_min(SDL_wcslen(videodata->ime_composition), (size_t)videodata->ime_cursor);

        سائز += حجم(videodata->ime_readingstring);
        بفر_2 = (WCHAR *)SDL_malloc(سائز + حجم(WCHAR));
        اگر (!بفر_2) {
            واپس;
        }
        بفر_2[0] = 0;

        SDL_wcslcpy(بفر_2, videodata->ime_composition, len + 1);
        SDL_wcslcat(بفر_2, videodata->ime_readingstring, سائز);
        SDL_wcslcat(بفر_2, &videodata->ime_composition[len], سائز);
    } ورنہ {
        بفر_2 = (WCHAR *)SDL_malloc(سائز + حجم(WCHAR));
        اگر (!بفر_2) {
            واپس;
        }
        بفر_2[0] = 0;
        SDL_wcslcpy(بفر_2, videodata->ime_composition, سائز);
    }

    s = WIN_String_مقصد_UTF8_W(بفر_2);
    اگر (s) {
        اگر (videodata->ime_readingstring[0]) {
            SDL_Send_Editing_متن(s, videodata->ime_cursor, (صحیح)SDL_wcslen(videodata->ime_readingstring));
        } ورنہ اگر (videodata->ime_cursor == videodata->ime_selected_آغاز) {
            SDL_Send_Editing_متن(s, videodata->ime_selected_آغاز, videodata->ime_selected_لمبائی);
        } ورنہ {
            SDL_Send_Editing_متن(s, videodata->ime_cursor, 0);
        }
        اگر (*s) {
            videodata->ime_needs_clear_composition = true;
        }
        SDL_free(s);
    }
    SDL_free(بفر_2);
}

ساکن خالی IME_SendClearComposition(SDL_Video_ڈیٹا *videodata)
{
    اگر (videodata->ime_needs_clear_composition) {
        SDL_Send_Editing_متن("", 0, 0);
        videodata->ime_needs_clear_composition = false;
    }
}

ساکن bool IME_OpenCandidateList(SDL_Video_ڈیٹا *videodata)
{
    videodata->ime_candidates_open = true;
    videodata->ime_candcount = 0;
    واپس true;
}

ساکن خالی IME_جوڑو_Candidate(SDL_Video_ڈیٹا *videodata, UINT i, LPCWSTR candidate)
{
    اگر (videodata->ime_candidates[i]) {
        SDL_free(videodata->ime_candidates[i]);
        videodata->ime_candidates[i] = تہی;
    }

    SDL_COMPILE_وقت_ASSERT(IME_CANDIDATE_INDEXING_REQUIRES, MAX_CANDLIST == 10);
    حرف *candidate_utf8 = WIN_String_مقصد_UTF8_W(candidate);
    SDL_asprintf(&videodata->ime_candidates[i], "%d %s", ((i + videodata->ime_candlistindexbase) % 10), candidate_utf8);
    SDL_free(candidate_utf8);

    videodata->ime_candcount = (i + 1);
}

ساکن خالی IME_SendCandidateList(SDL_Video_ڈیٹا *videodata)
{
    SDL_Send_Editing_متن_Candidates(videodata->ime_candidates, videodata->ime_candcount, videodata->ime_candsel, videodata->ime_horizontal_candidates);
}

ساکن خالی IME_CloseCandidateList(SDL_Video_ڈیٹا *videodata)
{
    videodata->ime_candidates_open = false;

    اگر (videodata->ime_candcount > 0) {
        برائے (صحیح i = 0; i < videodata->ime_candcount; ++i) {
            SDL_free(videodata->ime_candidates[i]);
            videodata->ime_candidates[i] = تہی;
        }
        videodata->ime_candcount = 0;

        SDL_Send_Editing_متن_Candidates(تہی, 0, -1, false);
    }
}

ساکن خالی IME_GetCandidateList(SDL_Video_ڈیٹا *videodata, HWND hwnd)
{
    HIMC himc;
    DWORD سائز;
    LPCANDIDATELIST cand_list;
    bool has_candidates = false;

    himc = ImmGetContext(hwnd);
    اگر (himc) {
        سائز = ImmGetCandidateListW(himc, 0, تہی, 0);
        اگر (سائز != 0) {
            cand_list = (LPCANDIDATELIST)SDL_malloc(سائز);
            اگر (cand_list != تہی) {
                سائز = ImmGetCandidateListW(himc, 0, cand_list, سائز);
                اگر (سائز != 0) {
                    اگر (IME_OpenCandidateList(videodata)) {
                        UINT i, j;
                        UINT صفحہ_آغاز = 0;
                        UINT صفحہ_سائز = 0;

                        videodata->ime_candsel = cand_list->dwSelection;

                        اگر (LANG() == LANG_CHS && IME_GetId(videodata, 0)) {
                            ثابت UINT maxcandchar = 18;
                            size_t cchars = 0;

                            برائے (i = 0; i < cand_list->dw_گنتی; ++i) {
                                size_t len = SDL_wcslen((LPWSTR)((DWORD_PTR)cand_list + cand_list->dw_انحراف[i])) + 1;
                                اگر (len + cchars > maxcandchar) {
                                    اگر (i > cand_list->dwSelection) {
                                        توڑو;
                                    }

                                    صفحہ_آغاز = i;
                                    cchars = len;
                                } ورنہ {
                                    cchars += len;
                                }
                            }
                            صفحہ_سائز = i - صفحہ_آغاز;
                        } ورنہ {
                            صفحہ_سائز = SDL_min(cand_list->dw_صفحہ_سائز == 0 ? MAX_CANDLIST : cand_list->dw_صفحہ_سائز, MAX_CANDLIST);
                            صفحہ_آغاز = (cand_list->dwSelection / صفحہ_سائز) * صفحہ_سائز;
                        }
                        برائے (i = صفحہ_آغاز, j = 0; (DWORD)i < cand_list->dw_گنتی && j < صفحہ_سائز; i++, j++) {
                            LPCWSTR candidate = (LPCWSTR)((DWORD_PTR)cand_list + cand_list->dw_انحراف[i]);
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

    اگر (!has_candidates) {
        IME_CloseCandidateList(videodata);
    }
}

bool WIN_HandleIMEMessage(HWND hwnd, UINT پیغام_2, WPARAM wParam, LPARAM *lParam, SDL_Video_ڈیٹا *videodata)
{
    bool trap = false;
    HIMC himc = 0;

    اگر (پیغام_2 == WM_IME_SETCONTEXT) {
        SDL_DebugIMELog("WM_IME_SETCONTEXT");

        LPARAM element_نقاب;
        element_نقاب = ISC_SHOWUIALL;
        اگر (videodata->ime_اندرونی_composition) {
            element_نقاب &= ~ISC_SHOWUICOMPOSITIONWINDOW;
        }
        اگر (videodata->ime_اندرونی_candidates) {
            element_نقاب &= ~ISC_SHOWUIALLCANDIDATEWINDOW;
        }
        *lParam &= element_نقاب;

        واپس false;
    } ورنہ اگر (پیغام_2 == WM_IME_STARTCOMPOSITION) {
        SDL_DebugIMELog("WM_IME_STARTCOMPOSITION");
        اگر (videodata->ime_اندرونی_composition) {
            videodata->ime_cursor = 0;
            // Windows may still display a composition dialog even with
            // ISC_SHOWUICOMPOSITIONWINDOW cleared, so trap the message
            // here to prevent that (even when the IME is disabled).
            واپس true;
        }
    }

    اگر (!videodata->ime_initialized || !videodata->ime_دستیاب || !videodata->ime_enabled) {
        واپس false;
    }

    انتخاب (پیغام_2) {
    حالت WM_KEYDOWN:
        اگر (wParam == VK_PROCESSKEY) {
            SDL_DebugIMELog("WM_KEYDOWN VK_PROCESSKEY");
            trap = true;
        } ورنہ {
            SDL_DebugIMELog("WM_KEYDOWN normal");
        }
        توڑو;
    حالت WM_SYSKEYDOWN:
        اگر (wParam == VK_PROCESSKEY) {
            SDL_DebugIMELog("WM_SYSKEYDOWN VK_PROCESSKEY");
            trap = true;
        } ورنہ {
            SDL_DebugIMELog("WM_SYSKEYDOWN normal");
        }
        توڑو;
    حالت WM_INPUTLANGCHANGE:
        SDL_DebugIMELog("WM_INPUTLANGCHANGE");
        IME_داخلہ_Lang_بدلا(videodata);
        توڑو;
    حالت WM_IME_COMPOSITION:
        SDL_DebugIMELog("WM_IME_COMPOSITION %x", lParam);
        اگر (videodata->ime_اندرونی_composition) {
            trap = true;
            himc = ImmGetContext(hwnd);
            اگر (*lParam & GCS_RESULTSTR) {
                SDL_DebugIMELog("GCS_RESULTSTR");
                IME_GetCompositionString(videodata, himc, lParam, GCS_RESULTSTR);
                IME_SendClearComposition(videodata);
                IME_Send_داخلہ_Event(videodata);
            }
            اگر (*lParam & GCS_COMPSTR) {
                SDL_DebugIMELog("GCS_COMPSTR");
                videodata->ime_readingstring[0] = 0;
                IME_GetCompositionString(videodata, himc, lParam, GCS_COMPSTR);
                IME_SendEditingEvent(videodata);
            }
            ImmReleaseContext(hwnd, himc);
        }
        توڑو;
    حالت WM_IME_ENDCOMPOSITION:
        SDL_DebugIMELog("WM_IME_ENDCOMPOSITION");
        اگر (videodata->ime_اندرونی_composition) {
            trap = true;
            videodata->ime_composition[0] = 0;
            videodata->ime_readingstring[0] = 0;
            videodata->ime_cursor = 0;
            videodata->ime_selected_آغاز = 0;
            videodata->ime_selected_لمبائی = 0;
            IME_SendClearComposition(videodata);
        }
        توڑو;
    حالت WM_IME_NOTIFY:
        SDL_DebugIMELog("WM_IME_NOTIFY %x", wParam);
        انتخاب (wParam) {
        حالت IMN_SETCOMPOSITIONWINDOW:
            SDL_DebugIMELog("IMN_SETCOMPOSITIONWINDOW");
            توڑو;
        حالت IMN_SETCOMPOSITIONFONT:
            SDL_DebugIMELog("IMN_SETCOMPOSITIONFONT");
            توڑو;
        حالت IMN_SETCANDIDATEPOS:
            SDL_DebugIMELog("IMN_SETCANDIDATEPOS");
            توڑو;
        حالت IMN_SETCONVERSIONMODE:
        حالت IMN_SETOPENSTATUS:
            SDL_DebugIMELog("%s", wParam == IMN_SETCONVERSIONMODE ? "IMN_SETCONVERSIONMODE" : "IMN_SETOPENSTATUS");
            IME_Update_داخلہ_Locale(videodata);
            توڑو;
        حالت IMN_OPENCANDIDATE:
        حالت IMN_CHANGECANDIDATE:
            SDL_DebugIMELog("%s", wParam == IMN_OPENCANDIDATE ? "IMN_OPENCANDIDATE" : "IMN_CHANGECANDIDATE");
            اگر (videodata->ime_اندرونی_candidates) {
                trap = true;
                videodata->ime_update_candidates = true;
            }
            توڑو;
        حالت IMN_CLOSECANDIDATE:
            SDL_DebugIMELog("IMN_CLOSECANDIDATE");
            اگر (videodata->ime_اندرونی_candidates) {
                trap = true;
                videodata->ime_update_candidates = false;
                IME_CloseCandidateList(videodata);
            }
            توڑو;
        حالت IMN_نجی:
        {
            DWORD dwId = IME_GetId(videodata, 0);
            SDL_DebugIMELog("IMN_PRIVATE %u", dwId);
            IME_GetReadingString(videodata, hwnd);
            انتخاب (dwId) {
            حالت IMEID_CHT_VER42:
            حالت IMEID_CHT_VER43:
            حالت IMEID_CHT_VER44:
            حالت IMEID_CHS_VER41:
            حالت IMEID_CHS_VER42:
                اگر (*lParam == 1 || *lParam == 2) {
                    trap = true;
                }

                توڑو;
            حالت IMEID_CHT_VER50:
            حالت IMEID_CHT_VER51:
            حالت IMEID_CHT_VER52:
            حالت IMEID_CHT_VER60:
            حالت IMEID_CHS_VER53:
                اگر (*lParam == 16 || *lParam == 17 || *lParam == 26 || *lParam == 27 || *lParam == 28) {
                    trap = true;
                }
                توڑو;
            }
        } توڑو;
        طےشدہ:
            trap = true;
            توڑو;
        }
        توڑو;
    }
    واپس trap;
}

خالی WIN_UpdateIMECandidates(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;

    اگر (videodata->ime_update_candidates) {
        IME_GetCandidateList(videodata, videodata->ime_hwnd_current);
        videodata->ime_update_candidates = false;
    }
}

#اگر_ختم // SDL_DISABLE_WINDOWS_IME

#اگر_ختم // SDL_VIDEO_DRIVER_WINDOWS
