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
SDL_X11_SYM(XSizeHints*,XAllocSizeHints,(تهی))
SDL_X11_SYM(XWMHints*,XAllocWMHints,(تهی))
SDL_X11_SYM(XClassHint*,XAllocClassHint,(تهی))
SDL_X11_SYM(صحیح,XChangePointerControl,(Display* a,Bool b,Bool c,صحیح d,صحیح e,صحیح f))
SDL_X11_SYM(صحیح,XChangeProperty,(Display* a,Window b,Atom c,Atom d,صحیح e,صحیح f,_Xconst unsigned نویسه* g,صحیح h))
SDL_X11_SYM(Bool,XCheckIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(صحیح,XClearWindow,(Display* a,Window b))
SDL_X11_SYM(صحیح,XCloseDisplay,(Display* a))
SDL_X11_SYM(صحیح,XConvertSelection,(Display* a,Atom b,Atom c,Atom d,Window e,Time f))
SDL_X11_SYM(Pixmap,XCreateBitmapFromData,(Display *dpy,Drawable d,_Xconst نویسه *data,unsigned صحیح width,unsigned صحیح height))
SDL_X11_SYM(Colormap,XCreateColormap,(Display* a,Window b,Visual* c,صحیح d))
SDL_X11_SYM(Cursor,XCreatePixmapCursor,(Display* a,Pixmap b,Pixmap c,XColor* d,XColor* e,unsigned صحیح f,unsigned صحیح g))
SDL_X11_SYM(Cursor,XCreatePixmap,(Display* a,Drawable b,unsigned صحیح d,unsigned صحیح e,unsigned صحیح f))
SDL_X11_SYM(Cursor,XCreateFontCursor,(Display* a,unsigned صحیح b))
SDL_X11_SYM(XFontSet,XCreateFontSet,(Display* a, _Xconst نویسه* b, نویسه*** c, صحیح* d, نویسه** e))
SDL_X11_SYM(GC,XCreateGC,(Display* a,Drawable b,unsigned long c,XGCValues* d))
SDL_X11_SYM(تهی,XSetFont,(Display* a,GC b,Font c))
SDL_X11_SYM(Status,XAllocColor,(Display *a, Colormap b, XColor *c))
SDL_X11_SYM(XImage*,XCreateImage,(Display* a,Visual* b,unsigned صحیح c,صحیح d,صحیح e,نویسه* f,unsigned صحیح g,unsigned صحیح h,صحیح i,صحیح j))
SDL_X11_SYM(Window,XCreateWindow,(Display* a,Window b,صحیح c,صحیح d,unsigned صحیح e,unsigned صحیح f,unsigned صحیح g,صحیح h,unsigned صحیح i,Visual* j,unsigned long k,XSetWindowAttributes* l))
SDL_X11_SYM(تهی,XCopyArea,(Display *a, Drawable b, Drawable c, GC d, صحیح e, صحیح f, unsigned صحیح g, unsigned صحیح h, صحیح i, صحیح j))
SDL_X11_SYM(صحیح,XDefineCursor,(Display* a,Window b,Cursor c))
SDL_X11_SYM(صحیح,XDeleteProperty,(Display* a,Window b,Atom c))
SDL_X11_SYM(صحیح,XDestroyWindow,(Display* a,Window b))
SDL_X11_SYM(صحیح,XDisplayKeycodes,(Display* a,صحیح* b,صحیح* c))
SDL_X11_SYM(صحیح,XDrawRectangle,(Display* a,Drawable b,GC c,صحیح d,صحیح e,unsigned صحیح f,unsigned صحیح g))
SDL_X11_SYM(صحیح,XFontsOfFontSet,(XFontSet a,XFontStruct ***b,نویسه ***c))
SDL_X11_SYM(صحیح,XFillArc,(Display* a,Drawable b,GC c,صحیح d,صحیح e,unsigned صحیح f,unsigned صحیح g, صحیح h, صحیح i))
SDL_X11_SYM(نویسه*,XDisplayName,(_Xconst نویسه* a))
SDL_X11_SYM(صحیح,XDrawString,(Display* a,Drawable b,GC c,صحیح d,صحیح e,_Xconst نویسه* f,صحیح g))
SDL_X11_SYM(صحیح,XEventsQueued,(Display* a,صحیح b))
SDL_X11_SYM(صحیح,XFillRectangle,(Display* a,Drawable b,GC c,صحیح d,صحیح e,unsigned صحیح f,unsigned صحیح g))
SDL_X11_SYM(Bool,XFilterEvent,(XEvent *event,Window w))
SDL_X11_SYM(صحیح,XFlush,(Display* a))
SDL_X11_SYM(صحیح,XFree,(تهی*a))
SDL_X11_SYM(صحیح,XFreeCursor,(Display* a,Cursor b))
SDL_X11_SYM(تهی,XFreeFontSet,(Display* a, XFontSet b))
SDL_X11_SYM(صحیح,XFreeGC,(Display* a,GC b))
SDL_X11_SYM(صحیح,XFreeFont,(Display* a, XFontStruct* b))
SDL_X11_SYM(صحیح,XFreeModifiermap,(XModifierKeymap* a))
SDL_X11_SYM(صحیح,XFreePixmap,(Display* a,Pixmap b))
SDL_X11_SYM(صحیح,XFreeColormap,(Display* a,Colormap b))
SDL_X11_SYM(تهی,XFreeStringList,(نویسه** a))
SDL_X11_SYM(نویسه*,XGetAtomName,(Display *a,Atom b))
SDL_X11_SYM(صحیح,XGet_درون_داد_Focus,(Display *a,Window *b,صحیح *c))
SDL_X11_SYM(کلید_Sym*,XGetKeyboardMapping,(Display *a, کلید_Code_2 b, صحیح c, صحیح *d))
SDL_X11_SYM(صحیح,XGetErrorDatabaseText,(Display* a,_Xconst نویسه* b,_Xconst نویسه* c,_Xconst نویسه* d,نویسه* e,صحیح f))
SDL_X11_SYM(XModifierKeymap*,XGetModifierMapping,(Display* a))
SDL_X11_SYM(صحیح,XGetPointerControl,(Display* a,صحیح* b,صحیح* c,صحیح* d))
SDL_X11_SYM(Window,XGetSelectionOwner,(Display* a,Atom b))
SDL_X11_SYM(XVisualInfo*,XGetVisualInfo,(Display* a,long b,XVisualInfo* c,صحیح* d))
SDL_X11_SYM(Status,XGetWindowAttributes,(Display* a,Window b,XWindowAttributes* c))
SDL_X11_SYM(صحیح,XGetWindowProperty,(Display* a,Window b,Atom c,long d,long e,Bool f,Atom g,Atom* h,صحیح* i,unsigned long* j,unsigned long *k,unsigned نویسه **l))
SDL_X11_SYM(XWMHints*,XGetWMHints,(Display* a,Window b))
SDL_X11_SYM(Status,XGetWMNormalHints,(Display *a,Window b, XSizeHints *c, long *d))
SDL_X11_SYM(صحیح,XIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(صحیح,XGrabKeyboard,(Display* a,Window b,Bool c,صحیح d,صحیح e,Time f))
SDL_X11_SYM(صحیح,XGrabPointer,(Display* a,Window b,Bool c,unsigned صحیح d,صحیح e,صحیح f,Window g,Cursor h,Time i))
SDL_X11_SYM(صحیح,XGrabServer,(Display* a))
SDL_X11_SYM(Status,XIconifyWindow,(Display* a,Window b,صحیح c))
SDL_X11_SYM(کلید_Code_2,XKeysymToKeycode,(Display* a,کلید_Sym b))
SDL_X11_SYM(نویسه*,XKeysymToString,(کلید_Sym a))
SDL_X11_SYM(صحیح,XInstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(Atom,XInternAtom,(Display* a,_Xconst نویسه* b,Bool c))
SDL_X11_SYM(XPixmap_Format_مقادیر*,XListPixmapFormats,(Display* a,صحیح* b))
SDL_X11_SYM(XFontStruct*,XLoadQueryFont,(Display* a,_Xconst نویسه* b))
SDL_X11_SYM(کلید_Sym,XLookupKeysym,(XKeyEvent* a,صحیح b))
SDL_X11_SYM(صحیح,XLookupString,(XKeyEvent* a,نویسه* b,صحیح c,کلید_Sym* d,XComposeStatus* e))
SDL_X11_SYM(صحیح,XMapRaised,(Display* a,Window b))
SDL_X11_SYM(Status,XMatchVisualInfo,(Display* a,صحیح b,صحیح c,صحیح d,XVisualInfo* e))
SDL_X11_SYM(صحیح,XMissingExtension,(Display* a,_Xconst نویسه* b))
SDL_X11_SYM(صحیح,XMoveWindow,(Display* a,Window b,صحیح c,صحیح d))
SDL_X11_SYM(Display*,XOpenDisplay,(_Xconst نویسه* a))
SDL_X11_SYM(Status,XInitThreads,(تهی))
SDL_X11_SYM(صحیح,XPeekEvent,(Display* a,XEvent* b))
SDL_X11_SYM(صحیح,XPending,(Display* a))
SDL_X11_SYM(XImage*,XGetImage,(Display* a,Drawable b,صحیح c, صحیح d,unsigned صحیح e,unsigned صحیح f,unsigned long g,صحیح h))
SDL_X11_SYM(صحیح,XPutImage,(Display* a,Drawable b,GC c,XImage* d,صحیح e,صحیح f,صحیح g,صحیح h,unsigned صحیح i,unsigned صحیح j))
SDL_X11_SYM(صحیح,XQueryKeymap,(Display* a,نویسه b[32]))
SDL_X11_SYM(Bool,XQueryPointer,(Display* a,Window b,Window* c,Window* d,صحیح* e,صحیح* f,صحیح* g,صحیح* h,unsigned صحیح* i))
SDL_X11_SYM(صحیح,XRaiseWindow,(Display* a,Window b))
SDL_X11_SYM(صحیح,XReparentWindow,(Display* a,Window b,Window c,صحیح d,صحیح e))
SDL_X11_SYM(صحیح,XResetScreenSaver,(Display* a))
SDL_X11_SYM(صحیح,XResizeWindow,(Display* a,Window b,unsigned صحیح c,unsigned صحیح d))
SDL_X11_SYM(صحیح,XScreen_عدد_Of_Screen,(Screen* a))
SDL_X11_SYM(صحیح,XSelect_درون_داد,(Display* a,Window b,long c))
SDL_X11_SYM(Status,XSendEvent,(Display* a,Window b,Bool c,long d,XEvent* e))
SDL_X11_SYM(XErrorHandler,XSetErrorHandler,(XErrorHandler a))
SDL_X11_SYM(صحیح,XSetForeground,(Display* a,GC b,unsigned long c))
SDL_X11_SYM(XIOErrorHandler,XSetIOErrorHandler,(XIOErrorHandler a))
SDL_X11_SYM(صحیح,XSet_درون_داد_Focus,(Display *a,Window b,صحیح c,Time d))
SDL_X11_SYM(صحیح,XSetSelectionOwner,(Display* a,Atom b,Window c,Time d))
SDL_X11_SYM(صحیح,XSetTransientForHint,(Display* a,Window b,Window c))
SDL_X11_SYM(تهی,XSetTextProperty,(Display* a,Window b,XTextProperty* c,Atom d))
SDL_X11_SYM(صحیح,XSetWindowBackground,(Display* a,Window b,unsigned long c))
SDL_X11_SYM(تهی,XSetWMHints,(Display* a,Window b,XWMHints* c))
SDL_X11_SYM(تهی,XSetWMNormalHints,(Display* a,Window b,XSizeHints* c))
SDL_X11_SYM(تهی,XSetWMProperties,(Display* a,Window b,XTextProperty* c,XTextProperty* d,نویسه** e,صحیح f,XSizeHints* g,XWMHints* h,XClassHint* i))
SDL_X11_SYM(Status,XSetWMProtocols,(Display* a,Window b,Atom* c,صحیح d))
SDL_X11_SYM(صحیح,XStoreColors,(Display* a,Colormap b,XColor* c,صحیح d))
SDL_X11_SYM(صحیح,XStoreName,(Display* a,Window b,_Xconst نویسه* c))
SDL_X11_SYM(Status,XStringListToTextProperty,(نویسه** a,صحیح b,XTextProperty* c))
SDL_X11_SYM(صحیح,XSync,(Display* a,Bool b))
SDL_X11_SYM(صحیح,XTextExtents,(XFontStruct* a,_Xconst نویسه* b,صحیح c,صحیح* d,صحیح* e,صحیح* f,XCharStruct* g))
SDL_X11_SYM(Bool,XTranslateCoordinates,(Display *a,Window b,Window c,صحیح d,صحیح e,صحیح* f,صحیح* g,Window* h))
SDL_X11_SYM(صحیح,XUndefineCursor,(Display* a,Window b))
SDL_X11_SYM(صحیح,XUngrabKeyboard,(Display* a,Time b))
SDL_X11_SYM(صحیح,XUngrabPointer,(Display* a,Time b))
SDL_X11_SYM(صحیح,XUngrabServer,(Display* a))
SDL_X11_SYM(صحیح,XUninstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(صحیح,XUnloadFont,(Display* a,Font b))
SDL_X11_SYM(صحیح,XWarpPointer,(Display* a,Window b,Window c,صحیح d,صحیح e,unsigned صحیح f,unsigned صحیح g,صحیح h,صحیح i))
SDL_X11_SYM(صحیح,XWindowEvent,(Display* a,Window b,long c,XEvent* d))
SDL_X11_SYM(Status,XWithdrawWindow,(Display* a,Window b,صحیح c))
SDL_X11_SYM(VisualID,XVisualIDFromVisual,(Visual* a))
SDL_X11_SYM(نویسه*,XGetDefault,(Display* a,_Xconst نویسه* b, _Xconst نویسه* c))
SDL_X11_SYM(Bool,XQueryExtension,(Display* a,_Xconst نویسه* b,صحیح* c,صحیح* d,صحیح* e))
SDL_X11_SYM(نویسه *,XDisplayString,(Display* a))
SDL_X11_SYM(صحیح,XGetErrorText,(Display* a,صحیح b,نویسه* c,صحیح d))
SDL_X11_SYM(تهی,_XEatData,(Display* a,unsigned long b))
SDL_X11_SYM(تهی,_XFlush,(Display* a))
SDL_X11_SYM(تهی,_XFlushGCCache,(Display* a,GC b))
SDL_X11_SYM(صحیح,_XRead,(Display* a,نویسه* b,long c))
SDL_X11_SYM(تهی,_XReadPad,(Display* a,نویسه* b,long c))
SDL_X11_SYM(تهی,_XSend,(Display* a,_Xconst نویسه* b,long c))
SDL_X11_SYM(Status,_XReply,(Display* a,xReply* b,صحیح c,Bool d))
SDL_X11_SYM(unsigned long,_XSetLastRequestRead,(Display* a,xGenericReply* b))
SDL_X11_SYM(SDL_X11_XSynchronizeRetType,XSynchronize,(Display* a,Bool b))
SDL_X11_SYM(SDL_X11_XESetWireToEventRetType,XESetWireToEvent,(Display* a,صحیح b,SDL_X11_XESetWireToEventRetType c))
SDL_X11_SYM(SDL_X11_XESetEventToWireRetType,XESetEventToWire,(Display* a,صحیح b,SDL_X11_XESetEventToWireRetType c))
SDL_X11_SYM(تهی,XRefreshKeyboardMapping,(XMappingEvent *a))
SDL_X11_SYM(صحیح,XQuery_درخت,(Display* a,Window b,Window* c,Window* d,Window** e,unsigned صحیح* f))
SDL_X11_SYM(Bool,XSupportsLocale,(تهی))
SDL_X11_SYM(Status,XmbTextListToTextProperty,(Display* a,نویسه** b,صحیح c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(Region,XCreateRegion,(تهی))
SDL_X11_SYM(صحیح,XUnionRectWithRegion,(XRectangle *a, Region b, Region c))
SDL_X11_SYM(تهی,XDestroyRegion,(Region))
SDL_X11_SYM(تهی,XrmInitialize,(تهی))
SDL_X11_SYM(نویسه*,XResourceManagerString,(Display *display))
SDL_X11_SYM(XrmDatabase,XrmGetStringDatabase,(نویسه *data))
SDL_X11_SYM(تهی,XrmDestroyDatabase,(XrmDatabase db))
SDL_X11_SYM(Bool,XrmGetResource,(XrmDatabase db, نویسه* str_name, نویسه* str_class, نویسه **str_type_return, Xrm_مقدار *))
SDL_X11_SYM(صحیح,XGetPointerMapping,(Display *a, unsigned نویسه *b, unsigned صحیح c))

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
SDL_X11_MODULE(XFIXES)
SDL_X11_SYM(PointerBarrier, XFixesCreatePointerBarrier, (Display* a, Window b, صحیح c, صحیح d, صحیح e, صحیح f, صحیح g, صحیح h, صحیح *i))
SDL_X11_SYM(تهی, XFixesDestroyPointerBarrier, (Display* a, PointerBarrier b))
SDL_X11_SYM(صحیح, XIBarrierReleasePointer,(Display* a,  صحیح b, PointerBarrier c, BarrierEventID d)) // this is actually Xinput2
SDL_X11_SYM(Status, XFixesQueryVersion,(Display* a, صحیح* b, صحیح* c))
SDL_X11_SYM(Status, XFixes_Select_Selection_درون_داد, (Display* a, Window b, Atom c, unsigned long d))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
SDL_X11_MODULE(XSYNC)
SDL_X11_SYM(Status, XSyncQueryExtension, (Display* a, صحیح* b, صحیح* c))
SDL_X11_SYM(Status, XSyncInitialize, (Display* a, صحیح* b, صحیح* c))
SDL_X11_SYM(XSyncCounter, XSyncCreateCounter, (Display* a, XSync_مقدار b))
SDL_X11_SYM(Status, XSyncDestroyCounter, (Display* a, XSyncCounter b))
SDL_X11_SYM(Status, XSyncSetCounter, (Display* a, XSyncCounter b, XSync_مقدار c))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XTEST
SDL_X11_MODULE(XTEST)
SDL_X11_SYM(Status, XTestQueryExtension, (Display* a, صحیح* b, صحیح* c))
SDL_X11_SYM(صحیح, XTestFakeMotionEvent, (Display* a, صحیح b, صحیح c, صحیح d, unsigned long e))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
SDL_X11_SYM(Bool,XGetEventData,(Display* a,XGenericEventCookie* b))
SDL_X11_SYM(تهی,XFreeEventData,(Display* a,XGenericEventCookie* b))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
SDL_X11_SYM(Bool,XkbQueryExtension,(Display* a,صحیح * b,صحیح * c,صحیح * d,صحیح * e, صحیح *f))
SDL_X11_SYM(کلید_Sym,XkbKeycodeToKeysym,(Display* a, کلید_Code_2 b, unsigned صحیح c, unsigned صحیح d))
SDL_X11_SYM(Bool,XkbSelectEvents,(Display* a, unsigned صحیح b, unsigned صحیح c, unsigned long d))
SDL_X11_SYM(Bool,XkbSelectEventDetails,(Display* a, unsigned صحیح b, unsigned صحیح c, unsigned long d, unsigned long e))
SDL_X11_SYM(Status,XkbGetNames,(Display *a, unsigned صحیح b, XkbDescPtr c))
SDL_X11_SYM(Status,XkbGetState,(Display* a,unsigned صحیح b,XkbStatePtr c))
SDL_X11_SYM(Status,XkbGetUpdatedMap,(Display* a,unsigned صحیح b,XkbDescPtr c))
SDL_X11_SYM(XkbDescPtr,XkbGetMap,(Display* a,unsigned صحیح b,unsigned صحیح c))
SDL_X11_SYM(تهی,XkbFreeClientMap,(XkbDescPtr a,unsigned صحیح b, Bool c))
SDL_X11_SYM(تهی,XkbFreeKeyboard,(XkbDescPtr a,unsigned صحیح b, Bool c))
SDL_X11_SYM(Status,XkbRefreshKeyboardMapping,(XkbMapNotifyEvent *a))
SDL_X11_SYM(Bool,XkbSetDetectableAutoRepeat,(Display* a, Bool b, Bool* c))
#endif

#ifdef X_HAVE_UTF8_STRING
SDL_X11_MODULE(UTF8)
SDL_X11_SYM(صحیح,Xutf8TextListToTextProperty,(Display* a,نویسه** b,صحیح c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(صحیح,Xutf8LookupString,(XIC a,XKeyPressedEvent* b,نویسه* c,صحیح d,کلید_Sym* e,Status* f))
SDL_X11_SYM(XIC,XCreateIC,(XIM,...))
SDL_X11_SYM(تهی,XDestroyIC,(XIC a))
SDL_X11_SYM(نویسه*,XGetICValues,(XIC,...))
SDL_X11_SYM(نویسه*,XSetICValues,(XIC,...))
SDL_X11_SYM(XVaNestedList,XVaCreateNestedList,(صحیح, ...))
SDL_X11_SYM(تهی,XSetICFocus,(XIC a))
SDL_X11_SYM(تهی,XUnsetICFocus,(XIC a))
SDL_X11_SYM(XIM,XOpenIM,(Display* a,ساختار _XrmHashBucketRec* b,نویسه* c,نویسه* d))
SDL_X11_SYM(Status,XCloseIM,(XIM a))
SDL_X11_SYM(نویسه*, XSetIMValues,(XIM,...))
SDL_X11_SYM(Bool,XRegisterIMInstantiateCallback,(Display*,ساختار _XrmHashBucketRec*,نویسه*,نویسه*,XIDProc,XPointer))
SDL_X11_SYM(Bool,XUnregisterIMInstantiateCallback,(Display*,ساختار _XrmHashBucketRec*,نویسه*,نویسه*,XIDProc,XPointer))
SDL_X11_SYM(تهی,Xutf8DrawString,(Display *a, Drawable b, XFontSet c, GC d, صحیح e, صحیح f, _Xconst نویسه *g, صحیح h))
SDL_X11_SYM(صحیح,Xutf8TextExtents,(XFontSet a, _Xconst نویسه* b, صحیح c, XRectangle* d, XRectangle* e))
SDL_X11_SYM(نویسه*,XSetLocaleModifiers,(ثابت نویسه *a))
SDL_X11_SYM(نویسه*,Xutf8ResetIC,(XIC a))
SDL_X11_SYM(XFontSetExtents*,XExtentsOfFontSet,(XFontSet a))
SDL_X11_SYM(Bool,XContextDependentDrawing,(XFontSet a))
#endif


#ifndef NO_SHARED_MEMORY
SDL_X11_MODULE(SHM)
SDL_X11_SYM(Status,XShmAttach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmDetach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmPutImage,(Display* a,Drawable b,GC c,XImage* d,صحیح e,صحیح f,صحیح g,صحیح h,unsigned صحیح i,unsigned صحیح j,Bool k))
SDL_X11_SYM(Status,XShmGetImage,(Display* a,Drawable b,XImage *c,صحیح d, صحیح e, unsigned long f))
SDL_X11_SYM(XImage*,XShmCreateImage,(Display* a,Visual* b,unsigned صحیح c,صحیح d,نویسه* e,XShmSegmentInfo* f,unsigned صحیح g,unsigned صحیح h))
SDL_X11_SYM(Pixmap,XShmCreatePixmap,(Display *a,Drawable b,نویسه* c,XShmSegmentInfo* d, unsigned صحیح e, unsigned صحیح f, unsigned صحیح g))
SDL_X11_SYM(Bool,XShmQueryExtension,(Display* a))
SDL_X11_SYM(Status,XShmQueryVersion,(Display* a, صحیح *b, صحیح *c, Bool *d))
SDL_X11_SYM(صحیح,XShmPixmapFormat,(Display* a))
#endif

/*
 * Not required...these only exist in code in headers on some 64-bit platforms,
 *  and are removed via macros elsewhere, so it's safe for them to be missing.
 */
#ifdef LONG64
SDL_X11_MODULE(IO_32BIT)
SDL_X11_SYM(صحیح,_XData32,(Display *dpy,ثبات _Xconst long *data,unsigned len))
SDL_X11_SYM(تهی,_XRead32,(Display *dpy,ثبات long *data,long len))
#endif

/*
 * These only show up on some variants of Unix.
 */
#ifdef SDL_PLATFORM_OSF
SDL_X11_MODULE(OSF_ENTRY_POINTS)
SDL_X11_SYM(تهی,_SmtBufferOverflow,(Display *dpy,ثبات smtDisplayPtr p))
SDL_X11_SYM(تهی,_SmtIpError,(Display *dpy,ثبات smtDisplayPtr p,صحیح i))
SDL_X11_SYM(صحیح,ipAllocateData,(ChannelPtr a,IPCard b,IPDataPtr * c))
SDL_X11_SYM(صحیح,ipUnallocateAndSendData,(ChannelPtr a,IPCard b))
#endif

// XCursor support
#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
SDL_X11_MODULE(XCURSOR)
SDL_X11_SYM(XcursorImage*,XcursorImageCreate,(صحیح a,صحیح b))
SDL_X11_SYM(XcursorImages*,XcursorImagesCreate,(صحیح a))
SDL_X11_SYM(تهی,XcursorImageDestroy,(XcursorImage *a))
SDL_X11_SYM(تهی,XcursorImagesDestroy,(XcursorImages *a))
SDL_X11_SYM(Cursor,XcursorImageLoadCursor,(Display *a,ثابت XcursorImage *b))
SDL_X11_SYM(Cursor,XcursorImagesLoadCursor,(Display *a,ثابت XcursorImages *b))
SDL_X11_SYM(Cursor,XcursorLibraryLoadCursor,(Display *a, ثابت نویسه *b))
#endif

// Xdbe support
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
SDL_X11_MODULE(XDBE)
SDL_X11_SYM(Status,XdbeQueryExtension,(Display *dpy,صحیح *major_version_return,صحیح *minor_version_return))
SDL_X11_SYM(XdbeBackBuffer,XdbeAllocateBackBufferName,(Display *dpy,Window window,XdbeSwapAction swap_action))
SDL_X11_SYM(Status,XdbeDeallocateBackBufferName,(Display *dpy,XdbeBackBuffer buffer))
SDL_X11_SYM(Status,XdbeSwapBuffers,(Display *dpy,XdbeSwapInfo *swap_info,صحیح رقم_windows))
SDL_X11_SYM(Status,XdbeBeginIdiom,(Display *dpy))
SDL_X11_SYM(Status,XdbeEndIdiom,(Display *dpy))
SDL_X11_SYM(XdbeScreenVisualInfo*,XdbeGetVisualInfo,(Display *dpy,Drawable *screen_specifiers,صحیح *رقم_screens))
SDL_X11_SYM(تهی,XdbeFreeVisualInfo,(XdbeScreenVisualInfo *visual_info))
SDL_X11_SYM(XdbeBackBufferAttributes*,XdbeGetBackBufferAttributes,(Display *dpy,XdbeBackBuffer buffer))
#endif

// XInput2 support for multiple mice, tablets, etc.
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
SDL_X11_MODULE(XINPUT2)
SDL_X11_SYM(XIDeviceInfo*,XIQueryDevice,(Display *a,صحیح b,صحیح *c))
SDL_X11_SYM(تهی,XIFreeDeviceInfo,(XIDeviceInfo *a))
SDL_X11_SYM(صحیح,XISelectEvents,(Display *a,Window b,XIEventMask *c,صحیح d))
SDL_X11_SYM(صحیح,XIGrabTouchBegin,(Display *a,صحیح b,Window c,صحیح d,XIEventMask *e,صحیح f,XIGrabModifiers *g))
SDL_X11_SYM(صحیح,XIUngrabTouchBegin, (Display *a,صحیح b,Window c, صحیح d,XIGrabModifiers *e))
SDL_X11_SYM(Status,XIQueryVersion,(Display *a,صحیح *b,صحیح *c))
SDL_X11_SYM(XIEventMask*,XIGetSelectedEvents,(Display *a,Window b,صحیح *c))
SDL_X11_SYM(Bool,XIGetClientPointer,(Display *a,Window b,صحیح *c))
SDL_X11_SYM(Bool,XIWarpPointer,(Display *a,صحیح b,Window c,Window d,دوگانه e,دوگانه f,صحیح g,صحیح h,دوگانه i,دوگانه j))
SDL_X11_SYM(Status,XIGetProperty,(Display *a,صحیح b,Atom c,long d,long e,Bool f, Atom g, Atom *h, صحیح *i, unsigned long *j, unsigned long *k, unsigned نویسه **l))
#endif

// XRandR support
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
SDL_X11_MODULE(XRANDR)
SDL_X11_SYM(Status,XRRQueryVersion,(Display *dpy,صحیح *major_versionp,صحیح *minor_versionp))
SDL_X11_SYM(Bool,XRRQueryExtension,(Display *dpy,صحیح *event_base_return,صحیح *error_base_return))
SDL_X11_SYM(XRRScreenConfiguration *,XRRGetScreenInfo,(Display *dpy,Drawable draw))
SDL_X11_SYM(SizeID,XRRConfigCurrentConfiguration,(XRRScreenConfiguration *config,Rotation *rotation))
SDL_X11_SYM(short,XRRConfigCurrentRate,(XRRScreenConfiguration *config))
SDL_X11_SYM(short *,XRRConfigRates,(XRRScreenConfiguration *config,صحیح sizeID,صحیح *nrates))
SDL_X11_SYM(XRRScreenSize *,XRRConfigSizes,(XRRScreenConfiguration *config,صحیح *nsizes))
SDL_X11_SYM(Status,XRRSetScreenConfigAndRate,(Display *dpy,XRRScreenConfiguration *config,Drawable draw,صحیح size_index,Rotation rotation,short rate,Time timestamp))
SDL_X11_SYM(تهی,XRRFreeScreenConfigInfo,(XRRScreenConfiguration *config))
SDL_X11_SYM(تهی,XRRSetScreenSize,(Display *dpy, Window window,صحیح width, صحیح height,صحیح mmWidth, صحیح mmHeight))
SDL_X11_SYM(Status,XRRGetScreenSizeRange,(Display *dpy, Window window,صحیح *minWidth, صحیح *minHeight, صحیح *maxWidth, صحیح *maxHeight))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResources,(Display *dpy, Window window))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResourcesCurrent,(Display *dpy, Window window))
SDL_X11_SYM(تهی,XRRFreeScreenResources,(XRRScreenResources *resources))
SDL_X11_SYM(XRROutputInfo *,XRRGetOutputInfo,(Display *dpy, XRRScreenResources *resources, RROutput output))
SDL_X11_SYM(تهی,XRRFreeOutputInfo,(XRROutputInfo *outputInfo))
SDL_X11_SYM(XRRCrtcInfo *,XRRGetCrtcInfo,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc))
SDL_X11_SYM(تهی,XRRFreeCrtcInfo,(XRRCrtcInfo *crtcInfo))
SDL_X11_SYM(Status,XRRSetCrtcConfig,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc, Time timestamp, صحیح x, صحیح y, RRMode mode, Rotation rotation, RROutput *outputs, صحیح noutputs))
SDL_X11_SYM(Atom*,XRRListOutputProperties,(Display *dpy, RROutput output, صحیح *nprop))
SDL_X11_SYM(XRRPropertyInfo*,XRRQueryOutputProperty,(Display *dpy,RROutput output, Atom property))
SDL_X11_SYM(صحیح,XRRGetOutputProperty,(Display *dpy,RROutput output, Atom property, long offset, long length, Bool _delete, Bool pending, Atom req_type, Atom *actual_type, صحیح *actual_format, unsigned long *nitems, unsigned long *bytes_after, unsigned نویسه **prop))
SDL_X11_SYM(RROutput,XRRGetOutputPrimary,(Display *dpy,Window window))
SDL_X11_SYM(تهی,XRRSelect_درون_داد,(Display *dpy, Window window, صحیح mask))
SDL_X11_SYM(Status,XRRGetCrtcTransform,(Display *dpy,RRCrtc crtc,XRRCrtcTransformAttributes **attributes))
#endif

// MIT-SCREEN-SAVER support
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
SDL_X11_MODULE(XSS)
SDL_X11_SYM(Bool,XScreenSaverQueryExtension,(Display *dpy,صحیح *event_base,صحیح *error_base))
SDL_X11_SYM(Status,XScreenSaverQueryVersion,(Display *dpy,صحیح *major_versionp,صحیح *minor_versionp))
SDL_X11_SYM(تهی,XScreenSaverSuspend,(Display *dpy,Bool suspend))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
SDL_X11_MODULE(XSHAPE)
SDL_X11_SYM(تهی,XShapeCombineMask,(Display *dpy,Window dest,صحیح dest_kind,صحیح x_off,صحیح y_off,Pixmap src,صحیح op))
SDL_X11_SYM(تهی,XShapeCombineRegion,(Display *a,Window b,صحیح c,صحیح d,صحیح e,Region f,صحیح g))
#endif

#undef SDL_X11_MODULE
#undef SDL_X11_SYM

/* *INDENT-ON* */ // clang-format on
