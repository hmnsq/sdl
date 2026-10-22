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

#समावेश "../../events/SDL_keyboard_c.h"
#समावेश "../../events/scancodes_windows.h"

#समावेश <imm.h>
#समावेश <oleauto.h>

#अगर_अघोषित SDL_DISABLE_WINDOWS_IME
#अगर 0
#घोषणा SDL_DebugIMELog SDL_Log
#अन्यथा
#घोषणा SDL_DebugIMELog(...)
#पूर्ण_अगर
अटल bool IME_Init(SDL_Video_तथ्य *videodata, SDL_Window *window);
अटल व्योम IME_Enable(SDL_Video_तथ्य *videodata, HWND hwnd);
अटल व्योम IME_Disable(SDL_Video_तथ्य *videodata, HWND hwnd);
अटल व्योम IME_Set_Text_निवेश_Area(SDL_Video_तथ्य *videodata, HWND hwnd, स्थिर SDL_Rect *rect, पूर्णांक cursor);
अटल व्योम IME_ClearComposition(SDL_Video_तथ्य *videodata);
अटल व्योम IME_GetCandidateList(SDL_Video_तथ्य *videodata, HWND hwnd);
अटल व्योम IME_Quit(SDL_Video_तथ्य *videodata);
#अन्यथा
अटल व्योम IME_Set_Text_निवेश_Area(SDL_Video_तथ्य *videodata, HWND hwnd, स्थिर SDL_Rect *rect, पूर्णांक cursor);
#पूर्ण_अगर // !SDL_DISABLE_WINDOWS_IME

#अगर_अघोषित MAPVK_VK_TO_VSC
#घोषणा MAPVK_VK_TO_VSC 0
#पूर्ण_अगर
#अगर_अघोषित MAPVK_VSC_TO_VK
#घोषणा MAPVK_VSC_TO_VK 1
#पूर्ण_अगर

/* Building keymaps is expensive, so keep a reasonably-sized LRU cache to
 * enable fast switching between commonly used ones.
 */
अटल काष्ठा WIN_KeymapCache
{
    HKL keyboard_layout;
    SDL_Keymap *keymap;
} keymap_cache[4];

अटल पूर्णांक keymap_cache_आकार;

अटल SDL_Keymap *WIN_GetCachedKeymap(HKL layout)
{
    SDL_Keymap *keymap = शून्य;
    क्रम (पूर्णांक i = 0; i < keymap_cache_आकार; ++i) {
        अगर (keymap_cache[i].keyboard_layout == layout) {
            keymap = keymap_cache[i].keymap;

            // Move the map to the front of the list.
            अगर (i) {
                SDL_memmove(keymap_cache + 1, keymap_cache, माप(काष्ठा WIN_KeymapCache) * i);
                keymap_cache[0].keyboard_layout = layout;
                keymap_cache[0].keymap = keymap;
            }
            अवरोध;
        }
    }
    वापस keymap;
}

अटल व्योम WIN_CacheKeymap(HKL layout, SDL_Keymap *keymap)
{
    // If the cache is full, evict the last keymap.
    अगर (keymap_cache_आकार == SDL_arraysize(keymap_cache)) {
        SDL_DestroyKeymap(keymap_cache[--keymap_cache_आकार].keymap);
    }

    // Move all elements down by one.
    अगर (keymap_cache_आकार) {
        SDL_memmove(keymap_cache + 1, keymap_cache, माप(काष्ठा WIN_KeymapCache) * keymap_cache_आकार);
    }

    keymap_cache[0].keyboard_layout = layout;
    keymap_cache[0].keymap = keymap;
    ++keymap_cache_आकार;
}

अटल SDL_Keymap *WIN_BuildKeymap(व्योम)
{
    SDL_Scancode scancode;
    BYTE keyboardState[256] = { 0 };
    WCHAR बफर_2[16];
    स्थिर SDL_Keymod mods[] = {
        SDL_KMOD_NONE,
        SDL_KMOD_SHIFT,
        SDL_KMOD_CAPS,
        (SDL_KMOD_SHIFT | SDL_KMOD_CAPS),
        SDL_KMOD_MODE,
        (SDL_KMOD_MODE | SDL_KMOD_SHIFT),
        (SDL_KMOD_MODE | SDL_KMOD_CAPS),
        (SDL_KMOD_MODE | SDL_KMOD_SHIFT | SDL_KMOD_CAPS)
    };

    WIN_Reset_Dead_कुंजियाँ();

    SDL_Keymap *keymap = SDL_CreateKeymap(false);
    अगर (!keymap) {
        वापस शून्य;
    }

    क्रम (पूर्णांक m = 0; m < SDL_arraysize(mods); ++m) {
        क्रम (पूर्णांक i = 0; i < SDL_arraysize(windows_scancode_table); i++) {
            पूर्णांक vk, sc, परिणाम;
            Uint32 *ch = 0;

            // Make sure this scancode is a valid character scancode
            scancode = windows_scancode_table[i];
            अगर (scancode == SDL_SCANCODE_UNKNOWN ||
                scancode == SDL_SCANCODE_DELETE ||
                (SDL_GetKeymapKeycode(शून्य, scancode, SDL_KMOD_NONE) & SDLK_SCANCODE_MASK)) {

                // The Colemak mapping swaps Backspace and CapsLock
                अगर (mods[m] == SDL_KMOD_NONE &&
                    (scancode == SDL_SCANCODE_CAPSLOCK ||
                     scancode == SDL_SCANCODE_BACKSPACE)) {
                    vk = LOBYTE(Map_Virtual_कुंजी(i, MAPVK_VSC_TO_VK));
                    अगर (vk == VK_CAPITAL) {
                        SDL_SetKeymapEntry(keymap, scancode, mods[m], SDLK_CAPSLOCK);
                    } अन्यथा अगर (vk == VK_BACK) {
                        SDL_SetKeymapEntry(keymap, scancode, mods[m], SDLK_BACKSPACE);
                    }
                }
                जारी;
            }

            // Unpack the single byte index to make the scan code.
            sc = MAKEWORD(i & 0x7f, (i & 0x80) ? 0xe0 : 0x00);
            vk = LOBYTE(Map_Virtual_कुंजी(sc, MAPVK_VSC_TO_VK));
            अगर (!vk) {
                जारी;
            }

            // Update the keyboard state for the modifiers
            keyboardState[VK_SHIFT] = (mods[m] & SDL_KMOD_SHIFT) ? 0x80 : 0x00;
            keyboardState[VK_CAPITAL] = (mods[m] & SDL_KMOD_CAPS) ? 0x01 : 0x00;
            keyboardState[VK_CONTROL] = (mods[m] & SDL_KMOD_MODE) ? 0x80 : 0x00;
            keyboardState[VK_MENU] = (mods[m] & SDL_KMOD_MODE) ? 0x80 : 0x00;

            परिणाम = ToUnicode(vk, sc, keyboardState, बफर_2, 16, 0);
            बफर_2[SDL_abs(परिणाम)] = 0;

            // Convert UTF-16 to UTF-32 code points
            ch = (Uint32 *)SDL_iconv_string("UTF-32LE", "UTF-16LE", (स्थिर अक्षर *)बफर_2, (SDL_abs(परिणाम) + 1) * माप(WCHAR));
            अगर (ch) {
                /* Windows keyboard layouts can emit several UTF-32 code points on a single key press.
                 * Use <U+FFFD REPLACEMENT CHARACTER> since we cannot fit into single SDL_Keycode value in SDL keymap.
                 * See https://kbdlayout.info/features/ligatures for a list of such keys. */
                SDL_SetKeymapEntry(keymap, scancode, mods[m], ch[1] == 0 ? ch[0] : 0xfffd);
                SDL_free(ch);
            } अन्यथा {
                // The default keymap doesn't have any SDL_KMOD_MODE entries, so we don't need to override them
                अगर (!(mods[m] & SDL_KMOD_MODE)) {
                    SDL_SetKeymapEntry(keymap, scancode, mods[m], SDLK_UNKNOWN);
                }
            }

            अगर (परिणाम < 0) {
                WIN_Reset_Dead_कुंजियाँ();
            }
        }
    }

    वापस keymap;
}

