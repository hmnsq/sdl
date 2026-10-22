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

#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU


// For application signature.
#அந்தர்பாவ "../../core/haiku/SDL_BeApp.h"

#அந்தர்பாவ <Alert.h>
#அந்தர்பாவ <Application.h>
#அந்தர்பாவ <Button.h>
#அந்தர்பாவ <Font.h>
#அந்தர்பாவ <Layout.h>
#அந்தர்பாவ <String.h>
#அந்தர்பாவ <TextView.h>
#அந்தர்பாவ <View.h>
#அந்தர்பாவ <Window.h>

#அந்தர்பாவ <InterfaceDefs.h>
#அந்தர்பாவ <SupportDefs.h>
#அந்தர்பாவ <GraphicsDefs.h>

#அந்தர்பாவ <new>
#அந்தர்பாவ <vector>
#அந்தர்பாவ <algorithm>
#அந்தர்பாவ <memory>

எண்ணிக்கை
{
	G_CLOSE_BUTTON_ID   = -1,
	G_DEFAULT_BUTTON_ID = 0,
	G_MAX_STRING_LENGTH_BYTES = 120
};

வகுப்பு HAIKU_SDL_MessageBox : பொது BAlert
{
	தசம fComputedMessageBoxWidth;

	BTextView *fMessageBoxTextView;

	முழு fCloseButton;
	முழு fDefaultButton;

	தருக்க fCustomColorScheme;
	தருக்க f_There_Is_Long_வரி;
	rgb_color fTextColor;

	மாறிலி எழுத்து *fTitle;
	மாறிலி எழுத்து *HAIKU_SDL_DefTitle;
	மாறிலி எழுத்து *HAIKU_SDL_DefMessage;
	மாறிலி எழுத்து *HAIKU_SDL_DefButton;

	std::vector<மாறிலி SDL_MessageBoxButtonData *> fButtons;

	நிலையான தருக்க
	SortButtonsPredicate(மாறிலி SDL_MessageBoxButtonData *a_Button_இடது,
	                                 மாறிலி SDL_MessageBoxButtonData *a_Button_வலது)
	{
		திரும்பு a_Button_இடது->buttonID < a_Button_வலது->buttonID;
	}

	alert_type
	ConvertMessageBoxType(மாறிலி SDL_MessageBoxFlags aWindowType) மாறிலி
	{
		தேர்வு (aWindowType)
		{
			இயல்பு:
			நிலை SDL_MESSAGEBOX_WARNING:
			{
				திரும்பு B_WARNING_ALERT;
			}
			நிலை SDL_MESSAGEBOX_ERROR:
			{
				திரும்பு B_STOP_ALERT;
			}
			நிலை SDL_MESSAGEBOX_INFORMATION:
			{
				திரும்பு B_INFO_ALERT;
			}
		}
	}

	rgb_color
	ConvertColorType(மாறிலி SDL_MessageBoxColor *aColor) மாறிலி
	{
		rgb_color color = { aColor->r, aColor->g, aColor->b, color.alpha = 255 };
		திரும்பு color;
	}

	int32
	Get_இடது_Panel_Width(வெறுமை) மாறிலி
	{
		// See file "haiku/src/kits/interface/Alert.cpp" for this magic numbers.
		//    IconStripeWidth = 30 * Scale
		//    IconSize = 32 * Scale
		//    Scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16)
		//    RealWidth = (IconStripeWidth * Scale) + (IconSize * Scale)

		int32 scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16);
		திரும்பு (30 * scale) + (32 * scale);
	}

	வெறுமை
	UpdateTextViewWidth(வெறுமை)
	{
		fComputedMessageBoxWidth = fMessageBoxTextView->PreferredSize().Width() + Get_இடது_Panel_Width();
	}

	வெறுமை
	ParseSdlMessageBoxData(மாறிலி SDL_MessageBoxData *aMessageBoxData)
	{
		எனில் (aMessageBoxData == வெற்று) {
			SetTitle(HAIKU_SDL_DefTitle);
			SetMessageText(HAIKU_SDL_DefMessage);
			AddButton(HAIKU_SDL_DefButton);
			திரும்பு;
		}

		எனில் (aMessageBoxData->numbuttons <= 0) {
			AddButton(HAIKU_SDL_DefButton);
		} இல்லையெனில் {
			AddSdlButtons(aMessageBoxData->buttons, aMessageBoxData->numbuttons);
		}

		எனில் (aMessageBoxData->colorScheme != வெற்று) {
			fCustomColorScheme = உண்மை;
			ApplyAndParseColorScheme(aMessageBoxData->colorScheme);
		}

		(aMessageBoxData->title[0]) ?
			SetTitle(aMessageBoxData->title) : SetTitle(HAIKU_SDL_DefTitle);
		(aMessageBoxData->message[0]) ?
			SetMessageText(aMessageBoxData->message) : SetMessageText(HAIKU_SDL_DefMessage);

		SetType(ConvertMessageBoxType(aMessageBoxData->flags));
	}

	வெறுமை
	ApplyAndParseColorScheme(மாறிலி SDL_MessageBoxColorScheme *aColorScheme)
	{
		SetBackgroundColor(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]);
		fTextColor = ConvertColorType(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT]);
		SetButtonColors(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]);
	}

	வெறுமை
	SetButtonColors(மாறிலி SDL_MessageBoxColor *aBorderColor,
	                மாறிலி SDL_MessageBoxColor *aBackgroundColor,
	                மாறிலி SDL_MessageBoxColor *aTextColor,
	                மாறிலி SDL_MessageBoxColor *aSelectedColor)
	{
		எனில் (fCustomColorScheme) {
			int32 மொத்தம்_Buttons = மொத்தம்_Buttons_2();
			க்கு (முழு i = 0; i < மொத்தம்_Buttons; ++i) {
				ButtonAt(i)->SetViewColor(ConvertColorType(aBorderColor));
				ButtonAt(i)->Set_கீழ்_Color(ConvertColorType(aBackgroundColor));

				// This doesn't work. See this why:
				// https://github.com/haiku/haiku/commit/de9c53f8f5008c7b3b0af75d944a628e17f6dffe
				// Let it remain.
				ButtonAt(i)->Set_உயர்வு_Color(ConvertColorType(aTextColor));
			}
		}
		// TODO: Not Implemented.
		// Is it even necessary?!
		(வெறுமை)aSelectedColor;
	}

	வெறுமை
	SetBackgroundColor(மாறிலி SDL_MessageBoxColor *aColor)
	{
		rgb_color background = ConvertColorType(aColor);

		GetLayout()->View()->SetViewColor(background);
		// See file "haiku/src/kits/interface/Alert.cpp", the "TAlertView" is the internal name of the left panel.
		FindView("TAlertView")->SetViewColor(background);
		fMessageBoxTextView->SetViewColor(background);
	}

	தருக்க
	Check_Long_வரிகள்(மாறிலி எழுத்து *aMessage)
	{
		முழு final = 0;

		// This UTF-8 friendly.
		BString message = aMessage;
		int32 length = message.மொத்தம்_Chars();

		க்கு (முழு i = 0, c = 0; i < length; ++i) {
			c++;
			எனில் (*(message.CharAt(i)) == '\n') {
				c = 0;
			}
			எனில் (c > final) {
				final = c;
			}
		}

		திரும்பு (final > G_MAX_STRING_LENGTH_BYTES);
	}

	வெறுமை
	SetMessageText(மாறிலி எழுத்து *aMessage)
	{
		f_There_Is_Long_வரி = Check_Long_வரிகள்(aMessage);
		எனில் (f_There_Is_Long_வரி) {
			fMessageBoxTextView->SetWordWrap(உண்மை);
		}

		rgb_color textColor = ui_color(B_PANEL_TEXT_COLOR);
		எனில் (fCustomColorScheme) {
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
		fMessageBoxTextView->செருகு(aMessage);

		// Be sure to call update width method.
		UpdateTextViewWidth();
	}

	வெறுமை
	AddSdlButtons(மாறிலி SDL_MessageBoxButtonData *aButtons, முழு a_இலக்கம்_Buttons)
	{
		க்கு (முழு i = 0; i < a_இலக்கம்_Buttons; ++i) {
			fButtons.தள்ளு_back(&aButtons[i]);
		}

		std::sort(fButtons.begin(), fButtons.end(), &HAIKU_SDL_MessageBox::SortButtonsPredicate);

		size_t மொத்தம்_Buttons = fButtons.size();
		க்கு (size_t i = 0; i < மொத்தம்_Buttons; ++i) {
			எனில் (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
                fCloseButton = static_cast<முழு>(i);
            }
			எனில் (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
                fDefaultButton = static_cast<முழு>(i);
            }
			AddButton(fButtons[i]->text);
		}

		SetDefaultButton(ButtonAt(fDefaultButton));
	}

பொது:
	explicit
	HAIKU_SDL_MessageBox(மாறிலி SDL_MessageBoxData *aMessageBoxData)
		: BAlert(வெற்று, வெற்று, வெற்று, வெற்று, வெற்று, B_WIDTH_FROM_LABEL, B_WARNING_ALERT),
		  fComputedMessageBoxWidth(0.0f),
		  fCloseButton(G_CLOSE_BUTTON_ID), fDefaultButton(G_DEFAULT_BUTTON_ID),
		  fCustomColorScheme(பொய்), f_There_Is_Long_வரி(பொய்),
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
		fMessageBoxTextView->SetWordWrap(பொய்);
		fMessageBoxTextView->SetStylable(உண்மை);

		ParseSdlMessageBoxData(aMessageBoxData);
	}

	முழு
	GetCloseButtonId(வெறுமை) மாறிலி
	{
		திரும்பு fCloseButton;
	}

	மெய்நிகர்
	~HAIKU_SDL_MessageBox(வெறுமை)
	{
		fButtons.clear();
	}

