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
SDL_X11_SYM(XSizeHints*,XAllocSizeHints,(शून्य))
SDL_X11_SYM(XWMHints*,XAllocWMHints,(शून्य))
SDL_X11_SYM(XClassHint*,XAllocClassHint,(शून्य))
SDL_X11_SYM(पूर्णाङ्क,XChangePointerControl,(Display* a,Bool b,Bool c,पूर्णाङ्क d,पूर्णाङ्क e,पूर्णाङ्क f))
SDL_X11_SYM(पूर्णाङ्क,XChangeProperty,(Display* a,Window b,Atom c,Atom d,पूर्णाङ्क e,पूर्णाङ्क f,_Xconst अचिन्हित वर्ण* g,पूर्णाङ्क h))
SDL_X11_SYM(Bool,XCheckIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(पूर्णाङ्क,XClearWindow,(Display* a,Window b))
SDL_X11_SYM(पूर्णाङ्क,XCloseDisplay,(Display* a))
SDL_X11_SYM(पूर्णाङ्क,XConvertSelection,(Display* a,Atom b,Atom c,Atom d,Window e,Time f))
SDL_X11_SYM(Pixmap,XCreateBitmapFromData,(Display *dpy,Drawable d,_Xconst वर्ण *data,अचिन्हित पूर्णाङ्क width,अचिन्हित पूर्णाङ्क height))
SDL_X11_SYM(Colormap,XCreateColormap,(Display* a,Window b,Visual* c,पूर्णाङ्क d))
SDL_X11_SYM(Cursor,XCreatePixmapCursor,(Display* a,Pixmap b,Pixmap c,XColor* d,XColor* e,अचिन्हित पूर्णाङ्क f,अचिन्हित पूर्णाङ्क g))
SDL_X11_SYM(Cursor,XCreatePixmap,(Display* a,Drawable b,अचिन्हित पूर्णाङ्क d,अचिन्हित पूर्णाङ्क e,अचिन्हित पूर्णाङ्क f))
SDL_X11_SYM(Cursor,XCreateFontCursor,(Display* a,अचिन्हित पूर्णाङ्क b))
SDL_X11_SYM(XFontSet,XCreateFontSet,(Display* a, _Xconst वर्ण* b, वर्ण*** c, पूर्णाङ्क* d, वर्ण** e))
SDL_X11_SYM(GC,XCreateGC,(Display* a,Drawable b,अचिन्हित दीर्घ c,XGCValues* d))
SDL_X11_SYM(शून्य,XSetFont,(Display* a,GC b,Font c))
SDL_X11_SYM(Status,XAllocColor,(Display *a, Colormap b, XColor *c))
SDL_X11_SYM(XImage*,XCreateImage,(Display* a,Visual* b,अचिन्हित पूर्णाङ्क c,पूर्णाङ्क d,पूर्णाङ्क e,वर्ण* f,अचिन्हित पूर्णाङ्क g,अचिन्हित पूर्णाङ्क h,पूर्णाङ्क i,पूर्णाङ्क j))
SDL_X11_SYM(Window,XCreateWindow,(Display* a,Window b,पूर्णाङ्क c,पूर्णाङ्क d,अचिन्हित पूर्णाङ्क e,अचिन्हित पूर्णाङ्क f,अचिन्हित पूर्णाङ्क g,पूर्णाङ्क h,अचिन्हित पूर्णाङ्क i,Visual* j,अचिन्हित दीर्घ k,XSetWindowAttributes* l))
SDL_X11_SYM(शून्य,XCopyArea,(Display *a, Drawable b, Drawable c, GC d, पूर्णाङ्क e, पूर्णाङ्क f, अचिन्हित पूर्णाङ्क g, अचिन्हित पूर्णाङ्क h, पूर्णाङ्क i, पूर्णाङ्क j))
SDL_X11_SYM(पूर्णाङ्क,XDefineCursor,(Display* a,Window b,Cursor c))
SDL_X11_SYM(पूर्णाङ्क,XDeleteProperty,(Display* a,Window b,Atom c))
SDL_X11_SYM(पूर्णाङ्क,XDestroyWindow,(Display* a,Window b))
SDL_X11_SYM(पूर्णाङ्क,XDisplayKeycodes,(Display* a,पूर्णाङ्क* b,पूर्णाङ्क* c))
SDL_X11_SYM(पूर्णाङ्क,XDrawRectangle,(Display* a,Drawable b,GC c,पूर्णाङ्क d,पूर्णाङ्क e,अचिन्हित पूर्णाङ्क f,अचिन्हित पूर्णाङ्क g))
SDL_X11_SYM(पूर्णाङ्क,XFontsOfFontSet,(XFontSet a,XFontStruct ***b,वर्ण ***c))
SDL_X11_SYM(पूर्णाङ्क,XFillArc,(Display* a,Drawable b,GC c,पूर्णाङ्क d,पूर्णाङ्क e,अचिन्हित पूर्णाङ्क f,अचिन्हित पूर्णाङ्क g, पूर्णाङ्क h, पूर्णाङ्क i))
SDL_X11_SYM(वर्ण*,XDisplayName,(_Xconst वर्ण* a))
SDL_X11_SYM(पूर्णाङ्क,XDrawString,(Display* a,Drawable b,GC c,पूर्णाङ्क d,पूर्णाङ्क e,_Xconst वर्ण* f,पूर्णाङ्क g))
SDL_X11_SYM(पूर्णाङ्क,XEventsQueued,(Display* a,पूर्णाङ्क b))
SDL_X11_SYM(पूर्णाङ्क,XFillRectangle,(Display* a,Drawable b,GC c,पूर्णाङ्क d,पूर्णाङ्क e,अचिन्हित पूर्णाङ्क f,अचिन्हित पूर्णाङ्क g))
SDL_X11_SYM(Bool,XFilterEvent,(XEvent *event,Window w))
SDL_X11_SYM(पूर्णाङ्क,XFlush,(Display* a))
SDL_X11_SYM(पूर्णाङ्क,XFree,(शून्य*a))
SDL_X11_SYM(पूर्णाङ्क,XFreeCursor,(Display* a,Cursor b))
SDL_X11_SYM(शून्य,XFreeFontSet,(Display* a, XFontSet b))
SDL_X11_SYM(पूर्णाङ्क,XFreeGC,(Display* a,GC b))
SDL_X11_SYM(पूर्णाङ्क,XFreeFont,(Display* a, XFontStruct* b))
SDL_X11_SYM(पूर्णाङ्क,XFreeModifiermap,(XModifierKeymap* a))
SDL_X11_SYM(पूर्णाङ्क,XFreePixmap,(Display* a,Pixmap b))
SDL_X11_SYM(पूर्णाङ्क,XFreeColormap,(Display* a,Colormap b))
SDL_X11_SYM(शून्य,XFreeStringList,(वर्ण** a))
SDL_X11_SYM(वर्ण*,XGetAtomName,(Display *a,Atom b))
SDL_X11_SYM(पूर्णाङ्क,XGet_आगत_Focus,(Display *a,Window *b,पूर्णाङ्क *c))
SDL_X11_SYM(साँचो_Sym*,XGetKeyboardMapping,(Display *a, साँचो_Code_2 b, पूर्णाङ्क c, पूर्णाङ्क *d))
SDL_X11_SYM(पूर्णाङ्क,XGetErrorDatabaseText,(Display* a,_Xconst वर्ण* b,_Xconst वर्ण* c,_Xconst वर्ण* d,वर्ण* e,पूर्णाङ्क f))
SDL_X11_SYM(XModifierKeymap*,XGetModifierMapping,(Display* a))
SDL_X11_SYM(पूर्णाङ्क,XGetPointerControl,(Display* a,पूर्णाङ्क* b,पूर्णाङ्क* c,पूर्णाङ्क* d))
SDL_X11_SYM(Window,XGetSelectionOwner,(Display* a,Atom b))
SDL_X11_SYM(XVisualInfo*,XGetVisualInfo,(Display* a,दीर्घ b,XVisualInfo* c,पूर्णाङ्क* d))
SDL_X11_SYM(Status,XGetWindowAttributes,(Display* a,Window b,XWindowAttributes* c))
SDL_X11_SYM(पूर्णाङ्क,XGetWindowProperty,(Display* a,Window b,Atom c,दीर्घ d,दीर्घ e,Bool f,Atom g,Atom* h,पूर्णाङ्क* i,अचिन्हित दीर्घ* j,अचिन्हित दीर्घ *k,अचिन्हित वर्ण **l))
SDL_X11_SYM(XWMHints*,XGetWMHints,(Display* a,Window b))
SDL_X11_SYM(Status,XGetWMNormalHints,(Display *a,Window b, XSizeHints *c, दीर्घ *d))
SDL_X11_SYM(पूर्णाङ्क,XIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(पूर्णाङ्क,XGrabKeyboard,(Display* a,Window b,Bool c,पूर्णाङ्क d,पूर्णाङ्क e,Time f))
SDL_X11_SYM(पूर्णाङ्क,XGrabPointer,(Display* a,Window b,Bool c,अचिन्हित पूर्णाङ्क d,पूर्णाङ्क e,पूर्णाङ्क f,Window g,Cursor h,Time i))
SDL_X11_SYM(पूर्णाङ्क,XGrabServer,(Display* a))
SDL_X11_SYM(Status,XIconifyWindow,(Display* a,Window b,पूर्णाङ्क c))
SDL_X11_SYM(साँचो_Code_2,XKeysymToKeycode,(Display* a,साँचो_Sym b))
SDL_X11_SYM(वर्ण*,XKeysymToString,(साँचो_Sym a))
SDL_X11_SYM(पूर्णाङ्क,XInstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(Atom,XInternAtom,(Display* a,_Xconst वर्ण* b,Bool c))
SDL_X11_SYM(XPixmap_Format_मानहरू*,XListPixmapFormats,(Display* a,पूर्णाङ्क* b))
SDL_X11_SYM(XFontStruct*,XLoadQueryFont,(Display* a,_Xconst वर्ण* b))
SDL_X11_SYM(साँचो_Sym,XLookupKeysym,(XKeyEvent* a,पूर्णाङ्क b))
SDL_X11_SYM(पूर्णाङ्क,XLookupString,(XKeyEvent* a,वर्ण* b,पूर्णाङ्क c,साँचो_Sym* d,XComposeStatus* e))
SDL_X11_SYM(पूर्णाङ्क,XMapRaised,(Display* a,Window b))
SDL_X11_SYM(Status,XMatchVisualInfo,(Display* a,पूर्णाङ्क b,पूर्णाङ्क c,पूर्णाङ्क d,XVisualInfo* e))
SDL_X11_SYM(पूर्णाङ्क,XMissingExtension,(Display* a,_Xconst वर्ण* b))
SDL_X11_SYM(पूर्णाङ्क,XMoveWindow,(Display* a,Window b,पूर्णाङ्क c,पूर्णाङ्क d))
SDL_X11_SYM(Display*,XOpenDisplay,(_Xconst वर्ण* a))
SDL_X11_SYM(Status,XInitThreads,(शून्य))
SDL_X11_SYM(पूर्णाङ्क,XPeekEvent,(Display* a,XEvent* b))
SDL_X11_SYM(पूर्णाङ्क,XPending,(Display* a))
SDL_X11_SYM(XImage*,XGetImage,(Display* a,Drawable b,पूर्णाङ्क c, पूर्णाङ्क d,अचिन्हित पूर्णाङ्क e,अचिन्हित पूर्णाङ्क f,अचिन्हित दीर्घ g,पूर्णाङ्क h))
SDL_X11_SYM(पूर्णाङ्क,XPutImage,(Display* a,Drawable b,GC c,XImage* d,पूर्णाङ्क e,पूर्णाङ्क f,पूर्णाङ्क g,पूर्णाङ्क h,अचिन्हित पूर्णाङ्क i,अचिन्हित पूर्णाङ्क j))
SDL_X11_SYM(पूर्णाङ्क,XQueryKeymap,(Display* a,वर्ण b[32]))
SDL_X11_SYM(Bool,XQueryPointer,(Display* a,Window b,Window* c,Window* d,पूर्णाङ्क* e,पूर्णाङ्क* f,पूर्णाङ्क* g,पूर्णाङ्क* h,अचिन्हित पूर्णाङ्क* i))
SDL_X11_SYM(पूर्णाङ्क,XRaiseWindow,(Display* a,Window b))
SDL_X11_SYM(पूर्णाङ्क,XReparentWindow,(Display* a,Window b,Window c,पूर्णाङ्क d,पूर्णाङ्क e))
SDL_X11_SYM(पूर्णाङ्क,XResetScreenSaver,(Display* a))
SDL_X11_SYM(पूर्णाङ्क,XResizeWindow,(Display* a,Window b,अचिन्हित पूर्णाङ्क c,अचिन्हित पूर्णाङ्क d))
SDL_X11_SYM(पूर्णाङ्क,XScreen_सङ्ख्या_Of_Screen,(Screen* a))
SDL_X11_SYM(पूर्णाङ्क,XSelect_आगत,(Display* a,Window b,दीर्घ c))
SDL_X11_SYM(Status,XSendEvent,(Display* a,Window b,Bool c,दीर्घ d,XEvent* e))
SDL_X11_SYM(XErrorHandler,XSetErrorHandler,(XErrorHandler a))
SDL_X11_SYM(पूर्णाङ्क,XSetForeground,(Display* a,GC b,अचिन्हित दीर्घ c))
SDL_X11_SYM(XIOErrorHandler,XSetIOErrorHandler,(XIOErrorHandler a))
SDL_X11_SYM(पूर्णाङ्क,XSet_आगत_Focus,(Display *a,Window b,पूर्णाङ्क c,Time d))
SDL_X11_SYM(पूर्णाङ्क,XSetSelectionOwner,(Display* a,Atom b,Window c,Time d))
SDL_X11_SYM(पूर्णाङ्क,XSetTransientForHint,(Display* a,Window b,Window c))
SDL_X11_SYM(शून्य,XSetTextProperty,(Display* a,Window b,XTextProperty* c,Atom d))
SDL_X11_SYM(पूर्णाङ्क,XSetWindowBackground,(Display* a,Window b,अचिन्हित दीर्घ c))
SDL_X11_SYM(शून्य,XSetWMHints,(Display* a,Window b,XWMHints* c))
SDL_X11_SYM(शून्य,XSetWMNormalHints,(Display* a,Window b,XSizeHints* c))
SDL_X11_SYM(शून्य,XSetWMProperties,(Display* a,Window b,XTextProperty* c,XTextProperty* d,वर्ण** e,पूर्णाङ्क f,XSizeHints* g,XWMHints* h,XClassHint* i))
SDL_X11_SYM(Status,XSetWMProtocols,(Display* a,Window b,Atom* c,पूर्णाङ्क d))
SDL_X11_SYM(पूर्णाङ्क,XStoreColors,(Display* a,Colormap b,XColor* c,पूर्णाङ्क d))
SDL_X11_SYM(पूर्णाङ्क,XStoreName,(Display* a,Window b,_Xconst वर्ण* c))
SDL_X11_SYM(Status,XStringListToTextProperty,(वर्ण** a,पूर्णाङ्क b,XTextProperty* c))
SDL_X11_SYM(पूर्णाङ्क,XSync,(Display* a,Bool b))
SDL_X11_SYM(पूर्णाङ्क,XTextExtents,(XFontStruct* a,_Xconst वर्ण* b,पूर्णाङ्क c,पूर्णाङ्क* d,पूर्णाङ्क* e,पूर्णाङ्क* f,XCharStruct* g))
SDL_X11_SYM(Bool,XTranslateCoordinates,(Display *a,Window b,Window c,पूर्णाङ्क d,पूर्णाङ्क e,पूर्णाङ्क* f,पूर्णाङ्क* g,Window* h))
SDL_X11_SYM(पूर्णाङ्क,XUndefineCursor,(Display* a,Window b))
SDL_X11_SYM(पूर्णाङ्क,XUngrabKeyboard,(Display* a,Time b))
SDL_X11_SYM(पूर्णाङ्क,XUngrabPointer,(Display* a,Time b))
SDL_X11_SYM(पूर्णाङ्क,XUngrabServer,(Display* a))
SDL_X11_SYM(पूर्णाङ्क,XUninstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(पूर्णाङ्क,XUnloadFont,(Display* a,Font b))
SDL_X11_SYM(पूर्णाङ्क,XWarpPointer,(Display* a,Window b,Window c,पूर्णाङ्क d,पूर्णाङ्क e,अचिन्हित पूर्णाङ्क f,अचिन्हित पूर्णाङ्क g,पूर्णाङ्क h,पूर्णाङ्क i))
SDL_X11_SYM(पूर्णाङ्क,XWindowEvent,(Display* a,Window b,दीर्घ c,XEvent* d))
SDL_X11_SYM(Status,XWithdrawWindow,(Display* a,Window b,पूर्णाङ्क c))
SDL_X11_SYM(VisualID,XVisualIDFromVisual,(Visual* a))
SDL_X11_SYM(वर्ण*,XGetDefault,(Display* a,_Xconst वर्ण* b, _Xconst वर्ण* c))
SDL_X11_SYM(Bool,XQueryExtension,(Display* a,_Xconst वर्ण* b,पूर्णाङ्क* c,पूर्णाङ्क* d,पूर्णाङ्क* e))
SDL_X11_SYM(वर्ण *,XDisplayString,(Display* a))
SDL_X11_SYM(पूर्णाङ्क,XGetErrorText,(Display* a,पूर्णाङ्क b,वर्ण* c,पूर्णाङ्क d))
SDL_X11_SYM(शून्य,_XEatData,(Display* a,अचिन्हित दीर्घ b))
SDL_X11_SYM(शून्य,_XFlush,(Display* a))
SDL_X11_SYM(शून्य,_XFlushGCCache,(Display* a,GC b))
SDL_X11_SYM(पूर्णाङ्क,_XRead,(Display* a,वर्ण* b,दीर्घ c))
SDL_X11_SYM(शून्य,_XReadPad,(Display* a,वर्ण* b,दीर्घ c))
SDL_X11_SYM(शून्य,_XSend,(Display* a,_Xconst वर्ण* b,दीर्घ c))
SDL_X11_SYM(Status,_XReply,(Display* a,xReply* b,पूर्णाङ्क c,Bool d))
SDL_X11_SYM(अचिन्हित दीर्घ,_XSetLastRequestRead,(Display* a,xGenericReply* b))
SDL_X11_SYM(SDL_X11_XSynchronizeRetType,XSynchronize,(Display* a,Bool b))
SDL_X11_SYM(SDL_X11_XESetWireToEventRetType,XESetWireToEvent,(Display* a,पूर्णाङ्क b,SDL_X11_XESetWireToEventRetType c))
SDL_X11_SYM(SDL_X11_XESetEventToWireRetType,XESetEventToWire,(Display* a,पूर्णाङ्क b,SDL_X11_XESetEventToWireRetType c))
SDL_X11_SYM(शून्य,XRefreshKeyboardMapping,(XMappingEvent *a))
SDL_X11_SYM(पूर्णाङ्क,XQuery_रूख,(Display* a,Window b,Window* c,Window* d,Window** e,अचिन्हित पूर्णाङ्क* f))
SDL_X11_SYM(Bool,XSupportsLocale,(शून्य))
SDL_X11_SYM(Status,XmbTextListToTextProperty,(Display* a,वर्ण** b,पूर्णाङ्क c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(Region,XCreateRegion,(शून्य))
SDL_X11_SYM(पूर्णाङ्क,XUnionRectWithRegion,(XRectangle *a, Region b, Region c))
SDL_X11_SYM(शून्य,XDestroyRegion,(Region))
SDL_X11_SYM(शून्य,XrmInitialize,(शून्य))
SDL_X11_SYM(वर्ण*,XResourceManagerString,(Display *display))
SDL_X11_SYM(XrmDatabase,XrmGetStringDatabase,(वर्ण *data))
SDL_X11_SYM(शून्य,XrmDestroyDatabase,(XrmDatabase db))
SDL_X11_SYM(Bool,XrmGetResource,(XrmDatabase db, वर्ण* str_name, वर्ण* str_class, वर्ण **str_type_return, Xrm_मान *))
SDL_X11_SYM(पूर्णाङ्क,XGetPointerMapping,(Display *a, अचिन्हित वर्ण *b, अचिन्हित पूर्णाङ्क c))

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
SDL_X11_MODULE(XFIXES)
SDL_X11_SYM(PointerBarrier, XFixesCreatePointerBarrier, (Display* a, Window b, पूर्णाङ्क c, पूर्णाङ्क d, पूर्णाङ्क e, पूर्णाङ्क f, पूर्णाङ्क g, पूर्णाङ्क h, पूर्णाङ्क *i))
SDL_X11_SYM(शून्य, XFixesDestroyPointerBarrier, (Display* a, PointerBarrier b))
SDL_X11_SYM(पूर्णाङ्क, XIBarrierReleasePointer,(Display* a,  पूर्णाङ्क b, PointerBarrier c, BarrierEventID d)) // this is actually Xinput2
SDL_X11_SYM(Status, XFixesQueryVersion,(Display* a, पूर्णाङ्क* b, पूर्णाङ्क* c))
SDL_X11_SYM(Status, XFixes_Select_Selection_आगत, (Display* a, Window b, Atom c, अचिन्हित दीर्घ d))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
SDL_X11_MODULE(XSYNC)
SDL_X11_SYM(Status, XSyncQueryExtension, (Display* a, पूर्णाङ्क* b, पूर्णाङ्क* c))
SDL_X11_SYM(Status, XSyncInitialize, (Display* a, पूर्णाङ्क* b, पूर्णाङ्क* c))
SDL_X11_SYM(XSyncCounter, XSyncCreateCounter, (Display* a, XSync_मान b))
SDL_X11_SYM(Status, XSyncDestroyCounter, (Display* a, XSyncCounter b))
SDL_X11_SYM(Status, XSyncSetCounter, (Display* a, XSyncCounter b, XSync_मान c))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XTEST
SDL_X11_MODULE(XTEST)
SDL_X11_SYM(Status, XTestQueryExtension, (Display* a, पूर्णाङ्क* b, पूर्णाङ्क* c))
SDL_X11_SYM(पूर्णाङ्क, XTestFakeMotionEvent, (Display* a, पूर्णाङ्क b, पूर्णाङ्क c, पूर्णाङ्क d, अचिन्हित दीर्घ e))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
SDL_X11_SYM(Bool,XGetEventData,(Display* a,XGenericEventCookie* b))
SDL_X11_SYM(शून्य,XFreeEventData,(Display* a,XGenericEventCookie* b))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
SDL_X11_SYM(Bool,XkbQueryExtension,(Display* a,पूर्णाङ्क * b,पूर्णाङ्क * c,पूर्णाङ्क * d,पूर्णाङ्क * e, पूर्णाङ्क *f))
SDL_X11_SYM(साँचो_Sym,XkbKeycodeToKeysym,(Display* a, साँचो_Code_2 b, अचिन्हित पूर्णाङ्क c, अचिन्हित पूर्णाङ्क d))
SDL_X11_SYM(Bool,XkbSelectEvents,(Display* a, अचिन्हित पूर्णाङ्क b, अचिन्हित पूर्णाङ्क c, अचिन्हित दीर्घ d))
SDL_X11_SYM(Bool,XkbSelectEventDetails,(Display* a, अचिन्हित पूर्णाङ्क b, अचिन्हित पूर्णाङ्क c, अचिन्हित दीर्घ d, अचिन्हित दीर्घ e))
SDL_X11_SYM(Status,XkbGetNames,(Display *a, अचिन्हित पूर्णाङ्क b, XkbDescPtr c))
SDL_X11_SYM(Status,XkbGetState,(Display* a,अचिन्हित पूर्णाङ्क b,XkbStatePtr c))
SDL_X11_SYM(Status,XkbGetUpdatedMap,(Display* a,अचिन्हित पूर्णाङ्क b,XkbDescPtr c))
SDL_X11_SYM(XkbDescPtr,XkbGetMap,(Display* a,अचिन्हित पूर्णाङ्क b,अचिन्हित पूर्णाङ्क c))
SDL_X11_SYM(शून्य,XkbFreeClientMap,(XkbDescPtr a,अचिन्हित पूर्णाङ्क b, Bool c))
SDL_X11_SYM(शून्य,XkbFreeKeyboard,(XkbDescPtr a,अचिन्हित पूर्णाङ्क b, Bool c))
SDL_X11_SYM(Status,XkbRefreshKeyboardMapping,(XkbMapNotifyEvent *a))
SDL_X11_SYM(Bool,XkbSetDetectableAutoRepeat,(Display* a, Bool b, Bool* c))
#endif

#ifdef X_HAVE_UTF8_STRING
SDL_X11_MODULE(UTF8)
SDL_X11_SYM(पूर्णाङ्क,Xutf8TextListToTextProperty,(Display* a,वर्ण** b,पूर्णाङ्क c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(पूर्णाङ्क,Xutf8LookupString,(XIC a,XKeyPressedEvent* b,वर्ण* c,पूर्णाङ्क d,साँचो_Sym* e,Status* f))
SDL_X11_SYM(XIC,XCreateIC,(XIM,...))
SDL_X11_SYM(शून्य,XDestroyIC,(XIC a))
SDL_X11_SYM(वर्ण*,XGetICValues,(XIC,...))
SDL_X11_SYM(वर्ण*,XSetICValues,(XIC,...))
SDL_X11_SYM(XVaNestedList,XVaCreateNestedList,(पूर्णाङ्क, ...))
SDL_X11_SYM(शून्य,XSetICFocus,(XIC a))
SDL_X11_SYM(शून्य,XUnsetICFocus,(XIC a))
SDL_X11_SYM(XIM,XOpenIM,(Display* a,संरचना _XrmHashBucketRec* b,वर्ण* c,वर्ण* d))
SDL_X11_SYM(Status,XCloseIM,(XIM a))
SDL_X11_SYM(वर्ण*, XSetIMValues,(XIM,...))
SDL_X11_SYM(Bool,XRegisterIMInstantiateCallback,(Display*,संरचना _XrmHashBucketRec*,वर्ण*,वर्ण*,XIDProc,XPointer))
SDL_X11_SYM(Bool,XUnregisterIMInstantiateCallback,(Display*,संरचना _XrmHashBucketRec*,वर्ण*,वर्ण*,XIDProc,XPointer))
SDL_X11_SYM(शून्य,Xutf8DrawString,(Display *a, Drawable b, XFontSet c, GC d, पूर्णाङ्क e, पूर्णाङ्क f, _Xconst वर्ण *g, पूर्णाङ्क h))
SDL_X11_SYM(पूर्णाङ्क,Xutf8TextExtents,(XFontSet a, _Xconst वर्ण* b, पूर्णाङ्क c, XRectangle* d, XRectangle* e))
SDL_X11_SYM(वर्ण*,XSetLocaleModifiers,(अचर वर्ण *a))
SDL_X11_SYM(वर्ण*,Xutf8ResetIC,(XIC a))
SDL_X11_SYM(XFontSetExtents*,XExtentsOfFontSet,(XFontSet a))
SDL_X11_SYM(Bool,XContextDependentDrawing,(XFontSet a))
#endif


#ifndef NO_SHARED_MEMORY
SDL_X11_MODULE(SHM)
SDL_X11_SYM(Status,XShmAttach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmDetach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmPutImage,(Display* a,Drawable b,GC c,XImage* d,पूर्णाङ्क e,पूर्णाङ्क f,पूर्णाङ्क g,पूर्णाङ्क h,अचिन्हित पूर्णाङ्क i,अचिन्हित पूर्णाङ्क j,Bool k))
SDL_X11_SYM(Status,XShmGetImage,(Display* a,Drawable b,XImage *c,पूर्णाङ्क d, पूर्णाङ्क e, अचिन्हित दीर्घ f))
SDL_X11_SYM(XImage*,XShmCreateImage,(Display* a,Visual* b,अचिन्हित पूर्णाङ्क c,पूर्णाङ्क d,वर्ण* e,XShmSegmentInfo* f,अचिन्हित पूर्णाङ्क g,अचिन्हित पूर्णाङ्क h))
SDL_X11_SYM(Pixmap,XShmCreatePixmap,(Display *a,Drawable b,वर्ण* c,XShmSegmentInfo* d, अचिन्हित पूर्णाङ्क e, अचिन्हित पूर्णाङ्क f, अचिन्हित पूर्णाङ्क g))
SDL_X11_SYM(Bool,XShmQueryExtension,(Display* a))
SDL_X11_SYM(Status,XShmQueryVersion,(Display* a, पूर्णाङ्क *b, पूर्णाङ्क *c, Bool *d))
SDL_X11_SYM(पूर्णाङ्क,XShmPixmapFormat,(Display* a))
#endif

/*
 * Not required...these only exist in code in headers on some 64-bit platforms,
 *  and are removed via macros elsewhere, so it's safe for them to be missing.
 */
#ifdef LONG64
SDL_X11_MODULE(IO_32BIT)
SDL_X11_SYM(पूर्णाङ्क,_XData32,(Display *dpy,पञ्जिका _Xconst दीर्घ *data,अचिन्हित len))
SDL_X11_SYM(शून्य,_XRead32,(Display *dpy,पञ्जिका दीर्घ *data,दीर्घ len))
#endif

/*
 * These only show up on some variants of Unix.
 */
#ifdef SDL_PLATFORM_OSF
SDL_X11_MODULE(OSF_ENTRY_POINTS)
SDL_X11_SYM(शून्य,_SmtBufferOverflow,(Display *dpy,पञ्जिका smtDisplayPtr p))
SDL_X11_SYM(शून्य,_SmtIpError,(Display *dpy,पञ्जिका smtDisplayPtr p,पूर्णाङ्क i))
SDL_X11_SYM(पूर्णाङ्क,ipAllocateData,(ChannelPtr a,IPCard b,IPDataPtr * c))
SDL_X11_SYM(पूर्णाङ्क,ipUnallocateAndSendData,(ChannelPtr a,IPCard b))
#endif

// XCursor support
#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
SDL_X11_MODULE(XCURSOR)
SDL_X11_SYM(XcursorImage*,XcursorImageCreate,(पूर्णाङ्क a,पूर्णाङ्क b))
SDL_X11_SYM(XcursorImages*,XcursorImagesCreate,(पूर्णाङ्क a))
SDL_X11_SYM(शून्य,XcursorImageDestroy,(XcursorImage *a))
SDL_X11_SYM(शून्य,XcursorImagesDestroy,(XcursorImages *a))
SDL_X11_SYM(Cursor,XcursorImageLoadCursor,(Display *a,अचर XcursorImage *b))
SDL_X11_SYM(Cursor,XcursorImagesLoadCursor,(Display *a,अचर XcursorImages *b))
SDL_X11_SYM(Cursor,XcursorLibraryLoadCursor,(Display *a, अचर वर्ण *b))
#endif

// Xdbe support
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
SDL_X11_MODULE(XDBE)
SDL_X11_SYM(Status,XdbeQueryExtension,(Display *dpy,पूर्णाङ्क *major_version_return,पूर्णाङ्क *minor_version_return))
SDL_X11_SYM(XdbeBackBuffer,XdbeAllocateBackBufferName,(Display *dpy,Window window,XdbeSwapAction swap_action))
SDL_X11_SYM(Status,XdbeDeallocateBackBufferName,(Display *dpy,XdbeBackBuffer buffer))
SDL_X11_SYM(Status,XdbeSwapBuffers,(Display *dpy,XdbeSwapInfo *swap_info,पूर्णाङ्क अङ्क_windows))
SDL_X11_SYM(Status,XdbeBeginIdiom,(Display *dpy))
SDL_X11_SYM(Status,XdbeEndIdiom,(Display *dpy))
SDL_X11_SYM(XdbeScreenVisualInfo*,XdbeGetVisualInfo,(Display *dpy,Drawable *screen_specifiers,पूर्णाङ्क *अङ्क_screens))
SDL_X11_SYM(शून्य,XdbeFreeVisualInfo,(XdbeScreenVisualInfo *visual_info))
SDL_X11_SYM(XdbeBackBufferAttributes*,XdbeGetBackBufferAttributes,(Display *dpy,XdbeBackBuffer buffer))
#endif

// XInput2 support for multiple mice, tablets, etc.
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
SDL_X11_MODULE(XINPUT2)
SDL_X11_SYM(XIDeviceInfo*,XIQueryDevice,(Display *a,पूर्णाङ्क b,पूर्णाङ्क *c))
SDL_X11_SYM(शून्य,XIFreeDeviceInfo,(XIDeviceInfo *a))
SDL_X11_SYM(पूर्णाङ्क,XISelectEvents,(Display *a,Window b,XIEventMask *c,पूर्णाङ्क d))
SDL_X11_SYM(पूर्णाङ्क,XIGrabTouchBegin,(Display *a,पूर्णाङ्क b,Window c,पूर्णाङ्क d,XIEventMask *e,पूर्णाङ्क f,XIGrabModifiers *g))
SDL_X11_SYM(पूर्णाङ्क,XIUngrabTouchBegin, (Display *a,पूर्णाङ्क b,Window c, पूर्णाङ्क d,XIGrabModifiers *e))
SDL_X11_SYM(Status,XIQueryVersion,(Display *a,पूर्णाङ्क *b,पूर्णाङ्क *c))
SDL_X11_SYM(XIEventMask*,XIGetSelectedEvents,(Display *a,Window b,पूर्णाङ्क *c))
SDL_X11_SYM(Bool,XIGetClientPointer,(Display *a,Window b,पूर्णाङ्क *c))
SDL_X11_SYM(Bool,XIWarpPointer,(Display *a,पूर्णाङ्क b,Window c,Window d,द्विगुण e,द्विगुण f,पूर्णाङ्क g,पूर्णाङ्क h,द्विगुण i,द्विगुण j))
SDL_X11_SYM(Status,XIGetProperty,(Display *a,पूर्णाङ्क b,Atom c,दीर्घ d,दीर्घ e,Bool f, Atom g, Atom *h, पूर्णाङ्क *i, अचिन्हित दीर्घ *j, अचिन्हित दीर्घ *k, अचिन्हित वर्ण **l))
#endif

// XRandR support
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
SDL_X11_MODULE(XRANDR)
SDL_X11_SYM(Status,XRRQueryVersion,(Display *dpy,पूर्णाङ्क *major_versionp,पूर्णाङ्क *minor_versionp))
SDL_X11_SYM(Bool,XRRQueryExtension,(Display *dpy,पूर्णाङ्क *event_base_return,पूर्णाङ्क *error_base_return))
SDL_X11_SYM(XRRScreenConfiguration *,XRRGetScreenInfo,(Display *dpy,Drawable draw))
SDL_X11_SYM(SizeID,XRRConfigCurrentConfiguration,(XRRScreenConfiguration *config,Rotation *rotation))
SDL_X11_SYM(लघु,XRRConfigCurrentRate,(XRRScreenConfiguration *config))
SDL_X11_SYM(लघु *,XRRConfigRates,(XRRScreenConfiguration *config,पूर्णाङ्क sizeID,पूर्णाङ्क *nrates))
SDL_X11_SYM(XRRScreenSize *,XRRConfigSizes,(XRRScreenConfiguration *config,पूर्णाङ्क *nsizes))
SDL_X11_SYM(Status,XRRSetScreenConfigAndRate,(Display *dpy,XRRScreenConfiguration *config,Drawable draw,पूर्णाङ्क size_index,Rotation rotation,लघु rate,Time timestamp))
SDL_X11_SYM(शून्य,XRRFreeScreenConfigInfo,(XRRScreenConfiguration *config))
SDL_X11_SYM(शून्य,XRRSetScreenSize,(Display *dpy, Window window,पूर्णाङ्क width, पूर्णाङ्क height,पूर्णाङ्क mmWidth, पूर्णाङ्क mmHeight))
SDL_X11_SYM(Status,XRRGetScreenSizeRange,(Display *dpy, Window window,पूर्णाङ्क *minWidth, पूर्णाङ्क *minHeight, पूर्णाङ्क *maxWidth, पूर्णाङ्क *maxHeight))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResources,(Display *dpy, Window window))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResourcesCurrent,(Display *dpy, Window window))
SDL_X11_SYM(शून्य,XRRFreeScreenResources,(XRRScreenResources *resources))
SDL_X11_SYM(XRROutputInfo *,XRRGetOutputInfo,(Display *dpy, XRRScreenResources *resources, RROutput output))
SDL_X11_SYM(शून्य,XRRFreeOutputInfo,(XRROutputInfo *outputInfo))
SDL_X11_SYM(XRRCrtcInfo *,XRRGetCrtcInfo,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc))
SDL_X11_SYM(शून्य,XRRFreeCrtcInfo,(XRRCrtcInfo *crtcInfo))
SDL_X11_SYM(Status,XRRSetCrtcConfig,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc, Time timestamp, पूर्णाङ्क x, पूर्णाङ्क y, RRMode mode, Rotation rotation, RROutput *outputs, पूर्णाङ्क noutputs))
SDL_X11_SYM(Atom*,XRRListOutputProperties,(Display *dpy, RROutput output, पूर्णाङ्क *nprop))
SDL_X11_SYM(XRRPropertyInfo*,XRRQueryOutputProperty,(Display *dpy,RROutput output, Atom property))
SDL_X11_SYM(पूर्णाङ्क,XRRGetOutputProperty,(Display *dpy,RROutput output, Atom property, दीर्घ offset, दीर्घ length, Bool _delete, Bool pending, Atom req_type, Atom *actual_type, पूर्णाङ्क *actual_format, अचिन्हित दीर्घ *nitems, अचिन्हित दीर्घ *bytes_after, अचिन्हित वर्ण **prop))
SDL_X11_SYM(RROutput,XRRGetOutputPrimary,(Display *dpy,Window window))
SDL_X11_SYM(शून्य,XRRSelect_आगत,(Display *dpy, Window window, पूर्णाङ्क mask))
SDL_X11_SYM(Status,XRRGetCrtcTransform,(Display *dpy,RRCrtc crtc,XRRCrtcTransformAttributes **attributes))
#endif

// MIT-SCREEN-SAVER support
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
SDL_X11_MODULE(XSS)
SDL_X11_SYM(Bool,XScreenSaverQueryExtension,(Display *dpy,पूर्णाङ्क *event_base,पूर्णाङ्क *error_base))
SDL_X11_SYM(Status,XScreenSaverQueryVersion,(Display *dpy,पूर्णाङ्क *major_versionp,पूर्णाङ्क *minor_versionp))
SDL_X11_SYM(शून्य,XScreenSaverSuspend,(Display *dpy,Bool suspend))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
SDL_X11_MODULE(XSHAPE)
SDL_X11_SYM(शून्य,XShapeCombineMask,(Display *dpy,Window dest,पूर्णाङ्क dest_kind,पूर्णाङ्क x_off,पूर्णाङ्क y_off,Pixmap src,पूर्णाङ्क op))
SDL_X11_SYM(शून्य,XShapeCombineRegion,(Display *a,Window b,पूर्णाङ्क c,पूर्णाङ्क d,पूर्णाङ्क e,Region f,पूर्णाङ्क g))
#endif

#undef SDL_X11_MODULE
#undef SDL_X11_SYM

/* *INDENT-ON* */ // clang-format on
