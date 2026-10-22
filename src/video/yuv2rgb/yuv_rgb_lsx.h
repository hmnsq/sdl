#अगर_घोषित SDL_LSX_INTRINSICS

#समावेश "yuv_rgb_common.h"

//yuv420 to bgra, lsx implementation
व्योम yuv420_rgb24_lsx(
	uint32_t width, uint32_t height,
	स्थिर uint8_t *y, स्थिर uint8_t *u, स्थिर uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

व्योम yuv420_rgba_lsx(
	uint32_t width, uint32_t height,
	स्थिर uint8_t *y, स्थिर uint8_t *v, स्थिर uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

व्योम yuv420_bgra_lsx(
	uint32_t width, uint32_t height,
	स्थिर uint8_t *y, स्थिर uint8_t *v, स्थिर uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

व्योम yuv420_argb_lsx(
	uint32_t width, uint32_t height,
	स्थिर uint8_t *y, स्थिर uint8_t *v, स्थिर uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

व्योम yuv420_abgr_lsx(
	uint32_t width, uint32_t height,
	स्थिर uint8_t *y, स्थिर uint8_t *v, स्थिर uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

#पूर्ण_अगर  //SDL_LSX_INTRINSICS
