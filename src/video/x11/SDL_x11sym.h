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
SDL_X11_SYM(XSizeHints*,XAllocSizeHints,(ശൂന്യം))
SDL_X11_SYM(XWMHints*,XAllocWMHints,(ശൂന്യം))
SDL_X11_SYM(XClassHint*,XAllocClassHint,(ശൂന്യം))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XChangePointerControl,(Display* a,Bool b,Bool c,പൂർണ്ണസംഖ്യ d,പൂർണ്ണസംഖ്യ e,പൂർണ്ണസംഖ്യ f))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XChangeProperty,(Display* a,Window b,Atom c,Atom d,പൂർണ്ണസംഖ്യ e,പൂർണ്ണസംഖ്യ f,_Xconst unsigned അക്ഷരം* g,പൂർണ്ണസംഖ്യ h))
SDL_X11_SYM(Bool,XCheckIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XClearWindow,(Display* a,Window b))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XCloseDisplay,(Display* a))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XConvertSelection,(Display* a,Atom b,Atom c,Atom d,Window e,Time f))
SDL_X11_SYM(Pixmap,XCreateBitmapFromData,(Display *dpy,Drawable d,_Xconst അക്ഷരം *data,unsigned പൂർണ്ണസംഖ്യ width,unsigned പൂർണ്ണസംഖ്യ height))
SDL_X11_SYM(Colormap,XCreateColormap,(Display* a,Window b,Visual* c,പൂർണ്ണസംഖ്യ d))
SDL_X11_SYM(Cursor,XCreatePixmapCursor,(Display* a,Pixmap b,Pixmap c,XColor* d,XColor* e,unsigned പൂർണ്ണസംഖ്യ f,unsigned പൂർണ്ണസംഖ്യ g))
SDL_X11_SYM(Cursor,XCreatePixmap,(Display* a,Drawable b,unsigned പൂർണ്ണസംഖ്യ d,unsigned പൂർണ്ണസംഖ്യ e,unsigned പൂർണ്ണസംഖ്യ f))
SDL_X11_SYM(Cursor,XCreateFontCursor,(Display* a,unsigned പൂർണ്ണസംഖ്യ b))
SDL_X11_SYM(XFontSet,XCreateFontSet,(Display* a, _Xconst അക്ഷരം* b, അക്ഷരം*** c, പൂർണ്ണസംഖ്യ* d, അക്ഷരം** e))
SDL_X11_SYM(GC,XCreateGC,(Display* a,Drawable b,unsigned long c,XGCValues* d))
SDL_X11_SYM(ശൂന്യം,XSetFont,(Display* a,GC b,Font c))
SDL_X11_SYM(Status,XAllocColor,(Display *a, Colormap b, XColor *c))
SDL_X11_SYM(XImage*,XCreateImage,(Display* a,Visual* b,unsigned പൂർണ്ണസംഖ്യ c,പൂർണ്ണസംഖ്യ d,പൂർണ്ണസംഖ്യ e,അക്ഷരം* f,unsigned പൂർണ്ണസംഖ്യ g,unsigned പൂർണ്ണസംഖ്യ h,പൂർണ്ണസംഖ്യ i,പൂർണ്ണസംഖ്യ j))
SDL_X11_SYM(Window,XCreateWindow,(Display* a,Window b,പൂർണ്ണസംഖ്യ c,പൂർണ്ണസംഖ്യ d,unsigned പൂർണ്ണസംഖ്യ e,unsigned പൂർണ്ണസംഖ്യ f,unsigned പൂർണ്ണസംഖ്യ g,പൂർണ്ണസംഖ്യ h,unsigned പൂർണ്ണസംഖ്യ i,Visual* j,unsigned long k,XSetWindowAttributes* l))
SDL_X11_SYM(ശൂന്യം,XCopyArea,(Display *a, Drawable b, Drawable c, GC d, പൂർണ്ണസംഖ്യ e, പൂർണ്ണസംഖ്യ f, unsigned പൂർണ്ണസംഖ്യ g, unsigned പൂർണ്ണസംഖ്യ h, പൂർണ്ണസംഖ്യ i, പൂർണ്ണസംഖ്യ j))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XDefineCursor,(Display* a,Window b,Cursor c))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XDeleteProperty,(Display* a,Window b,Atom c))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XDestroyWindow,(Display* a,Window b))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XDisplayKeycodes,(Display* a,പൂർണ്ണസംഖ്യ* b,പൂർണ്ണസംഖ്യ* c))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XDrawRectangle,(Display* a,Drawable b,GC c,പൂർണ്ണസംഖ്യ d,പൂർണ്ണസംഖ്യ e,unsigned പൂർണ്ണസംഖ്യ f,unsigned പൂർണ്ണസംഖ്യ g))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XFontsOfFontSet,(XFontSet a,XFontStruct ***b,അക്ഷരം ***c))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XFillArc,(Display* a,Drawable b,GC c,പൂർണ്ണസംഖ്യ d,പൂർണ്ണസംഖ്യ e,unsigned പൂർണ്ണസംഖ്യ f,unsigned പൂർണ്ണസംഖ്യ g, പൂർണ്ണസംഖ്യ h, പൂർണ്ണസംഖ്യ i))
SDL_X11_SYM(അക്ഷരം*,XDisplayName,(_Xconst അക്ഷരം* a))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XDrawString,(Display* a,Drawable b,GC c,പൂർണ്ണസംഖ്യ d,പൂർണ്ണസംഖ്യ e,_Xconst അക്ഷരം* f,പൂർണ്ണസംഖ്യ g))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XEventsQueued,(Display* a,പൂർണ്ണസംഖ്യ b))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XFillRectangle,(Display* a,Drawable b,GC c,പൂർണ്ണസംഖ്യ d,പൂർണ്ണസംഖ്യ e,unsigned പൂർണ്ണസംഖ്യ f,unsigned പൂർണ്ണസംഖ്യ g))
SDL_X11_SYM(Bool,XFilterEvent,(XEvent *event,Window w))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XFlush,(Display* a))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XFree,(ശൂന്യം*a))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XFreeCursor,(Display* a,Cursor b))
SDL_X11_SYM(ശൂന്യം,XFreeFontSet,(Display* a, XFontSet b))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XFreeGC,(Display* a,GC b))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XFreeFont,(Display* a, XFontStruct* b))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XFreeModifiermap,(XModifierKeymap* a))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XFreePixmap,(Display* a,Pixmap b))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XFreeColormap,(Display* a,Colormap b))
SDL_X11_SYM(ശൂന്യം,XFreeStringList,(അക്ഷരം** a))
SDL_X11_SYM(അക്ഷരം*,XGetAtomName,(Display *a,Atom b))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XGet_നിവേശം_Focus,(Display *a,Window *b,പൂർണ്ണസംഖ്യ *c))
SDL_X11_SYM(താക്കോൽ_Sym*,XGetKeyboardMapping,(Display *a, താക്കോൽ_Code_2 b, പൂർണ്ണസംഖ്യ c, പൂർണ്ണസംഖ്യ *d))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XGetErrorDatabaseText,(Display* a,_Xconst അക്ഷരം* b,_Xconst അക്ഷരം* c,_Xconst അക്ഷരം* d,അക്ഷരം* e,പൂർണ്ണസംഖ്യ f))
SDL_X11_SYM(XModifierKeymap*,XGetModifierMapping,(Display* a))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XGetPointerControl,(Display* a,പൂർണ്ണസംഖ്യ* b,പൂർണ്ണസംഖ്യ* c,പൂർണ്ണസംഖ്യ* d))
SDL_X11_SYM(Window,XGetSelectionOwner,(Display* a,Atom b))
SDL_X11_SYM(XVisualInfo*,XGetVisualInfo,(Display* a,long b,XVisualInfo* c,പൂർണ്ണസംഖ്യ* d))
SDL_X11_SYM(Status,XGetWindowAttributes,(Display* a,Window b,XWindowAttributes* c))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XGetWindowProperty,(Display* a,Window b,Atom c,long d,long e,Bool f,Atom g,Atom* h,പൂർണ്ണസംഖ്യ* i,unsigned long* j,unsigned long *k,unsigned അക്ഷരം **l))
SDL_X11_SYM(XWMHints*,XGetWMHints,(Display* a,Window b))
SDL_X11_SYM(Status,XGetWMNormalHints,(Display *a,Window b, XSizeHints *c, long *d))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XGrabKeyboard,(Display* a,Window b,Bool c,പൂർണ്ണസംഖ്യ d,പൂർണ്ണസംഖ്യ e,Time f))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XGrabPointer,(Display* a,Window b,Bool c,unsigned പൂർണ്ണസംഖ്യ d,പൂർണ്ണസംഖ്യ e,പൂർണ്ണസംഖ്യ f,Window g,Cursor h,Time i))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XGrabServer,(Display* a))
SDL_X11_SYM(Status,XIconifyWindow,(Display* a,Window b,പൂർണ്ണസംഖ്യ c))
SDL_X11_SYM(താക്കോൽ_Code_2,XKeysymToKeycode,(Display* a,താക്കോൽ_Sym b))
SDL_X11_SYM(അക്ഷരം*,XKeysymToString,(താക്കോൽ_Sym a))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XInstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(Atom,XInternAtom,(Display* a,_Xconst അക്ഷരം* b,Bool c))
SDL_X11_SYM(XPixmap_Format_മൂല്യങ്ങൾ*,XListPixmapFormats,(Display* a,പൂർണ്ണസംഖ്യ* b))
SDL_X11_SYM(XFontStruct*,XLoadQueryFont,(Display* a,_Xconst അക്ഷരം* b))
SDL_X11_SYM(താക്കോൽ_Sym,XLookupKeysym,(XKeyEvent* a,പൂർണ്ണസംഖ്യ b))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XLookupString,(XKeyEvent* a,അക്ഷരം* b,പൂർണ്ണസംഖ്യ c,താക്കോൽ_Sym* d,XComposeStatus* e))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XMapRaised,(Display* a,Window b))
SDL_X11_SYM(Status,XMatchVisualInfo,(Display* a,പൂർണ്ണസംഖ്യ b,പൂർണ്ണസംഖ്യ c,പൂർണ്ണസംഖ്യ d,XVisualInfo* e))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XMissingExtension,(Display* a,_Xconst അക്ഷരം* b))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XMoveWindow,(Display* a,Window b,പൂർണ്ണസംഖ്യ c,പൂർണ്ണസംഖ്യ d))
SDL_X11_SYM(Display*,XOpenDisplay,(_Xconst അക്ഷരം* a))
SDL_X11_SYM(Status,XInitThreads,(ശൂന്യം))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XPeekEvent,(Display* a,XEvent* b))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XPending,(Display* a))
SDL_X11_SYM(XImage*,XGetImage,(Display* a,Drawable b,പൂർണ്ണസംഖ്യ c, പൂർണ്ണസംഖ്യ d,unsigned പൂർണ്ണസംഖ്യ e,unsigned പൂർണ്ണസംഖ്യ f,unsigned long g,പൂർണ്ണസംഖ്യ h))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XPutImage,(Display* a,Drawable b,GC c,XImage* d,പൂർണ്ണസംഖ്യ e,പൂർണ്ണസംഖ്യ f,പൂർണ്ണസംഖ്യ g,പൂർണ്ണസംഖ്യ h,unsigned പൂർണ്ണസംഖ്യ i,unsigned പൂർണ്ണസംഖ്യ j))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XQueryKeymap,(Display* a,അക്ഷരം b[32]))
SDL_X11_SYM(Bool,XQueryPointer,(Display* a,Window b,Window* c,Window* d,പൂർണ്ണസംഖ്യ* e,പൂർണ്ണസംഖ്യ* f,പൂർണ്ണസംഖ്യ* g,പൂർണ്ണസംഖ്യ* h,unsigned പൂർണ്ണസംഖ്യ* i))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XRaiseWindow,(Display* a,Window b))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XReparentWindow,(Display* a,Window b,Window c,പൂർണ്ണസംഖ്യ d,പൂർണ്ണസംഖ്യ e))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XResetScreenSaver,(Display* a))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XResizeWindow,(Display* a,Window b,unsigned പൂർണ്ണസംഖ്യ c,unsigned പൂർണ്ണസംഖ്യ d))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XScreen_സംഖ്യ_Of_Screen,(Screen* a))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XSelect_നിവേശം,(Display* a,Window b,long c))
SDL_X11_SYM(Status,XSendEvent,(Display* a,Window b,Bool c,long d,XEvent* e))
SDL_X11_SYM(XErrorHandler,XSetErrorHandler,(XErrorHandler a))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XSetForeground,(Display* a,GC b,unsigned long c))
SDL_X11_SYM(XIOErrorHandler,XSetIOErrorHandler,(XIOErrorHandler a))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XSet_നിവേശം_Focus,(Display *a,Window b,പൂർണ്ണസംഖ്യ c,Time d))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XSetSelectionOwner,(Display* a,Atom b,Window c,Time d))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XSetTransientForHint,(Display* a,Window b,Window c))
SDL_X11_SYM(ശൂന്യം,XSetTextProperty,(Display* a,Window b,XTextProperty* c,Atom d))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XSetWindowBackground,(Display* a,Window b,unsigned long c))
SDL_X11_SYM(ശൂന്യം,XSetWMHints,(Display* a,Window b,XWMHints* c))
SDL_X11_SYM(ശൂന്യം,XSetWMNormalHints,(Display* a,Window b,XSizeHints* c))
SDL_X11_SYM(ശൂന്യം,XSetWMProperties,(Display* a,Window b,XTextProperty* c,XTextProperty* d,അക്ഷരം** e,പൂർണ്ണസംഖ്യ f,XSizeHints* g,XWMHints* h,XClassHint* i))
SDL_X11_SYM(Status,XSetWMProtocols,(Display* a,Window b,Atom* c,പൂർണ്ണസംഖ്യ d))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XStoreColors,(Display* a,Colormap b,XColor* c,പൂർണ്ണസംഖ്യ d))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XStoreName,(Display* a,Window b,_Xconst അക്ഷരം* c))
SDL_X11_SYM(Status,XStringListToTextProperty,(അക്ഷരം** a,പൂർണ്ണസംഖ്യ b,XTextProperty* c))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XSync,(Display* a,Bool b))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XTextExtents,(XFontStruct* a,_Xconst അക്ഷരം* b,പൂർണ്ണസംഖ്യ c,പൂർണ്ണസംഖ്യ* d,പൂർണ്ണസംഖ്യ* e,പൂർണ്ണസംഖ്യ* f,XCharStruct* g))
SDL_X11_SYM(Bool,XTranslateCoordinates,(Display *a,Window b,Window c,പൂർണ്ണസംഖ്യ d,പൂർണ്ണസംഖ്യ e,പൂർണ്ണസംഖ്യ* f,പൂർണ്ണസംഖ്യ* g,Window* h))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XUndefineCursor,(Display* a,Window b))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XUngrabKeyboard,(Display* a,Time b))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XUngrabPointer,(Display* a,Time b))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XUngrabServer,(Display* a))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XUninstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XUnloadFont,(Display* a,Font b))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XWarpPointer,(Display* a,Window b,Window c,പൂർണ്ണസംഖ്യ d,പൂർണ്ണസംഖ്യ e,unsigned പൂർണ്ണസംഖ്യ f,unsigned പൂർണ്ണസംഖ്യ g,പൂർണ്ണസംഖ്യ h,പൂർണ്ണസംഖ്യ i))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XWindowEvent,(Display* a,Window b,long c,XEvent* d))
SDL_X11_SYM(Status,XWithdrawWindow,(Display* a,Window b,പൂർണ്ണസംഖ്യ c))
SDL_X11_SYM(VisualID,XVisualIDFromVisual,(Visual* a))
SDL_X11_SYM(അക്ഷരം*,XGetDefault,(Display* a,_Xconst അക്ഷരം* b, _Xconst അക്ഷരം* c))
SDL_X11_SYM(Bool,XQueryExtension,(Display* a,_Xconst അക്ഷരം* b,പൂർണ്ണസംഖ്യ* c,പൂർണ്ണസംഖ്യ* d,പൂർണ്ണസംഖ്യ* e))
SDL_X11_SYM(അക്ഷരം *,XDisplayString,(Display* a))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XGetErrorText,(Display* a,പൂർണ്ണസംഖ്യ b,അക്ഷരം* c,പൂർണ്ണസംഖ്യ d))
SDL_X11_SYM(ശൂന്യം,_XEatData,(Display* a,unsigned long b))
SDL_X11_SYM(ശൂന്യം,_XFlush,(Display* a))
SDL_X11_SYM(ശൂന്യം,_XFlushGCCache,(Display* a,GC b))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,_XRead,(Display* a,അക്ഷരം* b,long c))
SDL_X11_SYM(ശൂന്യം,_XReadPad,(Display* a,അക്ഷരം* b,long c))
SDL_X11_SYM(ശൂന്യം,_XSend,(Display* a,_Xconst അക്ഷരം* b,long c))
SDL_X11_SYM(Status,_XReply,(Display* a,xReply* b,പൂർണ്ണസംഖ്യ c,Bool d))
SDL_X11_SYM(unsigned long,_XSetLastRequestRead,(Display* a,xGenericReply* b))
SDL_X11_SYM(SDL_X11_XSynchronizeRetType,XSynchronize,(Display* a,Bool b))
SDL_X11_SYM(SDL_X11_XESetWireToEventRetType,XESetWireToEvent,(Display* a,പൂർണ്ണസംഖ്യ b,SDL_X11_XESetWireToEventRetType c))
SDL_X11_SYM(SDL_X11_XESetEventToWireRetType,XESetEventToWire,(Display* a,പൂർണ്ണസംഖ്യ b,SDL_X11_XESetEventToWireRetType c))
SDL_X11_SYM(ശൂന്യം,XRefreshKeyboardMapping,(XMappingEvent *a))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XQuery_വൃക്ഷം,(Display* a,Window b,Window* c,Window* d,Window** e,unsigned പൂർണ്ണസംഖ്യ* f))
SDL_X11_SYM(Bool,XSupportsLocale,(ശൂന്യം))
SDL_X11_SYM(Status,XmbTextListToTextProperty,(Display* a,അക്ഷരം** b,പൂർണ്ണസംഖ്യ c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(Region,XCreateRegion,(ശൂന്യം))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XUnionRectWithRegion,(XRectangle *a, Region b, Region c))
SDL_X11_SYM(ശൂന്യം,XDestroyRegion,(Region))
SDL_X11_SYM(ശൂന്യം,XrmInitialize,(ശൂന്യം))
SDL_X11_SYM(അക്ഷരം*,XResourceManagerString,(Display *display))
SDL_X11_SYM(XrmDatabase,XrmGetStringDatabase,(അക്ഷരം *data))
SDL_X11_SYM(ശൂന്യം,XrmDestroyDatabase,(XrmDatabase db))
SDL_X11_SYM(Bool,XrmGetResource,(XrmDatabase db, അക്ഷരം* str_name, അക്ഷരം* str_class, അക്ഷരം **str_type_return, Xrm_മൂല്യം *))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XGetPointerMapping,(Display *a, unsigned അക്ഷരം *b, unsigned പൂർണ്ണസംഖ്യ c))

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
SDL_X11_MODULE(XFIXES)
SDL_X11_SYM(PointerBarrier, XFixesCreatePointerBarrier, (Display* a, Window b, പൂർണ്ണസംഖ്യ c, പൂർണ്ണസംഖ്യ d, പൂർണ്ണസംഖ്യ e, പൂർണ്ണസംഖ്യ f, പൂർണ്ണസംഖ്യ g, പൂർണ്ണസംഖ്യ h, പൂർണ്ണസംഖ്യ *i))
SDL_X11_SYM(ശൂന്യം, XFixesDestroyPointerBarrier, (Display* a, PointerBarrier b))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ, XIBarrierReleasePointer,(Display* a,  പൂർണ്ണസംഖ്യ b, PointerBarrier c, BarrierEventID d)) // this is actually Xinput2
SDL_X11_SYM(Status, XFixesQueryVersion,(Display* a, പൂർണ്ണസംഖ്യ* b, പൂർണ്ണസംഖ്യ* c))
SDL_X11_SYM(Status, XFixes_Select_Selection_നിവേശം, (Display* a, Window b, Atom c, unsigned long d))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
SDL_X11_MODULE(XSYNC)
SDL_X11_SYM(Status, XSyncQueryExtension, (Display* a, പൂർണ്ണസംഖ്യ* b, പൂർണ്ണസംഖ്യ* c))
SDL_X11_SYM(Status, XSyncInitialize, (Display* a, പൂർണ്ണസംഖ്യ* b, പൂർണ്ണസംഖ്യ* c))
SDL_X11_SYM(XSyncCounter, XSyncCreateCounter, (Display* a, XSync_മൂല്യം b))
SDL_X11_SYM(Status, XSyncDestroyCounter, (Display* a, XSyncCounter b))
SDL_X11_SYM(Status, XSyncSetCounter, (Display* a, XSyncCounter b, XSync_മൂല്യം c))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XTEST
SDL_X11_MODULE(XTEST)
SDL_X11_SYM(Status, XTestQueryExtension, (Display* a, പൂർണ്ണസംഖ്യ* b, പൂർണ്ണസംഖ്യ* c))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ, XTestFakeMotionEvent, (Display* a, പൂർണ്ണസംഖ്യ b, പൂർണ്ണസംഖ്യ c, പൂർണ്ണസംഖ്യ d, unsigned long e))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
SDL_X11_SYM(Bool,XGetEventData,(Display* a,XGenericEventCookie* b))
SDL_X11_SYM(ശൂന്യം,XFreeEventData,(Display* a,XGenericEventCookie* b))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
SDL_X11_SYM(Bool,XkbQueryExtension,(Display* a,പൂർണ്ണസംഖ്യ * b,പൂർണ്ണസംഖ്യ * c,പൂർണ്ണസംഖ്യ * d,പൂർണ്ണസംഖ്യ * e, പൂർണ്ണസംഖ്യ *f))
SDL_X11_SYM(താക്കോൽ_Sym,XkbKeycodeToKeysym,(Display* a, താക്കോൽ_Code_2 b, unsigned പൂർണ്ണസംഖ്യ c, unsigned പൂർണ്ണസംഖ്യ d))
SDL_X11_SYM(Bool,XkbSelectEvents,(Display* a, unsigned പൂർണ്ണസംഖ്യ b, unsigned പൂർണ്ണസംഖ്യ c, unsigned long d))
SDL_X11_SYM(Bool,XkbSelectEventDetails,(Display* a, unsigned പൂർണ്ണസംഖ്യ b, unsigned പൂർണ്ണസംഖ്യ c, unsigned long d, unsigned long e))
SDL_X11_SYM(Status,XkbGetNames,(Display *a, unsigned പൂർണ്ണസംഖ്യ b, XkbDescPtr c))
SDL_X11_SYM(Status,XkbGetState,(Display* a,unsigned പൂർണ്ണസംഖ്യ b,XkbStatePtr c))
SDL_X11_SYM(Status,XkbGetUpdatedMap,(Display* a,unsigned പൂർണ്ണസംഖ്യ b,XkbDescPtr c))
SDL_X11_SYM(XkbDescPtr,XkbGetMap,(Display* a,unsigned പൂർണ്ണസംഖ്യ b,unsigned പൂർണ്ണസംഖ്യ c))
SDL_X11_SYM(ശൂന്യം,XkbFreeClientMap,(XkbDescPtr a,unsigned പൂർണ്ണസംഖ്യ b, Bool c))
SDL_X11_SYM(ശൂന്യം,XkbFreeKeyboard,(XkbDescPtr a,unsigned പൂർണ്ണസംഖ്യ b, Bool c))
SDL_X11_SYM(Status,XkbRefreshKeyboardMapping,(XkbMapNotifyEvent *a))
SDL_X11_SYM(Bool,XkbSetDetectableAutoRepeat,(Display* a, Bool b, Bool* c))
#endif

