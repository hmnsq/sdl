/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>
  Copyright (C) 2018-2019 EXL <exlmotodev@gmail.com>

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

#ضمن "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU


// For application signature.
#ضمن "../../core/haiku/SDL_BeApp.h"

#ضمن <Alert.h>
#ضمن <Application.h>
#ضمن <Button.h>
#ضمن <Font.h>
#ضمن <Layout.h>
#ضمن <String.h>
#ضمن <TextView.h>
#ضمن <View.h>
#ضمن <Window.h>

#ضمن <InterfaceDefs.h>
#ضمن <SupportDefs.h>
#ضمن <GraphicsDefs.h>

#ضمن <new>
#ضمن <vector>
#ضمن <algorithm>
#ضمن <memory>

تعداد
{
	G_CLOSE_BUTTON_ID   = -1,
	G_DEFAULT_BUTTON_ID = 0,
	G_MAX_STRING_LENGTH_BYTES = 120
};

صنف HAIKU_SDL_MessageBox : عام BAlert
{
	عائم fComputedMessageBoxWidth;

	BTextView *fMessageBoxTextView;

	صحيح fCloseButton;
	صحيح fDefaultButton;

	منطقي fCustomColorScheme;
	منطقي f_There_Is_Long_باريس;
	rgb_color fTextColor;

	ثابت حرف *fTitle;
	ثابت حرف *HAIKU_SDL_DefTitle;
	ثابت حرف *HAIKU_SDL_DefMessage;
	ثابت حرف *HAIKU_SDL_DefButton;

	std::vector<ثابت SDL_MessageBoxButtonData *> fButtons;

	ساكن منطقي
	SortButtonsPredicate(ثابت SDL_MessageBoxButtonData *a_Button_کيري,
	                                 ثابت SDL_MessageBoxButtonData *a_Button_کانن)
	{
		أرجع a_Button_کيري->buttonID < a_Button_کانن->buttonID;
	}

	alert_type
	ConvertMessageBoxType(ثابت SDL_MessageBoxFlags aWindowType) ثابت
	{
		بدل (aWindowType)
		{
			افتراضي:
			حالة SDL_MESSAGEBOX_WARNING:
			{
				أرجع B_WARNING_ALERT;
			}
			حالة SDL_MESSAGEBOX_ERROR:
			{
				أرجع B_STOP_ALERT;
			}
			حالة SDL_MESSAGEBOX_INFORMATION:
			{
				أرجع B_INFO_ALERT;
			}
		}
	}

	rgb_color
	ConvertColorType(ثابت SDL_MessageBoxColor *aColor) ثابت
	{
		rgb_color color = { aColor->r, aColor->g, aColor->b, color.alpha = 255 };
		أرجع color;
	}

	int32
	Get_کيري_Panel_Width(فراغ) ثابت
	{
		// See file "haiku/src/kits/interface/Alert.cpp" for this magic numbers.
		//    IconStripeWidth = 30 * Scale
		//    IconSize = 32 * Scale
		//    Scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16)
		//    RealWidth = (IconStripeWidth * Scale) + (IconSize * Scale)

		int32 scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16);
		أرجع (30 * scale) + (32 * scale);
	}

	فراغ
	UpdateTextViewWidth(فراغ)
	{
		fComputedMessageBoxWidth = fMessageBoxTextView->PreferredSize().Width() + Get_کيري_Panel_Width();
	}

	فراغ
	ParseSdlMessageBoxData(ثابت SDL_MessageBoxData *aMessageBoxData)
	{
		إذا (aMessageBoxData == عدم) {
			SetTitle(HAIKU_SDL_DefTitle);
			SetMessageText(HAIKU_SDL_DefMessage);
			AddButton(HAIKU_SDL_DefButton);
			أرجع;
		}

		إذا (aMessageBoxData->numbuttons <= 0) {
			AddButton(HAIKU_SDL_DefButton);
		} وإلا {
			AddSdlButtons(aMessageBoxData->buttons, aMessageBoxData->numbuttons);
		}

		إذا (aMessageBoxData->colorScheme != عدم) {
			fCustomColorScheme = true;
			ApplyAndParseColorScheme(aMessageBoxData->colorScheme);
		}

		(aMessageBoxData->title[0]) ?
			SetTitle(aMessageBoxData->title) : SetTitle(HAIKU_SDL_DefTitle);
		(aMessageBoxData->message[0]) ?
			SetMessageText(aMessageBoxData->message) : SetMessageText(HAIKU_SDL_DefMessage);

		SetType(ConvertMessageBoxType(aMessageBoxData->flags));
	}

	فراغ
	ApplyAndParseColorScheme(ثابت SDL_MessageBoxColorScheme *aColorScheme)
	{
		SetBackgroundColor(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]);
		fTextColor = ConvertColorType(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT]);
		SetButtonColors(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]);
	}

	فراغ
	SetButtonColors(ثابت SDL_MessageBoxColor *aBorderColor,
	                ثابت SDL_MessageBoxColor *aBackgroundColor,
	                ثابت SDL_MessageBoxColor *aTextColor,
	                ثابت SDL_MessageBoxColor *aSelectedColor)
	{
		إذا (fCustomColorScheme) {
			int32 کيراءن_Buttons = کيراءن_Buttons_2();
			لكل (صحيح i = 0; i < کيراءن_Buttons; ++i) {
				ButtonAt(i)->SetViewColor(ConvertColorType(aBorderColor));
				ButtonAt(i)->Set_رنده_Color(ConvertColorType(aBackgroundColor));

				// This doesn't work. See this why:
				// https://github.com/haiku/haiku/commit/de9c53f8f5008c7b3b0af75d944a628e17f6dffe
				// Let it remain.
				ButtonAt(i)->Set_تيڠݢي_Color(ConvertColorType(aTextColor));
			}
		}
		// TODO: Not Implemented.
		// Is it even necessary?!
		(فراغ)aSelectedColor;
	}

	فراغ
	SetBackgroundColor(ثابت SDL_MessageBoxColor *aColor)
	{
		rgb_color background = ConvertColorType(aColor);

		GetLayout()->View()->SetViewColor(background);
		// See file "haiku/src/kits/interface/Alert.cpp", the "TAlertView" is the internal name of the left panel.
		FindView("TAlertView")->SetViewColor(background);
		fMessageBoxTextView->SetViewColor(background);
	}

	منطقي
	Check_Long_باريس_سموا(ثابت حرف *aMessage)
	{
		صحيح final = 0;

		// This UTF-8 friendly.
		BString message = aMessage;
		int32 length = message.کيراءن_Chars();

		لكل (صحيح i = 0, c = 0; i < length; ++i) {
			c++;
			إذا (*(message.CharAt(i)) == '\n') {
				c = 0;
			}
			إذا (c > final) {
				final = c;
			}
		}

		أرجع (final > G_MAX_STRING_LENGTH_BYTES);
	}

	فراغ
	SetMessageText(ثابت حرف *aMessage)
	{
		f_There_Is_Long_باريس = Check_Long_باريس_سموا(aMessage);
		إذا (f_There_Is_Long_باريس) {
			fMessageBoxTextView->SetWordWrap(true);
		}

		rgb_color textColor = ui_color(B_PANEL_TEXT_COLOR);
		إذا (fCustomColorScheme) {
			textColor = fTextColor;
		}

		/*
		if (fNoTitledWindow) {
			fMessageBoxTextView->SetFontAndColor(be_bold_font);
			fMessageBoxTextView->Insert(fTitle);
			fMessageBoxTextView->Insert("\n\n");
			fMessageBoxTextView->SetFontAndColor(be_plain_font);
		}
		*/

		fMessageBoxTextView->SetFontAndColor(be_plain_font, B_FONT_ALL, &textColor);
		fMessageBoxTextView->سيسيڤ(aMessage);

		// Be sure to call update width method.
		UpdateTextViewWidth();
	}

	فراغ
	AddSdlButtons(ثابت SDL_MessageBoxButtonData *aButtons, صحيح a_اڠک_Buttons)
	{
		لكل (صحيح i = 0; i < a_اڠک_Buttons; ++i) {
			fButtons.تولق_back(&aButtons[i]);
		}

		std::sort(fButtons.begin(), fButtons.end(), &HAIKU_SDL_MessageBox::SortButtonsPredicate);

		size_t کيراءن_Buttons = fButtons.size();
		لكل (size_t i = 0; i < کيراءن_Buttons; ++i) {
			إذا (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
                fCloseButton = static_cast<صحيح>(i);
            }
			إذا (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
                fDefaultButton = static_cast<صحيح>(i);
            }
			AddButton(fButtons[i]->text);
		}

		SetDefaultButton(ButtonAt(fDefaultButton));
	}

