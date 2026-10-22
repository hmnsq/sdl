// Copyright 2016 Adrien Descamps
// Distributed under BSD 3-Clause License

/* You need to define the following macros before including this file:
	STD_FUNCTION_NAME
	YUV_FORMAT
	RGB_FORMAT
*/

#ఒకవేళ RGB_FORMAT == RGB_FORMAT_RGB565

#నిర్వచించు PACK_PIXEL(rgb_ptr) \
	*(Uint16 *)rgb_ptr = \
		((((Uint16)clampU8(y_tmp+r_tmp)) << 8 ) & 0xF800) | \
		((((Uint16)clampU8(y_tmp+g_tmp)) << 3) & 0x07E0) | \
		(((Uint16)clampU8(y_tmp+b_tmp)) >> 3); \
	rgb_ptr += 2

#లేదావేళ RGB_FORMAT == RGB_FORMAT_RGB24

#నిర్వచించు PACK_PIXEL(rgb_ptr) \
	rgb_ptr[0] = clampU8(y_tmp+r_tmp); \
	rgb_ptr[1] = clampU8(y_tmp+g_tmp); \
	rgb_ptr[2] = clampU8(y_tmp+b_tmp); \
	rgb_ptr += 3

#లేదావేళ RGB_FORMAT == RGB_FORMAT_RGBA

#నిర్వచించు PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 24) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 8) | \
		0x000000FF; \
	rgb_ptr += 4

#లేదావేళ RGB_FORMAT == RGB_FORMAT_BGRA

#నిర్వచించు PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 24) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 8) | \
		0x000000FF; \
	rgb_ptr += 4

#లేదావేళ RGB_FORMAT == RGB_FORMAT_ARGB

#నిర్వచించు PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xFF000000 | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 8) | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 0); \
	rgb_ptr += 4

#లేదావేళ RGB_FORMAT == RGB_FORMAT_ABGR

#నిర్వచించు PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xFF000000 | \
		(((Uint32)clampU8(y_tmp+b_tmp)) << 16) | \
		(((Uint32)clampU8(y_tmp+g_tmp)) << 8) | \
		(((Uint32)clampU8(y_tmp+r_tmp)) << 0); \
	rgb_ptr += 4

#లేదావేళ RGB_FORMAT == RGB_FORMAT_XBGR2101010

#నిర్వచించు PACK_PIXEL(rgb_ptr) \
	*(Uint32 *)rgb_ptr = \
		0xC0000000 | \
		(((Uint32)clamp10(y_tmp+b_tmp)) << 20) | \
		(((Uint32)clamp10(y_tmp+g_tmp)) << 10) | \
		(((Uint32)clamp10(y_tmp+r_tmp)) << 0); \
	rgb_ptr += 4

#లేదావేళ RGB_FORMAT == RGB_FORMAT_RGB48

#నిర్వచించు PACK_PIXEL(rgb_ptr) \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + r_tmp); \
	rgb_ptr += పరిమాణం(Uint16);				   \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + g_tmp); \
	rgb_ptr += పరిమాణం(Uint16);				   \
	*(Uint16 *)rgb_ptr = clamp16(y_tmp + b_tmp); \
	rgb_ptr += పరిమాణం(Uint16)

#లేకపోతే
#దోషం PACK_PIXEL unimplemented
#అయితే_ముగింపు


#నిర్వచితమైతే _MSC_VER /* Visual Studio analyzer can't tell that we're building this with different constants */
#సూచన warning(నెట్టు)
#సూచన warning(disable : 6239)
#అయితే_ముగింపు

#నిర్వచనం_రద్దు YUV_TYPE
#ఒకవేళ YUV_బిట్లు > 8
#నిర్వచించు YUV_TYPE	uint16_t
#లేకపోతే
#నిర్వచించు YUV_TYPE	uint8_t
#అయితే_ముగింపు
#నిర్వచనం_రద్దు UV_స్థానభ్రంశం
#నిర్వచించు UV_స్థానభ్రంశం	(1 << ((YUV_బిట్లు)-1))

#నిర్వచనం_రద్దు GET
#ఒకవేళ YUV_బిట్లు == 10
#నిర్వచించు GET(X)	((X) >> 6)
#లేకపోతే
#నిర్వచించు GET(X)	(X)
#అయితే_ముగింపు

