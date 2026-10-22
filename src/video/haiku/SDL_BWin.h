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

#నిర్వచితం_కాకపోతే SDL_BWin_h_
#నిర్వచించు SDL_BWin_h_

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు

#అన్తర్భావ "SDL_internal.h"
#అన్తర్భావ "SDL_bframebuffer.h"

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అన్తర్భావ <stdio.h>
#అన్తర్భావ <AppKit.h>
#అన్తర్భావ <Cursor.h>
#అన్తర్భావ <InterfaceKit.h>
#నిర్వచితమైతే SDL_VIDEO_OPENGL
#అన్తర్భావ <opengl/GLView.h>
#అయితే_ముగింపు
#అన్తర్భావ "../../core/haiku/SDL_BApp.h"

గణన WinCommands
{
    BWIN_MOVE_కిటికీ,
    BWIN_RESIZE_కిటికీ,
    BWIN_SHOW_కిటికీ,
    BWIN_HIDE_కిటికీ,
    BWIN_MAXIMIZE_కిటికీ,
    BWIN_MINIMIZE_కిటికీ,
    BWIN_RESTORE_కిటికీ,
    BWIN_సమితి_TITLE,
    BWIN_సమితి_BORDERED,
    BWIN_సమితి_RESIZABLE,
    BWIN_FULLSCREEN,
    BWIN_UPDATE_FRAMEBUFFER,
    BWIN_MINIMUM_కొలత_కిటికీ
};

// non-OpenGL framebuffer view
class SDL_BView : బహిరంగ BView
{
  బహిరంగ:
    SDL_BView(BRect చట్రం, స్థిరరాశి అక్షరం *name, uint32 resizing_బహుళకం)
        : BView(చట్రం, name, resizing_బహుళకం, B_WILL_DRAW),
          fBitmap(ఖాళీ)
    {
    }

    శూన్య Draw(BRect dirty)
    {
        ఒకవేళ (fBitmap != ఖాళీ)
            DrawBitmap(fBitmap, B_ORIGIN);
    }

    శూన్య సమితి_Bitmap(BBitmap *bitmap)
    {
        fBitmap = bitmap;
    }

  అంతరంగ:
    BBitmap *fBitmap;
};

class SDL_BWin : బహిరంగ BWindow
{
  బహిరంగ:
    // Constructor/Destructor
    SDL_BWin(BRect bounds, కిటికీ_look look, uint32 flags)
        : BWindow(bounds, "Untitled", look, B_సాధారణ_కిటికీ_FEEL, flags)
    {
        చివరి_buttons = 0;

        _cur_view = ఖాళీ;
        _SDL_View = ఖాళీ;

#నిర్వచితమైతే SDL_VIDEO_OPENGL
        _SDL_GLView = ఖాళీ;
        _gl_type = 0;
#అయితే_ముగింపు
        _shown = false;
        _inhibit_resize = false;
        _mouse_focused = false;
        prev_చట్రం = ఖాళీ;
        _fullscreen = ఖాళీ;

        // Handle framebuffer stuff
        బఫరు_locker = new BLocker();
        _bitmap = ఖాళీ;
    }

