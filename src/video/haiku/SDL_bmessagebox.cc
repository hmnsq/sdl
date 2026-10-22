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

#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU


// For application signature.
#অন্তর্ভাব "../../core/haiku/SDL_BeApp.h"

#অন্তর্ভাব <Alert.h>
#অন্তর্ভাব <Application.h>
#অন্তর্ভাব <Button.h>
#অন্তর্ভাব <Font.h>
#অন্তর্ভাব <Layout.h>
#অন্তর্ভাব <String.h>
#অন্তর্ভাব <TextView.h>
#অন্তর্ভাব <View.h>
#অন্তর্ভাব <Window.h>

#অন্তর্ভাব <InterfaceDefs.h>
#অন্তর্ভাব <SupportDefs.h>
#অন্তর্ভাব <GraphicsDefs.h>

#অন্তর্ভাব <new>
#অন্তর্ভাব <vector>
#অন্তর্ভাব <algorithm>
#অন্তর্ভাব <memory>

গণনা
{
	G_CLOSE_BUTTON_ID   = -1,
	G_DEFAULT_BUTTON_ID = 0,
	G_MAX_STRING_দৈর্ঘ্য_BYTES = 120
};

শ্রেণী HAIKU_SDL_MessageBox : সর্বজনীন BAlert
{
	দশমিক fComputedMessageBoxWidth;

	BTextView *fMessageBoxTextView;

	পূর্ণসংখ্যা fCloseButton;
	পূর্ণসংখ্যা fDefaultButton;

	যৌক্তিক fCustomColorScheme;
	যৌক্তিক f_There_Is_Long_সারি;
	rgb_color fTextColor;

	ধ্রুবক অক্ষর *fTitle;
	ধ্রুবক অক্ষর *HAIKU_SDL_DefTitle;
	ধ্রুবক অক্ষর *HAIKU_SDL_DefMessage;
	ধ্রুবক অক্ষর *HAIKU_SDL_DefButton;

	std::vector<ধ্রুবক SDL_Message_Box_Button_তথ্য *> fButtons;

	স্থির যৌক্তিক
	SortButtonsPredicate(ধ্রুবক SDL_Message_Box_Button_তথ্য *a_Button_বাম,
	                                 ধ্রুবক SDL_Message_Box_Button_তথ্য *a_Button_ডান)
	{
		ফেরত a_Button_বাম->buttonID < a_Button_ডান->buttonID;
	}

	alert_type
	ConvertMessageBoxType(ধ্রুবক SDL_MessageBoxFlags aWindowType) ধ্রুবক
	{
		নির্বাচন (aWindowType)
		{
			পূর্বনির্ধারিত:
			ক্ষেত্র SDL_MESSAGEBOX_WARNING:
			{
				ফেরত B_WARNING_ALERT;
			}
			ক্ষেত্র SDL_MESSAGEBOX_ERROR:
			{
				ফেরত B_STOP_ALERT;
			}
			ক্ষেত্র SDL_MESSAGEBOX_INFORMATION:
			{
				ফেরত B_INFO_ALERT;
			}
		}
	}

	rgb_color
	ConvertColorType(ধ্রুবক SDL_MessageBoxColor *aColor) ধ্রুবক
	{
		rgb_color color = { aColor->r, aColor->g, aColor->b, color.alpha = 255 };
		ফেরত color;
	}

	int32
	Get_বাম_Panel_Width(শূন্য) ধ্রুবক
	{
		// See file "haiku/src/kits/interface/Alert.cpp" for this magic numbers.
		//    IconStripeWidth = 30 * Scale
		//    IconSize = 32 * Scale
		//    Scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16)
		//    RealWidth = (IconStripeWidth * Scale) + (IconSize * Scale)

		int32 scale = max_c(1, ((int32)be_plain_font->আকার_3() + 15) / 16);
		ফেরত (30 * scale) + (32 * scale);
	}

	শূন্য
	UpdateTextViewWidth(শূন্য)
	{
		fComputedMessageBoxWidth = fMessageBoxTextView->Preferred_আকার().Width() + Get_বাম_Panel_Width();
	}

	শূন্য
	Parse_Sdl_Message_Box_তথ্য(ধ্রুবক SDL_Message_Box_তথ্য *a_Message_Box_তথ্য)
	{
		যদি (a_Message_Box_তথ্য == ফাঁকা) {
			SetTitle(HAIKU_SDL_DefTitle);
			SetMessageText(HAIKU_SDL_DefMessage);
			AddButton(HAIKU_SDL_DefButton);
			ফেরত;
		}

		যদি (a_Message_Box_তথ্য->numbuttons <= 0) {
			AddButton(HAIKU_SDL_DefButton);
		} অন্যথা {
			AddSdlButtons(a_Message_Box_তথ্য->buttons, a_Message_Box_তথ্য->numbuttons);
		}

		যদি (a_Message_Box_তথ্য->colorScheme != ফাঁকা) {
			fCustomColorScheme = সত্য;
			ApplyAndParseColorScheme(a_Message_Box_তথ্য->colorScheme);
		}

		(a_Message_Box_তথ্য->title[0]) ?
			SetTitle(a_Message_Box_তথ্য->title) : SetTitle(HAIKU_SDL_DefTitle);
		(a_Message_Box_তথ্য->message[0]) ?
			SetMessageText(a_Message_Box_তথ্য->message) : SetMessageText(HAIKU_SDL_DefMessage);

		SetType(ConvertMessageBoxType(a_Message_Box_তথ্য->flags));
	}

	শূন্য
	ApplyAndParseColorScheme(ধ্রুবক SDL_MessageBoxColorScheme *aColorScheme)
	{
		SetBackgroundColor(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]);
		fTextColor = ConvertColorType(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT]);
		SetButtonColors(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]);
	}

	শূন্য
	SetButtonColors(ধ্রুবক SDL_MessageBoxColor *aBorderColor,
	                ধ্রুবক SDL_MessageBoxColor *aBackgroundColor,
	                ধ্রুবক SDL_MessageBoxColor *aTextColor,
	                ধ্রুবক SDL_MessageBoxColor *aSelectedColor)
	{
		যদি (fCustomColorScheme) {
			int32 গুনতি_Buttons = গুনতি_Buttons_2();
			জন্য (পূর্ণসংখ্যা i = 0; i < গুনতি_Buttons; ++i) {
				ButtonAt(i)->SetViewColor(ConvertColorType(aBorderColor));
				ButtonAt(i)->Set_নিচের_Color(ConvertColorType(aBackgroundColor));

				// This doesn't work. See this why:
				// https://github.com/haiku/haiku/commit/de9c53f8f5008c7b3b0af75d944a628e17f6dffe
				// Let it remain.
				ButtonAt(i)->Set_উপরের_Color(ConvertColorType(aTextColor));
			}
		}
		// TODO: Not Implemented.
		// Is it even necessary?!
		(শূন্য)aSelectedColor;
	}

	শূন্য
	SetBackgroundColor(ধ্রুবক SDL_MessageBoxColor *aColor)
	{
		rgb_color background = ConvertColorType(aColor);

		GetLayout()->View()->SetViewColor(background);
		// See file "haiku/src/kits/interface/Alert.cpp", the "TAlertView" is the internal name of the left panel.
		FindView("TAlertView")->SetViewColor(background);
		fMessageBoxTextView->SetViewColor(background);
	}

	যৌক্তিক
	Check_Long_সারিগুলি(ধ্রুবক অক্ষর *aMessage)
	{
		পূর্ণসংখ্যা final = 0;

		// This UTF-8 friendly.
		BString message = aMessage;
		int32 দৈর্ঘ্য = message.গুনতি_Chars();

		জন্য (পূর্ণসংখ্যা i = 0, c = 0; i < দৈর্ঘ্য; ++i) {
			c++;
			যদি (*(message.CharAt(i)) == '\n') {
				c = 0;
			}
			যদি (c > final) {
				final = c;
			}
		}

		ফেরত (final > G_MAX_STRING_দৈর্ঘ্য_BYTES);
	}

	শূন্য
	SetMessageText(ধ্রুবক অক্ষর *aMessage)
	{
		f_There_Is_Long_সারি = Check_Long_সারিগুলি(aMessage);
		যদি (f_There_Is_Long_সারি) {
			fMessageBoxTextView->SetWordWrap(সত্য);
		}

		rgb_color textColor = ui_color(B_PANEL_TEXT_COLOR);
		যদি (fCustomColorScheme) {
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
		fMessageBoxTextView->ঢোকাও(aMessage);

		// Be sure to call update width method.
		UpdateTextViewWidth();
	}

	শূন্য
	AddSdlButtons(ধ্রুবক SDL_Message_Box_Button_তথ্য *aButtons, পূর্ণসংখ্যা a_অঙ্ক_Buttons)
	{
		জন্য (পূর্ণসংখ্যা i = 0; i < a_অঙ্ক_Buttons; ++i) {
			fButtons.ঠেলো_back(&aButtons[i]);
		}

		std::sort(fButtons.begin(), fButtons.end(), &HAIKU_SDL_MessageBox::SortButtonsPredicate);

		size_t গুনতি_Buttons = fButtons.আকার_2();
		জন্য (size_t i = 0; i < গুনতি_Buttons; ++i) {
			যদি (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
                fCloseButton = static_cast<পূর্ণসংখ্যা>(i);
            }
			যদি (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
                fDefaultButton = static_cast<পূর্ণসংখ্যা>(i);
            }
			AddButton(fButtons[i]->text);
		}

		SetDefaultButton(ButtonAt(fDefaultButton));
	}

সর্বজনীন:
	explicit
	HAIKU_SDL_MessageBox(ধ্রুবক SDL_Message_Box_তথ্য *a_Message_Box_তথ্য)
		: BAlert(ফাঁকা, ফাঁকা, ফাঁকা, ফাঁকা, ফাঁকা, B_WIDTH_FROM_LABEL, B_WARNING_ALERT),
		  fComputedMessageBoxWidth(0.0f),
		  fCloseButton(G_CLOSE_BUTTON_ID), fDefaultButton(G_DEFAULT_BUTTON_ID),
		  fCustomColorScheme(মিথ্যা), f_There_Is_Long_সারি(মিথ্যা),
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
		fMessageBoxTextView->SetWordWrap(মিথ্যা);
		fMessageBoxTextView->SetStylable(সত্য);

		Parse_Sdl_Message_Box_তথ্য(a_Message_Box_তথ্য);
	}

	পূর্ণসংখ্যা
	GetCloseButtonId(শূন্য) ধ্রুবক
	{
		ফেরত fCloseButton;
	}

	আভাসী
	~HAIKU_SDL_MessageBox(শূন্য)
	{
		fButtons.clear();
	}

