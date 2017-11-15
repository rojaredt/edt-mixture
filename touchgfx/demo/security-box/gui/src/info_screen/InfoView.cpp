#include <gui/info_screen/InfoView.hpp>

InfoView::InfoView()
{
	
}

void InfoView::setupScreen()
{
	textAreaInfoIntro.setWideTextAction(WIDE_TEXT_CHARWRAP);
	textAreaInfoIntro.resizeHeightToCurrentText();
}

void InfoView::tearDownScreen()
{

}
