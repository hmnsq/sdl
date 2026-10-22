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

#ifndef SDL_X11_MODULE
#define SDL_X11_MODULE(modname)
#endif

#ifndef SDL_X11_SYM
#define SDL_X11_SYM(rc, fn, params)
#endif

SDL_X11_MODULE(BASEXLIB)
SDL_X11_SYM(XSizeHints*,XAllocSizeHints,(ಶೂನ್ಯ))
SDL_X11_SYM(XWMHints*,XAllocWMHints,(ಶೂನ್ಯ))
SDL_X11_SYM(XClassHint*,XAllocClassHint,(ಶೂನ್ಯ))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XChangePointerControl,(Display* a,Bool b,Bool c,ಪೂರ್ಣಾಙ್ಕ d,ಪೂರ್ಣಾಙ್ಕ e,ಪೂರ್ಣಾಙ್ಕ f))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XChangeProperty,(Display* a,Window b,Atom c,Atom d,ಪೂರ್ಣಾಙ್ಕ e,ಪೂರ್ಣಾಙ್ಕ f,_Xconst unsigned ವರ್ಣ* g,ಪೂರ್ಣಾಙ್ಕ h))
SDL_X11_SYM(Bool,XCheckIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XClearWindow,(Display* a,Window b))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XCloseDisplay,(Display* a))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XConvertSelection,(Display* a,Atom b,Atom c,Atom d,Window e,Time f))
SDL_X11_SYM(Pixmap,XCreateBitmapFromData,(Display *dpy,Drawable d,_Xconst ವರ್ಣ *data,unsigned ಪೂರ್ಣಾಙ್ಕ width,unsigned ಪೂರ್ಣಾಙ್ಕ height))
SDL_X11_SYM(Colormap,XCreateColormap,(Display* a,Window b,Visual* c,ಪೂರ್ಣಾಙ್ಕ d))
SDL_X11_SYM(Cursor,XCreatePixmapCursor,(Display* a,Pixmap b,Pixmap c,XColor* d,XColor* e,unsigned ಪೂರ್ಣಾಙ್ಕ f,unsigned ಪೂರ್ಣಾಙ್ಕ g))
SDL_X11_SYM(Cursor,XCreatePixmap,(Display* a,Drawable b,unsigned ಪೂರ್ಣಾಙ್ಕ d,unsigned ಪೂರ್ಣಾಙ್ಕ e,unsigned ಪೂರ್ಣಾಙ್ಕ f))
SDL_X11_SYM(Cursor,XCreateFontCursor,(Display* a,unsigned ಪೂರ್ಣಾಙ್ಕ b))
SDL_X11_SYM(XFontSet,XCreateFontSet,(Display* a, _Xconst ವರ್ಣ* b, ವರ್ಣ*** c, ಪೂರ್ಣಾಙ್ಕ* d, ವರ್ಣ** e))
SDL_X11_SYM(GC,XCreateGC,(Display* a,Drawable b,unsigned long c,XGCValues* d))
SDL_X11_SYM(ಶೂನ್ಯ,XSetFont,(Display* a,GC b,Font c))
SDL_X11_SYM(Status,XAllocColor,(Display *a, Colormap b, XColor *c))
SDL_X11_SYM(XImage*,XCreateImage,(Display* a,Visual* b,unsigned ಪೂರ್ಣಾಙ್ಕ c,ಪೂರ್ಣಾಙ್ಕ d,ಪೂರ್ಣಾಙ್ಕ e,ವರ್ಣ* f,unsigned ಪೂರ್ಣಾಙ್ಕ g,unsigned ಪೂರ್ಣಾಙ್ಕ h,ಪೂರ್ಣಾಙ್ಕ i,ಪೂರ್ಣಾಙ್ಕ j))
SDL_X11_SYM(Window,XCreateWindow,(Display* a,Window b,ಪೂರ್ಣಾಙ್ಕ c,ಪೂರ್ಣಾಙ್ಕ d,unsigned ಪೂರ್ಣಾಙ್ಕ e,unsigned ಪೂರ್ಣಾಙ್ಕ f,unsigned ಪೂರ್ಣಾಙ್ಕ g,ಪೂರ್ಣಾಙ್ಕ h,unsigned ಪೂರ್ಣಾಙ್ಕ i,Visual* j,unsigned long k,XSetWindowAttributes* l))
SDL_X11_SYM(ಶೂನ್ಯ,XCopyArea,(Display *a, Drawable b, Drawable c, GC d, ಪೂರ್ಣಾಙ್ಕ e, ಪೂರ್ಣಾಙ್ಕ f, unsigned ಪೂರ್ಣಾಙ್ಕ g, unsigned ಪೂರ್ಣಾಙ್ಕ h, ಪೂರ್ಣಾಙ್ಕ i, ಪೂರ್ಣಾಙ್ಕ j))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XDefineCursor,(Display* a,Window b,Cursor c))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XDeleteProperty,(Display* a,Window b,Atom c))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XDestroyWindow,(Display* a,Window b))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XDisplayKeycodes,(Display* a,ಪೂರ್ಣಾಙ್ಕ* b,ಪೂರ್ಣಾಙ್ಕ* c))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XDrawRectangle,(Display* a,Drawable b,GC c,ಪೂರ್ಣಾಙ್ಕ d,ಪೂರ್ಣಾಙ್ಕ e,unsigned ಪೂರ್ಣಾಙ್ಕ f,unsigned ಪೂರ್ಣಾಙ್ಕ g))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XFontsOfFontSet,(XFontSet a,XFontStruct ***b,ವರ್ಣ ***c))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XFillArc,(Display* a,Drawable b,GC c,ಪೂರ್ಣಾಙ್ಕ d,ಪೂರ್ಣಾಙ್ಕ e,unsigned ಪೂರ್ಣಾಙ್ಕ f,unsigned ಪೂರ್ಣಾಙ್ಕ g, ಪೂರ್ಣಾಙ್ಕ h, ಪೂರ್ಣಾಙ್ಕ i))
SDL_X11_SYM(ವರ್ಣ*,XDisplayName,(_Xconst ವರ್ಣ* a))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XDrawString,(Display* a,Drawable b,GC c,ಪೂರ್ಣಾಙ್ಕ d,ಪೂರ್ಣಾಙ್ಕ e,_Xconst ವರ್ಣ* f,ಪೂರ್ಣಾಙ್ಕ g))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XEventsQueued,(Display* a,ಪೂರ್ಣಾಙ್ಕ b))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XFillRectangle,(Display* a,Drawable b,GC c,ಪೂರ್ಣಾಙ್ಕ d,ಪೂರ್ಣಾಙ್ಕ e,unsigned ಪೂರ್ಣಾಙ್ಕ f,unsigned ಪೂರ್ಣಾಙ್ಕ g))
SDL_X11_SYM(Bool,XFilterEvent,(XEvent *event,Window w))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XFlush,(Display* a))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XFree,(ಶೂನ್ಯ*a))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XFreeCursor,(Display* a,Cursor b))
SDL_X11_SYM(ಶೂನ್ಯ,XFreeFontSet,(Display* a, XFontSet b))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XFreeGC,(Display* a,GC b))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XFreeFont,(Display* a, XFontStruct* b))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XFreeModifiermap,(XModifierKeymap* a))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XFreePixmap,(Display* a,Pixmap b))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XFreeColormap,(Display* a,Colormap b))
SDL_X11_SYM(ಶೂನ್ಯ,XFreeStringList,(ವರ್ಣ** a))
SDL_X11_SYM(ವರ್ಣ*,XGetAtomName,(Display *a,Atom b))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XGet_ಒಳಹರಿವು_Focus,(Display *a,Window *b,ಪೂರ್ಣಾಙ್ಕ *c))
SDL_X11_SYM(ಕೀಲಿ_Sym*,XGetKeyboardMapping,(Display *a, ಕೀಲಿ_Code_2 b, ಪೂರ್ಣಾಙ್ಕ c, ಪೂರ್ಣಾಙ್ಕ *d))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XGetErrorDatabaseText,(Display* a,_Xconst ವರ್ಣ* b,_Xconst ವರ್ಣ* c,_Xconst ವರ್ಣ* d,ವರ್ಣ* e,ಪೂರ್ಣಾಙ್ಕ f))
SDL_X11_SYM(XModifierKeymap*,XGetModifierMapping,(Display* a))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XGetPointerControl,(Display* a,ಪೂರ್ಣಾಙ್ಕ* b,ಪೂರ್ಣಾಙ್ಕ* c,ಪೂರ್ಣಾಙ್ಕ* d))
SDL_X11_SYM(Window,XGetSelectionOwner,(Display* a,Atom b))
SDL_X11_SYM(XVisualInfo*,XGetVisualInfo,(Display* a,long b,XVisualInfo* c,ಪೂರ್ಣಾಙ್ಕ* d))
SDL_X11_SYM(Status,XGetWindowAttributes,(Display* a,Window b,XWindowAttributes* c))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XGetWindowProperty,(Display* a,Window b,Atom c,long d,long e,Bool f,Atom g,Atom* h,ಪೂರ್ಣಾಙ್ಕ* i,unsigned long* j,unsigned long *k,unsigned ವರ್ಣ **l))
SDL_X11_SYM(XWMHints*,XGetWMHints,(Display* a,Window b))
SDL_X11_SYM(Status,XGetWMNormalHints,(Display *a,Window b, XSizeHints *c, long *d))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XGrabKeyboard,(Display* a,Window b,Bool c,ಪೂರ್ಣಾಙ್ಕ d,ಪೂರ್ಣಾಙ್ಕ e,Time f))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XGrabPointer,(Display* a,Window b,Bool c,unsigned ಪೂರ್ಣಾಙ್ಕ d,ಪೂರ್ಣಾಙ್ಕ e,ಪೂರ್ಣಾಙ್ಕ f,Window g,Cursor h,Time i))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XGrabServer,(Display* a))
SDL_X11_SYM(Status,XIconifyWindow,(Display* a,Window b,ಪೂರ್ಣಾಙ್ಕ c))
SDL_X11_SYM(ಕೀಲಿ_Code_2,XKeysymToKeycode,(Display* a,ಕೀಲಿ_Sym b))
SDL_X11_SYM(ವರ್ಣ*,XKeysymToString,(ಕೀಲಿ_Sym a))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XInstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(Atom,XInternAtom,(Display* a,_Xconst ವರ್ಣ* b,Bool c))
SDL_X11_SYM(XPixmap_Format_ಮೌಲ್ಯಗಳು*,XListPixmapFormats,(Display* a,ಪೂರ್ಣಾಙ್ಕ* b))
SDL_X11_SYM(XFontStruct*,XLoadQueryFont,(Display* a,_Xconst ವರ್ಣ* b))
SDL_X11_SYM(ಕೀಲಿ_Sym,XLookupKeysym,(XKeyEvent* a,ಪೂರ್ಣಾಙ್ಕ b))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XLookupString,(XKeyEvent* a,ವರ್ಣ* b,ಪೂರ್ಣಾಙ್ಕ c,ಕೀಲಿ_Sym* d,XComposeStatus* e))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XMapRaised,(Display* a,Window b))
SDL_X11_SYM(Status,XMatchVisualInfo,(Display* a,ಪೂರ್ಣಾಙ್ಕ b,ಪೂರ್ಣಾಙ್ಕ c,ಪೂರ್ಣಾಙ್ಕ d,XVisualInfo* e))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XMissingExtension,(Display* a,_Xconst ವರ್ಣ* b))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XMoveWindow,(Display* a,Window b,ಪೂರ್ಣಾಙ್ಕ c,ಪೂರ್ಣಾಙ್ಕ d))
SDL_X11_SYM(Display*,XOpenDisplay,(_Xconst ವರ್ಣ* a))
SDL_X11_SYM(Status,XInitThreads,(ಶೂನ್ಯ))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XPeekEvent,(Display* a,XEvent* b))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XPending,(Display* a))
SDL_X11_SYM(XImage*,XGetImage,(Display* a,Drawable b,ಪೂರ್ಣಾಙ್ಕ c, ಪೂರ್ಣಾಙ್ಕ d,unsigned ಪೂರ್ಣಾಙ್ಕ e,unsigned ಪೂರ್ಣಾಙ್ಕ f,unsigned long g,ಪೂರ್ಣಾಙ್ಕ h))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XPutImage,(Display* a,Drawable b,GC c,XImage* d,ಪೂರ್ಣಾಙ್ಕ e,ಪೂರ್ಣಾಙ್ಕ f,ಪೂರ್ಣಾಙ್ಕ g,ಪೂರ್ಣಾಙ್ಕ h,unsigned ಪೂರ್ಣಾಙ್ಕ i,unsigned ಪೂರ್ಣಾಙ್ಕ j))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XQueryKeymap,(Display* a,ವರ್ಣ b[32]))
SDL_X11_SYM(Bool,XQueryPointer,(Display* a,Window b,Window* c,Window* d,ಪೂರ್ಣಾಙ್ಕ* e,ಪೂರ್ಣಾಙ್ಕ* f,ಪೂರ್ಣಾಙ್ಕ* g,ಪೂರ್ಣಾಙ್ಕ* h,unsigned ಪೂರ್ಣಾಙ್ಕ* i))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XRaiseWindow,(Display* a,Window b))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XReparentWindow,(Display* a,Window b,Window c,ಪೂರ್ಣಾಙ್ಕ d,ಪೂರ್ಣಾಙ್ಕ e))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XResetScreenSaver,(Display* a))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XResizeWindow,(Display* a,Window b,unsigned ಪೂರ್ಣಾಙ್ಕ c,unsigned ಪೂರ್ಣಾಙ್ಕ d))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XScreen_ಸಂಖ್ಯೆ_Of_Screen,(Screen* a))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XSelect_ಒಳಹರಿವು,(Display* a,Window b,long c))
SDL_X11_SYM(Status,XSendEvent,(Display* a,Window b,Bool c,long d,XEvent* e))
SDL_X11_SYM(XErrorHandler,XSetErrorHandler,(XErrorHandler a))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XSetForeground,(Display* a,GC b,unsigned long c))
SDL_X11_SYM(XIOErrorHandler,XSetIOErrorHandler,(XIOErrorHandler a))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XSet_ಒಳಹರಿವು_Focus,(Display *a,Window b,ಪೂರ್ಣಾಙ್ಕ c,Time d))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XSetSelectionOwner,(Display* a,Atom b,Window c,Time d))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XSetTransientForHint,(Display* a,Window b,Window c))
SDL_X11_SYM(ಶೂನ್ಯ,XSetTextProperty,(Display* a,Window b,XTextProperty* c,Atom d))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XSetWindowBackground,(Display* a,Window b,unsigned long c))
SDL_X11_SYM(ಶೂನ್ಯ,XSetWMHints,(Display* a,Window b,XWMHints* c))
SDL_X11_SYM(ಶೂನ್ಯ,XSetWMNormalHints,(Display* a,Window b,XSizeHints* c))
SDL_X11_SYM(ಶೂನ್ಯ,XSetWMProperties,(Display* a,Window b,XTextProperty* c,XTextProperty* d,ವರ್ಣ** e,ಪೂರ್ಣಾಙ್ಕ f,XSizeHints* g,XWMHints* h,XClassHint* i))
SDL_X11_SYM(Status,XSetWMProtocols,(Display* a,Window b,Atom* c,ಪೂರ್ಣಾಙ್ಕ d))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XStoreColors,(Display* a,Colormap b,XColor* c,ಪೂರ್ಣಾಙ್ಕ d))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XStoreName,(Display* a,Window b,_Xconst ವರ್ಣ* c))
SDL_X11_SYM(Status,XStringListToTextProperty,(ವರ್ಣ** a,ಪೂರ್ಣಾಙ್ಕ b,XTextProperty* c))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XSync,(Display* a,Bool b))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XTextExtents,(XFontStruct* a,_Xconst ವರ್ಣ* b,ಪೂರ್ಣಾಙ್ಕ c,ಪೂರ್ಣಾಙ್ಕ* d,ಪೂರ್ಣಾಙ್ಕ* e,ಪೂರ್ಣಾಙ್ಕ* f,XCharStruct* g))
SDL_X11_SYM(Bool,XTranslateCoordinates,(Display *a,Window b,Window c,ಪೂರ್ಣಾಙ್ಕ d,ಪೂರ್ಣಾಙ್ಕ e,ಪೂರ್ಣಾಙ್ಕ* f,ಪೂರ್ಣಾಙ್ಕ* g,Window* h))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XUndefineCursor,(Display* a,Window b))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XUngrabKeyboard,(Display* a,Time b))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XUngrabPointer,(Display* a,Time b))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XUngrabServer,(Display* a))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XUninstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XUnloadFont,(Display* a,Font b))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XWarpPointer,(Display* a,Window b,Window c,ಪೂರ್ಣಾಙ್ಕ d,ಪೂರ್ಣಾಙ್ಕ e,unsigned ಪೂರ್ಣಾಙ್ಕ f,unsigned ಪೂರ್ಣಾಙ್ಕ g,ಪೂರ್ಣಾಙ್ಕ h,ಪೂರ್ಣಾಙ್ಕ i))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XWindowEvent,(Display* a,Window b,long c,XEvent* d))
SDL_X11_SYM(Status,XWithdrawWindow,(Display* a,Window b,ಪೂರ್ಣಾಙ್ಕ c))
SDL_X11_SYM(VisualID,XVisualIDFromVisual,(Visual* a))
SDL_X11_SYM(ವರ್ಣ*,XGetDefault,(Display* a,_Xconst ವರ್ಣ* b, _Xconst ವರ್ಣ* c))
SDL_X11_SYM(Bool,XQueryExtension,(Display* a,_Xconst ವರ್ಣ* b,ಪೂರ್ಣಾಙ್ಕ* c,ಪೂರ್ಣಾಙ್ಕ* d,ಪೂರ್ಣಾಙ್ಕ* e))
SDL_X11_SYM(ವರ್ಣ *,XDisplayString,(Display* a))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XGetErrorText,(Display* a,ಪೂರ್ಣಾಙ್ಕ b,ವರ್ಣ* c,ಪೂರ್ಣಾಙ್ಕ d))
SDL_X11_SYM(ಶೂನ್ಯ,_XEatData,(Display* a,unsigned long b))
SDL_X11_SYM(ಶೂನ್ಯ,_XFlush,(Display* a))
SDL_X11_SYM(ಶೂನ್ಯ,_XFlushGCCache,(Display* a,GC b))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,_XRead,(Display* a,ವರ್ಣ* b,long c))
SDL_X11_SYM(ಶೂನ್ಯ,_XReadPad,(Display* a,ವರ್ಣ* b,long c))
SDL_X11_SYM(ಶೂನ್ಯ,_XSend,(Display* a,_Xconst ವರ್ಣ* b,long c))
SDL_X11_SYM(Status,_XReply,(Display* a,xReply* b,ಪೂರ್ಣಾಙ್ಕ c,Bool d))
SDL_X11_SYM(unsigned long,_XSetLastRequestRead,(Display* a,xGenericReply* b))
SDL_X11_SYM(SDL_X11_XSynchronizeRetType,XSynchronize,(Display* a,Bool b))
SDL_X11_SYM(SDL_X11_XESetWireToEventRetType,XESetWireToEvent,(Display* a,ಪೂರ್ಣಾಙ್ಕ b,SDL_X11_XESetWireToEventRetType c))
SDL_X11_SYM(SDL_X11_XESetEventToWireRetType,XESetEventToWire,(Display* a,ಪೂರ್ಣಾಙ್ಕ b,SDL_X11_XESetEventToWireRetType c))
SDL_X11_SYM(ಶೂನ್ಯ,XRefreshKeyboardMapping,(XMappingEvent *a))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XQuery_ವೃಕ್ಷ,(Display* a,Window b,Window* c,Window* d,Window** e,unsigned ಪೂರ್ಣಾಙ್ಕ* f))
SDL_X11_SYM(Bool,XSupportsLocale,(ಶೂನ್ಯ))
SDL_X11_SYM(Status,XmbTextListToTextProperty,(Display* a,ವರ್ಣ** b,ಪೂರ್ಣಾಙ್ಕ c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(Region,XCreateRegion,(ಶೂನ್ಯ))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XUnionRectWithRegion,(XRectangle *a, Region b, Region c))
SDL_X11_SYM(ಶೂನ್ಯ,XDestroyRegion,(Region))
SDL_X11_SYM(ಶೂನ್ಯ,XrmInitialize,(ಶೂನ್ಯ))
SDL_X11_SYM(ವರ್ಣ*,XResourceManagerString,(Display *display))
SDL_X11_SYM(XrmDatabase,XrmGetStringDatabase,(ವರ್ಣ *data))
SDL_X11_SYM(ಶೂನ್ಯ,XrmDestroyDatabase,(XrmDatabase db))
SDL_X11_SYM(Bool,XrmGetResource,(XrmDatabase db, ವರ್ಣ* str_name, ವರ್ಣ* str_class, ವರ್ಣ **str_type_return, Xrm_ಮೌಲ್ಯ *))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XGetPointerMapping,(Display *a, unsigned ವರ್ಣ *b, unsigned ಪೂರ್ಣಾಙ್ಕ c))

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
SDL_X11_MODULE(XFIXES)
SDL_X11_SYM(PointerBarrier, XFixesCreatePointerBarrier, (Display* a, Window b, ಪೂರ್ಣಾಙ್ಕ c, ಪೂರ್ಣಾಙ್ಕ d, ಪೂರ್ಣಾಙ್ಕ e, ಪೂರ್ಣಾಙ್ಕ f, ಪೂರ್ಣಾಙ್ಕ g, ಪೂರ್ಣಾಙ್ಕ h, ಪೂರ್ಣಾಙ್ಕ *i))
SDL_X11_SYM(ಶೂನ್ಯ, XFixesDestroyPointerBarrier, (Display* a, PointerBarrier b))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ, XIBarrierReleasePointer,(Display* a,  ಪೂರ್ಣಾಙ್ಕ b, PointerBarrier c, BarrierEventID d)) // this is actually Xinput2
SDL_X11_SYM(Status, XFixesQueryVersion,(Display* a, ಪೂರ್ಣಾಙ್ಕ* b, ಪೂರ್ಣಾಙ್ಕ* c))
SDL_X11_SYM(Status, XFixes_Select_Selection_ಒಳಹರಿವು, (Display* a, Window b, Atom c, unsigned long d))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
SDL_X11_MODULE(XSYNC)
SDL_X11_SYM(Status, XSyncQueryExtension, (Display* a, ಪೂರ್ಣಾಙ್ಕ* b, ಪೂರ್ಣಾಙ್ಕ* c))
SDL_X11_SYM(Status, XSyncInitialize, (Display* a, ಪೂರ್ಣಾಙ್ಕ* b, ಪೂರ್ಣಾಙ್ಕ* c))
SDL_X11_SYM(XSyncCounter, XSyncCreateCounter, (Display* a, XSync_ಮೌಲ್ಯ b))
SDL_X11_SYM(Status, XSyncDestroyCounter, (Display* a, XSyncCounter b))
SDL_X11_SYM(Status, XSyncSetCounter, (Display* a, XSyncCounter b, XSync_ಮೌಲ್ಯ c))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XTEST
SDL_X11_MODULE(XTEST)
SDL_X11_SYM(Status, XTestQueryExtension, (Display* a, ಪೂರ್ಣಾಙ್ಕ* b, ಪೂರ್ಣಾಙ್ಕ* c))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ, XTestFakeMotionEvent, (Display* a, ಪೂರ್ಣಾಙ್ಕ b, ಪೂರ್ಣಾಙ್ಕ c, ಪೂರ್ಣಾಙ್ಕ d, unsigned long e))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
SDL_X11_SYM(Bool,XGetEventData,(Display* a,XGenericEventCookie* b))
SDL_X11_SYM(ಶೂನ್ಯ,XFreeEventData,(Display* a,XGenericEventCookie* b))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
SDL_X11_SYM(Bool,XkbQueryExtension,(Display* a,ಪೂರ್ಣಾಙ್ಕ * b,ಪೂರ್ಣಾಙ್ಕ * c,ಪೂರ್ಣಾಙ್ಕ * d,ಪೂರ್ಣಾಙ್ಕ * e, ಪೂರ್ಣಾಙ್ಕ *f))
SDL_X11_SYM(ಕೀಲಿ_Sym,XkbKeycodeToKeysym,(Display* a, ಕೀಲಿ_Code_2 b, unsigned ಪೂರ್ಣಾಙ್ಕ c, unsigned ಪೂರ್ಣಾಙ್ಕ d))
SDL_X11_SYM(Bool,XkbSelectEvents,(Display* a, unsigned ಪೂರ್ಣಾಙ್ಕ b, unsigned ಪೂರ್ಣಾಙ್ಕ c, unsigned long d))
SDL_X11_SYM(Bool,XkbSelectEventDetails,(Display* a, unsigned ಪೂರ್ಣಾಙ್ಕ b, unsigned ಪೂರ್ಣಾಙ್ಕ c, unsigned long d, unsigned long e))
SDL_X11_SYM(Status,XkbGetNames,(Display *a, unsigned ಪೂರ್ಣಾಙ್ಕ b, XkbDescPtr c))
SDL_X11_SYM(Status,XkbGetState,(Display* a,unsigned ಪೂರ್ಣಾಙ್ಕ b,XkbStatePtr c))
SDL_X11_SYM(Status,XkbGetUpdatedMap,(Display* a,unsigned ಪೂರ್ಣಾಙ್ಕ b,XkbDescPtr c))
SDL_X11_SYM(XkbDescPtr,XkbGetMap,(Display* a,unsigned ಪೂರ್ಣಾಙ್ಕ b,unsigned ಪೂರ್ಣಾಙ್ಕ c))
SDL_X11_SYM(ಶೂನ್ಯ,XkbFreeClientMap,(XkbDescPtr a,unsigned ಪೂರ್ಣಾಙ್ಕ b, Bool c))
SDL_X11_SYM(ಶೂನ್ಯ,XkbFreeKeyboard,(XkbDescPtr a,unsigned ಪೂರ್ಣಾಙ್ಕ b, Bool c))
SDL_X11_SYM(Status,XkbRefreshKeyboardMapping,(XkbMapNotifyEvent *a))
SDL_X11_SYM(Bool,XkbSetDetectableAutoRepeat,(Display* a, Bool b, Bool* c))
#endif