#ifdef X_HAVE_UTF8_STRING
SDL_X11_MODULE(UTF8)
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,Xutf8TextListToTextProperty,(Display* a,അക്ഷരം** b,പൂർണ്ണസംഖ്യ c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,Xutf8LookupString,(XIC a,XKeyPressedEvent* b,അക്ഷരം* c,പൂർണ്ണസംഖ്യ d,താക്കോൽ_Sym* e,Status* f))
SDL_X11_SYM(XIC,XCreateIC,(XIM,...))
SDL_X11_SYM(ശൂന്യം,XDestroyIC,(XIC a))
SDL_X11_SYM(അക്ഷരം*,XGetICValues,(XIC,...))
SDL_X11_SYM(അക്ഷരം*,XSetICValues,(XIC,...))
SDL_X11_SYM(XVaNestedList,XVaCreateNestedList,(പൂർണ്ണസംഖ്യ, ...))
SDL_X11_SYM(ശൂന്യം,XSetICFocus,(XIC a))
SDL_X11_SYM(ശൂന്യം,XUnsetICFocus,(XIC a))
SDL_X11_SYM(XIM,XOpenIM,(Display* a,ഘടന _XrmHashBucketRec* b,അക്ഷരം* c,അക്ഷരം* d))
SDL_X11_SYM(Status,XCloseIM,(XIM a))
SDL_X11_SYM(അക്ഷരം*, XSetIMValues,(XIM,...))
SDL_X11_SYM(Bool,XRegisterIMInstantiateCallback,(Display*,ഘടന _XrmHashBucketRec*,അക്ഷരം*,അക്ഷരം*,XIDProc,XPointer))
SDL_X11_SYM(Bool,XUnregisterIMInstantiateCallback,(Display*,ഘടന _XrmHashBucketRec*,അക്ഷരം*,അക്ഷരം*,XIDProc,XPointer))
SDL_X11_SYM(ശൂന്യം,Xutf8DrawString,(Display *a, Drawable b, XFontSet c, GC d, പൂർണ്ണസംഖ്യ e, പൂർണ്ണസംഖ്യ f, _Xconst അക്ഷരം *g, പൂർണ്ണസംഖ്യ h))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,Xutf8TextExtents,(XFontSet a, _Xconst അക്ഷരം* b, പൂർണ്ണസംഖ്യ c, XRectangle* d, XRectangle* e))
SDL_X11_SYM(അക്ഷരം*,XSetLocaleModifiers,(സ്ഥിരം അക്ഷരം *a))
SDL_X11_SYM(അക്ഷരം*,Xutf8ResetIC,(XIC a))
SDL_X11_SYM(XFontSetExtents*,XExtentsOfFontSet,(XFontSet a))
SDL_X11_SYM(Bool,XContextDependentDrawing,(XFontSet a))
#endif


