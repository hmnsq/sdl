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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#अन्तर्भाव <limits.h> // For INT_MAX

#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11clipboard.h"
#अन्तर्भाव "../SDL_clipboard_c.h"
#अन्तर्भाव "../../events/SDL_events_c.h"

स्थिर स्थिरांक अक्षर *स्थिरांक text_mime_types[] = {
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
    जर (data->clipboard_window == None) {
        Display *dpy = data->display;
        Window parent = मूळ_Window(dpy, DefaultScreen(dpy));
        XSetWindowAttributes xattr;
        data->clipboard_window = X11_XCreateWindow(dpy, parent, -10, -10, 1, 1, 0,
                                                   CopyFromParent, आदान_Only,
                                                   रिक्त, 0, &xattr);

        X11_XSelect_आदान(dpy, data->clipboard_window, PropertyChangeMask);
        X11_XFlush(data->display);
    }

    परत data->clipboard_window;
}

स्थिर bool SetSelectionData(SDL_VideoDevice *_this, Atom selection, SDL_ClipboardDataCallback callback,
                            शून्य *userdata, स्थिरांक अक्षर *स्थिरांक *mime_types, माप_प्रकार mime_मोजणी, Uint32 sequence)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    Window window;
    SDLX11_ClipboardData *clipboard;
    bool clipboard_owner = false;

    window = GetWindow(_this);
    जर (window == None) {
        परत SDL_SetError("Couldn't find a window to own the selection");
    }

    जर (selection == XA_PRIMARY) {
        clipboard = &videodata->primary_selection;
    } अन्यथा {
        clipboard = &videodata->clipboard;
    }

    clipboard_owner = X11_XGetSelectionOwner(display, selection) == window;

    // If we are canceling our own data we need to clean it up
    जर (clipboard_owner && clipboard->sequence == 0) {
        SDL_free(clipboard->userdata);
    }

    clipboard->callback = callback;
    clipboard->userdata = userdata;
    clipboard->mime_types = mime_types;
    clipboard->mime_मोजणी = mime_मोजणी;
    clipboard->sequence = sequence;

    X11_XSetSelectionOwner(display, selection, window, CurrentTime);
    परत true;
}

स्थिर शून्य *CloneDataBuffer(स्थिरांक शून्य *buffer, स्थिरांक माप_प्रकार len)
{
    शून्य *clone = रिक्त;
    जर (len > 0 && buffer) {
        clone = SDL_malloc(len + आकार(Uint32));
        जर (clone) {
            SDL_memcpy(clone, buffer, len);
            SDL_memset((Uint8 *)clone + len, 0, आकार(Uint32));
        }
    }
    परत clone;
}

/*
 * original_buffer is considered unusable after the function is called.
 */
स्थिर शून्य *AppendDataBuffer(शून्य *original_buffer, स्थिरांक माप_प्रकार old_len, स्थिरांक शून्य *buffer, स्थिरांक माप_प्रकार buffer_len)
{
    शून्य *resized_buffer;

    जर (buffer_len > 0 && buffer) {
        resized_buffer = SDL_realloc(original_buffer, old_len + buffer_len + आकार(Uint32));
        जर (resized_buffer) {
            SDL_memcpy((Uint8 *)resized_buffer + old_len, buffer, buffer_len);
            SDL_memset((Uint8 *)resized_buffer + old_len + buffer_len, 0, आकार(Uint32));
        }

        परत resized_buffer;
    } अन्यथा {
        परत original_buffer;
    }
}

स्थिर bool WaitForSelection(SDL_VideoDevice *_this, Atom selection_type, bool *flag)
{
    Uint64 waitStart;
    Uint64 waitElapsed;

    waitStart = SDL_GetTicks();
    *flag = true;
    पर्यंत (*flag) {
        X11_PumpEvents(_this);
        waitElapsed = SDL_GetTicks() - waitStart;
        // Wait one second for a selection response.
        जर (waitElapsed > 1000) {
            *flag = false;
            SDL_SetError("Selection timeout");
            /* We need to set the selection text so that next time we won't
               timeout, otherwise we will hang on every call to this function. */
            SetSelectionData(_this, selection_type, SDL_ClipboardTextCallback, रिक्त,
                             text_mime_types, SDL_arraysize(text_mime_types), 0);
            परत false;
        }
    }

    परत true;
}