శూన్య STD_FUNCTION_NAME(
	uint32_t వెడల్పు, uint32_t ఎత్తు,
	స్థిరరాశి YUV_TYPE *Y, స్థిరరాశి YUV_TYPE *U, స్థిరరాశి YUV_TYPE *V, uint32_t Y_stride, uint32_t UV_stride,
	uint8_t *RGB, uint32_t RGB_stride,
	YCbCrType yuv_type)
{
	స్థిరరాశి YUV2RGBParam *స్థిరరాశి param = &(YUV2RGB[yuv_type]);
#ఒకవేళ YUV_FORMAT == YUV_FORMAT_420
	#నిర్వచించు y_pixel_stride 1
	#నిర్వచించు uv_pixel_stride 1
	#నిర్వచించు uv_x_sample_interval 2
	#నిర్వచించు uv_y_sample_interval 2
#లేదావేళ YUV_FORMAT == YUV_FORMAT_422
	#నిర్వచించు y_pixel_stride 2
	#నిర్వచించు uv_pixel_stride 4
	#నిర్వచించు uv_x_sample_interval 2
	#నిర్వచించు uv_y_sample_interval 1
#లేదావేళ YUV_FORMAT == YUV_FORMAT_444
	#నిర్వచించు y_pixel_stride 1
	#నిర్వచించు uv_pixel_stride 1
	#నిర్వచించు uv_x_sample_interval 1
	#నిర్వచించు uv_y_sample_interval 1
#లేదావేళ YUV_FORMAT == YUV_FORMAT_NV12
	#నిర్వచించు y_pixel_stride 1
	#నిర్వచించు uv_pixel_stride 2
	#నిర్వచించు uv_x_sample_interval 2
	#నిర్వచించు uv_y_sample_interval 2
#అయితే_ముగింపు

	Y_stride /= పరిమాణం(YUV_TYPE);
	UV_stride /= పరిమాణం(YUV_TYPE);

	uint32_t x, y;
	కొరకు(y=0; y<(ఎత్తు-(uv_y_sample_interval-1)); y+=uv_y_sample_interval)
	{
		స్థిరరాశి YUV_TYPE *y_ptr1=Y+y*Y_stride,
			*u_ptr=U+(y/uv_y_sample_interval)*UV_stride,
			*v_ptr=V+(y/uv_y_sample_interval)*UV_stride;

		#ఒకవేళ uv_y_sample_interval > 1
		స్థిరరాశి YUV_TYPE *y_ptr2=Y+(y+1)*Y_stride;
		#అయితే_ముగింపు

		uint8_t *rgb_ptr1=RGB+y*RGB_stride;

		#ఒకవేళ uv_y_sample_interval > 1
		uint8_t *rgb_ptr2=RGB+(y+1)*RGB_stride;
		#అయితే_ముగింపు

		కొరకు(x=0; x<(వెడల్పు-(uv_x_sample_interval-1)); x+=uv_x_sample_interval)
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_స్థానభ్రంశం);
			int32_t v_tmp = (GET(*v_ptr)-UV_స్థానభ్రంశం);

			int32_t r_tmp = (v_tmp*param->v_r_గుణకం);
			int32_t g_tmp = (u_tmp*param->u_g_గుణకం + v_tmp*param->v_g_గుణకం);
			int32_t b_tmp = (u_tmp*param->u_b_గుణకం);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_జరుపు)*param->y_గుణకం);
			PACK_PIXEL(rgb_ptr1);

			#ఒకవేళ uv_x_sample_interval > 1
			y_tmp = (GET(y_ptr1[y_pixel_stride]-param->y_జరుపు)*param->y_గుణకం);
			PACK_PIXEL(rgb_ptr1);
			#అయితే_ముగింపు

			#ఒకవేళ uv_y_sample_interval > 1
			y_tmp = (GET(y_ptr2[0]-param->y_జరుపు)*param->y_గుణకం);
			PACK_PIXEL(rgb_ptr2);

			y_tmp = (GET(y_ptr2[y_pixel_stride]-param->y_జరుపు)*param->y_గుణకం);
			PACK_PIXEL(rgb_ptr2);
			#అయితే_ముగింపు

			#ఒకవేళ uv_x_sample_interval > 1
			y_ptr1+=2*y_pixel_stride;
			#లేకపోతే
			y_ptr1+=y_pixel_stride;
			#అయితే_ముగింపు
			#ఒకవేళ uv_y_sample_interval > 1
			y_ptr2+=2*y_pixel_stride;
			#అయితే_ముగింపు
			#ఒకవేళ uv_x_sample_interval > 1
			u_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			#లేకపోతే
			u_ptr+=uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=uv_pixel_stride/uv_x_sample_interval;
			#అయితే_ముగింపు
		}

		/* Catch the last pixel, if needed */