#ifndef NO_SHARED_MEMORY
SDL_X11_MODULE(SHM)
SDL_X11_SYM(Status,XShmAttach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmDetach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmPutImage,(Display* a,Drawable b,GC c,XImage* d,പൂർണ്ണസംഖ്യ e,പൂർണ്ണസംഖ്യ f,പൂർണ്ണസംഖ്യ g,പൂർണ്ണസംഖ്യ h,unsigned പൂർണ്ണസംഖ്യ i,unsigned പൂർണ്ണസംഖ്യ j,Bool k))
SDL_X11_SYM(Status,XShmGetImage,(Display* a,Drawable b,XImage *c,പൂർണ്ണസംഖ്യ d, പൂർണ്ണസംഖ്യ e, unsigned long f))
SDL_X11_SYM(XImage*,XShmCreateImage,(Display* a,Visual* b,unsigned പൂർണ്ണസംഖ്യ c,പൂർണ്ണസംഖ്യ d,അക്ഷരം* e,XShmSegmentInfo* f,unsigned പൂർണ്ണസംഖ്യ g,unsigned പൂർണ്ണസംഖ്യ h))
SDL_X11_SYM(Pixmap,XShmCreatePixmap,(Display *a,Drawable b,അക്ഷരം* c,XShmSegmentInfo* d, unsigned പൂർണ്ണസംഖ്യ e, unsigned പൂർണ്ണസംഖ്യ f, unsigned പൂർണ്ണസംഖ്യ g))
SDL_X11_SYM(Bool,XShmQueryExtension,(Display* a))
SDL_X11_SYM(Status,XShmQueryVersion,(Display* a, പൂർണ്ണസംഖ്യ *b, പൂർണ്ണസംഖ്യ *c, Bool *d))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XShmPixmapFormat,(Display* a))
#endif

