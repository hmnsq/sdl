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
/*
  Screen keyboard and text input backend
  for GDK platforms.
*/
#அந்தர்பாவ "SDL_internal.h"
#அந்தர்பாவ "SDL_gdktextinput.h"

#ifdef SDL_GDK_TEXTINPUT

// GDK headers are weird here
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#அந்தர்பாவ <Windows.h>
#அந்தர்பாவ <XGameUI.h>
#அந்தர்பாவ <XUser.h>

#ifdef __cplusplus
வெளி "C" {
#endif

#அந்தர்பாவ "../../events/SDL_keyboard_c.h"
#அந்தர்பாவ "../windows/SDL_windowsvideo.h"

// TODO: Have a separate task queue for text input perhaps?
நிலையான XTaskQueueHandle g_TextTaskQueue = வெற்று;
// Global because there can be only one text entry shown at once.
நிலையான XAsyncBlock *g_TextBlock = வெற்று;

// Creation parameters
நிலையான தருக்க g_DidRegisterHints = பொய்;
நிலையான எழுத்து *g_TitleText = வெற்று;
நிலையான எழுத்து *g_DescriptionText = வெற்று;
நிலையான எழுத்து *g_DefaultText = வெற்று;
நிலையான மாறிலி Sint32 g_Default_Text_உள்ளீடு_Scope = (Sint32)XGame_Ui_Text_Entry_உள்ளீடு_Scope::Default;
நிலையான Sint32 g_Text_உள்ளீடு_Scope = g_Default_Text_உள்ளீடு_Scope;
நிலையான மாறிலி Sint32 g_DefaultMaxTextLength = 1024; // as per doc: maximum allowed amount on consoles
நிலையான Sint32 g_MaxTextLength = g_DefaultMaxTextLength;

நிலையான வெறுமை SDLCALL GDK_InternalHintCallback(
    வெறுமை *userdata,
    மாறிலி எழுத்து *name,
    மாறிலி எழுத்து *old_மதிப்பு,
    மாறிலி எழுத்து *new_மதிப்பு)
{
    எனில் (!userdata) {
        திரும்பு;
    }

    // oldValue is ignored because we store it ourselves.
    // name is ignored because we deduce it from userdata

    எனில் (userdata == &g_Text_உள்ளீடு_Scope || userdata == &g_MaxTextLength) {
        // int32 hint
        Sint32 int_மதிப்பு = (!new_மதிப்பு || new_மதிப்பு[0] == '\0') ? 0 : SDL_atoi(new_மதிப்பு);
        எனில் (userdata == &g_MaxTextLength && int_மதிப்பு <= 0) {
            int_மதிப்பு = g_DefaultMaxTextLength;
        } இல்லையெனில் எனில் (userdata == &g_Text_உள்ளீடு_Scope && int_மதிப்பு < 0) {
            int_மதிப்பு = g_Default_Text_உள்ளீடு_Scope;
        }

        *(Sint32 *)userdata = int_மதிப்பு;
    } இல்லையெனில் {
        // string hint
        எனில் (!new_மதிப்பு || new_மதிப்பு[0] == '\0') {
            // treat empty or NULL strings as just NULL for this impl
            SDL_free(*(எழுத்து **)userdata);
            *(எழுத்து **)userdata = வெற்று;
        } இல்லையெனில் {
            எழுத்து *newString = SDL_strdup(new_மதிப்பு);
            எனில் (newString) {
                // free previous value and write the new one
                SDL_free(*(எழுத்து **)userdata);
                *(எழுத்து **)userdata = newString;
            }
        }
    }
}

நிலையான தருக்க GDK_InternalEnsureTaskQueue(வெறுமை)
{
    எனில் (!g_TextTaskQueue) {
        எனில் (!SDL_GetGDKTaskQueue(&g_TextTaskQueue)) {
            // SetError will be done for us.
            திரும்பு பொய்;
        }
    }
    திரும்பு உண்மை;
}

நிலையான வெறுமை CALLBACK GDK_InternalTextEntryCallback(XAsyncBlock *asyncBlock)
{
    HRESULT hR = S_OK;
    Uint32 resultSize = 0;
    Uint32 resultUsed = 0;
    எழுத்து *resultBuffer = வெற்று;

    // The keyboard will be already hidden when we reach this code

    எனில் (FAILED(hR = XGameUiShowTextEntryResultSize(
                   asyncBlock,
                   &resultSize))) {
        SDL_SetError("XGameUiShowTextEntryResultSize failure with HRESULT of %08X", hR);
    } இல்லையெனில் எனில் (resultSize > 0) {
        // +1 to be super sure that the buffer will be null terminated
        resultBuffer = (எழுத்து *)SDL_calloc(1 + (size_t)resultSize, அளவு(*resultBuffer));
        எனில் (resultBuffer) {
            // still pass the original size that we got from ResultSize
            எனில் (FAILED(hR = XGameUiShowTextEntryResult(
                           asyncBlock,
                           resultSize,
                           resultBuffer,
                           &resultUsed))) {
                SDL_SetError("XGameUiShowTextEntryResult failure with HRESULT of %08X", hR);
            }
            // check that we have some text and that we weren't cancelled
            இல்லையெனில் எனில் (resultUsed > 0 && resultBuffer[0] != '\0') {
                // it's null terminated so it's fine
                SDL_SendKeyboardText(resultBuffer);
            }
            // we're done with the buffer
            SDL_free(resultBuffer);
            resultBuffer = வெற்று;
        }
    }

    // free the async block after we're done
    SDL_free(asyncBlock);
    asyncBlock = வெற்று;
    g_TextBlock = வெற்று; // once we do this we're fully done with the keyboard

    SDL_SendScreenKeyboardHidden();
}

வெறுமை GDK_EnsureHints(வெறுமை)
{
    எனில் (g_DidRegisterHints == பொய்) {
        SDL_AddHintCallback(
            SDL_HINT_GDK_TEXTINPUT_TITLE,
            GDK_InternalHintCallback,
            &g_TitleText);
        SDL_AddHintCallback(
            SDL_HINT_GDK_TEXTINPUT_DESCRIPTION,
            GDK_InternalHintCallback,
            &g_DescriptionText);
        SDL_AddHintCallback(
            SDL_HINT_GDK_TEXTINPUT_DEFAULT_TEXT,
            GDK_InternalHintCallback,
            &g_DefaultText);
        SDL_AddHintCallback(
            SDL_HINT_GDK_TEXTINPUT_SCOPE,
            GDK_InternalHintCallback,
            &g_Text_உள்ளீடு_Scope);
        SDL_AddHintCallback(
            SDL_HINT_GDK_TEXTINPUT_MAX_LENGTH,
            GDK_InternalHintCallback,
            &g_MaxTextLength);
        g_DidRegisterHints = உண்மை;
    }
}

தருக்க GDK_Start_Text_உள்ளீடு(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    /*
     * Currently a stub, since all input is handled by the virtual keyboard,
     * but perhaps when implementing XGameUiTextEntryOpen in the future
     * you will need this.
     *
     * Also XGameUiTextEntryOpen docs say that it is
     * "not implemented on desktop" so... no thanks.
     *
     * Right now this function isn't implemented on Desktop
     * and seems to be present only in the docs? So I didn't bother.
     */
    திரும்பு உண்மை;
}

தருக்க GDK_Stop_Text_உள்ளீடு(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    திரும்பு உண்மை;
}

தருக்க GDK_Update_Text_உள்ளீடு_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
    /*
     * XGameUiShowTextEntryAsync does not allow you to set
     * the position of the virtual keyboard window.
     *
     * However, XGameUiTextEntryOpen seems to allow that,
     * but again, see notice in GDK_StartTextInput.
     *
     * Right now it's a stub which may be useful later.
     */
    திரும்பு உண்மை;
}

