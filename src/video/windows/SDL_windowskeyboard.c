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
#అన్తర్భావ "SDL_internal.h"

#ఒకవేళ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#అన్తర్భావ "SDL_windowsvideo.h"

#అన్తర్భావ "../../events/SDL_keyboard_c.h"
#అన్తర్భావ "../../events/scancodes_windows.h"

#అన్తర్భావ <imm.h>
#అన్తర్భావ <oleauto.h>

#నిర్వచితం_కాకపోతే SDL_DISABLE_WINDOWS_IME
#ఒకవేళ 0
#నిర్వచించు SDL_DebugIMELog SDL_Log
#లేకపోతే
#నిర్వచించు SDL_DebugIMELog(...)
#అయితే_ముగింపు
స్థిర bool IME_Init(SDL_Video_దత్తాంశం *videodata, SDL_కిటికీ *కిటికీ);
స్థిర శూన్య IME_Enable(SDL_Video_దత్తాంశం *videodata, HWND hwnd);
స్థిర శూన్య IME_Disable(SDL_Video_దత్తాంశం *videodata, HWND hwnd);
స్థిర శూన్య IME_సమితి_పాఠ్యం_ఆదానం_Area(SDL_Video_దత్తాంశం *videodata, HWND hwnd, స్థిరరాశి SDL_Rect *rect, పూర్ణాంకం cursor);
స్థిర శూన్య IME_ClearComposition(SDL_Video_దత్తాంశం *videodata);
స్థిర శూన్య IME_GetCandidateList(SDL_Video_దత్తాంశం *videodata, HWND hwnd);
స్థిర శూన్య IME_Quit(SDL_Video_దత్తాంశం *videodata);
#లేకపోతే
స్థిర శూన్య IME_సమితి_పాఠ్యం_ఆదానం_Area(SDL_Video_దత్తాంశం *videodata, HWND hwnd, స్థిరరాశి SDL_Rect *rect, పూర్ణాంకం cursor);
#అయితే_ముగింపు // !SDL_DISABLE_WINDOWS_IME

#నిర్వచితం_కాకపోతే MAPVK_VK_గమ్యం_VSC
#నిర్వచించు MAPVK_VK_గమ్యం_VSC 0
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే MAPVK_VSC_గమ్యం_VK
#నిర్వచించు MAPVK_VSC_గమ్యం_VK 1
#అయితే_ముగింపు

/* Building keymaps is expensive, so keep a reasonably-sized LRU cache to
 * enable fast switching between commonly used ones.
 */
స్థిర నిర్మాణం WIN_KeymapCache
{
    HKL keyboard_layout;
    SDL_Keymap *keymap;
} keymap_cache[4];

స్థిర పూర్ణాంకం keymap_cache_కొలత;

స్థిర SDL_Keymap *WIN_GetCachedKeymap(HKL layout)
{
    SDL_Keymap *keymap = ఖాళీ;
    కొరకు (పూర్ణాంకం i = 0; i < keymap_cache_కొలత; ++i) {
        ఒకవేళ (keymap_cache[i].keyboard_layout == layout) {
            keymap = keymap_cache[i].keymap;

            // Move the map to the front of the list.
            ఒకవేళ (i) {
                SDL_memmove(keymap_cache + 1, keymap_cache, పరిమాణం(నిర్మాణం WIN_KeymapCache) * i);
                keymap_cache[0].keyboard_layout = layout;
                keymap_cache[0].keymap = keymap;
            }
            ఆపు;
        }
    }
    తిరిగి keymap;
}

స్థిర శూన్య WIN_CacheKeymap(HKL layout, SDL_Keymap *keymap)
{
    // If the cache is full, evict the last keymap.
    ఒకవేళ (keymap_cache_కొలత == SDL_arraysize(keymap_cache)) {
        SDL_DestroyKeymap(keymap_cache[--keymap_cache_కొలత].keymap);
    }

    // Move all elements down by one.
    ఒకవేళ (keymap_cache_కొలత) {
        SDL_memmove(keymap_cache + 1, keymap_cache, పరిమాణం(నిర్మాణం WIN_KeymapCache) * keymap_cache_కొలత);
    }

    keymap_cache[0].keyboard_layout = layout;
    keymap_cache[0].keymap = keymap;
    ++keymap_cache_కొలత;
}

స్థిర SDL_Keymap *WIN_BuildKeymap(శూన్య)
{
    SDL_Scancode scancode;
    BYTE keyboardState[256] = { 0 };
    WCHAR బఫరు_2[16];
    స్థిరరాశి SDL_Keymod mods[] = {
        SDL_KMOD_NONE,
        SDL_KMOD_జరుపు,
        SDL_KMOD_CAPS,
        (SDL_KMOD_జరుపు | SDL_KMOD_CAPS),
        SDL_KMOD_బహుళకం,
        (SDL_KMOD_బహుళకం | SDL_KMOD_జరుపు),
        (SDL_KMOD_బహుళకం | SDL_KMOD_CAPS),
        (SDL_KMOD_బహుళకం | SDL_KMOD_జరుపు | SDL_KMOD_CAPS)
    };

    WIN_Reset_Dead_కీలకాలు();

    SDL_Keymap *keymap = SDL_CreateKeymap(false);
    ఒకవేళ (!keymap) {
        తిరిగి ఖాళీ;
    }

    కొరకు (పూర్ణాంకం m = 0; m < SDL_arraysize(mods); ++m) {
        కొరకు (పూర్ణాంకం i = 0; i < SDL_arraysize(windows_scancode_పట్టిక); i++) {
            పూర్ణాంకం vk, sc, ఫలితం;
            Uint32 *ch = 0;

            // Make sure this scancode is a valid character scancode
            scancode = windows_scancode_పట్టిక[i];
            ఒకవేళ (scancode == SDL_SCANCODE_UNKNOWN ||
                scancode == SDL_SCANCODE_DELETE ||
                (SDL_GetKeymapKeycode(ఖాళీ, scancode, SDL_KMOD_NONE) & SDLK_SCANCODE_ముసుగు)) {

                // The Colemak mapping swaps Backspace and CapsLock
                ఒకవేళ (mods[m] == SDL_KMOD_NONE &&
                    (scancode == SDL_SCANCODE_CAPSLOCK ||
                     scancode == SDL_SCANCODE_BACKSPACE)) {
                    vk = LOBYTE(Map_Virtual_కీలకం(i, MAPVK_VSC_గమ్యం_VK));
                    ఒకవేళ (vk == VK_CAPITAL) {
                        SDL_సమితి_Keymap_నమోదు(keymap, scancode, mods[m], SDLK_CAPSLOCK);
                    } లేకపోతే ఒకవేళ (vk == VK_వెనుక) {
                        SDL_సమితి_Keymap_నమోదు(keymap, scancode, mods[m], SDLK_BACKSPACE);
                    }
                }
                కొనసాగు;
            }

            // Unpack the single byte index to make the scan code.
            sc = MAKEWORD(i & 0x7f, (i & 0x80) ? 0xe0 : 0x00);
            vk = LOBYTE(Map_Virtual_కీలకం(sc, MAPVK_VSC_గమ్యం_VK));
            ఒకవేళ (!vk) {
                కొనసాగు;
            }

            // Update the keyboard state for the modifiers
            keyboardState[VK_జరుపు] = (mods[m] & SDL_KMOD_జరుపు) ? 0x80 : 0x00;
            keyboardState[VK_CAPITAL] = (mods[m] & SDL_KMOD_CAPS) ? 0x01 : 0x00;
            keyboardState[VK_CONTROL] = (mods[m] & SDL_KMOD_బహుళకం) ? 0x80 : 0x00;
            keyboardState[VK_MENU] = (mods[m] & SDL_KMOD_బహుళకం) ? 0x80 : 0x00;

            ఫలితం = గమ్యం_Unicode(vk, sc, keyboardState, బఫరు_2, 16, 0);
            బఫరు_2[SDL_abs(ఫలితం)] = 0;

            // Convert UTF-16 to UTF-32 code points
            ch = (Uint32 *)SDL_iconv_string("UTF-32LE", "UTF-16LE", (స్థిరరాశి అక్షరం *)బఫరు_2, (SDL_abs(ఫలితం) + 1) * పరిమాణం(WCHAR));
            ఒకవేళ (ch) {
                /* Windows keyboard layouts can emit several UTF-32 code points on a single key press.
                 * Use <U+FFFD REPLACEMENT CHARACTER> since we cannot fit into single SDL_Keycode value in SDL keymap.
                 * See https://kbdlayout.info/features/ligatures for a list of such keys. */
                SDL_సమితి_Keymap_నమోదు(keymap, scancode, mods[m], ch[1] == 0 ? ch[0] : 0xfffd);
                SDL_free(ch);
            } లేకపోతే {
                // The default keymap doesn't have any SDL_KMOD_MODE entries, so we don't need to override them
                ఒకవేళ (!(mods[m] & SDL_KMOD_బహుళకం)) {
                    SDL_సమితి_Keymap_నమోదు(keymap, scancode, mods[m], SDLK_UNKNOWN);
                }
            }

            ఒకవేళ (ఫలితం < 0) {
                WIN_Reset_Dead_కీలకాలు();
            }
        }
    }

    తిరిగి keymap;
}

