// Copyright 2016 Adrien Descamps
// Distributed under BSD 3-Clause License

/* You need to define the following macros before including this file:
	STD_FUNCTION_NAME
	YUV_FORMAT
	RGB_FORMAT
*/

#إذا RGB_FORMAT == RGB_FORMAT_RGB565

#تعریف_کړه PACK_PIXEL(rgb_ptr) \
	*(Uint16 *)rgb_ptr = \
		((((Uint16)clampU8(y_tmp+r_tmp)) << 8 ) & 0xF800) | \
		((((Uint16)clampU8(y_tmp+g_tmp)) << 3) & 0x07E0) | \
		(((Uint16)clampU8(y_tmp+b_tmp)) >> 3); \
	rgb_ptr += 2

#وإلاإذا RGB_FORMAT == RGB_FORMAT_RGB24

#تعریف_کړه PACK_PIXEL(rgb_ptr) \
	rgb_ptr[0] = clampU8(y_tmp+r_tmp); \
	rgb_ptr[1] = clampU8(y_tmp+g_tmp); \
	rgb_ptr[2] = clampU8(y_tmp+b_tmp); \
	rgb_ptr += 3

#وإلاإذا RGB_FORMAT == RGB_FORMAT_RGBA

#تعریف_کړه PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 24) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 8) | \
		0x000000FF; \
	rgb_ptr += 4

#وإلاإذا RGB_FORMAT == RGB_FORMAT_BGRA

#تعریف_کړه PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 24) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 8) | \
		0x000000FF; \
	rgb_ptr += 4

#وإلاإذا RGB_FORMAT == RGB_FORMAT_ARGB

#تعریف_کړه PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xFF000000 | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 8) | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 0); \
	rgb_ptr += 4

#وإلاإذا RGB_FORMAT == RGB_FORMAT_ABGR

#تعریف_کړه PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xFF000000 | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 8) | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 0); \
	rgb_ptr += 4

#وإلاإذا RGB_FORMAT == RGB_FORMAT_XBGR2101010

#تعریف_کړه PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xC0000000 | \
		(((Uint32)clamp10(y_tmp+b_tmp)) << 20) | \
		(((Uint32)clamp10(y_tmp+g_tmp)) << 10) | \
		(((Uint32)clamp10(y_tmp+r_tmp)) << 0); \
	rgb_ptr += 4

#وإلاإذا RGB_FORMAT == RGB_FORMAT_RGB48

#تعریف_کړه PACK_PIXEL(rgb_ptr) \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + r_tmp); \
	rgb_ptr += حجم(Uint16);				   \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + g_tmp); \
	rgb_ptr += حجم(Uint16);				   \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + b_tmp); \
	rgb_ptr += حجم(Uint16)

#وإلا
#تېروتنه PACK_PIXEL unimplemented
#د_که_پای


#که_تعریف_شوی _MSC_VER /* Visual Studio analyzer can't tell that we're building this with different constants */
#لارښوونه warning(ټېل)
#لارښوونه warning(disable : 6239)
#د_که_پای

#تعریف_لغوه YUV_TYPE
#إذا YUV_بټونه > 8
#تعریف_کړه YUV_TYPE	uint16_t
#وإلا
#تعریف_کړه YUV_TYPE	uint8_t
#د_که_پای
#تعریف_لغوه UV_دننه_واټن
#تعریف_کړه UV_دننه_واټن	(1 << ((YUV_بټونه)-1))

#تعریف_لغوه GET
#إذا YUV_بټونه == 10
#تعریف_کړه GET(X)	((X) >> 6)
#وإلا
#تعریف_کړه GET(X)	(X)
#د_که_پای

