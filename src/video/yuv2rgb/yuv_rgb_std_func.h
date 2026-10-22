// Copyright 2016 Adrien Descamps
// Distributed under BSD 3-Clause License

/* You need to define the following macros before including this file:
	STD_FUNCTION_NAME
	YUV_FORMAT
	RGB_FORMAT
*/

#ಯದಿ RGB_FORMAT == RGB_FORMAT_RGB565

#define PACK_PIXEL(rgb_ptr) \
	*(Uint16 *)rgb_ptr = \
		((((Uint16)clampU8(y_tmp+r_tmp)) << 8 ) & 0xF800) | \
		((((Uint16)clampU8(y_tmp+g_tmp)) << 3) & 0x07E0) | \
		(((Uint16)clampU8(y_tmp+b_tmp)) >> 3); \
	rgb_ptr += 2

#ನೋಚೇದ್ಯದಿ RGB_FORMAT == RGB_FORMAT_RGB24

#define PACK_PIXEL(rgb_ptr) \
	rgb_ptr[0] = clampU8(y_tmp+r_tmp); \
	rgb_ptr[1] = clampU8(y_tmp+g_tmp); \
	rgb_ptr[2] = clampU8(y_tmp+b_tmp); \
	rgb_ptr += 3

#ನೋಚೇದ್ಯದಿ RGB_FORMAT == RGB_FORMAT_RGBA

#define PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 24) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 8) | \
		0x000000FF; \
	rgb_ptr += 4

#ನೋಚೇದ್ಯದಿ RGB_FORMAT == RGB_FORMAT_BGRA

#define PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 24) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 8) | \
		0x000000FF; \
	rgb_ptr += 4

#ನೋಚೇದ್ಯದಿ RGB_FORMAT == RGB_FORMAT_ARGB

#define PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xFF000000 | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 8) | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 0); \
	rgb_ptr += 4

#ನೋಚೇದ್ಯದಿ RGB_FORMAT == RGB_FORMAT_ABGR

#define PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xFF000000 | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 8) | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 0); \
	rgb_ptr += 4

#ನೋಚೇದ್ಯದಿ RGB_FORMAT == RGB_FORMAT_XBGR2101010

#define PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xC0000000 | \
		(((Uint32)clamp10(y_tmp+b_tmp)) << 20) | \
		(((Uint32)clamp10(y_tmp+g_tmp)) << 10) | \
		(((Uint32)clamp10(y_tmp+r_tmp)) << 0); \
	rgb_ptr += 4

#ನೋಚೇದ್ಯದಿ RGB_FORMAT == RGB_FORMAT_RGB48

#define PACK_PIXEL(rgb_ptr) \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + r_tmp); \
	rgb_ptr += ಪರಿಮಾಣ(Uint16);				   \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + g_tmp); \
	rgb_ptr += ಪರಿಮಾಣ(Uint16);				   \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + b_tmp); \
	rgb_ptr += ಪರಿಮಾಣ(Uint16)

#ಅನ್ಯಥಾ
#error PACK_PIXEL unimplemented
#endif


#ifdef _MSC_VER /* Visual Studio analyzer can't tell that we're building this with different constants */
#pragma warning(ತಳ್ಳು)
#pragma warning(disable : 6239)
#endif

#undef YUV_TYPE
#ಯದಿ YUV_BITS > 8
#define YUV_TYPE	uint16_t
#ಅನ್ಯಥಾ
#define YUV_TYPE	uint8_t
#endif
#undef UV_OFFSET
#define UV_OFFSET	(1 << ((YUV_BITS)-1))

#undef GET
#ಯದಿ YUV_BITS == 10
#define GET(X)	((X) >> 6)
#ಅನ್ಯಥಾ
#define GET(X)	(X)
#endif

