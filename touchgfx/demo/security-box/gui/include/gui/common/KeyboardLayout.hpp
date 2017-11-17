#ifndef KEYBOARD_LAYOUT
#define KEYBOARD_LAYOUT

#include <touchgfx/widgets/Keyboard.hpp>
#include <touchgfx/hal/Types.hpp>
#include <fonts/ApplicationFontProvider.hpp>
#include "BitmapDatabase.hpp"

using namespace touchgfx;

static const float scale = 2.0;

/**
 * Array specifying the keys used in the CustomKeyboard.
 */
static const Keyboard::Key keyArray[30] =
{
	{ 1, Rect((uint16_t)(14         ), (uint16_t)(61 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},
	{ 2, Rect((uint16_t)(14 + 56    ), (uint16_t)(61 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},
	{ 3, Rect((uint16_t)(14 + 56 * 2), (uint16_t)(61 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},
	{ 4, Rect((uint16_t)(14 + 56 * 3), (uint16_t)(61 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},
	{ 5, Rect((uint16_t)(14 + 56 * 4), (uint16_t)(61 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},
	{ 6, Rect((uint16_t)(14 + 56 * 5), (uint16_t)(61 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},
	{ 7, Rect((uint16_t)(14 + 56 * 6), (uint16_t)(61 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},
	{ 8, Rect((uint16_t)(14 + 56 * 7), (uint16_t)(61 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},
	{ 9, Rect((uint16_t)(14 + 56 * 8), (uint16_t)(61 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},
	{10, Rect((uint16_t)(14 + 56 * 9), (uint16_t)(61 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},

	{12, Rect((uint16_t)(35 * scale)                 , (uint16_t)(105 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},
	{13, Rect((uint16_t)(35 * scale + 28 * 1 * scale), (uint16_t)(105 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},
	{14, Rect((uint16_t)(35 * scale + 28 * 2 * scale), (uint16_t)(105 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},
	{15, Rect((uint16_t)(35 * scale + 28 * 3 * scale), (uint16_t)(105 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},
	{16, Rect((uint16_t)(35 * scale + 28 * 4 * scale), (uint16_t)(105 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},
	{17, Rect((uint16_t)(35 * scale + 28 * 5 * scale), (uint16_t)(105 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},
	{18, Rect((uint16_t)(35 * scale + 28 * 6 * scale), (uint16_t)(105 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},
	{19, Rect((uint16_t)(35 * scale + 28 * 7 * scale), (uint16_t)(105 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},
	{20, Rect((uint16_t)(35 * scale + 28 * 8 * scale), (uint16_t)(105 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},

	{23, Rect((uint16_t)(63 * scale)                 , (uint16_t)(149 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},
	{24, Rect((uint16_t)(63 * scale + 28 * 1 * scale), (uint16_t)(149 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},
	{25, Rect((uint16_t)(63 * scale + 28 * 2 * scale), (uint16_t)(149 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},
	{26, Rect((uint16_t)(63 * scale + 28 * 3 * scale), (uint16_t)(149 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},
	{27, Rect((uint16_t)(63 * scale + 28 * 4 * scale), (uint16_t)(149 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},
	{28, Rect((uint16_t)(63 * scale + 28 * 5 * scale), (uint16_t)(149 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},
	{29, Rect((uint16_t)(63 * scale + 28 * 6 * scale), (uint16_t)(149 * scale), (uint16_t)(26 * scale), (uint16_t)(40 * scale)), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_52X80_ID},
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
static Keyboard::CallbackArea callbackAreas[2] =
{
	{ Rect((uint16_t)(35 * scale + 28 * 8 * scale - 2), (uint16_t)(149 * scale), (uint16_t)(56 * scale), (uint16_t)(40 * scale)), 0, BITMAP_KEYBOARD_KEY_DELETE_HIGHLIGHTED_112X80_ID},  // backspace
	{ Rect((uint16_t)(5 * scale)                      , (uint16_t)(149 * scale), (uint16_t)(56 * scale), (uint16_t)(40 * scale)), 0, BITMAP_KEYBOARD_KEY_SHIFT_HIGHLIGHTED_112X80_ID },  // enter user
//	{ Rect((uint16_t)(5 * scale)                      , (uint16_t)(149 * scale), (uint16_t)(56 * scale), (uint16_t)(40 * scale)), 0, BITMAP_KEYBOARD_KEY_SHIFT_HIGHLIGHTED_112X80_ID },  // enter password
};

static Keyboard::CallbackArea callbackAreasNumber[2] =
{
	{ Rect((uint16_t)(35 * scale + 28 * 8 * scale - 2), (uint16_t)(149 * scale), (uint16_t)(56 * scale), (uint16_t)(40 * scale)), 0, BITMAP_KEYBOARD_KEY_DELETE_HIGHLIGHTED_112X80_ID },  // backspace
//	{ Rect((uint16_t)(5 * scale)                      , (uint16_t)(149 * scale), (uint16_t)(56 * scale), (uint16_t)(40 * scale)), 0, BITMAP_KEYBOARD_KEY_SHIFT_HIGHLIGHTED_112X80_ID },  // enter user
	{ Rect((uint16_t)(5 * scale)                      , (uint16_t)(149 * scale), (uint16_t)(56 * scale), (uint16_t)(40 * scale)), 0, BITMAP_KEYBOARD_KEY_SHIFT_HIGHLIGHTED_112X80_ID },  // enter password
};


/**
 * The layout for the CustomKeyboard.
 */
static const Keyboard::Layout layout =
{
	BITMAP_KEYBOARD_BACKGROUND_640X392_ID,
	keyArray,
	30,
	callbackAreas,
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

static const Keyboard::Layout layoutNumberpad =
{
	BITMAP_KEYBOARD_NUMBERPAD_BACKGROUND_ID,
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