శూన్య WIN_UpdateKeymap(bool send_event)
{
    HKL layout = GetKeyboardLayout(0);
    SDL_Keymap *keymap = WIN_GetCachedKeymap(layout);
    ఒకవేళ (!keymap) {
        keymap = WIN_BuildKeymap();
        ఒకవేళ (keymap) {
            WIN_CacheKeymap(layout, keymap);
        }
    }

    SDL_సమితి_Keymap(keymap, send_event);
}

// Alphabetic scancodes for PC keyboards
శూన్య WIN_InitKeyboard(SDL_VideoDevice *_this)
{
#నిర్వచితం_కాకపోతే SDL_DISABLE_WINDOWS_IME
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    దత్తాంశం->ime_candlistindexbase = 1;
    దత్తాంశం->ime_composition_నిడివి = 32 * పరిమాణం(WCHAR);
    దత్తాంశం->ime_composition = (WCHAR *)SDL_calloc(దత్తాంశం->ime_composition_నిడివి, పరిమాణం(WCHAR));
#అయితే_ముగింపు // !SDL_DISABLE_WINDOWS_IME

    // Build and bind the current keymap.
    WIN_UpdateKeymap(false);

    SDL_సమితి_Scancode_Name(SDL_SCANCODE_APPLICATION, "Menu");
    SDL_సమితి_Scancode_Name(SDL_SCANCODE_LGUI, "Left Windows");
    SDL_సమితి_Scancode_Name(SDL_SCANCODE_RGUI, "Right Windows");

    // Are system caps/num/scroll lock active? Set our state to match.
    SDL_ToggleModState(SDL_KMOD_CAPS, (Get_కీలకం_State(VK_CAPITAL) & 0x0001) ? true : false);
    SDL_ToggleModState(SDL_KMOD_అంకె, (Get_కీలకం_State(VK_NUMLOCK) & 0x0001) ? true : false);
    SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_కీలకం_State(VK_SCROLL) & 0x0001) ? true : false);
}

శూన్య WIN_QuitKeyboard(SDL_VideoDevice *_this)
{
#నిర్వచితం_కాకపోతే SDL_DISABLE_WINDOWS_IME
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    IME_Quit(దత్తాంశం);

    ఒకవేళ (దత్తాంశం->ime_composition) {
        SDL_free(దత్తాంశం->ime_composition);
        దత్తాంశం->ime_composition = ఖాళీ;
    }
#అయితే_ముగింపు // !SDL_DISABLE_WINDOWS_IME

    కొరకు (పూర్ణాంకం i = 0; i < keymap_cache_కొలత; ++i) {
        SDL_DestroyKeymap(keymap_cache[i].keymap);
    }
    SDL_zeroa(keymap_cache);
    keymap_cache_కొలత = 0;
}

శూన్య WIN_Reset_Dead_కీలకాలు(శూన్య)
{
    /*
    if a deadkey has been typed, but not the next character (which the deadkey might modify),
    this tries to undo the effect pressing the deadkey.
    see: http://archives.miloush.net/michkap/archive/2006/09/10/748775.html
    */
    BYTE keyboardState[256];
    WCHAR బఫరు_2[16];
    పూర్ణాంకం vk, sc, ఫలితం, i;

    ఒకవేళ (!GetKeyboardState(keyboardState)) {
        తిరిగి;
    }

    vk = VK_SPACE;
    sc = Map_Virtual_కీలకం(vk, MAPVK_VK_గమ్యం_VSC);
    ఒకవేళ (sc == 0) {
        // the keyboard doesn't have this key
        తిరిగి;
    }

    కొరకు (i = 0; i < 5; i++) {
        ఫలితం = గమ్యం_Unicode(vk, sc, keyboardState, బఫరు_2, 16, 0);
        ఒకవేళ (ఫలితం > 0) {
            // success
            తిరిగి;
        }
    }
}

bool WIN_ప్రారంభం_పాఠ్యం_ఆదానం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID props)
{
    WIN_Reset_Dead_కీలకాలు();

#నిర్వచితం_కాకపోతే SDL_DISABLE_WINDOWS_IME
    HWND hwnd = కిటికీ->అంతర్గత->hwnd;
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    IME_Init(videodata, కిటికీ);
    IME_Enable(videodata, hwnd);

    WIN_Update_పాఠ్యం_ఆదానం_Area(_this, కిటికీ);
#అయితే_ముగింపు // !SDL_DISABLE_WINDOWS_IME

    తిరిగి true;
}

bool WIN_Stop_పాఠ్యం_ఆదానం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    WIN_Reset_Dead_కీలకాలు();

#నిర్వచితం_కాకపోతే SDL_DISABLE_WINDOWS_IME
    HWND hwnd = కిటికీ->అంతర్గత->hwnd;
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    IME_Init(videodata, కిటికీ);
    IME_Disable(videodata, hwnd);
#అయితే_ముగింపు // !SDL_DISABLE_WINDOWS_IME

    తిరిగి true;
}

bool WIN_Update_పాఠ్యం_ఆదానం_Area(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;

    IME_సమితి_పాఠ్యం_ఆదానం_Area(videodata, దత్తాంశం->hwnd, &కిటికీ->పాఠ్యం_ఆదానం_rect, కిటికీ->పాఠ్యం_ఆదానం_cursor);
    తిరిగి true;
}

