// Copyright 2016 Adrien Descamps
// Distributed under BSD 3-Clause License
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_HAVE_YUV
#അന്തര്ഭാവ "yuv_rgb_lsx.h"
#അന്തര്ഭാവ "yuv_rgb_internal.h"

#ifdef SDL_LSX_INTRINSICS

#define LSX_FUNCTION_NAME	yuv420_rgb24_lsx
#define STD_FUNCTION_NAME	yuv420_rgb24_std
#define YUV_FORMAT			YUV_FORMAT_420
#define RGB_FORMAT			RGB_FORMAT_RGB24
#അന്തര്ഭാവ "yuv_rgb_lsx_func.h"

#define LSX_FUNCTION_NAME	yuv420_rgba_lsx
#define STD_FUNCTION_NAME	yuv420_rgba_std
#define YUV_FORMAT			YUV_FORMAT_420
#define RGB_FORMAT			RGB_FORMAT_RGBA
#അന്തര്ഭാവ "yuv_rgb_lsx_func.h"

#define LSX_FUNCTION_NAME	yuv420_bgra_lsx
#define STD_FUNCTION_NAME	yuv420_bgra_std
#define YUV_FORMAT			YUV_FORMAT_420
#define RGB_FORMAT			RGB_FORMAT_BGRA
#അന്തര്ഭാവ "yuv_rgb_lsx_func.h"

#define LSX_FUNCTION_NAME	yuv420_argb_lsx
#define STD_FUNCTION_NAME	yuv420_argb_std
#define YUV_FORMAT			YUV_FORMAT_420
#define RGB_FORMAT			RGB_FORMAT_ARGB
#അന്തര്ഭാവ "yuv_rgb_lsx_func.h"

#define LSX_FUNCTION_NAME	yuv420_abgr_lsx
#define STD_FUNCTION_NAME	yuv420_abgr_std
#define YUV_FORMAT			YUV_FORMAT_420
#define RGB_FORMAT			RGB_FORMAT_ABGR
#അന്തര്ഭാവ "yuv_rgb_lsx_func.h"

#endif  // SDL_LSX_INTRINSICS

#endif // SDL_HAVE_YUV