व्योम WIN_UpdateKeymap(bool send_event)
{
    HKL layout = GetKeyboardLayout(0);
    SDL_Keymap *keymap = WIN_GetCachedKeymap(layout);
    अगर (!keymap) {
        keymap = WIN_BuildKeymap();
        अगर (keymap) {
            WIN_CacheKeymap(layout, keymap);
        }
    }

    SDL_SetKeymap(keymap, send_event);
}

// Alphabetic scancodes for PC keyboards
व्योम WIN_InitKeyboard(SDL_VideoDevice *_this)
{
#अगर_अघोषित SDL_DISABLE_WINDOWS_IME
    SDL_Video_तथ्य *तथ्य = _this->internal;

    तथ्य->ime_candlistindexbase = 1;
    तथ्य->ime_composition_लंबाई = 32 * माप(WCHAR);
    तथ्य->ime_composition = (WCHAR *)SDL_calloc(तथ्य->ime_composition_लंबाई, माप(WCHAR));
#पूर्ण_अगर // !SDL_DISABLE_WINDOWS_IME

    // Build and bind the current keymap.
    WIN_UpdateKeymap(false);

    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");
    SDL_SetScancodeName(SDL_SCANCODE_LGUI, "Left Windows");
    SDL_SetScancodeName(SDL_SCANCODE_RGUI, "Right Windows");

    // Are system caps/num/scroll lock active? Set our state to match.
    SDL_ToggleModState(SDL_KMOD_CAPS, (Get_कुंजी_State(VK_CAPITAL) & 0x0001) ? true : false);
    SDL_ToggleModState(SDL_KMOD_अंक, (Get_कुंजी_State(VK_NUMLOCK) & 0x0001) ? true : false);
    SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_कुंजी_State(VK_SCROLL) & 0x0001) ? true : false);
}

व्योम WIN_QuitKeyboard(SDL_VideoDevice *_this)
{
#अगर_अघोषित SDL_DISABLE_WINDOWS_IME
    SDL_Video_तथ्य *तथ्य = _this->internal;

    IME_Quit(तथ्य);

    अगर (तथ्य->ime_composition) {
        SDL_free(तथ्य->ime_composition);
        तथ्य->ime_composition = शून्य;
    }
#पूर्ण_अगर // !SDL_DISABLE_WINDOWS_IME

    क्रम (पूर्णांक i = 0; i < keymap_cache_आकार; ++i) {
        SDL_DestroyKeymap(keymap_cache[i].keymap);
    }
    SDL_zeroa(keymap_cache);
    keymap_cache_आकार = 0;
}

व्योम WIN_Reset_Dead_कुंजियाँ(व्योम)
{
    /*
    if a deadkey has been typed, but not the next character (which the deadkey might modify),
    this tries to undo the effect pressing the deadkey.
    see: http://archives.miloush.net/michkap/archive/2006/09/10/748775.html
    */
    BYTE keyboardState[256];
    WCHAR बफर_2[16];
    पूर्णांक vk, sc, परिणाम, i;

    अगर (!GetKeyboardState(keyboardState)) {
        वापस;
    }

    vk = VK_SPACE;
    sc = Map_Virtual_कुंजी(vk, MAPVK_VK_TO_VSC);
    अगर (sc == 0) {
        // the keyboard doesn't have this key
        वापस;
    }

    क्रम (i = 0; i < 5; i++) {
        परिणाम = ToUnicode(vk, sc, keyboardState, बफर_2, 16, 0);
        अगर (परिणाम > 0) {
            // success
            वापस;
        }
    }
}

bool WIN_Start_Text_निवेश(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    WIN_Reset_Dead_कुंजियाँ();

#अगर_अघोषित SDL_DISABLE_WINDOWS_IME
    HWND hwnd = window->internal->hwnd;
    SDL_Video_तथ्य *videodata = _this->internal;
    IME_Init(videodata, window);
    IME_Enable(videodata, hwnd);

    WIN_Update_Text_निवेश_Area(_this, window);
#पूर्ण_अगर // !SDL_DISABLE_WINDOWS_IME

    वापस true;
}

