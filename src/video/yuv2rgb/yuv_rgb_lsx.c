// Copyright 2016 Adrien Descamps
// Distributed under BSD 3-Clause License
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_HAVE_YUV
#અન્તર્ભાવ "yuv_rgb_lsx.h"
#અન્તર્ભાવ "yuv_rgb_internal.h"

#ifdef SDL_LSX_INTRINSICS

#define LSX_FUNCTION_NAME	yuv420_rgb24_lsx
#define STD_FUNCTION_NAME	yuv420_rgb24_std
#define YUV_FORMAT			YUV_FORMAT_420
#define RGB_FORMAT			RGB_FORMAT_RGB24
#અન્તર્ભાવ "yuv_rgb_lsx_func.h"

#define LSX_FUNCTION_NAME	yuv420_rgba_lsx
#define STD_FUNCTION_NAME	yuv420_rgba_std
#define YUV_FORMAT			YUV_FORMAT_420
#define RGB_FORMAT			RGB_FORMAT_RGBA
#અન્તર્ભાવ "yuv_rgb_lsx_func.h"

#define LSX_FUNCTION_NAME	yuv420_bgra_lsx
#define STD_FUNCTION_NAME	yuv420_bgra_std
#define YUV_FORMAT			YUV_FORMAT_420
#define RGB_FORMAT			RGB_FORMAT_BGRA
#અન્તર્ભાવ "yuv_rgb_lsx_func.h"

#define LSX_FUNCTION_NAME	yuv420_argb_lsx
#define STD_FUNCTION_NAME	yuv420_argb_std
#define YUV_FORMAT			YUV_FORMAT_420
#define RGB_FORMAT			RGB_FORMAT_ARGB
#અન્તર્ભાવ "yuv_rgb_lsx_func.h"

#define LSX_FUNCTION_NAME	yuv420_abgr_lsx
#define STD_FUNCTION_NAME	yuv420_abgr_std
#define YUV_FORMAT			YUV_FORMAT_420
#define RGB_FORMAT			RGB_FORMAT_ABGR
#અન્તર્ભાવ "yuv_rgb_lsx_func.h"

#endif  // SDL_LSX_INTRINSICS

#endif // SDL_HAVE_YUV
