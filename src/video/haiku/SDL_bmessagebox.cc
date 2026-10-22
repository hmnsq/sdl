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

#شامل "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU


// For application signature.
#شامل "../../core/haiku/SDL_BeApp.h"

#شامل <Alert.h>
#شامل <Application.h>
#شامل <Button.h>
#شامل <Font.h>
#شامل <Layout.h>
#شامل <String.h>
#شامل <TextView.h>
#شامل <View.h>
#شامل <Window.h>

#شامل <InterfaceDefs.h>
#شامل <SupportDefs.h>
#شامل <GraphicsDefs.h>

#شامل <new>
#شامل <vector>
#شامل <algorithm>
#شامل <memory>

شمارش
{
	G_CLOSE_BUTTON_ID   = -1,
	G_DEFAULT_BUTTON_ID = 0,
	G_MAX_STRING_LENGTH_BYTES = 120
};

رده HAIKU_SDL_MessageBox : عمومی BAlert
{
	اعشاری fComputedMessageBoxWidth;

	BTextView *fMessageBoxTextView;

	صحیح fCloseButton;
	صحیح fDefaultButton;

	منطقی fCustomColorScheme;
	منطقی f_There_Is_Long_سطر;
	rgb_color fTextColor;

	ثابت نویسه *fTitle;
	ثابت نویسه *HAIKU_SDL_DefTitle;
	ثابت نویسه *HAIKU_SDL_DefMessage;
	ثابت نویسه *HAIKU_SDL_DefButton;

	std::vector<ثابت SDL_MessageBoxButtonData *> fButtons;

	ایستا منطقی
	SortButtonsPredicate(ثابت SDL_MessageBoxButtonData *a_Button_چپ,
	                                 ثابت SDL_MessageBoxButtonData *a_Button_راست)
	{
		بازگشت a_Button_چپ->buttonID < a_Button_راست->buttonID;
	}

	alert_type
	ConvertMessageBoxType(ثابت SDL_MessageBoxFlags aWindowType) ثابت
	{
		انتخاب (aWindowType)
		{
			پیشفرض:
			حالت SDL_MESSAGEBOX_WARNING:
			{
				بازگشت B_WARNING_ALERT;
			}
			حالت SDL_MESSAGEBOX_ERROR:
			{
				بازگشت B_STOP_ALERT;
			}
			حالت SDL_MESSAGEBOX_INFORMATION:
			{
				بازگشت B_INFO_ALERT;
			}
		}
	}

	rgb_color
	ConvertColorType(ثابت SDL_MessageBoxColor *aColor) ثابت
	{
		rgb_color color = { aColor->r, aColor->g, aColor->b, color.alpha = 255 };
		بازگشت color;
	}

	int32
	Get_چپ_Panel_Width(تهی) ثابت
	{
		// See file "haiku/src/kits/interface/Alert.cpp" for this magic numbers.
		//    IconStripeWidth = 30 * Scale
		//    IconSize = 32 * Scale
		//    Scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16)
		//    RealWidth = (IconStripeWidth * Scale) + (IconSize * Scale)

		int32 scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16);
		بازگشت (30 * scale) + (32 * scale);
	}

	تهی
	UpdateTextViewWidth(تهی)
	{
		fComputedMessageBoxWidth = fMessageBoxTextView->PreferredSize().Width() + Get_چپ_Panel_Width();
	}

	تهی
	ParseSdlMessageBoxData(ثابت SDL_MessageBoxData *aMessageBoxData)
	{
		اگر (aMessageBoxData == پوچ) {
			SetTitle(HAIKU_SDL_DefTitle);
			SetMessageText(HAIKU_SDL_DefMessage);
			AddButton(HAIKU_SDL_DefButton);
			بازگشت;
		}

		اگر (aMessageBoxData->numbuttons <= 0) {
			AddButton(HAIKU_SDL_DefButton);
		} وگرنه {
			AddSdlButtons(aMessageBoxData->buttons, aMessageBoxData->numbuttons);
		}

		اگر (aMessageBoxData->colorScheme != پوچ) {
			fCustomColorScheme = درست;
			ApplyAndParseColorScheme(aMessageBoxData->colorScheme);
		}

		(aMessageBoxData->title[0]) ?
			SetTitle(aMessageBoxData->title) : SetTitle(HAIKU_SDL_DefTitle);
		(aMessageBoxData->message[0]) ?
			SetMessageText(aMessageBoxData->message) : SetMessageText(HAIKU_SDL_DefMessage);

		SetType(ConvertMessageBoxType(aMessageBoxData->flags));
	}

	تهی
	ApplyAndParseColorScheme(ثابت SDL_MessageBoxColorScheme *aColorScheme)
	{
		SetBackgroundColor(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]);
		fTextColor = ConvertColorType(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT]);
		SetButtonColors(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]);
	}

	تهی
	SetButtonColors(ثابت SDL_MessageBoxColor *aBorderColor,
	                ثابت SDL_MessageBoxColor *aBackgroundColor,
	                ثابت SDL_MessageBoxColor *aTextColor,
	                ثابت SDL_MessageBoxColor *aSelectedColor)
	{
		اگر (fCustomColorScheme) {
			int32 شمار_Buttons = شمار_Buttons_2();
			برای (صحیح i = 0; i < شمار_Buttons; ++i) {
				ButtonAt(i)->SetViewColor(ConvertColorType(aBorderColor));
				ButtonAt(i)->Set_کم_Color(ConvertColorType(aBackgroundColor));

				// This doesn't work. See this why:
				// https://github.com/haiku/haiku/commit/de9c53f8f5008c7b3b0af75d944a628e17f6dffe
				// Let it remain.
				ButtonAt(i)->Set_بالا_Color(ConvertColorType(aTextColor));
			}
		}
		// TODO: Not Implemented.
		// Is it even necessary?!
		(تهی)aSelectedColor;
	}

	تهی
	SetBackgroundColor(ثابت SDL_MessageBoxColor *aColor)
	{
		rgb_color background = ConvertColorType(aColor);

		GetLayout()->View()->SetViewColor(background);
		// See file "haiku/src/kits/interface/Alert.cpp", the "TAlertView" is the internal name of the left panel.
		FindView("TAlertView")->SetViewColor(background);
		fMessageBoxTextView->SetViewColor(background);
	}

	منطقی
	Check_Long_سطرها(ثابت نویسه *aMessage)
	{
		صحیح final = 0;

		// This UTF-8 friendly.
		BString message = aMessage;
		int32 length = message.شمار_Chars();

		برای (صحیح i = 0, c = 0; i < length; ++i) {
			c++;
			اگر (*(message.CharAt(i)) == '\n') {
				c = 0;
			}
			اگر (c > final) {
				final = c;
			}
		}

		بازگشت (final > G_MAX_STRING_LENGTH_BYTES);
	}

	تهی
	SetMessageText(ثابت نویسه *aMessage)
	{
		f_There_Is_Long_سطر = Check_Long_سطرها(aMessage);
		اگر (f_There_Is_Long_سطر) {
			fMessageBoxTextView->SetWordWrap(درست);
		}

		rgb_color textColor = ui_color(B_PANEL_TEXT_COLOR);
		اگر (fCustomColorScheme) {
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
		fMessageBoxTextView->درج(aMessage);

		// Be sure to call update width method.
		UpdateTextViewWidth();
	}

	تهی
	AddSdlButtons(ثابت SDL_MessageBoxButtonData *aButtons, صحیح a_رقم_Buttons)
	{
		برای (صحیح i = 0; i < a_رقم_Buttons; ++i) {
			fButtons.افزودن_back(&aButtons[i]);
		}

		std::sort(fButtons.begin(), fButtons.end(), &HAIKU_SDL_MessageBox::SortButtonsPredicate);

		size_t شمار_Buttons = fButtons.size();
		برای (size_t i = 0; i < شمار_Buttons; ++i) {
			اگر (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
                fCloseButton = static_cast<صحیح>(i);
            }
			اگر (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
                fDefaultButton = static_cast<صحیح>(i);
            }
			AddButton(fButtons[i]->text);
		}

		SetDefaultButton(ButtonAt(fDefaultButton));
	}

عمومی:
	explicit
	HAIKU_SDL_MessageBox(ثابت SDL_MessageBoxData *aMessageBoxData)
		: BAlert(پوچ, پوچ, پوچ, پوچ, پوچ, B_WIDTH_FROM_LABEL, B_WARNING_ALERT),
		  fComputedMessageBoxWidth(0.0f),
		  fCloseButton(G_CLOSE_BUTTON_ID), fDefaultButton(G_DEFAULT_BUTTON_ID),
		  fCustomColorScheme(نادرست), f_There_Is_Long_سطر(نادرست),
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
		fMessageBoxTextView->SetWordWrap(نادرست);
		fMessageBoxTextView->SetStylable(درست);

		ParseSdlMessageBoxData(aMessageBoxData);
	}

	صحیح
	GetCloseButtonId(تهی) ثابت
	{
		بازگشت fCloseButton;
	}

	مجازی
	~HAIKU_SDL_MessageBox(تهی)
	{
		fButtons.clear();
	}

