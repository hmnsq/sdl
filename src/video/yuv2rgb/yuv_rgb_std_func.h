// Copyright 2016 Adrien Descamps
// Distributed under BSD 3-Clause License

/* You need to define the following macros before including this file:
	STD_FUNCTION_NAME
	YUV_FORMAT
	RGB_FORMAT
*/

#ਜੇ RGB_FORMAT == RGB_FORMAT_RGB565

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PACK_PIXEL(rgb_ptr) \
	*(Uint16 *)rgb_ptr = \
		((((Uint16)clampU8(y_tmp+r_tmp)) << 8 ) & 0xF800) | \
		((((Uint16)clampU8(y_tmp+g_tmp)) << 3) & 0x07E0) | \
		(((Uint16)clampU8(y_tmp+b_tmp)) >> 3); \
	rgb_ptr += 2

#ਜਾਂਜੇ RGB_FORMAT == RGB_FORMAT_RGB24

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PACK_PIXEL(rgb_ptr) \
	rgb_ptr[0] = clampU8(y_tmp+r_tmp); \
	rgb_ptr[1] = clampU8(y_tmp+g_tmp); \
	rgb_ptr[2] = clampU8(y_tmp+b_tmp); \
	rgb_ptr += 3

#ਜਾਂਜੇ RGB_FORMAT == RGB_FORMAT_RGBA

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 24) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 8) | \
		0x000000FF; \
	rgb_ptr += 4

#ਜਾਂਜੇ RGB_FORMAT == RGB_FORMAT_BGRA

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 24) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 8) | \
		0x000000FF; \
	rgb_ptr += 4

#ਜਾਂਜੇ RGB_FORMAT == RGB_FORMAT_ARGB

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xFF000000 | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 8) | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 0); \
	rgb_ptr += 4

#ਜਾਂਜੇ RGB_FORMAT == RGB_FORMAT_ABGR

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xFF000000 | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 8) | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 0); \
	rgb_ptr += 4

#ਜਾਂਜੇ RGB_FORMAT == RGB_FORMAT_XBGR2101010

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xC0000000 | \
		(((Uint32)clamp10(y_tmp+b_tmp)) << 20) | \
		(((Uint32)clamp10(y_tmp+g_tmp)) << 10) | \
		(((Uint32)clamp10(y_tmp+r_tmp)) << 0); \
	rgb_ptr += 4

#ਜਾਂਜੇ RGB_FORMAT == RGB_FORMAT_RGB48

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PACK_PIXEL(rgb_ptr) \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + r_tmp); \
	rgb_ptr += ਆਕਾਰ(Uint16);				   \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + g_tmp); \
	rgb_ptr += ਆਕਾਰ(Uint16);				   \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + b_tmp); \
	rgb_ptr += ਆਕਾਰ(Uint16)

#ਨਹੀਂਤਾਂ
#ਗਲਤੀ PACK_PIXEL unimplemented
#ਜੇ_ਅੰਤ


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _MSC_VER /* Visual Studio analyzer can't tell that we're building this with different constants */
#ਹਦਾਇਤ warning(ਧੱਕੋ)
#ਹਦਾਇਤ warning(disable : 6239)
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ YUV_TYPE
#ਜੇ YUV_ਬਿੱਟ > 8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ YUV_TYPE	uint16_t
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ YUV_TYPE	uint8_t
#ਜੇ_ਅੰਤ
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ UV_ਵਿੱਥ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ UV_ਵਿੱਥ	(1 << ((YUV_ਬਿੱਟ)-1))

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ GET
#ਜੇ YUV_ਬਿੱਟ == 10
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GET(X)	((X) >> 6)
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GET(X)	(X)
#ਜੇ_ਅੰਤ