/*
 * Not required...these only exist in code in headers on some 64-bit platforms,
 *  and are removed via macros elsewhere, so it's safe for them to be missing.
 */
#ifdef LONG64
SDL_X11_MODULE(IO_32BIT)
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,_XData32,(Display *dpy,രജിസ്റ്റർ _Xconst long *data,unsigned len))
SDL_X11_SYM(ശൂന്യം,_XRead32,(Display *dpy,രജിസ്റ്റർ long *data,long len))
#endif

/*
 * These only show up on some variants of Unix.
 */
#ifdef SDL_PLATFORM_OSF
SDL_X11_MODULE(OSF_ENTRY_POINTS)
SDL_X11_SYM(ശൂന്യം,_SmtBufferOverflow,(Display *dpy,രജിസ്റ്റർ smtDisplayPtr p))
SDL_X11_SYM(ശൂന്യം,_SmtIpError,(Display *dpy,രജിസ്റ്റർ smtDisplayPtr p,പൂർണ്ണസംഖ്യ i))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,ipAllocateData,(ChannelPtr a,IPCard b,IPDataPtr * c))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,ipUnallocateAndSendData,(ChannelPtr a,IPCard b))
#endif

// XCursor support
#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
SDL_X11_MODULE(XCURSOR)
SDL_X11_SYM(XcursorImage*,XcursorImageCreate,(പൂർണ്ണസംഖ്യ a,പൂർണ്ണസംഖ്യ b))
SDL_X11_SYM(XcursorImages*,XcursorImagesCreate,(പൂർണ്ണസംഖ്യ a))
SDL_X11_SYM(ശൂന്യം,XcursorImageDestroy,(XcursorImage *a))
SDL_X11_SYM(ശൂന്യം,XcursorImagesDestroy,(XcursorImages *a))
SDL_X11_SYM(Cursor,XcursorImageLoadCursor,(Display *a,സ്ഥിരം XcursorImage *b))
SDL_X11_SYM(Cursor,XcursorImagesLoadCursor,(Display *a,സ്ഥിരം XcursorImages *b))
SDL_X11_SYM(Cursor,XcursorLibraryLoadCursor,(Display *a, സ്ഥിരം അക്ഷരം *b))
#endif

