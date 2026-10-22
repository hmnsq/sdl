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
#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#include <limits.h> // For INT_MAX

#include "SDL_x11video.h"
#include "SDL_x11clipboard.h"
#include "../SDL_clipboard_c.h"
#include "../../events/SDL_events_c.h"

static const char *const text_mime_types[] = {
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
    만약 (data->clipboard_window == None) {
        Display *dpy = data->display;
        Window parent = RootWindow(dpy, DefaultScreen(dpy));
        XSetWindowAttributes xattr;
        data->clipboard_window = X11_XCreateWindow(dpy, parent, -10, -10, 1, 1, 0,
                                                   CopyFromParent, InputOnly,
                                                   NULL, 0, &xattr);

        X11_XSelectInput(dpy, data->clipboard_window, PropertyChangeMask);
        X11_XFlush(data->display);
    }

    반환 data->clipboard_window;
}

static bool SetSelectionData(SDL_VideoDevice *_this, Atom selection, SDL_ClipboardDataCallback callback,
                            void *userdata, const char *const *mime_types, size_t mime_count, Uint32 sequence)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    Window window;
    SDLX11_ClipboardData *clipboard;
    bool clipboard_owner = false;

    window = GetWindow(_this);
    만약 (window == None) {
        반환 SDL_SetError("Couldn't find a window to own the selection");
    }

    만약 (selection == XA_PRIMARY) {
        clipboard = &videodata->primary_selection;
    } 아니면 {
        clipboard = &videodata->clipboard;
    }

    clipboard_owner = X11_XGetSelectionOwner(display, selection) == window;

    // If we are canceling our own data we need to clean it up
    만약 (clipboard_owner && clipboard->sequence == 0) {
        SDL_free(clipboard->userdata);
    }

    clipboard->callback = callback;
    clipboard->userdata = userdata;
    clipboard->mime_types = mime_types;
    clipboard->mime_count = mime_count;
    clipboard->sequence = sequence;

    X11_XSetSelectionOwner(display, selection, window, CurrentTime);
    반환 true;
}

static void *CloneDataBuffer(const void *buffer, const size_t len)
{
    void *clone = NULL;
    만약 (len > 0 && buffer) {
        clone = SDL_malloc(len + sizeof(Uint32));
        만약 (clone) {
            SDL_memcpy(clone, buffer, len);
            SDL_memset((Uint8 *)clone + len, 0, sizeof(Uint32));
        }
    }
    반환 clone;
}

/*
 * original_buffer is considered unusable after the function is called.
 */
static void *AppendDataBuffer(void *original_buffer, const size_t old_len, const void *buffer, const size_t buffer_len)
{
    void *resized_buffer;

    만약 (buffer_len > 0 && buffer) {
        resized_buffer = SDL_realloc(original_buffer, old_len + buffer_len + sizeof(Uint32));
        만약 (resized_buffer) {
            SDL_memcpy((Uint8 *)resized_buffer + old_len, buffer, buffer_len);
            SDL_memset((Uint8 *)resized_buffer + old_len + buffer_len, 0, sizeof(Uint32));
        }

        반환 resized_buffer;
    } 아니면 {
        반환 original_buffer;
    }
}

static bool WaitForSelection(SDL_VideoDevice *_this, Atom selection_type, bool *flag)
{
    Uint64 waitStart;
    Uint64 waitElapsed;

    waitStart = SDL_GetTicks();
    *flag = true;
    동안 (*flag) {
        X11_PumpEvents(_this);
        waitElapsed = SDL_GetTicks() - waitStart;
        // Wait one second for a selection response.
        만약 (waitElapsed > 1000) {
            *flag = false;
            SDL_SetError("Selection timeout");
            /* We need to set the selection text so that next time we won't
               timeout, otherwise we will hang on every call to this function. */
            SetSelectionData(_this, selection_type, SDL_ClipboardTextCallback, NULL,
                             text_mime_types, SDL_arraysize(text_mime_types), 0);
            반환 false;
        }
    }

    반환 true;
}