#ifdef X_HAVE_UTF8_STRING
SDL_X11_MODULE(UTF8)
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,Xutf8TextListToTextProperty,(Display* a,ವರ್ಣ** b,ಪೂರ್ಣಾಙ್ಕ c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,Xutf8LookupString,(XIC a,XKeyPressedEvent* b,ವರ್ಣ* c,ಪೂರ್ಣಾಙ್ಕ d,ಕೀಲಿ_Sym* e,Status* f))
SDL_X11_SYM(XIC,XCreateIC,(XIM,...))
SDL_X11_SYM(ಶೂನ್ಯ,XDestroyIC,(XIC a))
SDL_X11_SYM(ವರ್ಣ*,XGetICValues,(XIC,...))
SDL_X11_SYM(ವರ್ಣ*,XSetICValues,(XIC,...))
SDL_X11_SYM(XVaNestedList,XVaCreateNestedList,(ಪೂರ್ಣಾಙ್ಕ, ...))
SDL_X11_SYM(ಶೂನ್ಯ,XSetICFocus,(XIC a))
SDL_X11_SYM(ಶೂನ್ಯ,XUnsetICFocus,(XIC a))
SDL_X11_SYM(XIM,XOpenIM,(Display* a,ಸಂರಚನಾ _XrmHashBucketRec* b,ವರ್ಣ* c,ವರ್ಣ* d))
SDL_X11_SYM(Status,XCloseIM,(XIM a))
SDL_X11_SYM(ವರ್ಣ*, XSetIMValues,(XIM,...))
SDL_X11_SYM(Bool,XRegisterIMInstantiateCallback,(Display*,ಸಂರಚನಾ _XrmHashBucketRec*,ವರ್ಣ*,ವರ್ಣ*,XIDProc,XPointer))
SDL_X11_SYM(Bool,XUnregisterIMInstantiateCallback,(Display*,ಸಂರಚನಾ _XrmHashBucketRec*,ವರ್ಣ*,ವರ್ಣ*,XIDProc,XPointer))
SDL_X11_SYM(ಶೂನ್ಯ,Xutf8DrawString,(Display *a, Drawable b, XFontSet c, GC d, ಪೂರ್ಣಾಙ್ಕ e, ಪೂರ್ಣಾಙ್ಕ f, _Xconst ವರ್ಣ *g, ಪೂರ್ಣಾಙ್ಕ h))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,Xutf8TextExtents,(XFontSet a, _Xconst ವರ್ಣ* b, ಪೂರ್ಣಾಙ್ಕ c, XRectangle* d, XRectangle* e))
SDL_X11_SYM(ವರ್ಣ*,XSetLocaleModifiers,(ಧ್ರುವ ವರ್ಣ *a))
SDL_X11_SYM(ವರ್ಣ*,Xutf8ResetIC,(XIC a))
SDL_X11_SYM(XFontSetExtents*,XExtentsOfFontSet,(XFontSet a))
SDL_X11_SYM(Bool,XContextDependentDrawing,(XFontSet a))
#endif


