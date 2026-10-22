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
SDL_X11_SYM(XSizeHints*,XAllocSizeHints,(শূন্য))
SDL_X11_SYM(XWMHints*,XAllocWMHints,(শূন্য))
SDL_X11_SYM(XClassHint*,XAllocClassHint,(শূন্য))
SDL_X11_SYM(পূর্ণাঙ্ক,XChangePointerControl,(Display* a,Bool b,Bool c,পূর্ণাঙ্ক d,পূর্ণাঙ্ক e,পূর্ণাঙ্ক f))
SDL_X11_SYM(পূর্ণাঙ্ক,XChangeProperty,(Display* a,Window b,Atom c,Atom d,পূর্ণাঙ্ক e,পূর্ণাঙ্ক f,_Xconst unsigned ৱর্ণ* g,পূর্ণাঙ্ক h))
SDL_X11_SYM(Bool,XCheckIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(পূর্ণাঙ্ক,XClearWindow,(Display* a,Window b))
SDL_X11_SYM(পূর্ণাঙ্ক,XCloseDisplay,(Display* a))
SDL_X11_SYM(পূর্ণাঙ্ক,XConvertSelection,(Display* a,Atom b,Atom c,Atom d,Window e,Time f))
SDL_X11_SYM(Pixmap,XCreateBitmapFromData,(Display *dpy,Drawable d,_Xconst ৱর্ণ *data,unsigned পূর্ণাঙ্ক width,unsigned পূর্ণাঙ্ক height))
SDL_X11_SYM(Colormap,XCreateColormap,(Display* a,Window b,Visual* c,পূর্ণাঙ্ক d))
SDL_X11_SYM(Cursor,XCreatePixmapCursor,(Display* a,Pixmap b,Pixmap c,XColor* d,XColor* e,unsigned পূর্ণাঙ্ক f,unsigned পূর্ণাঙ্ক g))
SDL_X11_SYM(Cursor,XCreatePixmap,(Display* a,Drawable b,unsigned পূর্ণাঙ্ক d,unsigned পূর্ণাঙ্ক e,unsigned পূর্ণাঙ্ক f))
SDL_X11_SYM(Cursor,XCreateFontCursor,(Display* a,unsigned পূর্ণাঙ্ক b))
SDL_X11_SYM(XFontSet,XCreateFontSet,(Display* a, _Xconst ৱর্ণ* b, ৱর্ণ*** c, পূর্ণাঙ্ক* d, ৱর্ণ** e))
SDL_X11_SYM(GC,XCreateGC,(Display* a,Drawable b,unsigned long c,XGCValues* d))
SDL_X11_SYM(শূন্য,XSetFont,(Display* a,GC b,Font c))
SDL_X11_SYM(Status,XAllocColor,(Display *a, Colormap b, XColor *c))
SDL_X11_SYM(XImage*,XCreateImage,(Display* a,Visual* b,unsigned পূর্ণাঙ্ক c,পূর্ণাঙ্ক d,পূর্ণাঙ্ক e,ৱর্ণ* f,unsigned পূর্ণাঙ্ক g,unsigned পূর্ণাঙ্ক h,পূর্ণাঙ্ক i,পূর্ণাঙ্ক j))
SDL_X11_SYM(Window,XCreateWindow,(Display* a,Window b,পূর্ণাঙ্ক c,পূর্ণাঙ্ক d,unsigned পূর্ণাঙ্ক e,unsigned পূর্ণাঙ্ক f,unsigned পূর্ণাঙ্ক g,পূর্ণাঙ্ক h,unsigned পূর্ণাঙ্ক i,Visual* j,unsigned long k,XSetWindowAttributes* l))
SDL_X11_SYM(শূন্য,XCopyArea,(Display *a, Drawable b, Drawable c, GC d, পূর্ণাঙ্ক e, পূর্ণাঙ্ক f, unsigned পূর্ণাঙ্ক g, unsigned পূর্ণাঙ্ক h, পূর্ণাঙ্ক i, পূর্ণাঙ্ক j))
SDL_X11_SYM(পূর্ণাঙ্ক,XDefineCursor,(Display* a,Window b,Cursor c))
SDL_X11_SYM(পূর্ণাঙ্ক,XDeleteProperty,(Display* a,Window b,Atom c))
SDL_X11_SYM(পূর্ণাঙ্ক,XDestroyWindow,(Display* a,Window b))
SDL_X11_SYM(পূর্ণাঙ্ক,XDisplayKeycodes,(Display* a,পূর্ণাঙ্ক* b,পূর্ণাঙ্ক* c))
SDL_X11_SYM(পূর্ণাঙ্ক,XDrawRectangle,(Display* a,Drawable b,GC c,পূর্ণাঙ্ক d,পূর্ণাঙ্ক e,unsigned পূর্ণাঙ্ক f,unsigned পূর্ণাঙ্ক g))
SDL_X11_SYM(পূর্ণাঙ্ক,XFontsOfFontSet,(XFontSet a,XFontStruct ***b,ৱর্ণ ***c))
SDL_X11_SYM(পূর্ণাঙ্ক,XFillArc,(Display* a,Drawable b,GC c,পূর্ণাঙ্ক d,পূর্ণাঙ্ক e,unsigned পূর্ণাঙ্ক f,unsigned পূর্ণাঙ্ক g, পূর্ণাঙ্ক h, পূর্ণাঙ্ক i))
SDL_X11_SYM(ৱর্ণ*,XDisplayName,(_Xconst ৱর্ণ* a))
SDL_X11_SYM(পূর্ণাঙ্ক,XDrawString,(Display* a,Drawable b,GC c,পূর্ণাঙ্ক d,পূর্ণাঙ্ক e,_Xconst ৱর্ণ* f,পূর্ণাঙ্ক g))
SDL_X11_SYM(পূর্ণাঙ্ক,XEventsQueued,(Display* a,পূর্ণাঙ্ক b))
SDL_X11_SYM(পূর্ণাঙ্ক,XFillRectangle,(Display* a,Drawable b,GC c,পূর্ণাঙ্ক d,পূর্ণাঙ্ক e,unsigned পূর্ণাঙ্ক f,unsigned পূর্ণাঙ্ক g))
SDL_X11_SYM(Bool,XFilterEvent,(XEvent *event,Window w))
SDL_X11_SYM(পূর্ণাঙ্ক,XFlush,(Display* a))
SDL_X11_SYM(পূর্ণাঙ্ক,XFree,(শূন্য*a))
SDL_X11_SYM(পূর্ণাঙ্ক,XFreeCursor,(Display* a,Cursor b))
SDL_X11_SYM(শূন্য,XFreeFontSet,(Display* a, XFontSet b))
SDL_X11_SYM(পূর্ণাঙ্ক,XFreeGC,(Display* a,GC b))
SDL_X11_SYM(পূর্ণাঙ্ক,XFreeFont,(Display* a, XFontStruct* b))
SDL_X11_SYM(পূর্ণাঙ্ক,XFreeModifiermap,(XModifierKeymap* a))
SDL_X11_SYM(পূর্ণাঙ্ক,XFreePixmap,(Display* a,Pixmap b))
SDL_X11_SYM(পূর্ণাঙ্ক,XFreeColormap,(Display* a,Colormap b))
SDL_X11_SYM(শূন্য,XFreeStringList,(ৱর্ণ** a))
SDL_X11_SYM(ৱর্ণ*,XGetAtomName,(Display *a,Atom b))
SDL_X11_SYM(পূর্ণাঙ্ক,XGet_প্ৰবেশ_Focus,(Display *a,Window *b,পূর্ণাঙ্ক *c))
SDL_X11_SYM(চাবি_Sym*,XGetKeyboardMapping,(Display *a, চাবি_Code_2 b, পূর্ণাঙ্ক c, পূর্ণাঙ্ক *d))
SDL_X11_SYM(পূর্ণাঙ্ক,XGetErrorDatabaseText,(Display* a,_Xconst ৱর্ণ* b,_Xconst ৱর্ণ* c,_Xconst ৱর্ণ* d,ৱর্ণ* e,পূর্ণাঙ্ক f))
SDL_X11_SYM(XModifierKeymap*,XGetModifierMapping,(Display* a))
SDL_X11_SYM(পূর্ণাঙ্ক,XGetPointerControl,(Display* a,পূর্ণাঙ্ক* b,পূর্ণাঙ্ক* c,পূর্ণাঙ্ক* d))
SDL_X11_SYM(Window,XGetSelectionOwner,(Display* a,Atom b))
SDL_X11_SYM(XVisualInfo*,XGetVisualInfo,(Display* a,long b,XVisualInfo* c,পূর্ণাঙ্ক* d))
SDL_X11_SYM(Status,XGetWindowAttributes,(Display* a,Window b,XWindowAttributes* c))
SDL_X11_SYM(পূর্ণাঙ্ক,XGetWindowProperty,(Display* a,Window b,Atom c,long d,long e,Bool f,Atom g,Atom* h,পূর্ণাঙ্ক* i,unsigned long* j,unsigned long *k,unsigned ৱর্ণ **l))
SDL_X11_SYM(XWMHints*,XGetWMHints,(Display* a,Window b))
SDL_X11_SYM(Status,XGetWMNormalHints,(Display *a,Window b, XSizeHints *c, long *d))
SDL_X11_SYM(পূর্ণাঙ্ক,XIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(পূর্ণাঙ্ক,XGrabKeyboard,(Display* a,Window b,Bool c,পূর্ণাঙ্ক d,পূর্ণাঙ্ক e,Time f))
SDL_X11_SYM(পূর্ণাঙ্ক,XGrabPointer,(Display* a,Window b,Bool c,unsigned পূর্ণাঙ্ক d,পূর্ণাঙ্ক e,পূর্ণাঙ্ক f,Window g,Cursor h,Time i))
SDL_X11_SYM(পূর্ণাঙ্ক,XGrabServer,(Display* a))
SDL_X11_SYM(Status,XIconifyWindow,(Display* a,Window b,পূর্ণাঙ্ক c))
SDL_X11_SYM(চাবি_Code_2,XKeysymToKeycode,(Display* a,চাবি_Sym b))
SDL_X11_SYM(ৱর্ণ*,XKeysymToString,(চাবি_Sym a))
SDL_X11_SYM(পূর্ণাঙ্ক,XInstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(Atom,XInternAtom,(Display* a,_Xconst ৱর্ণ* b,Bool c))
SDL_X11_SYM(XPixmap_Format_মানসমূহ*,XListPixmapFormats,(Display* a,পূর্ণাঙ্ক* b))
SDL_X11_SYM(XFontStruct*,XLoadQueryFont,(Display* a,_Xconst ৱর্ণ* b))
SDL_X11_SYM(চাবি_Sym,XLookupKeysym,(XKeyEvent* a,পূর্ণাঙ্ক b))
SDL_X11_SYM(পূর্ণাঙ্ক,XLookupString,(XKeyEvent* a,ৱর্ণ* b,পূর্ণাঙ্ক c,চাবি_Sym* d,XComposeStatus* e))
SDL_X11_SYM(পূর্ণাঙ্ক,XMapRaised,(Display* a,Window b))
SDL_X11_SYM(Status,XMatchVisualInfo,(Display* a,পূর্ণাঙ্ক b,পূর্ণাঙ্ক c,পূর্ণাঙ্ক d,XVisualInfo* e))
SDL_X11_SYM(পূর্ণাঙ্ক,XMissingExtension,(Display* a,_Xconst ৱর্ণ* b))
SDL_X11_SYM(পূর্ণাঙ্ক,XMoveWindow,(Display* a,Window b,পূর্ণাঙ্ক c,পূর্ণাঙ্ক d))
SDL_X11_SYM(Display*,XOpenDisplay,(_Xconst ৱর্ণ* a))
SDL_X11_SYM(Status,XInitThreads,(শূন্য))
SDL_X11_SYM(পূর্ণাঙ্ক,XPeekEvent,(Display* a,XEvent* b))
SDL_X11_SYM(পূর্ণাঙ্ক,XPending,(Display* a))
SDL_X11_SYM(XImage*,XGetImage,(Display* a,Drawable b,পূর্ণাঙ্ক c, পূর্ণাঙ্ক d,unsigned পূর্ণাঙ্ক e,unsigned পূর্ণাঙ্ক f,unsigned long g,পূর্ণাঙ্ক h))
SDL_X11_SYM(পূর্ণাঙ্ক,XPutImage,(Display* a,Drawable b,GC c,XImage* d,পূর্ণাঙ্ক e,পূর্ণাঙ্ক f,পূর্ণাঙ্ক g,পূর্ণাঙ্ক h,unsigned পূর্ণাঙ্ক i,unsigned পূর্ণাঙ্ক j))
SDL_X11_SYM(পূর্ণাঙ্ক,XQueryKeymap,(Display* a,ৱর্ণ b[32]))
SDL_X11_SYM(Bool,XQueryPointer,(Display* a,Window b,Window* c,Window* d,পূর্ণাঙ্ক* e,পূর্ণাঙ্ক* f,পূর্ণাঙ্ক* g,পূর্ণাঙ্ক* h,unsigned পূর্ণাঙ্ক* i))
SDL_X11_SYM(পূর্ণাঙ্ক,XRaiseWindow,(Display* a,Window b))
SDL_X11_SYM(পূর্ণাঙ্ক,XReparentWindow,(Display* a,Window b,Window c,পূর্ণাঙ্ক d,পূর্ণাঙ্ক e))
SDL_X11_SYM(পূর্ণাঙ্ক,XResetScreenSaver,(Display* a))
SDL_X11_SYM(পূর্ণাঙ্ক,XResizeWindow,(Display* a,Window b,unsigned পূর্ণাঙ্ক c,unsigned পূর্ণাঙ্ক d))
SDL_X11_SYM(পূর্ণাঙ্ক,XScreen_সংখ্যা_Of_Screen,(Screen* a))
SDL_X11_SYM(পূর্ণাঙ্ক,XSelect_প্ৰবেশ,(Display* a,Window b,long c))
SDL_X11_SYM(Status,XSendEvent,(Display* a,Window b,Bool c,long d,XEvent* e))
SDL_X11_SYM(XErrorHandler,XSetErrorHandler,(XErrorHandler a))
SDL_X11_SYM(পূর্ণাঙ্ক,XSetForeground,(Display* a,GC b,unsigned long c))
SDL_X11_SYM(XIOErrorHandler,XSetIOErrorHandler,(XIOErrorHandler a))
SDL_X11_SYM(পূর্ণাঙ্ক,XSet_প্ৰবেশ_Focus,(Display *a,Window b,পূর্ণাঙ্ক c,Time d))
SDL_X11_SYM(পূর্ণাঙ্ক,XSetSelectionOwner,(Display* a,Atom b,Window c,Time d))
SDL_X11_SYM(পূর্ণাঙ্ক,XSetTransientForHint,(Display* a,Window b,Window c))
SDL_X11_SYM(শূন্য,XSetTextProperty,(Display* a,Window b,XTextProperty* c,Atom d))
SDL_X11_SYM(পূর্ণাঙ্ক,XSetWindowBackground,(Display* a,Window b,unsigned long c))
SDL_X11_SYM(শূন্য,XSetWMHints,(Display* a,Window b,XWMHints* c))
SDL_X11_SYM(শূন্য,XSetWMNormalHints,(Display* a,Window b,XSizeHints* c))
SDL_X11_SYM(শূন্য,XSetWMProperties,(Display* a,Window b,XTextProperty* c,XTextProperty* d,ৱর্ণ** e,পূর্ণাঙ্ক f,XSizeHints* g,XWMHints* h,XClassHint* i))
SDL_X11_SYM(Status,XSetWMProtocols,(Display* a,Window b,Atom* c,পূর্ণাঙ্ক d))
SDL_X11_SYM(পূর্ণাঙ্ক,XStoreColors,(Display* a,Colormap b,XColor* c,পূর্ণাঙ্ক d))
SDL_X11_SYM(পূর্ণাঙ্ক,XStoreName,(Display* a,Window b,_Xconst ৱর্ণ* c))
SDL_X11_SYM(Status,XStringListToTextProperty,(ৱর্ণ** a,পূর্ণাঙ্ক b,XTextProperty* c))
SDL_X11_SYM(পূর্ণাঙ্ক,XSync,(Display* a,Bool b))
SDL_X11_SYM(পূর্ণাঙ্ক,XTextExtents,(XFontStruct* a,_Xconst ৱর্ণ* b,পূর্ণাঙ্ক c,পূর্ণাঙ্ক* d,পূর্ণাঙ্ক* e,পূর্ণাঙ্ক* f,XCharStruct* g))
SDL_X11_SYM(Bool,XTranslateCoordinates,(Display *a,Window b,Window c,পূর্ণাঙ্ক d,পূর্ণাঙ্ক e,পূর্ণাঙ্ক* f,পূর্ণাঙ্ক* g,Window* h))
SDL_X11_SYM(পূর্ণাঙ্ক,XUndefineCursor,(Display* a,Window b))
SDL_X11_SYM(পূর্ণাঙ্ক,XUngrabKeyboard,(Display* a,Time b))
SDL_X11_SYM(পূর্ণাঙ্ক,XUngrabPointer,(Display* a,Time b))
SDL_X11_SYM(পূর্ণাঙ্ক,XUngrabServer,(Display* a))
SDL_X11_SYM(পূর্ণাঙ্ক,XUninstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(পূর্ণাঙ্ক,XUnloadFont,(Display* a,Font b))
SDL_X11_SYM(পূর্ণাঙ্ক,XWarpPointer,(Display* a,Window b,Window c,পূর্ণাঙ্ক d,পূর্ণাঙ্ক e,unsigned পূর্ণাঙ্ক f,unsigned পূর্ণাঙ্ক g,পূর্ণাঙ্ক h,পূর্ণাঙ্ক i))
SDL_X11_SYM(পূর্ণাঙ্ক,XWindowEvent,(Display* a,Window b,long c,XEvent* d))
SDL_X11_SYM(Status,XWithdrawWindow,(Display* a,Window b,পূর্ণাঙ্ক c))
SDL_X11_SYM(VisualID,XVisualIDFromVisual,(Visual* a))
SDL_X11_SYM(ৱর্ণ*,XGetDefault,(Display* a,_Xconst ৱর্ণ* b, _Xconst ৱর্ণ* c))
SDL_X11_SYM(Bool,XQueryExtension,(Display* a,_Xconst ৱর্ণ* b,পূর্ণাঙ্ক* c,পূর্ণাঙ্ক* d,পূর্ণাঙ্ক* e))
SDL_X11_SYM(ৱর্ণ *,XDisplayString,(Display* a))
SDL_X11_SYM(পূর্ণাঙ্ক,XGetErrorText,(Display* a,পূর্ণাঙ্ক b,ৱর্ণ* c,পূর্ণাঙ্ক d))
SDL_X11_SYM(শূন্য,_XEatData,(Display* a,unsigned long b))
SDL_X11_SYM(শূন্য,_XFlush,(Display* a))
SDL_X11_SYM(শূন্য,_XFlushGCCache,(Display* a,GC b))
SDL_X11_SYM(পূর্ণাঙ্ক,_XRead,(Display* a,ৱর্ণ* b,long c))
SDL_X11_SYM(শূন্য,_XReadPad,(Display* a,ৱর্ণ* b,long c))
SDL_X11_SYM(শূন্য,_XSend,(Display* a,_Xconst ৱর্ণ* b,long c))
SDL_X11_SYM(Status,_XReply,(Display* a,xReply* b,পূর্ণাঙ্ক c,Bool d))
SDL_X11_SYM(unsigned long,_XSetLastRequestRead,(Display* a,xGenericReply* b))
SDL_X11_SYM(SDL_X11_XSynchronizeRetType,XSynchronize,(Display* a,Bool b))
SDL_X11_SYM(SDL_X11_XESetWireToEventRetType,XESetWireToEvent,(Display* a,পূর্ণাঙ্ক b,SDL_X11_XESetWireToEventRetType c))
SDL_X11_SYM(SDL_X11_XESetEventToWireRetType,XESetEventToWire,(Display* a,পূর্ণাঙ্ক b,SDL_X11_XESetEventToWireRetType c))
SDL_X11_SYM(শূন্য,XRefreshKeyboardMapping,(XMappingEvent *a))
SDL_X11_SYM(পূর্ণাঙ্ক,XQuery_বৃক্ষ,(Display* a,Window b,Window* c,Window* d,Window** e,unsigned পূর্ণাঙ্ক* f))
SDL_X11_SYM(Bool,XSupportsLocale,(শূন্য))
SDL_X11_SYM(Status,XmbTextListToTextProperty,(Display* a,ৱর্ণ** b,পূর্ণাঙ্ক c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(Region,XCreateRegion,(শূন্য))
SDL_X11_SYM(পূর্ণাঙ্ক,XUnionRectWithRegion,(XRectangle *a, Region b, Region c))
SDL_X11_SYM(শূন্য,XDestroyRegion,(Region))
SDL_X11_SYM(শূন্য,XrmInitialize,(শূন্য))
SDL_X11_SYM(ৱর্ণ*,XResourceManagerString,(Display *display))
SDL_X11_SYM(XrmDatabase,XrmGetStringDatabase,(ৱর্ণ *data))
SDL_X11_SYM(শূন্য,XrmDestroyDatabase,(XrmDatabase db))
SDL_X11_SYM(Bool,XrmGetResource,(XrmDatabase db, ৱর্ণ* str_name, ৱর্ণ* str_class, ৱর্ণ **str_type_return, Xrm_মান *))
SDL_X11_SYM(পূর্ণাঙ্ক,XGetPointerMapping,(Display *a, unsigned ৱর্ণ *b, unsigned পূর্ণাঙ্ক c))

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
SDL_X11_MODULE(XFIXES)
SDL_X11_SYM(PointerBarrier, XFixesCreatePointerBarrier, (Display* a, Window b, পূর্ণাঙ্ক c, পূর্ণাঙ্ক d, পূর্ণাঙ্ক e, পূর্ণাঙ্ক f, পূর্ণাঙ্ক g, পূর্ণাঙ্ক h, পূর্ণাঙ্ক *i))
SDL_X11_SYM(শূন্য, XFixesDestroyPointerBarrier, (Display* a, PointerBarrier b))
SDL_X11_SYM(পূর্ণাঙ্ক, XIBarrierReleasePointer,(Display* a,  পূর্ণাঙ্ক b, PointerBarrier c, BarrierEventID d)) // this is actually Xinput2
SDL_X11_SYM(Status, XFixesQueryVersion,(Display* a, পূর্ণাঙ্ক* b, পূর্ণাঙ্ক* c))
SDL_X11_SYM(Status, XFixes_Select_Selection_প্ৰবেশ, (Display* a, Window b, Atom c, unsigned long d))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
SDL_X11_MODULE(XSYNC)
SDL_X11_SYM(Status, XSyncQueryExtension, (Display* a, পূর্ণাঙ্ক* b, পূর্ণাঙ্ক* c))
SDL_X11_SYM(Status, XSyncInitialize, (Display* a, পূর্ণাঙ্ক* b, পূর্ণাঙ্ক* c))
SDL_X11_SYM(XSyncCounter, XSyncCreateCounter, (Display* a, XSync_মান b))
SDL_X11_SYM(Status, XSyncDestroyCounter, (Display* a, XSyncCounter b))
SDL_X11_SYM(Status, XSyncSetCounter, (Display* a, XSyncCounter b, XSync_মান c))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XTEST
SDL_X11_MODULE(XTEST)
SDL_X11_SYM(Status, XTestQueryExtension, (Display* a, পূর্ণাঙ্ক* b, পূর্ণাঙ্ক* c))
SDL_X11_SYM(পূর্ণাঙ্ক, XTestFakeMotionEvent, (Display* a, পূর্ণাঙ্ক b, পূর্ণাঙ্ক c, পূর্ণাঙ্ক d, unsigned long e))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
SDL_X11_SYM(Bool,XGetEventData,(Display* a,XGenericEventCookie* b))
SDL_X11_SYM(শূন্য,XFreeEventData,(Display* a,XGenericEventCookie* b))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
SDL_X11_SYM(Bool,XkbQueryExtension,(Display* a,পূর্ণাঙ্ক * b,পূর্ণাঙ্ক * c,পূর্ণাঙ্ক * d,পূর্ণাঙ্ক * e, পূর্ণাঙ্ক *f))
SDL_X11_SYM(চাবি_Sym,XkbKeycodeToKeysym,(Display* a, চাবি_Code_2 b, unsigned পূর্ণাঙ্ক c, unsigned পূর্ণাঙ্ক d))
SDL_X11_SYM(Bool,XkbSelectEvents,(Display* a, unsigned পূর্ণাঙ্ক b, unsigned পূর্ণাঙ্ক c, unsigned long d))
SDL_X11_SYM(Bool,XkbSelectEventDetails,(Display* a, unsigned পূর্ণাঙ্ক b, unsigned পূর্ণাঙ্ক c, unsigned long d, unsigned long e))
SDL_X11_SYM(Status,XkbGetNames,(Display *a, unsigned পূর্ণাঙ্ক b, XkbDescPtr c))
SDL_X11_SYM(Status,XkbGetState,(Display* a,unsigned পূর্ণাঙ্ক b,XkbStatePtr c))
SDL_X11_SYM(Status,XkbGetUpdatedMap,(Display* a,unsigned পূর্ণাঙ্ক b,XkbDescPtr c))
SDL_X11_SYM(XkbDescPtr,XkbGetMap,(Display* a,unsigned পূর্ণাঙ্ক b,unsigned পূর্ণাঙ্ক c))
SDL_X11_SYM(শূন্য,XkbFreeClientMap,(XkbDescPtr a,unsigned পূর্ণাঙ্ক b, Bool c))
SDL_X11_SYM(শূন্য,XkbFreeKeyboard,(XkbDescPtr a,unsigned পূর্ণাঙ্ক b, Bool c))
SDL_X11_SYM(Status,XkbRefreshKeyboardMapping,(XkbMapNotifyEvent *a))
SDL_X11_SYM(Bool,XkbSetDetectableAutoRepeat,(Display* a, Bool b, Bool* c))
#endif

#ifdef X_HAVE_UTF8_STRING
SDL_X11_MODULE(UTF8)
SDL_X11_SYM(পূর্ণাঙ্ক,Xutf8TextListToTextProperty,(Display* a,ৱর্ণ** b,পূর্ণাঙ্ক c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(পূর্ণাঙ্ক,Xutf8LookupString,(XIC a,XKeyPressedEvent* b,ৱর্ণ* c,পূর্ণাঙ্ক d,চাবি_Sym* e,Status* f))
SDL_X11_SYM(XIC,XCreateIC,(XIM,...))
SDL_X11_SYM(শূন্য,XDestroyIC,(XIC a))
SDL_X11_SYM(ৱর্ণ*,XGetICValues,(XIC,...))
SDL_X11_SYM(ৱর্ণ*,XSetICValues,(XIC,...))
SDL_X11_SYM(XVaNestedList,XVaCreateNestedList,(পূর্ণাঙ্ক, ...))
SDL_X11_SYM(শূন্য,XSetICFocus,(XIC a))
SDL_X11_SYM(শূন্য,XUnsetICFocus,(XIC a))
SDL_X11_SYM(XIM,XOpenIM,(Display* a,সংরচনা _XrmHashBucketRec* b,ৱর্ণ* c,ৱর্ণ* d))
SDL_X11_SYM(Status,XCloseIM,(XIM a))
SDL_X11_SYM(ৱর্ণ*, XSetIMValues,(XIM,...))
SDL_X11_SYM(Bool,XRegisterIMInstantiateCallback,(Display*,সংরচনা _XrmHashBucketRec*,ৱর্ণ*,ৱর্ণ*,XIDProc,XPointer))
SDL_X11_SYM(Bool,XUnregisterIMInstantiateCallback,(Display*,সংরচনা _XrmHashBucketRec*,ৱর্ণ*,ৱর্ণ*,XIDProc,XPointer))
SDL_X11_SYM(শূন্য,Xutf8DrawString,(Display *a, Drawable b, XFontSet c, GC d, পূর্ণাঙ্ক e, পূর্ণাঙ্ক f, _Xconst ৱর্ণ *g, পূর্ণাঙ্ক h))
SDL_X11_SYM(পূর্ণাঙ্ক,Xutf8TextExtents,(XFontSet a, _Xconst ৱর্ণ* b, পূর্ণাঙ্ক c, XRectangle* d, XRectangle* e))
SDL_X11_SYM(ৱর্ণ*,XSetLocaleModifiers,(ধ্রুৱ ৱর্ণ *a))
SDL_X11_SYM(ৱর্ণ*,Xutf8ResetIC,(XIC a))
SDL_X11_SYM(XFontSetExtents*,XExtentsOfFontSet,(XFontSet a))
SDL_X11_SYM(Bool,XContextDependentDrawing,(XFontSet a))
#endif


#ifndef NO_SHARED_MEMORY
SDL_X11_MODULE(SHM)
SDL_X11_SYM(Status,XShmAttach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmDetach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmPutImage,(Display* a,Drawable b,GC c,XImage* d,পূর্ণাঙ্ক e,পূর্ণাঙ্ক f,পূর্ণাঙ্ক g,পূর্ণাঙ্ক h,unsigned পূর্ণাঙ্ক i,unsigned পূর্ণাঙ্ক j,Bool k))
SDL_X11_SYM(Status,XShmGetImage,(Display* a,Drawable b,XImage *c,পূর্ণাঙ্ক d, পূর্ণাঙ্ক e, unsigned long f))
SDL_X11_SYM(XImage*,XShmCreateImage,(Display* a,Visual* b,unsigned পূর্ণাঙ্ক c,পূর্ণাঙ্ক d,ৱর্ণ* e,XShmSegmentInfo* f,unsigned পূর্ণাঙ্ক g,unsigned পূর্ণাঙ্ক h))
SDL_X11_SYM(Pixmap,XShmCreatePixmap,(Display *a,Drawable b,ৱর্ণ* c,XShmSegmentInfo* d, unsigned পূর্ণাঙ্ক e, unsigned পূর্ণাঙ্ক f, unsigned পূর্ণাঙ্ক g))
SDL_X11_SYM(Bool,XShmQueryExtension,(Display* a))
SDL_X11_SYM(Status,XShmQueryVersion,(Display* a, পূর্ণাঙ্ক *b, পূর্ণাঙ্ক *c, Bool *d))
SDL_X11_SYM(পূর্ণাঙ্ক,XShmPixmapFormat,(Display* a))
#endif

/*
 * Not required...these only exist in code in headers on some 64-bit platforms,
 *  and are removed via macros elsewhere, so it's safe for them to be missing.
 */
#ifdef LONG64
SDL_X11_MODULE(IO_32BIT)
SDL_X11_SYM(পূর্ণাঙ্ক,_XData32,(Display *dpy,পঞ্জিকা _Xconst long *data,unsigned len))
SDL_X11_SYM(শূন্য,_XRead32,(Display *dpy,পঞ্জিকা long *data,long len))
#endif

/*
 * These only show up on some variants of Unix.
 */
#ifdef SDL_PLATFORM_OSF
SDL_X11_MODULE(OSF_ENTRY_POINTS)
SDL_X11_SYM(শূন্য,_SmtBufferOverflow,(Display *dpy,পঞ্জিকা smtDisplayPtr p))
SDL_X11_SYM(শূন্য,_SmtIpError,(Display *dpy,পঞ্জিকা smtDisplayPtr p,পূর্ণাঙ্ক i))
SDL_X11_SYM(পূর্ণাঙ্ক,ipAllocateData,(ChannelPtr a,IPCard b,IPDataPtr * c))
SDL_X11_SYM(পূর্ণাঙ্ক,ipUnallocateAndSendData,(ChannelPtr a,IPCard b))
#endif

// XCursor support
#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
SDL_X11_MODULE(XCURSOR)
SDL_X11_SYM(XcursorImage*,XcursorImageCreate,(পূর্ণাঙ্ক a,পূর্ণাঙ্ক b))
SDL_X11_SYM(XcursorImages*,XcursorImagesCreate,(পূর্ণাঙ্ক a))
SDL_X11_SYM(শূন্য,XcursorImageDestroy,(XcursorImage *a))
SDL_X11_SYM(শূন্য,XcursorImagesDestroy,(XcursorImages *a))
SDL_X11_SYM(Cursor,XcursorImageLoadCursor,(Display *a,ধ্রুৱ XcursorImage *b))
SDL_X11_SYM(Cursor,XcursorImagesLoadCursor,(Display *a,ধ্রুৱ XcursorImages *b))
SDL_X11_SYM(Cursor,XcursorLibraryLoadCursor,(Display *a, ধ্রুৱ ৱর্ণ *b))
#endif

// Xdbe support
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
SDL_X11_MODULE(XDBE)
SDL_X11_SYM(Status,XdbeQueryExtension,(Display *dpy,পূর্ণাঙ্ক *major_version_return,পূর্ণাঙ্ক *minor_version_return))
SDL_X11_SYM(XdbeBackBuffer,XdbeAllocateBackBufferName,(Display *dpy,Window window,XdbeSwapAction swap_action))
SDL_X11_SYM(Status,XdbeDeallocateBackBufferName,(Display *dpy,XdbeBackBuffer buffer))
SDL_X11_SYM(Status,XdbeSwapBuffers,(Display *dpy,XdbeSwapInfo *swap_info,পূর্ণাঙ্ক অঙ্ক_windows))
SDL_X11_SYM(Status,XdbeBeginIdiom,(Display *dpy))
SDL_X11_SYM(Status,XdbeEndIdiom,(Display *dpy))
SDL_X11_SYM(XdbeScreenVisualInfo*,XdbeGetVisualInfo,(Display *dpy,Drawable *screen_specifiers,পূর্ণাঙ্ক *অঙ্ক_screens))
SDL_X11_SYM(শূন্য,XdbeFreeVisualInfo,(XdbeScreenVisualInfo *visual_info))
SDL_X11_SYM(XdbeBackBufferAttributes*,XdbeGetBackBufferAttributes,(Display *dpy,XdbeBackBuffer buffer))
#endif

// XInput2 support for multiple mice, tablets, etc.
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
SDL_X11_MODULE(XINPUT2)
SDL_X11_SYM(XIDeviceInfo*,XIQueryDevice,(Display *a,পূর্ণাঙ্ক b,পূর্ণাঙ্ক *c))
SDL_X11_SYM(শূন্য,XIFreeDeviceInfo,(XIDeviceInfo *a))
SDL_X11_SYM(পূর্ণাঙ্ক,XISelectEvents,(Display *a,Window b,XIEventMask *c,পূর্ণাঙ্ক d))
SDL_X11_SYM(পূর্ণাঙ্ক,XIGrabTouchBegin,(Display *a,পূর্ণাঙ্ক b,Window c,পূর্ণাঙ্ক d,XIEventMask *e,পূর্ণাঙ্ক f,XIGrabModifiers *g))
SDL_X11_SYM(পূর্ণাঙ্ক,XIUngrabTouchBegin, (Display *a,পূর্ণাঙ্ক b,Window c, পূর্ণাঙ্ক d,XIGrabModifiers *e))
SDL_X11_SYM(Status,XIQueryVersion,(Display *a,পূর্ণাঙ্ক *b,পূর্ণাঙ্ক *c))
SDL_X11_SYM(XIEventMask*,XIGetSelectedEvents,(Display *a,Window b,পূর্ণাঙ্ক *c))
SDL_X11_SYM(Bool,XIGetClientPointer,(Display *a,Window b,পূর্ণাঙ্ক *c))
SDL_X11_SYM(Bool,XIWarpPointer,(Display *a,পূর্ণাঙ্ক b,Window c,Window d,দ্ৱিগুণ e,দ্ৱিগুণ f,পূর্ণাঙ্ক g,পূর্ণাঙ্ক h,দ্ৱিগুণ i,দ্ৱিগুণ j))
SDL_X11_SYM(Status,XIGetProperty,(Display *a,পূর্ণাঙ্ক b,Atom c,long d,long e,Bool f, Atom g, Atom *h, পূর্ণাঙ্ক *i, unsigned long *j, unsigned long *k, unsigned ৱর্ণ **l))
#endif

// XRandR support
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
SDL_X11_MODULE(XRANDR)
SDL_X11_SYM(Status,XRRQueryVersion,(Display *dpy,পূর্ণাঙ্ক *major_versionp,পূর্ণাঙ্ক *minor_versionp))
SDL_X11_SYM(Bool,XRRQueryExtension,(Display *dpy,পূর্ণাঙ্ক *event_base_return,পূর্ণাঙ্ক *error_base_return))
SDL_X11_SYM(XRRScreenConfiguration *,XRRGetScreenInfo,(Display *dpy,Drawable draw))
SDL_X11_SYM(SizeID,XRRConfigCurrentConfiguration,(XRRScreenConfiguration *config,Rotation *rotation))
SDL_X11_SYM(short,XRRConfigCurrentRate,(XRRScreenConfiguration *config))
SDL_X11_SYM(short *,XRRConfigRates,(XRRScreenConfiguration *config,পূর্ণাঙ্ক sizeID,পূর্ণাঙ্ক *nrates))
SDL_X11_SYM(XRRScreenSize *,XRRConfigSizes,(XRRScreenConfiguration *config,পূর্ণাঙ্ক *nsizes))
SDL_X11_SYM(Status,XRRSetScreenConfigAndRate,(Display *dpy,XRRScreenConfiguration *config,Drawable draw,পূর্ণাঙ্ক size_index,Rotation rotation,short rate,Time timestamp))
SDL_X11_SYM(শূন্য,XRRFreeScreenConfigInfo,(XRRScreenConfiguration *config))
SDL_X11_SYM(শূন্য,XRRSetScreenSize,(Display *dpy, Window window,পূর্ণাঙ্ক width, পূর্ণাঙ্ক height,পূর্ণাঙ্ক mmWidth, পূর্ণাঙ্ক mmHeight))
SDL_X11_SYM(Status,XRRGetScreenSizeRange,(Display *dpy, Window window,পূর্ণাঙ্ক *minWidth, পূর্ণাঙ্ক *minHeight, পূর্ণাঙ্ক *maxWidth, পূর্ণাঙ্ক *maxHeight))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResources,(Display *dpy, Window window))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResourcesCurrent,(Display *dpy, Window window))
SDL_X11_SYM(শূন্য,XRRFreeScreenResources,(XRRScreenResources *resources))
SDL_X11_SYM(XRROutputInfo *,XRRGetOutputInfo,(Display *dpy, XRRScreenResources *resources, RROutput output))
SDL_X11_SYM(শূন্য,XRRFreeOutputInfo,(XRROutputInfo *outputInfo))
SDL_X11_SYM(XRRCrtcInfo *,XRRGetCrtcInfo,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc))
SDL_X11_SYM(শূন্য,XRRFreeCrtcInfo,(XRRCrtcInfo *crtcInfo))
SDL_X11_SYM(Status,XRRSetCrtcConfig,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc, Time timestamp, পূর্ণাঙ্ক x, পূর্ণাঙ্ক y, RRMode mode, Rotation rotation, RROutput *outputs, পূর্ণাঙ্ক noutputs))
SDL_X11_SYM(Atom*,XRRListOutputProperties,(Display *dpy, RROutput output, পূর্ণাঙ্ক *nprop))
SDL_X11_SYM(XRRPropertyInfo*,XRRQueryOutputProperty,(Display *dpy,RROutput output, Atom property))
SDL_X11_SYM(পূর্ণাঙ্ক,XRRGetOutputProperty,(Display *dpy,RROutput output, Atom property, long offset, long length, Bool _delete, Bool pending, Atom req_type, Atom *actual_type, পূর্ণাঙ্ক *actual_format, unsigned long *nitems, unsigned long *bytes_after, unsigned ৱর্ণ **prop))
SDL_X11_SYM(RROutput,XRRGetOutputPrimary,(Display *dpy,Window window))
SDL_X11_SYM(শূন্য,XRRSelect_প্ৰবেশ,(Display *dpy, Window window, পূর্ণাঙ্ক mask))
SDL_X11_SYM(Status,XRRGetCrtcTransform,(Display *dpy,RRCrtc crtc,XRRCrtcTransformAttributes **attributes))
#endif

// MIT-SCREEN-SAVER support
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
SDL_X11_MODULE(XSS)
SDL_X11_SYM(Bool,XScreenSaverQueryExtension,(Display *dpy,পূর্ণাঙ্ক *event_base,পূর্ণাঙ্ক *error_base))
SDL_X11_SYM(Status,XScreenSaverQueryVersion,(Display *dpy,পূর্ণাঙ্ক *major_versionp,পূর্ণাঙ্ক *minor_versionp))
SDL_X11_SYM(শূন্য,XScreenSaverSuspend,(Display *dpy,Bool suspend))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
SDL_X11_MODULE(XSHAPE)
SDL_X11_SYM(শূন্য,XShapeCombineMask,(Display *dpy,Window dest,পূর্ণাঙ্ক dest_kind,পূর্ণাঙ্ক x_off,পূর্ণাঙ্ক y_off,Pixmap src,পূর্ণাঙ্ক op))
SDL_X11_SYM(শূন্য,XShapeCombineRegion,(Display *a,Window b,পূর্ণাঙ্ক c,পূর্ণাঙ্ক d,পূর্ণাঙ্ক e,Region f,পূর্ণাঙ্ক g))
#endif

#undef SDL_X11_MODULE
#undef SDL_X11_SYM

/* *INDENT-ON* */ // clang-format on
