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

#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/scancodes_windows.h"

#ಅನ್ತರ್ಭಾವ <imm.h>
#ಅನ್ತರ್ಭಾವ <oleauto.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_DISABLE_WINDOWS_IME
#ಆದರೆ 0
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_DebugIMELog SDL_Log
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_DebugIMELog(...)
#ಆದರೆ_ಅಂತ್ಯ
ಸ್ಥಿರ bool IME_Init(SDL_Video_ದತ್ತಾಂಶ *videodata, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಸ್ಥಿರ ಶೂನ್ಯ IME_Enable(SDL_Video_ದತ್ತಾಂಶ *videodata, HWND hwnd);
ಸ್ಥಿರ ಶೂನ್ಯ IME_Disable(SDL_Video_ದತ್ತಾಂಶ *videodata, HWND hwnd);
ಸ್ಥಿರ ಶೂನ್ಯ IME_ಗಣ_ಪಠ್ಯ_ಒಳಹರಿವು_Area(SDL_Video_ದತ್ತಾಂಶ *videodata, HWND hwnd, ಸ್ಥಿರಾಂಕ SDL_Rect *rect, ಪೂರ್ಣಾಂಕ cursor);
ಸ್ಥಿರ ಶೂನ್ಯ IME_ClearComposition(SDL_Video_ದತ್ತಾಂಶ *videodata);
ಸ್ಥಿರ ಶೂನ್ಯ IME_GetCandidateList(SDL_Video_ದತ್ತಾಂಶ *videodata, HWND hwnd);
ಸ್ಥಿರ ಶೂನ್ಯ IME_Quit(SDL_Video_ದತ್ತಾಂಶ *videodata);
#ಇಲ್ಲದಿದ್ದರೆ
ಸ್ಥಿರ ಶೂನ್ಯ IME_ಗಣ_ಪಠ್ಯ_ಒಳಹರಿವು_Area(SDL_Video_ದತ್ತಾಂಶ *videodata, HWND hwnd, ಸ್ಥಿರಾಂಕ SDL_Rect *rect, ಪೂರ್ಣಾಂಕ cursor);
#ಆದರೆ_ಅಂತ್ಯ // !SDL_DISABLE_WINDOWS_IME

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MAPVK_VK_ಗಮ್ಯ_VSC
#ವ್ಯಾಖ್ಯಾನಿಸು MAPVK_VK_ಗಮ್ಯ_VSC 0
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MAPVK_VSC_ಗಮ್ಯ_VK
#ವ್ಯಾಖ್ಯಾನಿಸು MAPVK_VSC_ಗಮ್ಯ_VK 1
#ಆದರೆ_ಅಂತ್ಯ

/* Building keymaps is expensive, so keep a reasonably-sized LRU cache to
 * enable fast switching between commonly used ones.
 */
ಸ್ಥಿರ ರಚನೆ WIN_KeymapCache
{
    HKL keyboard_layout;
    SDL_Keymap *keymap;
} keymap_cache[4];

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ keymap_cache_ಗಾತ್ರ;

ಸ್ಥಿರ SDL_Keymap *WIN_GetCachedKeymap(HKL layout)
{
    SDL_Keymap *keymap = ಖಾಲಿ;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < keymap_cache_ಗಾತ್ರ; ++i) {
        ಆದರೆ (keymap_cache[i].keyboard_layout == layout) {
            keymap = keymap_cache[i].keymap;

            // Move the map to the front of the list.
            ಆದರೆ (i) {
                SDL_memmove(keymap_cache + 1, keymap_cache, ಗಾತ್ರ(ರಚನೆ WIN_KeymapCache) * i);
                keymap_cache[0].keyboard_layout = layout;
                keymap_cache[0].keymap = keymap;
            }
            ನಿಲ್ಲಿಸು;
        }
    }
    ಹಿಂತಿರುಗಿ keymap;
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_CacheKeymap(HKL layout, SDL_Keymap *keymap)
{
    // If the cache is full, evict the last keymap.
    ಆದರೆ (keymap_cache_ಗಾತ್ರ == SDL_arraysize(keymap_cache)) {
        SDL_DestroyKeymap(keymap_cache[--keymap_cache_ಗಾತ್ರ].keymap);
    }

    // Move all elements down by one.
    ಆದರೆ (keymap_cache_ಗಾತ್ರ) {
        SDL_memmove(keymap_cache + 1, keymap_cache, ಗಾತ್ರ(ರಚನೆ WIN_KeymapCache) * keymap_cache_ಗಾತ್ರ);
    }

    keymap_cache[0].keyboard_layout = layout;
    keymap_cache[0].keymap = keymap;
    ++keymap_cache_ಗಾತ್ರ;
}

ಸ್ಥಿರ SDL_Keymap *WIN_BuildKeymap(ಶೂನ್ಯ)
{
    SDL_Scancode scancode;
    BYTE keyboardState[256] = { 0 };
    WCHAR ಬಫರ್_2[16];
    ಸ್ಥಿರಾಂಕ SDL_Keymod mods[] = {
        SDL_KMOD_NONE,
        SDL_KMOD_ಸರಿಸು,
        SDL_KMOD_CAPS,
        (SDL_KMOD_ಸರಿಸು | SDL_KMOD_CAPS),
        SDL_KMOD_ಬಹುಲಕ,
        (SDL_KMOD_ಬಹುಲಕ | SDL_KMOD_ಸರಿಸು),
        (SDL_KMOD_ಬಹುಲಕ | SDL_KMOD_CAPS),
        (SDL_KMOD_ಬಹುಲಕ | SDL_KMOD_ಸರಿಸು | SDL_KMOD_CAPS)
    };

    WIN_Reset_Dead_ಕೀಲಿಗಳು();

    SDL_Keymap *keymap = SDL_CreateKeymap(false);
    ಆದರೆ (!keymap) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ m = 0; m < SDL_arraysize(mods); ++m) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < SDL_arraysize(windows_scancode_ಕೋಷ್ಟಕ); i++) {
            ಪೂರ್ಣಾಂಕ vk, sc, ಫಲಿತಾಂಶ;
            Uint32 *ch = 0;

            // Make sure this scancode is a valid character scancode
            scancode = windows_scancode_ಕೋಷ್ಟಕ[i];
            ಆದರೆ (scancode == SDL_SCANCODE_UNKNOWN ||
                scancode == SDL_SCANCODE_DELETE ||
                (SDL_GetKeymapKeycode(ಖಾಲಿ, scancode, SDL_KMOD_NONE) & SDLK_SCANCODE_ಮುಖವಾಡ)) {

                // The Colemak mapping swaps Backspace and CapsLock
                ಆದರೆ (mods[m] == SDL_KMOD_NONE &&
                    (scancode == SDL_SCANCODE_CAPSLOCK ||
                     scancode == SDL_SCANCODE_BACKSPACE)) {
                    vk = LOBYTE(Map_Virtual_ಕೀಲಿ(i, MAPVK_VSC_ಗಮ್ಯ_VK));
                    ಆದರೆ (vk == VK_CAPITAL) {
                        SDL_ಗಣ_Keymap_ನಮೂದು(keymap, scancode, mods[m], SDLK_CAPSLOCK);
                    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (vk == VK_ಹಿಂಭಾಗ) {
                        SDL_ಗಣ_Keymap_ನಮೂದು(keymap, scancode, mods[m], SDLK_BACKSPACE);
                    }
                }
                ಮುಂದುವರಿ;
            }

            // Unpack the single byte index to make the scan code.
            sc = MAKEWORD(i & 0x7f, (i & 0x80) ? 0xe0 : 0x00);
            vk = LOBYTE(Map_Virtual_ಕೀಲಿ(sc, MAPVK_VSC_ಗಮ್ಯ_VK));
            ಆದರೆ (!vk) {
                ಮುಂದುವರಿ;
            }

            // Update the keyboard state for the modifiers
            keyboardState[VK_ಸರಿಸು] = (mods[m] & SDL_KMOD_ಸರಿಸು) ? 0x80 : 0x00;
            keyboardState[VK_CAPITAL] = (mods[m] & SDL_KMOD_CAPS) ? 0x01 : 0x00;
            keyboardState[VK_CONTROL] = (mods[m] & SDL_KMOD_ಬಹುಲಕ) ? 0x80 : 0x00;
            keyboardState[VK_MENU] = (mods[m] & SDL_KMOD_ಬಹುಲಕ) ? 0x80 : 0x00;

            ಫಲಿತಾಂಶ = ಗಮ್ಯ_Unicode(vk, sc, keyboardState, ಬಫರ್_2, 16, 0);
            ಬಫರ್_2[SDL_abs(ಫಲಿತಾಂಶ)] = 0;

            // Convert UTF-16 to UTF-32 code points
            ch = (Uint32 *)SDL_iconv_string("UTF-32LE", "UTF-16LE", (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)ಬಫರ್_2, (SDL_abs(ಫಲಿತಾಂಶ) + 1) * ಗಾತ್ರ(WCHAR));
            ಆದರೆ (ch) {
                /* Windows keyboard layouts can emit several UTF-32 code points on a single key press.
                 * Use <U+FFFD REPLACEMENT CHARACTER> since we cannot fit into single SDL_Keycode value in SDL keymap.
                 * See https://kbdlayout.info/features/ligatures for a list of such keys. */
                SDL_ಗಣ_Keymap_ನಮೂದು(keymap, scancode, mods[m], ch[1] == 0 ? ch[0] : 0xfffd);
                SDL_free(ch);
            } ಇಲ್ಲದಿದ್ದರೆ {
                // The default keymap doesn't have any SDL_KMOD_MODE entries, so we don't need to override them
                ಆದರೆ (!(mods[m] & SDL_KMOD_ಬಹುಲಕ)) {
                    SDL_ಗಣ_Keymap_ನಮೂದು(keymap, scancode, mods[m], SDLK_UNKNOWN);
                }
            }

            ಆದರೆ (ಫಲಿತಾಂಶ < 0) {
                WIN_Reset_Dead_ಕೀಲಿಗಳು();
            }
        }
    }

    ಹಿಂತಿರುಗಿ keymap;
}

