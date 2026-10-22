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

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11

#شامل <limits.h> // For INT_MAX

#شامل "SDL_x11video.h"
#شامل "SDL_x11clipboard.h"
#شامل "../SDL_clipboard_c.h"
#شامل "../../events/SDL_events_c.h"

ساکن ثابت حرف *ثابت متن_mime_types[] = {
    "UTF8_STRING",
    "text/plain;charset=utf-8",
    "text/plain",
    "TEXT",
    "STRING"
};

// Get any application owned window handle for clipboard association
کھڑکی_2 Get_کھڑکی(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    /* We create an unmapped window that exists just to manage the clipboard,
       since X11 selection data is tied to a specific window and dies with it.
       We create the window on demand, so apps that don't use the clipboard
       don't have to keep an unnecessary resource around. */
    اگر (ڈیٹا->clipboard_کھڑکی == None) {
        Display *dpy = ڈیٹا->display;
        کھڑکی_2 والد = جڑ_کھڑکی(dpy, DefaultScreen(dpy));
        XSet_کھڑکی_اوصاف xattr;
        ڈیٹا->clipboard_کھڑکی = X11_XCreate_کھڑکی(dpy, والد, -10, -10, 1, 1, 0,
                                                   Copy_From_والد, داخلہ_Only,
                                                   تہی, 0, &xattr);

        X11_XSelect_داخلہ(dpy, ڈیٹا->clipboard_کھڑکی, Property_Change_نقاب);
        X11_XFlush(ڈیٹا->display);
    }

    واپس ڈیٹا->clipboard_کھڑکی;
}

ساکن bool سیٹ_Selection_ڈیٹا(SDL_VideoDevice *_this, Atom selection, SDL_Clipboard_ڈیٹا_Callback callback,
                            خالی *userdata, ثابت حرف *ثابت *mime_types, size_t mime_گنتی, Uint32 sequence)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    Display *display = videodata->display;
    کھڑکی_2 کھڑکی;
    SDLX11_Clipboard_ڈیٹا *clipboard;
    bool clipboard_owner = false;

    کھڑکی = Get_کھڑکی(_this);
    اگر (کھڑکی == None) {
        واپس SDL_سیٹ_Error("Couldn't find a window to own the selection");
    }

    اگر (selection == XA_PRIMARY) {
        clipboard = &videodata->primary_selection;
    } ورنہ {
        clipboard = &videodata->clipboard;
    }

    clipboard_owner = X11_XGetSelectionOwner(display, selection) == کھڑکی;

    // If we are canceling our own data we need to clean it up
    اگر (clipboard_owner && clipboard->sequence == 0) {
        SDL_free(clipboard->userdata);
    }

    clipboard->callback = callback;
    clipboard->userdata = userdata;
    clipboard->mime_types = mime_types;
    clipboard->mime_گنتی = mime_گنتی;
    clipboard->sequence = sequence;

    X11_XSetSelectionOwner(display, selection, کھڑکی, Current_وقت);
    واپس true;
}

ساکن خالی *Clone_ڈیٹا_بفر(ثابت خالی *بفر_2, ثابت size_t len)
{
    خالی *clone = تہی;
    اگر (len > 0 && بفر_2) {
        clone = SDL_malloc(len + حجم(Uint32));
        اگر (clone) {
            SDL_memcpy(clone, بفر_2, len);
            SDL_memset((Uint8 *)clone + len, 0, حجم(Uint32));
        }
    }
    واپس clone;
}

/*
 * original_buffer is considered unusable after the function is called.
 */
ساکن خالی *Append_ڈیٹا_بفر(خالی *original_بفر, ثابت size_t old_len, ثابت خالی *بفر_2, ثابت size_t بفر_len)
{
    خالی *resized_بفر;

    اگر (بفر_len > 0 && بفر_2) {
        resized_بفر = SDL_realloc(original_بفر, old_len + بفر_len + حجم(Uint32));
        اگر (resized_بفر) {
            SDL_memcpy((Uint8 *)resized_بفر + old_len, بفر_2, بفر_len);
            SDL_memset((Uint8 *)resized_بفر + old_len + بفر_len, 0, حجم(Uint32));
        }

        واپس resized_بفر;
    } ورنہ {
        واپس original_بفر;
    }
}

