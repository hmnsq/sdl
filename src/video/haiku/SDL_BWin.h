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

#यदि_अपरिभाषितम् SDL_BWin_h_
#परिभाषय SDL_BWin_h_

#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः

#अन्तर्भाव "SDL_internal.h"
#अन्तर्भाव "SDL_bframebuffer.h"

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#अन्तर्भाव <stdio.h>
#अन्तर्भाव <AppKit.h>
#अन्तर्भाव <Cursor.h>
#अन्तर्भाव <InterfaceKit.h>
#यदि_परिभाषितम् SDL_VIDEO_OPENGL
#अन्तर्भाव <opengl/GLView.h>
#यदि_अन्तः
#अन्तर्भाव "../../core/haiku/SDL_BApp.h"

गणना WinCommands
{
    BWIN_MOVE_गवाक्षः,
    BWIN_RESIZE_गवाक्षः,
    BWIN_SHOW_गवाक्षः,
    BWIN_HIDE_गवाक्षः,
    BWIN_MAXIMIZE_गवाक्षः,
    BWIN_MINIMIZE_गवाक्षः,
    BWIN_RESTORE_गवाक्षः,
    BWIN_समुच्चयः_TITLE,
    BWIN_समुच्चयः_BORDERED,
    BWIN_समुच्चयः_RESIZABLE,
    BWIN_FULLSCREEN,
    BWIN_UPDATE_FRAMEBUFFER,
    BWIN_MINIMUM_आकार_गवाक्षः
};

// non-OpenGL framebuffer view
class SDL_BView : सार्वजनिक BView
{
  सार्वजनिक:
    SDL_BView(BRect frame, ध्रुव वर्ण *name, uint32 resizing_बहुलकम्)
        : BView(frame, name, resizing_बहुलकम्, B_WILL_DRAW),
          fBitmap(रिक्त)
    {
    }

    शून्य Draw(BRect dirty)
    {
        यदि (fBitmap != रिक्त)
            DrawBitmap(fBitmap, B_ORIGIN);
    }

    शून्य समुच्चयः_Bitmap(BBitmap *bitmap)
    {
        fBitmap = bitmap;
    }

  गुप्त:
    BBitmap *fBitmap;
};

class SDL_BWin : सार्वजनिक BWindow
{
  सार्वजनिक:
    // Constructor/Destructor
    SDL_BWin(BRect bounds, गवाक्षः_look look, uint32 flags)
        : BWindow(bounds, "Untitled", look, B_प्रसामान्यम्_गवाक्षः_FEEL, flags)
    {
        चरमः_buttons = 0;

        _cur_view = रिक्त;
        _SDL_View = रिक्त;

#यदि_परिभाषितम् SDL_VIDEO_OPENGL
        _SDL_GLView = रिक्त;
        _gl_type = 0;
#यदि_अन्तः
        _shown = false;
        _inhibit_resize = false;
        _mouse_focused = false;
        पूर्व_frame = रिक्त;
        _fullscreen = रिक्त;

        // Handle framebuffer stuff
        बफर_locker = new BLocker();
        _bitmap = रिक्त;
    }