ಶೂನ್ಯ WIN_UpdateKeymap(bool send_event)
{
    HKL layout = GetKeyboardLayout(0);
    SDL_Keymap *keymap = WIN_GetCachedKeymap(layout);
    ಆದರೆ (!keymap) {
        keymap = WIN_BuildKeymap();
        ಆದರೆ (keymap) {
            WIN_CacheKeymap(layout, keymap);
        }
    }

    SDL_ಗಣ_Keymap(keymap, send_event);
}

// Alphabetic scancodes for PC keyboards
ಶೂನ್ಯ WIN_InitKeyboard(SDL_VideoDevice *_this)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_DISABLE_WINDOWS_IME
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    ದತ್ತಾಂಶ->ime_candlistindexbase = 1;
    ದತ್ತಾಂಶ->ime_composition_ಉದ್ದಳತೆ = 32 * ಗಾತ್ರ(WCHAR);
    ದತ್ತಾಂಶ->ime_composition = (WCHAR *)SDL_calloc(ದತ್ತಾಂಶ->ime_composition_ಉದ್ದಳತೆ, ಗಾತ್ರ(WCHAR));
#ಆದರೆ_ಅಂತ್ಯ // !SDL_DISABLE_WINDOWS_IME

    // Build and bind the current keymap.
    WIN_UpdateKeymap(false);

    SDL_ಗಣ_Scancode_Name(SDL_SCANCODE_APPLICATION, "Menu");
    SDL_ಗಣ_Scancode_Name(SDL_SCANCODE_LGUI, "Left Windows");
    SDL_ಗಣ_Scancode_Name(SDL_SCANCODE_RGUI, "Right Windows");

    // Are system caps/num/scroll lock active? Set our state to match.
    SDL_ToggleModState(SDL_KMOD_CAPS, (Get_ಕೀಲಿ_State(VK_CAPITAL) & 0x0001) ? true : false);
    SDL_ToggleModState(SDL_KMOD_ಅಂಕೆ, (Get_ಕೀಲಿ_State(VK_NUMLOCK) & 0x0001) ? true : false);
    SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_ಕೀಲಿ_State(VK_SCROLL) & 0x0001) ? true : false);
}

ಶೂನ್ಯ WIN_QuitKeyboard(SDL_VideoDevice *_this)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_DISABLE_WINDOWS_IME
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    IME_Quit(ದತ್ತಾಂಶ);

    ಆದರೆ (ದತ್ತಾಂಶ->ime_composition) {
        SDL_free(ದತ್ತಾಂಶ->ime_composition);
        ದತ್ತಾಂಶ->ime_composition = ಖಾಲಿ;
    }
#ಆದರೆ_ಅಂತ್ಯ // !SDL_DISABLE_WINDOWS_IME

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < keymap_cache_ಗಾತ್ರ; ++i) {
        SDL_DestroyKeymap(keymap_cache[i].keymap);
    }
    SDL_zeroa(keymap_cache);
    keymap_cache_ಗಾತ್ರ = 0;
}

ಶೂನ್ಯ WIN_Reset_Dead_ಕೀಲಿಗಳು(ಶೂನ್ಯ)
{
    /*
    if a deadkey has been typed, but not the next character (which the deadkey might modify),
    this tries to undo the effect pressing the deadkey.
    see: http://archives.miloush.net/michkap/archive/2006/09/10/748775.html
    */
    BYTE keyboardState[256];
    WCHAR ಬಫರ್_2[16];
    ಪೂರ್ಣಾಂಕ vk, sc, ಫಲಿತಾಂಶ, i;

    ಆದರೆ (!GetKeyboardState(keyboardState)) {
        ಹಿಂತಿರುಗಿ;
    }

    vk = VK_SPACE;
    sc = Map_Virtual_ಕೀಲಿ(vk, MAPVK_VK_ಗಮ್ಯ_VSC);
    ಆದರೆ (sc == 0) {
        // the keyboard doesn't have this key
        ಹಿಂತಿರುಗಿ;
    }

    ಗಾಗಿ (i = 0; i < 5; i++) {
        ಫಲಿತಾಂಶ = ಗಮ್ಯ_Unicode(vk, sc, keyboardState, ಬಫರ್_2, 16, 0);
        ಆದರೆ (ಫಲಿತಾಂಶ > 0) {
            // success
            ಹಿಂತಿರುಗಿ;
        }
    }
}

