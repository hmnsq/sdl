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

#अन्तर्भाव "../../events/SDL_keyboard_c.h"
#अन्तर्भाव "../../events/scancodes_windows.h"

#अन्तर्भाव <imm.h>
#अन्तर्भाव <oleauto.h>

#यदि_अपरिभाषितम् SDL_DISABLE_WINDOWS_IME
#यदि 0
#परिभाषय SDL_DebugIMELog SDL_Log
#अन्यथा
#परिभाषय SDL_DebugIMELog(...)
#यदि_अन्तः
स्थिर bool IME_Init(SDL_Video_दत्त *videodata, SDL_गवाक्षः *गवाक्षः);
स्थिर शून्य IME_Enable(SDL_Video_दत्त *videodata, HWND hwnd);
स्थिर शून्य IME_Disable(SDL_Video_दत्त *videodata, HWND hwnd);
स्थिर शून्य IME_समुच्चयः_Text_निवेशः_Area(SDL_Video_दत्त *videodata, HWND hwnd, ध्रुव SDL_Rect *rect, पूर्णाङ्क cursor);
स्थिर शून्य IME_ClearComposition(SDL_Video_दत्त *videodata);
स्थिर शून्य IME_GetCandidateList(SDL_Video_दत्त *videodata, HWND hwnd);
स्थिर शून्य IME_Quit(SDL_Video_दत्त *videodata);
#अन्यथा
स्थिर शून्य IME_समुच्चयः_Text_निवेशः_Area(SDL_Video_दत्त *videodata, HWND hwnd, ध्रुव SDL_Rect *rect, पूर्णाङ्क cursor);
#यदि_अन्तः // !SDL_DISABLE_WINDOWS_IME

#यदि_अपरिभाषितम् MAPVK_VK_गन्तव्यम्_VSC
#परिभाषय MAPVK_VK_गन्तव्यम्_VSC 0
#यदि_अन्तः
#यदि_अपरिभाषितम् MAPVK_VSC_गन्तव्यम्_VK
#परिभाषय MAPVK_VSC_गन्तव्यम्_VK 1
#यदि_अन्तः

/* Building keymaps is expensive, so keep a reasonably-sized LRU cache to
 * enable fast switching between commonly used ones.
 */
स्थिर संरचना WIN_KeymapCache
{
    HKL keyboard_layout;
    SDL_Keymap *keymap;
} keymap_cache[4];

स्थिर पूर्णाङ्क keymap_cache_आकार;

स्थिर SDL_Keymap *WIN_GetCachedKeymap(HKL layout)
{
    SDL_Keymap *keymap = रिक्त;
    प्रति (पूर्णाङ्क i = 0; i < keymap_cache_आकार; ++i) {
        यदि (keymap_cache[i].keyboard_layout == layout) {
            keymap = keymap_cache[i].keymap;

            // Move the map to the front of the list.
            यदि (i) {
                SDL_memmove(keymap_cache + 1, keymap_cache, परिमाण(संरचना WIN_KeymapCache) * i);
                keymap_cache[0].keyboard_layout = layout;
                keymap_cache[0].keymap = keymap;
            }
            भङ्ग;
        }
    }
    प्रत्यागम keymap;
}

स्थिर शून्य WIN_CacheKeymap(HKL layout, SDL_Keymap *keymap)
{
    // If the cache is full, evict the last keymap.
    यदि (keymap_cache_आकार == SDL_arraysize(keymap_cache)) {
        SDL_DestroyKeymap(keymap_cache[--keymap_cache_आकार].keymap);
    }

    // Move all elements down by one.
    यदि (keymap_cache_आकार) {
        SDL_memmove(keymap_cache + 1, keymap_cache, परिमाण(संरचना WIN_KeymapCache) * keymap_cache_आकार);
    }

    keymap_cache[0].keyboard_layout = layout;
    keymap_cache[0].keymap = keymap;
    ++keymap_cache_आकार;
}

स्थिर SDL_Keymap *WIN_BuildKeymap(शून्य)
{
    SDL_Scancode scancode;
    BYTE keyboardState[256] = { 0 };
    WCHAR बफर_2[16];
    ध्रुव SDL_Keymod mods[] = {
        SDL_KMOD_NONE,
        SDL_KMOD_सरणम्,
        SDL_KMOD_CAPS,
        (SDL_KMOD_सरणम् | SDL_KMOD_CAPS),
        SDL_KMOD_बहुलकम्,
        (SDL_KMOD_बहुलकम् | SDL_KMOD_सरणम्),
        (SDL_KMOD_बहुलकम् | SDL_KMOD_CAPS),
        (SDL_KMOD_बहुलकम् | SDL_KMOD_सरणम् | SDL_KMOD_CAPS)
    };

    WIN_Reset_Dead_कुञ्चिकाः();

    SDL_Keymap *keymap = SDL_CreateKeymap(false);
    यदि (!keymap) {
        प्रत्यागम रिक्त;
    }

    प्रति (पूर्णाङ्क m = 0; m < SDL_arraysize(mods); ++m) {
        प्रति (पूर्णाङ्क i = 0; i < SDL_arraysize(windows_scancode_सारणी); i++) {
            पूर्णाङ्क vk, sc, परिणाम;
            Uint32 *ch = 0;

            // Make sure this scancode is a valid character scancode
            scancode = windows_scancode_सारणी[i];
            यदि (scancode == SDL_SCANCODE_UNKNOWN ||
                scancode == SDL_SCANCODE_DELETE ||
                (SDL_GetKeymapKeycode(रिक्त, scancode, SDL_KMOD_NONE) & SDLK_SCANCODE_आवरणम्)) {

                // The Colemak mapping swaps Backspace and CapsLock
                यदि (mods[m] == SDL_KMOD_NONE &&
                    (scancode == SDL_SCANCODE_CAPSLOCK ||
                     scancode == SDL_SCANCODE_BACKSPACE)) {
                    vk = LOBYTE(Map_Virtual_कुञ्चिका(i, MAPVK_VSC_गन्तव्यम्_VK));
                    यदि (vk == VK_CAPITAL) {
                        SDL_समुच्चयः_Keymap_प्रविष्टिः(keymap, scancode, mods[m], SDLK_CAPSLOCK);
                    } अन्यथा यदि (vk == VK_पृष्ठभागः) {
                        SDL_समुच्चयः_Keymap_प्रविष्टिः(keymap, scancode, mods[m], SDLK_BACKSPACE);
                    }
                }
                अनुवर्त;
            }

            // Unpack the single byte index to make the scan code.
            sc = MAKEWORD(i & 0x7f, (i & 0x80) ? 0xe0 : 0x00);
            vk = LOBYTE(Map_Virtual_कुञ्चिका(sc, MAPVK_VSC_गन्तव्यम्_VK));
            यदि (!vk) {
                अनुवर्त;
            }

            // Update the keyboard state for the modifiers
            keyboardState[VK_सरणम्] = (mods[m] & SDL_KMOD_सरणम्) ? 0x80 : 0x00;
            keyboardState[VK_CAPITAL] = (mods[m] & SDL_KMOD_CAPS) ? 0x01 : 0x00;
            keyboardState[VK_CONTROL] = (mods[m] & SDL_KMOD_बहुलकम्) ? 0x80 : 0x00;
            keyboardState[VK_MENU] = (mods[m] & SDL_KMOD_बहुलकम्) ? 0x80 : 0x00;

            परिणाम = गन्तव्यम्_Unicode(vk, sc, keyboardState, बफर_2, 16, 0);
            बफर_2[SDL_abs(परिणाम)] = 0;

            // Convert UTF-16 to UTF-32 code points
            ch = (Uint32 *)SDL_iconv_string("UTF-32LE", "UTF-16LE", (ध्रुव वर्ण *)बफर_2, (SDL_abs(परिणाम) + 1) * परिमाण(WCHAR));
            यदि (ch) {
                /* Windows keyboard layouts can emit several UTF-32 code points on a single key press.
                 * Use <U+FFFD REPLACEMENT CHARACTER> since we cannot fit into single SDL_Keycode value in SDL keymap.
                 * See https://kbdlayout.info/features/ligatures for a list of such keys. */
                SDL_समुच्चयः_Keymap_प्रविष्टिः(keymap, scancode, mods[m], ch[1] == 0 ? ch[0] : 0xfffd);
                SDL_free(ch);
            } अन्यथा {
                // The default keymap doesn't have any SDL_KMOD_MODE entries, so we don't need to override them
                यदि (!(mods[m] & SDL_KMOD_बहुलकम्)) {
                    SDL_समुच्चयः_Keymap_प्रविष्टिः(keymap, scancode, mods[m], SDLK_UNKNOWN);
                }
            }

            यदि (परिणाम < 0) {
                WIN_Reset_Dead_कुञ्चिकाः();
            }
        }
    }

    प्रत्यागम keymap;
}