// Xdbe support
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
SDL_X11_MODULE(XDBE)
SDL_X11_SYM(Status,XdbeQueryExtension,(Display *dpy,പൂർണ്ണസംഖ്യ *major_version_return,പൂർണ്ണസംഖ്യ *minor_version_return))
SDL_X11_SYM(XdbeBackBuffer,XdbeAllocateBackBufferName,(Display *dpy,Window window,XdbeSwapAction swap_action))
SDL_X11_SYM(Status,XdbeDeallocateBackBufferName,(Display *dpy,XdbeBackBuffer buffer))
SDL_X11_SYM(Status,XdbeSwapBuffers,(Display *dpy,XdbeSwapInfo *swap_info,പൂർണ്ണസംഖ്യ അക്കം_windows))
SDL_X11_SYM(Status,XdbeBeginIdiom,(Display *dpy))
SDL_X11_SYM(Status,XdbeEndIdiom,(Display *dpy))
SDL_X11_SYM(XdbeScreenVisualInfo*,XdbeGetVisualInfo,(Display *dpy,Drawable *screen_specifiers,പൂർണ്ണസംഖ്യ *അക്കം_screens))
SDL_X11_SYM(ശൂന്യം,XdbeFreeVisualInfo,(XdbeScreenVisualInfo *visual_info))
SDL_X11_SYM(XdbeBackBufferAttributes*,XdbeGetBackBufferAttributes,(Display *dpy,XdbeBackBuffer buffer))
#endif

