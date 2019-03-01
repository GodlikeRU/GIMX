/*
 Copyright (c) 2018 Daniel Kucner <darkandan@windowslive.com>
 Copyright (c) 2016 Mathieu Laurendeau <mat.lau@laposte.net>
 License: GPLv3
 */

#ifndef DEFS_H_
#define DEFS_H_

#ifdef WIN32
#define GIMX_PACKED __attribute__((gcc_struct, packed))
#else
#define GIMX_PACKED __attribute__((packed))
#endif

#define MAX_AXIS_VALUE_8BITS 255
#define MAX_AXIS_VALUE_10BITS 1023
#define MAX_AXIS_VALUE_14BITS 16383
#define MAX_AXIS_VALUE_16BITS 65535

#define CENTER_AXIS_VALUE_8BITS (MAX_AXIS_VALUE_8BITS/2+1)
#define CENTER_AXIS_VALUE_10BITS (MAX_AXIS_VALUE_10BITS/2+1)
#define CENTER_AXIS_VALUE_14BITS (MAX_AXIS_VALUE_14BITS/2+1)
#define CENTER_AXIS_VALUE_16BITS (MAX_AXIS_VALUE_16BITS/2+1)

typedef enum
{
  C_TYPE_JOYSTICK = 0,
  C_TYPE_360_PAD,
  C_TYPE_SIXAXIS,
  C_TYPE_PS2_PAD,
  C_TYPE_XBOX_PAD,
  C_TYPE_DS4,
  C_TYPE_XONE_PAD,
  C_TYPE_T300RS_PS4,
  C_TYPE_G27_PS3,
  C_TYPE_G29_PS4,
  C_TYPE_DF_PS2,
  C_TYPE_DFP_PS2,
  C_TYPE_GTF_PS2,
  C_TYPE_KEYBOARD,
  // <- add new types here
  C_TYPE_NONE,
  C_TYPE_MAX = C_TYPE_NONE,
} e_controller_type;

typedef enum
{
  rel_axis_0 = 0,
  rel_axis_1,
  rel_axis_2,
  rel_axis_3,
  rel_axis_lstick_x = rel_axis_0,
  rel_axis_lstick_y = rel_axis_1,
  rel_axis_rstick_x = rel_axis_2,
  rel_axis_rstick_y = rel_axis_3,
  rel_axis_4,
  rel_axis_5,
  rel_axis_6,
  rel_axis_7,
  rel_axis_max = rel_axis_7,
  abs_axis_0,
  abs_axis_1,
  abs_axis_2,
  abs_axis_3,
  abs_axis_4,
  abs_axis_5,
  abs_axis_6,
  abs_axis_7,
  abs_axis_8,
  abs_axis_9,
  abs_axis_10,
  abs_axis_11,
  abs_axis_12,
  abs_axis_13,
  abs_axis_14,
  abs_axis_15,
  abs_axis_16,
  abs_axis_17,
  abs_axis_18,
  abs_axis_19,
  abs_axis_20,
  abs_axis_21,
  abs_axis_22,
  abs_axis_23,
  abs_axis_24,
  abs_axis_25,
  abs_axis_26,
  abs_axis_27,
  abs_axis_28,
  abs_axis_29,
  abs_axis_30,
  abs_axis_31,
  abs_axis_32,
  abs_axis_33,
  abs_axis_34,
  abs_axis_35,
  abs_axis_36,
  abs_axis_37,
  abs_axis_38,
  abs_axis_39,
  abs_axis_40,
  abs_axis_41,
  abs_axis_42,
  abs_axis_43,
  abs_axis_44,
  abs_axis_45,
  abs_axis_46,
  abs_axis_47,
  abs_axis_48,
  abs_axis_49,
  abs_axis_50,
  abs_axis_51,
  abs_axis_52,
  abs_axis_53,
  abs_axis_54,
  abs_axis_55,
  abs_axis_56,
  abs_axis_57,
  abs_axis_58,
  abs_axis_59,
  abs_axis_60,
  abs_axis_61,
  abs_axis_62,
  abs_axis_63,
  abs_axis_64,
  abs_axis_65,
  abs_axis_66,
  abs_axis_67,
  abs_axis_68,
  abs_axis_69,
  abs_axis_70,
  abs_axis_71,
  abs_axis_72,
  abs_axis_73,
  abs_axis_74,
  abs_axis_75,
  abs_axis_76,
  abs_axis_77,
  abs_axis_78,
  abs_axis_79,
  abs_axis_80,
  abs_axis_81,
  abs_axis_82,
  abs_axis_83,
  abs_axis_84,
  abs_axis_85,
  abs_axis_max = abs_axis_85,
  AXIS_MAX,
} e_controller_axis_index;

#endif /* DEFS_H_ */
