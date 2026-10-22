// Copyright 2016 Adrien Descamps
// Distributed under BSD 3-Clause License

/* You need to define the following macros before including this file:
	STD_FUNCTION_NAME
	YUV_FORMAT
	RGB_FORMAT
*/

#यदि RGB_FORMAT == RGB_FORMAT_RGB565

#परिभाषय PACK_PIXEL(rgb_ptr) \
	*(Uint16 *)rgb_ptr = \
		((((Uint16)clampU8(y_tmp+r_tmp)) << 8 ) & 0xF800) | \
		((((Uint16)clampU8(y_tmp+g_tmp)) << 3) & 0x07E0) | \
		(((Uint16)clampU8(y_tmp+b_tmp)) >> 3); \
	rgb_ptr += 2

#नोचेद्यदि RGB_FORMAT == RGB_FORMAT_RGB24

#परिभाषय PACK_PIXEL(rgb_ptr) \
	rgb_ptr[0] = clampU8(y_tmp+r_tmp); \
	rgb_ptr[1] = clampU8(y_tmp+g_tmp); \
	rgb_ptr[2] = clampU8(y_tmp+b_tmp); \
	rgb_ptr += 3

#नोचेद्यदि RGB_FORMAT == RGB_FORMAT_RGBA

#परिभाषय PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 24) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 8) | \
		0x000000FF; \
	rgb_ptr += 4

#नोचेद्यदि RGB_FORMAT == RGB_FORMAT_BGRA

#परिभाषय PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 24) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 8) | \
		0x000000FF; \
	rgb_ptr += 4

#नोचेद्यदि RGB_FORMAT == RGB_FORMAT_ARGB

#परिभाषय PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xFF000000 | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 8) | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 0); \
	rgb_ptr += 4

#नोचेद्यदि RGB_FORMAT == RGB_FORMAT_ABGR

#परिभाषय PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xFF000000 | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 8) | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 0); \
	rgb_ptr += 4

#नोचेद्यदि RGB_FORMAT == RGB_FORMAT_XBGR2101010

#परिभाषय PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xC0000000 | \
		(((Uint32)clamp10(y_tmp+b_tmp)) << 20) | \
		(((Uint32)clamp10(y_tmp+g_tmp)) << 10) | \
		(((Uint32)clamp10(y_tmp+r_tmp)) << 0); \
	rgb_ptr += 4

#नोचेद्यदि RGB_FORMAT == RGB_FORMAT_RGB48

#परिभाषय PACK_PIXEL(rgb_ptr) \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + r_tmp); \
	rgb_ptr += परिमाण(Uint16);				   \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + g_tmp); \
	rgb_ptr += परिमाण(Uint16);				   \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + b_tmp); \
	rgb_ptr += परिमाण(Uint16)

#अन्यथा
#दोषः PACK_PIXEL unimplemented
#यदि_अन्तः


#यदि_परिभाषितम् _MSC_VER /* Visual Studio analyzer can't tell that we're building this with different constants */
#निर्देशः warning(प्रक्षिप)
#निर्देशः warning(disable : 6239)
#यदि_अन्तः

#अपरिभाषय YUV_TYPE
#यदि YUV_द्वयङ्काः > 8
#परिभाषय YUV_TYPE	uint16_t
#अन्यथा
#परिभाषय YUV_TYPE	uint8_t
#यदि_अन्तः
#अपरिभाषय UV_विस्थापनम्
#परिभाषय UV_विस्थापनम्	(1 << ((YUV_द्वयङ्काः)-1))

#अपरिभाषय GET
#यदि YUV_द्वयङ्काः == 10
#परिभाषय GET(X)	((X) >> 6)
#अन्यथा
#परिभाषय GET(X)	(X)
#यदि_अन्तः

