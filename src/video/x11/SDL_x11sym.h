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

#यदि_अपरिभाषितम् SDL_X11_MODULE
#परिभाषय SDL_X11_MODULE(modname)
#यदि_अन्तः

#यदि_अपरिभाषितम् SDL_X11_SYM
#परिभाषय SDL_X11_SYM(rc, fn, params)
#यदि_अन्तः

SDL_X11_MODULE(BASEXLIB)
SDL_X11_SYM(XSizeHints*,XAlloc_आकार_Hints,(शून्य))
SDL_X11_SYM(XWMHints*,XAllocWMHints,(शून्य))
SDL_X11_SYM(XClassHint*,XAllocClassHint,(शून्य))
SDL_X11_SYM(पूर्णाङ्क,XChangePointerControl,(Display* a,Bool b,Bool c,पूर्णाङ्क d,पूर्णाङ्क e,पूर्णाङ्क f))
SDL_X11_SYM(पूर्णाङ्क,XChangeProperty,(Display* a,गवाक्षः_2 b,Atom c,Atom d,पूर्णाङ्क e,पूर्णाङ्क f,_Xconst अचिह्नित वर्ण* g,पूर्णाङ्क h))
SDL_X11_SYM(Bool,XCheckIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(पूर्णाङ्क,XClear_गवाक्षः,(Display* a,गवाक्षः_2 b))
SDL_X11_SYM(पूर्णाङ्क,XCloseDisplay,(Display* a))
SDL_X11_SYM(पूर्णाङ्क,XConvertSelection,(Display* a,Atom b,Atom c,Atom d,गवाक्षः_2 e,Time f))
SDL_X11_SYM(Pixmap,XCreate_Bitmap_From_दत्त,(Display *dpy,Drawable d,_Xconst वर्ण *दत्त,अचिह्नित पूर्णाङ्क विस्तारः,अचिह्नित पूर्णाङ्क height))
SDL_X11_SYM(Colormap,XCreateColormap,(Display* a,गवाक्षः_2 b,Visual* c,पूर्णाङ्क d))
SDL_X11_SYM(Cursor,XCreatePixmapCursor,(Display* a,Pixmap b,Pixmap c,XColor* d,XColor* e,अचिह्नित पूर्णाङ्क f,अचिह्नित पूर्णाङ्क g))
SDL_X11_SYM(Cursor,XCreatePixmap,(Display* a,Drawable b,अचिह्नित पूर्णाङ्क d,अचिह्नित पूर्णाङ्क e,अचिह्नित पूर्णाङ्क f))
SDL_X11_SYM(Cursor,XCreateFontCursor,(Display* a,अचिह्नित पूर्णाङ्क b))
SDL_X11_SYM(XFont_समुच्चयः,XCreate_Font_समुच्चयः,(Display* a, _Xconst वर्ण* b, वर्ण*** c, पूर्णाङ्क* d, वर्ण** e))
SDL_X11_SYM(GC,XCreateGC,(Display* a,Drawable b,अचिह्नित दीर्घ c,XGCValues* d))
SDL_X11_SYM(शून्य,XSetFont,(Display* a,GC b,Font c))
SDL_X11_SYM(स्थितिः_2,XAllocColor,(Display *a, Colormap b, XColor *c))
SDL_X11_SYM(XImage*,XCreateImage,(Display* a,Visual* b,अचिह्नित पूर्णाङ्क c,पूर्णाङ्क d,पूर्णाङ्क e,वर्ण* f,अचिह्नित पूर्णाङ्क g,अचिह्नित पूर्णाङ्क h,पूर्णाङ्क i,पूर्णाङ्क j))
SDL_X11_SYM(गवाक्षः_2,XCreate_गवाक्षः,(Display* a,गवाक्षः_2 b,पूर्णाङ्क c,पूर्णाङ्क d,अचिह्नित पूर्णाङ्क e,अचिह्नित पूर्णाङ्क f,अचिह्नित पूर्णाङ्क g,पूर्णाङ्क h,अचिह्नित पूर्णाङ्क i,Visual* j,अचिह्नित दीर्घ k,XSet_गवाक्षः_गुणाः* l))
SDL_X11_SYM(शून्य,XCopyArea,(Display *a, Drawable b, Drawable c, GC d, पूर्णाङ्क e, पूर्णाङ्क f, अचिह्नित पूर्णाङ्क g, अचिह्नित पूर्णाङ्क h, पूर्णाङ्क i, पूर्णाङ्क j))
SDL_X11_SYM(पूर्णाङ्क,XDefineCursor,(Display* a,गवाक्षः_2 b,Cursor c))
SDL_X11_SYM(पूर्णाङ्क,XDeleteProperty,(Display* a,गवाक्षः_2 b,Atom c))
SDL_X11_SYM(पूर्णाङ्क,XDestroy_गवाक्षः,(Display* a,गवाक्षः_2 b))
SDL_X11_SYM(पूर्णाङ्क,XDisplayKeycodes,(Display* a,पूर्णाङ्क* b,पूर्णाङ्क* c))
SDL_X11_SYM(पूर्णाङ्क,XDrawRectangle,(Display* a,Drawable b,GC c,पूर्णाङ्क d,पूर्णाङ्क e,अचिह्नित पूर्णाङ्क f,अचिह्नित पूर्णाङ्क g))
SDL_X11_SYM(पूर्णाङ्क,XFonts_सम्बन्धि_Font_समुच्चयः,(XFont_समुच्चयः a,XFontStruct ***b,वर्ण ***c))
SDL_X11_SYM(पूर्णाङ्क,XFillArc,(Display* a,Drawable b,GC c,पूर्णाङ्क d,पूर्णाङ्क e,अचिह्नित पूर्णाङ्क f,अचिह्नित पूर्णाङ्क g, पूर्णाङ्क h, पूर्णाङ्क i))
SDL_X11_SYM(वर्ण*,XDisplayName,(_Xconst वर्ण* a))
SDL_X11_SYM(पूर्णाङ्क,XDrawString,(Display* a,Drawable b,GC c,पूर्णाङ्क d,पूर्णाङ्क e,_Xconst वर्ण* f,पूर्णाङ्क g))
SDL_X11_SYM(पूर्णाङ्क,XEventsQueued,(Display* a,पूर्णाङ्क b))
SDL_X11_SYM(पूर्णाङ्क,XFillRectangle,(Display* a,Drawable b,GC c,पूर्णाङ्क d,पूर्णाङ्क e,अचिह्नित पूर्णाङ्क f,अचिह्नित पूर्णाङ्क g))
SDL_X11_SYM(Bool,XFilterEvent,(XEvent *event,गवाक्षः_2 w))
SDL_X11_SYM(पूर्णाङ्क,XFlush,(Display* a))
SDL_X11_SYM(पूर्णाङ्क,XFree,(शून्य*a))
SDL_X11_SYM(पूर्णाङ्क,XFreeCursor,(Display* a,Cursor b))
SDL_X11_SYM(शून्य,XFree_Font_समुच्चयः,(Display* a, XFont_समुच्चयः b))
SDL_X11_SYM(पूर्णाङ्क,XFreeGC,(Display* a,GC b))
SDL_X11_SYM(पूर्णाङ्क,XFreeFont,(Display* a, XFontStruct* b))
SDL_X11_SYM(पूर्णाङ्क,XFreeModifiermap,(XModifierKeymap* a))
SDL_X11_SYM(पूर्णाङ्क,XFreePixmap,(Display* a,Pixmap b))
SDL_X11_SYM(पूर्णाङ्क,XFreeColormap,(Display* a,Colormap b))
SDL_X11_SYM(शून्य,XFreeStringList,(वर्ण** a))
SDL_X11_SYM(वर्ण*,XGetAtomName,(Display *a,Atom b))
SDL_X11_SYM(पूर्णाङ्क,XGet_निवेशः_Focus,(Display *a,गवाक्षः_2 *b,पूर्णाङ्क *c))
SDL_X11_SYM(कुञ्चिका_Sym*,XGetKeyboardMapping,(Display *a, कुञ्चिका_संहिता_2 b, पूर्णाङ्क c, पूर्णाङ्क *d))
SDL_X11_SYM(पूर्णाङ्क,XGetErrorDatabaseText,(Display* a,_Xconst वर्ण* b,_Xconst वर्ण* c,_Xconst वर्ण* d,वर्ण* e,पूर्णाङ्क f))
SDL_X11_SYM(XModifierKeymap*,XGetModifierMapping,(Display* a))
SDL_X11_SYM(पूर्णाङ्क,XGetPointerControl,(Display* a,पूर्णाङ्क* b,पूर्णाङ्क* c,पूर्णाङ्क* d))
SDL_X11_SYM(गवाक्षः_2,XGetSelectionOwner,(Display* a,Atom b))
SDL_X11_SYM(XVisualInfo*,XGetVisualInfo,(Display* a,दीर्घ b,XVisualInfo* c,पूर्णाङ्क* d))
SDL_X11_SYM(स्थितिः_2,XGet_गवाक्षः_गुणाः,(Display* a,गवाक्षः_2 b,XWindow_गुणाः* c))
SDL_X11_SYM(पूर्णाङ्क,XGet_गवाक्षः_Property,(Display* a,गवाक्षः_2 b,Atom c,दीर्घ d,दीर्घ e,Bool f,Atom g,Atom* h,पूर्णाङ्क* i,अचिह्नित दीर्घ* j,अचिह्नित दीर्घ *k,अचिह्नित वर्ण **l))
SDL_X11_SYM(XWMHints*,XGetWMHints,(Display* a,गवाक्षः_2 b))
SDL_X11_SYM(स्थितिः_2,XGetWMNormalHints,(Display *a,गवाक्षः_2 b, XSizeHints *c, दीर्घ *d))
SDL_X11_SYM(पूर्णाङ्क,XIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(पूर्णाङ्क,XGrabKeyboard,(Display* a,गवाक्षः_2 b,Bool c,पूर्णाङ्क d,पूर्णाङ्क e,Time f))
SDL_X11_SYM(पूर्णाङ्क,XGrabPointer,(Display* a,गवाक्षः_2 b,Bool c,अचिह्नित पूर्णाङ्क d,पूर्णाङ्क e,पूर्णाङ्क f,गवाक्षः_2 g,Cursor h,Time i))
SDL_X11_SYM(पूर्णाङ्क,XGrabServer,(Display* a))
SDL_X11_SYM(स्थितिः_2,XIconify_गवाक्षः,(Display* a,गवाक्षः_2 b,पूर्णाङ्क c))
SDL_X11_SYM(कुञ्चिका_संहिता_2,XKeysym_गन्तव्यम्_Keycode,(Display* a,कुञ्चिका_Sym b))
SDL_X11_SYM(वर्ण*,XKeysym_गन्तव्यम्_String,(कुञ्चिका_Sym a))
SDL_X11_SYM(पूर्णाङ्क,XInstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(Atom,XInternAtom,(Display* a,_Xconst वर्ण* b,Bool c))
SDL_X11_SYM(XPixmap_Format_मानानि*,XListPixmapFormats,(Display* a,पूर्णाङ्क* b))
SDL_X11_SYM(XFontStruct*,XLoadQueryFont,(Display* a,_Xconst वर्ण* b))
SDL_X11_SYM(कुञ्चिका_Sym,XLookupKeysym,(XKeyEvent* a,पूर्णाङ्क b))
SDL_X11_SYM(पूर्णाङ्क,XLookupString,(XKeyEvent* a,वर्ण* b,पूर्णाङ्क c,कुञ्चिका_Sym* d,XCompose_स्थितिः* e))
SDL_X11_SYM(पूर्णाङ्क,XMapRaised,(Display* a,गवाक्षः_2 b))
SDL_X11_SYM(स्थितिः_2,XMatchVisualInfo,(Display* a,पूर्णाङ्क b,पूर्णाङ्क c,पूर्णाङ्क d,XVisualInfo* e))
SDL_X11_SYM(पूर्णाङ्क,XMissingExtension,(Display* a,_Xconst वर्ण* b))
SDL_X11_SYM(पूर्णाङ्क,XMove_गवाक्षः,(Display* a,गवाक्षः_2 b,पूर्णाङ्क c,पूर्णाङ्क d))
SDL_X11_SYM(Display*,XOpenDisplay,(_Xconst वर्ण* a))
SDL_X11_SYM(स्थितिः_2,XInit_तन्तवः,(शून्य))
SDL_X11_SYM(पूर्णाङ्क,XPeekEvent,(Display* a,XEvent* b))
SDL_X11_SYM(पूर्णाङ्क,XPending,(Display* a))
SDL_X11_SYM(XImage*,XGetImage,(Display* a,Drawable b,पूर्णाङ्क c, पूर्णाङ्क d,अचिह्नित पूर्णाङ्क e,अचिह्नित पूर्णाङ्क f,अचिह्नित दीर्घ g,पूर्णाङ्क h))
SDL_X11_SYM(पूर्णाङ्क,XPutImage,(Display* a,Drawable b,GC c,XImage* d,पूर्णाङ्क e,पूर्णाङ्क f,पूर्णाङ्क g,पूर्णाङ्क h,अचिह्नित पूर्णाङ्क i,अचिह्नित पूर्णाङ्क j))
SDL_X11_SYM(पूर्णाङ्क,XQueryKeymap,(Display* a,वर्ण b[32]))
SDL_X11_SYM(Bool,XQueryPointer,(Display* a,गवाक्षः_2 b,गवाक्षः_2* c,गवाक्षः_2* d,पूर्णाङ्क* e,पूर्णाङ्क* f,पूर्णाङ्क* g,पूर्णाङ्क* h,अचिह्नित पूर्णाङ्क* i))
SDL_X11_SYM(पूर्णाङ्क,XRaise_गवाक्षः,(Display* a,गवाक्षः_2 b))
SDL_X11_SYM(पूर्णाङ्क,XReparent_गवाक्षः,(Display* a,गवाक्षः_2 b,गवाक्षः_2 c,पूर्णाङ्क d,पूर्णाङ्क e))
SDL_X11_SYM(पूर्णाङ्क,XResetScreenSaver,(Display* a))
SDL_X11_SYM(पूर्णाङ्क,XResize_गवाक्षः,(Display* a,गवाक्षः_2 b,अचिह्नित पूर्णाङ्क c,अचिह्नित पूर्णाङ्क d))
SDL_X11_SYM(पूर्णाङ्क,XScreen_सङ्ख्या_सम्बन्धि_Screen,(Screen* a))
SDL_X11_SYM(पूर्णाङ्क,XSelect_निवेशः,(Display* a,गवाक्षः_2 b,दीर्घ c))
SDL_X11_SYM(स्थितिः_2,XSendEvent,(Display* a,गवाक्षः_2 b,Bool c,दीर्घ d,XEvent* e))
SDL_X11_SYM(XErrorHandler,XSetErrorHandler,(XErrorHandler a))
SDL_X11_SYM(पूर्णाङ्क,XSetForeground,(Display* a,GC b,अचिह्नित दीर्घ c))
SDL_X11_SYM(XIOErrorHandler,XSetIOErrorHandler,(XIOErrorHandler a))
SDL_X11_SYM(पूर्णाङ्क,XSet_निवेशः_Focus,(Display *a,गवाक्षः_2 b,पूर्णाङ्क c,Time d))
SDL_X11_SYM(पूर्णाङ्क,XSetSelectionOwner,(Display* a,Atom b,गवाक्षः_2 c,Time d))
SDL_X11_SYM(पूर्णाङ्क,XSetTransientForHint,(Display* a,गवाक्षः_2 b,गवाक्षः_2 c))
SDL_X11_SYM(शून्य,XSetTextProperty,(Display* a,गवाक्षः_2 b,XTextProperty* c,Atom d))
SDL_X11_SYM(पूर्णाङ्क,XSet_गवाक्षः_Background,(Display* a,गवाक्षः_2 b,अचिह्नित दीर्घ c))
SDL_X11_SYM(शून्य,XSetWMHints,(Display* a,गवाक्षः_2 b,XWMHints* c))
SDL_X11_SYM(शून्य,XSetWMNormalHints,(Display* a,गवाक्षः_2 b,XSizeHints* c))
SDL_X11_SYM(शून्य,XSetWMProperties,(Display* a,गवाक्षः_2 b,XTextProperty* c,XTextProperty* d,वर्ण** e,पूर्णाङ्क f,XSizeHints* g,XWMHints* h,XClassHint* i))
SDL_X11_SYM(स्थितिः_2,XSetWMProtocols,(Display* a,गवाक्षः_2 b,Atom* c,पूर्णाङ्क d))
SDL_X11_SYM(पूर्णाङ्क,XStoreColors,(Display* a,Colormap b,XColor* c,पूर्णाङ्क d))
SDL_X11_SYM(पूर्णाङ्क,XStoreName,(Display* a,गवाक्षः_2 b,_Xconst वर्ण* c))
SDL_X11_SYM(स्थितिः_2,XString_List_गन्तव्यम्_Text_Property,(वर्ण** a,पूर्णाङ्क b,XTextProperty* c))
SDL_X11_SYM(पूर्णाङ्क,XSync,(Display* a,Bool b))
SDL_X11_SYM(पूर्णाङ्क,XTextExtents,(XFontStruct* a,_Xconst वर्ण* b,पूर्णाङ्क c,पूर्णाङ्क* d,पूर्णाङ्क* e,पूर्णाङ्क* f,XCharStruct* g))
SDL_X11_SYM(Bool,XTranslateCoordinates,(Display *a,गवाक्षः_2 b,गवाक्षः_2 c,पूर्णाङ्क d,पूर्णाङ्क e,पूर्णाङ्क* f,पूर्णाङ्क* g,गवाक्षः_2* h))
SDL_X11_SYM(पूर्णाङ्क,XUndefineCursor,(Display* a,गवाक्षः_2 b))
SDL_X11_SYM(पूर्णाङ्क,XUngrabKeyboard,(Display* a,Time b))
SDL_X11_SYM(पूर्णाङ्क,XUngrabPointer,(Display* a,Time b))
SDL_X11_SYM(पूर्णाङ्क,XUngrabServer,(Display* a))
SDL_X11_SYM(पूर्णाङ्क,XUninstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(पूर्णाङ्क,XUnloadFont,(Display* a,Font b))
SDL_X11_SYM(पूर्णाङ्क,XWarpPointer,(Display* a,गवाक्षः_2 b,गवाक्षः_2 c,पूर्णाङ्क d,पूर्णाङ्क e,अचिह्नित पूर्णाङ्क f,अचिह्नित पूर्णाङ्क g,पूर्णाङ्क h,पूर्णाङ्क i))
SDL_X11_SYM(पूर्णाङ्क,XWindowEvent,(Display* a,गवाक्षः_2 b,दीर्घ c,XEvent* d))
SDL_X11_SYM(स्थितिः_2,XWithdraw_गवाक्षः,(Display* a,गवाक्षः_2 b,पूर्णाङ्क c))
SDL_X11_SYM(VisualID,XVisualIDFromVisual,(Visual* a))
SDL_X11_SYM(वर्ण*,XGetDefault,(Display* a,_Xconst वर्ण* b, _Xconst वर्ण* c))
SDL_X11_SYM(Bool,XQueryExtension,(Display* a,_Xconst वर्ण* b,पूर्णाङ्क* c,पूर्णाङ्क* d,पूर्णाङ्क* e))
SDL_X11_SYM(वर्ण *,XDisplayString,(Display* a))
SDL_X11_SYM(पूर्णाङ्क,XGetErrorText,(Display* a,पूर्णाङ्क b,वर्ण* c,पूर्णाङ्क d))
SDL_X11_SYM(शून्य,XEat_दत्त,(Display* a,अचिह्नित दीर्घ b))
SDL_X11_SYM(शून्य,_XFlush,(Display* a))
SDL_X11_SYM(शून्य,_XFlushGCCache,(Display* a,GC b))
SDL_X11_SYM(पूर्णाङ्क,_XRead,(Display* a,वर्ण* b,दीर्घ c))
SDL_X11_SYM(शून्य,_XReadPad,(Display* a,वर्ण* b,दीर्घ c))
SDL_X11_SYM(शून्य,_XSend,(Display* a,_Xconst वर्ण* b,दीर्घ c))
SDL_X11_SYM(स्थितिः_2,_XReply,(Display* a,x_प्रत्युत्तरम्* b,पूर्णाङ्क c,Bool d))
SDL_X11_SYM(अचिह्नित दीर्घ,XSet_चरमः_Request_Read,(Display* a,x_Generic_प्रत्युत्तरम्* b))
SDL_X11_SYM(SDL_X11_XSynchronizeRetType,XSynchronize,(Display* a,Bool b))
SDL_X11_SYM(SDL_X11_XESet_Wire_गन्तव्यम्_Event_Ret_Type,XESet_Wire_गन्तव्यम्_Event,(Display* a,पूर्णाङ्क b,SDL_X11_XESet_Wire_गन्तव्यम्_Event_Ret_Type c))
SDL_X11_SYM(SDL_X11_XESet_Event_गन्तव्यम्_Wire_Ret_Type,XESet_Event_गन्तव्यम्_Wire,(Display* a,पूर्णाङ्क b,SDL_X11_XESet_Event_गन्तव्यम्_Wire_Ret_Type c))
SDL_X11_SYM(शून्य,XRefreshKeyboardMapping,(XMappingEvent *a))
SDL_X11_SYM(पूर्णाङ्क,XQuery_वृक्षः,(Display* a,गवाक्षः_2 b,गवाक्षः_2* c,गवाक्षः_2* d,गवाक्षः_2** e,अचिह्नित पूर्णाङ्क* f))
SDL_X11_SYM(Bool,XSupportsLocale,(शून्य))
SDL_X11_SYM(स्थितिः_2,Xmb_Text_List_गन्तव्यम्_Text_Property,(Display* a,वर्ण** b,पूर्णाङ्क c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(Region,XCreateRegion,(शून्य))
SDL_X11_SYM(पूर्णाङ्क,XUnionRectWithRegion,(XRectangle *a, Region b, Region c))
SDL_X11_SYM(शून्य,XDestroyRegion,(Region))
SDL_X11_SYM(शून्य,XrmInitialize,(शून्य))
SDL_X11_SYM(वर्ण*,XResourceManagerString,(Display *display))
SDL_X11_SYM(XrmDatabase,XrmGetStringDatabase,(वर्ण *दत्त))
SDL_X11_SYM(शून्य,XrmDestroyDatabase,(XrmDatabase db))
SDL_X11_SYM(Bool,XrmGetResource,(XrmDatabase db, वर्ण* str_name, वर्ण* str_class, वर्ण **str_type_return, Xrm_मानम् *))
SDL_X11_SYM(पूर्णाङ्क,XGetPointerMapping,(Display *a, अचिह्नित वर्ण *b, अचिह्नित पूर्णाङ्क c))

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XFIXES
SDL_X11_MODULE(XFIXES)
SDL_X11_SYM(PointerBarrier, XFixesCreatePointerBarrier, (Display* a, गवाक्षः_2 b, पूर्णाङ्क c, पूर्णाङ्क d, पूर्णाङ्क e, पूर्णाङ्क f, पूर्णाङ्क g, पूर्णाङ्क h, पूर्णाङ्क *i))
SDL_X11_SYM(शून्य, XFixesDestroyPointerBarrier, (Display* a, PointerBarrier b))
SDL_X11_SYM(पूर्णाङ्क, XIBarrierReleasePointer,(Display* a,  पूर्णाङ्क b, PointerBarrier c, BarrierEventID d)) // this is actually Xinput2
SDL_X11_SYM(स्थितिः_2, XFixes_Query_संस्करणम्,(Display* a, पूर्णाङ्क* b, पूर्णाङ्क* c))
SDL_X11_SYM(स्थितिः_2, XFixes_Select_Selection_निवेशः, (Display* a, गवाक्षः_2 b, Atom c, अचिह्नित दीर्घ d))
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XSYNC
SDL_X11_MODULE(XSYNC)
SDL_X11_SYM(स्थितिः_2, XSyncQueryExtension, (Display* a, पूर्णाङ्क* b, पूर्णाङ्क* c))
SDL_X11_SYM(स्थितिः_2, XSyncInitialize, (Display* a, पूर्णाङ्क* b, पूर्णाङ्क* c))
SDL_X11_SYM(XSync_गणक, XSync_Create_गणक, (Display* a, XSync_मानम् b))
SDL_X11_SYM(स्थितिः_2, XSync_Destroy_गणक, (Display* a, XSync_गणक b))
SDL_X11_SYM(स्थितिः_2, XSync_समुच्चयः_गणक, (Display* a, XSync_गणक b, XSync_मानम् c))
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XTEST
SDL_X11_MODULE(XTEST)
SDL_X11_SYM(स्थितिः_2, XTestQueryExtension, (Display* a, पूर्णाङ्क* b, पूर्णाङ्क* c))
SDL_X11_SYM(पूर्णाङ्क, XTestFakeMotionEvent, (Display* a, पूर्णाङ्क b, पूर्णाङ्क c, पूर्णाङ्क d, अचिह्नित दीर्घ e))
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
SDL_X11_SYM(Bool,XGet_Event_दत्त,(Display* a,XGenericEventCookie* b))
SDL_X11_SYM(शून्य,XFree_Event_दत्त,(Display* a,XGenericEventCookie* b))
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
SDL_X11_SYM(Bool,XkbQueryExtension,(Display* a,पूर्णाङ्क * b,पूर्णाङ्क * c,पूर्णाङ्क * d,पूर्णाङ्क * e, पूर्णाङ्क *f))
SDL_X11_SYM(कुञ्चिका_Sym,Xkb_Keycode_गन्तव्यम्_Keysym,(Display* a, कुञ्चिका_संहिता_2 b, अचिह्नित पूर्णाङ्क c, अचिह्नित पूर्णाङ्क d))
SDL_X11_SYM(Bool,XkbSelectEvents,(Display* a, अचिह्नित पूर्णाङ्क b, अचिह्नित पूर्णाङ्क c, अचिह्नित दीर्घ d))
SDL_X11_SYM(Bool,XkbSelectEventDetails,(Display* a, अचिह्नित पूर्णाङ्क b, अचिह्नित पूर्णाङ्क c, अचिह्नित दीर्घ d, अचिह्नित दीर्घ e))
SDL_X11_SYM(स्थितिः_2,Xkb_Get_नामानि,(Display *a, अचिह्नित पूर्णाङ्क b, XkbDescPtr c))
SDL_X11_SYM(स्थितिः_2,XkbGetState,(Display* a,अचिह्नित पूर्णाङ्क b,XkbStatePtr c))
SDL_X11_SYM(स्थितिः_2,XkbGetUpdatedMap,(Display* a,अचिह्नित पूर्णाङ्क b,XkbDescPtr c))
SDL_X11_SYM(XkbDescPtr,XkbGetMap,(Display* a,अचिह्नित पूर्णाङ्क b,अचिह्नित पूर्णाङ्क c))
SDL_X11_SYM(शून्य,XkbFreeClientMap,(XkbDescPtr a,अचिह्नित पूर्णाङ्क b, Bool c))
SDL_X11_SYM(शून्य,XkbFreeKeyboard,(XkbDescPtr a,अचिह्नित पूर्णाङ्क b, Bool c))
SDL_X11_SYM(स्थितिः_2,XkbRefreshKeyboardMapping,(XkbMapNotifyEvent *a))
SDL_X11_SYM(Bool,Xkb_समुच्चयः_Detectable_Auto_Repeat,(Display* a, Bool b, Bool* c))
#यदि_अन्तः

#यदि_परिभाषितम् X_HAVE_UTF8_STRING
SDL_X11_MODULE(UTF8)
SDL_X11_SYM(पूर्णाङ्क,Xutf8_Text_List_गन्तव्यम्_Text_Property,(Display* a,वर्ण** b,पूर्णाङ्क c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(पूर्णाङ्क,Xutf8LookupString,(XIC a,XKeyPressedEvent* b,वर्ण* c,पूर्णाङ्क d,कुञ्चिका_Sym* e,स्थितिः_2* f))
SDL_X11_SYM(XIC,XCreateIC,(XIM,...))
SDL_X11_SYM(शून्य,XDestroyIC,(XIC a))
SDL_X11_SYM(वर्ण*,XGetICValues,(XIC,...))
SDL_X11_SYM(वर्ण*,XSetICValues,(XIC,...))
SDL_X11_SYM(XVaNestedList,XVaCreateNestedList,(पूर्णाङ्क, ...))
SDL_X11_SYM(शून्य,XSetICFocus,(XIC a))
SDL_X11_SYM(शून्य,XUnsetICFocus,(XIC a))
SDL_X11_SYM(XIM,XOpenIM,(Display* a,संरचना _XrmHashBucketRec* b,वर्ण* c,वर्ण* d))
SDL_X11_SYM(स्थितिः_2,XCloseIM,(XIM a))
SDL_X11_SYM(वर्ण*, XSetIMValues,(XIM,...))
SDL_X11_SYM(Bool,XRegisterIMInstantiateCallback,(Display*,संरचना _XrmHashBucketRec*,वर्ण*,वर्ण*,XIDProc,XPointer))
SDL_X11_SYM(Bool,XUnregisterIMInstantiateCallback,(Display*,संरचना _XrmHashBucketRec*,वर्ण*,वर्ण*,XIDProc,XPointer))
SDL_X11_SYM(शून्य,Xutf8DrawString,(Display *a, Drawable b, XFont_समुच्चयः c, GC d, पूर्णाङ्क e, पूर्णाङ्क f, _Xconst वर्ण *g, पूर्णाङ्क h))
SDL_X11_SYM(पूर्णाङ्क,Xutf8TextExtents,(XFont_समुच्चयः a, _Xconst वर्ण* b, पूर्णाङ्क c, XRectangle* d, XRectangle* e))
SDL_X11_SYM(वर्ण*,XSetLocaleModifiers,(ध्रुव वर्ण *a))
SDL_X11_SYM(वर्ण*,Xutf8ResetIC,(XIC a))
SDL_X11_SYM(XFont_समुच्चयः_Extents*,XExtents_सम्बन्धि_Font_समुच्चयः,(XFont_समुच्चयः a))
SDL_X11_SYM(Bool,XContextDependentDrawing,(XFont_समुच्चयः a))
#यदि_अन्तः


#यदि_अपरिभाषितम् NO_SHARED_स्मृतिः
SDL_X11_MODULE(SHM)
SDL_X11_SYM(स्थितिः_2,XShmAttach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(स्थितिः_2,XShmDetach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(स्थितिः_2,XShmPutImage,(Display* a,Drawable b,GC c,XImage* d,पूर्णाङ्क e,पूर्णाङ्क f,पूर्णाङ्क g,पूर्णाङ्क h,अचिह्नित पूर्णाङ्क i,अचिह्नित पूर्णाङ्क j,Bool k))
SDL_X11_SYM(स्थितिः_2,XShmGetImage,(Display* a,Drawable b,XImage *c,पूर्णाङ्क d, पूर्णाङ्क e, अचिह्नित दीर्घ f))
SDL_X11_SYM(XImage*,XShmCreateImage,(Display* a,Visual* b,अचिह्नित पूर्णाङ्क c,पूर्णाङ्क d,वर्ण* e,XShmSegmentInfo* f,अचिह्नित पूर्णाङ्क g,अचिह्नित पूर्णाङ्क h))
SDL_X11_SYM(Pixmap,XShmCreatePixmap,(Display *a,Drawable b,वर्ण* c,XShmSegmentInfo* d, अचिह्नित पूर्णाङ्क e, अचिह्नित पूर्णाङ्क f, अचिह्नित पूर्णाङ्क g))
SDL_X11_SYM(Bool,XShmQueryExtension,(Display* a))
SDL_X11_SYM(स्थितिः_2,XShm_Query_संस्करणम्,(Display* a, पूर्णाङ्क *b, पूर्णाङ्क *c, Bool *d))
SDL_X11_SYM(पूर्णाङ्क,XShmPixmapFormat,(Display* a))
#यदि_अन्तः

/*
 * Not required...these only exist in code in headers on some 64-bit platforms,
 *  and are removed via macros elsewhere, so it's safe for them to be missing.
 */
#यदि_परिभाषितम् LONG64
SDL_X11_MODULE(IO_32BIT)
SDL_X11_SYM(पूर्णाङ्क,_XData32,(Display *dpy,पञ्जिका _Xconst दीर्घ *दत्त,अचिह्नित len))
SDL_X11_SYM(शून्य,_XRead32,(Display *dpy,पञ्जिका दीर्घ *दत्त,दीर्घ len))
#यदि_अन्तः

/*
 * These only show up on some variants of Unix.
 */
#यदि_परिभाषितम् SDL_PLATFORM_OSF
SDL_X11_MODULE(OSF_प्रविष्टिः_POINTS)
SDL_X11_SYM(शून्य,Smt_बफर_अतिप्रवाहः,(Display *dpy,पञ्जिका smtDisplayPtr p))
SDL_X11_SYM(शून्य,_SmtIpError,(Display *dpy,पञ्जिका smtDisplayPtr p,पूर्णाङ्क i))
SDL_X11_SYM(पूर्णाङ्क,ip_Allocate_दत्त,(ChannelPtr a,IPCard b,IPDataPtr * c))
SDL_X11_SYM(पूर्णाङ्क,ip_Unallocate_And_Send_दत्त,(ChannelPtr a,IPCard b))
#यदि_अन्तः

// XCursor support
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XCURSOR
SDL_X11_MODULE(XCURSOR)
SDL_X11_SYM(XcursorImage*,XcursorImageCreate,(पूर्णाङ्क a,पूर्णाङ्क b))
SDL_X11_SYM(XcursorImages*,XcursorImagesCreate,(पूर्णाङ्क a))
SDL_X11_SYM(शून्य,XcursorImageDestroy,(XcursorImage *a))
SDL_X11_SYM(शून्य,XcursorImagesDestroy,(XcursorImages *a))
SDL_X11_SYM(Cursor,Xcursor_Image_आरोपय_Cursor,(Display *a,ध्रुव XcursorImage *b))
SDL_X11_SYM(Cursor,Xcursor_Images_आरोपय_Cursor,(Display *a,ध्रुव XcursorImages *b))
SDL_X11_SYM(Cursor,Xcursor_Library_आरोपय_Cursor,(Display *a, ध्रुव वर्ण *b))
#यदि_अन्तः

// Xdbe support
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XDBE
SDL_X11_MODULE(XDBE)
SDL_X11_SYM(स्थितिः_2,XdbeQueryExtension,(Display *dpy,पूर्णाङ्क *major_संस्करणम्_return,पूर्णाङ्क *minor_संस्करणम्_return))
SDL_X11_SYM(Xdbe_पृष्ठभागः_बफर,Xdbe_Allocate_पृष्ठभागः_बफर_Name,(Display *dpy,गवाक्षः_2 गवाक्षः,XdbeSwapAction swap_action))
SDL_X11_SYM(स्थितिः_2,Xdbe_Deallocate_पृष्ठभागः_बफर_Name,(Display *dpy,Xdbe_पृष्ठभागः_बफर बफर_2))
SDL_X11_SYM(स्थितिः_2,XdbeSwapBuffers,(Display *dpy,XdbeSwapInfo *swap_info,पूर्णाङ्क अङ्कः_windows))
SDL_X11_SYM(स्थितिः_2,XdbeBeginIdiom,(Display *dpy))
SDL_X11_SYM(स्थितिः_2,Xdbe_अन्तः_Idiom,(Display *dpy))
SDL_X11_SYM(XdbeScreenVisualInfo*,XdbeGetVisualInfo,(Display *dpy,Drawable *screen_specifiers,पूर्णाङ्क *अङ्कः_screens))
SDL_X11_SYM(शून्य,XdbeFreeVisualInfo,(XdbeScreenVisualInfo *visual_info))
SDL_X11_SYM(Xdbe_पृष्ठभागः_बफर_गुणाः*,Xdbe_Get_पृष्ठभागः_बफर_गुणाः,(Display *dpy,Xdbe_पृष्ठभागः_बफर बफर_2))
#यदि_अन्तः

// XInput2 support for multiple mice, tablets, etc.
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2
SDL_X11_MODULE(XINPUT2)
SDL_X11_SYM(XIDeviceInfo*,XIQueryDevice,(Display *a,पूर्णाङ्क b,पूर्णाङ्क *c))
SDL_X11_SYM(शून्य,XIFreeDeviceInfo,(XIDeviceInfo *a))
SDL_X11_SYM(पूर्णाङ्क,XISelectEvents,(Display *a,गवाक्षः_2 b,XIEvent_आवरणम् *c,पूर्णाङ्क d))
SDL_X11_SYM(पूर्णाङ्क,XIGrabTouchBegin,(Display *a,पूर्णाङ्क b,गवाक्षः_2 c,पूर्णाङ्क d,XIEvent_आवरणम् *e,पूर्णाङ्क f,XIGrabModifiers *g))
SDL_X11_SYM(पूर्णाङ्क,XIUngrabTouchBegin, (Display *a,पूर्णाङ्क b,गवाक्षः_2 c, पूर्णाङ्क d,XIGrabModifiers *e))
SDL_X11_SYM(स्थितिः_2,XIQuery_संस्करणम्,(Display *a,पूर्णाङ्क *b,पूर्णाङ्क *c))
SDL_X11_SYM(XIEvent_आवरणम्*,XIGetSelectedEvents,(Display *a,गवाक्षः_2 b,पूर्णाङ्क *c))
SDL_X11_SYM(Bool,XIGetClientPointer,(Display *a,गवाक्षः_2 b,पूर्णाङ्क *c))
SDL_X11_SYM(Bool,XIWarpPointer,(Display *a,पूर्णाङ्क b,गवाक्षः_2 c,गवाक्षः_2 d,द्विगुण e,द्विगुण f,पूर्णाङ्क g,पूर्णाङ्क h,द्विगुण i,द्विगुण j))
SDL_X11_SYM(स्थितिः_2,XIGetProperty,(Display *a,पूर्णाङ्क b,Atom c,दीर्घ d,दीर्घ e,Bool f, Atom g, Atom *h, पूर्णाङ्क *i, अचिह्नित दीर्घ *j, अचिह्नित दीर्घ *k, अचिह्नित वर्ण **l))
#यदि_अन्तः

// XRandR support
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XRANDR
SDL_X11_MODULE(XRANDR)
SDL_X11_SYM(स्थितिः_2,XRRQuery_संस्करणम्,(Display *dpy,पूर्णाङ्क *major_versionp,पूर्णाङ्क *minor_versionp))
SDL_X11_SYM(Bool,XRRQueryExtension,(Display *dpy,पूर्णाङ्क *event_आधारः_return,पूर्णाङ्क *error_आधारः_return))
SDL_X11_SYM(XRRScreenConfiguration *,XRRGetScreenInfo,(Display *dpy,Drawable draw))
SDL_X11_SYM(आकार_ID,XRRConfigCurrentConfiguration,(XRRScreenConfiguration *config,Rotation *rotation))
SDL_X11_SYM(ह्रस्व,XRRConfig_Current_दरः,(XRRScreenConfiguration *config))
SDL_X11_SYM(ह्रस्व *,XRRConfigRates,(XRRScreenConfiguration *config,पूर्णाङ्क आकार_ID_2,पूर्णाङ्क *nrates))
SDL_X11_SYM(XRRScreen_आकार *,XRRConfigSizes,(XRRScreenConfiguration *config,पूर्णाङ्क *nsizes))
SDL_X11_SYM(स्थितिः_2,XRRSet_Screen_Config_And_दरः,(Display *dpy,XRRScreenConfiguration *config,Drawable draw,पूर्णाङ्क आकार_सूचकांक,Rotation rotation,ह्रस्व दरः,Time timestamp))
SDL_X11_SYM(शून्य,XRRFreeScreenConfigInfo,(XRRScreenConfiguration *config))
SDL_X11_SYM(शून्य,XRRSet_Screen_आकार,(Display *dpy, गवाक्षः_2 गवाक्षः,पूर्णाङ्क विस्तारः, पूर्णाङ्क height,पूर्णाङ्क mm_विस्तारः_2, पूर्णाङ्क mmHeight))
SDL_X11_SYM(स्थितिः_2,XRRGet_Screen_आकार_Range,(Display *dpy, गवाक्षः_2 गवाक्षः,पूर्णाङ्क *min_विस्तारः, पूर्णाङ्क *minHeight, पूर्णाङ्क *max_विस्तारः, पूर्णाङ्क *maxHeight))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResources,(Display *dpy, गवाक्षः_2 गवाक्षः))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResourcesCurrent,(Display *dpy, गवाक्षः_2 गवाक्षः))
SDL_X11_SYM(शून्य,XRRFreeScreenResources,(XRRScreenResources *resources))
SDL_X11_SYM(XRROutputInfo *,XRRGetOutputInfo,(Display *dpy, XRRScreenResources *resources, RROutput output))
SDL_X11_SYM(शून्य,XRRFreeOutputInfo,(XRROutputInfo *outputInfo))
SDL_X11_SYM(XRRCrtcInfo *,XRRGetCrtcInfo,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc))
SDL_X11_SYM(शून्य,XRRFreeCrtcInfo,(XRRCrtcInfo *crtcInfo))
SDL_X11_SYM(स्थितिः_2,XRRSetCrtcConfig,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc, Time timestamp, पूर्णाङ्क x, पूर्णाङ्क y, RRMode बहुलकम्, Rotation rotation, RROutput *outputs, पूर्णाङ्क noutputs))
SDL_X11_SYM(Atom*,XRRListOutputProperties,(Display *dpy, RROutput output, पूर्णाङ्क *nprop))
SDL_X11_SYM(XRRPropertyInfo*,XRRQueryOutputProperty,(Display *dpy,RROutput output, Atom property))
SDL_X11_SYM(पूर्णाङ्क,XRRGetOutputProperty,(Display *dpy,RROutput output, Atom property, दीर्घ विस्थापनम्_2, दीर्घ दीर्घता, Bool _delete, Bool pending, Atom req_type, Atom *actual_type, पूर्णाङ्क *actual_format, अचिह्नित दीर्घ *nitems, अचिह्नित दीर्घ *अष्टकानि_after, अचिह्नित वर्ण **prop))
SDL_X11_SYM(RROutput,XRRGetOutputPrimary,(Display *dpy,गवाक्षः_2 गवाक्षः))
SDL_X11_SYM(शून्य,XRRSelect_निवेशः,(Display *dpy, गवाक्षः_2 गवाक्षः, पूर्णाङ्क आवरणम्))
SDL_X11_SYM(स्थितिः_2,XRRGetCrtcTransform,(Display *dpy,RRCrtc crtc,XRRCrtc_Transform_गुणाः **गुणाः))
#यदि_अन्तः

// MIT-SCREEN-SAVER support
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XSCRNSAVER
SDL_X11_MODULE(XSS)
SDL_X11_SYM(Bool,XScreenSaverQueryExtension,(Display *dpy,पूर्णाङ्क *event_आधारः_2,पूर्णाङ्क *error_आधारः_2))
SDL_X11_SYM(स्थितिः_2,XScreen_Saver_Query_संस्करणम्,(Display *dpy,पूर्णाङ्क *major_versionp,पूर्णाङ्क *minor_versionp))
SDL_X11_SYM(शून्य,XScreenSaverSuspend,(Display *dpy,Bool suspend))
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XSHAPE
SDL_X11_MODULE(XSHAPE)
SDL_X11_SYM(शून्य,XShape_Combine_आवरणम्,(Display *dpy,गवाक्षः_2 dest,पूर्णाङ्क dest_विधा,पूर्णाङ्क x_off,पूर्णाङ्क y_off,Pixmap src,पूर्णाङ्क op))
SDL_X11_SYM(शून्य,XShapeCombineRegion,(Display *a,गवाक्षः_2 b,पूर्णाङ्क c,पूर्णाङ्क d,पूर्णाङ्क e,Region f,पूर्णाङ्क g))
#यदि_अन्तः

#अपरिभाषय SDL_X11_MODULE
#अपरिभाषय SDL_X11_SYM

/* *INDENT-ON* */ // clang-format on
