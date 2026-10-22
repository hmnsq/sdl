// Copyright 2016 Adrien Descamps
// Distributed under BSD 3-Clause License

/* You need to define the following macros before including this file:
	STD_FUNCTION_NAME
	YUV_FORMAT
	RGB_FORMAT
*/

#اگر RGB_FORMAT == RGB_FORMAT_RGB565

#تعریف_کرو PACK_PIXEL(rgb_ptr) \
	*(Uint16 *)rgb_ptr = \
		((((Uint16)clampU8(y_tmp+r_tmp)) << 8 ) & 0xF800) | \
		((((Uint16)clampU8(y_tmp+g_tmp)) << 3) & 0x07E0) | \
		(((Uint16)clampU8(y_tmp+b_tmp)) >> 3); \
	rgb_ptr += 2

#وگرنہ_اگر RGB_FORMAT == RGB_FORMAT_RGB24

#تعریف_کرو PACK_PIXEL(rgb_ptr) \
	rgb_ptr[0] = clampU8(y_tmp+r_tmp); \
	rgb_ptr[1] = clampU8(y_tmp+g_tmp); \
	rgb_ptr[2] = clampU8(y_tmp+b_tmp); \
	rgb_ptr += 3

#وگرنہ_اگر RGB_FORMAT == RGB_FORMAT_RGBA

#تعریف_کرو PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 24) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 8) | \
		0x000000FF; \
	rgb_ptr += 4

#وگرنہ_اگر RGB_FORMAT == RGB_FORMAT_BGRA

#تعریف_کرو PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 24) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 8) | \
		0x000000FF; \
	rgb_ptr += 4

#وگرنہ_اگر RGB_FORMAT == RGB_FORMAT_ARGB

#تعریف_کرو PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xFF000000 | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 8) | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 0); \
	rgb_ptr += 4

#وگرنہ_اگر RGB_FORMAT == RGB_FORMAT_ABGR

#تعریف_کرو PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xFF000000 | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 8) | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 0); \
	rgb_ptr += 4

#وگرنہ_اگر RGB_FORMAT == RGB_FORMAT_XBGR2101010

#تعریف_کرو PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xC0000000 | \
		(((Uint32)clamp10(y_tmp+b_tmp)) << 20) | \
		(((Uint32)clamp10(y_tmp+g_tmp)) << 10) | \
		(((Uint32)clamp10(y_tmp+r_tmp)) << 0); \
	rgb_ptr += 4

#وگرنہ_اگر RGB_FORMAT == RGB_FORMAT_RGB48

#تعریف_کرو PACK_PIXEL(rgb_ptr) \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + r_tmp); \
	rgb_ptr += حجم(Uint16);				   \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + g_tmp); \
	rgb_ptr += حجم(Uint16);				   \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + b_tmp); \
	rgb_ptr += حجم(Uint16)

#ورنہ
#غلطی PACK_PIXEL unimplemented
#اگر_ختم


#اگر_تعریف_شدہ _MSC_VER /* Visual Studio analyzer can't tell that we're building this with different constants */
#ہدایت warning(ڈالو)
#ہدایت warning(disable : 6239)
#اگر_ختم

#تعریف_منسوخ YUV_TYPE
#اگر YUV_بٹ > 8
#تعریف_کرو YUV_TYPE	uint16_t
#ورنہ
#تعریف_کرو YUV_TYPE	uint8_t
#اگر_ختم
#تعریف_منسوخ UV_انحراف
#تعریف_کرو UV_انحراف	(1 << ((YUV_بٹ)-1))

#تعریف_منسوخ GET
#اگر YUV_بٹ == 10
#تعریف_کرو GET(X)	((X) >> 6)
#ورنہ
#تعریف_کرو GET(X)	(X)
#اگر_ختم

