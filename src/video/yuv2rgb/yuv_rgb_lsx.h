#که_تعریف_شوی SDL_LSX_INTRINSICS

#ضمن "yuv_rgb_common.h"

//yuv420 to bgra, lsx implementation
فراغ yuv420_rgb24_lsx(
	uint32_t پلنوالی, uint32_t لوړوالی,
	ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

فراغ yuv420_rgba_lsx(
	uint32_t پلنوالی, uint32_t لوړوالی,
	ثابت uint8_t *y, ثابت uint8_t *v, ثابت uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

فراغ yuv420_bgra_lsx(
	uint32_t پلنوالی, uint32_t لوړوالی,
	ثابت uint8_t *y, ثابت uint8_t *v, ثابت uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

فراغ yuv420_argb_lsx(
	uint32_t پلنوالی, uint32_t لوړوالی,
	ثابت uint8_t *y, ثابت uint8_t *v, ثابت uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

فراغ yuv420_abgr_lsx(
	uint32_t پلنوالی, uint32_t لوړوالی,
	ثابت uint8_t *y, ثابت uint8_t *v, ثابت uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

#د_که_پای  //SDL_LSX_INTRINSICS