// XInput2 support for multiple mice, tablets, etc.
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
SDL_X11_MODULE(XINPUT2)
SDL_X11_SYM(XIDeviceInfo*,XIQueryDevice,(Display *a,പൂർണ്ണസംഖ്യ b,പൂർണ്ണസംഖ്യ *c))
SDL_X11_SYM(ശൂന്യം,XIFreeDeviceInfo,(XIDeviceInfo *a))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XISelectEvents,(Display *a,Window b,XIEventMask *c,പൂർണ്ണസംഖ്യ d))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XIGrabTouchBegin,(Display *a,പൂർണ്ണസംഖ്യ b,Window c,പൂർണ്ണസംഖ്യ d,XIEventMask *e,പൂർണ്ണസംഖ്യ f,XIGrabModifiers *g))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XIUngrabTouchBegin, (Display *a,പൂർണ്ണസംഖ്യ b,Window c, പൂർണ്ണസംഖ്യ d,XIGrabModifiers *e))
SDL_X11_SYM(Status,XIQueryVersion,(Display *a,പൂർണ്ണസംഖ്യ *b,പൂർണ്ണസംഖ്യ *c))
SDL_X11_SYM(XIEventMask*,XIGetSelectedEvents,(Display *a,Window b,പൂർണ്ണസംഖ്യ *c))
SDL_X11_SYM(Bool,XIGetClientPointer,(Display *a,Window b,പൂർണ്ണസംഖ്യ *c))
SDL_X11_SYM(Bool,XIWarpPointer,(Display *a,പൂർണ്ണസംഖ്യ b,Window c,Window d,ഇരട്ട e,ഇരട്ട f,പൂർണ്ണസംഖ്യ g,പൂർണ്ണസംഖ്യ h,ഇരട്ട i,ഇരട്ട j))
SDL_X11_SYM(Status,XIGetProperty,(Display *a,പൂർണ്ണസംഖ്യ b,Atom c,long d,long e,Bool f, Atom g, Atom *h, പൂർണ്ണസംഖ്യ *i, unsigned long *j, unsigned long *k, unsigned അക്ഷരം **l))
#endif