static void *GetSelectionData(SDL_VideoDevice *_this, Atom selection_type,
                              const char *mime_type, size_t *length)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    Window window;
    Window owner;
    Atom selection;
    Atom seln_type;
    정수 seln_format;
    unsigned long count;
    unsigned long overflow;

    SDLX11_ClipboardData *clipboard;
    void *data = NULL;
    unsigned char *src = NULL;
    bool incr_success = false;
    Atom XA_MIME = X11_XInternAtom(display, mime_type, False);

    *length = 0;

    // Get the window that holds the selection
    window = GetWindow(_this);
    owner = X11_XGetSelectionOwner(display, selection_type);
    만약 (owner == None) {
        // This requires a fallback to ancient X10 cut-buffers. We will just skip those for now
        data = NULL;
    } 아니면 만약 (owner == window) {
        owner = DefaultRootWindow(display);
        만약 (selection_type == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } 아니면 {
            clipboard = &videodata->clipboard;
        }

        만약 (clipboard->callback) {
            const void *clipboard_data = clipboard->callback(clipboard->userdata, mime_type, length);
            data = CloneDataBuffer(clipboard_data, *length);
        }
    } 아니면 {
        // Request that the selection owner copy the data to our window
        owner = window;
        selection = videodata->atoms.SDL_SELECTION;
        X11_XConvertSelection(display, selection_type, XA_MIME, selection, owner,
                              CurrentTime);

        만약 (WaitForSelection(_this, selection_type, &videodata->selection_waiting) == false) {
            data = NULL;
            *length = 0;
        }

        만약 (X11_XGetWindowProperty(display, owner, selection, 0, INT_MAX / 4, False,
                                   XA_MIME, &seln_type, &seln_format, &count, &overflow, &src) == Success) {
            만약 (seln_type == XA_MIME) {
                *length = (size_t)count;
                data = CloneDataBuffer(src, count);
            } 아니면 만약 (seln_type == videodata->atoms.INCR) {
                동안 (1) {
                    // Only delete the property after being done with the previous "chunk".
                    X11_XDeleteProperty(display, owner, selection);
                    X11_XFlush(display);

                    만약 (WaitForSelection(_this, selection_type, &videodata->selection_incr_waiting) == false) {
                        break;
                    }

                    X11_XFree(src);
                    만약 (X11_XGetWindowProperty(display, owner, selection, 0, INT_MAX / 4, False,
                                           XA_MIME, &seln_type, &seln_format, &count, &overflow, &src) != Success) {
                        break;
                    }

                    만약 (count == 0) {
                        incr_success = true;
                        break;
                    }

                    만약 (*length == 0) {
                        *length = (size_t)count;
                        data = CloneDataBuffer(src, count);
                    } 아니면 {
                        data = AppendDataBuffer(data, *length, src, count);
                        *length += (size_t)count;
                    }

                    만약 (data == NULL) {
                        break;
                    }
                }

                만약 (incr_success == false) {
                    SDL_free(data);
                    data = NULL;
                    *length = 0;
                }
            }
            X11_XFree(src);
        }
    }
    반환 data;
}

const char *const *X11_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *num_mime_types)
{
    *num_mime_types = SDL_arraysize(text_mime_types);
    반환 text_mime_types;
}

bool X11_SetClipboardData(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    반환 SetSelectionData(_this, videodata->atoms.CLIPBOARD, _this->clipboard_callback, _this->clipboard_userdata, (const char **)_this->clipboard_mime_types, _this->num_clipboard_mime_types, _this->clipboard_sequence);
}

void *X11_GetClipboardData(SDL_VideoDevice *_this, const char *mime_type, size_t *length)
{
    SDL_VideoData *videodata = _this->internal;

    *length = 0;

    만약 (!SDL_HasInternalClipboardData(_this, mime_type)) {
        // This mime type wasn't advertised by the last selection owner.
        // The atom might still have data, but it's stale, so ignore it.
        반환 NULL;
    }
    반환 GetSelectionData(_this, videodata->atoms.CLIPBOARD, mime_type, length);
}

bool X11_HasClipboardData(SDL_VideoDevice *_this, const char *mime_type)
{
    size_t length;
    void *data;
    data = X11_GetClipboardData(_this, mime_type, &length);
    SDL_free(data);
    반환 length > 0;
}

bool X11_SetPrimarySelectionText(SDL_VideoDevice *_this, const char *text)
{
    반환 SetSelectionData(_this, XA_PRIMARY, SDL_ClipboardTextCallback, SDL_strdup(text), text_mime_types, SDL_arraysize(text_mime_types), 0);
}

char *X11_GetPrimarySelectionText(SDL_VideoDevice *_this)
{
    size_t length;
    char *text = GetSelectionData(_this, XA_PRIMARY, text_mime_types[0], &length);
    만약 (!text) {
        text = SDL_strdup("");
    }
    반환 text;
}

bool X11_HasPrimarySelectionText(SDL_VideoDevice *_this)
{
    bool result = false;
    char *text = X11_GetPrimarySelectionText(_this);
    만약 (text) {
        만약 (text[0] != '\0') {
            result = true;
        }
        SDL_free(text);
    }
    반환 result;
}

void X11_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    만약 (data->primary_selection.sequence == 0) {
        SDL_free(data->primary_selection.userdata);
    }
    만약 (data->clipboard.sequence == 0) {
        SDL_free(data->clipboard.userdata);
    }
}

#endif // SDL_VIDEO_DRIVER_X11