#ifndef NO_SHARED_MEMORY
SDL_X11_MODULE(SHM)
SDL_X11_SYM(Status,XShmAttach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmDetach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmPutImage,(Display* a,Drawable b,GC c,XImage* d,ಪೂರ್ಣಾಙ್ಕ e,ಪೂರ್ಣಾಙ್ಕ f,ಪೂರ್ಣಾಙ್ಕ g,ಪೂರ್ಣಾಙ್ಕ h,unsigned ಪೂರ್ಣಾಙ್ಕ i,unsigned ಪೂರ್ಣಾಙ್ಕ j,Bool k))
SDL_X11_SYM(Status,XShmGetImage,(Display* a,Drawable b,XImage *c,ಪೂರ್ಣಾಙ್ಕ d, ಪೂರ್ಣಾಙ್ಕ e, unsigned long f))
SDL_X11_SYM(XImage*,XShmCreateImage,(Display* a,Visual* b,unsigned ಪೂರ್ಣಾಙ್ಕ c,ಪೂರ್ಣಾಙ್ಕ d,ವರ್ಣ* e,XShmSegmentInfo* f,unsigned ಪೂರ್ಣಾಙ್ಕ g,unsigned ಪೂರ್ಣಾಙ್ಕ h))
SDL_X11_SYM(Pixmap,XShmCreatePixmap,(Display *a,Drawable b,ವರ್ಣ* c,XShmSegmentInfo* d, unsigned ಪೂರ್ಣಾಙ್ಕ e, unsigned ಪೂರ್ಣಾಙ್ಕ f, unsigned ಪೂರ್ಣಾಙ್ಕ g))
SDL_X11_SYM(Bool,XShmQueryExtension,(Display* a))
SDL_X11_SYM(Status,XShmQueryVersion,(Display* a, ಪೂರ್ಣಾಙ್ಕ *b, ಪೂರ್ಣಾಙ್ಕ *c, Bool *d))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XShmPixmapFormat,(Display* a))
#endif

