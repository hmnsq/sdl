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
	G_MAX_STRING_LENGTH_BYTES = 120
};

বর্গ HAIKU_SDL_MessageBox : সার্বজনিক BAlert
{
	ভিন্ন fComputedMessageBoxWidth;

	BTextView *fMessageBoxTextView;

	পূর্ণাঙ্ক fCloseButton;
	পূর্ণাঙ্ক fDefaultButton;

	তার্কিক fCustomColorScheme;
	তার্কিক f_There_Is_Long_সারি;
	rgb_color fTextColor;

	ধ্রুব বর্ণ *fTitle;
	ধ্রুব বর্ণ *HAIKU_SDL_DefTitle;
	ধ্রুব বর্ণ *HAIKU_SDL_DefMessage;
	ধ্রুব বর্ণ *HAIKU_SDL_DefButton;

	std::vector<ধ্রুব SDL_MessageBoxButtonData *> fButtons;

	স্থির তার্কিক
	SortButtonsPredicate(ধ্রুব SDL_MessageBoxButtonData *a_Button_বাম,
	                                 ধ্রুব SDL_MessageBoxButtonData *a_Button_ডান)
	{
		প্রত্যাগম a_Button_বাম->buttonID < a_Button_ডান->buttonID;
	}

	alert_type
	ConvertMessageBoxType(ধ্রুব SDL_MessageBoxFlags aWindowType) ধ্রুব
	{
		বিকল্প (aWindowType)
		{
			স্বভাব:
			পক্ষ SDL_MESSAGEBOX_WARNING:
			{
				প্রত্যাগম B_WARNING_ALERT;
			}
			পক্ষ SDL_MESSAGEBOX_ERROR:
			{
				প্রত্যাগম B_STOP_ALERT;
			}
			পক্ষ SDL_MESSAGEBOX_INFORMATION:
			{
				প্রত্যাগম B_INFO_ALERT;
			}
		}
	}

	rgb_color
	ConvertColorType(ধ্রুব SDL_MessageBoxColor *aColor) ধ্রুব
	{
		rgb_color color = { aColor->r, aColor->g, aColor->b, color.alpha = 255 };
		প্রত্যাগম color;
	}

	int32
	Get_বাম_Panel_Width(শূন্য) ধ্রুব
	{
		// See file "haiku/src/kits/interface/Alert.cpp" for this magic numbers.
		//    IconStripeWidth = 30 * Scale
		//    IconSize = 32 * Scale
		//    Scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16)
		//    RealWidth = (IconStripeWidth * Scale) + (IconSize * Scale)

		int32 scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16);
		প্রত্যাগম (30 * scale) + (32 * scale);
	}

	শূন্য
	UpdateTextViewWidth(শূন্য)
	{
		fComputedMessageBoxWidth = fMessageBoxTextView->PreferredSize().Width() + Get_বাম_Panel_Width();
	}

	শূন্য
	ParseSdlMessageBoxData(ধ্রুব SDL_MessageBoxData *aMessageBoxData)
	{
		যদি (aMessageBoxData == রিক্ত) {
			SetTitle(HAIKU_SDL_DefTitle);
			SetMessageText(HAIKU_SDL_DefMessage);
			AddButton(HAIKU_SDL_DefButton);
			প্রত্যাগম;
		}

		যদি (aMessageBoxData->numbuttons <= 0) {
			AddButton(HAIKU_SDL_DefButton);
		} অন্যথা {
			AddSdlButtons(aMessageBoxData->buttons, aMessageBoxData->numbuttons);
		}

		যদি (aMessageBoxData->colorScheme != রিক্ত) {
			fCustomColorScheme = সত্য;
			ApplyAndParseColorScheme(aMessageBoxData->colorScheme);
		}

		(aMessageBoxData->title[0]) ?
			SetTitle(aMessageBoxData->title) : SetTitle(HAIKU_SDL_DefTitle);
		(aMessageBoxData->message[0]) ?
			SetMessageText(aMessageBoxData->message) : SetMessageText(HAIKU_SDL_DefMessage);

		SetType(ConvertMessageBoxType(aMessageBoxData->flags));
	}

	শূন্য
	ApplyAndParseColorScheme(ধ্রুব SDL_MessageBoxColorScheme *aColorScheme)
	{
		SetBackgroundColor(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]);
		fTextColor = ConvertColorType(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT]);
		SetButtonColors(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]);
	}

	শূন্য
	SetButtonColors(ধ্রুব SDL_MessageBoxColor *aBorderColor,
	                ধ্রুব SDL_MessageBoxColor *aBackgroundColor,
	                ধ্রুব SDL_MessageBoxColor *aTextColor,
	                ধ্রুব SDL_MessageBoxColor *aSelectedColor)
	{
		যদি (fCustomColorScheme) {
			int32 গুনতি_Buttons = গুনতি_Buttons_2();
			প্রতি (পূর্ণাঙ্ক i = 0; i < গুনতি_Buttons; ++i) {
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
	SetBackgroundColor(ধ্রুব SDL_MessageBoxColor *aColor)
	{
		rgb_color background = ConvertColorType(aColor);

		GetLayout()->View()->SetViewColor(background);
		// See file "haiku/src/kits/interface/Alert.cpp", the "TAlertView" is the internal name of the left panel.
		FindView("TAlertView")->SetViewColor(background);
		fMessageBoxTextView->SetViewColor(background);
	}

	তার্কিক
	Check_Long_সারিগুলি(ধ্রুব বর্ণ *aMessage)
	{
		পূর্ণাঙ্ক final = 0;

		// This UTF-8 friendly.
		BString message = aMessage;
		int32 length = message.গুনতি_Chars();

		প্রতি (পূর্ণাঙ্ক i = 0, c = 0; i < length; ++i) {
			c++;
			যদি (*(message.CharAt(i)) == '\n') {
				c = 0;
			}
			যদি (c > final) {
				final = c;
			}
		}

		প্রত্যাগম (final > G_MAX_STRING_LENGTH_BYTES);
	}

	শূন্য
	SetMessageText(ধ্রুব বর্ণ *aMessage)
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
	AddSdlButtons(ধ্রুব SDL_MessageBoxButtonData *aButtons, পূর্ণাঙ্ক a_অঙ্ক_Buttons)
	{
		প্রতি (পূর্ণাঙ্ক i = 0; i < a_অঙ্ক_Buttons; ++i) {
			fButtons.ঠেলো_back(&aButtons[i]);
		}

		std::sort(fButtons.begin(), fButtons.end(), &HAIKU_SDL_MessageBox::SortButtonsPredicate);

		size_t গুনতি_Buttons = fButtons.size();
		প্রতি (size_t i = 0; i < গুনতি_Buttons; ++i) {
			যদি (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
                fCloseButton = static_cast<পূর্ণাঙ্ক>(i);
            }
			যদি (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
                fDefaultButton = static_cast<পূর্ণাঙ্ক>(i);
            }
			AddButton(fButtons[i]->text);
		}

		SetDefaultButton(ButtonAt(fDefaultButton));
	}

সার্বজনিক:
	explicit
	HAIKU_SDL_MessageBox(ধ্রুব SDL_MessageBoxData *aMessageBoxData)
		: BAlert(রিক্ত, রিক্ত, রিক্ত, রিক্ত, রিক্ত, B_WIDTH_FROM_LABEL, B_WARNING_ALERT),
		  fComputedMessageBoxWidth(0.0f),
		  fCloseButton(G_CLOSE_BUTTON_ID), fDefaultButton(G_DEFAULT_BUTTON_ID),
		  fCustomColorScheme(অসত্য), f_There_Is_Long_সারি(অসত্য),
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
		fMessageBoxTextView->SetWordWrap(অসত্য);
		fMessageBoxTextView->SetStylable(সত্য);

		ParseSdlMessageBoxData(aMessageBoxData);
	}

	পূর্ণাঙ্ক
	GetCloseButtonId(শূন্য) ধ্রুব
	{
		প্রত্যাগম fCloseButton;
	}

	আভাস
	~HAIKU_SDL_MessageBox(শূন্য)
	{
		fButtons.clear();
	}

রক্ষিত:
	আভাস শূন্য
	FrameResized(ভিন্ন aNewWidth, ভিন্ন aNewHeight)
	{
		যদি (fComputedMessageBoxWidth > aNewWidth) {
			ResizeTo(fComputedMessageBoxWidth, aNewHeight);
		} অন্যথা {
			BAlert::FrameResized(aNewWidth, aNewHeight);
		}
	}

	আভাস শূন্য
	SetTitle(ধ্রুব বর্ণ *aTitle)
	{
		fTitle = aTitle;
		BAlert::SetTitle(aTitle);
	}
};

#ifdef __cplusplus
বাহ্য "C" {
#endif

তার্কিক HAIKU_ShowMessageBox(ধ্রুব SDL_MessageBoxData *messageboxdata, পূর্ণাঙ্ক *buttonID)
{
	// Initialize button by closed or error value first.
	*buttonID = G_CLOSE_BUTTON_ID;

	// We need to check "be_app" pointer to "NULL". The "messageboxdata->window" pointer isn't appropriate here
	// because it is possible to create a MessageBox from another thread. This fixes the following errors:
	// "You need a valid BApplication object before interacting with the app_server."
	// "2 BApplication objects were created. Only one is allowed."
	std::unique_ptr<BApplication> application;
	যদি (!be_app) {
		application = std::unique_ptr<BApplication>(নূতন(std::nothrow) BApplication(SDL_signature));
		যদি (!application) {
			প্রত্যাগম SDL_SetError("Cannot create the BApplication object. Lack of memory?");
		}
	}

	HAIKU_SDL_MessageBox *SDL_MessageBox = নূতন(std::nothrow) HAIKU_SDL_MessageBox(messageboxdata);
	যদি (!SDL_MessageBox) {
		প্রত্যাগম SDL_SetError("Cannot create the HAIKU_SDL_MessageBox (BAlert inheritor) object. Lack of memory?");
	}
	ধ্রুব পূর্ণাঙ্ক closeButton = SDL_MessageBox->GetCloseButtonId();
	পূর্ণাঙ্ক pushedButton = SDL_MessageBox->Go();

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

	প্রত্যাগম সত্য;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