// XRandR support
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
SDL_X11_MODULE(XRANDR)
SDL_X11_SYM(Status,XRRQueryVersion,(Display *dpy,പൂർണ്ണസംഖ്യ *major_versionp,പൂർണ്ണസംഖ്യ *minor_versionp))
SDL_X11_SYM(Bool,XRRQueryExtension,(Display *dpy,പൂർണ്ണസംഖ്യ *event_base_return,പൂർണ്ണസംഖ്യ *error_base_return))
SDL_X11_SYM(XRRScreenConfiguration *,XRRGetScreenInfo,(Display *dpy,Drawable draw))
SDL_X11_SYM(SizeID,XRRConfigCurrentConfiguration,(XRRScreenConfiguration *config,Rotation *rotation))
SDL_X11_SYM(short,XRRConfigCurrentRate,(XRRScreenConfiguration *config))
SDL_X11_SYM(short *,XRRConfigRates,(XRRScreenConfiguration *config,പൂർണ്ണസംഖ്യ sizeID,പൂർണ്ണസംഖ്യ *nrates))
SDL_X11_SYM(XRRScreenSize *,XRRConfigSizes,(XRRScreenConfiguration *config,പൂർണ്ണസംഖ്യ *nsizes))
SDL_X11_SYM(Status,XRRSetScreenConfigAndRate,(Display *dpy,XRRScreenConfiguration *config,Drawable draw,പൂർണ്ണസംഖ്യ size_index,Rotation rotation,short rate,Time timestamp))
SDL_X11_SYM(ശൂന്യം,XRRFreeScreenConfigInfo,(XRRScreenConfiguration *config))
SDL_X11_SYM(ശൂന്യം,XRRSetScreenSize,(Display *dpy, Window window,പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height,പൂർണ്ണസംഖ്യ mmWidth, പൂർണ്ണസംഖ്യ mmHeight))
SDL_X11_SYM(Status,XRRGetScreenSizeRange,(Display *dpy, Window window,പൂർണ്ണസംഖ്യ *minWidth, പൂർണ്ണസംഖ്യ *minHeight, പൂർണ്ണസംഖ്യ *maxWidth, പൂർണ്ണസംഖ്യ *maxHeight))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResources,(Display *dpy, Window window))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResourcesCurrent,(Display *dpy, Window window))
SDL_X11_SYM(ശൂന്യം,XRRFreeScreenResources,(XRRScreenResources *resources))
SDL_X11_SYM(XRROutputInfo *,XRRGetOutputInfo,(Display *dpy, XRRScreenResources *resources, RROutput output))
SDL_X11_SYM(ശൂന്യം,XRRFreeOutputInfo,(XRROutputInfo *outputInfo))
SDL_X11_SYM(XRRCrtcInfo *,XRRGetCrtcInfo,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc))
SDL_X11_SYM(ശൂന്യം,XRRFreeCrtcInfo,(XRRCrtcInfo *crtcInfo))
SDL_X11_SYM(Status,XRRSetCrtcConfig,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc, Time timestamp, പൂർണ്ണസംഖ്യ x, പൂർണ്ണസംഖ്യ y, RRMode mode, Rotation rotation, RROutput *outputs, പൂർണ്ണസംഖ്യ noutputs))
SDL_X11_SYM(Atom*,XRRListOutputProperties,(Display *dpy, RROutput output, പൂർണ്ണസംഖ്യ *nprop))
SDL_X11_SYM(XRRPropertyInfo*,XRRQueryOutputProperty,(Display *dpy,RROutput output, Atom property))
SDL_X11_SYM(പൂർണ്ണസംഖ്യ,XRRGetOutputProperty,(Display *dpy,RROutput output, Atom property, long offset, long length, Bool _delete, Bool pending, Atom req_type, Atom *actual_type, പൂർണ്ണസംഖ്യ *actual_format, unsigned long *nitems, unsigned long *bytes_after, unsigned അക്ഷരം **prop))
SDL_X11_SYM(RROutput,XRRGetOutputPrimary,(Display *dpy,Window window))
SDL_X11_SYM(ശൂന്യം,XRRSelect_നിവേശം,(Display *dpy, Window window, പൂർണ്ണസംഖ്യ mask))
SDL_X11_SYM(Status,XRRGetCrtcTransform,(Display *dpy,RRCrtc crtc,XRRCrtcTransformAttributes **attributes))
#endif