/*
 * Not required...these only exist in code in headers on some 64-bit platforms,
 *  and are removed via macros elsewhere, so it's safe for them to be missing.
 */
#ifdef LONG64
SDL_X11_MODULE(IO_32BIT)
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,_XData32,(Display *dpy,ಪಞ್ಜಿಕಾ _Xconst long *data,unsigned len))
SDL_X11_SYM(ಶೂನ್ಯ,_XRead32,(Display *dpy,ಪಞ್ಜಿಕಾ long *data,long len))
#endif

/*
 * These only show up on some variants of Unix.
 */
#ifdef SDL_PLATFORM_OSF
SDL_X11_MODULE(OSF_ENTRY_POINTS)
SDL_X11_SYM(ಶೂನ್ಯ,_SmtBufferOverflow,(Display *dpy,ಪಞ್ಜಿಕಾ smtDisplayPtr p))
SDL_X11_SYM(ಶೂನ್ಯ,_SmtIpError,(Display *dpy,ಪಞ್ಜಿಕಾ smtDisplayPtr p,ಪೂರ್ಣಾಙ್ಕ i))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,ipAllocateData,(ChannelPtr a,IPCard b,IPDataPtr * c))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,ipUnallocateAndSendData,(ChannelPtr a,IPCard b))
#endif

