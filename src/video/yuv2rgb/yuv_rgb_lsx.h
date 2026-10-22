#جيڪڏهن_وصف_ٿيل SDL_LSX_INTRINSICS

#ضمن "yuv_rgb_common.h"

//yuv420 to bgra, lsx implementation
فراغ yuv420_rgb24_lsx(
	uint32_t ويڪر, uint32_t اوچائي,
	ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

فراغ yuv420_rgba_lsx(
	uint32_t ويڪر, uint32_t اوچائي,
	ثابت uint8_t *y, ثابت uint8_t *v, ثابت uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

فراغ yuv420_bgra_lsx(
	uint32_t ويڪر, uint32_t اوچائي,
	ثابت uint8_t *y, ثابت uint8_t *v, ثابت uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

فراغ yuv420_argb_lsx(
	uint32_t ويڪر, uint32_t اوچائي,
	ثابت uint8_t *y, ثابت uint8_t *v, ثابت uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

فراغ yuv420_abgr_lsx(
	uint32_t ويڪر, uint32_t اوچائي,
	ثابت uint8_t *y, ثابت uint8_t *v, ثابت uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

#جيڪڏهن_پورو  //SDL_LSX_INTRINSICS
