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

#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keyboard_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/scancodes_windows.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <imm.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <oleauto.h>

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_DISABLE_WINDOWS_IME
#ਜੇ 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_DebugIMELog SDL_Log
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_DebugIMELog(...)
#ਜੇ_ਅੰਤ
ਸਥਿਰ bool IME_Init(SDL_Video_ਅੰਕੜੇ *videodata, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਸਥਿਰ ਖਾਲੀ IME_Enable(SDL_Video_ਅੰਕੜੇ *videodata, HWND hwnd);
ਸਥਿਰ ਖਾਲੀ IME_Disable(SDL_Video_ਅੰਕੜੇ *videodata, HWND hwnd);
ਸਥਿਰ ਖਾਲੀ IME_ਸੈੱਟ_ਪਾਠ_ਨਿਵੇਸ਼_Area(SDL_Video_ਅੰਕੜੇ *videodata, HWND hwnd, ਅਚਲ SDL_Rect *rect, ਪੂਰਨ cursor);
ਸਥਿਰ ਖਾਲੀ IME_ClearComposition(SDL_Video_ਅੰਕੜੇ *videodata);
ਸਥਿਰ ਖਾਲੀ IME_GetCandidateList(SDL_Video_ਅੰਕੜੇ *videodata, HWND hwnd);
ਸਥਿਰ ਖਾਲੀ IME_Quit(SDL_Video_ਅੰਕੜੇ *videodata);
#ਨਹੀਂਤਾਂ
ਸਥਿਰ ਖਾਲੀ IME_ਸੈੱਟ_ਪਾਠ_ਨਿਵੇਸ਼_Area(SDL_Video_ਅੰਕੜੇ *videodata, HWND hwnd, ਅਚਲ SDL_Rect *rect, ਪੂਰਨ cursor);
#ਜੇ_ਅੰਤ // !SDL_DISABLE_WINDOWS_IME

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MAPVK_VK_ਮੰਜ਼ਿਲ_VSC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAPVK_VK_ਮੰਜ਼ਿਲ_VSC 0
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MAPVK_VSC_ਮੰਜ਼ਿਲ_VK
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAPVK_VSC_ਮੰਜ਼ਿਲ_VK 1
#ਜੇ_ਅੰਤ

/* Building keymaps is expensive, so keep a reasonably-sized LRU cache to
 * enable fast switching between commonly used ones.
 */
ਸਥਿਰ ਬਣਤਰ WIN_KeymapCache
{
    HKL keyboard_layout;
    SDL_Keymap *keymap;
} keymap_cache[4];

ਸਥਿਰ ਪੂਰਨ keymap_cache_ਮਾਪ;

ਸਥਿਰ SDL_Keymap *WIN_GetCachedKeymap(HKL layout)
{
    SDL_Keymap *keymap = ਨਿਰਾ;
    ਲਈ (ਪੂਰਨ i = 0; i < keymap_cache_ਮਾਪ; ++i) {
        ਜੇ (keymap_cache[i].keyboard_layout == layout) {
            keymap = keymap_cache[i].keymap;

            // Move the map to the front of the list.
            ਜੇ (i) {
                SDL_memmove(keymap_cache + 1, keymap_cache, ਆਕਾਰ(ਬਣਤਰ WIN_KeymapCache) * i);
                keymap_cache[0].keyboard_layout = layout;
                keymap_cache[0].keymap = keymap;
            }
            ਰੋਕੋ;
        }
    }
    ਵਾਪਸ keymap;
}

ਸਥਿਰ ਖਾਲੀ WIN_CacheKeymap(HKL layout, SDL_Keymap *keymap)
{
    // If the cache is full, evict the last keymap.
    ਜੇ (keymap_cache_ਮਾਪ == SDL_arraysize(keymap_cache)) {
        SDL_DestroyKeymap(keymap_cache[--keymap_cache_ਮਾਪ].keymap);
    }

    // Move all elements down by one.
    ਜੇ (keymap_cache_ਮਾਪ) {
        SDL_memmove(keymap_cache + 1, keymap_cache, ਆਕਾਰ(ਬਣਤਰ WIN_KeymapCache) * keymap_cache_ਮਾਪ);
    }

    keymap_cache[0].keyboard_layout = layout;
    keymap_cache[0].keymap = keymap;
    ++keymap_cache_ਮਾਪ;
}

ਸਥਿਰ SDL_Keymap *WIN_BuildKeymap(ਖਾਲੀ)
{
    SDL_Scancode scancode;
    BYTE keyboardState[256] = { 0 };
    WCHAR ਬਫਰ_2[16];
    ਅਚਲ SDL_Keymod mods[] = {
        SDL_KMOD_NONE,
        SDL_KMOD_ਖਿਸਕਾਓ,
        SDL_KMOD_CAPS,
        (SDL_KMOD_ਖਿਸਕਾਓ | SDL_KMOD_CAPS),
        SDL_KMOD_ਬਹੁਲਕ,
        (SDL_KMOD_ਬਹੁਲਕ | SDL_KMOD_ਖਿਸਕਾਓ),
        (SDL_KMOD_ਬਹੁਲਕ | SDL_KMOD_CAPS),
        (SDL_KMOD_ਬਹੁਲਕ | SDL_KMOD_ਖਿਸਕਾਓ | SDL_KMOD_CAPS)
    };

    WIN_Reset_Dead_ਕੁੰਜੀਆਂ();

    SDL_Keymap *keymap = SDL_CreateKeymap(false);
    ਜੇ (!keymap) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਲਈ (ਪੂਰਨ m = 0; m < SDL_arraysize(mods); ++m) {
        ਲਈ (ਪੂਰਨ i = 0; i < SDL_arraysize(windows_scancode_ਸਾਰਣੀ); i++) {
            ਪੂਰਨ vk, sc, ਨਤੀਜਾ;
            Uint32 *ch = 0;

            // Make sure this scancode is a valid character scancode
            scancode = windows_scancode_ਸਾਰਣੀ[i];
            ਜੇ (scancode == SDL_SCANCODE_UNKNOWN ||
                scancode == SDL_SCANCODE_DELETE ||
                (SDL_GetKeymapKeycode(ਨਿਰਾ, scancode, SDL_KMOD_NONE) & SDLK_SCANCODE_ਨਕਾਬ)) {

                // The Colemak mapping swaps Backspace and CapsLock
                ਜੇ (mods[m] == SDL_KMOD_NONE &&
                    (scancode == SDL_SCANCODE_CAPSLOCK ||
                     scancode == SDL_SCANCODE_BACKSPACE)) {
                    vk = LOBYTE(Map_Virtual_ਕੁੰਜੀ(i, MAPVK_VSC_ਮੰਜ਼ਿਲ_VK));
                    ਜੇ (vk == VK_CAPITAL) {
                        SDL_ਸੈੱਟ_Keymap_ਇੰਦਰਾਜ(keymap, scancode, mods[m], SDLK_CAPSLOCK);
                    } ਨਹੀਂਤਾਂ ਜੇ (vk == VK_ਪਿੱਠ) {
                        SDL_ਸੈੱਟ_Keymap_ਇੰਦਰਾਜ(keymap, scancode, mods[m], SDLK_BACKSPACE);
                    }
                }
                ਜਾਰੀ;
            }

            // Unpack the single byte index to make the scan code.
            sc = MAKEWORD(i & 0x7f, (i & 0x80) ? 0xe0 : 0x00);
            vk = LOBYTE(Map_Virtual_ਕੁੰਜੀ(sc, MAPVK_VSC_ਮੰਜ਼ਿਲ_VK));
            ਜੇ (!vk) {
                ਜਾਰੀ;
            }

            // Update the keyboard state for the modifiers
            keyboardState[VK_ਖਿਸਕਾਓ] = (mods[m] & SDL_KMOD_ਖਿਸਕਾਓ) ? 0x80 : 0x00;
            keyboardState[VK_CAPITAL] = (mods[m] & SDL_KMOD_CAPS) ? 0x01 : 0x00;
            keyboardState[VK_CONTROL] = (mods[m] & SDL_KMOD_ਬਹੁਲਕ) ? 0x80 : 0x00;
            keyboardState[VK_MENU] = (mods[m] & SDL_KMOD_ਬਹੁਲਕ) ? 0x80 : 0x00;

            ਨਤੀਜਾ = ਮੰਜ਼ਿਲ_Unicode(vk, sc, keyboardState, ਬਫਰ_2, 16, 0);
            ਬਫਰ_2[SDL_abs(ਨਤੀਜਾ)] = 0;

            // Convert UTF-16 to UTF-32 code points
            ch = (Uint32 *)SDL_iconv_string("UTF-32LE", "UTF-16LE", (ਅਚਲ ਅੱਖਰ *)ਬਫਰ_2, (SDL_abs(ਨਤੀਜਾ) + 1) * ਆਕਾਰ(WCHAR));
            ਜੇ (ch) {
                /* Windows keyboard layouts can emit several UTF-32 code points on a single key press.
                 * Use <U+FFFD REPLACEMENT CHARACTER> since we cannot fit into single SDL_Keycode value in SDL keymap.
                 * See https://kbdlayout.info/features/ligatures for a list of such keys. */
                SDL_ਸੈੱਟ_Keymap_ਇੰਦਰਾਜ(keymap, scancode, mods[m], ch[1] == 0 ? ch[0] : 0xfffd);
                SDL_free(ch);
            } ਨਹੀਂਤਾਂ {
                // The default keymap doesn't have any SDL_KMOD_MODE entries, so we don't need to override them
                ਜੇ (!(mods[m] & SDL_KMOD_ਬਹੁਲਕ)) {
                    SDL_ਸੈੱਟ_Keymap_ਇੰਦਰਾਜ(keymap, scancode, mods[m], SDLK_UNKNOWN);
                }
            }

            ਜੇ (ਨਤੀਜਾ < 0) {
                WIN_Reset_Dead_ਕੁੰਜੀਆਂ();
            }
        }
    }

    ਵਾਪਸ keymap;
}

ਖਾਲੀ WIN_UpdateKeymap(bool send_event)
{
    HKL layout = GetKeyboardLayout(0);
    SDL_Keymap *keymap = WIN_GetCachedKeymap(layout);
    ਜੇ (!keymap) {
        keymap = WIN_BuildKeymap();
        ਜੇ (keymap) {
            WIN_CacheKeymap(layout, keymap);
        }
    }

    SDL_ਸੈੱਟ_Keymap(keymap, send_event);
}

// Alphabetic scancodes for PC keyboards
ਖਾਲੀ WIN_InitKeyboard(SDL_VideoDevice *_this)
{
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_DISABLE_WINDOWS_IME
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    ਅੰਕੜੇ->ime_candlistindexbase = 1;
    ਅੰਕੜੇ->ime_composition_ਲੰਮਾਈ = 32 * ਆਕਾਰ(WCHAR);
    ਅੰਕੜੇ->ime_composition = (WCHAR *)SDL_calloc(ਅੰਕੜੇ->ime_composition_ਲੰਮਾਈ, ਆਕਾਰ(WCHAR));
#ਜੇ_ਅੰਤ // !SDL_DISABLE_WINDOWS_IME

    // Build and bind the current keymap.
    WIN_UpdateKeymap(false);

    SDL_ਸੈੱਟ_Scancode_Name(SDL_SCANCODE_APPLICATION, "Menu");
    SDL_ਸੈੱਟ_Scancode_Name(SDL_SCANCODE_LGUI, "Left Windows");
    SDL_ਸੈੱਟ_Scancode_Name(SDL_SCANCODE_RGUI, "Right Windows");

    // Are system caps/num/scroll lock active? Set our state to match.
    SDL_ToggleModState(SDL_KMOD_CAPS, (Get_ਕੁੰਜੀ_State(VK_CAPITAL) & 0x0001) ? true : false);
    SDL_ToggleModState(SDL_KMOD_ਅੰਕ, (Get_ਕੁੰਜੀ_State(VK_NUMLOCK) & 0x0001) ? true : false);
    SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_ਕੁੰਜੀ_State(VK_SCROLL) & 0x0001) ? true : false);
}

