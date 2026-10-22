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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11

#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h> // For INT_MAX

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11video.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11clipboard.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_clipboard_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *ਅਚਲ ਪਾਠ_mime_types[] = {
    "UTF8_STRING",
    "text/plain;charset=utf-8",
    "text/plain",
    "TEXT",
    "STRING"
};

// Get any application owned window handle for clipboard association
ਖਿੜਕੀ_2 Get_ਖਿੜਕੀ(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    /* We create an unmapped window that exists just to manage the clipboard,
       since X11 selection data is tied to a specific window and dies with it.
       We create the window on demand, so apps that don't use the clipboard
       don't have to keep an unnecessary resource around. */
    ਜੇ (ਅੰਕੜੇ->clipboard_ਖਿੜਕੀ == None) {
        Display *dpy = ਅੰਕੜੇ->display;
        ਖਿੜਕੀ_2 ਮਾਪਾ = ਜੜ੍ਹ_ਖਿੜਕੀ(dpy, DefaultScreen(dpy));
        XSet_ਖਿੜਕੀ_ਗੁਣ xattr;
        ਅੰਕੜੇ->clipboard_ਖਿੜਕੀ = X11_XCreate_ਖਿੜਕੀ(dpy, ਮਾਪਾ, -10, -10, 1, 1, 0,
                                                   Copy_From_ਮਾਪਾ, ਨਿਵੇਸ਼_Only,
                                                   ਨਿਰਾ, 0, &xattr);

        X11_XSelect_ਨਿਵੇਸ਼(dpy, ਅੰਕੜੇ->clipboard_ਖਿੜਕੀ, Property_Change_ਨਕਾਬ);
        X11_XFlush(ਅੰਕੜੇ->display);
    }

    ਵਾਪਸ ਅੰਕੜੇ->clipboard_ਖਿੜਕੀ;
}

ਸਥਿਰ bool ਸੈੱਟ_Selection_ਅੰਕੜੇ(SDL_VideoDevice *_this, Atom selection, SDL_Clipboard_ਅੰਕੜੇ_Callback callback,
                            ਖਾਲੀ *userdata, ਅਚਲ ਅੱਖਰ *ਅਚਲ *mime_types, size_t mime_ਗਿਣਤੀ, Uint32 sequence)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    Display *display = videodata->display;
    ਖਿੜਕੀ_2 ਖਿੜਕੀ;
    SDLX11_Clipboard_ਅੰਕੜੇ *clipboard;
    bool clipboard_owner = false;

    ਖਿੜਕੀ = Get_ਖਿੜਕੀ(_this);
    ਜੇ (ਖਿੜਕੀ == None) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't find a window to own the selection");
    }

    ਜੇ (selection == XA_PRIMARY) {
        clipboard = &videodata->primary_selection;
    } ਨਹੀਂਤਾਂ {
        clipboard = &videodata->clipboard;
    }

    clipboard_owner = X11_XGetSelectionOwner(display, selection) == ਖਿੜਕੀ;

    // If we are canceling our own data we need to clean it up
    ਜੇ (clipboard_owner && clipboard->sequence == 0) {
        SDL_free(clipboard->userdata);
    }

    clipboard->callback = callback;
    clipboard->userdata = userdata;
    clipboard->mime_types = mime_types;
    clipboard->mime_ਗਿਣਤੀ = mime_ਗਿਣਤੀ;
    clipboard->sequence = sequence;

    X11_XSetSelectionOwner(display, selection, ਖਿੜਕੀ, Current_ਸਮਾਂ);
    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ *Clone_ਅੰਕੜੇ_ਬਫਰ(ਅਚਲ ਖਾਲੀ *ਬਫਰ_2, ਅਚਲ size_t len)
{
    ਖਾਲੀ *clone = ਨਿਰਾ;
    ਜੇ (len > 0 && ਬਫਰ_2) {
        clone = SDL_malloc(len + ਆਕਾਰ(Uint32));
        ਜੇ (clone) {
            SDL_memcpy(clone, ਬਫਰ_2, len);
            SDL_memset((Uint8 *)clone + len, 0, ਆਕਾਰ(Uint32));
        }
    }
    ਵਾਪਸ clone;
}