// XCursor support
#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
SDL_X11_MODULE(XCURSOR)
SDL_X11_SYM(XcursorImage*,XcursorImageCreate,(ಪೂರ್ಣಾಙ್ಕ a,ಪೂರ್ಣಾಙ್ಕ b))
SDL_X11_SYM(XcursorImages*,XcursorImagesCreate,(ಪೂರ್ಣಾಙ್ಕ a))
SDL_X11_SYM(ಶೂನ್ಯ,XcursorImageDestroy,(XcursorImage *a))
SDL_X11_SYM(ಶೂನ್ಯ,XcursorImagesDestroy,(XcursorImages *a))
SDL_X11_SYM(Cursor,XcursorImageLoadCursor,(Display *a,ಧ್ರುವ XcursorImage *b))
SDL_X11_SYM(Cursor,XcursorImagesLoadCursor,(Display *a,ಧ್ರುವ XcursorImages *b))
SDL_X11_SYM(Cursor,XcursorLibraryLoadCursor,(Display *a, ಧ್ರುವ ವರ್ಣ *b))
#endif

// Xdbe support
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
SDL_X11_MODULE(XDBE)
SDL_X11_SYM(Status,XdbeQueryExtension,(Display *dpy,ಪೂರ್ಣಾಙ್ಕ *major_version_return,ಪೂರ್ಣಾಙ್ಕ *minor_version_return))
SDL_X11_SYM(XdbeBackBuffer,XdbeAllocateBackBufferName,(Display *dpy,Window window,XdbeSwapAction swap_action))
SDL_X11_SYM(Status,XdbeDeallocateBackBufferName,(Display *dpy,XdbeBackBuffer buffer))
SDL_X11_SYM(Status,XdbeSwapBuffers,(Display *dpy,XdbeSwapInfo *swap_info,ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_windows))
SDL_X11_SYM(Status,XdbeBeginIdiom,(Display *dpy))
SDL_X11_SYM(Status,XdbeEndIdiom,(Display *dpy))
SDL_X11_SYM(XdbeScreenVisualInfo*,XdbeGetVisualInfo,(Display *dpy,Drawable *screen_specifiers,ಪೂರ್ಣಾಙ್ಕ *ಅಂಕೆ_screens))
SDL_X11_SYM(ಶೂನ್ಯ,XdbeFreeVisualInfo,(XdbeScreenVisualInfo *visual_info))
SDL_X11_SYM(XdbeBackBufferAttributes*,XdbeGetBackBufferAttributes,(Display *dpy,XdbeBackBuffer buffer))
#endif

