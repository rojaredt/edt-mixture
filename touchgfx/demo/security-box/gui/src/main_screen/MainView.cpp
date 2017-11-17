#include <gui/main_screen/MainView.hpp>

MainView::MainView()
	: checkAccountCallback(this, &MainView::checkAccountCallbackHandler)
{
	keyboard.setPosition(32, 44, 640, 392);
	keyboard.setCheckAccountAction(checkAccountCallback);
    add(keyboard);

	buttonLock.setVisible(false);
}

void MainView::setupScreen()
{

}

void MainView::tearDownScreen()
{

}

void MainView::clickButtonLock()
{
	keyboard.openMask();
}

void MainView::checkAccountCallbackHandler(bool valid)
{
	if (valid)
	{
		imageLock.setVisible(false);
		buttonLock.setVisible(true);
		imageLock.invalidate();
		buttonLock.invalidate();
	}
}