ಶೂನ್ಯ STD_FUNCTION_NAME(
	uint32_t width, uint32_t height,
	ಧ್ರುವ YUV_TYPE *Y, ಧ್ರುವ YUV_TYPE *U, ಧ್ರುವ YUV_TYPE *V, uint32_t Y_stride, uint32_t UV_stride,
	uint8_t *RGB, uint32_t RGB_stride,
	YCbCrType yuv_type)
{
	ಧ್ರುವ YUV2RGBParam *ಧ್ರುವ param = &(YUV2RGB[yuv_type]);
#ಯದಿ YUV_FORMAT == YUV_FORMAT_420
	#define y_pixel_stride 1
	#define uv_pixel_stride 1
	#define uv_x_sample_interval 2
	#define uv_y_sample_interval 2
#ನೋಚೇದ್ಯದಿ YUV_FORMAT == YUV_FORMAT_422
	#define y_pixel_stride 2
	#define uv_pixel_stride 4
	#define uv_x_sample_interval 2
	#define uv_y_sample_interval 1
#ನೋಚೇದ್ಯದಿ YUV_FORMAT == YUV_FORMAT_444
	#define y_pixel_stride 1
	#define uv_pixel_stride 1
	#define uv_x_sample_interval 1
	#define uv_y_sample_interval 1
#ನೋಚೇದ್ಯದಿ YUV_FORMAT == YUV_FORMAT_NV12
	#define y_pixel_stride 1
	#define uv_pixel_stride 2
	#define uv_x_sample_interval 2
	#define uv_y_sample_interval 2
#endif

	Y_stride /= ಪರಿಮಾಣ(YUV_TYPE);
	UV_stride /= ಪರಿಮಾಣ(YUV_TYPE);

	uint32_t x, y;
	ಪ್ರತಿ(y=0; y<(height-(uv_y_sample_interval-1)); y+=uv_y_sample_interval)
	{
		ಧ್ರುವ YUV_TYPE *y_ptr1=Y+y*Y_stride,
			*u_ptr=U+(y/uv_y_sample_interval)*UV_stride,
			*v_ptr=V+(y/uv_y_sample_interval)*UV_stride;

		#ಯದಿ uv_y_sample_interval > 1
		ಧ್ರುವ YUV_TYPE *y_ptr2=Y+(y+1)*Y_stride;
		#endif

		uint8_t *rgb_ptr1=RGB+y*RGB_stride;

		#ಯದಿ uv_y_sample_interval > 1
		uint8_t *rgb_ptr2=RGB+(y+1)*RGB_stride;
		#endif

		ಪ್ರತಿ(x=0; x<(width-(uv_x_sample_interval-1)); x+=uv_x_sample_interval)
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_OFFSET);
			int32_t v_tmp = (GET(*v_ptr)-UV_OFFSET);

			int32_t r_tmp = (v_tmp*param->v_r_factor);
			int32_t g_tmp = (u_tmp*param->u_g_factor + v_tmp*param->v_g_factor);
			int32_t b_tmp = (u_tmp*param->u_b_factor);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_shift)*param->y_factor);
			PACK_PIXEL(rgb_ptr1);

			#ಯದಿ uv_x_sample_interval > 1
			y_tmp = (GET(y_ptr1[y_pixel_stride]-param->y_shift)*param->y_factor);
			PACK_PIXEL(rgb_ptr1);
			#endif

			#ಯದಿ uv_y_sample_interval > 1
			y_tmp = (GET(y_ptr2[0]-param->y_shift)*param->y_factor);
			PACK_PIXEL(rgb_ptr2);

			y_tmp = (GET(y_ptr2[y_pixel_stride]-param->y_shift)*param->y_factor);
			PACK_PIXEL(rgb_ptr2);
			#endif

			#ಯದಿ uv_x_sample_interval > 1
			y_ptr1+=2*y_pixel_stride;
			#ಅನ್ಯಥಾ
			y_ptr1+=y_pixel_stride;
			#endif
			#ಯದಿ uv_y_sample_interval > 1
			y_ptr2+=2*y_pixel_stride;
			#endif
			#ಯದಿ uv_x_sample_interval > 1
			u_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			#ಅನ್ಯಥಾ
			u_ptr+=uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=uv_pixel_stride/uv_x_sample_interval;
			#endif
		}

		/* Catch the last pixel, if needed */
#ಯದಿ uv_x_sample_interval == 2
		ಯದಿ (x == (width-1))
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_OFFSET);
			int32_t v_tmp = (GET(*v_ptr)-UV_OFFSET);

			int32_t r_tmp = (v_tmp*param->v_r_factor);
			int32_t g_tmp = (u_tmp*param->u_g_factor + v_tmp*param->v_g_factor);
			int32_t b_tmp = (u_tmp*param->u_b_factor);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_shift)*param->y_factor);
			PACK_PIXEL(rgb_ptr1);

			#ಯದಿ uv_y_sample_interval > 1
			y_tmp = (GET(y_ptr2[0]-param->y_shift)*param->y_factor);
			PACK_PIXEL(rgb_ptr2);
			#endif
		}
#endif
	}

	/* Catch the last line, if needed */
#ಯದಿ uv_y_sample_interval == 2
	ಯದಿ (y == (height-1))
	{
		ಧ್ರುವ YUV_TYPE *y_ptr1=Y+y*Y_stride,
			*u_ptr=U+(y/uv_y_sample_interval)*UV_stride,
			*v_ptr=V+(y/uv_y_sample_interval)*UV_stride;

		uint8_t *rgb_ptr1=RGB+y*RGB_stride;

		ಪ್ರತಿ(x=0; x<(width-(uv_x_sample_interval-1)); x+=uv_x_sample_interval)
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_OFFSET);
			int32_t v_tmp = (GET(*v_ptr)-UV_OFFSET);

			int32_t r_tmp = (v_tmp*param->v_r_factor);
			int32_t g_tmp = (u_tmp*param->u_g_factor + v_tmp*param->v_g_factor);
			int32_t b_tmp = (u_tmp*param->u_b_factor);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_shift)*param->y_factor);
			PACK_PIXEL(rgb_ptr1);

			y_tmp = (GET(y_ptr1[y_pixel_stride]-param->y_shift)*param->y_factor);
			PACK_PIXEL(rgb_ptr1);

			y_ptr1+=2*y_pixel_stride;
			u_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
		}

		/* Catch the last pixel, if needed */
#ಯದಿ uv_x_sample_interval == 2
		ಯದಿ (x == (width-1))
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_OFFSET);
			int32_t v_tmp = (GET(*v_ptr)-UV_OFFSET);

			int32_t r_tmp = (v_tmp*param->v_r_factor);
			int32_t g_tmp = (u_tmp*param->u_g_factor + v_tmp*param->v_g_factor);
			int32_t b_tmp = (u_tmp*param->u_b_factor);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_shift)*param->y_factor);
			PACK_PIXEL(rgb_ptr1);
		}
#endif
	}
#endif

	#undef y_pixel_stride
	#undef uv_pixel_stride
	#undef uv_x_sample_interval
	#undef uv_y_sample_interval
}

#ifdef _MSC_VER
#pragma warning(ತೆಗೆ)
#endif

#undef STD_FUNCTION_NAME
#undef YUV_FORMAT
#undef RGB_FORMAT
#undef PACK_PIXEL