शून्य WIN_UpdateKeymap(bool send_event)
{
    HKL layout = GetKeyboardLayout(0);
    SDL_Keymap *keymap = WIN_GetCachedKeymap(layout);
    यदि (!keymap) {
        keymap = WIN_BuildKeymap();
        यदि (keymap) {
            WIN_CacheKeymap(layout, keymap);
        }
    }

    SDL_समुच्चयः_Keymap(keymap, send_event);
}

// Alphabetic scancodes for PC keyboards
शून्य WIN_InitKeyboard(SDL_VideoDevice *_this)
{
#यदि_अपरिभाषितम् SDL_DISABLE_WINDOWS_IME
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    दत्त->ime_candlistindexbase = 1;
    दत्त->ime_composition_दीर्घता = 32 * परिमाण(WCHAR);
    दत्त->ime_composition = (WCHAR *)SDL_calloc(दत्त->ime_composition_दीर्घता, परिमाण(WCHAR));
#यदि_अन्तः // !SDL_DISABLE_WINDOWS_IME

    // Build and bind the current keymap.
    WIN_UpdateKeymap(false);

    SDL_समुच्चयः_Scancode_Name(SDL_SCANCODE_APPLICATION, "Menu");
    SDL_समुच्चयः_Scancode_Name(SDL_SCANCODE_LGUI, "Left Windows");
    SDL_समुच्चयः_Scancode_Name(SDL_SCANCODE_RGUI, "Right Windows");

    // Are system caps/num/scroll lock active? Set our state to match.
    SDL_ToggleModState(SDL_KMOD_CAPS, (Get_कुञ्चिका_State(VK_CAPITAL) & 0x0001) ? true : false);
    SDL_ToggleModState(SDL_KMOD_अङ्कः, (Get_कुञ्चिका_State(VK_NUMLOCK) & 0x0001) ? true : false);
    SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_कुञ्चिका_State(VK_SCROLL) & 0x0001) ? true : false);
}

शून्य WIN_QuitKeyboard(SDL_VideoDevice *_this)
{
#यदि_अपरिभाषितम् SDL_DISABLE_WINDOWS_IME
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    IME_Quit(दत्त);

    यदि (दत्त->ime_composition) {
        SDL_free(दत्त->ime_composition);
        दत्त->ime_composition = रिक्त;
    }
#यदि_अन्तः // !SDL_DISABLE_WINDOWS_IME

    प्रति (पूर्णाङ्क i = 0; i < keymap_cache_आकार; ++i) {
        SDL_DestroyKeymap(keymap_cache[i].keymap);
    }
    SDL_zeroa(keymap_cache);
    keymap_cache_आकार = 0;
}

शून्य WIN_Reset_Dead_कुञ्चिकाः(शून्य)
{
    /*
    if a deadkey has been typed, but not the next character (which the deadkey might modify),
    this tries to undo the effect pressing the deadkey.
    see: http://archives.miloush.net/michkap/archive/2006/09/10/748775.html
    */
    BYTE keyboardState[256];
    WCHAR बफर_2[16];
    पूर्णाङ्क vk, sc, परिणाम, i;

    यदि (!GetKeyboardState(keyboardState)) {
        प्रत्यागम;
    }

    vk = VK_SPACE;
    sc = Map_Virtual_कुञ्चिका(vk, MAPVK_VK_गन्तव्यम्_VSC);
    यदि (sc == 0) {
        // the keyboard doesn't have this key
        प्रत्यागम;
    }

    प्रति (i = 0; i < 5; i++) {
        परिणाम = गन्तव्यम्_Unicode(vk, sc, keyboardState, बफर_2, 16, 0);
        यदि (परिणाम > 0) {
            // success
            प्रत्यागम;
        }
    }
}

bool WIN_Start_Text_निवेशः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID props)
{
    WIN_Reset_Dead_कुञ्चिकाः();

#यदि_अपरिभाषितम् SDL_DISABLE_WINDOWS_IME
    HWND hwnd = गवाक्षः->आन्तरिकम्->hwnd;
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    IME_Init(videodata, गवाक्षः);
    IME_Enable(videodata, hwnd);

    WIN_Update_Text_निवेशः_Area(_this, गवाक्षः);
#यदि_अन्तः // !SDL_DISABLE_WINDOWS_IME

    प्रत्यागम true;
}

bool WIN_Stop_Text_निवेशः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    WIN_Reset_Dead_कुञ्चिकाः();

#यदि_अपरिभाषितम् SDL_DISABLE_WINDOWS_IME
    HWND hwnd = गवाक्षः->आन्तरिकम्->hwnd;
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    IME_Init(videodata, गवाक्षः);
    IME_Disable(videodata, hwnd);
#यदि_अन्तः // !SDL_DISABLE_WINDOWS_IME

    प्रत्यागम true;
}

