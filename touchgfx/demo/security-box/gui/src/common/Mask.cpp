#include <gui/common/Mask.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/Color.hpp>

Mask::Mask()
	:
	backgroundMoveInEndedCallback_(this, &Mask::backgroundMoveInEndedHandler),
	backgroundMoveOutEndedCallback_(this, &Mask::backgroundMoveOutEndedHandler),
	maskResultMoveInEndedCallback_(this, &Mask::maskResultMoveInEndedHandler),
	maskResultMoveOutEndedCallback_(this, &Mask::maskResultMoveOutEndedHandler),
	titleMessageMoveInEndedCallback_(this, &Mask::titleMessageMoveInEndedHandler),
	titleMessageMoveOutEndedCallback_(this, &Mask::titleMessageMoveOutEndedHandler)
{	
	setWidth(620);
	setHeight(370);
	
	background_.setXY(backgraound_begin_x_, backgraound_begin_y_);
	background_.setBitmap(Bitmap(BITMAP_KEYBOARD_MASK_ID));

	mask_result_.setXY((backgraound_begin_x_ / 2 ) - (mask_result_.getWidth()), maskResult_end_y_);
	mask_result_.setBitmap(Bitmap(BITMAP_KEYBOARD_MASK_CORRECT_ID));

	//mask_error_.setXY((backgraound_begin_x_ / 2) - (mask_result_.getWidth()), backgraound_begin_y_);

	message_title_.setPosition(-360, 165, 400, 60);
	message_title_.setWildcard(message_title_buffer_);
	message_title_.setColor(Color::getColorFrom24BitRGB(255, 255, 255));
	message_title_.setAlpha(200);
	message_title_.setLinespacing(0);
	message_title_.setTypedText(TypedText(T_ENTEREDTEXT));
	
	add(background_);	
	//add(message_title_);
	add(mask_result_);
}

Mask::~Mask()
{
}

void Mask::startValidAnimation()
{
	setTouchable(false);

	mask_result_.setBitmap(Bitmap(BITMAP_KEYBOARD_MASK_CORRECT_ID));
	mask_result_.invalidate();

	message_title_.setVisible(true);
	Unicode::UnicodeChar msg[] = { 0x0043, 0x004F, 0x0052, 0x0052, 0x0045, 0x0043, 0x0054 };
	Unicode::snprintf(message_title_buffer_, 8, "%s", msg);
	message_title_.setPosition(-360, 165, 400, 60);
	message_title_.invalidate();
	
	background_.setMoveAnimationDelay(0);
	mask_result_.setMoveAnimationDelay(0);
	message_title_.setMoveAnimationDelay(0);
	
	background_.startMoveAnimation(10, backgraound_begin_y_, 90, EasingEquations::bounceEaseOut, EasingEquations::linearEaseIn);
	mask_result_.startMoveAnimation(maskResult_end_x_, maskResult_end_y_, 90, EasingEquations::bounceEaseOut, EasingEquations::linearEaseIn);
	message_title_.startMoveAnimation(280, 165, 90, EasingEquations::bounceEaseOut, EasingEquations::linearEaseIn);
}

void Mask::startInvalidAnimation()
{
	setTouchable(false);

	mask_result_.setBitmap(Bitmap(BITMAP_KEYBOARD_MASK_ERROR_ID));
	mask_result_.invalidate();

	message_title_.setVisible(true);
	Unicode::UnicodeChar msg[] = { 0x0045, 0x0052, 0x0052, 0x004F, 0x0052 };
	Unicode::snprintf(message_title_buffer_, 6, "%s", msg);
	message_title_.setPosition(-360, 165, 400, 60);
	message_title_.invalidate();

	background_.setMoveAnimationDelay(0);
	mask_result_.setMoveAnimationDelay(0);
	message_title_.setMoveAnimationDelay(0);

	background_.clearMoveAnimationEndedAction();
	mask_result_.clearMoveAnimationEndedAction();
	message_title_.clearMoveAnimationEndedAction();

	background_.setMoveAnimationEndedAction(backgroundMoveInEndedCallback_);
	mask_result_.setMoveAnimationEndedAction(maskResultMoveInEndedCallback_);
	message_title_.setMoveAnimationEndedAction(titleMessageMoveInEndedCallback_);

	background_.startMoveAnimation(10, backgraound_begin_y_, 90, EasingEquations::bounceEaseOut, EasingEquations::linearEaseIn);
	mask_result_.startMoveAnimation(maskResult_end_x_, maskResult_end_y_, 90, EasingEquations::bounceEaseOut, EasingEquations::linearEaseIn);
	message_title_.startMoveAnimation(280, 165, 90, EasingEquations::bounceEaseOut, EasingEquations::linearEaseIn);
}

void Mask::startAgainAnimation()
{
	setTouchable(false);

	background_.clearMoveAnimationEndedAction();
	mask_result_.clearMoveAnimationEndedAction();
	message_title_.clearMoveAnimationEndedAction();

	background_.setMoveAnimationDelay(0);
	mask_result_.setMoveAnimationDelay(0);
	message_title_.setMoveAnimationDelay(0);
	
	background_.startMoveAnimation(backgraound_begin_x_, backgraound_begin_y_, 30, EasingEquations::linearEaseOut, EasingEquations::linearEaseIn);
	mask_result_.startMoveAnimation((backgraound_begin_x_ / 2) - (mask_result_.getWidth()), maskResult_end_y_, 30, EasingEquations::linearEaseOut, EasingEquations::linearEaseIn);
	message_title_.startMoveAnimation(-360, 165, 30, EasingEquations::linearEaseOut, EasingEquations::linearEaseIn);
}

void Mask::backgroundMoveInEndedHandler(const MoveAnimator<Image>& source)
{
	background_.clearMoveAnimationEndedAction();
	background_.setMoveAnimationEndedAction(backgroundMoveOutEndedCallback_);
	background_.setMoveAnimationDelay(140);
	background_.startMoveAnimation(backgraound_begin_x_, backgraound_begin_y_, 30, EasingEquations::linearEaseOut, EasingEquations::linearEaseIn);
}

void Mask::backgroundMoveOutEndedHandler(const MoveAnimator<Image>& source)
{
}

void Mask::maskResultMoveInEndedHandler(const MoveAnimator<Image>& source)
{
	mask_result_.clearMoveAnimationEndedAction();
	mask_result_.setMoveAnimationEndedAction(backgroundMoveOutEndedCallback_);
	mask_result_.setMoveAnimationDelay(140);
	mask_result_.startMoveAnimation((backgraound_begin_x_ / 2) - (mask_result_.getWidth()), maskResult_end_y_, 30, EasingEquations::linearEaseOut, EasingEquations::linearEaseIn);
}

void Mask::maskResultMoveOutEndedHandler(const MoveAnimator<Image>& source)
{

}

void Mask::titleMessageMoveInEndedHandler(const MoveAnimator<TextAreaWithOneWildcard>& source)
{
	message_title_.clearMoveAnimationEndedAction();
	message_title_.setMoveAnimationEndedAction(titleMessageMoveOutEndedCallback_);
	message_title_.setMoveAnimationDelay(140);
	message_title_.startMoveAnimation(-360, 165, 30, EasingEquations::linearEaseOut, EasingEquations::linearEaseIn);
}

void Mask::titleMessageMoveOutEndedHandler(const MoveAnimator<TextAreaWithOneWildcard>& source)
{
}