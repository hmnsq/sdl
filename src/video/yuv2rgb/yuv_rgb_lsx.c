// Copyright 2016 Adrien Descamps
// Distributed under BSD 3-Clause License
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_HAVE_YUV
#شامل "yuv_rgb_lsx.h"
#شامل "yuv_rgb_internal.h"

#اگر_تعریف_شدہ SDL_LSX_INTRINSICS

#تعریف_کرو LSX_FUNCTION_NAME	yuv420_rgb24_lsx
#تعریف_کرو STD_FUNCTION_NAME	yuv420_rgb24_std
#تعریف_کرو YUV_FORMAT			YUV_FORMAT_420
#تعریف_کرو RGB_FORMAT			RGB_FORMAT_RGB24
#شامل "yuv_rgb_lsx_func.h"

#تعریف_کرو LSX_FUNCTION_NAME	yuv420_rgba_lsx
#تعریف_کرو STD_FUNCTION_NAME	yuv420_rgba_std
#تعریف_کرو YUV_FORMAT			YUV_FORMAT_420
#تعریف_کرو RGB_FORMAT			RGB_FORMAT_RGBA
#شامل "yuv_rgb_lsx_func.h"

#تعریف_کرو LSX_FUNCTION_NAME	yuv420_bgra_lsx
#تعریف_کرو STD_FUNCTION_NAME	yuv420_bgra_std
#تعریف_کرو YUV_FORMAT			YUV_FORMAT_420
#تعریف_کرو RGB_FORMAT			RGB_FORMAT_BGRA
#شامل "yuv_rgb_lsx_func.h"

#تعریف_کرو LSX_FUNCTION_NAME	yuv420_argb_lsx
#تعریف_کرو STD_FUNCTION_NAME	yuv420_argb_std
#تعریف_کرو YUV_FORMAT			YUV_FORMAT_420
#تعریف_کرو RGB_FORMAT			RGB_FORMAT_ARGB
#شامل "yuv_rgb_lsx_func.h"

#تعریف_کرو LSX_FUNCTION_NAME	yuv420_abgr_lsx
#تعریف_کرو STD_FUNCTION_NAME	yuv420_abgr_std
#تعریف_کرو YUV_FORMAT			YUV_FORMAT_420
#تعریف_کرو RGB_FORMAT			RGB_FORMAT_ABGR
#شامل "yuv_rgb_lsx_func.h"

#اگر_ختم  // SDL_LSX_INTRINSICS

#اگر_ختم // SDL_HAVE_YUV