সুরক্ষিত:
	আভাসী শূন্য
	FrameResized(দশমিক aNewWidth, দশমিক aNewHeight)
	{
		যদি (fComputedMessageBoxWidth > aNewWidth) {
			ResizeTo(fComputedMessageBoxWidth, aNewHeight);
		} অন্যথা {
			BAlert::FrameResized(aNewWidth, aNewHeight);
		}
	}

	আভাসী শূন্য
	SetTitle(ধ্রুবক অক্ষর *aTitle)
	{
		fTitle = aTitle;
		BAlert::SetTitle(aTitle);
	}
};

#ifdef __cplusplus
বাহ্যিক "C" {
#endif

যৌক্তিক HAIKU_ShowMessageBox(ধ্রুবক SDL_Message_Box_তথ্য *messageboxdata, পূর্ণসংখ্যা *buttonID)
{
	// Initialize button by closed or error value first.
	*buttonID = G_CLOSE_BUTTON_ID;

	// We need to check "be_app" pointer to "NULL". The "messageboxdata->window" pointer isn't appropriate here
	// because it is possible to create a MessageBox from another thread. This fixes the following errors:
	// "You need a valid BApplication object before interacting with the app_server."
	// "2 BApplication objects were created. Only one is allowed."
	std::unique_ptr<BApplication> application;
	যদি (!be_app) {
		application = std::unique_ptr<BApplication>(নতুন(std::nothrow) BApplication(SDL_signature));
		যদি (!application) {
			ফেরত SDL_SetError("Cannot create the BApplication object. Lack of memory?");
		}
	}

	HAIKU_SDL_MessageBox *SDL_MessageBox = নতুন(std::nothrow) HAIKU_SDL_MessageBox(messageboxdata);
	যদি (!SDL_MessageBox) {
		ফেরত SDL_SetError("Cannot create the HAIKU_SDL_MessageBox (BAlert inheritor) object. Lack of memory?");
	}
	ধ্রুবক পূর্ণসংখ্যা closeButton = SDL_MessageBox->GetCloseButtonId();
	পূর্ণসংখ্যা pushedButton = SDL_MessageBox->Go();

	// The close button is equivalent to pressing Escape.
	যদি (closeButton != G_CLOSE_BUTTON_ID && pushedButton == G_CLOSE_BUTTON_ID) {
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

	ফেরত সত্য;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
