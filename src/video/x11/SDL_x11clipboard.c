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

#ifdef SDL_VIDEO_DRIVER_X11

#ಅನ್ತರ್ಭಾವ <limits.h> // For INT_MAX

#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11clipboard.h"
#ಅನ್ತರ್ಭಾವ "../SDL_clipboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"

ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ text_mime_types[] = {
    "UTF8_STRING",
    "text/plain;charset=utf-8",
    "text/plain",
    "TEXT",
    "STRING"
};

// Get any application owned window handle for clipboard association
Window GetWindow(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    /* We create an unmapped window that exists just to manage the clipboard,
       since X11 selection data is tied to a specific window and dies with it.
       We create the window on demand, so apps that don't use the clipboard
       don't have to keep an unnecessary resource around. */
    ಯದಿ (data->clipboard_window == None) {
        Display *dpy = data->display;
        Window parent = ಬೇರು_Window(dpy, DefaultScreen(dpy));
        XSetWindowAttributes xattr;
        data->clipboard_window = X11_XCreateWindow(dpy, parent, -10, -10, 1, 1, 0,
                                                   CopyFromParent, ಒಳಹರಿವು_Only,
                                                   ರಿಕ್ತ, 0, &xattr);

        X11_XSelect_ಒಳಹರಿವು(dpy, data->clipboard_window, PropertyChangeMask);
        X11_XFlush(data->display);
    }

    ಪ್ರತ್ಯಾಗಮ data->clipboard_window;
}

ಸ್ಥಿರ bool SetSelectionData(SDL_VideoDevice *_this, Atom selection, SDL_ClipboardDataCallback callback,
                            ಶೂನ್ಯ *userdata, ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ *mime_types, size_t mime_ಎಣಿಕೆ, Uint32 sequence)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    Window window;
    SDLX11_ClipboardData *clipboard;
    bool clipboard_owner = false;

    window = GetWindow(_this);
    ಯದಿ (window == None) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Couldn't find a window to own the selection");
    }

    ಯದಿ (selection == XA_PRIMARY) {
        clipboard = &videodata->primary_selection;
    } ಅನ್ಯಥಾ {
        clipboard = &videodata->clipboard;
    }

    clipboard_owner = X11_XGetSelectionOwner(display, selection) == window;

    // If we are canceling our own data we need to clean it up
    ಯದಿ (clipboard_owner && clipboard->sequence == 0) {
        SDL_free(clipboard->userdata);
    }

    clipboard->callback = callback;
    clipboard->userdata = userdata;
    clipboard->mime_types = mime_types;
    clipboard->mime_ಎಣಿಕೆ = mime_ಎಣಿಕೆ;
    clipboard->sequence = sequence;

    X11_XSetSelectionOwner(display, selection, window, CurrentTime);
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ *CloneDataBuffer(ಧ್ರುವ ಶೂನ್ಯ *buffer, ಧ್ರುವ size_t len)
{
    ಶೂನ್ಯ *clone = ರಿಕ್ತ;
    ಯದಿ (len > 0 && buffer) {
        clone = SDL_malloc(len + ಪರಿಮಾಣ(Uint32));
        ಯದಿ (clone) {
            SDL_memcpy(clone, buffer, len);
            SDL_memset((Uint8 *)clone + len, 0, ಪರಿಮಾಣ(Uint32));
        }
    }
    ಪ್ರತ್ಯಾಗಮ clone;
}

/*
 * original_buffer is considered unusable after the function is called.
 */
ಸ್ಥಿರ ಶೂನ್ಯ *AppendDataBuffer(ಶೂನ್ಯ *original_buffer, ಧ್ರುವ size_t old_len, ಧ್ರುವ ಶೂನ್ಯ *buffer, ಧ್ರುವ size_t buffer_len)
{
    ಶೂನ್ಯ *resized_buffer;

    ಯದಿ (buffer_len > 0 && buffer) {
        resized_buffer = SDL_realloc(original_buffer, old_len + buffer_len + ಪರಿಮಾಣ(Uint32));
        ಯದಿ (resized_buffer) {
            SDL_memcpy((Uint8 *)resized_buffer + old_len, buffer, buffer_len);
            SDL_memset((Uint8 *)resized_buffer + old_len + buffer_len, 0, ಪರಿಮಾಣ(Uint32));
        }

        ಪ್ರತ್ಯಾಗಮ resized_buffer;
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ original_buffer;
    }
}

