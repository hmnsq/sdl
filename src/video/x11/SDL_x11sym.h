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
SDL_X11_SYM(XSizeHints*,XAllocSizeHints,(શૂન્ય))
SDL_X11_SYM(XWMHints*,XAllocWMHints,(શૂન્ય))
SDL_X11_SYM(XClassHint*,XAllocClassHint,(શૂન્ય))
SDL_X11_SYM(પૂર્ણાંક,XChangePointerControl,(Display* a,Bool b,Bool c,પૂર્ણાંક d,પૂર્ણાંક e,પૂર્ણાંક f))
SDL_X11_SYM(પૂર્ણાંક,XChangeProperty,(Display* a,Window b,Atom c,Atom d,પૂર્ણાંક e,પૂર્ણાંક f,_Xconst unsigned અક્ષર* g,પૂર્ણાંક h))
SDL_X11_SYM(Bool,XCheckIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(પૂર્ણાંક,XClearWindow,(Display* a,Window b))
SDL_X11_SYM(પૂર્ણાંક,XCloseDisplay,(Display* a))
SDL_X11_SYM(પૂર્ણાંક,XConvertSelection,(Display* a,Atom b,Atom c,Atom d,Window e,Time f))
SDL_X11_SYM(Pixmap,XCreateBitmapFromData,(Display *dpy,Drawable d,_Xconst અક્ષર *data,unsigned પૂર્ણાંક width,unsigned પૂર્ણાંક height))
SDL_X11_SYM(Colormap,XCreateColormap,(Display* a,Window b,Visual* c,પૂર્ણાંક d))
SDL_X11_SYM(Cursor,XCreatePixmapCursor,(Display* a,Pixmap b,Pixmap c,XColor* d,XColor* e,unsigned પૂર્ણાંક f,unsigned પૂર્ણાંક g))
SDL_X11_SYM(Cursor,XCreatePixmap,(Display* a,Drawable b,unsigned પૂર્ણાંક d,unsigned પૂર્ણાંક e,unsigned પૂર્ણાંક f))
SDL_X11_SYM(Cursor,XCreateFontCursor,(Display* a,unsigned પૂર્ણાંક b))
SDL_X11_SYM(XFontSet,XCreateFontSet,(Display* a, _Xconst અક્ષર* b, અક્ષર*** c, પૂર્ણાંક* d, અક્ષર** e))
SDL_X11_SYM(GC,XCreateGC,(Display* a,Drawable b,unsigned long c,XGCValues* d))
SDL_X11_SYM(શૂન્ય,XSetFont,(Display* a,GC b,Font c))
SDL_X11_SYM(Status,XAllocColor,(Display *a, Colormap b, XColor *c))
SDL_X11_SYM(XImage*,XCreateImage,(Display* a,Visual* b,unsigned પૂર્ણાંક c,પૂર્ણાંક d,પૂર્ણાંક e,અક્ષર* f,unsigned પૂર્ણાંક g,unsigned પૂર્ણાંક h,પૂર્ણાંક i,પૂર્ણાંક j))
SDL_X11_SYM(Window,XCreateWindow,(Display* a,Window b,પૂર્ણાંક c,પૂર્ણાંક d,unsigned પૂર્ણાંક e,unsigned પૂર્ણાંક f,unsigned પૂર્ણાંક g,પૂર્ણાંક h,unsigned પૂર્ણાંક i,Visual* j,unsigned long k,XSetWindowAttributes* l))
SDL_X11_SYM(શૂન્ય,XCopyArea,(Display *a, Drawable b, Drawable c, GC d, પૂર્ણાંક e, પૂર્ણાંક f, unsigned પૂર્ણાંક g, unsigned પૂર્ણાંક h, પૂર્ણાંક i, પૂર્ણાંક j))
SDL_X11_SYM(પૂર્ણાંક,XDefineCursor,(Display* a,Window b,Cursor c))
SDL_X11_SYM(પૂર્ણાંક,XDeleteProperty,(Display* a,Window b,Atom c))
SDL_X11_SYM(પૂર્ણાંક,XDestroyWindow,(Display* a,Window b))
SDL_X11_SYM(પૂર્ણાંક,XDisplayKeycodes,(Display* a,પૂર્ણાંક* b,પૂર્ણાંક* c))
SDL_X11_SYM(પૂર્ણાંક,XDrawRectangle,(Display* a,Drawable b,GC c,પૂર્ણાંક d,પૂર્ણાંક e,unsigned પૂર્ણાંક f,unsigned પૂર્ણાંક g))
SDL_X11_SYM(પૂર્ણાંક,XFontsOfFontSet,(XFontSet a,XFontStruct ***b,અક્ષર ***c))
SDL_X11_SYM(પૂર્ણાંક,XFillArc,(Display* a,Drawable b,GC c,પૂર્ણાંક d,પૂર્ણાંક e,unsigned પૂર્ણાંક f,unsigned પૂર્ણાંક g, પૂર્ણાંક h, પૂર્ણાંક i))
SDL_X11_SYM(અક્ષર*,XDisplayName,(_Xconst અક્ષર* a))
SDL_X11_SYM(પૂર્ણાંક,XDrawString,(Display* a,Drawable b,GC c,પૂર્ણાંક d,પૂર્ણાંક e,_Xconst અક્ષર* f,પૂર્ણાંક g))
SDL_X11_SYM(પૂર્ણાંક,XEventsQueued,(Display* a,પૂર્ણાંક b))
SDL_X11_SYM(પૂર્ણાંક,XFillRectangle,(Display* a,Drawable b,GC c,પૂર્ણાંક d,પૂર્ણાંક e,unsigned પૂર્ણાંક f,unsigned પૂર્ણાંક g))
SDL_X11_SYM(Bool,XFilterEvent,(XEvent *event,Window w))
SDL_X11_SYM(પૂર્ણાંક,XFlush,(Display* a))
SDL_X11_SYM(પૂર્ણાંક,XFree,(શૂન્ય*a))
SDL_X11_SYM(પૂર્ણાંક,XFreeCursor,(Display* a,Cursor b))
SDL_X11_SYM(શૂન્ય,XFreeFontSet,(Display* a, XFontSet b))
SDL_X11_SYM(પૂર્ણાંક,XFreeGC,(Display* a,GC b))
SDL_X11_SYM(પૂર્ણાંક,XFreeFont,(Display* a, XFontStruct* b))
SDL_X11_SYM(પૂર્ણાંક,XFreeModifiermap,(XModifierKeymap* a))
SDL_X11_SYM(પૂર્ણાંક,XFreePixmap,(Display* a,Pixmap b))
SDL_X11_SYM(પૂર્ણાંક,XFreeColormap,(Display* a,Colormap b))
SDL_X11_SYM(શૂન્ય,XFreeStringList,(અક્ષર** a))
SDL_X11_SYM(અક્ષર*,XGetAtomName,(Display *a,Atom b))
SDL_X11_SYM(પૂર્ણાંક,XGet_આગત_Focus,(Display *a,Window *b,પૂર્ણાંક *c))
SDL_X11_SYM(ચાવી_Sym*,XGetKeyboardMapping,(Display *a, ચાવી_Code_2 b, પૂર્ણાંક c, પૂર્ણાંક *d))
SDL_X11_SYM(પૂર્ણાંક,XGetErrorDatabaseText,(Display* a,_Xconst અક્ષર* b,_Xconst અક્ષર* c,_Xconst અક્ષર* d,અક્ષર* e,પૂર્ણાંક f))
SDL_X11_SYM(XModifierKeymap*,XGetModifierMapping,(Display* a))
SDL_X11_SYM(પૂર્ણાંક,XGetPointerControl,(Display* a,પૂર્ણાંક* b,પૂર્ણાંક* c,પૂર્ણાંક* d))
SDL_X11_SYM(Window,XGetSelectionOwner,(Display* a,Atom b))
SDL_X11_SYM(XVisualInfo*,XGetVisualInfo,(Display* a,long b,XVisualInfo* c,પૂર્ણાંક* d))
SDL_X11_SYM(Status,XGetWindowAttributes,(Display* a,Window b,XWindowAttributes* c))
SDL_X11_SYM(પૂર્ણાંક,XGetWindowProperty,(Display* a,Window b,Atom c,long d,long e,Bool f,Atom g,Atom* h,પૂર્ણાંક* i,unsigned long* j,unsigned long *k,unsigned અક્ષર **l))
SDL_X11_SYM(XWMHints*,XGetWMHints,(Display* a,Window b))
SDL_X11_SYM(Status,XGetWMNormalHints,(Display *a,Window b, XSizeHints *c, long *d))
SDL_X11_SYM(પૂર્ણાંક,XIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(પૂર્ણાંક,XGrabKeyboard,(Display* a,Window b,Bool c,પૂર્ણાંક d,પૂર્ણાંક e,Time f))
SDL_X11_SYM(પૂર્ણાંક,XGrabPointer,(Display* a,Window b,Bool c,unsigned પૂર્ણાંક d,પૂર્ણાંક e,પૂર્ણાંક f,Window g,Cursor h,Time i))
SDL_X11_SYM(પૂર્ણાંક,XGrabServer,(Display* a))
SDL_X11_SYM(Status,XIconifyWindow,(Display* a,Window b,પૂર્ણાંક c))
SDL_X11_SYM(ચાવી_Code_2,XKeysymToKeycode,(Display* a,ચાવી_Sym b))
SDL_X11_SYM(અક્ષર*,XKeysymToString,(ચાવી_Sym a))
SDL_X11_SYM(પૂર્ણાંક,XInstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(Atom,XInternAtom,(Display* a,_Xconst અક્ષર* b,Bool c))
SDL_X11_SYM(XPixmap_Format_કિંમતો*,XListPixmapFormats,(Display* a,પૂર્ણાંક* b))
SDL_X11_SYM(XFontStruct*,XLoadQueryFont,(Display* a,_Xconst અક્ષર* b))
SDL_X11_SYM(ચાવી_Sym,XLookupKeysym,(XKeyEvent* a,પૂર્ણાંક b))
SDL_X11_SYM(પૂર્ણાંક,XLookupString,(XKeyEvent* a,અક્ષર* b,પૂર્ણાંક c,ચાવી_Sym* d,XComposeStatus* e))
SDL_X11_SYM(પૂર્ણાંક,XMapRaised,(Display* a,Window b))
SDL_X11_SYM(Status,XMatchVisualInfo,(Display* a,પૂર્ણાંક b,પૂર્ણાંક c,પૂર્ણાંક d,XVisualInfo* e))
SDL_X11_SYM(પૂર્ણાંક,XMissingExtension,(Display* a,_Xconst અક્ષર* b))
SDL_X11_SYM(પૂર્ણાંક,XMoveWindow,(Display* a,Window b,પૂર્ણાંક c,પૂર્ણાંક d))
SDL_X11_SYM(Display*,XOpenDisplay,(_Xconst અક્ષર* a))
SDL_X11_SYM(Status,XInitThreads,(શૂન્ય))
SDL_X11_SYM(પૂર્ણાંક,XPeekEvent,(Display* a,XEvent* b))
SDL_X11_SYM(પૂર્ણાંક,XPending,(Display* a))
SDL_X11_SYM(XImage*,XGetImage,(Display* a,Drawable b,પૂર્ણાંક c, પૂર્ણાંક d,unsigned પૂર્ણાંક e,unsigned પૂર્ણાંક f,unsigned long g,પૂર્ણાંક h))
SDL_X11_SYM(પૂર્ણાંક,XPutImage,(Display* a,Drawable b,GC c,XImage* d,પૂર્ણાંક e,પૂર્ણાંક f,પૂર્ણાંક g,પૂર્ણાંક h,unsigned પૂર્ણાંક i,unsigned પૂર્ણાંક j))
SDL_X11_SYM(પૂર્ણાંક,XQueryKeymap,(Display* a,અક્ષર b[32]))
SDL_X11_SYM(Bool,XQueryPointer,(Display* a,Window b,Window* c,Window* d,પૂર્ણાંક* e,પૂર્ણાંક* f,પૂર્ણાંક* g,પૂર્ણાંક* h,unsigned પૂર્ણાંક* i))
SDL_X11_SYM(પૂર્ણાંક,XRaiseWindow,(Display* a,Window b))
SDL_X11_SYM(પૂર્ણાંક,XReparentWindow,(Display* a,Window b,Window c,પૂર્ણાંક d,પૂર્ણાંક e))
SDL_X11_SYM(પૂર્ણાંક,XResetScreenSaver,(Display* a))
SDL_X11_SYM(પૂર્ણાંક,XResizeWindow,(Display* a,Window b,unsigned પૂર્ણાંક c,unsigned પૂર્ણાંક d))
SDL_X11_SYM(પૂર્ણાંક,XScreen_સંખ્યા_Of_Screen,(Screen* a))
SDL_X11_SYM(પૂર્ણાંક,XSelect_આગત,(Display* a,Window b,long c))
SDL_X11_SYM(Status,XSendEvent,(Display* a,Window b,Bool c,long d,XEvent* e))
SDL_X11_SYM(XErrorHandler,XSetErrorHandler,(XErrorHandler a))
SDL_X11_SYM(પૂર્ણાંક,XSetForeground,(Display* a,GC b,unsigned long c))
SDL_X11_SYM(XIOErrorHandler,XSetIOErrorHandler,(XIOErrorHandler a))
SDL_X11_SYM(પૂર્ણાંક,XSet_આગત_Focus,(Display *a,Window b,પૂર્ણાંક c,Time d))
SDL_X11_SYM(પૂર્ણાંક,XSetSelectionOwner,(Display* a,Atom b,Window c,Time d))
SDL_X11_SYM(પૂર્ણાંક,XSetTransientForHint,(Display* a,Window b,Window c))
SDL_X11_SYM(શૂન્ય,XSetTextProperty,(Display* a,Window b,XTextProperty* c,Atom d))
SDL_X11_SYM(પૂર્ણાંક,XSetWindowBackground,(Display* a,Window b,unsigned long c))
SDL_X11_SYM(શૂન્ય,XSetWMHints,(Display* a,Window b,XWMHints* c))
SDL_X11_SYM(શૂન્ય,XSetWMNormalHints,(Display* a,Window b,XSizeHints* c))
SDL_X11_SYM(શૂન્ય,XSetWMProperties,(Display* a,Window b,XTextProperty* c,XTextProperty* d,અક્ષર** e,પૂર્ણાંક f,XSizeHints* g,XWMHints* h,XClassHint* i))
SDL_X11_SYM(Status,XSetWMProtocols,(Display* a,Window b,Atom* c,પૂર્ણાંક d))
SDL_X11_SYM(પૂર્ણાંક,XStoreColors,(Display* a,Colormap b,XColor* c,પૂર્ણાંક d))
SDL_X11_SYM(પૂર્ણાંક,XStoreName,(Display* a,Window b,_Xconst અક્ષર* c))
SDL_X11_SYM(Status,XStringListToTextProperty,(અક્ષર** a,પૂર્ણાંક b,XTextProperty* c))
SDL_X11_SYM(પૂર્ણાંક,XSync,(Display* a,Bool b))
SDL_X11_SYM(પૂર્ણાંક,XTextExtents,(XFontStruct* a,_Xconst અક્ષર* b,પૂર્ણાંક c,પૂર્ણાંક* d,પૂર્ણાંક* e,પૂર્ણાંક* f,XCharStruct* g))
SDL_X11_SYM(Bool,XTranslateCoordinates,(Display *a,Window b,Window c,પૂર્ણાંક d,પૂર્ણાંક e,પૂર્ણાંક* f,પૂર્ણાંક* g,Window* h))
SDL_X11_SYM(પૂર્ણાંક,XUndefineCursor,(Display* a,Window b))
SDL_X11_SYM(પૂર્ણાંક,XUngrabKeyboard,(Display* a,Time b))
SDL_X11_SYM(પૂર્ણાંક,XUngrabPointer,(Display* a,Time b))
SDL_X11_SYM(પૂર્ણાંક,XUngrabServer,(Display* a))
SDL_X11_SYM(પૂર્ણાંક,XUninstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(પૂર્ણાંક,XUnloadFont,(Display* a,Font b))
SDL_X11_SYM(પૂર્ણાંક,XWarpPointer,(Display* a,Window b,Window c,પૂર્ણાંક d,પૂર્ણાંક e,unsigned પૂર્ણાંક f,unsigned પૂર્ણાંક g,પૂર્ણાંક h,પૂર્ણાંક i))
SDL_X11_SYM(પૂર્ણાંક,XWindowEvent,(Display* a,Window b,long c,XEvent* d))
SDL_X11_SYM(Status,XWithdrawWindow,(Display* a,Window b,પૂર્ણાંક c))
SDL_X11_SYM(VisualID,XVisualIDFromVisual,(Visual* a))
SDL_X11_SYM(અક્ષર*,XGetDefault,(Display* a,_Xconst અક્ષર* b, _Xconst અક્ષર* c))
SDL_X11_SYM(Bool,XQueryExtension,(Display* a,_Xconst અક્ષર* b,પૂર્ણાંક* c,પૂર્ણાંક* d,પૂર્ણાંક* e))
SDL_X11_SYM(અક્ષર *,XDisplayString,(Display* a))
SDL_X11_SYM(પૂર્ણાંક,XGetErrorText,(Display* a,પૂર્ણાંક b,અક્ષર* c,પૂર્ણાંક d))
SDL_X11_SYM(શૂન્ય,_XEatData,(Display* a,unsigned long b))
SDL_X11_SYM(શૂન્ય,_XFlush,(Display* a))
SDL_X11_SYM(શૂન્ય,_XFlushGCCache,(Display* a,GC b))
SDL_X11_SYM(પૂર્ણાંક,_XRead,(Display* a,અક્ષર* b,long c))
SDL_X11_SYM(શૂન્ય,_XReadPad,(Display* a,અક્ષર* b,long c))
SDL_X11_SYM(શૂન્ય,_XSend,(Display* a,_Xconst અક્ષર* b,long c))
SDL_X11_SYM(Status,_XReply,(Display* a,xReply* b,પૂર્ણાંક c,Bool d))
SDL_X11_SYM(unsigned long,_XSetLastRequestRead,(Display* a,xGenericReply* b))
SDL_X11_SYM(SDL_X11_XSynchronizeRetType,XSynchronize,(Display* a,Bool b))
SDL_X11_SYM(SDL_X11_XESetWireToEventRetType,XESetWireToEvent,(Display* a,પૂર્ણાંક b,SDL_X11_XESetWireToEventRetType c))
SDL_X11_SYM(SDL_X11_XESetEventToWireRetType,XESetEventToWire,(Display* a,પૂર્ણાંક b,SDL_X11_XESetEventToWireRetType c))
SDL_X11_SYM(શૂન્ય,XRefreshKeyboardMapping,(XMappingEvent *a))
SDL_X11_SYM(પૂર્ણાંક,XQuery_વૃક્ષ,(Display* a,Window b,Window* c,Window* d,Window** e,unsigned પૂર્ણાંક* f))
SDL_X11_SYM(Bool,XSupportsLocale,(શૂન્ય))
SDL_X11_SYM(Status,XmbTextListToTextProperty,(Display* a,અક્ષર** b,પૂર્ણાંક c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(Region,XCreateRegion,(શૂન્ય))
SDL_X11_SYM(પૂર્ણાંક,XUnionRectWithRegion,(XRectangle *a, Region b, Region c))
SDL_X11_SYM(શૂન્ય,XDestroyRegion,(Region))
SDL_X11_SYM(શૂન્ય,XrmInitialize,(શૂન્ય))
SDL_X11_SYM(અક્ષર*,XResourceManagerString,(Display *display))
SDL_X11_SYM(XrmDatabase,XrmGetStringDatabase,(અક્ષર *data))
SDL_X11_SYM(શૂન્ય,XrmDestroyDatabase,(XrmDatabase db))
SDL_X11_SYM(Bool,XrmGetResource,(XrmDatabase db, અક્ષર* str_name, અક્ષર* str_class, અક્ષર **str_type_return, Xrm_કિંમત *))
SDL_X11_SYM(પૂર્ણાંક,XGetPointerMapping,(Display *a, unsigned અક્ષર *b, unsigned પૂર્ણાંક c))

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
SDL_X11_MODULE(XFIXES)
SDL_X11_SYM(PointerBarrier, XFixesCreatePointerBarrier, (Display* a, Window b, પૂર્ણાંક c, પૂર્ણાંક d, પૂર્ણાંક e, પૂર્ણાંક f, પૂર્ણાંક g, પૂર્ણાંક h, પૂર્ણાંક *i))
SDL_X11_SYM(શૂન્ય, XFixesDestroyPointerBarrier, (Display* a, PointerBarrier b))
SDL_X11_SYM(પૂર્ણાંક, XIBarrierReleasePointer,(Display* a,  પૂર્ણાંક b, PointerBarrier c, BarrierEventID d)) // this is actually Xinput2
SDL_X11_SYM(Status, XFixesQueryVersion,(Display* a, પૂર્ણાંક* b, પૂર્ણાંક* c))
SDL_X11_SYM(Status, XFixes_Select_Selection_આગત, (Display* a, Window b, Atom c, unsigned long d))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
SDL_X11_MODULE(XSYNC)
SDL_X11_SYM(Status, XSyncQueryExtension, (Display* a, પૂર્ણાંક* b, પૂર્ણાંક* c))
SDL_X11_SYM(Status, XSyncInitialize, (Display* a, પૂર્ણાંક* b, પૂર્ણાંક* c))
SDL_X11_SYM(XSyncCounter, XSyncCreateCounter, (Display* a, XSync_કિંમત b))
SDL_X11_SYM(Status, XSyncDestroyCounter, (Display* a, XSyncCounter b))
SDL_X11_SYM(Status, XSyncSetCounter, (Display* a, XSyncCounter b, XSync_કિંમત c))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XTEST
SDL_X11_MODULE(XTEST)
SDL_X11_SYM(Status, XTestQueryExtension, (Display* a, પૂર્ણાંક* b, પૂર્ણાંક* c))
SDL_X11_SYM(પૂર્ણાંક, XTestFakeMotionEvent, (Display* a, પૂર્ણાંક b, પૂર્ણાંક c, પૂર્ણાંક d, unsigned long e))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
SDL_X11_SYM(Bool,XGetEventData,(Display* a,XGenericEventCookie* b))
SDL_X11_SYM(શૂન્ય,XFreeEventData,(Display* a,XGenericEventCookie* b))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
SDL_X11_SYM(Bool,XkbQueryExtension,(Display* a,પૂર્ણાંક * b,પૂર્ણાંક * c,પૂર્ણાંક * d,પૂર્ણાંક * e, પૂર્ણાંક *f))
SDL_X11_SYM(ચાવી_Sym,XkbKeycodeToKeysym,(Display* a, ચાવી_Code_2 b, unsigned પૂર્ણાંક c, unsigned પૂર્ણાંક d))
SDL_X11_SYM(Bool,XkbSelectEvents,(Display* a, unsigned પૂર્ણાંક b, unsigned પૂર્ણાંક c, unsigned long d))
SDL_X11_SYM(Bool,XkbSelectEventDetails,(Display* a, unsigned પૂર્ણાંક b, unsigned પૂર્ણાંક c, unsigned long d, unsigned long e))
SDL_X11_SYM(Status,XkbGetNames,(Display *a, unsigned પૂર્ણાંક b, XkbDescPtr c))
SDL_X11_SYM(Status,XkbGetState,(Display* a,unsigned પૂર્ણાંક b,XkbStatePtr c))
SDL_X11_SYM(Status,XkbGetUpdatedMap,(Display* a,unsigned પૂર્ણાંક b,XkbDescPtr c))
SDL_X11_SYM(XkbDescPtr,XkbGetMap,(Display* a,unsigned પૂર્ણાંક b,unsigned પૂર્ણાંક c))
SDL_X11_SYM(શૂન્ય,XkbFreeClientMap,(XkbDescPtr a,unsigned પૂર્ણાંક b, Bool c))
SDL_X11_SYM(શૂન્ય,XkbFreeKeyboard,(XkbDescPtr a,unsigned પૂર્ણાંક b, Bool c))
SDL_X11_SYM(Status,XkbRefreshKeyboardMapping,(XkbMapNotifyEvent *a))
SDL_X11_SYM(Bool,XkbSetDetectableAutoRepeat,(Display* a, Bool b, Bool* c))
#endif

#ifdef X_HAVE_UTF8_STRING
SDL_X11_MODULE(UTF8)
SDL_X11_SYM(પૂર્ણાંક,Xutf8TextListToTextProperty,(Display* a,અક્ષર** b,પૂર્ણાંક c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(પૂર્ણાંક,Xutf8LookupString,(XIC a,XKeyPressedEvent* b,અક્ષર* c,પૂર્ણાંક d,ચાવી_Sym* e,Status* f))
SDL_X11_SYM(XIC,XCreateIC,(XIM,...))
SDL_X11_SYM(શૂન્ય,XDestroyIC,(XIC a))
SDL_X11_SYM(અક્ષર*,XGetICValues,(XIC,...))
SDL_X11_SYM(અક્ષર*,XSetICValues,(XIC,...))
SDL_X11_SYM(XVaNestedList,XVaCreateNestedList,(પૂર્ણાંક, ...))
SDL_X11_SYM(શૂન્ય,XSetICFocus,(XIC a))
SDL_X11_SYM(શૂન્ય,XUnsetICFocus,(XIC a))
SDL_X11_SYM(XIM,XOpenIM,(Display* a,સંરચના _XrmHashBucketRec* b,અક્ષર* c,અક્ષર* d))
SDL_X11_SYM(Status,XCloseIM,(XIM a))
SDL_X11_SYM(અક્ષર*, XSetIMValues,(XIM,...))
SDL_X11_SYM(Bool,XRegisterIMInstantiateCallback,(Display*,સંરચના _XrmHashBucketRec*,અક્ષર*,અક્ષર*,XIDProc,XPointer))
SDL_X11_SYM(Bool,XUnregisterIMInstantiateCallback,(Display*,સંરચના _XrmHashBucketRec*,અક્ષર*,અક્ષર*,XIDProc,XPointer))
SDL_X11_SYM(શૂન્ય,Xutf8DrawString,(Display *a, Drawable b, XFontSet c, GC d, પૂર્ણાંક e, પૂર્ણાંક f, _Xconst અક્ષર *g, પૂર્ણાંક h))
SDL_X11_SYM(પૂર્ણાંક,Xutf8TextExtents,(XFontSet a, _Xconst અક્ષર* b, પૂર્ણાંક c, XRectangle* d, XRectangle* e))
SDL_X11_SYM(અક્ષર*,XSetLocaleModifiers,(અચલ અક્ષર *a))
SDL_X11_SYM(અક્ષર*,Xutf8ResetIC,(XIC a))
SDL_X11_SYM(XFontSetExtents*,XExtentsOfFontSet,(XFontSet a))
SDL_X11_SYM(Bool,XContextDependentDrawing,(XFontSet a))
#endif


#ifndef NO_SHARED_MEMORY
SDL_X11_MODULE(SHM)
SDL_X11_SYM(Status,XShmAttach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmDetach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmPutImage,(Display* a,Drawable b,GC c,XImage* d,પૂર્ણાંક e,પૂર્ણાંક f,પૂર્ણાંક g,પૂર્ણાંક h,unsigned પૂર્ણાંક i,unsigned પૂર્ણાંક j,Bool k))
SDL_X11_SYM(Status,XShmGetImage,(Display* a,Drawable b,XImage *c,પૂર્ણાંક d, પૂર્ણાંક e, unsigned long f))
SDL_X11_SYM(XImage*,XShmCreateImage,(Display* a,Visual* b,unsigned પૂર્ણાંક c,પૂર્ણાંક d,અક્ષર* e,XShmSegmentInfo* f,unsigned પૂર્ણાંક g,unsigned પૂર્ણાંક h))
SDL_X11_SYM(Pixmap,XShmCreatePixmap,(Display *a,Drawable b,અક્ષર* c,XShmSegmentInfo* d, unsigned પૂર્ણાંક e, unsigned પૂર્ણાંક f, unsigned પૂર્ણાંક g))
SDL_X11_SYM(Bool,XShmQueryExtension,(Display* a))
SDL_X11_SYM(Status,XShmQueryVersion,(Display* a, પૂર્ણાંક *b, પૂર્ણાંક *c, Bool *d))
SDL_X11_SYM(પૂર્ણાંક,XShmPixmapFormat,(Display* a))
#endif

/*
 * Not required...these only exist in code in headers on some 64-bit platforms,
 *  and are removed via macros elsewhere, so it's safe for them to be missing.
 */
#ifdef LONG64
SDL_X11_MODULE(IO_32BIT)
SDL_X11_SYM(પૂર્ણાંક,_XData32,(Display *dpy,નોંધણી _Xconst long *data,unsigned len))
SDL_X11_SYM(શૂન્ય,_XRead32,(Display *dpy,નોંધણી long *data,long len))
#endif

/*
 * These only show up on some variants of Unix.
 */
#ifdef SDL_PLATFORM_OSF
SDL_X11_MODULE(OSF_ENTRY_POINTS)
SDL_X11_SYM(શૂન્ય,_SmtBufferOverflow,(Display *dpy,નોંધણી smtDisplayPtr p))
SDL_X11_SYM(શૂન્ય,_SmtIpError,(Display *dpy,નોંધણી smtDisplayPtr p,પૂર્ણાંક i))
SDL_X11_SYM(પૂર્ણાંક,ipAllocateData,(ChannelPtr a,IPCard b,IPDataPtr * c))
SDL_X11_SYM(પૂર્ણાંક,ipUnallocateAndSendData,(ChannelPtr a,IPCard b))
#endif

// XCursor support
#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
SDL_X11_MODULE(XCURSOR)
SDL_X11_SYM(XcursorImage*,XcursorImageCreate,(પૂર્ણાંક a,પૂર્ણાંક b))
SDL_X11_SYM(XcursorImages*,XcursorImagesCreate,(પૂર્ણાંક a))
SDL_X11_SYM(શૂન્ય,XcursorImageDestroy,(XcursorImage *a))
SDL_X11_SYM(શૂન્ય,XcursorImagesDestroy,(XcursorImages *a))
SDL_X11_SYM(Cursor,XcursorImageLoadCursor,(Display *a,અચલ XcursorImage *b))
SDL_X11_SYM(Cursor,XcursorImagesLoadCursor,(Display *a,અચલ XcursorImages *b))
SDL_X11_SYM(Cursor,XcursorLibraryLoadCursor,(Display *a, અચલ અક્ષર *b))
#endif

// Xdbe support
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
SDL_X11_MODULE(XDBE)
SDL_X11_SYM(Status,XdbeQueryExtension,(Display *dpy,પૂર્ણાંક *major_version_return,પૂર્ણાંક *minor_version_return))
SDL_X11_SYM(XdbeBackBuffer,XdbeAllocateBackBufferName,(Display *dpy,Window window,XdbeSwapAction swap_action))
SDL_X11_SYM(Status,XdbeDeallocateBackBufferName,(Display *dpy,XdbeBackBuffer buffer))
SDL_X11_SYM(Status,XdbeSwapBuffers,(Display *dpy,XdbeSwapInfo *swap_info,પૂર્ણાંક અંક_windows))
SDL_X11_SYM(Status,XdbeBeginIdiom,(Display *dpy))
SDL_X11_SYM(Status,XdbeEndIdiom,(Display *dpy))
SDL_X11_SYM(XdbeScreenVisualInfo*,XdbeGetVisualInfo,(Display *dpy,Drawable *screen_specifiers,પૂર્ણાંક *અંક_screens))
SDL_X11_SYM(શૂન્ય,XdbeFreeVisualInfo,(XdbeScreenVisualInfo *visual_info))
SDL_X11_SYM(XdbeBackBufferAttributes*,XdbeGetBackBufferAttributes,(Display *dpy,XdbeBackBuffer buffer))
#endif

// XInput2 support for multiple mice, tablets, etc.
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
SDL_X11_MODULE(XINPUT2)
SDL_X11_SYM(XIDeviceInfo*,XIQueryDevice,(Display *a,પૂર્ણાંક b,પૂર્ણાંક *c))
SDL_X11_SYM(શૂન્ય,XIFreeDeviceInfo,(XIDeviceInfo *a))
SDL_X11_SYM(પૂર્ણાંક,XISelectEvents,(Display *a,Window b,XIEventMask *c,પૂર્ણાંક d))
SDL_X11_SYM(પૂર્ણાંક,XIGrabTouchBegin,(Display *a,પૂર્ણાંક b,Window c,પૂર્ણાંક d,XIEventMask *e,પૂર્ણાંક f,XIGrabModifiers *g))
SDL_X11_SYM(પૂર્ણાંક,XIUngrabTouchBegin, (Display *a,પૂર્ણાંક b,Window c, પૂર્ણાંક d,XIGrabModifiers *e))
SDL_X11_SYM(Status,XIQueryVersion,(Display *a,પૂર્ણાંક *b,પૂર્ણાંક *c))
SDL_X11_SYM(XIEventMask*,XIGetSelectedEvents,(Display *a,Window b,પૂર્ણાંક *c))
SDL_X11_SYM(Bool,XIGetClientPointer,(Display *a,Window b,પૂર્ણાંક *c))
SDL_X11_SYM(Bool,XIWarpPointer,(Display *a,પૂર્ણાંક b,Window c,Window d,દ્વિગુણ e,દ્વિગુણ f,પૂર્ણાંક g,પૂર્ણાંક h,દ્વિગુણ i,દ્વિગુણ j))
SDL_X11_SYM(Status,XIGetProperty,(Display *a,પૂર્ણાંક b,Atom c,long d,long e,Bool f, Atom g, Atom *h, પૂર્ણાંક *i, unsigned long *j, unsigned long *k, unsigned અક્ષર **l))
#endif

// XRandR support
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
SDL_X11_MODULE(XRANDR)
SDL_X11_SYM(Status,XRRQueryVersion,(Display *dpy,પૂર્ણાંક *major_versionp,પૂર્ણાંક *minor_versionp))
SDL_X11_SYM(Bool,XRRQueryExtension,(Display *dpy,પૂર્ણાંક *event_base_return,પૂર્ણાંક *error_base_return))
SDL_X11_SYM(XRRScreenConfiguration *,XRRGetScreenInfo,(Display *dpy,Drawable draw))
SDL_X11_SYM(SizeID,XRRConfigCurrentConfiguration,(XRRScreenConfiguration *config,Rotation *rotation))
SDL_X11_SYM(short,XRRConfigCurrentRate,(XRRScreenConfiguration *config))
SDL_X11_SYM(short *,XRRConfigRates,(XRRScreenConfiguration *config,પૂર્ણાંક sizeID,પૂર્ણાંક *nrates))
SDL_X11_SYM(XRRScreenSize *,XRRConfigSizes,(XRRScreenConfiguration *config,પૂર્ણાંક *nsizes))
SDL_X11_SYM(Status,XRRSetScreenConfigAndRate,(Display *dpy,XRRScreenConfiguration *config,Drawable draw,પૂર્ણાંક size_index,Rotation rotation,short rate,Time timestamp))
SDL_X11_SYM(શૂન્ય,XRRFreeScreenConfigInfo,(XRRScreenConfiguration *config))
SDL_X11_SYM(શૂન્ય,XRRSetScreenSize,(Display *dpy, Window window,પૂર્ણાંક width, પૂર્ણાંક height,પૂર્ણાંક mmWidth, પૂર્ણાંક mmHeight))
SDL_X11_SYM(Status,XRRGetScreenSizeRange,(Display *dpy, Window window,પૂર્ણાંક *minWidth, પૂર્ણાંક *minHeight, પૂર્ણાંક *maxWidth, પૂર્ણાંક *maxHeight))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResources,(Display *dpy, Window window))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResourcesCurrent,(Display *dpy, Window window))
SDL_X11_SYM(શૂન્ય,XRRFreeScreenResources,(XRRScreenResources *resources))
SDL_X11_SYM(XRROutputInfo *,XRRGetOutputInfo,(Display *dpy, XRRScreenResources *resources, RROutput output))
SDL_X11_SYM(શૂન્ય,XRRFreeOutputInfo,(XRROutputInfo *outputInfo))
SDL_X11_SYM(XRRCrtcInfo *,XRRGetCrtcInfo,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc))
SDL_X11_SYM(શૂન્ય,XRRFreeCrtcInfo,(XRRCrtcInfo *crtcInfo))
SDL_X11_SYM(Status,XRRSetCrtcConfig,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc, Time timestamp, પૂર્ણાંક x, પૂર્ણાંક y, RRMode mode, Rotation rotation, RROutput *outputs, પૂર્ણાંક noutputs))
SDL_X11_SYM(Atom*,XRRListOutputProperties,(Display *dpy, RROutput output, પૂર્ણાંક *nprop))
SDL_X11_SYM(XRRPropertyInfo*,XRRQueryOutputProperty,(Display *dpy,RROutput output, Atom property))
SDL_X11_SYM(પૂર્ણાંક,XRRGetOutputProperty,(Display *dpy,RROutput output, Atom property, long offset, long length, Bool _delete, Bool pending, Atom req_type, Atom *actual_type, પૂર્ણાંક *actual_format, unsigned long *nitems, unsigned long *bytes_after, unsigned અક્ષર **prop))
SDL_X11_SYM(RROutput,XRRGetOutputPrimary,(Display *dpy,Window window))
SDL_X11_SYM(શૂન્ય,XRRSelect_આગત,(Display *dpy, Window window, પૂર્ણાંક mask))
SDL_X11_SYM(Status,XRRGetCrtcTransform,(Display *dpy,RRCrtc crtc,XRRCrtcTransformAttributes **attributes))
#endif

// MIT-SCREEN-SAVER support
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
SDL_X11_MODULE(XSS)
SDL_X11_SYM(Bool,XScreenSaverQueryExtension,(Display *dpy,પૂર્ણાંક *event_base,પૂર્ણાંક *error_base))
SDL_X11_SYM(Status,XScreenSaverQueryVersion,(Display *dpy,પૂર્ણાંક *major_versionp,પૂર્ણાંક *minor_versionp))
SDL_X11_SYM(શૂન્ય,XScreenSaverSuspend,(Display *dpy,Bool suspend))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
SDL_X11_MODULE(XSHAPE)
SDL_X11_SYM(શૂન્ય,XShapeCombineMask,(Display *dpy,Window dest,પૂર્ણાંક dest_kind,પૂર્ણાંક x_off,પૂર્ણાંક y_off,Pixmap src,પૂર્ણાંક op))
SDL_X11_SYM(શૂન્ય,XShapeCombineRegion,(Display *a,Window b,પૂર્ણાંક c,પૂર્ણાંક d,પૂર્ણાંક e,Region f,પૂર્ણાંક g))
#endif

#undef SDL_X11_MODULE
#undef SDL_X11_SYM

/* *INDENT-ON* */ // clang-format on
