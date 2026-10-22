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
SDL_X11_SYM(XSizeHints*,XAlloc_আকার_Hints,(শূন্য))
SDL_X11_SYM(XWMHints*,XAllocWMHints,(শূন্য))
SDL_X11_SYM(XClassHint*,XAllocClassHint,(শূন্য))
SDL_X11_SYM(পূর্ণসংখ্যা,XChangePointerControl,(Display* a,Bool b,Bool c,পূর্ণসংখ্যা d,পূর্ণসংখ্যা e,পূর্ণসংখ্যা f))
SDL_X11_SYM(পূর্ণসংখ্যা,XChangeProperty,(Display* a,Window b,Atom c,Atom d,পূর্ণসংখ্যা e,পূর্ণসংখ্যা f,_Xconst unsigned অক্ষর* g,পূর্ণসংখ্যা h))
SDL_X11_SYM(Bool,XCheckIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(পূর্ণসংখ্যা,XClearWindow,(Display* a,Window b))
SDL_X11_SYM(পূর্ণসংখ্যা,XCloseDisplay,(Display* a))
SDL_X11_SYM(পূর্ণসংখ্যা,XConvertSelection,(Display* a,Atom b,Atom c,Atom d,Window e,Time f))
SDL_X11_SYM(Pixmap,XCreate_Bitmap_From_তথ্য,(Display *dpy,Drawable d,_Xconst অক্ষর *তথ্য,unsigned পূর্ণসংখ্যা width,unsigned পূর্ণসংখ্যা height))
SDL_X11_SYM(Colormap,XCreateColormap,(Display* a,Window b,Visual* c,পূর্ণসংখ্যা d))
SDL_X11_SYM(Cursor,XCreatePixmapCursor,(Display* a,Pixmap b,Pixmap c,XColor* d,XColor* e,unsigned পূর্ণসংখ্যা f,unsigned পূর্ণসংখ্যা g))
SDL_X11_SYM(Cursor,XCreatePixmap,(Display* a,Drawable b,unsigned পূর্ণসংখ্যা d,unsigned পূর্ণসংখ্যা e,unsigned পূর্ণসংখ্যা f))
SDL_X11_SYM(Cursor,XCreateFontCursor,(Display* a,unsigned পূর্ণসংখ্যা b))
SDL_X11_SYM(XFontSet,XCreateFontSet,(Display* a, _Xconst অক্ষর* b, অক্ষর*** c, পূর্ণসংখ্যা* d, অক্ষর** e))
SDL_X11_SYM(GC,XCreateGC,(Display* a,Drawable b,unsigned long c,XGCValues* d))
SDL_X11_SYM(শূন্য,XSetFont,(Display* a,GC b,Font c))
SDL_X11_SYM(Status,XAllocColor,(Display *a, Colormap b, XColor *c))
SDL_X11_SYM(XImage*,XCreateImage,(Display* a,Visual* b,unsigned পূর্ণসংখ্যা c,পূর্ণসংখ্যা d,পূর্ণসংখ্যা e,অক্ষর* f,unsigned পূর্ণসংখ্যা g,unsigned পূর্ণসংখ্যা h,পূর্ণসংখ্যা i,পূর্ণসংখ্যা j))
SDL_X11_SYM(Window,XCreateWindow,(Display* a,Window b,পূর্ণসংখ্যা c,পূর্ণসংখ্যা d,unsigned পূর্ণসংখ্যা e,unsigned পূর্ণসংখ্যা f,unsigned পূর্ণসংখ্যা g,পূর্ণসংখ্যা h,unsigned পূর্ণসংখ্যা i,Visual* j,unsigned long k,XSetWindowAttributes* l))
SDL_X11_SYM(শূন্য,XCopyArea,(Display *a, Drawable b, Drawable c, GC d, পূর্ণসংখ্যা e, পূর্ণসংখ্যা f, unsigned পূর্ণসংখ্যা g, unsigned পূর্ণসংখ্যা h, পূর্ণসংখ্যা i, পূর্ণসংখ্যা j))
SDL_X11_SYM(পূর্ণসংখ্যা,XDefineCursor,(Display* a,Window b,Cursor c))
SDL_X11_SYM(পূর্ণসংখ্যা,XDeleteProperty,(Display* a,Window b,Atom c))
SDL_X11_SYM(পূর্ণসংখ্যা,XDestroyWindow,(Display* a,Window b))
SDL_X11_SYM(পূর্ণসংখ্যা,XDisplayKeycodes,(Display* a,পূর্ণসংখ্যা* b,পূর্ণসংখ্যা* c))
SDL_X11_SYM(পূর্ণসংখ্যা,XDrawRectangle,(Display* a,Drawable b,GC c,পূর্ণসংখ্যা d,পূর্ণসংখ্যা e,unsigned পূর্ণসংখ্যা f,unsigned পূর্ণসংখ্যা g))
SDL_X11_SYM(পূর্ণসংখ্যা,XFontsOfFontSet,(XFontSet a,XFontStruct ***b,অক্ষর ***c))
SDL_X11_SYM(পূর্ণসংখ্যা,XFillArc,(Display* a,Drawable b,GC c,পূর্ণসংখ্যা d,পূর্ণসংখ্যা e,unsigned পূর্ণসংখ্যা f,unsigned পূর্ণসংখ্যা g, পূর্ণসংখ্যা h, পূর্ণসংখ্যা i))
SDL_X11_SYM(অক্ষর*,XDisplayName,(_Xconst অক্ষর* a))
SDL_X11_SYM(পূর্ণসংখ্যা,XDrawString,(Display* a,Drawable b,GC c,পূর্ণসংখ্যা d,পূর্ণসংখ্যা e,_Xconst অক্ষর* f,পূর্ণসংখ্যা g))
SDL_X11_SYM(পূর্ণসংখ্যা,XEventsQueued,(Display* a,পূর্ণসংখ্যা b))
SDL_X11_SYM(পূর্ণসংখ্যা,XFillRectangle,(Display* a,Drawable b,GC c,পূর্ণসংখ্যা d,পূর্ণসংখ্যা e,unsigned পূর্ণসংখ্যা f,unsigned পূর্ণসংখ্যা g))
SDL_X11_SYM(Bool,XFilterEvent,(XEvent *event,Window w))
SDL_X11_SYM(পূর্ণসংখ্যা,XFlush,(Display* a))
SDL_X11_SYM(পূর্ণসংখ্যা,XFree,(শূন্য*a))
SDL_X11_SYM(পূর্ণসংখ্যা,XFreeCursor,(Display* a,Cursor b))
SDL_X11_SYM(শূন্য,XFreeFontSet,(Display* a, XFontSet b))
SDL_X11_SYM(পূর্ণসংখ্যা,XFreeGC,(Display* a,GC b))
SDL_X11_SYM(পূর্ণসংখ্যা,XFreeFont,(Display* a, XFontStruct* b))
SDL_X11_SYM(পূর্ণসংখ্যা,XFreeModifiermap,(XModifierKeymap* a))
SDL_X11_SYM(পূর্ণসংখ্যা,XFreePixmap,(Display* a,Pixmap b))
SDL_X11_SYM(পূর্ণসংখ্যা,XFreeColormap,(Display* a,Colormap b))
SDL_X11_SYM(শূন্য,XFreeStringList,(অক্ষর** a))
SDL_X11_SYM(অক্ষর*,XGetAtomName,(Display *a,Atom b))
SDL_X11_SYM(পূর্ণসংখ্যা,XGet_প্রবেশ_Focus,(Display *a,Window *b,পূর্ণসংখ্যা *c))
SDL_X11_SYM(চাবি_Sym*,XGetKeyboardMapping,(Display *a, চাবি_Code_2 b, পূর্ণসংখ্যা c, পূর্ণসংখ্যা *d))
SDL_X11_SYM(পূর্ণসংখ্যা,XGetErrorDatabaseText,(Display* a,_Xconst অক্ষর* b,_Xconst অক্ষর* c,_Xconst অক্ষর* d,অক্ষর* e,পূর্ণসংখ্যা f))
SDL_X11_SYM(XModifierKeymap*,XGetModifierMapping,(Display* a))
SDL_X11_SYM(পূর্ণসংখ্যা,XGetPointerControl,(Display* a,পূর্ণসংখ্যা* b,পূর্ণসংখ্যা* c,পূর্ণসংখ্যা* d))
SDL_X11_SYM(Window,XGetSelectionOwner,(Display* a,Atom b))
SDL_X11_SYM(XVisualInfo*,XGetVisualInfo,(Display* a,long b,XVisualInfo* c,পূর্ণসংখ্যা* d))
SDL_X11_SYM(Status,XGetWindowAttributes,(Display* a,Window b,XWindowAttributes* c))
SDL_X11_SYM(পূর্ণসংখ্যা,XGetWindowProperty,(Display* a,Window b,Atom c,long d,long e,Bool f,Atom g,Atom* h,পূর্ণসংখ্যা* i,unsigned long* j,unsigned long *k,unsigned অক্ষর **l))
SDL_X11_SYM(XWMHints*,XGetWMHints,(Display* a,Window b))
SDL_X11_SYM(Status,XGetWMNormalHints,(Display *a,Window b, XSizeHints *c, long *d))
SDL_X11_SYM(পূর্ণসংখ্যা,XIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(পূর্ণসংখ্যা,XGrabKeyboard,(Display* a,Window b,Bool c,পূর্ণসংখ্যা d,পূর্ণসংখ্যা e,Time f))
SDL_X11_SYM(পূর্ণসংখ্যা,XGrabPointer,(Display* a,Window b,Bool c,unsigned পূর্ণসংখ্যা d,পূর্ণসংখ্যা e,পূর্ণসংখ্যা f,Window g,Cursor h,Time i))
SDL_X11_SYM(পূর্ণসংখ্যা,XGrabServer,(Display* a))
SDL_X11_SYM(Status,XIconifyWindow,(Display* a,Window b,পূর্ণসংখ্যা c))
SDL_X11_SYM(চাবি_Code_2,XKeysymToKeycode,(Display* a,চাবি_Sym b))
SDL_X11_SYM(অক্ষর*,XKeysymToString,(চাবি_Sym a))
SDL_X11_SYM(পূর্ণসংখ্যা,XInstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(Atom,XInternAtom,(Display* a,_Xconst অক্ষর* b,Bool c))
SDL_X11_SYM(XPixmap_Format_মানসমূহ*,XListPixmapFormats,(Display* a,পূর্ণসংখ্যা* b))
SDL_X11_SYM(XFontStruct*,XLoadQueryFont,(Display* a,_Xconst অক্ষর* b))
SDL_X11_SYM(চাবি_Sym,XLookupKeysym,(XKeyEvent* a,পূর্ণসংখ্যা b))
SDL_X11_SYM(পূর্ণসংখ্যা,XLookupString,(XKeyEvent* a,অক্ষর* b,পূর্ণসংখ্যা c,চাবি_Sym* d,XComposeStatus* e))
SDL_X11_SYM(পূর্ণসংখ্যা,XMapRaised,(Display* a,Window b))
SDL_X11_SYM(Status,XMatchVisualInfo,(Display* a,পূর্ণসংখ্যা b,পূর্ণসংখ্যা c,পূর্ণসংখ্যা d,XVisualInfo* e))
SDL_X11_SYM(পূর্ণসংখ্যা,XMissingExtension,(Display* a,_Xconst অক্ষর* b))
SDL_X11_SYM(পূর্ণসংখ্যা,XMoveWindow,(Display* a,Window b,পূর্ণসংখ্যা c,পূর্ণসংখ্যা d))
SDL_X11_SYM(Display*,XOpenDisplay,(_Xconst অক্ষর* a))
SDL_X11_SYM(Status,XInitThreads,(শূন্য))
SDL_X11_SYM(পূর্ণসংখ্যা,XPeekEvent,(Display* a,XEvent* b))
SDL_X11_SYM(পূর্ণসংখ্যা,XPending,(Display* a))
SDL_X11_SYM(XImage*,XGetImage,(Display* a,Drawable b,পূর্ণসংখ্যা c, পূর্ণসংখ্যা d,unsigned পূর্ণসংখ্যা e,unsigned পূর্ণসংখ্যা f,unsigned long g,পূর্ণসংখ্যা h))
SDL_X11_SYM(পূর্ণসংখ্যা,XPutImage,(Display* a,Drawable b,GC c,XImage* d,পূর্ণসংখ্যা e,পূর্ণসংখ্যা f,পূর্ণসংখ্যা g,পূর্ণসংখ্যা h,unsigned পূর্ণসংখ্যা i,unsigned পূর্ণসংখ্যা j))
SDL_X11_SYM(পূর্ণসংখ্যা,XQueryKeymap,(Display* a,অক্ষর b[32]))
SDL_X11_SYM(Bool,XQueryPointer,(Display* a,Window b,Window* c,Window* d,পূর্ণসংখ্যা* e,পূর্ণসংখ্যা* f,পূর্ণসংখ্যা* g,পূর্ণসংখ্যা* h,unsigned পূর্ণসংখ্যা* i))
SDL_X11_SYM(পূর্ণসংখ্যা,XRaiseWindow,(Display* a,Window b))
SDL_X11_SYM(পূর্ণসংখ্যা,XReparentWindow,(Display* a,Window b,Window c,পূর্ণসংখ্যা d,পূর্ণসংখ্যা e))
SDL_X11_SYM(পূর্ণসংখ্যা,XResetScreenSaver,(Display* a))
SDL_X11_SYM(পূর্ণসংখ্যা,XResizeWindow,(Display* a,Window b,unsigned পূর্ণসংখ্যা c,unsigned পূর্ণসংখ্যা d))
SDL_X11_SYM(পূর্ণসংখ্যা,XScreen_সংখ্যা_Of_Screen,(Screen* a))
SDL_X11_SYM(পূর্ণসংখ্যা,XSelect_প্রবেশ,(Display* a,Window b,long c))
SDL_X11_SYM(Status,XSendEvent,(Display* a,Window b,Bool c,long d,XEvent* e))
SDL_X11_SYM(XErrorHandler,XSetErrorHandler,(XErrorHandler a))
SDL_X11_SYM(পূর্ণসংখ্যা,XSetForeground,(Display* a,GC b,unsigned long c))
SDL_X11_SYM(XIOErrorHandler,XSetIOErrorHandler,(XIOErrorHandler a))
SDL_X11_SYM(পূর্ণসংখ্যা,XSet_প্রবেশ_Focus,(Display *a,Window b,পূর্ণসংখ্যা c,Time d))
SDL_X11_SYM(পূর্ণসংখ্যা,XSetSelectionOwner,(Display* a,Atom b,Window c,Time d))
SDL_X11_SYM(পূর্ণসংখ্যা,XSetTransientForHint,(Display* a,Window b,Window c))
SDL_X11_SYM(শূন্য,XSetTextProperty,(Display* a,Window b,XTextProperty* c,Atom d))
SDL_X11_SYM(পূর্ণসংখ্যা,XSetWindowBackground,(Display* a,Window b,unsigned long c))
SDL_X11_SYM(শূন্য,XSetWMHints,(Display* a,Window b,XWMHints* c))
SDL_X11_SYM(শূন্য,XSetWMNormalHints,(Display* a,Window b,XSizeHints* c))
SDL_X11_SYM(শূন্য,XSetWMProperties,(Display* a,Window b,XTextProperty* c,XTextProperty* d,অক্ষর** e,পূর্ণসংখ্যা f,XSizeHints* g,XWMHints* h,XClassHint* i))
SDL_X11_SYM(Status,XSetWMProtocols,(Display* a,Window b,Atom* c,পূর্ণসংখ্যা d))
SDL_X11_SYM(পূর্ণসংখ্যা,XStoreColors,(Display* a,Colormap b,XColor* c,পূর্ণসংখ্যা d))
SDL_X11_SYM(পূর্ণসংখ্যা,XStoreName,(Display* a,Window b,_Xconst অক্ষর* c))
SDL_X11_SYM(Status,XStringListToTextProperty,(অক্ষর** a,পূর্ণসংখ্যা b,XTextProperty* c))
SDL_X11_SYM(পূর্ণসংখ্যা,XSync,(Display* a,Bool b))
SDL_X11_SYM(পূর্ণসংখ্যা,XTextExtents,(XFontStruct* a,_Xconst অক্ষর* b,পূর্ণসংখ্যা c,পূর্ণসংখ্যা* d,পূর্ণসংখ্যা* e,পূর্ণসংখ্যা* f,XCharStruct* g))
SDL_X11_SYM(Bool,XTranslateCoordinates,(Display *a,Window b,Window c,পূর্ণসংখ্যা d,পূর্ণসংখ্যা e,পূর্ণসংখ্যা* f,পূর্ণসংখ্যা* g,Window* h))
SDL_X11_SYM(পূর্ণসংখ্যা,XUndefineCursor,(Display* a,Window b))
SDL_X11_SYM(পূর্ণসংখ্যা,XUngrabKeyboard,(Display* a,Time b))
SDL_X11_SYM(পূর্ণসংখ্যা,XUngrabPointer,(Display* a,Time b))
SDL_X11_SYM(পূর্ণসংখ্যা,XUngrabServer,(Display* a))
SDL_X11_SYM(পূর্ণসংখ্যা,XUninstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(পূর্ণসংখ্যা,XUnloadFont,(Display* a,Font b))
SDL_X11_SYM(পূর্ণসংখ্যা,XWarpPointer,(Display* a,Window b,Window c,পূর্ণসংখ্যা d,পূর্ণসংখ্যা e,unsigned পূর্ণসংখ্যা f,unsigned পূর্ণসংখ্যা g,পূর্ণসংখ্যা h,পূর্ণসংখ্যা i))
SDL_X11_SYM(পূর্ণসংখ্যা,XWindowEvent,(Display* a,Window b,long c,XEvent* d))
SDL_X11_SYM(Status,XWithdrawWindow,(Display* a,Window b,পূর্ণসংখ্যা c))
SDL_X11_SYM(VisualID,XVisualIDFromVisual,(Visual* a))
SDL_X11_SYM(অক্ষর*,XGetDefault,(Display* a,_Xconst অক্ষর* b, _Xconst অক্ষর* c))
SDL_X11_SYM(Bool,XQueryExtension,(Display* a,_Xconst অক্ষর* b,পূর্ণসংখ্যা* c,পূর্ণসংখ্যা* d,পূর্ণসংখ্যা* e))
SDL_X11_SYM(অক্ষর *,XDisplayString,(Display* a))
SDL_X11_SYM(পূর্ণসংখ্যা,XGetErrorText,(Display* a,পূর্ণসংখ্যা b,অক্ষর* c,পূর্ণসংখ্যা d))
SDL_X11_SYM(শূন্য,XEat_তথ্য,(Display* a,unsigned long b))
SDL_X11_SYM(শূন্য,_XFlush,(Display* a))
SDL_X11_SYM(শূন্য,_XFlushGCCache,(Display* a,GC b))
SDL_X11_SYM(পূর্ণসংখ্যা,_XRead,(Display* a,অক্ষর* b,long c))
SDL_X11_SYM(শূন্য,_XReadPad,(Display* a,অক্ষর* b,long c))
SDL_X11_SYM(শূন্য,_XSend,(Display* a,_Xconst অক্ষর* b,long c))
SDL_X11_SYM(Status,_XReply,(Display* a,xReply* b,পূর্ণসংখ্যা c,Bool d))
SDL_X11_SYM(unsigned long,_XSetLastRequestRead,(Display* a,xGenericReply* b))
SDL_X11_SYM(SDL_X11_XSynchronizeRetType,XSynchronize,(Display* a,Bool b))
SDL_X11_SYM(SDL_X11_XESetWireToEventRetType,XESetWireToEvent,(Display* a,পূর্ণসংখ্যা b,SDL_X11_XESetWireToEventRetType c))
SDL_X11_SYM(SDL_X11_XESetEventToWireRetType,XESetEventToWire,(Display* a,পূর্ণসংখ্যা b,SDL_X11_XESetEventToWireRetType c))
SDL_X11_SYM(শূন্য,XRefreshKeyboardMapping,(XMappingEvent *a))
SDL_X11_SYM(পূর্ণসংখ্যা,XQuery_বৃক্ষ,(Display* a,Window b,Window* c,Window* d,Window** e,unsigned পূর্ণসংখ্যা* f))
SDL_X11_SYM(Bool,XSupportsLocale,(শূন্য))
SDL_X11_SYM(Status,XmbTextListToTextProperty,(Display* a,অক্ষর** b,পূর্ণসংখ্যা c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(Region,XCreateRegion,(শূন্য))
SDL_X11_SYM(পূর্ণসংখ্যা,XUnionRectWithRegion,(XRectangle *a, Region b, Region c))
SDL_X11_SYM(শূন্য,XDestroyRegion,(Region))
SDL_X11_SYM(শূন্য,XrmInitialize,(শূন্য))
SDL_X11_SYM(অক্ষর*,XResourceManagerString,(Display *display))
SDL_X11_SYM(XrmDatabase,XrmGetStringDatabase,(অক্ষর *তথ্য))
SDL_X11_SYM(শূন্য,XrmDestroyDatabase,(XrmDatabase db))
SDL_X11_SYM(Bool,XrmGetResource,(XrmDatabase db, অক্ষর* str_name, অক্ষর* str_class, অক্ষর **str_type_return, Xrm_মান *))
SDL_X11_SYM(পূর্ণসংখ্যা,XGetPointerMapping,(Display *a, unsigned অক্ষর *b, unsigned পূর্ণসংখ্যা c))

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
SDL_X11_MODULE(XFIXES)
SDL_X11_SYM(PointerBarrier, XFixesCreatePointerBarrier, (Display* a, Window b, পূর্ণসংখ্যা c, পূর্ণসংখ্যা d, পূর্ণসংখ্যা e, পূর্ণসংখ্যা f, পূর্ণসংখ্যা g, পূর্ণসংখ্যা h, পূর্ণসংখ্যা *i))
SDL_X11_SYM(শূন্য, XFixesDestroyPointerBarrier, (Display* a, PointerBarrier b))
SDL_X11_SYM(পূর্ণসংখ্যা, XIBarrierReleasePointer,(Display* a,  পূর্ণসংখ্যা b, PointerBarrier c, BarrierEventID d)) // this is actually Xinput2
SDL_X11_SYM(Status, XFixesQueryVersion,(Display* a, পূর্ণসংখ্যা* b, পূর্ণসংখ্যা* c))
SDL_X11_SYM(Status, XFixes_Select_Selection_প্রবেশ, (Display* a, Window b, Atom c, unsigned long d))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
SDL_X11_MODULE(XSYNC)
SDL_X11_SYM(Status, XSyncQueryExtension, (Display* a, পূর্ণসংখ্যা* b, পূর্ণসংখ্যা* c))
SDL_X11_SYM(Status, XSyncInitialize, (Display* a, পূর্ণসংখ্যা* b, পূর্ণসংখ্যা* c))
SDL_X11_SYM(XSync_গণক, XSync_Create_গণক, (Display* a, XSync_মান b))
SDL_X11_SYM(Status, XSync_Destroy_গণক, (Display* a, XSync_গণক b))
SDL_X11_SYM(Status, XSync_Set_গণক, (Display* a, XSync_গণক b, XSync_মান c))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XTEST
SDL_X11_MODULE(XTEST)
SDL_X11_SYM(Status, XTestQueryExtension, (Display* a, পূর্ণসংখ্যা* b, পূর্ণসংখ্যা* c))
SDL_X11_SYM(পূর্ণসংখ্যা, XTestFakeMotionEvent, (Display* a, পূর্ণসংখ্যা b, পূর্ণসংখ্যা c, পূর্ণসংখ্যা d, unsigned long e))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
SDL_X11_SYM(Bool,XGet_Event_তথ্য,(Display* a,XGenericEventCookie* b))
SDL_X11_SYM(শূন্য,XFree_Event_তথ্য,(Display* a,XGenericEventCookie* b))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
SDL_X11_SYM(Bool,XkbQueryExtension,(Display* a,পূর্ণসংখ্যা * b,পূর্ণসংখ্যা * c,পূর্ণসংখ্যা * d,পূর্ণসংখ্যা * e, পূর্ণসংখ্যা *f))
SDL_X11_SYM(চাবি_Sym,XkbKeycodeToKeysym,(Display* a, চাবি_Code_2 b, unsigned পূর্ণসংখ্যা c, unsigned পূর্ণসংখ্যা d))
SDL_X11_SYM(Bool,XkbSelectEvents,(Display* a, unsigned পূর্ণসংখ্যা b, unsigned পূর্ণসংখ্যা c, unsigned long d))
SDL_X11_SYM(Bool,XkbSelectEventDetails,(Display* a, unsigned পূর্ণসংখ্যা b, unsigned পূর্ণসংখ্যা c, unsigned long d, unsigned long e))
SDL_X11_SYM(Status,XkbGetNames,(Display *a, unsigned পূর্ণসংখ্যা b, XkbDescPtr c))
SDL_X11_SYM(Status,XkbGetState,(Display* a,unsigned পূর্ণসংখ্যা b,XkbStatePtr c))
SDL_X11_SYM(Status,XkbGetUpdatedMap,(Display* a,unsigned পূর্ণসংখ্যা b,XkbDescPtr c))
SDL_X11_SYM(XkbDescPtr,XkbGetMap,(Display* a,unsigned পূর্ণসংখ্যা b,unsigned পূর্ণসংখ্যা c))
SDL_X11_SYM(শূন্য,XkbFreeClientMap,(XkbDescPtr a,unsigned পূর্ণসংখ্যা b, Bool c))
SDL_X11_SYM(শূন্য,XkbFreeKeyboard,(XkbDescPtr a,unsigned পূর্ণসংখ্যা b, Bool c))
SDL_X11_SYM(Status,XkbRefreshKeyboardMapping,(XkbMapNotifyEvent *a))
SDL_X11_SYM(Bool,XkbSetDetectableAutoRepeat,(Display* a, Bool b, Bool* c))
#endif

#ifdef X_HAVE_UTF8_STRING
SDL_X11_MODULE(UTF8)
SDL_X11_SYM(পূর্ণসংখ্যা,Xutf8TextListToTextProperty,(Display* a,অক্ষর** b,পূর্ণসংখ্যা c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(পূর্ণসংখ্যা,Xutf8LookupString,(XIC a,XKeyPressedEvent* b,অক্ষর* c,পূর্ণসংখ্যা d,চাবি_Sym* e,Status* f))
SDL_X11_SYM(XIC,XCreateIC,(XIM,...))
SDL_X11_SYM(শূন্য,XDestroyIC,(XIC a))
SDL_X11_SYM(অক্ষর*,XGetICValues,(XIC,...))
SDL_X11_SYM(অক্ষর*,XSetICValues,(XIC,...))
SDL_X11_SYM(XVaNestedList,XVaCreateNestedList,(পূর্ণসংখ্যা, ...))
SDL_X11_SYM(শূন্য,XSetICFocus,(XIC a))
SDL_X11_SYM(শূন্য,XUnsetICFocus,(XIC a))
SDL_X11_SYM(XIM,XOpenIM,(Display* a,কাঠামো _XrmHashBucketRec* b,অক্ষর* c,অক্ষর* d))
SDL_X11_SYM(Status,XCloseIM,(XIM a))
SDL_X11_SYM(অক্ষর*, XSetIMValues,(XIM,...))
SDL_X11_SYM(Bool,XRegisterIMInstantiateCallback,(Display*,কাঠামো _XrmHashBucketRec*,অক্ষর*,অক্ষর*,XIDProc,XPointer))
SDL_X11_SYM(Bool,XUnregisterIMInstantiateCallback,(Display*,কাঠামো _XrmHashBucketRec*,অক্ষর*,অক্ষর*,XIDProc,XPointer))
SDL_X11_SYM(শূন্য,Xutf8DrawString,(Display *a, Drawable b, XFontSet c, GC d, পূর্ণসংখ্যা e, পূর্ণসংখ্যা f, _Xconst অক্ষর *g, পূর্ণসংখ্যা h))
SDL_X11_SYM(পূর্ণসংখ্যা,Xutf8TextExtents,(XFontSet a, _Xconst অক্ষর* b, পূর্ণসংখ্যা c, XRectangle* d, XRectangle* e))
SDL_X11_SYM(অক্ষর*,XSetLocaleModifiers,(ধ্রুবক অক্ষর *a))
SDL_X11_SYM(অক্ষর*,Xutf8ResetIC,(XIC a))
SDL_X11_SYM(XFontSetExtents*,XExtentsOfFontSet,(XFontSet a))
SDL_X11_SYM(Bool,XContextDependentDrawing,(XFontSet a))
#endif


#ifndef NO_SHARED_MEMORY
SDL_X11_MODULE(SHM)
SDL_X11_SYM(Status,XShmAttach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmDetach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmPutImage,(Display* a,Drawable b,GC c,XImage* d,পূর্ণসংখ্যা e,পূর্ণসংখ্যা f,পূর্ণসংখ্যা g,পূর্ণসংখ্যা h,unsigned পূর্ণসংখ্যা i,unsigned পূর্ণসংখ্যা j,Bool k))
SDL_X11_SYM(Status,XShmGetImage,(Display* a,Drawable b,XImage *c,পূর্ণসংখ্যা d, পূর্ণসংখ্যা e, unsigned long f))
SDL_X11_SYM(XImage*,XShmCreateImage,(Display* a,Visual* b,unsigned পূর্ণসংখ্যা c,পূর্ণসংখ্যা d,অক্ষর* e,XShmSegmentInfo* f,unsigned পূর্ণসংখ্যা g,unsigned পূর্ণসংখ্যা h))
SDL_X11_SYM(Pixmap,XShmCreatePixmap,(Display *a,Drawable b,অক্ষর* c,XShmSegmentInfo* d, unsigned পূর্ণসংখ্যা e, unsigned পূর্ণসংখ্যা f, unsigned পূর্ণসংখ্যা g))
SDL_X11_SYM(Bool,XShmQueryExtension,(Display* a))
SDL_X11_SYM(Status,XShmQueryVersion,(Display* a, পূর্ণসংখ্যা *b, পূর্ণসংখ্যা *c, Bool *d))
SDL_X11_SYM(পূর্ণসংখ্যা,XShmPixmapFormat,(Display* a))
#endif

/*
 * Not required...these only exist in code in headers on some 64-bit platforms,
 *  and are removed via macros elsewhere, so it's safe for them to be missing.
 */
#ifdef LONG64
SDL_X11_MODULE(IO_32BIT)
SDL_X11_SYM(পূর্ণসংখ্যা,_XData32,(Display *dpy,নিবন্ধ _Xconst long *তথ্য,unsigned len))
SDL_X11_SYM(শূন্য,_XRead32,(Display *dpy,নিবন্ধ long *তথ্য,long len))
#endif

/*
 * These only show up on some variants of Unix.
 */
#ifdef SDL_PLATFORM_OSF
SDL_X11_MODULE(OSF_ENTRY_POINTS)
SDL_X11_SYM(শূন্য,Smt_বাফার_Overflow,(Display *dpy,নিবন্ধ smtDisplayPtr p))
SDL_X11_SYM(শূন্য,_SmtIpError,(Display *dpy,নিবন্ধ smtDisplayPtr p,পূর্ণসংখ্যা i))
SDL_X11_SYM(পূর্ণসংখ্যা,ip_Allocate_তথ্য,(ChannelPtr a,IPCard b,IPDataPtr * c))
SDL_X11_SYM(পূর্ণসংখ্যা,ip_Unallocate_And_Send_তথ্য,(ChannelPtr a,IPCard b))
#endif

// XCursor support
#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
SDL_X11_MODULE(XCURSOR)
SDL_X11_SYM(XcursorImage*,XcursorImageCreate,(পূর্ণসংখ্যা a,পূর্ণসংখ্যা b))
SDL_X11_SYM(XcursorImages*,XcursorImagesCreate,(পূর্ণসংখ্যা a))
SDL_X11_SYM(শূন্য,XcursorImageDestroy,(XcursorImage *a))
SDL_X11_SYM(শূন্য,XcursorImagesDestroy,(XcursorImages *a))
SDL_X11_SYM(Cursor,XcursorImageLoadCursor,(Display *a,ধ্রুবক XcursorImage *b))
SDL_X11_SYM(Cursor,XcursorImagesLoadCursor,(Display *a,ধ্রুবক XcursorImages *b))
SDL_X11_SYM(Cursor,XcursorLibraryLoadCursor,(Display *a, ধ্রুবক অক্ষর *b))
#endif

// Xdbe support
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
SDL_X11_MODULE(XDBE)
SDL_X11_SYM(Status,XdbeQueryExtension,(Display *dpy,পূর্ণসংখ্যা *major_version_return,পূর্ণসংখ্যা *minor_version_return))
SDL_X11_SYM(Xdbe_Back_বাফার,Xdbe_Allocate_Back_বাফার_Name,(Display *dpy,Window window,XdbeSwapAction swap_action))
SDL_X11_SYM(Status,Xdbe_Deallocate_Back_বাফার_Name,(Display *dpy,Xdbe_Back_বাফার বাফার_2))
SDL_X11_SYM(Status,XdbeSwapBuffers,(Display *dpy,XdbeSwapInfo *swap_info,পূর্ণসংখ্যা অঙ্ক_windows))
SDL_X11_SYM(Status,XdbeBeginIdiom,(Display *dpy))
SDL_X11_SYM(Status,XdbeEndIdiom,(Display *dpy))
SDL_X11_SYM(XdbeScreenVisualInfo*,XdbeGetVisualInfo,(Display *dpy,Drawable *screen_specifiers,পূর্ণসংখ্যা *অঙ্ক_screens))
SDL_X11_SYM(শূন্য,XdbeFreeVisualInfo,(XdbeScreenVisualInfo *visual_info))
SDL_X11_SYM(Xdbe_Back_বাফার_Attributes*,Xdbe_Get_Back_বাফার_Attributes,(Display *dpy,Xdbe_Back_বাফার বাফার_2))
#endif

// XInput2 support for multiple mice, tablets, etc.
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
SDL_X11_MODULE(XINPUT2)
SDL_X11_SYM(XIDeviceInfo*,XIQueryDevice,(Display *a,পূর্ণসংখ্যা b,পূর্ণসংখ্যা *c))
SDL_X11_SYM(শূন্য,XIFreeDeviceInfo,(XIDeviceInfo *a))
SDL_X11_SYM(পূর্ণসংখ্যা,XISelectEvents,(Display *a,Window b,XIEventMask *c,পূর্ণসংখ্যা d))
SDL_X11_SYM(পূর্ণসংখ্যা,XIGrabTouchBegin,(Display *a,পূর্ণসংখ্যা b,Window c,পূর্ণসংখ্যা d,XIEventMask *e,পূর্ণসংখ্যা f,XIGrabModifiers *g))
SDL_X11_SYM(পূর্ণসংখ্যা,XIUngrabTouchBegin, (Display *a,পূর্ণসংখ্যা b,Window c, পূর্ণসংখ্যা d,XIGrabModifiers *e))
SDL_X11_SYM(Status,XIQueryVersion,(Display *a,পূর্ণসংখ্যা *b,পূর্ণসংখ্যা *c))
SDL_X11_SYM(XIEventMask*,XIGetSelectedEvents,(Display *a,Window b,পূর্ণসংখ্যা *c))
SDL_X11_SYM(Bool,XIGetClientPointer,(Display *a,Window b,পূর্ণসংখ্যা *c))
SDL_X11_SYM(Bool,XIWarpPointer,(Display *a,পূর্ণসংখ্যা b,Window c,Window d,দ্বিগুণ e,দ্বিগুণ f,পূর্ণসংখ্যা g,পূর্ণসংখ্যা h,দ্বিগুণ i,দ্বিগুণ j))
SDL_X11_SYM(Status,XIGetProperty,(Display *a,পূর্ণসংখ্যা b,Atom c,long d,long e,Bool f, Atom g, Atom *h, পূর্ণসংখ্যা *i, unsigned long *j, unsigned long *k, unsigned অক্ষর **l))
#endif

// XRandR support
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
SDL_X11_MODULE(XRANDR)
SDL_X11_SYM(Status,XRRQueryVersion,(Display *dpy,পূর্ণসংখ্যা *major_versionp,পূর্ণসংখ্যা *minor_versionp))
SDL_X11_SYM(Bool,XRRQueryExtension,(Display *dpy,পূর্ণসংখ্যা *event_base_return,পূর্ণসংখ্যা *error_base_return))
SDL_X11_SYM(XRRScreenConfiguration *,XRRGetScreenInfo,(Display *dpy,Drawable draw))
SDL_X11_SYM(আকার_ID,XRRConfigCurrentConfiguration,(XRRScreenConfiguration *config,Rotation *rotation))
SDL_X11_SYM(short,XRRConfigCurrentRate,(XRRScreenConfiguration *config))
SDL_X11_SYM(short *,XRRConfigRates,(XRRScreenConfiguration *config,পূর্ণসংখ্যা আকার_ID_2,পূর্ণসংখ্যা *nrates))
SDL_X11_SYM(XRRScreen_আকার *,XRRConfigSizes,(XRRScreenConfiguration *config,পূর্ণসংখ্যা *nsizes))
SDL_X11_SYM(Status,XRRSetScreenConfigAndRate,(Display *dpy,XRRScreenConfiguration *config,Drawable draw,পূর্ণসংখ্যা আকার_সূচক,Rotation rotation,short rate,Time timestamp))
SDL_X11_SYM(শূন্য,XRRFreeScreenConfigInfo,(XRRScreenConfiguration *config))
SDL_X11_SYM(শূন্য,XRRSet_Screen_আকার,(Display *dpy, Window window,পূর্ণসংখ্যা width, পূর্ণসংখ্যা height,পূর্ণসংখ্যা mmWidth, পূর্ণসংখ্যা mmHeight))
SDL_X11_SYM(Status,XRRGet_Screen_আকার_Range,(Display *dpy, Window window,পূর্ণসংখ্যা *minWidth, পূর্ণসংখ্যা *minHeight, পূর্ণসংখ্যা *maxWidth, পূর্ণসংখ্যা *maxHeight))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResources,(Display *dpy, Window window))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResourcesCurrent,(Display *dpy, Window window))
SDL_X11_SYM(শূন্য,XRRFreeScreenResources,(XRRScreenResources *resources))
SDL_X11_SYM(XRROutputInfo *,XRRGetOutputInfo,(Display *dpy, XRRScreenResources *resources, RROutput output))
SDL_X11_SYM(শূন্য,XRRFreeOutputInfo,(XRROutputInfo *outputInfo))
SDL_X11_SYM(XRRCrtcInfo *,XRRGetCrtcInfo,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc))
SDL_X11_SYM(শূন্য,XRRFreeCrtcInfo,(XRRCrtcInfo *crtcInfo))
SDL_X11_SYM(Status,XRRSetCrtcConfig,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc, Time timestamp, পূর্ণসংখ্যা x, পূর্ণসংখ্যা y, RRMode mode, Rotation rotation, RROutput *outputs, পূর্ণসংখ্যা noutputs))
SDL_X11_SYM(Atom*,XRRListOutputProperties,(Display *dpy, RROutput output, পূর্ণসংখ্যা *nprop))
SDL_X11_SYM(XRRPropertyInfo*,XRRQueryOutputProperty,(Display *dpy,RROutput output, Atom property))
SDL_X11_SYM(পূর্ণসংখ্যা,XRRGetOutputProperty,(Display *dpy,RROutput output, Atom property, long offset, long দৈর্ঘ্য, Bool _delete, Bool pending, Atom req_type, Atom *actual_type, পূর্ণসংখ্যা *actual_format, unsigned long *nitems, unsigned long *bytes_after, unsigned অক্ষর **prop))
SDL_X11_SYM(RROutput,XRRGetOutputPrimary,(Display *dpy,Window window))
SDL_X11_SYM(শূন্য,XRRSelect_প্রবেশ,(Display *dpy, Window window, পূর্ণসংখ্যা mask))
SDL_X11_SYM(Status,XRRGetCrtcTransform,(Display *dpy,RRCrtc crtc,XRRCrtcTransformAttributes **attributes))
#endif

// MIT-SCREEN-SAVER support
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
SDL_X11_MODULE(XSS)
SDL_X11_SYM(Bool,XScreenSaverQueryExtension,(Display *dpy,পূর্ণসংখ্যা *event_base,পূর্ণসংখ্যা *error_base))
SDL_X11_SYM(Status,XScreenSaverQueryVersion,(Display *dpy,পূর্ণসংখ্যা *major_versionp,পূর্ণসংখ্যা *minor_versionp))
SDL_X11_SYM(শূন্য,XScreenSaverSuspend,(Display *dpy,Bool suspend))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
SDL_X11_MODULE(XSHAPE)
SDL_X11_SYM(শূন্য,XShapeCombineMask,(Display *dpy,Window dest,পূর্ণসংখ্যা dest_kind,পূর্ণসংখ্যা x_off,পূর্ণসংখ্যা y_off,Pixmap src,পূর্ণসংখ্যা op))
SDL_X11_SYM(শূন্য,XShapeCombineRegion,(Display *a,Window b,পূর্ণসংখ্যা c,পূর্ণসংখ্যা d,পূর্ণসংখ্যা e,Region f,পূর্ণসংখ্যা g))
#endif

#undef SDL_X11_MODULE
#undef SDL_X11_SYM

/* *INDENT-ON* */ // clang-format on