ಸ್ಥಿರ bool WaitForSelection(SDL_VideoDevice *_this, Atom selection_type, bool *flag)
{
    Uint64 waitStart;
    Uint64 waitElapsed;

    waitStart = SDL_GetTicks();
    *flag = true;
    ಯಾವತ್ (*flag) {
        X11_PumpEvents(_this);
        waitElapsed = SDL_GetTicks() - waitStart;
        // Wait one second for a selection response.
        ಯದಿ (waitElapsed > 1000) {
            *flag = false;
            SDL_SetError("Selection timeout");
            /* We need to set the selection text so that next time we won't
               timeout, otherwise we will hang on every call to this function. */
            SetSelectionData(_this, selection_type, SDL_ClipboardTextCallback, ರಿಕ್ತ,
                             text_mime_types, SDL_arraysize(text_mime_types), 0);
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ *GetSelectionData(SDL_VideoDevice *_this, Atom selection_type,
                              ಧ್ರುವ ವರ್ಣ *mime_type, size_t *length)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    Window window;
    Window owner;
    Atom selection;
    Atom seln_type;
    ಪೂರ್ಣಾಙ್ಕ seln_format;
    unsigned long ಎಣಿಕೆ;
    unsigned long overflow;

    SDLX11_ClipboardData *clipboard;
    ಶೂನ್ಯ *data = ರಿಕ್ತ;
    unsigned ವರ್ಣ *src = ರಿಕ್ತ;
    bool incr_success = false;
    Atom XA_MIME = X11_XInternAtom(display, mime_type, False);

    *length = 0;

    // Get the window that holds the selection
    window = GetWindow(_this);
    owner = X11_XGetSelectionOwner(display, selection_type);
    ಯದಿ (owner == None) {
        // This requires a fallback to ancient X10 cut-buffers. We will just skip those for now
        data = ರಿಕ್ತ;
    } ಅನ್ಯಥಾ ಯದಿ (owner == window) {
        owner = Default_ಬೇರು_Window(display);
        ಯದಿ (selection_type == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } ಅನ್ಯಥಾ {
            clipboard = &videodata->clipboard;
        }

        ಯದಿ (clipboard->callback) {
            ಧ್ರುವ ಶೂನ್ಯ *clipboard_data = clipboard->callback(clipboard->userdata, mime_type, length);
            data = CloneDataBuffer(clipboard_data, *length);
        }
    } ಅನ್ಯಥಾ {
        // Request that the selection owner copy the data to our window
        owner = window;
        selection = videodata->atoms.SDL_SELECTION;
        X11_XConvertSelection(display, selection_type, XA_MIME, selection, owner,
                              CurrentTime);

        ಯದಿ (WaitForSelection(_this, selection_type, &videodata->selection_waiting) == false) {
            data = ರಿಕ್ತ;
            *length = 0;
        }

        ಯದಿ (X11_XGetWindowProperty(display, owner, selection, 0, INT_MAX / 4, False,
                                   XA_MIME, &seln_type, &seln_format, &ಎಣಿಕೆ, &overflow, &src) == Success) {
            ಯದಿ (seln_type == XA_MIME) {
                *length = (size_t)ಎಣಿಕೆ;
                data = CloneDataBuffer(src, ಎಣಿಕೆ);
            } ಅನ್ಯಥಾ ಯದಿ (seln_type == videodata->atoms.INCR) {
                ಯಾವತ್ (1) {
                    // Only delete the property after being done with the previous "chunk".
                    X11_XDeleteProperty(display, owner, selection);
                    X11_XFlush(display);

                    ಯದಿ (WaitForSelection(_this, selection_type, &videodata->selection_incr_waiting) == false) {
                        ಭಙ್ಗ;
                    }

                    X11_XFree(src);
                    ಯದಿ (X11_XGetWindowProperty(display, owner, selection, 0, INT_MAX / 4, False,
                                           XA_MIME, &seln_type, &seln_format, &ಎಣಿಕೆ, &overflow, &src) != Success) {
                        ಭಙ್ಗ;
                    }

                    ಯದಿ (ಎಣಿಕೆ == 0) {
                        incr_success = true;
                        ಭಙ್ಗ;
                    }

                    ಯದಿ (*length == 0) {
                        *length = (size_t)ಎಣಿಕೆ;
                        data = CloneDataBuffer(src, ಎಣಿಕೆ);
                    } ಅನ್ಯಥಾ {
                        data = AppendDataBuffer(data, *length, src, ಎಣಿಕೆ);
                        *length += (size_t)ಎಣಿಕೆ;
                    }

                    ಯದಿ (data == ರಿಕ್ತ) {
                        ಭಙ್ಗ;
                    }
                }

                ಯದಿ (incr_success == false) {
                    SDL_free(data);
                    data = ರಿಕ್ತ;
                    *length = 0;
                }
            }
            X11_XFree(src);
        }
    }
    ಪ್ರತ್ಯಾಗಮ data;
}

ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ *X11_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *ಅಂಕೆ_mime_types)
{
    *ಅಂಕೆ_mime_types = SDL_arraysize(text_mime_types);
    ಪ್ರತ್ಯಾಗಮ text_mime_types;
}

bool X11_SetClipboardData(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    ಪ್ರತ್ಯಾಗಮ SetSelectionData(_this, videodata->atoms.CLIPBOARD, _this->clipboard_callback, _this->clipboard_userdata, (ಧ್ರುವ ವರ್ಣ **)_this->clipboard_mime_types, _this->ಅಂಕೆ_clipboard_mime_types, _this->clipboard_sequence);
}

ಶೂನ್ಯ *X11_GetClipboardData(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *mime_type, size_t *length)
{
    SDL_VideoData *videodata = _this->internal;

    *length = 0;

    ಯದಿ (!SDL_HasInternalClipboardData(_this, mime_type)) {
        // This mime type wasn't advertised by the last selection owner.
        // The atom might still have data, but it's stale, so ignore it.
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಪ್ರತ್ಯಾಗಮ GetSelectionData(_this, videodata->atoms.CLIPBOARD, mime_type, length);
}

bool X11_HasClipboardData(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *mime_type)
{
    size_t length;
    ಶೂನ್ಯ *data;
    data = X11_GetClipboardData(_this, mime_type, &length);
    SDL_free(data);
    ಪ್ರತ್ಯಾಗಮ length > 0;
}

bool X11_SetPrimarySelectionText(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *text)
{
    ಪ್ರತ್ಯಾಗಮ SetSelectionData(_this, XA_PRIMARY, SDL_ClipboardTextCallback, SDL_strdup(text), text_mime_types, SDL_arraysize(text_mime_types), 0);
}

ವರ್ಣ *X11_GetPrimarySelectionText(SDL_VideoDevice *_this)
{
    size_t length;
    ವರ್ಣ *text = GetSelectionData(_this, XA_PRIMARY, text_mime_types[0], &length);
    ಯದಿ (!text) {
        text = SDL_strdup("");
    }
    ಪ್ರತ್ಯಾಗಮ text;
}

bool X11_HasPrimarySelectionText(SDL_VideoDevice *_this)
{
    bool result = false;
    ವರ್ಣ *text = X11_GetPrimarySelectionText(_this);
    ಯದಿ (text) {
        ಯದಿ (text[0] != '\0') {
            result = true;
        }
        SDL_free(text);
    }
    ಪ್ರತ್ಯಾಗಮ result;
}

ಶೂನ್ಯ X11_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    ಯದಿ (data->primary_selection.sequence == 0) {
        SDL_free(data->primary_selection.userdata);
    }
    ಯದಿ (data->clipboard.sequence == 0) {
        SDL_free(data->clipboard.userdata);
    }
}

#endif // SDL_VIDEO_DRIVER_X11