bool WIN_Update_Text_निवेशः_Area(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;

    IME_समुच्चयः_Text_निवेशः_Area(videodata, दत्त->hwnd, &गवाक्षः->text_निवेशः_rect, गवाक्षः->text_निवेशः_cursor);
    प्रत्यागम true;
}

bool WIN_ClearComposition(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
#यदि_अपरिभाषितम् SDL_DISABLE_WINDOWS_IME
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;

    IME_ClearComposition(videodata);
#यदि_अन्तः
    प्रत्यागम true;
}

#यदि_परिभाषितम् SDL_DISABLE_WINDOWS_IME

bool WIN_HandleIMEMessage(HWND hwnd, UINT सन्देशः_2, WPARAM wParam, LPARAM *lParam, SDL_Video_दत्त *videodata)
{
    प्रत्यागम false;
}

शून्य WIN_UpdateIMECandidates(SDL_VideoDevice *_this)
{
    प्रत्यागम;
}

#अन्यथा

#परिभाषय LANG_CHT MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_TRADITIONAL)
#परिभाषय LANG_CHS MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED)

#परिभाषय MAKEIMEVERSION(major, minor) ((DWORD)(((BYTE)(major) << 24) | ((BYTE)(minor) << 16)))
#परिभाषय IMEID_VER(id)                ((id)&0xffff0000)
#परिभाषय IMEID_LANG(id)               ((id)&0x0000ffff)

#परिभाषय CHT_HKL_DAYI          ((HKL)(UINT_PTR)0xE0060404)
#परिभाषय CHT_HKL_NEW_PHONETIC  ((HKL)(UINT_PTR)0xE0080404)
#परिभाषय CHT_HKL_NEW_CHANG_JIE ((HKL)(UINT_PTR)0xE0090404)
#परिभाषय CHT_HKL_NEW_शीघ्र     ((HKL)(UINT_PTR)0xE00A0404)
#परिभाषय CHT_HKL_HK_CANTONESE  ((HKL)(UINT_PTR)0xE00B0404)
#परिभाषय CHT_IMEFILENAME1      "TINTLGNT.IME"
#परिभाषय CHT_IMEFILENAME2      "CINTLGNT.IME"
#परिभाषय CHT_IMEFILENAME3      "MSTCIPHA.IME"
#परिभाषय IMEID_CHT_VER42       (LANG_CHT | MAKEIMEVERSION(4, 2))
#परिभाषय IMEID_CHT_VER43       (LANG_CHT | MAKEIMEVERSION(4, 3))
#परिभाषय IMEID_CHT_VER44       (LANG_CHT | MAKEIMEVERSION(4, 4))
#परिभाषय IMEID_CHT_VER50       (LANG_CHT | MAKEIMEVERSION(5, 0))
#परिभाषय IMEID_CHT_VER51       (LANG_CHT | MAKEIMEVERSION(5, 1))
#परिभाषय IMEID_CHT_VER52       (LANG_CHT | MAKEIMEVERSION(5, 2))
#परिभाषय IMEID_CHT_VER60       (LANG_CHT | MAKEIMEVERSION(6, 0))
#परिभाषय IMEID_CHT_VER_VISTA   (LANG_CHT | MAKEIMEVERSION(7, 0))

#परिभाषय CHS_HKL          ((HKL)(UINT_PTR)0xE00E0804)
#परिभाषय CHS_IMEFILENAME1 "PINTLGNT.IME"
#परिभाषय CHS_IMEFILENAME2 "MSSCIPYA.IME"
#परिभाषय IMEID_CHS_VER41  (LANG_CHS | MAKEIMEVERSION(4, 1))
#परिभाषय IMEID_CHS_VER42  (LANG_CHS | MAKEIMEVERSION(4, 2))
#परिभाषय IMEID_CHS_VER53  (LANG_CHS | MAKEIMEVERSION(5, 3))

#परिभाषय LANG()         LOWORD((videodata->ime_hkl))
#परिभाषय PRIMLANG()     ((WORD)PRIMARYLANGID(LANG()))
#परिभाषय SUBLANG()      SUBLANGID(LANG())

स्थिर शून्य IME_Update_निवेशः_Locale(SDL_Video_दत्त *videodata);
स्थिर शून्य IME_समुच्चयः_गवाक्षः(SDL_Video_दत्त *videodata, SDL_गवाक्षः *गवाक्षः);
स्थिर शून्य IME_सज्जता_API(SDL_Video_दत्त *videodata);
स्थिर DWORD IME_GetId(SDL_Video_दत्त *videodata, UINT u_सूचकांक);
स्थिर शून्य IME_SendEditingEvent(SDL_Video_दत्त *videodata);
स्थिर शून्य IME_SendClearComposition(SDL_Video_दत्त *videodata);

स्थिर bool IME_Init(SDL_Video_दत्त *videodata, SDL_गवाक्षः *गवाक्षः)
{
    HWND hwnd = गवाक्षः->आन्तरिकम्->hwnd;

    यदि (videodata->ime_initialized) {
        प्रत्यागम true;
    }

    ध्रुव वर्ण *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);
    यदि (hint && SDL_strstr(hint, "composition")) {
        videodata->ime_आन्तरिकम्_composition = true;
    }
    यदि (hint && SDL_strstr(hint, "candidates")) {
        videodata->ime_आन्तरिकम्_candidates = true;
    }

    videodata->ime_hwnd_main = hwnd;
    videodata->ime_initialized = true;
    videodata->ime_himm32 = SDL_आरोपय_Object("imm32.dll");
    यदि (!videodata->ime_himm32) {
        videodata->ime_उपलब्धम् = false;
        SDL_ClearError();
        प्रत्यागम true;
    }
    /* *INDENT-OFF* */ // clang-format off
    videodata->Imm_तालकम्_IMC = (LPINPUTCONTEXT2 (WINAPI *)(HIMC))SDL_आरोपय_Function(videodata->ime_himm32, "ImmLockIMC");
    videodata->ImmUnlockIMC = (BOOL (WINAPI *)(HIMC))SDL_आरोपय_Function(videodata->ime_himm32, "ImmUnlockIMC");
    videodata->Imm_तालकम्_IMCC = (LPVOID (WINAPI *)(HIMCC))SDL_आरोपय_Function(videodata->ime_himm32, "ImmLockIMCC");
    videodata->ImmUnlockIMCC = (BOOL (WINAPI *)(HIMCC))SDL_आरोपय_Function(videodata->ime_himm32, "ImmUnlockIMCC");
    /* *INDENT-ON* */ // clang-format on

    IME_समुच्चयः_गवाक्षः(videodata, गवाक्षः);
    videodata->ime_himc = ImmGetContext(hwnd);
    ImmReleaseContext(hwnd, videodata->ime_himc);
    यदि (!videodata->ime_himc) {
        videodata->ime_उपलब्धम् = false;
        IME_Disable(videodata, hwnd);
        प्रत्यागम true;
    }
    videodata->ime_उपलब्धम् = true;
    IME_Update_निवेशः_Locale(videodata);
    IME_सज्जता_API(videodata);
    IME_Update_निवेशः_Locale(videodata);
    IME_Disable(videodata, hwnd);
    प्रत्यागम true;
}