    आभास ~SDL_BWin()
    {
        तालकम्();

        यदि (_SDL_View != रिक्त && _SDL_View != _cur_view) {
            delete _SDL_View;
            _SDL_View = रिक्त;
        }

#यदि_परिभाषितम् SDL_VIDEO_OPENGL
        यदि (_SDL_GLView) {
            यदि (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->समुच्चयः_Current_Context(रिक्त);
            यदि (_SDL_GLView == _cur_view)
                RemoveChild(_SDL_GLView);
            _SDL_GLView = रिक्त;
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }

#यदि_अन्तः
        Unlock();

        delete पूर्व_frame;

        // Clean up framebuffer stuff
        बफर_locker->तालकम्();
        delete बफर_locker;
    }

    शून्य समुच्चयः_Current_View(BView *view)
    {
        यदि (_cur_view != view) {
            यदि (_cur_view != रिक्त)
                RemoveChild(_cur_view);
            _cur_view = view;
            यदि (_cur_view != रिक्त)
                सङ्कलय_Child(_cur_view);
        }
    }

    शून्य UpdateCurrentView()
    {
#यदि_परिभाषितम् SDL_VIDEO_OPENGL
        यदि (_SDL_GLView != रिक्त) {
            समुच्चयः_Current_View(_SDL_GLView);
        } अन्यथा
#यदि_अन्तः
        यदि (_SDL_View != रिक्त) {
            समुच्चयः_Current_View(_SDL_View);
        } अन्यथा {
            समुच्चयः_Current_View(रिक्त);
        }
    }

    SDL_BView *CreateView()
    {
        तालकम्();
        यदि (_SDL_View == रिक्त) {
            _SDL_View = new SDL_BView(Bounds(), "SDL View", B_FOLLOW_ALL_SIDES);
            UpdateCurrentView();
        }
        Unlock();
        प्रत्यागम _SDL_View;
    }

    शून्य RemoveView()
    {
        तालकम्();
        यदि (_SDL_View != रिक्त) {
            SDL_BView *oldView = _SDL_View;
            _SDL_View = रिक्त;
            UpdateCurrentView();
            delete oldView;
        }
        Unlock();
    }

    /* * * * * OpenGL functionality * * * * */
#यदि_परिभाषितम् SDL_VIDEO_OPENGL
    BGLView *CreateGLView(Uint32 gl_flags)
    {
        तालकम्();
        यदि (_SDL_GLView == रिक्त) {
            _SDL_GLView = new BGLView(Bounds(), "SDL GLView",
                                      B_FOLLOW_ALL_SIDES,
                                      (B_WILL_DRAW | B_FRAME_EVENTS),
                                      gl_flags);
            _gl_type = gl_flags;
            UpdateCurrentView();
        }
        Unlock();
        प्रत्यागम _SDL_GLView;
    }

    शून्य RemoveGLView()
    {
        तालकम्();
        यदि (_SDL_GLView != रिक्त) {
            यदि (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->समुच्चयः_Current_Context(रिक्त);
            _SDL_GLView = रिक्त;
            UpdateCurrentView();
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }
        Unlock();
    }

    शून्य SwapBuffers(शून्य)
    {
        _SDL_GLView->SwapBuffers();
    }
#यदि_अन्तः

    /* * * * * Event sending * * * * */
    // Hook functions
    आभास शून्य FrameMoved(BPoint origin)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage सन्देशः_2(BAPP_गवाक्षः_MOVED);
        सन्देशः_2.सङ्कलय_Int32("window-x", (पूर्णाङ्क)origin.x);
        सन्देशः_2.सङ्कलय_Int32("window-y", (पूर्णाङ्क)origin.y);
        Post_गवाक्षः_Event(सन्देशः_2);

        // Perform normal hook operations
        BWindow::FrameMoved(origin);
    }

    शून्य FrameResized(भिन्न विस्तारः, भिन्न height)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage सन्देशः_2(BAPP_गवाक्षः_RESIZED);

        सन्देशः_2.सङ्कलय_Int32("window-w", (पूर्णाङ्क)विस्तारः + 1);
        सन्देशः_2.सङ्कलय_Int32("window-h", (पूर्णाङ्क)height + 1);
        Post_गवाक्षः_Event(सन्देशः_2);

        // Perform normal hook operations
        BWindow::FrameResized(विस्तारः, height);
    }

    bool QuitRequested()
    {
        BMessage सन्देशः_2(BAPP_गवाक्षः_CLOSE_REQUESTED);
        Post_गवाक्षः_Event(सन्देशः_2);

        // We won't allow a quit unless asked by DestroyWindow()
        प्रत्यागम false;
    }