// XInput2 support for multiple mice, tablets, etc.
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
SDL_X11_MODULE(XINPUT2)
SDL_X11_SYM(XIDeviceInfo*,XIQueryDevice,(Display *a,ಪೂರ್ಣಾಙ್ಕ b,ಪೂರ್ಣಾಙ್ಕ *c))
SDL_X11_SYM(ಶೂನ್ಯ,XIFreeDeviceInfo,(XIDeviceInfo *a))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XISelectEvents,(Display *a,Window b,XIEventMask *c,ಪೂರ್ಣಾಙ್ಕ d))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XIGrabTouchBegin,(Display *a,ಪೂರ್ಣಾಙ್ಕ b,Window c,ಪೂರ್ಣಾಙ್ಕ d,XIEventMask *e,ಪೂರ್ಣಾಙ್ಕ f,XIGrabModifiers *g))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XIUngrabTouchBegin, (Display *a,ಪೂರ್ಣಾಙ್ಕ b,Window c, ಪೂರ್ಣಾಙ್ಕ d,XIGrabModifiers *e))
SDL_X11_SYM(Status,XIQueryVersion,(Display *a,ಪೂರ್ಣಾಙ್ಕ *b,ಪೂರ್ಣಾಙ್ಕ *c))
SDL_X11_SYM(XIEventMask*,XIGetSelectedEvents,(Display *a,Window b,ಪೂರ್ಣಾಙ್ಕ *c))
SDL_X11_SYM(Bool,XIGetClientPointer,(Display *a,Window b,ಪೂರ್ಣಾಙ್ಕ *c))
SDL_X11_SYM(Bool,XIWarpPointer,(Display *a,ಪೂರ್ಣಾಙ್ಕ b,Window c,Window d,ದ್ವಿಗುಣ e,ದ್ವಿಗುಣ f,ಪೂರ್ಣಾಙ್ಕ g,ಪೂರ್ಣಾಙ್ಕ h,ದ್ವಿಗುಣ i,ದ್ವಿಗುಣ j))
SDL_X11_SYM(Status,XIGetProperty,(Display *a,ಪೂರ್ಣಾಙ್ಕ b,Atom c,long d,long e,Bool f, Atom g, Atom *h, ಪೂರ್ಣಾಙ್ಕ *i, unsigned long *j, unsigned long *k, unsigned ವರ್ಣ **l))
#endif

