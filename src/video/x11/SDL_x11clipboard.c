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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#அந்தர்பாவ <limits.h> // For INT_MAX

#அந்தர்பாவ "SDL_x11video.h"
#அந்தர்பாவ "SDL_x11clipboard.h"
#அந்தர்பாவ "../SDL_clipboard_c.h"
#அந்தர்பாவ "../../events/SDL_events_c.h"

நிலையான மாறிலி எழுத்து *மாறிலி text_mime_types[] = {
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
    எனில் (data->clipboard_window == None) {
        Display *dpy = data->display;
        Window parent = வேர்_Window(dpy, DefaultScreen(dpy));
        XSetWindowAttributes xattr;
        data->clipboard_window = X11_XCreateWindow(dpy, parent, -10, -10, 1, 1, 0,
                                                   CopyFromParent, உள்ளீடு_Only,
                                                   வெற்று, 0, &xattr);

        X11_XSelect_உள்ளீடு(dpy, data->clipboard_window, PropertyChangeMask);
        X11_XFlush(data->display);
    }

    திரும்பு data->clipboard_window;
}

நிலையான bool SetSelectionData(SDL_VideoDevice *_this, Atom selection, SDL_ClipboardDataCallback callback,
                            வெறுமை *userdata, மாறிலி எழுத்து *மாறிலி *mime_types, size_t mime_மொத்தம், Uint32 sequence)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    Window window;
    SDLX11_ClipboardData *clipboard;
    bool clipboard_owner = false;

    window = GetWindow(_this);
    எனில் (window == None) {
        திரும்பு SDL_SetError("Couldn't find a window to own the selection");
    }

    எனில் (selection == XA_PRIMARY) {
        clipboard = &videodata->primary_selection;
    } இல்லையெனில் {
        clipboard = &videodata->clipboard;
    }

    clipboard_owner = X11_XGetSelectionOwner(display, selection) == window;

    // If we are canceling our own data we need to clean it up
    எனில் (clipboard_owner && clipboard->sequence == 0) {
        SDL_free(clipboard->userdata);
    }

    clipboard->callback = callback;
    clipboard->userdata = userdata;
    clipboard->mime_types = mime_types;
    clipboard->mime_மொத்தம் = mime_மொத்தம்;
    clipboard->sequence = sequence;

    X11_XSetSelectionOwner(display, selection, window, CurrentTime);
    திரும்பு true;
}

நிலையான வெறுமை *CloneDataBuffer(மாறிலி வெறுமை *buffer, மாறிலி size_t len)
{
    வெறுமை *clone = வெற்று;
    எனில் (len > 0 && buffer) {
        clone = SDL_malloc(len + அளவு(Uint32));
        எனில் (clone) {
            SDL_memcpy(clone, buffer, len);
            SDL_memset((Uint8 *)clone + len, 0, அளவு(Uint32));
        }
    }
    திரும்பு clone;
}

/*
 * original_buffer is considered unusable after the function is called.
 */
நிலையான வெறுமை *AppendDataBuffer(வெறுமை *original_buffer, மாறிலி size_t old_len, மாறிலி வெறுமை *buffer, மாறிலி size_t buffer_len)
{
    வெறுமை *resized_buffer;

    எனில் (buffer_len > 0 && buffer) {
        resized_buffer = SDL_realloc(original_buffer, old_len + buffer_len + அளவு(Uint32));
        எனில் (resized_buffer) {
            SDL_memcpy((Uint8 *)resized_buffer + old_len, buffer, buffer_len);
            SDL_memset((Uint8 *)resized_buffer + old_len + buffer_len, 0, அளவு(Uint32));
        }

        திரும்பு resized_buffer;
    } இல்லையெனில் {
        திரும்பு original_buffer;
    }
}

நிலையான bool WaitForSelection(SDL_VideoDevice *_this, Atom selection_type, bool *flag)
{
    Uint64 waitStart;
    Uint64 waitElapsed;

    waitStart = SDL_GetTicks();
    *flag = true;
    போது (*flag) {
        X11_PumpEvents(_this);
        waitElapsed = SDL_GetTicks() - waitStart;
        // Wait one second for a selection response.
        எனில் (waitElapsed > 1000) {
            *flag = false;
            SDL_SetError("Selection timeout");
            /* We need to set the selection text so that next time we won't
               timeout, otherwise we will hang on every call to this function. */
            SetSelectionData(_this, selection_type, SDL_ClipboardTextCallback, வெற்று,
                             text_mime_types, SDL_arraysize(text_mime_types), 0);
            திரும்பு false;
        }
    }

    திரும்பு true;
}

