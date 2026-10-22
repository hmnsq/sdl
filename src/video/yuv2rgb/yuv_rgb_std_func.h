// Copyright 2016 Adrien Descamps
// Distributed under BSD 3-Clause License

/* You need to define the following macros before including this file:
	STD_FUNCTION_NAME
	YUV_FORMAT
	RGB_FORMAT
*/

#إذا RGB_FORMAT == RGB_FORMAT_RGB565

#تعریف_کرو PACK_PIXEL(rgb_ptr) \
	*(Uint16 *)rgb_ptr = \
		((((Uint16)clampU8(y_tmp+r_tmp)) << 8 ) & 0xF800) | \
		((((Uint16)clampU8(y_tmp+g_tmp)) << 3) & 0x07E0) | \
		(((Uint16)clampU8(y_tmp+b_tmp)) >> 3); \
	rgb_ptr += 2

#وإلاإذا RGB_FORMAT == RGB_FORMAT_RGB24

#تعریف_کرو PACK_PIXEL(rgb_ptr) \
	rgb_ptr[0] = clampU8(y_tmp+r_tmp); \
	rgb_ptr[1] = clampU8(y_tmp+g_tmp); \
	rgb_ptr[2] = clampU8(y_tmp+b_tmp); \
	rgb_ptr += 3

#وإلاإذا RGB_FORMAT == RGB_FORMAT_RGBA

#تعریف_کرو PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 24) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 8) | \
		0x000000FF; \
	rgb_ptr += 4

#وإلاإذا RGB_FORMAT == RGB_FORMAT_BGRA

#تعریف_کرو PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 24) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 8) | \
		0x000000FF; \
	rgb_ptr += 4

#وإلاإذا RGB_FORMAT == RGB_FORMAT_ARGB

#تعریف_کرو PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xFF000000 | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 8) | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 0); \
	rgb_ptr += 4

#وإلاإذا RGB_FORMAT == RGB_FORMAT_ABGR

#تعریف_کرو PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xFF000000 | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 8) | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 0); \
	rgb_ptr += 4

#وإلاإذا RGB_FORMAT == RGB_FORMAT_XBGR2101010

#تعریف_کرو PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xC0000000 | \
		(((Uint32)clamp10(y_tmp+b_tmp)) << 20) | \
		(((Uint32)clamp10(y_tmp+g_tmp)) << 10) | \
		(((Uint32)clamp10(y_tmp+r_tmp)) << 0); \
	rgb_ptr += 4

#وإلاإذا RGB_FORMAT == RGB_FORMAT_RGB48

#تعریف_کرو PACK_PIXEL(rgb_ptr) \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + r_tmp); \
	rgb_ptr += حجم(Uint16);				   \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + g_tmp); \
	rgb_ptr += حجم(Uint16);				   \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + b_tmp); \
	rgb_ptr += حجم(Uint16)

#وإلا
#غلطی PACK_PIXEL unimplemented
#جے_انت


#جے_تعریف_شدہ _MSC_VER /* Visual Studio analyzer can't tell that we're building this with different constants */
#ہدایت warning(ڈالو)
#ہدایت warning(disable : 6239)
#جے_انت

#تعریف_رد YUV_TYPE
#إذا YUV_بٹ > 8
#تعریف_کرو YUV_TYPE	uint16_t
#وإلا
#تعریف_کرو YUV_TYPE	uint8_t
#جے_انت
#تعریف_رد UV_وتھ
#تعریف_کرو UV_وتھ	(1 << ((YUV_بٹ)-1))

#تعریف_رد GET
#إذا YUV_بٹ == 10
#تعریف_کرو GET(X)	((X) >> 6)
#وإلا
#تعریف_کرو GET(X)	(X)
#جے_انت

