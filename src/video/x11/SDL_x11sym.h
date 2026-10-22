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
SDL_X11_SYM(XSizeHints*,XAllocSizeHints,(void))
SDL_X11_SYM(XWMHints*,XAllocWMHints,(void))
SDL_X11_SYM(XClassHint*,XAllocClassHint,(void))
SDL_X11_SYM(ကိန်းပြည့်,XChangePointerControl,(Display* a,Bool b,Bool c,ကိန်းပြည့် d,ကိန်းပြည့် e,ကိန်းပြည့် f))
SDL_X11_SYM(ကိန်းပြည့်,XChangeProperty,(Display* a,Window b,Atom c,Atom d,ကိန်းပြည့် e,ကိန်းပြည့် f,_Xconst unsigned var_na* g,ကိန်းပြည့် h))
SDL_X11_SYM(Bool,XCheckIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(ကိန်းပြည့်,XClearWindow,(Display* a,Window b))
SDL_X11_SYM(ကိန်းပြည့်,XCloseDisplay,(Display* a))
SDL_X11_SYM(ကိန်းပြည့်,XConvertSelection,(Display* a,Atom b,Atom c,Atom d,Window e,Time f))
SDL_X11_SYM(Pixmap,XCreateBitmapFromData,(Display *dpy,Drawable d,_Xconst var_na *data,unsigned ကိန်းပြည့် width,unsigned ကိန်းပြည့် height))
SDL_X11_SYM(Colormap,XCreateColormap,(Display* a,Window b,Visual* c,ကိန်းပြည့် d))
SDL_X11_SYM(Cursor,XCreatePixmapCursor,(Display* a,Pixmap b,Pixmap c,XColor* d,XColor* e,unsigned ကိန်းပြည့် f,unsigned ကိန်းပြည့် g))
SDL_X11_SYM(Cursor,XCreatePixmap,(Display* a,Drawable b,unsigned ကိန်းပြည့် d,unsigned ကိန်းပြည့် e,unsigned ကိန်းပြည့် f))
SDL_X11_SYM(Cursor,XCreateFontCursor,(Display* a,unsigned ကိန်းပြည့် b))
SDL_X11_SYM(XFontSet,XCreateFontSet,(Display* a, _Xconst var_na* b, var_na*** c, ကိန်းပြည့်* d, var_na** e))
SDL_X11_SYM(GC,XCreateGC,(Display* a,Drawable b,unsigned long c,XGCValues* d))
SDL_X11_SYM(void,XSetFont,(Display* a,GC b,Font c))
SDL_X11_SYM(Status,XAllocColor,(Display *a, Colormap b, XColor *c))
SDL_X11_SYM(XImage*,XCreateImage,(Display* a,Visual* b,unsigned ကိန်းပြည့် c,ကိန်းပြည့် d,ကိန်းပြည့် e,var_na* f,unsigned ကိန်းပြည့် g,unsigned ကိန်းပြည့် h,ကိန်းပြည့် i,ကိန်းပြည့် j))
SDL_X11_SYM(Window,XCreateWindow,(Display* a,Window b,ကိန်းပြည့် c,ကိန်းပြည့် d,unsigned ကိန်းပြည့် e,unsigned ကိန်းပြည့် f,unsigned ကိန်းပြည့် g,ကိန်းပြည့် h,unsigned ကိန်းပြည့် i,Visual* j,unsigned long k,XSetWindowAttributes* l))
SDL_X11_SYM(void,XCopyArea,(Display *a, Drawable b, Drawable c, GC d, ကိန်းပြည့် e, ကိန်းပြည့် f, unsigned ကိန်းပြည့် g, unsigned ကိန်းပြည့် h, ကိန်းပြည့် i, ကိန်းပြည့် j))
SDL_X11_SYM(ကိန်းပြည့်,XDefineCursor,(Display* a,Window b,Cursor c))
SDL_X11_SYM(ကိန်းပြည့်,XDeleteProperty,(Display* a,Window b,Atom c))
SDL_X11_SYM(ကိန်းပြည့်,XDestroyWindow,(Display* a,Window b))
SDL_X11_SYM(ကိန်းပြည့်,XDisplayKeycodes,(Display* a,ကိန်းပြည့်* b,ကိန်းပြည့်* c))
SDL_X11_SYM(ကိန်းပြည့်,XDrawRectangle,(Display* a,Drawable b,GC c,ကိန်းပြည့် d,ကိန်းပြည့် e,unsigned ကိန်းပြည့် f,unsigned ကိန်းပြည့် g))
SDL_X11_SYM(ကိန်းပြည့်,XFontsOfFontSet,(XFontSet a,XFontStruct ***b,var_na ***c))
SDL_X11_SYM(ကိန်းပြည့်,XFillArc,(Display* a,Drawable b,GC c,ကိန်းပြည့် d,ကိန်းပြည့် e,unsigned ကိန်းပြည့် f,unsigned ကိန်းပြည့် g, ကိန်းပြည့် h, ကိန်းပြည့် i))
SDL_X11_SYM(var_na*,XDisplayName,(_Xconst var_na* a))
SDL_X11_SYM(ကိန်းပြည့်,XDrawString,(Display* a,Drawable b,GC c,ကိန်းပြည့် d,ကိန်းပြည့် e,_Xconst var_na* f,ကိန်းပြည့် g))
SDL_X11_SYM(ကိန်းပြည့်,XEventsQueued,(Display* a,ကိန်းပြည့် b))
SDL_X11_SYM(ကိန်းပြည့်,XFillRectangle,(Display* a,Drawable b,GC c,ကိန်းပြည့် d,ကိန်းပြည့် e,unsigned ကိန်းပြည့် f,unsigned ကိန်းပြည့် g))
SDL_X11_SYM(Bool,XFilterEvent,(XEvent *event,Window w))
SDL_X11_SYM(ကိန်းပြည့်,XFlush,(Display* a))
SDL_X11_SYM(ကိန်းပြည့်,XFree,(void*a))
SDL_X11_SYM(ကိန်းပြည့်,XFreeCursor,(Display* a,Cursor b))
SDL_X11_SYM(void,XFreeFontSet,(Display* a, XFontSet b))
SDL_X11_SYM(ကိန်းပြည့်,XFreeGC,(Display* a,GC b))
SDL_X11_SYM(ကိန်းပြည့်,XFreeFont,(Display* a, XFontStruct* b))
SDL_X11_SYM(ကိန်းပြည့်,XFreeModifiermap,(XModifierKeymap* a))
SDL_X11_SYM(ကိန်းပြည့်,XFreePixmap,(Display* a,Pixmap b))
SDL_X11_SYM(ကိန်းပြည့်,XFreeColormap,(Display* a,Colormap b))
SDL_X11_SYM(void,XFreeStringList,(var_na** a))
SDL_X11_SYM(var_na*,XGetAtomName,(Display *a,Atom b))
SDL_X11_SYM(ကိန်းပြည့်,XGetInputFocus,(Display *a,Window *b,ကိန်းပြည့် *c))
SDL_X11_SYM(KeySym*,XGetKeyboardMapping,(Display *a, KeyCode b, ကိန်းပြည့် c, ကိန်းပြည့် *d))
SDL_X11_SYM(ကိန်းပြည့်,XGetErrorDatabaseText,(Display* a,_Xconst var_na* b,_Xconst var_na* c,_Xconst var_na* d,var_na* e,ကိန်းပြည့် f))
SDL_X11_SYM(XModifierKeymap*,XGetModifierMapping,(Display* a))
SDL_X11_SYM(ကိန်းပြည့်,XGetPointerControl,(Display* a,ကိန်းပြည့်* b,ကိန်းပြည့်* c,ကိန်းပြည့်* d))
SDL_X11_SYM(Window,XGetSelectionOwner,(Display* a,Atom b))
SDL_X11_SYM(XVisualInfo*,XGetVisualInfo,(Display* a,long b,XVisualInfo* c,ကိန်းပြည့်* d))
SDL_X11_SYM(Status,XGetWindowAttributes,(Display* a,Window b,XWindowAttributes* c))
SDL_X11_SYM(ကိန်းပြည့်,XGetWindowProperty,(Display* a,Window b,Atom c,long d,long e,Bool f,Atom g,Atom* h,ကိန်းပြည့်* i,unsigned long* j,unsigned long *k,unsigned var_na **l))
SDL_X11_SYM(XWMHints*,XGetWMHints,(Display* a,Window b))
SDL_X11_SYM(Status,XGetWMNormalHints,(Display *a,Window b, XSizeHints *c, long *d))
SDL_X11_SYM(ကိန်းပြည့်,XIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(ကိန်းပြည့်,XGrabKeyboard,(Display* a,Window b,Bool c,ကိန်းပြည့် d,ကိန်းပြည့် e,Time f))
SDL_X11_SYM(ကိန်းပြည့်,XGrabPointer,(Display* a,Window b,Bool c,unsigned ကိန်းပြည့် d,ကိန်းပြည့် e,ကိန်းပြည့် f,Window g,Cursor h,Time i))
SDL_X11_SYM(ကိန်းပြည့်,XGrabServer,(Display* a))
SDL_X11_SYM(Status,XIconifyWindow,(Display* a,Window b,ကိန်းပြည့် c))
SDL_X11_SYM(KeyCode,XKeysymToKeycode,(Display* a,KeySym b))
SDL_X11_SYM(var_na*,XKeysymToString,(KeySym a))
SDL_X11_SYM(ကိန်းပြည့်,XInstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(Atom,XInternAtom,(Display* a,_Xconst var_na* b,Bool c))
SDL_X11_SYM(XPixmapFormatValues*,XListPixmapFormats,(Display* a,ကိန်းပြည့်* b))
SDL_X11_SYM(XFontStruct*,XLoadQueryFont,(Display* a,_Xconst var_na* b))
SDL_X11_SYM(KeySym,XLookupKeysym,(XKeyEvent* a,ကိန်းပြည့် b))
SDL_X11_SYM(ကိန်းပြည့်,XLookupString,(XKeyEvent* a,var_na* b,ကိန်းပြည့် c,KeySym* d,XComposeStatus* e))
SDL_X11_SYM(ကိန်းပြည့်,XMapRaised,(Display* a,Window b))
SDL_X11_SYM(Status,XMatchVisualInfo,(Display* a,ကိန်းပြည့် b,ကိန်းပြည့် c,ကိန်းပြည့် d,XVisualInfo* e))
SDL_X11_SYM(ကိန်းပြည့်,XMissingExtension,(Display* a,_Xconst var_na* b))
SDL_X11_SYM(ကိန်းပြည့်,XMoveWindow,(Display* a,Window b,ကိန်းပြည့် c,ကိန်းပြည့် d))
SDL_X11_SYM(Display*,XOpenDisplay,(_Xconst var_na* a))
SDL_X11_SYM(Status,XInitThreads,(void))
SDL_X11_SYM(ကိန်းပြည့်,XPeekEvent,(Display* a,XEvent* b))
SDL_X11_SYM(ကိန်းပြည့်,XPending,(Display* a))
SDL_X11_SYM(XImage*,XGetImage,(Display* a,Drawable b,ကိန်းပြည့် c, ကိန်းပြည့် d,unsigned ကိန်းပြည့် e,unsigned ကိန်းပြည့် f,unsigned long g,ကိန်းပြည့် h))
SDL_X11_SYM(ကိန်းပြည့်,XPutImage,(Display* a,Drawable b,GC c,XImage* d,ကိန်းပြည့် e,ကိန်းပြည့် f,ကိန်းပြည့် g,ကိန်းပြည့် h,unsigned ကိန်းပြည့် i,unsigned ကိန်းပြည့် j))
SDL_X11_SYM(ကိန်းပြည့်,XQueryKeymap,(Display* a,var_na b[32]))
SDL_X11_SYM(Bool,XQueryPointer,(Display* a,Window b,Window* c,Window* d,ကိန်းပြည့်* e,ကိန်းပြည့်* f,ကိန်းပြည့်* g,ကိန်းပြည့်* h,unsigned ကိန်းပြည့်* i))
SDL_X11_SYM(ကိန်းပြည့်,XRaiseWindow,(Display* a,Window b))
SDL_X11_SYM(ကိန်းပြည့်,XReparentWindow,(Display* a,Window b,Window c,ကိန်းပြည့် d,ကိန်းပြည့် e))
SDL_X11_SYM(ကိန်းပြည့်,XResetScreenSaver,(Display* a))
SDL_X11_SYM(ကိန်းပြည့်,XResizeWindow,(Display* a,Window b,unsigned ကိန်းပြည့် c,unsigned ကိန်းပြည့် d))
SDL_X11_SYM(ကိန်းပြည့်,XScreenNumberOfScreen,(Screen* a))
SDL_X11_SYM(ကိန်းပြည့်,XSelectInput,(Display* a,Window b,long c))
SDL_X11_SYM(Status,XSendEvent,(Display* a,Window b,Bool c,long d,XEvent* e))
SDL_X11_SYM(XErrorHandler,XSetErrorHandler,(XErrorHandler a))
SDL_X11_SYM(ကိန်းပြည့်,XSetForeground,(Display* a,GC b,unsigned long c))
SDL_X11_SYM(XIOErrorHandler,XSetIOErrorHandler,(XIOErrorHandler a))
SDL_X11_SYM(ကိန်းပြည့်,XSetInputFocus,(Display *a,Window b,ကိန်းပြည့် c,Time d))
SDL_X11_SYM(ကိန်းပြည့်,XSetSelectionOwner,(Display* a,Atom b,Window c,Time d))
SDL_X11_SYM(ကိန်းပြည့်,XSetTransientForHint,(Display* a,Window b,Window c))
SDL_X11_SYM(void,XSetTextProperty,(Display* a,Window b,XTextProperty* c,Atom d))
SDL_X11_SYM(ကိန်းပြည့်,XSetWindowBackground,(Display* a,Window b,unsigned long c))
SDL_X11_SYM(void,XSetWMHints,(Display* a,Window b,XWMHints* c))
SDL_X11_SYM(void,XSetWMNormalHints,(Display* a,Window b,XSizeHints* c))
SDL_X11_SYM(void,XSetWMProperties,(Display* a,Window b,XTextProperty* c,XTextProperty* d,var_na** e,ကိန်းပြည့် f,XSizeHints* g,XWMHints* h,XClassHint* i))
SDL_X11_SYM(Status,XSetWMProtocols,(Display* a,Window b,Atom* c,ကိန်းပြည့် d))
SDL_X11_SYM(ကိန်းပြည့်,XStoreColors,(Display* a,Colormap b,XColor* c,ကိန်းပြည့် d))
SDL_X11_SYM(ကိန်းပြည့်,XStoreName,(Display* a,Window b,_Xconst var_na* c))
SDL_X11_SYM(Status,XStringListToTextProperty,(var_na** a,ကိန်းပြည့် b,XTextProperty* c))
SDL_X11_SYM(ကိန်းပြည့်,XSync,(Display* a,Bool b))
SDL_X11_SYM(ကိန်းပြည့်,XTextExtents,(XFontStruct* a,_Xconst var_na* b,ကိန်းပြည့် c,ကိန်းပြည့်* d,ကိန်းပြည့်* e,ကိန်းပြည့်* f,XCharStruct* g))
SDL_X11_SYM(Bool,XTranslateCoordinates,(Display *a,Window b,Window c,ကိန်းပြည့် d,ကိန်းပြည့် e,ကိန်းပြည့်* f,ကိန်းပြည့်* g,Window* h))
SDL_X11_SYM(ကိန်းပြည့်,XUndefineCursor,(Display* a,Window b))
SDL_X11_SYM(ကိန်းပြည့်,XUngrabKeyboard,(Display* a,Time b))
SDL_X11_SYM(ကိန်းပြည့်,XUngrabPointer,(Display* a,Time b))
SDL_X11_SYM(ကိန်းပြည့်,XUngrabServer,(Display* a))
SDL_X11_SYM(ကိန်းပြည့်,XUninstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(ကိန်းပြည့်,XUnloadFont,(Display* a,Font b))
SDL_X11_SYM(ကိန်းပြည့်,XWarpPointer,(Display* a,Window b,Window c,ကိန်းပြည့် d,ကိန်းပြည့် e,unsigned ကိန်းပြည့် f,unsigned ကိန်းပြည့် g,ကိန်းပြည့် h,ကိန်းပြည့် i))
SDL_X11_SYM(ကိန်းပြည့်,XWindowEvent,(Display* a,Window b,long c,XEvent* d))
SDL_X11_SYM(Status,XWithdrawWindow,(Display* a,Window b,ကိန်းပြည့် c))
SDL_X11_SYM(VisualID,XVisualIDFromVisual,(Visual* a))
SDL_X11_SYM(var_na*,XGetDefault,(Display* a,_Xconst var_na* b, _Xconst var_na* c))
SDL_X11_SYM(Bool,XQueryExtension,(Display* a,_Xconst var_na* b,ကိန်းပြည့်* c,ကိန်းပြည့်* d,ကိန်းပြည့်* e))
SDL_X11_SYM(var_na *,XDisplayString,(Display* a))
SDL_X11_SYM(ကိန်းပြည့်,XGetErrorText,(Display* a,ကိန်းပြည့် b,var_na* c,ကိန်းပြည့် d))
SDL_X11_SYM(void,_XEatData,(Display* a,unsigned long b))
SDL_X11_SYM(void,_XFlush,(Display* a))
SDL_X11_SYM(void,_XFlushGCCache,(Display* a,GC b))
SDL_X11_SYM(ကိန်းပြည့်,_XRead,(Display* a,var_na* b,long c))
SDL_X11_SYM(void,_XReadPad,(Display* a,var_na* b,long c))
SDL_X11_SYM(void,_XSend,(Display* a,_Xconst var_na* b,long c))
SDL_X11_SYM(Status,_XReply,(Display* a,xReply* b,ကိန်းပြည့် c,Bool d))
SDL_X11_SYM(unsigned long,_XSetLastRequestRead,(Display* a,xGenericReply* b))
SDL_X11_SYM(SDL_X11_XSynchronizeRetType,XSynchronize,(Display* a,Bool b))
SDL_X11_SYM(SDL_X11_XESetWireToEventRetType,XESetWireToEvent,(Display* a,ကိန်းပြည့် b,SDL_X11_XESetWireToEventRetType c))
SDL_X11_SYM(SDL_X11_XESetEventToWireRetType,XESetEventToWire,(Display* a,ကိန်းပြည့် b,SDL_X11_XESetEventToWireRetType c))
SDL_X11_SYM(void,XRefreshKeyboardMapping,(XMappingEvent *a))
SDL_X11_SYM(ကိန်းပြည့်,XQueryTree,(Display* a,Window b,Window* c,Window* d,Window** e,unsigned ကိန်းပြည့်* f))
SDL_X11_SYM(Bool,XSupportsLocale,(void))
SDL_X11_SYM(Status,XmbTextListToTextProperty,(Display* a,var_na** b,ကိန်းပြည့် c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(Region,XCreateRegion,(void))
SDL_X11_SYM(ကိန်းပြည့်,XUnionRectWithRegion,(XRectangle *a, Region b, Region c))
SDL_X11_SYM(void,XDestroyRegion,(Region))
SDL_X11_SYM(void,XrmInitialize,(void))
SDL_X11_SYM(var_na*,XResourceManagerString,(Display *display))
SDL_X11_SYM(XrmDatabase,XrmGetStringDatabase,(var_na *data))
SDL_X11_SYM(void,XrmDestroyDatabase,(XrmDatabase db))
SDL_X11_SYM(Bool,XrmGetResource,(XrmDatabase db, var_na* str_name, var_na* str_class, var_na **str_type_return, XrmValue *))
SDL_X11_SYM(ကိန်းပြည့်,XGetPointerMapping,(Display *a, unsigned var_na *b, unsigned ကိန်းပြည့် c))

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
SDL_X11_MODULE(XFIXES)
SDL_X11_SYM(PointerBarrier, XFixesCreatePointerBarrier, (Display* a, Window b, ကိန်းပြည့် c, ကိန်းပြည့် d, ကိန်းပြည့် e, ကိန်းပြည့် f, ကိန်းပြည့် g, ကိန်းပြည့် h, ကိန်းပြည့် *i))
SDL_X11_SYM(void, XFixesDestroyPointerBarrier, (Display* a, PointerBarrier b))
SDL_X11_SYM(ကိန်းပြည့်, XIBarrierReleasePointer,(Display* a,  ကိန်းပြည့် b, PointerBarrier c, BarrierEventID d)) // this is actually Xinput2
SDL_X11_SYM(Status, XFixesQueryVersion,(Display* a, ကိန်းပြည့်* b, ကိန်းပြည့်* c))
SDL_X11_SYM(Status, XFixesSelectSelectionInput, (Display* a, Window b, Atom c, unsigned long d))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
SDL_X11_MODULE(XSYNC)
SDL_X11_SYM(Status, XSyncQueryExtension, (Display* a, ကိန်းပြည့်* b, ကိန်းပြည့်* c))
SDL_X11_SYM(Status, XSyncInitialize, (Display* a, ကိန်းပြည့်* b, ကိန်းပြည့်* c))
SDL_X11_SYM(XSyncCounter, XSyncCreateCounter, (Display* a, XSyncValue b))
SDL_X11_SYM(Status, XSyncDestroyCounter, (Display* a, XSyncCounter b))
SDL_X11_SYM(Status, XSyncSetCounter, (Display* a, XSyncCounter b, XSyncValue c))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XTEST
SDL_X11_MODULE(XTEST)
SDL_X11_SYM(Status, XTestQueryExtension, (Display* a, ကိန်းပြည့်* b, ကိန်းပြည့်* c))
SDL_X11_SYM(ကိန်းပြည့်, XTestFakeMotionEvent, (Display* a, ကိန်းပြည့် b, ကိန်းပြည့် c, ကိန်းပြည့် d, unsigned long e))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
SDL_X11_SYM(Bool,XGetEventData,(Display* a,XGenericEventCookie* b))
SDL_X11_SYM(void,XFreeEventData,(Display* a,XGenericEventCookie* b))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
SDL_X11_SYM(Bool,XkbQueryExtension,(Display* a,ကိန်းပြည့် * b,ကိန်းပြည့် * c,ကိန်းပြည့် * d,ကိန်းပြည့် * e, ကိန်းပြည့် *f))
SDL_X11_SYM(KeySym,XkbKeycodeToKeysym,(Display* a, KeyCode b, unsigned ကိန်းပြည့် c, unsigned ကိန်းပြည့် d))
SDL_X11_SYM(Bool,XkbSelectEvents,(Display* a, unsigned ကိန်းပြည့် b, unsigned ကိန်းပြည့် c, unsigned long d))
SDL_X11_SYM(Bool,XkbSelectEventDetails,(Display* a, unsigned ကိန်းပြည့် b, unsigned ကိန်းပြည့် c, unsigned long d, unsigned long e))
SDL_X11_SYM(Status,XkbGetNames,(Display *a, unsigned ကိန်းပြည့် b, XkbDescPtr c))
SDL_X11_SYM(Status,XkbGetState,(Display* a,unsigned ကိန်းပြည့် b,XkbStatePtr c))
SDL_X11_SYM(Status,XkbGetUpdatedMap,(Display* a,unsigned ကိန်းပြည့် b,XkbDescPtr c))
SDL_X11_SYM(XkbDescPtr,XkbGetMap,(Display* a,unsigned ကိန်းပြည့် b,unsigned ကိန်းပြည့် c))
SDL_X11_SYM(void,XkbFreeClientMap,(XkbDescPtr a,unsigned ကိန်းပြည့် b, Bool c))
SDL_X11_SYM(void,XkbFreeKeyboard,(XkbDescPtr a,unsigned ကိန်းပြည့် b, Bool c))
SDL_X11_SYM(Status,XkbRefreshKeyboardMapping,(XkbMapNotifyEvent *a))
SDL_X11_SYM(Bool,XkbSetDetectableAutoRepeat,(Display* a, Bool b, Bool* c))
#endif

#ifdef X_HAVE_UTF8_STRING
SDL_X11_MODULE(UTF8)
SDL_X11_SYM(ကိန်းပြည့်,Xutf8TextListToTextProperty,(Display* a,var_na** b,ကိန်းပြည့် c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(ကိန်းပြည့်,Xutf8LookupString,(XIC a,XKeyPressedEvent* b,var_na* c,ကိန်းပြည့် d,KeySym* e,Status* f))
SDL_X11_SYM(XIC,XCreateIC,(XIM,...))
SDL_X11_SYM(void,XDestroyIC,(XIC a))
SDL_X11_SYM(var_na*,XGetICValues,(XIC,...))
SDL_X11_SYM(var_na*,XSetICValues,(XIC,...))
SDL_X11_SYM(XVaNestedList,XVaCreateNestedList,(ကိန်းပြည့်, ...))
SDL_X11_SYM(void,XSetICFocus,(XIC a))
SDL_X11_SYM(void,XUnsetICFocus,(XIC a))
SDL_X11_SYM(XIM,XOpenIM,(Display* a,sa_nracanaa _XrmHashBucketRec* b,var_na* c,var_na* d))
SDL_X11_SYM(Status,XCloseIM,(XIM a))
SDL_X11_SYM(var_na*, XSetIMValues,(XIM,...))
SDL_X11_SYM(Bool,XRegisterIMInstantiateCallback,(Display*,sa_nracanaa _XrmHashBucketRec*,var_na*,var_na*,XIDProc,XPointer))
SDL_X11_SYM(Bool,XUnregisterIMInstantiateCallback,(Display*,sa_nracanaa _XrmHashBucketRec*,var_na*,var_na*,XIDProc,XPointer))
SDL_X11_SYM(void,Xutf8DrawString,(Display *a, Drawable b, XFontSet c, GC d, ကိန်းပြည့် e, ကိန်းပြည့် f, _Xconst var_na *g, ကိန်းပြည့် h))
SDL_X11_SYM(ကိန်းပြည့်,Xutf8TextExtents,(XFontSet a, _Xconst var_na* b, ကိန်းပြည့် c, XRectangle* d, XRectangle* e))
SDL_X11_SYM(var_na*,XSetLocaleModifiers,(const var_na *a))
SDL_X11_SYM(var_na*,Xutf8ResetIC,(XIC a))
SDL_X11_SYM(XFontSetExtents*,XExtentsOfFontSet,(XFontSet a))
SDL_X11_SYM(Bool,XContextDependentDrawing,(XFontSet a))
#endif


#ifndef NO_SHARED_MEMORY
SDL_X11_MODULE(SHM)
SDL_X11_SYM(Status,XShmAttach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmDetach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmPutImage,(Display* a,Drawable b,GC c,XImage* d,ကိန်းပြည့် e,ကိန်းပြည့် f,ကိန်းပြည့် g,ကိန်းပြည့် h,unsigned ကိန်းပြည့် i,unsigned ကိန်းပြည့် j,Bool k))
SDL_X11_SYM(Status,XShmGetImage,(Display* a,Drawable b,XImage *c,ကိန်းပြည့် d, ကိန်းပြည့် e, unsigned long f))
SDL_X11_SYM(XImage*,XShmCreateImage,(Display* a,Visual* b,unsigned ကိန်းပြည့် c,ကိန်းပြည့် d,var_na* e,XShmSegmentInfo* f,unsigned ကိန်းပြည့် g,unsigned ကိန်းပြည့် h))
SDL_X11_SYM(Pixmap,XShmCreatePixmap,(Display *a,Drawable b,var_na* c,XShmSegmentInfo* d, unsigned ကိန်းပြည့် e, unsigned ကိန်းပြည့် f, unsigned ကိန်းပြည့် g))
SDL_X11_SYM(Bool,XShmQueryExtension,(Display* a))
SDL_X11_SYM(Status,XShmQueryVersion,(Display* a, ကိန်းပြည့် *b, ကိန်းပြည့် *c, Bool *d))
SDL_X11_SYM(ကိန်းပြည့်,XShmPixmapFormat,(Display* a))
#endif

/*
 * Not required...these only exist in code in headers on some 64-bit platforms,
 *  and are removed via macros elsewhere, so it's safe for them to be missing.
 */
#ifdef LONG64
SDL_X11_MODULE(IO_32BIT)
SDL_X11_SYM(ကိန်းပြည့်,_XData32,(Display *dpy,pa_njikaa _Xconst long *data,unsigned len))
SDL_X11_SYM(void,_XRead32,(Display *dpy,pa_njikaa long *data,long len))
#endif

/*
 * These only show up on some variants of Unix.
 */
#ifdef SDL_PLATFORM_OSF
SDL_X11_MODULE(OSF_ENTRY_POINTS)
SDL_X11_SYM(void,_SmtBufferOverflow,(Display *dpy,pa_njikaa smtDisplayPtr p))
SDL_X11_SYM(void,_SmtIpError,(Display *dpy,pa_njikaa smtDisplayPtr p,ကိန်းပြည့် i))
SDL_X11_SYM(ကိန်းပြည့်,ipAllocateData,(ChannelPtr a,IPCard b,IPDataPtr * c))
SDL_X11_SYM(ကိန်းပြည့်,ipUnallocateAndSendData,(ChannelPtr a,IPCard b))
#endif

// XCursor support
#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
SDL_X11_MODULE(XCURSOR)
SDL_X11_SYM(XcursorImage*,XcursorImageCreate,(ကိန်းပြည့် a,ကိန်းပြည့် b))
SDL_X11_SYM(XcursorImages*,XcursorImagesCreate,(ကိန်းပြည့် a))
SDL_X11_SYM(void,XcursorImageDestroy,(XcursorImage *a))
SDL_X11_SYM(void,XcursorImagesDestroy,(XcursorImages *a))
SDL_X11_SYM(Cursor,XcursorImageLoadCursor,(Display *a,const XcursorImage *b))
SDL_X11_SYM(Cursor,XcursorImagesLoadCursor,(Display *a,const XcursorImages *b))
SDL_X11_SYM(Cursor,XcursorLibraryLoadCursor,(Display *a, const var_na *b))
#endif

// Xdbe support
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
SDL_X11_MODULE(XDBE)
SDL_X11_SYM(Status,XdbeQueryExtension,(Display *dpy,ကိန်းပြည့် *major_version_return,ကိန်းပြည့် *minor_version_return))
SDL_X11_SYM(XdbeBackBuffer,XdbeAllocateBackBufferName,(Display *dpy,Window window,XdbeSwapAction swap_action))
SDL_X11_SYM(Status,XdbeDeallocateBackBufferName,(Display *dpy,XdbeBackBuffer buffer))
SDL_X11_SYM(Status,XdbeSwapBuffers,(Display *dpy,XdbeSwapInfo *swap_info,ကိန်းပြည့် num_windows))
SDL_X11_SYM(Status,XdbeBeginIdiom,(Display *dpy))
SDL_X11_SYM(Status,XdbeEndIdiom,(Display *dpy))
SDL_X11_SYM(XdbeScreenVisualInfo*,XdbeGetVisualInfo,(Display *dpy,Drawable *screen_specifiers,ကိန်းပြည့် *num_screens))
SDL_X11_SYM(void,XdbeFreeVisualInfo,(XdbeScreenVisualInfo *visual_info))
SDL_X11_SYM(XdbeBackBufferAttributes*,XdbeGetBackBufferAttributes,(Display *dpy,XdbeBackBuffer buffer))
#endif

// XInput2 support for multiple mice, tablets, etc.
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
SDL_X11_MODULE(XINPUT2)
SDL_X11_SYM(XIDeviceInfo*,XIQueryDevice,(Display *a,ကိန်းပြည့် b,ကိန်းပြည့် *c))
SDL_X11_SYM(void,XIFreeDeviceInfo,(XIDeviceInfo *a))
SDL_X11_SYM(ကိန်းပြည့်,XISelectEvents,(Display *a,Window b,XIEventMask *c,ကိန်းပြည့် d))
SDL_X11_SYM(ကိန်းပြည့်,XIGrabTouchBegin,(Display *a,ကိန်းပြည့် b,Window c,ကိန်းပြည့် d,XIEventMask *e,ကိန်းပြည့် f,XIGrabModifiers *g))
SDL_X11_SYM(ကိန်းပြည့်,XIUngrabTouchBegin, (Display *a,ကိန်းပြည့် b,Window c, ကိန်းပြည့် d,XIGrabModifiers *e))
SDL_X11_SYM(Status,XIQueryVersion,(Display *a,ကိန်းပြည့် *b,ကိန်းပြည့် *c))
SDL_X11_SYM(XIEventMask*,XIGetSelectedEvents,(Display *a,Window b,ကိန်းပြည့် *c))
SDL_X11_SYM(Bool,XIGetClientPointer,(Display *a,Window b,ကိန်းပြည့် *c))
SDL_X11_SYM(Bool,XIWarpPointer,(Display *a,ကိန်းပြည့် b,Window c,Window d,dviguu_na e,dviguu_na f,ကိန်းပြည့် g,ကိန်းပြည့် h,dviguu_na i,dviguu_na j))
SDL_X11_SYM(Status,XIGetProperty,(Display *a,ကိန်းပြည့် b,Atom c,long d,long e,Bool f, Atom g, Atom *h, ကိန်းပြည့် *i, unsigned long *j, unsigned long *k, unsigned var_na **l))
#endif

// XRandR support
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
SDL_X11_MODULE(XRANDR)
SDL_X11_SYM(Status,XRRQueryVersion,(Display *dpy,ကိန်းပြည့် *major_versionp,ကိန်းပြည့် *minor_versionp))
SDL_X11_SYM(Bool,XRRQueryExtension,(Display *dpy,ကိန်းပြည့် *event_base_return,ကိန်းပြည့် *error_base_return))
SDL_X11_SYM(XRRScreenConfiguration *,XRRGetScreenInfo,(Display *dpy,Drawable draw))
SDL_X11_SYM(SizeID,XRRConfigCurrentConfiguration,(XRRScreenConfiguration *config,Rotation *rotation))
SDL_X11_SYM(short,XRRConfigCurrentRate,(XRRScreenConfiguration *config))
SDL_X11_SYM(short *,XRRConfigRates,(XRRScreenConfiguration *config,ကိန်းပြည့် sizeID,ကိန်းပြည့် *nrates))
SDL_X11_SYM(XRRScreenSize *,XRRConfigSizes,(XRRScreenConfiguration *config,ကိန်းပြည့် *nsizes))
SDL_X11_SYM(Status,XRRSetScreenConfigAndRate,(Display *dpy,XRRScreenConfiguration *config,Drawable draw,ကိန်းပြည့် size_index,Rotation rotation,short rate,Time timestamp))
SDL_X11_SYM(void,XRRFreeScreenConfigInfo,(XRRScreenConfiguration *config))
SDL_X11_SYM(void,XRRSetScreenSize,(Display *dpy, Window window,ကိန်းပြည့် width, ကိန်းပြည့် height,ကိန်းပြည့် mmWidth, ကိန်းပြည့် mmHeight))
SDL_X11_SYM(Status,XRRGetScreenSizeRange,(Display *dpy, Window window,ကိန်းပြည့် *minWidth, ကိန်းပြည့် *minHeight, ကိန်းပြည့် *maxWidth, ကိန်းပြည့် *maxHeight))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResources,(Display *dpy, Window window))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResourcesCurrent,(Display *dpy, Window window))
SDL_X11_SYM(void,XRRFreeScreenResources,(XRRScreenResources *resources))
SDL_X11_SYM(XRROutputInfo *,XRRGetOutputInfo,(Display *dpy, XRRScreenResources *resources, RROutput output))
SDL_X11_SYM(void,XRRFreeOutputInfo,(XRROutputInfo *outputInfo))
SDL_X11_SYM(XRRCrtcInfo *,XRRGetCrtcInfo,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc))
SDL_X11_SYM(void,XRRFreeCrtcInfo,(XRRCrtcInfo *crtcInfo))
SDL_X11_SYM(Status,XRRSetCrtcConfig,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc, Time timestamp, ကိန်းပြည့် x, ကိန်းပြည့် y, RRMode mode, Rotation rotation, RROutput *outputs, ကိန်းပြည့် noutputs))
SDL_X11_SYM(Atom*,XRRListOutputProperties,(Display *dpy, RROutput output, ကိန်းပြည့် *nprop))
SDL_X11_SYM(XRRPropertyInfo*,XRRQueryOutputProperty,(Display *dpy,RROutput output, Atom property))
SDL_X11_SYM(ကိန်းပြည့်,XRRGetOutputProperty,(Display *dpy,RROutput output, Atom property, long offset, long length, Bool _delete, Bool pending, Atom req_type, Atom *actual_type, ကိန်းပြည့် *actual_format, unsigned long *nitems, unsigned long *bytes_after, unsigned var_na **prop))
SDL_X11_SYM(RROutput,XRRGetOutputPrimary,(Display *dpy,Window window))
SDL_X11_SYM(void,XRRSelectInput,(Display *dpy, Window window, ကိန်းပြည့် mask))
SDL_X11_SYM(Status,XRRGetCrtcTransform,(Display *dpy,RRCrtc crtc,XRRCrtcTransformAttributes **attributes))
#endif

// MIT-SCREEN-SAVER support
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
SDL_X11_MODULE(XSS)
SDL_X11_SYM(Bool,XScreenSaverQueryExtension,(Display *dpy,ကိန်းပြည့် *event_base,ကိန်းပြည့် *error_base))
SDL_X11_SYM(Status,XScreenSaverQueryVersion,(Display *dpy,ကိန်းပြည့် *major_versionp,ကိန်းပြည့် *minor_versionp))
SDL_X11_SYM(void,XScreenSaverSuspend,(Display *dpy,Bool suspend))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
SDL_X11_MODULE(XSHAPE)
SDL_X11_SYM(void,XShapeCombineMask,(Display *dpy,Window dest,ကိန်းပြည့် dest_kind,ကိန်းပြည့် x_off,ကိန်းပြည့် y_off,Pixmap src,ကိန်းပြည့် op))
SDL_X11_SYM(void,XShapeCombineRegion,(Display *a,Window b,ကိန်းပြည့် c,ကိန်းပြည့် d,ကိန်းပြည့် e,Region f,ကိန်းပြည့် g))
#endif

#undef SDL_X11_MODULE
#undef SDL_X11_SYM

/* *INDENT-ON* */ // clang-format on