ਖਾਲੀ WIN_QuitKeyboard(SDL_VideoDevice *_this)
{
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_DISABLE_WINDOWS_IME
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    IME_Quit(ਅੰਕੜੇ);

    ਜੇ (ਅੰਕੜੇ->ime_composition) {
        SDL_free(ਅੰਕੜੇ->ime_composition);
        ਅੰਕੜੇ->ime_composition = ਨਿਰਾ;
    }
#ਜੇ_ਅੰਤ // !SDL_DISABLE_WINDOWS_IME

    ਲਈ (ਪੂਰਨ i = 0; i < keymap_cache_ਮਾਪ; ++i) {
        SDL_DestroyKeymap(keymap_cache[i].keymap);
    }
    SDL_zeroa(keymap_cache);
    keymap_cache_ਮਾਪ = 0;
}

ਖਾਲੀ WIN_Reset_Dead_ਕੁੰਜੀਆਂ(ਖਾਲੀ)
{
    /*
    if a deadkey has been typed, but not the next character (which the deadkey might modify),
    this tries to undo the effect pressing the deadkey.
    see: http://archives.miloush.net/michkap/archive/2006/09/10/748775.html
    */
    BYTE keyboardState[256];
    WCHAR ਬਫਰ_2[16];
    ਪੂਰਨ vk, sc, ਨਤੀਜਾ, i;

    ਜੇ (!GetKeyboardState(keyboardState)) {
        ਵਾਪਸ;
    }

    vk = VK_SPACE;
    sc = Map_Virtual_ਕੁੰਜੀ(vk, MAPVK_VK_ਮੰਜ਼ਿਲ_VSC);
    ਜੇ (sc == 0) {
        // the keyboard doesn't have this key
        ਵਾਪਸ;
    }

    ਲਈ (i = 0; i < 5; i++) {
        ਨਤੀਜਾ = ਮੰਜ਼ਿਲ_Unicode(vk, sc, keyboardState, ਬਫਰ_2, 16, 0);
        ਜੇ (ਨਤੀਜਾ > 0) {
            // success
            ਵਾਪਸ;
        }
    }
}