शून्य STD_FUNCTION_NAME(
	uint32_t विस्तारः, uint32_t height,
	ध्रुव YUV_TYPE *Y, ध्रुव YUV_TYPE *U, ध्रुव YUV_TYPE *V, uint32_t Y_stride, uint32_t UV_stride,
	uint8_t *RGB, uint32_t RGB_stride,
	YCbCrType yuv_type)
{
	ध्रुव YUV2RGBParam *ध्रुव param = &(YUV2RGB[yuv_type]);
#यदि YUV_FORMAT == YUV_FORMAT_420
	#परिभाषय y_pixel_stride 1
	#परिभाषय uv_pixel_stride 1
	#परिभाषय uv_x_sample_interval 2
	#परिभाषय uv_y_sample_interval 2
#नोचेद्यदि YUV_FORMAT == YUV_FORMAT_422
	#परिभाषय y_pixel_stride 2
	#परिभाषय uv_pixel_stride 4
	#परिभाषय uv_x_sample_interval 2
	#परिभाषय uv_y_sample_interval 1
#नोचेद्यदि YUV_FORMAT == YUV_FORMAT_444
	#परिभाषय y_pixel_stride 1
	#परिभाषय uv_pixel_stride 1
	#परिभाषय uv_x_sample_interval 1
	#परिभाषय uv_y_sample_interval 1
#नोचेद्यदि YUV_FORMAT == YUV_FORMAT_NV12
	#परिभाषय y_pixel_stride 1
	#परिभाषय uv_pixel_stride 2
	#परिभाषय uv_x_sample_interval 2
	#परिभाषय uv_y_sample_interval 2
#यदि_अन्तः

	Y_stride /= परिमाण(YUV_TYPE);
	UV_stride /= परिमाण(YUV_TYPE);

	uint32_t x, y;
	प्रति(y=0; y<(height-(uv_y_sample_interval-1)); y+=uv_y_sample_interval)
	{
		ध्रुव YUV_TYPE *y_ptr1=Y+y*Y_stride,
			*u_ptr=U+(y/uv_y_sample_interval)*UV_stride,
			*v_ptr=V+(y/uv_y_sample_interval)*UV_stride;

		#यदि uv_y_sample_interval > 1
		ध्रुव YUV_TYPE *y_ptr2=Y+(y+1)*Y_stride;
		#यदि_अन्तः

		uint8_t *rgb_ptr1=RGB+y*RGB_stride;

		#यदि uv_y_sample_interval > 1
		uint8_t *rgb_ptr2=RGB+(y+1)*RGB_stride;
		#यदि_अन्तः

		प्रति(x=0; x<(विस्तारः-(uv_x_sample_interval-1)); x+=uv_x_sample_interval)
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_विस्थापनम्);
			int32_t v_tmp = (GET(*v_ptr)-UV_विस्थापनम्);

			int32_t r_tmp = (v_tmp*param->v_r_गुणकः);
			int32_t g_tmp = (u_tmp*param->u_g_गुणकः + v_tmp*param->v_g_गुणकः);
			int32_t b_tmp = (u_tmp*param->u_b_गुणकः);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_सरणम्)*param->y_गुणकः);
			PACK_PIXEL(rgb_ptr1);

			#यदि uv_x_sample_interval > 1
			y_tmp = (GET(y_ptr1[y_pixel_stride]-param->y_सरणम्)*param->y_गुणकः);
			PACK_PIXEL(rgb_ptr1);
			#यदि_अन्तः

			#यदि uv_y_sample_interval > 1
			y_tmp = (GET(y_ptr2[0]-param->y_सरणम्)*param->y_गुणकः);
			PACK_PIXEL(rgb_ptr2);

			y_tmp = (GET(y_ptr2[y_pixel_stride]-param->y_सरणम्)*param->y_गुणकः);
			PACK_PIXEL(rgb_ptr2);
			#यदि_अन्तः

			#यदि uv_x_sample_interval > 1
			y_ptr1+=2*y_pixel_stride;
			#अन्यथा
			y_ptr1+=y_pixel_stride;
			#यदि_अन्तः
			#यदि uv_y_sample_interval > 1
			y_ptr2+=2*y_pixel_stride;
			#यदि_अन्तः
			#यदि uv_x_sample_interval > 1
			u_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			#अन्यथा
			u_ptr+=uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=uv_pixel_stride/uv_x_sample_interval;
			#यदि_अन्तः
		}

		/* Catch the last pixel, if needed */
