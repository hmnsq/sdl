// Copyright 2016 Adrien Descamps
// Distributed under BSD 3-Clause License

/* You need to define the following macros before including this file:
	STD_FUNCTION_NAME
	YUV_FORMAT
	RGB_FORMAT
*/

#ಆದರೆ RGB_FORMAT == RGB_FORMAT_RGB565

#ವ್ಯಾಖ್ಯಾನಿಸು PACK_PIXEL(rgb_ptr) \
	*(Uint16 *)rgb_ptr = \
		((((Uint16)clampU8(y_tmp+r_tmp)) << 8 ) & 0xF800) | \
		((((Uint16)clampU8(y_tmp+g_tmp)) << 3) & 0x07E0) | \
		(((Uint16)clampU8(y_tmp+b_tmp)) >> 3); \
	rgb_ptr += 2

#ಅಥವಾಆದರೆ RGB_FORMAT == RGB_FORMAT_RGB24

#ವ್ಯಾಖ್ಯಾನಿಸು PACK_PIXEL(rgb_ptr) \
	rgb_ptr[0] = clampU8(y_tmp+r_tmp); \
	rgb_ptr[1] = clampU8(y_tmp+g_tmp); \
	rgb_ptr[2] = clampU8(y_tmp+b_tmp); \
	rgb_ptr += 3

#ಅಥವಾಆದರೆ RGB_FORMAT == RGB_FORMAT_RGBA

#ವ್ಯಾಖ್ಯಾನಿಸು PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 24) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 8) | \
		0x000000FF; \
	rgb_ptr += 4

#ಅಥವಾಆದರೆ RGB_FORMAT == RGB_FORMAT_BGRA

#ವ್ಯಾಖ್ಯಾನಿಸು PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 24) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 8) | \
		0x000000FF; \
	rgb_ptr += 4

#ಅಥವಾಆದರೆ RGB_FORMAT == RGB_FORMAT_ARGB

#ವ್ಯಾಖ್ಯಾನಿಸು PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xFF000000 | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 8) | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 0); \
	rgb_ptr += 4

#ಅಥವಾಆದರೆ RGB_FORMAT == RGB_FORMAT_ABGR

#ವ್ಯಾಖ್ಯಾನಿಸು PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xFF000000 | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 8) | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 0); \
	rgb_ptr += 4

#ಅಥವಾಆದರೆ RGB_FORMAT == RGB_FORMAT_XBGR2101010

#ವ್ಯಾಖ್ಯಾನಿಸು PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xC0000000 | \
		(((Uint32)clamp10(y_tmp+b_tmp)) << 20) | \
		(((Uint32)clamp10(y_tmp+g_tmp)) << 10) | \
		(((Uint32)clamp10(y_tmp+r_tmp)) << 0); \
	rgb_ptr += 4

#ಅಥವಾಆದರೆ RGB_FORMAT == RGB_FORMAT_RGB48

#ವ್ಯಾಖ್ಯಾನಿಸು PACK_PIXEL(rgb_ptr) \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + r_tmp); \
	rgb_ptr += ಗಾತ್ರ(Uint16);				   \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + g_tmp); \
	rgb_ptr += ಗಾತ್ರ(Uint16);				   \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + b_tmp); \
	rgb_ptr += ಗಾತ್ರ(Uint16)

#ಇಲ್ಲದಿದ್ದರೆ
#ದೋಷ PACK_PIXEL unimplemented
#ಆದರೆ_ಅಂತ್ಯ


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _MSC_VER /* Visual Studio analyzer can't tell that we're building this with different constants */
#ಸೂಚನೆ warning(ತಳ್ಳು)
#ಸೂಚನೆ warning(disable : 6239)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು YUV_TYPE
#ಆದರೆ YUV_ಬಿಟ್ಟುಗಳು > 8
#ವ್ಯಾಖ್ಯಾನಿಸು YUV_TYPE	uint16_t
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು YUV_TYPE	uint8_t
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು UV_ಸ್ಥಾನಾಂತರ
#ವ್ಯಾಖ್ಯಾನಿಸು UV_ಸ್ಥಾನಾಂತರ	(1 << ((YUV_ಬಿಟ್ಟುಗಳು)-1))

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು GET
#ಆದರೆ YUV_ಬಿಟ್ಟುಗಳು == 10
#ವ್ಯಾಖ್ಯಾನಿಸು GET(X)	((X) >> 6)
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು GET(X)	(X)
#ಆದರೆ_ಅಂತ್ಯ

