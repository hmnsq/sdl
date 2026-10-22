// Copyright 2016 Adrien Descamps
// Distributed under BSD 3-Clause License
#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_HAVE_YUV
#अन्तर्भाव "yuv_rgb_lsx.h"
#अन्तर्भाव "yuv_rgb_internal.h"

#यदि_परिभाषितम् SDL_LSX_INTRINSICS

#परिभाषय LSX_FUNCTION_NAME	yuv420_rgb24_lsx
#परिभाषय STD_FUNCTION_NAME	yuv420_rgb24_std
#परिभाषय YUV_FORMAT			YUV_FORMAT_420
#परिभाषय RGB_FORMAT			RGB_FORMAT_RGB24
#अन्तर्भाव "yuv_rgb_lsx_func.h"

#परिभाषय LSX_FUNCTION_NAME	yuv420_rgba_lsx
#परिभाषय STD_FUNCTION_NAME	yuv420_rgba_std
#परिभाषय YUV_FORMAT			YUV_FORMAT_420
#परिभाषय RGB_FORMAT			RGB_FORMAT_RGBA
#अन्तर्भाव "yuv_rgb_lsx_func.h"

#परिभाषय LSX_FUNCTION_NAME	yuv420_bgra_lsx
#परिभाषय STD_FUNCTION_NAME	yuv420_bgra_std
#परिभाषय YUV_FORMAT			YUV_FORMAT_420
#परिभाषय RGB_FORMAT			RGB_FORMAT_BGRA
#अन्तर्भाव "yuv_rgb_lsx_func.h"

#परिभाषय LSX_FUNCTION_NAME	yuv420_argb_lsx
#परिभाषय STD_FUNCTION_NAME	yuv420_argb_std
#परिभाषय YUV_FORMAT			YUV_FORMAT_420
#परिभाषय RGB_FORMAT			RGB_FORMAT_ARGB
#अन्तर्भाव "yuv_rgb_lsx_func.h"

#परिभाषय LSX_FUNCTION_NAME	yuv420_abgr_lsx
#परिभाषय STD_FUNCTION_NAME	yuv420_abgr_std
#परिभाषय YUV_FORMAT			YUV_FORMAT_420
#परिभाषय RGB_FORMAT			RGB_FORMAT_ABGR
#अन्तर्भाव "yuv_rgb_lsx_func.h"

#यदि_अन्तः  // SDL_LSX_INTRINSICS

#यदि_अन्तः // SDL_HAVE_YUV
