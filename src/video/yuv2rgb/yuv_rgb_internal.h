// Copyright 2016 Adrien Descamps
// Distributed under BSD 3-Clause License
#ਅਨ੍ਤਰ੍ਭਾਵ "yuv_rgb.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PRECISION 6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PRECISION_ਗੁਣਕ (1<<PRECISION)

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
	uint8_t y_ਖਿਸਕਾਓ;
	int16_t ਮੈਟ੍ਰਿਕਸ[3][3];
} RGB2YUVParam;
// |Y|   |y_shift|                        |matrix[0][0] matrix[0][1] matrix[0][2]|   |R|
// |U| = |  128  | + 1/PRECISION_FACTOR * |matrix[1][0] matrix[1][1] matrix[1][2]| * |G|
// |V|   |  128  |                        |matrix[2][0] matrix[2][1] matrix[2][2]|   |B|

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
	uint8_t y_ਖਿਸਕਾਓ;
	int16_t y_ਗੁਣਕ;
	int16_t v_r_ਗੁਣਕ;
	int16_t u_g_ਗੁਣਕ;
	int16_t v_g_ਗੁਣਕ;
	int16_t u_b_ਗੁਣਕ;
} YUV2RGBParam;
// |R|                        |y_factor      0       v_r_factor|   |Y-y_shift|
// |G| = 1/PRECISION_FACTOR * |y_factor  u_g_factor  v_g_factor| * |  U-128  |
// |B|                        |y_factor  u_b_factor      0     |   |  V-128  |

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _MSC_VER
#ਹਦਾਇਤ warning(ਧੱਕੋ)
#ਹਦਾਇਤ warning(disable : 26451)
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ V(ਮੁੱਲ) (int16_t)((ਮੁੱਲ*PRECISION_ਗੁਣਕ)+0.5)

// for ITU-T T.871, values can be found in section 7
// for ITU-R BT.601-7 values are derived from equations in sections 2.5.1-2.5.3, assuming RGB is encoded using full range ([0-1]<->[0-255])
// for ITU-R BT.709-6 values are derived from equations in sections 3.2-3.4, assuming RGB is encoded using full range ([0-1]<->[0-255])
// for ITU-R BT.2020 values are assuming RGB is encoded using full 10-bit range ([0-1]<->[0-1023])
// all values are rounded to the fourth decimal

ਸਥਿਰ ਅਚਲ YUV2RGBParam YUV2RGB[] = {
	// ITU-T T.871 (JPEG)
	{/*.y_shift=*/ 0, /*.y_factor=*/ V(1.0), /*.v_r_factor=*/ V(1.402), /*.u_g_factor=*/ -V(0.3441), /*.v_g_factor=*/ -V(0.7141), /*.u_b_factor=*/ V(1.772)},
	// ITU-R BT.601-7
	{/*.y_shift=*/ 16, /*.y_factor=*/ V(1.1644), /*.v_r_factor=*/ V(1.596), /*.u_g_factor=*/ -V(0.3918), /*.v_g_factor=*/ -V(0.813), /*.u_b_factor=*/ V(2.0172)},
	// ITU-R BT.709-6 full range
	{/*.y_shift=*/ 0, /*.y_factor=*/ V(1.0), /*.v_r_factor=*/ V(1.581), /*.u_g_factor=*/ -V(0.1881), /*.v_g_factor=*/ -V(0.47), /*.u_b_factor=*/ V(1.8629)},
	// ITU-R BT.709-6
	{/*.y_shift=*/ 16, /*.y_factor=*/ V(1.1644), /*.v_r_factor=*/ V(1.7927), /*.u_g_factor=*/ -V(0.2132), /*.v_g_factor=*/ -V(0.5329), /*.u_b_factor=*/ V(2.1124)},
	// ITU-R BT.2020 10-bit full range
	{/*.y_shift=*/ 0, /*.y_factor=*/ V(1.0), /*.v_r_factor=*/ V(1.4760), /*.u_g_factor=*/ -V(0.1647), /*.v_g_factor=*/ -V(0.5719), /*.u_b_factor=*/ V(1.8832) }
};

ਸਥਿਰ ਅਚਲ RGB2YUVParam RGB2YUV[] = {
	// ITU-T T.871 (JPEG)
	{/*.y_shift=*/ 0, /*.matrix=*/ {{V(0.299), V(0.587), V(0.114)}, {-V(0.1687), -V(0.3313), V(0.5)}, {V(0.5), -V(0.4187), -V(0.0813)}}},
	// ITU-R BT.601-7
	{/*.y_shift=*/ 16, /*.matrix=*/ {{V(0.2568), V(0.5041), V(0.0979)}, {-V(0.1482), -V(0.291), V(0.4392)}, {V(0.4392), -V(0.3678), -V(0.0714)}}},
	// ITU-R BT.709-6 full range
	{/*.y_shift=*/ 0, /*.matrix=*/ {{V(0.2126), V(0.7152), V(0.0722)}, {-V(0.1141), -V(0.3839), V(0.498)}, {V(0.498), -V(0.4524), -V(0.0457)}}},
	// ITU-R BT.709-6
	{/*.y_shift=*/ 16, /*.matrix=*/ {{V(0.1826), V(0.6142), V(0.062)}, {-V(0.1006), -V(0.3386), V(0.4392)}, {V(0.4392), -V(0.3989), -V(0.0403)}}},
	// ITU-R BT.2020 10-bit full range
	{/*.y_shift=*/ 0, /*.matrix=*/ {{V(0.2627), V(0.6780), V(0.0593)}, {-V(0.1395), -V(0.3600), V(0.4995)}, {V(0.4995), -V(0.4593), -V(0.0402)}}},
};

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _MSC_VER
#ਹਦਾਇਤ warning(ਕੱਢੋ)
#ਜੇ_ਅੰਤ

/* The various layouts of YUV data we support */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ YUV_FORMAT_420	1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ YUV_FORMAT_422  2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ YUV_FORMAT_444  3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ YUV_FORMAT_NV12	4

/* The various formats of RGB pixel that we support */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_FORMAT_RGB565	1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_FORMAT_RGB24	2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_FORMAT_RGBA		3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_FORMAT_BGRA		4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_FORMAT_ARGB		5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_FORMAT_ABGR		6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_FORMAT_XBGR2101010  7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_FORMAT_RGB48	8
