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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#અન્તર્ભાવ <limits.h> // For INT_MAX

#અન્તર્ભાવ "SDL_x11video.h"
#અન્તર્ભાવ "SDL_x11clipboard.h"
#અન્તર્ભાવ "../SDL_clipboard_c.h"
#અન્તર્ભાવ "../../events/SDL_events_c.h"

સ્થિર અચલ અક્ષર *અચલ text_mime_types[] = {
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
    જો (data->clipboard_window == None) {
        Display *dpy = data->display;
        Window parent = મૂળ_Window(dpy, DefaultScreen(dpy));
        XSetWindowAttributes xattr;
        data->clipboard_window = X11_XCreateWindow(dpy, parent, -10, -10, 1, 1, 0,
                                                   CopyFromParent, આગત_Only,
                                                   ખાલી, 0, &xattr);

        X11_XSelect_આગત(dpy, data->clipboard_window, PropertyChangeMask);
        X11_XFlush(data->display);
    }

    પાછા data->clipboard_window;
}

સ્થિર bool SetSelectionData(SDL_VideoDevice *_this, Atom selection, SDL_ClipboardDataCallback callback,
                            શૂન્ય *userdata, અચલ અક્ષર *અચલ *mime_types, size_t mime_ગણતરી, Uint32 sequence)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    Window window;
    SDLX11_ClipboardData *clipboard;
    bool clipboard_owner = false;

    window = GetWindow(_this);
    જો (window == None) {
        પાછા SDL_SetError("Couldn't find a window to own the selection");
    }

    જો (selection == XA_PRIMARY) {
        clipboard = &videodata->primary_selection;
    } નહીંતર {
        clipboard = &videodata->clipboard;
    }

    clipboard_owner = X11_XGetSelectionOwner(display, selection) == window;

    // If we are canceling our own data we need to clean it up
    જો (clipboard_owner && clipboard->sequence == 0) {
        SDL_free(clipboard->userdata);
    }

    clipboard->callback = callback;
    clipboard->userdata = userdata;
    clipboard->mime_types = mime_types;
    clipboard->mime_ગણતરી = mime_ગણતરી;
    clipboard->sequence = sequence;

    X11_XSetSelectionOwner(display, selection, window, CurrentTime);
    પાછા true;
}

સ્થિર શૂન્ય *CloneDataBuffer(અચલ શૂન્ય *buffer, અચલ size_t len)
{
    શૂન્ય *clone = ખાલી;
    જો (len > 0 && buffer) {
        clone = SDL_malloc(len + કદ(Uint32));
        જો (clone) {
            SDL_memcpy(clone, buffer, len);
            SDL_memset((Uint8 *)clone + len, 0, કદ(Uint32));
        }
    }
    પાછા clone;
}

/*
 * original_buffer is considered unusable after the function is called.
 */
સ્થિર શૂન્ય *AppendDataBuffer(શૂન્ય *original_buffer, અચલ size_t old_len, અચલ શૂન્ય *buffer, અચલ size_t buffer_len)
{
    શૂન્ય *resized_buffer;

    જો (buffer_len > 0 && buffer) {
        resized_buffer = SDL_realloc(original_buffer, old_len + buffer_len + કદ(Uint32));
        જો (resized_buffer) {
            SDL_memcpy((Uint8 *)resized_buffer + old_len, buffer, buffer_len);
            SDL_memset((Uint8 *)resized_buffer + old_len + buffer_len, 0, કદ(Uint32));
        }

        પાછા resized_buffer;
    } નહીંતર {
        પાછા original_buffer;
    }
}

સ્થિર bool WaitForSelection(SDL_VideoDevice *_this, Atom selection_type, bool *flag)
{
    Uint64 waitStart;
    Uint64 waitElapsed;

    waitStart = SDL_GetTicks();
    *flag = true;
    જ્યારે (*flag) {
        X11_PumpEvents(_this);
        waitElapsed = SDL_GetTicks() - waitStart;
        // Wait one second for a selection response.
        જો (waitElapsed > 1000) {
            *flag = false;
            SDL_SetError("Selection timeout");
            /* We need to set the selection text so that next time we won't
               timeout, otherwise we will hang on every call to this function. */
            SetSelectionData(_this, selection_type, SDL_ClipboardTextCallback, ખાલી,
                             text_mime_types, SDL_arraysize(text_mime_types), 0);
            પાછા false;
        }
    }

    પાછા true;
}

