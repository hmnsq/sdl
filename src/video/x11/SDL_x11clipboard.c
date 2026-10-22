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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#ଅନ୍ତର୍ଭାଵ <limits.h> // For INT_MAX

#ଅନ୍ତର୍ଭାଵ "SDL_x11video.h"
#ଅନ୍ତର୍ଭାଵ "SDL_x11clipboard.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_clipboard_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_events_c.h"

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *ଅଚଳ text_mime_types[] = {
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
    ଯଦି (data->clipboard_window == None) {
        Display *dpy = data->display;
        Window parent = ମୂଳ_Window(dpy, DefaultScreen(dpy));
        XSetWindowAttributes xattr;
        data->clipboard_window = X11_XCreateWindow(dpy, parent, -10, -10, 1, 1, 0,
                                                   CopyFromParent, ନିବେଶ_Only,
                                                   ଖାଲି, 0, &xattr);

        X11_XSelect_ନିବେଶ(dpy, data->clipboard_window, PropertyChangeMask);
        X11_XFlush(data->display);
    }

    ଫେରନ୍ତୁ data->clipboard_window;
}

ସ୍ଥିର bool SetSelectionData(SDL_VideoDevice *_this, Atom selection, SDL_ClipboardDataCallback callback,
                            ଶୂନ୍ୟ *userdata, ଅଚଳ ଅକ୍ଷର *ଅଚଳ *mime_types, size_t mime_ଗଣନା, Uint32 sequence)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    Window window;
    SDLX11_ClipboardData *clipboard;
    bool clipboard_owner = false;

    window = GetWindow(_this);
    ଯଦି (window == None) {
        ଫେରନ୍ତୁ SDL_SetError("Couldn't find a window to own the selection");
    }

    ଯଦି (selection == XA_PRIMARY) {
        clipboard = &videodata->primary_selection;
    } ଅନ୍ୟଥା {
        clipboard = &videodata->clipboard;
    }

    clipboard_owner = X11_XGetSelectionOwner(display, selection) == window;

    // If we are canceling our own data we need to clean it up
    ଯଦି (clipboard_owner && clipboard->sequence == 0) {
        SDL_free(clipboard->userdata);
    }

    clipboard->callback = callback;
    clipboard->userdata = userdata;
    clipboard->mime_types = mime_types;
    clipboard->mime_ଗଣନା = mime_ଗଣନା;
    clipboard->sequence = sequence;

    X11_XSetSelectionOwner(display, selection, window, CurrentTime);
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର ଶୂନ୍ୟ *CloneDataBuffer(ଅଚଳ ଶୂନ୍ୟ *buffer, ଅଚଳ size_t len)
{
    ଶୂନ୍ୟ *clone = ଖାଲି;
    ଯଦି (len > 0 && buffer) {
        clone = SDL_malloc(len + ଆକାର(Uint32));
        ଯଦି (clone) {
            SDL_memcpy(clone, buffer, len);
            SDL_memset((Uint8 *)clone + len, 0, ଆକାର(Uint32));
        }
    }
    ଫେରନ୍ତୁ clone;
}

/*
 * original_buffer is considered unusable after the function is called.
 */
ସ୍ଥିର ଶୂନ୍ୟ *AppendDataBuffer(ଶୂନ୍ୟ *original_buffer, ଅଚଳ size_t old_len, ଅଚଳ ଶୂନ୍ୟ *buffer, ଅଚଳ size_t buffer_len)
{
    ଶୂନ୍ୟ *resized_buffer;

    ଯଦି (buffer_len > 0 && buffer) {
        resized_buffer = SDL_realloc(original_buffer, old_len + buffer_len + ଆକାର(Uint32));
        ଯଦି (resized_buffer) {
            SDL_memcpy((Uint8 *)resized_buffer + old_len, buffer, buffer_len);
            SDL_memset((Uint8 *)resized_buffer + old_len + buffer_len, 0, ଆକାର(Uint32));
        }

        ଫେରନ୍ତୁ resized_buffer;
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ original_buffer;
    }
}