ساکن bool WaitForSelection(SDL_VideoDevice *_this, Atom selection_type, bool *flag)
{
    Uint64 wait_آغاز;
    Uint64 waitElapsed;

    wait_آغاز = SDL_GetTicks();
    *flag = true;
    جب (*flag) {
        X11_PumpEvents(_this);
        waitElapsed = SDL_GetTicks() - wait_آغاز;
        // Wait one second for a selection response.
        اگر (waitElapsed > 1000) {
            *flag = false;
            SDL_سیٹ_Error("Selection timeout");
            /* We need to set the selection text so that next time we won't
               timeout, otherwise we will hang on every call to this function. */
            سیٹ_Selection_ڈیٹا(_this, selection_type, SDL_Clipboard_متن_Callback, تہی,
                             متن_mime_types, SDL_arraysize(متن_mime_types), 0);
            واپس false;
        }
    }

    واپس true;
}

ساکن خالی *Get_Selection_ڈیٹا(SDL_VideoDevice *_this, Atom selection_type,
                              ثابت حرف *mime_type, size_t *لمبائی)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    Display *display = videodata->display;
    کھڑکی_2 کھڑکی;
    کھڑکی_2 owner;
    Atom selection;
    Atom seln_type;
    صحیح seln_format;
    غیرعلامتی طویل گنتی;
    غیرعلامتی طویل حد_سے_تجاوز;

    SDLX11_Clipboard_ڈیٹا *clipboard;
    خالی *ڈیٹا = تہی;
    غیرعلامتی حرف *src = تہی;
    bool incr_success = false;
    Atom XA_MIME = X11_XInternAtom(display, mime_type, False);

    *لمبائی = 0;

    // Get the window that holds the selection
    کھڑکی = Get_کھڑکی(_this);
    owner = X11_XGetSelectionOwner(display, selection_type);
    اگر (owner == None) {
        // This requires a fallback to ancient X10 cut-buffers. We will just skip those for now
        ڈیٹا = تہی;
    } ورنہ اگر (owner == کھڑکی) {
        owner = Default_جڑ_کھڑکی(display);
        اگر (selection_type == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } ورنہ {
            clipboard = &videodata->clipboard;
        }

        اگر (clipboard->callback) {
            ثابت خالی *clipboard_ڈیٹا = clipboard->callback(clipboard->userdata, mime_type, لمبائی);
            ڈیٹا = Clone_ڈیٹا_بفر(clipboard_ڈیٹا, *لمبائی);
        }
    } ورنہ {
        // Request that the selection owner copy the data to our window
        owner = کھڑکی;
        selection = videodata->atoms.SDL_SELECTION;
        X11_XConvertSelection(display, selection_type, XA_MIME, selection, owner,
                              Current_وقت);

        اگر (WaitForSelection(_this, selection_type, &videodata->selection_انتظار) == false) {
            ڈیٹا = تہی;
            *لمبائی = 0;
        }

        اگر (X11_XGet_کھڑکی_Property(display, owner, selection, 0, زیادہ_سے_زیادہ_عدد / 4, False,
                                   XA_MIME, &seln_type, &seln_format, &گنتی, &حد_سے_تجاوز, &src) == Success) {
            اگر (seln_type == XA_MIME) {
                *لمبائی = (size_t)گنتی;
                ڈیٹا = Clone_ڈیٹا_بفر(src, گنتی);
            } ورنہ اگر (seln_type == videodata->atoms.INCR) {
                جب (1) {
                    // Only delete the property after being done with the previous "chunk".
                    X11_XDeleteProperty(display, owner, selection);
                    X11_XFlush(display);

                    اگر (WaitForSelection(_this, selection_type, &videodata->selection_incr_انتظار) == false) {
                        توڑو;
                    }

                    X11_XFree(src);
                    اگر (X11_XGet_کھڑکی_Property(display, owner, selection, 0, زیادہ_سے_زیادہ_عدد / 4, False,
                                           XA_MIME, &seln_type, &seln_format, &گنتی, &حد_سے_تجاوز, &src) != Success) {
                        توڑو;
                    }

                    اگر (گنتی == 0) {
                        incr_success = true;
                        توڑو;
                    }

                    اگر (*لمبائی == 0) {
                        *لمبائی = (size_t)گنتی;
                        ڈیٹا = Clone_ڈیٹا_بفر(src, گنتی);
                    } ورنہ {
                        ڈیٹا = Append_ڈیٹا_بفر(ڈیٹا, *لمبائی, src, گنتی);
                        *لمبائی += (size_t)گنتی;
                    }

                    اگر (ڈیٹا == تہی) {
                        توڑو;
                    }
                }

                اگر (incr_success == false) {
                    SDL_free(ڈیٹا);
                    ڈیٹا = تہی;
                    *لمبائی = 0;
                }
            }
            X11_XFree(src);
        }
    }
    واپس ڈیٹا;
}

