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

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU


// For application signature.
#ଅନ୍ତର୍ଭାଵ "../../core/haiku/SDL_BeApp.h"

#ଅନ୍ତର୍ଭାଵ <Alert.h>
#ଅନ୍ତର୍ଭାଵ <Application.h>
#ଅନ୍ତର୍ଭାଵ <Button.h>
#ଅନ୍ତର୍ଭାଵ <Font.h>
#ଅନ୍ତର୍ଭାଵ <Layout.h>
#ଅନ୍ତର୍ଭାଵ <String.h>
#ଅନ୍ତର୍ଭାଵ <TextView.h>
#ଅନ୍ତର୍ଭାଵ <View.h>
#ଅନ୍ତର୍ଭାଵ <Window.h>

#ଅନ୍ତର୍ଭାଵ <InterfaceDefs.h>
#ଅନ୍ତର୍ଭାଵ <SupportDefs.h>
#ଅନ୍ତର୍ଭାଵ <GraphicsDefs.h>

#ଅନ୍ତର୍ଭାଵ <new>
#ଅନ୍ତର୍ଭାଵ <vector>
#ଅନ୍ତର୍ଭାଵ <algorithm>
#ଅନ୍ତର୍ଭାଵ <memory>

ଗଣନା
{
	G_CLOSE_BUTTON_ID   = -1,
	G_DEFAULT_BUTTON_ID = 0,
	G_MAX_STRING_LENGTH_BYTES = 120
};

