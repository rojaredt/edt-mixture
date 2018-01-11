#ifndef KEYBOARD_LAYOUT
#define KEYBOARD_LAYOUT

#include <touchgfx/widgets/Keyboard.hpp>
#include <touchgfx/hal/Types.hpp>
#include <fonts/ApplicationFontProvider.hpp>
#include "BitmapDatabase.hpp"

using namespace touchgfx;

static const float scale = 8.0f; // Base=100px.

static const uint16_t key_english_width = (uint16_t)(10.25f * scale);
static const uint16_t key_english_height = (uint16_t)(11.5 * scale);

/**
 * Array specifying the keys used in the CustomKeyboard.
 */
static const Keyboard::Key keyArray[30] =
{
	{ 1, Rect((uint16_t)(12.0f + 07.70f * scale * 00.0f), (uint16_t)(128.0f + 10.50f * scale * 00.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
	{ 2, Rect((uint16_t)(12.0f + 07.70f * scale * 01.0f), (uint16_t)(128.0f + 10.50f * scale * 00.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
	{ 3, Rect((uint16_t)(12.0f + 07.70f * scale * 02.0f), (uint16_t)(128.0f + 10.50f * scale * 00.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
	{ 4, Rect((uint16_t)(12.0f + 07.70f * scale * 03.0f), (uint16_t)(128.0f + 10.50f * scale * 00.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
	{ 5, Rect((uint16_t)(12.0f + 07.70f * scale * 04.0f), (uint16_t)(128.0f + 10.50f * scale * 00.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
	{ 6, Rect((uint16_t)(12.0f + 07.70f * scale * 05.0f), (uint16_t)(128.0f + 10.50f * scale * 00.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
	{ 7, Rect((uint16_t)(12.0f + 07.70f * scale * 06.0f), (uint16_t)(128.0f + 10.50f * scale * 00.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
	{ 8, Rect((uint16_t)(12.0f + 07.70f * scale * 07.0f), (uint16_t)(128.0f + 10.50f * scale * 00.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
	{ 9, Rect((uint16_t)(12.0f + 07.70f * scale * 08.0f), (uint16_t)(128.0f + 10.50f * scale * 00.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
	{10, Rect((uint16_t)(12.0f + 07.70f * scale * 09.0f), (uint16_t)(128.0f + 10.50f * scale * 00.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
							   	 											  	 
	{12, Rect((uint16_t)(38.0f + 07.70f * scale * 00.0f), (uint16_t)(128.0f + 10.50f * scale * 01.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
	{13, Rect((uint16_t)(38.0f + 07.70f * scale * 01.0f), (uint16_t)(128.0f + 10.50f * scale * 01.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
	{14, Rect((uint16_t)(38.0f + 07.70f * scale * 02.0f), (uint16_t)(128.0f + 10.50f * scale * 01.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
	{15, Rect((uint16_t)(38.0f + 07.70f * scale * 03.0f), (uint16_t)(128.0f + 10.50f * scale * 01.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
	{16, Rect((uint16_t)(38.0f + 07.70f * scale * 04.0f), (uint16_t)(128.0f + 10.50f * scale * 01.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
	{17, Rect((uint16_t)(38.0f + 07.70f * scale * 05.0f), (uint16_t)(128.0f + 10.50f * scale * 01.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
	{18, Rect((uint16_t)(38.0f + 07.70f * scale * 06.0f), (uint16_t)(128.0f + 10.50f * scale * 01.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
	{19, Rect((uint16_t)(38.0f + 07.70f * scale * 07.0f), (uint16_t)(128.0f + 10.50f * scale * 01.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
	{20, Rect((uint16_t)(38.0f + 07.70f * scale * 08.0f), (uint16_t)(128.0f + 10.50f * scale * 01.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
																				 
    {23, Rect((uint16_t)(100.0f + 08.10f * scale * 00.0f), (uint16_t)(128.0f + 10.50f * scale * 02.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},	
	{24, Rect((uint16_t)(100.0f + 08.10f * scale * 01.0f), (uint16_t)(128.0f + 10.50f * scale * 02.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
	{25, Rect((uint16_t)(100.0f + 08.10f * scale * 02.0f), (uint16_t)(128.0f + 10.50f * scale * 02.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
	{26, Rect((uint16_t)(100.0f + 08.10f * scale * 03.0f), (uint16_t)(128.0f + 10.50f * scale * 02.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
	{27, Rect((uint16_t)(100.0f + 08.10f * scale * 04.0f), (uint16_t)(128.0f + 10.50f * scale * 02.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
	{28, Rect((uint16_t)(100.0f + 08.10f * scale * 05.0f), (uint16_t)(128.0f + 10.50f * scale * 02.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
	{29, Rect((uint16_t)(100.0f + 08.10f * scale * 06.0f), (uint16_t)(128.0f + 10.50f * scale * 02.0f), key_english_width, key_english_height), BITMAP_KEYBOARD_KEY_HIGHLIGHT_ENGLISH_ID},
};

static const Keyboard::Key keyArrayNumber[30] =
{
	{ 1 , Rect((uint16_t)(14 + 56 * 2), (uint16_t)(61 * scale) , 104, 80), BITMAP_KEYBOARD_NUMBERPAD_KEY_HIGHLIGHTED_ID },
	{ 2 , Rect((uint16_t)(14 + 56 * 4), (uint16_t)(61 * scale) , 104, 80), BITMAP_KEYBOARD_NUMBERPAD_KEY_HIGHLIGHTED_ID },
	{ 3 , Rect((uint16_t)(14 + 56 * 6), (uint16_t)(61 * scale) , 104, 80), BITMAP_KEYBOARD_NUMBERPAD_KEY_HIGHLIGHTED_ID },
	{ 4 , Rect((uint16_t)(14 + 56 * 2), (uint16_t)(105 * scale), 104, 80), BITMAP_KEYBOARD_NUMBERPAD_KEY_HIGHLIGHTED_ID },
	{ 5 , Rect((uint16_t)(14 + 56 * 4), (uint16_t)(105 * scale), 104, 80), BITMAP_KEYBOARD_NUMBERPAD_KEY_HIGHLIGHTED_ID },
	{ 6 , Rect((uint16_t)(14 + 56 * 6), (uint16_t)(105 * scale), 104, 80), BITMAP_KEYBOARD_NUMBERPAD_KEY_HIGHLIGHTED_ID },
	{ 7 , Rect((uint16_t)(14 + 56 * 2), (uint16_t)(149 * scale), 104, 80), BITMAP_KEYBOARD_NUMBERPAD_KEY_HIGHLIGHTED_ID },
	{ 8 , Rect((uint16_t)(14 + 56 * 4), (uint16_t)(149 * scale), 104, 80), BITMAP_KEYBOARD_NUMBERPAD_KEY_HIGHLIGHTED_ID },
	{ 9 , Rect((uint16_t)(14 + 56 * 6), (uint16_t)(149 * scale), 104, 80), BITMAP_KEYBOARD_NUMBERPAD_KEY_HIGHLIGHTED_ID },
	{ 10, Rect((uint16_t)(14 + 56 * 8), (uint16_t)(105 * scale), 104, 80), BITMAP_KEYBOARD_NUMBERPAD_KEY_HIGHLIGHTED_ID },
};


/**
 * Callback areas for the special buttons on the CustomKeyboard.
 */
static Keyboard::CallbackArea callbackAreasEnglish[2] =
{
	{ Rect((uint16_t)(02.00f * scale), (uint16_t)(38.70f * scale), (uint16_t)(11.87f * scale), (uint16_t)(08.75f * scale)), 0, BITMAP_KEYBOARD_KEY_DELETE_PRESS_ID },  // Enter
	{ Rect((uint16_t)(68.88f * scale), (uint16_t)(38.70f * scale), (uint16_t)(11.87f * scale), (uint16_t)(08.75f * scale)), 0, BITMAP_KEYBOARD_KEY_ENTER_PRESS_ID  },  // Backspace
};

static Keyboard::CallbackArea callbackAreasNumber[2] =
{
	{ Rect((uint16_t)(02.00f * scale), (uint16_t)(38.70f * scale), (uint16_t)(11.87f * scale), (uint16_t)(08.75f * scale)), 0, BITMAP_KEYBOARD_KEY_DELETE_PRESS_ID },  // Enter
    { Rect((uint16_t)(68.88f * scale), (uint16_t)(38.70f * scale), (uint16_t)(11.87f * scale), (uint16_t)(08.75f * scale)), 0, BITMAP_KEYBOARD_KEY_ENTER_PRESS_ID  },  // Backspace
};


/**
 * The layout for the CustomKeyboard.
 */
static const Keyboard::Layout layout =
{
	BITMAP_ENGLISH_KEYBOARD_BACKGROUND_ID,
	keyArray,
	30,
	callbackAreasEnglish,
	2,
	Rect((uint16_t)(03.50f * scale), (uint16_t)(03.00f * scale), (uint16_t)(11 * 28 * scale), (uint16_t)(40 * scale)),
	TypedText(T_ENTEREDTEXT),
#if !defined(USE_BPP) || USE_BPP==16
	0xFFFF,
#elif USE_BPP==24
	0xFFFFFF,
#elif USE_BPP==4
	0xF,
#elif USE_BPP==2
	0x3,
#else
#error Unknown USE_BPP
#endif
	Typography::KEYBOARD,
#if !defined(USE_BPP) || USE_BPP==16
	0xFFFF,
#elif USE_BPP==24
	0xFFFFFF,
#else
#error Unknown USE_BPP
#endif
};

static const Keyboard::Layout layoutNumberpad =
{
	BITMAP_ENGLISH_KEYBOARD_BACKGROUND_ID,
	keyArrayNumber,
	30,
	callbackAreasNumber,
	2,
	Rect((uint16_t)(15 * scale), (uint16_t)(10 * scale), (uint16_t)(11 * 28 * scale), (uint16_t)(40 * scale)),
	TypedText(T_ENTEREDTEXT),
#if !defined(USE_BPP) || USE_BPP==16
	0xFFFF,
#elif USE_BPP==24
	0xFFFFFF,
#elif USE_BPP==4
	0xF,
#elif USE_BPP==2
	0x3,
#else
#error Unknown USE_BPP
#endif
	Typography::KEYBOARD,
	0
};

static const uint16_t shiftCursor[128] =
{
	0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
	0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
	0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
	0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
	0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 27 , 28 , // 49
	27 , 27 , 27 , 27 , 27 , 27 , 27 , 27 , 00 , 00 , 
	00 , 00 , 00 , 00 , 00 , 31 , 31 , 30 , 32 , 28 , // 69
	28 , 33 , 34 , 14 , 27 , 31 , 26 , 41 , 34 , 32 , // 79
	31 , 33 , 32 , 30 , 28 , 32 , 31 , 42 , 30 , 30 ,
	28 , 00 , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
};

#endif