    शून्य गवाक्षः_Activated(bool सक्रिय)
    {
        BMessage सन्देशः_2(BAPP_KEYBOARD_FOCUS); // Mouse focus sold separately
        सन्देशः_2.सङ्कलय_Bool("focusGained", सक्रिय);
        Post_गवाक्षः_Event(सन्देशः_2);
    }

    शून्य Zoom(BPoint origin,
              भिन्न विस्तारः,
              भिन्न height)
    {
        BMessage सन्देशः_2(BAPP_MAXIMIZE); // Closest thing to maximization Haiku has
        Post_गवाक्षः_Event(सन्देशः_2);

        // Before the window zooms, record its size
        यदि (!पूर्व_frame)
            पूर्व_frame = new BRect(Frame());

        // Perform normal hook operations
        BWindow::Zoom(origin, विस्तारः, height);
    }

    // Member functions
    शून्य Show()
    {
        यावत् (IsHidden()) {
            BWindow::Show();
        }
        _shown = true;

        BMessage सन्देशः_2(BAPP_SHOW);
        Post_गवाक्षः_Event(सन्देशः_2);
    }

    शून्य Hide()
    {
        BWindow::Hide();
        _shown = false;

        BMessage सन्देशः_2(BAPP_HIDE);
        Post_गवाक्षः_Event(सन्देशः_2);
    }

    शून्य Minimize(bool minimize)
    {
        BWindow::Minimize(minimize);
        int32 minState = (minimize ? BAPP_MINIMIZE : BAPP_RESTORE);

        BMessage सन्देशः_2(minState);
        Post_गवाक्षः_Event(सन्देशः_2);
    }

    शून्य Screen_परिवर्तितम्(BRect screenFrame, color_space गभीरता_2)
    {
        यदि (_fullscreen) {
            Move_गन्तव्यम्(screenFrame.वामः, screenFrame.शिखरम्);
            Resize_गन्तव्यम्(screenFrame.विस्तारः_2(), screenFrame.Height());
        }
    }

    // BView message interruption
    शून्य Dispatch_सन्देशः(BMessage *सन्देशः_2, BHandler *target)
    {
        BPoint where;  // Used by mouse moved
        int32 buttons; // Used for mouse button events
        int32 कुञ्चिका;     // Used for key events

        विकल्प (सन्देशः_2->what) {
        पक्ष B_MOUSE_MOVED:
            int32 transit;
            यदि (सन्देशः_2->FindPoint("where", &where) == B_OK && सन्देशः_2->FindInt32("be:transit", &transit) == B_OK) {
                _MouseMotionEvent(where, transit);
            }
            भङ्ग;

        पक्ष B_MOUSE_अधस्तात्:
            यदि (सन्देशः_2->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, true);
            }
            भङ्ग;

        पक्ष B_MOUSE_ऊर्ध्वम्:
            यदि (सन्देशः_2->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, false);
            }
            भङ्ग;

        पक्ष B_MOUSE_WHEEL_परिवर्तितम्:
            भिन्न x, y;
            यदि (सन्देशः_2->FindFloat("be:wheel_delta_x", &x) == B_OK && सन्देशः_2->FindFloat("be:wheel_delta_y", &y) == B_OK) {
                _MouseWheelEvent((पूर्णाङ्क)x, (पूर्णाङ्क)y);
            }
            भङ्ग;

        पक्ष B_कुञ्चिका_अधस्तात्:
        {
            int32 i = 0;
            int8 byte;
            int8 अष्टकानि[4] = { 0, 0, 0, 0 };
            यावत् (i < 4 && सन्देशः_2->FindInt8("byte", i, &byte) == B_OK) {
                अष्टकानि[i] = byte;
                i++;
            }
            यदि (सन्देशः_2->FindInt32("key", &कुञ्चिका) == B_OK) {
                कुञ्चिका_Event_2((SDL_Scancode)कुञ्चिका, &अष्टकानि[0], i, true);
            }
        } भङ्ग;

