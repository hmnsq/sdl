// Copyright 2016 Adrien Descamps
// Distributed under BSD 3-Clause License

/* You need to define the following macros before including this file:
	STD_FUNCTION_NAME
	YUV_FORMAT
	RGB_FORMAT
*/

#अगर RGB_FORMAT == RGB_FORMAT_RGB565

#घोषणा PACK_PIXEL(rgb_ptr) \
	*(Uint16 *)rgb_ptr = \
		((((Uint16)clampU8(y_tmp+r_tmp)) << 8 ) & 0xF800) | \
		((((Uint16)clampU8(y_tmp+g_tmp)) << 3) & 0x07E0) | \
		(((Uint16)clampU8(y_tmp+b_tmp)) >> 3); \
	rgb_ptr += 2

#या_अगर RGB_FORMAT == RGB_FORMAT_RGB24

#घोषणा PACK_PIXEL(rgb_ptr) \
	rgb_ptr[0] = clampU8(y_tmp+r_tmp); \
	rgb_ptr[1] = clampU8(y_tmp+g_tmp); \
	rgb_ptr[2] = clampU8(y_tmp+b_tmp); \
	rgb_ptr += 3

#या_अगर RGB_FORMAT == RGB_FORMAT_RGBA

#घोषणा PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 24) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 8) | \
		0x000000FF; \
	rgb_ptr += 4

#या_अगर RGB_FORMAT == RGB_FORMAT_BGRA

#घोषणा PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 24) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 8) | \
		0x000000FF; \
	rgb_ptr += 4

#या_अगर RGB_FORMAT == RGB_FORMAT_ARGB

#घोषणा PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xFF000000 | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 8) | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 0); \
	rgb_ptr += 4

#या_अगर RGB_FORMAT == RGB_FORMAT_ABGR

#घोषणा PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xFF000000 | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 8) | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 0); \
	rgb_ptr += 4

#या_अगर RGB_FORMAT == RGB_FORMAT_XBGR2101010

#घोषणा PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xC0000000 | \
		(((Uint32)clamp10(y_tmp+b_tmp)) << 20) | \
		(((Uint32)clamp10(y_tmp+g_tmp)) << 10) | \
		(((Uint32)clamp10(y_tmp+r_tmp)) << 0); \
	rgb_ptr += 4

#या_अगर RGB_FORMAT == RGB_FORMAT_RGB48

#घोषणा PACK_PIXEL(rgb_ptr) \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + r_tmp); \
	rgb_ptr += माप(Uint16);				   \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + g_tmp); \
	rgb_ptr += माप(Uint16);				   \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + b_tmp); \
	rgb_ptr += माप(Uint16)

#अन्यथा
#त्रुटि PACK_PIXEL unimplemented
#पूर्ण_अगर


#अगर_घोषित _MSC_VER /* Visual Studio analyzer can't tell that we're building this with different constants */
#आशय warning(धकेलो)
#आशय warning(disable : 6239)
#पूर्ण_अगर

#अघोषित YUV_TYPE
#अगर YUV_BITS > 8
#घोषणा YUV_TYPE	uint16_t
#अन्यथा
#घोषणा YUV_TYPE	uint8_t
#पूर्ण_अगर
#अघोषित UV_OFFSET
#घोषणा UV_OFFSET	(1 << ((YUV_BITS)-1))

#अघोषित GET
#अगर YUV_BITS == 10
#घोषणा GET(X)	((X) >> 6)
#अन्यथा
#घोषणा GET(X)	(X)
#पूर्ण_अगर

