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

#నిర్వచితం_కాకపోతే SDL_X11_MODULE
#నిర్వచించు SDL_X11_MODULE(modname)
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే SDL_X11_SYM
#నిర్వచించు SDL_X11_SYM(rc, fn, params)
#అయితే_ముగింపు

SDL_X11_MODULE(BASEXLIB)
SDL_X11_SYM(XSizeHints*,XAlloc_కొలత_Hints,(శూన్య))
SDL_X11_SYM(XWMHints*,XAllocWMHints,(శూన్య))
SDL_X11_SYM(XClassHint*,XAllocClassHint,(శూన్య))
SDL_X11_SYM(పూర్ణాంకం,XChange_సూచిక_Control,(Display* a,Bool b,Bool c,పూర్ణాంకం d,పూర్ణాంకం e,పూర్ణాంకం f))
SDL_X11_SYM(పూర్ణాంకం,XChangeProperty,(Display* a,కిటికీ_2 b,Atom c,Atom d,పూర్ణాంకం e,పూర్ణాంకం f,_Xconst గుర్తులేని అక్షరం* g,పూర్ణాంకం h))
SDL_X11_SYM(Bool,XCheckIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(పూర్ణాంకం,XClear_కిటికీ,(Display* a,కిటికీ_2 b))
SDL_X11_SYM(పూర్ణాంకం,XCloseDisplay,(Display* a))
SDL_X11_SYM(పూర్ణాంకం,XConvertSelection,(Display* a,Atom b,Atom c,Atom d,కిటికీ_2 e,సమయం_2 f))
SDL_X11_SYM(Pixmap,XCreate_Bitmap_From_దత్తాంశం,(Display *dpy,Drawable d,_Xconst అక్షరం *దత్తాంశం,గుర్తులేని పూర్ణాంకం వెడల్పు,గుర్తులేని పూర్ణాంకం ఎత్తు))
SDL_X11_SYM(Colormap,XCreateColormap,(Display* a,కిటికీ_2 b,Visual* c,పూర్ణాంకం d))
SDL_X11_SYM(Cursor,XCreatePixmapCursor,(Display* a,Pixmap b,Pixmap c,XColor* d,XColor* e,గుర్తులేని పూర్ణాంకం f,గుర్తులేని పూర్ణాంకం g))
SDL_X11_SYM(Cursor,XCreatePixmap,(Display* a,Drawable b,గుర్తులేని పూర్ణాంకం d,గుర్తులేని పూర్ణాంకం e,గుర్తులేని పూర్ణాంకం f))
SDL_X11_SYM(Cursor,XCreateFontCursor,(Display* a,గుర్తులేని పూర్ణాంకం b))
SDL_X11_SYM(XFont_సమితి,XCreate_Font_సమితి,(Display* a, _Xconst అక్షరం* b, అక్షరం*** c, పూర్ణాంకం* d, అక్షరం** e))
SDL_X11_SYM(GC,XCreateGC,(Display* a,Drawable b,గుర్తులేని దీర్ఘ c,XGCValues* d))
SDL_X11_SYM(శూన్య,XSetFont,(Display* a,GC b,Font c))
SDL_X11_SYM(స్థితి_3,XAllocColor,(Display *a, Colormap b, XColor *c))
SDL_X11_SYM(XImage*,XCreateImage,(Display* a,Visual* b,గుర్తులేని పూర్ణాంకం c,పూర్ణాంకం d,పూర్ణాంకం e,అక్షరం* f,గుర్తులేని పూర్ణాంకం g,గుర్తులేని పూర్ణాంకం h,పూర్ణాంకం i,పూర్ణాంకం j))
SDL_X11_SYM(కిటికీ_2,XCreate_కిటికీ,(Display* a,కిటికీ_2 b,పూర్ణాంకం c,పూర్ణాంకం d,గుర్తులేని పూర్ణాంకం e,గుర్తులేని పూర్ణాంకం f,గుర్తులేని పూర్ణాంకం g,పూర్ణాంకం h,గుర్తులేని పూర్ణాంకం i,Visual* j,గుర్తులేని దీర్ఘ k,XSet_కిటికీ_లక్షణాలు* l))
SDL_X11_SYM(శూన్య,XCopyArea,(Display *a, Drawable b, Drawable c, GC d, పూర్ణాంకం e, పూర్ణాంకం f, గుర్తులేని పూర్ణాంకం g, గుర్తులేని పూర్ణాంకం h, పూర్ణాంకం i, పూర్ణాంకం j))
SDL_X11_SYM(పూర్ణాంకం,XDefineCursor,(Display* a,కిటికీ_2 b,Cursor c))
SDL_X11_SYM(పూర్ణాంకం,XDeleteProperty,(Display* a,కిటికీ_2 b,Atom c))
SDL_X11_SYM(పూర్ణాంకం,XDestroy_కిటికీ,(Display* a,కిటికీ_2 b))
SDL_X11_SYM(పూర్ణాంకం,XDisplayKeycodes,(Display* a,పూర్ణాంకం* b,పూర్ణాంకం* c))
SDL_X11_SYM(పూర్ణాంకం,XDrawRectangle,(Display* a,Drawable b,GC c,పూర్ణాంకం d,పూర్ణాంకం e,గుర్తులేని పూర్ణాంకం f,గుర్తులేని పూర్ణాంకం g))
SDL_X11_SYM(పూర్ణాంకం,XFonts_యొక్క_Font_సమితి,(XFont_సమితి a,XFontStruct ***b,అక్షరం ***c))
SDL_X11_SYM(పూర్ణాంకం,XFillArc,(Display* a,Drawable b,GC c,పూర్ణాంకం d,పూర్ణాంకం e,గుర్తులేని పూర్ణాంకం f,గుర్తులేని పూర్ణాంకం g, పూర్ణాంకం h, పూర్ణాంకం i))
SDL_X11_SYM(అక్షరం*,XDisplayName,(_Xconst అక్షరం* a))
SDL_X11_SYM(పూర్ణాంకం,XDrawString,(Display* a,Drawable b,GC c,పూర్ణాంకం d,పూర్ణాంకం e,_Xconst అక్షరం* f,పూర్ణాంకం g))
SDL_X11_SYM(పూర్ణాంకం,XEventsQueued,(Display* a,పూర్ణాంకం b))
SDL_X11_SYM(పూర్ణాంకం,XFillRectangle,(Display* a,Drawable b,GC c,పూర్ణాంకం d,పూర్ణాంకం e,గుర్తులేని పూర్ణాంకం f,గుర్తులేని పూర్ణాంకం g))
SDL_X11_SYM(Bool,XFilterEvent,(XEvent *event,కిటికీ_2 w))
SDL_X11_SYM(పూర్ణాంకం,XFlush,(Display* a))
SDL_X11_SYM(పూర్ణాంకం,XFree,(శూన్య*a))
SDL_X11_SYM(పూర్ణాంకం,XFreeCursor,(Display* a,Cursor b))
SDL_X11_SYM(శూన్య,XFree_Font_సమితి,(Display* a, XFont_సమితి b))
SDL_X11_SYM(పూర్ణాంకం,XFreeGC,(Display* a,GC b))
SDL_X11_SYM(పూర్ణాంకం,XFreeFont,(Display* a, XFontStruct* b))
SDL_X11_SYM(పూర్ణాంకం,XFreeModifiermap,(XModifierKeymap* a))
SDL_X11_SYM(పూర్ణాంకం,XFreePixmap,(Display* a,Pixmap b))
SDL_X11_SYM(పూర్ణాంకం,XFreeColormap,(Display* a,Colormap b))
SDL_X11_SYM(శూన్య,XFreeStringList,(అక్షరం** a))
SDL_X11_SYM(అక్షరం*,XGetAtomName,(Display *a,Atom b))
SDL_X11_SYM(పూర్ణాంకం,XGet_ఆదానం_Focus,(Display *a,కిటికీ_2 *b,పూర్ణాంకం *c))
SDL_X11_SYM(కీలకం_Sym*,XGetKeyboardMapping,(Display *a, కీలకం_సంకేతం_2 b, పూర్ణాంకం c, పూర్ణాంకం *d))
SDL_X11_SYM(పూర్ణాంకం,XGet_Error_Database_పాఠ్యం,(Display* a,_Xconst అక్షరం* b,_Xconst అక్షరం* c,_Xconst అక్షరం* d,అక్షరం* e,పూర్ణాంకం f))
SDL_X11_SYM(XModifierKeymap*,XGetModifierMapping,(Display* a))
SDL_X11_SYM(పూర్ణాంకం,XGet_సూచిక_Control,(Display* a,పూర్ణాంకం* b,పూర్ణాంకం* c,పూర్ణాంకం* d))
SDL_X11_SYM(కిటికీ_2,XGetSelectionOwner,(Display* a,Atom b))
SDL_X11_SYM(XVisualInfo*,XGetVisualInfo,(Display* a,దీర్ఘ b,XVisualInfo* c,పూర్ణాంకం* d))
SDL_X11_SYM(స్థితి_3,XGet_కిటికీ_లక్షణాలు,(Display* a,కిటికీ_2 b,XWindow_లక్షణాలు* c))
SDL_X11_SYM(పూర్ణాంకం,XGet_కిటికీ_Property,(Display* a,కిటికీ_2 b,Atom c,దీర్ఘ d,దీర్ఘ e,Bool f,Atom g,Atom* h,పూర్ణాంకం* i,గుర్తులేని దీర్ఘ* j,గుర్తులేని దీర్ఘ *k,గుర్తులేని అక్షరం **l))
SDL_X11_SYM(XWMHints*,XGetWMHints,(Display* a,కిటికీ_2 b))
SDL_X11_SYM(స్థితి_3,XGetWMNormalHints,(Display *a,కిటికీ_2 b, XSizeHints *c, దీర్ఘ *d))
SDL_X11_SYM(పూర్ణాంకం,XIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(పూర్ణాంకం,XGrabKeyboard,(Display* a,కిటికీ_2 b,Bool c,పూర్ణాంకం d,పూర్ణాంకం e,సమయం_2 f))
SDL_X11_SYM(పూర్ణాంకం,XGrab_సూచిక,(Display* a,కిటికీ_2 b,Bool c,గుర్తులేని పూర్ణాంకం d,పూర్ణాంకం e,పూర్ణాంకం f,కిటికీ_2 g,Cursor h,సమయం_2 i))
SDL_X11_SYM(పూర్ణాంకం,XGrabServer,(Display* a))
SDL_X11_SYM(స్థితి_3,XIconify_కిటికీ,(Display* a,కిటికీ_2 b,పూర్ణాంకం c))
SDL_X11_SYM(కీలకం_సంకేతం_2,XKeysym_గమ్యం_Keycode,(Display* a,కీలకం_Sym b))
SDL_X11_SYM(అక్షరం*,XKeysym_గమ్యం_String,(కీలకం_Sym a))
SDL_X11_SYM(పూర్ణాంకం,XInstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(Atom,XInternAtom,(Display* a,_Xconst అక్షరం* b,Bool c))
SDL_X11_SYM(XPixmap_Format_విలువలు*,XListPixmapFormats,(Display* a,పూర్ణాంకం* b))
SDL_X11_SYM(XFontStruct*,XLoadQueryFont,(Display* a,_Xconst అక్షరం* b))
SDL_X11_SYM(కీలకం_Sym,XLookupKeysym,(XKeyEvent* a,పూర్ణాంకం b))
SDL_X11_SYM(పూర్ణాంకం,XLookupString,(XKeyEvent* a,అక్షరం* b,పూర్ణాంకం c,కీలకం_Sym* d,XCompose_స్థితి* e))
SDL_X11_SYM(పూర్ణాంకం,XMapRaised,(Display* a,కిటికీ_2 b))
SDL_X11_SYM(స్థితి_3,XMatchVisualInfo,(Display* a,పూర్ణాంకం b,పూర్ణాంకం c,పూర్ణాంకం d,XVisualInfo* e))
SDL_X11_SYM(పూర్ణాంకం,XMissingExtension,(Display* a,_Xconst అక్షరం* b))
SDL_X11_SYM(పూర్ణాంకం,XMove_కిటికీ,(Display* a,కిటికీ_2 b,పూర్ణాంకం c,పూర్ణాంకం d))
SDL_X11_SYM(Display*,XOpenDisplay,(_Xconst అక్షరం* a))
SDL_X11_SYM(స్థితి_3,XInit_దారాలు,(శూన్య))
SDL_X11_SYM(పూర్ణాంకం,XPeekEvent,(Display* a,XEvent* b))
SDL_X11_SYM(పూర్ణాంకం,XPending,(Display* a))
SDL_X11_SYM(XImage*,XGetImage,(Display* a,Drawable b,పూర్ణాంకం c, పూర్ణాంకం d,గుర్తులేని పూర్ణాంకం e,గుర్తులేని పూర్ణాంకం f,గుర్తులేని దీర్ఘ g,పూర్ణాంకం h))
SDL_X11_SYM(పూర్ణాంకం,XPutImage,(Display* a,Drawable b,GC c,XImage* d,పూర్ణాంకం e,పూర్ణాంకం f,పూర్ణాంకం g,పూర్ణాంకం h,గుర్తులేని పూర్ణాంకం i,గుర్తులేని పూర్ణాంకం j))
SDL_X11_SYM(పూర్ణాంకం,XQueryKeymap,(Display* a,అక్షరం b[32]))
SDL_X11_SYM(Bool,XQuery_సూచిక,(Display* a,కిటికీ_2 b,కిటికీ_2* c,కిటికీ_2* d,పూర్ణాంకం* e,పూర్ణాంకం* f,పూర్ణాంకం* g,పూర్ణాంకం* h,గుర్తులేని పూర్ణాంకం* i))
SDL_X11_SYM(పూర్ణాంకం,XRaise_కిటికీ,(Display* a,కిటికీ_2 b))
SDL_X11_SYM(పూర్ణాంకం,XReparent_కిటికీ,(Display* a,కిటికీ_2 b,కిటికీ_2 c,పూర్ణాంకం d,పూర్ణాంకం e))
SDL_X11_SYM(పూర్ణాంకం,XResetScreenSaver,(Display* a))
SDL_X11_SYM(పూర్ణాంకం,XResize_కిటికీ,(Display* a,కిటికీ_2 b,గుర్తులేని పూర్ణాంకం c,గుర్తులేని పూర్ణాంకం d))
SDL_X11_SYM(పూర్ణాంకం,XScreen_సంఖ్య_యొక్క_Screen,(Screen* a))
SDL_X11_SYM(పూర్ణాంకం,XSelect_ఆదానం,(Display* a,కిటికీ_2 b,దీర్ఘ c))
SDL_X11_SYM(స్థితి_3,XSendEvent,(Display* a,కిటికీ_2 b,Bool c,దీర్ఘ d,XEvent* e))
SDL_X11_SYM(XErrorHandler,XSetErrorHandler,(XErrorHandler a))
SDL_X11_SYM(పూర్ణాంకం,XSetForeground,(Display* a,GC b,గుర్తులేని దీర్ఘ c))
SDL_X11_SYM(XIOErrorHandler,XSetIOErrorHandler,(XIOErrorHandler a))
SDL_X11_SYM(పూర్ణాంకం,XSet_ఆదానం_Focus,(Display *a,కిటికీ_2 b,పూర్ణాంకం c,సమయం_2 d))
SDL_X11_SYM(పూర్ణాంకం,XSetSelectionOwner,(Display* a,Atom b,కిటికీ_2 c,సమయం_2 d))
SDL_X11_SYM(పూర్ణాంకం,XSetTransientForHint,(Display* a,కిటికీ_2 b,కిటికీ_2 c))
SDL_X11_SYM(శూన్య,XSet_పాఠ్యం_Property,(Display* a,కిటికీ_2 b,XTextProperty* c,Atom d))
SDL_X11_SYM(పూర్ణాంకం,XSet_కిటికీ_Background,(Display* a,కిటికీ_2 b,గుర్తులేని దీర్ఘ c))
SDL_X11_SYM(శూన్య,XSetWMHints,(Display* a,కిటికీ_2 b,XWMHints* c))
SDL_X11_SYM(శూన్య,XSetWMNormalHints,(Display* a,కిటికీ_2 b,XSizeHints* c))
SDL_X11_SYM(శూన్య,XSetWMProperties,(Display* a,కిటికీ_2 b,XTextProperty* c,XTextProperty* d,అక్షరం** e,పూర్ణాంకం f,XSizeHints* g,XWMHints* h,XClassHint* i))
SDL_X11_SYM(స్థితి_3,XSetWMProtocols,(Display* a,కిటికీ_2 b,Atom* c,పూర్ణాంకం d))
SDL_X11_SYM(పూర్ణాంకం,XStoreColors,(Display* a,Colormap b,XColor* c,పూర్ణాంకం d))
SDL_X11_SYM(పూర్ణాంకం,XStoreName,(Display* a,కిటికీ_2 b,_Xconst అక్షరం* c))
SDL_X11_SYM(స్థితి_3,XString_List_గమ్యం_పాఠ్యం_Property,(అక్షరం** a,పూర్ణాంకం b,XTextProperty* c))
SDL_X11_SYM(పూర్ణాంకం,XSync,(Display* a,Bool b))
SDL_X11_SYM(పూర్ణాంకం,XTextExtents,(XFontStruct* a,_Xconst అక్షరం* b,పూర్ణాంకం c,పూర్ణాంకం* d,పూర్ణాంకం* e,పూర్ణాంకం* f,XCharStruct* g))
SDL_X11_SYM(Bool,XTranslateCoordinates,(Display *a,కిటికీ_2 b,కిటికీ_2 c,పూర్ణాంకం d,పూర్ణాంకం e,పూర్ణాంకం* f,పూర్ణాంకం* g,కిటికీ_2* h))
SDL_X11_SYM(పూర్ణాంకం,XUndefineCursor,(Display* a,కిటికీ_2 b))
SDL_X11_SYM(పూర్ణాంకం,XUngrabKeyboard,(Display* a,సమయం_2 b))
SDL_X11_SYM(పూర్ణాంకం,XUngrab_సూచిక,(Display* a,సమయం_2 b))
SDL_X11_SYM(పూర్ణాంకం,XUngrabServer,(Display* a))
SDL_X11_SYM(పూర్ణాంకం,XUninstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(పూర్ణాంకం,XUnloadFont,(Display* a,Font b))
SDL_X11_SYM(పూర్ణాంకం,XWarp_సూచిక,(Display* a,కిటికీ_2 b,కిటికీ_2 c,పూర్ణాంకం d,పూర్ణాంకం e,గుర్తులేని పూర్ణాంకం f,గుర్తులేని పూర్ణాంకం g,పూర్ణాంకం h,పూర్ణాంకం i))
SDL_X11_SYM(పూర్ణాంకం,XWindowEvent,(Display* a,కిటికీ_2 b,దీర్ఘ c,XEvent* d))
SDL_X11_SYM(స్థితి_3,XWithdraw_కిటికీ,(Display* a,కిటికీ_2 b,పూర్ణాంకం c))
SDL_X11_SYM(VisualID,XVisualIDFromVisual,(Visual* a))
SDL_X11_SYM(అక్షరం*,XGetDefault,(Display* a,_Xconst అక్షరం* b, _Xconst అక్షరం* c))
SDL_X11_SYM(Bool,XQueryExtension,(Display* a,_Xconst అక్షరం* b,పూర్ణాంకం* c,పూర్ణాంకం* d,పూర్ణాంకం* e))
SDL_X11_SYM(అక్షరం *,XDisplayString,(Display* a))
SDL_X11_SYM(పూర్ణాంకం,XGet_Error_పాఠ్యం,(Display* a,పూర్ణాంకం b,అక్షరం* c,పూర్ణాంకం d))
SDL_X11_SYM(శూన్య,XEat_దత్తాంశం,(Display* a,గుర్తులేని దీర్ఘ b))
SDL_X11_SYM(శూన్య,_XFlush,(Display* a))
SDL_X11_SYM(శూన్య,_XFlushGCCache,(Display* a,GC b))
SDL_X11_SYM(పూర్ణాంకం,_XRead,(Display* a,అక్షరం* b,దీర్ఘ c))
SDL_X11_SYM(శూన్య,_XReadPad,(Display* a,అక్షరం* b,దీర్ఘ c))
SDL_X11_SYM(శూన్య,_XSend,(Display* a,_Xconst అక్షరం* b,దీర్ఘ c))
SDL_X11_SYM(స్థితి_3,_XReply,(Display* a,x_జవాబు* b,పూర్ణాంకం c,Bool d))
SDL_X11_SYM(గుర్తులేని దీర్ఘ,XSet_చివరి_Request_Read,(Display* a,x_Generic_జవాబు* b))
SDL_X11_SYM(SDL_X11_XSynchronizeRetType,XSynchronize,(Display* a,Bool b))
SDL_X11_SYM(SDL_X11_XESet_Wire_గమ్యం_Event_Ret_Type,XESet_Wire_గమ్యం_Event,(Display* a,పూర్ణాంకం b,SDL_X11_XESet_Wire_గమ్యం_Event_Ret_Type c))
SDL_X11_SYM(SDL_X11_XESet_Event_గమ్యం_Wire_Ret_Type,XESet_Event_గమ్యం_Wire,(Display* a,పూర్ణాంకం b,SDL_X11_XESet_Event_గమ్యం_Wire_Ret_Type c))
SDL_X11_SYM(శూన్య,XRefreshKeyboardMapping,(XMappingEvent *a))
SDL_X11_SYM(పూర్ణాంకం,XQuery_వృక్షం,(Display* a,కిటికీ_2 b,కిటికీ_2* c,కిటికీ_2* d,కిటికీ_2** e,గుర్తులేని పూర్ణాంకం* f))
SDL_X11_SYM(Bool,XSupportsLocale,(శూన్య))
SDL_X11_SYM(స్థితి_3,Xmb_పాఠ్యం_List_గమ్యం_పాఠ్యం_Property,(Display* a,అక్షరం** b,పూర్ణాంకం c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(Region,XCreateRegion,(శూన్య))
SDL_X11_SYM(పూర్ణాంకం,XUnionRectWithRegion,(XRectangle *a, Region b, Region c))
SDL_X11_SYM(శూన్య,XDestroyRegion,(Region))
SDL_X11_SYM(శూన్య,XrmInitialize,(శూన్య))
SDL_X11_SYM(అక్షరం*,XResourceManagerString,(Display *display))
SDL_X11_SYM(XrmDatabase,XrmGetStringDatabase,(అక్షరం *దత్తాంశం))
SDL_X11_SYM(శూన్య,XrmDestroyDatabase,(XrmDatabase db))
SDL_X11_SYM(Bool,XrmGetResource,(XrmDatabase db, అక్షరం* str_name, అక్షరం* str_class, అక్షరం **str_type_return, Xrm_విలువ *))
SDL_X11_SYM(పూర్ణాంకం,XGet_సూచిక_Mapping,(Display *a, గుర్తులేని అక్షరం *b, గుర్తులేని పూర్ణాంకం c))

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XFIXES
SDL_X11_MODULE(XFIXES)
SDL_X11_SYM(సూచిక_Barrier, XFixes_Create_సూచిక_Barrier, (Display* a, కిటికీ_2 b, పూర్ణాంకం c, పూర్ణాంకం d, పూర్ణాంకం e, పూర్ణాంకం f, పూర్ణాంకం g, పూర్ణాంకం h, పూర్ణాంకం *i))
SDL_X11_SYM(శూన్య, XFixes_Destroy_సూచిక_Barrier, (Display* a, సూచిక_Barrier b))
SDL_X11_SYM(పూర్ణాంకం, XIBarrier_Release_సూచిక,(Display* a,  పూర్ణాంకం b, సూచిక_Barrier c, BarrierEventID d)) // this is actually Xinput2
SDL_X11_SYM(స్థితి_3, XFixes_Query_సంస్కరణ,(Display* a, పూర్ణాంకం* b, పూర్ణాంకం* c))
SDL_X11_SYM(స్థితి_3, XFixes_Select_Selection_ఆదానం, (Display* a, కిటికీ_2 b, Atom c, గుర్తులేని దీర్ఘ d))
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XSYNC
SDL_X11_MODULE(XSYNC)
SDL_X11_SYM(స్థితి_3, XSyncQueryExtension, (Display* a, పూర్ణాంకం* b, పూర్ణాంకం* c))
SDL_X11_SYM(స్థితి_3, XSyncInitialize, (Display* a, పూర్ణాంకం* b, పూర్ణాంకం* c))
SDL_X11_SYM(XSyncCounter, XSyncCreateCounter, (Display* a, XSync_విలువ b))
SDL_X11_SYM(స్థితి_3, XSyncDestroyCounter, (Display* a, XSyncCounter b))
SDL_X11_SYM(స్థితి_3, XSync_సమితి_Counter, (Display* a, XSyncCounter b, XSync_విలువ c))
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XTEST
SDL_X11_MODULE(XTEST)
SDL_X11_SYM(స్థితి_3, XTestQueryExtension, (Display* a, పూర్ణాంకం* b, పూర్ణాంకం* c))
SDL_X11_SYM(పూర్ణాంకం, XTestFakeMotionEvent, (Display* a, పూర్ణాంకం b, పూర్ణాంకం c, పూర్ణాంకం d, గుర్తులేని దీర్ఘ e))
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
SDL_X11_SYM(Bool,XGet_Event_దత్తాంశం,(Display* a,XGenericEventCookie* b))
SDL_X11_SYM(శూన్య,XFree_Event_దత్తాంశం,(Display* a,XGenericEventCookie* b))
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
SDL_X11_SYM(Bool,XkbQueryExtension,(Display* a,పూర్ణాంకం * b,పూర్ణాంకం * c,పూర్ణాంకం * d,పూర్ణాంకం * e, పూర్ణాంకం *f))
SDL_X11_SYM(కీలకం_Sym,Xkb_Keycode_గమ్యం_Keysym,(Display* a, కీలకం_సంకేతం_2 b, గుర్తులేని పూర్ణాంకం c, గుర్తులేని పూర్ణాంకం d))
SDL_X11_SYM(Bool,XkbSelectEvents,(Display* a, గుర్తులేని పూర్ణాంకం b, గుర్తులేని పూర్ణాంకం c, గుర్తులేని దీర్ఘ d))
SDL_X11_SYM(Bool,XkbSelectEventDetails,(Display* a, గుర్తులేని పూర్ణాంకం b, గుర్తులేని పూర్ణాంకం c, గుర్తులేని దీర్ఘ d, గుర్తులేని దీర్ఘ e))
SDL_X11_SYM(స్థితి_3,Xkb_Get_పేర్లు,(Display *a, గుర్తులేని పూర్ణాంకం b, XkbDescPtr c))
SDL_X11_SYM(స్థితి_3,XkbGetState,(Display* a,గుర్తులేని పూర్ణాంకం b,XkbStatePtr c))
SDL_X11_SYM(స్థితి_3,XkbGetUpdatedMap,(Display* a,గుర్తులేని పూర్ణాంకం b,XkbDescPtr c))
SDL_X11_SYM(XkbDescPtr,XkbGetMap,(Display* a,గుర్తులేని పూర్ణాంకం b,గుర్తులేని పూర్ణాంకం c))
SDL_X11_SYM(శూన్య,XkbFreeClientMap,(XkbDescPtr a,గుర్తులేని పూర్ణాంకం b, Bool c))
SDL_X11_SYM(శూన్య,XkbFreeKeyboard,(XkbDescPtr a,గుర్తులేని పూర్ణాంకం b, Bool c))
SDL_X11_SYM(స్థితి_3,XkbRefreshKeyboardMapping,(XkbMapNotifyEvent *a))
SDL_X11_SYM(Bool,Xkb_సమితి_Detectable_Auto_Repeat,(Display* a, Bool b, Bool* c))
#అయితే_ముగింపు

#నిర్వచితమైతే X_HAVE_UTF8_STRING
SDL_X11_MODULE(UTF8)
SDL_X11_SYM(పూర్ణాంకం,Xutf8_పాఠ్యం_List_గమ్యం_పాఠ్యం_Property,(Display* a,అక్షరం** b,పూర్ణాంకం c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(పూర్ణాంకం,Xutf8LookupString,(XIC a,XKeyPressedEvent* b,అక్షరం* c,పూర్ణాంకం d,కీలకం_Sym* e,స్థితి_3* f))
SDL_X11_SYM(XIC,XCreateIC,(XIM,...))
SDL_X11_SYM(శూన్య,XDestroyIC,(XIC a))
SDL_X11_SYM(అక్షరం*,XGetICValues,(XIC,...))
SDL_X11_SYM(అక్షరం*,XSetICValues,(XIC,...))
SDL_X11_SYM(XVaNestedList,XVaCreateNestedList,(పూర్ణాంకం, ...))
SDL_X11_SYM(శూన్య,XSetICFocus,(XIC a))
SDL_X11_SYM(శూన్య,XUnsetICFocus,(XIC a))
SDL_X11_SYM(XIM,XOpenIM,(Display* a,నిర్మాణం Xrm_Hash_పాత్ర_Rec* b,అక్షరం* c,అక్షరం* d))
SDL_X11_SYM(స్థితి_3,XCloseIM,(XIM a))
SDL_X11_SYM(అక్షరం*, XSetIMValues,(XIM,...))
SDL_X11_SYM(Bool,XRegisterIMInstantiateCallback,(Display*,నిర్మాణం Xrm_Hash_పాత్ర_Rec*,అక్షరం*,అక్షరం*,XIDProc,XPointer))
SDL_X11_SYM(Bool,XUnregisterIMInstantiateCallback,(Display*,నిర్మాణం Xrm_Hash_పాత్ర_Rec*,అక్షరం*,అక్షరం*,XIDProc,XPointer))
SDL_X11_SYM(శూన్య,Xutf8DrawString,(Display *a, Drawable b, XFont_సమితి c, GC d, పూర్ణాంకం e, పూర్ణాంకం f, _Xconst అక్షరం *g, పూర్ణాంకం h))
SDL_X11_SYM(పూర్ణాంకం,Xutf8_పాఠ్యం_Extents,(XFont_సమితి a, _Xconst అక్షరం* b, పూర్ణాంకం c, XRectangle* d, XRectangle* e))
SDL_X11_SYM(అక్షరం*,XSetLocaleModifiers,(స్థిరరాశి అక్షరం *a))
SDL_X11_SYM(అక్షరం*,Xutf8ResetIC,(XIC a))
SDL_X11_SYM(XFont_సమితి_Extents*,XExtents_యొక్క_Font_సమితి,(XFont_సమితి a))
SDL_X11_SYM(Bool,XContextDependentDrawing,(XFont_సమితి a))
#అయితే_ముగింపు


#నిర్వచితం_కాకపోతే NO_SHARED_జ్ఞాపకం
SDL_X11_MODULE(SHM)
SDL_X11_SYM(స్థితి_3,XShmAttach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(స్థితి_3,XShmDetach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(స్థితి_3,XShmPutImage,(Display* a,Drawable b,GC c,XImage* d,పూర్ణాంకం e,పూర్ణాంకం f,పూర్ణాంకం g,పూర్ణాంకం h,గుర్తులేని పూర్ణాంకం i,గుర్తులేని పూర్ణాంకం j,Bool k))
SDL_X11_SYM(స్థితి_3,XShmGetImage,(Display* a,Drawable b,XImage *c,పూర్ణాంకం d, పూర్ణాంకం e, గుర్తులేని దీర్ఘ f))
SDL_X11_SYM(XImage*,XShmCreateImage,(Display* a,Visual* b,గుర్తులేని పూర్ణాంకం c,పూర్ణాంకం d,అక్షరం* e,XShmSegmentInfo* f,గుర్తులేని పూర్ణాంకం g,గుర్తులేని పూర్ణాంకం h))
SDL_X11_SYM(Pixmap,XShmCreatePixmap,(Display *a,Drawable b,అక్షరం* c,XShmSegmentInfo* d, గుర్తులేని పూర్ణాంకం e, గుర్తులేని పూర్ణాంకం f, గుర్తులేని పూర్ణాంకం g))
SDL_X11_SYM(Bool,XShmQueryExtension,(Display* a))
SDL_X11_SYM(స్థితి_3,XShm_Query_సంస్కరణ,(Display* a, పూర్ణాంకం *b, పూర్ణాంకం *c, Bool *d))
SDL_X11_SYM(పూర్ణాంకం,XShmPixmapFormat,(Display* a))
#అయితే_ముగింపు

/*
 * Not required...these only exist in code in headers on some 64-bit platforms,
 *  and are removed via macros elsewhere, so it's safe for them to be missing.
 */
#నిర్వచితమైతే LONG64
SDL_X11_MODULE(IO_32_బిట్టు)
SDL_X11_SYM(పూర్ణాంకం,_XData32,(Display *dpy,నమోదు _Xconst దీర్ఘ *దత్తాంశం,గుర్తులేని len))
SDL_X11_SYM(శూన్య,_XRead32,(Display *dpy,నమోదు దీర్ఘ *దత్తాంశం,దీర్ఘ len))
#అయితే_ముగింపు

/*
 * These only show up on some variants of Unix.
 */
#నిర్వచితమైతే SDL_PLATFORM_OSF
SDL_X11_MODULE(OSF_నమోదు_POINTS)
SDL_X11_SYM(శూన్య,Smt_బఫరు_అధికప్రవాహం,(Display *dpy,నమోదు smtDisplayPtr p))
SDL_X11_SYM(శూన్య,_SmtIpError,(Display *dpy,నమోదు smtDisplayPtr p,పూర్ణాంకం i))
SDL_X11_SYM(పూర్ణాంకం,ip_Allocate_దత్తాంశం,(ChannelPtr a,IPCard b,IPDataPtr * c))
SDL_X11_SYM(పూర్ణాంకం,ip_Unallocate_And_Send_దత్తాంశం,(ChannelPtr a,IPCard b))
#అయితే_ముగింపు

// XCursor support
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XCURSOR
SDL_X11_MODULE(XCURSOR)
SDL_X11_SYM(XcursorImage*,XcursorImageCreate,(పూర్ణాంకం a,పూర్ణాంకం b))
SDL_X11_SYM(XcursorImages*,XcursorImagesCreate,(పూర్ణాంకం a))
SDL_X11_SYM(శూన్య,XcursorImageDestroy,(XcursorImage *a))
SDL_X11_SYM(శూన్య,XcursorImagesDestroy,(XcursorImages *a))
SDL_X11_SYM(Cursor,Xcursor_Image_ఎక్కించు_Cursor,(Display *a,స్థిరరాశి XcursorImage *b))
SDL_X11_SYM(Cursor,Xcursor_Images_ఎక్కించు_Cursor,(Display *a,స్థిరరాశి XcursorImages *b))
SDL_X11_SYM(Cursor,Xcursor_Library_ఎక్కించు_Cursor,(Display *a, స్థిరరాశి అక్షరం *b))
#అయితే_ముగింపు

// Xdbe support
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XDBE
SDL_X11_MODULE(XDBE)
SDL_X11_SYM(స్థితి_3,XdbeQueryExtension,(Display *dpy,పూర్ణాంకం *major_సంస్కరణ_return,పూర్ణాంకం *minor_సంస్కరణ_return))
SDL_X11_SYM(Xdbe_వెనుక_బఫరు,Xdbe_Allocate_వెనుక_బఫరు_Name,(Display *dpy,కిటికీ_2 కిటికీ,Xdbe_మార్పిడి_Action మార్పిడి_action))
SDL_X11_SYM(స్థితి_3,Xdbe_Deallocate_వెనుక_బఫరు_Name,(Display *dpy,Xdbe_వెనుక_బఫరు బఫరు_2))
SDL_X11_SYM(స్థితి_3,Xdbe_మార్పిడి_Buffers,(Display *dpy,Xdbe_మార్పిడి_Info *మార్పిడి_info,పూర్ణాంకం అంకె_windows))
SDL_X11_SYM(స్థితి_3,XdbeBeginIdiom,(Display *dpy))
SDL_X11_SYM(స్థితి_3,Xdbe_చివర_Idiom,(Display *dpy))
SDL_X11_SYM(XdbeScreenVisualInfo*,XdbeGetVisualInfo,(Display *dpy,Drawable *screen_specifiers,పూర్ణాంకం *అంకె_screens))
SDL_X11_SYM(శూన్య,XdbeFreeVisualInfo,(XdbeScreenVisualInfo *visual_info))
SDL_X11_SYM(Xdbe_వెనుక_బఫరు_లక్షణాలు*,Xdbe_Get_వెనుక_బఫరు_లక్షణాలు,(Display *dpy,Xdbe_వెనుక_బఫరు బఫరు_2))
#అయితే_ముగింపు

// XInput2 support for multiple mice, tablets, etc.
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2
SDL_X11_MODULE(XINPUT2)
SDL_X11_SYM(XIDeviceInfo*,XIQueryDevice,(Display *a,పూర్ణాంకం b,పూర్ణాంకం *c))
SDL_X11_SYM(శూన్య,XIFreeDeviceInfo,(XIDeviceInfo *a))
SDL_X11_SYM(పూర్ణాంకం,XISelectEvents,(Display *a,కిటికీ_2 b,XIEvent_ముసుగు *c,పూర్ణాంకం d))
SDL_X11_SYM(పూర్ణాంకం,XIGrabTouchBegin,(Display *a,పూర్ణాంకం b,కిటికీ_2 c,పూర్ణాంకం d,XIEvent_ముసుగు *e,పూర్ణాంకం f,XIGrabModifiers *g))
SDL_X11_SYM(పూర్ణాంకం,XIUngrabTouchBegin, (Display *a,పూర్ణాంకం b,కిటికీ_2 c, పూర్ణాంకం d,XIGrabModifiers *e))
SDL_X11_SYM(స్థితి_3,XIQuery_సంస్కరణ,(Display *a,పూర్ణాంకం *b,పూర్ణాంకం *c))
SDL_X11_SYM(XIEvent_ముసుగు*,XIGetSelectedEvents,(Display *a,కిటికీ_2 b,పూర్ణాంకం *c))
SDL_X11_SYM(Bool,XIGet_Client_సూచిక,(Display *a,కిటికీ_2 b,పూర్ణాంకం *c))
SDL_X11_SYM(Bool,XIWarp_సూచిక,(Display *a,పూర్ణాంకం b,కిటికీ_2 c,కిటికీ_2 d,ద్విగుణ e,ద్విగుణ f,పూర్ణాంకం g,పూర్ణాంకం h,ద్విగుణ i,ద్విగుణ j))
SDL_X11_SYM(స్థితి_3,XIGetProperty,(Display *a,పూర్ణాంకం b,Atom c,దీర్ఘ d,దీర్ఘ e,Bool f, Atom g, Atom *h, పూర్ణాంకం *i, గుర్తులేని దీర్ఘ *j, గుర్తులేని దీర్ఘ *k, గుర్తులేని అక్షరం **l))
#అయితే_ముగింపు

// XRandR support
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XRANDR
SDL_X11_MODULE(XRANDR)
SDL_X11_SYM(స్థితి_3,XRRQuery_సంస్కరణ,(Display *dpy,పూర్ణాంకం *major_versionp,పూర్ణాంకం *minor_versionp))
SDL_X11_SYM(Bool,XRRQueryExtension,(Display *dpy,పూర్ణాంకం *event_పునాది_return,పూర్ణాంకం *error_పునాది_return))
SDL_X11_SYM(XRRScreenConfiguration *,XRRGetScreenInfo,(Display *dpy,Drawable draw))
SDL_X11_SYM(కొలత_ID,XRRConfigCurrentConfiguration,(XRRScreenConfiguration *config,Rotation *rotation))
SDL_X11_SYM(పొట్టి,XRRConfig_Current_రేటు,(XRRScreenConfiguration *config))
SDL_X11_SYM(పొట్టి *,XRRConfigRates,(XRRScreenConfiguration *config,పూర్ణాంకం కొలత_ID_2,పూర్ణాంకం *nrates))
SDL_X11_SYM(XRRScreen_కొలత *,XRRConfigSizes,(XRRScreenConfiguration *config,పూర్ణాంకం *nsizes))
SDL_X11_SYM(స్థితి_3,XRRSet_Screen_Config_And_రేటు,(Display *dpy,XRRScreenConfiguration *config,Drawable draw,పూర్ణాంకం కొలత_సూచీ,Rotation rotation,పొట్టి రేటు,సమయం_2 timestamp))
SDL_X11_SYM(శూన్య,XRRFreeScreenConfigInfo,(XRRScreenConfiguration *config))
SDL_X11_SYM(శూన్య,XRRSet_Screen_కొలత,(Display *dpy, కిటికీ_2 కిటికీ,పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు,పూర్ణాంకం mm_వెడల్పు_2, పూర్ణాంకం mm_ఎత్తు_2))
SDL_X11_SYM(స్థితి_3,XRRGet_Screen_కొలత_Range,(Display *dpy, కిటికీ_2 కిటికీ,పూర్ణాంకం *min_వెడల్పు, పూర్ణాంకం *min_ఎత్తు, పూర్ణాంకం *max_వెడల్పు, పూర్ణాంకం *max_ఎత్తు))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResources,(Display *dpy, కిటికీ_2 కిటికీ))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResourcesCurrent,(Display *dpy, కిటికీ_2 కిటికీ))
SDL_X11_SYM(శూన్య,XRRFreeScreenResources,(XRRScreenResources *resources))
SDL_X11_SYM(XRROutputInfo *,XRRGetOutputInfo,(Display *dpy, XRRScreenResources *resources, RROutput output))
SDL_X11_SYM(శూన్య,XRRFreeOutputInfo,(XRROutputInfo *outputInfo))
SDL_X11_SYM(XRRCrtcInfo *,XRRGetCrtcInfo,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc))
SDL_X11_SYM(శూన్య,XRRFreeCrtcInfo,(XRRCrtcInfo *crtcInfo))
SDL_X11_SYM(స్థితి_3,XRRSetCrtcConfig,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc, సమయం_2 timestamp, పూర్ణాంకం x, పూర్ణాంకం y, RRMode బహుళకం, Rotation rotation, RROutput *outputs, పూర్ణాంకం noutputs))
SDL_X11_SYM(Atom*,XRRListOutputProperties,(Display *dpy, RROutput output, పూర్ణాంకం *nprop))
SDL_X11_SYM(XRRPropertyInfo*,XRRQueryOutputProperty,(Display *dpy,RROutput output, Atom property))
SDL_X11_SYM(పూర్ణాంకం,XRRGetOutputProperty,(Display *dpy,RROutput output, Atom property, దీర్ఘ స్థానభ్రంశం_2, దీర్ఘ నిడివి, Bool _delete, Bool pending, Atom req_type, Atom *actual_type, పూర్ణాంకం *actual_format, గుర్తులేని దీర్ఘ *nitems, గుర్తులేని దీర్ఘ *బైట్లు_after, గుర్తులేని అక్షరం **prop))
SDL_X11_SYM(RROutput,XRRGetOutputPrimary,(Display *dpy,కిటికీ_2 కిటికీ))
SDL_X11_SYM(శూన్య,XRRSelect_ఆదానం,(Display *dpy, కిటికీ_2 కిటికీ, పూర్ణాంకం ముసుగు))
SDL_X11_SYM(స్థితి_3,XRRGetCrtcTransform,(Display *dpy,RRCrtc crtc,XRRCrtc_Transform_లక్షణాలు **లక్షణాలు))
#అయితే_ముగింపు

// MIT-SCREEN-SAVER support
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XSCRNSAVER
SDL_X11_MODULE(XSS)
SDL_X11_SYM(Bool,XScreenSaverQueryExtension,(Display *dpy,పూర్ణాంకం *event_పునాది_2,పూర్ణాంకం *error_పునాది_2))
SDL_X11_SYM(స్థితి_3,XScreen_Saver_Query_సంస్కరణ,(Display *dpy,పూర్ణాంకం *major_versionp,పూర్ణాంకం *minor_versionp))
SDL_X11_SYM(శూన్య,XScreenSaverSuspend,(Display *dpy,Bool suspend))
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XSHAPE
SDL_X11_MODULE(XSHAPE)
SDL_X11_SYM(శూన్య,XShape_Combine_ముసుగు,(Display *dpy,కిటికీ_2 dest,పూర్ణాంకం dest_రకం,పూర్ణాంకం x_off,పూర్ణాంకం y_off,Pixmap src,పూర్ణాంకం op))
SDL_X11_SYM(శూన్య,XShapeCombineRegion,(Display *a,కిటికీ_2 b,పూర్ణాంకం c,పూర్ణాంకం d,పూర్ణాంకం e,Region f,పూర్ణాంకం g))
#అయితే_ముగింపు

#నిర్వచనం_రద్దు SDL_X11_MODULE
#నిర్వచనం_రద్దు SDL_X11_SYM

/* *INDENT-ON* */ // clang-format on
