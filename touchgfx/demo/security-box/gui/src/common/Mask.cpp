#include <gui/common/Mask.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/Color.hpp>

Mask::Mask()
	:
	backgroundMoveInEndedCallback_(this, &Mask::backgroundMoveInEndedHandler),
	backgroundMoveOutEndedCallback_(this, &Mask::backgroundMoveOutEndedHandler),
	maskResultMoveInEndedCallback_(this, &Mask::maskResultMoveInEndedHandler),
	maskResultMoveOutEndedCallback_(this, &Mask::maskResultMoveOutEndedHandler)
{	
	setWidth(620);
	setHeight(370);
	
	background_.setXY(backgraound_begin_x_, backgraound_begin_y_);
	background_.setBitmap(Bitmap(BITMAP_KEYBOARD_MASK_ID));

	mask_result_.setXY((backgraound_begin_x_ / 2 ) - (mask_result_.getWidth()), maskResult_end_y_);
	mask_result_.setBitmap(Bitmap(BITMAP_KEYBOARD_MASK_CORRECT_ID));	
	
	add(background_);	
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

	background_.setMoveAnimationDelay(0);
	mask_result_.setMoveAnimationDelay(0);
	
	background_.startMoveAnimation(10, backgraound_begin_y_, 90, EasingEquations::bounceEaseOut, EasingEquations::linearEaseIn);
	mask_result_.startMoveAnimation(maskResult_end_x_, maskResult_end_y_, 90, EasingEquations::bounceEaseOut, EasingEquations::linearEaseIn);
}

void Mask::startInvalidAnimation()
{
	setTouchable(false);

	mask_result_.setBitmap(Bitmap(BITMAP_KEYBOARD_MASK_ERROR_ID));
	mask_result_.invalidate();

	background_.setMoveAnimationDelay(0);
	mask_result_.setMoveAnimationDelay(0);

	background_.clearMoveAnimationEndedAction();
	mask_result_.clearMoveAnimationEndedAction();

	background_.setMoveAnimationEndedAction(backgroundMoveInEndedCallback_);
	mask_result_.setMoveAnimationEndedAction(maskResultMoveInEndedCallback_);

	background_.startMoveAnimation(10, backgraound_begin_y_, 90, EasingEquations::bounceEaseOut, EasingEquations::linearEaseIn);
	mask_result_.startMoveAnimation(maskResult_end_x_, maskResult_end_y_, 90, EasingEquations::bounceEaseOut, EasingEquations::linearEaseIn);
}

void Mask::startAgainAnimation()
{
	setTouchable(false);

	background_.clearMoveAnimationEndedAction();
	mask_result_.clearMoveAnimationEndedAction();

	background_.setMoveAnimationDelay(0);
	mask_result_.setMoveAnimationDelay(0);
	
	background_.startMoveAnimation(backgraound_begin_x_, backgraound_begin_y_, 30, EasingEquations::linearEaseOut, EasingEquations::linearEaseIn);
	mask_result_.startMoveAnimation((backgraound_begin_x_ / 2) - (mask_result_.getWidth()), maskResult_end_y_, 30, EasingEquations::linearEaseOut, EasingEquations::linearEaseIn);
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