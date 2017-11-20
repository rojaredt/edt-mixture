#include <gui/main_screen/MainView.hpp>

MainView::MainView()
	: checkAccountCallback(this, &MainView::checkAccountCallbackHandler)
{
	keyboard.setPosition(32, 44, 640, 392);
	keyboard.setCheckAccountAction(checkAccountCallback);
    add(keyboard);

	mask_.setPosition(32, 44, 640, 392);
	add(mask_);

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
	buttonLock.setVisible(false);
	imageLock.setVisible(true);
	buttonLock.invalidate();
	imageLock.invalidate();
	mask_.startAgainAnimation();
}

void MainView::checkAccountCallbackHandler(bool valid)
{
	if (valid)
	{
		mask_.startValidAnimation();

		imageLock.setVisible(false);
		buttonLock.setVisible(true);
		imageLock.invalidate();
		buttonLock.invalidate();
	}
	else
	{
		mask_.startInvalidAnimation();
	}
}