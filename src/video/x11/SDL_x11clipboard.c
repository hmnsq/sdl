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
#ضمن "SDL_internal.h"

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11

#ضمن <limits.h> // For INT_MAX

#ضمن "SDL_x11video.h"
#ضمن "SDL_x11clipboard.h"
#ضمن "../SDL_clipboard_c.h"
#ضمن "../../events/SDL_events_c.h"

ساكن ثابت حرف *ثابت متن_mime_types[] = {
    "UTF8_STRING",
    "text/plain;charset=utf-8",
    "text/plain",
    "TEXT",
    "STRING"
};

// Get any application owned window handle for clipboard association
دري_2 Get_دري(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;

    /* We create an unmapped window that exists just to manage the clipboard,
       since X11 selection data is tied to a specific window and dies with it.
       We create the window on demand, so apps that don't use the clipboard
       don't have to keep an unnecessary resource around. */
    إذا (معلومات->clipboard_دري == None) {
        Display *dpy = معلومات->display;
        دري_2 والد = پاڙ_دري(dpy, DefaultScreen(dpy));
        XSet_دري_خاصيتون xattr;
        معلومات->clipboard_دري = X11_XCreate_دري(dpy, والد, -10, -10, 1, 1, 0,
                                                   Copy_From_والد, داخلا_Only,
                                                   عدم, 0, &xattr);

        X11_XSelect_داخلا(dpy, معلومات->clipboard_دري, Property_Change_نقاب);
        X11_XFlush(معلومات->display);
    }

    أرجع معلومات->clipboard_دري;
}

ساكن bool سيٽ_Selection_معلومات(SDL_VideoDevice *_this, Atom selection, SDL_Clipboard_معلومات_Callback callback,
                            فراغ *userdata, ثابت حرف *ثابت *mime_types, size_t mime_ڳڻپ, Uint32 sequence)
{
    SDL_Video_معلومات *videodata = _this->اندروني;
    Display *display = videodata->display;
    دري_2 دري;
    SDLX11_Clipboard_معلومات *clipboard;
    bool clipboard_owner = false;

    دري = Get_دري(_this);
    إذا (دري == None) {
        أرجع SDL_سيٽ_Error("Couldn't find a window to own the selection");
    }

    إذا (selection == XA_PRIMARY) {
        clipboard = &videodata->primary_selection;
    } وإلا {
        clipboard = &videodata->clipboard;
    }

    clipboard_owner = X11_XGetSelectionOwner(display, selection) == دري;

    // If we are canceling our own data we need to clean it up
    إذا (clipboard_owner && clipboard->sequence == 0) {
        SDL_free(clipboard->userdata);
    }

    clipboard->callback = callback;
    clipboard->userdata = userdata;
    clipboard->mime_types = mime_types;
    clipboard->mime_ڳڻپ = mime_ڳڻپ;
    clipboard->sequence = sequence;

    X11_XSetSelectionOwner(display, selection, دري, Current_وقت);
    أرجع true;
}

ساكن فراغ *Clone_معلومات_بفر(ثابت فراغ *بفر_2, ثابت size_t len)
{
    فراغ *clone = عدم;
    إذا (len > 0 && بفر_2) {
        clone = SDL_malloc(len + حجم(Uint32));
        إذا (clone) {
            SDL_memcpy(clone, بفر_2, len);
            SDL_memset((Uint8 *)clone + len, 0, حجم(Uint32));
        }
    }
    أرجع clone;
}

/*
 * original_buffer is considered unusable after the function is called.
 */
ساكن فراغ *Append_معلومات_بفر(فراغ *original_بفر, ثابت size_t old_len, ثابت فراغ *بفر_2, ثابت size_t بفر_len)
{
    فراغ *resized_بفر;

    إذا (بفر_len > 0 && بفر_2) {
        resized_بفر = SDL_realloc(original_بفر, old_len + بفر_len + حجم(Uint32));
        إذا (resized_بفر) {
            SDL_memcpy((Uint8 *)resized_بفر + old_len, بفر_2, بفر_len);
            SDL_memset((Uint8 *)resized_بفر + old_len + بفر_len, 0, حجم(Uint32));
        }

        أرجع resized_بفر;
    } وإلا {
        أرجع original_بفر;
    }
}