பாதுகாக்கப்பட்ட:
	மெய்நிகர் வெறுமை
	FrameResized(தசம aNewWidth, தசம aNewHeight)
	{
		எனில் (fComputedMessageBoxWidth > aNewWidth) {
			ResizeTo(fComputedMessageBoxWidth, aNewHeight);
		} இல்லையெனில் {
			BAlert::FrameResized(aNewWidth, aNewHeight);
		}
	}

	மெய்நிகர் வெறுமை
	SetTitle(மாறிலி எழுத்து *aTitle)
	{
		fTitle = aTitle;
		BAlert::SetTitle(aTitle);
	}
};

#ifdef __cplusplus
வெளி "C" {
#endif

தருக்க HAIKU_ShowMessageBox(மாறிலி SDL_MessageBoxData *messageboxdata, முழு *buttonID)
{
	// Initialize button by closed or error value first.
	*buttonID = G_CLOSE_BUTTON_ID;

	// We need to check "be_app" pointer to "NULL". The "messageboxdata->window" pointer isn't appropriate here
	// because it is possible to create a MessageBox from another thread. This fixes the following errors:
	// "You need a valid BApplication object before interacting with the app_server."
	// "2 BApplication objects were created. Only one is allowed."
	std::unique_ptr<BApplication> application;
	எனில் (!be_app) {
		application = std::unique_ptr<BApplication>(புதிய(std::nothrow) BApplication(SDL_signature));
		எனில் (!application) {
			திரும்பு SDL_SetError("Cannot create the BApplication object. Lack of memory?");
		}
	}

	HAIKU_SDL_MessageBox *SDL_MessageBox = புதிய(std::nothrow) HAIKU_SDL_MessageBox(messageboxdata);
	எனில் (!SDL_MessageBox) {
		திரும்பு SDL_SetError("Cannot create the HAIKU_SDL_MessageBox (BAlert inheritor) object. Lack of memory?");
	}
	மாறிலி முழு closeButton = SDL_MessageBox->GetCloseButtonId();
	முழு pushedButton = SDL_MessageBox->Go();

	// The close button is equivalent to pressing Escape.
	எனில் (closeButton != G_CLOSE_BUTTON_ID && pushedButton == G_CLOSE_BUTTON_ID) {
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

	திரும்பு உண்மை;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