bool WIN_ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID props)
{
    WIN_Reset_Dead_ਕੁੰਜੀਆਂ();

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_DISABLE_WINDOWS_IME
    HWND hwnd = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->hwnd;
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    IME_Init(videodata, ਖਿੜਕੀ);
    IME_Enable(videodata, hwnd);

    WIN_Update_ਪਾਠ_ਨਿਵੇਸ਼_Area(_this, ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ // !SDL_DISABLE_WINDOWS_IME

    ਵਾਪਸ true;
}

bool WIN_Stop_ਪਾਠ_ਨਿਵੇਸ਼(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    WIN_Reset_Dead_ਕੁੰਜੀਆਂ();

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_DISABLE_WINDOWS_IME
    HWND hwnd = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->hwnd;
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    IME_Init(videodata, ਖਿੜਕੀ);
    IME_Disable(videodata, hwnd);
#ਜੇ_ਅੰਤ // !SDL_DISABLE_WINDOWS_IME

    ਵਾਪਸ true;
}

bool WIN_Update_ਪਾਠ_ਨਿਵੇਸ਼_Area(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    IME_ਸੈੱਟ_ਪਾਠ_ਨਿਵੇਸ਼_Area(videodata, ਅੰਕੜੇ->hwnd, &ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_rect, ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_cursor);
    ਵਾਪਸ true;
}

bool WIN_ClearComposition(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_DISABLE_WINDOWS_IME
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;

    IME_ClearComposition(videodata);
#ਜੇ_ਅੰਤ
    ਵਾਪਸ true;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_DISABLE_WINDOWS_IME

bool WIN_HandleIMEMessage(HWND hwnd, UINT ਸੁਨੇਹਾ_2, WPARAM wParam, LPARAM *lParam, SDL_Video_ਅੰਕੜੇ *videodata)
{
    ਵਾਪਸ false;
}

ਖਾਲੀ WIN_UpdateIMECandidates(SDL_VideoDevice *_this)
{
    ਵਾਪਸ;
}

#ਨਹੀਂਤਾਂ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_CHT MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_TRADITIONAL)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_CHS MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAKEIMEVERSION(major, minor) ((DWORD)(((BYTE)(major) << 24) | ((BYTE)(minor) << 16)))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IMEID_VER(id)                ((id)&0xffff0000)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IMEID_LANG(id)               ((id)&0x0000ffff)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHT_HKL_DAYI          ((HKL)(UINT_PTR)0xE0060404)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHT_HKL_NEW_PHONETIC  ((HKL)(UINT_PTR)0xE0080404)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHT_HKL_NEW_CHANG_JIE ((HKL)(UINT_PTR)0xE0090404)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHT_HKL_NEW_ਤੇਜ਼     ((HKL)(UINT_PTR)0xE00A0404)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHT_HKL_HK_CANTONESE  ((HKL)(UINT_PTR)0xE00B0404)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHT_IMEFILENAME1      "TINTLGNT.IME"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHT_IMEFILENAME2      "CINTLGNT.IME"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHT_IMEFILENAME3      "MSTCIPHA.IME"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IMEID_CHT_VER42       (LANG_CHT | MAKEIMEVERSION(4, 2))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IMEID_CHT_VER43       (LANG_CHT | MAKEIMEVERSION(4, 3))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IMEID_CHT_VER44       (LANG_CHT | MAKEIMEVERSION(4, 4))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IMEID_CHT_VER50       (LANG_CHT | MAKEIMEVERSION(5, 0))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IMEID_CHT_VER51       (LANG_CHT | MAKEIMEVERSION(5, 1))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IMEID_CHT_VER52       (LANG_CHT | MAKEIMEVERSION(5, 2))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IMEID_CHT_VER60       (LANG_CHT | MAKEIMEVERSION(6, 0))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IMEID_CHT_VER_VISTA   (LANG_CHT | MAKEIMEVERSION(7, 0))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHS_HKL          ((HKL)(UINT_PTR)0xE00E0804)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHS_IMEFILENAME1 "PINTLGNT.IME"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHS_IMEFILENAME2 "MSSCIPYA.IME"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IMEID_CHS_VER41  (LANG_CHS | MAKEIMEVERSION(4, 1))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IMEID_CHS_VER42  (LANG_CHS | MAKEIMEVERSION(4, 2))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IMEID_CHS_VER53  (LANG_CHS | MAKEIMEVERSION(5, 3))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG()         LOWORD((videodata->ime_hkl))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PRIMLANG()     ((ਸ਼ਬਦ_2)PRIMARYLANGID(LANG()))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SUBLANG()      SUBLANGID(LANG())

ਸਥਿਰ ਖਾਲੀ IME_Update_ਨਿਵੇਸ਼_Locale(SDL_Video_ਅੰਕੜੇ *videodata);
ਸਥਿਰ ਖਾਲੀ IME_ਸੈੱਟ_ਖਿੜਕੀ(SDL_Video_ਅੰਕੜੇ *videodata, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਸਥਿਰ ਖਾਲੀ IME_ਤਿਆਰੀ_API(SDL_Video_ਅੰਕੜੇ *videodata);
ਸਥਿਰ DWORD IME_GetId(SDL_Video_ਅੰਕੜੇ *videodata, UINT u_ਸੂਚਕਾਂਕ);
ਸਥਿਰ ਖਾਲੀ IME_SendEditingEvent(SDL_Video_ਅੰਕੜੇ *videodata);
ਸਥਿਰ ਖਾਲੀ IME_SendClearComposition(SDL_Video_ਅੰਕੜੇ *videodata);

ਸਥਿਰ bool IME_Init(SDL_Video_ਅੰਕੜੇ *videodata, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    HWND hwnd = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->hwnd;

    ਜੇ (videodata->ime_initialized) {
        ਵਾਪਸ true;
    }

    ਅਚਲ ਅੱਖਰ *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);
    ਜੇ (hint && SDL_strstr(hint, "composition")) {
        videodata->ime_ਅੰਦਰੂਨੀ_composition = true;
    }
    ਜੇ (hint && SDL_strstr(hint, "candidates")) {
        videodata->ime_ਅੰਦਰੂਨੀ_candidates = true;
    }

    videodata->ime_hwnd_main = hwnd;
    videodata->ime_initialized = true;
    videodata->ime_himm32 = SDL_ਲੱਦੋ_Object("imm32.dll");
    ਜੇ (!videodata->ime_himm32) {
        videodata->ime_ਉਪਲਬਧ = false;
        SDL_ClearError();
        ਵਾਪਸ true;
    }
    /* *INDENT-OFF* */ // clang-format off
    videodata->Imm_ਤਾਲਾ_IMC = (LPINPUTCONTEXT2 (WINAPI *)(HIMC))SDL_ਲੱਦੋ_Function(videodata->ime_himm32, "ImmLockIMC");
    videodata->ImmUnlockIMC = (BOOL (WINAPI *)(HIMC))SDL_ਲੱਦੋ_Function(videodata->ime_himm32, "ImmUnlockIMC");
    videodata->Imm_ਤਾਲਾ_IMCC = (LPVOID (WINAPI *)(HIMCC))SDL_ਲੱਦੋ_Function(videodata->ime_himm32, "ImmLockIMCC");
    videodata->ImmUnlockIMCC = (BOOL (WINAPI *)(HIMCC))SDL_ਲੱਦੋ_Function(videodata->ime_himm32, "ImmUnlockIMCC");
    /* *INDENT-ON* */ // clang-format on

    IME_ਸੈੱਟ_ਖਿੜਕੀ(videodata, ਖਿੜਕੀ);
    videodata->ime_himc = ImmGetContext(hwnd);
    ImmReleaseContext(hwnd, videodata->ime_himc);
    ਜੇ (!videodata->ime_himc) {
        videodata->ime_ਉਪਲਬਧ = false;
        IME_Disable(videodata, hwnd);
        ਵਾਪਸ true;
    }
    videodata->ime_ਉਪਲਬਧ = true;
    IME_Update_ਨਿਵੇਸ਼_Locale(videodata);
    IME_ਤਿਆਰੀ_API(videodata);
    IME_Update_ਨਿਵੇਸ਼_Locale(videodata);
    IME_Disable(videodata, hwnd);
    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ IME_Enable(SDL_Video_ਅੰਕੜੇ *videodata, HWND hwnd)
{
    ਜੇ (!videodata->ime_initialized || !videodata->ime_hwnd_current) {
        ਵਾਪਸ;
    }

    ਜੇ (!videodata->ime_ਉਪਲਬਧ) {
        IME_Disable(videodata, hwnd);
        ਵਾਪਸ;
    }
    ਜੇ (videodata->ime_hwnd_current == videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_current, videodata->ime_himc);
    }

    videodata->ime_enabled = true;
    IME_Update_ਨਿਵੇਸ਼_Locale(videodata);
}

ਸਥਿਰ ਖਾਲੀ IME_Disable(SDL_Video_ਅੰਕੜੇ *videodata, HWND hwnd)
{
    ਜੇ (!videodata->ime_initialized || !videodata->ime_hwnd_current) {
        ਵਾਪਸ;
    }

    IME_ClearComposition(videodata);
    ਜੇ (videodata->ime_hwnd_current == videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_current, (HIMC)0);
    }

    videodata->ime_enabled = false;
}

ਸਥਿਰ ਖਾਲੀ IME_Quit(SDL_Video_ਅੰਕੜੇ *videodata)
{
    ਜੇ (!videodata->ime_initialized) {
        ਵਾਪਸ;
    }

    ਜੇ (videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_main, videodata->ime_himc);
    }

    videodata->ime_hwnd_main = 0;
    videodata->ime_himc = 0;
    ਜੇ (videodata->ime_himm32) {
        SDL_UnloadObject(videodata->ime_himm32);
        videodata->ime_himm32 = 0;
    }
    ਲਈ (ਪੂਰਨ i = 0; i < videodata->ime_candcount; ++i) {
        SDL_free(videodata->ime_candidates[i]);
        videodata->ime_candidates[i] = ਨਿਰਾ;
    }
    videodata->ime_initialized = false;
}