bool WIN_Stop_Text_निवेश(SDL_VideoDevice *_this, SDL_Window *window)
{
    WIN_Reset_Dead_कुंजियाँ();

#अगर_अघोषित SDL_DISABLE_WINDOWS_IME
    HWND hwnd = window->internal->hwnd;
    SDL_Video_तथ्य *videodata = _this->internal;
    IME_Init(videodata, window);
    IME_Disable(videodata, hwnd);
#पूर्ण_अगर // !SDL_DISABLE_WINDOWS_IME

    वापस true;
}

bool WIN_Update_Text_निवेश_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_तथ्य *videodata = _this->internal;
    SDL_Window_तथ्य *तथ्य = window->internal;

    IME_Set_Text_निवेश_Area(videodata, तथ्य->hwnd, &window->text_निवेश_rect, window->text_निवेश_cursor);
    वापस true;
}

bool WIN_ClearComposition(SDL_VideoDevice *_this, SDL_Window *window)
{
#अगर_अघोषित SDL_DISABLE_WINDOWS_IME
    SDL_Video_तथ्य *videodata = _this->internal;

    IME_ClearComposition(videodata);
#पूर्ण_अगर
    वापस true;
}

#अगर_घोषित SDL_DISABLE_WINDOWS_IME

bool WIN_HandleIMEMessage(HWND hwnd, UINT संदेश, WPARAM wParam, LPARAM *lParam, SDL_Video_तथ्य *videodata)
{
    वापस false;
}

व्योम WIN_UpdateIMECandidates(SDL_VideoDevice *_this)
{
    वापस;
}

#अन्यथा

#घोषणा LANG_CHT MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_TRADITIONAL)
#घोषणा LANG_CHS MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED)

#घोषणा MAKEIMEVERSION(major, minor) ((DWORD)(((BYTE)(major) << 24) | ((BYTE)(minor) << 16)))
#घोषणा IMEID_VER(id)                ((id)&0xffff0000)
#घोषणा IMEID_LANG(id)               ((id)&0x0000ffff)

#घोषणा CHT_HKL_DAYI          ((HKL)(UINT_PTR)0xE0060404)
#घोषणा CHT_HKL_NEW_PHONETIC  ((HKL)(UINT_PTR)0xE0080404)
#घोषणा CHT_HKL_NEW_CHANG_JIE ((HKL)(UINT_PTR)0xE0090404)
#घोषणा CHT_HKL_NEW_QUICK     ((HKL)(UINT_PTR)0xE00A0404)
#घोषणा CHT_HKL_HK_CANTONESE  ((HKL)(UINT_PTR)0xE00B0404)
#घोषणा CHT_IMEFILENAME1      "TINTLGNT.IME"
#घोषणा CHT_IMEFILENAME2      "CINTLGNT.IME"
#घोषणा CHT_IMEFILENAME3      "MSTCIPHA.IME"
#घोषणा IMEID_CHT_VER42       (LANG_CHT | MAKEIMEVERSION(4, 2))
#घोषणा IMEID_CHT_VER43       (LANG_CHT | MAKEIMEVERSION(4, 3))
#घोषणा IMEID_CHT_VER44       (LANG_CHT | MAKEIMEVERSION(4, 4))
#घोषणा IMEID_CHT_VER50       (LANG_CHT | MAKEIMEVERSION(5, 0))
#घोषणा IMEID_CHT_VER51       (LANG_CHT | MAKEIMEVERSION(5, 1))
#घोषणा IMEID_CHT_VER52       (LANG_CHT | MAKEIMEVERSION(5, 2))
#घोषणा IMEID_CHT_VER60       (LANG_CHT | MAKEIMEVERSION(6, 0))
#घोषणा IMEID_CHT_VER_VISTA   (LANG_CHT | MAKEIMEVERSION(7, 0))

#घोषणा CHS_HKL          ((HKL)(UINT_PTR)0xE00E0804)
#घोषणा CHS_IMEFILENAME1 "PINTLGNT.IME"
#घोषणा CHS_IMEFILENAME2 "MSSCIPYA.IME"
#घोषणा IMEID_CHS_VER41  (LANG_CHS | MAKEIMEVERSION(4, 1))
#घोषणा IMEID_CHS_VER42  (LANG_CHS | MAKEIMEVERSION(4, 2))
#घोषणा IMEID_CHS_VER53  (LANG_CHS | MAKEIMEVERSION(5, 3))

#घोषणा LANG()         LOWORD((videodata->ime_hkl))
#घोषणा PRIMLANG()     ((WORD)PRIMARYLANGID(LANG()))
#घोषणा SUBLANG()      SUBLANGID(LANG())

अटल व्योम IME_Update_निवेश_Locale(SDL_Video_तथ्य *videodata);
अटल व्योम IME_SetWindow(SDL_Video_तथ्य *videodata, SDL_Window *window);
अटल व्योम IME_SetupAPI(SDL_Video_तथ्य *videodata);
अटल DWORD IME_GetId(SDL_Video_तथ्य *videodata, UINT u_सूचकांक);
अटल व्योम IME_SendEditingEvent(SDL_Video_तथ्य *videodata);
अटल व्योम IME_SendClearComposition(SDL_Video_तथ्य *videodata);

अटल bool IME_Init(SDL_Video_तथ्य *videodata, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;

    अगर (videodata->ime_initialized) {
        वापस true;
    }

    स्थिर अक्षर *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);
    अगर (hint && SDL_strstr(hint, "composition")) {
        videodata->ime_internal_composition = true;
    }
    अगर (hint && SDL_strstr(hint, "candidates")) {
        videodata->ime_internal_candidates = true;
    }

    videodata->ime_hwnd_main = hwnd;
    videodata->ime_initialized = true;
    videodata->ime_himm32 = SDL_LoadObject("imm32.dll");
    अगर (!videodata->ime_himm32) {
        videodata->ime_available = false;
        SDL_ClearError();
        वापस true;
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
    अगर (!videodata->ime_himc) {
        videodata->ime_available = false;
        IME_Disable(videodata, hwnd);
        वापस true;
    }
    videodata->ime_available = true;
    IME_Update_निवेश_Locale(videodata);
    IME_SetupAPI(videodata);
    IME_Update_निवेश_Locale(videodata);
    IME_Disable(videodata, hwnd);
    वापस true;
}

