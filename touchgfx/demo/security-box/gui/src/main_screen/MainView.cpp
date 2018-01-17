#include <gui/main_screen/MainView.hpp>

MainView::MainView()
	: 
	checkAccountCallback(this, &MainView::checkAccountCallbackHandler),
	tickCounter_(0),
	hours_(8),
	minutes_(16),
	seconds_(32),
	connect_ani_count_(0)
{
	keyboard.setPosition(23, 35, 662, 412);
	keyboard.setCheckAccountAction(checkAccountCallback);
    add(keyboard);

	mask_.setPosition(32, 44, 640, 392);
	add(mask_);

	digitalClock_.setPosition(185, 440, 150, 30);
	digitalClock_.setTypedText(TypedText(T_DIGITALCLOCK));
	digitalClock_.setColor(Color::getColorFrom24BitRGB(243, 164, 39));
	digitalClock_.setDisplayMode(DigitalClock::DISPLAY_24_HOUR);
	digitalClock_.displayLeadingZeroForHourIndicator(true);
	add(digitalClock_);

	digitalClock_.setTime24Hour(hours_, minutes_, seconds_);	
	
	buttonLock.setVisible(false);
}

void MainView::setupScreen()
{

}

void MainView::tearDownScreen()
{

}

void MainView::handleTickEvent()
{
	tickCounter_++;

	if (tickCounter_ % 60 == 0)
	{
		if (++seconds_ >= 60)
		{
			seconds_ = 0;
			if (++minutes_ >= 60)
			{
				minutes_ = 0;
				if (++hours_ >= 24)
				{
					hours_ = 0;
				}
			}
		}

		digitalClock_.setTime24Hour(hours_, minutes_, seconds_);		

		connect_ani_count_++;

		if (1 == connect_ani_count_) 
		{
			imageConnect.setBitmap(Bitmap(BITMAP_WIFI_ON_0_ID));
			imageConnect.invalidate();
		}
		else if (2 == connect_ani_count_)
		{
			imageConnect.setBitmap(Bitmap(BITMAP_WIFI_ON_1_ID));
			imageConnect.invalidate();
		}
		else if (3 == connect_ani_count_)
		{
			imageConnect.setBitmap(Bitmap(BITMAP_WIFI_ON_2_ID));
			imageConnect.invalidate();
			connect_ani_count_ = -1;
		}
		else if(0 == connect_ani_count_)
		{
			imageConnect.setBitmap(Bitmap(BITMAP_WIFI_ON_ID));
			imageConnect.invalidate();
		}		
	}
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
		uint16_t record[18] = { 0x00 };
		keyboard.getBufferUser(record, 12);                
		record[12] = 2018;
		record[13] = 1;
		record[14] = 2;
		record[15] = hours_;
		record[16] = minutes_;
		record[17] = seconds_;
		presenter->writeLoginRecord(record, 18);
                
		mask_.startInvalidAnimation();
	}
}