ਸਥਿਰ ਖਾਲੀ IME_GetReadingString(SDL_Video_ਅੰਕੜੇ *videodata, HWND hwnd)
{
    DWORD id = 0;
    HIMC himc = 0;
    WCHAR ਬਫਰ_2[16];
    WCHAR *s = ਬਫਰ_2;
    DWORD len = 0;
    INT err = 0;
    BOOL vertical = FALSE;
    UINT maxuilen = 0;

    videodata->ime_readingstring[0] = 0;

    id = IME_GetId(videodata, 0);
    ਜੇ (!id) {
        ਵਾਪਸ;
    }

    himc = ImmGetContext(hwnd);
    ਜੇ (!himc) {
        ਵਾਪਸ;
    }

    ਜੇ (videodata->GetReadingString) {
        len = videodata->GetReadingString(himc, 0, 0, &err, &vertical, &maxuilen);
        ਜੇ (len) {
            ਜੇ (len > SDL_arraysize(ਬਫਰ_2)) {
                len = SDL_arraysize(ਬਫਰ_2);
            }

            len = videodata->GetReadingString(himc, len, s, &err, &vertical, &maxuilen);
        }
        SDL_wcslcpy(videodata->ime_readingstring, s, len);
    } ਨਹੀਂਤਾਂ {
        LPINPUTCONTEXT2 lpimc = videodata->Imm_ਤਾਲਾ_IMC(himc);
        LPBYTE p = 0;
        s = 0;
        ਚੋਣ (id) {
        ਹਾਲਤ IMEID_CHT_VER42:
        ਹਾਲਤ IMEID_CHT_VER43:
        ਹਾਲਤ IMEID_CHT_VER44:
            p = *(LPBYTE *)((LPBYTE)videodata->Imm_ਤਾਲਾ_IMCC(lpimc->h_ਨਿੱਜੀ) + 24);
            ਜੇ (!p) {
                ਰੋਕੋ;
            }

            len = *(DWORD *)(p + 7 * 4 + 32 * 4);
            s = (WCHAR *)(p + 56);
            ਰੋਕੋ;
        ਹਾਲਤ IMEID_CHT_VER51:
        ਹਾਲਤ IMEID_CHT_VER52:
        ਹਾਲਤ IMEID_CHS_VER53:
            p = *(LPBYTE *)((LPBYTE)videodata->Imm_ਤਾਲਾ_IMCC(lpimc->h_ਨਿੱਜੀ) + 4);
            ਜੇ (!p) {
                ਰੋਕੋ;
            }

            p = *(LPBYTE *)(p + 1 * 4 + 5 * 4);
            ਜੇ (!p) {
                ਰੋਕੋ;
            }

            len = *(DWORD *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4 + 16 * 2);
            s = (WCHAR *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4);
            ਰੋਕੋ;
        ਹਾਲਤ IMEID_CHS_VER41:
        {
            ਪੂਰਨ ਵਿੱਥ_2 = (IME_GetId(videodata, 1) >= 0x00000002) ? 8 : 7;
            p = *(LPBYTE *)((LPBYTE)videodata->Imm_ਤਾਲਾ_IMCC(lpimc->h_ਨਿੱਜੀ) + ਵਿੱਥ_2 * 4);
            ਜੇ (!p) {
                ਰੋਕੋ;
            }

            len = *(DWORD *)(p + 7 * 4 + 16 * 2 * 4);
            s = (WCHAR *)(p + 6 * 4 + 16 * 2 * 1);
        } ਰੋਕੋ;
        ਹਾਲਤ IMEID_CHS_VER42:
            p = *(LPBYTE *)((LPBYTE)videodata->Imm_ਤਾਲਾ_IMCC(lpimc->h_ਨਿੱਜੀ) + 1 * 4 + 1 * 4 + 6 * 4);
            ਜੇ (!p) {
                ਰੋਕੋ;
            }

            len = *(DWORD *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4 + 16 * 2);
            s = (WCHAR *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4);
            ਰੋਕੋ;
        }
        ਜੇ (s) {
            size_t ਮਾਪ = SDL_min((size_t)(len + 1), SDL_arraysize(videodata->ime_readingstring));
            SDL_wcslcpy(videodata->ime_readingstring, s, ਮਾਪ);
        }

        videodata->ImmUnlockIMCC(lpimc->h_ਨਿੱਜੀ);
        videodata->ImmUnlockIMC(himc);
    }
    ImmReleaseContext(hwnd, himc);
    IME_SendEditingEvent(videodata);
}

ਸਥਿਰ ਖਾਲੀ IME_ਨਿਵੇਸ਼_Lang_ਬਦਲਿਆ(SDL_Video_ਅੰਕੜੇ *videodata)
{
    UINT lang = PRIMLANG();
    IME_Update_ਨਿਵੇਸ਼_Locale(videodata);

    IME_ਤਿਆਰੀ_API(videodata);
    ਜੇ (lang != PRIMLANG()) {
        IME_ClearComposition(videodata);
    }
}

ਸਥਿਰ DWORD IME_GetId(SDL_Video_ਅੰਕੜੇ *videodata, UINT u_ਸੂਚਕਾਂਕ)
{
    ਸਥਿਰ HKL hklprev = 0;
    ਸਥਿਰ DWORD dwRet[2] = { 0 };
    DWORD dw_Ver_ਮਾਪ = 0;
    LPVOID lp_Ver_ਬਫਰ = 0;
    LPVOID lp_Ver_ਅੰਕੜੇ = 0;
    UINT cb_Ver_ਅੰਕੜੇ = 0;
    ਅੱਖਰ sz_ਆਰਜ਼ੀ[256];
    HKL hkl = 0;
    DWORD dwLang = 0;
    SDL_assert(u_ਸੂਚਕਾਂਕ < SDL_arraysize(dwRet));

    hkl = videodata->ime_hkl;
    ਜੇ (hklprev == hkl) {
        ਵਾਪਸ dwRet[u_ਸੂਚਕਾਂਕ];
    }
    hklprev = hkl;

    SDL_assert(u_ਸੂਚਕਾਂਕ == 0);
    dwLang = ((DWORD_PTR)hkl & 0xffff);
    // FIXME: What does this do?
    ਜੇ (videodata->ime_ਅੰਦਰੂਨੀ_candidates && dwLang == LANG_CHT) {
        dwRet[0] = IMEID_CHT_VER_VISTA;
        dwRet[1] = 0;
        ਵਾਪਸ dwRet[0];
    }
    ਜੇ (hkl != CHT_HKL_NEW_PHONETIC && hkl != CHT_HKL_NEW_CHANG_JIE && hkl != CHT_HKL_NEW_ਤੇਜ਼ && hkl != CHT_HKL_HK_CANTONESE && hkl != CHS_HKL) {
        dwRet[0] = dwRet[1] = 0;
        ਵਾਪਸ dwRet[0];
    }
    ਜੇ (!ImmGetIMEFileNameA(hkl, sz_ਆਰਜ਼ੀ, ਆਕਾਰ(sz_ਆਰਜ਼ੀ) - 1)) {
        dwRet[0] = dwRet[1] = 0;
        ਵਾਪਸ dwRet[0];
    }
    ਜੇ (!videodata->GetReadingString) {
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LCID_INVARIANT MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), ਛਾਂਟੋ_DEFAULT)
        ਜੇ (CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_ਆਰਜ਼ੀ, -1, CHT_IMEFILENAME1, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_ਆਰਜ਼ੀ, -1, CHT_IMEFILENAME2, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_ਆਰਜ਼ੀ, -1, CHT_IMEFILENAME3, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_ਆਰਜ਼ੀ, -1, CHS_IMEFILENAME1, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_ਆਰਜ਼ੀ, -1, CHS_IMEFILENAME2, -1) != 2) {
            dwRet[0] = dwRet[1] = 0;
            ਵਾਪਸ dwRet[0];
        }
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LCID_INVARIANT
        dw_Ver_ਮਾਪ = Get_File_ਸੰਸਕਰਣ_Info_ਮਾਪ_A(sz_ਆਰਜ਼ੀ, ਨਿਰਾ);
        ਜੇ (dw_Ver_ਮਾਪ) {
            lp_Ver_ਬਫਰ = SDL_malloc(dw_Ver_ਮਾਪ);
            ਜੇ (lp_Ver_ਬਫਰ) {
                ਜੇ (Get_File_ਸੰਸਕਰਣ_Info_A(sz_ਆਰਜ਼ੀ, 0, dw_Ver_ਮਾਪ, lp_Ver_ਬਫਰ)) {
                    ਜੇ (Ver_Query_ਮੁੱਲ_A(lp_Ver_ਬਫਰ, "\\", &lp_Ver_ਅੰਕੜੇ, &cb_Ver_ਅੰਕੜੇ)) {
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ pVerFixedInfo ((VS_FIXEDFILEINFO FAR *)lp_Ver_ਅੰਕੜੇ)
                        DWORD dwVer = pVerFixedInfo->dw_File_ਸੰਸਕਰਣ_MS;
                        dwVer = (dwVer & 0x00ff0000) << 8 | (dwVer & 0x000000ff) << 16;
                        ਜੇ ((videodata->GetReadingString) ||
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
                            dwRet[1] = pVerFixedInfo->dw_File_ਸੰਸਕਰਣ_LS;
                            SDL_free(lp_Ver_ਬਫਰ);
                            ਵਾਪਸ dwRet[0];
                        }
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ pVerFixedInfo
                    }
                }
            }
            SDL_free(lp_Ver_ਬਫਰ);
        }
    }
    dwRet[0] = dwRet[1] = 0;
    ਵਾਪਸ dwRet[0];
}

