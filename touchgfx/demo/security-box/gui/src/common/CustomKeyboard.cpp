#include <gui/common/CustomKeyboard.hpp>
#include <touchgfx/hal/HAL.hpp>

CustomKeyboard::CustomKeyboard() : 
	tick(0),
	keyboardNumberpad_(false),
	keyboard(),
    modeBtnTextArea(),
    capslockPressed(this, &CustomKeyboard::capslockPressedHandler),
    backspacePressed(this, &CustomKeyboard::backspacePressedHandler),
	modePressed(this, &CustomKeyboard::modePressedHandler),
	enterUserPressed(this, &CustomKeyboard::enterUserPressedHandler),
	enterPasswordPressed(this, &CustomKeyboard::enterPasswordPressedHandler),
    keyPressed(this, &CustomKeyboard::keyPressedhandler),
    alphaKeys(true),
    uppercaseKeys(false),
    firstCharacterEntry(false)
{
    //Set the callbacks for the callback areas of the keyboard and set its layout.
	layout.callbackAreaArray[0].callback = &backspacePressed;
	layout.callbackAreaArray[1].callback = &enterUserPressed;
	layoutNumberpad.callbackAreaArray[0].callback = &backspacePressed;
	layoutNumberpad.callbackAreaArray[1].callback = &enterPasswordPressed;


	//layout.callbackAreaArray[2].callback = &enterPasswordPressed;
    keyboard.setLayout(&layout);
    keyboard.setKeyListener(keyPressed);
    keyboard.setPosition(0, 0, 640, 392);
    keyboard.setTextIndentation();
    //Allocate the buffer associated with keyboard.
    memset(buffer, 0, sizeof(buffer));
    keyboard.setBuffer(buffer, BUFFER_SIZE);

    uppercaseKeys = true;
    firstCharacterEntry = true;

    modeBtnTextArea.setPosition(5, 196, 56, 40);
    modeBtnTextArea.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));

    setKeyMappingList();

	cursor.setPosition(cursor_, 25, 10, 60);
	cursor.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
	cursor.setAlpha(50);

	message_.setPosition(cursor_ + 20, 20, 410, 60);
	message_.setWildcard(message_buffer_);
	message_.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
	message_.setAlpha(100);
	message_.setLinespacing(0);
	message_.setTypedText(TypedText(T_ENTEREDTEXT));

    add(keyboard);
	add(cursor);
	add(message_);

	Unicode::UnicodeChar list[] = { 0x0055, 0x0053, 0x0045, 0x0052 };
	Unicode::snprintf(message_buffer_, 5, "%s", list);
	message_.invalidate();

	Application::getInstance()->registerTimerWidget(this);
}

void CustomKeyboard::setKeyMappingList()
{
    if (alphaKeys)
    {
        if (uppercaseKeys)
        {
            keyboard.setKeymappingList(&keyMappingListAlphaUpper);
        }
        else
        {
            keyboard.setKeymappingList(&keyMappingListAlphaLower);
        }
    }
    else
    {
        if (uppercaseKeys)
        {
            keyboard.setKeymappingList(&keyMappingListNumUpper);
        }
        else
        {
            keyboard.setKeymappingList(&keyMappingListNumLower);
        }
    }
}

void CustomKeyboard::backspacePressedHandler()
{
    uint16_t pos = keyboard.getBufferPosition();
    if (pos > 0)
    {
        //Delete the previous entry in the buffer and decrement the position.
        buffer[pos - 1] = 0;
        keyboard.setBufferPosition(pos - 1);

        //Change keymappings if we have reached the first position.
        if (1 == pos)
        {
			message_.setVisible(true);
            firstCharacterEntry = true;
        }
    }

	moveCursor();
}

void CustomKeyboard::capslockPressedHandler()
{
    uppercaseKeys = !uppercaseKeys;
    setKeyMappingList();
}

void CustomKeyboard::modePressedHandler()
{
    alphaKeys = !alphaKeys;

    // if we have changed back to alpha and still has no chars in the buffer,
    // we show upper case letters.
    if (firstCharacterEntry && alphaKeys)
    {
        uppercaseKeys = true;
    }
    else
    {
        uppercaseKeys = false;
    }
    setKeyMappingList();
}