bool WIN_ಆರಂಭ_ಪಠ್ಯ_ಒಳಹರಿವು(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID props)
{
    WIN_Reset_Dead_ಕೀಲಿಗಳು();

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_DISABLE_WINDOWS_IME
    HWND hwnd = ಕಿಟಕಿ->ಆಂತರಿಕ->hwnd;
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    IME_Init(videodata, ಕಿಟಕಿ);
    IME_Enable(videodata, hwnd);

    WIN_Update_ಪಠ್ಯ_ಒಳಹರಿವು_Area(_this, ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ // !SDL_DISABLE_WINDOWS_IME

    ಹಿಂತಿರುಗಿ true;
}

bool WIN_Stop_ಪಠ್ಯ_ಒಳಹರಿವು(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    WIN_Reset_Dead_ಕೀಲಿಗಳು();

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_DISABLE_WINDOWS_IME
    HWND hwnd = ಕಿಟಕಿ->ಆಂತರಿಕ->hwnd;
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    IME_Init(videodata, ಕಿಟಕಿ);
    IME_Disable(videodata, hwnd);
#ಆದರೆ_ಅಂತ್ಯ // !SDL_DISABLE_WINDOWS_IME

    ಹಿಂತಿರುಗಿ true;
}

bool WIN_Update_ಪಠ್ಯ_ಒಳಹರಿವು_Area(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

    IME_ಗಣ_ಪಠ್ಯ_ಒಳಹರಿವು_Area(videodata, ದತ್ತಾಂಶ->hwnd, &ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_rect, ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_cursor);
    ಹಿಂತಿರುಗಿ true;
}

bool WIN_ClearComposition(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_DISABLE_WINDOWS_IME
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;

    IME_ClearComposition(videodata);
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ true;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_DISABLE_WINDOWS_IME

bool WIN_HandleIMEMessage(HWND hwnd, UINT ಸಂದೇಶ_2, WPARAM wParam, LPARAM *lParam, SDL_Video_ದತ್ತಾಂಶ *videodata)
{
    ಹಿಂತಿರುಗಿ false;
}

ಶೂನ್ಯ WIN_UpdateIMECandidates(SDL_VideoDevice *_this)
{
    ಹಿಂತಿರುಗಿ;
}

#ಇಲ್ಲದಿದ್ದರೆ

#ವ್ಯಾಖ್ಯಾನಿಸು LANG_CHT MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_TRADITIONAL)
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_CHS MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED)

#ವ್ಯಾಖ್ಯಾನಿಸು MAKEIMEVERSION(major, minor) ((DWORD)(((BYTE)(major) << 24) | ((BYTE)(minor) << 16)))
#ವ್ಯಾಖ್ಯಾನಿಸು IMEID_VER(id)                ((id)&0xffff0000)
#ವ್ಯಾಖ್ಯಾನಿಸು IMEID_LANG(id)               ((id)&0x0000ffff)

#ವ್ಯಾಖ್ಯಾನಿಸು CHT_HKL_DAYI          ((HKL)(UINT_PTR)0xE0060404)
#ವ್ಯಾಖ್ಯಾನಿಸು CHT_HKL_NEW_PHONETIC  ((HKL)(UINT_PTR)0xE0080404)
#ವ್ಯಾಖ್ಯಾನಿಸು CHT_HKL_NEW_CHANG_JIE ((HKL)(UINT_PTR)0xE0090404)
#ವ್ಯಾಖ್ಯಾನಿಸು CHT_HKL_NEW_ಶೀಘ್ರ     ((HKL)(UINT_PTR)0xE00A0404)
#ವ್ಯಾಖ್ಯಾನಿಸು CHT_HKL_HK_CANTONESE  ((HKL)(UINT_PTR)0xE00B0404)
#ವ್ಯಾಖ್ಯಾನಿಸು CHT_IMEFILENAME1      "TINTLGNT.IME"
#ವ್ಯಾಖ್ಯಾನಿಸು CHT_IMEFILENAME2      "CINTLGNT.IME"
#ವ್ಯಾಖ್ಯಾನಿಸು CHT_IMEFILENAME3      "MSTCIPHA.IME"
#ವ್ಯಾಖ್ಯಾನಿಸು IMEID_CHT_VER42       (LANG_CHT | MAKEIMEVERSION(4, 2))
#ವ್ಯಾಖ್ಯಾನಿಸು IMEID_CHT_VER43       (LANG_CHT | MAKEIMEVERSION(4, 3))
#ವ್ಯಾಖ್ಯಾನಿಸು IMEID_CHT_VER44       (LANG_CHT | MAKEIMEVERSION(4, 4))
#ವ್ಯಾಖ್ಯಾನಿಸು IMEID_CHT_VER50       (LANG_CHT | MAKEIMEVERSION(5, 0))
#ವ್ಯಾಖ್ಯಾನಿಸು IMEID_CHT_VER51       (LANG_CHT | MAKEIMEVERSION(5, 1))
#ವ್ಯಾಖ್ಯಾನಿಸು IMEID_CHT_VER52       (LANG_CHT | MAKEIMEVERSION(5, 2))
#ವ್ಯಾಖ್ಯಾನಿಸು IMEID_CHT_VER60       (LANG_CHT | MAKEIMEVERSION(6, 0))
#ವ್ಯಾಖ್ಯಾನಿಸು IMEID_CHT_VER_VISTA   (LANG_CHT | MAKEIMEVERSION(7, 0))

#ವ್ಯಾಖ್ಯಾನಿಸು CHS_HKL          ((HKL)(UINT_PTR)0xE00E0804)
#ವ್ಯಾಖ್ಯಾನಿಸು CHS_IMEFILENAME1 "PINTLGNT.IME"
#ವ್ಯಾಖ್ಯಾನಿಸು CHS_IMEFILENAME2 "MSSCIPYA.IME"
#ವ್ಯಾಖ್ಯಾನಿಸು IMEID_CHS_VER41  (LANG_CHS | MAKEIMEVERSION(4, 1))
#ವ್ಯಾಖ್ಯಾನಿಸು IMEID_CHS_VER42  (LANG_CHS | MAKEIMEVERSION(4, 2))
#ವ್ಯಾಖ್ಯಾನಿಸು IMEID_CHS_VER53  (LANG_CHS | MAKEIMEVERSION(5, 3))

#ವ್ಯಾಖ್ಯಾನಿಸು LANG()         LOWORD((videodata->ime_hkl))
#ವ್ಯಾಖ್ಯಾನಿಸು PRIMLANG()     ((ಶಬ್ದ)PRIMARYLANGID(LANG()))
#ವ್ಯಾಖ್ಯಾನಿಸು SUBLANG()      SUBLANGID(LANG())

ಸ್ಥಿರ ಶೂನ್ಯ IME_Update_ಒಳಹರಿವು_Locale(SDL_Video_ದತ್ತಾಂಶ *videodata);
ಸ್ಥಿರ ಶೂನ್ಯ IME_ಗಣ_ಕಿಟಕಿ(SDL_Video_ದತ್ತಾಂಶ *videodata, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಸ್ಥಿರ ಶೂನ್ಯ IME_ಸಿದ್ಧತೆ_API(SDL_Video_ದತ್ತಾಂಶ *videodata);
ಸ್ಥಿರ DWORD IME_GetId(SDL_Video_ದತ್ತಾಂಶ *videodata, UINT u_ಸೂಚ್ಯಂಕ);
ಸ್ಥಿರ ಶೂನ್ಯ IME_SendEditingEvent(SDL_Video_ದತ್ತಾಂಶ *videodata);
ಸ್ಥಿರ ಶೂನ್ಯ IME_SendClearComposition(SDL_Video_ದತ್ತಾಂಶ *videodata);

ಸ್ಥಿರ bool IME_Init(SDL_Video_ದತ್ತಾಂಶ *videodata, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    HWND hwnd = ಕಿಟಕಿ->ಆಂತರಿಕ->hwnd;

    ಆದರೆ (videodata->ime_initialized) {
        ಹಿಂತಿರುಗಿ true;
    }

    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);
    ಆದರೆ (hint && SDL_strstr(hint, "composition")) {
        videodata->ime_ಆಂತರಿಕ_composition = true;
    }
    ಆದರೆ (hint && SDL_strstr(hint, "candidates")) {
        videodata->ime_ಆಂತರಿಕ_candidates = true;
    }

    videodata->ime_hwnd_main = hwnd;
    videodata->ime_initialized = true;
    videodata->ime_himm32 = SDL_ತುಂಬು_Object("imm32.dll");
    ಆದರೆ (!videodata->ime_himm32) {
        videodata->ime_ಲಭ್ಯ = false;
        SDL_ClearError();
        ಹಿಂತಿರುಗಿ true;
    }
    /* *INDENT-OFF* */ // clang-format off
    videodata->Imm_ಬೀಗ_IMC = (LPINPUTCONTEXT2 (WINAPI *)(HIMC))SDL_ತುಂಬು_Function(videodata->ime_himm32, "ImmLockIMC");
    videodata->ImmUnlockIMC = (BOOL (WINAPI *)(HIMC))SDL_ತುಂಬು_Function(videodata->ime_himm32, "ImmUnlockIMC");
    videodata->Imm_ಬೀಗ_IMCC = (LPVOID (WINAPI *)(HIMCC))SDL_ತುಂಬು_Function(videodata->ime_himm32, "ImmLockIMCC");
    videodata->ImmUnlockIMCC = (BOOL (WINAPI *)(HIMCC))SDL_ತುಂಬು_Function(videodata->ime_himm32, "ImmUnlockIMCC");
    /* *INDENT-ON* */ // clang-format on

    IME_ಗಣ_ಕಿಟಕಿ(videodata, ಕಿಟಕಿ);
    videodata->ime_himc = ImmGetContext(hwnd);
    ImmReleaseContext(hwnd, videodata->ime_himc);
    ಆದರೆ (!videodata->ime_himc) {
        videodata->ime_ಲಭ್ಯ = false;
        IME_Disable(videodata, hwnd);
        ಹಿಂತಿರುಗಿ true;
    }
    videodata->ime_ಲಭ್ಯ = true;
    IME_Update_ಒಳಹರಿವು_Locale(videodata);
    IME_ಸಿದ್ಧತೆ_API(videodata);
    IME_Update_ಒಳಹರಿವು_Locale(videodata);
    IME_Disable(videodata, hwnd);
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ IME_Enable(SDL_Video_ದತ್ತಾಂಶ *videodata, HWND hwnd)
{
    ಆದರೆ (!videodata->ime_initialized || !videodata->ime_hwnd_current) {
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (!videodata->ime_ಲಭ್ಯ) {
        IME_Disable(videodata, hwnd);
        ಹಿಂತಿರುಗಿ;
    }
    ಆದರೆ (videodata->ime_hwnd_current == videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_current, videodata->ime_himc);
    }

    videodata->ime_enabled = true;
    IME_Update_ಒಳಹರಿವು_Locale(videodata);
}

ಸ್ಥಿರ ಶೂನ್ಯ IME_Disable(SDL_Video_ದತ್ತಾಂಶ *videodata, HWND hwnd)
{
    ಆದರೆ (!videodata->ime_initialized || !videodata->ime_hwnd_current) {
        ಹಿಂತಿರುಗಿ;
    }

    IME_ClearComposition(videodata);
    ಆದರೆ (videodata->ime_hwnd_current == videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_current, (HIMC)0);
    }

    videodata->ime_enabled = false;
}

ಸ್ಥಿರ ಶೂನ್ಯ IME_Quit(SDL_Video_ದತ್ತಾಂಶ *videodata)
{
    ಆದರೆ (!videodata->ime_initialized) {
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_main, videodata->ime_himc);
    }

    videodata->ime_hwnd_main = 0;
    videodata->ime_himc = 0;
    ಆದರೆ (videodata->ime_himm32) {
        SDL_UnloadObject(videodata->ime_himm32);
        videodata->ime_himm32 = 0;
    }
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < videodata->ime_candcount; ++i) {
        SDL_free(videodata->ime_candidates[i]);
        videodata->ime_candidates[i] = ಖಾಲಿ;
    }
    videodata->ime_initialized = false;
}