خالی STD_FUNCTION_NAME(
	uint32_t چوڑائی, uint32_t اونچائی,
	ثابت YUV_TYPE *Y, ثابت YUV_TYPE *U, ثابت YUV_TYPE *V, uint32_t Y_stride, uint32_t UV_stride,
	uint8_t *RGB, uint32_t RGB_stride,
	YCbCrType yuv_type)
{
	ثابت YUV2RGBParam *ثابت param = &(YUV2RGB[yuv_type]);
#اگر YUV_FORMAT == YUV_FORMAT_420
	#تعریف_کرو y_pixel_stride 1
	#تعریف_کرو uv_pixel_stride 1
	#تعریف_کرو uv_x_sample_interval 2
	#تعریف_کرو uv_y_sample_interval 2
#وگرنہ_اگر YUV_FORMAT == YUV_FORMAT_422
	#تعریف_کرو y_pixel_stride 2
	#تعریف_کرو uv_pixel_stride 4
	#تعریف_کرو uv_x_sample_interval 2
	#تعریف_کرو uv_y_sample_interval 1
#وگرنہ_اگر YUV_FORMAT == YUV_FORMAT_444
	#تعریف_کرو y_pixel_stride 1
	#تعریف_کرو uv_pixel_stride 1
	#تعریف_کرو uv_x_sample_interval 1
	#تعریف_کرو uv_y_sample_interval 1
#وگرنہ_اگر YUV_FORMAT == YUV_FORMAT_NV12
	#تعریف_کرو y_pixel_stride 1
	#تعریف_کرو uv_pixel_stride 2
	#تعریف_کرو uv_x_sample_interval 2
	#تعریف_کرو uv_y_sample_interval 2
#اگر_ختم

	Y_stride /= حجم(YUV_TYPE);
	UV_stride /= حجم(YUV_TYPE);

	uint32_t x, y;
	برائے(y=0; y<(اونچائی-(uv_y_sample_interval-1)); y+=uv_y_sample_interval)
	{
		ثابت YUV_TYPE *y_ptr1=Y+y*Y_stride,
			*u_ptr=U+(y/uv_y_sample_interval)*UV_stride,
			*v_ptr=V+(y/uv_y_sample_interval)*UV_stride;

		#اگر uv_y_sample_interval > 1
		ثابت YUV_TYPE *y_ptr2=Y+(y+1)*Y_stride;
		#اگر_ختم

		uint8_t *rgb_ptr1=RGB+y*RGB_stride;

		#اگر uv_y_sample_interval > 1
		uint8_t *rgb_ptr2=RGB+(y+1)*RGB_stride;
		#اگر_ختم

		برائے(x=0; x<(چوڑائی-(uv_x_sample_interval-1)); x+=uv_x_sample_interval)
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_انحراف);
			int32_t v_tmp = (GET(*v_ptr)-UV_انحراف);

			int32_t r_tmp = (v_tmp*param->v_r_ضربی_عدد);
			int32_t g_tmp = (u_tmp*param->u_g_ضربی_عدد + v_tmp*param->v_g_ضربی_عدد);
			int32_t b_tmp = (u_tmp*param->u_b_ضربی_عدد);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_سرکاؤ)*param->y_ضربی_عدد);
			PACK_PIXEL(rgb_ptr1);

			#اگر uv_x_sample_interval > 1
			y_tmp = (GET(y_ptr1[y_pixel_stride]-param->y_سرکاؤ)*param->y_ضربی_عدد);
			PACK_PIXEL(rgb_ptr1);
			#اگر_ختم

			#اگر uv_y_sample_interval > 1
			y_tmp = (GET(y_ptr2[0]-param->y_سرکاؤ)*param->y_ضربی_عدد);
			PACK_PIXEL(rgb_ptr2);

			y_tmp = (GET(y_ptr2[y_pixel_stride]-param->y_سرکاؤ)*param->y_ضربی_عدد);
			PACK_PIXEL(rgb_ptr2);
			#اگر_ختم

			#اگر uv_x_sample_interval > 1
			y_ptr1+=2*y_pixel_stride;
			#ورنہ
			y_ptr1+=y_pixel_stride;
			#اگر_ختم
			#اگر uv_y_sample_interval > 1
			y_ptr2+=2*y_pixel_stride;
			#اگر_ختم
			#اگر uv_x_sample_interval > 1
			u_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			#ورنہ
			u_ptr+=uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=uv_pixel_stride/uv_x_sample_interval;
			#اگر_ختم
		}

		/* Catch the last pixel, if needed */