ಶೂನ್ಯ STD_FUNCTION_NAME(
	uint32_t ಅಗಲ, uint32_t ಎತ್ತರ,
	ಸ್ಥಿರಾಂಕ YUV_TYPE *Y, ಸ್ಥಿರಾಂಕ YUV_TYPE *U, ಸ್ಥಿರಾಂಕ YUV_TYPE *V, uint32_t Y_stride, uint32_t UV_stride,
	uint8_t *RGB, uint32_t RGB_stride,
	YCbCrType yuv_type)
{
	ಸ್ಥಿರಾಂಕ YUV2RGBParam *ಸ್ಥಿರಾಂಕ param = &(YUV2RGB[yuv_type]);
#ಆದರೆ YUV_FORMAT == YUV_FORMAT_420
	#ವ್ಯಾಖ್ಯಾನಿಸು y_pixel_stride 1
	#ವ್ಯಾಖ್ಯಾನಿಸು uv_pixel_stride 1
	#ವ್ಯಾಖ್ಯಾನಿಸು uv_x_sample_interval 2
	#ವ್ಯಾಖ್ಯಾನಿಸು uv_y_sample_interval 2
#ಅಥವಾಆದರೆ YUV_FORMAT == YUV_FORMAT_422
	#ವ್ಯಾಖ್ಯಾನಿಸು y_pixel_stride 2
	#ವ್ಯಾಖ್ಯಾನಿಸು uv_pixel_stride 4
	#ವ್ಯಾಖ್ಯಾನಿಸು uv_x_sample_interval 2
	#ವ್ಯಾಖ್ಯಾನಿಸು uv_y_sample_interval 1
#ಅಥವಾಆದರೆ YUV_FORMAT == YUV_FORMAT_444
	#ವ್ಯಾಖ್ಯಾನಿಸು y_pixel_stride 1
	#ವ್ಯಾಖ್ಯಾನಿಸು uv_pixel_stride 1
	#ವ್ಯಾಖ್ಯಾನಿಸು uv_x_sample_interval 1
	#ವ್ಯಾಖ್ಯಾನಿಸು uv_y_sample_interval 1
#ಅಥವಾಆದರೆ YUV_FORMAT == YUV_FORMAT_NV12
	#ವ್ಯಾಖ್ಯಾನಿಸು y_pixel_stride 1
	#ವ್ಯಾಖ್ಯಾನಿಸು uv_pixel_stride 2
	#ವ್ಯಾಖ್ಯಾನಿಸು uv_x_sample_interval 2
	#ವ್ಯಾಖ್ಯಾನಿಸು uv_y_sample_interval 2
#ಆದರೆ_ಅಂತ್ಯ

	Y_stride /= ಗಾತ್ರ(YUV_TYPE);
	UV_stride /= ಗಾತ್ರ(YUV_TYPE);

	uint32_t x, y;
	ಗಾಗಿ(y=0; y<(ಎತ್ತರ-(uv_y_sample_interval-1)); y+=uv_y_sample_interval)
	{
		ಸ್ಥಿರಾಂಕ YUV_TYPE *y_ptr1=Y+y*Y_stride,
			*u_ptr=U+(y/uv_y_sample_interval)*UV_stride,
			*v_ptr=V+(y/uv_y_sample_interval)*UV_stride;

		#ಆದರೆ uv_y_sample_interval > 1
		ಸ್ಥಿರಾಂಕ YUV_TYPE *y_ptr2=Y+(y+1)*Y_stride;
		#ಆದರೆ_ಅಂತ್ಯ

		uint8_t *rgb_ptr1=RGB+y*RGB_stride;

		#ಆದರೆ uv_y_sample_interval > 1
		uint8_t *rgb_ptr2=RGB+(y+1)*RGB_stride;
		#ಆದರೆ_ಅಂತ್ಯ

		ಗಾಗಿ(x=0; x<(ಅಗಲ-(uv_x_sample_interval-1)); x+=uv_x_sample_interval)
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_ಸ್ಥಾನಾಂತರ);
			int32_t v_tmp = (GET(*v_ptr)-UV_ಸ್ಥಾನಾಂತರ);

			int32_t r_tmp = (v_tmp*param->v_r_ಗುಣಕ);
			int32_t g_tmp = (u_tmp*param->u_g_ಗುಣಕ + v_tmp*param->v_g_ಗುಣಕ);
			int32_t b_tmp = (u_tmp*param->u_b_ಗುಣಕ);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_ಸರಿಸು)*param->y_ಗುಣಕ);
			PACK_PIXEL(rgb_ptr1);

			#ಆದರೆ uv_x_sample_interval > 1
			y_tmp = (GET(y_ptr1[y_pixel_stride]-param->y_ಸರಿಸು)*param->y_ಗುಣಕ);
			PACK_PIXEL(rgb_ptr1);
			#ಆದರೆ_ಅಂತ್ಯ

			#ಆದರೆ uv_y_sample_interval > 1
			y_tmp = (GET(y_ptr2[0]-param->y_ಸರಿಸು)*param->y_ಗುಣಕ);
			PACK_PIXEL(rgb_ptr2);

			y_tmp = (GET(y_ptr2[y_pixel_stride]-param->y_ಸರಿಸು)*param->y_ಗುಣಕ);
			PACK_PIXEL(rgb_ptr2);
			#ಆದರೆ_ಅಂತ್ಯ

			#ಆದರೆ uv_x_sample_interval > 1
			y_ptr1+=2*y_pixel_stride;
			#ಇಲ್ಲದಿದ್ದರೆ
			y_ptr1+=y_pixel_stride;
			#ಆದರೆ_ಅಂತ್ಯ
			#ಆದರೆ uv_y_sample_interval > 1
			y_ptr2+=2*y_pixel_stride;
			#ಆದರೆ_ಅಂತ್ಯ
			#ಆದರೆ uv_x_sample_interval > 1
			u_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			#ಇಲ್ಲದಿದ್ದರೆ
			u_ptr+=uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=uv_pixel_stride/uv_x_sample_interval;
			#ಆದರೆ_ಅಂತ್ಯ
		}

		/* Catch the last pixel, if needed */