अटल व्योम IME_Enable(SDL_Video_तथ्य *videodata, HWND hwnd)
{
    अगर (!videodata->ime_initialized || !videodata->ime_hwnd_current) {
        वापस;
    }

    अगर (!videodata->ime_available) {
        IME_Disable(videodata, hwnd);
        वापस;
    }
    अगर (videodata->ime_hwnd_current == videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_current, videodata->ime_himc);
    }

    videodata->ime_enabled = true;
    IME_Update_निवेश_Locale(videodata);
}

अटल व्योम IME_Disable(SDL_Video_तथ्य *videodata, HWND hwnd)
{
    अगर (!videodata->ime_initialized || !videodata->ime_hwnd_current) {
        वापस;
    }

    IME_ClearComposition(videodata);
    अगर (videodata->ime_hwnd_current == videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_current, (HIMC)0);
    }

    videodata->ime_enabled = false;
}

अटल व्योम IME_Quit(SDL_Video_तथ्य *videodata)
{
    अगर (!videodata->ime_initialized) {
        वापस;
    }

    अगर (videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_main, videodata->ime_himc);
    }

    videodata->ime_hwnd_main = 0;
    videodata->ime_himc = 0;
    अगर (videodata->ime_himm32) {
        SDL_UnloadObject(videodata->ime_himm32);
        videodata->ime_himm32 = 0;
    }
    क्रम (पूर्णांक i = 0; i < videodata->ime_candcount; ++i) {
        SDL_free(videodata->ime_candidates[i]);
        videodata->ime_candidates[i] = शून्य;
    }
    videodata->ime_initialized = false;
}

अटल व्योम IME_GetReadingString(SDL_Video_तथ्य *videodata, HWND hwnd)
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
    अगर (!id) {
        वापस;
    }

    himc = ImmGetContext(hwnd);
    अगर (!himc) {
        वापस;
    }

    अगर (videodata->GetReadingString) {
        len = videodata->GetReadingString(himc, 0, 0, &err, &vertical, &maxuilen);
        अगर (len) {
            अगर (len > SDL_arraysize(बफर_2)) {
                len = SDL_arraysize(बफर_2);
            }

            len = videodata->GetReadingString(himc, len, s, &err, &vertical, &maxuilen);
        }
        SDL_wcslcpy(videodata->ime_readingstring, s, len);
    } अन्यथा {
        LPINPUTCONTEXT2 lpimc = videodata->ImmLockIMC(himc);
        LPBYTE p = 0;
        s = 0;
        चयन (id) {
        हाल IMEID_CHT_VER42:
        हाल IMEID_CHT_VER43:
        हाल IMEID_CHT_VER44:
            p = *(LPBYTE *)((LPBYTE)videodata->ImmLockIMCC(lpimc->hPrivate) + 24);
            अगर (!p) {
                अवरोध;
            }

            len = *(DWORD *)(p + 7 * 4 + 32 * 4);
            s = (WCHAR *)(p + 56);
            अवरोध;
        हाल IMEID_CHT_VER51:
        हाल IMEID_CHT_VER52:
        हाल IMEID_CHS_VER53:
            p = *(LPBYTE *)((LPBYTE)videodata->ImmLockIMCC(lpimc->hPrivate) + 4);
            अगर (!p) {
                अवरोध;
            }

            p = *(LPBYTE *)(p + 1 * 4 + 5 * 4);
            अगर (!p) {
                अवरोध;
            }

            len = *(DWORD *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4 + 16 * 2);
            s = (WCHAR *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4);
            अवरोध;
        हाल IMEID_CHS_VER41:
        {
            पूर्णांक offset = (IME_GetId(videodata, 1) >= 0x00000002) ? 8 : 7;
            p = *(LPBYTE *)((LPBYTE)videodata->ImmLockIMCC(lpimc->hPrivate) + offset * 4);
            अगर (!p) {
                अवरोध;
            }

            len = *(DWORD *)(p + 7 * 4 + 16 * 2 * 4);
            s = (WCHAR *)(p + 6 * 4 + 16 * 2 * 1);
        } अवरोध;
        हाल IMEID_CHS_VER42:
            p = *(LPBYTE *)((LPBYTE)videodata->ImmLockIMCC(lpimc->hPrivate) + 1 * 4 + 1 * 4 + 6 * 4);
            अगर (!p) {
                अवरोध;
            }

            len = *(DWORD *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4 + 16 * 2);
            s = (WCHAR *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4);
            अवरोध;
        }
        अगर (s) {
            माप_प्रकार आकार = SDL_min((माप_प्रकार)(len + 1), SDL_arraysize(videodata->ime_readingstring));
            SDL_wcslcpy(videodata->ime_readingstring, s, आकार);
        }

        videodata->ImmUnlockIMCC(lpimc->hPrivate);
        videodata->ImmUnlockIMC(himc);
    }
    ImmReleaseContext(hwnd, himc);
    IME_SendEditingEvent(videodata);
}

अटल व्योम IME_निवेश_Lang_Changed(SDL_Video_तथ्य *videodata)
{
    UINT lang = PRIMLANG();
    IME_Update_निवेश_Locale(videodata);

    IME_SetupAPI(videodata);
    अगर (lang != PRIMLANG()) {
        IME_ClearComposition(videodata);
    }
}