ساكن bool WaitForSelection(SDL_VideoDevice *_this, Atom selection_type, bool *flag)
{
    Uint64 wait_شروعات;
    Uint64 waitElapsed;

    wait_شروعات = SDL_GetTicks();
    *flag = true;
    طالما (*flag) {
        X11_PumpEvents(_this);
        waitElapsed = SDL_GetTicks() - wait_شروعات;
        // Wait one second for a selection response.
        إذا (waitElapsed > 1000) {
            *flag = false;
            SDL_سيٽ_Error("Selection timeout");
            /* We need to set the selection text so that next time we won't
               timeout, otherwise we will hang on every call to this function. */
            سيٽ_Selection_معلومات(_this, selection_type, SDL_Clipboard_متن_Callback, عدم,
                             متن_mime_types, SDL_arraysize(متن_mime_types), 0);
            أرجع false;
        }
    }

    أرجع true;
}

ساكن فراغ *Get_Selection_معلومات(SDL_VideoDevice *_this, Atom selection_type,
                              ثابت حرف *mime_type, size_t *ڊيگهائي)
{
    SDL_Video_معلومات *videodata = _this->اندروني;
    Display *display = videodata->display;
    دري_2 دري;
    دري_2 owner;
    Atom selection;
    Atom seln_type;
    صحيح seln_format;
    بنانشان ڊگهو ڳڻپ;
    بنانشان ڊگهو حد_کان_مٿي;

    SDLX11_Clipboard_معلومات *clipboard;
    فراغ *معلومات = عدم;
    بنانشان حرف *src = عدم;
    bool incr_success = false;
    Atom XA_MIME = X11_XInternAtom(display, mime_type, False);

    *ڊيگهائي = 0;

    // Get the window that holds the selection
    دري = Get_دري(_this);
    owner = X11_XGetSelectionOwner(display, selection_type);
    إذا (owner == None) {
        // This requires a fallback to ancient X10 cut-buffers. We will just skip those for now
        معلومات = عدم;
    } وإلا إذا (owner == دري) {
        owner = Default_پاڙ_دري(display);
        إذا (selection_type == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } وإلا {
            clipboard = &videodata->clipboard;
        }

        إذا (clipboard->callback) {
            ثابت فراغ *clipboard_معلومات = clipboard->callback(clipboard->userdata, mime_type, ڊيگهائي);
            معلومات = Clone_معلومات_بفر(clipboard_معلومات, *ڊيگهائي);
        }
    } وإلا {
        // Request that the selection owner copy the data to our window
        owner = دري;
        selection = videodata->atoms.SDL_SELECTION;
        X11_XConvertSelection(display, selection_type, XA_MIME, selection, owner,
                              Current_وقت);

        إذا (WaitForSelection(_this, selection_type, &videodata->selection_انتظار) == false) {
            معلومات = عدم;
            *ڊيگهائي = 0;
        }

        إذا (X11_XGet_دري_Property(display, owner, selection, 0, وڌ_کان_وڌ_عدد / 4, False,
                                   XA_MIME, &seln_type, &seln_format, &ڳڻپ, &حد_کان_مٿي, &src) == Success) {
            إذا (seln_type == XA_MIME) {
                *ڊيگهائي = (size_t)ڳڻپ;
                معلومات = Clone_معلومات_بفر(src, ڳڻپ);
            } وإلا إذا (seln_type == videodata->atoms.INCR) {
                طالما (1) {
                    // Only delete the property after being done with the previous "chunk".
                    X11_XDeleteProperty(display, owner, selection);
                    X11_XFlush(display);

                    إذا (WaitForSelection(_this, selection_type, &videodata->selection_incr_انتظار) == false) {
                        اكسر;
                    }

                    X11_XFree(src);
                    إذا (X11_XGet_دري_Property(display, owner, selection, 0, وڌ_کان_وڌ_عدد / 4, False,
                                           XA_MIME, &seln_type, &seln_format, &ڳڻپ, &حد_کان_مٿي, &src) != Success) {
                        اكسر;
                    }

                    إذا (ڳڻپ == 0) {
                        incr_success = true;
                        اكسر;
                    }

                    إذا (*ڊيگهائي == 0) {
                        *ڊيگهائي = (size_t)ڳڻپ;
                        معلومات = Clone_معلومات_بفر(src, ڳڻپ);
                    } وإلا {
                        معلومات = Append_معلومات_بفر(معلومات, *ڊيگهائي, src, ڳڻپ);
                        *ڊيگهائي += (size_t)ڳڻپ;
                    }

                    إذا (معلومات == عدم) {
                        اكسر;
                    }
                }

                إذا (incr_success == false) {
                    SDL_free(معلومات);
                    معلومات = عدم;
                    *ڊيگهائي = 0;
                }
            }
            X11_XFree(src);
        }
    }
    أرجع معلومات;
}

