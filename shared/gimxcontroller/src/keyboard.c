/*
 Copyright (c) 2018 Daniel Kucner <darkandan@windowslive.com>
 License: GPLv3
 */

#include <keyboard.h>
#include <report.h>
#include <string.h>
#include "../include/controller.h"

static s_axis axes[AXIS_MAX] =
{
  [kb_B1]        = { .name = "1",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_B2]        = { .name = "2",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_B3]        = { .name = "3",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_B4]        = { .name = "4",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_B5]        = { .name = "5",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_B6]        = { .name = "6",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_B7]        = { .name = "7",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_B8]        = { .name = "8",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_B9]        = { .name = "9",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_B0]        = { .name = "0",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BQ]        = { .name = "Q",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BW]        = { .name = "W",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BE]        = { .name = "E",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BR]        = { .name = "R",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BT]        = { .name = "T",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BY]        = { .name = "Y",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BU]        = { .name = "U",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BI]        = { .name = "I",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BO]        = { .name = "O",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BP]        = { .name = "P",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BA]        = { .name = "A",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BS]        = { .name = "S",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BD]        = { .name = "D",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BF]        = { .name = "F",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BG]        = { .name = "G",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BH]        = { .name = "H",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BJ]        = { .name = "J",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BK]        = { .name = "K",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BL]        = { .name = "L",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BZ]        = { .name = "Z",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BX]        = { .name = "X",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BC]        = { .name = "C",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BV]        = { .name = "V",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BB]        = { .name = "B",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BN]        = { .name = "N",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BM]        = { .name = "M",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BBackspace]        = { .name = "Backspace",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BEnter]        = { .name = "Enter",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BSpace]        = { .name = "Space",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BLAlt]        = { .name = "LAlt",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BRAlt]        = { .name = "RAlt",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BLShift]        = { .name = "LShift",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BRShift]        = { .name = "RShift",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BLCtrl]        = { .name = "LCtrl",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BRCtrl]        = { .name = "RCtrl",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BCapsLock]        = { .name = "CapsLock",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BTab]        = { .name = "Tab",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BTilde]        = { .name = "Tilde",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BEsc]        = { .name = "Esc",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BF1]        = { .name = "F1",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BF2]        = { .name = "F2",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BF3]        = { .name = "F3",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BF4]        = { .name = "F4",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BF5]        = { .name = "F5",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BF6]        = { .name = "F6",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BF7]        = { .name = "F7",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BF8]        = { .name = "F8",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BF9]        = { .name = "F9",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BF10]        = { .name = "F10",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BF11]        = { .name = "F11",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BF12]        = { .name = "F12",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BPrintScreen]        = { .name = "PrintScreen",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BPauseBreak]        = { .name = "PauseBreak",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BDelete]        = { .name = "Delete",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BPlus]        = { .name = "Plus",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BMinus]        = { .name = "Minus",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BOpeningBracket]        = { .name = "OpeningBracket",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BClosingBracket]        = { .name = "ClosingBracket",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BBackslash]        = { .name = "Backslash",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BSemicolon]        = { .name = "Semicolon",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BApostrophe]        = { .name = "Apostrophe",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BComma]        = { .name = "Comma",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BDot]        = { .name = "Dot",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BSlash]        = { .name = "Slash",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BLeftArrow]        = { .name = "LeftArrow",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BRightArrow]        = { .name = "RightArrow",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BUpArrow]        = { .name = "UpArrow",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [kb_BDownArrow]        = { .name = "DownArrow",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
};

static s_axis_name_dir axis_name_dirs[] =
{

  {.name = "1",       {.axis = kb_B1,       .props = AXIS_PROP_TOGGLE}},
  {.name = "2",       {.axis = kb_B2,       .props = AXIS_PROP_TOGGLE}},
  {.name = "3",       {.axis = kb_B3,       .props = AXIS_PROP_TOGGLE}},
  {.name = "4",       {.axis = kb_B4,       .props = AXIS_PROP_TOGGLE}},
  {.name = "5",       {.axis = kb_B5,       .props = AXIS_PROP_TOGGLE}},
  {.name = "6",       {.axis = kb_B6,       .props = AXIS_PROP_TOGGLE}},
  {.name = "7",       {.axis = kb_B7,       .props = AXIS_PROP_TOGGLE}},
  {.name = "8",       {.axis = kb_B8,       .props = AXIS_PROP_TOGGLE}},
  {.name = "9",       {.axis = kb_B9,       .props = AXIS_PROP_TOGGLE}},
  {.name = "0",       {.axis = kb_B0,       .props = AXIS_PROP_TOGGLE}},
  {.name = "Q",       {.axis = kb_BQ,       .props = AXIS_PROP_TOGGLE}},
  {.name = "W",       {.axis = kb_BW,       .props = AXIS_PROP_TOGGLE}},
  {.name = "E",       {.axis = kb_BE,       .props = AXIS_PROP_TOGGLE}},
  {.name = "R",       {.axis = kb_BR,       .props = AXIS_PROP_TOGGLE}},
  {.name = "T",       {.axis = kb_BT,       .props = AXIS_PROP_TOGGLE}},
  {.name = "Y",       {.axis = kb_BY,       .props = AXIS_PROP_TOGGLE}},
  {.name = "U",       {.axis = kb_BU,       .props = AXIS_PROP_TOGGLE}},
  {.name = "I",       {.axis = kb_BI,       .props = AXIS_PROP_TOGGLE}},
  {.name = "O",       {.axis = kb_BO,       .props = AXIS_PROP_TOGGLE}},
  {.name = "P",       {.axis = kb_BP,       .props = AXIS_PROP_TOGGLE}},
  {.name = "A",       {.axis = kb_BA,       .props = AXIS_PROP_TOGGLE}},
  {.name = "S",       {.axis = kb_BS,       .props = AXIS_PROP_TOGGLE}},
  {.name = "D",       {.axis = kb_BD,       .props = AXIS_PROP_TOGGLE}},
  {.name = "F",       {.axis = kb_BF,       .props = AXIS_PROP_TOGGLE}},
  {.name = "G",       {.axis = kb_BG,       .props = AXIS_PROP_TOGGLE}},
  {.name = "H",       {.axis = kb_BH,       .props = AXIS_PROP_TOGGLE}},
  {.name = "J",       {.axis = kb_BJ,       .props = AXIS_PROP_TOGGLE}},
  {.name = "K",       {.axis = kb_BK,       .props = AXIS_PROP_TOGGLE}},
  {.name = "L",       {.axis = kb_BL,       .props = AXIS_PROP_TOGGLE}},
  {.name = "Z",       {.axis = kb_BZ,       .props = AXIS_PROP_TOGGLE}},
  {.name = "X",       {.axis = kb_BX,       .props = AXIS_PROP_TOGGLE}},
  {.name = "C",       {.axis = kb_BC,       .props = AXIS_PROP_TOGGLE}},
  {.name = "V",       {.axis = kb_BV,       .props = AXIS_PROP_TOGGLE}},
  {.name = "B",       {.axis = kb_BB,       .props = AXIS_PROP_TOGGLE}},
  {.name = "N",       {.axis = kb_BN,       .props = AXIS_PROP_TOGGLE}},
  {.name = "M",       {.axis = kb_BM,       .props = AXIS_PROP_TOGGLE}},
  {.name = "Backspace",       {.axis = kb_BBackspace,       .props = AXIS_PROP_TOGGLE}},
  {.name = "Enter",       {.axis = kb_BEnter,       .props = AXIS_PROP_TOGGLE}},
  {.name = "Space",       {.axis = kb_BSpace,       .props = AXIS_PROP_TOGGLE}},
  {.name = "LAlt",       {.axis = kb_BLAlt,       .props = AXIS_PROP_TOGGLE}},
  {.name = "RAlt",       {.axis = kb_BRAlt,       .props = AXIS_PROP_TOGGLE}},
  {.name = "LShift",       {.axis = kb_BLShift,       .props = AXIS_PROP_TOGGLE}},
  {.name = "RShift",       {.axis = kb_BRShift,       .props = AXIS_PROP_TOGGLE}},
  {.name = "LCtrl",       {.axis = kb_BLCtrl,       .props = AXIS_PROP_TOGGLE}},
  {.name = "RCtrl",       {.axis = kb_BRCtrl,       .props = AXIS_PROP_TOGGLE}},
  {.name = "CapsLock",       {.axis = kb_BCapsLock,       .props = AXIS_PROP_TOGGLE}},
  {.name = "Tab",       {.axis = kb_BTab,       .props = AXIS_PROP_TOGGLE}},
  {.name = "Tilde",       {.axis = kb_BTilde,       .props = AXIS_PROP_TOGGLE}},
  {.name = "Esc",       {.axis = kb_BEsc,       .props = AXIS_PROP_TOGGLE}},
  {.name = "F1",       {.axis = kb_BF1,       .props = AXIS_PROP_TOGGLE}},
  {.name = "F2",       {.axis = kb_BF2,       .props = AXIS_PROP_TOGGLE}},
  {.name = "F3",       {.axis = kb_BF3,       .props = AXIS_PROP_TOGGLE}},
  {.name = "F4",       {.axis = kb_BF4,       .props = AXIS_PROP_TOGGLE}},
  {.name = "F5",       {.axis = kb_BF5,       .props = AXIS_PROP_TOGGLE}},
  {.name = "F6",       {.axis = kb_BF6,       .props = AXIS_PROP_TOGGLE}},
  {.name = "F7",       {.axis = kb_BF7,       .props = AXIS_PROP_TOGGLE}},
  {.name = "F8",       {.axis = kb_BF8,       .props = AXIS_PROP_TOGGLE}},
  {.name = "F9",       {.axis = kb_BF9,       .props = AXIS_PROP_TOGGLE}},
  {.name = "F10",       {.axis = kb_BF10,       .props = AXIS_PROP_TOGGLE}},
  {.name = "F11",       {.axis = kb_BF11,       .props = AXIS_PROP_TOGGLE}},
  {.name = "F12",       {.axis = kb_BF12,       .props = AXIS_PROP_TOGGLE}},
  {.name = "PrintScreen",       {.axis = kb_BPrintScreen,       .props = AXIS_PROP_TOGGLE}},
  {.name = "PauseBreak",       {.axis = kb_BPauseBreak,       .props = AXIS_PROP_TOGGLE}},
  {.name = "Delete",       {.axis = kb_BDelete,       .props = AXIS_PROP_TOGGLE}},
  {.name = "Plus",       {.axis = kb_BPlus,       .props = AXIS_PROP_TOGGLE}},
  {.name = "Minus",       {.axis = kb_BMinus,       .props = AXIS_PROP_TOGGLE}},
  {.name = "OpeningBracket",       {.axis = kb_BOpeningBracket,       .props = AXIS_PROP_TOGGLE}},
  {.name = "ClosingBracket",       {.axis = kb_BClosingBracket,       .props = AXIS_PROP_TOGGLE}},
  {.name = "Backslash",       {.axis = kb_BBackslash,       .props = AXIS_PROP_TOGGLE}},
  {.name = "Semicolon",       {.axis = kb_BSemicolon,       .props = AXIS_PROP_TOGGLE}},
  {.name = "Apostrophe",       {.axis = kb_BApostrophe,       .props = AXIS_PROP_TOGGLE}},
  {.name = "Comma",       {.axis = kb_BComma,       .props = AXIS_PROP_TOGGLE}},
  {.name = "Dot",       {.axis = kb_BDot,       .props = AXIS_PROP_TOGGLE}},
  {.name = "Slash",       {.axis = kb_BSlash,       .props = AXIS_PROP_TOGGLE}},
  {.name = "LeftArrow",       {.axis = kb_BLeftArrow,       .props = AXIS_PROP_TOGGLE}},
  {.name = "RightArrow",       {.axis = kb_BRightArrow,       .props = AXIS_PROP_TOGGLE}},
  {.name = "UpArrow",       {.axis = kb_BUpArrow,       .props = AXIS_PROP_TOGGLE}},
  {.name = "DownArrow",       {.axis = kb_BDownArrow,       .props = AXIS_PROP_TOGGLE}},
};

static s_report_keyboard default_report =
{
  .Modifier = 0x0000,
  .Reserved = 0x0000,
  .Keys = {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
};

static void init_report(s_report * report)
{
  memcpy(report, &default_report, sizeof(default_report));
}

static void clear_report(s_report_keyboard * kbr)
{
	// Could use memset but this is more readable
	kbr->Keys[0]= 0x00;
	kbr->Keys[1]= 0x00;
	kbr->Keys[2]= 0x00;
	kbr->Keys[3]= 0x00;
	kbr->Keys[4]= 0x00;
	kbr->Keys[5]= 0x00;
	kbr->Modifier = 0x00;
}

// Manage adding keys to avoid accessing index out of array
static void add_key(s_report_keyboard * kbr, int * simulKeyArrayIndex, unsigned char keyCode)
{
	int maxKeyArrayIndex = MAX_SIMULTANEOUS_KEYS -1; // 5
	
	if(*simulKeyArrayIndex > maxKeyArrayIndex)
		return; // Don't add a key to report if there's already maximum amount of simultaneously pressed keys
	
	kbr->Keys[*simulKeyArrayIndex] = keyCode;
	
	++*simulKeyArrayIndex; // Increase index so next key will be added to next index in key array
}

static unsigned int build_report(int axis[AXIS_MAX], s_report_packet report[MAX_REPORTS])
{
  unsigned int index = 0;
  int simulKeyArrayIndex = 0;
  report[index].length = sizeof(s_report_keyboard);
  s_report_keyboard* kbr = &report[index].value.kbr;
  
  clear_report(kbr); // Clear key report so they won't repeat when not pressed
  
  /** KEYBOARD KEYS **/
  if (axis[kb_BQ])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_Q);
  }
  if (axis[kb_BW])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_W);
  }
  if (axis[kb_BE])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_E);
  }
  if (axis[kb_BR])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_R);
  }
  if (axis[kb_BT])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_T);
  }
  if (axis[kb_BY])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_Y);
  }
  if (axis[kb_BU])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_U);
  }
  if (axis[kb_BI])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_I);
  }
  if (axis[kb_BO])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_O);
  }
  if (axis[kb_BP])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_P);
  }
  if (axis[kb_BA])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_A);
  }
  if (axis[kb_BS])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_S);
  }
  if (axis[kb_BD])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_D);
  }
  if (axis[kb_BF])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_F);
  }
  if (axis[kb_BG])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_G);
  }
  if (axis[kb_BH])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_H);
  }
  if (axis[kb_BJ])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_J);
  }
  if (axis[kb_BK])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_K);
  }
  if (axis[kb_BL])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_L);
  }
  if (axis[kb_BZ])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_Z);
  }
  if (axis[kb_BX])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_X);
  }
  if (axis[kb_BC])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_C);
  }
  if (axis[kb_BV])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_V);
  }
  if (axis[kb_BB])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_B);
  }
  if (axis[kb_BN])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_N);
  }
  if (axis[kb_BM])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_M);
  }
  if (axis[kb_BBackspace])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_BACKSPACE);
  }
  if (axis[kb_BEnter])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_ENTER);
  }
  if (axis[kb_BSpace])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_SPACE);
  }
  if (axis[kb_B1])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_1_AND_EXCLAMATION);
  }
  if (axis[kb_B2])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_2_AND_AT);
  }
  if (axis[kb_B3])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_3_AND_HASHMARK);
  }
  if (axis[kb_B4])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_4_AND_DOLLAR);
  }
  if (axis[kb_B5])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_5_AND_PERCENTAGE);
  }
  if (axis[kb_B6])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_6_AND_CARET);
  }
  if (axis[kb_B7])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_7_AND_AMPERSAND);
  }
  if (axis[kb_B8])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_8_AND_ASTERISK);
  }
  if (axis[kb_B9])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_9_AND_OPENING_PARENTHESIS);
  }
  if (axis[kb_B0])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS);
  }
  
  if (axis[kb_BCapsLock])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_CAPS_LOCK);
  }
  if (axis[kb_BTab])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_TAB);
  }
  if (axis[kb_BTilde])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_GRAVE_ACCENT_AND_TILDE);
  }
  if (axis[kb_BEsc])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_ESCAPE);
  }
  if (axis[kb_BF1])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_F1);
  }
  if (axis[kb_BF2])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_F2);
  }
  if (axis[kb_BF3])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_F3);
  }
  if (axis[kb_BF4])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_F4);
  }
  if (axis[kb_BF5])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_F5);
  }
  if (axis[kb_BF6])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_F6);
  }
  if (axis[kb_BF7])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_F7);
  }
  if (axis[kb_BF8])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_F8);
  }
  if (axis[kb_BF9])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_F9);
  }
  if (axis[kb_BF10])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_F10);
  }
  if (axis[kb_BF11])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_F11);
  }
  if (axis[kb_BF12])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_F12);
  }
  if (axis[kb_BPrintScreen])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_PRINT_SCREEN);
  }
  if (axis[kb_BPauseBreak])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_PAUSE);
  }
  if(axis[kb_BDelete])
  {
    add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_DELETE);
  }
  if (axis[kb_BPlus])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_EQUAL_AND_PLUS);
  }
  if (axis[kb_BMinus])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE);
  }
  if (axis[kb_BOpeningBracket])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE);
  }
  if (axis[kb_BClosingBracket])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE);
  }
  if (axis[kb_BBackslash])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_BACKSLASH_AND_PIPE);
  }
  if (axis[kb_BSemicolon])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_SEMICOLON_AND_COLON);
  }
  if (axis[kb_BApostrophe])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE);
  }
  if (axis[kb_BComma])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN);
  }
  if (axis[kb_BDot])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN);
  }
  if (axis[kb_BSlash])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK);
  }
  if (axis[kb_BLeftArrow])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_LEFT_ARROW);
  }
  if (axis[kb_BRightArrow])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_RIGHT_ARROW);
  }
  if (axis[kb_BUpArrow])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_UP_ARROW);
  }
  if (axis[kb_BDownArrow])
  {
	  add_key(kbr, &simulKeyArrayIndex, HID_KEYBOARD_SC_DOWN_ARROW);
  }

  /** MODIFIER KEYS **/
  if(axis[kb_BLAlt])
  {
    kbr->Modifier |= HID_KEYBOARD_MODIFIER_LEFTALT;
  }
  if(axis[kb_BRAlt])
  {
    kbr->Modifier |= HID_KEYBOARD_MODIFIER_RIGHTALT;
  }
  if(axis[kb_BLShift])
  {
    kbr->Modifier |= HID_KEYBOARD_MODIFIER_LEFTSHIFT;
  }
  if(axis[kb_BRShift])
  {
    kbr->Modifier |= HID_KEYBOARD_MODIFIER_RIGHTSHIFT;
  }
  /* BUGGED DONT USE
  if(axis[kb_BLCtrl])
  {
    kbr->Modifier |= HID_KEYBOARD_MODIFIER_LEFTCTRL;
  }
  if(axis[kb_BRCtrl])
  {
    kbr->Modifier |= HID_KEYBOARD_MODIFIER_RIGHTCTRL;
  }*/

  return index;
}

static s_controller controller =
{
  .name = "Keyboard",
  .vid = 0x0000,
  .pid = 0x0000,
  .refresh_period = { .min_value = 5000, .default_value = 5000 }, // Keyboard interval = 0x05
  .auth_required = 0,
  .axes = axes,
  .axis_name_dirs = { .nb = sizeof(axis_name_dirs)/sizeof(*axis_name_dirs), .values = axis_name_dirs },
  .fp_build_report = build_report,
  .fp_init_report = init_report,
};

void keyboard_init(void) __attribute__((constructor));
void keyboard_init(void)
{
  controller_register(C_TYPE_KEYBOARD, &controller);
}