સ્થિર શૂન્ય *GetSelectionData(SDL_VideoDevice *_this, Atom selection_type,
                              અચલ અક્ષર *mime_type, size_t *length)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    Window window;
    Window owner;
    Atom selection;
    Atom seln_type;
    પૂર્ણાંક seln_format;
    unsigned long ગણતરી;
    unsigned long overflow;

    SDLX11_ClipboardData *clipboard;
    શૂન્ય *data = ખાલી;
    unsigned અક્ષર *src = ખાલી;
    bool incr_success = false;
    Atom XA_MIME = X11_XInternAtom(display, mime_type, False);

    *length = 0;

    // Get the window that holds the selection
    window = GetWindow(_this);
    owner = X11_XGetSelectionOwner(display, selection_type);
    જો (owner == None) {
        // This requires a fallback to ancient X10 cut-buffers. We will just skip those for now
        data = ખાલી;
    } નહીંતર જો (owner == window) {
        owner = Default_મૂળ_Window(display);
        જો (selection_type == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } નહીંતર {
            clipboard = &videodata->clipboard;
        }

        જો (clipboard->callback) {
            અચલ શૂન્ય *clipboard_data = clipboard->callback(clipboard->userdata, mime_type, length);
            data = CloneDataBuffer(clipboard_data, *length);
        }
    } નહીંતર {
        // Request that the selection owner copy the data to our window
        owner = window;
        selection = videodata->atoms.SDL_SELECTION;
        X11_XConvertSelection(display, selection_type, XA_MIME, selection, owner,
                              CurrentTime);

        જો (WaitForSelection(_this, selection_type, &videodata->selection_waiting) == false) {
            data = ખાલી;
            *length = 0;
        }

        જો (X11_XGetWindowProperty(display, owner, selection, 0, INT_MAX / 4, False,
                                   XA_MIME, &seln_type, &seln_format, &ગણતરી, &overflow, &src) == Success) {
            જો (seln_type == XA_MIME) {
                *length = (size_t)ગણતરી;
                data = CloneDataBuffer(src, ગણતરી);
            } નહીંતર જો (seln_type == videodata->atoms.INCR) {
                જ્યારે (1) {
                    // Only delete the property after being done with the previous "chunk".
                    X11_XDeleteProperty(display, owner, selection);
                    X11_XFlush(display);

                    જો (WaitForSelection(_this, selection_type, &videodata->selection_incr_waiting) == false) {
                        તોડો;
                    }

                    X11_XFree(src);
                    જો (X11_XGetWindowProperty(display, owner, selection, 0, INT_MAX / 4, False,
                                           XA_MIME, &seln_type, &seln_format, &ગણતરી, &overflow, &src) != Success) {
                        તોડો;
                    }

                    જો (ગણતરી == 0) {
                        incr_success = true;
                        તોડો;
                    }

                    જો (*length == 0) {
                        *length = (size_t)ગણતરી;
                        data = CloneDataBuffer(src, ગણતરી);
                    } નહીંતર {
                        data = AppendDataBuffer(data, *length, src, ગણતરી);
                        *length += (size_t)ગણતરી;
                    }

                    જો (data == ખાલી) {
                        તોડો;
                    }
                }

                જો (incr_success == false) {
                    SDL_free(data);
                    data = ખાલી;
                    *length = 0;
                }
            }
            X11_XFree(src);
        }
    }
    પાછા data;
}

અચલ અક્ષર *અચલ *X11_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *અંક_mime_types)
{
    *અંક_mime_types = SDL_arraysize(text_mime_types);
    પાછા text_mime_types;
}

bool X11_SetClipboardData(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    પાછા SetSelectionData(_this, videodata->atoms.CLIPBOARD, _this->clipboard_callback, _this->clipboard_userdata, (અચલ અક્ષર **)_this->clipboard_mime_types, _this->અંક_clipboard_mime_types, _this->clipboard_sequence);
}

શૂન્ય *X11_GetClipboardData(SDL_VideoDevice *_this, અચલ અક્ષર *mime_type, size_t *length)
{
    SDL_VideoData *videodata = _this->internal;

    *length = 0;

    જો (!SDL_HasInternalClipboardData(_this, mime_type)) {
        // This mime type wasn't advertised by the last selection owner.
        // The atom might still have data, but it's stale, so ignore it.
        પાછા ખાલી;
    }
    પાછા GetSelectionData(_this, videodata->atoms.CLIPBOARD, mime_type, length);
}

bool X11_HasClipboardData(SDL_VideoDevice *_this, અચલ અક્ષર *mime_type)
{
    size_t length;
    શૂન્ય *data;
    data = X11_GetClipboardData(_this, mime_type, &length);
    SDL_free(data);
    પાછા length > 0;
}

bool X11_SetPrimarySelectionText(SDL_VideoDevice *_this, અચલ અક્ષર *text)
{
    પાછા SetSelectionData(_this, XA_PRIMARY, SDL_ClipboardTextCallback, SDL_strdup(text), text_mime_types, SDL_arraysize(text_mime_types), 0);
}

અક્ષર *X11_GetPrimarySelectionText(SDL_VideoDevice *_this)
{
    size_t length;
    અક્ષર *text = GetSelectionData(_this, XA_PRIMARY, text_mime_types[0], &length);
    જો (!text) {
        text = SDL_strdup("");
    }
    પાછા text;
}

bool X11_HasPrimarySelectionText(SDL_VideoDevice *_this)
{
    bool result = false;
    અક્ષર *text = X11_GetPrimarySelectionText(_this);
    જો (text) {
        જો (text[0] != '\0') {
            result = true;
        }
        SDL_free(text);
    }
    પાછા result;
}

શૂન્ય X11_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    જો (data->primary_selection.sequence == 0) {
        SDL_free(data->primary_selection.userdata);
    }
    જો (data->clipboard.sequence == 0) {
        SDL_free(data->clipboard.userdata);
    }
}

#endif // SDL_VIDEO_DRIVER_X11