فراغ STD_FUNCTION_NAME(
	uint32_t پلنوالی, uint32_t لوړوالی,
	ثابت YUV_TYPE *Y, ثابت YUV_TYPE *U, ثابت YUV_TYPE *V, uint32_t Y_stride, uint32_t UV_stride,
	uint8_t *RGB, uint32_t RGB_stride,
	YCbCrType yuv_type)
{
	ثابت YUV2RGBParam *ثابت param = &(YUV2RGB[yuv_type]);
#إذا YUV_FORMAT == YUV_FORMAT_420
	#تعریف_کړه y_pixel_stride 1
	#تعریف_کړه uv_pixel_stride 1
	#تعریف_کړه uv_x_sample_interval 2
	#تعریف_کړه uv_y_sample_interval 2
#وإلاإذا YUV_FORMAT == YUV_FORMAT_422
	#تعریف_کړه y_pixel_stride 2
	#تعریف_کړه uv_pixel_stride 4
	#تعریف_کړه uv_x_sample_interval 2
	#تعریف_کړه uv_y_sample_interval 1
#وإلاإذا YUV_FORMAT == YUV_FORMAT_444
	#تعریف_کړه y_pixel_stride 1
	#تعریف_کړه uv_pixel_stride 1
	#تعریف_کړه uv_x_sample_interval 1
	#تعریف_کړه uv_y_sample_interval 1
#وإلاإذا YUV_FORMAT == YUV_FORMAT_NV12
	#تعریف_کړه y_pixel_stride 1
	#تعریف_کړه uv_pixel_stride 2
	#تعریف_کړه uv_x_sample_interval 2
	#تعریف_کړه uv_y_sample_interval 2
#د_که_پای

	Y_stride /= حجم(YUV_TYPE);
	UV_stride /= حجم(YUV_TYPE);

	uint32_t x, y;
	لكل(y=0; y<(لوړوالی-(uv_y_sample_interval-1)); y+=uv_y_sample_interval)
	{
		ثابت YUV_TYPE *y_ptr1=Y+y*Y_stride,
			*u_ptr=U+(y/uv_y_sample_interval)*UV_stride,
			*v_ptr=V+(y/uv_y_sample_interval)*UV_stride;

		#إذا uv_y_sample_interval > 1
		ثابت YUV_TYPE *y_ptr2=Y+(y+1)*Y_stride;
		#د_که_پای

		uint8_t *rgb_ptr1=RGB+y*RGB_stride;

		#إذا uv_y_sample_interval > 1
		uint8_t *rgb_ptr2=RGB+(y+1)*RGB_stride;
		#د_که_پای

		لكل(x=0; x<(پلنوالی-(uv_x_sample_interval-1)); x+=uv_x_sample_interval)
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_دننه_واټن);
			int32_t v_tmp = (GET(*v_ptr)-UV_دننه_واټن);

			int32_t r_tmp = (v_tmp*param->v_r_ضریب);
			int32_t g_tmp = (u_tmp*param->u_g_ضریب + v_tmp*param->v_g_ضریب);
			int32_t b_tmp = (u_tmp*param->u_b_ضریب);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_ښويدنه)*param->y_ضریب);
			PACK_PIXEL(rgb_ptr1);

			#إذا uv_x_sample_interval > 1
			y_tmp = (GET(y_ptr1[y_pixel_stride]-param->y_ښويدنه)*param->y_ضریب);
			PACK_PIXEL(rgb_ptr1);
			#د_که_پای

			#إذا uv_y_sample_interval > 1
			y_tmp = (GET(y_ptr2[0]-param->y_ښويدنه)*param->y_ضریب);
			PACK_PIXEL(rgb_ptr2);

			y_tmp = (GET(y_ptr2[y_pixel_stride]-param->y_ښويدنه)*param->y_ضریب);
			PACK_PIXEL(rgb_ptr2);
			#د_که_پای

			#إذا uv_x_sample_interval > 1
			y_ptr1+=2*y_pixel_stride;
			#وإلا
			y_ptr1+=y_pixel_stride;
			#د_که_پای
			#إذا uv_y_sample_interval > 1
			y_ptr2+=2*y_pixel_stride;
			#د_که_پای
			#إذا uv_x_sample_interval > 1
			u_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			#وإلا
			u_ptr+=uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=uv_pixel_stride/uv_x_sample_interval;
			#د_که_پای
		}

		/* Catch the last pixel, if needed */
#إذا uv_x_sample_interval == 2
		إذا (x == (پلنوالی-1))
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_دننه_واټن);
			int32_t v_tmp = (GET(*v_ptr)-UV_دننه_واټن);

			int32_t r_tmp = (v_tmp*param->v_r_ضریب);
			int32_t g_tmp = (u_tmp*param->u_g_ضریب + v_tmp*param->v_g_ضریب);
			int32_t b_tmp = (u_tmp*param->u_b_ضریب);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_ښويدنه)*param->y_ضریب);
			PACK_PIXEL(rgb_ptr1);

			#إذا uv_y_sample_interval > 1
			y_tmp = (GET(y_ptr2[0]-param->y_ښويدنه)*param->y_ضریب);
			PACK_PIXEL(rgb_ptr2);
			#د_که_پای
		}
#د_که_پای
	}

	/* Catch the last line, if needed */
#إذا uv_y_sample_interval == 2
	إذا (y == (لوړوالی-1))
	{
		ثابت YUV_TYPE *y_ptr1=Y+y*Y_stride,
			*u_ptr=U+(y/uv_y_sample_interval)*UV_stride,
			*v_ptr=V+(y/uv_y_sample_interval)*UV_stride;

		uint8_t *rgb_ptr1=RGB+y*RGB_stride;

		لكل(x=0; x<(پلنوالی-(uv_x_sample_interval-1)); x+=uv_x_sample_interval)
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_دننه_واټن);
			int32_t v_tmp = (GET(*v_ptr)-UV_دننه_واټن);

			int32_t r_tmp = (v_tmp*param->v_r_ضریب);
			int32_t g_tmp = (u_tmp*param->u_g_ضریب + v_tmp*param->v_g_ضریب);
			int32_t b_tmp = (u_tmp*param->u_b_ضریب);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_ښويدنه)*param->y_ضریب);
			PACK_PIXEL(rgb_ptr1);

			y_tmp = (GET(y_ptr1[y_pixel_stride]-param->y_ښويدنه)*param->y_ضریب);
			PACK_PIXEL(rgb_ptr1);

			y_ptr1+=2*y_pixel_stride;
			u_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
		}

		/* Catch the last pixel, if needed */
#إذا uv_x_sample_interval == 2
		إذا (x == (پلنوالی-1))
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_دننه_واټن);
			int32_t v_tmp = (GET(*v_ptr)-UV_دننه_واټن);

			int32_t r_tmp = (v_tmp*param->v_r_ضریب);
			int32_t g_tmp = (u_tmp*param->u_g_ضریب + v_tmp*param->v_g_ضریب);
			int32_t b_tmp = (u_tmp*param->u_b_ضریب);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_ښويدنه)*param->y_ضریب);
			PACK_PIXEL(rgb_ptr1);
		}
#د_که_پای
	}
#د_که_پای

	#تعریف_لغوه y_pixel_stride
	#تعریف_لغوه uv_pixel_stride
	#تعریف_لغوه uv_x_sample_interval
	#تعریف_لغوه uv_y_sample_interval
}

#که_تعریف_شوی _MSC_VER
#لارښوونه warning(راوباسه)
#د_که_پای

#تعریف_لغوه STD_FUNCTION_NAME
#تعریف_لغوه YUV_FORMAT
#تعریف_لغوه RGB_FORMAT
#تعریف_لغوه PACK_PIXEL