ସ୍ଥିର bool WaitForSelection(SDL_VideoDevice *_this, Atom selection_type, bool *flag)
{
    Uint64 waitStart;
    Uint64 waitElapsed;

    waitStart = SDL_GetTicks();
    *flag = true;
    ଯେତେବେଳେ (*flag) {
        X11_PumpEvents(_this);
        waitElapsed = SDL_GetTicks() - waitStart;
        // Wait one second for a selection response.
        ଯଦି (waitElapsed > 1000) {
            *flag = false;
            SDL_SetError("Selection timeout");
            /* We need to set the selection text so that next time we won't
               timeout, otherwise we will hang on every call to this function. */
            SetSelectionData(_this, selection_type, SDL_ClipboardTextCallback, ଖାଲି,
                             text_mime_types, SDL_arraysize(text_mime_types), 0);
            ଫେରନ୍ତୁ false;
        }
    }

    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର ଶୂନ୍ୟ *GetSelectionData(SDL_VideoDevice *_this, Atom selection_type,
                              ଅଚଳ ଅକ୍ଷର *mime_type, size_t *length)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    Window window;
    Window owner;
    Atom selection;
    Atom seln_type;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା seln_format;
    unsigned long ଗଣନା_2;
    unsigned long overflow;

    SDLX11_ClipboardData *clipboard;
    ଶୂନ୍ୟ *data = ଖାଲି;
    unsigned ଅକ୍ଷର *src = ଖାଲି;
    bool incr_success = false;
    Atom XA_MIME = X11_XInternAtom(display, mime_type, False);

    *length = 0;

    // Get the window that holds the selection
    window = GetWindow(_this);
    owner = X11_XGetSelectionOwner(display, selection_type);
    ଯଦି (owner == None) {
        // This requires a fallback to ancient X10 cut-buffers. We will just skip those for now
        data = ଖାଲି;
    } ଅନ୍ୟଥା ଯଦି (owner == window) {
        owner = Default_ମୂଳ_Window(display);
        ଯଦି (selection_type == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } ଅନ୍ୟଥା {
            clipboard = &videodata->clipboard;
        }

        ଯଦି (clipboard->callback) {
            ଅଚଳ ଶୂନ୍ୟ *clipboard_data = clipboard->callback(clipboard->userdata, mime_type, length);
            data = CloneDataBuffer(clipboard_data, *length);
        }
    } ଅନ୍ୟଥା {
        // Request that the selection owner copy the data to our window
        owner = window;
        selection = videodata->atoms.SDL_SELECTION;
        X11_XConvertSelection(display, selection_type, XA_MIME, selection, owner,
                              CurrentTime);

        ଯଦି (WaitForSelection(_this, selection_type, &videodata->selection_waiting) == false) {
            data = ଖାଲି;
            *length = 0;
        }

        ଯଦି (X11_XGetWindowProperty(display, owner, selection, 0, INT_MAX / 4, False,
                                   XA_MIME, &seln_type, &seln_format, &ଗଣନା_2, &overflow, &src) == Success) {
            ଯଦି (seln_type == XA_MIME) {
                *length = (size_t)ଗଣନା_2;
                data = CloneDataBuffer(src, ଗଣନା_2);
            } ଅନ୍ୟଥା ଯଦି (seln_type == videodata->atoms.INCR) {
                ଯେତେବେଳେ (1) {
                    // Only delete the property after being done with the previous "chunk".
                    X11_XDeleteProperty(display, owner, selection);
                    X11_XFlush(display);

                    ଯଦି (WaitForSelection(_this, selection_type, &videodata->selection_incr_waiting) == false) {
                        ଭାଙ୍ଗ;
                    }

                    X11_XFree(src);
                    ଯଦି (X11_XGetWindowProperty(display, owner, selection, 0, INT_MAX / 4, False,
                                           XA_MIME, &seln_type, &seln_format, &ଗଣନା_2, &overflow, &src) != Success) {
                        ଭାଙ୍ଗ;
                    }

                    ଯଦି (ଗଣନା_2 == 0) {
                        incr_success = true;
                        ଭାଙ୍ଗ;
                    }

                    ଯଦି (*length == 0) {
                        *length = (size_t)ଗଣନା_2;
                        data = CloneDataBuffer(src, ଗଣନା_2);
                    } ଅନ୍ୟଥା {
                        data = AppendDataBuffer(data, *length, src, ଗଣନା_2);
                        *length += (size_t)ଗଣନା_2;
                    }

                    ଯଦି (data == ଖାଲି) {
                        ଭାଙ୍ଗ;
                    }
                }

                ଯଦି (incr_success == false) {
                    SDL_free(data);
                    data = ଖାଲି;
                    *length = 0;
                }
            }
            X11_XFree(src);
        }
    }
    ଫେରନ୍ତୁ data;
}