#ಆದರೆ uv_x_sample_interval == 2
		ಆದರೆ (x == (ಅಗಲ-1))
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_ಸ್ಥಾನಾಂತರ);
			int32_t v_tmp = (GET(*v_ptr)-UV_ಸ್ಥಾನಾಂತರ);

			int32_t r_tmp = (v_tmp*param->v_r_ಗುಣಕ);
			int32_t g_tmp = (u_tmp*param->u_g_ಗುಣಕ + v_tmp*param->v_g_ಗುಣಕ);
			int32_t b_tmp = (u_tmp*param->u_b_ಗುಣಕ);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_ಸರಿಸು)*param->y_ಗುಣಕ);
			PACK_PIXEL(rgb_ptr1);

			#ಆದರೆ uv_y_sample_interval > 1
			y_tmp = (GET(y_ptr2[0]-param->y_ಸರಿಸು)*param->y_ಗುಣಕ);
			PACK_PIXEL(rgb_ptr2);
			#ಆದರೆ_ಅಂತ್ಯ
		}
#ಆದರೆ_ಅಂತ್ಯ
	}

	/* Catch the last line, if needed */
#ಆದರೆ uv_y_sample_interval == 2
	ಆದರೆ (y == (ಎತ್ತರ-1))
	{
		ಸ್ಥಿರಾಂಕ YUV_TYPE *y_ptr1=Y+y*Y_stride,
			*u_ptr=U+(y/uv_y_sample_interval)*UV_stride,
			*v_ptr=V+(y/uv_y_sample_interval)*UV_stride;

		uint8_t *rgb_ptr1=RGB+y*RGB_stride;

		ಗಾಗಿ(x=0; x<(ಅಗಲ-(uv_x_sample_interval-1)); x+=uv_x_sample_interval)
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_ಸ್ಥಾನಾಂತರ);
			int32_t v_tmp = (GET(*v_ptr)-UV_ಸ್ಥಾನಾಂತರ);

			int32_t r_tmp = (v_tmp*param->v_r_ಗುಣಕ);
			int32_t g_tmp = (u_tmp*param->u_g_ಗುಣಕ + v_tmp*param->v_g_ಗುಣಕ);
			int32_t b_tmp = (u_tmp*param->u_b_ಗುಣಕ);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_ಸರಿಸು)*param->y_ಗುಣಕ);
			PACK_PIXEL(rgb_ptr1);

			y_tmp = (GET(y_ptr1[y_pixel_stride]-param->y_ಸರಿಸು)*param->y_ಗುಣಕ);
			PACK_PIXEL(rgb_ptr1);

			y_ptr1+=2*y_pixel_stride;
			u_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
		}

		/* Catch the last pixel, if needed */
#ಆದರೆ uv_x_sample_interval == 2
		ಆದರೆ (x == (ಅಗಲ-1))
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_ಸ್ಥಾನಾಂತರ);
			int32_t v_tmp = (GET(*v_ptr)-UV_ಸ್ಥಾನಾಂತರ);

			int32_t r_tmp = (v_tmp*param->v_r_ಗುಣಕ);
			int32_t g_tmp = (u_tmp*param->u_g_ಗುಣಕ + v_tmp*param->v_g_ಗುಣಕ);
			int32_t b_tmp = (u_tmp*param->u_b_ಗುಣಕ);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_ಸರಿಸು)*param->y_ಗುಣಕ);
			PACK_PIXEL(rgb_ptr1);
		}
#ಆದರೆ_ಅಂತ್ಯ
	}
#ಆದರೆ_ಅಂತ್ಯ

	#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು y_pixel_stride
	#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು uv_pixel_stride
	#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು uv_x_sample_interval
	#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು uv_y_sample_interval
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _MSC_VER
#ಸೂಚನೆ warning(ತೆಗೆ)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು STD_FUNCTION_NAME
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು YUV_FORMAT
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು RGB_FORMAT
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು PACK_PIXEL
