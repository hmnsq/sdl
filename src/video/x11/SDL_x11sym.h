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

/* *INDENT-OFF* */ // clang-format off

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_X11_MODULE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_X11_MODULE(modname)
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_X11_SYM
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_X11_SYM(rc, fn, params)
#ਜੇ_ਅੰਤ

SDL_X11_MODULE(BASEXLIB)
SDL_X11_SYM(XSizeHints*,XAlloc_ਮਾਪ_Hints,(ਖਾਲੀ))
SDL_X11_SYM(XWMHints*,XAllocWMHints,(ਖਾਲੀ))
SDL_X11_SYM(XClassHint*,XAllocClassHint,(ਖਾਲੀ))
SDL_X11_SYM(ਪੂਰਨ,XChange_ਸੂਚਕ_Control,(Display* a,Bool b,Bool c,ਪੂਰਨ d,ਪੂਰਨ e,ਪੂਰਨ f))
SDL_X11_SYM(ਪੂਰਨ,XChangeProperty,(Display* a,ਖਿੜਕੀ_2 b,Atom c,Atom d,ਪੂਰਨ e,ਪੂਰਨ f,_Xconst ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ* g,ਪੂਰਨ h))
SDL_X11_SYM(Bool,XCheckIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(ਪੂਰਨ,XClear_ਖਿੜਕੀ,(Display* a,ਖਿੜਕੀ_2 b))
SDL_X11_SYM(ਪੂਰਨ,XCloseDisplay,(Display* a))
SDL_X11_SYM(ਪੂਰਨ,XConvertSelection,(Display* a,Atom b,Atom c,Atom d,ਖਿੜਕੀ_2 e,ਸਮਾਂ_2 f))
SDL_X11_SYM(Pixmap,XCreate_Bitmap_From_ਅੰਕੜੇ,(Display *dpy,Drawable d,_Xconst ਅੱਖਰ *ਅੰਕੜੇ,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਚੌੜਾਈ,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਉਚਾਈ))
SDL_X11_SYM(Colormap,XCreateColormap,(Display* a,ਖਿੜਕੀ_2 b,Visual* c,ਪੂਰਨ d))
SDL_X11_SYM(Cursor,XCreatePixmapCursor,(Display* a,Pixmap b,Pixmap c,XColor* d,XColor* e,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ f,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ g))
SDL_X11_SYM(Cursor,XCreatePixmap,(Display* a,Drawable b,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ d,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ e,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ f))
SDL_X11_SYM(Cursor,XCreateFontCursor,(Display* a,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ b))
SDL_X11_SYM(XFont_ਸੈੱਟ,XCreate_Font_ਸੈੱਟ,(Display* a, _Xconst ਅੱਖਰ* b, ਅੱਖਰ*** c, ਪੂਰਨ* d, ਅੱਖਰ** e))
SDL_X11_SYM(GC,XCreateGC,(Display* a,Drawable b,ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ c,XGCValues* d))
SDL_X11_SYM(ਖਾਲੀ,XSetFont,(Display* a,GC b,Font c))
SDL_X11_SYM(ਸਥਿਤੀ_2,XAllocColor,(Display *a, Colormap b, XColor *c))
SDL_X11_SYM(XImage*,XCreateImage,(Display* a,Visual* b,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ c,ਪੂਰਨ d,ਪੂਰਨ e,ਅੱਖਰ* f,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ g,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ h,ਪੂਰਨ i,ਪੂਰਨ j))
SDL_X11_SYM(ਖਿੜਕੀ_2,XCreate_ਖਿੜਕੀ,(Display* a,ਖਿੜਕੀ_2 b,ਪੂਰਨ c,ਪੂਰਨ d,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ e,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ f,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ g,ਪੂਰਨ h,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i,Visual* j,ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k,XSet_ਖਿੜਕੀ_ਗੁਣ* l))
SDL_X11_SYM(ਖਾਲੀ,XCopyArea,(Display *a, Drawable b, Drawable c, GC d, ਪੂਰਨ e, ਪੂਰਨ f, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ g, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ h, ਪੂਰਨ i, ਪੂਰਨ j))
SDL_X11_SYM(ਪੂਰਨ,XDefineCursor,(Display* a,ਖਿੜਕੀ_2 b,Cursor c))
SDL_X11_SYM(ਪੂਰਨ,XDeleteProperty,(Display* a,ਖਿੜਕੀ_2 b,Atom c))
SDL_X11_SYM(ਪੂਰਨ,XDestroy_ਖਿੜਕੀ,(Display* a,ਖਿੜਕੀ_2 b))
SDL_X11_SYM(ਪੂਰਨ,XDisplayKeycodes,(Display* a,ਪੂਰਨ* b,ਪੂਰਨ* c))
SDL_X11_SYM(ਪੂਰਨ,XDrawRectangle,(Display* a,Drawable b,GC c,ਪੂਰਨ d,ਪੂਰਨ e,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ f,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ g))
SDL_X11_SYM(ਪੂਰਨ,XFonts_ਦਾ_Font_ਸੈੱਟ,(XFont_ਸੈੱਟ a,XFontStruct ***b,ਅੱਖਰ ***c))
SDL_X11_SYM(ਪੂਰਨ,XFillArc,(Display* a,Drawable b,GC c,ਪੂਰਨ d,ਪੂਰਨ e,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ f,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ g, ਪੂਰਨ h, ਪੂਰਨ i))
SDL_X11_SYM(ਅੱਖਰ*,XDisplayName,(_Xconst ਅੱਖਰ* a))
SDL_X11_SYM(ਪੂਰਨ,XDrawString,(Display* a,Drawable b,GC c,ਪੂਰਨ d,ਪੂਰਨ e,_Xconst ਅੱਖਰ* f,ਪੂਰਨ g))
SDL_X11_SYM(ਪੂਰਨ,XEventsQueued,(Display* a,ਪੂਰਨ b))
SDL_X11_SYM(ਪੂਰਨ,XFillRectangle,(Display* a,Drawable b,GC c,ਪੂਰਨ d,ਪੂਰਨ e,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ f,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ g))
SDL_X11_SYM(Bool,XFilterEvent,(XEvent *event,ਖਿੜਕੀ_2 w))
SDL_X11_SYM(ਪੂਰਨ,XFlush,(Display* a))
SDL_X11_SYM(ਪੂਰਨ,XFree,(ਖਾਲੀ*a))
SDL_X11_SYM(ਪੂਰਨ,XFreeCursor,(Display* a,Cursor b))
SDL_X11_SYM(ਖਾਲੀ,XFree_Font_ਸੈੱਟ,(Display* a, XFont_ਸੈੱਟ b))
SDL_X11_SYM(ਪੂਰਨ,XFreeGC,(Display* a,GC b))
SDL_X11_SYM(ਪੂਰਨ,XFreeFont,(Display* a, XFontStruct* b))
SDL_X11_SYM(ਪੂਰਨ,XFreeModifiermap,(XModifierKeymap* a))
SDL_X11_SYM(ਪੂਰਨ,XFreePixmap,(Display* a,Pixmap b))
SDL_X11_SYM(ਪੂਰਨ,XFreeColormap,(Display* a,Colormap b))
SDL_X11_SYM(ਖਾਲੀ,XFreeStringList,(ਅੱਖਰ** a))
SDL_X11_SYM(ਅੱਖਰ*,XGetAtomName,(Display *a,Atom b))
SDL_X11_SYM(ਪੂਰਨ,XGet_ਨਿਵੇਸ਼_Focus,(Display *a,ਖਿੜਕੀ_2 *b,ਪੂਰਨ *c))
SDL_X11_SYM(ਕੁੰਜੀ_Sym*,XGetKeyboardMapping,(Display *a, ਕੁੰਜੀ_ਕੋਡ_2 b, ਪੂਰਨ c, ਪੂਰਨ *d))
SDL_X11_SYM(ਪੂਰਨ,XGet_Error_Database_ਪਾਠ,(Display* a,_Xconst ਅੱਖਰ* b,_Xconst ਅੱਖਰ* c,_Xconst ਅੱਖਰ* d,ਅੱਖਰ* e,ਪੂਰਨ f))
SDL_X11_SYM(XModifierKeymap*,XGetModifierMapping,(Display* a))
SDL_X11_SYM(ਪੂਰਨ,XGet_ਸੂਚਕ_Control,(Display* a,ਪੂਰਨ* b,ਪੂਰਨ* c,ਪੂਰਨ* d))
SDL_X11_SYM(ਖਿੜਕੀ_2,XGetSelectionOwner,(Display* a,Atom b))
SDL_X11_SYM(XVisualInfo*,XGetVisualInfo,(Display* a,ਲੰਮਾ b,XVisualInfo* c,ਪੂਰਨ* d))
SDL_X11_SYM(ਸਥਿਤੀ_2,XGet_ਖਿੜਕੀ_ਗੁਣ,(Display* a,ਖਿੜਕੀ_2 b,XWindow_ਗੁਣ* c))
SDL_X11_SYM(ਪੂਰਨ,XGet_ਖਿੜਕੀ_Property,(Display* a,ਖਿੜਕੀ_2 b,Atom c,ਲੰਮਾ d,ਲੰਮਾ e,Bool f,Atom g,Atom* h,ਪੂਰਨ* i,ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ* j,ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ *k,ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ **l))
SDL_X11_SYM(XWMHints*,XGetWMHints,(Display* a,ਖਿੜਕੀ_2 b))
SDL_X11_SYM(ਸਥਿਤੀ_2,XGetWMNormalHints,(Display *a,ਖਿੜਕੀ_2 b, XSizeHints *c, ਲੰਮਾ *d))
SDL_X11_SYM(ਪੂਰਨ,XIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(ਪੂਰਨ,XGrabKeyboard,(Display* a,ਖਿੜਕੀ_2 b,Bool c,ਪੂਰਨ d,ਪੂਰਨ e,ਸਮਾਂ_2 f))
SDL_X11_SYM(ਪੂਰਨ,XGrab_ਸੂਚਕ,(Display* a,ਖਿੜਕੀ_2 b,Bool c,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ d,ਪੂਰਨ e,ਪੂਰਨ f,ਖਿੜਕੀ_2 g,Cursor h,ਸਮਾਂ_2 i))
SDL_X11_SYM(ਪੂਰਨ,XGrabServer,(Display* a))
SDL_X11_SYM(ਸਥਿਤੀ_2,XIconify_ਖਿੜਕੀ,(Display* a,ਖਿੜਕੀ_2 b,ਪੂਰਨ c))
SDL_X11_SYM(ਕੁੰਜੀ_ਕੋਡ_2,XKeysym_ਮੰਜ਼ਿਲ_Keycode,(Display* a,ਕੁੰਜੀ_Sym b))
SDL_X11_SYM(ਅੱਖਰ*,XKeysym_ਮੰਜ਼ਿਲ_String,(ਕੁੰਜੀ_Sym a))
SDL_X11_SYM(ਪੂਰਨ,XInstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(Atom,XInternAtom,(Display* a,_Xconst ਅੱਖਰ* b,Bool c))
SDL_X11_SYM(XPixmap_Format_ਮੁੱਲਾਂ*,XListPixmapFormats,(Display* a,ਪੂਰਨ* b))
SDL_X11_SYM(XFontStruct*,XLoadQueryFont,(Display* a,_Xconst ਅੱਖਰ* b))
SDL_X11_SYM(ਕੁੰਜੀ_Sym,XLookupKeysym,(XKeyEvent* a,ਪੂਰਨ b))
SDL_X11_SYM(ਪੂਰਨ,XLookupString,(XKeyEvent* a,ਅੱਖਰ* b,ਪੂਰਨ c,ਕੁੰਜੀ_Sym* d,XCompose_ਸਥਿਤੀ* e))
SDL_X11_SYM(ਪੂਰਨ,XMapRaised,(Display* a,ਖਿੜਕੀ_2 b))
SDL_X11_SYM(ਸਥਿਤੀ_2,XMatchVisualInfo,(Display* a,ਪੂਰਨ b,ਪੂਰਨ c,ਪੂਰਨ d,XVisualInfo* e))
SDL_X11_SYM(ਪੂਰਨ,XMissingExtension,(Display* a,_Xconst ਅੱਖਰ* b))
SDL_X11_SYM(ਪੂਰਨ,XMove_ਖਿੜਕੀ,(Display* a,ਖਿੜਕੀ_2 b,ਪੂਰਨ c,ਪੂਰਨ d))
SDL_X11_SYM(Display*,XOpenDisplay,(_Xconst ਅੱਖਰ* a))
SDL_X11_SYM(ਸਥਿਤੀ_2,XInit_ਧਾਗੇ,(ਖਾਲੀ))
SDL_X11_SYM(ਪੂਰਨ,XPeekEvent,(Display* a,XEvent* b))
SDL_X11_SYM(ਪੂਰਨ,XPending,(Display* a))
SDL_X11_SYM(XImage*,XGetImage,(Display* a,Drawable b,ਪੂਰਨ c, ਪੂਰਨ d,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ e,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ f,ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ g,ਪੂਰਨ h))
SDL_X11_SYM(ਪੂਰਨ,XPutImage,(Display* a,Drawable b,GC c,XImage* d,ਪੂਰਨ e,ਪੂਰਨ f,ਪੂਰਨ g,ਪੂਰਨ h,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ j))
SDL_X11_SYM(ਪੂਰਨ,XQueryKeymap,(Display* a,ਅੱਖਰ b[32]))
SDL_X11_SYM(Bool,XQuery_ਸੂਚਕ,(Display* a,ਖਿੜਕੀ_2 b,ਖਿੜਕੀ_2* c,ਖਿੜਕੀ_2* d,ਪੂਰਨ* e,ਪੂਰਨ* f,ਪੂਰਨ* g,ਪੂਰਨ* h,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ* i))
SDL_X11_SYM(ਪੂਰਨ,XRaise_ਖਿੜਕੀ,(Display* a,ਖਿੜਕੀ_2 b))
SDL_X11_SYM(ਪੂਰਨ,XReparent_ਖਿੜਕੀ,(Display* a,ਖਿੜਕੀ_2 b,ਖਿੜਕੀ_2 c,ਪੂਰਨ d,ਪੂਰਨ e))
SDL_X11_SYM(ਪੂਰਨ,XResetScreenSaver,(Display* a))
SDL_X11_SYM(ਪੂਰਨ,XResize_ਖਿੜਕੀ,(Display* a,ਖਿੜਕੀ_2 b,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ c,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ d))
SDL_X11_SYM(ਪੂਰਨ,XScreen_ਸੰਖਿਆ_ਦਾ_Screen,(Screen* a))
SDL_X11_SYM(ਪੂਰਨ,XSelect_ਨਿਵੇਸ਼,(Display* a,ਖਿੜਕੀ_2 b,ਲੰਮਾ c))
SDL_X11_SYM(ਸਥਿਤੀ_2,XSendEvent,(Display* a,ਖਿੜਕੀ_2 b,Bool c,ਲੰਮਾ d,XEvent* e))
SDL_X11_SYM(XErrorHandler,XSetErrorHandler,(XErrorHandler a))
SDL_X11_SYM(ਪੂਰਨ,XSetForeground,(Display* a,GC b,ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ c))
SDL_X11_SYM(XIOErrorHandler,XSetIOErrorHandler,(XIOErrorHandler a))
SDL_X11_SYM(ਪੂਰਨ,XSet_ਨਿਵੇਸ਼_Focus,(Display *a,ਖਿੜਕੀ_2 b,ਪੂਰਨ c,ਸਮਾਂ_2 d))
SDL_X11_SYM(ਪੂਰਨ,XSetSelectionOwner,(Display* a,Atom b,ਖਿੜਕੀ_2 c,ਸਮਾਂ_2 d))
SDL_X11_SYM(ਪੂਰਨ,XSetTransientForHint,(Display* a,ਖਿੜਕੀ_2 b,ਖਿੜਕੀ_2 c))
SDL_X11_SYM(ਖਾਲੀ,XSet_ਪਾਠ_Property,(Display* a,ਖਿੜਕੀ_2 b,XTextProperty* c,Atom d))
SDL_X11_SYM(ਪੂਰਨ,XSet_ਖਿੜਕੀ_Background,(Display* a,ਖਿੜਕੀ_2 b,ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ c))
SDL_X11_SYM(ਖਾਲੀ,XSetWMHints,(Display* a,ਖਿੜਕੀ_2 b,XWMHints* c))
SDL_X11_SYM(ਖਾਲੀ,XSetWMNormalHints,(Display* a,ਖਿੜਕੀ_2 b,XSizeHints* c))
SDL_X11_SYM(ਖਾਲੀ,XSetWMProperties,(Display* a,ਖਿੜਕੀ_2 b,XTextProperty* c,XTextProperty* d,ਅੱਖਰ** e,ਪੂਰਨ f,XSizeHints* g,XWMHints* h,XClassHint* i))
SDL_X11_SYM(ਸਥਿਤੀ_2,XSetWMProtocols,(Display* a,ਖਿੜਕੀ_2 b,Atom* c,ਪੂਰਨ d))
SDL_X11_SYM(ਪੂਰਨ,XStoreColors,(Display* a,Colormap b,XColor* c,ਪੂਰਨ d))
SDL_X11_SYM(ਪੂਰਨ,XStoreName,(Display* a,ਖਿੜਕੀ_2 b,_Xconst ਅੱਖਰ* c))
SDL_X11_SYM(ਸਥਿਤੀ_2,XString_List_ਮੰਜ਼ਿਲ_ਪਾਠ_Property,(ਅੱਖਰ** a,ਪੂਰਨ b,XTextProperty* c))
SDL_X11_SYM(ਪੂਰਨ,XSync,(Display* a,Bool b))
SDL_X11_SYM(ਪੂਰਨ,XTextExtents,(XFontStruct* a,_Xconst ਅੱਖਰ* b,ਪੂਰਨ c,ਪੂਰਨ* d,ਪੂਰਨ* e,ਪੂਰਨ* f,XCharStruct* g))
SDL_X11_SYM(Bool,XTranslateCoordinates,(Display *a,ਖਿੜਕੀ_2 b,ਖਿੜਕੀ_2 c,ਪੂਰਨ d,ਪੂਰਨ e,ਪੂਰਨ* f,ਪੂਰਨ* g,ਖਿੜਕੀ_2* h))
SDL_X11_SYM(ਪੂਰਨ,XUndefineCursor,(Display* a,ਖਿੜਕੀ_2 b))
SDL_X11_SYM(ਪੂਰਨ,XUngrabKeyboard,(Display* a,ਸਮਾਂ_2 b))
SDL_X11_SYM(ਪੂਰਨ,XUngrab_ਸੂਚਕ,(Display* a,ਸਮਾਂ_2 b))
SDL_X11_SYM(ਪੂਰਨ,XUngrabServer,(Display* a))
SDL_X11_SYM(ਪੂਰਨ,XUninstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(ਪੂਰਨ,XUnloadFont,(Display* a,Font b))
SDL_X11_SYM(ਪੂਰਨ,XWarp_ਸੂਚਕ,(Display* a,ਖਿੜਕੀ_2 b,ਖਿੜਕੀ_2 c,ਪੂਰਨ d,ਪੂਰਨ e,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ f,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ g,ਪੂਰਨ h,ਪੂਰਨ i))
SDL_X11_SYM(ਪੂਰਨ,XWindowEvent,(Display* a,ਖਿੜਕੀ_2 b,ਲੰਮਾ c,XEvent* d))
SDL_X11_SYM(ਸਥਿਤੀ_2,XWithdraw_ਖਿੜਕੀ,(Display* a,ਖਿੜਕੀ_2 b,ਪੂਰਨ c))
SDL_X11_SYM(VisualID,XVisualIDFromVisual,(Visual* a))
SDL_X11_SYM(ਅੱਖਰ*,XGetDefault,(Display* a,_Xconst ਅੱਖਰ* b, _Xconst ਅੱਖਰ* c))
SDL_X11_SYM(Bool,XQueryExtension,(Display* a,_Xconst ਅੱਖਰ* b,ਪੂਰਨ* c,ਪੂਰਨ* d,ਪੂਰਨ* e))
SDL_X11_SYM(ਅੱਖਰ *,XDisplayString,(Display* a))
SDL_X11_SYM(ਪੂਰਨ,XGet_Error_ਪਾਠ,(Display* a,ਪੂਰਨ b,ਅੱਖਰ* c,ਪੂਰਨ d))
SDL_X11_SYM(ਖਾਲੀ,XEat_ਅੰਕੜੇ,(Display* a,ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ b))
SDL_X11_SYM(ਖਾਲੀ,_XFlush,(Display* a))
SDL_X11_SYM(ਖਾਲੀ,_XFlushGCCache,(Display* a,GC b))
SDL_X11_SYM(ਪੂਰਨ,_XRead,(Display* a,ਅੱਖਰ* b,ਲੰਮਾ c))
SDL_X11_SYM(ਖਾਲੀ,_XReadPad,(Display* a,ਅੱਖਰ* b,ਲੰਮਾ c))
SDL_X11_SYM(ਖਾਲੀ,_XSend,(Display* a,_Xconst ਅੱਖਰ* b,ਲੰਮਾ c))
SDL_X11_SYM(ਸਥਿਤੀ_2,_XReply,(Display* a,x_ਜਵਾਬ* b,ਪੂਰਨ c,Bool d))
SDL_X11_SYM(ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ,XSet_ਆਖਰੀ_Request_Read,(Display* a,x_Generic_ਜਵਾਬ* b))
SDL_X11_SYM(SDL_X11_XSynchronizeRetType,XSynchronize,(Display* a,Bool b))
SDL_X11_SYM(SDL_X11_XESet_Wire_ਮੰਜ਼ਿਲ_Event_Ret_Type,XESet_Wire_ਮੰਜ਼ਿਲ_Event,(Display* a,ਪੂਰਨ b,SDL_X11_XESet_Wire_ਮੰਜ਼ਿਲ_Event_Ret_Type c))
SDL_X11_SYM(SDL_X11_XESet_Event_ਮੰਜ਼ਿਲ_Wire_Ret_Type,XESet_Event_ਮੰਜ਼ਿਲ_Wire,(Display* a,ਪੂਰਨ b,SDL_X11_XESet_Event_ਮੰਜ਼ਿਲ_Wire_Ret_Type c))
SDL_X11_SYM(ਖਾਲੀ,XRefreshKeyboardMapping,(XMappingEvent *a))
SDL_X11_SYM(ਪੂਰਨ,XQuery_ਰੁੱਖ,(Display* a,ਖਿੜਕੀ_2 b,ਖਿੜਕੀ_2* c,ਖਿੜਕੀ_2* d,ਖਿੜਕੀ_2** e,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ* f))
SDL_X11_SYM(Bool,XSupportsLocale,(ਖਾਲੀ))
SDL_X11_SYM(ਸਥਿਤੀ_2,Xmb_ਪਾਠ_List_ਮੰਜ਼ਿਲ_ਪਾਠ_Property,(Display* a,ਅੱਖਰ** b,ਪੂਰਨ c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(Region,XCreateRegion,(ਖਾਲੀ))
SDL_X11_SYM(ਪੂਰਨ,XUnionRectWithRegion,(XRectangle *a, Region b, Region c))
SDL_X11_SYM(ਖਾਲੀ,XDestroyRegion,(Region))
SDL_X11_SYM(ਖਾਲੀ,XrmInitialize,(ਖਾਲੀ))
SDL_X11_SYM(ਅੱਖਰ*,XResourceManagerString,(Display *display))
SDL_X11_SYM(XrmDatabase,XrmGetStringDatabase,(ਅੱਖਰ *ਅੰਕੜੇ))
SDL_X11_SYM(ਖਾਲੀ,XrmDestroyDatabase,(XrmDatabase db))
SDL_X11_SYM(Bool,XrmGetResource,(XrmDatabase db, ਅੱਖਰ* str_name, ਅੱਖਰ* str_class, ਅੱਖਰ **str_type_return, Xrm_ਮੁੱਲ *))
SDL_X11_SYM(ਪੂਰਨ,XGet_ਸੂਚਕ_Mapping,(Display *a, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *b, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ c))

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XFIXES
SDL_X11_MODULE(XFIXES)
SDL_X11_SYM(ਸੂਚਕ_Barrier, XFixes_Create_ਸੂਚਕ_Barrier, (Display* a, ਖਿੜਕੀ_2 b, ਪੂਰਨ c, ਪੂਰਨ d, ਪੂਰਨ e, ਪੂਰਨ f, ਪੂਰਨ g, ਪੂਰਨ h, ਪੂਰਨ *i))
SDL_X11_SYM(ਖਾਲੀ, XFixes_Destroy_ਸੂਚਕ_Barrier, (Display* a, ਸੂਚਕ_Barrier b))
SDL_X11_SYM(ਪੂਰਨ, XIBarrier_Release_ਸੂਚਕ,(Display* a,  ਪੂਰਨ b, ਸੂਚਕ_Barrier c, BarrierEventID d)) // this is actually Xinput2
SDL_X11_SYM(ਸਥਿਤੀ_2, XFixes_Query_ਸੰਸਕਰਣ,(Display* a, ਪੂਰਨ* b, ਪੂਰਨ* c))
SDL_X11_SYM(ਸਥਿਤੀ_2, XFixes_Select_Selection_ਨਿਵੇਸ਼, (Display* a, ਖਿੜਕੀ_2 b, Atom c, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ d))
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XSYNC
SDL_X11_MODULE(XSYNC)
SDL_X11_SYM(ਸਥਿਤੀ_2, XSyncQueryExtension, (Display* a, ਪੂਰਨ* b, ਪੂਰਨ* c))
SDL_X11_SYM(ਸਥਿਤੀ_2, XSyncInitialize, (Display* a, ਪੂਰਨ* b, ਪੂਰਨ* c))
SDL_X11_SYM(XSyncCounter, XSyncCreateCounter, (Display* a, XSync_ਮੁੱਲ b))
SDL_X11_SYM(ਸਥਿਤੀ_2, XSyncDestroyCounter, (Display* a, XSyncCounter b))
SDL_X11_SYM(ਸਥਿਤੀ_2, XSync_ਸੈੱਟ_Counter, (Display* a, XSyncCounter b, XSync_ਮੁੱਲ c))
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XTEST
SDL_X11_MODULE(XTEST)
SDL_X11_SYM(ਸਥਿਤੀ_2, XTestQueryExtension, (Display* a, ਪੂਰਨ* b, ਪੂਰਨ* c))
SDL_X11_SYM(ਪੂਰਨ, XTestFakeMotionEvent, (Display* a, ਪੂਰਨ b, ਪੂਰਨ c, ਪੂਰਨ d, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ e))
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
SDL_X11_SYM(Bool,XGet_Event_ਅੰਕੜੇ,(Display* a,XGenericEventCookie* b))
SDL_X11_SYM(ਖਾਲੀ,XFree_Event_ਅੰਕੜੇ,(Display* a,XGenericEventCookie* b))
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
SDL_X11_SYM(Bool,XkbQueryExtension,(Display* a,ਪੂਰਨ * b,ਪੂਰਨ * c,ਪੂਰਨ * d,ਪੂਰਨ * e, ਪੂਰਨ *f))
SDL_X11_SYM(ਕੁੰਜੀ_Sym,Xkb_Keycode_ਮੰਜ਼ਿਲ_Keysym,(Display* a, ਕੁੰਜੀ_ਕੋਡ_2 b, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ c, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ d))
SDL_X11_SYM(Bool,XkbSelectEvents,(Display* a, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ b, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ c, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ d))
SDL_X11_SYM(Bool,XkbSelectEventDetails,(Display* a, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ b, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ c, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ d, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ e))
SDL_X11_SYM(ਸਥਿਤੀ_2,Xkb_Get_ਨਾਂ,(Display *a, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ b, XkbDescPtr c))
SDL_X11_SYM(ਸਥਿਤੀ_2,XkbGetState,(Display* a,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ b,XkbStatePtr c))
SDL_X11_SYM(ਸਥਿਤੀ_2,XkbGetUpdatedMap,(Display* a,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ b,XkbDescPtr c))
SDL_X11_SYM(XkbDescPtr,XkbGetMap,(Display* a,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ b,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ c))
SDL_X11_SYM(ਖਾਲੀ,XkbFreeClientMap,(XkbDescPtr a,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ b, Bool c))
SDL_X11_SYM(ਖਾਲੀ,XkbFreeKeyboard,(XkbDescPtr a,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ b, Bool c))
SDL_X11_SYM(ਸਥਿਤੀ_2,XkbRefreshKeyboardMapping,(XkbMapNotifyEvent *a))
SDL_X11_SYM(Bool,Xkb_ਸੈੱਟ_Detectable_Auto_Repeat,(Display* a, Bool b, Bool* c))
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
SDL_X11_MODULE(UTF8)
SDL_X11_SYM(ਪੂਰਨ,Xutf8_ਪਾਠ_List_ਮੰਜ਼ਿਲ_ਪਾਠ_Property,(Display* a,ਅੱਖਰ** b,ਪੂਰਨ c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(ਪੂਰਨ,Xutf8LookupString,(XIC a,XKeyPressedEvent* b,ਅੱਖਰ* c,ਪੂਰਨ d,ਕੁੰਜੀ_Sym* e,ਸਥਿਤੀ_2* f))
SDL_X11_SYM(XIC,XCreateIC,(XIM,...))
SDL_X11_SYM(ਖਾਲੀ,XDestroyIC,(XIC a))
SDL_X11_SYM(ਅੱਖਰ*,XGetICValues,(XIC,...))
SDL_X11_SYM(ਅੱਖਰ*,XSetICValues,(XIC,...))
SDL_X11_SYM(XVaNestedList,XVaCreateNestedList,(ਪੂਰਨ, ...))
SDL_X11_SYM(ਖਾਲੀ,XSetICFocus,(XIC a))
SDL_X11_SYM(ਖਾਲੀ,XUnsetICFocus,(XIC a))
SDL_X11_SYM(XIM,XOpenIM,(Display* a,ਬਣਤਰ Xrm_Hash_ਬਾਲਟੀ_Rec* b,ਅੱਖਰ* c,ਅੱਖਰ* d))
SDL_X11_SYM(ਸਥਿਤੀ_2,XCloseIM,(XIM a))
SDL_X11_SYM(ਅੱਖਰ*, XSetIMValues,(XIM,...))
SDL_X11_SYM(Bool,XRegisterIMInstantiateCallback,(Display*,ਬਣਤਰ Xrm_Hash_ਬਾਲਟੀ_Rec*,ਅੱਖਰ*,ਅੱਖਰ*,XIDProc,XPointer))
SDL_X11_SYM(Bool,XUnregisterIMInstantiateCallback,(Display*,ਬਣਤਰ Xrm_Hash_ਬਾਲਟੀ_Rec*,ਅੱਖਰ*,ਅੱਖਰ*,XIDProc,XPointer))
SDL_X11_SYM(ਖਾਲੀ,Xutf8DrawString,(Display *a, Drawable b, XFont_ਸੈੱਟ c, GC d, ਪੂਰਨ e, ਪੂਰਨ f, _Xconst ਅੱਖਰ *g, ਪੂਰਨ h))
SDL_X11_SYM(ਪੂਰਨ,Xutf8_ਪਾਠ_Extents,(XFont_ਸੈੱਟ a, _Xconst ਅੱਖਰ* b, ਪੂਰਨ c, XRectangle* d, XRectangle* e))
SDL_X11_SYM(ਅੱਖਰ*,XSetLocaleModifiers,(ਅਚਲ ਅੱਖਰ *a))
SDL_X11_SYM(ਅੱਖਰ*,Xutf8ResetIC,(XIC a))
SDL_X11_SYM(XFont_ਸੈੱਟ_Extents*,XExtents_ਦਾ_Font_ਸੈੱਟ,(XFont_ਸੈੱਟ a))
SDL_X11_SYM(Bool,XContextDependentDrawing,(XFont_ਸੈੱਟ a))
#ਜੇ_ਅੰਤ


#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NO_SHARED_ਸਮ੍ਰਿਤੀ
SDL_X11_MODULE(SHM)
SDL_X11_SYM(ਸਥਿਤੀ_2,XShmAttach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(ਸਥਿਤੀ_2,XShmDetach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(ਸਥਿਤੀ_2,XShmPutImage,(Display* a,Drawable b,GC c,XImage* d,ਪੂਰਨ e,ਪੂਰਨ f,ਪੂਰਨ g,ਪੂਰਨ h,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ j,Bool k))
SDL_X11_SYM(ਸਥਿਤੀ_2,XShmGetImage,(Display* a,Drawable b,XImage *c,ਪੂਰਨ d, ਪੂਰਨ e, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ f))
SDL_X11_SYM(XImage*,XShmCreateImage,(Display* a,Visual* b,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ c,ਪੂਰਨ d,ਅੱਖਰ* e,XShmSegmentInfo* f,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ g,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ h))
SDL_X11_SYM(Pixmap,XShmCreatePixmap,(Display *a,Drawable b,ਅੱਖਰ* c,XShmSegmentInfo* d, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ e, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ f, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ g))
SDL_X11_SYM(Bool,XShmQueryExtension,(Display* a))
SDL_X11_SYM(ਸਥਿਤੀ_2,XShm_Query_ਸੰਸਕਰਣ,(Display* a, ਪੂਰਨ *b, ਪੂਰਨ *c, Bool *d))
SDL_X11_SYM(ਪੂਰਨ,XShmPixmapFormat,(Display* a))
#ਜੇ_ਅੰਤ

/*
 * Not required...these only exist in code in headers on some 64-bit platforms,
 *  and are removed via macros elsewhere, so it's safe for them to be missing.
 */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ LONG64
SDL_X11_MODULE(IO_32_ਦੋਆਧਾਰੀ_ਅੰਕ)
SDL_X11_SYM(ਪੂਰਨ,_XData32,(Display *dpy,ਰਜਿਸਟਰ _Xconst ਲੰਮਾ *ਅੰਕੜੇ,ਬਿਨਾਨਿਸ਼ਾਨੀ len))
SDL_X11_SYM(ਖਾਲੀ,_XRead32,(Display *dpy,ਰਜਿਸਟਰ ਲੰਮਾ *ਅੰਕੜੇ,ਲੰਮਾ len))
#ਜੇ_ਅੰਤ

/*
 * These only show up on some variants of Unix.
 */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_OSF
SDL_X11_MODULE(OSF_ਇੰਦਰਾਜ_POINTS)
SDL_X11_SYM(ਖਾਲੀ,Smt_ਬਫਰ_ਉਛਾਲ,(Display *dpy,ਰਜਿਸਟਰ smtDisplayPtr p))
SDL_X11_SYM(ਖਾਲੀ,_SmtIpError,(Display *dpy,ਰਜਿਸਟਰ smtDisplayPtr p,ਪੂਰਨ i))
SDL_X11_SYM(ਪੂਰਨ,ip_Allocate_ਅੰਕੜੇ,(ChannelPtr a,IPCard b,IPDataPtr * c))
SDL_X11_SYM(ਪੂਰਨ,ip_Unallocate_And_Send_ਅੰਕੜੇ,(ChannelPtr a,IPCard b))
#ਜੇ_ਅੰਤ

// XCursor support
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XCURSOR
SDL_X11_MODULE(XCURSOR)
SDL_X11_SYM(XcursorImage*,XcursorImageCreate,(ਪੂਰਨ a,ਪੂਰਨ b))
SDL_X11_SYM(XcursorImages*,XcursorImagesCreate,(ਪੂਰਨ a))
SDL_X11_SYM(ਖਾਲੀ,XcursorImageDestroy,(XcursorImage *a))
SDL_X11_SYM(ਖਾਲੀ,XcursorImagesDestroy,(XcursorImages *a))
SDL_X11_SYM(Cursor,Xcursor_Image_ਲੱਦੋ_Cursor,(Display *a,ਅਚਲ XcursorImage *b))
SDL_X11_SYM(Cursor,Xcursor_Images_ਲੱਦੋ_Cursor,(Display *a,ਅਚਲ XcursorImages *b))
SDL_X11_SYM(Cursor,Xcursor_Library_ਲੱਦੋ_Cursor,(Display *a, ਅਚਲ ਅੱਖਰ *b))
#ਜੇ_ਅੰਤ

// Xdbe support
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XDBE
SDL_X11_MODULE(XDBE)
SDL_X11_SYM(ਸਥਿਤੀ_2,XdbeQueryExtension,(Display *dpy,ਪੂਰਨ *major_ਸੰਸਕਰਣ_return,ਪੂਰਨ *minor_ਸੰਸਕਰਣ_return))
SDL_X11_SYM(Xdbe_ਪਿੱਠ_ਬਫਰ,Xdbe_Allocate_ਪਿੱਠ_ਬਫਰ_Name,(Display *dpy,ਖਿੜਕੀ_2 ਖਿੜਕੀ,Xdbe_ਅਦਲਾ_ਬਦਲੀ_Action ਅਦਲਾ_ਬਦਲੀ_action))
SDL_X11_SYM(ਸਥਿਤੀ_2,Xdbe_Deallocate_ਪਿੱਠ_ਬਫਰ_Name,(Display *dpy,Xdbe_ਪਿੱਠ_ਬਫਰ ਬਫਰ_2))
SDL_X11_SYM(ਸਥਿਤੀ_2,Xdbe_ਅਦਲਾ_ਬਦਲੀ_Buffers,(Display *dpy,Xdbe_ਅਦਲਾ_ਬਦਲੀ_Info *ਅਦਲਾ_ਬਦਲੀ_info,ਪੂਰਨ ਅੰਕ_windows))
SDL_X11_SYM(ਸਥਿਤੀ_2,XdbeBeginIdiom,(Display *dpy))
SDL_X11_SYM(ਸਥਿਤੀ_2,Xdbe_ਸਿਰਾ_Idiom,(Display *dpy))
SDL_X11_SYM(XdbeScreenVisualInfo*,XdbeGetVisualInfo,(Display *dpy,Drawable *screen_specifiers,ਪੂਰਨ *ਅੰਕ_screens))
SDL_X11_SYM(ਖਾਲੀ,XdbeFreeVisualInfo,(XdbeScreenVisualInfo *visual_info))
SDL_X11_SYM(Xdbe_ਪਿੱਠ_ਬਫਰ_ਗੁਣ*,Xdbe_Get_ਪਿੱਠ_ਬਫਰ_ਗੁਣ,(Display *dpy,Xdbe_ਪਿੱਠ_ਬਫਰ ਬਫਰ_2))
#ਜੇ_ਅੰਤ

// XInput2 support for multiple mice, tablets, etc.
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2
SDL_X11_MODULE(XINPUT2)
SDL_X11_SYM(XIDeviceInfo*,XIQueryDevice,(Display *a,ਪੂਰਨ b,ਪੂਰਨ *c))
SDL_X11_SYM(ਖਾਲੀ,XIFreeDeviceInfo,(XIDeviceInfo *a))
SDL_X11_SYM(ਪੂਰਨ,XISelectEvents,(Display *a,ਖਿੜਕੀ_2 b,XIEvent_ਨਕਾਬ *c,ਪੂਰਨ d))
SDL_X11_SYM(ਪੂਰਨ,XIGrabTouchBegin,(Display *a,ਪੂਰਨ b,ਖਿੜਕੀ_2 c,ਪੂਰਨ d,XIEvent_ਨਕਾਬ *e,ਪੂਰਨ f,XIGrabModifiers *g))
SDL_X11_SYM(ਪੂਰਨ,XIUngrabTouchBegin, (Display *a,ਪੂਰਨ b,ਖਿੜਕੀ_2 c, ਪੂਰਨ d,XIGrabModifiers *e))
SDL_X11_SYM(ਸਥਿਤੀ_2,XIQuery_ਸੰਸਕਰਣ,(Display *a,ਪੂਰਨ *b,ਪੂਰਨ *c))
SDL_X11_SYM(XIEvent_ਨਕਾਬ*,XIGetSelectedEvents,(Display *a,ਖਿੜਕੀ_2 b,ਪੂਰਨ *c))
SDL_X11_SYM(Bool,XIGet_Client_ਸੂਚਕ,(Display *a,ਖਿੜਕੀ_2 b,ਪੂਰਨ *c))
SDL_X11_SYM(Bool,XIWarp_ਸੂਚਕ,(Display *a,ਪੂਰਨ b,ਖਿੜਕੀ_2 c,ਖਿੜਕੀ_2 d,ਦੁੱਗਣਾ e,ਦੁੱਗਣਾ f,ਪੂਰਨ g,ਪੂਰਨ h,ਦੁੱਗਣਾ i,ਦੁੱਗਣਾ j))
SDL_X11_SYM(ਸਥਿਤੀ_2,XIGetProperty,(Display *a,ਪੂਰਨ b,Atom c,ਲੰਮਾ d,ਲੰਮਾ e,Bool f, Atom g, Atom *h, ਪੂਰਨ *i, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ *j, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ *k, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ **l))
#ਜੇ_ਅੰਤ

// XRandR support
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XRANDR
SDL_X11_MODULE(XRANDR)
SDL_X11_SYM(ਸਥਿਤੀ_2,XRRQuery_ਸੰਸਕਰਣ,(Display *dpy,ਪੂਰਨ *major_versionp,ਪੂਰਨ *minor_versionp))
SDL_X11_SYM(Bool,XRRQueryExtension,(Display *dpy,ਪੂਰਨ *event_ਅਧਾਰ_return,ਪੂਰਨ *error_ਅਧਾਰ_return))
SDL_X11_SYM(XRRScreenConfiguration *,XRRGetScreenInfo,(Display *dpy,Drawable draw))
SDL_X11_SYM(ਮਾਪ_ID,XRRConfigCurrentConfiguration,(XRRScreenConfiguration *config,Rotation *rotation))
SDL_X11_SYM(ਛੋਟਾ,XRRConfig_Current_ਦਰ,(XRRScreenConfiguration *config))
SDL_X11_SYM(ਛੋਟਾ *,XRRConfigRates,(XRRScreenConfiguration *config,ਪੂਰਨ ਮਾਪ_ID_2,ਪੂਰਨ *nrates))
SDL_X11_SYM(XRRScreen_ਮਾਪ *,XRRConfigSizes,(XRRScreenConfiguration *config,ਪੂਰਨ *nsizes))
SDL_X11_SYM(ਸਥਿਤੀ_2,XRRSet_Screen_Config_And_ਦਰ,(Display *dpy,XRRScreenConfiguration *config,Drawable draw,ਪੂਰਨ ਮਾਪ_ਸੂਚਕਾਂਕ,Rotation rotation,ਛੋਟਾ ਦਰ,ਸਮਾਂ_2 timestamp))
SDL_X11_SYM(ਖਾਲੀ,XRRFreeScreenConfigInfo,(XRRScreenConfiguration *config))
SDL_X11_SYM(ਖਾਲੀ,XRRSet_Screen_ਮਾਪ,(Display *dpy, ਖਿੜਕੀ_2 ਖਿੜਕੀ,ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ,ਪੂਰਨ mm_ਚੌੜਾਈ_2, ਪੂਰਨ mm_ਉਚਾਈ_2))
SDL_X11_SYM(ਸਥਿਤੀ_2,XRRGet_Screen_ਮਾਪ_Range,(Display *dpy, ਖਿੜਕੀ_2 ਖਿੜਕੀ,ਪੂਰਨ *min_ਚੌੜਾਈ, ਪੂਰਨ *min_ਉਚਾਈ, ਪੂਰਨ *max_ਚੌੜਾਈ, ਪੂਰਨ *max_ਉਚਾਈ))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResources,(Display *dpy, ਖਿੜਕੀ_2 ਖਿੜਕੀ))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResourcesCurrent,(Display *dpy, ਖਿੜਕੀ_2 ਖਿੜਕੀ))
SDL_X11_SYM(ਖਾਲੀ,XRRFreeScreenResources,(XRRScreenResources *resources))
SDL_X11_SYM(XRROutputInfo *,XRRGetOutputInfo,(Display *dpy, XRRScreenResources *resources, RROutput output))
SDL_X11_SYM(ਖਾਲੀ,XRRFreeOutputInfo,(XRROutputInfo *outputInfo))
SDL_X11_SYM(XRRCrtcInfo *,XRRGetCrtcInfo,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc))
SDL_X11_SYM(ਖਾਲੀ,XRRFreeCrtcInfo,(XRRCrtcInfo *crtcInfo))
SDL_X11_SYM(ਸਥਿਤੀ_2,XRRSetCrtcConfig,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc, ਸਮਾਂ_2 timestamp, ਪੂਰਨ x, ਪੂਰਨ y, RRMode ਬਹੁਲਕ, Rotation rotation, RROutput *outputs, ਪੂਰਨ noutputs))
SDL_X11_SYM(Atom*,XRRListOutputProperties,(Display *dpy, RROutput output, ਪੂਰਨ *nprop))
SDL_X11_SYM(XRRPropertyInfo*,XRRQueryOutputProperty,(Display *dpy,RROutput output, Atom property))
SDL_X11_SYM(ਪੂਰਨ,XRRGetOutputProperty,(Display *dpy,RROutput output, Atom property, ਲੰਮਾ ਵਿੱਥ_2, ਲੰਮਾ ਲੰਮਾਈ, Bool _delete, Bool pending, Atom req_type, Atom *actual_type, ਪੂਰਨ *actual_format, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ *nitems, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ *ਬਾਈਟਾਂ_after, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ **prop))
SDL_X11_SYM(RROutput,XRRGetOutputPrimary,(Display *dpy,ਖਿੜਕੀ_2 ਖਿੜਕੀ))
SDL_X11_SYM(ਖਾਲੀ,XRRSelect_ਨਿਵੇਸ਼,(Display *dpy, ਖਿੜਕੀ_2 ਖਿੜਕੀ, ਪੂਰਨ ਨਕਾਬ))
SDL_X11_SYM(ਸਥਿਤੀ_2,XRRGetCrtcTransform,(Display *dpy,RRCrtc crtc,XRRCrtc_Transform_ਗੁਣ **ਗੁਣ))
#ਜੇ_ਅੰਤ

// MIT-SCREEN-SAVER support
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XSCRNSAVER
SDL_X11_MODULE(XSS)
SDL_X11_SYM(Bool,XScreenSaverQueryExtension,(Display *dpy,ਪੂਰਨ *event_ਅਧਾਰ_2,ਪੂਰਨ *error_ਅਧਾਰ_2))
SDL_X11_SYM(ਸਥਿਤੀ_2,XScreen_Saver_Query_ਸੰਸਕਰਣ,(Display *dpy,ਪੂਰਨ *major_versionp,ਪੂਰਨ *minor_versionp))
SDL_X11_SYM(ਖਾਲੀ,XScreenSaverSuspend,(Display *dpy,Bool suspend))
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XSHAPE
SDL_X11_MODULE(XSHAPE)
SDL_X11_SYM(ਖਾਲੀ,XShape_Combine_ਨਕਾਬ,(Display *dpy,ਖਿੜਕੀ_2 dest,ਪੂਰਨ dest_ਕਿਸਮ,ਪੂਰਨ x_off,ਪੂਰਨ y_off,Pixmap src,ਪੂਰਨ op))
SDL_X11_SYM(ਖਾਲੀ,XShapeCombineRegion,(Display *a,ਖਿੜਕੀ_2 b,ਪੂਰਨ c,ਪੂਰਨ d,ਪੂਰਨ e,Region f,ਪੂਰਨ g))
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ SDL_X11_MODULE
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ SDL_X11_SYM

/* *INDENT-ON* */ // clang-format on
