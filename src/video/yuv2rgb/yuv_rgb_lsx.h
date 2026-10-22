#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_LSX_INTRINSICS

#ਅਨ੍ਤਰ੍ਭਾਵ "yuv_rgb_common.h"

//yuv420 to bgra, lsx implementation
ਖਾਲੀ yuv420_rgb24_lsx(
	uint32_t ਚੌੜਾਈ, uint32_t ਉਚਾਈ,
	ਅਚਲ uint8_t *y, ਅਚਲ uint8_t *u, ਅਚਲ uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

ਖਾਲੀ yuv420_rgba_lsx(
	uint32_t ਚੌੜਾਈ, uint32_t ਉਚਾਈ,
	ਅਚਲ uint8_t *y, ਅਚਲ uint8_t *v, ਅਚਲ uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

ਖਾਲੀ yuv420_bgra_lsx(
	uint32_t ਚੌੜਾਈ, uint32_t ਉਚਾਈ,
	ਅਚਲ uint8_t *y, ਅਚਲ uint8_t *v, ਅਚਲ uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

ਖਾਲੀ yuv420_argb_lsx(
	uint32_t ਚੌੜਾਈ, uint32_t ਉਚਾਈ,
	ਅਚਲ uint8_t *y, ਅਚਲ uint8_t *v, ਅਚਲ uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

ਖਾਲੀ yuv420_abgr_lsx(
	uint32_t ਚੌੜਾਈ, uint32_t ਉਚਾਈ,
	ਅਚਲ uint8_t *y, ਅਚਲ uint8_t *v, ਅਚਲ uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

#ਜੇ_ਅੰਤ  //SDL_LSX_INTRINSICS
