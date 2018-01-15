#ifndef MASK_HPP_
#define MASK_HPP_

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <gui/common/FrontendApplication.hpp>

using namespace touchgfx;

class Mask : public Container
{
public:	
	Mask();
	virtual ~Mask();

	void startAgainAnimation();
	void startInvalidAnimation();
	void startValidAnimation();

protected:	
	MoveAnimator<Image> background_;
	MoveAnimator<Image> mask_result_;
	//MoveAnimator<Image> mask_error_;

	MoveAnimator<TextAreaWithOneWildcard> message_title_;
	Unicode::UnicodeChar message_title_buffer_[10];

private:
	static const int16_t backgraound_begin_x_ = -630;
	static const int16_t backgraound_begin_y_ = 11;
	static const int16_t maskResult_end_x_ = (640 / 2) - (190 / 2);
	static const int16_t maskResult_end_y_ = (392 / 2) - (250 / 2);

	Callback<Mask, const MoveAnimator<Image>& > backgroundMoveInEndedCallback_;
	Callback<Mask, const MoveAnimator<Image>& > backgroundMoveOutEndedCallback_;
	Callback<Mask, const MoveAnimator<Image>& > maskResultMoveInEndedCallback_;
	Callback<Mask, const MoveAnimator<Image>& > maskResultMoveOutEndedCallback_;
	Callback<Mask, const MoveAnimator<TextAreaWithOneWildcard>& > titleMessageMoveInEndedCallback_;
	Callback<Mask, const MoveAnimator<TextAreaWithOneWildcard>& > titleMessageMoveOutEndedCallback_;
	
	void backgroundMoveInEndedHandler(const MoveAnimator<Image>& source);
	void backgroundMoveOutEndedHandler(const MoveAnimator<Image>& source);
	void maskResultMoveInEndedHandler(const MoveAnimator<Image>& source);
	void maskResultMoveOutEndedHandler(const MoveAnimator<Image>& source);
	void titleMessageMoveInEndedHandler(const MoveAnimator<TextAreaWithOneWildcard>& source);
	void titleMessageMoveOutEndedHandler(const MoveAnimator<TextAreaWithOneWildcard>& source);
};

#endif /* MASK_HPP_ */