// XRandR support
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
SDL_X11_MODULE(XRANDR)
SDL_X11_SYM(Status,XRRQueryVersion,(Display *dpy,ಪೂರ್ಣಾಙ್ಕ *major_versionp,ಪೂರ್ಣಾಙ್ಕ *minor_versionp))
SDL_X11_SYM(Bool,XRRQueryExtension,(Display *dpy,ಪೂರ್ಣಾಙ್ಕ *event_base_return,ಪೂರ್ಣಾಙ್ಕ *error_base_return))
SDL_X11_SYM(XRRScreenConfiguration *,XRRGetScreenInfo,(Display *dpy,Drawable draw))
SDL_X11_SYM(SizeID,XRRConfigCurrentConfiguration,(XRRScreenConfiguration *config,Rotation *rotation))
SDL_X11_SYM(short,XRRConfigCurrentRate,(XRRScreenConfiguration *config))
SDL_X11_SYM(short *,XRRConfigRates,(XRRScreenConfiguration *config,ಪೂರ್ಣಾಙ್ಕ sizeID,ಪೂರ್ಣಾಙ್ಕ *nrates))
SDL_X11_SYM(XRRScreenSize *,XRRConfigSizes,(XRRScreenConfiguration *config,ಪೂರ್ಣಾಙ್ಕ *nsizes))
SDL_X11_SYM(Status,XRRSetScreenConfigAndRate,(Display *dpy,XRRScreenConfiguration *config,Drawable draw,ಪೂರ್ಣಾಙ್ಕ size_index,Rotation rotation,short rate,Time timestamp))
SDL_X11_SYM(ಶೂನ್ಯ,XRRFreeScreenConfigInfo,(XRRScreenConfiguration *config))
SDL_X11_SYM(ಶೂನ್ಯ,XRRSetScreenSize,(Display *dpy, Window window,ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height,ಪೂರ್ಣಾಙ್ಕ mmWidth, ಪೂರ್ಣಾಙ್ಕ mmHeight))
SDL_X11_SYM(Status,XRRGetScreenSizeRange,(Display *dpy, Window window,ಪೂರ್ಣಾಙ್ಕ *minWidth, ಪೂರ್ಣಾಙ್ಕ *minHeight, ಪೂರ್ಣಾಙ್ಕ *maxWidth, ಪೂರ್ಣಾಙ್ಕ *maxHeight))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResources,(Display *dpy, Window window))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResourcesCurrent,(Display *dpy, Window window))
SDL_X11_SYM(ಶೂನ್ಯ,XRRFreeScreenResources,(XRRScreenResources *resources))
SDL_X11_SYM(XRROutputInfo *,XRRGetOutputInfo,(Display *dpy, XRRScreenResources *resources, RROutput output))
SDL_X11_SYM(ಶೂನ್ಯ,XRRFreeOutputInfo,(XRROutputInfo *outputInfo))
SDL_X11_SYM(XRRCrtcInfo *,XRRGetCrtcInfo,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc))
SDL_X11_SYM(ಶೂನ್ಯ,XRRFreeCrtcInfo,(XRRCrtcInfo *crtcInfo))
SDL_X11_SYM(Status,XRRSetCrtcConfig,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc, Time timestamp, ಪೂರ್ಣಾಙ್ಕ x, ಪೂರ್ಣಾಙ್ಕ y, RRMode mode, Rotation rotation, RROutput *outputs, ಪೂರ್ಣಾಙ್ಕ noutputs))
SDL_X11_SYM(Atom*,XRRListOutputProperties,(Display *dpy, RROutput output, ಪೂರ್ಣಾಙ್ಕ *nprop))
SDL_X11_SYM(XRRPropertyInfo*,XRRQueryOutputProperty,(Display *dpy,RROutput output, Atom property))
SDL_X11_SYM(ಪೂರ್ಣಾಙ್ಕ,XRRGetOutputProperty,(Display *dpy,RROutput output, Atom property, long offset, long length, Bool _delete, Bool pending, Atom req_type, Atom *actual_type, ಪೂರ್ಣಾಙ್ಕ *actual_format, unsigned long *nitems, unsigned long *bytes_after, unsigned ವರ್ಣ **prop))
SDL_X11_SYM(RROutput,XRRGetOutputPrimary,(Display *dpy,Window window))
SDL_X11_SYM(ಶೂನ್ಯ,XRRSelect_ಒಳಹರಿವು,(Display *dpy, Window window, ಪೂರ್ಣಾಙ್ಕ mask))
SDL_X11_SYM(Status,XRRGetCrtcTransform,(Display *dpy,RRCrtc crtc,XRRCrtcTransformAttributes **attributes))
#endif

