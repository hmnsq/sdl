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

#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU


// For application signature.
#અન્તર્ભાવ "../../core/haiku/SDL_BeApp.h"

#અન્તર્ભાવ <Alert.h>
#અન્તર્ભાવ <Application.h>
#અન્તર્ભાવ <Button.h>
#અન્તર્ભાવ <Font.h>
#અન્તર્ભાવ <Layout.h>
#અન્તર્ભાવ <String.h>
#અન્તર્ભાવ <TextView.h>
#અન્તર્ભાવ <View.h>
#અન્તર્ભાવ <Window.h>

#અન્તર્ભાવ <InterfaceDefs.h>
#અન્તર્ભાવ <SupportDefs.h>
#અન્તર્ભાવ <GraphicsDefs.h>

#અન્તર્ભાવ <new>
#અન્તર્ભાવ <vector>
#અન્તર્ભાવ <algorithm>
#અન્તર્ભાવ <memory>

ગણના
{
	G_CLOSE_BUTTON_ID   = -1,
	G_DEFAULT_BUTTON_ID = 0,
	G_MAX_STRING_LENGTH_BYTES = 120
};

વર્ગ HAIKU_SDL_MessageBox : જાહેર BAlert
{
	દશાંશ fComputedMessageBoxWidth;

	BTextView *fMessageBoxTextView;

	પૂર્ણાંક fCloseButton;
	પૂર્ણાંક fDefaultButton;

	તાર્કિક fCustomColorScheme;
	તાર્કિક f_There_Is_Long_લીટી;
	rgb_color fTextColor;

	અચલ અક્ષર *fTitle;
	અચલ અક્ષર *HAIKU_SDL_DefTitle;
	અચલ અક્ષર *HAIKU_SDL_DefMessage;
	અચલ અક્ષર *HAIKU_SDL_DefButton;

	std::vector<અચલ SDL_MessageBoxButtonData *> fButtons;

	સ્થિર તાર્કિક
	SortButtonsPredicate(અચલ SDL_MessageBoxButtonData *a_Button_ડાબું,
	                                 અચલ SDL_MessageBoxButtonData *a_Button_જમણું)
	{
		પાછા a_Button_ડાબું->buttonID < a_Button_જમણું->buttonID;
	}

	alert_type
	ConvertMessageBoxType(અચલ SDL_MessageBoxFlags aWindowType) અચલ
	{
		પસંદગી (aWindowType)
		{
			મૂળભૂત:
			સ્થિતિ SDL_MESSAGEBOX_WARNING:
			{
				પાછા B_WARNING_ALERT;
			}
			સ્થિતિ SDL_MESSAGEBOX_ERROR:
			{
				પાછા B_STOP_ALERT;
			}
			સ્થિતિ SDL_MESSAGEBOX_INFORMATION:
			{
				પાછા B_INFO_ALERT;
			}
		}
	}

	rgb_color
	ConvertColorType(અચલ SDL_MessageBoxColor *aColor) અચલ
	{
		rgb_color color = { aColor->r, aColor->g, aColor->b, color.alpha = 255 };
		પાછા color;
	}

	int32
	Get_ડાબું_Panel_Width(શૂન્ય) અચલ
	{
		// See file "haiku/src/kits/interface/Alert.cpp" for this magic numbers.
		//    IconStripeWidth = 30 * Scale
		//    IconSize = 32 * Scale
		//    Scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16)
		//    RealWidth = (IconStripeWidth * Scale) + (IconSize * Scale)

		int32 scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16);
		પાછા (30 * scale) + (32 * scale);
	}

	શૂન્ય
	UpdateTextViewWidth(શૂન્ય)
	{
		fComputedMessageBoxWidth = fMessageBoxTextView->PreferredSize().Width() + Get_ડાબું_Panel_Width();
	}

	શૂન્ય
	ParseSdlMessageBoxData(અચલ SDL_MessageBoxData *aMessageBoxData)
	{
		જો (aMessageBoxData == ખાલી) {
			SetTitle(HAIKU_SDL_DefTitle);
			SetMessageText(HAIKU_SDL_DefMessage);
			AddButton(HAIKU_SDL_DefButton);
			પાછા;
		}

		જો (aMessageBoxData->numbuttons <= 0) {
			AddButton(HAIKU_SDL_DefButton);
		} નહીંતર {
			AddSdlButtons(aMessageBoxData->buttons, aMessageBoxData->numbuttons);
		}

		જો (aMessageBoxData->colorScheme != ખાલી) {
			fCustomColorScheme = સાચું;
			ApplyAndParseColorScheme(aMessageBoxData->colorScheme);
		}

		(aMessageBoxData->title[0]) ?
			SetTitle(aMessageBoxData->title) : SetTitle(HAIKU_SDL_DefTitle);
		(aMessageBoxData->message[0]) ?
			SetMessageText(aMessageBoxData->message) : SetMessageText(HAIKU_SDL_DefMessage);

		SetType(ConvertMessageBoxType(aMessageBoxData->flags));
	}

	શૂન્ય
	ApplyAndParseColorScheme(અચલ SDL_MessageBoxColorScheme *aColorScheme)
	{
		SetBackgroundColor(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]);
		fTextColor = ConvertColorType(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT]);
		SetButtonColors(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]);
	}

	શૂન્ય
	SetButtonColors(અચલ SDL_MessageBoxColor *aBorderColor,
	                અચલ SDL_MessageBoxColor *aBackgroundColor,
	                અચલ SDL_MessageBoxColor *aTextColor,
	                અચલ SDL_MessageBoxColor *aSelectedColor)
	{
		જો (fCustomColorScheme) {
			int32 ગણતરી_Buttons = ગણતરી_Buttons_2();
			માટે (પૂર્ણાંક i = 0; i < ગણતરી_Buttons; ++i) {
				ButtonAt(i)->SetViewColor(ConvertColorType(aBorderColor));
				ButtonAt(i)->Set_નીચલું_Color(ConvertColorType(aBackgroundColor));

				// This doesn't work. See this why:
				// https://github.com/haiku/haiku/commit/de9c53f8f5008c7b3b0af75d944a628e17f6dffe
				// Let it remain.
				ButtonAt(i)->Set_ઉપલું_Color(ConvertColorType(aTextColor));
			}
		}
		// TODO: Not Implemented.
		// Is it even necessary?!
		(શૂન્ય)aSelectedColor;
	}

	શૂન્ય
	SetBackgroundColor(અચલ SDL_MessageBoxColor *aColor)
	{
		rgb_color background = ConvertColorType(aColor);

		GetLayout()->View()->SetViewColor(background);
		// See file "haiku/src/kits/interface/Alert.cpp", the "TAlertView" is the internal name of the left panel.
		FindView("TAlertView")->SetViewColor(background);
		fMessageBoxTextView->SetViewColor(background);
	}

	તાર્કિક
	Check_Long_લીટીઓ(અચલ અક્ષર *aMessage)
	{
		પૂર્ણાંક final = 0;

		// This UTF-8 friendly.
		BString message = aMessage;
		int32 length = message.ગણતરી_Chars();

		માટે (પૂર્ણાંક i = 0, c = 0; i < length; ++i) {
			c++;
			જો (*(message.CharAt(i)) == '\n') {
				c = 0;
			}
			જો (c > final) {
				final = c;
			}
		}

		પાછા (final > G_MAX_STRING_LENGTH_BYTES);
	}

	શૂન્ય
	SetMessageText(અચલ અક્ષર *aMessage)
	{
		f_There_Is_Long_લીટી = Check_Long_લીટીઓ(aMessage);
		જો (f_There_Is_Long_લીટી) {
			fMessageBoxTextView->SetWordWrap(સાચું);
		}

		rgb_color textColor = ui_color(B_PANEL_TEXT_COLOR);
		જો (fCustomColorScheme) {
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
		fMessageBoxTextView->ઉમેરો(aMessage);

		// Be sure to call update width method.
		UpdateTextViewWidth();
	}

	શૂન્ય
	AddSdlButtons(અચલ SDL_MessageBoxButtonData *aButtons, પૂર્ણાંક a_અંક_Buttons)
	{
		માટે (પૂર્ણાંક i = 0; i < a_અંક_Buttons; ++i) {
			fButtons.ધકેલો_back(&aButtons[i]);
		}

		std::sort(fButtons.begin(), fButtons.end(), &HAIKU_SDL_MessageBox::SortButtonsPredicate);

		size_t ગણતરી_Buttons = fButtons.size();
		માટે (size_t i = 0; i < ગણતરી_Buttons; ++i) {
			જો (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
                fCloseButton = static_cast<પૂર્ણાંક>(i);
            }
			જો (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
                fDefaultButton = static_cast<પૂર્ણાંક>(i);
            }
			AddButton(fButtons[i]->text);
		}

		SetDefaultButton(ButtonAt(fDefaultButton));
	}

જાહેર:
	explicit
	HAIKU_SDL_MessageBox(અચલ SDL_MessageBoxData *aMessageBoxData)
		: BAlert(ખાલી, ખાલી, ખાલી, ખાલી, ખાલી, B_WIDTH_FROM_LABEL, B_WARNING_ALERT),
		  fComputedMessageBoxWidth(0.0f),
		  fCloseButton(G_CLOSE_BUTTON_ID), fDefaultButton(G_DEFAULT_BUTTON_ID),
		  fCustomColorScheme(ખોટું), f_There_Is_Long_લીટી(ખોટું),
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
		fMessageBoxTextView->SetWordWrap(ખોટું);
		fMessageBoxTextView->SetStylable(સાચું);

		ParseSdlMessageBoxData(aMessageBoxData);
	}

	પૂર્ણાંક
	GetCloseButtonId(શૂન્ય) અચલ
	{
		પાછા fCloseButton;
	}

	આભાસી
	~HAIKU_SDL_MessageBox(શૂન્ય)
	{
		fButtons.clear();
	}