/*
 * original_buffer is considered unusable after the function is called.
 */
ਸਥਿਰ ਖਾਲੀ *Append_ਅੰਕੜੇ_ਬਫਰ(ਖਾਲੀ *original_ਬਫਰ, ਅਚਲ size_t old_len, ਅਚਲ ਖਾਲੀ *ਬਫਰ_2, ਅਚਲ size_t ਬਫਰ_len)
{
    ਖਾਲੀ *resized_ਬਫਰ;

    ਜੇ (ਬਫਰ_len > 0 && ਬਫਰ_2) {
        resized_ਬਫਰ = SDL_realloc(original_ਬਫਰ, old_len + ਬਫਰ_len + ਆਕਾਰ(Uint32));
        ਜੇ (resized_ਬਫਰ) {
            SDL_memcpy((Uint8 *)resized_ਬਫਰ + old_len, ਬਫਰ_2, ਬਫਰ_len);
            SDL_memset((Uint8 *)resized_ਬਫਰ + old_len + ਬਫਰ_len, 0, ਆਕਾਰ(Uint32));
        }

        ਵਾਪਸ resized_ਬਫਰ;
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ original_ਬਫਰ;
    }
}

ਸਥਿਰ bool WaitForSelection(SDL_VideoDevice *_this, Atom selection_type, bool *flag)
{
    Uint64 wait_ਸ਼ੁਰੂ;
    Uint64 waitElapsed;

    wait_ਸ਼ੁਰੂ = SDL_GetTicks();
    *flag = true;
    ਜਦੋਂ (*flag) {
        X11_PumpEvents(_this);
        waitElapsed = SDL_GetTicks() - wait_ਸ਼ੁਰੂ;
        // Wait one second for a selection response.
        ਜੇ (waitElapsed > 1000) {
            *flag = false;
            SDL_ਸੈੱਟ_Error("Selection timeout");
            /* We need to set the selection text so that next time we won't
               timeout, otherwise we will hang on every call to this function. */
            ਸੈੱਟ_Selection_ਅੰਕੜੇ(_this, selection_type, SDL_Clipboard_ਪਾਠ_Callback, ਨਿਰਾ,
                             ਪਾਠ_mime_types, SDL_arraysize(ਪਾਠ_mime_types), 0);
            ਵਾਪਸ false;
        }
    }

    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ *Get_Selection_ਅੰਕੜੇ(SDL_VideoDevice *_this, Atom selection_type,
                              ਅਚਲ ਅੱਖਰ *mime_type, size_t *ਲੰਮਾਈ)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    Display *display = videodata->display;
    ਖਿੜਕੀ_2 ਖਿੜਕੀ;
    ਖਿੜਕੀ_2 owner;
    Atom selection;
    Atom seln_type;
    ਪੂਰਨ seln_format;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਗਿਣਤੀ_2;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਉਛਾਲ;

    SDLX11_Clipboard_ਅੰਕੜੇ *clipboard;
    ਖਾਲੀ *ਅੰਕੜੇ = ਨਿਰਾ;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *src = ਨਿਰਾ;
    bool incr_success = false;
    Atom XA_MIME = X11_XInternAtom(display, mime_type, False);

    *ਲੰਮਾਈ = 0;

    // Get the window that holds the selection
    ਖਿੜਕੀ = Get_ਖਿੜਕੀ(_this);
    owner = X11_XGetSelectionOwner(display, selection_type);
    ਜੇ (owner == None) {
        // This requires a fallback to ancient X10 cut-buffers. We will just skip those for now
        ਅੰਕੜੇ = ਨਿਰਾ;
    } ਨਹੀਂਤਾਂ ਜੇ (owner == ਖਿੜਕੀ) {
        owner = Default_ਜੜ੍ਹ_ਖਿੜਕੀ(display);
        ਜੇ (selection_type == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } ਨਹੀਂਤਾਂ {
            clipboard = &videodata->clipboard;
        }

        ਜੇ (clipboard->callback) {
            ਅਚਲ ਖਾਲੀ *clipboard_ਅੰਕੜੇ = clipboard->callback(clipboard->userdata, mime_type, ਲੰਮਾਈ);
            ਅੰਕੜੇ = Clone_ਅੰਕੜੇ_ਬਫਰ(clipboard_ਅੰਕੜੇ, *ਲੰਮਾਈ);
        }
    } ਨਹੀਂਤਾਂ {
        // Request that the selection owner copy the data to our window
        owner = ਖਿੜਕੀ;
        selection = videodata->atoms.SDL_SELECTION;
        X11_XConvertSelection(display, selection_type, XA_MIME, selection, owner,
                              Current_ਸਮਾਂ);

        ਜੇ (WaitForSelection(_this, selection_type, &videodata->selection_ਉਡੀਕ) == false) {
            ਅੰਕੜੇ = ਨਿਰਾ;
            *ਲੰਮਾਈ = 0;
        }

        ਜੇ (X11_XGet_ਖਿੜਕੀ_Property(display, owner, selection, 0, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ / 4, False,
                                   XA_MIME, &seln_type, &seln_format, &ਗਿਣਤੀ_2, &ਉਛਾਲ, &src) == Success) {
            ਜੇ (seln_type == XA_MIME) {
                *ਲੰਮਾਈ = (size_t)ਗਿਣਤੀ_2;
                ਅੰਕੜੇ = Clone_ਅੰਕੜੇ_ਬਫਰ(src, ਗਿਣਤੀ_2);
            } ਨਹੀਂਤਾਂ ਜੇ (seln_type == videodata->atoms.INCR) {
                ਜਦੋਂ (1) {
                    // Only delete the property after being done with the previous "chunk".
                    X11_XDeleteProperty(display, owner, selection);
                    X11_XFlush(display);

                    ਜੇ (WaitForSelection(_this, selection_type, &videodata->selection_incr_ਉਡੀਕ) == false) {
                        ਰੋਕੋ;
                    }

                    X11_XFree(src);
                    ਜੇ (X11_XGet_ਖਿੜਕੀ_Property(display, owner, selection, 0, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ / 4, False,
                                           XA_MIME, &seln_type, &seln_format, &ਗਿਣਤੀ_2, &ਉਛਾਲ, &src) != Success) {
                        ਰੋਕੋ;
                    }

                    ਜੇ (ਗਿਣਤੀ_2 == 0) {
                        incr_success = true;
                        ਰੋਕੋ;
                    }

                    ਜੇ (*ਲੰਮਾਈ == 0) {
                        *ਲੰਮਾਈ = (size_t)ਗਿਣਤੀ_2;
                        ਅੰਕੜੇ = Clone_ਅੰਕੜੇ_ਬਫਰ(src, ਗਿਣਤੀ_2);
                    } ਨਹੀਂਤਾਂ {
                        ਅੰਕੜੇ = Append_ਅੰਕੜੇ_ਬਫਰ(ਅੰਕੜੇ, *ਲੰਮਾਈ, src, ਗਿਣਤੀ_2);
                        *ਲੰਮਾਈ += (size_t)ਗਿਣਤੀ_2;
                    }

                    ਜੇ (ਅੰਕੜੇ == ਨਿਰਾ) {
                        ਰੋਕੋ;
                    }
                }

                ਜੇ (incr_success == false) {
                    SDL_free(ਅੰਕੜੇ);
                    ਅੰਕੜੇ = ਨਿਰਾ;
                    *ਲੰਮਾਈ = 0;
                }
            }
            X11_XFree(src);
        }
    }
    ਵਾਪਸ ਅੰਕੜੇ;
}

