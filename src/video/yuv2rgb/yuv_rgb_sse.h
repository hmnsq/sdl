#اگر_تعریف_شدہ SDL_SSE2_INTRINSICS

#شامل "yuv_rgb_common.h"

// yuv to rgb, sse implementation
// pointers must be 16 byte aligned, and strides must be divisable by 16
خالی yuv420_rgb565_sse(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuv420_rgb24_sse(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuv420_rgba_sse(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuv420_bgra_sse(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuv420_argb_sse(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuv420_abgr_sse(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuv422_rgb565_sse(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuv422_rgb24_sse(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuv422_rgba_sse(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuv422_bgra_sse(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuv422_argb_sse(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuv422_abgr_sse(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuvnv12_rgb565_sse(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuvnv12_rgb24_sse(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuvnv12_rgba_sse(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuvnv12_bgra_sse(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuvnv12_argb_sse(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuvnv12_abgr_sse(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

// yuv to rgb, sse implementation
// pointers do not need to be 16 byte aligned
خالی yuv420_rgb565_sseu(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuv420_rgb24_sseu(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuv420_rgba_sseu(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuv420_bgra_sseu(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuv420_argb_sseu(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuv420_abgr_sseu(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuv422_rgb565_sseu(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuv422_rgb24_sseu(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuv422_rgba_sseu(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuv422_bgra_sseu(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuv422_argb_sseu(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuv422_abgr_sseu(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuvnv12_rgb565_sseu(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuvnv12_rgb24_sseu(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuvnv12_rgba_sseu(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuvnv12_bgra_sseu(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuvnv12_argb_sseu(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);

خالی yuvnv12_abgr_sseu(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *y, ثابت uint8_t *u, ثابت uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        uint8_t *rgb, uint32_t rgb_stride,
        YCbCrType yuv_type);


// rgb to yuv, sse implementation
// pointers must be 16 byte aligned, and strides must be divisible by 16
خالی rgb24_yuv420_sse(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *rgb, uint32_t rgb_stride,
        uint8_t *y, uint8_t *u, uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        YCbCrType yuv_type);

// rgb to yuv, sse implementation
// pointers do not need to be 16 byte aligned
خالی rgb24_yuv420_sseu(
        uint32_t چوڑائی, uint32_t اونچائی,
        ثابت uint8_t *rgb, uint32_t rgb_stride,
        uint8_t *y, uint8_t *u, uint8_t *v, uint32_t y_stride, uint32_t uv_stride,
        YCbCrType yuv_type);
#اگر_ختم
