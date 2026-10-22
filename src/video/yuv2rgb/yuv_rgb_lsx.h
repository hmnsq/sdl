#ifdef SDL_LSX_INTRINSICS

#அந்தர்பாவ "yuv_rgb_common.h"

//yuv420 to bgra, lsx implementation
வெறுமை yuv420_rgb24_lsx(
	uint32_t width, uint32_t height,
	மாறிலி uint8_t *y, மாறிலி uint8_t *u, மாறிலி uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

வெறுமை yuv420_rgba_lsx(
	uint32_t width, uint32_t height,
	மாறிலி uint8_t *y, மாறிலி uint8_t *v, மாறிலி uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

வெறுமை yuv420_bgra_lsx(
	uint32_t width, uint32_t height,
	மாறிலி uint8_t *y, மாறிலி uint8_t *v, மாறிலி uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

வெறுமை yuv420_argb_lsx(
	uint32_t width, uint32_t height,
	மாறிலி uint8_t *y, மாறிலி uint8_t *v, மாறிலி uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

வெறுமை yuv420_abgr_lsx(
	uint32_t width, uint32_t height,
	மாறிலி uint8_t *y, மாறிலி uint8_t *v, மாறிலி uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

#endif  //SDL_LSX_INTRINSICS
