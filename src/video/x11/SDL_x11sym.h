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

#अगर_अघोषित SDL_X11_MODULE
#घोषणा SDL_X11_MODULE(modname)
#पूर्ण_अगर

#अगर_अघोषित SDL_X11_SYM
#घोषणा SDL_X11_SYM(rc, fn, params)
#पूर्ण_अगर

SDL_X11_MODULE(BASEXLIB)
SDL_X11_SYM(XSizeHints*,XAlloc_आकार_Hints,(व्योम))
SDL_X11_SYM(XWMHints*,XAllocWMHints,(व्योम))
SDL_X11_SYM(XClassHint*,XAllocClassHint,(व्योम))
SDL_X11_SYM(पूर्णांक,XChangePointerControl,(Display* a,Bool b,Bool c,पूर्णांक d,पूर्णांक e,पूर्णांक f))
SDL_X11_SYM(पूर्णांक,XChangeProperty,(Display* a,Window b,Atom c,Atom d,पूर्णांक e,पूर्णांक f,_Xconst अचिन्हित अक्षर* g,पूर्णांक h))
SDL_X11_SYM(Bool,XCheckIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(पूर्णांक,XClearWindow,(Display* a,Window b))
SDL_X11_SYM(पूर्णांक,XCloseDisplay,(Display* a))
SDL_X11_SYM(पूर्णांक,XConvertSelection,(Display* a,Atom b,Atom c,Atom d,Window e,Time f))
SDL_X11_SYM(Pixmap,XCreate_Bitmap_From_तथ्य,(Display *dpy,Drawable d,_Xconst अक्षर *तथ्य,अचिन्हित पूर्णांक width,अचिन्हित पूर्णांक height))
SDL_X11_SYM(Colormap,XCreateColormap,(Display* a,Window b,Visual* c,पूर्णांक d))
SDL_X11_SYM(Cursor,XCreatePixmapCursor,(Display* a,Pixmap b,Pixmap c,XColor* d,XColor* e,अचिन्हित पूर्णांक f,अचिन्हित पूर्णांक g))
SDL_X11_SYM(Cursor,XCreatePixmap,(Display* a,Drawable b,अचिन्हित पूर्णांक d,अचिन्हित पूर्णांक e,अचिन्हित पूर्णांक f))
SDL_X11_SYM(Cursor,XCreateFontCursor,(Display* a,अचिन्हित पूर्णांक b))
SDL_X11_SYM(XFontSet,XCreateFontSet,(Display* a, _Xconst अक्षर* b, अक्षर*** c, पूर्णांक* d, अक्षर** e))
SDL_X11_SYM(GC,XCreateGC,(Display* a,Drawable b,अचिन्हित दीर्घ c,XGCValues* d))
SDL_X11_SYM(व्योम,XSetFont,(Display* a,GC b,Font c))
SDL_X11_SYM(Status,XAllocColor,(Display *a, Colormap b, XColor *c))
SDL_X11_SYM(XImage*,XCreateImage,(Display* a,Visual* b,अचिन्हित पूर्णांक c,पूर्णांक d,पूर्णांक e,अक्षर* f,अचिन्हित पूर्णांक g,अचिन्हित पूर्णांक h,पूर्णांक i,पूर्णांक j))
SDL_X11_SYM(Window,XCreateWindow,(Display* a,Window b,पूर्णांक c,पूर्णांक d,अचिन्हित पूर्णांक e,अचिन्हित पूर्णांक f,अचिन्हित पूर्णांक g,पूर्णांक h,अचिन्हित पूर्णांक i,Visual* j,अचिन्हित दीर्घ k,XSetWindowAttributes* l))
SDL_X11_SYM(व्योम,XCopyArea,(Display *a, Drawable b, Drawable c, GC d, पूर्णांक e, पूर्णांक f, अचिन्हित पूर्णांक g, अचिन्हित पूर्णांक h, पूर्णांक i, पूर्णांक j))
SDL_X11_SYM(पूर्णांक,XDefineCursor,(Display* a,Window b,Cursor c))
SDL_X11_SYM(पूर्णांक,XDeleteProperty,(Display* a,Window b,Atom c))
SDL_X11_SYM(पूर्णांक,XDestroyWindow,(Display* a,Window b))
SDL_X11_SYM(पूर्णांक,XDisplayKeycodes,(Display* a,पूर्णांक* b,पूर्णांक* c))
SDL_X11_SYM(पूर्णांक,XDrawRectangle,(Display* a,Drawable b,GC c,पूर्णांक d,पूर्णांक e,अचिन्हित पूर्णांक f,अचिन्हित पूर्णांक g))
SDL_X11_SYM(पूर्णांक,XFontsOfFontSet,(XFontSet a,XFontStruct ***b,अक्षर ***c))
SDL_X11_SYM(पूर्णांक,XFillArc,(Display* a,Drawable b,GC c,पूर्णांक d,पूर्णांक e,अचिन्हित पूर्णांक f,अचिन्हित पूर्णांक g, पूर्णांक h, पूर्णांक i))
SDL_X11_SYM(अक्षर*,XDisplayName,(_Xconst अक्षर* a))
SDL_X11_SYM(पूर्णांक,XDrawString,(Display* a,Drawable b,GC c,पूर्णांक d,पूर्णांक e,_Xconst अक्षर* f,पूर्णांक g))
SDL_X11_SYM(पूर्णांक,XEventsQueued,(Display* a,पूर्णांक b))
SDL_X11_SYM(पूर्णांक,XFillRectangle,(Display* a,Drawable b,GC c,पूर्णांक d,पूर्णांक e,अचिन्हित पूर्णांक f,अचिन्हित पूर्णांक g))
SDL_X11_SYM(Bool,XFilterEvent,(XEvent *event,Window w))
SDL_X11_SYM(पूर्णांक,XFlush,(Display* a))
SDL_X11_SYM(पूर्णांक,XFree,(व्योम*a))
SDL_X11_SYM(पूर्णांक,XFreeCursor,(Display* a,Cursor b))
SDL_X11_SYM(व्योम,XFreeFontSet,(Display* a, XFontSet b))
SDL_X11_SYM(पूर्णांक,XFreeGC,(Display* a,GC b))
SDL_X11_SYM(पूर्णांक,XFreeFont,(Display* a, XFontStruct* b))
SDL_X11_SYM(पूर्णांक,XFreeModifiermap,(XModifierKeymap* a))
SDL_X11_SYM(पूर्णांक,XFreePixmap,(Display* a,Pixmap b))
SDL_X11_SYM(पूर्णांक,XFreeColormap,(Display* a,Colormap b))
SDL_X11_SYM(व्योम,XFreeStringList,(अक्षर** a))
SDL_X11_SYM(अक्षर*,XGetAtomName,(Display *a,Atom b))
SDL_X11_SYM(पूर्णांक,XGet_निवेश_Focus,(Display *a,Window *b,पूर्णांक *c))
SDL_X11_SYM(कुंजी_Sym*,XGetKeyboardMapping,(Display *a, कुंजी_Code_2 b, पूर्णांक c, पूर्णांक *d))
SDL_X11_SYM(पूर्णांक,XGetErrorDatabaseText,(Display* a,_Xconst अक्षर* b,_Xconst अक्षर* c,_Xconst अक्षर* d,अक्षर* e,पूर्णांक f))
SDL_X11_SYM(XModifierKeymap*,XGetModifierMapping,(Display* a))
SDL_X11_SYM(पूर्णांक,XGetPointerControl,(Display* a,पूर्णांक* b,पूर्णांक* c,पूर्णांक* d))
SDL_X11_SYM(Window,XGetSelectionOwner,(Display* a,Atom b))
SDL_X11_SYM(XVisualInfo*,XGetVisualInfo,(Display* a,दीर्घ b,XVisualInfo* c,पूर्णांक* d))
SDL_X11_SYM(Status,XGetWindowAttributes,(Display* a,Window b,XWindowAttributes* c))
SDL_X11_SYM(पूर्णांक,XGetWindowProperty,(Display* a,Window b,Atom c,दीर्घ d,दीर्घ e,Bool f,Atom g,Atom* h,पूर्णांक* i,अचिन्हित दीर्घ* j,अचिन्हित दीर्घ *k,अचिन्हित अक्षर **l))
SDL_X11_SYM(XWMHints*,XGetWMHints,(Display* a,Window b))
SDL_X11_SYM(Status,XGetWMNormalHints,(Display *a,Window b, XSizeHints *c, दीर्घ *d))
SDL_X11_SYM(पूर्णांक,XIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(पूर्णांक,XGrabKeyboard,(Display* a,Window b,Bool c,पूर्णांक d,पूर्णांक e,Time f))
SDL_X11_SYM(पूर्णांक,XGrabPointer,(Display* a,Window b,Bool c,अचिन्हित पूर्णांक d,पूर्णांक e,पूर्णांक f,Window g,Cursor h,Time i))
SDL_X11_SYM(पूर्णांक,XGrabServer,(Display* a))
SDL_X11_SYM(Status,XIconifyWindow,(Display* a,Window b,पूर्णांक c))
SDL_X11_SYM(कुंजी_Code_2,XKeysymToKeycode,(Display* a,कुंजी_Sym b))
SDL_X11_SYM(अक्षर*,XKeysymToString,(कुंजी_Sym a))
SDL_X11_SYM(पूर्णांक,XInstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(Atom,XInternAtom,(Display* a,_Xconst अक्षर* b,Bool c))
SDL_X11_SYM(XPixmap_Format_मूल्यावली*,XListPixmapFormats,(Display* a,पूर्णांक* b))
SDL_X11_SYM(XFontStruct*,XLoadQueryFont,(Display* a,_Xconst अक्षर* b))
SDL_X11_SYM(कुंजी_Sym,XLookupKeysym,(XKeyEvent* a,पूर्णांक b))
SDL_X11_SYM(पूर्णांक,XLookupString,(XKeyEvent* a,अक्षर* b,पूर्णांक c,कुंजी_Sym* d,XComposeStatus* e))
SDL_X11_SYM(पूर्णांक,XMapRaised,(Display* a,Window b))
SDL_X11_SYM(Status,XMatchVisualInfo,(Display* a,पूर्णांक b,पूर्णांक c,पूर्णांक d,XVisualInfo* e))
SDL_X11_SYM(पूर्णांक,XMissingExtension,(Display* a,_Xconst अक्षर* b))
SDL_X11_SYM(पूर्णांक,XMoveWindow,(Display* a,Window b,पूर्णांक c,पूर्णांक d))
SDL_X11_SYM(Display*,XOpenDisplay,(_Xconst अक्षर* a))
SDL_X11_SYM(Status,XInitThreads,(व्योम))
SDL_X11_SYM(पूर्णांक,XPeekEvent,(Display* a,XEvent* b))
SDL_X11_SYM(पूर्णांक,XPending,(Display* a))
SDL_X11_SYM(XImage*,XGetImage,(Display* a,Drawable b,पूर्णांक c, पूर्णांक d,अचिन्हित पूर्णांक e,अचिन्हित पूर्णांक f,अचिन्हित दीर्घ g,पूर्णांक h))
SDL_X11_SYM(पूर्णांक,XPutImage,(Display* a,Drawable b,GC c,XImage* d,पूर्णांक e,पूर्णांक f,पूर्णांक g,पूर्णांक h,अचिन्हित पूर्णांक i,अचिन्हित पूर्णांक j))
SDL_X11_SYM(पूर्णांक,XQueryKeymap,(Display* a,अक्षर b[32]))
SDL_X11_SYM(Bool,XQueryPointer,(Display* a,Window b,Window* c,Window* d,पूर्णांक* e,पूर्णांक* f,पूर्णांक* g,पूर्णांक* h,अचिन्हित पूर्णांक* i))
SDL_X11_SYM(पूर्णांक,XRaiseWindow,(Display* a,Window b))
SDL_X11_SYM(पूर्णांक,XReparentWindow,(Display* a,Window b,Window c,पूर्णांक d,पूर्णांक e))
SDL_X11_SYM(पूर्णांक,XResetScreenSaver,(Display* a))
SDL_X11_SYM(पूर्णांक,XResizeWindow,(Display* a,Window b,अचिन्हित पूर्णांक c,अचिन्हित पूर्णांक d))
SDL_X11_SYM(पूर्णांक,XScreen_संख्या_Of_Screen,(Screen* a))
SDL_X11_SYM(पूर्णांक,XSelect_निवेश,(Display* a,Window b,दीर्घ c))
SDL_X11_SYM(Status,XSendEvent,(Display* a,Window b,Bool c,दीर्घ d,XEvent* e))
SDL_X11_SYM(XErrorHandler,XSetErrorHandler,(XErrorHandler a))
SDL_X11_SYM(पूर्णांक,XSetForeground,(Display* a,GC b,अचिन्हित दीर्घ c))
SDL_X11_SYM(XIOErrorHandler,XSetIOErrorHandler,(XIOErrorHandler a))
SDL_X11_SYM(पूर्णांक,XSet_निवेश_Focus,(Display *a,Window b,पूर्णांक c,Time d))
SDL_X11_SYM(पूर्णांक,XSetSelectionOwner,(Display* a,Atom b,Window c,Time d))
SDL_X11_SYM(पूर्णांक,XSetTransientForHint,(Display* a,Window b,Window c))
SDL_X11_SYM(व्योम,XSetTextProperty,(Display* a,Window b,XTextProperty* c,Atom d))
SDL_X11_SYM(पूर्णांक,XSetWindowBackground,(Display* a,Window b,अचिन्हित दीर्घ c))
SDL_X11_SYM(व्योम,XSetWMHints,(Display* a,Window b,XWMHints* c))
SDL_X11_SYM(व्योम,XSetWMNormalHints,(Display* a,Window b,XSizeHints* c))
SDL_X11_SYM(व्योम,XSetWMProperties,(Display* a,Window b,XTextProperty* c,XTextProperty* d,अक्षर** e,पूर्णांक f,XSizeHints* g,XWMHints* h,XClassHint* i))
SDL_X11_SYM(Status,XSetWMProtocols,(Display* a,Window b,Atom* c,पूर्णांक d))
SDL_X11_SYM(पूर्णांक,XStoreColors,(Display* a,Colormap b,XColor* c,पूर्णांक d))
SDL_X11_SYM(पूर्णांक,XStoreName,(Display* a,Window b,_Xconst अक्षर* c))
SDL_X11_SYM(Status,XStringListToTextProperty,(अक्षर** a,पूर्णांक b,XTextProperty* c))
SDL_X11_SYM(पूर्णांक,XSync,(Display* a,Bool b))
SDL_X11_SYM(पूर्णांक,XTextExtents,(XFontStruct* a,_Xconst अक्षर* b,पूर्णांक c,पूर्णांक* d,पूर्णांक* e,पूर्णांक* f,XCharStruct* g))
SDL_X11_SYM(Bool,XTranslateCoordinates,(Display *a,Window b,Window c,पूर्णांक d,पूर्णांक e,पूर्णांक* f,पूर्णांक* g,Window* h))
SDL_X11_SYM(पूर्णांक,XUndefineCursor,(Display* a,Window b))
SDL_X11_SYM(पूर्णांक,XUngrabKeyboard,(Display* a,Time b))
SDL_X11_SYM(पूर्णांक,XUngrabPointer,(Display* a,Time b))
SDL_X11_SYM(पूर्णांक,XUngrabServer,(Display* a))
SDL_X11_SYM(पूर्णांक,XUninstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(पूर्णांक,XUnloadFont,(Display* a,Font b))
SDL_X11_SYM(पूर्णांक,XWarpPointer,(Display* a,Window b,Window c,पूर्णांक d,पूर्णांक e,अचिन्हित पूर्णांक f,अचिन्हित पूर्णांक g,पूर्णांक h,पूर्णांक i))
SDL_X11_SYM(पूर्णांक,XWindowEvent,(Display* a,Window b,दीर्घ c,XEvent* d))
SDL_X11_SYM(Status,XWithdrawWindow,(Display* a,Window b,पूर्णांक c))
SDL_X11_SYM(VisualID,XVisualIDFromVisual,(Visual* a))
SDL_X11_SYM(अक्षर*,XGetDefault,(Display* a,_Xconst अक्षर* b, _Xconst अक्षर* c))
SDL_X11_SYM(Bool,XQueryExtension,(Display* a,_Xconst अक्षर* b,पूर्णांक* c,पूर्णांक* d,पूर्णांक* e))
SDL_X11_SYM(अक्षर *,XDisplayString,(Display* a))
SDL_X11_SYM(पूर्णांक,XGetErrorText,(Display* a,पूर्णांक b,अक्षर* c,पूर्णांक d))
SDL_X11_SYM(व्योम,XEat_तथ्य,(Display* a,अचिन्हित दीर्घ b))
SDL_X11_SYM(व्योम,_XFlush,(Display* a))
SDL_X11_SYM(व्योम,_XFlushGCCache,(Display* a,GC b))
SDL_X11_SYM(पूर्णांक,_XRead,(Display* a,अक्षर* b,दीर्घ c))
SDL_X11_SYM(व्योम,_XReadPad,(Display* a,अक्षर* b,दीर्घ c))
SDL_X11_SYM(व्योम,_XSend,(Display* a,_Xconst अक्षर* b,दीर्घ c))
SDL_X11_SYM(Status,_XReply,(Display* a,xReply* b,पूर्णांक c,Bool d))
SDL_X11_SYM(अचिन्हित दीर्घ,_XSetLastRequestRead,(Display* a,xGenericReply* b))
SDL_X11_SYM(SDL_X11_XSynchronizeRetType,XSynchronize,(Display* a,Bool b))
SDL_X11_SYM(SDL_X11_XESetWireToEventRetType,XESetWireToEvent,(Display* a,पूर्णांक b,SDL_X11_XESetWireToEventRetType c))
SDL_X11_SYM(SDL_X11_XESetEventToWireRetType,XESetEventToWire,(Display* a,पूर्णांक b,SDL_X11_XESetEventToWireRetType c))
SDL_X11_SYM(व्योम,XRefreshKeyboardMapping,(XMappingEvent *a))
SDL_X11_SYM(पूर्णांक,XQuery_वृक्ष,(Display* a,Window b,Window* c,Window* d,Window** e,अचिन्हित पूर्णांक* f))
SDL_X11_SYM(Bool,XSupportsLocale,(व्योम))
SDL_X11_SYM(Status,XmbTextListToTextProperty,(Display* a,अक्षर** b,पूर्णांक c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(Region,XCreateRegion,(व्योम))
SDL_X11_SYM(पूर्णांक,XUnionRectWithRegion,(XRectangle *a, Region b, Region c))
SDL_X11_SYM(व्योम,XDestroyRegion,(Region))
SDL_X11_SYM(व्योम,XrmInitialize,(व्योम))
SDL_X11_SYM(अक्षर*,XResourceManagerString,(Display *display))
SDL_X11_SYM(XrmDatabase,XrmGetStringDatabase,(अक्षर *तथ्य))
SDL_X11_SYM(व्योम,XrmDestroyDatabase,(XrmDatabase db))
SDL_X11_SYM(Bool,XrmGetResource,(XrmDatabase db, अक्षर* str_name, अक्षर* str_class, अक्षर **str_type_return, Xrm_मूल्य *))
SDL_X11_SYM(पूर्णांक,XGetPointerMapping,(Display *a, अचिन्हित अक्षर *b, अचिन्हित पूर्णांक c))

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XFIXES
SDL_X11_MODULE(XFIXES)
SDL_X11_SYM(PointerBarrier, XFixesCreatePointerBarrier, (Display* a, Window b, पूर्णांक c, पूर्णांक d, पूर्णांक e, पूर्णांक f, पूर्णांक g, पूर्णांक h, पूर्णांक *i))
SDL_X11_SYM(व्योम, XFixesDestroyPointerBarrier, (Display* a, PointerBarrier b))
SDL_X11_SYM(पूर्णांक, XIBarrierReleasePointer,(Display* a,  पूर्णांक b, PointerBarrier c, BarrierEventID d)) // this is actually Xinput2
SDL_X11_SYM(Status, XFixesQueryVersion,(Display* a, पूर्णांक* b, पूर्णांक* c))
SDL_X11_SYM(Status, XFixes_Select_Selection_निवेश, (Display* a, Window b, Atom c, अचिन्हित दीर्घ d))
#पूर्ण_अगर

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XSYNC
SDL_X11_MODULE(XSYNC)
SDL_X11_SYM(Status, XSyncQueryExtension, (Display* a, पूर्णांक* b, पूर्णांक* c))
SDL_X11_SYM(Status, XSyncInitialize, (Display* a, पूर्णांक* b, पूर्णांक* c))
SDL_X11_SYM(XSync_गणक, XSync_Create_गणक, (Display* a, XSync_मूल्य b))
SDL_X11_SYM(Status, XSync_Destroy_गणक, (Display* a, XSync_गणक b))
SDL_X11_SYM(Status, XSync_Set_गणक, (Display* a, XSync_गणक b, XSync_मूल्य c))
#पूर्ण_अगर

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XTEST
SDL_X11_MODULE(XTEST)
SDL_X11_SYM(Status, XTestQueryExtension, (Display* a, पूर्णांक* b, पूर्णांक* c))
SDL_X11_SYM(पूर्णांक, XTestFakeMotionEvent, (Display* a, पूर्णांक b, पूर्णांक c, पूर्णांक d, अचिन्हित दीर्घ e))
#पूर्ण_अगर

#अगर_घोषित SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
SDL_X11_SYM(Bool,XGet_Event_तथ्य,(Display* a,XGenericEventCookie* b))
SDL_X11_SYM(व्योम,XFree_Event_तथ्य,(Display* a,XGenericEventCookie* b))
#पूर्ण_अगर

#अगर_घोषित SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
SDL_X11_SYM(Bool,XkbQueryExtension,(Display* a,पूर्णांक * b,पूर्णांक * c,पूर्णांक * d,पूर्णांक * e, पूर्णांक *f))
SDL_X11_SYM(कुंजी_Sym,XkbKeycodeToKeysym,(Display* a, कुंजी_Code_2 b, अचिन्हित पूर्णांक c, अचिन्हित पूर्णांक d))
SDL_X11_SYM(Bool,XkbSelectEvents,(Display* a, अचिन्हित पूर्णांक b, अचिन्हित पूर्णांक c, अचिन्हित दीर्घ d))
SDL_X11_SYM(Bool,XkbSelectEventDetails,(Display* a, अचिन्हित पूर्णांक b, अचिन्हित पूर्णांक c, अचिन्हित दीर्घ d, अचिन्हित दीर्घ e))
SDL_X11_SYM(Status,XkbGetNames,(Display *a, अचिन्हित पूर्णांक b, XkbDescPtr c))
SDL_X11_SYM(Status,XkbGetState,(Display* a,अचिन्हित पूर्णांक b,XkbStatePtr c))
SDL_X11_SYM(Status,XkbGetUpdatedMap,(Display* a,अचिन्हित पूर्णांक b,XkbDescPtr c))
SDL_X11_SYM(XkbDescPtr,XkbGetMap,(Display* a,अचिन्हित पूर्णांक b,अचिन्हित पूर्णांक c))
SDL_X11_SYM(व्योम,XkbFreeClientMap,(XkbDescPtr a,अचिन्हित पूर्णांक b, Bool c))
SDL_X11_SYM(व्योम,XkbFreeKeyboard,(XkbDescPtr a,अचिन्हित पूर्णांक b, Bool c))
SDL_X11_SYM(Status,XkbRefreshKeyboardMapping,(XkbMapNotifyEvent *a))
SDL_X11_SYM(Bool,XkbSetDetectableAutoRepeat,(Display* a, Bool b, Bool* c))
#पूर्ण_अगर

#अगर_घोषित X_HAVE_UTF8_STRING
SDL_X11_MODULE(UTF8)
SDL_X11_SYM(पूर्णांक,Xutf8TextListToTextProperty,(Display* a,अक्षर** b,पूर्णांक c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(पूर्णांक,Xutf8LookupString,(XIC a,XKeyPressedEvent* b,अक्षर* c,पूर्णांक d,कुंजी_Sym* e,Status* f))
SDL_X11_SYM(XIC,XCreateIC,(XIM,...))
SDL_X11_SYM(व्योम,XDestroyIC,(XIC a))
SDL_X11_SYM(अक्षर*,XGetICValues,(XIC,...))
SDL_X11_SYM(अक्षर*,XSetICValues,(XIC,...))
SDL_X11_SYM(XVaNestedList,XVaCreateNestedList,(पूर्णांक, ...))
SDL_X11_SYM(व्योम,XSetICFocus,(XIC a))
SDL_X11_SYM(व्योम,XUnsetICFocus,(XIC a))
SDL_X11_SYM(XIM,XOpenIM,(Display* a,काष्ठा _XrmHashBucketRec* b,अक्षर* c,अक्षर* d))
SDL_X11_SYM(Status,XCloseIM,(XIM a))
SDL_X11_SYM(अक्षर*, XSetIMValues,(XIM,...))
SDL_X11_SYM(Bool,XRegisterIMInstantiateCallback,(Display*,काष्ठा _XrmHashBucketRec*,अक्षर*,अक्षर*,XIDProc,XPointer))
SDL_X11_SYM(Bool,XUnregisterIMInstantiateCallback,(Display*,काष्ठा _XrmHashBucketRec*,अक्षर*,अक्षर*,XIDProc,XPointer))
SDL_X11_SYM(व्योम,Xutf8DrawString,(Display *a, Drawable b, XFontSet c, GC d, पूर्णांक e, पूर्णांक f, _Xconst अक्षर *g, पूर्णांक h))
SDL_X11_SYM(पूर्णांक,Xutf8TextExtents,(XFontSet a, _Xconst अक्षर* b, पूर्णांक c, XRectangle* d, XRectangle* e))
SDL_X11_SYM(अक्षर*,XSetLocaleModifiers,(स्थिर अक्षर *a))
SDL_X11_SYM(अक्षर*,Xutf8ResetIC,(XIC a))
SDL_X11_SYM(XFontSetExtents*,XExtentsOfFontSet,(XFontSet a))
SDL_X11_SYM(Bool,XContextDependentDrawing,(XFontSet a))
#पूर्ण_अगर


#अगर_अघोषित NO_SHARED_MEMORY
SDL_X11_MODULE(SHM)
SDL_X11_SYM(Status,XShmAttach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmDetach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmPutImage,(Display* a,Drawable b,GC c,XImage* d,पूर्णांक e,पूर्णांक f,पूर्णांक g,पूर्णांक h,अचिन्हित पूर्णांक i,अचिन्हित पूर्णांक j,Bool k))
SDL_X11_SYM(Status,XShmGetImage,(Display* a,Drawable b,XImage *c,पूर्णांक d, पूर्णांक e, अचिन्हित दीर्घ f))
SDL_X11_SYM(XImage*,XShmCreateImage,(Display* a,Visual* b,अचिन्हित पूर्णांक c,पूर्णांक d,अक्षर* e,XShmSegmentInfo* f,अचिन्हित पूर्णांक g,अचिन्हित पूर्णांक h))
SDL_X11_SYM(Pixmap,XShmCreatePixmap,(Display *a,Drawable b,अक्षर* c,XShmSegmentInfo* d, अचिन्हित पूर्णांक e, अचिन्हित पूर्णांक f, अचिन्हित पूर्णांक g))
SDL_X11_SYM(Bool,XShmQueryExtension,(Display* a))
SDL_X11_SYM(Status,XShmQueryVersion,(Display* a, पूर्णांक *b, पूर्णांक *c, Bool *d))
SDL_X11_SYM(पूर्णांक,XShmPixmapFormat,(Display* a))
#पूर्ण_अगर

/*
 * Not required...these only exist in code in headers on some 64-bit platforms,
 *  and are removed via macros elsewhere, so it's safe for them to be missing.
 */
#अगर_घोषित LONG64
SDL_X11_MODULE(IO_32BIT)
SDL_X11_SYM(पूर्णांक,_XData32,(Display *dpy,रेजिस्टर _Xconst दीर्घ *तथ्य,अचिन्हित len))
SDL_X11_SYM(व्योम,_XRead32,(Display *dpy,रेजिस्टर दीर्घ *तथ्य,दीर्घ len))
#पूर्ण_अगर

/*
 * These only show up on some variants of Unix.
 */
#अगर_घोषित SDL_PLATFORM_OSF
SDL_X11_MODULE(OSF_ENTRY_POINTS)
SDL_X11_SYM(व्योम,Smt_बफर_Overflow,(Display *dpy,रेजिस्टर smtDisplayPtr p))
SDL_X11_SYM(व्योम,_SmtIpError,(Display *dpy,रेजिस्टर smtDisplayPtr p,पूर्णांक i))
SDL_X11_SYM(पूर्णांक,ip_Allocate_तथ्य,(ChannelPtr a,IPCard b,IPDataPtr * c))
SDL_X11_SYM(पूर्णांक,ip_Unallocate_And_Send_तथ्य,(ChannelPtr a,IPCard b))
#पूर्ण_अगर

// XCursor support
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XCURSOR
SDL_X11_MODULE(XCURSOR)
SDL_X11_SYM(XcursorImage*,XcursorImageCreate,(पूर्णांक a,पूर्णांक b))
SDL_X11_SYM(XcursorImages*,XcursorImagesCreate,(पूर्णांक a))
SDL_X11_SYM(व्योम,XcursorImageDestroy,(XcursorImage *a))
SDL_X11_SYM(व्योम,XcursorImagesDestroy,(XcursorImages *a))
SDL_X11_SYM(Cursor,XcursorImageLoadCursor,(Display *a,स्थिर XcursorImage *b))
SDL_X11_SYM(Cursor,XcursorImagesLoadCursor,(Display *a,स्थिर XcursorImages *b))
SDL_X11_SYM(Cursor,XcursorLibraryLoadCursor,(Display *a, स्थिर अक्षर *b))
#पूर्ण_अगर

// Xdbe support
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XDBE
SDL_X11_MODULE(XDBE)
SDL_X11_SYM(Status,XdbeQueryExtension,(Display *dpy,पूर्णांक *major_version_return,पूर्णांक *minor_version_return))
SDL_X11_SYM(Xdbe_Back_बफर,Xdbe_Allocate_Back_बफर_Name,(Display *dpy,Window window,XdbeSwapAction swap_action))
SDL_X11_SYM(Status,Xdbe_Deallocate_Back_बफर_Name,(Display *dpy,Xdbe_Back_बफर बफर_2))
SDL_X11_SYM(Status,XdbeSwapBuffers,(Display *dpy,XdbeSwapInfo *swap_info,पूर्णांक अंक_windows))
SDL_X11_SYM(Status,XdbeBeginIdiom,(Display *dpy))
SDL_X11_SYM(Status,XdbeEndIdiom,(Display *dpy))
SDL_X11_SYM(XdbeScreenVisualInfo*,XdbeGetVisualInfo,(Display *dpy,Drawable *screen_specifiers,पूर्णांक *अंक_screens))
SDL_X11_SYM(व्योम,XdbeFreeVisualInfo,(XdbeScreenVisualInfo *visual_info))
SDL_X11_SYM(Xdbe_Back_बफर_Attributes*,Xdbe_Get_Back_बफर_Attributes,(Display *dpy,Xdbe_Back_बफर बफर_2))
#पूर्ण_अगर

// XInput2 support for multiple mice, tablets, etc.
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2
SDL_X11_MODULE(XINPUT2)
SDL_X11_SYM(XIDeviceInfo*,XIQueryDevice,(Display *a,पूर्णांक b,पूर्णांक *c))
SDL_X11_SYM(व्योम,XIFreeDeviceInfo,(XIDeviceInfo *a))
SDL_X11_SYM(पूर्णांक,XISelectEvents,(Display *a,Window b,XIEventMask *c,पूर्णांक d))
SDL_X11_SYM(पूर्णांक,XIGrabTouchBegin,(Display *a,पूर्णांक b,Window c,पूर्णांक d,XIEventMask *e,पूर्णांक f,XIGrabModifiers *g))
SDL_X11_SYM(पूर्णांक,XIUngrabTouchBegin, (Display *a,पूर्णांक b,Window c, पूर्णांक d,XIGrabModifiers *e))
SDL_X11_SYM(Status,XIQueryVersion,(Display *a,पूर्णांक *b,पूर्णांक *c))
SDL_X11_SYM(XIEventMask*,XIGetSelectedEvents,(Display *a,Window b,पूर्णांक *c))
SDL_X11_SYM(Bool,XIGetClientPointer,(Display *a,Window b,पूर्णांक *c))
SDL_X11_SYM(Bool,XIWarpPointer,(Display *a,पूर्णांक b,Window c,Window d,द्विगुन e,द्विगुन f,पूर्णांक g,पूर्णांक h,द्विगुन i,द्विगुन j))
SDL_X11_SYM(Status,XIGetProperty,(Display *a,पूर्णांक b,Atom c,दीर्घ d,दीर्घ e,Bool f, Atom g, Atom *h, पूर्णांक *i, अचिन्हित दीर्घ *j, अचिन्हित दीर्घ *k, अचिन्हित अक्षर **l))
#पूर्ण_अगर

// XRandR support
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XRANDR
SDL_X11_MODULE(XRANDR)
SDL_X11_SYM(Status,XRRQueryVersion,(Display *dpy,पूर्णांक *major_versionp,पूर्णांक *minor_versionp))
SDL_X11_SYM(Bool,XRRQueryExtension,(Display *dpy,पूर्णांक *event_base_return,पूर्णांक *error_base_return))
SDL_X11_SYM(XRRScreenConfiguration *,XRRGetScreenInfo,(Display *dpy,Drawable draw))
SDL_X11_SYM(आकार_ID,XRRConfigCurrentConfiguration,(XRRScreenConfiguration *config,Rotation *rotation))
SDL_X11_SYM(लघु,XRRConfigCurrentRate,(XRRScreenConfiguration *config))
SDL_X11_SYM(लघु *,XRRConfigRates,(XRRScreenConfiguration *config,पूर्णांक आकार_ID_2,पूर्णांक *nrates))
SDL_X11_SYM(XRRScreen_आकार *,XRRConfigSizes,(XRRScreenConfiguration *config,पूर्णांक *nsizes))
SDL_X11_SYM(Status,XRRSetScreenConfigAndRate,(Display *dpy,XRRScreenConfiguration *config,Drawable draw,पूर्णांक आकार_सूचकांक,Rotation rotation,लघु rate,Time timestamp))
SDL_X11_SYM(व्योम,XRRFreeScreenConfigInfo,(XRRScreenConfiguration *config))
SDL_X11_SYM(व्योम,XRRSet_Screen_आकार,(Display *dpy, Window window,पूर्णांक width, पूर्णांक height,पूर्णांक mmWidth, पूर्णांक mmHeight))
SDL_X11_SYM(Status,XRRGet_Screen_आकार_Range,(Display *dpy, Window window,पूर्णांक *minWidth, पूर्णांक *minHeight, पूर्णांक *maxWidth, पूर्णांक *maxHeight))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResources,(Display *dpy, Window window))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResourcesCurrent,(Display *dpy, Window window))
SDL_X11_SYM(व्योम,XRRFreeScreenResources,(XRRScreenResources *resources))
SDL_X11_SYM(XRROutputInfo *,XRRGetOutputInfo,(Display *dpy, XRRScreenResources *resources, RROutput output))
SDL_X11_SYM(व्योम,XRRFreeOutputInfo,(XRROutputInfo *outputInfo))
SDL_X11_SYM(XRRCrtcInfo *,XRRGetCrtcInfo,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc))
SDL_X11_SYM(व्योम,XRRFreeCrtcInfo,(XRRCrtcInfo *crtcInfo))
SDL_X11_SYM(Status,XRRSetCrtcConfig,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc, Time timestamp, पूर्णांक x, पूर्णांक y, RRMode mode, Rotation rotation, RROutput *outputs, पूर्णांक noutputs))
SDL_X11_SYM(Atom*,XRRListOutputProperties,(Display *dpy, RROutput output, पूर्णांक *nprop))
SDL_X11_SYM(XRRPropertyInfo*,XRRQueryOutputProperty,(Display *dpy,RROutput output, Atom property))
SDL_X11_SYM(पूर्णांक,XRRGetOutputProperty,(Display *dpy,RROutput output, Atom property, दीर्घ offset, दीर्घ लंबाई, Bool _delete, Bool pending, Atom req_type, Atom *actual_type, पूर्णांक *actual_format, अचिन्हित दीर्घ *nitems, अचिन्हित दीर्घ *bytes_after, अचिन्हित अक्षर **prop))
SDL_X11_SYM(RROutput,XRRGetOutputPrimary,(Display *dpy,Window window))
SDL_X11_SYM(व्योम,XRRSelect_निवेश,(Display *dpy, Window window, पूर्णांक mask))
SDL_X11_SYM(Status,XRRGetCrtcTransform,(Display *dpy,RRCrtc crtc,XRRCrtcTransformAttributes **attributes))
#पूर्ण_अगर

// MIT-SCREEN-SAVER support
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XSCRNSAVER
SDL_X11_MODULE(XSS)
SDL_X11_SYM(Bool,XScreenSaverQueryExtension,(Display *dpy,पूर्णांक *event_base,पूर्णांक *error_base))
SDL_X11_SYM(Status,XScreenSaverQueryVersion,(Display *dpy,पूर्णांक *major_versionp,पूर्णांक *minor_versionp))
SDL_X11_SYM(व्योम,XScreenSaverSuspend,(Display *dpy,Bool suspend))
#पूर्ण_अगर

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XSHAPE
SDL_X11_MODULE(XSHAPE)
SDL_X11_SYM(व्योम,XShapeCombineMask,(Display *dpy,Window dest,पूर्णांक dest_kind,पूर्णांक x_off,पूर्णांक y_off,Pixmap src,पूर्णांक op))
SDL_X11_SYM(व्योम,XShapeCombineRegion,(Display *a,Window b,पूर्णांक c,पूर्णांक d,पूर्णांक e,Region f,पूर्णांक g))
#पूर्ण_अगर

#अघोषित SDL_X11_MODULE
#अघोषित SDL_X11_SYM

/* *INDENT-ON* */ // clang-format on