#यदि uv_x_sample_interval == 2
		यदि (x == (विस्तारः-1))
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_विस्थापनम्);
			int32_t v_tmp = (GET(*v_ptr)-UV_विस्थापनम्);

			int32_t r_tmp = (v_tmp*param->v_r_गुणकः);
			int32_t g_tmp = (u_tmp*param->u_g_गुणकः + v_tmp*param->v_g_गुणकः);
			int32_t b_tmp = (u_tmp*param->u_b_गुणकः);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_सरणम्)*param->y_गुणकः);
			PACK_PIXEL(rgb_ptr1);

			#यदि uv_y_sample_interval > 1
			y_tmp = (GET(y_ptr2[0]-param->y_सरणम्)*param->y_गुणकः);
			PACK_PIXEL(rgb_ptr2);
			#यदि_अन्तः
		}
#यदि_अन्तः
	}

	/* Catch the last line, if needed */
#यदि uv_y_sample_interval == 2
	यदि (y == (height-1))
	{
		ध्रुव YUV_TYPE *y_ptr1=Y+y*Y_stride,
			*u_ptr=U+(y/uv_y_sample_interval)*UV_stride,
			*v_ptr=V+(y/uv_y_sample_interval)*UV_stride;

		uint8_t *rgb_ptr1=RGB+y*RGB_stride;

		प्रति(x=0; x<(विस्तारः-(uv_x_sample_interval-1)); x+=uv_x_sample_interval)
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_विस्थापनम्);
			int32_t v_tmp = (GET(*v_ptr)-UV_विस्थापनम्);

			int32_t r_tmp = (v_tmp*param->v_r_गुणकः);
			int32_t g_tmp = (u_tmp*param->u_g_गुणकः + v_tmp*param->v_g_गुणकः);
			int32_t b_tmp = (u_tmp*param->u_b_गुणकः);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_सरणम्)*param->y_गुणकः);
			PACK_PIXEL(rgb_ptr1);

			y_tmp = (GET(y_ptr1[y_pixel_stride]-param->y_सरणम्)*param->y_गुणकः);
			PACK_PIXEL(rgb_ptr1);

			y_ptr1+=2*y_pixel_stride;
			u_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
		}

		/* Catch the last pixel, if needed */
#यदि uv_x_sample_interval == 2
		यदि (x == (विस्तारः-1))
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_विस्थापनम्);
			int32_t v_tmp = (GET(*v_ptr)-UV_विस्थापनम्);

			int32_t r_tmp = (v_tmp*param->v_r_गुणकः);
			int32_t g_tmp = (u_tmp*param->u_g_गुणकः + v_tmp*param->v_g_गुणकः);
			int32_t b_tmp = (u_tmp*param->u_b_गुणकः);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_सरणम्)*param->y_गुणकः);
			PACK_PIXEL(rgb_ptr1);
		}
#यदि_अन्तः
	}
#यदि_अन्तः

	#अपरिभाषय y_pixel_stride
	#अपरिभाषय uv_pixel_stride
	#अपरिभाषय uv_x_sample_interval
	#अपरिभाषय uv_y_sample_interval
}

#यदि_परिभाषितम् _MSC_VER
#निर्देशः warning(निष्कासय)
#यदि_अन्तः

#अपरिभाषय STD_FUNCTION_NAME
#अपरिभाषय YUV_FORMAT
#अपरिभाषय RGB_FORMAT
#अपरिभाषय PACK_PIXEL