        पक्ष B_UNMAPPED_कुञ्चिका_अधस्तात्: // modifier keys are unmapped
            यदि (सन्देशः_2->FindInt32("key", &कुञ्चिका) == B_OK) {
                कुञ्चिका_Event_2((SDL_Scancode)कुञ्चिका, रिक्त, 0, true);
            }
            भङ्ग;

        पक्ष B_कुञ्चिका_ऊर्ध्वम्:
        पक्ष B_UNMAPPED_कुञ्चिका_ऊर्ध्वम्: // modifier keys are unmapped
            यदि (सन्देशः_2->FindInt32("key", &कुञ्चिका) == B_OK) {
                कुञ्चिका_Event_2(कुञ्चिका, रिक्त, 0, false);
            }
            भङ्ग;

        स्वभाव:
            /* move it after switch{} so it's always handled
               that way we keep Haiku features like:
               - CTRL+Q to close window (and other shortcuts)
               - PrintScreen to make screenshot into /boot/home
               - etc.. */
            // BWindow::DispatchMessage(msg, target);
            भङ्ग;
        }

        BWindow::Dispatch_सन्देशः(सन्देशः_2, target);
    }

    // Handle command messages
    शून्य सन्देशः_Received(BMessage *सन्देशः)
    {
        विकल्प (सन्देशः->what) {
        // Handle commands from SDL
        पक्ष BWIN_समुच्चयः_TITLE:
            समुच्चयः_Title(सन्देशः);
            भङ्ग;
        पक्ष BWIN_MOVE_गवाक्षः:
            Move_गन्तव्यम्_2(सन्देशः);
            भङ्ग;
        पक्ष BWIN_RESIZE_गवाक्षः:
            Resize_गन्तव्यम्_2(सन्देशः);
            भङ्ग;
        पक्ष BWIN_समुच्चयः_BORDERED:
        {
            bool bEnabled;
            यदि (सन्देशः->FindBool("window-border", &bEnabled) == B_OK)
                समुच्चयः_Bordered(bEnabled);
            भङ्ग;
        }
        पक्ष BWIN_समुच्चयः_RESIZABLE:
        {
            bool bEnabled;
            यदि (सन्देशः->FindBool("window-resizable", &bEnabled) == B_OK)
                समुच्चयः_Resizable(bEnabled);
            भङ्ग;
        }
        पक्ष BWIN_SHOW_गवाक्षः:
            Show();
            भङ्ग;
        पक्ष BWIN_HIDE_गवाक्षः:
            Hide();
            भङ्ग;
        पक्ष BWIN_MAXIMIZE_गवाक्षः:
            BWindow::Zoom();
            भङ्ग;
        पक्ष BWIN_MINIMIZE_गवाक्षः:
            Minimize(true);
            भङ्ग;
        पक्ष BWIN_RESTORE_गवाक्षः:
            _Restore();
            भङ्ग;
        पक्ष BWIN_FULLSCREEN:
        {
            bool fullscreen;
            यदि (सन्देशः->FindBool("fullscreen", &fullscreen) == B_OK)
                समुच्चयः_पूर्णम्_Screen(fullscreen);
            भङ्ग;
        }
        पक्ष BWIN_MINIMUM_आकार_गवाक्षः:
            समुच्चयः_Minimum_आकार(सन्देशः);
            भङ्ग;
        पक्ष BWIN_UPDATE_FRAMEBUFFER:
        {
            BMessage *pending_सन्देशः;
            यावत् ((pending_सन्देशः = सन्देशः_Queue()->Find_सन्देशः(BWIN_UPDATE_FRAMEBUFFER, 0))) {
                सन्देशः_Queue()->Remove_सन्देशः(pending_सन्देशः);
                delete pending_सन्देशः;
            }
            यदि (_bitmap != रिक्त) {
#यदि_परिभाषितम् SDL_VIDEO_OPENGL
                यदि (_SDL_GLView != रिक्त && _cur_view == _SDL_GLView) {
                    _SDL_GLView->Copy_Pixels_अन्तर्(_bitmap, B_ORIGIN);
                } अन्यथा
#यदि_अन्तः
                यदि (_SDL_View != रिक्त && _cur_view == _SDL_View) {
                    _SDL_View->Draw(Bounds());
                }
            }
            भङ्ग;
        }
        स्वभाव:
            // Perform normal message handling
            BWindow::सन्देशः_Received(सन्देशः);
            भङ्ग;
        }
    }

    // Accessor methods
    bool IsShown() { प्रत्यागम _shown; }
    int32 GetID() { प्रत्यागम _id; }
    BBitmap *GetBitmap() { प्रत्यागम _bitmap; }
    BView *GetCurView() { प्रत्यागम _cur_view; }
    SDL_BView *GetView() { प्रत्यागम _SDL_View; }
