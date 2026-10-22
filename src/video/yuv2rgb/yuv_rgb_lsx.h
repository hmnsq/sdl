#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_LSX_INTRINSICS

#ಅನ್ತರ್ಭಾವ "yuv_rgb_common.h"

//yuv420 to bgra, lsx implementation
ಶೂನ್ಯ yuv420_rgb24_lsx(
	uint32_t ಅಗಲ, uint32_t ಎತ್ತರ,
	ಸ್ಥಿರಾಂಕ uint8_t *y, ಸ್ಥಿರಾಂಕ uint8_t *u, ಸ್ಥಿರಾಂಕ uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

ಶೂನ್ಯ yuv420_rgba_lsx(
	uint32_t ಅಗಲ, uint32_t ಎತ್ತರ,
	ಸ್ಥಿರಾಂಕ uint8_t *y, ಸ್ಥಿರಾಂಕ uint8_t *v, ಸ್ಥಿರಾಂಕ uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

ಶೂನ್ಯ yuv420_bgra_lsx(
	uint32_t ಅಗಲ, uint32_t ಎತ್ತರ,
	ಸ್ಥಿರಾಂಕ uint8_t *y, ಸ್ಥಿರಾಂಕ uint8_t *v, ಸ್ಥಿರಾಂಕ uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

ಶೂನ್ಯ yuv420_argb_lsx(
	uint32_t ಅಗಲ, uint32_t ಎತ್ತರ,
	ಸ್ಥಿರಾಂಕ uint8_t *y, ಸ್ಥಿರಾಂಕ uint8_t *v, ಸ್ಥಿರಾಂಕ uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

ಶೂನ್ಯ yuv420_abgr_lsx(
	uint32_t ಅಗಲ, uint32_t ಎತ್ತರ,
	ಸ್ಥಿರಾಂಕ uint8_t *y, ಸ್ಥಿರಾಂಕ uint8_t *v, ಸ್ಥಿರಾಂಕ uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

#ಆದರೆ_ಅಂತ್ಯ  //SDL_LSX_INTRINSICS
