#నిర్వచితమైతే SDL_LSX_INTRINSICS

#అన్తర్భావ "yuv_rgb_common.h"

//yuv420 to bgra, lsx implementation
శూన్య yuv420_rgb24_lsx(
	uint32_t వెడల్పు, uint32_t ఎత్తు,
	స్థిరరాశి uint8_t *y, స్థిరరాశి uint8_t *u, స్థిరరాశి uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

శూన్య yuv420_rgba_lsx(
	uint32_t వెడల్పు, uint32_t ఎత్తు,
	స్థిరరాశి uint8_t *y, స్థిరరాశి uint8_t *v, స్థిరరాశి uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

శూన్య yuv420_bgra_lsx(
	uint32_t వెడల్పు, uint32_t ఎత్తు,
	స్థిరరాశి uint8_t *y, స్థిరరాశి uint8_t *v, స్థిరరాశి uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

శూన్య yuv420_argb_lsx(
	uint32_t వెడల్పు, uint32_t ఎత్తు,
	స్థిరరాశి uint8_t *y, స్థిరరాశి uint8_t *v, స్థిరరాశి uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

శూన్య yuv420_abgr_lsx(
	uint32_t వెడల్పు, uint32_t ఎత్తు,
	స్థిరరాశి uint8_t *y, స్థిరరాశి uint8_t *v, స్థిరరాశి uint8_t *u, uint32_t y_stride, uint32_t uv_stride,
	uint8_t *rgb, uint32_t rgb_stride,
	YCbCrType yuv_type);

#అయితే_ముగింపు  //SDL_LSX_INTRINSICS