#ఒకవేళ uv_x_sample_interval == 2
		ఒకవేళ (x == (వెడల్పు-1))
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_స్థానభ్రంశం);
			int32_t v_tmp = (GET(*v_ptr)-UV_స్థానభ్రంశం);

			int32_t r_tmp = (v_tmp*param->v_r_గుణకం);
			int32_t g_tmp = (u_tmp*param->u_g_గుణకం + v_tmp*param->v_g_గుణకం);
			int32_t b_tmp = (u_tmp*param->u_b_గుణకం);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_జరుపు)*param->y_గుణకం);
			PACK_PIXEL(rgb_ptr1);

			#ఒకవేళ uv_y_sample_interval > 1
			y_tmp = (GET(y_ptr2[0]-param->y_జరుపు)*param->y_గుణకం);
			PACK_PIXEL(rgb_ptr2);
			#అయితే_ముగింపు
		}
#అయితే_ముగింపు
	}

	/* Catch the last line, if needed */
#ఒకవేళ uv_y_sample_interval == 2
	ఒకవేళ (y == (ఎత్తు-1))
	{
		స్థిరరాశి YUV_TYPE *y_ptr1=Y+y*Y_stride,
			*u_ptr=U+(y/uv_y_sample_interval)*UV_stride,
			*v_ptr=V+(y/uv_y_sample_interval)*UV_stride;

		uint8_t *rgb_ptr1=RGB+y*RGB_stride;

		కొరకు(x=0; x<(వెడల్పు-(uv_x_sample_interval-1)); x+=uv_x_sample_interval)
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_స్థానభ్రంశం);
			int32_t v_tmp = (GET(*v_ptr)-UV_స్థానభ్రంశం);

			int32_t r_tmp = (v_tmp*param->v_r_గుణకం);
			int32_t g_tmp = (u_tmp*param->u_g_గుణకం + v_tmp*param->v_g_గుణకం);
			int32_t b_tmp = (u_tmp*param->u_b_గుణకం);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_జరుపు)*param->y_గుణకం);
			PACK_PIXEL(rgb_ptr1);

			y_tmp = (GET(y_ptr1[y_pixel_stride]-param->y_జరుపు)*param->y_గుణకం);
			PACK_PIXEL(rgb_ptr1);

			y_ptr1+=2*y_pixel_stride;
			u_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
			v_ptr+=2*uv_pixel_stride/uv_x_sample_interval;
		}

		/* Catch the last pixel, if needed */
#ఒకవేళ uv_x_sample_interval == 2
		ఒకవేళ (x == (వెడల్పు-1))
		{
			// Compute U and V contributions, common to the four pixels

			int32_t u_tmp = (GET(*u_ptr)-UV_స్థానభ్రంశం);
			int32_t v_tmp = (GET(*v_ptr)-UV_స్థానభ్రంశం);

			int32_t r_tmp = (v_tmp*param->v_r_గుణకం);
			int32_t g_tmp = (u_tmp*param->u_g_గుణకం + v_tmp*param->v_g_గుణకం);
			int32_t b_tmp = (u_tmp*param->u_b_గుణకం);

			// Compute the Y contribution for each pixel

			int32_t y_tmp = (GET(y_ptr1[0]-param->y_జరుపు)*param->y_గుణకం);
			PACK_PIXEL(rgb_ptr1);
		}
#అయితే_ముగింపు
	}
#అయితే_ముగింపు

	#నిర్వచనం_రద్దు y_pixel_stride
	#నిర్వచనం_రద్దు uv_pixel_stride
	#నిర్వచనం_రద్దు uv_x_sample_interval
	#నిర్వచనం_రద్దు uv_y_sample_interval
}

#నిర్వచితమైతే _MSC_VER
#సూచన warning(తీయి)
#అయితే_ముగింపు

#నిర్వచనం_రద్దు STD_FUNCTION_NAME
#నిర్వచనం_రద్దు YUV_FORMAT
#నిర్వచనం_రద్దు RGB_FORMAT
#నిర్వచనం_రద్దు PACK_PIXEL
