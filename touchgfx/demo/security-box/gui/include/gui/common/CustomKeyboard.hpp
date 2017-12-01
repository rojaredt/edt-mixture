#ifndef TGFXKEYBOARD_HPP_
#define TGFXKEYBOARD_HPP_

#include <touchgfx/widgets/Keyboard.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/KeyboardLayout.hpp>
#include <fonts/ApplicationFontProvider.hpp>
#include <gui/common/KeyboardKeyMapping.hpp>

using namespace touchgfx;

/**
 * An alphanumeric keyboard with backspace, space-bar and delete functionality.
 * Keyboard mappings for the keyboard are defined in gui/include/gui/common/KeyboardKeyMapping.hpp.
 * Keyboard layout for the keyboard is defined in gui/include/gui/common/KeyboardLayout.hpp.
 * Please note that the ApplicationFontProvider is initialized and set with the FontManager in main.cpp
 * The fonts and the characters used by the keyboard have to be defined in the assets/texts/texts.xlsx file.
 */
class CustomKeyboard : public Container
{
public:
    CustomKeyboard();
    virtual ~CustomKeyboard() { }

    /*
     * Override setTouchable to also affect the keyboard object inside this
     * CustomKeyboard.
     */
    void setTouchable(bool touch);

	void setCheckAccountAction(GenericCallback<const bool>& callback)
	{
		checkAccountCallback = &callback;
	}

	bool checkAccount();

	virtual void handleTickEvent();

	void getBufferUser(uint16_t* user, uint16_t length);
private:
	static const uint16_t cursor_ = 28;

    /*
     * The size of the buffer that is used by the keyboard.
     * The size determines how much text the keyboard can contain in its textfield.
     */
    static const uint8_t BUFFER_SIZE = 13;

	uint16_t tick;
	bool keyboardNumberpad_;

    /**
     * The keyboard which this CustomKeyboard wraps.
     */
    Keyboard keyboard;

	/*
	 * The cursor for keyboard.
	 */
	Box cursor;

	TextAreaWithOneWildcard message_;
	Unicode::UnicodeChar message_buffer_[10];

    /**
     * The buffer used by the keyboard for text input.
     */
    Unicode::UnicodeChar buffer[BUFFER_SIZE];

	Unicode::UnicodeChar bufferUser[BUFFER_SIZE];
	Unicode::UnicodeChar bufferPassword[BUFFER_SIZE];

    /**
     * Used to display text on top of the button for changing keyboard mode.
     */
    TextArea modeBtnTextArea;

    /**
     * Callback for the capslock button.
     */
    Callback<CustomKeyboard> capslockPressed;

    /**
     * Callback for the backspace button.
     */
    Callback<CustomKeyboard> backspacePressed;

    /**
     * Callback for the keyboard mode button.
     */
    Callback<CustomKeyboard> modePressed;

	Callback<CustomKeyboard> enterUserPressed;
	Callback<CustomKeyboard> enterPasswordPressed;

	GenericCallback<const bool>* checkAccountCallback;

    /**
     * Callback for when keys are pressed on the keyboard.
     */
    Callback<CustomKeyboard, Unicode::UnicodeChar> keyPressed;

    /**
     * True if the keyboard should show alpha keys, false for numeric.
     */
    bool alphaKeys;

    /**
     * True if the keyboard should show upper-case keys.
     */
    bool uppercaseKeys;

    /**
     * True if the input position in the text field, and hence the buffer, is at the beginning.
     */
    bool firstCharacterEntry;

    /*
     * Sets the correct key mappings of the keyboard according to alpha/numeric and upper-case/lower-case.
     */
    void setKeyMappingList();

    /**
     * Callback handler for the backspace button.
     */
    void backspacePressedHandler();

    /**
     * Callback handler for the caps-lock button.
     */
    void capslockPressedHandler();

    /**
     * Callback handler for the mode button.
     */
    void modePressedHandler();

	void enterUserPressedHandler();
	void enterPasswordPressedHandler();

    /**
     * Callback handler for key presses.
     * @param keyChar The UnicodeChar for the key that was pressed.
     */
    void keyPressedhandler(Unicode::UnicodeChar keyChar);

	void moveCursor();
};

#endif /* TGFXKEYBOARD_HPP_ */
