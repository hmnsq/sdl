#ifdef SDL_LSX_INTRINSICS

#অন্তর্ভাব "yuv_rgb_common.h"

//yuv420 to bgra, lsx implementation
শূন্য yuv420_rgb24_lsx(
	uint32_t width, uint32_t height,
	ধ্রুব uint8_t *y, ধ্রুব uint8_t *u, ধ্রুব uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

শূন্য yuv420_rgba_lsx(
	uint32_t width, uint32_t height,
	ধ্রুব uint8_t *y, ধ্রুব uint8_t *v, ধ্রুব uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

শূন্য yuv420_bgra_lsx(
	uint32_t width, uint32_t height,
	ধ্রুব uint8_t *y, ধ্রুব uint8_t *v, ধ্রুব uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

শূন্য yuv420_argb_lsx(
	uint32_t width, uint32_t height,
	ধ্রুব uint8_t *y, ধ্রুব uint8_t *v, ধ্রুব uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

শূন্য yuv420_abgr_lsx(
	uint32_t width, uint32_t height,
	ধ্রুব uint8_t *y, ধ্রুব uint8_t *v, ধ্রুব uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

#endif  //SDL_LSX_INTRINSICS