ଶ୍ରେଣୀ HAIKU_SDL_MessageBox : ସର୍ବସାଧାରଣ BAlert
{
	ଦଶମିକ fComputedMessageBoxWidth;

	BTextView *fMessageBoxTextView;

	ପୂର୍ଣ୍ଣସଂଖ୍ୟା fCloseButton;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା fDefaultButton;

	ତାର୍କିକ fCustomColorScheme;
	ତାର୍କିକ f_There_Is_Long_ଧାଡ଼ି;
	rgb_color fTextColor;

	ଅଚଳ ଅକ୍ଷର *fTitle;
	ଅଚଳ ଅକ୍ଷର *HAIKU_SDL_DefTitle;
	ଅଚଳ ଅକ୍ଷର *HAIKU_SDL_DefMessage;
	ଅଚଳ ଅକ୍ଷର *HAIKU_SDL_DefButton;

	std::vector<ଅଚଳ SDL_MessageBoxButtonData *> fButtons;

	ସ୍ଥିର ତାର୍କିକ
	SortButtonsPredicate(ଅଚଳ SDL_MessageBoxButtonData *a_Button_ବାମ,
	                                 ଅଚଳ SDL_MessageBoxButtonData *a_Button_ଡାହାଣ)
	{
		ଫେରନ୍ତୁ a_Button_ବାମ->buttonID < a_Button_ଡାହାଣ->buttonID;
	}

	alert_type
	ConvertMessageBoxType(ଅଚଳ SDL_MessageBoxFlags aWindowType) ଅଚଳ
	{
		ବାଛ (aWindowType)
		{
			ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
			ସ୍ଥିତି SDL_MESSAGEBOX_WARNING:
			{
				ଫେରନ୍ତୁ B_WARNING_ALERT;
			}
			ସ୍ଥିତି SDL_MESSAGEBOX_ERROR:
			{
				ଫେରନ୍ତୁ B_STOP_ALERT;
			}
			ସ୍ଥିତି SDL_MESSAGEBOX_INFORMATION:
			{
				ଫେରନ୍ତୁ B_INFO_ALERT;
			}
		}
	}

	rgb_color
	ConvertColorType(ଅଚଳ SDL_MessageBoxColor *aColor) ଅଚଳ
	{
		rgb_color color = { aColor->r, aColor->g, aColor->b, color.alpha = 255 };
		ଫେରନ୍ତୁ color;
	}

	int32
	Get_ବାମ_Panel_Width(ଶୂନ୍ୟ) ଅଚଳ
	{
		// See file "haiku/src/kits/interface/Alert.cpp" for this magic numbers.
		//    IconStripeWidth = 30 * Scale
		//    IconSize = 32 * Scale
		//    Scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16)
		//    RealWidth = (IconStripeWidth * Scale) + (IconSize * Scale)

		int32 scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16);
		ଫେରନ୍ତୁ (30 * scale) + (32 * scale);
	}

	ଶୂନ୍ୟ
	UpdateTextViewWidth(ଶୂନ୍ୟ)
	{
		fComputedMessageBoxWidth = fMessageBoxTextView->PreferredSize().Width() + Get_ବାମ_Panel_Width();
	}

	ଶୂନ୍ୟ
	ParseSdlMessageBoxData(ଅଚଳ SDL_MessageBoxData *aMessageBoxData)
	{
		ଯଦି (aMessageBoxData == ଖାଲି) {
			SetTitle(HAIKU_SDL_DefTitle);
			SetMessageText(HAIKU_SDL_DefMessage);
			AddButton(HAIKU_SDL_DefButton);
			ଫେରନ୍ତୁ;
		}

		ଯଦି (aMessageBoxData->numbuttons <= 0) {
			AddButton(HAIKU_SDL_DefButton);
		} ଅନ୍ୟଥା {
			AddSdlButtons(aMessageBoxData->buttons, aMessageBoxData->numbuttons);
		}

		ଯଦି (aMessageBoxData->colorScheme != ଖାଲି) {
			fCustomColorScheme = ସତ୍ୟ;
			ApplyAndParseColorScheme(aMessageBoxData->colorScheme);
		}

		(aMessageBoxData->title[0]) ?
			SetTitle(aMessageBoxData->title) : SetTitle(HAIKU_SDL_DefTitle);
		(aMessageBoxData->message[0]) ?
			SetMessageText(aMessageBoxData->message) : SetMessageText(HAIKU_SDL_DefMessage);

		SetType(ConvertMessageBoxType(aMessageBoxData->flags));
	}

	ଶୂନ୍ୟ
	ApplyAndParseColorScheme(ଅଚଳ SDL_MessageBoxColorScheme *aColorScheme)
	{
		SetBackgroundColor(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]);
		fTextColor = ConvertColorType(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT]);
		SetButtonColors(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]);
	}

	ଶୂନ୍ୟ
	SetButtonColors(ଅଚଳ SDL_MessageBoxColor *aBorderColor,
	                ଅଚଳ SDL_MessageBoxColor *aBackgroundColor,
	                ଅଚଳ SDL_MessageBoxColor *aTextColor,
	                ଅଚଳ SDL_MessageBoxColor *aSelectedColor)
	{
		ଯଦି (fCustomColorScheme) {
			int32 ଗଣନା_Buttons = ଗଣନା_Buttons_2();
			ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ଗଣନା_Buttons; ++i) {
				ButtonAt(i)->SetViewColor(ConvertColorType(aBorderColor));
				ButtonAt(i)->Set_ତଳ_Color(ConvertColorType(aBackgroundColor));

				// This doesn't work. See this why:
				// https://github.com/haiku/haiku/commit/de9c53f8f5008c7b3b0af75d944a628e17f6dffe
				// Let it remain.
				ButtonAt(i)->Set_ଉପର_Color(ConvertColorType(aTextColor));
			}
		}
		// TODO: Not Implemented.
		// Is it even necessary?!
		(ଶୂନ୍ୟ)aSelectedColor;
	}

	ଶୂନ୍ୟ
	SetBackgroundColor(ଅଚଳ SDL_MessageBoxColor *aColor)
	{
		rgb_color background = ConvertColorType(aColor);

		GetLayout()->View()->SetViewColor(background);
		// See file "haiku/src/kits/interface/Alert.cpp", the "TAlertView" is the internal name of the left panel.
		FindView("TAlertView")->SetViewColor(background);
		fMessageBoxTextView->SetViewColor(background);
	}

	ତାର୍କିକ
	Check_Long_ଧାଡ଼ିଗୁଡ଼ିକ(ଅଚଳ ଅକ୍ଷର *aMessage)
	{
		ପୂର୍ଣ୍ଣସଂଖ୍ୟା final = 0;

		// This UTF-8 friendly.
		BString message = aMessage;
		int32 length = message.ଗଣନା_Chars();

		ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0, c = 0; i < length; ++i) {
			c++;
			ଯଦି (*(message.CharAt(i)) == '\n') {
				c = 0;
			}
			ଯଦି (c > final) {
				final = c;
			}
		}

		ଫେରନ୍ତୁ (final > G_MAX_STRING_LENGTH_BYTES);
	}

	ଶୂନ୍ୟ
	SetMessageText(ଅଚଳ ଅକ୍ଷର *aMessage)
	{
		f_There_Is_Long_ଧାଡ଼ି = Check_Long_ଧାଡ଼ିଗୁଡ଼ିକ(aMessage);
		ଯଦି (f_There_Is_Long_ଧାଡ଼ି) {
			fMessageBoxTextView->SetWordWrap(ସତ୍ୟ);
		}

		rgb_color textColor = ui_color(B_PANEL_TEXT_COLOR);
		ଯଦି (fCustomColorScheme) {
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
		fMessageBoxTextView->ଭର୍ତ୍ତି(aMessage);

		// Be sure to call update width method.
		UpdateTextViewWidth();
	}

	ଶୂନ୍ୟ
	AddSdlButtons(ଅଚଳ SDL_MessageBoxButtonData *aButtons, ପୂର୍ଣ୍ଣସଂଖ୍ୟା a_ଅଙ୍କ_Buttons)
	{
		ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < a_ଅଙ୍କ_Buttons; ++i) {
			fButtons.ଠେଲ_back(&aButtons[i]);
		}

		std::sort(fButtons.begin(), fButtons.end(), &HAIKU_SDL_MessageBox::SortButtonsPredicate);

		size_t ଗଣନା_Buttons = fButtons.size();
		ପାଇଁ (size_t i = 0; i < ଗଣନା_Buttons; ++i) {
			ଯଦି (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
                fCloseButton = static_cast<ପୂର୍ଣ୍ଣସଂଖ୍ୟା>(i);
            }
			ଯଦି (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
                fDefaultButton = static_cast<ପୂର୍ଣ୍ଣସଂଖ୍ୟା>(i);
            }
			AddButton(fButtons[i]->text);
		}

		SetDefaultButton(ButtonAt(fDefaultButton));
	}