ثابت حرف *ثابت *X11_Get_متن_Mime_Types(SDL_VideoDevice *_this, size_t *عدد_mime_types)
{
    *عدد_mime_types = SDL_arraysize(متن_mime_types);
    واپس متن_mime_types;
}

bool X11_سیٹ_Clipboard_ڈیٹا(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    واپس سیٹ_Selection_ڈیٹا(_this, videodata->atoms.CLIPBOARD, _this->clipboard_callback, _this->clipboard_userdata, (ثابت حرف **)_this->clipboard_mime_types, _this->عدد_clipboard_mime_types, _this->clipboard_sequence);
}

خالی *X11_Get_Clipboard_ڈیٹا(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *لمبائی)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;

    *لمبائی = 0;

    اگر (!SDL_Has_اندرونی_Clipboard_ڈیٹا(_this, mime_type)) {
        // This mime type wasn't advertised by the last selection owner.
        // The atom might still have data, but it's stale, so ignore it.
        واپس تہی;
    }
    واپس Get_Selection_ڈیٹا(_this, videodata->atoms.CLIPBOARD, mime_type, لمبائی);
}

bool X11_Has_Clipboard_ڈیٹا(SDL_VideoDevice *_this, ثابت حرف *mime_type)
{
    size_t لمبائی;
    خالی *ڈیٹا;
    ڈیٹا = X11_Get_Clipboard_ڈیٹا(_this, mime_type, &لمبائی);
    SDL_free(ڈیٹا);
    واپس لمبائی > 0;
}

bool X11_سیٹ_Primary_Selection_متن(SDL_VideoDevice *_this, ثابت حرف *متن)
{
    واپس سیٹ_Selection_ڈیٹا(_this, XA_PRIMARY, SDL_Clipboard_متن_Callback, SDL_strdup(متن), متن_mime_types, SDL_arraysize(متن_mime_types), 0);
}

حرف *X11_Get_Primary_Selection_متن(SDL_VideoDevice *_this)
{
    size_t لمبائی;
    حرف *متن = Get_Selection_ڈیٹا(_this, XA_PRIMARY, متن_mime_types[0], &لمبائی);
    اگر (!متن) {
        متن = SDL_strdup("");
    }
    واپس متن;
}

bool X11_Has_Primary_Selection_متن(SDL_VideoDevice *_this)
{
    bool نتیجہ = false;
    حرف *متن = X11_Get_Primary_Selection_متن(_this);
    اگر (متن) {
        اگر (متن[0] != '\0') {
            نتیجہ = true;
        }
        SDL_free(متن);
    }
    واپس نتیجہ;
}

خالی X11_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    اگر (ڈیٹا->primary_selection.sequence == 0) {
        SDL_free(ڈیٹا->primary_selection.userdata);
    }
    اگر (ڈیٹا->clipboard.sequence == 0) {
        SDL_free(ڈیٹا->clipboard.userdata);
    }
}

#اگر_ختم // SDL_VIDEO_DRIVER_X11