தருக்க GDK_ClearComposition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    திரும்பு உண்மை;
}

தருக்க GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    // Currently always true for this input method
    திரும்பு உண்மை;
}

வெறுமை GDK_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    /*
     * There is XGameUiTextEntryOpen but it's only in online docs,
     * My October Update 1 GDKX installation does not have this function defined
     * and as such I decided not to use it at all, since some folks might use even older GDKs.
     *
     * That means the only text input option for us is a simple virtual keyboard widget.
     */

    HRESULT hR = S_OK;

    எனில் (g_TextBlock) {
        // already showing the keyboard
        திரும்பு;
    }

    எனில் (!GDK_InternalEnsureTaskQueue()) {
        // unable to obtain the SDL GDK queue
        திரும்பு;
    }

    g_TextBlock = (XAsyncBlock *)SDL_calloc(1, அளவு(*g_TextBlock));
    எனில் (!g_TextBlock) {
        திரும்பு;
    }

    XGame_Ui_Text_Entry_உள்ளீடு_Scope scope;
    தேர்வு (SDL_Get_Text_உள்ளீடு_Type(props)) {
    இயல்பு:
    நிலை SDL_TEXTINPUT_TYPE_TEXT:
        scope = (XGame_Ui_Text_Entry_உள்ளீடு_Scope)g_Text_உள்ளீடு_Scope;
        நிறுத்து;
    நிலை SDL_TEXTINPUT_TYPE_TEXT_NAME:
        scope = XGame_Ui_Text_Entry_உள்ளீடு_Scope::Default;
        நிறுத்து;
    நிலை SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        scope = XGame_Ui_Text_Entry_உள்ளீடு_Scope::EmailSmtpAddress;
        நிறுத்து;
    நிலை SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        scope = XGame_Ui_Text_Entry_உள்ளீடு_Scope::Default;
        நிறுத்து;
    நிலை SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        scope = XGame_Ui_Text_Entry_உள்ளீடு_Scope::Password;
        நிறுத்து;
    நிலை SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_Entry_உள்ளீடு_Scope::Default;
        நிறுத்து;
    நிலை SDL_TEXTINPUT_TYPE_எண்:
        scope = XGame_Ui_Text_Entry_உள்ளீடு_Scope::எண்;
        நிறுத்து;
    நிலை SDL_TEXTINPUT_TYPE_எண்_PASSWORD_HIDDEN:
        // FIXME: Password or number scope?
        scope = XGame_Ui_Text_Entry_உள்ளீடு_Scope::எண்;
        நிறுத்து;
    நிலை SDL_TEXTINPUT_TYPE_எண்_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_Entry_உள்ளீடு_Scope::எண்;
        நிறுத்து;
    }

    g_TextBlock->queue = g_TextTaskQueue;
    g_TextBlock->context = _this;
    g_TextBlock->callback = GDK_InternalTextEntryCallback;
    எனில் (SUCCEEDED(hR = XGameUiShowTextEntryAsync(
                   g_TextBlock,
                   g_TitleText,
                   g_DescriptionText,
                   g_DefaultText,
                   scope,
                   (uint32_t)g_MaxTextLength))) {
        SDL_SendScreenKeyboardShown();
    } இல்லையெனில் {
        SDL_free(g_TextBlock);
        g_TextBlock = வெற்று;
        SDL_SetError("XGameUiShowTextEntryAsync failure with HRESULT of %08X", hR);
    }
}

வெறுமை GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    எனில் (g_TextBlock) {
        XAsyncCancel(g_TextBlock);
        // the completion callback will free the block
    }
}

#ifdef __cplusplus
}
#endif

#endif