ثابت حرف *ثابت *X11_Get_متن_Mime_Types(SDL_VideoDevice *_this, size_t *انگ_mime_types)
{
    *انگ_mime_types = SDL_arraysize(متن_mime_types);
    أرجع متن_mime_types;
}

bool X11_سيٽ_Clipboard_معلومات(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *videodata = _this->اندروني;
    أرجع سيٽ_Selection_معلومات(_this, videodata->atoms.CLIPBOARD, _this->clipboard_callback, _this->clipboard_userdata, (ثابت حرف **)_this->clipboard_mime_types, _this->انگ_clipboard_mime_types, _this->clipboard_sequence);
}

فراغ *X11_Get_Clipboard_معلومات(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *ڊيگهائي)
{
    SDL_Video_معلومات *videodata = _this->اندروني;

    *ڊيگهائي = 0;

    إذا (!SDL_Has_اندروني_Clipboard_معلومات(_this, mime_type)) {
        // This mime type wasn't advertised by the last selection owner.
        // The atom might still have data, but it's stale, so ignore it.
        أرجع عدم;
    }
    أرجع Get_Selection_معلومات(_this, videodata->atoms.CLIPBOARD, mime_type, ڊيگهائي);
}

bool X11_Has_Clipboard_معلومات(SDL_VideoDevice *_this, ثابت حرف *mime_type)
{
    size_t ڊيگهائي;
    فراغ *معلومات;
    معلومات = X11_Get_Clipboard_معلومات(_this, mime_type, &ڊيگهائي);
    SDL_free(معلومات);
    أرجع ڊيگهائي > 0;
}

bool X11_سيٽ_Primary_Selection_متن(SDL_VideoDevice *_this, ثابت حرف *متن)
{
    أرجع سيٽ_Selection_معلومات(_this, XA_PRIMARY, SDL_Clipboard_متن_Callback, SDL_strdup(متن), متن_mime_types, SDL_arraysize(متن_mime_types), 0);
}

حرف *X11_Get_Primary_Selection_متن(SDL_VideoDevice *_this)
{
    size_t ڊيگهائي;
    حرف *متن = Get_Selection_معلومات(_this, XA_PRIMARY, متن_mime_types[0], &ڊيگهائي);
    إذا (!متن) {
        متن = SDL_strdup("");
    }
    أرجع متن;
}

bool X11_Has_Primary_Selection_متن(SDL_VideoDevice *_this)
{
    bool نتيجو = false;
    حرف *متن = X11_Get_Primary_Selection_متن(_this);
    إذا (متن) {
        إذا (متن[0] != '\0') {
            نتيجو = true;
        }
        SDL_free(متن);
    }
    أرجع نتيجو;
}

فراغ X11_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;
    إذا (معلومات->primary_selection.sequence == 0) {
        SDL_free(معلومات->primary_selection.userdata);
    }
    إذا (معلومات->clipboard.sequence == 0) {
        SDL_free(معلومات->clipboard.userdata);
    }
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_X11