bool WIN_ClearComposition(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
#నిర్వచితం_కాకపోతే SDL_DISABLE_WINDOWS_IME
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;

    IME_ClearComposition(videodata);
#అయితే_ముగింపు
    తిరిగి true;
}

#నిర్వచితమైతే SDL_DISABLE_WINDOWS_IME

bool WIN_HandleIMEMessage(HWND hwnd, UINT సందేశం_2, WPARAM wParam, LPARAM *lParam, SDL_Video_దత్తాంశం *videodata)
{
    తిరిగి false;
}

శూన్య WIN_UpdateIMECandidates(SDL_VideoDevice *_this)
{
    తిరిగి;
}

#లేకపోతే

#నిర్వచించు LANG_CHT MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_TRADITIONAL)
#నిర్వచించు LANG_CHS MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED)

#నిర్వచించు MAKEIMEVERSION(major, minor) ((DWORD)(((BYTE)(major) << 24) | ((BYTE)(minor) << 16)))
#నిర్వచించు IMEID_VER(id)                ((id)&0xffff0000)
#నిర్వచించు IMEID_LANG(id)               ((id)&0x0000ffff)

#నిర్వచించు CHT_HKL_DAYI          ((HKL)(UINT_PTR)0xE0060404)
#నిర్వచించు CHT_HKL_NEW_PHONETIC  ((HKL)(UINT_PTR)0xE0080404)
#నిర్వచించు CHT_HKL_NEW_CHANG_JIE ((HKL)(UINT_PTR)0xE0090404)
#నిర్వచించు CHT_HKL_NEW_శీఘ్ర     ((HKL)(UINT_PTR)0xE00A0404)
#నిర్వచించు CHT_HKL_HK_CANTONESE  ((HKL)(UINT_PTR)0xE00B0404)
#నిర్వచించు CHT_IMEFILENAME1      "TINTLGNT.IME"
#నిర్వచించు CHT_IMEFILENAME2      "CINTLGNT.IME"
#నిర్వచించు CHT_IMEFILENAME3      "MSTCIPHA.IME"
#నిర్వచించు IMEID_CHT_VER42       (LANG_CHT | MAKEIMEVERSION(4, 2))
#నిర్వచించు IMEID_CHT_VER43       (LANG_CHT | MAKEIMEVERSION(4, 3))
#నిర్వచించు IMEID_CHT_VER44       (LANG_CHT | MAKEIMEVERSION(4, 4))
#నిర్వచించు IMEID_CHT_VER50       (LANG_CHT | MAKEIMEVERSION(5, 0))
#నిర్వచించు IMEID_CHT_VER51       (LANG_CHT | MAKEIMEVERSION(5, 1))
#నిర్వచించు IMEID_CHT_VER52       (LANG_CHT | MAKEIMEVERSION(5, 2))
#నిర్వచించు IMEID_CHT_VER60       (LANG_CHT | MAKEIMEVERSION(6, 0))
#నిర్వచించు IMEID_CHT_VER_VISTA   (LANG_CHT | MAKEIMEVERSION(7, 0))

#నిర్వచించు CHS_HKL          ((HKL)(UINT_PTR)0xE00E0804)
#నిర్వచించు CHS_IMEFILENAME1 "PINTLGNT.IME"
#నిర్వచించు CHS_IMEFILENAME2 "MSSCIPYA.IME"
#నిర్వచించు IMEID_CHS_VER41  (LANG_CHS | MAKEIMEVERSION(4, 1))
#నిర్వచించు IMEID_CHS_VER42  (LANG_CHS | MAKEIMEVERSION(4, 2))
#నిర్వచించు IMEID_CHS_VER53  (LANG_CHS | MAKEIMEVERSION(5, 3))

#నిర్వచించు LANG()         LOWORD((videodata->ime_hkl))
#నిర్వచించు PRIMLANG()     ((మాట)PRIMARYLANGID(LANG()))
#నిర్వచించు SUBLANG()      SUBLANGID(LANG())

స్థిర శూన్య IME_Update_ఆదానం_Locale(SDL_Video_దత్తాంశం *videodata);
స్థిర శూన్య IME_సమితి_కిటికీ(SDL_Video_దత్తాంశం *videodata, SDL_కిటికీ *కిటికీ);
స్థిర శూన్య IME_అమరిక_API(SDL_Video_దత్తాంశం *videodata);
స్థిర DWORD IME_GetId(SDL_Video_దత్తాంశం *videodata, UINT u_సూచీ);
స్థిర శూన్య IME_SendEditingEvent(SDL_Video_దత్తాంశం *videodata);
స్థిర శూన్య IME_SendClearComposition(SDL_Video_దత్తాంశం *videodata);

స్థిర bool IME_Init(SDL_Video_దత్తాంశం *videodata, SDL_కిటికీ *కిటికీ)
{
    HWND hwnd = కిటికీ->అంతర్గత->hwnd;

    ఒకవేళ (videodata->ime_initialized) {
        తిరిగి true;
    }

    స్థిరరాశి అక్షరం *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);
    ఒకవేళ (hint && SDL_strstr(hint, "composition")) {
        videodata->ime_అంతర్గత_composition = true;
    }
    ఒకవేళ (hint && SDL_strstr(hint, "candidates")) {
        videodata->ime_అంతర్గత_candidates = true;
    }

    videodata->ime_hwnd_main = hwnd;
    videodata->ime_initialized = true;
    videodata->ime_himm32 = SDL_ఎక్కించు_Object("imm32.dll");
    ఒకవేళ (!videodata->ime_himm32) {
        videodata->ime_అందుబాటు = false;
        SDL_ClearError();
        తిరిగి true;
    }
    /* *INDENT-OFF* */ // clang-format off
    videodata->Imm_తాళం_IMC = (LPINPUTCONTEXT2 (WINAPI *)(HIMC))SDL_ఎక్కించు_Function(videodata->ime_himm32, "ImmLockIMC");
    videodata->ImmUnlockIMC = (BOOL (WINAPI *)(HIMC))SDL_ఎక్కించు_Function(videodata->ime_himm32, "ImmUnlockIMC");
    videodata->Imm_తాళం_IMCC = (LPVOID (WINAPI *)(HIMCC))SDL_ఎక్కించు_Function(videodata->ime_himm32, "ImmLockIMCC");
    videodata->ImmUnlockIMCC = (BOOL (WINAPI *)(HIMCC))SDL_ఎక్కించు_Function(videodata->ime_himm32, "ImmUnlockIMCC");
    /* *INDENT-ON* */ // clang-format on

    IME_సమితి_కిటికీ(videodata, కిటికీ);
    videodata->ime_himc = ImmGetContext(hwnd);
    ImmReleaseContext(hwnd, videodata->ime_himc);
    ఒకవేళ (!videodata->ime_himc) {
        videodata->ime_అందుబాటు = false;
        IME_Disable(videodata, hwnd);
        తిరిగి true;
    }
    videodata->ime_అందుబాటు = true;
    IME_Update_ఆదానం_Locale(videodata);
    IME_అమరిక_API(videodata);
    IME_Update_ఆదానం_Locale(videodata);
    IME_Disable(videodata, hwnd);
    తిరిగి true;
}