#اگر uv_x_sample_interval == 2
		اگر (x == (چوڑائی-1))
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_انحراف);
			int32_t v_tmp = (GET(*v_ptr)-UV_انحراف);

			int32_t r_tmp = (v_tmp*param->v_r_ضربی_عدد);
			int32_t g_tmp = (u_tmp*param->u_g_ضربی_عدد + v_tmp*param->v_g_ضربی_عدد);
			int32_t b_tmp = (u_tmp*param->u_b_ضربی_عدد);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_سرکاؤ)*param->y_ضربی_عدد);
			PACK_PIXEL(rgb_ptr1);

			#اگر uv_y_sample_interval > 1
			y_tmp = (GET(y_ptr2[0]-param->y_سرکاؤ)*param->y_ضربی_عدد);
			PACK_PIXEL(rgb_ptr2);
			#اگر_ختم
		}
#اگر_ختم
	}

	/* Catch the last line, if needed */
#اگر uv_y_sample_interval == 2
	اگر (y == (اونچائی-1))
	{
		ثابت YUV_TYPE *y_ptr1=Y+y*Y_stride,
			*u_ptr=U+(y/uv_y_sample_interval)*UV_stride,
			*v_ptr=V+(y/uv_y_sample_interval)*UV_stride;

		uint8_t *rgb_ptr1=RGB+y*RGB_stride;

		برائے(x=0; x<(چوڑائی-(uv_x_sample_interval-1)); x+=uv_x_sample_interval)
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_انحراف);
			int32_t v_tmp = (GET(*v_ptr)-UV_انحراف);

			int32_t r_tmp = (v_tmp*param->v_r_ضربی_عدد);
			int32_t g_tmp = (u_tmp*param->u_g_ضربی_عدد + v_tmp*param->v_g_ضربی_عدد);
			int32_t b_tmp = (u_tmp*param->u_b_ضربی_عدد);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_سرکاؤ)*param->y_ضربی_عدد);
			PACK_PIXEL(rgb_ptr1);

			y_tmp = (GET(y_ptr1[y_pixel_stride]-param->y_سرکاؤ)*param->y_ضربی_عدد);
			PACK_PIXEL(rgb_ptr1);

			y_ptr1+=2*y_pixel_stride;
			u_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
		}

		/* Catch the last pixel, if needed */
#اگر uv_x_sample_interval == 2
		اگر (x == (چوڑائی-1))
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_انحراف);
			int32_t v_tmp = (GET(*v_ptr)-UV_انحراف);

			int32_t r_tmp = (v_tmp*param->v_r_ضربی_عدد);
			int32_t g_tmp = (u_tmp*param->u_g_ضربی_عدد + v_tmp*param->v_g_ضربی_عدد);
			int32_t b_tmp = (u_tmp*param->u_b_ضربی_عدد);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_سرکاؤ)*param->y_ضربی_عدد);
			PACK_PIXEL(rgb_ptr1);
		}
#اگر_ختم
	}
#اگر_ختم

	#تعریف_منسوخ y_pixel_stride
	#تعریف_منسوخ uv_pixel_stride
	#تعریف_منسوخ uv_x_sample_interval
	#تعریف_منسوخ uv_y_sample_interval
}

#اگر_تعریف_شدہ _MSC_VER
#ہدایت warning(نکالو)
#اگر_ختم

#تعریف_منسوخ STD_FUNCTION_NAME
#تعریف_منسوخ YUV_FORMAT
#تعریف_منسوخ RGB_FORMAT
#تعریف_منسوخ PACK_PIXEL