void CustomKeyboard::keyPressedhandler(Unicode::UnicodeChar keyChar)
{
    // After the first keypress, the keyboard will shift to lowercase.
    if (firstCharacterEntry && keyChar != 0)
    {
		message_.setVisible(false);
        firstCharacterEntry = false;
        //uppercaseKeys = false;
        setKeyMappingList();
    }

	moveCursor();
}

void CustomKeyboard::enterUserPressedHandler()
{
	HAL::getInstance()->blockCopy(bufferUser, buffer, 15 * sizeof(buffer) / BUFFER_SIZE);

	keyboard.setLayout(&layoutNumberpad);
	keyboard.setKeyListener(keyPressed);
	keyboard.setPosition(0, 0, 640, 392);
	keyboard.setTextIndentation();
	//Allocate the buffer associated with keyboard.
	memset(buffer, 0, sizeof(buffer));
	keyboard.setBuffer(buffer, BUFFER_SIZE);

	modePressedHandler();

	message_.setVisible(true);
	Unicode::UnicodeChar msg[] = { 0x0050, 0x0041, 0x0053, 0x0053, 0x0057, 0x004F, 0x0052, 0x0044 };
	Unicode::snprintf(message_buffer_, 9, "%s", msg);
	message_.invalidate();

	firstCharacterEntry = true;
}

void CustomKeyboard::enterPasswordPressedHandler()
{	
	HAL::getInstance()->blockCopy(bufferPassword, buffer, 15 * sizeof(buffer) / BUFFER_SIZE);
	
	if (checkAccount()) {
		if (checkAccountCallback && checkAccountCallback->isValid())
		{
			checkAccountCallback->execute(true);
		}
	}
	else
	{
		if (checkAccountCallback && checkAccountCallback->isValid())
		{
			checkAccountCallback->execute(false);
		}
	}

	firstCharacterEntry = true;
	uppercaseKeys = true;

	modePressedHandler();

	keyboard.setLayout(&layout);
	keyboard.setKeyListener(keyPressed);	
	keyboard.setPosition(0, 0, 640, 392);
	keyboard.setTextIndentation();
	
	memset(buffer, 0, 15 * sizeof(buffer) / BUFFER_SIZE);
	keyboard.setBuffer(buffer, BUFFER_SIZE);

	Unicode::UnicodeChar list[] = { 0x0055, 0x0053, 0x0045, 0x0052 };
	Unicode::snprintf(message_buffer_, 5, "%s", list);
	message_.setVisible(true);
	message_.invalidate();
}

void CustomKeyboard::setTouchable(bool touch)
{
    Container::setTouchable(touch);
    keyboard.setTouchable(touch);
}

void CustomKeyboard::moveCursor() 
{
	uint16_t pos = keyboard.getBufferPosition();
	uint16_t cursorPosition = cursor_;

	for (int i = 0; i < pos; i++)
	{
		cursorPosition += shiftCursor[buffer[i]];
	}

	cursor.setPosition(cursorPosition, 25, 10, 60);
}

bool CustomKeyboard::checkAccount()
{
	//EDT, 3038
	if (bufferUser[0] == 69 &&
		bufferUser[1] == 68 &&
		bufferUser[2] == 84 &&
		bufferUser[3] == 00 &&
		bufferPassword[0] == 51 &&
		bufferPassword[1] == 48 &&
		bufferPassword[2] == 51 &&
		bufferPassword[3] == 56 && 
		bufferPassword[4] == 00 )
	{
		return true;
	}

	//ROJAR, 3683
	if (bufferUser[0] == 82 &&
		bufferUser[1] == 79 &&
		bufferUser[2] == 74 &&
		bufferUser[3] == 65 &&
		bufferUser[4] == 82 &&
		bufferUser[5] == 00 &&
		bufferPassword[0] == 51 &&
		bufferPassword[1] == 54 &&
		bufferPassword[2] == 56 &&
		bufferPassword[3] == 51 &&
		bufferPassword[4] == 00)
	{
		return true;
	}

	return false;
}

void CustomKeyboard::handleTickEvent()
{
	if ((tick % 30) == 0)
	{
		if (cursor.getAlpha() == 50) 
		{
			cursor.setAlpha(10);
		}
		else
		{
			cursor.setAlpha(50);
		}
		
		cursor.invalidate();
	}

	tick++;
}