ಸ್ಥಿರ ಶೂನ್ಯ IME_GetReadingString(SDL_Video_ದತ್ತಾಂಶ *videodata, HWND hwnd)
{
    DWORD id = 0;
    HIMC himc = 0;
    WCHAR ಬಫರ್_2[16];
    WCHAR *s = ಬಫರ್_2;
    DWORD len = 0;
    INT err = 0;
    BOOL vertical = FALSE;
    UINT maxuilen = 0;

    videodata->ime_readingstring[0] = 0;

    id = IME_GetId(videodata, 0);
    ಆದರೆ (!id) {
        ಹಿಂತಿರುಗಿ;
    }

    himc = ImmGetContext(hwnd);
    ಆದರೆ (!himc) {
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (videodata->GetReadingString) {
        len = videodata->GetReadingString(himc, 0, 0, &err, &vertical, &maxuilen);
        ಆದರೆ (len) {
            ಆದರೆ (len > SDL_arraysize(ಬಫರ್_2)) {
                len = SDL_arraysize(ಬಫರ್_2);
            }

            len = videodata->GetReadingString(himc, len, s, &err, &vertical, &maxuilen);
        }
        SDL_wcslcpy(videodata->ime_readingstring, s, len);
    } ಇಲ್ಲದಿದ್ದರೆ {
        LPINPUTCONTEXT2 lpimc = videodata->Imm_ಬೀಗ_IMC(himc);
        LPBYTE p = 0;
        s = 0;
        ಆಯ್ಕೆ (id) {
        ಸ್ಥಿತಿ IMEID_CHT_VER42:
        ಸ್ಥಿತಿ IMEID_CHT_VER43:
        ಸ್ಥಿತಿ IMEID_CHT_VER44:
            p = *(LPBYTE *)((LPBYTE)videodata->Imm_ಬೀಗ_IMCC(lpimc->h_ಖಾಸಗಿ) + 24);
            ಆದರೆ (!p) {
                ನಿಲ್ಲಿಸು;
            }

            len = *(DWORD *)(p + 7 * 4 + 32 * 4);
            s = (WCHAR *)(p + 56);
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ IMEID_CHT_VER51:
        ಸ್ಥಿತಿ IMEID_CHT_VER52:
        ಸ್ಥಿತಿ IMEID_CHS_VER53:
            p = *(LPBYTE *)((LPBYTE)videodata->Imm_ಬೀಗ_IMCC(lpimc->h_ಖಾಸಗಿ) + 4);
            ಆದರೆ (!p) {
                ನಿಲ್ಲಿಸು;
            }

            p = *(LPBYTE *)(p + 1 * 4 + 5 * 4);
            ಆದರೆ (!p) {
                ನಿಲ್ಲಿಸು;
            }

            len = *(DWORD *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4 + 16 * 2);
            s = (WCHAR *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4);
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ IMEID_CHS_VER41:
        {
            ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ_2 = (IME_GetId(videodata, 1) >= 0x00000002) ? 8 : 7;
            p = *(LPBYTE *)((LPBYTE)videodata->Imm_ಬೀಗ_IMCC(lpimc->h_ಖಾಸಗಿ) + ಸ್ಥಾನಾಂತರ_2 * 4);
            ಆದರೆ (!p) {
                ನಿಲ್ಲಿಸು;
            }

            len = *(DWORD *)(p + 7 * 4 + 16 * 2 * 4);
            s = (WCHAR *)(p + 6 * 4 + 16 * 2 * 1);
        } ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ IMEID_CHS_VER42:
            p = *(LPBYTE *)((LPBYTE)videodata->Imm_ಬೀಗ_IMCC(lpimc->h_ಖಾಸಗಿ) + 1 * 4 + 1 * 4 + 6 * 4);
            ಆದರೆ (!p) {
                ನಿಲ್ಲಿಸು;
            }

            len = *(DWORD *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4 + 16 * 2);
            s = (WCHAR *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4);
            ನಿಲ್ಲಿಸು;
        }
        ಆದರೆ (s) {
            size_t ಗಾತ್ರ_2 = SDL_min((size_t)(len + 1), SDL_arraysize(videodata->ime_readingstring));
            SDL_wcslcpy(videodata->ime_readingstring, s, ಗಾತ್ರ_2);
        }

        videodata->ImmUnlockIMCC(lpimc->h_ಖಾಸಗಿ);
        videodata->ImmUnlockIMC(himc);
    }
    ImmReleaseContext(hwnd, himc);
    IME_SendEditingEvent(videodata);
}

ಸ್ಥಿರ ಶೂನ್ಯ IME_ಒಳಹರಿವು_Lang_ಬದಲಾಯಿತು(SDL_Video_ದತ್ತಾಂಶ *videodata)
{
    UINT lang = PRIMLANG();
    IME_Update_ಒಳಹರಿವು_Locale(videodata);

    IME_ಸಿದ್ಧತೆ_API(videodata);
    ಆದರೆ (lang != PRIMLANG()) {
        IME_ClearComposition(videodata);
    }
}

ಸ್ಥಿರ DWORD IME_GetId(SDL_Video_ದತ್ತಾಂಶ *videodata, UINT u_ಸೂಚ್ಯಂಕ)
{
    ಸ್ಥಿರ HKL hklprev = 0;
    ಸ್ಥಿರ DWORD dwRet[2] = { 0 };
    DWORD dw_Ver_ಗಾತ್ರ = 0;
    LPVOID lp_Ver_ಬಫರ್ = 0;
    LPVOID lp_Ver_ದತ್ತಾಂಶ = 0;
    UINT cb_Ver_ದತ್ತಾಂಶ = 0;
    ಅಕ್ಷರ sz_ತಾತ್ಕಾಲಿಕ[256];
    HKL hkl = 0;
    DWORD dwLang = 0;
    SDL_assert(u_ಸೂಚ್ಯಂಕ < SDL_arraysize(dwRet));

    hkl = videodata->ime_hkl;
    ಆದರೆ (hklprev == hkl) {
        ಹಿಂತಿರುಗಿ dwRet[u_ಸೂಚ್ಯಂಕ];
    }
    hklprev = hkl;

    SDL_assert(u_ಸೂಚ್ಯಂಕ == 0);
    dwLang = ((DWORD_PTR)hkl & 0xffff);
    // FIXME: What does this do?
    ಆದರೆ (videodata->ime_ಆಂತರಿಕ_candidates && dwLang == LANG_CHT) {
        dwRet[0] = IMEID_CHT_VER_VISTA;
        dwRet[1] = 0;
        ಹಿಂತಿರುಗಿ dwRet[0];
    }
    ಆದರೆ (hkl != CHT_HKL_NEW_PHONETIC && hkl != CHT_HKL_NEW_CHANG_JIE && hkl != CHT_HKL_NEW_ಶೀಘ್ರ && hkl != CHT_HKL_HK_CANTONESE && hkl != CHS_HKL) {
        dwRet[0] = dwRet[1] = 0;
        ಹಿಂತಿರುಗಿ dwRet[0];
    }
    ಆದರೆ (!ImmGetIMEFileNameA(hkl, sz_ತಾತ್ಕಾಲಿಕ, ಗಾತ್ರ(sz_ತಾತ್ಕಾಲಿಕ) - 1)) {
        dwRet[0] = dwRet[1] = 0;
        ಹಿಂತಿರುಗಿ dwRet[0];
    }
    ಆದರೆ (!videodata->GetReadingString) {
#ವ್ಯಾಖ್ಯಾನಿಸು LCID_INVARIANT MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), ವಿಂಗಡಿಸು_DEFAULT)
        ಆದರೆ (CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_ತಾತ್ಕಾಲಿಕ, -1, CHT_IMEFILENAME1, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_ತಾತ್ಕಾಲಿಕ, -1, CHT_IMEFILENAME2, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_ತಾತ್ಕಾಲಿಕ, -1, CHT_IMEFILENAME3, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_ತಾತ್ಕಾಲಿಕ, -1, CHS_IMEFILENAME1, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_ತಾತ್ಕಾಲಿಕ, -1, CHS_IMEFILENAME2, -1) != 2) {
            dwRet[0] = dwRet[1] = 0;
            ಹಿಂತಿರುಗಿ dwRet[0];
        }
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LCID_INVARIANT
        dw_Ver_ಗಾತ್ರ = Get_File_ಆವೃತ್ತಿ_Info_ಗಾತ್ರ_A(sz_ತಾತ್ಕಾಲಿಕ, ಖಾಲಿ);
        ಆದರೆ (dw_Ver_ಗಾತ್ರ) {
            lp_Ver_ಬಫರ್ = SDL_malloc(dw_Ver_ಗಾತ್ರ);
            ಆದರೆ (lp_Ver_ಬಫರ್) {
                ಆದರೆ (Get_File_ಆವೃತ್ತಿ_Info_A(sz_ತಾತ್ಕಾಲಿಕ, 0, dw_Ver_ಗಾತ್ರ, lp_Ver_ಬಫರ್)) {
                    ಆದರೆ (Ver_Query_ಮೌಲ್ಯ_A(lp_Ver_ಬಫರ್, "\\", &lp_Ver_ದತ್ತಾಂಶ, &cb_Ver_ದತ್ತಾಂಶ)) {
#ವ್ಯಾಖ್ಯಾನಿಸು pVerFixedInfo ((VS_FIXEDFILEINFO FAR *)lp_Ver_ದತ್ತಾಂಶ)
                        DWORD dwVer = pVerFixedInfo->dw_File_ಆವೃತ್ತಿ_MS;
                        dwVer = (dwVer & 0x00ff0000) << 8 | (dwVer & 0x000000ff) << 16;
                        ಆದರೆ ((videodata->GetReadingString) ||
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
                            dwRet[1] = pVerFixedInfo->dw_File_ಆವೃತ್ತಿ_LS;
                            SDL_free(lp_Ver_ಬಫರ್);
                            ಹಿಂತಿರುಗಿ dwRet[0];
                        }
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು pVerFixedInfo
                    }
                }
            }
            SDL_free(lp_Ver_ಬಫರ್);
        }
    }
    dwRet[0] = dwRet[1] = 0;
    ಹಿಂತಿರುಗಿ dwRet[0];
}