ਸਥਿਰ ਖਾਲੀ IME_ਤਿਆਰੀ_API(SDL_Video_ਅੰਕੜੇ *videodata)
{
    ਅੱਖਰ ime_file[MAX_ਰਸਤਾ + 1];
    SDL_SharedObject *hime = 0;
    HKL hkl = 0;
    videodata->GetReadingString = ਨਿਰਾ;
    videodata->Show_Reading_ਖਿੜਕੀ = ਨਿਰਾ;

    hkl = videodata->ime_hkl;
    ਜੇ (!ImmGetIMEFileNameA(hkl, ime_file, ਆਕਾਰ(ime_file) - 1)) {
        ਵਾਪਸ;
    }

    hime = SDL_ਲੱਦੋ_Object(ime_file);
    ਜੇ (!hime) {
        ਵਾਪਸ;
    }

    /* *INDENT-OFF* */ // clang-format off
    videodata->GetReadingString = (UINT (WINAPI *)(HIMC, UINT, LPWSTR, PINT, BOOL*, PUINT))
        SDL_ਲੱਦੋ_Function(hime, "GetReadingString");
    videodata->Show_Reading_ਖਿੜਕੀ = (BOOL (WINAPI *)(HIMC, BOOL))
        SDL_ਲੱਦੋ_Function(hime, "ShowReadingWindow");
    /* *INDENT-ON* */ // clang-format on

    ਜੇ (videodata->Show_Reading_ਖਿੜਕੀ) {
        HIMC himc = ImmGetContext(videodata->ime_hwnd_current);
        ਜੇ (himc) {
            videodata->Show_Reading_ਖਿੜਕੀ(himc, FALSE);
            ImmReleaseContext(videodata->ime_hwnd_current, himc);
        }
    }
}

ਸਥਿਰ ਖਾਲੀ IME_ਸੈੱਟ_ਖਿੜਕੀ(SDL_Video_ਅੰਕੜੇ *videodata, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    HWND hwnd = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->hwnd;

    ਜੇ (hwnd != videodata->ime_hwnd_current) {
        videodata->ime_hwnd_current = hwnd;
        SDL_zero(videodata->ime_composition_area);
        SDL_zero(videodata->ime_candidate_area);
    }

    IME_ਸੈੱਟ_ਪਾਠ_ਨਿਵੇਸ਼_Area(videodata, hwnd, &ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_rect, ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_cursor);
}

#ਜੇ_ਅੰਤ

ਸਥਿਰ ਖਾਲੀ IME_ਸੈੱਟ_ਪਾਠ_ਨਿਵੇਸ਼_Area(SDL_Video_ਅੰਕੜੇ *videodata, HWND hwnd, ਅਚਲ SDL_Rect *rect, ਪੂਰਨ cursor)
{
    HIMC himc;

    himc = ImmGetContext(hwnd);
    ਜੇ (himc) {
        COMPOSITIONFORM cof;
        CANDIDATEFORM caf;
        ਪੂਰਨ font_ਉਚਾਈ = rect->h;

        LOGFONTW font;
        ਜੇ (ImmGetCompositionFontW(himc, &font)) {
            font_ਉਚਾਈ = font.lf_ਉਚਾਈ;
        }

        SDL_zero(cof);
        cof.dwStyle = CFS_RECT;
        cof.ptCurrentPos.x = rect->x + cursor;
        cof.ptCurrentPos.y = rect->y + (rect->h - font_ਉਚਾਈ) / 2;
        cof.rcArea.ਖੱਬਾ = rect->x;
        cof.rcArea.ਸੱਜਾ = (LONG)rect->x + rect->w;
        cof.rcArea.ਸਿਖਰ = rect->y;
        cof.rcArea.bottom = (LONG)rect->y + rect->h;
        ਜੇ (SDL_memcmp(&cof, &videodata->ime_composition_area, ਆਕਾਰ(cof)) != 0) {
            SDL_copyp(&videodata->ime_composition_area, &cof);
            Imm_ਸੈੱਟ_Composition_ਖਿੜਕੀ(himc, &cof);
        }

        SDL_zero(caf);
        caf.dw_ਸੂਚਕਾਂਕ = 0;
        caf.dwStyle = CFS_EXCLUDE;
        caf.ptCurrentPos.x = rect->x + cursor;
        caf.ptCurrentPos.y = rect->y;
        caf.rcArea.ਖੱਬਾ = rect->x;
        caf.rcArea.ਸੱਜਾ = (LONG)rect->x + rect->w;
        caf.rcArea.ਸਿਖਰ = rect->y;
        caf.rcArea.bottom = (LONG)rect->y + rect->h;
        ਜੇ (SDL_memcmp(&caf, &videodata->ime_candidate_area, ਆਕਾਰ(caf)) != 0) {
            SDL_copyp(&videodata->ime_candidate_area, &caf);
            Imm_ਸੈੱਟ_Candidate_ਖਿੜਕੀ(himc, &caf);
        }

        ImmReleaseContext(hwnd, himc);
    }
}

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_DISABLE_WINDOWS_IME

ਸਥਿਰ ਖਾਲੀ IME_Update_ਨਿਵੇਸ਼_Locale(SDL_Video_ਅੰਕੜੇ *videodata)
{
    HKL hklnext = GetKeyboardLayout(0);

    ਜੇ (hklnext == videodata->ime_hkl) {
        ਵਾਪਸ;
    }

    videodata->ime_hkl = hklnext;
    videodata->ime_horizontal_candidates = (PRIMLANG() == LANG_KOREAN || LANG() == LANG_CHS);
    videodata->ime_candlistindexbase = (videodata->ime_hkl == CHT_HKL_DAYI) ? 0 : 1;
}