ਅਚਲ ਅੱਖਰ *ਅਚਲ *X11_Get_ਪਾਠ_Mime_Types(SDL_VideoDevice *_this, size_t *ਅੰਕ_mime_types)
{
    *ਅੰਕ_mime_types = SDL_arraysize(ਪਾਠ_mime_types);
    ਵਾਪਸ ਪਾਠ_mime_types;
}

bool X11_ਸੈੱਟ_Clipboard_ਅੰਕੜੇ(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    ਵਾਪਸ ਸੈੱਟ_Selection_ਅੰਕੜੇ(_this, videodata->atoms.CLIPBOARD, _this->clipboard_callback, _this->clipboard_userdata, (ਅਚਲ ਅੱਖਰ **)_this->clipboard_mime_types, _this->ਅੰਕ_clipboard_mime_types, _this->clipboard_sequence);
}

ਖਾਲੀ *X11_Get_Clipboard_ਅੰਕੜੇ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *mime_type, size_t *ਲੰਮਾਈ)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;

    *ਲੰਮਾਈ = 0;

    ਜੇ (!SDL_Has_ਅੰਦਰੂਨੀ_Clipboard_ਅੰਕੜੇ(_this, mime_type)) {
        // This mime type wasn't advertised by the last selection owner.
        // The atom might still have data, but it's stale, so ignore it.
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਵਾਪਸ Get_Selection_ਅੰਕੜੇ(_this, videodata->atoms.CLIPBOARD, mime_type, ਲੰਮਾਈ);
}