فراغ STD_FUNCTION_NAME(
	uint32_t چوڑائی, uint32_t اچائی,
	ثابت YUV_TYPE *Y, ثابت YUV_TYPE *U, ثابت YUV_TYPE *V, uint32_t Y_stride, uint32_t UV_stride,
	uint8_t *RGB, uint32_t RGB_stride,
	YCbCrType yuv_type)
{
	ثابت YUV2RGBParam *ثابت param = &(YUV2RGB[yuv_type]);
#إذا YUV_FORMAT == YUV_FORMAT_420
	#تعریف_کرو y_pixel_stride 1
	#تعریف_کرو uv_pixel_stride 1
	#تعریف_کرو uv_x_sample_interval 2
	#تعریف_کرو uv_y_sample_interval 2
#وإلاإذا YUV_FORMAT == YUV_FORMAT_422
	#تعریف_کرو y_pixel_stride 2
	#تعریف_کرو uv_pixel_stride 4
	#تعریف_کرو uv_x_sample_interval 2
	#تعریف_کرو uv_y_sample_interval 1
#وإلاإذا YUV_FORMAT == YUV_FORMAT_444
	#تعریف_کرو y_pixel_stride 1
	#تعریف_کرو uv_pixel_stride 1
	#تعریف_کرو uv_x_sample_interval 1
	#تعریف_کرو uv_y_sample_interval 1
#وإلاإذا YUV_FORMAT == YUV_FORMAT_NV12
	#تعریف_کرو y_pixel_stride 1
	#تعریف_کرو uv_pixel_stride 2
	#تعریف_کرو uv_x_sample_interval 2
	#تعریف_کرو uv_y_sample_interval 2
#جے_انت

	Y_stride /= حجم(YUV_TYPE);
	UV_stride /= حجم(YUV_TYPE);

	uint32_t x, y;
	لكل(y=0; y<(اچائی-(uv_y_sample_interval-1)); y+=uv_y_sample_interval)
	{
		ثابت YUV_TYPE *y_ptr1=Y+y*Y_stride,
			*u_ptr=U+(y/uv_y_sample_interval)*UV_stride,
			*v_ptr=V+(y/uv_y_sample_interval)*UV_stride;

		#إذا uv_y_sample_interval > 1
		ثابت YUV_TYPE *y_ptr2=Y+(y+1)*Y_stride;
		#جے_انت

		uint8_t *rgb_ptr1=RGB+y*RGB_stride;

		#إذا uv_y_sample_interval > 1
		uint8_t *rgb_ptr2=RGB+(y+1)*RGB_stride;
		#جے_انت

		لكل(x=0; x<(چوڑائی-(uv_x_sample_interval-1)); x+=uv_x_sample_interval)
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_وتھ);
			int32_t v_tmp = (GET(*v_ptr)-UV_وتھ);

			int32_t r_tmp = (v_tmp*param->v_r_ضارب);
			int32_t g_tmp = (u_tmp*param->u_g_ضارب + v_tmp*param->v_g_ضارب);
			int32_t b_tmp = (u_tmp*param->u_b_ضارب);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_کھسکاؤ)*param->y_ضارب);
			PACK_PIXEL(rgb_ptr1);

			#إذا uv_x_sample_interval > 1
			y_tmp = (GET(y_ptr1[y_pixel_stride]-param->y_کھسکاؤ)*param->y_ضارب);
			PACK_PIXEL(rgb_ptr1);
			#جے_انت

			#إذا uv_y_sample_interval > 1
			y_tmp = (GET(y_ptr2[0]-param->y_کھسکاؤ)*param->y_ضارب);
			PACK_PIXEL(rgb_ptr2);

			y_tmp = (GET(y_ptr2[y_pixel_stride]-param->y_کھسکاؤ)*param->y_ضارب);
			PACK_PIXEL(rgb_ptr2);
			#جے_انت

			#إذا uv_x_sample_interval > 1
			y_ptr1+=2*y_pixel_stride;
			#وإلا
			y_ptr1+=y_pixel_stride;
			#جے_انت
			#إذا uv_y_sample_interval > 1
			y_ptr2+=2*y_pixel_stride;
			#جے_انت
			#إذا uv_x_sample_interval > 1
			u_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			#وإلا
			u_ptr+=uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=uv_pixel_stride/uv_x_sample_interval;
			#جے_انت
		}

		/* Catch the last pixel, if needed */
#إذا uv_x_sample_interval == 2
		إذا (x == (چوڑائی-1))
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_وتھ);
			int32_t v_tmp = (GET(*v_ptr)-UV_وتھ);

			int32_t r_tmp = (v_tmp*param->v_r_ضارب);
			int32_t g_tmp = (u_tmp*param->u_g_ضارب + v_tmp*param->v_g_ضارب);
			int32_t b_tmp = (u_tmp*param->u_b_ضارب);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_کھسکاؤ)*param->y_ضارب);
			PACK_PIXEL(rgb_ptr1);

			#إذا uv_y_sample_interval > 1
			y_tmp = (GET(y_ptr2[0]-param->y_کھسکاؤ)*param->y_ضارب);
			PACK_PIXEL(rgb_ptr2);
			#جے_انت
		}
#جے_انت
	}

	/* Catch the last line, if needed */
#إذا uv_y_sample_interval == 2
	إذا (y == (اچائی-1))
	{
		ثابت YUV_TYPE *y_ptr1=Y+y*Y_stride,
			*u_ptr=U+(y/uv_y_sample_interval)*UV_stride,
			*v_ptr=V+(y/uv_y_sample_interval)*UV_stride;

		uint8_t *rgb_ptr1=RGB+y*RGB_stride;

		لكل(x=0; x<(چوڑائی-(uv_x_sample_interval-1)); x+=uv_x_sample_interval)
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_وتھ);
			int32_t v_tmp = (GET(*v_ptr)-UV_وتھ);

			int32_t r_tmp = (v_tmp*param->v_r_ضارب);
			int32_t g_tmp = (u_tmp*param->u_g_ضارب + v_tmp*param->v_g_ضارب);
			int32_t b_tmp = (u_tmp*param->u_b_ضارب);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_کھسکاؤ)*param->y_ضارب);
			PACK_PIXEL(rgb_ptr1);

			y_tmp = (GET(y_ptr1[y_pixel_stride]-param->y_کھسکاؤ)*param->y_ضارب);
			PACK_PIXEL(rgb_ptr1);

			y_ptr1+=2*y_pixel_stride;
			u_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
		}

		/* Catch the last pixel, if needed */
#إذا uv_x_sample_interval == 2
		إذا (x == (چوڑائی-1))
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_وتھ);
			int32_t v_tmp = (GET(*v_ptr)-UV_وتھ);

			int32_t r_tmp = (v_tmp*param->v_r_ضارب);
			int32_t g_tmp = (u_tmp*param->u_g_ضارب + v_tmp*param->v_g_ضارب);
			int32_t b_tmp = (u_tmp*param->u_b_ضارب);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_کھسکاؤ)*param->y_ضارب);
			PACK_PIXEL(rgb_ptr1);
		}
#جے_انت
	}
#جے_انت

	#تعریف_رد y_pixel_stride
	#تعریف_رد uv_pixel_stride
	#تعریف_رد uv_x_sample_interval
	#تعریف_رد uv_y_sample_interval
}

#جے_تعریف_شدہ _MSC_VER
#ہدایت warning(نکالو)
#جے_انت

#تعریف_رد STD_FUNCTION_NAME
#تعریف_رد YUV_FORMAT
#تعریف_رد RGB_FORMAT
#تعریف_رد PACK_PIXEL
