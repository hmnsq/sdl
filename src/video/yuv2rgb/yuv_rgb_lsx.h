#ifdef SDL_LSX_INTRINSICS

#અન્તર્ભાવ "yuv_rgb_common.h"

//yuv420 to bgra, lsx implementation
શૂન્ય yuv420_rgb24_lsx(
	uint32_t width, uint32_t height,
	અચલ uint8_t *y, અચલ uint8_t *u, અચલ uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

શૂન્ય yuv420_rgba_lsx(
	uint32_t width, uint32_t height,
	અચલ uint8_t *y, અચલ uint8_t *v, અચલ uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

શૂન્ય yuv420_bgra_lsx(
	uint32_t width, uint32_t height,
	અચલ uint8_t *y, અચલ uint8_t *v, અચલ uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

શૂન્ય yuv420_argb_lsx(
	uint32_t width, uint32_t height,
	અચલ uint8_t *y, અચલ uint8_t *v, અચલ uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

શૂન્ય yuv420_abgr_lsx(
	uint32_t width, uint32_t height,
	અચલ uint8_t *y, અચલ uint8_t *v, અચલ uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

#endif  //SDL_LSX_INTRINSICS