स्थिर शून्य *GetSelectionData(SDL_VideoDevice *_this, Atom selection_type,
                              स्थिरांक अक्षर *mime_type, माप_प्रकार *length)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    Window window;
    Window owner;
    Atom selection;
    Atom seln_type;
    पूर्णांक seln_format;
    अचिन्हित दीर्घ मोजणी;
    अचिन्हित दीर्घ overflow;

    SDLX11_ClipboardData *clipboard;
    शून्य *data = रिक्त;
    अचिन्हित अक्षर *src = रिक्त;
    bool incr_success = false;
    Atom XA_MIME = X11_XInternAtom(display, mime_type, False);

    *length = 0;

    // Get the window that holds the selection
    window = GetWindow(_this);
    owner = X11_XGetSelectionOwner(display, selection_type);
    जर (owner == None) {
        // This requires a fallback to ancient X10 cut-buffers. We will just skip those for now
        data = रिक्त;
    } अन्यथा जर (owner == window) {
        owner = Default_मूळ_Window(display);
        जर (selection_type == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } अन्यथा {
            clipboard = &videodata->clipboard;
        }

        जर (clipboard->callback) {
            स्थिरांक शून्य *clipboard_data = clipboard->callback(clipboard->userdata, mime_type, length);
            data = CloneDataBuffer(clipboard_data, *length);
        }
    } अन्यथा {
        // Request that the selection owner copy the data to our window
        owner = window;
        selection = videodata->atoms.SDL_SELECTION;
        X11_XConvertSelection(display, selection_type, XA_MIME, selection, owner,
                              CurrentTime);

        जर (WaitForSelection(_this, selection_type, &videodata->selection_waiting) == false) {
            data = रिक्त;
            *length = 0;
        }

        जर (X11_XGetWindowProperty(display, owner, selection, 0, पूर्णांक_उच्च / 4, False,
                                   XA_MIME, &seln_type, &seln_format, &मोजणी, &overflow, &src) == Success) {
            जर (seln_type == XA_MIME) {
                *length = (माप_प्रकार)मोजणी;
                data = CloneDataBuffer(src, मोजणी);
            } अन्यथा जर (seln_type == videodata->atoms.INCR) {
                पर्यंत (1) {
                    // Only delete the property after being done with the previous "chunk".
                    X11_XDeleteProperty(display, owner, selection);
                    X11_XFlush(display);

                    जर (WaitForSelection(_this, selection_type, &videodata->selection_incr_waiting) == false) {
                        थांबा;
                    }

                    X11_XFree(src);
                    जर (X11_XGetWindowProperty(display, owner, selection, 0, पूर्णांक_उच्च / 4, False,
                                           XA_MIME, &seln_type, &seln_format, &मोजणी, &overflow, &src) != Success) {
                        थांबा;
                    }

                    जर (मोजणी == 0) {
                        incr_success = true;
                        थांबा;
                    }

                    जर (*length == 0) {
                        *length = (माप_प्रकार)मोजणी;
                        data = CloneDataBuffer(src, मोजणी);
                    } अन्यथा {
                        data = AppendDataBuffer(data, *length, src, मोजणी);
                        *length += (माप_प्रकार)मोजणी;
                    }

                    जर (data == रिक्त) {
                        थांबा;
                    }
                }

                जर (incr_success == false) {
                    SDL_free(data);
                    data = रिक्त;
                    *length = 0;
                }
            }
            X11_XFree(src);
        }
    }
    परत data;
}

स्थिरांक अक्षर *स्थिरांक *X11_GetTextMimeTypes(SDL_VideoDevice *_this, माप_प्रकार *अंक_mime_types)
{
    *अंक_mime_types = SDL_arraysize(text_mime_types);
    परत text_mime_types;
}

bool X11_SetClipboardData(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    परत SetSelectionData(_this, videodata->atoms.CLIPBOARD, _this->clipboard_callback, _this->clipboard_userdata, (स्थिरांक अक्षर **)_this->clipboard_mime_types, _this->अंक_clipboard_mime_types, _this->clipboard_sequence);
}

शून्य *X11_GetClipboardData(SDL_VideoDevice *_this, स्थिरांक अक्षर *mime_type, माप_प्रकार *length)
{
    SDL_VideoData *videodata = _this->internal;

    *length = 0;

    जर (!SDL_HasInternalClipboardData(_this, mime_type)) {
        // This mime type wasn't advertised by the last selection owner.
        // The atom might still have data, but it's stale, so ignore it.
        परत रिक्त;
    }
    परत GetSelectionData(_this, videodata->atoms.CLIPBOARD, mime_type, length);
}

bool X11_HasClipboardData(SDL_VideoDevice *_this, स्थिरांक अक्षर *mime_type)
{
    माप_प्रकार length;
    शून्य *data;
    data = X11_GetClipboardData(_this, mime_type, &length);
    SDL_free(data);
    परत length > 0;
}

bool X11_SetPrimarySelectionText(SDL_VideoDevice *_this, स्थिरांक अक्षर *text)
{
    परत SetSelectionData(_this, XA_PRIMARY, SDL_ClipboardTextCallback, SDL_strdup(text), text_mime_types, SDL_arraysize(text_mime_types), 0);
}

अक्षर *X11_GetPrimarySelectionText(SDL_VideoDevice *_this)
{
    माप_प्रकार length;
    अक्षर *text = GetSelectionData(_this, XA_PRIMARY, text_mime_types[0], &length);
    जर (!text) {
        text = SDL_strdup("");
    }
    परत text;
}

bool X11_HasPrimarySelectionText(SDL_VideoDevice *_this)
{
    bool result = false;
    अक्षर *text = X11_GetPrimarySelectionText(_this);
    जर (text) {
        जर (text[0] != '\0') {
            result = true;
        }
        SDL_free(text);
    }
    परत result;
}

शून्य X11_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    जर (data->primary_selection.sequence == 0) {
        SDL_free(data->primary_selection.userdata);
    }
    जर (data->clipboard.sequence == 0) {
        SDL_free(data->clipboard.userdata);
    }
}

#endif // SDL_VIDEO_DRIVER_X11