    మాయా ~SDL_BWin()
    {
        తాళం();

        ఒకవేళ (_SDL_View != ఖాళీ && _SDL_View != _cur_view) {
            delete _SDL_View;
            _SDL_View = ఖాళీ;
        }

#నిర్వచితమైతే SDL_VIDEO_OPENGL
        ఒకవేళ (_SDL_GLView) {
            ఒకవేళ (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->సమితి_Current_Context(ఖాళీ);
            ఒకవేళ (_SDL_GLView == _cur_view)
                Remove_బిడ్డ(_SDL_GLView);
            _SDL_GLView = ఖాళీ;
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }

#అయితే_ముగింపు
        Unlock();

        delete prev_చట్రం;

        // Clean up framebuffer stuff
        బఫరు_locker->తాళం();
        delete బఫరు_locker;
    }

    శూన్య సమితి_Current_View(BView *view)
    {
        ఒకవేళ (_cur_view != view) {
            ఒకవేళ (_cur_view != ఖాళీ)
                Remove_బిడ్డ(_cur_view);
            _cur_view = view;
            ఒకవేళ (_cur_view != ఖాళీ)
                కూడు_బిడ్డ(_cur_view);
        }
    }

    శూన్య UpdateCurrentView()
    {
#నిర్వచితమైతే SDL_VIDEO_OPENGL
        ఒకవేళ (_SDL_GLView != ఖాళీ) {
            సమితి_Current_View(_SDL_GLView);
        } లేకపోతే
#అయితే_ముగింపు
        ఒకవేళ (_SDL_View != ఖాళీ) {
            సమితి_Current_View(_SDL_View);
        } లేకపోతే {
            సమితి_Current_View(ఖాళీ);
        }
    }

    SDL_BView *CreateView()
    {
        తాళం();
        ఒకవేళ (_SDL_View == ఖాళీ) {
            _SDL_View = new SDL_BView(Bounds(), "SDL View", B_FOLLOW_ALL_SIDES);
            UpdateCurrentView();
        }
        Unlock();
        తిరిగి _SDL_View;
    }

    శూన్య RemoveView()
    {
        తాళం();
        ఒకవేళ (_SDL_View != ఖాళీ) {
            SDL_BView *oldView = _SDL_View;
            _SDL_View = ఖాళీ;
            UpdateCurrentView();
            delete oldView;
        }
        Unlock();
    }

    /* * * * * OpenGL functionality * * * * */
#నిర్వచితమైతే SDL_VIDEO_OPENGL
    BGLView *CreateGLView(Uint32 gl_flags)
    {
        తాళం();
        ఒకవేళ (_SDL_GLView == ఖాళీ) {
            _SDL_GLView = new BGLView(Bounds(), "SDL GLView",
                                      B_FOLLOW_ALL_SIDES,
                                      (B_WILL_DRAW | B_చట్రం_EVENTS),
                                      gl_flags);
            _gl_type = gl_flags;
            UpdateCurrentView();
        }
        Unlock();
        తిరిగి _SDL_GLView;
    }

    శూన్య RemoveGLView()
    {
        తాళం();
        ఒకవేళ (_SDL_GLView != ఖాళీ) {
            ఒకవేళ (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->సమితి_Current_Context(ఖాళీ);
            _SDL_GLView = ఖాళీ;
            UpdateCurrentView();
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }
        Unlock();
    }

    శూన్య మార్పిడి_Buffers(శూన్య)
    {
        _SDL_GLView->మార్పిడి_Buffers();
    }
#అయితే_ముగింపు

    /* * * * * Event sending * * * * */
    // Hook functions
    మాయా శూన్య చట్రం_Moved(BPoint origin)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage సందేశం_2(BAPP_కిటికీ_MOVED);
        సందేశం_2.కూడు_Int32("window-x", (పూర్ణాంకం)origin.x);
        సందేశం_2.కూడు_Int32("window-y", (పూర్ణాంకం)origin.y);
        Post_కిటికీ_Event(సందేశం_2);

        // Perform normal hook operations
        BWindow::చట్రం_Moved(origin);
    }

    శూన్య చట్రం_Resized(దశాంశం వెడల్పు, దశాంశం ఎత్తు)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage సందేశం_2(BAPP_కిటికీ_RESIZED);

        సందేశం_2.కూడు_Int32("window-w", (పూర్ణాంకం)వెడల్పు + 1);
        సందేశం_2.కూడు_Int32("window-h", (పూర్ణాంకం)ఎత్తు + 1);
        Post_కిటికీ_Event(సందేశం_2);

        // Perform normal hook operations
        BWindow::చట్రం_Resized(వెడల్పు, ఎత్తు);
    }