#यदि_परिभाषितम् SDL_VIDEO_OPENGL
    BGLView *GetGLView()
    {
        प्रत्यागम _SDL_GLView;
    }
    Uint32 GetGLType() { प्रत्यागम _gl_type; }
#यदि_अन्तः

    // Setter methods
    शून्य समुच्चयः_ID(int32 id) { _id = id; }
    शून्य तालकम्_बफर() { बफर_locker->तालकम्(); }
    शून्य Unlock_बफर() { बफर_locker->Unlock(); }
    शून्य समुच्चयः_Bitmap(BBitmap *bitmap)
    {
        _bitmap = bitmap;
        यदि (_SDL_View != रिक्त)
            _SDL_View->समुच्चयः_Bitmap(bitmap);
    }

  गुप्त:
    // Event redirection
    शून्य _MouseMotionEvent(BPoint &where, int32 transit)
    {
        यदि (transit == B_EXITED_VIEW) {
            // Change mouse focus
            यदि (_mouse_focused) {
                _MouseFocusEvent(false);
            }
        } अन्यथा {
            // Change mouse focus
            यदि (!_mouse_focused) {
                _MouseFocusEvent(true);
            }
            BMessage सन्देशः_2(BAPP_MOUSE_MOVED);
            सन्देशः_2.सङ्कलय_Int32("x", (पूर्णाङ्क)where.x);
            सन्देशः_2.सङ्कलय_Int32("y", (पूर्णाङ्क)where.y);

            Post_गवाक्षः_Event(सन्देशः_2);
        }
    }

    शून्य _MouseFocusEvent(bool focusGained)
    {
        _mouse_focused = focusGained;
        BMessage सन्देशः_2(BAPP_MOUSE_FOCUS);
        सन्देशः_2.सङ्कलय_Bool("focusGained", focusGained);
        Post_गवाक्षः_Event(सन्देशः_2);

        /* FIXME: Why were these here?
         if false: be_app->SetCursor(B_HAND_CURSOR);
         if true:  SDL_SetCursor(NULL); */
    }

    शून्य _MouseButtonEvent(int32 buttons, bool अधस्तात्)
    {
        int32 buttonStateChange = buttons ^ चरमः_buttons;

        यदि (buttonStateChange & B_PRIMARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_वामः, अधस्तात्);
        }
        यदि (buttonStateChange & B_SECONDARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_दक्षिणः, अधस्तात्);
        }
        यदि (buttonStateChange & B_TERTIARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_मध्यः, अधस्तात्);
        }

        चरमः_buttons = buttons;
    }

    शून्य _SendMouseButton(int32 button, bool अधस्तात्)
    {
        BMessage सन्देशः_2(BAPP_MOUSE_BUTTON);
        सन्देशः_2.सङ्कलय_Int32("button-id", button);
        सन्देशः_2.सङ्कलय_Bool("button-down", अधस्तात्);
        Post_गवाक्षः_Event(सन्देशः_2);
    }

    शून्य _MouseWheelEvent(int32 x, int32 y)
    {
        // Create a message to pass along to the BeApp thread
        BMessage सन्देशः_2(BAPP_MOUSE_WHEEL);
        सन्देशः_2.सङ्कलय_Int32("xticks", x);
        सन्देशः_2.सङ्कलय_Int32("yticks", y);
        Post_गवाक्षः_Event(सन्देशः_2);
    }

    शून्य कुञ्चिका_Event_2(int32 कुञ्चिका_संहिता, ध्रुव int8 *कुञ्चिका_Utf8, ध्रुव ssize_t &len, bool अधस्तात्)
    {
        // Create a message to pass along to the BeApp thread
        BMessage सन्देशः_2(BAPP_कुञ्चिका);
        सन्देशः_2.सङ्कलय_Int32("key-scancode", कुञ्चिका_संहिता);
        यदि (कुञ्चिका_Utf8 != रिक्त) {
            सन्देशः_2.सङ्कलय_दत्त("key-utf8", B_INT8_TYPE, (ध्रुव शून्य *)कुञ्चिका_Utf8, len);
        }
        सन्देशः_2.सङ्कलय_Bool("key-down", अधस्तात्);
        SDL_Looper->Post_सन्देशः(&सन्देशः_2);
    }

    शून्य _RepaintEvent()
    {
        // Force a repaint: Call the SDL exposed event
        BMessage सन्देशः_2(BAPP_REPAINT);
        Post_गवाक्षः_Event(सन्देशः_2);
    }
    शून्य Post_गवाक्षः_Event(BMessage &सन्देशः_2)
    {
        सन्देशः_2.सङ्कलय_Int32("window-id", _id);
        SDL_Looper->Post_सन्देशः(&सन्देशः_2);
    }

    // Command methods (functions called upon by SDL)
    शून्य समुच्चयः_Title(BMessage *सन्देशः_2)
    {
        ध्रुव वर्ण *title;
        यदि (
            सन्देशः_2->FindString("window-title", &title) != B_OK) {
            प्रत्यागम;
        }
        समुच्चयः_Title_2(title);
    }

    शून्य Move_गन्तव्यम्_2(BMessage *सन्देशः_2)
    {
        int32 x, y;
        यदि (
            सन्देशः_2->FindInt32("window-x", &x) != B_OK ||
            सन्देशः_2->FindInt32("window-y", &y) != B_OK) {
            प्रत्यागम;
        }
        यदि (_fullscreen)
            _non_fullscreen_frame.विस्थापनम्_गन्तव्यम्(x, y);
        अन्यथा
            Move_गन्तव्यम्(x, y);
    }

    शून्य Resize_गन्तव्यम्_2(BMessage *सन्देशः_2)
    {
        int32 w, h;
        यदि (
            सन्देशः_2->FindInt32("window-w", &w) != B_OK ||
            सन्देशः_2->FindInt32("window-h", &h) != B_OK) {
            प्रत्यागम;
        }
        यदि (_fullscreen) {
            _non_fullscreen_frame.दक्षिणः = _non_fullscreen_frame.वामः + w;
            _non_fullscreen_frame.bottom = _non_fullscreen_frame.शिखरम् + h;
        } अन्यथा
            Resize_गन्तव्यम्(w, h);
    }

    शून्य समुच्चयः_Bordered(bool bEnabled)
    {
        यदि (_fullscreen)
            _bordered = bEnabled;
        अन्यथा
            समुच्चयः_Look(bEnabled ? B_TITLED_गवाक्षः_LOOK : B_NO_BORDER_गवाक्षः_LOOK);
    }

    शून्य समुच्चयः_Resizable(bool bEnabled)
    {
        यदि (_fullscreen)
            _resizable = bEnabled;
        अन्यथा {
            यदि (bEnabled) {
                समुच्चयः_Flags(Flags() & ~(B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            } अन्यथा {
                समुच्चयः_Flags(Flags() | (B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            }
        }
    }

    शून्य समुच्चयः_Minimum_आकार(BMessage *सन्देशः_2)
    {
        भिन्न maxHeight;
        भिन्न max_विस्तारः;
        भिन्न _;
        int32 minHeight;
        int32 min_विस्तारः;

        // This is a bit convoluted, we only want to set the minimum not the maximum
        // But there is no direct call to do that, so store the maximum size beforehand
        Get_आकार_Limits(&_, &max_विस्तारः, &_, &maxHeight);
        यदि (सन्देशः_2->FindInt32("window-w", &min_विस्तारः) != B_OK)
            प्रत्यागम;
        यदि (सन्देशः_2->FindInt32("window-h", &minHeight) != B_OK)
            प्रत्यागम;
        समुच्चयः_आकार_Limits((भिन्न)min_विस्तारः, max_विस्तारः, (भिन्न)minHeight, maxHeight);
        Update_आकार_Limits();
    }

    शून्य _Restore()
    {
        यदि (IsMinimized()) {
            Minimize(false);
        } अन्यथा यदि (IsHidden()) {
            Show();
        } अन्यथा यदि (_fullscreen) {

        } अन्यथा यदि (पूर्व_frame != रिक्त) { // Zoomed
            Move_गन्तव्यम्(पूर्व_frame->वामः, पूर्व_frame->शिखरम्);
            Resize_गन्तव्यम्(पूर्व_frame->विस्तारः_2(), पूर्व_frame->Height());
        }
    }

    शून्य समुच्चयः_पूर्णम्_Screen(bool fullscreen)
    {
        यदि (fullscreen != _fullscreen) {
            यदि (fullscreen) {
                BScreen screen(this);
                BRect screenFrame = screen.Frame();
                _bordered = Look() != B_NO_BORDER_गवाक्षः_LOOK;
                _resizable = !(Flags() & B_NOT_RESIZABLE);
                _non_fullscreen_frame = Frame();
                समुच्चयः_Bordered(false);
                समुच्चयः_Resizable(false);
                Move_गन्तव्यम्(screenFrame.वामः, screenFrame.शिखरम्);
                Resize_गन्तव्यम्(screenFrame.विस्तारः_2(), screenFrame.Height());
                _fullscreen = fullscreen;
            } अन्यथा {
                _fullscreen = fullscreen;
                Move_गन्तव्यम्(_non_fullscreen_frame.वामः, _non_fullscreen_frame.शिखरम्);
                Resize_गन्तव्यम्(_non_fullscreen_frame.विस्तारः_2(), _non_fullscreen_frame.Height());
                समुच्चयः_Bordered(_bordered);
                समुच्चयः_Resizable(_resizable);
            }
        }
    }

    // Members

    BView *_cur_view;
    SDL_BView *_SDL_View;
#यदि_परिभाषितम् SDL_VIDEO_OPENGL
    BGLView *_SDL_GLView;
    Uint32 _gl_type;
#यदि_अन्तः

    int32 चरमः_buttons;
    int32 _id;           // Window id used by SDL_BApp
    bool _mouse_focused; // Does this window have mouse focus?
    bool _shown;
    bool _inhibit_resize;

    BRect *पूर्व_frame; // Previous position and size of the window
    bool _fullscreen;
    // valid only if fullscreen
    BRect _non_fullscreen_frame;
    bool _bordered;
    bool _resizable;

    // Framebuffer members
    BLocker *बफर_locker;
    BBitmap *_bitmap;
};

/* FIXME:
 * An explanation of framebuffer flags.
 *
 * _connected -           Original variable used to let the drawing thread know
 *                         when changes are being made to the other framebuffer
 *                         members.
 * _connection_disabled - Used to signal to the drawing thread that the window
 *                         is closing, and the thread should exit.
 * _buffer_created -      True if the current buffer is valid
 * _buffer_dirty -        True if the window should be redrawn.
 * _trash_window_buffer - True if the window buffer needs to be trashed partway
 *                         through a draw cycle.  Occurs when the previous
 *                         buffer provided by DirectConnected() is invalidated.
 */
#यदि_अन्तः // SDL_BWin_h_