ਖਾਲੀ STD_FUNCTION_NAME(
	uint32_t ਚੌੜਾਈ, uint32_t ਉਚਾਈ,
	ਅਚਲ YUV_TYPE *Y, ਅਚਲ YUV_TYPE *U, ਅਚਲ YUV_TYPE *V, uint32_t Y_stride, uint32_t UV_stride,
	uint8_t *RGB, uint32_t RGB_stride,
	YCbCrType yuv_type)
{
	ਅਚਲ YUV2RGBParam *ਅਚਲ param = &(YUV2RGB[yuv_type]);
#ਜੇ YUV_FORMAT == YUV_FORMAT_420
	#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ y_pixel_stride 1
	#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ uv_pixel_stride 1
	#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ uv_x_sample_interval 2
	#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ uv_y_sample_interval 2
#ਜਾਂਜੇ YUV_FORMAT == YUV_FORMAT_422
	#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ y_pixel_stride 2
	#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ uv_pixel_stride 4
	#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ uv_x_sample_interval 2
	#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ uv_y_sample_interval 1
#ਜਾਂਜੇ YUV_FORMAT == YUV_FORMAT_444
	#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ y_pixel_stride 1
	#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ uv_pixel_stride 1
	#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ uv_x_sample_interval 1
	#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ uv_y_sample_interval 1
#ਜਾਂਜੇ YUV_FORMAT == YUV_FORMAT_NV12
	#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ y_pixel_stride 1
	#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ uv_pixel_stride 2
	#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ uv_x_sample_interval 2
	#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ uv_y_sample_interval 2
#ਜੇ_ਅੰਤ

	Y_stride /= ਆਕਾਰ(YUV_TYPE);
	UV_stride /= ਆਕਾਰ(YUV_TYPE);

	uint32_t x, y;
	ਲਈ(y=0; y<(ਉਚਾਈ-(uv_y_sample_interval-1)); y+=uv_y_sample_interval)
	{
		ਅਚਲ YUV_TYPE *y_ptr1=Y+y*Y_stride,
			*u_ptr=U+(y/uv_y_sample_interval)*UV_stride,
			*v_ptr=V+(y/uv_y_sample_interval)*UV_stride;

		#ਜੇ uv_y_sample_interval > 1
		ਅਚਲ YUV_TYPE *y_ptr2=Y+(y+1)*Y_stride;
		#ਜੇ_ਅੰਤ

		uint8_t *rgb_ptr1=RGB+y*RGB_stride;

		#ਜੇ uv_y_sample_interval > 1
		uint8_t *rgb_ptr2=RGB+(y+1)*RGB_stride;
		#ਜੇ_ਅੰਤ

		ਲਈ(x=0; x<(ਚੌੜਾਈ-(uv_x_sample_interval-1)); x+=uv_x_sample_interval)
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_ਵਿੱਥ);
			int32_t v_tmp = (GET(*v_ptr)-UV_ਵਿੱਥ);

			int32_t r_tmp = (v_tmp*param->v_r_ਗੁਣਕ);
			int32_t g_tmp = (u_tmp*param->u_g_ਗੁਣਕ + v_tmp*param->v_g_ਗੁਣਕ);
			int32_t b_tmp = (u_tmp*param->u_b_ਗੁਣਕ);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_ਖਿਸਕਾਓ)*param->y_ਗੁਣਕ);
			PACK_PIXEL(rgb_ptr1);

			#ਜੇ uv_x_sample_interval > 1
			y_tmp = (GET(y_ptr1[y_pixel_stride]-param->y_ਖਿਸਕਾਓ)*param->y_ਗੁਣਕ);
			PACK_PIXEL(rgb_ptr1);
			#ਜੇ_ਅੰਤ

			#ਜੇ uv_y_sample_interval > 1
			y_tmp = (GET(y_ptr2[0]-param->y_ਖਿਸਕਾਓ)*param->y_ਗੁਣਕ);
			PACK_PIXEL(rgb_ptr2);

			y_tmp = (GET(y_ptr2[y_pixel_stride]-param->y_ਖਿਸਕਾਓ)*param->y_ਗੁਣਕ);
			PACK_PIXEL(rgb_ptr2);
			#ਜੇ_ਅੰਤ

			#ਜੇ uv_x_sample_interval > 1
			y_ptr1+=2*y_pixel_stride;
			#ਨਹੀਂਤਾਂ
			y_ptr1+=y_pixel_stride;
			#ਜੇ_ਅੰਤ
			#ਜੇ uv_y_sample_interval > 1
			y_ptr2+=2*y_pixel_stride;
			#ਜੇ_ਅੰਤ
			#ਜੇ uv_x_sample_interval > 1
			u_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			#ਨਹੀਂਤਾਂ
			u_ptr+=uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=uv_pixel_stride/uv_x_sample_interval;
			#ਜੇ_ਅੰਤ
		}

		/* Catch the last pixel, if needed */