// MIT-SCREEN-SAVER support
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
SDL_X11_MODULE(XSS)
SDL_X11_SYM(Bool,XScreenSaverQueryExtension,(Display *dpy,പൂർണ്ണസംഖ്യ *event_base,പൂർണ്ണസംഖ്യ *error_base))
SDL_X11_SYM(Status,XScreenSaverQueryVersion,(Display *dpy,പൂർണ്ണസംഖ്യ *major_versionp,പൂർണ്ണസംഖ്യ *minor_versionp))
SDL_X11_SYM(ശൂന്യം,XScreenSaverSuspend,(Display *dpy,Bool suspend))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
SDL_X11_MODULE(XSHAPE)
SDL_X11_SYM(ശൂന്യം,XShapeCombineMask,(Display *dpy,Window dest,പൂർണ്ണസംഖ്യ dest_kind,പൂർണ്ണസംഖ്യ x_off,പൂർണ്ണസംഖ്യ y_off,Pixmap src,പൂർണ്ണസംഖ്യ op))
SDL_X11_SYM(ശൂന്യം,XShapeCombineRegion,(Display *a,Window b,പൂർണ്ണസംഖ്യ c,പൂർണ്ണസംഖ്യ d,പൂർണ്ണസംഖ്യ e,Region f,പൂർണ്ണസംഖ്യ g))
#endif

#undef SDL_X11_MODULE
#undef SDL_X11_SYM

/* *INDENT-ON* */ // clang-format on