நிலையான வெறுமை *GetSelectionData(SDL_VideoDevice *_this, Atom selection_type,
                              மாறிலி எழுத்து *mime_type, size_t *length)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    Window window;
    Window owner;
    Atom selection;
    Atom seln_type;
    முழு seln_format;
    unsigned long மொத்தம்;
    unsigned long overflow;

    SDLX11_ClipboardData *clipboard;
    வெறுமை *data = வெற்று;
    unsigned எழுத்து *src = வெற்று;
    bool incr_success = false;
    Atom XA_MIME = X11_XInternAtom(display, mime_type, False);

    *length = 0;

    // Get the window that holds the selection
    window = GetWindow(_this);
    owner = X11_XGetSelectionOwner(display, selection_type);
    எனில் (owner == None) {
        // This requires a fallback to ancient X10 cut-buffers. We will just skip those for now
        data = வெற்று;
    } இல்லையெனில் எனில் (owner == window) {
        owner = Default_வேர்_Window(display);
        எனில் (selection_type == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } இல்லையெனில் {
            clipboard = &videodata->clipboard;
        }

        எனில் (clipboard->callback) {
            மாறிலி வெறுமை *clipboard_data = clipboard->callback(clipboard->userdata, mime_type, length);
            data = CloneDataBuffer(clipboard_data, *length);
        }
    } இல்லையெனில் {
        // Request that the selection owner copy the data to our window
        owner = window;
        selection = videodata->atoms.SDL_SELECTION;
        X11_XConvertSelection(display, selection_type, XA_MIME, selection, owner,
                              CurrentTime);

        எனில் (WaitForSelection(_this, selection_type, &videodata->selection_waiting) == false) {
            data = வெற்று;
            *length = 0;
        }

        எனில் (X11_XGetWindowProperty(display, owner, selection, 0, INT_MAX / 4, False,
                                   XA_MIME, &seln_type, &seln_format, &மொத்தம், &overflow, &src) == Success) {
            எனில் (seln_type == XA_MIME) {
                *length = (size_t)மொத்தம்;
                data = CloneDataBuffer(src, மொத்தம்);
            } இல்லையெனில் எனில் (seln_type == videodata->atoms.INCR) {
                போது (1) {
                    // Only delete the property after being done with the previous "chunk".
                    X11_XDeleteProperty(display, owner, selection);
                    X11_XFlush(display);

                    எனில் (WaitForSelection(_this, selection_type, &videodata->selection_incr_waiting) == false) {
                        நிறுத்து;
                    }

                    X11_XFree(src);
                    எனில் (X11_XGetWindowProperty(display, owner, selection, 0, INT_MAX / 4, False,
                                           XA_MIME, &seln_type, &seln_format, &மொத்தம், &overflow, &src) != Success) {
                        நிறுத்து;
                    }

                    எனில் (மொத்தம் == 0) {
                        incr_success = true;
                        நிறுத்து;
                    }

                    எனில் (*length == 0) {
                        *length = (size_t)மொத்தம்;
                        data = CloneDataBuffer(src, மொத்தம்);
                    } இல்லையெனில் {
                        data = AppendDataBuffer(data, *length, src, மொத்தம்);
                        *length += (size_t)மொத்தம்;
                    }

                    எனில் (data == வெற்று) {
                        நிறுத்து;
                    }
                }

                எனில் (incr_success == false) {
                    SDL_free(data);
                    data = வெற்று;
                    *length = 0;
                }
            }
            X11_XFree(src);
        }
    }
    திரும்பு data;
}

மாறிலி எழுத்து *மாறிலி *X11_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *இலக்கம்_mime_types)
{
    *இலக்கம்_mime_types = SDL_arraysize(text_mime_types);
    திரும்பு text_mime_types;
}

bool X11_SetClipboardData(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    திரும்பு SetSelectionData(_this, videodata->atoms.CLIPBOARD, _this->clipboard_callback, _this->clipboard_userdata, (மாறிலி எழுத்து **)_this->clipboard_mime_types, _this->இலக்கம்_clipboard_mime_types, _this->clipboard_sequence);
}

வெறுமை *X11_GetClipboardData(SDL_VideoDevice *_this, மாறிலி எழுத்து *mime_type, size_t *length)
{
    SDL_VideoData *videodata = _this->internal;

    *length = 0;

    எனில் (!SDL_HasInternalClipboardData(_this, mime_type)) {
        // This mime type wasn't advertised by the last selection owner.
        // The atom might still have data, but it's stale, so ignore it.
        திரும்பு வெற்று;
    }
    திரும்பு GetSelectionData(_this, videodata->atoms.CLIPBOARD, mime_type, length);
}

bool X11_HasClipboardData(SDL_VideoDevice *_this, மாறிலி எழுத்து *mime_type)
{
    size_t length;
    வெறுமை *data;
    data = X11_GetClipboardData(_this, mime_type, &length);
    SDL_free(data);
    திரும்பு length > 0;
}

bool X11_SetPrimarySelectionText(SDL_VideoDevice *_this, மாறிலி எழுத்து *text)
{
    திரும்பு SetSelectionData(_this, XA_PRIMARY, SDL_ClipboardTextCallback, SDL_strdup(text), text_mime_types, SDL_arraysize(text_mime_types), 0);
}

எழுத்து *X11_GetPrimarySelectionText(SDL_VideoDevice *_this)
{
    size_t length;
    எழுத்து *text = GetSelectionData(_this, XA_PRIMARY, text_mime_types[0], &length);
    எனில் (!text) {
        text = SDL_strdup("");
    }
    திரும்பு text;
}

bool X11_HasPrimarySelectionText(SDL_VideoDevice *_this)
{
    bool result = false;
    எழுத்து *text = X11_GetPrimarySelectionText(_this);
    எனில் (text) {
        எனில் (text[0] != '\0') {
            result = true;
        }
        SDL_free(text);
    }
    திரும்பு result;
}

வெறுமை X11_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    எனில் (data->primary_selection.sequence == 0) {
        SDL_free(data->primary_selection.userdata);
    }
    எனில் (data->clipboard.sequence == 0) {
        SDL_free(data->clipboard.userdata);
    }
}

#endif // SDL_VIDEO_DRIVER_X11