bool X11_Has_Clipboard_ਅੰਕੜੇ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *mime_type)
{
    size_t ਲੰਮਾਈ;
    ਖਾਲੀ *ਅੰਕੜੇ;
    ਅੰਕੜੇ = X11_Get_Clipboard_ਅੰਕੜੇ(_this, mime_type, &ਲੰਮਾਈ);
    SDL_free(ਅੰਕੜੇ);
    ਵਾਪਸ ਲੰਮਾਈ > 0;
}

bool X11_ਸੈੱਟ_Primary_Selection_ਪਾਠ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਪਾਠ)
{
    ਵਾਪਸ ਸੈੱਟ_Selection_ਅੰਕੜੇ(_this, XA_PRIMARY, SDL_Clipboard_ਪਾਠ_Callback, SDL_strdup(ਪਾਠ), ਪਾਠ_mime_types, SDL_arraysize(ਪਾਠ_mime_types), 0);
}

ਅੱਖਰ *X11_Get_Primary_Selection_ਪਾਠ(SDL_VideoDevice *_this)
{
    size_t ਲੰਮਾਈ;
    ਅੱਖਰ *ਪਾਠ = Get_Selection_ਅੰਕੜੇ(_this, XA_PRIMARY, ਪਾਠ_mime_types[0], &ਲੰਮਾਈ);
    ਜੇ (!ਪਾਠ) {
        ਪਾਠ = SDL_strdup("");
    }
    ਵਾਪਸ ਪਾਠ;
}

bool X11_Has_Primary_Selection_ਪਾਠ(SDL_VideoDevice *_this)
{
    bool ਨਤੀਜਾ = false;
    ਅੱਖਰ *ਪਾਠ = X11_Get_Primary_Selection_ਪਾਠ(_this);
    ਜੇ (ਪਾਠ) {
        ਜੇ (ਪਾਠ[0] != '\0') {
            ਨਤੀਜਾ = true;
        }
        SDL_free(ਪਾਠ);
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

ਖਾਲੀ X11_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    ਜੇ (ਅੰਕੜੇ->primary_selection.sequence == 0) {
        SDL_free(ਅੰਕੜੇ->primary_selection.userdata);
    }
    ਜੇ (ਅੰਕੜੇ->clipboard.sequence == 0) {
        SDL_free(ਅੰਕੜੇ->clipboard.userdata);
    }
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11
