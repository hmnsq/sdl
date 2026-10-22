#ifdef SDL_LSX_INTRINSICS

#ଅନ୍ତର୍ଭାଵ "yuv_rgb_common.h"

//yuv420 to bgra, lsx implementation
ଶୂନ୍ୟ yuv420_rgb24_lsx(
	uint32_t width, uint32_t height,
	ଅଚଳ uint8_t *y, ଅଚଳ uint8_t *u, ଅଚଳ uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

ଶୂନ୍ୟ yuv420_rgba_lsx(
	uint32_t width, uint32_t height,
	ଅଚଳ uint8_t *y, ଅଚଳ uint8_t *v, ଅଚଳ uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

ଶୂନ୍ୟ yuv420_bgra_lsx(
	uint32_t width, uint32_t height,
	ଅଚଳ uint8_t *y, ଅଚଳ uint8_t *v, ଅଚଳ uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

ଶୂନ୍ୟ yuv420_argb_lsx(
	uint32_t width, uint32_t height,
	ଅଚଳ uint8_t *y, ଅଚଳ uint8_t *v, ଅଚଳ uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

ଶୂନ୍ୟ yuv420_abgr_lsx(
	uint32_t width, uint32_t height,
	ଅଚଳ uint8_t *y, ଅଚଳ uint8_t *v, ଅଚଳ uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

#endif  //SDL_LSX_INTRINSICS