ସର୍ବସାଧାରଣ:
	explicit
	HAIKU_SDL_MessageBox(ଅଚଳ SDL_MessageBoxData *aMessageBoxData)
		: BAlert(ଖାଲି, ଖାଲି, ଖାଲି, ଖାଲି, ଖାଲି, B_WIDTH_FROM_LABEL, B_WARNING_ALERT),
		  fComputedMessageBoxWidth(0.0f),
		  fCloseButton(G_CLOSE_BUTTON_ID), fDefaultButton(G_DEFAULT_BUTTON_ID),
		  fCustomColorScheme(ମିଥ୍ୟା), f_There_Is_Long_ଧାଡ଼ି(ମିଥ୍ୟା),
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
		fMessageBoxTextView->SetWordWrap(ମିଥ୍ୟା);
		fMessageBoxTextView->SetStylable(ସତ୍ୟ);

		ParseSdlMessageBoxData(aMessageBoxData);
	}

	ପୂର୍ଣ୍ଣସଂଖ୍ୟା
	GetCloseButtonId(ଶୂନ୍ୟ) ଅଚଳ
	{
		ଫେରନ୍ତୁ fCloseButton;
	}

	ଆଭାସୀ
	~HAIKU_SDL_MessageBox(ଶୂନ୍ୟ)
	{
		fButtons.clear();
	}

ସୁରକ୍ଷିତ:
	ଆଭାସୀ ଶୂନ୍ୟ
	FrameResized(ଦଶମିକ aNewWidth, ଦଶମିକ aNewHeight)
	{
		ଯଦି (fComputedMessageBoxWidth > aNewWidth) {
			ResizeTo(fComputedMessageBoxWidth, aNewHeight);
		} ଅନ୍ୟଥା {
			BAlert::FrameResized(aNewWidth, aNewHeight);
		}
	}

	ଆଭାସୀ ଶୂନ୍ୟ
	SetTitle(ଅଚଳ ଅକ୍ଷର *aTitle)
	{
		fTitle = aTitle;
		BAlert::SetTitle(aTitle);
	}
};

#ifdef __cplusplus
ବାହ୍ୟ "C" {
#endif

ତାର୍କିକ HAIKU_ShowMessageBox(ଅଚଳ SDL_MessageBoxData *messageboxdata, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *buttonID)
{
	// Initialize button by closed or error value first.
	*buttonID = G_CLOSE_BUTTON_ID;

	// We need to check "be_app" pointer to "NULL". The "messageboxdata->window" pointer isn't appropriate here
	// because it is possible to create a MessageBox from another thread. This fixes the following errors:
	// "You need a valid BApplication object before interacting with the app_server."
	// "2 BApplication objects were created. Only one is allowed."
	std::unique_ptr<BApplication> application;
	ଯଦି (!be_app) {
		application = std::unique_ptr<BApplication>(ନୂତନ(std::nothrow) BApplication(SDL_signature));
		ଯଦି (!application) {
			ଫେରନ୍ତୁ SDL_SetError("Cannot create the BApplication object. Lack of memory?");
		}
	}

	HAIKU_SDL_MessageBox *SDL_MessageBox = ନୂତନ(std::nothrow) HAIKU_SDL_MessageBox(messageboxdata);
	ଯଦି (!SDL_MessageBox) {
		ଫେରନ୍ତୁ SDL_SetError("Cannot create the HAIKU_SDL_MessageBox (BAlert inheritor) object. Lack of memory?");
	}
	ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା closeButton = SDL_MessageBox->GetCloseButtonId();
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା pushedButton = SDL_MessageBox->Go();

	// The close button is equivalent to pressing Escape.
	ଯଦି (closeButton != G_CLOSE_BUTTON_ID && pushedButton == G_CLOSE_BUTTON_ID) {
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

	ଫେରନ୍ତୁ ସତ୍ୟ;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