محافظتشده:
	مجازی تهی
	FrameResized(اعشاری aNewWidth, اعشاری aNewHeight)
	{
		اگر (fComputedMessageBoxWidth > aNewWidth) {
			ResizeTo(fComputedMessageBoxWidth, aNewHeight);
		} وگرنه {
			BAlert::FrameResized(aNewWidth, aNewHeight);
		}
	}

	مجازی تهی
	SetTitle(ثابت نویسه *aTitle)
	{
		fTitle = aTitle;
		BAlert::SetTitle(aTitle);
	}
};

#ifdef __cplusplus
بیرونی "C" {
#endif

منطقی HAIKU_ShowMessageBox(ثابت SDL_MessageBoxData *messageboxdata, صحیح *buttonID)
{
	// Initialize button by closed or error value first.
	*buttonID = G_CLOSE_BUTTON_ID;

	// We need to check "be_app" pointer to "NULL". The "messageboxdata->window" pointer isn't appropriate here
	// because it is possible to create a MessageBox from another thread. This fixes the following errors:
	// "You need a valid BApplication object before interacting with the app_server."
	// "2 BApplication objects were created. Only one is allowed."
	std::unique_ptr<BApplication> application;
	اگر (!be_app) {
		application = std::unique_ptr<BApplication>(جدید(std::nothrow) BApplication(SDL_signature));
		اگر (!application) {
			بازگشت SDL_SetError("Cannot create the BApplication object. Lack of memory?");
		}
	}

	HAIKU_SDL_MessageBox *SDL_MessageBox = جدید(std::nothrow) HAIKU_SDL_MessageBox(messageboxdata);
	اگر (!SDL_MessageBox) {
		بازگشت SDL_SetError("Cannot create the HAIKU_SDL_MessageBox (BAlert inheritor) object. Lack of memory?");
	}
	ثابت صحیح closeButton = SDL_MessageBox->GetCloseButtonId();
	صحیح pushedButton = SDL_MessageBox->Go();

	// The close button is equivalent to pressing Escape.
	اگر (closeButton != G_CLOSE_BUTTON_ID && pushedButton == G_CLOSE_BUTTON_ID) {
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

	بازگشت درست;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