స్థిర శూన్య IME_Enable(SDL_Video_దత్తాంశం *videodata, HWND hwnd)
{
    ఒకవేళ (!videodata->ime_initialized || !videodata->ime_hwnd_current) {
        తిరిగి;
    }

    ఒకవేళ (!videodata->ime_అందుబాటు) {
        IME_Disable(videodata, hwnd);
        తిరిగి;
    }
    ఒకవేళ (videodata->ime_hwnd_current == videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_current, videodata->ime_himc);
    }

    videodata->ime_enabled = true;
    IME_Update_ఆదానం_Locale(videodata);
}

స్థిర శూన్య IME_Disable(SDL_Video_దత్తాంశం *videodata, HWND hwnd)
{
    ఒకవేళ (!videodata->ime_initialized || !videodata->ime_hwnd_current) {
        తిరిగి;
    }

    IME_ClearComposition(videodata);
    ఒకవేళ (videodata->ime_hwnd_current == videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_current, (HIMC)0);
    }

    videodata->ime_enabled = false;
}

స్థిర శూన్య IME_Quit(SDL_Video_దత్తాంశం *videodata)
{
    ఒకవేళ (!videodata->ime_initialized) {
        తిరిగి;
    }

    ఒకవేళ (videodata->ime_hwnd_main) {
        ImmAssociateContext(videodata->ime_hwnd_main, videodata->ime_himc);
    }

    videodata->ime_hwnd_main = 0;
    videodata->ime_himc = 0;
    ఒకవేళ (videodata->ime_himm32) {
        SDL_UnloadObject(videodata->ime_himm32);
        videodata->ime_himm32 = 0;
    }
    కొరకు (పూర్ణాంకం i = 0; i < videodata->ime_candcount; ++i) {
        SDL_free(videodata->ime_candidates[i]);
        videodata->ime_candidates[i] = ఖాళీ;
    }
    videodata->ime_initialized = false;
}

స్థిర శూన్య IME_GetReadingString(SDL_Video_దత్తాంశం *videodata, HWND hwnd)
{
    DWORD id = 0;
    HIMC himc = 0;
    WCHAR బఫరు_2[16];
    WCHAR *s = బఫరు_2;
    DWORD len = 0;
    INT err = 0;
    BOOL vertical = FALSE;
    UINT maxuilen = 0;

    videodata->ime_readingstring[0] = 0;

    id = IME_GetId(videodata, 0);
    ఒకవేళ (!id) {
        తిరిగి;
    }

    himc = ImmGetContext(hwnd);
    ఒకవేళ (!himc) {
        తిరిగి;
    }

    ఒకవేళ (videodata->GetReadingString) {
        len = videodata->GetReadingString(himc, 0, 0, &err, &vertical, &maxuilen);
        ఒకవేళ (len) {
            ఒకవేళ (len > SDL_arraysize(బఫరు_2)) {
                len = SDL_arraysize(బఫరు_2);
            }

            len = videodata->GetReadingString(himc, len, s, &err, &vertical, &maxuilen);
        }
        SDL_wcslcpy(videodata->ime_readingstring, s, len);
    } లేకపోతే {
        LPINPUTCONTEXT2 lpimc = videodata->Imm_తాళం_IMC(himc);
        LPBYTE p = 0;
        s = 0;
        ఎంపిక (id) {
        స్థితి IMEID_CHT_VER42:
        స్థితి IMEID_CHT_VER43:
        స్థితి IMEID_CHT_VER44:
            p = *(LPBYTE *)((LPBYTE)videodata->Imm_తాళం_IMCC(lpimc->h_వ్యక్తిగత) + 24);
            ఒకవేళ (!p) {
                ఆపు;
            }

            len = *(DWORD *)(p + 7 * 4 + 32 * 4);
            s = (WCHAR *)(p + 56);
            ఆపు;
        స్థితి IMEID_CHT_VER51:
        స్థితి IMEID_CHT_VER52:
        స్థితి IMEID_CHS_VER53:
            p = *(LPBYTE *)((LPBYTE)videodata->Imm_తాళం_IMCC(lpimc->h_వ్యక్తిగత) + 4);
            ఒకవేళ (!p) {
                ఆపు;
            }

            p = *(LPBYTE *)(p + 1 * 4 + 5 * 4);
            ఒకవేళ (!p) {
                ఆపు;
            }

            len = *(DWORD *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4 + 16 * 2);
            s = (WCHAR *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4);
            ఆపు;
        స్థితి IMEID_CHS_VER41:
        {
            పూర్ణాంకం స్థానభ్రంశం_2 = (IME_GetId(videodata, 1) >= 0x00000002) ? 8 : 7;
            p = *(LPBYTE *)((LPBYTE)videodata->Imm_తాళం_IMCC(lpimc->h_వ్యక్తిగత) + స్థానభ్రంశం_2 * 4);
            ఒకవేళ (!p) {
                ఆపు;
            }

            len = *(DWORD *)(p + 7 * 4 + 16 * 2 * 4);
            s = (WCHAR *)(p + 6 * 4 + 16 * 2 * 1);
        } ఆపు;
        స్థితి IMEID_CHS_VER42:
            p = *(LPBYTE *)((LPBYTE)videodata->Imm_తాళం_IMCC(lpimc->h_వ్యక్తిగత) + 1 * 4 + 1 * 4 + 6 * 4);
            ఒకవేళ (!p) {
                ఆపు;
            }

            len = *(DWORD *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4 + 16 * 2);
            s = (WCHAR *)(p + 1 * 4 + (16 * 2 + 2 * 4) + 5 * 4);
            ఆపు;
        }
        ఒకవేళ (s) {
            size_t కొలత = SDL_min((size_t)(len + 1), SDL_arraysize(videodata->ime_readingstring));
            SDL_wcslcpy(videodata->ime_readingstring, s, కొలత);
        }

        videodata->ImmUnlockIMCC(lpimc->h_వ్యక్తిగత);
        videodata->ImmUnlockIMC(himc);
    }
    ImmReleaseContext(hwnd, himc);
    IME_SendEditingEvent(videodata);
}

స్థిర శూన్య IME_ఆదానం_Lang_మారింది(SDL_Video_దత్తాంశం *videodata)
{
    UINT lang = PRIMLANG();
    IME_Update_ఆదానం_Locale(videodata);

    IME_అమరిక_API(videodata);
    ఒకవేళ (lang != PRIMLANG()) {
        IME_ClearComposition(videodata);
    }
}