व्योम STD_FUNCTION_NAME(
	uint32_t width, uint32_t height,
	स्थिर YUV_TYPE *Y, स्थिर YUV_TYPE *U, स्थिर YUV_TYPE *V, uint32_t Y_stride, uint32_t UV_stride,
	uint8_t *RGB, uint32_t RGB_stride,
	YCbCrType yuv_type)
{
	स्थिर YUV2RGBParam *स्थिर param = &(YUV2RGB[yuv_type]);
#अगर YUV_FORMAT == YUV_FORMAT_420
	#घोषणा y_pixel_stride 1
	#घोषणा uv_pixel_stride 1
	#घोषणा uv_x_sample_interval 2
	#घोषणा uv_y_sample_interval 2
#या_अगर YUV_FORMAT == YUV_FORMAT_422
	#घोषणा y_pixel_stride 2
	#घोषणा uv_pixel_stride 4
	#घोषणा uv_x_sample_interval 2
	#घोषणा uv_y_sample_interval 1
#या_अगर YUV_FORMAT == YUV_FORMAT_444
	#घोषणा y_pixel_stride 1
	#घोषणा uv_pixel_stride 1
	#घोषणा uv_x_sample_interval 1
	#घोषणा uv_y_sample_interval 1
#या_अगर YUV_FORMAT == YUV_FORMAT_NV12
	#घोषणा y_pixel_stride 1
	#घोषणा uv_pixel_stride 2
	#घोषणा uv_x_sample_interval 2
	#घोषणा uv_y_sample_interval 2
#पूर्ण_अगर

	Y_stride /= माप(YUV_TYPE);
	UV_stride /= माप(YUV_TYPE);

	uint32_t x, y;
	क्रम(y=0; y<(height-(uv_y_sample_interval-1)); y+=uv_y_sample_interval)
	{
		स्थिर YUV_TYPE *y_ptr1=Y+y*Y_stride,
			*u_ptr=U+(y/uv_y_sample_interval)*UV_stride,
			*v_ptr=V+(y/uv_y_sample_interval)*UV_stride;

		#अगर uv_y_sample_interval > 1
		स्थिर YUV_TYPE *y_ptr2=Y+(y+1)*Y_stride;
		#पूर्ण_अगर

		uint8_t *rgb_ptr1=RGB+y*RGB_stride;

		#अगर uv_y_sample_interval > 1
		uint8_t *rgb_ptr2=RGB+(y+1)*RGB_stride;
		#पूर्ण_अगर

		क्रम(x=0; x<(width-(uv_x_sample_interval-1)); x+=uv_x_sample_interval)
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

			#अगर uv_x_sample_interval > 1
			y_tmp = (GET(y_ptr1[y_pixel_stride]-param->y_shift)*param->y_factor);
			PACK_PIXEL(rgb_ptr1);
			#पूर्ण_अगर

			#अगर uv_y_sample_interval > 1
			y_tmp = (GET(y_ptr2[0]-param->y_shift)*param->y_factor);
			PACK_PIXEL(rgb_ptr2);

			y_tmp = (GET(y_ptr2[y_pixel_stride]-param->y_shift)*param->y_factor);
			PACK_PIXEL(rgb_ptr2);
			#पूर्ण_अगर

			#अगर uv_x_sample_interval > 1
			y_ptr1+=2*y_pixel_stride;
			#अन्यथा
			y_ptr1+=y_pixel_stride;
			#पूर्ण_अगर
			#अगर uv_y_sample_interval > 1
			y_ptr2+=2*y_pixel_stride;
			#पूर्ण_अगर
			#अगर uv_x_sample_interval > 1
			u_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			#अन्यथा
			u_ptr+=uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=uv_pixel_stride/uv_x_sample_interval;
			#पूर्ण_अगर
		}

		/* Catch the last pixel, if needed */
#अगर uv_x_sample_interval == 2
		अगर (x == (width-1))
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

			#अगर uv_y_sample_interval > 1
			y_tmp = (GET(y_ptr2[0]-param->y_shift)*param->y_factor);
			PACK_PIXEL(rgb_ptr2);
			#पूर्ण_अगर
		}
#पूर्ण_अगर
	}

	/* Catch the last line, if needed */
#अगर uv_y_sample_interval == 2
	अगर (y == (height-1))
	{
		स्थिर YUV_TYPE *y_ptr1=Y+y*Y_stride,
			*u_ptr=U+(y/uv_y_sample_interval)*UV_stride,
			*v_ptr=V+(y/uv_y_sample_interval)*UV_stride;

		uint8_t *rgb_ptr1=RGB+y*RGB_stride;

		क्रम(x=0; x<(width-(uv_x_sample_interval-1)); x+=uv_x_sample_interval)
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
#अगर uv_x_sample_interval == 2
		अगर (x == (width-1))
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
#पूर्ण_अगर
	}
#पूर्ण_अगर

	#अघोषित y_pixel_stride
	#अघोषित uv_pixel_stride
	#अघोषित uv_x_sample_interval
	#अघोषित uv_y_sample_interval
}

#अगर_घोषित _MSC_VER
#आशय warning(निकालो)
#पूर्ण_अगर

#अघोषित STD_FUNCTION_NAME
#अघोषित YUV_FORMAT
#अघोषित RGB_FORMAT
#अघोषित PACK_PIXEL
