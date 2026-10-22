#ifdef SDL_LSX_INTRINSICS

#अन्तर्भाव "yuv_rgb_common.h"

//yuv420 to bgra, lsx implementation
शून्य yuv420_rgb24_lsx(
	uint32_t width, uint32_t height,
	स्थिरांक uint8_t *y, स्थिरांक uint8_t *u, स्थिरांक uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

शून्य yuv420_rgba_lsx(
	uint32_t width, uint32_t height,
	स्थिरांक uint8_t *y, स्थिरांक uint8_t *v, स्थिरांक uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

शून्य yuv420_bgra_lsx(
	uint32_t width, uint32_t height,
	स्थिरांक uint8_t *y, स्थिरांक uint8_t *v, स्थिरांक uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

शून्य yuv420_argb_lsx(
	uint32_t width, uint32_t height,
	स्थिरांक uint8_t *y, स्थिरांक uint8_t *v, स्थिरांक uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

शून्य yuv420_abgr_lsx(
	uint32_t width, uint32_t height,
	स्थिरांक uint8_t *y, स्थिरांक uint8_t *v, स्थिरांक uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

#endif  //SDL_LSX_INTRINSICS