अटल DWORD IME_GetId(SDL_Video_तथ्य *videodata, UINT u_सूचकांक)
{
    अटल HKL hklprev = 0;
    अटल DWORD dwRet[2] = { 0 };
    DWORD dw_Ver_आकार = 0;
    LPVOID lp_Ver_बफर = 0;
    LPVOID lp_Ver_तथ्य = 0;
    UINT cb_Ver_तथ्य = 0;
    अक्षर sz_अस्थायी[256];
    HKL hkl = 0;
    DWORD dwLang = 0;
    SDL_assert(u_सूचकांक < SDL_arraysize(dwRet));

    hkl = videodata->ime_hkl;
    अगर (hklprev == hkl) {
        वापस dwRet[u_सूचकांक];
    }
    hklprev = hkl;

    SDL_assert(u_सूचकांक == 0);
    dwLang = ((DWORD_PTR)hkl & 0xffff);
    // FIXME: What does this do?
    अगर (videodata->ime_internal_candidates && dwLang == LANG_CHT) {
        dwRet[0] = IMEID_CHT_VER_VISTA;
        dwRet[1] = 0;
        वापस dwRet[0];
    }
    अगर (hkl != CHT_HKL_NEW_PHONETIC && hkl != CHT_HKL_NEW_CHANG_JIE && hkl != CHT_HKL_NEW_QUICK && hkl != CHT_HKL_HK_CANTONESE && hkl != CHS_HKL) {
        dwRet[0] = dwRet[1] = 0;
        वापस dwRet[0];
    }
    अगर (!ImmGetIMEFileNameA(hkl, sz_अस्थायी, माप(sz_अस्थायी) - 1)) {
        dwRet[0] = dwRet[1] = 0;
        वापस dwRet[0];
    }
    अगर (!videodata->GetReadingString) {
#घोषणा LCID_INVARIANT MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT)
        अगर (CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_अस्थायी, -1, CHT_IMEFILENAME1, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_अस्थायी, -1, CHT_IMEFILENAME2, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_अस्थायी, -1, CHT_IMEFILENAME3, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_अस्थायी, -1, CHS_IMEFILENAME1, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_अस्थायी, -1, CHS_IMEFILENAME2, -1) != 2) {
            dwRet[0] = dwRet[1] = 0;
            वापस dwRet[0];
        }
#अघोषित LCID_INVARIANT
        dw_Ver_आकार = Get_File_Version_Info_आकार_A(sz_अस्थायी, शून्य);
        अगर (dw_Ver_आकार) {
            lp_Ver_बफर = SDL_malloc(dw_Ver_आकार);
            अगर (lp_Ver_बफर) {
                अगर (GetFileVersionInfoA(sz_अस्थायी, 0, dw_Ver_आकार, lp_Ver_बफर)) {
                    अगर (Ver_Query_मूल्य_A(lp_Ver_बफर, "\\", &lp_Ver_तथ्य, &cb_Ver_तथ्य)) {
#घोषणा pVerFixedInfo ((VS_FIXEDFILEINFO FAR *)lp_Ver_तथ्य)
                        DWORD dwVer = pVerFixedInfo->dwFileVersionMS;
                        dwVer = (dwVer & 0x00ff0000) << 8 | (dwVer & 0x000000ff) << 16;
                        अगर ((videodata->GetReadingString) ||
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
                            SDL_free(lp_Ver_बफर);
                            वापस dwRet[0];
                        }
#अघोषित pVerFixedInfo
                    }
                }
            }
            SDL_free(lp_Ver_बफर);
        }
    }
    dwRet[0] = dwRet[1] = 0;
    वापस dwRet[0];
}

अटल व्योम IME_SetupAPI(SDL_Video_तथ्य *videodata)
{
    अक्षर ime_file[MAX_PATH + 1];
    SDL_SharedObject *hime = 0;
    HKL hkl = 0;
    videodata->GetReadingString = शून्य;
    videodata->ShowReadingWindow = शून्य;

    hkl = videodata->ime_hkl;
    अगर (!ImmGetIMEFileNameA(hkl, ime_file, माप(ime_file) - 1)) {
        वापस;
    }

    hime = SDL_LoadObject(ime_file);
    अगर (!hime) {
        वापस;
    }

    /* *INDENT-OFF* */ // clang-format off
    videodata->GetReadingString = (UINT (WINAPI *)(HIMC, UINT, LPWSTR, PINT, BOOL*, PUINT))
        SDL_LoadFunction(hime, "GetReadingString");
    videodata->ShowReadingWindow = (BOOL (WINAPI *)(HIMC, BOOL))
        SDL_LoadFunction(hime, "ShowReadingWindow");
    /* *INDENT-ON* */ // clang-format on

    अगर (videodata->ShowReadingWindow) {
        HIMC himc = ImmGetContext(videodata->ime_hwnd_current);
        अगर (himc) {
            videodata->ShowReadingWindow(himc, FALSE);
            ImmReleaseContext(videodata->ime_hwnd_current, himc);
        }
    }
}

अटल व्योम IME_SetWindow(SDL_Video_तथ्य *videodata, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;

    अगर (hwnd != videodata->ime_hwnd_current) {
        videodata->ime_hwnd_current = hwnd;
        SDL_zero(videodata->ime_composition_area);
        SDL_zero(videodata->ime_candidate_area);
    }

    IME_Set_Text_निवेश_Area(videodata, hwnd, &window->text_निवेश_rect, window->text_निवेश_cursor);
}

#पूर्ण_अगर

अटल व्योम IME_Set_Text_निवेश_Area(SDL_Video_तथ्य *videodata, HWND hwnd, स्थिर SDL_Rect *rect, पूर्णांक cursor)
{
    HIMC himc;

    himc = ImmGetContext(hwnd);
    अगर (himc) {
        COMPOSITIONFORM cof;
        CANDIDATEFORM caf;
        पूर्णांक font_height = rect->h;

        LOGFONTW font;
        अगर (ImmGetCompositionFontW(himc, &font)) {
            font_height = font.lfHeight;
        }

        SDL_zero(cof);
        cof.dwStyle = CFS_RECT;
        cof.ptCurrentPos.x = rect->x + cursor;
        cof.ptCurrentPos.y = rect->y + (rect->h - font_height) / 2;
        cof.rcArea.बायाँ = rect->x;
        cof.rcArea.दायाँ = (LONG)rect->x + rect->w;
        cof.rcArea.शीर्ष = rect->y;
        cof.rcArea.bottom = (LONG)rect->y + rect->h;
        अगर (SDL_memcmp(&cof, &videodata->ime_composition_area, माप(cof)) != 0) {
            SDL_copyp(&videodata->ime_composition_area, &cof);
            ImmSetCompositionWindow(himc, &cof);
        }

        SDL_zero(caf);
        caf.dw_सूचकांक = 0;
        caf.dwStyle = CFS_EXCLUDE;
        caf.ptCurrentPos.x = rect->x + cursor;
        caf.ptCurrentPos.y = rect->y;
        caf.rcArea.बायाँ = rect->x;
        caf.rcArea.दायाँ = (LONG)rect->x + rect->w;
        caf.rcArea.शीर्ष = rect->y;
        caf.rcArea.bottom = (LONG)rect->y + rect->h;
        अगर (SDL_memcmp(&caf, &videodata->ime_candidate_area, माप(caf)) != 0) {
            SDL_copyp(&videodata->ime_candidate_area, &caf);
            ImmSetCandidateWindow(himc, &caf);
        }

        ImmReleaseContext(hwnd, himc);
    }
}