స్థిర DWORD IME_GetId(SDL_Video_దత్తాంశం *videodata, UINT u_సూచీ)
{
    స్థిర HKL hklprev = 0;
    స్థిర DWORD dwRet[2] = { 0 };
    DWORD dw_Ver_కొలత = 0;
    LPVOID lp_Ver_బఫరు = 0;
    LPVOID lp_Ver_దత్తాంశం = 0;
    UINT cb_Ver_దత్తాంశం = 0;
    అక్షరం sz_తాత్కాలిక[256];
    HKL hkl = 0;
    DWORD dwLang = 0;
    SDL_assert(u_సూచీ < SDL_arraysize(dwRet));

    hkl = videodata->ime_hkl;
    ఒకవేళ (hklprev == hkl) {
        తిరిగి dwRet[u_సూచీ];
    }
    hklprev = hkl;

    SDL_assert(u_సూచీ == 0);
    dwLang = ((DWORD_PTR)hkl & 0xffff);
    // FIXME: What does this do?
    ఒకవేళ (videodata->ime_అంతర్గత_candidates && dwLang == LANG_CHT) {
        dwRet[0] = IMEID_CHT_VER_VISTA;
        dwRet[1] = 0;
        తిరిగి dwRet[0];
    }
    ఒకవేళ (hkl != CHT_HKL_NEW_PHONETIC && hkl != CHT_HKL_NEW_CHANG_JIE && hkl != CHT_HKL_NEW_శీఘ్ర && hkl != CHT_HKL_HK_CANTONESE && hkl != CHS_HKL) {
        dwRet[0] = dwRet[1] = 0;
        తిరిగి dwRet[0];
    }
    ఒకవేళ (!ImmGetIMEFileNameA(hkl, sz_తాత్కాలిక, పరిమాణం(sz_తాత్కాలిక) - 1)) {
        dwRet[0] = dwRet[1] = 0;
        తిరిగి dwRet[0];
    }
    ఒకవేళ (!videodata->GetReadingString) {
#నిర్వచించు LCID_INVARIANT MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), క్రమీకరించు_DEFAULT)
        ఒకవేళ (CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_తాత్కాలిక, -1, CHT_IMEFILENAME1, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_తాత్కాలిక, -1, CHT_IMEFILENAME2, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_తాత్కాలిక, -1, CHT_IMEFILENAME3, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_తాత్కాలిక, -1, CHS_IMEFILENAME1, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, sz_తాత్కాలిక, -1, CHS_IMEFILENAME2, -1) != 2) {
            dwRet[0] = dwRet[1] = 0;
            తిరిగి dwRet[0];
        }
#నిర్వచనం_రద్దు LCID_INVARIANT
        dw_Ver_కొలత = Get_File_సంస్కరణ_Info_కొలత_A(sz_తాత్కాలిక, ఖాళీ);
        ఒకవేళ (dw_Ver_కొలత) {
            lp_Ver_బఫరు = SDL_malloc(dw_Ver_కొలత);
            ఒకవేళ (lp_Ver_బఫరు) {
                ఒకవేళ (Get_File_సంస్కరణ_Info_A(sz_తాత్కాలిక, 0, dw_Ver_కొలత, lp_Ver_బఫరు)) {
                    ఒకవేళ (Ver_Query_విలువ_A(lp_Ver_బఫరు, "\\", &lp_Ver_దత్తాంశం, &cb_Ver_దత్తాంశం)) {
#నిర్వచించు pVerFixedInfo ((VS_FIXEDFILEINFO FAR *)lp_Ver_దత్తాంశం)
                        DWORD dwVer = pVerFixedInfo->dw_File_సంస్కరణ_MS;
                        dwVer = (dwVer & 0x00ff0000) << 8 | (dwVer & 0x000000ff) << 16;
                        ఒకవేళ ((videodata->GetReadingString) ||
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
                            dwRet[1] = pVerFixedInfo->dw_File_సంస్కరణ_LS;
                            SDL_free(lp_Ver_బఫరు);
                            తిరిగి dwRet[0];
                        }
#నిర్వచనం_రద్దు pVerFixedInfo
                    }
                }
            }
            SDL_free(lp_Ver_బఫరు);
        }
    }
    dwRet[0] = dwRet[1] = 0;
    తిరిగి dwRet[0];
}

స్థిర శూన్య IME_అమరిక_API(SDL_Video_దత్తాంశం *videodata)
{
    అక్షరం ime_file[MAX_మార్గం + 1];
    SDL_SharedObject *hime = 0;
    HKL hkl = 0;
    videodata->GetReadingString = ఖాళీ;
    videodata->Show_Reading_కిటికీ = ఖాళీ;

    hkl = videodata->ime_hkl;
    ఒకవేళ (!ImmGetIMEFileNameA(hkl, ime_file, పరిమాణం(ime_file) - 1)) {
        తిరిగి;
    }

    hime = SDL_ఎక్కించు_Object(ime_file);
    ఒకవేళ (!hime) {
        తిరిగి;
    }

    /* *INDENT-OFF* */ // clang-format off
    videodata->GetReadingString = (UINT (WINAPI *)(HIMC, UINT, LPWSTR, PINT, BOOL*, PUINT))
        SDL_ఎక్కించు_Function(hime, "GetReadingString");
    videodata->Show_Reading_కిటికీ = (BOOL (WINAPI *)(HIMC, BOOL))
        SDL_ఎక్కించు_Function(hime, "ShowReadingWindow");
    /* *INDENT-ON* */ // clang-format on

    ఒకవేళ (videodata->Show_Reading_కిటికీ) {
        HIMC himc = ImmGetContext(videodata->ime_hwnd_current);
        ఒకవేళ (himc) {
            videodata->Show_Reading_కిటికీ(himc, FALSE);
            ImmReleaseContext(videodata->ime_hwnd_current, himc);
        }
    }
}

స్థిర శూన్య IME_సమితి_కిటికీ(SDL_Video_దత్తాంశం *videodata, SDL_కిటికీ *కిటికీ)
{
    HWND hwnd = కిటికీ->అంతర్గత->hwnd;

    ఒకవేళ (hwnd != videodata->ime_hwnd_current) {
        videodata->ime_hwnd_current = hwnd;
        SDL_zero(videodata->ime_composition_area);
        SDL_zero(videodata->ime_candidate_area);
    }

    IME_సమితి_పాఠ్యం_ఆదానం_Area(videodata, hwnd, &కిటికీ->పాఠ్యం_ఆదానం_rect, కిటికీ->పాఠ్యం_ఆదానం_cursor);
}

#అయితే_ముగింపు

స్థిర శూన్య IME_సమితి_పాఠ్యం_ఆదానం_Area(SDL_Video_దత్తాంశం *videodata, HWND hwnd, స్థిరరాశి SDL_Rect *rect, పూర్ణాంకం cursor)
{
    HIMC himc;

    himc = ImmGetContext(hwnd);
    ఒకవేళ (himc) {
        COMPOSITIONFORM cof;
        CANDIDATEFORM caf;
        పూర్ణాంకం font_ఎత్తు = rect->h;

        LOGFONTW font;
        ఒకవేళ (ImmGetCompositionFontW(himc, &font)) {
            font_ఎత్తు = font.lf_ఎత్తు;
        }

        SDL_zero(cof);
        cof.dwStyle = CFS_RECT;
        cof.ptCurrentPos.x = rect->x + cursor;
        cof.ptCurrentPos.y = rect->y + (rect->h - font_ఎత్తు) / 2;
        cof.rcArea.ఎడమ = rect->x;
        cof.rcArea.కుడి = (LONG)rect->x + rect->w;
        cof.rcArea.శిఖరం = rect->y;
        cof.rcArea.bottom = (LONG)rect->y + rect->h;
        ఒకవేళ (SDL_memcmp(&cof, &videodata->ime_composition_area, పరిమాణం(cof)) != 0) {
            SDL_copyp(&videodata->ime_composition_area, &cof);
            Imm_సమితి_Composition_కిటికీ(himc, &cof);
        }

        SDL_zero(caf);
        caf.dw_సూచీ = 0;
        caf.dwStyle = CFS_EXCLUDE;
        caf.ptCurrentPos.x = rect->x + cursor;
        caf.ptCurrentPos.y = rect->y;
        caf.rcArea.ఎడమ = rect->x;
        caf.rcArea.కుడి = (LONG)rect->x + rect->w;
        caf.rcArea.శిఖరం = rect->y;
        caf.rcArea.bottom = (LONG)rect->y + rect->h;
        ఒకవేళ (SDL_memcmp(&caf, &videodata->ime_candidate_area, పరిమాణం(caf)) != 0) {
            SDL_copyp(&videodata->ime_candidate_area, &caf);
            Imm_సమితి_Candidate_కిటికీ(himc, &caf);
        }

        ImmReleaseContext(hwnd, himc);
    }
}

