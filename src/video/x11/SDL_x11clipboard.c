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
#شامل "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#شامل <limits.h> // For INT_MAX

#شامل "SDL_x11video.h"
#شامل "SDL_x11clipboard.h"
#شامل "../SDL_clipboard_c.h"
#شامل "../../events/SDL_events_c.h"

ایستا ثابت نویسه *ثابت text_mime_types[] = {
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
    اگر (data->clipboard_window == None) {
        Display *dpy = data->display;
        Window parent = ریشه_Window(dpy, DefaultScreen(dpy));
        XSetWindowAttributes xattr;
        data->clipboard_window = X11_XCreateWindow(dpy, parent, -10, -10, 1, 1, 0,
                                                   CopyFromParent, درون_داد_Only,
                                                   پوچ, 0, &xattr);

        X11_XSelect_درون_داد(dpy, data->clipboard_window, PropertyChangeMask);
        X11_XFlush(data->display);
    }

    بازگشت data->clipboard_window;
}

ایستا bool SetSelectionData(SDL_VideoDevice *_this, Atom selection, SDL_ClipboardDataCallback callback,
                            تهی *userdata, ثابت نویسه *ثابت *mime_types, size_t mime_شمار, Uint32 sequence)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    Window window;
    SDLX11_ClipboardData *clipboard;
    bool clipboard_owner = false;

    window = GetWindow(_this);
    اگر (window == None) {
        بازگشت SDL_SetError("Couldn't find a window to own the selection");
    }

    اگر (selection == XA_PRIMARY) {
        clipboard = &videodata->primary_selection;
    } وگرنه {
        clipboard = &videodata->clipboard;
    }

    clipboard_owner = X11_XGetSelectionOwner(display, selection) == window;

    // If we are canceling our own data we need to clean it up
    اگر (clipboard_owner && clipboard->sequence == 0) {
        SDL_free(clipboard->userdata);
    }

    clipboard->callback = callback;
    clipboard->userdata = userdata;
    clipboard->mime_types = mime_types;
    clipboard->mime_شمار = mime_شمار;
    clipboard->sequence = sequence;

    X11_XSetSelectionOwner(display, selection, window, CurrentTime);
    بازگشت true;
}

ایستا تهی *CloneDataBuffer(ثابت تهی *buffer, ثابت size_t len)
{
    تهی *clone = پوچ;
    اگر (len > 0 && buffer) {
        clone = SDL_malloc(len + اندازه(Uint32));
        اگر (clone) {
            SDL_memcpy(clone, buffer, len);
            SDL_memset((Uint8 *)clone + len, 0, اندازه(Uint32));
        }
    }
    بازگشت clone;
}

/*
 * original_buffer is considered unusable after the function is called.
 */
ایستا تهی *AppendDataBuffer(تهی *original_buffer, ثابت size_t old_len, ثابت تهی *buffer, ثابت size_t buffer_len)
{
    تهی *resized_buffer;

    اگر (buffer_len > 0 && buffer) {
        resized_buffer = SDL_realloc(original_buffer, old_len + buffer_len + اندازه(Uint32));
        اگر (resized_buffer) {
            SDL_memcpy((Uint8 *)resized_buffer + old_len, buffer, buffer_len);
            SDL_memset((Uint8 *)resized_buffer + old_len + buffer_len, 0, اندازه(Uint32));
        }

        بازگشت resized_buffer;
    } وگرنه {
        بازگشت original_buffer;
    }
}

ایستا bool WaitForSelection(SDL_VideoDevice *_this, Atom selection_type, bool *flag)
{
    Uint64 waitStart;
    Uint64 waitElapsed;

    waitStart = SDL_GetTicks();
    *flag = true;
    وقتی (*flag) {
        X11_PumpEvents(_this);
        waitElapsed = SDL_GetTicks() - waitStart;
        // Wait one second for a selection response.
        اگر (waitElapsed > 1000) {
            *flag = false;
            SDL_SetError("Selection timeout");
            /* We need to set the selection text so that next time we won't
               timeout, otherwise we will hang on every call to this function. */
            SetSelectionData(_this, selection_type, SDL_ClipboardTextCallback, پوچ,
                             text_mime_types, SDL_arraysize(text_mime_types), 0);
            بازگشت false;
        }
    }

    بازگشت true;
}