ਸਥਿਰ ਖਾਲੀ IME_ClearComposition(SDL_Video_ਅੰਕੜੇ *videodata)
{
    HIMC himc = 0;
    ਜੇ (!videodata->ime_initialized) {
        ਵਾਪਸ;
    }

    himc = ImmGetContext(videodata->ime_hwnd_current);
    ਜੇ (!himc) {
        ਵਾਪਸ;
    }

    ImmNotifyIME(himc, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
    Imm_ਸੈੱਟ_Composition_String(himc, SCS_SETSTR, ਪਾਠ_2(""), ਆਕਾਰ(TCHAR), ਪਾਠ_2(""), ਆਕਾਰ(TCHAR));

    ImmNotifyIME(himc, NI_CLOSECANDIDATE, 0, 0);
    ImmReleaseContext(videodata->ime_hwnd_current, himc);
    IME_SendClearComposition(videodata);
}

ਸਥਿਰ ਖਾਲੀ IME_GetCompositionString(SDL_Video_ਅੰਕੜੇ *videodata, HIMC himc, LPARAM *lParam, DWORD string)
{
    LONG ਲੰਮਾਈ;
    DWORD dwLang = ((DWORD_PTR)videodata->ime_hkl & 0xffff);

    ਜੇ (*lParam & GCS_CURSORPOS) {
        videodata->ime_cursor = LOWORD(ImmGetCompositionStringW(himc, GCS_CURSORPOS, 0, 0));
    }
    videodata->ime_selected_ਸ਼ੁਰੂ = 0;
    videodata->ime_selected_ਲੰਮਾਈ = 0;
    SDL_DebugIMELog("Cursor = %d", videodata->ime_cursor);

    ਲੰਮਾਈ = ImmGetCompositionStringW(himc, string, ਨਿਰਾ, 0);
    ਜੇ (ਲੰਮਾਈ > 0 && videodata->ime_composition_ਲੰਮਾਈ < ਲੰਮਾਈ) {
        SDL_free(videodata->ime_composition);

        videodata->ime_composition = (WCHAR *)SDL_malloc(ਲੰਮਾਈ + ਆਕਾਰ(WCHAR));
        videodata->ime_composition_ਲੰਮਾਈ = ਲੰਮਾਈ;
    }

    ਲੰਮਾਈ = ImmGetCompositionStringW(himc, string, videodata->ime_composition, videodata->ime_composition_ਲੰਮਾਈ);
    ਜੇ (ਲੰਮਾਈ < 0) {
        ਲੰਮਾਈ = 0;
    }
    ਲੰਮਾਈ /= ਆਕਾਰ(WCHAR);

    ਜੇ (!(*lParam & GCS_CURSORPOS)) {
        // If the IME doesn't support GCS_CURSORPOS, default the cursor to the end of the composition.
        videodata->ime_cursor = ਲੰਮਾਈ;
    }

    ਜੇ ((dwLang == LANG_CHT || dwLang == LANG_CHS) &&
        videodata->ime_cursor > 0 &&
        videodata->ime_cursor < (ਪੂਰਨ)(videodata->ime_composition_ਲੰਮਾਈ / ਆਕਾਰ(WCHAR)) &&
        (videodata->ime_composition[0] == 0x3000 || videodata->ime_composition[0] == 0x0020)) {
        // Traditional Chinese IMEs add a placeholder U+3000
        // Simplified Chinese IMEs seem to add a placeholder U+0020 sometimes
        ਲਈ (ਪੂਰਨ i = videodata->ime_cursor + 1; i < ਲੰਮਾਈ; ++i) {
            videodata->ime_composition[i - 1] = videodata->ime_composition[i];
        }
        --ਲੰਮਾਈ;
    }

    videodata->ime_composition[ਲੰਮਾਈ] = 0;

    ਲੰਮਾਈ = ImmGetCompositionStringW(himc, GCS_COMPATTR, ਨਿਰਾ, 0);
    ਜੇ (ਲੰਮਾਈ > 0) {
        Uint8 *ਗੁਣ = (Uint8 *)SDL_malloc(ਲੰਮਾਈ);
        ਜੇ (ਗੁਣ) {
            ਪੂਰਨ ਸ਼ੁਰੂ = 0;
            ਪੂਰਨ ਸਿਰਾ = 0;

            ਲੰਮਾਈ = ImmGetCompositionString(himc, GCS_COMPATTR, ਗੁਣ, ਲੰਮਾਈ);
            ਜੇ (ਲੰਮਾਈ < 0) {
                ਲੰਮਾਈ = 0;
            }

            ਲਈ (LONG i = 0; i < ਲੰਮਾਈ; ++i) {
                SDL_DebugIMELog("attrib[%d] = %d", i, ਗੁਣ[i]);
            }

            ਲਈ (ਸ਼ੁਰੂ = 0; ਸ਼ੁਰੂ < ਲੰਮਾਈ; ++ਸ਼ੁਰੂ) {
                ਜੇ (ਗੁਣ[ਸ਼ੁਰੂ] == ATTR_ਨਿਸ਼ਾਨਾ_CONVERTED || ਗੁਣ[ਸ਼ੁਰੂ] == ATTR_ਨਿਸ਼ਾਨਾ_NOTCONVERTED) {
                    ਰੋਕੋ;
                }
            }

            ਲਈ (ਸਿਰਾ = ਸ਼ੁਰੂ; ਸਿਰਾ < ਲੰਮਾਈ; ++ਸਿਰਾ) {
                ਜੇ (ਗੁਣ[ਸਿਰਾ] != ATTR_ਨਿਸ਼ਾਨਾ_CONVERTED && ਗੁਣ[ਸਿਰਾ] != ATTR_ਨਿਸ਼ਾਨਾ_NOTCONVERTED) {
                    ਰੋਕੋ;
                }
            }

            ਜੇ (ਸਿਰਾ > ਸ਼ੁਰੂ) {
                videodata->ime_selected_ਸ਼ੁਰੂ = ਸ਼ੁਰੂ;
                videodata->ime_selected_ਲੰਮਾਈ = ਸਿਰਾ - ਸ਼ੁਰੂ;
            }

            SDL_free(ਗੁਣ);
        }
    }
}

ਸਥਿਰ ਖਾਲੀ IME_Send_ਨਿਵੇਸ਼_Event(SDL_Video_ਅੰਕੜੇ *videodata)
{
    ਅੱਖਰ *s = 0;
    s = WIN_String_ਮੰਜ਼ਿਲ_UTF8_W(videodata->ime_composition);
    SDL_Send_Keyboard_ਪਾਠ(s);
    SDL_free(s);

    videodata->ime_composition[0] = 0;
    videodata->ime_readingstring[0] = 0;
    videodata->ime_cursor = 0;
}

ਸਥਿਰ ਖਾਲੀ IME_SendEditingEvent(SDL_Video_ਅੰਕੜੇ *videodata)
{
    ਅੱਖਰ *s = ਨਿਰਾ;
    WCHAR *ਬਫਰ_2 = ਨਿਰਾ;
    size_t ਮਾਪ = videodata->ime_composition_ਲੰਮਾਈ;
    ਜੇ (videodata->ime_readingstring[0]) {
        size_t len = SDL_min(SDL_wcslen(videodata->ime_composition), (size_t)videodata->ime_cursor);

        ਮਾਪ += ਆਕਾਰ(videodata->ime_readingstring);
        ਬਫਰ_2 = (WCHAR *)SDL_malloc(ਮਾਪ + ਆਕਾਰ(WCHAR));
        ਜੇ (!ਬਫਰ_2) {
            ਵਾਪਸ;
        }
        ਬਫਰ_2[0] = 0;

        SDL_wcslcpy(ਬਫਰ_2, videodata->ime_composition, len + 1);
        SDL_wcslcat(ਬਫਰ_2, videodata->ime_readingstring, ਮਾਪ);
        SDL_wcslcat(ਬਫਰ_2, &videodata->ime_composition[len], ਮਾਪ);
    } ਨਹੀਂਤਾਂ {
        ਬਫਰ_2 = (WCHAR *)SDL_malloc(ਮਾਪ + ਆਕਾਰ(WCHAR));
        ਜੇ (!ਬਫਰ_2) {
            ਵਾਪਸ;
        }
        ਬਫਰ_2[0] = 0;
        SDL_wcslcpy(ਬਫਰ_2, videodata->ime_composition, ਮਾਪ);
    }

    s = WIN_String_ਮੰਜ਼ਿਲ_UTF8_W(ਬਫਰ_2);
    ਜੇ (s) {
        ਜੇ (videodata->ime_readingstring[0]) {
            SDL_Send_Editing_ਪਾਠ(s, videodata->ime_cursor, (ਪੂਰਨ)SDL_wcslen(videodata->ime_readingstring));
        } ਨਹੀਂਤਾਂ ਜੇ (videodata->ime_cursor == videodata->ime_selected_ਸ਼ੁਰੂ) {
            SDL_Send_Editing_ਪਾਠ(s, videodata->ime_selected_ਸ਼ੁਰੂ, videodata->ime_selected_ਲੰਮਾਈ);
        } ਨਹੀਂਤਾਂ {
            SDL_Send_Editing_ਪਾਠ(s, videodata->ime_cursor, 0);
        }
        ਜੇ (*s) {
            videodata->ime_needs_clear_composition = true;
        }
        SDL_free(s);
    }
    SDL_free(ਬਫਰ_2);
}

ਸਥਿਰ ਖਾਲੀ IME_SendClearComposition(SDL_Video_ਅੰਕੜੇ *videodata)
{
    ਜੇ (videodata->ime_needs_clear_composition) {
        SDL_Send_Editing_ਪਾਠ("", 0, 0);
        videodata->ime_needs_clear_composition = false;
    }
}

ਸਥਿਰ bool IME_OpenCandidateList(SDL_Video_ਅੰਕੜੇ *videodata)
{
    videodata->ime_candidates_open = true;
    videodata->ime_candcount = 0;
    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ IME_ਜੋੜੋ_Candidate(SDL_Video_ਅੰਕੜੇ *videodata, UINT i, LPCWSTR candidate)
{
    ਜੇ (videodata->ime_candidates[i]) {
        SDL_free(videodata->ime_candidates[i]);
        videodata->ime_candidates[i] = ਨਿਰਾ;
    }

    SDL_COMPILE_ਸਮਾਂ_ASSERT(IME_CANDIDATE_INDEXING_REQUIRES, MAX_CANDLIST == 10);
    ਅੱਖਰ *candidate_utf8 = WIN_String_ਮੰਜ਼ਿਲ_UTF8_W(candidate);
    SDL_asprintf(&videodata->ime_candidates[i], "%d %s", ((i + videodata->ime_candlistindexbase) % 10), candidate_utf8);
    SDL_free(candidate_utf8);

    videodata->ime_candcount = (i + 1);
}

ਸਥਿਰ ਖਾਲੀ IME_SendCandidateList(SDL_Video_ਅੰਕੜੇ *videodata)
{
    SDL_Send_Editing_ਪਾਠ_Candidates(videodata->ime_candidates, videodata->ime_candcount, videodata->ime_candsel, videodata->ime_horizontal_candidates);
}

ਸਥਿਰ ਖਾਲੀ IME_CloseCandidateList(SDL_Video_ਅੰਕੜੇ *videodata)
{
    videodata->ime_candidates_open = false;

    ਜੇ (videodata->ime_candcount > 0) {
        ਲਈ (ਪੂਰਨ i = 0; i < videodata->ime_candcount; ++i) {
            SDL_free(videodata->ime_candidates[i]);
            videodata->ime_candidates[i] = ਨਿਰਾ;
        }
        videodata->ime_candcount = 0;

        SDL_Send_Editing_ਪਾਠ_Candidates(ਨਿਰਾ, 0, -1, false);
    }
}

ਸਥਿਰ ਖਾਲੀ IME_GetCandidateList(SDL_Video_ਅੰਕੜੇ *videodata, HWND hwnd)
{
    HIMC himc;
    DWORD ਮਾਪ;
    LPCANDIDATELIST cand_list;
    bool has_candidates = false;

    himc = ImmGetContext(hwnd);
    ਜੇ (himc) {
        ਮਾਪ = ImmGetCandidateListW(himc, 0, ਨਿਰਾ, 0);
        ਜੇ (ਮਾਪ != 0) {
            cand_list = (LPCANDIDATELIST)SDL_malloc(ਮਾਪ);
            ਜੇ (cand_list != ਨਿਰਾ) {
                ਮਾਪ = ImmGetCandidateListW(himc, 0, cand_list, ਮਾਪ);
                ਜੇ (ਮਾਪ != 0) {
                    ਜੇ (IME_OpenCandidateList(videodata)) {
                        UINT i, j;
                        UINT ਪੰਨਾ_ਸ਼ੁਰੂ = 0;
                        UINT ਪੰਨਾ_ਮਾਪ = 0;

                        videodata->ime_candsel = cand_list->dwSelection;

                        ਜੇ (LANG() == LANG_CHS && IME_GetId(videodata, 0)) {
                            ਅਚਲ UINT maxcandchar = 18;
                            size_t cchars = 0;

                            ਲਈ (i = 0; i < cand_list->dw_ਗਿਣਤੀ; ++i) {
                                size_t len = SDL_wcslen((LPWSTR)((DWORD_PTR)cand_list + cand_list->dw_ਵਿੱਥ[i])) + 1;
                                ਜੇ (len + cchars > maxcandchar) {
                                    ਜੇ (i > cand_list->dwSelection) {
                                        ਰੋਕੋ;
                                    }

                                    ਪੰਨਾ_ਸ਼ੁਰੂ = i;
                                    cchars = len;
                                } ਨਹੀਂਤਾਂ {
                                    cchars += len;
                                }
                            }
                            ਪੰਨਾ_ਮਾਪ = i - ਪੰਨਾ_ਸ਼ੁਰੂ;
                        } ਨਹੀਂਤਾਂ {
                            ਪੰਨਾ_ਮਾਪ = SDL_min(cand_list->dw_ਪੰਨਾ_ਮਾਪ == 0 ? MAX_CANDLIST : cand_list->dw_ਪੰਨਾ_ਮਾਪ, MAX_CANDLIST);
                            ਪੰਨਾ_ਸ਼ੁਰੂ = (cand_list->dwSelection / ਪੰਨਾ_ਮਾਪ) * ਪੰਨਾ_ਮਾਪ;
                        }
                        ਲਈ (i = ਪੰਨਾ_ਸ਼ੁਰੂ, j = 0; (DWORD)i < cand_list->dw_ਗਿਣਤੀ && j < ਪੰਨਾ_ਮਾਪ; i++, j++) {
                            LPCWSTR candidate = (LPCWSTR)((DWORD_PTR)cand_list + cand_list->dw_ਵਿੱਥ[i]);
                            IME_ਜੋੜੋ_Candidate(videodata, j, candidate);
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

    ਜੇ (!has_candidates) {
        IME_CloseCandidateList(videodata);
    }
}

bool WIN_HandleIMEMessage(HWND hwnd, UINT ਸੁਨੇਹਾ_2, WPARAM wParam, LPARAM *lParam, SDL_Video_ਅੰਕੜੇ *videodata)
{
    bool trap = false;
    HIMC himc = 0;

    ਜੇ (ਸੁਨੇਹਾ_2 == WM_IME_SETCONTEXT) {
        SDL_DebugIMELog("WM_IME_SETCONTEXT");

        LPARAM element_ਨਕਾਬ;
        element_ਨਕਾਬ = ISC_SHOWUIALL;
        ਜੇ (videodata->ime_ਅੰਦਰੂਨੀ_composition) {
            element_ਨਕਾਬ &= ~ISC_SHOWUICOMPOSITIONWINDOW;
        }
        ਜੇ (videodata->ime_ਅੰਦਰੂਨੀ_candidates) {
            element_ਨਕਾਬ &= ~ISC_SHOWUIALLCANDIDATEWINDOW;
        }
        *lParam &= element_ਨਕਾਬ;

        ਵਾਪਸ false;
    } ਨਹੀਂਤਾਂ ਜੇ (ਸੁਨੇਹਾ_2 == WM_IME_STARTCOMPOSITION) {
        SDL_DebugIMELog("WM_IME_STARTCOMPOSITION");
        ਜੇ (videodata->ime_ਅੰਦਰੂਨੀ_composition) {
            videodata->ime_cursor = 0;
            // Windows may still display a composition dialog even with
            // ISC_SHOWUICOMPOSITIONWINDOW cleared, so trap the message
            // here to prevent that (even when the IME is disabled).
            ਵਾਪਸ true;
        }
    }

    ਜੇ (!videodata->ime_initialized || !videodata->ime_ਉਪਲਬਧ || !videodata->ime_enabled) {
        ਵਾਪਸ false;
    }

    ਚੋਣ (ਸੁਨੇਹਾ_2) {
    ਹਾਲਤ WM_KEYDOWN:
        ਜੇ (wParam == VK_PROCESSKEY) {
            SDL_DebugIMELog("WM_KEYDOWN VK_PROCESSKEY");
            trap = true;
        } ਨਹੀਂਤਾਂ {
            SDL_DebugIMELog("WM_KEYDOWN normal");
        }
        ਰੋਕੋ;
    ਹਾਲਤ WM_SYSKEYDOWN:
        ਜੇ (wParam == VK_PROCESSKEY) {
            SDL_DebugIMELog("WM_SYSKEYDOWN VK_PROCESSKEY");
            trap = true;
        } ਨਹੀਂਤਾਂ {
            SDL_DebugIMELog("WM_SYSKEYDOWN normal");
        }
        ਰੋਕੋ;
    ਹਾਲਤ WM_INPUTLANGCHANGE:
        SDL_DebugIMELog("WM_INPUTLANGCHANGE");
        IME_ਨਿਵੇਸ਼_Lang_ਬਦਲਿਆ(videodata);
        ਰੋਕੋ;
    ਹਾਲਤ WM_IME_COMPOSITION:
        SDL_DebugIMELog("WM_IME_COMPOSITION %x", lParam);
        ਜੇ (videodata->ime_ਅੰਦਰੂਨੀ_composition) {
            trap = true;
            himc = ImmGetContext(hwnd);
            ਜੇ (*lParam & GCS_RESULTSTR) {
                SDL_DebugIMELog("GCS_RESULTSTR");
                IME_GetCompositionString(videodata, himc, lParam, GCS_RESULTSTR);
                IME_SendClearComposition(videodata);
                IME_Send_ਨਿਵੇਸ਼_Event(videodata);
            }
            ਜੇ (*lParam & GCS_COMPSTR) {
                SDL_DebugIMELog("GCS_COMPSTR");
                videodata->ime_readingstring[0] = 0;
                IME_GetCompositionString(videodata, himc, lParam, GCS_COMPSTR);
                IME_SendEditingEvent(videodata);
            }
            ImmReleaseContext(hwnd, himc);
        }
        ਰੋਕੋ;
    ਹਾਲਤ WM_IME_ENDCOMPOSITION:
        SDL_DebugIMELog("WM_IME_ENDCOMPOSITION");
        ਜੇ (videodata->ime_ਅੰਦਰੂਨੀ_composition) {
            trap = true;
            videodata->ime_composition[0] = 0;
            videodata->ime_readingstring[0] = 0;
            videodata->ime_cursor = 0;
            videodata->ime_selected_ਸ਼ੁਰੂ = 0;
            videodata->ime_selected_ਲੰਮਾਈ = 0;
            IME_SendClearComposition(videodata);
        }
        ਰੋਕੋ;
    ਹਾਲਤ WM_IME_NOTIFY:
        SDL_DebugIMELog("WM_IME_NOTIFY %x", wParam);
        ਚੋਣ (wParam) {
        ਹਾਲਤ IMN_SETCOMPOSITIONWINDOW:
            SDL_DebugIMELog("IMN_SETCOMPOSITIONWINDOW");
            ਰੋਕੋ;
        ਹਾਲਤ IMN_SETCOMPOSITIONFONT:
            SDL_DebugIMELog("IMN_SETCOMPOSITIONFONT");
            ਰੋਕੋ;
        ਹਾਲਤ IMN_SETCANDIDATEPOS:
            SDL_DebugIMELog("IMN_SETCANDIDATEPOS");
            ਰੋਕੋ;
        ਹਾਲਤ IMN_SETCONVERSIONMODE:
        ਹਾਲਤ IMN_SETOPENSTATUS:
            SDL_DebugIMELog("%s", wParam == IMN_SETCONVERSIONMODE ? "IMN_SETCONVERSIONMODE" : "IMN_SETOPENSTATUS");
            IME_Update_ਨਿਵੇਸ਼_Locale(videodata);
            ਰੋਕੋ;
        ਹਾਲਤ IMN_OPENCANDIDATE:
        ਹਾਲਤ IMN_CHANGECANDIDATE:
            SDL_DebugIMELog("%s", wParam == IMN_OPENCANDIDATE ? "IMN_OPENCANDIDATE" : "IMN_CHANGECANDIDATE");
            ਜੇ (videodata->ime_ਅੰਦਰੂਨੀ_candidates) {
                trap = true;
                videodata->ime_update_candidates = true;
            }
            ਰੋਕੋ;
        ਹਾਲਤ IMN_CLOSECANDIDATE:
            SDL_DebugIMELog("IMN_CLOSECANDIDATE");
            ਜੇ (videodata->ime_ਅੰਦਰੂਨੀ_candidates) {
                trap = true;
                videodata->ime_update_candidates = false;
                IME_CloseCandidateList(videodata);
            }
            ਰੋਕੋ;
        ਹਾਲਤ IMN_ਨਿੱਜੀ:
        {
            DWORD dwId = IME_GetId(videodata, 0);
            SDL_DebugIMELog("IMN_PRIVATE %u", dwId);
            IME_GetReadingString(videodata, hwnd);
            ਚੋਣ (dwId) {
            ਹਾਲਤ IMEID_CHT_VER42:
            ਹਾਲਤ IMEID_CHT_VER43:
            ਹਾਲਤ IMEID_CHT_VER44:
            ਹਾਲਤ IMEID_CHS_VER41:
            ਹਾਲਤ IMEID_CHS_VER42:
                ਜੇ (*lParam == 1 || *lParam == 2) {
                    trap = true;
                }

                ਰੋਕੋ;
            ਹਾਲਤ IMEID_CHT_VER50:
            ਹਾਲਤ IMEID_CHT_VER51:
            ਹਾਲਤ IMEID_CHT_VER52:
            ਹਾਲਤ IMEID_CHT_VER60:
            ਹਾਲਤ IMEID_CHS_VER53:
                ਜੇ (*lParam == 16 || *lParam == 17 || *lParam == 26 || *lParam == 27 || *lParam == 28) {
                    trap = true;
                }
                ਰੋਕੋ;
            }
        } ਰੋਕੋ;
        ਮੂਲ:
            trap = true;
            ਰੋਕੋ;
        }
        ਰੋਕੋ;
    }
    ਵਾਪਸ trap;
}

ਖਾਲੀ WIN_UpdateIMECandidates(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;

    ਜੇ (videodata->ime_update_candidates) {
        IME_GetCandidateList(videodata, videodata->ime_hwnd_current);
        videodata->ime_update_candidates = false;
    }
}

#ਜੇ_ਅੰਤ // SDL_DISABLE_WINDOWS_IME

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WINDOWS