ଅଚଳ ଅକ୍ଷର *ଅଚଳ *X11_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *ଅଙ୍କ_mime_types)
{
    *ଅଙ୍କ_mime_types = SDL_arraysize(text_mime_types);
    ଫେରନ୍ତୁ text_mime_types;
}

bool X11_SetClipboardData(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    ଫେରନ୍ତୁ SetSelectionData(_this, videodata->atoms.CLIPBOARD, _this->clipboard_callback, _this->clipboard_userdata, (ଅଚଳ ଅକ୍ଷର **)_this->clipboard_mime_types, _this->ଅଙ୍କ_clipboard_mime_types, _this->clipboard_sequence);
}

ଶୂନ୍ୟ *X11_GetClipboardData(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *mime_type, size_t *length)
{
    SDL_VideoData *videodata = _this->internal;

    *length = 0;

    ଯଦି (!SDL_HasInternalClipboardData(_this, mime_type)) {
        // This mime type wasn't advertised by the last selection owner.
        // The atom might still have data, but it's stale, so ignore it.
        ଫେରନ୍ତୁ ଖାଲି;
    }
    ଫେରନ୍ତୁ GetSelectionData(_this, videodata->atoms.CLIPBOARD, mime_type, length);
}

bool X11_HasClipboardData(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *mime_type)
{
    size_t length;
    ଶୂନ୍ୟ *data;
    data = X11_GetClipboardData(_this, mime_type, &length);
    SDL_free(data);
    ଫେରନ୍ତୁ length > 0;
}

bool X11_SetPrimarySelectionText(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *text)
{
    ଫେରନ୍ତୁ SetSelectionData(_this, XA_PRIMARY, SDL_ClipboardTextCallback, SDL_strdup(text), text_mime_types, SDL_arraysize(text_mime_types), 0);
}

ଅକ୍ଷର *X11_GetPrimarySelectionText(SDL_VideoDevice *_this)
{
    size_t length;
    ଅକ୍ଷର *text = GetSelectionData(_this, XA_PRIMARY, text_mime_types[0], &length);
    ଯଦି (!text) {
        text = SDL_strdup("");
    }
    ଫେରନ୍ତୁ text;
}

bool X11_HasPrimarySelectionText(SDL_VideoDevice *_this)
{
    bool result = false;
    ଅକ୍ଷର *text = X11_GetPrimarySelectionText(_this);
    ଯଦି (text) {
        ଯଦି (text[0] != '\0') {
            result = true;
        }
        SDL_free(text);
    }
    ଫେରନ୍ତୁ result;
}

ଶୂନ୍ୟ X11_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    ଯଦି (data->primary_selection.sequence == 0) {
        SDL_free(data->primary_selection.userdata);
    }
    ଯଦି (data->clipboard.sequence == 0) {
        SDL_free(data->clipboard.userdata);
    }
}

#endif // SDL_VIDEO_DRIVER_X11