ایستا تهی *GetSelectionData(SDL_VideoDevice *_this, Atom selection_type,
                              ثابت نویسه *mime_type, size_t *length)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    Window window;
    Window owner;
    Atom selection;
    Atom seln_type;
    صحیح seln_format;
    unsigned long شمار;
    unsigned long overflow;

    SDLX11_ClipboardData *clipboard;
    تهی *data = پوچ;
    unsigned نویسه *src = پوچ;
    bool incr_success = false;
    Atom XA_MIME = X11_XInternAtom(display, mime_type, False);

    *length = 0;

    // Get the window that holds the selection
    window = GetWindow(_this);
    owner = X11_XGetSelectionOwner(display, selection_type);
    اگر (owner == None) {
        // This requires a fallback to ancient X10 cut-buffers. We will just skip those for now
        data = پوچ;
    } وگرنه اگر (owner == window) {
        owner = Default_ریشه_Window(display);
        اگر (selection_type == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } وگرنه {
            clipboard = &videodata->clipboard;
        }

        اگر (clipboard->callback) {
            ثابت تهی *clipboard_data = clipboard->callback(clipboard->userdata, mime_type, length);
            data = CloneDataBuffer(clipboard_data, *length);
        }
    } وگرنه {
        // Request that the selection owner copy the data to our window
        owner = window;
        selection = videodata->atoms.SDL_SELECTION;
        X11_XConvertSelection(display, selection_type, XA_MIME, selection, owner,
                              CurrentTime);

        اگر (WaitForSelection(_this, selection_type, &videodata->selection_waiting) == false) {
            data = پوچ;
            *length = 0;
        }

        اگر (X11_XGetWindowProperty(display, owner, selection, 0, INT_MAX / 4, False,
                                   XA_MIME, &seln_type, &seln_format, &شمار, &overflow, &src) == Success) {
            اگر (seln_type == XA_MIME) {
                *length = (size_t)شمار;
                data = CloneDataBuffer(src, شمار);
            } وگرنه اگر (seln_type == videodata->atoms.INCR) {
                وقتی (1) {
                    // Only delete the property after being done with the previous "chunk".
                    X11_XDeleteProperty(display, owner, selection);
                    X11_XFlush(display);

                    اگر (WaitForSelection(_this, selection_type, &videodata->selection_incr_waiting) == false) {
                        بشکن;
                    }

                    X11_XFree(src);
                    اگر (X11_XGetWindowProperty(display, owner, selection, 0, INT_MAX / 4, False,
                                           XA_MIME, &seln_type, &seln_format, &شمار, &overflow, &src) != Success) {
                        بشکن;
                    }

                    اگر (شمار == 0) {
                        incr_success = true;
                        بشکن;
                    }

                    اگر (*length == 0) {
                        *length = (size_t)شمار;
                        data = CloneDataBuffer(src, شمار);
                    } وگرنه {
                        data = AppendDataBuffer(data, *length, src, شمار);
                        *length += (size_t)شمار;
                    }

                    اگر (data == پوچ) {
                        بشکن;
                    }
                }

                اگر (incr_success == false) {
                    SDL_free(data);
                    data = پوچ;
                    *length = 0;
                }
            }
            X11_XFree(src);
        }
    }
    بازگشت data;
}

ثابت نویسه *ثابت *X11_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *رقم_mime_types)
{
    *رقم_mime_types = SDL_arraysize(text_mime_types);
    بازگشت text_mime_types;
}

bool X11_SetClipboardData(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    بازگشت SetSelectionData(_this, videodata->atoms.CLIPBOARD, _this->clipboard_callback, _this->clipboard_userdata, (ثابت نویسه **)_this->clipboard_mime_types, _this->رقم_clipboard_mime_types, _this->clipboard_sequence);
}

تهی *X11_GetClipboardData(SDL_VideoDevice *_this, ثابت نویسه *mime_type, size_t *length)
{
    SDL_VideoData *videodata = _this->internal;

    *length = 0;

    اگر (!SDL_HasInternalClipboardData(_this, mime_type)) {
        // This mime type wasn't advertised by the last selection owner.
        // The atom might still have data, but it's stale, so ignore it.
        بازگشت پوچ;
    }
    بازگشت GetSelectionData(_this, videodata->atoms.CLIPBOARD, mime_type, length);
}

bool X11_HasClipboardData(SDL_VideoDevice *_this, ثابت نویسه *mime_type)
{
    size_t length;
    تهی *data;
    data = X11_GetClipboardData(_this, mime_type, &length);
    SDL_free(data);
    بازگشت length > 0;
}

bool X11_SetPrimarySelectionText(SDL_VideoDevice *_this, ثابت نویسه *text)
{
    بازگشت SetSelectionData(_this, XA_PRIMARY, SDL_ClipboardTextCallback, SDL_strdup(text), text_mime_types, SDL_arraysize(text_mime_types), 0);
}

نویسه *X11_GetPrimarySelectionText(SDL_VideoDevice *_this)
{
    size_t length;
    نویسه *text = GetSelectionData(_this, XA_PRIMARY, text_mime_types[0], &length);
    اگر (!text) {
        text = SDL_strdup("");
    }
    بازگشت text;
}

bool X11_HasPrimarySelectionText(SDL_VideoDevice *_this)
{
    bool result = false;
    نویسه *text = X11_GetPrimarySelectionText(_this);
    اگر (text) {
        اگر (text[0] != '\0') {
            result = true;
        }
        SDL_free(text);
    }
    بازگشت result;
}

تهی X11_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    اگر (data->primary_selection.sequence == 0) {
        SDL_free(data->primary_selection.userdata);
    }
    اگر (data->clipboard.sequence == 0) {
        SDL_free(data->clipboard.userdata);
    }
}

#endif // SDL_VIDEO_DRIVER_X11