ಸ್ಥಿರ ಶೂನ್ಯ IME_ಸಿದ್ಧತೆ_API(SDL_Video_ದತ್ತಾಂಶ *videodata)
{
    ಅಕ್ಷರ ime_file[MAX_ಮಾರ್ಗ + 1];
    SDL_SharedObject *hime = 0;
    HKL hkl = 0;
    videodata->GetReadingString = ಖಾಲಿ;
    videodata->Show_Reading_ಕಿಟಕಿ = ಖಾಲಿ;

    hkl = videodata->ime_hkl;
    ಆದರೆ (!ImmGetIMEFileNameA(hkl, ime_file, ಗಾತ್ರ(ime_file) - 1)) {
        ಹಿಂತಿರುಗಿ;
    }

    hime = SDL_ತುಂಬು_Object(ime_file);
    ಆದರೆ (!hime) {
        ಹಿಂತಿರುಗಿ;
    }

    /* *INDENT-OFF* */ // clang-format off
    videodata->GetReadingString = (UINT (WINAPI *)(HIMC, UINT, LPWSTR, PINT, BOOL*, PUINT))
        SDL_ತುಂಬು_Function(hime, "GetReadingString");
    videodata->Show_Reading_ಕಿಟಕಿ = (BOOL (WINAPI *)(HIMC, BOOL))
        SDL_ತುಂಬು_Function(hime, "ShowReadingWindow");
    /* *INDENT-ON* */ // clang-format on

    ಆದರೆ (videodata->Show_Reading_ಕಿಟಕಿ) {
        HIMC himc = ImmGetContext(videodata->ime_hwnd_current);
        ಆದರೆ (himc) {
            videodata->Show_Reading_ಕಿಟಕಿ(himc, FALSE);
            ImmReleaseContext(videodata->ime_hwnd_current, himc);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ IME_ಗಣ_ಕಿಟಕಿ(SDL_Video_ದತ್ತಾಂಶ *videodata, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    HWND hwnd = ಕಿಟಕಿ->ಆಂತರಿಕ->hwnd;

    ಆದರೆ (hwnd != videodata->ime_hwnd_current) {
        videodata->ime_hwnd_current = hwnd;
        SDL_zero(videodata->ime_composition_area);
        SDL_zero(videodata->ime_candidate_area);
    }

    IME_ಗಣ_ಪಠ್ಯ_ಒಳಹರಿವು_Area(videodata, hwnd, &ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_rect, ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_cursor);
}

#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಶೂನ್ಯ IME_ಗಣ_ಪಠ್ಯ_ಒಳಹರಿವು_Area(SDL_Video_ದತ್ತಾಂಶ *videodata, HWND hwnd, ಸ್ಥಿರಾಂಕ SDL_Rect *rect, ಪೂರ್ಣಾಂಕ cursor)
{
    HIMC himc;

    himc = ImmGetContext(hwnd);
    ಆದರೆ (himc) {
        COMPOSITIONFORM cof;
        CANDIDATEFORM caf;
        ಪೂರ್ಣಾಂಕ font_ಎತ್ತರ = rect->h;

        LOGFONTW font;
        ಆದರೆ (ImmGetCompositionFontW(himc, &font)) {
            font_ಎತ್ತರ = font.lf_ಎತ್ತರ;
        }

        SDL_zero(cof);
        cof.dwStyle = CFS_RECT;
        cof.ptCurrentPos.x = rect->x + cursor;
        cof.ptCurrentPos.y = rect->y + (rect->h - font_ಎತ್ತರ) / 2;
        cof.rcArea.ಎಡ = rect->x;
        cof.rcArea.ಬಲ = (LONG)rect->x + rect->w;
        cof.rcArea.ತುದಿ = rect->y;
        cof.rcArea.bottom = (LONG)rect->y + rect->h;
        ಆದರೆ (SDL_memcmp(&cof, &videodata->ime_composition_area, ಗಾತ್ರ(cof)) != 0) {
            SDL_copyp(&videodata->ime_composition_area, &cof);
            Imm_ಗಣ_Composition_ಕಿಟಕಿ(himc, &cof);
        }

        SDL_zero(caf);
        caf.dw_ಸೂಚ್ಯಂಕ = 0;
        caf.dwStyle = CFS_EXCLUDE;
        caf.ptCurrentPos.x = rect->x + cursor;
        caf.ptCurrentPos.y = rect->y;
        caf.rcArea.ಎಡ = rect->x;
        caf.rcArea.ಬಲ = (LONG)rect->x + rect->w;
        caf.rcArea.ತುದಿ = rect->y;
        caf.rcArea.bottom = (LONG)rect->y + rect->h;
        ಆದರೆ (SDL_memcmp(&caf, &videodata->ime_candidate_area, ಗಾತ್ರ(caf)) != 0) {
            SDL_copyp(&videodata->ime_candidate_area, &caf);
            Imm_ಗಣ_Candidate_ಕಿಟಕಿ(himc, &caf);
        }

        ImmReleaseContext(hwnd, himc);
    }
}

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_DISABLE_WINDOWS_IME

ಸ್ಥಿರ ಶೂನ್ಯ IME_Update_ಒಳಹರಿವು_Locale(SDL_Video_ದತ್ತಾಂಶ *videodata)
{
    HKL hklnext = GetKeyboardLayout(0);

    ಆದರೆ (hklnext == videodata->ime_hkl) {
        ಹಿಂತಿರುಗಿ;
    }

    videodata->ime_hkl = hklnext;
    videodata->ime_horizontal_candidates = (PRIMLANG() == LANG_KOREAN || LANG() == LANG_CHS);
    videodata->ime_candlistindexbase = (videodata->ime_hkl == CHT_HKL_DAYI) ? 0 : 1;
}

ಸ್ಥಿರ ಶೂನ್ಯ IME_ClearComposition(SDL_Video_ದತ್ತಾಂಶ *videodata)
{
    HIMC himc = 0;
    ಆದರೆ (!videodata->ime_initialized) {
        ಹಿಂತಿರುಗಿ;
    }

    himc = ImmGetContext(videodata->ime_hwnd_current);
    ಆದರೆ (!himc) {
        ಹಿಂತಿರುಗಿ;
    }

    ImmNotifyIME(himc, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
    Imm_ಗಣ_Composition_String(himc, SCS_SETSTR, ಪಠ್ಯ_2(""), ಗಾತ್ರ(TCHAR), ಪಠ್ಯ_2(""), ಗಾತ್ರ(TCHAR));

    ImmNotifyIME(himc, NI_CLOSECANDIDATE, 0, 0);
    ImmReleaseContext(videodata->ime_hwnd_current, himc);
    IME_SendClearComposition(videodata);
}

ಸ್ಥಿರ ಶೂನ್ಯ IME_GetCompositionString(SDL_Video_ದತ್ತಾಂಶ *videodata, HIMC himc, LPARAM *lParam, DWORD string)
{
    LONG ಉದ್ದಳತೆ;
    DWORD dwLang = ((DWORD_PTR)videodata->ime_hkl & 0xffff);

    ಆದರೆ (*lParam & GCS_CURSORPOS) {
        videodata->ime_cursor = LOWORD(ImmGetCompositionStringW(himc, GCS_CURSORPOS, 0, 0));
    }
    videodata->ime_selected_ಆರಂಭ = 0;
    videodata->ime_selected_ಉದ್ದಳತೆ = 0;
    SDL_DebugIMELog("Cursor = %d", videodata->ime_cursor);

    ಉದ್ದಳತೆ = ImmGetCompositionStringW(himc, string, ಖಾಲಿ, 0);
    ಆದರೆ (ಉದ್ದಳತೆ > 0 && videodata->ime_composition_ಉದ್ದಳತೆ < ಉದ್ದಳತೆ) {
        SDL_free(videodata->ime_composition);

        videodata->ime_composition = (WCHAR *)SDL_malloc(ಉದ್ದಳತೆ + ಗಾತ್ರ(WCHAR));
        videodata->ime_composition_ಉದ್ದಳತೆ = ಉದ್ದಳತೆ;
    }

    ಉದ್ದಳತೆ = ImmGetCompositionStringW(himc, string, videodata->ime_composition, videodata->ime_composition_ಉದ್ದಳತೆ);
    ಆದರೆ (ಉದ್ದಳತೆ < 0) {
        ಉದ್ದಳತೆ = 0;
    }
    ಉದ್ದಳತೆ /= ಗಾತ್ರ(WCHAR);

    ಆದರೆ (!(*lParam & GCS_CURSORPOS)) {
        // If the IME doesn't support GCS_CURSORPOS, default the cursor to the end of the composition.
        videodata->ime_cursor = ಉದ್ದಳತೆ;
    }

    ಆದರೆ ((dwLang == LANG_CHT || dwLang == LANG_CHS) &&
        videodata->ime_cursor > 0 &&
        videodata->ime_cursor < (ಪೂರ್ಣಾಂಕ)(videodata->ime_composition_ಉದ್ದಳತೆ / ಗಾತ್ರ(WCHAR)) &&
        (videodata->ime_composition[0] == 0x3000 || videodata->ime_composition[0] == 0x0020)) {
        // Traditional Chinese IMEs add a placeholder U+3000
        // Simplified Chinese IMEs seem to add a placeholder U+0020 sometimes
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = videodata->ime_cursor + 1; i < ಉದ್ದಳತೆ; ++i) {
            videodata->ime_composition[i - 1] = videodata->ime_composition[i];
        }
        --ಉದ್ದಳತೆ;
    }

    videodata->ime_composition[ಉದ್ದಳತೆ] = 0;

    ಉದ್ದಳತೆ = ImmGetCompositionStringW(himc, GCS_COMPATTR, ಖಾಲಿ, 0);
    ಆದರೆ (ಉದ್ದಳತೆ > 0) {
        Uint8 *ಗುಣಲಕ್ಷಣಗಳು = (Uint8 *)SDL_malloc(ಉದ್ದಳತೆ);
        ಆದರೆ (ಗುಣಲಕ್ಷಣಗಳು) {
            ಪೂರ್ಣಾಂಕ ಆರಂಭ = 0;
            ಪೂರ್ಣಾಂಕ ಕೊನೆ = 0;

            ಉದ್ದಳತೆ = ImmGetCompositionString(himc, GCS_COMPATTR, ಗುಣಲಕ್ಷಣಗಳು, ಉದ್ದಳತೆ);
            ಆದರೆ (ಉದ್ದಳತೆ < 0) {
                ಉದ್ದಳತೆ = 0;
            }

            ಗಾಗಿ (LONG i = 0; i < ಉದ್ದಳತೆ; ++i) {
                SDL_DebugIMELog("attrib[%d] = %d", i, ಗುಣಲಕ್ಷಣಗಳು[i]);
            }

            ಗಾಗಿ (ಆರಂಭ = 0; ಆರಂಭ < ಉದ್ದಳತೆ; ++ಆರಂಭ) {
                ಆದರೆ (ಗುಣಲಕ್ಷಣಗಳು[ಆರಂಭ] == ATTR_ಗುರಿ_CONVERTED || ಗುಣಲಕ್ಷಣಗಳು[ಆರಂಭ] == ATTR_ಗುರಿ_NOTCONVERTED) {
                    ನಿಲ್ಲಿಸು;
                }
            }

            ಗಾಗಿ (ಕೊನೆ = ಆರಂಭ; ಕೊನೆ < ಉದ್ದಳತೆ; ++ಕೊನೆ) {
                ಆದರೆ (ಗುಣಲಕ್ಷಣಗಳು[ಕೊನೆ] != ATTR_ಗುರಿ_CONVERTED && ಗುಣಲಕ್ಷಣಗಳು[ಕೊನೆ] != ATTR_ಗುರಿ_NOTCONVERTED) {
                    ನಿಲ್ಲಿಸು;
                }
            }

            ಆದರೆ (ಕೊನೆ > ಆರಂಭ) {
                videodata->ime_selected_ಆರಂಭ = ಆರಂಭ;
                videodata->ime_selected_ಉದ್ದಳತೆ = ಕೊನೆ - ಆರಂಭ;
            }

            SDL_free(ಗುಣಲಕ್ಷಣಗಳು);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ IME_Send_ಒಳಹರಿವು_Event(SDL_Video_ದತ್ತಾಂಶ *videodata)
{
    ಅಕ್ಷರ *s = 0;
    s = WIN_String_ಗಮ್ಯ_UTF8_W(videodata->ime_composition);
    SDL_Send_Keyboard_ಪಠ್ಯ(s);
    SDL_free(s);

    videodata->ime_composition[0] = 0;
    videodata->ime_readingstring[0] = 0;
    videodata->ime_cursor = 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ IME_SendEditingEvent(SDL_Video_ದತ್ತಾಂಶ *videodata)
{
    ಅಕ್ಷರ *s = ಖಾಲಿ;
    WCHAR *ಬಫರ್_2 = ಖಾಲಿ;
    size_t ಗಾತ್ರ_2 = videodata->ime_composition_ಉದ್ದಳತೆ;
    ಆದರೆ (videodata->ime_readingstring[0]) {
        size_t len = SDL_min(SDL_wcslen(videodata->ime_composition), (size_t)videodata->ime_cursor);

        ಗಾತ್ರ_2 += ಗಾತ್ರ(videodata->ime_readingstring);
        ಬಫರ್_2 = (WCHAR *)SDL_malloc(ಗಾತ್ರ_2 + ಗಾತ್ರ(WCHAR));
        ಆದರೆ (!ಬಫರ್_2) {
            ಹಿಂತಿರುಗಿ;
        }
        ಬಫರ್_2[0] = 0;

        SDL_wcslcpy(ಬಫರ್_2, videodata->ime_composition, len + 1);
        SDL_wcslcat(ಬಫರ್_2, videodata->ime_readingstring, ಗಾತ್ರ_2);
        SDL_wcslcat(ಬಫರ್_2, &videodata->ime_composition[len], ಗಾತ್ರ_2);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಬಫರ್_2 = (WCHAR *)SDL_malloc(ಗಾತ್ರ_2 + ಗಾತ್ರ(WCHAR));
        ಆದರೆ (!ಬಫರ್_2) {
            ಹಿಂತಿರುಗಿ;
        }
        ಬಫರ್_2[0] = 0;
        SDL_wcslcpy(ಬಫರ್_2, videodata->ime_composition, ಗಾತ್ರ_2);
    }

    s = WIN_String_ಗಮ್ಯ_UTF8_W(ಬಫರ್_2);
    ಆದರೆ (s) {
        ಆದರೆ (videodata->ime_readingstring[0]) {
            SDL_Send_Editing_ಪಠ್ಯ(s, videodata->ime_cursor, (ಪೂರ್ಣಾಂಕ)SDL_wcslen(videodata->ime_readingstring));
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (videodata->ime_cursor == videodata->ime_selected_ಆರಂಭ) {
            SDL_Send_Editing_ಪಠ್ಯ(s, videodata->ime_selected_ಆರಂಭ, videodata->ime_selected_ಉದ್ದಳತೆ);
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_Send_Editing_ಪಠ್ಯ(s, videodata->ime_cursor, 0);
        }
        ಆದರೆ (*s) {
            videodata->ime_needs_clear_composition = true;
        }
        SDL_free(s);
    }
    SDL_free(ಬಫರ್_2);
}

ಸ್ಥಿರ ಶೂನ್ಯ IME_SendClearComposition(SDL_Video_ದತ್ತಾಂಶ *videodata)
{
    ಆದರೆ (videodata->ime_needs_clear_composition) {
        SDL_Send_Editing_ಪಠ್ಯ("", 0, 0);
        videodata->ime_needs_clear_composition = false;
    }
}

ಸ್ಥಿರ bool IME_OpenCandidateList(SDL_Video_ದತ್ತಾಂಶ *videodata)
{
    videodata->ime_candidates_open = true;
    videodata->ime_candcount = 0;
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ IME_ಕೂಡಿಸು_Candidate(SDL_Video_ದತ್ತಾಂಶ *videodata, UINT i, LPCWSTR candidate)
{
    ಆದರೆ (videodata->ime_candidates[i]) {
        SDL_free(videodata->ime_candidates[i]);
        videodata->ime_candidates[i] = ಖಾಲಿ;
    }

    SDL_COMPILE_ಸಮಯ_ASSERT(IME_CANDIDATE_INDEXING_REQUIRES, MAX_CANDLIST == 10);
    ಅಕ್ಷರ *candidate_utf8 = WIN_String_ಗಮ್ಯ_UTF8_W(candidate);
    SDL_asprintf(&videodata->ime_candidates[i], "%d %s", ((i + videodata->ime_candlistindexbase) % 10), candidate_utf8);
    SDL_free(candidate_utf8);

    videodata->ime_candcount = (i + 1);
}

ಸ್ಥಿರ ಶೂನ್ಯ IME_SendCandidateList(SDL_Video_ದತ್ತಾಂಶ *videodata)
{
    SDL_Send_Editing_ಪಠ್ಯ_Candidates(videodata->ime_candidates, videodata->ime_candcount, videodata->ime_candsel, videodata->ime_horizontal_candidates);
}

ಸ್ಥಿರ ಶೂನ್ಯ IME_CloseCandidateList(SDL_Video_ದತ್ತಾಂಶ *videodata)
{
    videodata->ime_candidates_open = false;

    ಆದರೆ (videodata->ime_candcount > 0) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < videodata->ime_candcount; ++i) {
            SDL_free(videodata->ime_candidates[i]);
            videodata->ime_candidates[i] = ಖಾಲಿ;
        }
        videodata->ime_candcount = 0;

        SDL_Send_Editing_ಪಠ್ಯ_Candidates(ಖಾಲಿ, 0, -1, false);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ IME_GetCandidateList(SDL_Video_ದತ್ತಾಂಶ *videodata, HWND hwnd)
{
    HIMC himc;
    DWORD ಗಾತ್ರ_2;
    LPCANDIDATELIST cand_list;
    bool has_candidates = false;

    himc = ImmGetContext(hwnd);
    ಆದರೆ (himc) {
        ಗಾತ್ರ_2 = ImmGetCandidateListW(himc, 0, ಖಾಲಿ, 0);
        ಆದರೆ (ಗಾತ್ರ_2 != 0) {
            cand_list = (LPCANDIDATELIST)SDL_malloc(ಗಾತ್ರ_2);
            ಆದರೆ (cand_list != ಖಾಲಿ) {
                ಗಾತ್ರ_2 = ImmGetCandidateListW(himc, 0, cand_list, ಗಾತ್ರ_2);
                ಆದರೆ (ಗಾತ್ರ_2 != 0) {
                    ಆದರೆ (IME_OpenCandidateList(videodata)) {
                        UINT i, j;
                        UINT ಪುಟ_ಆರಂಭ = 0;
                        UINT ಪುಟ_ಗಾತ್ರ = 0;

                        videodata->ime_candsel = cand_list->dwSelection;

                        ಆದರೆ (LANG() == LANG_CHS && IME_GetId(videodata, 0)) {
                            ಸ್ಥಿರಾಂಕ UINT maxcandchar = 18;
                            size_t cchars = 0;

                            ಗಾಗಿ (i = 0; i < cand_list->dw_ಎಣಿಕೆ; ++i) {
                                size_t len = SDL_wcslen((LPWSTR)((DWORD_PTR)cand_list + cand_list->dw_ಸ್ಥಾನಾಂತರ[i])) + 1;
                                ಆದರೆ (len + cchars > maxcandchar) {
                                    ಆದರೆ (i > cand_list->dwSelection) {
                                        ನಿಲ್ಲಿಸು;
                                    }

                                    ಪುಟ_ಆರಂಭ = i;
                                    cchars = len;
                                } ಇಲ್ಲದಿದ್ದರೆ {
                                    cchars += len;
                                }
                            }
                            ಪುಟ_ಗಾತ್ರ = i - ಪುಟ_ಆರಂಭ;
                        } ಇಲ್ಲದಿದ್ದರೆ {
                            ಪುಟ_ಗಾತ್ರ = SDL_min(cand_list->dw_ಪುಟ_ಗಾತ್ರ == 0 ? MAX_CANDLIST : cand_list->dw_ಪುಟ_ಗಾತ್ರ, MAX_CANDLIST);
                            ಪುಟ_ಆರಂಭ = (cand_list->dwSelection / ಪುಟ_ಗಾತ್ರ) * ಪುಟ_ಗಾತ್ರ;
                        }
                        ಗಾಗಿ (i = ಪುಟ_ಆರಂಭ, j = 0; (DWORD)i < cand_list->dw_ಎಣಿಕೆ && j < ಪುಟ_ಗಾತ್ರ; i++, j++) {
                            LPCWSTR candidate = (LPCWSTR)((DWORD_PTR)cand_list + cand_list->dw_ಸ್ಥಾನಾಂತರ[i]);
                            IME_ಕೂಡಿಸು_Candidate(videodata, j, candidate);
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

    ಆದರೆ (!has_candidates) {
        IME_CloseCandidateList(videodata);
    }
}

bool WIN_HandleIMEMessage(HWND hwnd, UINT ಸಂದೇಶ_2, WPARAM wParam, LPARAM *lParam, SDL_Video_ದತ್ತಾಂಶ *videodata)
{
    bool trap = false;
    HIMC himc = 0;

    ಆದರೆ (ಸಂದೇಶ_2 == WM_IME_SETCONTEXT) {
        SDL_DebugIMELog("WM_IME_SETCONTEXT");

        LPARAM element_ಮುಖವಾಡ;
        element_ಮುಖವಾಡ = ISC_SHOWUIALL;
        ಆದರೆ (videodata->ime_ಆಂತರಿಕ_composition) {
            element_ಮುಖವಾಡ &= ~ISC_SHOWUICOMPOSITIONWINDOW;
        }
        ಆದರೆ (videodata->ime_ಆಂತರಿಕ_candidates) {
            element_ಮುಖವಾಡ &= ~ISC_SHOWUIALLCANDIDATEWINDOW;
        }
        *lParam &= element_ಮುಖವಾಡ;

        ಹಿಂತಿರುಗಿ false;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಸಂದೇಶ_2 == WM_IME_STARTCOMPOSITION) {
        SDL_DebugIMELog("WM_IME_STARTCOMPOSITION");
        ಆದರೆ (videodata->ime_ಆಂತರಿಕ_composition) {
            videodata->ime_cursor = 0;
            // Windows may still display a composition dialog even with
            // ISC_SHOWUICOMPOSITIONWINDOW cleared, so trap the message
            // here to prevent that (even when the IME is disabled).
            ಹಿಂತಿರುಗಿ true;
        }
    }

    ಆದರೆ (!videodata->ime_initialized || !videodata->ime_ಲಭ್ಯ || !videodata->ime_enabled) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆಯ್ಕೆ (ಸಂದೇಶ_2) {
    ಸ್ಥಿತಿ WM_KEYDOWN:
        ಆದರೆ (wParam == VK_PROCESSKEY) {
            SDL_DebugIMELog("WM_KEYDOWN VK_PROCESSKEY");
            trap = true;
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_DebugIMELog("WM_KEYDOWN normal");
        }
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ WM_SYSKEYDOWN:
        ಆದರೆ (wParam == VK_PROCESSKEY) {
            SDL_DebugIMELog("WM_SYSKEYDOWN VK_PROCESSKEY");
            trap = true;
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_DebugIMELog("WM_SYSKEYDOWN normal");
        }
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ WM_INPUTLANGCHANGE:
        SDL_DebugIMELog("WM_INPUTLANGCHANGE");
        IME_ಒಳಹರಿವು_Lang_ಬದಲಾಯಿತು(videodata);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ WM_IME_COMPOSITION:
        SDL_DebugIMELog("WM_IME_COMPOSITION %x", lParam);
        ಆದರೆ (videodata->ime_ಆಂತರಿಕ_composition) {
            trap = true;
            himc = ImmGetContext(hwnd);
            ಆದರೆ (*lParam & GCS_RESULTSTR) {
                SDL_DebugIMELog("GCS_RESULTSTR");
                IME_GetCompositionString(videodata, himc, lParam, GCS_RESULTSTR);
                IME_SendClearComposition(videodata);
                IME_Send_ಒಳಹರಿವು_Event(videodata);
            }
            ಆದರೆ (*lParam & GCS_COMPSTR) {
                SDL_DebugIMELog("GCS_COMPSTR");
                videodata->ime_readingstring[0] = 0;
                IME_GetCompositionString(videodata, himc, lParam, GCS_COMPSTR);
                IME_SendEditingEvent(videodata);
            }
            ImmReleaseContext(hwnd, himc);
        }
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ WM_IME_ENDCOMPOSITION:
        SDL_DebugIMELog("WM_IME_ENDCOMPOSITION");
        ಆದರೆ (videodata->ime_ಆಂತರಿಕ_composition) {
            trap = true;
            videodata->ime_composition[0] = 0;
            videodata->ime_readingstring[0] = 0;
            videodata->ime_cursor = 0;
            videodata->ime_selected_ಆರಂಭ = 0;
            videodata->ime_selected_ಉದ್ದಳತೆ = 0;
            IME_SendClearComposition(videodata);
        }
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ WM_IME_NOTIFY:
        SDL_DebugIMELog("WM_IME_NOTIFY %x", wParam);
        ಆಯ್ಕೆ (wParam) {
        ಸ್ಥಿತಿ IMN_SETCOMPOSITIONWINDOW:
            SDL_DebugIMELog("IMN_SETCOMPOSITIONWINDOW");
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ IMN_SETCOMPOSITIONFONT:
            SDL_DebugIMELog("IMN_SETCOMPOSITIONFONT");
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ IMN_SETCANDIDATEPOS:
            SDL_DebugIMELog("IMN_SETCANDIDATEPOS");
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ IMN_SETCONVERSIONMODE:
        ಸ್ಥಿತಿ IMN_SETOPENSTATUS:
            SDL_DebugIMELog("%s", wParam == IMN_SETCONVERSIONMODE ? "IMN_SETCONVERSIONMODE" : "IMN_SETOPENSTATUS");
            IME_Update_ಒಳಹರಿವು_Locale(videodata);
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ IMN_OPENCANDIDATE:
        ಸ್ಥಿತಿ IMN_CHANGECANDIDATE:
            SDL_DebugIMELog("%s", wParam == IMN_OPENCANDIDATE ? "IMN_OPENCANDIDATE" : "IMN_CHANGECANDIDATE");
            ಆದರೆ (videodata->ime_ಆಂತರಿಕ_candidates) {
                trap = true;
                videodata->ime_update_candidates = true;
            }
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ IMN_CLOSECANDIDATE:
            SDL_DebugIMELog("IMN_CLOSECANDIDATE");
            ಆದರೆ (videodata->ime_ಆಂತರಿಕ_candidates) {
                trap = true;
                videodata->ime_update_candidates = false;
                IME_CloseCandidateList(videodata);
            }
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ IMN_ಖಾಸಗಿ:
        {
            DWORD dwId = IME_GetId(videodata, 0);
            SDL_DebugIMELog("IMN_PRIVATE %u", dwId);
            IME_GetReadingString(videodata, hwnd);
            ಆಯ್ಕೆ (dwId) {
            ಸ್ಥಿತಿ IMEID_CHT_VER42:
            ಸ್ಥಿತಿ IMEID_CHT_VER43:
            ಸ್ಥಿತಿ IMEID_CHT_VER44:
            ಸ್ಥಿತಿ IMEID_CHS_VER41:
            ಸ್ಥಿತಿ IMEID_CHS_VER42:
                ಆದರೆ (*lParam == 1 || *lParam == 2) {
                    trap = true;
                }

                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ IMEID_CHT_VER50:
            ಸ್ಥಿತಿ IMEID_CHT_VER51:
            ಸ್ಥಿತಿ IMEID_CHT_VER52:
            ಸ್ಥಿತಿ IMEID_CHT_VER60:
            ಸ್ಥಿತಿ IMEID_CHS_VER53:
                ಆದರೆ (*lParam == 16 || *lParam == 17 || *lParam == 26 || *lParam == 27 || *lParam == 28) {
                    trap = true;
                }
                ನಿಲ್ಲಿಸು;
            }
        } ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            trap = true;
            ನಿಲ್ಲಿಸು;
        }
        ನಿಲ್ಲಿಸು;
    }
    ಹಿಂತಿರುಗಿ trap;
}

ಶೂನ್ಯ WIN_UpdateIMECandidates(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;

    ಆದರೆ (videodata->ime_update_candidates) {
        IME_GetCandidateList(videodata, videodata->ime_hwnd_current);
        videodata->ime_update_candidates = false;
    }
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_DISABLE_WINDOWS_IME

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WINDOWS