#अगर_अघोषित SDL_DISABLE_WINDOWS_IME

अटल व्योम IME_Update_निवेश_Locale(SDL_Video_तथ्य *videodata)
{
    HKL hklnext = GetKeyboardLayout(0);

    अगर (hklnext == videodata->ime_hkl) {
        वापस;
    }

    videodata->ime_hkl = hklnext;
    videodata->ime_horizontal_candidates = (PRIMLANG() == LANG_KOREAN || LANG() == LANG_CHS);
    videodata->ime_candlistindexbase = (videodata->ime_hkl == CHT_HKL_DAYI) ? 0 : 1;
}

अटल व्योम IME_ClearComposition(SDL_Video_तथ्य *videodata)
{
    HIMC himc = 0;
    अगर (!videodata->ime_initialized) {
        वापस;
    }

    himc = ImmGetContext(videodata->ime_hwnd_current);
    अगर (!himc) {
        वापस;
    }

    ImmNotifyIME(himc, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
    ImmSetCompositionString(himc, SCS_SETSTR, TEXT(""), माप(TCHAR), TEXT(""), माप(TCHAR));

    ImmNotifyIME(himc, NI_CLOSECANDIDATE, 0, 0);
    ImmReleaseContext(videodata->ime_hwnd_current, himc);
    IME_SendClearComposition(videodata);
}

अटल व्योम IME_GetCompositionString(SDL_Video_तथ्य *videodata, HIMC himc, LPARAM *lParam, DWORD string)
{
    LONG लंबाई;
    DWORD dwLang = ((DWORD_PTR)videodata->ime_hkl & 0xffff);

    अगर (*lParam & GCS_CURSORPOS) {
        videodata->ime_cursor = LOWORD(ImmGetCompositionStringW(himc, GCS_CURSORPOS, 0, 0));
    }
    videodata->ime_selected_start = 0;
    videodata->ime_selected_लंबाई = 0;
    SDL_DebugIMELog("Cursor = %d", videodata->ime_cursor);

    लंबाई = ImmGetCompositionStringW(himc, string, शून्य, 0);
    अगर (लंबाई > 0 && videodata->ime_composition_लंबाई < लंबाई) {
        SDL_free(videodata->ime_composition);

        videodata->ime_composition = (WCHAR *)SDL_malloc(लंबाई + माप(WCHAR));
        videodata->ime_composition_लंबाई = लंबाई;
    }

    लंबाई = ImmGetCompositionStringW(himc, string, videodata->ime_composition, videodata->ime_composition_लंबाई);
    अगर (लंबाई < 0) {
        लंबाई = 0;
    }
    लंबाई /= माप(WCHAR);

    अगर (!(*lParam & GCS_CURSORPOS)) {
        // If the IME doesn't support GCS_CURSORPOS, default the cursor to the end of the composition.
        videodata->ime_cursor = लंबाई;
    }

    अगर ((dwLang == LANG_CHT || dwLang == LANG_CHS) &&
        videodata->ime_cursor > 0 &&
        videodata->ime_cursor < (पूर्णांक)(videodata->ime_composition_लंबाई / माप(WCHAR)) &&
        (videodata->ime_composition[0] == 0x3000 || videodata->ime_composition[0] == 0x0020)) {
        // Traditional Chinese IMEs add a placeholder U+3000
        // Simplified Chinese IMEs seem to add a placeholder U+0020 sometimes
        क्रम (पूर्णांक i = videodata->ime_cursor + 1; i < लंबाई; ++i) {
            videodata->ime_composition[i - 1] = videodata->ime_composition[i];
        }
        --लंबाई;
    }

    videodata->ime_composition[लंबाई] = 0;

    लंबाई = ImmGetCompositionStringW(himc, GCS_COMPATTR, शून्य, 0);
    अगर (लंबाई > 0) {
        Uint8 *attributes = (Uint8 *)SDL_malloc(लंबाई);
        अगर (attributes) {
            पूर्णांक start = 0;
            पूर्णांक end = 0;

            लंबाई = ImmGetCompositionString(himc, GCS_COMPATTR, attributes, लंबाई);
            अगर (लंबाई < 0) {
                लंबाई = 0;
            }

            क्रम (LONG i = 0; i < लंबाई; ++i) {
                SDL_DebugIMELog("attrib[%d] = %d", i, attributes[i]);
            }

            क्रम (start = 0; start < लंबाई; ++start) {
                अगर (attributes[start] == ATTR_TARGET_CONVERTED || attributes[start] == ATTR_TARGET_NOTCONVERTED) {
                    अवरोध;
                }
            }

            क्रम (end = start; end < लंबाई; ++end) {
                अगर (attributes[end] != ATTR_TARGET_CONVERTED && attributes[end] != ATTR_TARGET_NOTCONVERTED) {
                    अवरोध;
                }
            }

            अगर (end > start) {
                videodata->ime_selected_start = start;
                videodata->ime_selected_लंबाई = end - start;
            }

            SDL_free(attributes);
        }
    }
}

अटल व्योम IME_Send_निवेश_Event(SDL_Video_तथ्य *videodata)
{
    अक्षर *s = 0;
    s = WIN_StringToUTF8W(videodata->ime_composition);
    SDL_SendKeyboardText(s);
    SDL_free(s);

    videodata->ime_composition[0] = 0;
    videodata->ime_readingstring[0] = 0;
    videodata->ime_cursor = 0;
}

अटल व्योम IME_SendEditingEvent(SDL_Video_तथ्य *videodata)
{
    अक्षर *s = शून्य;
    WCHAR *बफर_2 = शून्य;
    माप_प्रकार आकार = videodata->ime_composition_लंबाई;
    अगर (videodata->ime_readingstring[0]) {
        माप_प्रकार len = SDL_min(SDL_wcslen(videodata->ime_composition), (माप_प्रकार)videodata->ime_cursor);

        आकार += माप(videodata->ime_readingstring);
        बफर_2 = (WCHAR *)SDL_malloc(आकार + माप(WCHAR));
        अगर (!बफर_2) {
            वापस;
        }
        बफर_2[0] = 0;

        SDL_wcslcpy(बफर_2, videodata->ime_composition, len + 1);
        SDL_wcslcat(बफर_2, videodata->ime_readingstring, आकार);
        SDL_wcslcat(बफर_2, &videodata->ime_composition[len], आकार);
    } अन्यथा {
        बफर_2 = (WCHAR *)SDL_malloc(आकार + माप(WCHAR));
        अगर (!बफर_2) {
            वापस;
        }
        बफर_2[0] = 0;
        SDL_wcslcpy(बफर_2, videodata->ime_composition, आकार);
    }

    s = WIN_StringToUTF8W(बफर_2);
    अगर (s) {
        अगर (videodata->ime_readingstring[0]) {
            SDL_SendEditingText(s, videodata->ime_cursor, (पूर्णांक)SDL_wcslen(videodata->ime_readingstring));
        } अन्यथा अगर (videodata->ime_cursor == videodata->ime_selected_start) {
            SDL_SendEditingText(s, videodata->ime_selected_start, videodata->ime_selected_लंबाई);
        } अन्यथा {
            SDL_SendEditingText(s, videodata->ime_cursor, 0);
        }
        अगर (*s) {
            videodata->ime_needs_clear_composition = true;
        }
        SDL_free(s);
    }
    SDL_free(बफर_2);
}

अटल व्योम IME_SendClearComposition(SDL_Video_तथ्य *videodata)
{
    अगर (videodata->ime_needs_clear_composition) {
        SDL_SendEditingText("", 0, 0);
        videodata->ime_needs_clear_composition = false;
    }
}

अटल bool IME_OpenCandidateList(SDL_Video_तथ्य *videodata)
{
    videodata->ime_candidates_open = true;
    videodata->ime_candcount = 0;
    वापस true;
}

अटल व्योम IME_AddCandidate(SDL_Video_तथ्य *videodata, UINT i, LPCWSTR candidate)
{
    अगर (videodata->ime_candidates[i]) {
        SDL_free(videodata->ime_candidates[i]);
        videodata->ime_candidates[i] = शून्य;
    }

    SDL_COMPILE_TIME_ASSERT(IME_CANDIDATE_INDEXING_REQUIRES, MAX_CANDLIST == 10);
    अक्षर *candidate_utf8 = WIN_StringToUTF8W(candidate);
    SDL_asprintf(&videodata->ime_candidates[i], "%d %s", ((i + videodata->ime_candlistindexbase) % 10), candidate_utf8);
    SDL_free(candidate_utf8);

    videodata->ime_candcount = (i + 1);
}

अटल व्योम IME_SendCandidateList(SDL_Video_तथ्य *videodata)
{
    SDL_SendEditingTextCandidates(videodata->ime_candidates, videodata->ime_candcount, videodata->ime_candsel, videodata->ime_horizontal_candidates);
}

अटल व्योम IME_CloseCandidateList(SDL_Video_तथ्य *videodata)
{
    videodata->ime_candidates_open = false;

    अगर (videodata->ime_candcount > 0) {
        क्रम (पूर्णांक i = 0; i < videodata->ime_candcount; ++i) {
            SDL_free(videodata->ime_candidates[i]);
            videodata->ime_candidates[i] = शून्य;
        }
        videodata->ime_candcount = 0;

        SDL_SendEditingTextCandidates(शून्य, 0, -1, false);
    }
}

अटल व्योम IME_GetCandidateList(SDL_Video_तथ्य *videodata, HWND hwnd)
{
    HIMC himc;
    DWORD आकार;
    LPCANDIDATELIST cand_list;
    bool has_candidates = false;

    himc = ImmGetContext(hwnd);
    अगर (himc) {
        आकार = ImmGetCandidateListW(himc, 0, शून्य, 0);
        अगर (आकार != 0) {
            cand_list = (LPCANDIDATELIST)SDL_malloc(आकार);
            अगर (cand_list != शून्य) {
                आकार = ImmGetCandidateListW(himc, 0, cand_list, आकार);
                अगर (आकार != 0) {
                    अगर (IME_OpenCandidateList(videodata)) {
                        UINT i, j;
                        UINT page_start = 0;
                        UINT page_आकार = 0;

                        videodata->ime_candsel = cand_list->dwSelection;

                        अगर (LANG() == LANG_CHS && IME_GetId(videodata, 0)) {
                            स्थिर UINT maxcandchar = 18;
                            माप_प्रकार cchars = 0;

                            क्रम (i = 0; i < cand_list->dw_गिनती; ++i) {
                                माप_प्रकार len = SDL_wcslen((LPWSTR)((DWORD_PTR)cand_list + cand_list->dwOffset[i])) + 1;
                                अगर (len + cchars > maxcandchar) {
                                    अगर (i > cand_list->dwSelection) {
                                        अवरोध;
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
                        क्रम (i = page_start, j = 0; (DWORD)i < cand_list->dw_गिनती && j < page_आकार; i++, j++) {
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

    अगर (!has_candidates) {
        IME_CloseCandidateList(videodata);
    }
}

bool WIN_HandleIMEMessage(HWND hwnd, UINT संदेश, WPARAM wParam, LPARAM *lParam, SDL_Video_तथ्य *videodata)
{
    bool trap = false;
    HIMC himc = 0;

    अगर (संदेश == WM_IME_SETCONTEXT) {
        SDL_DebugIMELog("WM_IME_SETCONTEXT");

        LPARAM element_mask;
        element_mask = ISC_SHOWUIALL;
        अगर (videodata->ime_internal_composition) {
            element_mask &= ~ISC_SHOWUICOMPOSITIONWINDOW;
        }
        अगर (videodata->ime_internal_candidates) {
            element_mask &= ~ISC_SHOWUIALLCANDIDATEWINDOW;
        }
        *lParam &= element_mask;

        वापस false;
    } अन्यथा अगर (संदेश == WM_IME_STARTCOMPOSITION) {
        SDL_DebugIMELog("WM_IME_STARTCOMPOSITION");
        अगर (videodata->ime_internal_composition) {
            videodata->ime_cursor = 0;
            // Windows may still display a composition dialog even with
            // ISC_SHOWUICOMPOSITIONWINDOW cleared, so trap the message
            // here to prevent that (even when the IME is disabled).
            वापस true;
        }
    }

    अगर (!videodata->ime_initialized || !videodata->ime_available || !videodata->ime_enabled) {
        वापस false;
    }

    चयन (संदेश) {
    हाल WM_KEYDOWN:
        अगर (wParam == VK_PROCESSKEY) {
            SDL_DebugIMELog("WM_KEYDOWN VK_PROCESSKEY");
            trap = true;
        } अन्यथा {
            SDL_DebugIMELog("WM_KEYDOWN normal");
        }
        अवरोध;
    हाल WM_SYSKEYDOWN:
        अगर (wParam == VK_PROCESSKEY) {
            SDL_DebugIMELog("WM_SYSKEYDOWN VK_PROCESSKEY");
            trap = true;
        } अन्यथा {
            SDL_DebugIMELog("WM_SYSKEYDOWN normal");
        }
        अवरोध;
    हाल WM_INPUTLANGCHANGE:
        SDL_DebugIMELog("WM_INPUTLANGCHANGE");
        IME_निवेश_Lang_Changed(videodata);
        अवरोध;
    हाल WM_IME_COMPOSITION:
        SDL_DebugIMELog("WM_IME_COMPOSITION %x", lParam);
        अगर (videodata->ime_internal_composition) {
            trap = true;
            himc = ImmGetContext(hwnd);
            अगर (*lParam & GCS_RESULTSTR) {
                SDL_DebugIMELog("GCS_RESULTSTR");
                IME_GetCompositionString(videodata, himc, lParam, GCS_RESULTSTR);
                IME_SendClearComposition(videodata);
                IME_Send_निवेश_Event(videodata);
            }
            अगर (*lParam & GCS_COMPSTR) {
                SDL_DebugIMELog("GCS_COMPSTR");
                videodata->ime_readingstring[0] = 0;
                IME_GetCompositionString(videodata, himc, lParam, GCS_COMPSTR);
                IME_SendEditingEvent(videodata);
            }
            ImmReleaseContext(hwnd, himc);
        }
        अवरोध;
    हाल WM_IME_ENDCOMPOSITION:
        SDL_DebugIMELog("WM_IME_ENDCOMPOSITION");
        अगर (videodata->ime_internal_composition) {
            trap = true;
            videodata->ime_composition[0] = 0;
            videodata->ime_readingstring[0] = 0;
            videodata->ime_cursor = 0;
            videodata->ime_selected_start = 0;
            videodata->ime_selected_लंबाई = 0;
            IME_SendClearComposition(videodata);
        }
        अवरोध;
    हाल WM_IME_NOTIFY:
        SDL_DebugIMELog("WM_IME_NOTIFY %x", wParam);
        चयन (wParam) {
        हाल IMN_SETCOMPOSITIONWINDOW:
            SDL_DebugIMELog("IMN_SETCOMPOSITIONWINDOW");
            अवरोध;
        हाल IMN_SETCOMPOSITIONFONT:
            SDL_DebugIMELog("IMN_SETCOMPOSITIONFONT");
            अवरोध;
        हाल IMN_SETCANDIDATEPOS:
            SDL_DebugIMELog("IMN_SETCANDIDATEPOS");
            अवरोध;
        हाल IMN_SETCONVERSIONMODE:
        हाल IMN_SETOPENSTATUS:
            SDL_DebugIMELog("%s", wParam == IMN_SETCONVERSIONMODE ? "IMN_SETCONVERSIONMODE" : "IMN_SETOPENSTATUS");
            IME_Update_निवेश_Locale(videodata);
            अवरोध;
        हाल IMN_OPENCANDIDATE:
        हाल IMN_CHANGECANDIDATE:
            SDL_DebugIMELog("%s", wParam == IMN_OPENCANDIDATE ? "IMN_OPENCANDIDATE" : "IMN_CHANGECANDIDATE");
            अगर (videodata->ime_internal_candidates) {
                trap = true;
                videodata->ime_update_candidates = true;
            }
            अवरोध;
        हाल IMN_CLOSECANDIDATE:
            SDL_DebugIMELog("IMN_CLOSECANDIDATE");
            अगर (videodata->ime_internal_candidates) {
                trap = true;
                videodata->ime_update_candidates = false;
                IME_CloseCandidateList(videodata);
            }
            अवरोध;
        हाल IMN_PRIVATE:
        {
            DWORD dwId = IME_GetId(videodata, 0);
            SDL_DebugIMELog("IMN_PRIVATE %u", dwId);
            IME_GetReadingString(videodata, hwnd);
            चयन (dwId) {
            हाल IMEID_CHT_VER42:
            हाल IMEID_CHT_VER43:
            हाल IMEID_CHT_VER44:
            हाल IMEID_CHS_VER41:
            हाल IMEID_CHS_VER42:
                अगर (*lParam == 1 || *lParam == 2) {
                    trap = true;
                }

                अवरोध;
            हाल IMEID_CHT_VER50:
            हाल IMEID_CHT_VER51:
            हाल IMEID_CHT_VER52:
            हाल IMEID_CHT_VER60:
            हाल IMEID_CHS_VER53:
                अगर (*lParam == 16 || *lParam == 17 || *lParam == 26 || *lParam == 27 || *lParam == 28) {
                    trap = true;
                }
                अवरोध;
            }
        } अवरोध;
        शेष:
            trap = true;
            अवरोध;
        }
        अवरोध;
    }
    वापस trap;
}

व्योम WIN_UpdateIMECandidates(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *videodata = _this->internal;

    अगर (videodata->ime_update_candidates) {
        IME_GetCandidateList(videodata, videodata->ime_hwnd_current);
        videodata->ime_update_candidates = false;
    }
}

#पूर्ण_अगर // SDL_DISABLE_WINDOWS_IME

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WINDOWS