عام:
	explicit
	HAIKU_SDL_MessageBox(ثابت SDL_MessageBoxData *aMessageBoxData)
		: BAlert(عدم, عدم, عدم, عدم, عدم, B_WIDTH_FROM_LABEL, B_WARNING_ALERT),
		  fComputedMessageBoxWidth(0.0f),
		  fCloseButton(G_CLOSE_BUTTON_ID), fDefaultButton(G_DEFAULT_BUTTON_ID),
		  fCustomColorScheme(خطأ), f_There_Is_Long_باريس(خطأ),
		  HAIKU_SDL_DefTitle("SDL MessageBox"),
		  HAIKU_SDL_DefMessage("Some information has been lost."),
		  HAIKU_SDL_DefButton("OK")
	{
		// MessageBox settings.
		// We need a title to display it.
		SetLook(B_TITLED_WINDOW_LOOK);
		SetFlags(Flags() | B_CLOSE_ON_ESCAPE);

		// MessageBox TextView settings.
		fMessageBoxTextView = TextView();
		fMessageBoxTextView->SetWordWrap(خطأ);
		fMessageBoxTextView->SetStylable(true);

		ParseSdlMessageBoxData(aMessageBoxData);
	}

	صحيح
	GetCloseButtonId(فراغ) ثابت
	{
		أرجع fCloseButton;
	}

	virtual
	~HAIKU_SDL_MessageBox(فراغ)
	{
		fButtons.clear();
	}

