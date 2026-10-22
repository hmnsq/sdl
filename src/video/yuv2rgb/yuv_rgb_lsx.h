#ifdef SDL_LSX_INTRINSICS

#അന്തര്ഭാവ "yuv_rgb_common.h"

//yuv420 to bgra, lsx implementation
ശൂന്യം yuv420_rgb24_lsx(
	uint32_t width, uint32_t height,
	സ്ഥിരം uint8_t *y, സ്ഥിരം uint8_t *u, സ്ഥിരം uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

ശൂന്യം yuv420_rgba_lsx(
	uint32_t width, uint32_t height,
	സ്ഥിരം uint8_t *y, സ്ഥിരം uint8_t *v, സ്ഥിരം uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

ശൂന്യം yuv420_bgra_lsx(
	uint32_t width, uint32_t height,
	സ്ഥിരം uint8_t *y, സ്ഥിരം uint8_t *v, സ്ഥിരം uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

ശൂന്യം yuv420_argb_lsx(
	uint32_t width, uint32_t height,
	സ്ഥിരം uint8_t *y, സ്ഥിരം uint8_t *v, സ്ഥിരം uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

ശൂന്യം yuv420_abgr_lsx(
	uint32_t width, uint32_t height,
	സ്ഥിരം uint8_t *y, സ്ഥിരം uint8_t *v, സ്ഥിരം uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

#endif  //SDL_LSX_INTRINSICS