#ਜੇ uv_x_sample_interval == 2
		ਜੇ (x == (ਚੌੜਾਈ-1))
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_ਵਿੱਥ);
			int32_t v_tmp = (GET(*v_ptr)-UV_ਵਿੱਥ);

			int32_t r_tmp = (v_tmp*param->v_r_ਗੁਣਕ);
			int32_t g_tmp = (u_tmp*param->u_g_ਗੁਣਕ + v_tmp*param->v_g_ਗੁਣਕ);
			int32_t b_tmp = (u_tmp*param->u_b_ਗੁਣਕ);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_ਖਿਸਕਾਓ)*param->y_ਗੁਣਕ);
			PACK_PIXEL(rgb_ptr1);

			#ਜੇ uv_y_sample_interval > 1
			y_tmp = (GET(y_ptr2[0]-param->y_ਖਿਸਕਾਓ)*param->y_ਗੁਣਕ);
			PACK_PIXEL(rgb_ptr2);
			#ਜੇ_ਅੰਤ
		}
#ਜੇ_ਅੰਤ
	}

	/* Catch the last line, if needed */
#ਜੇ uv_y_sample_interval == 2
	ਜੇ (y == (ਉਚਾਈ-1))
	{
		ਅਚਲ YUV_TYPE *y_ptr1=Y+y*Y_stride,
			*u_ptr=U+(y/uv_y_sample_interval)*UV_stride,
			*v_ptr=V+(y/uv_y_sample_interval)*UV_stride;

		uint8_t *rgb_ptr1=RGB+y*RGB_stride;

		ਲਈ(x=0; x<(ਚੌੜਾਈ-(uv_x_sample_interval-1)); x+=uv_x_sample_interval)
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_ਵਿੱਥ);
			int32_t v_tmp = (GET(*v_ptr)-UV_ਵਿੱਥ);

			int32_t r_tmp = (v_tmp*param->v_r_ਗੁਣਕ);
			int32_t g_tmp = (u_tmp*param->u_g_ਗੁਣਕ + v_tmp*param->v_g_ਗੁਣਕ);
			int32_t b_tmp = (u_tmp*param->u_b_ਗੁਣਕ);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_ਖਿਸਕਾਓ)*param->y_ਗੁਣਕ);
			PACK_PIXEL(rgb_ptr1);

			y_tmp = (GET(y_ptr1[y_pixel_stride]-param->y_ਖਿਸਕਾਓ)*param->y_ਗੁਣਕ);
			PACK_PIXEL(rgb_ptr1);

			y_ptr1+=2*y_pixel_stride;
			u_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
		}

		/* Catch the last pixel, if needed */
#ਜੇ uv_x_sample_interval == 2
		ਜੇ (x == (ਚੌੜਾਈ-1))
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_ਵਿੱਥ);
			int32_t v_tmp = (GET(*v_ptr)-UV_ਵਿੱਥ);

			int32_t r_tmp = (v_tmp*param->v_r_ਗੁਣਕ);
			int32_t g_tmp = (u_tmp*param->u_g_ਗੁਣਕ + v_tmp*param->v_g_ਗੁਣਕ);
			int32_t b_tmp = (u_tmp*param->u_b_ਗੁਣਕ);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_ਖਿਸਕਾਓ)*param->y_ਗੁਣਕ);
			PACK_PIXEL(rgb_ptr1);
		}
#ਜੇ_ਅੰਤ
	}
#ਜੇ_ਅੰਤ

	#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ y_pixel_stride
	#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ uv_pixel_stride
	#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ uv_x_sample_interval
	#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ uv_y_sample_interval
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _MSC_VER
#ਹਦਾਇਤ warning(ਕੱਢੋ)
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ STD_FUNCTION_NAME
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ YUV_FORMAT
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ RGB_FORMAT
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ PACK_PIXEL