#నిర్వచితం_కాకపోతే SDL_DISABLE_WINDOWS_IME

స్థిర శూన్య IME_Update_ఆదానం_Locale(SDL_Video_దత్తాంశం *videodata)
{
    HKL hklnext = GetKeyboardLayout(0);

    ఒకవేళ (hklnext == videodata->ime_hkl) {
        తిరిగి;
    }

    videodata->ime_hkl = hklnext;
    videodata->ime_horizontal_candidates = (PRIMLANG() == LANG_KOREAN || LANG() == LANG_CHS);
    videodata->ime_candlistindexbase = (videodata->ime_hkl == CHT_HKL_DAYI) ? 0 : 1;
}

స్థిర శూన్య IME_ClearComposition(SDL_Video_దత్తాంశం *videodata)
{
    HIMC himc = 0;
    ఒకవేళ (!videodata->ime_initialized) {
        తిరిగి;
    }

    himc = ImmGetContext(videodata->ime_hwnd_current);
    ఒకవేళ (!himc) {
        తిరిగి;
    }

    ImmNotifyIME(himc, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
    Imm_సమితి_Composition_String(himc, SCS_SETSTR, పాఠ్యం_2(""), పరిమాణం(TCHAR), పాఠ్యం_2(""), పరిమాణం(TCHAR));

    ImmNotifyIME(himc, NI_CLOSECANDIDATE, 0, 0);
    ImmReleaseContext(videodata->ime_hwnd_current, himc);
    IME_SendClearComposition(videodata);
}

స్థిర శూన్య IME_GetCompositionString(SDL_Video_దత్తాంశం *videodata, HIMC himc, LPARAM *lParam, DWORD string)
{
    LONG నిడివి;
    DWORD dwLang = ((DWORD_PTR)videodata->ime_hkl & 0xffff);

    ఒకవేళ (*lParam & GCS_CURSORPOS) {
        videodata->ime_cursor = LOWORD(ImmGetCompositionStringW(himc, GCS_CURSORPOS, 0, 0));
    }
    videodata->ime_selected_ప్రారంభం = 0;
    videodata->ime_selected_నిడివి = 0;
    SDL_DebugIMELog("Cursor = %d", videodata->ime_cursor);

    నిడివి = ImmGetCompositionStringW(himc, string, ఖాళీ, 0);
    ఒకవేళ (నిడివి > 0 && videodata->ime_composition_నిడివి < నిడివి) {
        SDL_free(videodata->ime_composition);

        videodata->ime_composition = (WCHAR *)SDL_malloc(నిడివి + పరిమాణం(WCHAR));
        videodata->ime_composition_నిడివి = నిడివి;
    }

    నిడివి = ImmGetCompositionStringW(himc, string, videodata->ime_composition, videodata->ime_composition_నిడివి);
    ఒకవేళ (నిడివి < 0) {
        నిడివి = 0;
    }
    నిడివి /= పరిమాణం(WCHAR);

    ఒకవేళ (!(*lParam & GCS_CURSORPOS)) {
        // If the IME doesn't support GCS_CURSORPOS, default the cursor to the end of the composition.
        videodata->ime_cursor = నిడివి;
    }

    ఒకవేళ ((dwLang == LANG_CHT || dwLang == LANG_CHS) &&
        videodata->ime_cursor > 0 &&
        videodata->ime_cursor < (పూర్ణాంకం)(videodata->ime_composition_నిడివి / పరిమాణం(WCHAR)) &&
        (videodata->ime_composition[0] == 0x3000 || videodata->ime_composition[0] == 0x0020)) {
        // Traditional Chinese IMEs add a placeholder U+3000
        // Simplified Chinese IMEs seem to add a placeholder U+0020 sometimes
        కొరకు (పూర్ణాంకం i = videodata->ime_cursor + 1; i < నిడివి; ++i) {
            videodata->ime_composition[i - 1] = videodata->ime_composition[i];
        }
        --నిడివి;
    }

    videodata->ime_composition[నిడివి] = 0;

    నిడివి = ImmGetCompositionStringW(himc, GCS_COMPATTR, ఖాళీ, 0);
    ఒకవేళ (నిడివి > 0) {
        Uint8 *లక్షణాలు = (Uint8 *)SDL_malloc(నిడివి);
        ఒకవేళ (లక్షణాలు) {
            పూర్ణాంకం ప్రారంభం = 0;
            పూర్ణాంకం చివర = 0;

            నిడివి = ImmGetCompositionString(himc, GCS_COMPATTR, లక్షణాలు, నిడివి);
            ఒకవేళ (నిడివి < 0) {
                నిడివి = 0;
            }

            కొరకు (LONG i = 0; i < నిడివి; ++i) {
                SDL_DebugIMELog("attrib[%d] = %d", i, లక్షణాలు[i]);
            }

            కొరకు (ప్రారంభం = 0; ప్రారంభం < నిడివి; ++ప్రారంభం) {
                ఒకవేళ (లక్షణాలు[ప్రారంభం] == ATTR_లక్ష్యం_CONVERTED || లక్షణాలు[ప్రారంభం] == ATTR_లక్ష్యం_NOTCONVERTED) {
                    ఆపు;
                }
            }

            కొరకు (చివర = ప్రారంభం; చివర < నిడివి; ++చివర) {
                ఒకవేళ (లక్షణాలు[చివర] != ATTR_లక్ష్యం_CONVERTED && లక్షణాలు[చివర] != ATTR_లక్ష్యం_NOTCONVERTED) {
                    ఆపు;
                }
            }

            ఒకవేళ (చివర > ప్రారంభం) {
                videodata->ime_selected_ప్రారంభం = ప్రారంభం;
                videodata->ime_selected_నిడివి = చివర - ప్రారంభం;
            }

            SDL_free(లక్షణాలు);
        }
    }
}

స్థిర శూన్య IME_Send_ఆదానం_Event(SDL_Video_దత్తాంశం *videodata)
{
    అక్షరం *s = 0;
    s = WIN_String_గమ్యం_UTF8_W(videodata->ime_composition);
    SDL_Send_Keyboard_పాఠ్యం(s);
    SDL_free(s);

    videodata->ime_composition[0] = 0;
    videodata->ime_readingstring[0] = 0;
    videodata->ime_cursor = 0;
}

స్థిర శూన్య IME_SendEditingEvent(SDL_Video_దత్తాంశం *videodata)
{
    అక్షరం *s = ఖాళీ;
    WCHAR *బఫరు_2 = ఖాళీ;
    size_t కొలత = videodata->ime_composition_నిడివి;
    ఒకవేళ (videodata->ime_readingstring[0]) {
        size_t len = SDL_min(SDL_wcslen(videodata->ime_composition), (size_t)videodata->ime_cursor);

        కొలత += పరిమాణం(videodata->ime_readingstring);
        బఫరు_2 = (WCHAR *)SDL_malloc(కొలత + పరిమాణం(WCHAR));
        ఒకవేళ (!బఫరు_2) {
            తిరిగి;
        }
        బఫరు_2[0] = 0;

        SDL_wcslcpy(బఫరు_2, videodata->ime_composition, len + 1);
        SDL_wcslcat(బఫరు_2, videodata->ime_readingstring, కొలత);
        SDL_wcslcat(బఫరు_2, &videodata->ime_composition[len], కొలత);
    } లేకపోతే {
        బఫరు_2 = (WCHAR *)SDL_malloc(కొలత + పరిమాణం(WCHAR));
        ఒకవేళ (!బఫరు_2) {
            తిరిగి;
        }
        బఫరు_2[0] = 0;
        SDL_wcslcpy(బఫరు_2, videodata->ime_composition, కొలత);
    }

    s = WIN_String_గమ్యం_UTF8_W(బఫరు_2);
    ఒకవేళ (s) {
        ఒకవేళ (videodata->ime_readingstring[0]) {
            SDL_Send_Editing_పాఠ్యం(s, videodata->ime_cursor, (పూర్ణాంకం)SDL_wcslen(videodata->ime_readingstring));
        } లేకపోతే ఒకవేళ (videodata->ime_cursor == videodata->ime_selected_ప్రారంభం) {
            SDL_Send_Editing_పాఠ్యం(s, videodata->ime_selected_ప్రారంభం, videodata->ime_selected_నిడివి);
        } లేకపోతే {
            SDL_Send_Editing_పాఠ్యం(s, videodata->ime_cursor, 0);
        }
        ఒకవేళ (*s) {
            videodata->ime_needs_clear_composition = true;
        }
        SDL_free(s);
    }
    SDL_free(బఫరు_2);
}

స్థిర శూన్య IME_SendClearComposition(SDL_Video_దత్తాంశం *videodata)
{
    ఒకవేళ (videodata->ime_needs_clear_composition) {
        SDL_Send_Editing_పాఠ్యం("", 0, 0);
        videodata->ime_needs_clear_composition = false;
    }
}

స్థిర bool IME_OpenCandidateList(SDL_Video_దత్తాంశం *videodata)
{
    videodata->ime_candidates_open = true;
    videodata->ime_candcount = 0;
    తిరిగి true;
}

స్థిర శూన్య IME_కూడు_Candidate(SDL_Video_దత్తాంశం *videodata, UINT i, LPCWSTR candidate)
{
    ఒకవేళ (videodata->ime_candidates[i]) {
        SDL_free(videodata->ime_candidates[i]);
        videodata->ime_candidates[i] = ఖాళీ;
    }

    SDL_COMPILE_సమయం_ASSERT(IME_CANDIDATE_INDEXING_REQUIRES, MAX_CANDLIST == 10);
    అక్షరం *candidate_utf8 = WIN_String_గమ్యం_UTF8_W(candidate);
    SDL_asprintf(&videodata->ime_candidates[i], "%d %s", ((i + videodata->ime_candlistindexbase) % 10), candidate_utf8);
    SDL_free(candidate_utf8);

    videodata->ime_candcount = (i + 1);
}

స్థిర శూన్య IME_SendCandidateList(SDL_Video_దత్తాంశం *videodata)
{
    SDL_Send_Editing_పాఠ్యం_Candidates(videodata->ime_candidates, videodata->ime_candcount, videodata->ime_candsel, videodata->ime_horizontal_candidates);
}

స్థిర శూన్య IME_CloseCandidateList(SDL_Video_దత్తాంశం *videodata)
{
    videodata->ime_candidates_open = false;

    ఒకవేళ (videodata->ime_candcount > 0) {
        కొరకు (పూర్ణాంకం i = 0; i < videodata->ime_candcount; ++i) {
            SDL_free(videodata->ime_candidates[i]);
            videodata->ime_candidates[i] = ఖాళీ;
        }
        videodata->ime_candcount = 0;

        SDL_Send_Editing_పాఠ్యం_Candidates(ఖాళీ, 0, -1, false);
    }
}

స్థిర శూన్య IME_GetCandidateList(SDL_Video_దత్తాంశం *videodata, HWND hwnd)
{
    HIMC himc;
    DWORD కొలత;
    LPCANDIDATELIST cand_list;
    bool has_candidates = false;

    himc = ImmGetContext(hwnd);
    ఒకవేళ (himc) {
        కొలత = ImmGetCandidateListW(himc, 0, ఖాళీ, 0);
        ఒకవేళ (కొలత != 0) {
            cand_list = (LPCANDIDATELIST)SDL_malloc(కొలత);
            ఒకవేళ (cand_list != ఖాళీ) {
                కొలత = ImmGetCandidateListW(himc, 0, cand_list, కొలత);
                ఒకవేళ (కొలత != 0) {
                    ఒకవేళ (IME_OpenCandidateList(videodata)) {
                        UINT i, j;
                        UINT పుట_ప్రారంభం = 0;
                        UINT పుట_కొలత = 0;

                        videodata->ime_candsel = cand_list->dwSelection;

                        ఒకవేళ (LANG() == LANG_CHS && IME_GetId(videodata, 0)) {
                            స్థిరరాశి UINT maxcandchar = 18;
                            size_t cchars = 0;

                            కొరకు (i = 0; i < cand_list->dw_లెక్క; ++i) {
                                size_t len = SDL_wcslen((LPWSTR)((DWORD_PTR)cand_list + cand_list->dw_స్థానభ్రంశం[i])) + 1;
                                ఒకవేళ (len + cchars > maxcandchar) {
                                    ఒకవేళ (i > cand_list->dwSelection) {
                                        ఆపు;
                                    }

                                    పుట_ప్రారంభం = i;
                                    cchars = len;
                                } లేకపోతే {
                                    cchars += len;
                                }
                            }
                            పుట_కొలత = i - పుట_ప్రారంభం;
                        } లేకపోతే {
                            పుట_కొలత = SDL_min(cand_list->dw_పుట_కొలత == 0 ? MAX_CANDLIST : cand_list->dw_పుట_కొలత, MAX_CANDLIST);
                            పుట_ప్రారంభం = (cand_list->dwSelection / పుట_కొలత) * పుట_కొలత;
                        }
                        కొరకు (i = పుట_ప్రారంభం, j = 0; (DWORD)i < cand_list->dw_లెక్క && j < పుట_కొలత; i++, j++) {
                            LPCWSTR candidate = (LPCWSTR)((DWORD_PTR)cand_list + cand_list->dw_స్థానభ్రంశం[i]);
                            IME_కూడు_Candidate(videodata, j, candidate);
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

    ఒకవేళ (!has_candidates) {
        IME_CloseCandidateList(videodata);
    }
}

bool WIN_HandleIMEMessage(HWND hwnd, UINT సందేశం_2, WPARAM wParam, LPARAM *lParam, SDL_Video_దత్తాంశం *videodata)
{
    bool trap = false;
    HIMC himc = 0;

    ఒకవేళ (సందేశం_2 == WM_IME_SETCONTEXT) {
        SDL_DebugIMELog("WM_IME_SETCONTEXT");

        LPARAM element_ముసుగు;
        element_ముసుగు = ISC_SHOWUIALL;
        ఒకవేళ (videodata->ime_అంతర్గత_composition) {
            element_ముసుగు &= ~ISC_SHOWUICOMPOSITIONWINDOW;
        }
        ఒకవేళ (videodata->ime_అంతర్గత_candidates) {
            element_ముసుగు &= ~ISC_SHOWUIALLCANDIDATEWINDOW;
        }
        *lParam &= element_ముసుగు;

        తిరిగి false;
    } లేకపోతే ఒకవేళ (సందేశం_2 == WM_IME_STARTCOMPOSITION) {
        SDL_DebugIMELog("WM_IME_STARTCOMPOSITION");
        ఒకవేళ (videodata->ime_అంతర్గత_composition) {
            videodata->ime_cursor = 0;
            // Windows may still display a composition dialog even with
            // ISC_SHOWUICOMPOSITIONWINDOW cleared, so trap the message
            // here to prevent that (even when the IME is disabled).
            తిరిగి true;
        }
    }

    ఒకవేళ (!videodata->ime_initialized || !videodata->ime_అందుబాటు || !videodata->ime_enabled) {
        తిరిగి false;
    }

    ఎంపిక (సందేశం_2) {
    స్థితి WM_KEYDOWN:
        ఒకవేళ (wParam == VK_PROCESSKEY) {
            SDL_DebugIMELog("WM_KEYDOWN VK_PROCESSKEY");
            trap = true;
        } లేకపోతే {
            SDL_DebugIMELog("WM_KEYDOWN normal");
        }
        ఆపు;
    స్థితి WM_SYSKEYDOWN:
        ఒకవేళ (wParam == VK_PROCESSKEY) {
            SDL_DebugIMELog("WM_SYSKEYDOWN VK_PROCESSKEY");
            trap = true;
        } లేకపోతే {
            SDL_DebugIMELog("WM_SYSKEYDOWN normal");
        }
        ఆపు;
    స్థితి WM_INPUTLANGCHANGE:
        SDL_DebugIMELog("WM_INPUTLANGCHANGE");
        IME_ఆదానం_Lang_మారింది(videodata);
        ఆపు;
    స్థితి WM_IME_COMPOSITION:
        SDL_DebugIMELog("WM_IME_COMPOSITION %x", lParam);
        ఒకవేళ (videodata->ime_అంతర్గత_composition) {
            trap = true;
            himc = ImmGetContext(hwnd);
            ఒకవేళ (*lParam & GCS_RESULTSTR) {
                SDL_DebugIMELog("GCS_RESULTSTR");
                IME_GetCompositionString(videodata, himc, lParam, GCS_RESULTSTR);
                IME_SendClearComposition(videodata);
                IME_Send_ఆదానం_Event(videodata);
            }
            ఒకవేళ (*lParam & GCS_COMPSTR) {
                SDL_DebugIMELog("GCS_COMPSTR");
                videodata->ime_readingstring[0] = 0;
                IME_GetCompositionString(videodata, himc, lParam, GCS_COMPSTR);
                IME_SendEditingEvent(videodata);
            }
            ImmReleaseContext(hwnd, himc);
        }
        ఆపు;
    స్థితి WM_IME_ENDCOMPOSITION:
        SDL_DebugIMELog("WM_IME_ENDCOMPOSITION");
        ఒకవేళ (videodata->ime_అంతర్గత_composition) {
            trap = true;
            videodata->ime_composition[0] = 0;
            videodata->ime_readingstring[0] = 0;
            videodata->ime_cursor = 0;
            videodata->ime_selected_ప్రారంభం = 0;
            videodata->ime_selected_నిడివి = 0;
            IME_SendClearComposition(videodata);
        }
        ఆపు;
    స్థితి WM_IME_NOTIFY:
        SDL_DebugIMELog("WM_IME_NOTIFY %x", wParam);
        ఎంపిక (wParam) {
        స్థితి IMN_SETCOMPOSITIONWINDOW:
            SDL_DebugIMELog("IMN_SETCOMPOSITIONWINDOW");
            ఆపు;
        స్థితి IMN_SETCOMPOSITIONFONT:
            SDL_DebugIMELog("IMN_SETCOMPOSITIONFONT");
            ఆపు;
        స్థితి IMN_SETCANDIDATEPOS:
            SDL_DebugIMELog("IMN_SETCANDIDATEPOS");
            ఆపు;
        స్థితి IMN_SETCONVERSIONMODE:
        స్థితి IMN_SETOPENSTATUS:
            SDL_DebugIMELog("%s", wParam == IMN_SETCONVERSIONMODE ? "IMN_SETCONVERSIONMODE" : "IMN_SETOPENSTATUS");
            IME_Update_ఆదానం_Locale(videodata);
            ఆపు;
        స్థితి IMN_OPENCANDIDATE:
        స్థితి IMN_CHANGECANDIDATE:
            SDL_DebugIMELog("%s", wParam == IMN_OPENCANDIDATE ? "IMN_OPENCANDIDATE" : "IMN_CHANGECANDIDATE");
            ఒకవేళ (videodata->ime_అంతర్గత_candidates) {
                trap = true;
                videodata->ime_update_candidates = true;
            }
            ఆపు;
        స్థితి IMN_CLOSECANDIDATE:
            SDL_DebugIMELog("IMN_CLOSECANDIDATE");
            ఒకవేళ (videodata->ime_అంతర్గత_candidates) {
                trap = true;
                videodata->ime_update_candidates = false;
                IME_CloseCandidateList(videodata);
            }
            ఆపు;
        స్థితి IMN_వ్యక్తిగత:
        {
            DWORD dwId = IME_GetId(videodata, 0);
            SDL_DebugIMELog("IMN_PRIVATE %u", dwId);
            IME_GetReadingString(videodata, hwnd);
            ఎంపిక (dwId) {
            స్థితి IMEID_CHT_VER42:
            స్థితి IMEID_CHT_VER43:
            స్థితి IMEID_CHT_VER44:
            స్థితి IMEID_CHS_VER41:
            స్థితి IMEID_CHS_VER42:
                ఒకవేళ (*lParam == 1 || *lParam == 2) {
                    trap = true;
                }

                ఆపు;
            స్థితి IMEID_CHT_VER50:
            స్థితి IMEID_CHT_VER51:
            స్థితి IMEID_CHT_VER52:
            స్థితి IMEID_CHT_VER60:
            స్థితి IMEID_CHS_VER53:
                ఒకవేళ (*lParam == 16 || *lParam == 17 || *lParam == 26 || *lParam == 27 || *lParam == 28) {
                    trap = true;
                }
                ఆపు;
            }
        } ఆపు;
        అప్రమేయ:
            trap = true;
            ఆపు;
        }
        ఆపు;
    }
    తిరిగి trap;
}

శూన్య WIN_UpdateIMECandidates(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;

    ఒకవేళ (videodata->ime_update_candidates) {
        IME_GetCandidateList(videodata, videodata->ime_hwnd_current);
        videodata->ime_update_candidates = false;
    }
}

#అయితే_ముగింపు // SDL_DISABLE_WINDOWS_IME

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WINDOWS
