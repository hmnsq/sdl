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
SDL_X11_SYM(XSizeHints*,XAllocSizeHints,(فراغ))
SDL_X11_SYM(XWMHints*,XAllocWMHints,(فراغ))
SDL_X11_SYM(XClassHint*,XAllocClassHint,(فراغ))
SDL_X11_SYM(صحيح,XChangePointerControl,(Display* a,Bool b,Bool c,صحيح d,صحيح e,صحيح f))
SDL_X11_SYM(صحيح,XChangeProperty,(Display* a,Window b,Atom c,Atom d,صحيح e,صحيح f,_Xconst unsigned حرف* g,صحيح h))
SDL_X11_SYM(Bool,XCheckIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(صحيح,XClearWindow,(Display* a,Window b))
SDL_X11_SYM(صحيح,XCloseDisplay,(Display* a))
SDL_X11_SYM(صحيح,XConvertSelection,(Display* a,Atom b,Atom c,Atom d,Window e,Time f))
SDL_X11_SYM(Pixmap,XCreateBitmapFromData,(Display *dpy,Drawable d,_Xconst حرف *data,unsigned صحيح width,unsigned صحيح height))
SDL_X11_SYM(Colormap,XCreateColormap,(Display* a,Window b,Visual* c,صحيح d))
SDL_X11_SYM(Cursor,XCreatePixmapCursor,(Display* a,Pixmap b,Pixmap c,XColor* d,XColor* e,unsigned صحيح f,unsigned صحيح g))
SDL_X11_SYM(Cursor,XCreatePixmap,(Display* a,Drawable b,unsigned صحيح d,unsigned صحيح e,unsigned صحيح f))
SDL_X11_SYM(Cursor,XCreateFontCursor,(Display* a,unsigned صحيح b))
SDL_X11_SYM(XFontSet,XCreateFontSet,(Display* a, _Xconst حرف* b, حرف*** c, صحيح* d, حرف** e))
SDL_X11_SYM(GC,XCreateGC,(Display* a,Drawable b,unsigned long c,XGCValues* d))
SDL_X11_SYM(فراغ,XSetFont,(Display* a,GC b,Font c))
SDL_X11_SYM(Status,XAllocColor,(Display *a, Colormap b, XColor *c))
SDL_X11_SYM(XImage*,XCreateImage,(Display* a,Visual* b,unsigned صحيح c,صحيح d,صحيح e,حرف* f,unsigned صحيح g,unsigned صحيح h,صحيح i,صحيح j))
SDL_X11_SYM(Window,XCreateWindow,(Display* a,Window b,صحيح c,صحيح d,unsigned صحيح e,unsigned صحيح f,unsigned صحيح g,صحيح h,unsigned صحيح i,Visual* j,unsigned long k,XSetWindowAttributes* l))
SDL_X11_SYM(فراغ,XCopyArea,(Display *a, Drawable b, Drawable c, GC d, صحيح e, صحيح f, unsigned صحيح g, unsigned صحيح h, صحيح i, صحيح j))
SDL_X11_SYM(صحيح,XDefineCursor,(Display* a,Window b,Cursor c))
SDL_X11_SYM(صحيح,XDeleteProperty,(Display* a,Window b,Atom c))
SDL_X11_SYM(صحيح,XDestroyWindow,(Display* a,Window b))
SDL_X11_SYM(صحيح,XDisplayKeycodes,(Display* a,صحيح* b,صحيح* c))
SDL_X11_SYM(صحيح,XDrawRectangle,(Display* a,Drawable b,GC c,صحيح d,صحيح e,unsigned صحيح f,unsigned صحيح g))
SDL_X11_SYM(صحيح,XFontsOfFontSet,(XFontSet a,XFontStruct ***b,حرف ***c))
SDL_X11_SYM(صحيح,XFillArc,(Display* a,Drawable b,GC c,صحيح d,صحيح e,unsigned صحيح f,unsigned صحيح g, صحيح h, صحيح i))
SDL_X11_SYM(حرف*,XDisplayName,(_Xconst حرف* a))
SDL_X11_SYM(صحيح,XDrawString,(Display* a,Drawable b,GC c,صحيح d,صحيح e,_Xconst حرف* f,صحيح g))
SDL_X11_SYM(صحيح,XEventsQueued,(Display* a,صحيح b))
SDL_X11_SYM(صحيح,XFillRectangle,(Display* a,Drawable b,GC c,صحيح d,صحيح e,unsigned صحيح f,unsigned صحيح g))
SDL_X11_SYM(Bool,XFilterEvent,(XEvent *event,Window w))
SDL_X11_SYM(صحيح,XFlush,(Display* a))
SDL_X11_SYM(صحيح,XFree,(فراغ*a))
SDL_X11_SYM(صحيح,XFreeCursor,(Display* a,Cursor b))
SDL_X11_SYM(فراغ,XFreeFontSet,(Display* a, XFontSet b))
SDL_X11_SYM(صحيح,XFreeGC,(Display* a,GC b))
SDL_X11_SYM(صحيح,XFreeFont,(Display* a, XFontStruct* b))
SDL_X11_SYM(صحيح,XFreeModifiermap,(XModifierKeymap* a))
SDL_X11_SYM(صحيح,XFreePixmap,(Display* a,Pixmap b))
SDL_X11_SYM(صحيح,XFreeColormap,(Display* a,Colormap b))
SDL_X11_SYM(فراغ,XFreeStringList,(حرف** a))
SDL_X11_SYM(حرف*,XGetAtomName,(Display *a,Atom b))
SDL_X11_SYM(صحيح,XGet_إدخال_Focus,(Display *a,Window *b,صحيح *c))
SDL_X11_SYM(مفتاح_Sym*,XGetKeyboardMapping,(Display *a, مفتاح_Code_2 b, صحيح c, صحيح *d))
SDL_X11_SYM(صحيح,XGetErrorDatabaseText,(Display* a,_Xconst حرف* b,_Xconst حرف* c,_Xconst حرف* d,حرف* e,صحيح f))
SDL_X11_SYM(XModifierKeymap*,XGetModifierMapping,(Display* a))
SDL_X11_SYM(صحيح,XGetPointerControl,(Display* a,صحيح* b,صحيح* c,صحيح* d))
SDL_X11_SYM(Window,XGetSelectionOwner,(Display* a,Atom b))
SDL_X11_SYM(XVisualInfo*,XGetVisualInfo,(Display* a,long b,XVisualInfo* c,صحيح* d))
SDL_X11_SYM(Status,XGetWindowAttributes,(Display* a,Window b,XWindowAttributes* c))
SDL_X11_SYM(صحيح,XGetWindowProperty,(Display* a,Window b,Atom c,long d,long e,Bool f,Atom g,Atom* h,صحيح* i,unsigned long* j,unsigned long *k,unsigned حرف **l))
SDL_X11_SYM(XWMHints*,XGetWMHints,(Display* a,Window b))
SDL_X11_SYM(Status,XGetWMNormalHints,(Display *a,Window b, XSizeHints *c, long *d))
SDL_X11_SYM(صحيح,XIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(صحيح,XGrabKeyboard,(Display* a,Window b,Bool c,صحيح d,صحيح e,Time f))
SDL_X11_SYM(صحيح,XGrabPointer,(Display* a,Window b,Bool c,unsigned صحيح d,صحيح e,صحيح f,Window g,Cursor h,Time i))
SDL_X11_SYM(صحيح,XGrabServer,(Display* a))
SDL_X11_SYM(Status,XIconifyWindow,(Display* a,Window b,صحيح c))
SDL_X11_SYM(مفتاح_Code_2,XKeysymToKeycode,(Display* a,مفتاح_Sym b))
SDL_X11_SYM(حرف*,XKeysymToString,(مفتاح_Sym a))
SDL_X11_SYM(صحيح,XInstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(Atom,XInternAtom,(Display* a,_Xconst حرف* b,Bool c))
SDL_X11_SYM(XPixmap_Format_قيم*,XListPixmapFormats,(Display* a,صحيح* b))
SDL_X11_SYM(XFontStruct*,XLoadQueryFont,(Display* a,_Xconst حرف* b))
SDL_X11_SYM(مفتاح_Sym,XLookupKeysym,(XKeyEvent* a,صحيح b))
SDL_X11_SYM(صحيح,XLookupString,(XKeyEvent* a,حرف* b,صحيح c,مفتاح_Sym* d,XComposeStatus* e))
SDL_X11_SYM(صحيح,XMapRaised,(Display* a,Window b))
SDL_X11_SYM(Status,XMatchVisualInfo,(Display* a,صحيح b,صحيح c,صحيح d,XVisualInfo* e))
SDL_X11_SYM(صحيح,XMissingExtension,(Display* a,_Xconst حرف* b))
SDL_X11_SYM(صحيح,XMoveWindow,(Display* a,Window b,صحيح c,صحيح d))
SDL_X11_SYM(Display*,XOpenDisplay,(_Xconst حرف* a))
SDL_X11_SYM(Status,XInitThreads,(فراغ))
SDL_X11_SYM(صحيح,XPeekEvent,(Display* a,XEvent* b))
SDL_X11_SYM(صحيح,XPending,(Display* a))
SDL_X11_SYM(XImage*,XGetImage,(Display* a,Drawable b,صحيح c, صحيح d,unsigned صحيح e,unsigned صحيح f,unsigned long g,صحيح h))
SDL_X11_SYM(صحيح,XPutImage,(Display* a,Drawable b,GC c,XImage* d,صحيح e,صحيح f,صحيح g,صحيح h,unsigned صحيح i,unsigned صحيح j))
SDL_X11_SYM(صحيح,XQueryKeymap,(Display* a,حرف b[32]))
SDL_X11_SYM(Bool,XQueryPointer,(Display* a,Window b,Window* c,Window* d,صحيح* e,صحيح* f,صحيح* g,صحيح* h,unsigned صحيح* i))
SDL_X11_SYM(صحيح,XRaiseWindow,(Display* a,Window b))
SDL_X11_SYM(صحيح,XReparentWindow,(Display* a,Window b,Window c,صحيح d,صحيح e))
SDL_X11_SYM(صحيح,XResetScreenSaver,(Display* a))
SDL_X11_SYM(صحيح,XResizeWindow,(Display* a,Window b,unsigned صحيح c,unsigned صحيح d))
SDL_X11_SYM(صحيح,XScreen_العدد_Of_Screen,(Screen* a))
SDL_X11_SYM(صحيح,XSelect_إدخال,(Display* a,Window b,long c))
SDL_X11_SYM(Status,XSendEvent,(Display* a,Window b,Bool c,long d,XEvent* e))
SDL_X11_SYM(XErrorHandler,XSetErrorHandler,(XErrorHandler a))
SDL_X11_SYM(صحيح,XSetForeground,(Display* a,GC b,unsigned long c))
SDL_X11_SYM(XIOErrorHandler,XSetIOErrorHandler,(XIOErrorHandler a))
SDL_X11_SYM(صحيح,XSet_إدخال_Focus,(Display *a,Window b,صحيح c,Time d))
SDL_X11_SYM(صحيح,XSetSelectionOwner,(Display* a,Atom b,Window c,Time d))
SDL_X11_SYM(صحيح,XSetTransientForHint,(Display* a,Window b,Window c))
SDL_X11_SYM(فراغ,XSetTextProperty,(Display* a,Window b,XTextProperty* c,Atom d))
SDL_X11_SYM(صحيح,XSetWindowBackground,(Display* a,Window b,unsigned long c))
SDL_X11_SYM(فراغ,XSetWMHints,(Display* a,Window b,XWMHints* c))
SDL_X11_SYM(فراغ,XSetWMNormalHints,(Display* a,Window b,XSizeHints* c))
SDL_X11_SYM(فراغ,XSetWMProperties,(Display* a,Window b,XTextProperty* c,XTextProperty* d,حرف** e,صحيح f,XSizeHints* g,XWMHints* h,XClassHint* i))
SDL_X11_SYM(Status,XSetWMProtocols,(Display* a,Window b,Atom* c,صحيح d))
SDL_X11_SYM(صحيح,XStoreColors,(Display* a,Colormap b,XColor* c,صحيح d))
SDL_X11_SYM(صحيح,XStoreName,(Display* a,Window b,_Xconst حرف* c))
SDL_X11_SYM(Status,XStringListToTextProperty,(حرف** a,صحيح b,XTextProperty* c))
SDL_X11_SYM(صحيح,XSync,(Display* a,Bool b))
SDL_X11_SYM(صحيح,XTextExtents,(XFontStruct* a,_Xconst حرف* b,صحيح c,صحيح* d,صحيح* e,صحيح* f,XCharStruct* g))
SDL_X11_SYM(Bool,XTranslateCoordinates,(Display *a,Window b,Window c,صحيح d,صحيح e,صحيح* f,صحيح* g,Window* h))
SDL_X11_SYM(صحيح,XUndefineCursor,(Display* a,Window b))
SDL_X11_SYM(صحيح,XUngrabKeyboard,(Display* a,Time b))
SDL_X11_SYM(صحيح,XUngrabPointer,(Display* a,Time b))
SDL_X11_SYM(صحيح,XUngrabServer,(Display* a))
SDL_X11_SYM(صحيح,XUninstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(صحيح,XUnloadFont,(Display* a,Font b))
SDL_X11_SYM(صحيح,XWarpPointer,(Display* a,Window b,Window c,صحيح d,صحيح e,unsigned صحيح f,unsigned صحيح g,صحيح h,صحيح i))
SDL_X11_SYM(صحيح,XWindowEvent,(Display* a,Window b,long c,XEvent* d))
SDL_X11_SYM(Status,XWithdrawWindow,(Display* a,Window b,صحيح c))
SDL_X11_SYM(VisualID,XVisualIDFromVisual,(Visual* a))
SDL_X11_SYM(حرف*,XGetDefault,(Display* a,_Xconst حرف* b, _Xconst حرف* c))
SDL_X11_SYM(Bool,XQueryExtension,(Display* a,_Xconst حرف* b,صحيح* c,صحيح* d,صحيح* e))
SDL_X11_SYM(حرف *,XDisplayString,(Display* a))
SDL_X11_SYM(صحيح,XGetErrorText,(Display* a,صحيح b,حرف* c,صحيح d))
SDL_X11_SYM(فراغ,_XEatData,(Display* a,unsigned long b))
SDL_X11_SYM(فراغ,_XFlush,(Display* a))
SDL_X11_SYM(فراغ,_XFlushGCCache,(Display* a,GC b))
SDL_X11_SYM(صحيح,_XRead,(Display* a,حرف* b,long c))
SDL_X11_SYM(فراغ,_XReadPad,(Display* a,حرف* b,long c))
SDL_X11_SYM(فراغ,_XSend,(Display* a,_Xconst حرف* b,long c))
SDL_X11_SYM(Status,_XReply,(Display* a,xReply* b,صحيح c,Bool d))
SDL_X11_SYM(unsigned long,_XSetLastRequestRead,(Display* a,xGenericReply* b))
SDL_X11_SYM(SDL_X11_XSynchronizeRetType,XSynchronize,(Display* a,Bool b))
SDL_X11_SYM(SDL_X11_XESetWireToEventRetType,XESetWireToEvent,(Display* a,صحيح b,SDL_X11_XESetWireToEventRetType c))
SDL_X11_SYM(SDL_X11_XESetEventToWireRetType,XESetEventToWire,(Display* a,صحيح b,SDL_X11_XESetEventToWireRetType c))
SDL_X11_SYM(فراغ,XRefreshKeyboardMapping,(XMappingEvent *a))
SDL_X11_SYM(صحيح,XQuery_شجرة,(Display* a,Window b,Window* c,Window* d,Window** e,unsigned صحيح* f))
SDL_X11_SYM(Bool,XSupportsLocale,(فراغ))
SDL_X11_SYM(Status,XmbTextListToTextProperty,(Display* a,حرف** b,صحيح c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(Region,XCreateRegion,(فراغ))
SDL_X11_SYM(صحيح,XUnionRectWithRegion,(XRectangle *a, Region b, Region c))
SDL_X11_SYM(فراغ,XDestroyRegion,(Region))
SDL_X11_SYM(فراغ,XrmInitialize,(فراغ))
SDL_X11_SYM(حرف*,XResourceManagerString,(Display *display))
SDL_X11_SYM(XrmDatabase,XrmGetStringDatabase,(حرف *data))
SDL_X11_SYM(فراغ,XrmDestroyDatabase,(XrmDatabase db))
SDL_X11_SYM(Bool,XrmGetResource,(XrmDatabase db, حرف* str_name, حرف* str_class, حرف **str_type_return, Xrm_قيمة *))
SDL_X11_SYM(صحيح,XGetPointerMapping,(Display *a, unsigned حرف *b, unsigned صحيح c))

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
SDL_X11_MODULE(XFIXES)
SDL_X11_SYM(PointerBarrier, XFixesCreatePointerBarrier, (Display* a, Window b, صحيح c, صحيح d, صحيح e, صحيح f, صحيح g, صحيح h, صحيح *i))
SDL_X11_SYM(فراغ, XFixesDestroyPointerBarrier, (Display* a, PointerBarrier b))
SDL_X11_SYM(صحيح, XIBarrierReleasePointer,(Display* a,  صحيح b, PointerBarrier c, BarrierEventID d)) // this is actually Xinput2
SDL_X11_SYM(Status, XFixesQueryVersion,(Display* a, صحيح* b, صحيح* c))
SDL_X11_SYM(Status, XFixes_Select_Selection_إدخال, (Display* a, Window b, Atom c, unsigned long d))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
SDL_X11_MODULE(XSYNC)
SDL_X11_SYM(Status, XSyncQueryExtension, (Display* a, صحيح* b, صحيح* c))
SDL_X11_SYM(Status, XSyncInitialize, (Display* a, صحيح* b, صحيح* c))
SDL_X11_SYM(XSyncCounter, XSyncCreateCounter, (Display* a, XSync_قيمة b))
SDL_X11_SYM(Status, XSyncDestroyCounter, (Display* a, XSyncCounter b))
SDL_X11_SYM(Status, XSyncSetCounter, (Display* a, XSyncCounter b, XSync_قيمة c))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XTEST
SDL_X11_MODULE(XTEST)
SDL_X11_SYM(Status, XTestQueryExtension, (Display* a, صحيح* b, صحيح* c))
SDL_X11_SYM(صحيح, XTestFakeMotionEvent, (Display* a, صحيح b, صحيح c, صحيح d, unsigned long e))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
SDL_X11_SYM(Bool,XGetEventData,(Display* a,XGenericEventCookie* b))
SDL_X11_SYM(فراغ,XFreeEventData,(Display* a,XGenericEventCookie* b))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
SDL_X11_SYM(Bool,XkbQueryExtension,(Display* a,صحيح * b,صحيح * c,صحيح * d,صحيح * e, صحيح *f))
SDL_X11_SYM(مفتاح_Sym,XkbKeycodeToKeysym,(Display* a, مفتاح_Code_2 b, unsigned صحيح c, unsigned صحيح d))
SDL_X11_SYM(Bool,XkbSelectEvents,(Display* a, unsigned صحيح b, unsigned صحيح c, unsigned long d))
SDL_X11_SYM(Bool,XkbSelectEventDetails,(Display* a, unsigned صحيح b, unsigned صحيح c, unsigned long d, unsigned long e))
SDL_X11_SYM(Status,XkbGetNames,(Display *a, unsigned صحيح b, XkbDescPtr c))
SDL_X11_SYM(Status,XkbGetState,(Display* a,unsigned صحيح b,XkbStatePtr c))
SDL_X11_SYM(Status,XkbGetUpdatedMap,(Display* a,unsigned صحيح b,XkbDescPtr c))
SDL_X11_SYM(XkbDescPtr,XkbGetMap,(Display* a,unsigned صحيح b,unsigned صحيح c))
SDL_X11_SYM(فراغ,XkbFreeClientMap,(XkbDescPtr a,unsigned صحيح b, Bool c))
SDL_X11_SYM(فراغ,XkbFreeKeyboard,(XkbDescPtr a,unsigned صحيح b, Bool c))
SDL_X11_SYM(Status,XkbRefreshKeyboardMapping,(XkbMapNotifyEvent *a))
SDL_X11_SYM(Bool,XkbSetDetectableAutoRepeat,(Display* a, Bool b, Bool* c))
#endif

#ifdef X_HAVE_UTF8_STRING
SDL_X11_MODULE(UTF8)
SDL_X11_SYM(صحيح,Xutf8TextListToTextProperty,(Display* a,حرف** b,صحيح c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(صحيح,Xutf8LookupString,(XIC a,XKeyPressedEvent* b,حرف* c,صحيح d,مفتاح_Sym* e,Status* f))
SDL_X11_SYM(XIC,XCreateIC,(XIM,...))
SDL_X11_SYM(فراغ,XDestroyIC,(XIC a))
SDL_X11_SYM(حرف*,XGetICValues,(XIC,...))
SDL_X11_SYM(حرف*,XSetICValues,(XIC,...))
SDL_X11_SYM(XVaNestedList,XVaCreateNestedList,(صحيح, ...))
SDL_X11_SYM(فراغ,XSetICFocus,(XIC a))
SDL_X11_SYM(فراغ,XUnsetICFocus,(XIC a))
SDL_X11_SYM(XIM,XOpenIM,(Display* a,بنية _XrmHashBucketRec* b,حرف* c,حرف* d))
SDL_X11_SYM(Status,XCloseIM,(XIM a))
SDL_X11_SYM(حرف*, XSetIMValues,(XIM,...))
SDL_X11_SYM(Bool,XRegisterIMInstantiateCallback,(Display*,بنية _XrmHashBucketRec*,حرف*,حرف*,XIDProc,XPointer))
SDL_X11_SYM(Bool,XUnregisterIMInstantiateCallback,(Display*,بنية _XrmHashBucketRec*,حرف*,حرف*,XIDProc,XPointer))
SDL_X11_SYM(فراغ,Xutf8DrawString,(Display *a, Drawable b, XFontSet c, GC d, صحيح e, صحيح f, _Xconst حرف *g, صحيح h))
SDL_X11_SYM(صحيح,Xutf8TextExtents,(XFontSet a, _Xconst حرف* b, صحيح c, XRectangle* d, XRectangle* e))
SDL_X11_SYM(حرف*,XSetLocaleModifiers,(ثابت حرف *a))
SDL_X11_SYM(حرف*,Xutf8ResetIC,(XIC a))
SDL_X11_SYM(XFontSetExtents*,XExtentsOfFontSet,(XFontSet a))
SDL_X11_SYM(Bool,XContextDependentDrawing,(XFontSet a))
#endif


#ifndef NO_SHARED_MEMORY
SDL_X11_MODULE(SHM)
SDL_X11_SYM(Status,XShmAttach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmDetach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmPutImage,(Display* a,Drawable b,GC c,XImage* d,صحيح e,صحيح f,صحيح g,صحيح h,unsigned صحيح i,unsigned صحيح j,Bool k))
SDL_X11_SYM(Status,XShmGetImage,(Display* a,Drawable b,XImage *c,صحيح d, صحيح e, unsigned long f))
SDL_X11_SYM(XImage*,XShmCreateImage,(Display* a,Visual* b,unsigned صحيح c,صحيح d,حرف* e,XShmSegmentInfo* f,unsigned صحيح g,unsigned صحيح h))
SDL_X11_SYM(Pixmap,XShmCreatePixmap,(Display *a,Drawable b,حرف* c,XShmSegmentInfo* d, unsigned صحيح e, unsigned صحيح f, unsigned صحيح g))
SDL_X11_SYM(Bool,XShmQueryExtension,(Display* a))
SDL_X11_SYM(Status,XShmQueryVersion,(Display* a, صحيح *b, صحيح *c, Bool *d))
SDL_X11_SYM(صحيح,XShmPixmapFormat,(Display* a))
#endif

/*
 * Not required...these only exist in code in headers on some 64-bit platforms,
 *  and are removed via macros elsewhere, so it's safe for them to be missing.
 */
#ifdef LONG64
SDL_X11_MODULE(IO_32BIT)
SDL_X11_SYM(صحيح,_XData32,(Display *dpy,سجل _Xconst long *data,unsigned len))
SDL_X11_SYM(فراغ,_XRead32,(Display *dpy,سجل long *data,long len))
#endif

/*
 * These only show up on some variants of Unix.
 */
#ifdef SDL_PLATFORM_OSF
SDL_X11_MODULE(OSF_ENTRY_POINTS)
SDL_X11_SYM(فراغ,_SmtBufferOverflow,(Display *dpy,سجل smtDisplayPtr p))
SDL_X11_SYM(فراغ,_SmtIpError,(Display *dpy,سجل smtDisplayPtr p,صحيح i))
SDL_X11_SYM(صحيح,ipAllocateData,(ChannelPtr a,IPCard b,IPDataPtr * c))
SDL_X11_SYM(صحيح,ipUnallocateAndSendData,(ChannelPtr a,IPCard b))
#endif

// XCursor support
#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
SDL_X11_MODULE(XCURSOR)
SDL_X11_SYM(XcursorImage*,XcursorImageCreate,(صحيح a,صحيح b))
SDL_X11_SYM(XcursorImages*,XcursorImagesCreate,(صحيح a))
SDL_X11_SYM(فراغ,XcursorImageDestroy,(XcursorImage *a))
SDL_X11_SYM(فراغ,XcursorImagesDestroy,(XcursorImages *a))
SDL_X11_SYM(Cursor,XcursorImageLoadCursor,(Display *a,ثابت XcursorImage *b))
SDL_X11_SYM(Cursor,XcursorImagesLoadCursor,(Display *a,ثابت XcursorImages *b))
SDL_X11_SYM(Cursor,XcursorLibraryLoadCursor,(Display *a, ثابت حرف *b))
#endif

// Xdbe support
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
SDL_X11_MODULE(XDBE)
SDL_X11_SYM(Status,XdbeQueryExtension,(Display *dpy,صحيح *major_version_return,صحيح *minor_version_return))
SDL_X11_SYM(XdbeBackBuffer,XdbeAllocateBackBufferName,(Display *dpy,Window window,XdbeSwapAction swap_action))
SDL_X11_SYM(Status,XdbeDeallocateBackBufferName,(Display *dpy,XdbeBackBuffer buffer))
SDL_X11_SYM(Status,XdbeSwapBuffers,(Display *dpy,XdbeSwapInfo *swap_info,صحيح رقم_windows))
SDL_X11_SYM(Status,XdbeBeginIdiom,(Display *dpy))
SDL_X11_SYM(Status,XdbeEndIdiom,(Display *dpy))
SDL_X11_SYM(XdbeScreenVisualInfo*,XdbeGetVisualInfo,(Display *dpy,Drawable *screen_specifiers,صحيح *رقم_screens))
SDL_X11_SYM(فراغ,XdbeFreeVisualInfo,(XdbeScreenVisualInfo *visual_info))
SDL_X11_SYM(XdbeBackBufferAttributes*,XdbeGetBackBufferAttributes,(Display *dpy,XdbeBackBuffer buffer))
#endif

// XInput2 support for multiple mice, tablets, etc.
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
SDL_X11_MODULE(XINPUT2)
SDL_X11_SYM(XIDeviceInfo*,XIQueryDevice,(Display *a,صحيح b,صحيح *c))
SDL_X11_SYM(فراغ,XIFreeDeviceInfo,(XIDeviceInfo *a))
SDL_X11_SYM(صحيح,XISelectEvents,(Display *a,Window b,XIEventMask *c,صحيح d))
SDL_X11_SYM(صحيح,XIGrabTouchBegin,(Display *a,صحيح b,Window c,صحيح d,XIEventMask *e,صحيح f,XIGrabModifiers *g))
SDL_X11_SYM(صحيح,XIUngrabTouchBegin, (Display *a,صحيح b,Window c, صحيح d,XIGrabModifiers *e))
SDL_X11_SYM(Status,XIQueryVersion,(Display *a,صحيح *b,صحيح *c))
SDL_X11_SYM(XIEventMask*,XIGetSelectedEvents,(Display *a,Window b,صحيح *c))
SDL_X11_SYM(Bool,XIGetClientPointer,(Display *a,Window b,صحيح *c))
SDL_X11_SYM(Bool,XIWarpPointer,(Display *a,صحيح b,Window c,Window d,مزدوج e,مزدوج f,صحيح g,صحيح h,مزدوج i,مزدوج j))
SDL_X11_SYM(Status,XIGetProperty,(Display *a,صحيح b,Atom c,long d,long e,Bool f, Atom g, Atom *h, صحيح *i, unsigned long *j, unsigned long *k, unsigned حرف **l))
#endif

// XRandR support
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
SDL_X11_MODULE(XRANDR)
SDL_X11_SYM(Status,XRRQueryVersion,(Display *dpy,صحيح *major_versionp,صحيح *minor_versionp))
SDL_X11_SYM(Bool,XRRQueryExtension,(Display *dpy,صحيح *event_base_return,صحيح *error_base_return))
SDL_X11_SYM(XRRScreenConfiguration *,XRRGetScreenInfo,(Display *dpy,Drawable draw))
SDL_X11_SYM(SizeID,XRRConfigCurrentConfiguration,(XRRScreenConfiguration *config,Rotation *rotation))
SDL_X11_SYM(short,XRRConfigCurrentRate,(XRRScreenConfiguration *config))
SDL_X11_SYM(short *,XRRConfigRates,(XRRScreenConfiguration *config,صحيح sizeID,صحيح *nrates))
SDL_X11_SYM(XRRScreenSize *,XRRConfigSizes,(XRRScreenConfiguration *config,صحيح *nsizes))
SDL_X11_SYM(Status,XRRSetScreenConfigAndRate,(Display *dpy,XRRScreenConfiguration *config,Drawable draw,صحيح size_index,Rotation rotation,short rate,Time timestamp))
SDL_X11_SYM(فراغ,XRRFreeScreenConfigInfo,(XRRScreenConfiguration *config))
SDL_X11_SYM(فراغ,XRRSetScreenSize,(Display *dpy, Window window,صحيح width, صحيح height,صحيح mmWidth, صحيح mmHeight))
SDL_X11_SYM(Status,XRRGetScreenSizeRange,(Display *dpy, Window window,صحيح *minWidth, صحيح *minHeight, صحيح *maxWidth, صحيح *maxHeight))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResources,(Display *dpy, Window window))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResourcesCurrent,(Display *dpy, Window window))
SDL_X11_SYM(فراغ,XRRFreeScreenResources,(XRRScreenResources *resources))
SDL_X11_SYM(XRROutputInfo *,XRRGetOutputInfo,(Display *dpy, XRRScreenResources *resources, RROutput output))
SDL_X11_SYM(فراغ,XRRFreeOutputInfo,(XRROutputInfo *outputInfo))
SDL_X11_SYM(XRRCrtcInfo *,XRRGetCrtcInfo,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc))
SDL_X11_SYM(فراغ,XRRFreeCrtcInfo,(XRRCrtcInfo *crtcInfo))
SDL_X11_SYM(Status,XRRSetCrtcConfig,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc, Time timestamp, صحيح x, صحيح y, RRMode mode, Rotation rotation, RROutput *outputs, صحيح noutputs))
SDL_X11_SYM(Atom*,XRRListOutputProperties,(Display *dpy, RROutput output, صحيح *nprop))
SDL_X11_SYM(XRRPropertyInfo*,XRRQueryOutputProperty,(Display *dpy,RROutput output, Atom property))
SDL_X11_SYM(صحيح,XRRGetOutputProperty,(Display *dpy,RROutput output, Atom property, long offset, long length, Bool _delete, Bool pending, Atom req_type, Atom *actual_type, صحيح *actual_format, unsigned long *nitems, unsigned long *bytes_after, unsigned حرف **prop))
SDL_X11_SYM(RROutput,XRRGetOutputPrimary,(Display *dpy,Window window))
SDL_X11_SYM(فراغ,XRRSelect_إدخال,(Display *dpy, Window window, صحيح mask))
SDL_X11_SYM(Status,XRRGetCrtcTransform,(Display *dpy,RRCrtc crtc,XRRCrtcTransformAttributes **attributes))
#endif

// MIT-SCREEN-SAVER support
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
SDL_X11_MODULE(XSS)
SDL_X11_SYM(Bool,XScreenSaverQueryExtension,(Display *dpy,صحيح *event_base,صحيح *error_base))
SDL_X11_SYM(Status,XScreenSaverQueryVersion,(Display *dpy,صحيح *major_versionp,صحيح *minor_versionp))
SDL_X11_SYM(فراغ,XScreenSaverSuspend,(Display *dpy,Bool suspend))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
SDL_X11_MODULE(XSHAPE)
SDL_X11_SYM(فراغ,XShapeCombineMask,(Display *dpy,Window dest,صحيح dest_kind,صحيح x_off,صحيح y_off,Pixmap src,صحيح op))
SDL_X11_SYM(فراغ,XShapeCombineRegion,(Display *a,Window b,صحيح c,صحيح d,صحيح e,Region f,صحيح g))
#endif

#undef SDL_X11_MODULE
#undef SDL_X11_SYM

/* *INDENT-ON* */ // clang-format on