स्थिर शून्य IME_Enable(SDL_Video_दत्त *videodata, HWND hwnd)
{
    यदि (!videodata->ime_initialized || !videodata->ime_hwnd_current) {
        प्रत्यागम;
    }

    यदि (!videodata->ime_उपलब्धम्) {
        IME_Disable(videodata, hwnd);
        प्रत्यागम;
    }
    यदि (videodata->ime_hwnd_current == videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_current, videodata->ime_himc);
    }

    videodata->ime_enabled = true;
    IME_Update_निवेशः_Locale(videodata);
}

स्थिर शून्य IME_Disable(SDL_Video_दत्त *videodata, HWND hwnd)
{
    यदि (!videodata->ime_initialized || !videodata->ime_hwnd_current) {
        प्रत्यागम;
    }

    IME_ClearComposition(videodata);
    यदि (videodata->ime_hwnd_current == videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_current, (HIMC)0);
    }

    videodata->ime_enabled = false;
}

स्थिर शून्य IME_Quit(SDL_Video_दत्त *videodata)
{
    यदि (!videodata->ime_initialized) {
        प्रत्यागम;
    }

    यदि (videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_main, videodata->ime_himc);
    }

    videodata->ime_hwnd_main = 0;
    videodata->ime_himc = 0;
    यदि (videodata->ime_himm32) {
        SDL_UnloadObject(videodata->ime_himm32);
        videodata->ime_himm32 = 0;
    }
    प्रति (पूर्णाङ्क i = 0; i < videodata->ime_candcount; ++i) {
        SDL_free(videodata->ime_candidates[i]);
        videodata->ime_candidates[i] = रिक्त;
    }
    videodata->ime_initialized = false;
}

स्थिर शून्य IME_GetReadingString(SDL_Video_दत्त *videodata, HWND hwnd)
{
    DWORD id = 0;
    HIMC himc = 0;
    WCHAR बफर_2[16];
    WCHAR *s = बफर_2;
    DWORD len = 0;
    INT err = 0;
    BOOL vertical = FALSE;
    UINT maxuilen = 0;

    videodata->ime_readingstring[0] = 0;

    id = IME_GetId(videodata, 0);
    यदि (!id) {
        प्रत्यागम;
    }

    himc = ImmGetContext(hwnd);
    यदि (!himc) {
        प्रत्यागम;
    }

    यदि (videodata->GetReadingString) {
        len = videodata->GetReadingString(himc, 0, 0, &err, &vertical, &maxuilen);
        यदि (len) {
            यदि (len > SDL_arraysize(बफर_2)) {
                len = SDL_arraysize(बफर_2);
            }

            len = videodata->GetReadingString(himc, len, s, &err, &vertical, &maxuilen);
        }
        SDL_wcslcpy(videodata->ime_readingstring, s, len);
    } अन्यथा {
        LPINPUTCONTEXT2 lpimc = videodata->Imm_तालकम्_IMC(himc);
        LPBYTE p = 0;
        s = 0;
        विकल्प (id) {
        पक्ष IMEID_CHT_VER42:
        पक्ष IMEID_CHT_VER43:
        पक्ष IMEID_CHT_VER44:
            p = *(LPBYTE *)((LPBYTE)videodata->Imm_तालकम्_IMCC(lpimc->h_वैयक्तिकम्) + 24);
            यदि (!p) {
                भङ्ग;
            }

            len = *(DWORD *)(p + 7 * 4 + 32 * 4);
            s = (WCHAR *)(p + 56);
            भङ्ग;
        पक्ष IMEID_CHT_VER51:
        पक्ष IMEID_CHT_VER52:
        पक्ष IMEID_CHS_VER53:
            p = *(LPBYTE *)((LPBYTE)videodata->Imm_तालकम्_IMCC(lpimc->h_वैयक्तिकम्) + 4);
            यदि (!p) {
                भङ्ग;
            }

            p = *(LPBYTE *)(p + 1 * 4 + 5 * 4);
            यदि (!p) {
                भङ्ग;
            }

            len = *(DWORD *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4 + 16 * 2);
            s = (WCHAR *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4);
            भङ्ग;
        पक्ष IMEID_CHS_VER41:
        {
            पूर्णाङ्क विस्थापनम्_2 = (IME_GetId(videodata, 1) >= 0x00000002) ? 8 : 7;
            p = *(LPBYTE *)((LPBYTE)videodata->Imm_तालकम्_IMCC(lpimc->h_वैयक्तिकम्) + विस्थापनम्_2 * 4);
            यदि (!p) {
                भङ्ग;
            }

            len = *(DWORD *)(p + 7 * 4 + 16 * 2 * 4);
            s = (WCHAR *)(p + 6 * 4 + 16 * 2 * 1);
        } भङ्ग;
        पक्ष IMEID_CHS_VER42:
            p = *(LPBYTE *)((LPBYTE)videodata->Imm_तालकम्_IMCC(lpimc->h_वैयक्तिकम्) + 1 * 4 + 1 * 4 + 6 * 4);
            यदि (!p) {
                भङ्ग;
            }

            len = *(DWORD *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4 + 16 * 2);
            s = (WCHAR *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4);
            भङ्ग;
        }
        यदि (s) {
            size_t आकार = SDL_min((size_t)(len + 1), SDL_arraysize(videodata->ime_readingstring));
            SDL_wcslcpy(videodata->ime_readingstring, s, आकार);
        }

        videodata->ImmUnlockIMCC(lpimc->h_वैयक्तिकम्);
        videodata->ImmUnlockIMC(himc);
    }
    ImmReleaseContext(hwnd, himc);
    IME_SendEditingEvent(videodata);
}

स्थिर शून्य IME_निवेशः_Lang_परिवर्तितम्(SDL_Video_दत्त *videodata)
{
    UINT lang = PRIMLANG();
    IME_Update_निवेशः_Locale(videodata);

    IME_सज्जता_API(videodata);
    यदि (lang != PRIMLANG()) {
        IME_ClearComposition(videodata);
    }
}