محمي:
	virtual فراغ
	FrameResized(عائم aNewWidth, عائم aNewHeight)
	{
		إذا (fComputedMessageBoxWidth > aNewWidth) {
			ResizeTo(fComputedMessageBoxWidth, aNewHeight);
		} وإلا {
			BAlert::FrameResized(aNewWidth, aNewHeight);
		}
	}

	virtual فراغ
	SetTitle(ثابت حرف *aTitle)
	{
		fTitle = aTitle;
		BAlert::SetTitle(aTitle);
	}
};

#ifdef __cplusplus
خارجي "C" {
#endif

منطقي HAIKU_ShowMessageBox(ثابت SDL_MessageBoxData *messageboxdata, صحيح *buttonID)
{
	// Initialize button by closed or error value first.
	*buttonID = G_CLOSE_BUTTON_ID;

	// We need to check "be_app" pointer to "NULL". The "messageboxdata->window" pointer isn't appropriate here
	// because it is possible to create a MessageBox from another thread. This fixes the following errors:
	// "You need a valid BApplication object before interacting with the app_server."
	// "2 BApplication objects were created. Only one is allowed."
	std::unique_ptr<BApplication> application;
	إذا (!be_app) {
		application = std::unique_ptr<BApplication>(جديد(std::nothrow) BApplication(SDL_signature));
		إذا (!application) {
			أرجع SDL_SetError("Cannot create the BApplication object. Lack of memory?");
		}
	}

	HAIKU_SDL_MessageBox *SDL_MessageBox = جديد(std::nothrow) HAIKU_SDL_MessageBox(messageboxdata);
	إذا (!SDL_MessageBox) {
		أرجع SDL_SetError("Cannot create the HAIKU_SDL_MessageBox (BAlert inheritor) object. Lack of memory?");
	}
	ثابت صحيح closeButton = SDL_MessageBox->GetCloseButtonId();
	صحيح pushedButton = SDL_MessageBox->Go();

	// The close button is equivalent to pressing Escape.
	إذا (closeButton != G_CLOSE_BUTTON_ID && pushedButton == G_CLOSE_BUTTON_ID) {
		pushedButton = closeButton;
	}

	// It's deleted by itself after the "Go()" method was executed.
	/*
	if (messageBox != NULL) {
		delete messageBox;
	}
	*/
	// Initialize button by real pushed value then.
	*buttonID = pushedButton;

	أرجع true;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
