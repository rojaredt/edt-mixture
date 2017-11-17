#include <gui/main_screen/MainView.hpp>

MainView::MainView()
	: checkAccountCallback(this, &MainView::checkAccountCallbackHandler)
{
	keyboard.setPosition(32, 44, 640, 392);
	keyboard.setCheckAccountAction(checkAccountCallback);
    add(keyboard);

	//buttonWithIconLog.setBitmaps(Bitmap(BITMAP_LOG_R_ID), Bitmap(BITMAP_LOG_P_ID), Bitmap(BITMAP_LOG_R_ID), Bitmap(BITMAP_LOG_P_ID));
	//buttonWithIconLog.setXY(714, 200);

	//buttonWithIconLog.setAction(buttonClickedCallback);
	//buttonWithIconLog.setVisible(true);
	//buttonWithIconLog.setLabelText(TypedText(T_CONFIG_RESET_TO_FACTORY));
	//buttonWithIconLog.setLabelColor(Color::getColorFrom24BitRGB(192, 192, 192));
	//buttonWithIconLog.setLabelColorPressed(Color::getColorFrom24BitRGB(255, 255, 255));
	
	//buttonWithIconSettings.setBitmaps(Bitmap(BITMAP_SETTINGS_R_ID), Bitmap(BITMAP_SETTINGS_P_ID), Bitmap(BITMAP_SETTINGS_R_ID), Bitmap(BITMAP_SETTINGS_P_ID));
	//buttonWithIconSettings.setXY(716, 298);

	//buttonWithIconInfo.setBitmaps(Bitmap(BITMAP_INFO_R_ID), Bitmap(BITMAP_INFO_P_ID), Bitmap(BITMAP_INFO_R_ID), Bitmap(BITMAP_INFO_P_ID));
	//buttonWithIconInfo.setXY(716, 396);
}

void MainView::setupScreen()
{

}

void MainView::tearDownScreen()
{

}

void MainView::checkAccountCallbackHandler(bool valid)
{

}