स्थिर DWORD IME_GetId(SDL_Video_दत्त *videodata, UINT u_सूचकांक)
{
    स्थिर HKL hklprev = 0;
    स्थिर DWORD dwRet[2] = { 0 };
    DWORD dw_Ver_आकार = 0;
    LPVOID lp_Ver_बफर = 0;
    LPVOID lp_Ver_दत्त = 0;
    UINT cb_Ver_दत्त = 0;
    वर्ण sz_अस्थायी[256];
    HKL hkl = 0;
    DWORD dwLang = 0;
    SDL_assert(u_सूचकांक < SDL_arraysize(dwRet));

    hkl = videodata->ime_hkl;
    यदि (hklprev == hkl) {
        प्रत्यागम dwRet[u_सूचकांक];
    }
    hklprev = hkl;

    SDL_assert(u_सूचकांक == 0);
    dwLang = ((DWORD_PTR)hkl & 0xffff);
    // FIXME: What does this do?
    यदि (videodata->ime_आन्तरिकम्_candidates && dwLang == LANG_CHT) {
        dwRet[0] = IMEID_CHT_VER_VISTA;
        dwRet[1] = 0;
        प्रत्यागम dwRet[0];
    }
    यदि (hkl != CHT_HKL_NEW_PHONETIC && hkl != CHT_HKL_NEW_CHANG_JIE && hkl != CHT_HKL_NEW_शीघ्र && hkl != CHT_HKL_HK_CANTONESE && hkl != CHS_HKL) {
        dwRet[0] = dwRet[1] = 0;
        प्रत्यागम dwRet[0];
    }
    यदि (!ImmGetIMEFileNameA(hkl, sz_अस्थायी, परिमाण(sz_अस्थायी) - 1)) {
        dwRet[0] = dwRet[1] = 0;
        प्रत्यागम dwRet[0];
    }
    यदि (!videodata->GetReadingString) {
#परिभाषय LCID_INVARIANT MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), क्रमय_DEFAULT)
        यदि (CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_अस्थायी, -1, CHT_IMEFILENAME1, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_अस्थायी, -1, CHT_IMEFILENAME2, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_अस्थायी, -1, CHT_IMEFILENAME3, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_अस्थायी, -1, CHS_IMEFILENAME1, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_अस्थायी, -1, CHS_IMEFILENAME2, -1) != 2) {
            dwRet[0] = dwRet[1] = 0;
            प्रत्यागम dwRet[0];
        }
#अपरिभाषय LCID_INVARIANT
        dw_Ver_आकार = Get_File_संस्करणम्_Info_आकार_A(sz_अस्थायी, रिक्त);
        यदि (dw_Ver_आकार) {
            lp_Ver_बफर = SDL_malloc(dw_Ver_आकार);
            यदि (lp_Ver_बफर) {
                यदि (Get_File_संस्करणम्_Info_A(sz_अस्थायी, 0, dw_Ver_आकार, lp_Ver_बफर)) {
                    यदि (Ver_Query_मानम्_A(lp_Ver_बफर, "\\", &lp_Ver_दत्त, &cb_Ver_दत्त)) {
#परिभाषय pVerFixedInfo ((VS_FIXEDFILEINFO FAR *)lp_Ver_दत्त)
                        DWORD dwVer = pVerFixedInfo->dw_File_संस्करणम्_MS;
                        dwVer = (dwVer & 0x00ff0000) << 8 | (dwVer & 0x000000ff) << 16;
                        यदि ((videodata->GetReadingString) ||
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
                            dwRet[1] = pVerFixedInfo->dw_File_संस्करणम्_LS;
                            SDL_free(lp_Ver_बफर);
                            प्रत्यागम dwRet[0];
                        }
#अपरिभाषय pVerFixedInfo
                    }
                }
            }
            SDL_free(lp_Ver_बफर);
        }
    }
    dwRet[0] = dwRet[1] = 0;
    प्रत्यागम dwRet[0];
}

स्थिर शून्य IME_सज्जता_API(SDL_Video_दत्त *videodata)
{
    वर्ण ime_file[MAX_मार्गः + 1];
    SDL_SharedObject *hime = 0;
    HKL hkl = 0;
    videodata->GetReadingString = रिक्त;
    videodata->Show_Reading_गवाक्षः = रिक्त;

    hkl = videodata->ime_hkl;
    यदि (!ImmGetIMEFileNameA(hkl, ime_file, परिमाण(ime_file) - 1)) {
        प्रत्यागम;
    }

    hime = SDL_आरोपय_Object(ime_file);
    यदि (!hime) {
        प्रत्यागम;
    }

    /* *INDENT-OFF* */ // clang-format off
    videodata->GetReadingString = (UINT (WINAPI *)(HIMC, UINT, LPWSTR, PINT, BOOL*, PUINT))
        SDL_आरोपय_Function(hime, "GetReadingString");
    videodata->Show_Reading_गवाक्षः = (BOOL (WINAPI *)(HIMC, BOOL))
        SDL_आरोपय_Function(hime, "ShowReadingWindow");
    /* *INDENT-ON* */ // clang-format on

    यदि (videodata->Show_Reading_गवाक्षः) {
        HIMC himc = ImmGetContext(videodata->ime_hwnd_current);
        यदि (himc) {
            videodata->Show_Reading_गवाक्षः(himc, FALSE);
            ImmReleaseContext(videodata->ime_hwnd_current, himc);
        }
    }
}

स्थिर शून्य IME_समुच्चयः_गवाक्षः(SDL_Video_दत्त *videodata, SDL_गवाक्षः *गवाक्षः)
{
    HWND hwnd = गवाक्षः->आन्तरिकम्->hwnd;

    यदि (hwnd != videodata->ime_hwnd_current) {
        videodata->ime_hwnd_current = hwnd;
        SDL_zero(videodata->ime_composition_area);
        SDL_zero(videodata->ime_candidate_area);
    }

    IME_समुच्चयः_Text_निवेशः_Area(videodata, hwnd, &गवाक्षः->text_निवेशः_rect, गवाक्षः->text_निवेशः_cursor);
}

#यदि_अन्तः

स्थिर शून्य IME_समुच्चयः_Text_निवेशः_Area(SDL_Video_दत्त *videodata, HWND hwnd, ध्रुव SDL_Rect *rect, पूर्णाङ्क cursor)
{
    HIMC himc;

    himc = ImmGetContext(hwnd);
    यदि (himc) {
        COMPOSITIONFORM cof;
        CANDIDATEFORM caf;
        पूर्णाङ्क font_height = rect->h;

        LOGFONTW font;
        यदि (ImmGetCompositionFontW(himc, &font)) {
            font_height = font.lfHeight;
        }

        SDL_zero(cof);
        cof.dwStyle = CFS_RECT;
        cof.ptCurrentPos.x = rect->x + cursor;
        cof.ptCurrentPos.y = rect->y + (rect->h - font_height) / 2;
        cof.rcArea.वामः = rect->x;
        cof.rcArea.दक्षिणः = (LONG)rect->x + rect->w;
        cof.rcArea.शिखरम् = rect->y;
        cof.rcArea.bottom = (LONG)rect->y + rect->h;
        यदि (SDL_memcmp(&cof, &videodata->ime_composition_area, परिमाण(cof)) != 0) {
            SDL_copyp(&videodata->ime_composition_area, &cof);
            Imm_समुच्चयः_Composition_गवाक्षः(himc, &cof);
        }

        SDL_zero(caf);
        caf.dw_सूचकांक = 0;
        caf.dwStyle = CFS_EXCLUDE;
        caf.ptCurrentPos.x = rect->x + cursor;
        caf.ptCurrentPos.y = rect->y;
        caf.rcArea.वामः = rect->x;
        caf.rcArea.दक्षिणः = (LONG)rect->x + rect->w;
        caf.rcArea.शिखरम् = rect->y;
        caf.rcArea.bottom = (LONG)rect->y + rect->h;
        यदि (SDL_memcmp(&caf, &videodata->ime_candidate_area, परिमाण(caf)) != 0) {
            SDL_copyp(&videodata->ime_candidate_area, &caf);
            Imm_समुच्चयः_Candidate_गवाक्षः(himc, &caf);
        }

        ImmReleaseContext(hwnd, himc);
    }
}