સુરક્ષિત:
	આભાસી શૂન્ય
	FrameResized(દશાંશ aNewWidth, દશાંશ aNewHeight)
	{
		જો (fComputedMessageBoxWidth > aNewWidth) {
			ResizeTo(fComputedMessageBoxWidth, aNewHeight);
		} નહીંતર {
			BAlert::FrameResized(aNewWidth, aNewHeight);
		}
	}

	આભાસી શૂન્ય
	SetTitle(અચલ અક્ષર *aTitle)
	{
		fTitle = aTitle;
		BAlert::SetTitle(aTitle);
	}
};

#ifdef __cplusplus
બાહ્ય "C" {
#endif

તાર્કિક HAIKU_ShowMessageBox(અચલ SDL_MessageBoxData *messageboxdata, પૂર્ણાંક *buttonID)
{
	// Initialize button by closed or error value first.
	*buttonID = G_CLOSE_BUTTON_ID;

	// We need to check "be_app" pointer to "NULL". The "messageboxdata->window" pointer isn't appropriate here
	// because it is possible to create a MessageBox from another thread. This fixes the following errors:
	// "You need a valid BApplication object before interacting with the app_server."
	// "2 BApplication objects were created. Only one is allowed."
	std::unique_ptr<BApplication> application;
	જો (!be_app) {
		application = std::unique_ptr<BApplication>(નવું(std::nothrow) BApplication(SDL_signature));
		જો (!application) {
			પાછા SDL_SetError("Cannot create the BApplication object. Lack of memory?");
		}
	}

	HAIKU_SDL_MessageBox *SDL_MessageBox = નવું(std::nothrow) HAIKU_SDL_MessageBox(messageboxdata);
	જો (!SDL_MessageBox) {
		પાછા SDL_SetError("Cannot create the HAIKU_SDL_MessageBox (BAlert inheritor) object. Lack of memory?");
	}
	અચલ પૂર્ણાંક closeButton = SDL_MessageBox->GetCloseButtonId();
	પૂર્ણાંક pushedButton = SDL_MessageBox->Go();

	// The close button is equivalent to pressing Escape.
	જો (closeButton != G_CLOSE_BUTTON_ID && pushedButton == G_CLOSE_BUTTON_ID) {
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

	પાછા સાચું;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