    bool QuitRequested()
    {
        BMessage సందేశం_2(BAPP_కిటికీ_CLOSE_REQUESTED);
        Post_కిటికీ_Event(సందేశం_2);

        // We won't allow a quit unless asked by DestroyWindow()
        తిరిగి false;
    }

    శూన్య కిటికీ_Activated(bool చురుకైన)
    {
        BMessage సందేశం_2(BAPP_KEYBOARD_FOCUS); // Mouse focus sold separately
        సందేశం_2.కూడు_Bool("focusGained", చురుకైన);
        Post_కిటికీ_Event(సందేశం_2);
    }

    శూన్య Zoom(BPoint origin,
              దశాంశం వెడల్పు,
              దశాంశం ఎత్తు)
    {
        BMessage సందేశం_2(BAPP_MAXIMIZE); // Closest thing to maximization Haiku has
        Post_కిటికీ_Event(సందేశం_2);

        // Before the window zooms, record its size
        ఒకవేళ (!prev_చట్రం)
            prev_చట్రం = new BRect(చట్రం_2());

        // Perform normal hook operations
        BWindow::Zoom(origin, వెడల్పు, ఎత్తు);
    }

    // Member functions
    శూన్య Show()
    {
        అయితే (IsHidden()) {
            BWindow::Show();
        }
        _shown = true;

        BMessage సందేశం_2(BAPP_SHOW);
        Post_కిటికీ_Event(సందేశం_2);
    }

    శూన్య Hide()
    {
        BWindow::Hide();
        _shown = false;

        BMessage సందేశం_2(BAPP_HIDE);
        Post_కిటికీ_Event(సందేశం_2);
    }

    శూన్య Minimize(bool minimize)
    {
        BWindow::Minimize(minimize);
        int32 minState = (minimize ? BAPP_MINIMIZE : BAPP_RESTORE);

        BMessage సందేశం_2(minState);
        Post_కిటికీ_Event(సందేశం_2);
    }

    శూన్య Screen_మారింది(BRect screen_చట్రం, color_space లోతు_2)
    {
        ఒకవేళ (_fullscreen) {
            Move_గమ్యం(screen_చట్రం.ఎడమ, screen_చట్రం.శిఖరం);
            Resize_గమ్యం(screen_చట్రం.వెడల్పు_2(), screen_చట్రం.ఎత్తు_2());
        }
    }

    // BView message interruption
    శూన్య Dispatch_సందేశం(BMessage *సందేశం_2, BHandler *లక్ష్యం)
    {
        BPoint where;  // Used by mouse moved
        int32 buttons; // Used for mouse button events
        int32 కీలకం;     // Used for key events

        ఎంపిక (సందేశం_2->what) {
        స్థితి B_MOUSE_MOVED:
            int32 transit;
            ఒకవేళ (సందేశం_2->కనుగొను_బిందువు("where", &where) == B_OK && సందేశం_2->కనుగొను_Int32("be:transit", &transit) == B_OK) {
                _MouseMotionEvent(where, transit);
            }
            ఆపు;

        స్థితి B_MOUSE_కిందికి:
            ఒకవేళ (సందేశం_2->కనుగొను_Int32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, true);
            }
            ఆపు;

        స్థితి B_MOUSE_పైకి:
            ఒకవేళ (సందేశం_2->కనుగొను_Int32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, false);
            }
            ఆపు;

        స్థితి B_MOUSE_WHEEL_మారింది:
            దశాంశం x, y;
            ఒకవేళ (సందేశం_2->కనుగొను_Float("be:wheel_delta_x", &x) == B_OK && సందేశం_2->కనుగొను_Float("be:wheel_delta_y", &y) == B_OK) {
                _MouseWheelEvent((పూర్ణాంకం)x, (పూర్ణాంకం)y);
            }
            ఆపు;