// MIT-SCREEN-SAVER support
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
SDL_X11_MODULE(XSS)
SDL_X11_SYM(Bool,XScreenSaverQueryExtension,(Display *dpy,ಪೂರ್ಣಾಙ್ಕ *event_base,ಪೂರ್ಣಾಙ್ಕ *error_base))
SDL_X11_SYM(Status,XScreenSaverQueryVersion,(Display *dpy,ಪೂರ್ಣಾಙ್ಕ *major_versionp,ಪೂರ್ಣಾಙ್ಕ *minor_versionp))
SDL_X11_SYM(ಶೂನ್ಯ,XScreenSaverSuspend,(Display *dpy,Bool suspend))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
SDL_X11_MODULE(XSHAPE)
SDL_X11_SYM(ಶೂನ್ಯ,XShapeCombineMask,(Display *dpy,Window dest,ಪೂರ್ಣಾಙ್ಕ dest_kind,ಪೂರ್ಣಾಙ್ಕ x_off,ಪೂರ್ಣಾಙ್ಕ y_off,Pixmap src,ಪೂರ್ಣಾಙ್ಕ op))
SDL_X11_SYM(ಶೂನ್ಯ,XShapeCombineRegion,(Display *a,Window b,ಪೂರ್ಣಾಙ್ಕ c,ಪೂರ್ಣಾಙ್ಕ d,ಪೂರ್ಣಾಙ್ಕ e,Region f,ಪೂರ್ಣಾಙ್ಕ g))
#endif

#undef SDL_X11_MODULE
#undef SDL_X11_SYM

/* *INDENT-ON* */ // clang-format on