#यदि_अपरिभाषितम् SDL_DISABLE_WINDOWS_IME

स्थिर शून्य IME_Update_निवेशः_Locale(SDL_Video_दत्त *videodata)
{
    HKL hklnext = GetKeyboardLayout(0);

    यदि (hklnext == videodata->ime_hkl) {
        प्रत्यागम;
    }

    videodata->ime_hkl = hklnext;
    videodata->ime_horizontal_candidates = (PRIMLANG() == LANG_KOREAN || LANG() == LANG_CHS);
    videodata->ime_candlistindexbase = (videodata->ime_hkl == CHT_HKL_DAYI) ? 0 : 1;
}

स्थिर शून्य IME_ClearComposition(SDL_Video_दत्त *videodata)
{
    HIMC himc = 0;
    यदि (!videodata->ime_initialized) {
        प्रत्यागम;
    }

    himc = ImmGetContext(videodata->ime_hwnd_current);
    यदि (!himc) {
        प्रत्यागम;
    }

    ImmNotifyIME(himc, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
    Imm_समुच्चयः_Composition_String(himc, SCS_SETSTR, TEXT(""), परिमाण(TCHAR), TEXT(""), परिमाण(TCHAR));

    ImmNotifyIME(himc, NI_CLOSECANDIDATE, 0, 0);
    ImmReleaseContext(videodata->ime_hwnd_current, himc);
    IME_SendClearComposition(videodata);
}

स्थिर शून्य IME_GetCompositionString(SDL_Video_दत्त *videodata, HIMC himc, LPARAM *lParam, DWORD string)
{
    LONG दीर्घता;
    DWORD dwLang = ((DWORD_PTR)videodata->ime_hkl & 0xffff);

    यदि (*lParam & GCS_CURSORPOS) {
        videodata->ime_cursor = LOWORD(ImmGetCompositionStringW(himc, GCS_CURSORPOS, 0, 0));
    }
    videodata->ime_selected_start = 0;
    videodata->ime_selected_दीर्घता = 0;
    SDL_DebugIMELog("Cursor = %d", videodata->ime_cursor);

    दीर्घता = ImmGetCompositionStringW(himc, string, रिक्त, 0);
    यदि (दीर्घता > 0 && videodata->ime_composition_दीर्घता < दीर्घता) {
        SDL_free(videodata->ime_composition);

        videodata->ime_composition = (WCHAR *)SDL_malloc(दीर्घता + परिमाण(WCHAR));
        videodata->ime_composition_दीर्घता = दीर्घता;
    }

    दीर्घता = ImmGetCompositionStringW(himc, string, videodata->ime_composition, videodata->ime_composition_दीर्घता);
    यदि (दीर्घता < 0) {
        दीर्घता = 0;
    }
    दीर्घता /= परिमाण(WCHAR);

    यदि (!(*lParam & GCS_CURSORPOS)) {
        // If the IME doesn't support GCS_CURSORPOS, default the cursor to the end of the composition.
        videodata->ime_cursor = दीर्घता;
    }

    यदि ((dwLang == LANG_CHT || dwLang == LANG_CHS) &&
        videodata->ime_cursor > 0 &&
        videodata->ime_cursor < (पूर्णाङ्क)(videodata->ime_composition_दीर्घता / परिमाण(WCHAR)) &&
        (videodata->ime_composition[0] == 0x3000 || videodata->ime_composition[0] == 0x0020)) {
        // Traditional Chinese IMEs add a placeholder U+3000
        // Simplified Chinese IMEs seem to add a placeholder U+0020 sometimes
        प्रति (पूर्णाङ्क i = videodata->ime_cursor + 1; i < दीर्घता; ++i) {
            videodata->ime_composition[i - 1] = videodata->ime_composition[i];
        }
        --दीर्घता;
    }

    videodata->ime_composition[दीर्घता] = 0;

    दीर्घता = ImmGetCompositionStringW(himc, GCS_COMPATTR, रिक्त, 0);
    यदि (दीर्घता > 0) {
        Uint8 *गुणाः = (Uint8 *)SDL_malloc(दीर्घता);
        यदि (गुणाः) {
            पूर्णाङ्क start = 0;
            पूर्णाङ्क अन्तः = 0;

            दीर्घता = ImmGetCompositionString(himc, GCS_COMPATTR, गुणाः, दीर्घता);
            यदि (दीर्घता < 0) {
                दीर्घता = 0;
            }

            प्रति (LONG i = 0; i < दीर्घता; ++i) {
                SDL_DebugIMELog("attrib[%d] = %d", i, गुणाः[i]);
            }

            प्रति (start = 0; start < दीर्घता; ++start) {
                यदि (गुणाः[start] == ATTR_TARGET_CONVERTED || गुणाः[start] == ATTR_TARGET_NOTCONVERTED) {
                    भङ्ग;
                }
            }

            प्रति (अन्तः = start; अन्तः < दीर्घता; ++अन्तः) {
                यदि (गुणाः[अन्तः] != ATTR_TARGET_CONVERTED && गुणाः[अन्तः] != ATTR_TARGET_NOTCONVERTED) {
                    भङ्ग;
                }
            }

            यदि (अन्तः > start) {
                videodata->ime_selected_start = start;
                videodata->ime_selected_दीर्घता = अन्तः - start;
            }

            SDL_free(गुणाः);
        }
    }
}

स्थिर शून्य IME_Send_निवेशः_Event(SDL_Video_दत्त *videodata)
{
    वर्ण *s = 0;
    s = WIN_String_गन्तव्यम्_UTF8_W(videodata->ime_composition);
    SDL_SendKeyboardText(s);
    SDL_free(s);

    videodata->ime_composition[0] = 0;
    videodata->ime_readingstring[0] = 0;
    videodata->ime_cursor = 0;
}

स्थिर शून्य IME_SendEditingEvent(SDL_Video_दत्त *videodata)
{
    वर्ण *s = रिक्त;
    WCHAR *बफर_2 = रिक्त;
    size_t आकार = videodata->ime_composition_दीर्घता;
    यदि (videodata->ime_readingstring[0]) {
        size_t len = SDL_min(SDL_wcslen(videodata->ime_composition), (size_t)videodata->ime_cursor);

        आकार += परिमाण(videodata->ime_readingstring);
        बफर_2 = (WCHAR *)SDL_malloc(आकार + परिमाण(WCHAR));
        यदि (!बफर_2) {
            प्रत्यागम;
        }
        बफर_2[0] = 0;

        SDL_wcslcpy(बफर_2, videodata->ime_composition, len + 1);
        SDL_wcslcat(बफर_2, videodata->ime_readingstring, आकार);
        SDL_wcslcat(बफर_2, &videodata->ime_composition[len], आकार);
    } अन्यथा {
        बफर_2 = (WCHAR *)SDL_malloc(आकार + परिमाण(WCHAR));
        यदि (!बफर_2) {
            प्रत्यागम;
        }
        बफर_2[0] = 0;
        SDL_wcslcpy(बफर_2, videodata->ime_composition, आकार);
    }

    s = WIN_String_गन्तव्यम्_UTF8_W(बफर_2);
    यदि (s) {
        यदि (videodata->ime_readingstring[0]) {
            SDL_SendEditingText(s, videodata->ime_cursor, (पूर्णाङ्क)SDL_wcslen(videodata->ime_readingstring));
        } अन्यथा यदि (videodata->ime_cursor == videodata->ime_selected_start) {
            SDL_SendEditingText(s, videodata->ime_selected_start, videodata->ime_selected_दीर्घता);
        } अन्यथा {
            SDL_SendEditingText(s, videodata->ime_cursor, 0);
        }
        यदि (*s) {
            videodata->ime_needs_clear_composition = true;
        }
        SDL_free(s);
    }
    SDL_free(बफर_2);
}

स्थिर शून्य IME_SendClearComposition(SDL_Video_दत्त *videodata)
{
    यदि (videodata->ime_needs_clear_composition) {
        SDL_SendEditingText("", 0, 0);
        videodata->ime_needs_clear_composition = false;
    }
}

स्थिर bool IME_OpenCandidateList(SDL_Video_दत्त *videodata)
{
    videodata->ime_candidates_open = true;
    videodata->ime_candcount = 0;
    प्रत्यागम true;
}

स्थिर शून्य IME_सङ्कलय_Candidate(SDL_Video_दत्त *videodata, UINT i, LPCWSTR candidate)
{
    यदि (videodata->ime_candidates[i]) {
        SDL_free(videodata->ime_candidates[i]);
        videodata->ime_candidates[i] = रिक्त;
    }

    SDL_COMPILE_TIME_ASSERT(IME_CANDIDATE_INDEXING_REQUIRES, MAX_CANDLIST == 10);
    वर्ण *candidate_utf8 = WIN_String_गन्तव्यम्_UTF8_W(candidate);
    SDL_asprintf(&videodata->ime_candidates[i], "%d %s", ((i + videodata->ime_candlistindexbase) % 10), candidate_utf8);
    SDL_free(candidate_utf8);

    videodata->ime_candcount = (i + 1);
}

स्थिर शून्य IME_SendCandidateList(SDL_Video_दत्त *videodata)
{
    SDL_SendEditingTextCandidates(videodata->ime_candidates, videodata->ime_candcount, videodata->ime_candsel, videodata->ime_horizontal_candidates);
}

स्थिर शून्य IME_CloseCandidateList(SDL_Video_दत्त *videodata)
{
    videodata->ime_candidates_open = false;

    यदि (videodata->ime_candcount > 0) {
        प्रति (पूर्णाङ्क i = 0; i < videodata->ime_candcount; ++i) {
            SDL_free(videodata->ime_candidates[i]);
            videodata->ime_candidates[i] = रिक्त;
        }
        videodata->ime_candcount = 0;

        SDL_SendEditingTextCandidates(रिक्त, 0, -1, false);
    }
}

स्थिर शून्य IME_GetCandidateList(SDL_Video_दत्त *videodata, HWND hwnd)
{
    HIMC himc;
    DWORD आकार;
    LPCANDIDATELIST cand_list;
    bool has_candidates = false;

    himc = ImmGetContext(hwnd);
    यदि (himc) {
        आकार = ImmGetCandidateListW(himc, 0, रिक्त, 0);
        यदि (आकार != 0) {
            cand_list = (LPCANDIDATELIST)SDL_malloc(आकार);
            यदि (cand_list != रिक्त) {
                आकार = ImmGetCandidateListW(himc, 0, cand_list, आकार);
                यदि (आकार != 0) {
                    यदि (IME_OpenCandidateList(videodata)) {
                        UINT i, j;
                        UINT page_start = 0;
                        UINT page_आकार = 0;

                        videodata->ime_candsel = cand_list->dwSelection;

                        यदि (LANG() == LANG_CHS && IME_GetId(videodata, 0)) {
                            ध्रुव UINT maxcandchar = 18;
                            size_t cchars = 0;

                            प्रति (i = 0; i < cand_list->dw_गणनम्; ++i) {
                                size_t len = SDL_wcslen((LPWSTR)((DWORD_PTR)cand_list + cand_list->dw_विस्थापनम्[i])) + 1;
                                यदि (len + cchars > maxcandchar) {
                                    यदि (i > cand_list->dwSelection) {
                                        भङ्ग;
                                    }

                                    page_start = i;
                                    cchars = len;
                                } अन्यथा {
                                    cchars += len;
                                }
                            }
                            page_आकार = i - page_start;
                        } अन्यथा {
                            page_आकार = SDL_min(cand_list->dw_Page_आकार == 0 ? MAX_CANDLIST : cand_list->dw_Page_आकार, MAX_CANDLIST);
                            page_start = (cand_list->dwSelection / page_आकार) * page_आकार;
                        }
                        प्रति (i = page_start, j = 0; (DWORD)i < cand_list->dw_गणनम् && j < page_आकार; i++, j++) {
                            LPCWSTR candidate = (LPCWSTR)((DWORD_PTR)cand_list + cand_list->dw_विस्थापनम्[i]);
                            IME_सङ्कलय_Candidate(videodata, j, candidate);
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

    यदि (!has_candidates) {
        IME_CloseCandidateList(videodata);
    }
}

bool WIN_HandleIMEMessage(HWND hwnd, UINT सन्देशः_2, WPARAM wParam, LPARAM *lParam, SDL_Video_दत्त *videodata)
{
    bool trap = false;
    HIMC himc = 0;

    यदि (सन्देशः_2 == WM_IME_SETCONTEXT) {
        SDL_DebugIMELog("WM_IME_SETCONTEXT");

        LPARAM element_आवरणम्;
        element_आवरणम् = ISC_SHOWUIALL;
        यदि (videodata->ime_आन्तरिकम्_composition) {
            element_आवरणम् &= ~ISC_SHOWUICOMPOSITIONWINDOW;
        }
        यदि (videodata->ime_आन्तरिकम्_candidates) {
            element_आवरणम् &= ~ISC_SHOWUIALLCANDIDATEWINDOW;
        }
        *lParam &= element_आवरणम्;

        प्रत्यागम false;
    } अन्यथा यदि (सन्देशः_2 == WM_IME_STARTCOMPOSITION) {
        SDL_DebugIMELog("WM_IME_STARTCOMPOSITION");
        यदि (videodata->ime_आन्तरिकम्_composition) {
            videodata->ime_cursor = 0;
            // Windows may still display a composition dialog even with
            // ISC_SHOWUICOMPOSITIONWINDOW cleared, so trap the message
            // here to prevent that (even when the IME is disabled).
            प्रत्यागम true;
        }
    }

    यदि (!videodata->ime_initialized || !videodata->ime_उपलब्धम् || !videodata->ime_enabled) {
        प्रत्यागम false;
    }

    विकल्प (सन्देशः_2) {
    पक्ष WM_KEYDOWN:
        यदि (wParam == VK_PROCESSKEY) {
            SDL_DebugIMELog("WM_KEYDOWN VK_PROCESSKEY");
            trap = true;
        } अन्यथा {
            SDL_DebugIMELog("WM_KEYDOWN normal");
        }
        भङ्ग;
    पक्ष WM_SYSKEYDOWN:
        यदि (wParam == VK_PROCESSKEY) {
            SDL_DebugIMELog("WM_SYSKEYDOWN VK_PROCESSKEY");
            trap = true;
        } अन्यथा {
            SDL_DebugIMELog("WM_SYSKEYDOWN normal");
        }
        भङ्ग;
    पक्ष WM_INPUTLANGCHANGE:
        SDL_DebugIMELog("WM_INPUTLANGCHANGE");
        IME_निवेशः_Lang_परिवर्तितम्(videodata);
        भङ्ग;
    पक्ष WM_IME_COMPOSITION:
        SDL_DebugIMELog("WM_IME_COMPOSITION %x", lParam);
        यदि (videodata->ime_आन्तरिकम्_composition) {
            trap = true;
            himc = ImmGetContext(hwnd);
            यदि (*lParam & GCS_RESULTSTR) {
                SDL_DebugIMELog("GCS_RESULTSTR");
                IME_GetCompositionString(videodata, himc, lParam, GCS_RESULTSTR);
                IME_SendClearComposition(videodata);
                IME_Send_निवेशः_Event(videodata);
            }
            यदि (*lParam & GCS_COMPSTR) {
                SDL_DebugIMELog("GCS_COMPSTR");
                videodata->ime_readingstring[0] = 0;
                IME_GetCompositionString(videodata, himc, lParam, GCS_COMPSTR);
                IME_SendEditingEvent(videodata);
            }
            ImmReleaseContext(hwnd, himc);
        }
        भङ्ग;
    पक्ष WM_IME_ENDCOMPOSITION:
        SDL_DebugIMELog("WM_IME_ENDCOMPOSITION");
        यदि (videodata->ime_आन्तरिकम्_composition) {
            trap = true;
            videodata->ime_composition[0] = 0;
            videodata->ime_readingstring[0] = 0;
            videodata->ime_cursor = 0;
            videodata->ime_selected_start = 0;
            videodata->ime_selected_दीर्घता = 0;
            IME_SendClearComposition(videodata);
        }
        भङ्ग;
    पक्ष WM_IME_NOTIFY:
        SDL_DebugIMELog("WM_IME_NOTIFY %x", wParam);
        विकल्प (wParam) {
        पक्ष IMN_SETCOMPOSITIONWINDOW:
            SDL_DebugIMELog("IMN_SETCOMPOSITIONWINDOW");
            भङ्ग;
        पक्ष IMN_SETCOMPOSITIONFONT:
            SDL_DebugIMELog("IMN_SETCOMPOSITIONFONT");
            भङ्ग;
        पक्ष IMN_SETCANDIDATEPOS:
            SDL_DebugIMELog("IMN_SETCANDIDATEPOS");
            भङ्ग;
        पक्ष IMN_SETCONVERSIONMODE:
        पक्ष IMN_SETOPENSTATUS:
            SDL_DebugIMELog("%s", wParam == IMN_SETCONVERSIONMODE ? "IMN_SETCONVERSIONMODE" : "IMN_SETOPENSTATUS");
            IME_Update_निवेशः_Locale(videodata);
            भङ्ग;
        पक्ष IMN_OPENCANDIDATE:
        पक्ष IMN_CHANGECANDIDATE:
            SDL_DebugIMELog("%s", wParam == IMN_OPENCANDIDATE ? "IMN_OPENCANDIDATE" : "IMN_CHANGECANDIDATE");
            यदि (videodata->ime_आन्तरिकम्_candidates) {
                trap = true;
                videodata->ime_update_candidates = true;
            }
            भङ्ग;
        पक्ष IMN_CLOSECANDIDATE:
            SDL_DebugIMELog("IMN_CLOSECANDIDATE");
            यदि (videodata->ime_आन्तरिकम्_candidates) {
                trap = true;
                videodata->ime_update_candidates = false;
                IME_CloseCandidateList(videodata);
            }
            भङ्ग;
        पक्ष IMN_वैयक्तिकम्:
        {
            DWORD dwId = IME_GetId(videodata, 0);
            SDL_DebugIMELog("IMN_PRIVATE %u", dwId);
            IME_GetReadingString(videodata, hwnd);
            विकल्प (dwId) {
            पक्ष IMEID_CHT_VER42:
            पक्ष IMEID_CHT_VER43:
            पक्ष IMEID_CHT_VER44:
            पक्ष IMEID_CHS_VER41:
            पक्ष IMEID_CHS_VER42:
                यदि (*lParam == 1 || *lParam == 2) {
                    trap = true;
                }

                भङ्ग;
            पक्ष IMEID_CHT_VER50:
            पक्ष IMEID_CHT_VER51:
            पक्ष IMEID_CHT_VER52:
            पक्ष IMEID_CHT_VER60:
            पक्ष IMEID_CHS_VER53:
                यदि (*lParam == 16 || *lParam == 17 || *lParam == 26 || *lParam == 27 || *lParam == 28) {
                    trap = true;
                }
                भङ्ग;
            }
        } भङ्ग;
        स्वभाव:
            trap = true;
            भङ्ग;
        }
        भङ्ग;
    }
    प्रत्यागम trap;
}

शून्य WIN_UpdateIMECandidates(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;

    यदि (videodata->ime_update_candidates) {
        IME_GetCandidateList(videodata, videodata->ime_hwnd_current);
        videodata->ime_update_candidates = false;
    }
}

#यदि_अन्तः // SDL_DISABLE_WINDOWS_IME

#यदि_अन्तः // SDL_VIDEO_DRIVER_WINDOWS