        స్థితి B_కీలకం_కిందికి:
        {
            int32 i = 0;
            int8 byte;
            int8 బైట్లు[4] = { 0, 0, 0, 0 };
            అయితే (i < 4 && సందేశం_2->కనుగొను_Int8("byte", i, &byte) == B_OK) {
                బైట్లు[i] = byte;
                i++;
            }
            ఒకవేళ (సందేశం_2->కనుగొను_Int32("key", &కీలకం) == B_OK) {
                కీలకం_Event_2((SDL_Scancode)కీలకం, &బైట్లు[0], i, true);
            }
        } ఆపు;

        స్థితి B_UNMAPPED_కీలకం_కిందికి: // modifier keys are unmapped
            ఒకవేళ (సందేశం_2->కనుగొను_Int32("key", &కీలకం) == B_OK) {
                కీలకం_Event_2((SDL_Scancode)కీలకం, ఖాళీ, 0, true);
            }
            ఆపు;

        స్థితి B_కీలకం_పైకి:
        స్థితి B_UNMAPPED_కీలకం_పైకి: // modifier keys are unmapped
            ఒకవేళ (సందేశం_2->కనుగొను_Int32("key", &కీలకం) == B_OK) {
                కీలకం_Event_2(కీలకం, ఖాళీ, 0, false);
            }
            ఆపు;

        అప్రమేయ:
            /* move it after switch{} so it's always handled
               that way we keep Haiku features like:
               - CTRL+Q to close window (and other shortcuts)
               - PrintScreen to make screenshot into /boot/home
               - etc.. */
            // BWindow::DispatchMessage(msg, target);
            ఆపు;
        }

        BWindow::Dispatch_సందేశం(సందేశం_2, లక్ష్యం);
    }

    // Handle command messages
    శూన్య సందేశం_Received(BMessage *సందేశం)
    {
        ఎంపిక (సందేశం->what) {
        // Handle commands from SDL
        స్థితి BWIN_సమితి_TITLE:
            సమితి_Title(సందేశం);
            ఆపు;
        స్థితి BWIN_MOVE_కిటికీ:
            Move_గమ్యం_2(సందేశం);
            ఆపు;
        స్థితి BWIN_RESIZE_కిటికీ:
            Resize_గమ్యం_2(సందేశం);
            ఆపు;
        స్థితి BWIN_సమితి_BORDERED:
        {
            bool bEnabled;
            ఒకవేళ (సందేశం->కనుగొను_Bool("window-border", &bEnabled) == B_OK)
                సమితి_Bordered(bEnabled);
            ఆపు;
        }
        స్థితి BWIN_సమితి_RESIZABLE:
        {
            bool bEnabled;
            ఒకవేళ (సందేశం->కనుగొను_Bool("window-resizable", &bEnabled) == B_OK)
                సమితి_Resizable(bEnabled);
            ఆపు;
        }
        స్థితి BWIN_SHOW_కిటికీ:
            Show();
            ఆపు;
        స్థితి BWIN_HIDE_కిటికీ:
            Hide();
            ఆపు;
        స్థితి BWIN_MAXIMIZE_కిటికీ:
            BWindow::Zoom();
            ఆపు;
        స్థితి BWIN_MINIMIZE_కిటికీ:
            Minimize(true);
            ఆపు;
        స్థితి BWIN_RESTORE_కిటికీ:
            _Restore();
            ఆపు;
        స్థితి BWIN_FULLSCREEN:
        {
            bool fullscreen;
            ఒకవేళ (సందేశం->కనుగొను_Bool("fullscreen", &fullscreen) == B_OK)
                సమితి_నిండిన_Screen(fullscreen);
            ఆపు;
        }
        స్థితి BWIN_MINIMUM_కొలత_కిటికీ:
            సమితి_Minimum_కొలత(సందేశం);
            ఆపు;
        స్థితి BWIN_UPDATE_FRAMEBUFFER:
        {
            BMessage *pending_సందేశం;
            అయితే ((pending_సందేశం = సందేశం_వరుస()->కనుగొను_సందేశం(BWIN_UPDATE_FRAMEBUFFER, 0))) {
                సందేశం_వరుస()->Remove_సందేశం(pending_సందేశం);
                delete pending_సందేశం;
            }
            ఒకవేళ (_bitmap != ఖాళీ) {
#నిర్వచితమైతే SDL_VIDEO_OPENGL
                ఒకవేళ (_SDL_GLView != ఖాళీ && _cur_view == _SDL_GLView) {
                    _SDL_GLView->Copy_Pixels_లోపల(_bitmap, B_ORIGIN);
                } లేకపోతే
#అయితే_ముగింపు
                ఒకవేళ (_SDL_View != ఖాళీ && _cur_view == _SDL_View) {
                    _SDL_View->Draw(Bounds());
                }
            }
            ఆపు;
        }
        అప్రమేయ:
            // Perform normal message handling
            BWindow::సందేశం_Received(సందేశం);
            ఆపు;
        }
    }

    // Accessor methods
    bool IsShown() { తిరిగి _shown; }
    int32 GetID() { తిరిగి _id; }
    BBitmap *GetBitmap() { తిరిగి _bitmap; }
    BView *GetCurView() { తిరిగి _cur_view; }
    SDL_BView *GetView() { తిరిగి _SDL_View; }
