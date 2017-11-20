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

	MoveAnimator<TextAreaWithOneWildcard> message_title_;
	Unicode::UnicodeChar message_title_buffer_[10];

private:
	Callback<Mask, const MoveAnimator<Image>& > backgroundMoveInEndedCallback_;

	Callback<Mask, const MoveAnimator<Image>& > backgroundMoveOutEndedCallback_;

	Callback<Mask, const MoveAnimator<TextAreaWithOneWildcard>& > titleMessageMoveInEndedCallback_;

	Callback<Mask, const MoveAnimator<TextAreaWithOneWildcard>& > titleMessageMoveOutEndedCallback_;

	void backgroundMoveInEndedHandler(const MoveAnimator<Image>& source);

	void backgroundMoveOutEndedHandler(const MoveAnimator<Image>& source);

	void titleMessageMoveInEndedHandler(const MoveAnimator<TextAreaWithOneWildcard>& source);

	void titleMessageMoveOutEndedHandler(const MoveAnimator<TextAreaWithOneWildcard>& source);
};

#endif /* MASK_HPP_ */