#నిర్వచితమైతే SDL_VIDEO_OPENGL
    BGLView *GetGLView()
    {
        తిరిగి _SDL_GLView;
    }
    Uint32 GetGLType() { తిరిగి _gl_type; }
#అయితే_ముగింపు

    // Setter methods
    శూన్య సమితి_ID(int32 id) { _id = id; }
    శూన్య తాళం_బఫరు() { బఫరు_locker->తాళం(); }
    శూన్య Unlock_బఫరు() { బఫరు_locker->Unlock(); }
    శూన్య సమితి_Bitmap(BBitmap *bitmap)
    {
        _bitmap = bitmap;
        ఒకవేళ (_SDL_View != ఖాళీ)
            _SDL_View->సమితి_Bitmap(bitmap);
    }

  అంతరంగ:
    // Event redirection
    శూన్య _MouseMotionEvent(BPoint &where, int32 transit)
    {
        ఒకవేళ (transit == B_EXITED_VIEW) {
            // Change mouse focus
            ఒకవేళ (_mouse_focused) {
                _MouseFocusEvent(false);
            }
        } లేకపోతే {
            // Change mouse focus
            ఒకవేళ (!_mouse_focused) {
                _MouseFocusEvent(true);
            }
            BMessage సందేశం_2(BAPP_MOUSE_MOVED);
            సందేశం_2.కూడు_Int32("x", (పూర్ణాంకం)where.x);
            సందేశం_2.కూడు_Int32("y", (పూర్ణాంకం)where.y);

            Post_కిటికీ_Event(సందేశం_2);
        }
    }

    శూన్య _MouseFocusEvent(bool focusGained)
    {
        _mouse_focused = focusGained;
        BMessage సందేశం_2(BAPP_MOUSE_FOCUS);
        సందేశం_2.కూడు_Bool("focusGained", focusGained);
        Post_కిటికీ_Event(సందేశం_2);

        /* FIXME: Why were these here?
         if false: be_app->SetCursor(B_HAND_CURSOR);
         if true:  SDL_SetCursor(NULL); */
    }

    శూన్య _MouseButtonEvent(int32 buttons, bool కిందికి)
    {
        int32 buttonStateChange = buttons ^ చివరి_buttons;

        ఒకవేళ (buttonStateChange & B_PRIMARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_ఎడమ, కిందికి);
        }
        ఒకవేళ (buttonStateChange & B_SECONDARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_కుడి, కిందికి);
        }
        ఒకవేళ (buttonStateChange & B_TERTIARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_మధ్య, కిందికి);
        }

        చివరి_buttons = buttons;
    }

    శూన్య _SendMouseButton(int32 button, bool కిందికి)
    {
        BMessage సందేశం_2(BAPP_MOUSE_BUTTON);
        సందేశం_2.కూడు_Int32("button-id", button);
        సందేశం_2.కూడు_Bool("button-down", కిందికి);
        Post_కిటికీ_Event(సందేశం_2);
    }

    శూన్య _MouseWheelEvent(int32 x, int32 y)
    {
        // Create a message to pass along to the BeApp thread
        BMessage సందేశం_2(BAPP_MOUSE_WHEEL);
        సందేశం_2.కూడు_Int32("xticks", x);
        సందేశం_2.కూడు_Int32("yticks", y);
        Post_కిటికీ_Event(సందేశం_2);
    }

    శూన్య కీలకం_Event_2(int32 కీలకం_సంకేతం, స్థిరరాశి int8 *కీలకం_Utf8, స్థిరరాశి ssize_t &len, bool కిందికి)
    {
        // Create a message to pass along to the BeApp thread
        BMessage సందేశం_2(BAPP_కీలకం);
        సందేశం_2.కూడు_Int32("key-scancode", కీలకం_సంకేతం);
        ఒకవేళ (కీలకం_Utf8 != ఖాళీ) {
            సందేశం_2.కూడు_దత్తాంశం("key-utf8", B_INT8_TYPE, (స్థిరరాశి శూన్య *)కీలకం_Utf8, len);
        }
        సందేశం_2.కూడు_Bool("key-down", కిందికి);
        SDL_Looper->Post_సందేశం(&సందేశం_2);
    }

    శూన్య _RepaintEvent()
    {
        // Force a repaint: Call the SDL exposed event
        BMessage సందేశం_2(BAPP_REPAINT);
        Post_కిటికీ_Event(సందేశం_2);
    }
    శూన్య Post_కిటికీ_Event(BMessage &సందేశం_2)
    {
        సందేశం_2.కూడు_Int32("window-id", _id);
        SDL_Looper->Post_సందేశం(&సందేశం_2);
    }

    // Command methods (functions called upon by SDL)
    శూన్య సమితి_Title(BMessage *సందేశం_2)
    {
        స్థిరరాశి అక్షరం *title;
        ఒకవేళ (
            సందేశం_2->కనుగొను_String("window-title", &title) != B_OK) {
            తిరిగి;
        }
        సమితి_Title_2(title);
    }

    శూన్య Move_గమ్యం_2(BMessage *సందేశం_2)
    {
        int32 x, y;
        ఒకవేళ (
            సందేశం_2->కనుగొను_Int32("window-x", &x) != B_OK ||
            సందేశం_2->కనుగొను_Int32("window-y", &y) != B_OK) {
            తిరిగి;
        }
        ఒకవేళ (_fullscreen)
            non_fullscreen_చట్రం.స్థానభ్రంశం_గమ్యం(x, y);
        లేకపోతే
            Move_గమ్యం(x, y);
    }

    శూన్య Resize_గమ్యం_2(BMessage *సందేశం_2)
    {
        int32 w, h;
        ఒకవేళ (
            సందేశం_2->కనుగొను_Int32("window-w", &w) != B_OK ||
            సందేశం_2->కనుగొను_Int32("window-h", &h) != B_OK) {
            తిరిగి;
        }
        ఒకవేళ (_fullscreen) {
            non_fullscreen_చట్రం.కుడి = non_fullscreen_చట్రం.ఎడమ + w;
            non_fullscreen_చట్రం.bottom = non_fullscreen_చట్రం.శిఖరం + h;
        } లేకపోతే
            Resize_గమ్యం(w, h);
    }

    శూన్య సమితి_Bordered(bool bEnabled)
    {
        ఒకవేళ (_fullscreen)
            _bordered = bEnabled;
        లేకపోతే
            సమితి_Look(bEnabled ? B_TITLED_కిటికీ_LOOK : B_NO_BORDER_కిటికీ_LOOK);
    }

    శూన్య సమితి_Resizable(bool bEnabled)
    {
        ఒకవేళ (_fullscreen)
            _resizable = bEnabled;
        లేకపోతే {
            ఒకవేళ (bEnabled) {
                సమితి_Flags(Flags() & ~(B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            } లేకపోతే {
                సమితి_Flags(Flags() | (B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            }
        }
    }

    శూన్య సమితి_Minimum_కొలత(BMessage *సందేశం_2)
    {
        దశాంశం max_ఎత్తు;
        దశాంశం max_వెడల్పు;
        దశాంశం _;
        int32 min_ఎత్తు;
        int32 min_వెడల్పు;

        // This is a bit convoluted, we only want to set the minimum not the maximum
        // But there is no direct call to do that, so store the maximum size beforehand
        Get_కొలత_Limits(&_, &max_వెడల్పు, &_, &max_ఎత్తు);
        ఒకవేళ (సందేశం_2->కనుగొను_Int32("window-w", &min_వెడల్పు) != B_OK)
            తిరిగి;
        ఒకవేళ (సందేశం_2->కనుగొను_Int32("window-h", &min_ఎత్తు) != B_OK)
            తిరిగి;
        సమితి_కొలత_Limits((దశాంశం)min_వెడల్పు, max_వెడల్పు, (దశాంశం)min_ఎత్తు, max_ఎత్తు);
        Update_కొలత_Limits();
    }

    శూన్య _Restore()
    {
        ఒకవేళ (IsMinimized()) {
            Minimize(false);
        } లేకపోతే ఒకవేళ (IsHidden()) {
            Show();
        } లేకపోతే ఒకవేళ (_fullscreen) {

        } లేకపోతే ఒకవేళ (prev_చట్రం != ఖాళీ) { // Zoomed
            Move_గమ్యం(prev_చట్రం->ఎడమ, prev_చట్రం->శిఖరం);
            Resize_గమ్యం(prev_చట్రం->వెడల్పు_2(), prev_చట్రం->ఎత్తు_2());
        }
    }

    శూన్య సమితి_నిండిన_Screen(bool fullscreen)
    {
        ఒకవేళ (fullscreen != _fullscreen) {
            ఒకవేళ (fullscreen) {
                BScreen screen(this);
                BRect screen_చట్రం = screen.చట్రం_2();
                _bordered = Look() != B_NO_BORDER_కిటికీ_LOOK;
                _resizable = !(Flags() & B_NOT_RESIZABLE);
                non_fullscreen_చట్రం = చట్రం_2();
                సమితి_Bordered(false);
                సమితి_Resizable(false);
                Move_గమ్యం(screen_చట్రం.ఎడమ, screen_చట్రం.శిఖరం);
                Resize_గమ్యం(screen_చట్రం.వెడల్పు_2(), screen_చట్రం.ఎత్తు_2());
                _fullscreen = fullscreen;
            } లేకపోతే {
                _fullscreen = fullscreen;
                Move_గమ్యం(non_fullscreen_చట్రం.ఎడమ, non_fullscreen_చట్రం.శిఖరం);
                Resize_గమ్యం(non_fullscreen_చట్రం.వెడల్పు_2(), non_fullscreen_చట్రం.ఎత్తు_2());
                సమితి_Bordered(_bordered);
                సమితి_Resizable(_resizable);
            }
        }
    }

    // Members

    BView *_cur_view;
    SDL_BView *_SDL_View;
#నిర్వచితమైతే SDL_VIDEO_OPENGL
    BGLView *_SDL_GLView;
    Uint32 _gl_type;
#అయితే_ముగింపు

    int32 చివరి_buttons;
    int32 _id;           // Window id used by SDL_BApp
    bool _mouse_focused; // Does this window have mouse focus?
    bool _shown;
    bool _inhibit_resize;

    BRect *prev_చట్రం; // Previous position and size of the window
    bool _fullscreen;
    // valid only if fullscreen
    BRect non_fullscreen_చట్రం;
    bool _bordered;
    bool _resizable;

    // Framebuffer members
    BLocker *బఫరు_locker;
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
#అయితే_ముగింపు // SDL_BWin_h_
